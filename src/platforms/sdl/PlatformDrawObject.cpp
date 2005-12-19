//* -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*- */
///////////////////////////////////////////////////////////////////////////////
//    Name:       src/platforms/sdl/PlatformDrawObject.cpp
//    Purpose:    Platform-specific classes drawing things.
//    Author:     Shane T. Mueller, Ph.D.
//    Copyright:  (c) 2005 Shane T. Mueller <smueller@obereed.net>
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

#include "PlatformDrawObject.h"
#include "PlatformWidget.h"

#include "SDL/SDL.h"
#include "SDL/SDL_gfxPrimitives.h"

#include <iostream>

// PlatformDrawObject::PlatformDrawObject(PlatformWidget * widget)
// {
//     mSurface = widget->GetSDL_Surface();
//     mParentSurface = NULL;
//     mIsVisible=true;
// }

// PlatformDrawObject::PlatformDrawObject(PlatformWidget * widget, int x, int y ):
//     mSurface(widget->GetSDL_Surface())
// {

//     mX = x;
//     mY = y;


// }

//  PlatformDrawObject::~PlatformDrawObject()
// {
//     //Don't delete the surface--it belongs to somebody else.
// }

//  bool PlatformDrawObject::Draw()
// {
 
//     return true;
// }


// std::ostream & PlatformDrawObject::SendToStream(std::ostream& out) const
// {

//     out << "A draw object";
//     return out;
// }


// SDL_Surface * PlatformDrawObject::GetSDL_Surface()
// {
//     return mSurface;
// }

//  bool PlatformDrawObject::SetParentSurface(SDL_Surface * surface)
// {
//     mParentSurface = surface;
//     return true;
// }


// ///This needs to be used on some platforms/video cards
// bool PlatformDrawObject::LockSurface()
// {
//     if(SDL_MUSTLOCK(mSurface))
//         { 

//             //cout << "Locking-------->" << endl;
//             //The below returns 0 on success, -1 otherwise,
//             //so reverse it for t/f
//             if(SDL_LockSurface(mSurface)<0)
//                 {
//                     std::cerr << "Need to lock surface but can't\n";
//                     return false;
//                 }
//             return true;
//         }
    
//     return false;

// }

// ///This needs to be used on some platforms/video cards
// bool PlatformDrawObject::UnlockSurface()
// {
//    if(SDL_MUSTLOCK(mSurface))
//         { 
//             // cout << "------->Unlocking" << endl;
//             SDL_UnlockSurface(mSurface);
//         }
//    return true;
// }




PlatformLine::PlatformLine(int x1, int y1, int dx, int dy, PColor fg):
    PLine(x1,y1,dx,dy,fg)
{
    mCDT=CDT_DRAWOBJECT;
    //mX = x1;
    //mY = y1;
    mSurface =NULL;
    mParent = NULL;
    mIsVisible=true;
}

PlatformLine::~PlatformLine()
{

}

std::ostream & PlatformLine::SendToStream(std::ostream& out) const
{
    out << "<A line:"<< mX1 << ", " << mY1 << ":" << mX2 << ", " << mY2 << std::endl;
    return out;
}

bool PlatformLine::Draw()
{

    int result;
    //LockSurface();
 
    result = lineRGBA(mParentSurface,mX+mX1, mY + mY1, mX+mX2, mY+mY2,
                      mColor.GetRed(), mColor.GetGreen(), mColor.GetBlue(), mColor.GetAlpha());
    
    //UnlockSurface();
    return result;
}


PlatformRectangle::PlatformRectangle(int x1, int y1, int dx, int dy, PColor fg, bool filled):
    PRectangle(x1,y1,dx,dy,fg,filled)
{
    mCDT = CDT_DRAWOBJECT;
}

PlatformRectangle::~PlatformRectangle()
{
}

bool PlatformRectangle::Draw()
{

    int result;
    //LockSurface();
    if(mFilled)
        {
            result = boxRGBA(mParentSurface,mX+mX1, mY + mY1, mX+mDX, mY+mDY,
                             mColor.GetRed(), mColor.GetGreen(), mColor.GetBlue(), mColor.GetAlpha());
       
        }
    else
        {
            result = rectangleRGBA(mParentSurface,mX+mX1, mY + mY1, mX+mDX, mY+mDY,
                                   mColor.GetRed(), mColor.GetGreen(), mColor.GetBlue(), mColor.GetAlpha());
            
        }
    //UnlockSurface();
    return result;

}

std::ostream & PlatformRectangle::SendToStream(std::ostream& out) const
{
    out << "A Rectangle";
    return out;
}


PlatformSquare::PlatformSquare(int x, int y, int size, PColor fg, bool filled):
    PSquare(x,y,size,fg,filled)

{
    mCDT=CDT_DRAWOBJECT;
}

PlatformSquare::~PlatformSquare()
{
}


bool PlatformSquare::Draw()

{

   int result;
    //LockSurface();
    if(mFilled)
        {
            result = boxRGBA(mParentSurface,mX+mX1, mY + mY1, mX+mDX, mY+mDY,
                             mColor.GetRed(), mColor.GetGreen(), mColor.GetBlue(), mColor.GetAlpha());
       
        }
    else
        {
            result = rectangleRGBA(mParentSurface,mX+mX1, mY + mY1, mX+mDX, mY+mDY,
                                   mColor.GetRed(), mColor.GetGreen(), mColor.GetBlue(), mColor.GetAlpha());
            
        }
    //UnlockSurface();
    return result;
}


std::ostream & PlatformSquare::SendToStream(std::ostream& out) const
{
    out << "A Square";
    return out;
}








PlatformEllipse::PlatformEllipse(int x1, int y1, int dx, int dy, PColor fg, bool filled):
    PEllipse(x1,y1,dx,dy,fg, filled)
{
    mCDT = CDT_DRAWOBJECT;
    mSurface =NULL;
    mParent = NULL;
    mIsVisible=true;
    mX = x1;
    mY = y1;

}

PlatformEllipse::~PlatformEllipse()
{

}

std::ostream & PlatformEllipse::SendToStream(std::ostream& out) const
{
    out << "<An ellipse:"<< mX1 << ", " << mY1 << ":" << mRX << ", " << mRY << std::endl;
    return out;
}

bool PlatformEllipse::Draw()
{

    int result;
    //LockSurface();
    if(mFilled)
        {
            result = filledEllipseRGBA(mParentSurface,mX+mX1, mY + mY1, mRX, mRY,
                                     mColor.GetRed(), mColor.GetGreen(), mColor.GetBlue(), mColor.GetAlpha());
            
        }
    else
        {
            result = ellipseRGBA(mParentSurface,mX+mX1, mY + mY1, mRX, mRY,
                                 mColor.GetRed(), mColor.GetGreen(), mColor.GetBlue(), mColor.GetAlpha());
        }
    //UnlockSurface();
    return result;
}



PlatformCircle::PlatformCircle(int x1, int y1, int r, PColor fg, bool filled):
    PCircle(x1,y1,r,fg,filled)

{
    mCDT=CDT_DRAWOBJECT;
    mSurface =NULL;
    mParent = NULL;
    mIsVisible=true;
    //    mX = x1;
    //    mY = y1;

}

PlatformCircle::~PlatformCircle()
{

}

std::ostream & PlatformCircle::SendToStream(std::ostream& out) const
{
    out << "<A Circle :"<< mX1 << ", " << mY1 << ":" << mR  << std::endl;
    return out;
}

bool PlatformCircle::Draw()
{
    int result;
    //LockSurface();
    if(mFilled)
        {
            result = filledCircleRGBA(mParentSurface, mX+mX1,  mY+mY1, (int)mR,
                                      mColor.GetRed(), mColor.GetGreen(), mColor.GetBlue(), mColor.GetAlpha());

        }
    else
        {
            result = circleRGBA(mParentSurface,mX+mX1, mY + mY1, (int)mR,
                                mColor.GetRed(), mColor.GetGreen(), mColor.GetBlue(), mColor.GetAlpha());
        }
    //UnlockSurface();
    return result;
}
