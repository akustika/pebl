//* -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*- */
/////////////////////////////////////////////////////////////////////////////////
//    Name:       src/base/PComplexData.h
//    Purpose:    Contains definition for the complex data type, held by the Variant Class
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
#ifndef __PCOMPLEXDATA_H__
#define __PCOMPLEXDATA_H__

#include "PList.h"
#include "../objects/PColor.h"

#include "../platforms/sdl/PlatformEnvironment.h"
#include "../platforms/sdl/PlatformWindow.h"
#include "../platforms/sdl/PlatformImageBox.h"
#include "../platforms/sdl/PlatformFont.h"
#include "../platforms/sdl/PlatformLabel.h"
#include "../platforms/sdl/PlatformTextBox.h"
#include "../platforms/sdl/PlatformKeyboard.h"
#include "../devices/PStream.h"
#include "../platforms/sdl/PlatformAudioOut.h"
#include "../utility/rc_ptrs.h"
#include <iostream>



/// This class contains pointers to each type of complex data.
/// Only one should be valid at a time--this is sort of a 
/// 'union' but it allows using classes, and shields the complexity
/// from Variant.
/// A pointer to a PComplexData can be stored in
/// A Variant. 

/// The decision to make these classes be contained within PComplexData, rather
/// than inheriting from it, was made to avoid too-frequent and dangerous down-casting.



///  Design Note:  This class uses the rc_ptr template class extensively to 
/// allow automatic memory management for referenced data objects.  All contained
/// data structures are stored as rc pointers, initialized to 0.  Whenever the 
/// a new copy of something is created, it is done with rc_ptrs so they automagically 
/// get cleaned up.  
/// The GetWidgets method returns raw pointers because I couldn't determine how to
/// return a casted  counted pointer.  Anyone who uses this should be wary.


enum ComplexDataType 
    {
        CDT_UNDEFINED,
        CDT_AUDIOOUT,
        CDT_COLOR,      
        CDT_ENVIRONMENT,
        CDT_FILESTREAM,
        CDT_FONT,
        CDT_IMAGEBOX,        
        CDT_KEYBOARD,        
        CDT_LIST,
        CDT_TEXTBOX,
        CDT_WINDOW,
        CDT_LABEL
    };

class PComplexData
{
public:
 

    //Constructors
    PComplexData();
    PComplexData(counted_ptr<PList>);
    PComplexData(counted_ptr<PlatformEnvironment>);
    PComplexData(counted_ptr<PlatformWindow>);
    PComplexData(counted_ptr<PColor>);
    PComplexData(counted_ptr<PlatformFont>);
    PComplexData(counted_ptr<PlatformLabel>);
    PComplexData(counted_ptr<PlatformTextBox> );
    PComplexData(counted_ptr<PlatformImageBox>);
    PComplexData(counted_ptr<PlatformKeyboard>);
    PComplexData(counted_ptr<PStream>);
    PComplexData(counted_ptr<PlatformAudioOut>);
    

    ///Copy Constructors
    PComplexData(const PComplexData &);
    PComplexData(const PComplexData * pcd);


    ///Destructor. Does not destroy the pointed-to contents.
    ~PComplexData();


    //Overload of the << operator
    friend std::ostream & operator <<(std::ostream & out, const PComplexData & pcd );




    //'Get' Methods.

    ComplexDataType GetType() const;
    std::string  GetTypeName() const;

    counted_ptr<PList>                 GetList() const;
    counted_ptr<PlatformEnvironment>   GetEnvironment() const;
    counted_ptr<PlatformWindow>        GetWindow() const;
    counted_ptr<PColor>                GetColor() const;
    counted_ptr<PlatformFont>          GetFont() const;
    counted_ptr<PlatformLabel>         GetLabel() const;
    counted_ptr<PlatformTextBox>       GetTextBox() const;
    counted_ptr<PlatformImageBox>      GetImageBox() const;
    counted_ptr<PlatformKeyboard>      GetKeyboard() const;
   

    counted_ptr<PStream>               GetFileStream() const;
    counted_ptr<PlatformAudioOut>      GetAudioOut() const;

    //This is no longer under control of the counted pointer system.
    PlatformWidget *    GetWidget() const;             //Returns pointer to a widget, whatever it is.


    //'IsX' methods
    bool IsList() const;
    bool IsEnvironment()const;
    bool IsWidget() const;
    bool IsWindow() const;
    bool IsColor() const;
    bool IsFont() const;
    bool IsTextObject() const;
    bool IsLabel() const;
    bool IsTextBox() const;
    bool IsImageBox() const;
    bool IsKeyboard() const;
    bool IsFileStream() const;
    bool IsAudioOut() const;



protected:
    //Inheritable function for use by << operator.
    std::ostream & SendToStream(std::ostream& out) const;
    
    
private:


    ///This will clear all the pointers that things are pointing to
    ///deleting the data when necessary.
    void ClearPointers();

    ComplexDataType mComplexDataType;

    //This isn't very efficient--each of these gets
    //created whenever a PCD is created (or copied), and each
    //will get destroyed as well.  
    counted_ptr<PList>                mList;
    counted_ptr<PlatformEnvironment>  mEnvironment;
    counted_ptr<PlatformWindow>       mWindow;
    counted_ptr<PColor>               mColor;
    counted_ptr<PlatformFont>         mFont;
    counted_ptr<PlatformLabel>        mLabel;
    counted_ptr<PlatformTextBox>      mTextBox;
    counted_ptr<PlatformImageBox>     mImageBox;
    counted_ptr<PlatformKeyboard>     mKeyboard;
    counted_ptr<PStream>              mFileStream; 
    counted_ptr<PlatformAudioOut>     mAudioOut;
};


#endif
