//* -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*- */
/////////////////////////////////////////////////////////////////////////////////
//    Name:       src/objects/PFont.h
//    Purpose:    Contains generic specs for a font
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
#ifndef __PFONT_H__
#define __PFONT_H__


#include "PWidget.h"
#include "PColor.h"
#include "../utility/rc_ptrs.h"


/// This class represents a font in a cross-platform manner.
/// It includes face, size, style, foreground/background color, and
/// whether or not it should be anti-aliased.
/// This should be overridden by a platform-specific PlatformFont class
/// that hooks this information into specific font types and renderers.

enum PFontStyle
    {
        PFS_Normal    = 0x00,   //this is a dummy
        PFS_Bold      = 0x01,
        PFS_Italic    = 0x02,
        PFS_Underline = 0x04,
    };


class PFont: virtual public PObject
{
public:

    ///Standard constructors:
    PFont();                                     
    PFont(const char * filename);
    PFont(const char* filename, int style, int size, PColor fgcolor, PColor bgcolor, bool aa);
    PFont(const PFont & font);              ///Copy constructor
    virtual ~PFont();                       ///Standard Destructors
    
    ///Set methods for all of the data in font
    virtual void SetFontFileName(const char* name)       {mFontFileName = strdup(name);};
    virtual void SetFontStyle(const int style)           {mFontStyle=style;};
    virtual void SetFontSize(const int size)             {mFontSize = size;};
    virtual void SetFontColor(const PColor & color)      {mFontColor = color;};  
    virtual void SetBackgroundColor(const PColor & color){mBackgroundColor = color;};
    virtual void SetAntiAliased(const bool aa)           {mAntiAliased = aa;};


    
    //Get methods for all of the data in font
    virtual char* GetFontFileName()     const {return strdup(mFontFileName);};
    virtual int GetFontStyle()          const {return mFontStyle;};
    virtual int GetFontSize()           const {return mFontSize;};
    virtual PColor GetFontColor()       const {return mFontColor;};
    virtual PColor GetBackgroundColor() const {return mBackgroundColor;};
    virtual bool GetAntiAliased()       const {return mAntiAliased;};


    //These get different styles
    virtual bool IsNormalFont() const;
    virtual bool IsBoldFont()   const;
    virtual bool IsItalicFont() const;
    virtual bool IsUnderlineFont() const;


protected:
    virtual  std::ostream & SendToStream(std::ostream& out) const;    
    
    char * mFontFileName;            // Filename of font file.
    int  mFontStyle;                 // Bold, underlined, italics, normal, etc.  These use PFontStyle constants or'ed together
    int  mFontSize;                  // Size, in 'points'

    PColor  mFontColor;              // Foreground color, using PColor, an RGBA value
    PColor  mBackgroundColor;        // Background color, using PColor, an RGBA value (use (0,0,0,0) for tranparent background
    bool mAntiAliased;               // Whether the text is anti-aliased, alpha-blended with background (slow but nice)    
};


#endif
