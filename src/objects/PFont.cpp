//* -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*- */
/////////////////////////////////////////////////////////////////////////////////
//    Name:       src/objects/PFont.cpp
//    Purpose:    Contains generic specification for a font
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
#include "PFont.h"
#include "PColor.h"


///Standard constructor of PFont

PFont::PFont():
    mFontFileName(strdup("Vera.ttf")),
    mFontStyle(PFS_Normal),
    mFontSize(16),
    mFontColor(PColor(0,0,0,255)),
    mBackgroundColor(PColor(0,0,0,0)),
    mAntiAliased(false)
{
} 


///Convenience constructor of PFont:
PFont::PFont(const char* filename, int style, int size, PColor fgcolor, PColor bgcolor, bool aa):
    mFontFileName(strdup(filename)),
    mFontStyle(style),
    mFontSize(size),
    mFontColor(fgcolor),
    mBackgroundColor(bgcolor),
    mAntiAliased(aa)
{

};


///Copy constructor of PFont:
PFont::PFont(const PFont & font)
{
    mFontFileName    = font.GetFontFileName();
    mFontStyle       = font.GetFontStyle();
    mFontSize        = font.GetFontSize();
    mFontColor       = font.GetFontColor();
    mBackgroundColor = font.GetBackgroundColor();
    mAntiAliased     = font.GetAntiAliased();

}


///Standard destructor of PFont
PFont::~PFont()
{
    if(mFontFileName)
        free(mFontFileName);
}



/// This sends the font descriptions to the specified stream.
std::ostream & PFont::SendToStream(std::ostream& out) const
{
    out << "<PFont: Name:        [" << mFontFileName << "]\n";
    out << "        Style:       ["<< mFontStyle<< "]\n";
    out << "        Size:        ["<< mFontSize << "]\n";
    out << "        Color:       ["<< mFontColor << "]\n";
    out << "        BGColor:     ["<< mBackgroundColor<< "]\n";
    out << "        Antialiased: ["<< mAntiAliased << "]>\n";

    return out;
}

 
//These get different styles
bool PFont::IsNormalFont() const
{
    return mFontStyle == 0;
}

bool PFont::IsBoldFont() const
{
    //The PFS_Bold acts as a bit filter, if it isn't bold the & should be 0.
    return (mFontStyle & PFS_Bold);
}

bool PFont::IsItalicFont() const
{
    //The PFS_Italic acts as a bit filter, if it isn't bold the & should be 0.
    return (mFontStyle & PFS_Italic);
}

bool PFont::IsUnderlineFont() const
{
    //The PFS_Underline acts as a bit filter, if it isn't bold the & should be 0.
    return (mFontStyle & PFS_Underline);
}
