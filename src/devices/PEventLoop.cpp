//* -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*- */
/////////////////////////////////////////////////////////////////////////////////
//    Name:       src/devices/PEventLoop.cpp
//    Purpose:    Primary generic timer event device
//    Author:     Shane T. Mueller, Ph.D.
//    Copyright:  (c) 2003-2004 Shane T. Mueller <smueller@obereed.net>
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
#include "PEventLoop.h"
#include "PDevice.h"
#include "PEventQueue.h"
#include "../platforms/sdl/PlatformEventQueue.h"
#include "../base/FunctionMap.h"
#include "../base/Evaluator.h"
#include "../base/PComplexData.h"


#include "../libs/PEBLEnvironment.h"
#include <iostream>


extern PlatformEventQueue * gEventQueue;

/// This is the standard PEventLoop constructor
PEventLoop::PEventLoop()
{

}

/// This is the standard pNode destructor
PEventLoop::~PEventLoop()
{
    // Standard Destructor
}



/// This function will 'register' a specific event that will be tested for
/// in an event-loop.  This allows multiple tests to be registered (time limit, key press, etc.)
/// and tested within a fairly tight compiled loop, without the user having to write his/her own 
/// interpreted event loop.
void PEventLoop::RegisterState(DeviceState * state, const std::string & function, PList * parameters)
{

    //Add the state to the states list.
    mStates.push_back(state);
    //Make a PNode representing the function. If the function-name is null, push a
    //null PNode onto the vector; this is a short-cut for an end-of-loop event.
    if(function != "")
        {
            PNode * node = Evaluator::mFunctionMap.GetFunction(function);
            mNodes.push_back(node);
        }
    else
        {

            mNodes.push_back(NULL);
        }
    //Add parameters, for use later.
    mParameters.push_back(parameters);
    mIsEvent.push_back(false);
}

/// This function will 'register' a specific event that will be tested for
/// in an event-loop.  This allows multiple tests to be registered (time limit, key press, etc.)
/// and tested within a fairly tight compiled loop, without the user having to write his/her own 
/// interpreted event loop.

/// This method takes over ownership of the DeviceState, and is responsible for cleaning it up 
/// when finished.
void PEventLoop::RegisterEvent(DeviceState * state, const std::string &  function, PList * parameters)
{
    //Add the state to the states list.
    mStates.push_back(state);
    //Make a PNode representing the function. If the function-name is null, push a
    //null PNode onto the vector; this is a short-cut for an end-of-loop event.
    if(function != "")
        {
            PNode * node = Evaluator::mFunctionMap.GetFunction(function);
            mNodes.push_back(node);
        }
    else
        {

            mNodes.push_back(NULL);
        }
    //Add parameters, for use later.
    mParameters.push_back(parameters);
    mIsEvent.push_back(true);
}



void PEventLoop::Clear()
{

    //When the eventloop is Clear()ed, the states should be deleted one-by-one,
    //to avoid a memory leak.
    
    std::vector<DeviceState*>::iterator i = mStates.begin();
    while(i != mStates.end())
        {
            delete *i;
            i++;
        }

    mStates.clear();
    mNodes.clear();
    mParameters.clear();
    mIsEvent.clear();
}


/// The following method will initiate an event loop.  It will repetitively
/// cycle through each of the devices-events registered and determine if any are 
/// satisfied.  Whenever one is satisfied, it will follow the directive of that
/// event.  It will continue until a STOPEVENTLOOP event is processed.
PEvent PEventLoop::Loop()
{
    Evaluator * myEval = new Evaluator();
    unsigned int i, result =0;
    PEvent returnval(PDT_UNKNOWN,0);

    //Enter a variable into the global variable map.  The loop will exit
    //when this is set false.
    myEval->gGlobalVariableMap.AddVariable("gKeepLooping", 1);

    //cout <<"*****" <<myEval->gGlobalVariableMap.RetrieveValue("gKeepLooping") << "--"<< mStates.size() << endl;

    //while loop stops when gKeepLooping turns false or there are no more states to check for.
    while(myEval->gGlobalVariableMap.RetrieveValue("gKeepLooping") 
          && mStates.size() != 0)
        {
            
            //At the beginning of a cycle, the event queue has not yet been primed.
            gEventQueue->Prime();
            
            //Scan through each event in the event vector.         
            for(i = 0; i < mStates.size(); i++)
                {

                    if(mIsEvent[i])   //The test is for an event queue-type event.
                        {
                            //Only test the event if the queue is not empty.
                            if(!gEventQueue->IsEmpty())
                                {
                                    //Now, we only should test an event if it is the proper device type.
                                    if(gEventQueue->GetFirstEventType() == mStates[i]->GetDeviceType())
                                        {
                                            //Now, just test the device.
                                            
                                            result = mStates[i]->TestDevice();
                                            
                                            if(result)
                                                {
                                                    returnval = gEventQueue->GetFirstEvent();
                                                    
                                                    //The test was successful.  Add a global variable giving the time of the event.
                                                    
                                                    // myEval->gGlobalVariableMap.AddVariable("gLastEventTime", eventQueue->GetFirstEvent().GetTime());
                                                    if(mNodes[i])  //Execute mNodes
                                                        {
                                                            //Add the parameters, as a list, to the stack.
                                                            counted_ptr<PList> tmpList = counted_ptr<PList>(mParameters[i]);
                                                            counted_ptr<PComplexData> pcd = counted_ptr<PComplexData>(new PComplexData(tmpList));
                                                            myEval->Push(Variant(pcd));
                                                            myEval->Evaluate(mNodes[i]);
                                                            
                                                        }
                                                    else                                             //If mNodes[i] is null, terminate
                                                        {
                                                            myEval->gGlobalVariableMap.AddVariable("gKeepLooping", 0);
                                                            
                                                        }
                                            goto end;
                                                }
                                        }
                                }
                        }
                    else
                        {
                            //The test exmanines the device's state directly.
                            
                            result = mStates[i]->TestDevice();
                            if(result)
                                {
                                    //We need to create a 'dummy' event to use here.
                                    PEBL_DummyEvent pde;
                                    pde.value = mStates[i]->GetInterface();

                                    //time needs to go in  the 0 below.
                                    returnval = PEvent(PDT_DUMMY,0);
                                    returnval.SetDummyEvent(pde);

                                    //If mNodes[i] is null, terminate
                                    if(mNodes[i])
                                        {
                                            //Add the parameters, as a list, to the stack.
                                            counted_ptr<PList> tmpList = counted_ptr<PList>(mParameters[i]);
                                            counted_ptr<PComplexData>  pcd =counted_ptr<PComplexData>(new PComplexData(tmpList));
                                            myEval->Push(Variant(pcd));
                                            myEval->Evaluate(mNodes[i]);
                                        }
                                    else
                                        {
                                            myEval->gGlobalVariableMap.AddVariable("gKeepLooping", 0);

                                        }
                                    goto end;                                    
                                    
                                }
                        }

                }
        end:
            //Get rid of the top item in the event queue
            gEventQueue->PopEvent();

        }

    delete myEval;
    return returnval;
}


//Overload of the << operator
std::ostream & operator <<(std::ostream & out, const PEventLoop & loop )
{

    out << "PEBL Event Loop:" << flush;
    
    return out;
}
