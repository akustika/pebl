//* -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*- */
///////////////////////////////////////////////////////////////////////////////
//    Name:       src/objects/PDrawObject.h
//    Purpose:    Utility class drawing things.
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
#ifndef __PDRAWOBJECT_H__
#define __PDRAWOBJECT_H__

#include "PWidget.h"
#include "PColor.h"


//A DrawObject is parallel to PWidget, but specific to drawing 
//primitives.
class PDrawObject: public virtual PWidget

{

public:

    PDrawObject();
    PDrawObject(int x, int y, const PColor & fg, const PColor & outline);
    virtual ~PDrawObject();
  
//     ///This unconditionally sets the parent widget.
//     virtual void SetParent(PWidget * widget){mParent = widget;}

//     ///This draws the subwidgets.  It doesn't need a 'parent'
//     ///argument, because 'this' is it.
//     virtual bool Draw(){return false;}

//     ///Sets the location of the upper left-hand corner of the
//     ///image on the parent widget.
//     virtual void SetPosition(int x, int y){mX=x; mY=y;};
    
//     virtual int GetX()const {return mX;};
//     virtual int GetY()const {return mY;};

//     //This returns the width and height of the drawing object.
//     virtual int GetWidth()const=0;
//     virtual int GetHeight()const=0;

//     virtual void SetColor(const PColor & color){mColor=color;};
//     virtual void SetBackgroundColor(const PColor & color){mOutlineColor=color;};
        
//     ///These change the visibility state.  If invisible, the widget gets
//     ///skipped over when drawn.
//     virtual void Show(){mIsVisible = true;}
//     virtual void Hide(){mIsVisible = false;}
//     virtual bool IsVisible(){return mIsVisible;}

protected:

    ///An inheritable printing class used by PObject::operator<<
    virtual std::ostream & SendToStream(std::ostream& out) const=0;
 
//     ///The x and y coordinates, in pixels, from the upper left corner
//     ///of the parent screen
//     int mX, mY;

//     //These are the actual locations of the points to be drawn.  They differ
//     //from mX and mY in labels and images, which are drawn on their center point.
//     int mDrawX;
//     int mDrawY;

//     /// The background color of the widget.  if alpha = 0, will not be painted.
    PColor mColor;
    PColor mOutlineColor;

//     //Whether this should actually get drawn.
//     bool mIsVisible;

//     ///The parent widget. If null (0), this has no parent (top-level window).
//     ///or is currently unattached.
//     PWidget * mParent;
private:

};


class PLine: public virtual PDrawObject
{
public:
    PLine(int x1, int y1, int dx, int dy, const PColor & fg);
    ~PLine();
    virtual int GetWidth() const{return mX2;};
    virtual int GetHeight() const{return mY2;};
    virtual std::ostream & SendToStream(std::ostream& out);

protected:
    //X1--Y2 are relative to mX and mY
    int mX1;
    int mY1;
    int mX2;
    int mY2;  
    int mWidth;

    bool mAntiAliased;
private:
};

// class PBezier: public PDrawObject
// {
// };

// class PPolygon: public PDrawObject
// {
// public:
//     PPolygon();
//     ~PPolygon();
// protected:
// private:
// };

// class PTriangle: public PPolygon
// {
// public:
//     PTriangle();
//     ~PTriangle();
// protected:
// private:

// };

// class PTrapezoid: public PPolygon
// {
// public:
//     PTrapezoid();
//     ~PTrapezoid();
// protected:
// private:
// };


// class PRectangle: public PTrapezoid
// {
// public:
//     PRectangle();
//     ~PRectangle();
// protected:
// private:
// };

// class PSquare: public PRectangle
// {
// public:
//     PSquare();
//     ~PSquare();
// protected:
// private:
// };


// class PEllipse: public PDrawObject
// {
// public:
//     PEllipse();
//     ~PEllipse();
// protected:
// private:
// };


// class PCircle: public PEllipse
// {
// public:
//     PCircle();
//     ~PCircle();
// protected:
// private:

// };


// class PDrawGroup: public PDrawObject
// {
// public:
//     PDrawGroup();
//     ~PDrawGroup();
// protected:
// private:
// };


#endif
