//* -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*- */
/////////////////////////////////////////////////////////////////////////////////
//    Name:       src/objects/PWord.h
//    Purpose:    Contains generic specs for all objects containing text
//    Author:     Shane T. Mueller, Ph.D.
//    Copyright:  (c) 2003 Shane T. Mueller <smueller@umich.edu>
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
#ifndef __PTEXTOBJECT_H__
#define __PTEXTOBJECT_H__


#include "PWidget.h"
#include "PFont.h"
#include "PColor.h"
#include "../utility/rc_ptrs.h"

#include <string>

///  This class simply represent a visual word.  It contains a pointer to a PFont structure
///  and a character string. It can be used by a higher-level class to represent a string of
///  text; but do so while keeping track of the specific locations of words. 
///  It actually can represent multiple words, but only displays a single line.


class PTextObject: virtual public PWidget
{
public:
    PTextObject();
    PTextObject(const std::string & text);
    PTextObject(PTextObject & object);
    virtual ~PTextObject();

    virtual void SetText(const std::string & text){mText = text; mTextChanged = true;}
    virtual std::string GetText()const {return mText;}

    virtual int GetNumCharacters(){return mText.length();}


private:


protected:

    
    virtual std::ostream & SendToStream(std::ostream& out) const{return out;};

    bool mTextChanged;     //Determines whether the object should be re-rendered.
    std::string mText;
};


#endif
