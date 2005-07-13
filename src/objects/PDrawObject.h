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
    //PDrawObject(int x, int y, const PColor & fg, const PColor & outline);
    //PDrawObject(int x, int y, const PColor & fg, const PColor & outline, bool filled);
    virtual ~PDrawObject();
    virtual void SetFilled(bool filled){mFilled = filled;};

protected:

    ///An inheritable printing class used by PObject::operator<<
    virtual std::ostream & SendToStream(std::ostream& out) const=0;
 
    PColor mColor;
    PColor mOutlineColor;
    bool mFilled;

private:

};


class PLine: public virtual PDrawObject
{
public:
    PLine(int x1, int y1, int dx, int dy, const PColor & fg);
    virtual ~PLine();
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

    bool mFilled;
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


class PEllipse: public virtual PDrawObject
 {
 public:
     PEllipse(int x1, int y1, int rx, int ry, const PColor & fg, bool filled);
     virtual ~PEllipse();
     virtual int GetWidth() const{return mRX;};
     virtual int GetHeight() const{return mRY;};
     virtual std::ostream & SendToStream(std::ostream& out);
     
 protected:
     
     //X1--Y2 are relative to mX and mY
     int mX1;
     int mY1;
     int mRX;
     int mRY;  


 private:
};


 class PCircle: public virtual PDrawObject
 {
 public:
     PCircle(int x1, int y1, int r, const PColor & fg, bool filled);
     virtual ~PCircle();

     virtual int GetWidth() const{return (int)(2*mR);};
     virtual int GetHeight() const{return (int)(2*mR);};
     virtual std::ostream & SendToStream(std::ostream& out);

 protected:

     int mX1;
     int mY1;
     double mR;
 private:
 };


// class PDrawGroup: public PDrawObject
// {
// public:
//     PDrawGroup();
//     ~PDrawGroup();
// protected:
// private:
// };


#endif
