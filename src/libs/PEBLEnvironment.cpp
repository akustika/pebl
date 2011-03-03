//* -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*- */
///////////////////////////////////////////////////////////////////////////////
//    Name:       src/libs/PEBLEnvironment.cpp
//    Purpose:    General Environment Function Library for PEBL
//    Author:     Shane T. Mueller, Ph.D.
//    Copyright:  (c) 2003-2011 Shane T. Mueller <smueller@obereed.net>
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
///////////////////////////////////////////////////////////////////////////////
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

    Evaluator::mEventLoop.RegisterState(state, funcname, Variant(NULL));
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


// /// This function uses the event loop to schedule a single
// /// device-test, which checks for the selected key.
// Variant PEBLEnvironment::WaitForMouseOverRegion(Variant v)
// {
//     //v[1-4] should specify a rectangle
//     PList * plist = v.GetComplexData()->GetList();

//     PError::AssertType(plist->First(), PEAT_STRING, "Argument error in function [WaitForKeyPress(<string>)]:  ");    

//     string mystring = plist->First(); plist->PopFront();
//     PEBLKey key = PEBLUtility::TranslateString(mystring);
    
 

//     RegionState  * state = new RegionState(10,100,10,100, DT_INSIDE, , gEventQueue, PDT_MOUSEMOTION);

//     //NULL,NULL will terminate the looping
//     string funcname = "";
//     PList* params = NULL;
//     Evaluator::mEventLoop.RegisterEvent(state,funcname, params);
//     PEvent returnval = Evaluator::mEventLoop.Loop();

//     //Now, clear the event loop tests
//     Evaluator::mEventLoop.Clear();

//     return Variant(PEBLUtility::TranslateKeyCode(returnval.GetKeyboardEvent().key,0));
// }



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


    Evaluator::mEventLoop.RegisterState(state,funcname, Variant(NULL));
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
    Evaluator::mEventLoop.RegisterState(state, funcname, Variant(NULL));
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

    Evaluator::mEventLoop.RegisterState(state, funcname, Variant(NULL));
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

    Evaluator::mEventLoop.RegisterEvent(state,funcname, Variant(NULL));
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

    Evaluator::mEventLoop.RegisterEvent(state, funcname, Variant(NULL));
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

    Evaluator::mEventLoop.RegisterEvent(state, funcname, Variant(NULL));
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
    Evaluator::mEventLoop.RegisterState(state,funcname, Variant(NULL));
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

    //PDevice * device = new PlatformKeyboard(myKeyboard);
    ValueState  * state = new ValueState(PEBL_PRESSED, DT_EQUAL, key, gEventQueue, PDT_KEYBOARD);

    //NULL,NULL will terminate the looping
    string  funcname = "";
    Evaluator::mEventLoop.RegisterState(state,funcname, Variant(NULL));
    Evaluator::mEventLoop.RegisterState(timestate, funcname, Variant(NULL));
    PEvent returnval = Evaluator::mEventLoop.Loop();

    //Now, clear the event loop tests
    Evaluator::mEventLoop.Clear();

    return Variant(returnval.GetDummyEvent().value);

}

// This returns the key pressed, and not the timeout.
// The keypress object will eventually be time-stamped,
// or the time can be obtained from GetTime()

Variant PEBLEnvironment::WaitForAnyKeyPressWithTimeout(Variant v)
{

   //v[1] should have the parameter: a time to wait.
    PList * plist = v.GetComplexData()->GetList();

    PError::AssertType(plist->First(), PEAT_NUMBER, "Argument error in function [WaitForAnyKeyPressWithTimeout(<number>)]:  ");    

    int delay = plist->First(); plist->PopFront();
    delay += myTimer.GetTime();
                                                                                                                   
    //Create a timer test correspending to keydown.
    //1 is the value (down), DT_GREATERTHAN is the test, key is
    // the interface (e.g., the 'A' key)
    PDevice * timer = new PlatformTimer(myTimer);
    ValueState  * timestate = new ValueState(delay, DT_GREATER_THAN_OR_EQUAL, 1, timer, PDT_TIMER);


    PEBLKey key = PEBLKEY_ANYKEY;
    //Create a keyboard test correspending to keydown. 
    //1 is the value (down), DT_EQUAL is the test, key is the interface (e.g., the 'A' key) 

    PDevice * device = new PlatformKeyboard(myKeyboard);
    ValueState  * state = new ValueState(1, DT_EQUAL, key, device, PDT_KEYBOARD);

    //NULL,NULL will terminate the looping
    string  funcname = "";

    Evaluator::mEventLoop.RegisterState(state,funcname, Variant(NULL));
    Evaluator::mEventLoop.RegisterState(timestate, funcname, Variant(NULL));
    PEvent returnval = Evaluator::mEventLoop.Loop();

    //    std::cout << "Returnval: "<<returnval.GetType() << std::endl;
    //Now, clear the event loop tests
    Evaluator::mEventLoop.Clear();
    //    return Variant(returnval.GetDummyEvent().value);

    return Variant(PEBLUtility::TranslateKeyCode(returnval.GetKeyboardEvent().key,0));
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

    PEBLKey key;

    while(p != end)
        {
            //Create a keyboard tests correspending to each item in v1. 
            //1 is the value (down), DT_EQUAL is the test, key is the interface (e.g., the 'A' key) 
            key = PEBLUtility::TranslateString(*p);
            state = new ValueState(PEBL_PRESSED, DT_EQUAL, key, gEventQueue, PDT_KEYBOARD);
            //NULL,NULL will terminate the looping
            Evaluator::mEventLoop.RegisterEvent(state,funcname, Variant(NULL));
            p++;
        }


                                                                                                                   
    //Create a timer test correspending to keydown.
    //1 is the value (down), DT_GREATERTHAN is the test, key is the interface (e.g., the 'A' key)
    PDevice * timer = new PlatformTimer(myTimer);
    ValueState  * timestate = new ValueState(delay, DT_GREATER_THAN_OR_EQUAL, 1, timer, PDT_TIMER);


    //NULL,NULL will terminate the looping
    Evaluator::mEventLoop.RegisterState(timestate, funcname, Variant(NULL));
    PEvent returnval = Evaluator::mEventLoop.Loop();

    //Now, clear the event loop tests
    Evaluator::mEventLoop.Clear();

    //    return Variant(PEBLUtility::TranslateKeyCode(returnval.GetKeyboardEvent().key,0));
    Variant ret;
    //    std::cout<<"Type:" << returnval.GetType() <<std::endl;

    if(returnval.GetType() == PDT_KEYBOARD)
        {
            ret = Variant(PEBLUtility::TranslateKeyCode(returnval.GetKeyboardEvent().key,0));
        }
    else
        {
            
            PList *newlist = new PList();
            newlist->PushBack(Variant("<timeout>"));
            counted_ptr<PEBLObjectBase>newlist2 = counted_ptr<PEBLObjectBase>(newlist);
            PComplexData *   pcd = new PComplexData(newlist2); 

            ret = Variant(pcd);
        }
    
    return ret;

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

    PEBLKey key;


    while(p != end)
        {
            //Create a keyboard tests correspending to each item in v1. 
            //1 is the value (down), DT_EQUAL is the test, key is the interface (e.g., the 'A' key) 
            key = PEBLUtility::TranslateString(*p);
            state = new ValueState(1, DT_EQUAL, key, device, PDT_KEYBOARD);
            //NULL,NULL will terminate the looping
            Evaluator::mEventLoop.RegisterState(state,funcname, Variant(NULL));
            p++;
        }


    //Start the event loop.
    PEvent returnval = Evaluator::mEventLoop.Loop();


    Evaluator::mEventLoop.Clear();
    Variant ret;
    if(returnval.GetType() == PDT_KEYBOARD)
        {

             ret = Variant(returnval.GetDummyEvent().value);
        }
    else
        {
            //            cout <<"======="<< returnval.GetDummyEvent().value << std::endl;
            
            PList *newlist = new PList();
            newlist->PushBack(Variant("<timeout>"));
            counted_ptr<PEBLObjectBase>newlist2 = counted_ptr<PEBLObjectBase>(newlist);
            PComplexData *   pcd = new PComplexData(newlist2); 

            ret = Variant(pcd);
        }
    
    return ret;
}


//This function will block until one of the keys listed in
// the argument is depressed, 
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

    PEBLKey key;

    while(p != end)
        {
            //Create a keyboard tests correspending to each item in v1. 
            //1 is the value (down), DT_EQUAL is the test, key is the interface (e.g., the 'A' key) 


            key = PEBLUtility::TranslateString(*p);
            //            std::cout<< "Key:" << *p << "|"<<key<< std::endl;
            state = new ValueState(PEBL_PRESSED, DT_EQUAL, key, gEventQueue, PDT_KEYBOARD);
            //NULL,NULL will terminate the looping
            Evaluator::mEventLoop.RegisterEvent(state,funcname, Variant(NULL));
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


    //The next argument should be the 'escape' key, or a list of 'escape' keys.
    // l.GetType() << std::endl;
    //type = plist->First()->GetType();

    PError::AssertType(plist->First(), PEAT_STRING, "Argument error in function [GetInput(<textbox>,<key-string>)]: ");    
    string  myString = plist->First(); plist->PopFront();


    //Create a keyboard test correspending to escape keydown. 
    //1 is the value (down), DT_EQUAL is the test, key is the interface (e.g., the 'A' key) 


    ValueState  * keypressstate = new ValueState(PEBL_PRESSED, DT_EQUAL, PEBLKEY_ANYKEY,gEventQueue, PDT_KEYBOARD);

    //NULL,NULL will terminate the looping
    string funcname = "";


    //Make the textbox editable.
    textbox->SetEditable(true);
    myEnv->Draw();    

    Evaluator::mEventLoop.Clear();
    Evaluator::mEventLoop.RegisterEvent(keypressstate, funcname, Variant(NULL));


    PEvent keypress =  Evaluator::mEventLoop.Loop();  
    PEBL_KeyboardEvent pke = keypress.GetKeyboardEvent();



    //match on lowercase matches to trigger character.  
    //    while(pke.key != PEBLUtility::TranslateString(myString))
    while(PEBLUtility::TranslateKeyCode(pke.key, pke.modkeys) != PEBLUtility::ToLower(myString))
        {
            //std::cout << pke.key << "|" << pke.modkeys << std::endl;
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



/// This function uses the event loop to schedule a single
/// device-test, which checks for any type of mouse click.
/// It returns x,y, button, and type of button press.
Variant PEBLEnvironment::WaitForMouseButton(Variant v)
{
     //Create a mouse test
    //1 is the value (down), DT_EQUAL is the test, 1 is the interface (e.g., the 'A' key) 

    ValueState  * state = new ValueState(PEBL_PRESSED, DT_TRUE, 1, gEventQueue, PDT_MOUSE_BUTTON);

    //NULL,NULL will terminate the looping
    string funcname = "";
    Evaluator::mEventLoop.RegisterEvent(state,funcname, Variant(NULL));
    PEvent returnval = Evaluator::mEventLoop.Loop();

    //Now, clear the event loop tests
    Evaluator::mEventLoop.Clear();

    PList * newlist = new PList();

    int x =returnval.GetMouseButtonEvent().x;
    int y =returnval.GetMouseButtonEvent().y;
    newlist->PushFront(Variant(x));
    newlist->PushBack(Variant(y));
    int btn = returnval.GetMouseButtonEvent().button;
    Variant button = Variant(btn);
    newlist ->PushBack(button);

    Variant buttonstate = "";
    int upstate = returnval.GetMouseButtonEvent().state;
    if(upstate == PEBL_PRESSED)
        {
            buttonstate = Variant("<pressed>");
        } else {
            buttonstate = Variant("<released>");
        }
    newlist->PushBack(buttonstate);
    
 
    counted_ptr<PEBLObjectBase> newlist2 = counted_ptr<PEBLObjectBase>(newlist);
    PComplexData *   pcd = new PComplexData(newlist2); 

    return Variant(pcd);
}

/// This function uses the event loop to schedule a single
/// device-test, which checks for any type of mouse click.
/// It returns x,y, button, and type of button press.
Variant PEBLEnvironment::WaitForMouseButtonWithTimeout(Variant v)
{



   //v[1] should have the parameter: a time to wait.
    PList * plist = v.GetComplexData()->GetList();

    PError::AssertType(plist->First(), PEAT_NUMBER, "Argument error in function [WaitForMouseButtonWithTimeout(<number>)]:  ");    

    //set the timeout
    int delay = plist->First(); plist->PopFront();
    delay += myTimer.GetTime();
    
                                                                                                                   
    //Create a timer test 
    //1 is the value (down), DT_GREATERTHAN is the test, key is
    // the interface (e.g., the 'A' key)
    PDevice * timer = new PlatformTimer(myTimer);
    ValueState  * timestate = new ValueState(delay, DT_GREATER_THAN_OR_EQUAL, PDT_TIMER, timer, PDT_TIMER);



    ///////////////////////////////////////
     //Create a mouse test
    //1 is the value (down), DT_EQUAL is the test, 1 is the interface (e.g., the 'A' key) 

    ValueState  * state = new ValueState(PEBL_PRESSED, DT_TRUE, 1, gEventQueue, PDT_MOUSE_BUTTON);

    //NULL,NULL will terminate the looping
    string funcname = "";
    Evaluator::mEventLoop.RegisterEvent(state,funcname, Variant(NULL));
    Evaluator::mEventLoop.RegisterState(timestate, funcname, Variant(NULL));

    PEvent returnval = Evaluator::mEventLoop.Loop();




    //Now, clear the event loop tests
    Evaluator::mEventLoop.Clear();

    PList *newlist = new PList();

    if(returnval.GetType()== PDT_MOUSE_BUTTON)
        {

           
            int x =returnval.GetMouseButtonEvent().x;
            int y =returnval.GetMouseButtonEvent().y;
            newlist->PushFront(Variant(x));
            newlist->PushBack(Variant(y));
            int btn = returnval.GetMouseButtonEvent().button;
            Variant button = Variant(btn);
            newlist ->PushBack(button);
            
            Variant buttonstate = "";
            int upstate = returnval.GetMouseButtonEvent().state;
            if(upstate == PEBL_PRESSED)
                {
                    buttonstate = Variant("<pressed>");
                } else {
                buttonstate = Variant("<released>");
            }
            newlist->PushBack(buttonstate);
            
        }    else  //PCD_TIMER
        {


            newlist->PushBack(Variant("<timeout>"));


            
        }

    counted_ptr<PEBLObjectBase>newlist2 = counted_ptr<PEBLObjectBase>(newlist);
    PComplexData *   pcd = new PComplexData(newlist2); 
    return Variant(pcd);
}




/// This gets the x,y coordinates of the mouse, and
/// returns them in a list
Variant PEBLEnvironment::GetCursorPosition(Variant v)
{
    return myEnv->GetCursorPosition();
}


/// This sets the mouse to a new position.
Variant PEBLEnvironment::SetCursorPosition(Variant v)
{
    PList * plist = v.GetComplexData()->GetList();
    //The first argument should be a textbox.
    PError::AssertType(plist->First(), PEAT_INTEGER, "Argument error in first argument of function [SetCursorPosition(<x>,<y>)]: "); 
    int x = plist->First();
    plist->PopFront();    

    PError::AssertType(plist->First(), PEAT_INTEGER, "Argument error in second argumeent of function [SetCursorPosition(<x>,<y>)]: "); 

    int y = plist->First();
    plist->PopFront();    
    
    myEnv->SetCursorPosition(x,y);
     return Variant(1);
}



    //basic joystick stuff
Variant PEBLEnvironment::GetNumJoysticks(Variant v)
{
    return myEnv->GetNumJoysticks();
}

//This returns a joystic to use, based on its name.
Variant  PEBLEnvironment::GetJoystick(Variant v)
{

    PList * plist = v.GetComplexData()->GetList();
    //The first argument should be an integer specifying the joystick index
    PError::AssertType(plist->First(), PEAT_INTEGER, "Argument error in argument of function [GetJoystick(<int>)]: "); 
    int id = plist->First();
    plist->PopFront();


    PlatformJoystick * js = new PlatformJoystick(id);
    counted_ptr<PEBLObjectBase> joy = counted_ptr<PEBLObjectBase>(js);
    PComplexData *   pcd = new PComplexData(joy);
    return Variant(pcd);

}

Variant  PEBLEnvironment::GetNumJoystickAxes(Variant v)
{

    PList * plist = v.GetComplexData()->GetList();
    //The first argument should be a joystick
    PError::AssertType(plist->First(), PEAT_JOYSTICK, "Argument error in argument of function [GetNumJoystickAxes(<joystick>)]: ");
    
    PlatformJoystick * joystick = dynamic_cast<PlatformJoystick*>(plist->First().GetComplexData()->GetObject().get());
    
    return Variant(joystick->GetNumAxes());
}


Variant  PEBLEnvironment::GetNumJoystickBalls(Variant v)
{
    PList * plist = v.GetComplexData()->GetList();
    //The first argument should be a joystick
    PError::AssertType(plist->First(), PEAT_JOYSTICK, "Argument error in argument of function [GetNumJoystickBalls(<joystick>)]: ");
    
    PlatformJoystick * joystick = dynamic_cast<PlatformJoystick*>(plist->First().GetComplexData()->GetObject().get());

    
    return Variant(joystick->GetNumBalls());

}
Variant PEBLEnvironment::GetNumJoystickButtons(Variant v)
{
    PList * plist = v.GetComplexData()->GetList();
    //The first argument should be a joystick
    PError::AssertType(plist->First(), PEAT_JOYSTICK, "Argument error in argument of function [GetNumJoystickButtons(<joystick>)]: ");
    PlatformJoystick * joystick = dynamic_cast<PlatformJoystick*>(plist->First().GetComplexData()->GetObject().get());


    
    return Variant(joystick->GetNumButtons());

}
Variant  PEBLEnvironment::GetNumJoystickHats(Variant v)
{
    PList * plist = v.GetComplexData()->GetList();
    //The first argument should be a joystick
    PError::AssertType(plist->First(), PEAT_JOYSTICK, "Argument error in argument of function [GetNumJoystickHats(<joystick>)]: ");
    PlatformJoystick * joystick = dynamic_cast<PlatformJoystick*>(plist->First().GetComplexData()->GetObject().get());

    
    return Variant(joystick->GetNumHats());

}


Variant  PEBLEnvironment::GetJoystickButtonState(Variant v)
{
    PList * plist = v.GetComplexData()->GetList();
    //The first argument should be a joystick
    PError::AssertType(plist->First(), PEAT_JOYSTICK, "Argument error in first argument of function [GetJoystickButtonState(<joystick>,<button>)]: ");
    PlatformJoystick * joystick = dynamic_cast<PlatformJoystick*>(plist->First().GetComplexData()->GetObject().get());
    plist->PopFront();

    PError::AssertType(plist->First(), PEAT_INTEGER, "Argument error in second argument of function [GetJoystickButtonState(<joystick>,<button>)]: ");
    unsigned int button  = (unsigned int)(int)(plist->First());


    return joystick->GetButtonState(button);
}

Variant  PEBLEnvironment::GetJoystickAxisState(Variant v)
{

    PList * plist = v.GetComplexData()->GetList();
    //The first argument should be a joystick
    PError::AssertType(plist->First(), PEAT_JOYSTICK, "Argument error in first argument of function [GetJoystickAxisState(<joystick>,<axis>)]: ");
    PlatformJoystick * joystick = dynamic_cast<PlatformJoystick*>(plist->First().GetComplexData()->GetObject().get());
    plist->PopFront();

    PError::AssertType(plist->First(), PEAT_INTEGER, "Argument error in second argument of function [GetJoystickAxisState(<joystick>,<axis>)]: ");

    unsigned int axis  = (unsigned int)(int)(plist->First());


    return joystick->GetAxisState(axis);

}


Variant  PEBLEnvironment::GetJoystickHatState(Variant v)
{
    PList * plist = v.GetComplexData()->GetList();
    //The first argument should be a joystick
    PError::AssertType(plist->First(), PEAT_JOYSTICK, "Argument error in first argument of function [GetJoystickHatState(<joystick>,<hat>)]: ");
    PlatformJoystick * joystick = dynamic_cast<PlatformJoystick*>(plist->First().GetComplexData()->GetObject().get());
    plist->PopFront();

    PError::AssertType(plist->First(), PEAT_INTEGER, "Argument error in second argument of function [GetJoystickHatState(<joystick>,<hat>)]: ");

    unsigned int hat  = (unsigned int)(int)(plist->First());

    return joystick->GetHatState(hat);
    
}


Variant  PEBLEnvironment::GetJoystickBallState(Variant v)
{
    PList * plist = v.GetComplexData()->GetList();
    //The first argument should be a joystick
    PError::AssertType(plist->First(), PEAT_JOYSTICK, "Argument error in first argument of function [GetJoystickBallState(<joystick>,<button>)]: ");
    PlatformJoystick * joystick = dynamic_cast<PlatformJoystick*>(plist->First().GetComplexData()->GetObject().get());
    plist->PopFront();

    PError::AssertType(plist->First(), PEAT_INTEGER, "Argument error in second argument of function [GetJoystickBallState(<joystick>,<button>)]: ");
    unsigned int button  = (unsigned int)(int)(plist->First());


    return joystick->GetBallState(button);
    

}


// This takes an event definition, and function, 
// 
//
// First parameter is device as a <string> should take Device as a 
//Complex eventloop construction.
//  arguments are:
//
//  device
//  intface
//  comparison  
//  function name
//  parameters???
//
//
//
//
Variant  PEBLEnvironment::RegisterEvent( Variant v)
{

    //v[1] should have the parameter-a letter
    PList * plist = v.GetComplexData()->GetList();


    PError::AssertType(plist->First(), PEAT_STRING, "Argument error in function [RegisterEvent(<string>)]:  ");    
    string mystring = PEBLUtility::ToUpper(plist->First()); plist->PopFront();

    PDevice*device;
    
    enum PEBL_DEVICE_TYPE devicetype = PDT_DUMMY;


    
    if(mystring== "<KEYBOARD>")
        {
            device = new PlatformKeyboard(myKeyboard);
            devicetype = PDT_KEYBOARD;
        }else if(mystring == "<MOUSE_MOVEMENT>")
        {
            device = gEventQueue;
            devicetype = PDT_MOUSE_MOVEMENT;
        }else if(mystring == "MOUSE_BUTTON")
        {
            device = gEventQueue;
            devicetype = PDT_MOUSE_BUTTON;
        }else if(mystring==  "<TIMER>")
        {
        
            //This has the potential to leak:
            device = new PlatformTimer(myTimer);
            devicetype = PDT_TIMER;

            //this will be a state, not an event.

            
        }else if (mystring == "<JOYSTICK_BUTTON>")
        {

            device = gEventQueue;
            devicetype = PDT_JOYSTICK_BUTTON;

        }else if (mystring == "<JOYSTICK_HAT>")
        {

            device = gEventQueue;
            devicetype = PDT_JOYSTICK_HAT;


        }else if (mystring == "<JOYSTICK_AXIS>")
        {

            device = gEventQueue;
            devicetype = PDT_JOYSTICK_HAT;

        }else if (mystring == "<JOYSTICK_BALL>")
        {

            device = gEventQueue;
            devicetype = PDT_JOYSTICK_HAT;
        }else
        {
            //Note: PDT_stream, PDTevent_queue, and PDT_audio_out
            //not handled.
            
            PError::SignalFatalError("Unknown Device\n");
        }


    //Netx argument is the interface
    Variant intface =(plist->First()); plist->PopFront();


    //Next argument is a value or range
    //It should be either a number,
    // or a list of 2 or 4 items
    Variant p = plist->First();plist->PopFront();
    Variant v1,v2,v11,v12,v21,v22;
    enum DeviceTestType testtype;



    if(p.IsNumber())
        {

            testtype =DTT_VALUESTATE;
            PError::AssertType(p, PEAT_INTEGER, "In RegisterEvent, test bounds not a number:");    
            //valuestate
            
            // this will crash!!!       }else if (p.IsList())
        }else
        {


            PList * myList = (PList*)(p.GetComplexData()->GetObject().get());
            // This will be either intervalstate or regionstate
            // if it is an intervalstate, the list well have two numbers inside it
            // for a regionstate, the list will have two sublists.
            
             v1 = myList->First();myList->PopFront();
             v2 = myList->First();myList->PopFront();
            
             if(0)//v1.IsList())
                {

                    

                    //regionstate;
                    testtype =DTT_REGIONSTATE;

                    PList * sublist1 = (PList*)(v1.GetComplexData()->GetObject().get());
                    PList * sublist2 = (PList*)(v2.GetComplexData()->GetObject().get());

                    //Could this end up destroying a global list???
                    v11 = sublist1->First(); sublist1->PopFront();
                    v12 = sublist1->First(); 
                    v21 = sublist2->First(); sublist1->PopFront();
                    v22 = sublist2->First(); 

                }
            else
                {

                    testtype = DTT_INTERVALSTATE;
                    PError::AssertType(v1, PEAT_NUMBER, "In RegisterEvent, test bounds not a number:");    
                    PError::AssertType(v2, PEAT_NUMBER, "In RegisterEvent, test bounds not a number:");    
                    //intervalstate
                    //ValueState  * state = new ValueState(1, DT_EQUAL, key, device, PDT_KEYBOARD);
                    
                   
                }


        }
    // else
    //        {
    //
    //            std::cerr << "h\n";
    //            PError::SignalFatalError(" argument of function [RegisterEvent() must be a number or a list: ");    
    //        }
    


    //Create a keyboard test correspending to keydown. 
    //1 is the value (down), DT_EQUAL is the test, key is the interface (e.g., the 'A' key) 

    //   intervalstate or
    //   regionstate:
    //      inside
    //      not_outside
    //      outside
    //      note_inside
    //      on_edge

    //   other:
    //   TRUE
    //   FALSE


    PError::AssertType(plist->First(), PEAT_STRING, 
                       "Error in  of function [RegisterEvent(<device>,<interface>,<function>)]: ");    

    
    std::string test = PEBLUtility::ToUpper(plist->First()); plist->PopFront();


    enum DeviceTest type;

    switch(testtype)
        {
        case DTT_VALUESTATE:
    

            if(test == "<NOTEQUAL>")
                {
                    type = DT_NOT_EQUAL;
                }
            else if(test == "<EQUAL>")
                {
                    type = DT_EQUAL;
                }
            else if(test == "<LESSTHAN>")
                {
                    type = DT_LESS_THAN;
                }
            else if(test == "<GREATERTHAN>")
                {
                    type = DT_GREATER_THAN;
                }
            else if(test =="<LEQ>")
                {
                    type = DT_LESS_THAN_OR_EQUAL;
                }
            else if( test == "<GEQ>")
                {
                    type = DT_GREATER_THAN_OR_EQUAL;
                }
            else if(test == "<TRUE>")
                {
                    type = DT_TRUE;
                }
            else if(test == "<FALSE>")
                {
                    type = DT_FALSE;
                }else{

                PError::SignalFatalError("test type not available for value comparisons");
            }
            
            break;

            //The same test types are available
            //for intervals and regions.
        case DTT_INTERVALSTATE:
        case DTT_REGIONSTATE:

            if(test =="<INSIDE>")
                {
                    type = DT_INSIDE;
                }
            else if(test == "<OUTSIDE>")
                {
                    type = DT_OUTSIDE;
                }
            else if (test == "<TRUE>")
                {
                    type = DT_TRUE;
                }
            else if (test == "<FALSE>")
                {
                    type = DT_FALSE;
                }
            else if( test == "<ON_EDGE>")
                {
                    type = DT_ON_EDGE;
                }
            else if(test =="<NOT_INSIDE>")
                {
                    type = DT_NOT_INSIDE;
                }
            else if(test == "<NOT_OUTSIDE>")
                {
                    type = DT_OUTSIDE;
                }else
                {
                    PError::SignalFatalError("Test type not available for region or interval test");
                }

        }




    PError::AssertType(plist->First(), PEAT_STRING, "Error in parameter of function [RegisterEvent(<device>,<xxx>,<functionname>)]:  ");
    string funcname = PEBLUtility::ToUpper(plist->First()); plist->PopFront();
    //Can we check to see if funcname exists in the functionmap?





    DeviceState * state  = NULL;
    
    switch(testtype)
        {
        case DTT_VALUESTATE:
            state = new ValueState((int)p, type, (int)intface, device, devicetype);
            break;
        case DTT_INTERVALSTATE:
            state = new IntervalState((int)v1,(int)v2, type, (int)intface, device, devicetype);
            break;
        case DTT_REGIONSTATE:
            state = new RegionState((int)v11, (int)v12, (int)v21, (int)v22, type, (int)intface, device, devicetype);
            break;
        }



    //get the parameter to pass to the callback function.

    Variant parameters =  plist->First(); plist->PopFront();

    if(parameters.IsStackSignal())
        parameters = Variant(NULL);

    if(devicetype == PDT_TIMER)
        {
            Evaluator::mEventLoop.RegisterState(state,funcname, parameters);

        }
    else
        {
            Evaluator::mEventLoop.RegisterEvent(state,funcname, parameters);
        }



    return Variant(0);
}


Variant  PEBLEnvironment::StartEventLoop(Variant v)
{

    PEvent returnval = Evaluator::mEventLoop.Loop();
    return Variant(returnval.GetDummyEvent().value);

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


Variant PEBLEnvironment::GetVideoModes(Variant v)
{
    return myEnv->GetScreenModes();

}

Variant  PEBLEnvironment::GetPEBLVersion(Variant v)
{
   
    return Variant("PEBL Version 0.12");
}


Variant PEBLEnvironment::GetSystemType(Variant v)
{
#if defined(PEBL_OSX)
    Variant type = "OSX";
#elif defined (PEBL_UNIX)
    Variant type = "LINUX";
#else
    Variant type = "WINDOWS";
#endif

    return type;
}


Variant PEBLEnvironment::SystemCall(Variant v)
{
    PList * plist = v.GetComplexData()->GetList();
    std::string call  = plist->First().GetString();
    
    const char* call2 = call.c_str();
    int x = system(call2);  //do a system call with the argument string.
    return Variant(x);
}





Variant PEBLEnvironment::IsDirectory(Variant v)
{
    PList * plist = v.GetComplexData()->GetList();

    PError::AssertType(plist->First(), PEAT_STRING, "Argument error in function [IsDirectory(<pathname>)]:  ");    

    Variant out = PEBLUtility::IsDirectory(plist->First());
    return out;
}


Variant PEBLEnvironment::GetDirectoryListing(Variant v)
{
    PList * plist = v.GetComplexData()->GetList();

    PError::AssertType(plist->First(), PEAT_STRING, "Argument error in function [GetDirectoryListing(<pathname>)]:  ");    

    Variant out = PEBLUtility::GetDirectoryListing(plist->First());
    return out;
}



Variant PEBLEnvironment::FileExists(Variant v)
{
    PList * plist = v.GetComplexData()->GetList();

    PError::AssertType(plist->First(), PEAT_STRING, "Argument error in function [FileExists(<filename>)]:  ");    

    Variant out = PEBLUtility::FileExists(plist->First());
    return out;
}



//  This does not currently work.
//
Variant PEBLEnvironment::VariableExists(Variant v)
{
   PList * plist = v.GetComplexData()->GetList();
   Variant x  = plist->First();
   return Variant(1);
}



Variant PEBLEnvironment::IsText(Variant v)
{
    PList * plist = v.GetComplexData()->GetList();

    return plist->First().IsString();
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



Variant PEBLEnvironment::IsJoystick(Variant v)
{
    PList * plist = v.GetComplexData()->GetList();

    Variant v1 =  plist->First();
    if (v1.IsComplexData())
        {
            if((v1.GetComplexData())->IsJoystick())
                {
                    return Variant(true);
                }
        }
    return Variant(false);
}




Variant PEBLEnvironment::IsCanvas(Variant v)
{
    PList * plist = v.GetComplexData()->GetList();
    Variant v1 =  plist->First();
    if (v1.IsComplexData())
        {
            if((v1.GetComplexData())->IsCanvas())
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

Variant PEBLEnvironment::IsWindow(Variant v)
{

    PList * plist = v.GetComplexData()->GetList();
    Variant v1 =  plist->First();
    if (v1.IsComplexData())
        {
            if((v1.GetComplexData())->IsWindow())
                {
                    return Variant(true);
                }
        }
    return Variant(false);
}


Variant PEBLEnvironment::IsShape(Variant v)
{

    PList * plist = v.GetComplexData()->GetList();
    Variant v1 =  plist->First();
    if (v1.IsComplexData())
        {
            if((v1.GetComplexData())->IsDrawObject())
                {
                    return Variant(true);
                }
        }
    return Variant(false);
}

