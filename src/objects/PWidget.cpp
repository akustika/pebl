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
    mZoomX(1),
    mZoomY(1),
    mRotation(0),
    mIsVisible(true),
    mParent(NULL)
{
    
    InitializeProperty("X",Variant(mX));
    InitializeProperty("Y",Variant(mY));
    InitializeProperty("WIDTH",Variant(mWidth));
    InitializeProperty("HEIGHT",Variant(mHeight));
    InitializeProperty("VISIBLE",Variant(mIsVisible));
    InitializeProperty("ZOOMX",Variant(mZoomX));
    InitializeProperty("ZOOMY",Variant(mZoomY));
    InitializeProperty("ROTATION",Variant(mRotation));
    
}

PWidget::PWidget(int x, int y, int width, int height, bool visible):
    mX(x),
    mY(y),
    mDrawX(x),
    mDrawY(y),
    mWidth(width),
    mHeight(height),
    mZoomX(1.0),
    mZoomY(1.0),
    mRotation(0),
    mIsVisible(visible),
    mParent(NULL)
{
    
    InitializeProperty("X",Variant(mX));
    InitializeProperty("Y",Variant(mY));
    InitializeProperty("WIDTH",Variant(mWidth));
    InitializeProperty("HEIGHT",Variant(mHeight));
    InitializeProperty("VISIBLE",Variant(mIsVisible));
    InitializeProperty("ZOOMX",Variant(mZoomX));
    InitializeProperty("ZOOMY",Variant(mZoomY));
    InitializeProperty("ROTATION",Variant(mRotation));
    
}

PWidget::~PWidget()
{
}

bool PWidget::RotoZoom(double angle, double zoomx, double zoomy, int smooth)
{
    
    return false;
}

bool PWidget::SetProperty(std::string name, Variant v)
{


    //Height and width are not universally settable.

    if (name == "X") SetPosition(v,mY);
    else if (name == "Y") SetPosition(mX,v);
    else if (name == "ZOOMX") SetZoomX((long double)v);
    else if (name == "ZOOMY") SetZoomY((long double)v);
    else if (name == "ROTATION") SetRotation((long double)v);
    else if (name == "WIDTH") SetWidth((int)v);
    else if (name == "HEIGHT") SetHeight((int)v);
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



 ObjectValidationError PWidget::ValidateProperty(std::string name, Variant v)const
{
    return OVE_VALID;
}


 ObjectValidationError PWidget::ValidateProperty(std::string name)const
{


    //This only returns valid for properties that are valid to widgets
    //in general--subclasses need to check on their own.
    if(name == "X" ||
       name == "Y" ||
       name == "VISIBLE" ||
       name == "WIDTH" ||
       name == "HEIGHT" ||
       name == "ZOOMX" ||
       name == "ZOOMY" ||
       name == "ROTATION")
        return OVE_VALID;
    else
        return OVE_INVALID_PROPERTY_NAME;
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

///This sets the widget's position on its parent widget.
void PWidget::SetZoomX(double x)
{
    mZoomX = x;
    PEBLObjectBase::SetProperty("ZOOMX",mX);
}
///This sets the widget's position on its parent widget.
void PWidget::SetZoomY(double y)
{
    mZoomY = y;
    PEBLObjectBase::SetProperty("ZOOMY",mY);
}



void PWidget::SetHeight(int h)
{
    mHeight = h;
    PEBLObjectBase::SetProperty("HEIGHT",mHeight);

}

void PWidget::SetWidth(int w)
{
    mWidth = w;
    PEBLObjectBase::SetProperty("WIDTH",mWidth);

}

///This sets the widget's position on its parent widget.
void PWidget::SetRotation(double x)
{
    mRotation = x;
    PEBLObjectBase::SetProperty("ROTATION",x);
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


