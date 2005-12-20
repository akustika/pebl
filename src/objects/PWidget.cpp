//* -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*- */
/////////////////////////////////////////////////////////////////////////////////
//    Name:       src/objects/PWidget.cpp
//    Purpose:    Contains methods for primary GUI element
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
#include "PWidget.h"
#include <list>
#include <iostream>

using std::cout;
using std::endl;

PWidget::PWidget():
    mX(0),
    mY(0),
    mDrawX(0),
    mDrawY(0),
    mWidth(0),
    mHeight(0),
    mIsVisible(true),
    mParent(NULL)
{
    
    InitializeProperty("X",Variant(mX));
    InitializeProperty("Y",Variant(mY));
    InitializeProperty("WIDTH",Variant(mWidth));
    InitializeProperty("HEIGHT",Variant(mHeight));
    InitializeProperty("VISIBLE",Variant(mIsVisible));
    
}

PWidget::PWidget(int x, int y, int width, int height, bool visible):
    mX(x),
    mY(y),
    mDrawX(x),
    mDrawY(y),
    mWidth(width),
    mHeight(height),
    mIsVisible(visible),
    mParent(NULL)
{

     InitializeProperty("X",Variant(mX));
     InitializeProperty("Y",Variant(mY));
     InitializeProperty("WIDTH",Variant(mWidth));
     InitializeProperty("HEIGHT",Variant(mHeight));
     InitializeProperty("VISIBLE",Variant(mIsVisible));

}


PWidget::~PWidget()
{
}


bool PWidget::SetProperty(std::string name, Variant v)
{

    //Height and width are not universally settable.

    if(!PWidget::SetProperty(name,v))

        if (name == "X") SetPosition(v,mY);
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



Variant  PWidget::GetProperty(std::string name)const
{
    return PEBLObjectBase::GetProperty(name);
}



 ObjectValidationError PWidget::ValidateProperty(std::string, Variant v)const
{
    return OVE_SUCCESS;
}


 ObjectValidationError PWidget::ValidateProperty(std::string)const
{
    return OVE_SUCCESS;
}


///This sets the widget's position on its parent widget.
void PWidget::SetPosition(int x, int y)
{
    mX = x;
    mY = y;
    mDrawX = x;
    mDrawY = y;

     PEBLObjectBase::SetProperty("X",mX);
     PEBLObjectBase::SetProperty("Y",mY);
}



//Inherited from PComplexObject->PEBLObjectBase
std::ostream & PWidget::SendToStream(std::ostream& out) const
{
    out << "<Unknown PWidget>" << std::flush;
    return out;
}


void PWidget::SetBackgroundColor(PColor color)
{
    mBackgroundColor = color;
}



bool PWidget::AddSubWidget(PWidget * widget)
{

    mSubWidgets.push_front(widget);
    widget->SetParent(this);
    return true;
}


bool PWidget::RemoveSubWidget(PWidget * widget)
{
    mSubWidgets.remove(widget);
    widget->SetParent(NULL);
    return true;
}

bool PWidget::RemoveLastSubWidget()
{
    mSubWidgets.pop_front();
    return true;
}


void PWidget::Show()
{
    mIsVisible = true;
    PEBLObjectBase::SetProperty("VISIBLE",mIsVisible);

}
void PWidget::Hide()
{
    mIsVisible = false;    
    PEBLObjectBase::SetProperty("VISIBLE",mIsVisible);
}


