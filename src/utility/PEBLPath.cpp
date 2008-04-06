//* -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*- */
/////////////////////////////////////////////////////////////////////////////////
//    Name:       src/utility/PEBLPath.cpp
//    Purpose:    Utility class storing search path and searching for files there
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

#include "PEBLPath.h"
#include "../base/Variant.h"
#include "PError.h"
#include "BinReloc.h"

#include <sys/stat.h>
#include <list>
#include <string>
#include <iostream>

using std::endl;
using std::string;
using std::ostream;
using std::cout;

PEBLPath::PEBLPath()
{
}


void PEBLPath::Initialize(std::list<std::string> files)
{
	//std::cout << "Initializing path\n";
#if defined PEBL_UNIX
    //On unix, add the following paths:
    //current working directory,
    AddToPathList("./");
    
    //Look for absolute pathnames
    AddToPathList("");
    //The directories of each file on the command-line.
    string tmp;
    std::list<string>::iterator i=files.begin();
    i++;  //skip over the command name in UNIX.
    while(i != files.end())
        {
            //For each commandline argument, strip the filename and add it.
            tmp = StripFile(*i);
            if(tmp != "")
                {
                    AddToPathList(tmp);
                }
            i++;
        }

    string basedir = "";
    //Initialize the binreloc library (courtesy of autopackage).
    BrInitError error; 
    if (br_init (&error) == 0 && error != BR_INIT_ERROR_DISABLED) 
        { 
            PError::SignalWarning("Warning: BinReloc failed to initialize.\n Will fallback to hardcoded default path.\n"); 
            basedir = "/usr/local/share/pebl/";
        } else {

            std::cerr << "Executable file located at: [" << br_find_exe("") << "].\n";
            string prefix = br_find_prefix("/usr/local/");
            basedir = prefix + string("/share/pebl/");
            
        }

        
    
    //media subdirectories of execution directory.
    //fonts
    AddToPathList(MergePathAndFile(basedir, "media/fonts/"));
    
    //Sounds
    AddToPathList(MergePathAndFile(basedir, "media/sounds/"));
    
    //images
    AddToPathList(MergePathAndFile(basedir, "media/images/"));
    
    //text
    AddToPathList(MergePathAndFile(basedir, "media/text/"));
    
    //library functions
    AddToPathList(MergePathAndFile(basedir, "pebl-lib/"));

/*#elif defined(PEBL_WIN32) or defined(WIN32)*/
#else
	//On Windows add the following paths:

    //current working directory
    AddToPathList(".\\");
    
    //Absolute Pathnames
    AddToPathList("");
    
    //The base directory is the parent of the executable's directory.
    string basedir = StripFile(files.front()) + "..\\";

    //The directories of each file on the command-line.
    // files[0] is the execution directory, 
    // the others are filenames.
    string tmp;
    std::list<string>::iterator i=files.begin();
    while(i != files.end())
        {
            //For each commandline argument, strip the filename and add it.
            tmp = StripFile(*i);
            if(tmp != "")
                {
                    AddToPathList(tmp);
                }
            i++;
        }

    
    //media subdirectories of execution directory.
    //fonts
    AddToPathList(MergePathAndFile(basedir, "media\\fonts\\"));
    
    //Audio
    AddToPathList(MergePathAndFile(basedir, "media\\sounds\\"));
    
    //images
    AddToPathList(MergePathAndFile(basedir, "media\\images\\"));
    
    //Text files
    AddToPathList(MergePathAndFile(basedir, "media\\text\\"));
    
    //PEBL Library functions
    AddToPathList(MergePathAndFile(basedir, "pebl-lib\\"));

 
#endif
    
    
}

PEBLPath::~PEBLPath()
{
    mPathList.clear();
}


//Note: paths should be added with a '/' afterwards
void PEBLPath::AddToPathList(const  string & pathname)
{

    mPathList.push_back(pathname);
}


string  PEBLPath::FindFile(const string & filename)
{

    std::list<string>::const_iterator p = mPathList.begin();
    
    struct stat st;
    
    int lengthp;
    int lengthfilename;
    string tmp;
   while(p != mPathList.end())
       {
           lengthp = (*p).size(); 
           lengthfilename = filename.size();
           
           tmp = (*p) + filename;
               

               //Check to see if the file exists.
               if(stat(tmp.c_str(), &st)==0)
                   {
                       //The file exists, so return it
                       return tmp;
                   }

           //otherwise, increment and try again.
           p++;
       }
   //If everything fails, return "".
   return "";
}


//When given a filename, this will strip the filename from 
//the path and return the path. If given a directory name 
// (ending with a '/' or '\'), it won't strip that character.
const string PEBLPath::StripFile(const string &  file)
{
#if defined PEBL_UNIX
    char separator = '/';
#else
    char separator = '\\';
#endif
    
    int lastsep  = 0;
    int i = file.size();
    //end 
    //Start at the end of the filename and move backward
    while(i > 0)
        {
            if(file[i] == separator)
                {
                    lastsep = i;
                    return file.substr(0,lastsep+1);
                }
            i--;
        }
    return "";
}

const string PEBLPath::MergePathAndFile(const string & path, const string &  file)
{
    return path + file;
}


bool PEBLPath::IsDirectory(const string & pathname)
{
#if defined PEBL_UNIX
    char separator = '/';
#elif defined PEBL_WIN32 
    char separator = '\\';
#elif defined WIN32
	char separator = '\\';
#endif
    

    //This may not be the best way to do it; we maybe
    //should check to see using OS library calls.
    if(pathname[pathname.size()-1] == separator)
        return true;
    else
        return false;
    
}


ostream & PEBLPath::Print(ostream & out) const
{

    out << "--------------------------------------\n";
    out << "Path List:\n"; 
    std::list<string>::const_iterator p = mPathList.begin();
    while(p != mPathList.end())
        {
            out << *p << endl;
            p++;
        }
    
    out << "--------------------------------------\n";
    return out;
}

ostream & operator << (ostream & out, const PEBLPath & path)
{
    return path.Print(out);

}
