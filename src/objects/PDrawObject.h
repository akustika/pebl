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

#include <vector>

//A DrawObject is parallel to PWidget, but specific to drawing 
//primitives.
class PDrawObject: virtual public PWidget

{

public:

    PDrawObject();
    //PDrawObject(int x, int y, const PColor & fg, const PColor & outline);
    //PDrawObject(int x, int y, const PColor & fg, const PColor & outline, bool filled);
    virtual ~PDrawObject();
    virtual void SetFilled(bool filled);
    virtual void SetColor(Variant  col);
    virtual void SetOutlineColor(Variant ocol);

    //overloaded generic PEBLObjectBase methods
    virtual bool SetProperty(std::string, Variant v);
    virtual Variant GetProperty(std::string)const;
    virtual ObjectValidationError ValidateProperty(std::string, Variant v)const;
    virtual ObjectValidationError ValidateProperty(std::string)const;

protected:

    ///An inheritable printing class used by PEBLObjectBase::operator<<
    virtual std::ostream & SendToStream(std::ostream& out) const=0;
 
    PColor mColor;
    PColor mOutlineColor;
    bool mFilled;

private:

};


class PLine: public PDrawObject
{
public:
    PLine(int x1, int y1, int dx, int dy, Variant fg);
    virtual ~PLine();
    virtual int GetWidth() const{return mDX;};
    virtual int GetHeight() const{return mDY;};
    virtual void SetSize(int dx, int dy);
    virtual std::ostream & SendToStream(std::ostream& out);


    //overloaded generic PEBLObjectBase methods
    virtual bool SetProperty(std::string, Variant v);
    virtual Variant GetProperty(std::string)const;
    virtual ObjectValidationError ValidateProperty(std::string, Variant v)const;
    virtual ObjectValidationError ValidateProperty(std::string)const;


protected:
    //X1--Y2 are relative to mX and mY
    int mDX;  
    int mDY;  

    bool mAntiAliased;

private:
};

// class PBezier: public PDrawObject
// {
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



//For rectangles/squares, the 'position' is at the center of the object.
//
 class PRectangle: public PDrawObject
 {
 public:
     PRectangle(int x1, int y1, int dx, int dy, Variant fg, bool filled);
     virtual ~PRectangle();
     virtual int GetWidth() const{return mDX;};
     virtual int GetHeight() const{return mDY;};
     virtual void SetSize(int dx, int dy);
     virtual std::ostream & SendToStream(std::ostream& out);

     //overloaded generic PEBLObjectBase methods
     virtual bool SetProperty(std::string, Variant v);
     virtual Variant GetProperty(std::string)const;
     virtual ObjectValidationError ValidateProperty(std::string, Variant v)const;
     virtual ObjectValidationError ValidateProperty(std::string)const;


 protected:
     int mDX;
     int mDY;
 private:
 };

 class PSquare: public PRectangle
 {
 public:
     PSquare(int x, int y, int size, Variant fg, bool filled);
     virtual ~PSquare();
     virtual int GetWidth() const{return mDX;};
     virtual int GetHeight() const{return mDY;};
     virtual void SetSize(int size);
     virtual std::ostream & SendToStream(std::ostream& out);
     


     //overloaded generic PEBLObjectBase methods
     virtual bool SetProperty(std::string, Variant v);
     virtual Variant GetProperty(std::string)const;
     virtual ObjectValidationError ValidateProperty(std::string, Variant v)const;
     virtual ObjectValidationError ValidateProperty(std::string)const;

 protected:
 private:
 };


class PEllipse: public  PDrawObject
 {
 public:
     PEllipse(int x1, int y1, int rx, int ry, Variant fg, bool filled);
     virtual ~PEllipse();
     virtual int GetWidth() const{return mRX;};
     virtual int GetHeight() const{return mRY;};
     virtual void SetSize(int dx, int dy);
     virtual std::ostream & SendToStream(std::ostream& out);
     

     //overloaded generic PEBLObjectBase methods
     virtual bool SetProperty(std::string, Variant v);
     virtual Variant GetProperty(std::string)const;
     virtual ObjectValidationError ValidateProperty(std::string, Variant v)const;
     virtual ObjectValidationError ValidateProperty(std::string)const;


 protected:
     
     //X1--Y2 are relative to mX and mY
     int mRX;
     int mRY;  


 private:
};


 class PCircle: public PDrawObject
 {
 public:
     PCircle(int x1, int y1, int r, Variant fg, bool filled);
     virtual ~PCircle();

     virtual int GetWidth() const{return (int)(2*mR);};
     virtual int GetHeight() const{return (int)(2*mR);};
     virtual std::ostream & SendToStream(std::ostream& out);

     virtual void SetSize(int r);

    //overloaded generic PEBLObjectBase methods
     virtual bool SetProperty(std::string, Variant v);
     virtual Variant GetProperty(std::string)const;
     virtual ObjectValidationError ValidateProperty(std::string, Variant v)const;
     virtual ObjectValidationError ValidateProperty(std::string)const;


 protected:

     double mR;
 private:
 };



 class PPolygon: public PDrawObject
 {
 public:
     PPolygon(int x, int y, Variant xpoints, Variant ypoints,  Variant fg, bool filled);
     virtual ~PPolygon();

     virtual int GetWidth() const{return mWidth;};
     virtual int GetHeight() const{return mHeight;};

     virtual bool SetXPoints(Variant v);
     virtual bool SetYPoints(Variant v);

     virtual std::ostream & SendToStream(std::ostream& out);


    //overloaded generic PEBLObjectBase methods
     virtual bool SetProperty(std::string, Variant v);
     virtual Variant GetProperty(std::string)const;
     virtual ObjectValidationError ValidateProperty(std::string, Variant v)const;
     virtual ObjectValidationError ValidateProperty(std::string)const;


 protected:

     Variant mXPoints;
     Variant mYPoints;

 private:
 };


 class PBezier: public PDrawObject
 {
 public:
     PBezier(int x, int y, Variant xpoints, Variant ypoints,  int steps, Variant fg);
     virtual ~PBezier();

     virtual int GetWidth() const{return mWidth;};
     virtual int GetHeight() const{return mHeight;};

     virtual bool SetXPoints(Variant v);
     virtual bool SetYPoints(Variant v);
     virtual bool SetSteps(Variant v);

     virtual std::ostream & SendToStream(std::ostream& out);


    //overloaded generic PEBLObjectBase methods
     virtual bool SetProperty(std::string, Variant v);
     virtual Variant GetProperty(std::string)const;
     virtual ObjectValidationError ValidateProperty(std::string, Variant v)const;
     virtual ObjectValidationError ValidateProperty(std::string)const;


 protected:

     Variant mXPoints;
     Variant mYPoints;
     int mSteps;
 private:
 };

#endif





