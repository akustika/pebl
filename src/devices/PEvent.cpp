//* -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*- */
/////////////////////////////////////////////////////////////////////////////////
//    Name:        src/devices/PEvent.cpp
//    Purpose:     Events processed by Event Loop.
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
#include "PEvent.h"
#include "../utility/PError.h"

#include <iostream>

using std::cout;
using std::cerr;
using std::endl;

PEvent::PEvent(PEBL_DEVICE_TYPE type, long unsigned int time):
	mType(type),
    mEventTime(time)
{
}

PEvent::PEvent(const PEvent & evt)
{
    mType = evt.GetType();
    
    switch(mType)
		{
		case PDT_KEYBOARD:
            {   
                PEBL_KeyboardEvent event = evt.GetKeyboardEvent();
                mEvent.keyboardEvent = event;
            }
			break;
			
		case PDT_MOUSE_MOVEMENT:
            {
                PEBL_MouseMovementEvent event = evt.GetMouseMovementEvent();
                mEvent.mouseMovementEvent = event;
            }
            break;

		case PDT_MOUSE_BUTTON:
		case PDT_TIMER:
        case PDT_UNKNOWN:
		default:
            ;
		}

}

void PEvent::SetKeyboardEvent(const PEBL_KeyboardEvent & evt)
{
	mType = PDT_KEYBOARD;
    mEvent.keyboardEvent = evt;
}


void PEvent::SetMouseMovementEvent(const PEBL_MouseMovementEvent & evt)
{
    mType = PDT_MOUSE_MOVEMENT;
    mEvent.mouseMovementEvent = evt;
}
void PEvent::SetDummyEvent(const PEBL_DummyEvent & evt)
{
    mEvent.dummyEvent = evt;
}

PEvent::~PEvent()
{
}



PEBL_KeyboardEvent PEvent::GetKeyboardEvent() const
{
    if(PDT_KEYBOARD ==  mType )
        return mEvent.keyboardEvent;
    else
        {
            PEBL_KeyboardEvent tmp;
            tmp.key = PEBLKEY_UNKNOWN;
            tmp.state = PEBL_UNKNOWN;
            tmp.modkeys = 0;
            return tmp;
        }
}

PEBL_MouseMovementEvent PEvent::GetMouseMovementEvent() const
{
    if(PDT_MOUSE_MOVEMENT ==  mType )
        return mEvent.mouseMovementEvent;
    else
        {
            PEBL_MouseMovementEvent tmp;
            tmp.x = 0;
            tmp.y = 0;
            tmp.relx = 0;
            tmp.rely = 0;
            return tmp;
        }
}


PEBL_DummyEvent PEvent::GetDummyEvent() const
{
    if(PDT_DUMMY == mType)
        return mEvent.dummyEvent;
    else
        {
            PEBL_DummyEvent tmp;
            tmp.value = 0;
            return tmp;
        }
}


int PEvent::GetState(int iface) const
{
       
    //  This gets the 'state' described in an event.
    switch(mType)
        {
 
            //For keyboard events, the interface is the key.
        case PDT_KEYBOARD:
 
            //If the interface is the "anykey", return the key state
            if((PEBLKey)iface == PEBLKEY_ANYKEY)
                {
                    return mEvent.keyboardEvent.state;
                }
 
            //Determine which key is being used.
            if(mEvent.keyboardEvent.key == (PEBLKey)iface)
                {
                    return mEvent.keyboardEvent.state;
                }
            else
                return 0;
 
            break;
             
 
            
        case PDT_MOUSE_MOVEMENT:
        case PDT_MOUSE_BUTTON:
        case PDT_TIMER:
        case PDT_UNKNOWN:
            return PEBL_UNKNOWN;
             
        default:
             
            cerr << mType << endl;
            PError::SignalFatalError("Unhandled device type in PEvent::GetState\n");
 
            break;
        }
                 
     
    return PEBL_UNKNOWN;
}
 
