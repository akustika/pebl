//* -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*- */
/////////////////////////////////////////////////////////////////////////////////
//    Name:       src/devices/PEven.h
//    Purpose:    Events processed by Event Loop.
//    Author:     Shane T. Mueller, Ph.D.
//    Copyright:  (c) 2004 Shane T. Mueller <smueller@obereed.net>
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
#ifndef __PEVENT_H__
#define __PEVENT_H__

#include "PKeyboard.h"

//These are some super-lightweight structs for
//representing different events.

//Various useful symbolic enumerations.
enum
	{
        PEBL_UNKNOWN = 0,
		PEBL_UP,
		PEBL_DOWN,
		PEBL_LEFT,
		PEBL_RIGHT,
		PEBL_PRESSED,
		PEBL_RELEASED
	};



//Keyboard Events
typedef struct
{
	PEBLKey key;
	unsigned int state; //PEBL_PRESSED or PEBL_RELEASED
    int modkeys;   //or'ed set of mod keys.
} PEBL_KeyboardEvent;


//Mouse movement events
typedef struct
{
	unsigned int x, y;
	int relx, rely;
		
} PEBL_MouseMovementEvent;


typedef struct
{
    int value; 
    
} PEBL_DummyEvent;


class PEvent
{
 public:
	PEvent(PEBL_DEVICE_TYPE type, long unsigned int time);
    PEvent::PEvent(const PEvent & evt);

	~PEvent();

	PEBL_DEVICE_TYPE GetType() const {return mType;};
    
    void SetKeyboardEvent(const PEBL_KeyboardEvent & evt);
    void SetMouseMovementEvent(const PEBL_MouseMovementEvent & evt);
    void SetDummyEvent(const PEBL_DummyEvent & evt);
    
    int GetState(int iface) const;
    
    unsigned long int GetEventTime(){return mEventTime;};
    
    PEBL_KeyboardEvent GetKeyboardEvent() const;
    PEBL_MouseMovementEvent GetMouseMovementEvent() const;
    PEBL_DummyEvent GetDummyEvent() const;

 private:

	PEBL_DEVICE_TYPE mType;

    union
	{
		PEBL_KeyboardEvent      keyboardEvent;
		PEBL_MouseMovementEvent mouseMovementEvent;	
        PEBL_DummyEvent         dummyEvent;
	} mEvent;

    //This keeps track of the time the event was 
    //first processed at.
    unsigned long int mEventTime;
};


#endif
