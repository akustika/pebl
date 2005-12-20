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
#include "../base/PComplexData.h"

PDrawObject::PDrawObject()
{

    InitializeProperty("FILLED",Variant(0));
    InitializeProperty("COLOR",Variant(0));
    InitializeProperty("OUTLINECOLOR",Variant(0));

}



PDrawObject::~PDrawObject()
{
}


bool PDrawObject::SetProperty(std::string name, Variant v)
{
    if(!PWidget::SetProperty(name,v))

        if (name == "FILLED") SetFilled(v);
        else if (name == "COLOR") SetColor(v);
        else if (name == "OUTLINECOLOR")SetOutlineColor(v);
        else return false;
    
    return true;
}


Variant PDrawObject::GetProperty(std::string name)const
{
    return PEBLObjectBase::GetProperty(name);
}


ObjectValidationError PDrawObject::ValidateProperty(std::string name, Variant v)const
{
    return ValidateProperty(name);
}

ObjectValidationError PDrawObject::ValidateProperty(std::string name)const
{

    ObjectValidationError tmp = PWidget::ValidateProperty(name);
    
    if(tmp == OVE_SUCCESS ) return OVE_SUCCESS;
    else
        {
        if(name == "FILLED" ||
           name == "COLOR" ||
           name =="OUTLINECOLOR")
            return OVE_SUCCESS;
        else return OVE_INVALID_PROPERTY_NAME;
        }
}

void PDrawObject::SetFilled(bool filled)
{
    mFilled = filled;
    PEBLObjectBase::SetProperty("FILLED",filled);
}

void PDrawObject::SetColor(Variant col)
{
    PEBLObjectBase::SetProperty("COLOR",col);
    mColor = *dynamic_cast<PColor*>(col.GetComplexData()->GetObject().get());

}

void  PDrawObject::SetOutlineColor(Variant  ocol)
{
    PEBLObjectBase::SetProperty("OUTLINECOLOR",ocol);
    mOutlineColor = *dynamic_cast<PColor*>(ocol.GetComplexData()->GetObject().get());
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




bool PLine::SetProperty(std::string name, Variant v)
{

    if(!PDrawObject::SetProperty(name,v))
        if("DUMMY" == name) return true;
        else return false;
    
    return true;
}


Variant PLine::GetProperty(std::string name)const
{
    //return PEBLObjectBase::GetProperty(name);
    return Variant(name);
}


ObjectValidationError PLine::ValidateProperty(std::string name, Variant v)const
{
    return ValidateProperty(name);
}

ObjectValidationError PLine::ValidateProperty(std::string name)const
{
    return PDrawObject::ValidateProperty(name);
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

bool PRectangle::SetProperty(std::string name, Variant v)
{

    if(!PDrawObject::SetProperty(name,v))
        if("DUMMY" == name) return true;
        else return false;
    
    return true;
}


Variant PRectangle::GetProperty(std::string name)const
{
    return PEBLObjectBase::GetProperty(name);

}


ObjectValidationError PRectangle::ValidateProperty(std::string name, Variant v)const
{
    return ValidateProperty(name);
}

ObjectValidationError PRectangle::ValidateProperty(std::string name)const
{
    return PDrawObject::ValidateProperty(name);
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


bool PSquare::SetProperty(std::string name, Variant v)
{

    if(!PDrawObject::SetProperty(name,v))
        if("DUMMY" == name) return true;
        else return false;
    
    return true;
}


Variant PSquare::GetProperty(std::string name)const
{
    return PEBLObjectBase::GetProperty(name);

}


ObjectValidationError PSquare::ValidateProperty(std::string name, Variant v)const
{
    return ValidateProperty(name);
}

ObjectValidationError PSquare::ValidateProperty(std::string name)const
{
    return PDrawObject::ValidateProperty(name);
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

bool PEllipse::SetProperty(std::string name, Variant v)
{

    if(!PDrawObject::SetProperty(name,v))
        if("DUMMY" == name) return true;
        else return false;
    
    return true;
}


Variant PEllipse::GetProperty(std::string name)const
{
    return PEBLObjectBase::GetProperty(name);

}


ObjectValidationError PEllipse::ValidateProperty(std::string name, Variant v)const
{
    return ValidateProperty(name);
}

ObjectValidationError PEllipse::ValidateProperty(std::string name)const
{
    return PDrawObject::ValidateProperty(name);
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

bool PCircle::SetProperty(std::string name, Variant v)
{

    if(!PDrawObject::SetProperty(name,v))
        if("DUMMY" == name) return true;
        else return false;
    
    return true;
}


Variant PCircle::GetProperty(std::string name)const
{
    return PEBLObjectBase::GetProperty(name);

}


ObjectValidationError PCircle::ValidateProperty(std::string name, Variant v)const
{
    return ValidateProperty(name);
}

ObjectValidationError PCircle::ValidateProperty(std::string name)const
{
    return PDrawObject::ValidateProperty(name);
}
