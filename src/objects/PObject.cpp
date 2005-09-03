//* -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*- */
/////////////////////////////////////////////////////////////////////////////////
//    Name:       src/objects/PObject.cpp
//    Purpose:    Contains a simple list class, part of the Variant Class
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

#include "PObject.h"

#include "../base/PComplexData.h"
#include "../utility/PError.h"
#include <stdio.h>

using std::cout;
using std::cerr;
using std::endl;
using std::flush;
using std::list;
using std::ostream;


///Standard Constructor
PObject::PObject()
{
}



///Standard Destructor
PObject::~PObject()
{
  
}


bool PObject::SetProperty(std::string name, Variant v)
{

    ObjectValidationError err = ValidateProperty(name,v);
    if(err == OVE_SUCCESS)
        {
            mProperties[name]=v;
            return true;
        }
    else
        {
            PError::SignalFatalError("Failing to set property\n");
            return false;
        }
}


bool PObject::InitializeProperty(std::string name, Variant v)
{
    mProperties[name]=v;
    return true;
}

Variant PObject::GetProperty(const std::string name)const
{
 
    
   ObjectValidationError err = ValidateProperty(name);
    if(err == 0)
        return mProperties.find(name)->second;
    else
        {

 
            PError::SignalFatalError("Attempted to get invalid property [" + name + "] of object.");
        }
    return Variant(0);
}


//By default, just check to see if the property exists.
ObjectValidationError PObject::ValidateProperty(std::string name, Variant v)const
{
    return ValidateProperty(name);
}

ObjectValidationError PObject::ValidateProperty(std::string name)const
{
    if(mProperties.find(name) == mProperties.end())
        return OVE_INVALID_PROPERTY_NAME;
    else
        return OVE_SUCCESS;
}


//Overload of the << operator
std::ostream & operator <<(std::ostream & out, const PObject & object )
{
    object.SendToStream(out);
    return out;
}



std::string PObject::ObjectName() const
{
    return "<Unknown PObject>";
}

ostream & PObject::PrintProperties(ostream& out) const
{
    out << "----------\n";
    std::map<std::string, Variant>::const_iterator i;
    i = mProperties.begin();
    while(i != mProperties.end())
        {
            out << i->first << " " <<  i->second << endl;
            i++;
        }
    out << "----------\n";


    return out;

}

// Inheritable function that is called by friend method << operator of PComplexData
ostream & PObject::SendToStream(ostream& out) const
{
    
    out << ObjectName() << flush;
    return out;
}
