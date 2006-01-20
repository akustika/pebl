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
    
    if(tmp == OVE_VALID ) return OVE_VALID;
    else
        {
        if(name == "FILLED" ||
           name == "COLOR" ||
           name =="OUTLINECOLOR")
            return OVE_VALID;
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


PLine::PLine(int x1, int y1, int dx, int dy, Variant col):
    PDrawObject(),
    mDX(dx),
    mDY(dy)
{
    InitializeProperty("DX",dx);
    InitializeProperty("DY",dy);

    SetPosition(x1,y1);
    PDrawObject::SetColor(col);

}

PLine::~PLine()
{
}


void PLine::SetSize(int dx, int dy)
{
    mDX = dx;
    mDY = dy;
    PEBLObjectBase::SetProperty("DX",dx);
    PEBLObjectBase::SetProperty("DY",dy);
}


bool PLine::SetProperty(std::string name, Variant v)
{

    if(PDrawObject::SetProperty(name,v))
        {
            return true;
        } else {
            
            if("DX" == name) 
                SetSize(v,mDY);
            else if ("DY" == name)
                SetSize(mDX, v);
            else
                return false;
        }
    
    return true;
}


Variant PLine::GetProperty(std::string name)const
{
    return PEBLObjectBase::GetProperty(name);
}


ObjectValidationError PLine::ValidateProperty(std::string name, Variant v)const
{
    return ValidateProperty(name);
}


ObjectValidationError PLine::ValidateProperty(std::string name)const
{

   if(OVE_VALID == PDrawObject::ValidateProperty(name))
       {
           return OVE_VALID;
       }
   else
       {
           if("DX" == name || "DY" == name )
               return OVE_VALID;
           else return OVE_INVALID_PROPERTY_NAME;
       }
}


std::ostream & PLine::SendToStream(std::ostream& out)
{
  out << "PLine";
  return out;
}


PRectangle::PRectangle(int x1, int y1, int dx, int dy, Variant col, bool filled)
{
    InitializeProperty("DX",dx);
    InitializeProperty("DY",dy);
    SetSize(dx,dy);
    SetPosition(x1,y1);
    SetFilled(filled);
    PDrawObject::SetColor(col);
    PDrawObject::SetOutlineColor(col);
}


PRectangle:: ~PRectangle()
{
}

void PRectangle::SetSize(int dx, int dy)
{
    mDX = dx;
    mDY = dy;
    PEBLObjectBase::SetProperty("DX",dx);
    PEBLObjectBase::SetProperty("DY",dy);
    Draw();
}

bool PRectangle::SetProperty(std::string name, Variant v)
{

    if(!PDrawObject::SetProperty(name,v))
        if("DX" == name) SetSize(v,mDY);
        else if("DY" == name) SetSize(mDX,v);
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




PSquare::PSquare(int x, int y, int size, Variant col, bool filled):
    PRectangle(x,y,size,size,col,filled)
{
    InitializeProperty("SIZE",size);
    SetSize(size);
}


PSquare:: ~PSquare()
{
}






std::ostream & PSquare::SendToStream(std::ostream& out)
{
    out <<"PSquare";
    return out;
}

void PSquare::SetSize(int size)
{
    mDX = size;
    mDY = size;
    PEBLObjectBase::SetProperty("DX",size);
    PEBLObjectBase::SetProperty("DY",size);
    PEBLObjectBase::SetProperty("SIZE",size);
    
}

bool PSquare::SetProperty(std::string name, Variant v)
{
    if(!PDrawObject::SetProperty(name,v))
        {
            
            if("DX" == name || 
               "DY" == name || 
               "SIZE" == name)
                {
                    SetSize(v);
                }
            else return false;
        }
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






PEllipse:: PEllipse(int x1, int y1, int rx, int ry, Variant col, bool filled)
{
    SetPosition(x1,y1);
    SetFilled(filled);
    InitializeProperty("RX",rx);
    InitializeProperty("RY",ry);
    SetSize(rx,ry);
    SetColor(col);
    SetOutlineColor(col);
}

PEllipse::~PEllipse()
{
}
void PEllipse::SetSize(int dx, int dy)
{
    mRX = dx;
    mRY = dy;
    PEBLObjectBase::SetProperty("RX",dx);
    PEBLObjectBase::SetProperty("RY",dy);
}

std::ostream & PEllipse::SendToStream(std::ostream& out)
{
  out << "PEllipse";
  return out;
}

bool PEllipse::SetProperty(std::string name, Variant v)
{
    
    if(!PDrawObject::SetProperty(name,v))
        if("RX" == name) SetSize(v,mRY);
        else if ("RY" == name)SetSize(mRX,v);
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


PCircle::PCircle(int x1, int y1, int r, Variant fg, bool filled)
{
    
    SetPosition(x1,y1);
    SetFilled(filled);
    InitializeProperty("R",r);
    SetSize(r);
    SetColor(fg);
    SetOutlineColor(fg);
}

PCircle::~PCircle()
{

}

void PCircle::SetSize(int r)
{
    mR = r;
    PEBLObjectBase::SetProperty("R",r);
}


std::ostream & PCircle::SendToStream(std::ostream& out)
{
  out << "PCircle";
  return out;
}

bool PCircle::SetProperty(std::string name, Variant v)
{

    if(!PDrawObject::SetProperty(name,v))
        if("R" == name) SetSize(v);
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