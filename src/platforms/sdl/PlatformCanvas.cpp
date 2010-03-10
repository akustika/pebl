//* -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*- */
/////////////////////////////////////////////////////////////////////////////////
//    Name:       src/platforms/sdl/PlatformTextBox.cpp
//    Purpose:    Contains SDL-specific interface for a draw canvas.
//    Author:     Shane T. Mueller, Ph.D.
//    Copyright:  (c) 2010 Shane T. Mueller <smueller@obereed.net>
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

#include "PlatformCanvas.h"
#include "../../objects/PCanvas.h"
#include "SDLUtility.h"

#include "../../base/PComplexData.h"


#include "../../utility/rc_ptrs.h"
#include "../../utility/PError.h"
#include "../../utility/PEBLUtility.h"

#include "SDL/SDL.h"

#include <stdio.h>
#include <string>

using std::cout;
using std::cerr;
using std::endl;
using std::flush;
using std::list;
using std::ostream;
using std::string;


PlatformCanvas::PlatformCanvas(int width, int height, Variant bg):
    PlatformWidget(),
    PCanvas(width, height,bg)
{

    //    mWidth = width;
    //    mHeight = height;

    mCDT = CDT_CANVAS;
    InitializeProperty("BGCOLOR",bg);
    SetColor(bg);
    

    mSurface = NULL;
    Reset();
    Draw();

}


PlatformCanvas::PlatformCanvas(const PlatformCanvas & canvas):
    PlatformWidget(),
    PCanvas()
{

    mCDT = CDT_CANVAS;
    mWidth = canvas.GetWidth();
    mHeight = canvas.GetHeight();
    mSurface = NULL;
    Reset();   //reset initializes the canvas
    Draw();
    //    if(!RenderText()) cerr << "Unable to render text.\n";
}


///Standard Destructor
PlatformCanvas::~PlatformCanvas()
{
 
    // PlatformWidget frees mSurface, 
}

// Inheritable function that is called by friend method << operator of PComplexData
ostream & PlatformCanvas::SendToStream(ostream& out) const
{
    out << "<SDL PlatformCanvas>" <<flush;
    return out;
}

 


/// This method should be called when the font is initialized or the text is changed.
/// It will make the mSurface pointer hold the appropriate image.
bool  PlatformCanvas::Reset()
{



    //free the memory if it is currently pointing at something.
    if(mSurface)  SDL_FreeSurface(mSurface);

    //create a new surface on which to render the text.

#if SDL_BYTEORDER == SDL_BIG_ENDIAN

    Uint32 rmask = 0xff000000;
    Uint32 gmask = 0x00ff0000;
    Uint32 bmask = 0x0000ff00;
    Uint32 amask = 0x00000000;

#else

    Uint32 rmask = 0x000000ff;
    Uint32 gmask = 0x0000ff00;
    Uint32 bmask = 0x00ff0000;
    Uint32 amask = 0x00000000;

#endif



    //Make a surface of the prescribed size.
    mSurface = SDL_CreateRGBSurface(SDL_SWSURFACE, mWidth, mHeight, 32,
                                    rmask, gmask, bmask, amask);
    if(!mSurface)  PError::SignalFatalError("Surface not created in Canvas::Reset.");
    

    //Fill the box with the background color of the font.
    SDL_FillRect(mSurface, NULL, SDL_MapRGBA(mSurface->format, 
                                             mBackgroundColor.GetRed(),
                                             mBackgroundColor.GetGreen(),
                                             mBackgroundColor.GetBlue(),
                                             mBackgroundColor.GetAlpha()));
    

    mReset = false;  //Reset the reset button.

    //If mSurface is null, then rendering failed.
    if(mSurface)
        return true;
    else
        return false;
}


bool PlatformCanvas::SetProperty(std::string name, Variant v)
{
    
    return PCanvas::SetProperty(name,v);
}

bool PlatformCanvas::Draw()
{


    if(mReset)
        {
            Reset();
        }
    
    bool ret =     PlatformWidget::Draw();
    mReset = false;
    return  ret;
}



