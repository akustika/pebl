//* -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*- */
///////////////////////////////////////////////////////////////////////////////
//    Name:       src/objects/PDrawObject.cpp
//    Purpose:    Platform-generic classes drawing things.
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

#include "PDrawObject.h"
#include "PWidget.h"


PDrawObject::PDrawObject()
{
}



PDrawObject::~PDrawObject()
{
}



PLine::PLine(int x1, int y1, int dx, int dy, PColor fg):
    mX1(0),
    mY1(0),
    mX2(dx),
    mY2(dy)
{

    mX = x1;
    mY = y1;

    mBackgroundColor = fg;
    mColor = fg;
    mOutlineColor = fg;
}

PLine::~PLine()
{
}

std::ostream & PLine::SendToStream(std::ostream& out)
{
  out << "PLine";
  return out;
}


PRectangle::PRectangle(int x1, int y1, int dx, int dy, PColor fg, bool filled):
    mX1(-dx/2),
    mY1(-dy/2),
    mDX(dx),
    mDY(dy)
{
    mX = x1 + dx/2;
    mY = y1 + dy/2;
    mFilled = filled;
    mBackgroundColor = fg;
    mColor = fg;
    mOutlineColor = fg;
}


PRectangle:: ~PRectangle()
{
}

std::ostream & PRectangle::SendToStream(std::ostream& out)
{
    out <<"PRectangle";
    return out;
}




PSquare::PSquare(int x, int y, int size, PColor fg, bool filled):
    PRectangle(x,y,size,size,fg,filled)
{
    mX = x + size/2;
    mY = y + size/2;
    mFilled = filled;
    mBackgroundColor = fg;
    mColor = fg;
    mOutlineColor = fg;
}


PSquare:: ~PSquare()
{
}

std::ostream & PSquare::SendToStream(std::ostream& out)
{
    out <<"PSquare";
    return out;
}







PEllipse:: PEllipse(int x1, int y1, int rx, int ry, PColor fg, bool filled):
    mX1(0),
    mY1(0),
    mRX(rx),
    mRY(ry)

{
    mX = x1;
    mY = y1;
    mFilled = filled;

    std::cout << mX << " " << mY << std::endl;
    mBackgroundColor = fg;
    mColor = fg;
    mOutlineColor = fg;
}

PEllipse::~PEllipse()
{
}

std::ostream & PEllipse::SendToStream(std::ostream& out)
{
  out << "PEllipse";
  return out;
}


PCircle:: PCircle(int x1, int y1, int r, PColor fg, bool filled):
    mX1(0),
    mY1(0),
    mR(r)
{
    mFilled = filled;
    mX = x1;
    mY = y1;
    
    mBackgroundColor = fg;
    mColor = fg;
    mOutlineColor = fg;
}

PCircle::~PCircle()
{

}



std::ostream & PCircle::SendToStream(std::ostream& out)
{
  out << "PCircle";
  return out;
}
