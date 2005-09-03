//* -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*- */
/////////////////////////////////////////////////////////////////////////////////
//    Name:       src/objects/PImageBox.cpp
//    Purpose:    Contains generic specification for a imagebox  class.
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

#include "PImageBox.h"
#include <iostream>

using std::cout;

PImageBox::PImageBox():
    PWidget()
{

 
}

///This sets the imagebox's position on its parent widget.
///It overrides the parent method because images positions
///are set by their centers.
void PImageBox::SetPosition(int x, int y)
{


    PWidget::SetPosition(x,y);
    mDrawX = x - GetWidth()/2;
    mDrawY = y - GetHeight()/2;

}



//overloaded generic PObject methods
bool PImageBox::SetProperty(std::string name, Variant v)
{


    if(name == "X") SetPosition(v,mY);
    else if (name == "Y") SetPosition(mX,v);
    else if (name == "VISIBLE") 
        {
            if(v.GetInteger())
                Show();
            else 
                Hide();
        }
    else return false;

    return true;
}


Variant PImageBox::GetProperty(std::string name)const
{
    return PObject::GetProperty(name);
}


ObjectValidationError PImageBox::ValidateProperty(std::string name, Variant v)const
{

    return ValidateProperty(name);
}

ObjectValidationError PImageBox::ValidateProperty(std::string name)const
{
    if(name == "X" ||
       name == "Y" ||
       name == "VISIBLE" ||
       name == "WIDTH" ||
       name == "HEIGHT" )
        return OVE_SUCCESS;
    else
        return OVE_INVALID_PROPERTY_NAME;
}



//This makes sure that the object properties are synced with the class properties.
void PImageBox::__SetProps__()
{

    PObject::SetProperty("X",mX);
    PObject::SetProperty("Y",mY);
    PObject::SetProperty("VISIBLE",mIsVisible);
    PObject::SetProperty("WIDTH",mWidth);
    PObject::SetProperty("HEIGHT",mHeight);

}
