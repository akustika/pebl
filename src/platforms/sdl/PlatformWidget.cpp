//* -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*- */
/////////////////////////////////////////////////////////////////////////////////
//    Name:       src/platforms/sdl/PlatformWidget.cpp
//    Purpose:    Contains SDL-specific interface GUI objects
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
#include "PlatformWidget.h"
#include "SDL/SDL.h"

#include <iostream>

using std::cout;
using std::cerr;
using std::endl;

//Standard constructor 
PlatformWidget::PlatformWidget():
    mSurface(NULL),
    mParentSurface(NULL)
{

}

PlatformWidget::~PlatformWidget()
{
    SDL_FreeSurface(mSurface);
    mSubWidgets.clear();
}



std::ostream & PlatformWidget::SendToStream(std::ostream& out) const
{
    out << "<SDL PlatformWidget> " << std::flush;
    return out;
}




bool PlatformWidget::Draw()
{

    if(IsVisible())
        {
            //To draw a widget, draw each of the window's subwidgets
            //(using PlatformWidget::Draw(SDLSurface)
            //This should be done backwards, so that the last item added
            //(which is on the front) will be the last item drawn.

            std::list<PWidget *>::iterator p = mSubWidgets.end();

            while(p != mSubWidgets.begin())
                {
                    //decrement iterator--moving backward so we draw things in 
                    //reverse order.
                    p--;
                    //Draw the subwidget
                    if((*p)->IsVisible())
                        {
                            (*p)->Draw();
                        }
                }
            
            //Once the widget sub-items are drawn, draw the widget to its parent.
            if (mParentSurface)
                {          
                    SDL_Rect  fromRect = {0,0,mWidth,mHeight};
                    SDL_Rect  toRect   = {mDrawX,mDrawY,mWidth,mHeight};
                    //  unsigne    d long int start =SDL_GetTicks();
                    SDL_BlitSurface(mSurface, &fromRect, mParentSurface, &toRect);
                    //  unsigned long int end =SDL_GetTicks();
                    //     cout << "Time to BlitSurface:  " << end - start << endl;
                }
            else
                {
                    // IF there is no parent, this is probably a window, which handles 
                    // performs a SDL_Flip after this method is called.
                }
        }
    return true;
}



SDL_Surface * PlatformWidget::GetSDL_Surface()
{
    return mSurface;
}




bool PlatformWidget::AddSubWidget(PlatformWidget * child)
{
    child->SetParentSurface(mSurface);
    PWidget::AddSubWidget(child);

    return true;
}


bool PlatformWidget::RemoveSubWidget(PlatformWidget * child)
{
    child->SetParentSurface(NULL);
    PWidget::RemoveSubWidget(child);

    return true;
}

void PlatformWidget::SetParentSurface(SDL_Surface* surface)
{
    mParentSurface = surface;
}


///This needs to be used on some platforms/video cards
bool PlatformWidget::LockSurface()
{
    if(SDL_MUSTLOCK(mSurface))
        { 

            //cout << "Locking-------->" << endl;
            //The below returns 0 on success, -1 otherwise,
            //so reverse it for t/f
            if(SDL_LockSurface(mSurface)<0)
                {
                    cerr << "Need to lock surface but can't\n";
                    return false;
                }
            return true;
        }
    
    return false;

}

///This needs to be used on some platforms/video cards
bool PlatformWidget::UnlockSurface()
{
   if(SDL_MUSTLOCK(mSurface))
        { 
            // cout << "------->Unlocking" << endl;
            SDL_UnlockSurface(mSurface);
        }
   return true;
}
