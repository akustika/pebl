//* -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*- */
/////////////////////////////////////////////////////////////////////////////////
//    Name:       src/objects/PWidget.cpp
//    Purpose:    Contains methods for primary GUI element
//    Author:     Shane T. Mueller, Ph.D.
//    Copyright:  (c) 2003-2010 Shane T. Mueller <smueller@obereed.net>
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
#include "../base/PComplexData.h"
#include "../utility/PError.h"
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
    //    InitializeProperty("NAME",Variant(""));
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
    //    InitializeProperty("NAME",Variant(""));
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


bool PWidget::SetPoint(int x, int y, PColor col)
{
    //This should go straight to PlatforwWidget::SetPoint

    return false;
}


PColor PWidget::GetPixel(int x, int y)
{
    //This should go straight to PlatforwWidget::GetPixel

    return false;
}



bool PWidget::SetProperty(std::string name, Variant v)
{


    ObjectValidationError err = ValidateProperty(name,v);
    if(err == OVE_SUCCESS)
        {
            if (name == "X") SetPosition(v,mY);
            else if (name == "Y") SetPosition(mX,v);
            else if (name == "ZOOMX") SetZoomX((long double)v);
            else if (name == "ZOOMY") SetZoomY((long double)v);
            else if (name == "ROTATION") SetRotation((long double)v);
            else if (name == "WIDTH") SetWidth((int)v);
            else if (name == "HEIGHT") SetHeight((int)v);
            else if (name == "BGCOLOR") 
                {

                    SetBackgroundColor(*((PColor*)(v.GetComplexData())));
                }
            else if (name == "VISIBLE")
                {
                    if(v.GetInteger())
                        Show();
                    else 
                        Hide();
                }
        
            else return false;
        } 
    else
        {
            PError::SignalFatalError("Failing to set invalid property: ["+ name +"]" );
            return false;
        }
    return false;
}


Variant  PWidget::GetProperty(std::string name)const
{
    return PEBLObjectBase::GetProperty(name);
}



 ObjectValidationError PWidget::ValidateProperty(std::string name, Variant v)const
{
    return ValidateProperty(name);
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
       name == "BGCOLOR" ||
       name == "ROTATION" ||
       name == "NAME")
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
    PEBLObjectBase::SetProperty("ZOOMX",mZoomX);
}
///This sets the widget's position on its parent widget.
void PWidget::SetZoomY(double y)
{
    mZoomY = y;
    PEBLObjectBase::SetProperty("ZOOMY",mZoomY);
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
    counted_ptr<PEBLObjectBase> pob = counted_ptr<PEBLObjectBase>(&mBackgroundColor);
    PComplexData * pcd = new PComplexData(pob);
    Variant col = Variant(pcd);
    InitializeProperty("BGCOLOR", col);
}



bool PWidget::AddSubWidget(PWidget * widget)
{

    //Remove the subwidget if it is already there.
    mSubWidgets.remove(widget);    

    //now, add it back on:
    mSubWidgets.push_front(widget);
    widget->SetParent(this);
    return true;
}

bool PWidget::RemoveSubWidgets()

{                       
    if(mSubWidgets.size()>0)
        {

            std::list<PWidget*>::iterator i = mSubWidgets.begin();
            while(i != mSubWidgets.end())
                {
                    
                    (*i)->SetParent(NULL);
                    mSubWidgets.pop_front();
                    i=mSubWidgets.begin();  //readjust so it points to the start of the list.
                }

            mSubWidgets.clear();
        }
    return true;
}


bool PWidget::RemoveSubWidget(PWidget * widget)
{

    widget->SetParent(NULL);
    mSubWidgets.remove(widget);

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


