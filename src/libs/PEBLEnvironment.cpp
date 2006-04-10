//* -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*- */
/////////////////////////////////////////////////////////////////////////////////
//    Name:       src/libs/PEBLEnvironment.cpp
//    Purpose:    General Environment Function Library for PEBL
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
#include "PEBLEnvironment.h"
#include "PEBLObjects.h"

#include "../base/Variant.h"
#include "../base/PList.h"
#include "../base/PComplexData.h"
#include "../base/Evaluator.h"

#include "../utility/PError.h"
#include "../utility/PEBLUtility.h"
#include "../utility/rc_ptrs.h"

#include "../devices/PTimer.h"
#include "../devices/DeviceState.h"
#include "../devices/PEventLoop.h"

#include "../objects/PTextBox.h"

#include "../platforms/sdl/PlatformTimer.h"
#include "../platforms/sdl/PlatformKeyboard.h"
#include "../platforms/sdl/PlatformTextBox.h" 
#include "../platforms/sdl/PlatformEventQueue.h"

#include <ctime>
#include <string>

using std::string;

/// The following initiates classes used by functions in the Environment library.
namespace PEBLEnvironment
{
    PlatformTimer myTimer;
    PlatformKeyboard myKeyboard;

}

extern PlatformEnvironment * myEnv;
extern PlatformEventQueue  * gEventQueue;

/// This function moves a widget to a new location.
Variant PEBLEnvironment::GetTime(Variant v)
{
   //v should have no parameters

    //get the time from timer object.
    return Variant(myTimer.GetTime());
}


Variant  PEBLEnvironment::Wait(Variant v)
{


    //v[1] should have the parameter
    PList * plist = v.GetComplexData()->GetList();


    PError::AssertType(plist->First(), PEAT_NUMBER, "Argument error in function [Wait(<number>)]: ");
    int delay = plist->First(); plist->PopFront();
    delay += myTimer.GetTime();
    //Create a timer test correspending to keydown.
    //1 is the value (down), DT_GREATER_THAN is the test, key is the interface (e.g., the 'A' key)
    PDevice * device = new PlatformTimer(myTimer);
    ValueState  * state = new ValueState(delay, DT_GREATER_THAN_OR_EQUAL, 1,device, PDT_TIMER);
    //NULL,NULL will terminate the looping
    string funcname = "";
    PList* params = NULL;
    Evaluator::mEventLoop.RegisterState(state, funcname, params);
    PEvent returnval = Evaluator::mEventLoop.Loop();
    //Now, clear the event loop tests
    Evaluator::mEventLoop.Clear();
    delete device;

    return Variant(returnval.GetDummyEvent().value);
}


Variant PEBLEnvironment::IsKeyDown(Variant v)
{
    //v[1] should have the parameter-a letter
     PList * plist = v.GetComplexData()->GetList();
    PError::AssertType(plist->First(), PEAT_STRING, "Argument error in function [IsKeyDown(<string>)]: ");    

    std::string mystring = plist->First(); plist->PopFront();
    PEBLKey key = PEBLUtility::TranslateString(mystring);

    return Variant(myKeyboard.IsKeyDown(key));
}




Variant PEBLEnvironment::IsKeyUp(Variant v)
{
    PList * plist = v.GetComplexData()->GetList();
   //v[1] should have the parameter-a letter

    PError::AssertType(plist->First(), PEAT_STRING, "Argument error in function [IsKeyUp(<string>)]:  ");    

    string mystring = plist->First(); plist->PopFront();
    PEBLKey key = PEBLUtility::TranslateString(mystring);

    return Variant(myKeyboard.IsKeyUp(key));
}



Variant PEBLEnvironment::IsAnyKeyDown(Variant v)
{
    //This shouldn't receive any arguments    

    return Variant(myKeyboard.IsKeyDown(PEBLKEY_ANYKEY));
}

Variant PEBLEnvironment::ShowCursor(Variant v)
{
    PList * plist = v.GetComplexData()->GetList();
    PError::AssertType(plist->First(), PEAT_INTEGER, "Argument error in function [ShowCursor(<bool>)]: ");
    int val = plist->First();
    return Variant(myEnv->ShowCursor(val));
}


/// This function uses the event loop to schedule a single
/// device-test, which checks for the selected key.
Variant PEBLEnvironment::WaitForKeyDown(Variant v)
{

    //v[1] should have the parameter-a letter
    PList * plist = v.GetComplexData()->GetList();

    PError::AssertType(plist->First(), PEAT_STRING, "Argument error in function [WaitForKeyDown(<string>)]:  ");    

    string mystring = plist->First(); plist->PopFront();
    PEBLKey key = PEBLUtility::TranslateString(mystring);
    
 
    //Create a keyboard test correspending to keydown. 
    //1 is the value (down), DT_EQUAL is the test, key is the interface (e.g., the 'A' key) 
    PDevice * device = new PlatformKeyboard(myKeyboard);
    ValueState  * state = new ValueState(1, DT_EQUAL, key, device, PDT_KEYBOARD);

    //NULL,NULL will terminate the looping
    string  funcname = "";
    PList* params = NULL;
    Evaluator::mEventLoop.RegisterState(state,funcname, params);
    PEvent returnval = Evaluator::mEventLoop.Loop();

    //Now, clear the event loop tests
    Evaluator::mEventLoop.Clear();

    return Variant(returnval.GetDummyEvent().value);
}



Variant PEBLEnvironment::WaitForKeyUp(Variant v)
{

    //v[1] should have the parameter-a letter
    PList * plist = v.GetComplexData()->GetList();

    PError::AssertType(plist->First(), PEAT_STRING, "Argument error in function [WaitForKeyUp(<string>)]:  ");    

    string mystring = plist->First(); plist->PopFront();
    PEBLKey key = PEBLUtility::TranslateString(mystring);
    

    //Create a keyboard test correspending to keydown. 
    //1 is the value (down), DT_NOT_EQUAL is the test, key is the interface (e.g., the 'A' key) 
    PDevice * device = new PlatformKeyboard(myKeyboard);
    ValueState  * state = new ValueState(1, DT_NOT_EQUAL, key, device, PDT_KEYBOARD);

    //NULL,NULL will terminate the looping
    string funcname = "";
    PList* params = NULL;
    Evaluator::mEventLoop.RegisterState(state, funcname, params);
    PEvent returnval = Evaluator::mEventLoop.Loop();

    //Now, clear the event loop tests
    Evaluator::mEventLoop.Clear();

    return Variant(returnval.GetDummyEvent().value);

}




/// This function uses the event loop to schedule a single
/// device-test, which checks for the selected key.
Variant PEBLEnvironment::WaitForAnyKeyDown(Variant v)
{

    PEBLKey key = PEBLKEY_ANYKEY;
    
    //Create a keyboard test correspending to keydown. 
    //1 is the value (down), DT_EQUAL is the test, key is the interface (normally an actual key, here the "ANYKEY")
    PDevice * device = new PlatformKeyboard(myKeyboard);
    ValueState  * state = new ValueState(1, DT_EQUAL, key, device,PDT_KEYBOARD);

    //NULL,NULL will terminate the looping
    string  funcname = "";
    PList* params = NULL;
    Evaluator::mEventLoop.RegisterState(state, funcname, params);
    PEvent returnval = Evaluator::mEventLoop.Loop();

    //Now, clear the event loop tests
    Evaluator::mEventLoop.Clear();

    return Variant(returnval.GetDummyEvent().value);
}




/// This function uses the event loop to schedule a single
/// device-test, which checks for the selected key.
Variant PEBLEnvironment::WaitForKeyPress(Variant v)
{
    //v[1] should have the parameter-a letter
    PList * plist = v.GetComplexData()->GetList();

    PError::AssertType(plist->First(), PEAT_STRING, "Argument error in function [WaitForKeyPress(<string>)]:  ");    

    string mystring = plist->First(); plist->PopFront();
    PEBLKey key = PEBLUtility::TranslateString(mystring);
    
 
    //Create a keyboard test correspending to keydown. 
    //1 is the value (down), DT_EQUAL is the test, key is the interface (e.g., the 'A' key) 

    ValueState  * state = new ValueState(PEBL_PRESSED, DT_EQUAL, key, gEventQueue, PDT_KEYBOARD);

    //NULL,NULL will terminate the looping
    string funcname = "";
    PList* params = NULL;
    Evaluator::mEventLoop.RegisterEvent(state,funcname, params);
    PEvent returnval = Evaluator::mEventLoop.Loop();

    //Now, clear the event loop tests
    Evaluator::mEventLoop.Clear();

    return Variant(PEBLUtility::TranslateKeyCode(returnval.GetKeyboardEvent().key,0));
}



Variant PEBLEnvironment::WaitForKeyRelease(Variant v)
{

    //v[1] should have the parameter-a letter
    PList * plist = v.GetComplexData()->GetList();

    PError::AssertType(plist->First(), PEAT_STRING, "Argument error in function [WaitForKeyRelease(<string>)]:  ");    

    string mystring = plist->First(); plist->PopFront();
    PEBLKey key = PEBLUtility::TranslateString(mystring);
    

    //Create a keyboard test correspending to keydown. 
    //1 is the value (down), DT_NOT_EQUAL is the test, key is the interface (e.g., the 'A' key) 

    ValueState  * state = new ValueState(PEBL_RELEASED, DT_EQUAL, key, gEventQueue, PDT_KEYBOARD);

    //NULL,NULL will terminate the looping
    string funcname = "";
    PList* params = NULL;
    Evaluator::mEventLoop.RegisterEvent(state, funcname, params);
    PEvent returnval = Evaluator::mEventLoop.Loop();

    //Now, clear the event loop tests
    Evaluator::mEventLoop.Clear();


    return Variant(PEBLUtility::TranslateKeyCode(returnval.GetKeyboardEvent().key,0));

}




/// This function uses the event loop to schedule a single
/// device-test, which checks for the selected key.
Variant PEBLEnvironment::WaitForAnyKeyPress(Variant v)
{

    PEBLKey key = PEBLKEY_ANYKEY;
    
    //Create a keyboard test correspending to keydown. 
    ValueState  * state = new ValueState(PEBL_PRESSED, DT_EQUAL, key, gEventQueue, PDT_KEYBOARD);

    //NULL,NULL will terminate the looping
    string  funcname = "";
    PList* params = NULL;
    Evaluator::mEventLoop.RegisterEvent(state, funcname, params);
    PEvent returnval = Evaluator::mEventLoop.Loop();

    //Now, clear the event loop tests
    Evaluator::mEventLoop.Clear();

    return Variant(PEBLUtility::TranslateKeyCode(returnval.GetKeyboardEvent().key,0));

}




Variant PEBLEnvironment::WaitForAllKeysUp(Variant v)
{

    PEBLKey key = PEBLKEY_ANYKEY;
    
    
    //Create a keyboard test correspending to keydown. 
    //1 is the value (down), DT_EQUAL is the test, key is the interface (e.g., the 'A' key) 
    PDevice * device = new PlatformKeyboard(myKeyboard);    
    ValueState  * state = new ValueState(1, DT_NOT_EQUAL, key, device, PDT_KEYBOARD);
    
    //NULL,NULL will terminate the looping
    string  funcname = "";
    PList* params = NULL;
    Evaluator::mEventLoop.RegisterState(state,funcname, params);
    PEvent returnval = Evaluator::mEventLoop.Loop();

    //Now, clear the event loop tests
    Evaluator::mEventLoop.Clear();


    return Variant(returnval.GetDummyEvent().value);
}


Variant PEBLEnvironment::WaitForAnyKeyDownWithTimeout(Variant v)
{

   //v[1] should have the parameter: a time to wait.
    PList * plist = v.GetComplexData()->GetList();

    PError::AssertType(plist->First(), PEAT_NUMBER, "Argument error in function [WaitForAnyKeyDownWithTimeout(<number>)]:  ");    

    int delay = plist->First(); plist->PopFront();
    delay += myTimer.GetTime();
                                                                                                                   
    //Create a timer test correspending to keydown.
    //1 is the value (down), DT_GREATERTHAN is the test, key is the interface (e.g., the 'A' key)
    PDevice * timer = new PlatformTimer(myTimer);
    ValueState  * timestate = new ValueState(delay, DT_GREATER_THAN_OR_EQUAL, 1, timer, PDT_TIMER);


    PEBLKey key = PEBLKEY_ANYKEY;
    //Create a keyboard test correspending to keydown. 
    //1 is the value (down), DT_EQUAL is the test, key is the interface (e.g., the 'A' key) 

    PDevice * device = new PlatformKeyboard(myKeyboard);
    ValueState  * state = new ValueState(1, DT_EQUAL, key, device, PDT_KEYBOARD);

    //NULL,NULL will terminate the looping
    string  funcname = "";
    PList* params = NULL;
    Evaluator::mEventLoop.RegisterState(state,funcname, params);
    Evaluator::mEventLoop.RegisterState(timestate, funcname, params);
    PEvent returnval = Evaluator::mEventLoop.Loop();

    //Now, clear the event loop tests
    Evaluator::mEventLoop.Clear();

    return Variant(returnval.GetDummyEvent().value);

}


// This takes a list of keys, a timeout duration, and an integer specifying
// the style: 
//  1 == return after whichever happens first
//  2 == return only after timeout occurs
//  3 == return after both occur (response and min duration necessary)
//  In all cases, the key pressed is returned.  If a key has not been pressed, 
//  the empty string "" is returned.

Variant PEBLEnvironment::WaitForListKeyPressWithTimeout(Variant v)
{
  
    PList * plist = v.GetComplexData()->GetList();
    Variant v1 = plist->First(); plist->PopFront();
    PError::AssertType(v1, PEAT_LIST, "Argument error in first parameter of function [WaitForListKeyPressWithTimeout(<list-of-keys>,<timeout>,<style>)]:  ");    


    //Use plist to get the actual list of items.
    PList * keylist = (PList*)((v1.GetComplexData())->GetObject().get());

    PError::AssertType(plist->First(), PEAT_NUMBER, "Argument error in second parameter of function [WaitForListKeyPressWithTimeout(<list-of-keys>,<timeout>,<style>)]:  ");    
    int delay  = plist->First(); plist->PopFront();
    delay += myTimer.GetTime();

    PError::AssertType(plist->First(), PEAT_INTEGER, "Argument error in third parameter of function [WaitForListKeyPressWithTimeout(<list-of-keys>,<timeout>,<style>)]:  ");    
    Variant v3 = plist->First(); plist->PopFront();

    



    std::list<Variant>::iterator p = keylist->Begin();
    std::list<Variant>::iterator end = keylist->End();

    ValueState * state;
    string funcname = "";
    PList* params = NULL;
    PEBLKey key;

    while(p != end)
        {
            //Create a keyboard tests correspending to each item in v1. 
            //1 is the value (down), DT_EQUAL is the test, key is the interface (e.g., the 'A' key) 
            key = PEBLUtility::TranslateString(*p);
            state = new ValueState(PEBL_PRESSED, DT_EQUAL, key, gEventQueue, PDT_KEYBOARD);
            //NULL,NULL will terminate the looping
            Evaluator::mEventLoop.RegisterEvent(state,funcname, params);
            p++;
        }


                                                                                                                   
    //Create a timer test correspending to keydown.
    //1 is the value (down), DT_GREATERTHAN is the test, key is the interface (e.g., the 'A' key)
    PDevice * timer = new PlatformTimer(myTimer);
    ValueState  * timestate = new ValueState(delay, DT_GREATER_THAN_OR_EQUAL, 1, timer, PDT_TIMER);


    //NULL,NULL will terminate the looping
    Evaluator::mEventLoop.RegisterState(timestate, funcname, params);
    PEvent returnval = Evaluator::mEventLoop.Loop();

    //Now, clear the event loop tests
    Evaluator::mEventLoop.Clear();

    return Variant(returnval.GetDummyEvent().value);

}


//This function will block until one of the keys listed in the argument is depressed, 
//and then return the value of the key that was hit.
Variant PEBLEnvironment::WaitForKeyListDown(Variant v)
{

   //v[1] should have the parameter: a list of keys to wait for.
    PList * plist = v.GetComplexData()->GetList();
    Variant v1 = plist->First(); plist->PopFront();
    PError::AssertType(v1, PEAT_LIST, "Argument error in function [WaitForKeyListDown(<list>)]:  ");    
    
    //Use plist to get the actual list of items.
    PList * keylist = (PList*)((v1.GetComplexData())->GetObject().get());
                                                   
    std::list<Variant>::iterator p = keylist->Begin();
    std::list<Variant>::iterator end = keylist->End();

    PDevice * device = new PlatformKeyboard(myKeyboard);
    ValueState * state;
    string  funcname = "";
    PList* params = NULL;
    PEBLKey key;


    while(p != end)
        {
            //Create a keyboard tests correspending to each item in v1. 
            //1 is the value (down), DT_EQUAL is the test, key is the interface (e.g., the 'A' key) 
            key = PEBLUtility::TranslateString(*p);
            state = new ValueState(1, DT_EQUAL, key, device, PDT_KEYBOARD);
            //NULL,NULL will terminate the looping
            Evaluator::mEventLoop.RegisterState(state,funcname, params);
            p++;
        }


    //Start the event loop.
    PEvent returnval = Evaluator::mEventLoop.Loop();

    Evaluator::mEventLoop.Clear();
    return Variant(returnval.GetDummyEvent().value);
}


//This function will block until one of the keys listed in the argument is depressed, 
//and then return the value of the key that was hit.
Variant PEBLEnvironment::WaitForListKeyPress(Variant v)
{

   //v[1] should have the parameter: a list of keys to wait for.
    PList * plist = v.GetComplexData()->GetList();

    Variant v1 = plist->First(); plist->PopFront();
    PError::AssertType(v1, PEAT_LIST, "Argument error in function [WaitForKeyListPress(<list>)]:  ");    
    
    //Use plist to get the actual list of items.
    PList * keylist = (PList*)((v1.GetComplexData())->GetObject().get());

    std::list<Variant>::iterator p = keylist->Begin();
    std::list<Variant>::iterator end = keylist->End();

    ValueState * state;
    string funcname = "";
    PList* params = NULL;
    PEBLKey key;

    while(p != end)
        {
            //Create a keyboard tests correspending to each item in v1. 
            //1 is the value (down), DT_EQUAL is the test, key is the interface (e.g., the 'A' key) 
            key = PEBLUtility::TranslateString(*p);
            state = new ValueState(PEBL_PRESSED, DT_EQUAL, key, gEventQueue, PDT_KEYBOARD);
            //NULL,NULL will terminate the looping
            Evaluator::mEventLoop.RegisterEvent(state,funcname, params);
            p++;
        }


    //Start the event loop.
    PEvent returnval = Evaluator::mEventLoop.Loop();
    Evaluator::mEventLoop.Clear();
    return Variant(PEBLUtility::TranslateKeyCode(returnval.GetKeyboardEvent().key,0));
}



/// This takes as an argument a textbox and an 'escape' key.
/// Once executed, it will allow all keyboard entry to show up
/// in the text box.  Once the escape key is hit, the function
/// will return the text inside the box.
Variant PEBLEnvironment::GetInput(Variant v)
{
    PList * plist = v.GetComplexData()->GetList();
    //The first argument should be a textbox.
    PError::AssertType(plist->First(), PEAT_TEXTBOX, "Argument error in function [GetInput(<textbox>,<key-string>)]: "); 
    PlatformTextBox * textbox = dynamic_cast<PlatformTextBox*>(plist->First().GetComplexData()->GetObject().get());
    plist->PopFront();    

    //The next argument should be the 'escape' key.
    PError::AssertType(plist->First(), PEAT_STRING, "Argument error in function [GetInput(<textbox>,<key-string>)]: ");    
    string  myString = plist->First(); plist->PopFront();


    //Create a keyboard test correspending to escape keydown. 
    //1 is the value (down), DT_EQUAL is the test, key is the interface (e.g., the 'A' key) 


    ValueState  * keypressstate = new ValueState(PEBL_PRESSED, DT_EQUAL, PEBLKEY_ANYKEY,gEventQueue, PDT_KEYBOARD);

    //NULL,NULL will terminate the looping
    string funcname = "";
    PList* params = NULL;


    //Make the textbox editable.
    textbox->SetEditable(true);
    myEnv->Draw();    

    Evaluator::mEventLoop.Clear();
    Evaluator::mEventLoop.RegisterEvent(keypressstate, funcname, params);


    PEvent keypress =  Evaluator::mEventLoop.Loop();  
    PEBL_KeyboardEvent pke = keypress.GetKeyboardEvent();

    while(pke.key != PEBLUtility::TranslateString(myString))
        {

            // cout << pke.key << endl;
            //Process the input and redraw the textbox.
            textbox->HandleKeyPress(pke.key, pke.modkeys);

            if(myEnv)
                {
                    myEnv->Draw();
                }
            
            //Wait for the next keystroke..
            keypress =  Evaluator::mEventLoop.Loop();
            pke = keypress.GetKeyboardEvent();
        }
    
    
    Evaluator::mEventLoop.Clear();
    textbox->SetEditable(false);
    return Variant(textbox->GetText());
}



 //Complex eventloop construction.
Variant  PEBLEnvironment::RegisterEvent( Variant v)
{
    PError::SignalFatalError("Function [RegisterEvent] Not implemented.");
    return Variant(0);
}
Variant  PEBLEnvironment::StartEventLoop(Variant v)
{
    PError::SignalFatalError("Function [StartEventLoop] Not implemented.");
    return Variant(0);
}
Variant  PEBLEnvironment::ClearEventLoop(Variant v)
{
    Evaluator::mEventLoop.Clear();
    return Variant(0);
}




Variant PEBLEnvironment::SignalFatalError(Variant v)
{
    //Signal a fatal error with the message inside v
    PList * plist = v.GetComplexData()->GetList();
    std::string message  = plist->First().GetString();

    PError::SignalFatalError(message);
    return Variant(false);
}


/// This function takes as an argument an integer, and returns
/// the string values corresponding to that keycode.
///
Variant PEBLEnvironment::TranslateKeyCode(Variant v)
{

   //v[1] should have the key
    PList * plist = v.GetComplexData()->GetList();

    PError::AssertType(plist->First(), PEAT_INTEGER, "Argument error in function [TranslateKeyCode(<integer>)]:  ");    

    int key = (int)(plist->First()); plist->PopFront();
    
    std::string retval = PEBLUtility::TranslateKeyCode((PEBLKey)key, PEBLMOD_NONE);
    return Variant(retval);

}


Variant PEBLEnvironment::TimeStamp(Variant v)
{

    time_t  rawtime;
    rawtime = time(NULL);
    char* timestring = ctime(&rawtime);
   
    
    //timestring now ends with a carriage return.  So fix it.
    
    int pos =0;
    while( timestring[pos] != '\n' && timestring[pos] != '\0')
        {
            pos++;
        }
    timestring[pos] = '\0';
    Variant ret = Variant(timestring);

    return ret;
}



Variant  PEBLEnvironment::GetPEBLVersion(Variant v)
{
    
    return Variant("PEBL Version 0.07");
}


Variant PEBLEnvironment::IsNumber(Variant v)
{
    PList * plist = v.GetComplexData()->GetList();

    return plist->First().IsNumber();
}

Variant PEBLEnvironment::IsInteger(Variant v)
{
    PList * plist = v.GetComplexData()->GetList();

    return plist->First().IsInteger();
}


Variant PEBLEnvironment::IsFloat(Variant v)
{
    PList * plist = v.GetComplexData()->GetList();

    return plist->First().IsFloat();
}



Variant PEBLEnvironment::IsString(Variant v)
{
    PList * plist = v.GetComplexData()->GetList();
    return plist->First().IsString();
}


Variant PEBLEnvironment::IsList(Variant v)
{
    PList * plist = v.GetComplexData()->GetList();

    Variant v1 =  plist->First();
    if (v1.IsComplexData())
        {
            if((v1.GetComplexData())->IsList())
                {
                    return Variant(true);
                }
        }
    return Variant(false);
}


Variant PEBLEnvironment::IsTextBox(Variant v)
{
    PList * plist = v.GetComplexData()->GetList();

    Variant v1 =  plist->First();
    if (v1.IsComplexData())
        {
            if((v1.GetComplexData())->IsTextBox())
                {
                    return Variant(true);
                }
        }
    return Variant(false);
}

Variant PEBLEnvironment::IsImage(Variant v)
{
    PList * plist = v.GetComplexData()->GetList();
    Variant v1 =  plist->First();
    if (v1.IsComplexData())
        {
            if((v1.GetComplexData())->IsImageBox())
                {
                    return Variant(true);
                }
        }
    return Variant(false);
}



Variant PEBLEnvironment::IsLabel(Variant v)
{
    PList * plist = v.GetComplexData()->GetList();
    Variant v1 =  plist->First();
    if (v1.IsComplexData())
        {
            if((v1.GetComplexData())->IsLabel())
                {
                    return Variant(true);
                }
        }
    return Variant(false);
}



Variant PEBLEnvironment::IsAudioOut(Variant v)
{
    PList * plist = v.GetComplexData()->GetList();

    Variant v1 =  plist->First();
    if (v1.IsComplexData())
        {
            if((v1.GetComplexData())->IsAudioOut())
                {
                    return Variant(true);
                }
        }
    return Variant(false);
}



Variant PEBLEnvironment::IsFont(Variant v)
{
    PList * plist = v.GetComplexData()->GetList();

    Variant v1 =  plist->First();
    if (v1.IsComplexData())
        {
            if((v1.GetComplexData())->IsFont())
                {
                    return Variant(true);
                }
        }
    return Variant(false);
}



Variant PEBLEnvironment::IsColor(Variant v)
{
    PList * plist = v.GetComplexData()->GetList();

    Variant v1 =  plist->First();
    if (v1.IsComplexData())
        {
            if((v1.GetComplexData())->IsColor())
                {
                    return Variant(true);
                }
        }
    return Variant(false);
}


Variant PEBLEnvironment::IsFileStream(Variant v)
{
     PList * plist = v.GetComplexData()->GetList();
    Variant v1 =  plist->First();
    if (v1.IsComplexData())
        {
            if((v1.GetComplexData())->IsFileStream())
                {
                    return Variant(true);
                }
        }
    return Variant(false);
}

Variant PEBLEnvironment::IsWidget(Variant v)
{

    PList * plist = v.GetComplexData()->GetList();
    Variant v1 =  plist->First();
    if (v1.IsComplexData())
        {
            if((v1.GetComplexData())->IsWidget())
                {
                    return Variant(true);
                }
        }
    return Variant(false);
}
