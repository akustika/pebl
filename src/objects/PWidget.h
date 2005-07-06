//* -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*- */
/////////////////////////////////////////////////////////////////////////////////
//    Name:       src/objects/PWidget.h
//    Purpose:    Contains the Definition of the basic gui widget
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
#ifndef __PWIDGET_H__
#define __PWIDGET_H__

#include "PObject.h"
#include "PColor.h"

#include <list>
#include <iostream>

///
/// This class is the main visual gui base class.  It is an abstract class, containing methods that need
/// to be overriden by an inherited class (i.e., Platform*) to be used.


class PWidget: public PObject
{
public:
  
    PWidget();
    PWidget(int x, int y, int width, int height, bool visible);
    virtual ~PWidget();
  

    ///This unconditionally sets the parent widget.
    virtual void SetParent(PWidget * widget){mParent = widget;}

    ///This draws the subwidgets.  It doesn't need a 'parent'
    ///argument, because 'this' is it.
    virtual bool Draw(){return false;}

    ///Sets the location of the upper left-hand corner of the
    ///image on the parent widget.
    virtual void SetPosition(int x, int y);
    
    virtual int GetX()const {return mX;};
    virtual int GetY()const {return mY;};

    virtual int GetWidth()const {return mWidth;};
    virtual int GetHeight()const {return mHeight;};

     
    virtual void SetBackgroundColor(PColor  color);
    virtual PColor  GetBackgroundColor(){return mBackgroundColor;};
    
    ///AddSubWidget takes care of adding a widget to a parent widget, and setting
    ///the parent field of the child widget to the parent widget.
    virtual bool AddSubWidget(PWidget * widget);

    ///This method iterates through the subwidgets and sees if any
    ///are equal to the argument.  If so, it removes it.  It does not delete it.
    virtual bool RemoveSubWidget(PWidget * widget);

    ///This is probably pretty useless.
    virtual bool RemoveLastSubWidget();
    
    ///These change the visibility state.  If invisible, the widget gets
    ///skipped over when drawn.
    virtual void Show(){mIsVisible = true;}
    virtual void Hide(){mIsVisible = false;}
    virtual bool IsVisible(){return mIsVisible;}

protected:

    ///An inheritable printing class used by PObject::operator<<
    virtual std::ostream & SendToStream(std::ostream& out) const;
 
    ///The x and y coordinates, in pixels, from the upper left corner
    ///of the parent screen
    int mX, mY;

    //These are the actual locations of the points to be drawn.  They differ
    //from mX and mY in labels and images, which are drawn on their center point.
    int mDrawX;
    int mDrawY;

    ///The height and width, in pixels, of the loaded widget
    int mWidth, mHeight;

    /// The background color of the widget.  if alpha = 0, will not be painted.
    PColor  mBackgroundColor;

   //A list of sub-widgets.
    std::list<PWidget*> mSubWidgets;

    //Whether this should actually get drawn.
    bool mIsVisible;

    ///The parent widget. If null (0), this has no parent (top-level window).
    ///or is currently unattached.
    PWidget * mParent;
private:



};


#endif
