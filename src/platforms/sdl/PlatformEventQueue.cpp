//* -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*- */
/////////////////////////////////////////////////////////////////////////////////
//    Name:       src/platforms/sdl/PlatformEventQueue.cpp
//    Purpose:    Interface to platform-specific event queue.
//    Author:     Shane T. Mueller, Ph.D.
//    Copyright:  (c) 2004-2008 Shane T. Mueller <smueller@obereed.net>
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

#include "PlatformEventQueue.h"
#include "../../devices/PEventQueue.h"
#include "../../devices/PEvent.h"
#include "../../utility/PError.h"
#include "SDL/SDL.h"

using std::cout;
using std::endl;


//This should be moved into PEventQueue
PlatformEventQueue::PlatformEventQueue()
{
}

PlatformEventQueue::~PlatformEventQueue()
{
}



/// The Prime method takes any all events waiting in the SDL
/// event queue, converts them to PEvents, stamps them with a timestamp,
/// and puts them into the platform-generic event queue.
void PlatformEventQueue::Prime()
{

	SDL_Event test_event;
    unsigned long int time = SDL_GetTicks();

	//Get the next event in the queue. SDL_PollEvent returns 0 
    //when there are no pending events available.
    while(SDL_PollEvent(&test_event))
        {
            
            //cout << "Event [" << (int)(test_event.type) << "]\n";

            //first, check to see if the event is the 'magic' abort event: ctrl-alt-shift-X.

            if(test_event.type == SDL_KEYDOWN)
                {
                    if(test_event.key.keysym.sym == SDLK_BACKSLASH)
                        {
                            if((test_event.key.keysym.mod & KMOD_SHIFT )
                               && (test_event.key.keysym.mod & KMOD_ALT)
                               && (test_event.key.keysym.mod & KMOD_CTRL))
                                {
                                    PError::SignalFatalError("Stopping execution: Received abort key-combo.\n");
                                }
                        }

                }

            //Create a PEBL event from the SDL event, if possible.
            
            switch(test_event.type) 
                {
                    
                case SDL_KEYDOWN:
                    {

                        
                        //Determine which key is being used.

                        PEvent evt(PDT_KEYBOARD, time);
                        PEBL_KeyboardEvent pke;
                        pke.key = (PEBLKey)(test_event.key.keysym.sym);
                        pke.state = PEBL_PRESSED;
                        pke.modkeys = test_event.key.keysym.mod;

                        evt.SetKeyboardEvent(pke);
                        mEventQueue.push(evt);
                       
                    }
                    break;
 
                case SDL_KEYUP:
                    {
                        //create a new event to add to the queue.
                        PEvent evt(PDT_KEYBOARD, time);

                        //The event has a keyboard event inside it.
                        PEBL_KeyboardEvent pke;
                        pke.key = (PEBLKey)(test_event.key.keysym.sym);
                        pke.state = PEBL_RELEASED;
                        pke.modkeys = test_event.key.keysym.mod;

                        evt.SetKeyboardEvent(pke);
                        mEventQueue.push(evt);

                    }
                    break;
                    
                case SDL_QUIT:
                    PError::SignalFatalError("Stopping execution because of quit signal.\n");
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    {
                        PEvent evt(PDT_MOUSE_BUTTON, time);
                        PEBL_MouseButtonEvent pme;

                        pme.x= test_event.button.x;
                        pme.y= test_event.button.y;
                        pme.button=test_event.button.button;
                        pme.state =test_event.button.state;


                        pme.state = PEBL_PRESSED;

                        evt.SetMouseButtonEvent(pme);
                        mEventQueue.push(evt);
                        //cout << "mouse down ["<< pme.x << " " << pme.y << "]\n";
                        

                    }
                    break;

                case SDL_MOUSEBUTTONUP:
                    {

                        PEvent evt(PDT_MOUSE_BUTTON, time);
                        PEBL_MouseButtonEvent pme;

                        pme.x= test_event.button.x;
                        pme.y= test_event.button.y;
                        pme.button=test_event.button.button;
                        pme.state =test_event.button.state;

                        pme.state = PEBL_RELEASED;

                        evt.SetMouseButtonEvent(pme);
                        mEventQueue.push(evt);

                    }

                case SDL_MOUSEMOTION:
                    {
                        PEvent evt(PDT_MOUSE_MOVEMENT, time);
                        PEBL_MouseMovementEvent pme;
                        
                        pme.x= test_event.motion.x;
                        pme.y= test_event.motion.y;
                        pme.relx =test_event.motion.xrel;
                        pme.rely =test_event.motion.yrel;


                        evt.SetMouseMovementEvent(pme);
                        mEventQueue.push(evt);

                    }

                default:
                    ;
                }

            time =  SDL_GetTicks();
            
        }
}
