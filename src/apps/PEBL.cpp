//* -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*- */
/////////////////////////////////////////////////////////////////////////////////
//    Name:       src/apps/PEBL.cpp
//    Purpose:    The primary PEBL run-time interpreter.
//    Author:     Shane T. Mueller, Ph.D.
//    Copyright:  (c) 2003-2005 Shane T. Mueller <smueller@obereed.net>
//    License:    GPL 2
//
//   
//
//     This file is part of the PEBL project.
//
//    PEBL is free software; you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation; either version 2 of the License, or
//    (at your option) any later version.
//
//    PEBL is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with PEBL; if not, write to the Free Software
//    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
////////////////////////////////////////////////////////////////////////////////

#include "../base/Evaluator.h"
#include "../base/grammar.tab.hpp"
#include "../base/PNode.h"
#include "../base/Loader.h"
#include "../base/PComplexData.h"
#include "../base/PList.h"
#include "../base/FunctionMap.h"
#include "../base/VariableMap.h"
#include "../base/Variant.h"

#include "../libs/PEBLObjects.h"

#include "../utility/PError.h"
#include "../utility/PEBLPath.h"
#include "../utility/PEBLUtility.h"
#include "../utility/rc_ptrs.h"

#include "../devices/PEventLoop.h"
#include "Globals.h"

#include <iostream>
#include <signal.h>
#include <list>

//Unix-specific definitions
#if defined(PEBL_UNIX)
//For running at higher priority:
#include <sys/resource.h>   
//For better fifo scheduling.
#include <sched.h>  

#elif defined(PEBL_WIN32)
//For running at higher priority.
#include <windows.h>
#endif

#ifdef WIN32
#include <time.h>
#endif


using std::cerr;
using std::endl;


/// This is the main PEBL interpreter program. It takes files as command-line arguments,
/// which it parses with the bison parser, creating a single tree of PNodes.  Then, it feeds
/// this tree into the loader, which loads the individual functions into a function map.  Then, 
/// it sets up any global entities:  a graphical environment, a timer, a global variable map.
/// Finally, it locates the 'Start' function and executes it.


//Prototype for c function defined in grammar.y:
PNode *  parse(const char* filename);
std::list<string> GetFiles(int argc, char * argv[]);
void  PrintOptions();
   
///Initiate some static member data.
FunctionMap Evaluator::mFunctionMap;
PEventLoop Evaluator::mEventLoop; 
VariableMap Evaluator::gGlobalVariableMap;
const PNode * Evaluator::gEvalNode = NULL;
PEBLPath  Evaluator::gPath;
PCallStack Evaluator::gCallStack;

Loader* myLoader;
PNode * head;

//std::list<PNode> PError::gCallStack;


int PEBLInterpret( int argc, char *argv[] )
{ 
    
    PNode * tmp = NULL;
    
    //Cycle through command-line parameters extracting the files.
    //This does not check for file validity, it just removes any other command-line options,
    //i.e. ones that are of the form <-flag> <option> or whatever.
    std::list<std::string> files = GetFiles(argc, argv);

    //Set up the search path.
    Evaluator::gPath.Initialize(files);
    
    cerr << Evaluator::gPath;

    //Add the built-in PEBL libraries to the files list.
    files.push_back("Design.pbl");
    files.push_back("Utility.pbl");
    files.push_back("Math.pbl");

    //Process the first command-line argument.
    std::list<std::string>::iterator i = files.begin();
    //Skip ahead one on the list; the first one is the executable's name
    i++;


    //-----------------------------------------------------------
    //        Process all files on the command-line
    //-----------------------------------------------------------
	//std::cout << *i << endl;
	string inputfilename = Evaluator::gPath.FindFile(*i);
    head = NULL;
    if(inputfilename != "")
        {
            cerr << "Processing PEBL Source File: " <<  inputfilename << endl;
            head  = parse(inputfilename.c_str());
        }
    else
        {
            PError::SignalFatalError("Unable to find file: " + inputfilename);
        }
    
    //If there are any more arguments, process them by accomodating them
    //inside a function list.
    
    //Increment the iterator to move to the second command-line 
    i++;
    while(i != files.end())
        {
            inputfilename = Evaluator::gPath.FindFile(*i);
            if(inputfilename != "")
                {
                    cerr << "Processing PEBL Source File: " <<  inputfilename << endl;
                    
                    //A filename could be a directory (e.g., with media in it.)  
                    //If so, don't parse it.
                    if(!Evaluator::gPath.IsDirectory(inputfilename))
                        {
                            //Make a new node.
                            tmp = parse(inputfilename.c_str());
                            
                            //Now, make a new node that contains head and tmp.
                            head = new OpNode(PEBL_FUNCTIONS, head, tmp, "INTERNAL PEBL STRUCTURE", -1);
                        }
                }
            else
                {
                    PError::SignalFatalError("Unable to find file: " + inputfilename);

                }
            i++;
       }
    
    //       Done processing files.
    //------------------------------------------------------

    
    cerr << "---------Loading Program---------" << endl;     
    //Now, load it into the environment:
 
    // Create a loader that will load functions into the functionmap 
    myLoader = new Loader(); 
    myLoader->LoadUserFunctions((OpNode*)head);


    cerr <<"Analyzing code for functions." << endl;
    myLoader->FindFunctions(head);


    cerr << "Loading Library functions." << endl;
    myLoader->LoadLibraryFunctions();

    //This just destroys the function tree, not the
    //parsed node structure that is contained within
    //mFunctionMap.
    cerr << "Removing residual function tree\n";
    ((OpNode*)head)->DestroyFunctionTree();
    delete head;
    head = NULL;


    cerr << "\n\n--------------------------------\n";
    cerr << "Functions used in program: " << endl;
    cerr << "--------------------------------\n";
    Evaluator::mFunctionMap.DumpValues();
    cerr << "--------------------------------\n\n";


    //Parse command-line arguments.

    PList *  pList =  new PList();
    PList *  arglist = new PList();
    std::string displaySize="640x480";
    std::string depth = "16";
    enum PEBLVideoMode displayMode;
    enum PEBLVideoDepth displayDepth;
    bool windowed = true;
    Variant subnum = 0;
    //Extract the command-line variables to bind   
    for(int j = 1; j < argc; j++)
        {
            
            if(strcmp(argv[j], "-v")==0 ||
               strcmp(argv[j], "-V")==0)
                {
                    Variant tmp = argv[++j];
                    arglist->PushBack(tmp);
                }

            else if(strcmp(argv[j], "-s")==0 ||
                    strcmp(argv[j], "-S")==0)
                {
                    subnum  = argv[++j];
                }
            //set the driver directly from the command-line, if necessary.
            else if(strcmp(argv[j],"--driver")==0)
                {
                    if(j+1 < argc)
                        {
                            j++;
                            
                            //This now works on Windows; windib versus directx.
#if defined(PEBL_UNIX)
                            setenv("SDL_VIDEODRIVER", argv[j] ,1);
#else
                            _putenv((std::string("SDL_VIDEODRIVER=") + std::string(argv[j])).c_str());
#endif
                        }
                }
            else if(strcmp(argv[j],"--display")==0)
                {
                    displaySize = argv[++j];
                }
            
            else if(strcmp(argv[j],"--depth")==0)
                {
                    depth = argv[++j];
                    
                }
            
            else if (strcmp(argv[j],"--fullscreen")==0)
                {
                    windowed = false;
                }
            else if(strcmp(argv[j],"--windowed")==0)
                {
                    windowed = true;
                }
        }
            

    //Now, set the display modes variables based on the command-line options.
    displayMode = PEBLUtility::GetVideoMode(displaySize);
    displayDepth = PEBLUtility::GetVideoDepth(depth);
    
    
    
    //This sets the video driver, and other platform-specific stuff.
#if defined(PEBL_UNIX)
    //Do specific *nix stuff here (excluding OSX).    

    //These can be controlled by a command-line option
    // setenv("SDL_VIDEODRIVER", "dga",1);  //Requires root privileges to run;  fullscreen.
    // setenv("SDL_VIDEODRIVER", "svgalib",1);  //Requires root and special library
    // setenv("SDL_VIDEODRIVER", "x11",1);

    
    //Now, set the priority to the highest it can go.

    //setpriority(PRIO_PROCESS,0,PRIO_MIN);
    setpriority(PRIO_PROCESS,0,0);
    int priority = getpriority(PRIO_PROCESS,0);
    cerr << "Process running at a nice value of " << priority << endl;
    
    /*
      struct sched_param mysched;
      mysched.sched_priority = sched_get_priority_max(SCHED_FIFO) - 1;
      if( sched_setscheduler( 0, SCHED_RR, &mysched ) == -1 ) 
      {
      cout << "Unable to enable round-robin scheduling.  Must have root priviledges.\n";
      }
      else
      {
      cout << "Round-robin scheduling enabled.\n";
      }
      
      struct timespec interval;
      if(sched_rr_get_interval(0,&interval)== -1)
      {
      cout << "Unable to get Round-robin scheduling interval.\n";
      }
      else
      {
      cout << "Round Robin Scheduling Interval: [" <<interval.tv_sec * 1000 + interval.tv_nsec / 1000 <<"] ms.\n";
      }
      
    */
    

#elif defined(PEBL_WIN32)
     //Do specific win32 stuff here.
    
    //SetPriorityClass(GetCurrentProcess(),REALTIME_PRIORITY_CLASS);
    //REALTIME causes program to hang on keyboard input.
    SetPriorityClass(GetCurrentProcess(),HIGH_PRIORITY_CLASS);
       
    //setenv()
#endif


    PEBLObjects::MakeEnvironment(displayMode, displayDepth, windowed);

    //Seed the random number generator with time of day.
    //May not be cross-platform.
    srand(time(0));

    cerr << "---------Creating Evaluator-----" << endl;
    //Create evaluator, because it contains a function map as a static member variable.
    //Create it with the command-line -v parameters as a list  bound to the argument.


    //Now, arglist should contain any values specified with the -v flag.
    if(arglist->Length()==0)
        {
            arglist->PushBack(Variant(0));
            PComplexData * pcd = new PComplexData(counted_ptr<PEBLObjectBase>(arglist));
            pList->PushFront(Variant(pcd));
        }
    else
        {
            PComplexData * pcd = new PComplexData(counted_ptr<PEBLObjectBase>(arglist));
            pList->PushFront(Variant(pcd));
        }
        
    PComplexData * pcd = new PComplexData(counted_ptr<PEBLObjectBase>(pList));
    Variant v = Variant(pcd);
    

    std::list<PNode> tmpcallstack;
    Evaluator myEval = Evaluator(v,"Start");



    //Add the subject identifier.
    Evaluator::gGlobalVariableMap.AddVariable("gSubNum",subnum);



    //Now, everything should be F-I-N-E fine.
    head = myLoader->GetMainPEBLFunction();

    if(head) 
        {
            cerr << "---------Evaluating Program-----" << endl;
            //Execute everything

            myEval.Evaluate(head);

            delete myLoader; 
            
            Evaluator::mFunctionMap.Destroy();
            
            return 0;
        }
    else
        {
            cerr << "Error: Can't evaluate program" << endl;
            return 1;
            delete myLoader;
        }

        }

    void  CaptureSignal(int signal)
{
    cerr << "Exiting PEBL because of captured signal.\n";

    delete myLoader;
    raise(signal);

    exit(0);
}


int main(int argc,  char *argv[])
{

    
    //  Set up some signals to capture  
#ifdef SIGHUP
    signal(SIGHUP, CaptureSignal);
#endif

#ifdef SIGKILL
    signal(SIGKILL, CaptureSignal);
#endif

#ifdef SIGSTOP
    signal(SIGSTOP, CaptureSignal);
#endif

#ifdef SIGTERM
    signal(SIGTERM, CaptureSignal);
#endif

    signal(SIGINT, CaptureSignal);


#ifdef SIGQUIT
    signal(SIGQUIT, CaptureSignal);
#endif


    signal(SIGTERM, CaptureSignal);
    

    if(argc == 1)
        {
            PrintOptions();
            return 1;
        }
    return PEBLInterpret(argc, argv);
}


//This returns a list of the files listed on the command-line.
std::list<std::string> GetFiles(int argc,  char * argv[])
{

    std::list<std::string> tmp;
    for(int i = 0; i < argc; i++)
        {
            if(strcmp(argv[i], "-v")==0 ||
               strcmp(argv[i], "-V")==0 || 
               strcmp(argv[i], "-s")==0 ||
               strcmp(argv[i], "-S") == 0)
                {
                    //This is the variable switch.  get rid of it and the next argument.
                    i++;
                }
            else if (strcmp(argv[i],"--driver")==0 ||
                     strcmp(argv[i],"--display")==0 ||
                     strcmp(argv[i],"--depth")==0 )
                {
                    //This is a video driver switch.
                    i++;
                }
            else if (strcmp(argv[i],"--windowed")==0 ||
                     strcmp(argv[i],"--fullscreen")==0 )
                {
                    //Don't bother incrementing 'i'
                }
            else
                {

                    tmp.push_back(std::string(argv[i]));
                }
            
        }
    return tmp;
}

void PrintOptions()
{
    cout << "-------------------------------------------------------------------------------\n";
    cout << "PEBL: The Psychology Experiment Building Language\n";
    cout << "Version 0.07\n";
    cout << "(c) 2003-2006 Shane T. Mueller, Ph.D.\n";
    cout << "smueller@obereed.net   http://pebl.sf.net\n";
    cout << "-------------------------------------------------------------------------------\n";

    cout << "Usage:  Invoke pebl with the experiment script files (.pbl) and command-line\n";
    cout << "arguments.\n\n";
    cout << "example: pebl experiment.pbl -v sub1 --fullscreen --display 800x600 --driver dga\n\n";
    cout << "COMMAND-LINE OPTIONS:\n";
    cout << "-v VALUE1 -v VALUE2\n";
    cout << "  Invokes script and passes VALUE1 and VALUE2 (and any text immediately\n" ;
    cout << "  following -v) to a list in the argument of the Start() function.\n\n";
    cout << "-s IDENTIFIER\n";
    cout << "  Initiates the global variable gSubNum to IDENTIFIER.  If not set here,\n";
    cout << " gSubNum is initiated to 0.\n\n";
    cout << "--driver <drivername>\n";
    cout << "  Sets the video driver, when there is a choice.  For linux SDL, options xf86,\n";
    cout << "  dga, svgalib (from console).  Also controlled via environment variables.\n\n";
    cout << "--display  <widthxheight>\n";
    cout << "  Controls the screen width and height (in pixels). Defaults to 640x480.\n";
    cout << "  Currently, only the following screens are supported:\n";
    cout << "  		512x384\n";
    cout << "  		640x480\n";
    cout << "  		800x600\n";
    cout << "  		960x720\n";
    cout << "  		1024x768\n";
    cout << "  		1152x864\n";
    cout << "  		1280x1024\n";
    cout << "  Note: the way this is invoked may be changed in the future.\n\n";
    cout << "--depth\n";
    cout << "  Controls the pixel depth.  Depends on your video card.  Currently,\n";
    cout << "  depths of 2,8,15,16,24, and 32 are allowed on the command-line.\n";
    cout << "--windowed\n";
    cout << "--fullscreen\n";
    cout << "  Controls whether the script will run in a window or fullscreen.\n\n";

}
