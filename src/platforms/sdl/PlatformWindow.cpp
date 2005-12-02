//* -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*- */
/////////////////////////////////////////////////////////////////////////////////
//    Name:       src/platforms/sdl/PlatformWindow.cpp
//    Purpose:    Contains SDL-specific interface for the main window class.
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
#include "PlatformWindow.h"
#include "../../objects/PWindow.h"
#include "../../objects/PColor.h"
#include "../../base/Evaluator.h"
#include "../../base/VariableMap.h"

#include "SDL/SDL.h"
#include <stdio.h>

using std::cout;
using std::cerr;
using std::endl;
using std::flush;
using std::list;
using std::ostream;


///Standard Constructor
PlatformWindow::PlatformWindow():
    mCDT(CDT_WINDOW)
{
    PWidget::SetBackgroundColor(counted_ptr<PColor>(new PColor(200,200,200,255)));
}


///Standard Destructor
PlatformWindow::~PlatformWindow()
{
 
}

// Inheritable function that is called by friend method << operator of PComplexData
ostream & PlatformWindow::SendToStream(ostream& out) const
{
    out << "<SDL PlatformWindow>" << flush;
    return out;
}

int PlatformWindow::GetVideoFlags()
{
	int videoFlags;
	const SDL_VideoInfo *videoInfo;


	videoInfo = SDL_GetVideoInfo();
	if (videoInfo == NULL) {
        std::cerr << "SDL Video Error in PEBL" << endl;
	}


	// This checks to see if surfaces can be stored in memory
	if (videoInfo->hw_available)
        {
            videoFlags  = SDL_HWSURFACE;
            videoFlags |= SDL_DOUBLEBUF; 
            videoFlags |= SDL_HWPALETTE;
            //videoFlags |= SDL_FULLSCREEN;
            videoFlags |= SDL_ANYFORMAT;      
            cerr << "Hardware surfaces available.\n";
        }
	else 
        {
            videoFlags  = SDL_SWSURFACE;
            //videoFlags |= SDL_RESIZABLE;       // Enable window resizing
            cerr << "Hardware surfaces NOT available.\n";
        }

	// This checks if hardware blits can be done
	if (videoInfo->blit_hw)
        {
            cerr << "Hardware blits are possible.\n";
            videoFlags |= SDL_HWACCEL;
        }
    
	return videoFlags;
}



///This method initiates everything needed to display the main window
bool PlatformWindow::Initialize(PEBLVideoMode mode, 
                                PEBLVideoDepth vdepth, 
                                bool windowed)
{  
    Variant v = 0;
    Evaluator * myEval = new Evaluator(v,"Window");
    //gVideoWidth and gVideoHeight may have been set by the user
    //in the script.  First, get these values, and try them.

    Variant vWidth =  0;
    Variant vHeight = 0;
    Variant vDp =  0;

    //Extract video values from variable values.
    if(myEval->gGlobalVariableMap.Exists("gVideoWidth"))
        vWidth =  myEval->gGlobalVariableMap.RetrieveValue("gVideoWidth");

    if(myEval->gGlobalVariableMap.Exists("gVideoHeight"))
       vHeight =  myEval->gGlobalVariableMap.RetrieveValue("gVideoHeight");

    if(myEval->gGlobalVariableMap.Exists("gVideoDepth"))
        vDp =   myEval->gGlobalVariableMap.RetrieveValue("gVideoDepth");

    int vflags = GetVideoFlags();

    int width  = vWidth;
    int height = vHeight;
    int depth  = vDp;    

    //If either width or height are undefined, get the externally-set value.
    if(!( width>0 && height>0))
    switch(mode)
        {
		case PVM_512_384:
            width=512;
            height=384;
            break;

		case PVM_640_480:
            width=640;
            height=480;
            break;

		case PVM_800_600:
            width=800;
            height=600;
            break;

		case PVM_960_720:
            width=960;
            height=720;
            break;

		case PVM_1024_768:
            width=1024;
            height=768;
            break;

		case PVM_1152_864:
            width=1152;
            height=864;
            break;

		case PVM_1280_1024:
            width=1280;
            height=1024;
            break;


        default:
            width=640;
            height=480;
            break;
        }

    if(!(depth > 0))
        depth = (int)vdepth;

    if(!windowed)
        {
            vflags |=  SDL_FULLSCREEN;       // Enable fullscreen
        }

    
       //Re-stare the values
       myEval->gGlobalVariableMap.AddVariable("gVideoWidth", width);
       myEval->gGlobalVariableMap.AddVariable("gVideoHeight", height);
       myEval->gGlobalVariableMap.AddVariable("gVideoDepth", depth);
       delete myEval;
       
       
       //INitialize the SDL surface with the appropriate flags.
       mSurface=SDL_SetVideoMode(width,height,depth,vflags);
       
       if ( mSurface == NULL )
    {          
        cerr << "Unable to set " << width << "x" << height << ": " << depth << " video mode: " << SDL_GetError() << endl;
            return false;
        }
    else
        {
            cerr << "\n\n----------------------------------------------------------------------------------------\n";        
            cerr << " Current Video Mode:" << endl;
            cerr << "----------------------------------------------------------------------------------------\n";
            const SDL_VideoInfo * info = SDL_GetVideoInfo();
            cerr << "hw_available   Is it possible to create hardware surfaces?:           [" << info->hw_available << "]\n";
            cerr << "wm_available   Is there a window manager available:                   [" << info->wm_available << "]\n";
            cerr << "blit_hw        Are hardware to hardware blits accelerated?:           [" << info->blit_hw << "]\n";
            cerr << "blit_hw_CC     Are hardware to hardware colorkey blits accelerated?:  [" << info->blit_hw_CC << "]\n";
            cerr << "blit_hw_A      Are hardware to hardware alpha blits accelerated?:     [" << info->blit_hw_A << "]\n";
            cerr << "blit_sw        Are software to hardware blits accelerated?:           [" << info->blit_sw << "]\n";
            cerr << "blit_sw_CC     Are software to hardware colorkey blits accelerated?:  [" << info->blit_sw_CC << "]\n";
            cerr << "blit_sw_A      Are software to hardware alpha blits accelerated?:     [" << info->blit_sw_A << "]\n";
            cerr << "blit_fill      Are color fills accelerated?:                          [" << info->blit_fill << "]\n";
            cerr << "video_mem      Total amount of video memory in Kilobytes:             [" << info->video_mem << "]\n";
            cerr << "Display Mode:  Width  (pixels)                                        [" << width << "]\n";
            cerr << "Display Mode:  Height (pixels)                                        [" << height << "]\n";
            cerr << "Display Mode:  Color Depth (bits)                                     [" << depth << "]\n";

            cerr << "---------------------------------- PIXEL FORMAT----------------------------------------\n";

            const SDL_PixelFormat *pf = info->vfmt;
            
            cerr << "SDL_Palette *palette (0 for realcolor):     [" << pf->palette  << "]\n";
            /*       cerr << "BitsPerPixel:                               [" << Uint8(pf->BitsPerPixel) << "]\n";
            cerr << "BytesPerPixel:                              [" << Uint8(pf->BytesPerPixel) << "]\n";
            cerr << "Rmask, Gmask, Bmask, Amask:                 [" << Uint8(pf->Rmask) <<"] [" << Uint8(pf->Gmask) <<"] [" <<  Uint8( pf->Bmask) << "] ["  <<   Uint8(pf->Amask) << "]\n";
            cerr << "Rshift, Gshift, Bshift, Ashift:             [" << Uint8(pf->Rshift)   <<"] ["  <<  Uint8(pf->Gshift) <<"] ["  <<  Uint8(pf->Bshift) << "] ["  <<  Uint8(pf->Ashift) << "]\n";
            cerr << "Rloss, Gloss, Bloss, Aloss:                 [" << Uint8(pf->Rloss)    <<"] ["  <<  Uint8(pf->Gloss) <<"] ["  <<  Uint8(pf->Bloss) << "] ["  <<  Uint8(pf->Aloss) << "]\n";
            cerr << "colorkey:                                   [" << pf->colorkey << "]\n";
            cerr << "alpha:                                      [" << Uint8(pf->alpha)    << "]\n";
            */
            char drivername[20];
            SDL_VideoDriverName(drivername, 20);
            cerr << "Using Video Driver: " << drivername << endl;
            
            cerr << "---------------------------------------------------------------------------------------\n\n";

            return true;
        }

}

bool PlatformWindow::Draw()
{
 
    //First, draw the background       
    SDL_FillRect(mSurface, NULL, SDL_MapRGBA(mSurface->format, 
                                             mBackgroundColor->GetRed(),
                                             mBackgroundColor->GetGreen(),
                                             mBackgroundColor->GetBlue(),
                                             mBackgroundColor->GetAlpha()));

    
    //Now, draw the subwidgets.
    PlatformWidget::Draw();
    
    int result = SDL_Flip(mSurface);
    
    if(result == -2)
        {
            cerr << "Lost Video Memory; reload everything" ;
        }
   
    return !result;
}

// This will draw the current screen repeatedly for cycles cycles and return.
// On platforms where SDL_Flip blocks until it finishes (e.g., maybe like linux),
// then it should return immediately after the vsync, allowing time for removing the 
// surface or whatever.  On platforms where SDL_Flip returns immediately, it should
// still block until the _next_ cycle, so it will return right after the n-1 cycle, giving
// time to delete etc before another draw command needs to be issued.
long int PlatformWindow::DrawFor(unsigned int cycles)
{

    //Do an initial syncing flip.
    int result = 0;// = SDL_Flip(mSurface);
        //First, draw the background       
    SDL_FillRect(mSurface, NULL, SDL_MapRGBA(mSurface->format, 
                                             mBackgroundColor->GetRed(),
                                             mBackgroundColor->GetGreen(),
                                             mBackgroundColor->GetBlue(),
                                             mBackgroundColor->GetAlpha()));

    
    
    //Now, draw the subwidgets.
    PlatformWidget::Draw();

    unsigned int cyclesleft = cycles;
    unsigned int tstart=0;
    while(result != -2 && cyclesleft > 0 )
        {
            //Get the time *AFTER* the first cycle. 
            //This method will only really work on a platform wher SDL_Flip blocks.
            if(cyclesleft==cycles) tstart = SDL_GetTicks();
            result = SDL_Flip(mSurface);
            cyclesleft--;
        }
    
    unsigned int tend = SDL_GetTicks();
    if(result == -2)
        {
            cerr << "Lost Video Memory; reload everything" ;
        }
    else
        {
            result = tend-tstart;
        }
    //If the return value is positive, it is the time that
    //this was displayed.  Otherwise, it is an error code.
    return result;

}
