//* -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*- */
/////////////////////////////////////////////////////////////////////////////////
//    Name:       src/platforms/sdl/PlatformEnvironment.cpp
//    Purpose:    Contains SDL-specific interface for the main environment.
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
#include "PlatformEnvironment.h"

#include "../../objects/PEnvironment.h"
#include "PlatformWindow.h"

#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"


#include <list>
#include <stdio.h>


#if defined PEBL_WIN32
#include <windows.h>
#include <ddraw.h>
#endif

using std::cout;
using std::cerr;
using std::endl;
using std::flush;
using std::list;
using std::ostream;


///Standard Constructor
PlatformEnvironment::PlatformEnvironment(PEBLVideoMode mode, PEBLVideoDepth depth, bool windowed):
    mVideoMode(mode),
    mVideoDepth(depth),
    mWindowed(windowed)
{
    mIsInitialized = false;
}


///Standard Destructor
PlatformEnvironment::~PlatformEnvironment()
{
    SDL_Quit();
}

// Inheritable function that is called by friend method << operator of PComplexData
ostream & PlatformEnvironment::SendToStream(ostream& out) const
{
    
    out << "<SDL PlatformEnvironment>" << flush;
    return out;
}



///This method initiates everything needed to display the main window
void PlatformEnvironment::Initialize()
{
    mIsInitialized = true;
    if ( SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) < 0 )
        {
            cerr << "Unable to init SDL: " <<  SDL_GetError() << endl;;
            mIsInitialized = false;
        }
    else if ( TTF_Init() < 0 )
        {
            /* Initialize the TTF library */
            cerr <<  "Couldn't initialize TTF: " << SDL_GetError() << endl;
            mIsInitialized = false;
        }
    else
        {
            cerr << "Successfully initialized SDL Graphics" << endl;
            //char name[32];
            //cerr  << "Using audio driver: " <<  SDL_AudioDriverName(name, 32) << endl;


        }


}

    

/// This method 'draws' the environment; it iterates through
/// each window in the environment and calls the draw method on each.
bool PlatformEnvironment::Draw()
{
    //Iterate through all child windows and draw them
    list<PWindow*>::iterator p;
    for(p=mWindows.begin(); p!= mWindows.end(); p++)
        {
            (*p)->Draw();
        }


    return true;
}

