//* -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*- */
/////////////////////////////////////////////////////////////////////////////////
//    Name:       src/objects/PTextObject.cpp
//    Purpose:     Contains generic specs for all objects containing text
//    Author:     Shane T. Mueller, Ph.D.
//    Copyright:  (c) 2004-2005 Shane T. Mueller <smueller@obereed.net>
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
#include "PTextObject.h"
#include "PFont.h"

#include <string>
#include <iostream>
using std::cout;
using std::endl;

PTextObject::PTextObject():
    PWidget(0,0,0,0,false),
    mTextChanged(true),
    mText("")
{
    InitializeProperty("TEXT","");
    PrintProperties(cout);
}



PTextObject::PTextObject(const std::string & text):
    PWidget(0,0,0,0,false),
    mTextChanged(true),
    mText(std::string(text))
{
    InitializeProperty("TEXT",Variant(mText));
}


PTextObject::PTextObject( PTextObject &object):
    PWidget(0,0,0,0,false),
    mTextChanged(true),
    mText(object.GetText())
 
{
    InitializeProperty("TEXT",Variant(mText));
}

PTextObject::~PTextObject()
{
}
