//* -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*- */
/////////////////////////////////////////////////////////////////////////////////
//    Name:       src/base/PComplexData.h
//    Purpose:    Contains base class for complex data, held by the Variant Class
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
#include "PComplexData.h"

#include <iostream.h>

#include "../utility/PError.h"
#include "../utility/rc_ptrs.h"


using std::ostream;
using std::cerr;
using std::endl;

///
/// This class is the base class that all complex data types 
/// inherit from. A pointer to a PComplexData can be stored in
/// A Variant. 

PComplexData::PComplexData():
    mComplexDataType(CDT_UNDEFINED)
{

}


PComplexData::PComplexData(counted_ptr<PList> list):
    mComplexDataType(CDT_LIST),
    mList(list)
{

}

PComplexData::PComplexData(counted_ptr<PlatformEnvironment> env):
    mComplexDataType(CDT_ENVIRONMENT),
    mEnvironment(env)
{

}


PComplexData::PComplexData(counted_ptr<PlatformWindow> window):
    mComplexDataType(CDT_WINDOW),
    mWindow(window)
{

}

PComplexData::PComplexData(counted_ptr<PColor> color):
    mComplexDataType(CDT_COLOR),
    mColor( color)
{


}

PComplexData::PComplexData(counted_ptr<PlatformFont>  font):
    mComplexDataType(CDT_FONT),
    mFont(font)
{

}

PComplexData::PComplexData(counted_ptr<PlatformLabel> label):
    mComplexDataType(CDT_LABEL),
    mLabel(label)
{

}


PComplexData::PComplexData(counted_ptr<PlatformTextBox> textbox):
    mComplexDataType(CDT_TEXTBOX),
    mTextBox(textbox)
{

}


PComplexData::PComplexData(counted_ptr<PlatformImageBox> imagebox):
    mComplexDataType(CDT_IMAGEBOX),
    mImageBox(imagebox)
{

}

PComplexData::PComplexData(counted_ptr<PlatformKeyboard> keyboard):
    mComplexDataType(CDT_KEYBOARD),
    mKeyboard(keyboard)
{

}


PComplexData::PComplexData(counted_ptr<PStream> stream):
    mComplexDataType(CDT_FILESTREAM),
    mFileStream(stream)
{

}


PComplexData::PComplexData(counted_ptr<PlatformAudioOut> audio):
    mComplexDataType(CDT_AUDIOOUT),
    mAudioOut(audio)
{

}




PComplexData::~PComplexData()
{

}
  

///This is a generic copy constructor
PComplexData::PComplexData(const PComplexData & pcd):
    mComplexDataType(pcd.GetType())
{

    switch(mComplexDataType)
        {
        case CDT_LIST:
            mList = pcd.GetList();
            break;
        case CDT_ENVIRONMENT:
            mEnvironment = pcd.GetEnvironment();
            break;
        case CDT_WINDOW:      
            mWindow = pcd.GetWindow();
            break;
        case CDT_COLOR:       
            mColor = pcd.GetColor();
            break;
        case CDT_FONT:        
            mFont = pcd.GetFont();
            break;
        case CDT_LABEL:       
            mLabel = pcd.GetLabel();
            break; 
  
        case CDT_TEXTBOX:
            mTextBox = pcd.GetTextBox();
            break;
            
        case CDT_IMAGEBOX:    
            mImageBox = pcd.GetImageBox();
            break;
        case CDT_KEYBOARD:    
            mKeyboard = pcd.GetKeyboard();
            break;
        case CDT_FILESTREAM:
            mFileStream = pcd.GetFileStream();
            break;
        case CDT_AUDIOOUT:
            mAudioOut = pcd.GetAudioOut();
            break;

        case CDT_UNDEFINED:
        default:             
            PError::SignalFatalError("Trying to copy undefined PComplexData.");
        }

}



///sorta-copy Constructor
PComplexData::PComplexData(const PComplexData * pcd):
    mComplexDataType( pcd->GetType())
{

    switch(mComplexDataType)
        {
        case CDT_LIST:
            mList = pcd->GetList();
            break;
        case CDT_ENVIRONMENT:
            mEnvironment = pcd->GetEnvironment();
            break;
        case CDT_WINDOW:      
            mWindow = pcd->GetWindow();
            break;
        case CDT_COLOR:       
            mColor = pcd->GetColor();
            break;
        case CDT_FONT:
            mFont = pcd->GetFont();
            break;
        case CDT_LABEL:       
            mLabel = pcd->GetLabel();
            break; 

        case CDT_TEXTBOX:       
            mTextBox = pcd->GetTextBox();
            break; 

        case CDT_IMAGEBOX:    
            mImageBox = pcd->GetImageBox();
            break;
        case CDT_KEYBOARD:    
            mKeyboard = pcd->GetKeyboard();
            break;
        case CDT_FILESTREAM:
            mFileStream = pcd->GetFileStream();
            break;

        case CDT_AUDIOOUT:
            mAudioOut = pcd->GetAudioOut();
            break;

        case CDT_UNDEFINED:
        default:             
            PError::SignalFatalError("Trying to copy undefined PComplexData.");
            break;
        }

}



//Overload of the << operator
ostream & operator <<(ostream & out, const PComplexData & pcd )
{
    
    pcd.SendToStream(out);
    return out;
}
 

//This prints out stuff to a stream.
ostream & PComplexData::SendToStream(ostream& out) const
{

    switch(mComplexDataType)
        {
        case CDT_LIST:         out << *mList; break;
        case CDT_ENVIRONMENT:  out << *mEnvironment; break;
        case CDT_WINDOW:       out << *mWindow;  break;
        case CDT_COLOR:        out << *mColor; break;
        case CDT_FONT:         out << *mFont;  break;
        case CDT_LABEL:        out << *mLabel;  break;
        case CDT_TEXTBOX:      out << *mTextBox;  break;
        case CDT_IMAGEBOX:     out << *mImageBox; break;
        case CDT_KEYBOARD:     out << *mKeyboard; break;
        case CDT_FILESTREAM:   out << *mFileStream; break;
        case CDT_AUDIOOUT:     out << *mAudioOut; break;
        case CDT_UNDEFINED:
        default:               out << "Undefined" << GetTypeName();
            break;
        }
    
    return out;
}


ComplexDataType PComplexData::GetType() const
{
    return mComplexDataType;
}



const char *  PComplexData::GetTypeName() const
{
    switch(mComplexDataType)
        {
        case CDT_LIST:
            return "Complex Data: List";

        case CDT_ENVIRONMENT:
            return "Complex Data: Environment";

        case CDT_WINDOW:
            return "Complex Data: Window";

        case CDT_COLOR:
            return "Complex Data: Color";

        case CDT_FONT:
            return "Complex Data: Font";

        case CDT_LABEL:
            return "Complex Data: Label";

        case CDT_TEXTBOX:
            return "Complex Data: TextBox";

        case CDT_IMAGEBOX:
            return "Complex Data: ImageBox";

        case CDT_KEYBOARD:
            return "Complex Data: Keyboard";

        case CDT_FILESTREAM:
            return "Complex Data: FileStream";
            
        case CDT_AUDIOOUT:
            return "Complex Data: Audio Out";
        case CDT_UNDEFINED:
        default:
            return "Complex Data: Undefined";

        }

}
 


counted_ptr<PList> PComplexData::GetList() const
{

    if(IsList())
        {
            return mList;
        }
    else
        {
            PError::SignalFatalError("Trying to get a list but got another data type.");
            exit(1);
        }

}


counted_ptr<PlatformEnvironment> PComplexData::GetEnvironment() const
{

    if(IsEnvironment())
        {
            return mEnvironment;
        }
    else
        {
            PError::SignalFatalError("Trying to get an Environment.");
            exit(1);
        }

}

counted_ptr<PlatformWindow> PComplexData::GetWindow() const
{


    if(IsWindow())
        {
            return mWindow;
        }
    else
        {
            PError::SignalFatalError("Trying to get a Window.");
            exit(1);
        }

}

counted_ptr<PColor> PComplexData::GetColor() const
{

    if(IsColor())
        {
            return mColor;
        }
    else
        {
            PError::SignalFatalError("Trying to get a Color.");
            exit(1);
        }


}

counted_ptr<PlatformFont> PComplexData::GetFont() const
{

    if(IsFont())
        {
            return mFont;
        }
    else
        {
            PError::SignalFatalError("Trying to get a Font.");
            exit(1);

        }

}

counted_ptr<PlatformLabel> PComplexData::GetLabel() const
{

    if(IsLabel())
        {
            return mLabel;
        }
    else
        {
            PError::SignalFatalError("Trying to get a Label.");
            exit(1);
        }
}

counted_ptr<PlatformTextBox> PComplexData::GetTextBox() const
{

    if(IsTextBox())
        {
            return mTextBox;
        }
    else
        {
            PError::SignalFatalError("Trying to get a Textbox.");
            exit(1);

        }
}

counted_ptr<PlatformImageBox> PComplexData::GetImageBox() const
{

    if(IsImageBox())
        {
            return mImageBox;
        }
    else
        {
            PError::SignalFatalError("Trying to get a Imagebox another data type.");
            exit(1);

        }
}


counted_ptr<PlatformKeyboard> PComplexData::GetKeyboard() const
{
    if(IsKeyboard())
        {
            return mKeyboard;
        }
    else
        {
            PError::SignalFatalError("Trying to get a keyboard but got another data type.");
            exit(1);
        }
}




counted_ptr<PStream> PComplexData::GetFileStream() const
{
    if(IsFileStream())
        {
            return mFileStream;
        }
    else
        {
            PError::SignalFatalError("Trying to get a FileStream.");
            exit(0);
        }
}


counted_ptr<PlatformAudioOut> PComplexData::GetAudioOut() const
{

    if(IsAudioOut())
        {
            return mAudioOut;
        }
    else
        {
            PError::SignalFatalError("Trying to get a AudioOut Stream.");
            exit(0);
        }

}



//  This accessor will return a pointer to a raw pointer to a 
// 'widget' if the data is one, or NULL otherwise.
//  This is dangerous to use, as it circumvents the counted-pointer system.
// If you use it, do not destroy anything, and be aware that any new copies will
// not get added to the counted reference system.
PlatformWidget * PComplexData::GetWidget() const
{  
    switch(mComplexDataType)
        {
            
        case CDT_WINDOW:
            return mWindow.get();

        case CDT_LABEL:
            return mLabel.get();

        case CDT_TEXTBOX:
            return mTextBox.get();

        case CDT_IMAGEBOX:
            return mImageBox.get();

            //These all fall through to the NULL return, because they are not widgets..
        case CDT_COLOR:
        case CDT_FONT:
        case CDT_KEYBOARD:
        case CDT_FILESTREAM:
        case CDT_LIST:
        case CDT_ENVIRONMENT:
        case CDT_AUDIOOUT:
        case CDT_UNDEFINED:
        default:
            PError::SignalFatalError("Unable to get widget from PComplexData.");
            exit(1);

        }
}




bool PComplexData::IsList() const
{
    return mComplexDataType == CDT_LIST;
}


bool PComplexData::IsEnvironment() const
{
    return mComplexDataType == CDT_ENVIRONMENT;
}


bool PComplexData::IsWidget() const
{
    if( (mComplexDataType == CDT_WINDOW)
        || (mComplexDataType == CDT_LABEL)
        || (mComplexDataType == CDT_IMAGEBOX)
        || (mComplexDataType == CDT_TEXTBOX)
       )
        return true;
    else
        return false;
}


bool PComplexData::IsWindow() const
{
    return mComplexDataType == CDT_WINDOW;
}


bool PComplexData::IsColor() const
{
    return mComplexDataType == CDT_COLOR;
}


bool PComplexData::IsFont() const
{
    return mComplexDataType == CDT_FONT;
}

bool PComplexData::IsTextObject() const
{
    return (mComplexDataType == CDT_TEXTBOX)
        || (mComplexDataType == CDT_LABEL);
}

bool PComplexData::IsLabel() const
{
    return mComplexDataType == CDT_LABEL;
}

bool PComplexData::IsTextBox() const
{
    return mComplexDataType == CDT_TEXTBOX;
}


 
bool PComplexData::IsImageBox() const
{
    return mComplexDataType == CDT_IMAGEBOX;
}


bool PComplexData::IsKeyboard() const
{
    return mComplexDataType == CDT_KEYBOARD;
}

bool PComplexData::IsFileStream() const
{
    return mComplexDataType == CDT_FILESTREAM;
}
 
bool PComplexData::IsAudioOut() const
{
    return mComplexDataType == CDT_AUDIOOUT;
}


/// This method unpoints any non-null pointer.
///It isn't used because rc pointers handle things for themselves.
///It may be necessary to resurrect in the future if the counted_ptr<>s are
///managed a little bit differently.  If this happens, though, it may 
///be possible to fold some of this back into Variant.
void PComplexData::ClearPointers()
{


   switch(mComplexDataType)
        {
        case CDT_LIST:
         
            break;
            
        case CDT_ENVIRONMENT:
         
            break;

        case CDT_WINDOW:
         
            break;

        case CDT_COLOR:
         
            break;
            
        case CDT_FONT:
         
            break;

        case CDT_LABEL:
         
            break;

        case CDT_TEXTBOX:
         
            break;

        case CDT_IMAGEBOX:
         
            break;

        case CDT_KEYBOARD:
         
            break;

        case CDT_FILESTREAM:
         
            break;
            
        case CDT_AUDIOOUT:
         
            break;

        case CDT_UNDEFINED:
            break;

        default:
            PError::SignalFatalError("Undefined data type in PComplexData::ClearPointers()");
        }

}
