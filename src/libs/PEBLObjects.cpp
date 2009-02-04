//* -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*- */
/////////////////////////////////////////////////////////////////////////////////
//    Name:       src/libs/PEBLObjects.cpp
//    Purpose:    Function Library for managing PEBL Objects
//    Author:     Shane T. Mueller, Ph.D.
//    Copyright:  (c) 2003-2009 Shane T. Mueller <smueller@obereed.net>
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
#include "PEBLObjects.h"

#include "PEBLEnvironment.h"
#include "../base/Variant.h"
#include "../base/PList.h"
#include "../base/PComplexData.h"
#include "../base/PEBLObject.h"

#include "../devices/DeviceState.h"
#include "../devices/PEventLoop.h"


#include "../objects/PColor.h"
#include "../objects/PTextBox.h"
#include "../objects/PDrawObject.h"
#include "../utility/PError.h"


#include "../platforms/sdl/PlatformEnvironment.h"
#include "../platforms/sdl/PlatformWindow.h"
#include "../platforms/sdl/PlatformImageBox.h"
#include "../platforms/sdl/PlatformDrawObject.h"
#include "../platforms/sdl/PlatformLabel.h"
#include "../platforms/sdl/PlatformFont.h" 
#include "../platforms/sdl/PlatformEventQueue.h"
#include "../platforms/sdl/PlatformTextBox.h" 

#include "PEBLList.h"

#include <string>
using std::string;


/// This function instantiates the namespace-viewable
//  PEBLObjects::myEnv, creating a new Environment for displaying 
/// stimuli. It is not used directly by functions, but by
/// the program itself.
namespace PEBLObjects
{
}

//Initiate static data
extern PlatformEnvironment * myEnv;
extern PlatformEventQueue * gEventQueue = NULL;



void PEBLObjects::MakeEnvironment(PEBLVideoMode mode, PEBLVideoDepth depth,
                                  bool windowed,bool unicode)
{

    myEnv = new PlatformEnvironment(mode, depth, windowed,unicode);
    myEnv->Initialize();

    //Initialize the event queue.
    gEventQueue = new PlatformEventQueue();
}



/// This function makes a new root-level window and return 
/// a variant to access it.
Variant PEBLObjects::MakeWindow(Variant v)
{

    //If there is no argument, make the background grey.
    //If there is an argument, it should be the name of a color
    Variant color;
    if(v.IsStackSignal())
        {
            color = "grey";
        }
    else
        {
            PList * plist = v.GetComplexData()->GetList();
            
            color = plist->First();
            PError::AssertType(color, PEAT_STRING,"Argument error in [MakeWindow(<color>)]: ");            
        }


    //Create a new window, and reference it in a counted pointer.
    PlatformWindow * myWindow = new PlatformWindow;

    myWindow->SetBackgroundColor(PColor(color.GetString()));
    PEBLVideoMode mode = myEnv->GetVideoMode();
    PEBLVideoDepth depth = myEnv->GetVideoDepth();
    bool windowed = myEnv->GetWindowed();

    myWindow->Initialize(mode, depth, windowed);
    
    //Add the window to the environment
    myEnv->AddWindow(myWindow);

    counted_ptr<PEBLObjectBase> tmp2   =  counted_ptr<PEBLObjectBase> (myWindow);
    PComplexData *  pcd = new PComplexData(tmp2);
    return Variant(pcd);
}


Variant PEBLObjects::MakeImage(Variant v)
{
    //v[1] should be have a filename in it.
    PList * plist = v.GetComplexData()->GetList();
    Variant name = plist->First();
    PError::AssertType(name, PEAT_STRING, "Argument error in function [MakeImage(<filename>)]: "); 
    PlatformImageBox * myImageBox = new PlatformImageBox;
    
    myImageBox->LoadImage(name);
    
    counted_ptr<PEBLObjectBase>tmp2 = counted_ptr<PEBLObjectBase>(myImageBox);
    PComplexData *  pcd = new PComplexData(tmp2);


    return Variant(pcd);
}



Variant PEBLObjects::MakeLabel(Variant v)
{
    //v[1] should have text in it, 
    //v[2] should have a font in it.
    
    PList * plist = v.GetComplexData()->GetList();
    

    //Get the text
    PError::AssertType(plist->First(), PEAT_STRING, "Argument error in first parameter of function [MakeLabel(<text>, <font>)]: ");     
    std::string  text = (plist->First()); plist->PopFront();

    //Get the font
    Variant v2 = plist->First(); plist->PopFront();
    PError::AssertType(v2, PEAT_FONT, "Argument error in second parameter of function [MakeLabel(<text>, <font>)]: "); 

    counted_ptr<PEBLObjectBase> tmpFont = v2.GetComplexData()->GetObject();


    //Create the 'label'
    PlatformLabel * tmpLabel = new PlatformLabel(text,tmpFont);
    //Place it by default at 0,0
    tmpLabel->SetPosition(0,0);
    counted_ptr<PEBLObjectBase> myLabel = counted_ptr<PEBLObjectBase>(tmpLabel);
    
    
    //Return a variant containing the label.
    PComplexData *  pcd =     new PComplexData(myLabel);

    return Variant(pcd);
}


Variant PEBLObjects::MakeTextBox(Variant v)
{
    //v[1] should have text in it, 
    //v[2] should have a font in it.
    //v[3] should have a width in it (in pixels)
    //v[4] should have a height in it (in pixels)

    PList * plist = v.GetComplexData()->GetList();
    PError::AssertType(plist->First(), PEAT_STRING,"Argument error in first parameter of function [MakeTextBox(<text>,<font>,<width>,<height>)]: ");

    //Get the text
    string  text = (plist->First()).GetString(); plist->PopFront();

    //Get the font
    Variant v2 = plist->First(); plist->PopFront();   
    PError::AssertType(v2, PEAT_FONT, "Argument error in second parameter of function [MakeTextBox(<text>,<font>,<width>,<height>)]: ");

    counted_ptr<PEBLObjectBase> myFont = v2.GetComplexData()->GetObject();


    //Get the width
    PError::AssertType(plist->First(), PEAT_NUMBER,"Argument error in third parameter of function [MakeTextBox(<text>,<font>,<width>,<height>)]: ");
    int width = plist->First(); plist->PopFront();   

    //Get the height
    PError::AssertType(plist->First(), PEAT_NUMBER,"Argument error in fourth parameter of function [MakeTextBox(<text>,<font>,<width>,<height>)]: ");
    int height = plist->First(); plist->PopFront();   

   //Create the text box
    PlatformTextBox * tmptb = new PlatformTextBox(text, myFont,width,height);

    //Place it by default at 0,0
    tmptb->SetPosition(0,0);

    counted_ptr<PEBLObjectBase> myTextBox = counted_ptr<PEBLObjectBase>(tmptb);
    
    //Return a variant containing the label.
    PComplexData *   pcd = new PComplexData(myTextBox);

    return Variant(pcd);

}


Variant PEBLObjects::MakeColor(Variant v)
{
    //v[1] should be a color name
    //Access for rgb and rgba colors should be provided.


    PList * plist = v.GetComplexData()->GetList();

    std::string name = plist->First(); plist->PopFront();

    counted_ptr<PEBLObjectBase> myColor = counted_ptr<PEBLObjectBase>(new PColor(name));    
    PComplexData *  pcd = new PComplexData(myColor);
    return Variant(pcd);
}

Variant PEBLObjects::MakeColorRGB(Variant v)
{
    //v[1] [2] [3] should be RGB values between 0 and 255
    PList * plist = v.GetComplexData()->GetList();

    PError::AssertType(plist->First(), PEAT_INTEGER, "Argument error in first parameter of function [MakeColorRGB(<red>, <green>, <blue>)]: "); 
    int red  = plist->First(); plist->PopFront();

    PError::AssertType(plist->First(), PEAT_INTEGER, "Argument error in first parameter of function [MakeColorRGB(<red>, <green>, <blue>)]: "); 
    int green  = plist->First(); plist->PopFront();

    PError::AssertType(plist->First(), PEAT_INTEGER, "Argument error in first parameter of function [MakeColorRGB(<red>, <green>, <blue>)]: "); 
    int blue  = plist->First(); plist->PopFront();
    
    PColor * tmpColor = new PColor(red,green,blue, 255);
    counted_ptr<PEBLObjectBase> myColor = counted_ptr<PEBLObjectBase>(tmpColor);
    PComplexData *  pcd = new PComplexData(myColor);
    return     Variant(pcd);
}



Variant PEBLObjects::MakeFont(Variant v)
{
    //v[1-6] should be have font parameters in it.
    PList * plist = v.GetComplexData()->GetList();

    //First comes the filename of the font.
    PError::AssertType(plist->First(), PEAT_STRING, "Argument error in first parameter of function [MakeFont(<filename>, <style>, <size>, <fg>, <bg>, <aa>)]: "); 
    std::string name = plist->First(); plist->PopFront();

    //Next comes the style, an integerized code for normal, bold, italic, underline.
    PError::AssertType(plist->First(), PEAT_INTEGER, "Argument error in second parameter of function [MakeFont(<filename>, <style>, <size>, <fg>, <bg>, <aa>)]: "); 
    int style = plist->First(); plist->PopFront();

    //Next is the point size.
    PError::AssertType(plist->First(), PEAT_INTEGER, "Argument error in third parameter of function [MakeFont(<filename>, <style>, <size>, <fg>, <bg>, <aa>)]: "); 
    int size = plist->First(); plist->PopFront();

    //The next parameter should be a PColor--foreground color
    Variant vfg = plist->First(); plist->PopFront();


    PError::AssertType(vfg, PEAT_COLOR, "Argument error in fourth parameter of function [MakeFont(<filename>, <style>, <size>, <fg>, <bg>, <aa>)]: "); 
    PColor fgcolor = *((PColor*)(vfg.GetComplexData()->GetObject().get()));


    //The next parameter should be a PColor--background color
    Variant vbg = plist->First(); plist->PopFront();
    PError::AssertType(vbg, PEAT_COLOR, "Argument error in fifth parameter of function [MakeFont(<filename>, <style>, <size>, <fg>, <bg>, <aa>)]: "); 

    PColor bgcolor = *((PColor*)(vbg.GetComplexData()->GetObject().get()));
    //Whether the font should be rendered with anti-aliasing against background.
    PError::AssertType(plist->First(), PEAT_INTEGER, "Argument error in sixth parameter of function [MakeFont(<filename>, <style>, <size>, <fg>, <bg>, <aa>)]: "); 
    bool aa = plist->First(); plist->PopFront();

    //Make the font and wrap it up in a Variant to return it.
    PlatformFont * tmpFont = new PlatformFont(name, style, size, fgcolor, bgcolor, aa);
    counted_ptr<PEBLObjectBase> myFont = counted_ptr<PEBLObjectBase>(tmpFont);
    PComplexData *  pcd = new PComplexData(myFont);
    
    return Variant(pcd);
}



/// This function adds a widget to a parent widget. 
Variant PEBLObjects::AddObject(Variant v)
{
    //v[1] should have the child widget
    //v[2] should have the parent widget

    PList * plist = v.GetComplexData()->GetList();


    Variant v1 = plist->First(); plist->PopFront();
    PError::AssertType(v1, PEAT_WIDGET, "Argument error in first parameter of function [AddObject(<child-widget>, <parent-widget>)]: "); 


    PlatformWidget * child = dynamic_cast<PlatformWidget*>((v1.GetComplexData())->GetObject().get());

    Variant v2 = plist->First(); plist->PopFront();
    PError::AssertType(v2, PEAT_WIDGET, "Argument error in second parameter of function [AddObject(<child-widget>, <parent-widget>)]: "); 

    PlatformWidget * parent = dynamic_cast<PlatformWidget*>((v2.GetComplexData())->GetObject().get());

    parent->AddSubWidget(child);

    return Variant(true);
}



/// This removes a child widget from the parent widget.
Variant PEBLObjects::RemoveObject(Variant v)
{
    //v[1] should have the child widget
    //v[2] should have the parent widget
    PList * plist = v.GetComplexData()->GetList();
    Variant v1 = plist->First(); plist->PopFront();
    PError::AssertType(v1, PEAT_WIDGET, "Argument error in first parameter of function [RemoveObject(<child-widget>, <parent-widget>)]: "); 


    PlatformWidget * child = dynamic_cast<PlatformWidget*>(v1.GetComplexData()->GetObject().get());
    
    Variant v2 = plist->First(); plist->PopFront();
    PError::AssertType(v2, PEAT_WIDGET, "Argument error in second parameter of function [RemoveObject(<child-widgett>, <parent-widget>)]: "); 


    PlatformWidget * parent = dynamic_cast<PlatformWidget*>(v2.GetComplexData()->GetObject().get());  

    //Removing subwidgets does not destroy the Variant, so we don't need to
    // worry about a memory leak here, even though we are using raw pointers.
    parent->RemoveSubWidget(child);

    return Variant(true);
}



//This sets the  cursor location (in characters) within a textbox.
Variant PEBLObjects::SetCursorPosition(Variant v)
{
    PList * plist = v.GetComplexData()->GetList();

    PError::AssertType(plist->First(), PEAT_TEXTBOX, "Argument error in first argument of function [SetCursorPosition(<textbox>, <position>)]: "); 


    counted_ptr<PEBLObjectBase> textbox = plist->First().GetComplexData()->GetObject(); plist->PopFront();    
    
    PError::AssertType(plist->First(), PEAT_NUMBER, "Argument error in second argument of function [SetCursorPosition(<textbox>, <position>)]: "); 
    Variant v1 = plist->First(); plist->PopFront();

    (dynamic_cast<PTextBox *>(textbox.get()))->SetCursorPosition(v1.GetInteger());
    
    return Variant(1);
}

//This gets the cursor location (in characters) within a textbox.
Variant PEBLObjects::GetCursorPosition(Variant v)
{
    PList * plist = v.GetComplexData()->GetList();

    PError::AssertType(plist->First(), PEAT_TEXTBOX, "Argument error in function [GetCursorPosition(<textbox>)]: "); 

    counted_ptr<PEBLObjectBase> textbox = plist->First().GetComplexData()->GetObject(); plist->PopFront();
    return Variant((dynamic_cast<PTextBox *>(textbox.get()))->GetCursorPosition());
}

Variant PEBLObjects::SetEditable(Variant v)
{
    PList * plist = v.GetComplexData()->GetList();

    PError::AssertType(plist->First(), PEAT_TEXTBOX, "Argument error in first argument of function [SetEditable(<textbox>, <boolean>)]: "); 
    
    PlatformTextBox * textbox = dynamic_cast<PlatformTextBox*>(plist->First().GetComplexData()->GetObject().get()); plist->PopFront();
    
    Variant v1 = plist->First(); plist->PopFront();

    if(bool(v1))
        {
            textbox->SetEditable(true);
            return Variant(true);
        }
    else
        {
            textbox->SetEditable(false);
            return Variant(false);
        }

}



Variant PEBLObjects::SetText(Variant v)
{

    PList * plist = v.GetComplexData()->GetList();

    
    //This can be used on either a textbox or a label.
    Variant v1 = plist->First(); plist->PopFront();
    PError::AssertType(v1, PEAT_TEXTOBJECT, "Argument error in first argument of function [SetText(<object>, <text>)]: "); 
    //Get the text to change it to.
    Variant v2 = plist->First(); plist->PopFront();
    PError::AssertType(v2, PEAT_STRING, "Argument error in second argument of function [SetText(<object>, <text>)]: "); 


    //Make the change.  
    if(v1.GetComplexData()->IsLabel() )
        {
            PlatformLabel * label = dynamic_cast<PlatformLabel*>(v1.GetComplexData()->GetObject().get());
            label->SetText(v2.GetString());            
        }
    else
        {
            PlatformTextBox * textbox = dynamic_cast<PlatformTextBox*>(v1.GetComplexData()->GetObject().get());
            textbox->SetText(v2.GetString());            
        
        }
 
    return Variant(1);
}


Variant PEBLObjects::GetText(Variant v)
{
    PList * plist = v.GetComplexData()->GetList();

    PError::AssertType(plist->First(), PEAT_TEXTBOX, "Argument error in function [GetText(<textbox>)]: "); 

    PlatformTextBox * textbox = dynamic_cast<PlatformTextBox*>(plist->First().GetComplexData()->GetObject().get());
    plist->PopFront();    
    
    return Variant(textbox->GetText());
}

Variant PEBLObjects::SetFont(Variant v)
{

    PList * plist = v.GetComplexData()->GetList();
    
    //This can be used on either a textbox or a label.
    Variant v1 = plist->First(); plist->PopFront();
    PError::AssertType(v1, PEAT_TEXTOBJECT, "Argument error in first argument of function [SetFont(<object>, <font>)]: "); 
    //Get the text to change it to.
    Variant v2 = plist->First(); plist->PopFront();
    PError::AssertType(v2, PEAT_FONT, "Argument error in second argument of function [SetFont(<object>, <font>)]: "); 


    //Make the change.  
    if(v1.GetComplexData()->IsLabel() )
        {
            PlatformLabel * label = dynamic_cast<PlatformLabel*>(v1.GetComplexData()->GetObject().get());
            
            counted_ptr<PEBLObjectBase>tmpFont = v2.GetComplexData()->GetObject();
            label->SetFont(tmpFont);
        }
    else
        {
            PlatformTextBox * textbox =dynamic_cast<PlatformTextBox*>(v1.GetComplexData()->GetObject().get());
            counted_ptr<PEBLObjectBase> tmpFont = v2.GetComplexData()->GetObject();
            textbox->SetFont(tmpFont);
        }
 
    return Variant(1);
}

Variant PEBLObjects::PrintProperties(Variant v)
{
    //v[1] should have the  widget
    PList * plist = v.GetComplexData()->GetList();
    Variant v1 = plist->First(); plist->PopFront();
    PError::AssertType(v1, PEAT_WIDGET, "Argument error in function [PrintProperties(<widget>)]: "); 

    PlatformWidget * widget = dynamic_cast<PlatformWidget*>(v1.GetComplexData()->GetObject().get());
    
    widget->PrintProperties(std::cout);

    return Variant(true);
}
Variant PEBLObjects::Show(Variant v)
{

    //v[1] should have the  widget
    PList * plist = v.GetComplexData()->GetList();


    Variant v1 = plist->First(); plist->PopFront();
    PError::AssertType(v1, PEAT_WIDGET, "Argument error in function [Show(<widget>)]: "); 


    PlatformWidget * widget = dynamic_cast<PlatformWidget*>(v1.GetComplexData()->GetObject().get());
    
    widget->Show();

    return Variant(true);
}



Variant PEBLObjects::Hide(Variant v)
{
 
    //v[1] should have the  widget
    PList * plist = v.GetComplexData()->GetList();


    Variant v1 = plist->First(); plist->PopFront();

    PlatformWidget * widget = dynamic_cast<PlatformWidget*>(v1.GetComplexData()->GetObject().get());
    
    widget->Hide();

    return Variant(true);
}






/// The Draw() function should only really be callable on the environment,
/// or it maybe shouldn't need an argument.
///
Variant PEBLObjects::Draw(Variant v)
{
    //v[1] should have the object.  If it is null, 
    //redraw the entire environment.

    if(v.IsStackSignal())
        {
            myEnv->Draw();
        }
    else
        {
        
            PList * plist = v.GetComplexData()->GetList();
            
            Variant v2 = plist->First(); plist->PopFront();
            PError::AssertType(v2, PEAT_WIDGET, "Argument error in function [Draw(<widget>)]: "); 



            PlatformWidget * myWidget = dynamic_cast<PlatformWidget*>(v2.GetComplexData()->GetObject().get());
            myWidget->Draw();
        }
    return Variant(true);
}


///This calls the Draw() routine a number of times equal to the 
///the parameter.  It returns a value that should approximate the 
///presentation time fairly well.  It should be given a window.
Variant PEBLObjects::DrawFor(Variant v)
{
    PList * plist = v.GetComplexData()->GetList();

    Variant v1 = plist->First(); plist->PopFront();
    PError::AssertType(v1, PEAT_WIDGET, "Argument error in first parameter of function [DrawFor(<widget>, <count>)]: "); 

    PlatformWindow * window = dynamic_cast<PlatformWindow*>(v1.GetComplexData()->GetObject().get());
    PError::AssertType(plist->First(), PEAT_INTEGER, "Argument error in second parameter of function [DrawFor(<widget>, <count>)]: "); 

    unsigned int count =static_cast<long unsigned int>(( plist->First()));
        
    return Variant(window->DrawFor(count));

}


/// This function moves a widget to a new location.
/// It moves the CENTER of the object to the specified location, which
/// is probably the most common thing we want to do..  To 
/// move some other part, use the GetSize(object) function.
Variant PEBLObjects::Move(Variant v)
{
   //v[1] should have the object, v[2] should be X, v[3] shoud be Y
    PList * plist = v.GetComplexData()->GetList();

    Variant v1 = plist->First(); plist->PopFront();
    PError::AssertType(v1, PEAT_WIDGET, "Argument error in first parameter of function [Move(<widget>,<x>, <y>)]: "); 

    PError::AssertType(plist->First(), PEAT_NUMBER, "Argument error in second parameter of function [Move(<widget>,<x>, <y>)]: "); 
    int x = plist->First(); plist->PopFront();
    PError::AssertType(plist->First(), PEAT_NUMBER, "Argument error in third parameter of function [Move(<widget>,<x>, <y>)]: "); 
    int y = plist->First(); plist->PopFront();



    PWidget * widget = dynamic_cast<PWidget*>(v1.GetComplexData()->GetObject().get());

    widget->SetPosition(x , y);  
    
    return Variant(true);
}


Variant PEBLObjects::GetSize(Variant v)
{


    //v[1] should have the object
    PList * plist = v.GetComplexData()->GetList();

    Variant v1 = plist->First(); plist->PopFront();
    PError::AssertType(v1, PEAT_WIDGET, "Argument error in GetSize(<widget>). ");


    PWidget * widget = dynamic_cast<PWidget*>(v1.GetComplexData()->GetObject().get());
    
    Variant width = widget->GetWidth();
    Variant height = widget->GetHeight();

    PList * newlist = new PList();

    newlist->PushFront(height);
    newlist->PushBack(width);
    
    counted_ptr<PEBLObjectBase> newlist2 = counted_ptr<PEBLObjectBase>(newlist);
    PComplexData *   pcd = new PComplexData(newlist2); 
    return Variant(pcd);
}



///This function loads a sound from a file. It also 'initializes' it
///when appropriate, so that it may be used by the play functions.
Variant PEBLObjects::LoadSound(Variant v)
{
   //v[1] should have the filename
    PList * plist = v.GetComplexData()->GetList();

    Variant v1 = plist->First(); plist->PopFront();
    PError::AssertType(v1, PEAT_STRING, "Argument error in function [LoadSound(<filename>)]: "); 
    
    PlatformAudioOut * myAudio = new PlatformAudioOut();
    myAudio->LoadSoundFile(v1);
    myAudio->Initialize();
    
    counted_ptr<PEBLObjectBase> audio2 = counted_ptr<PEBLObjectBase>(myAudio);
    PComplexData *  pcd = new PComplexData(audio2);
    return Variant(pcd);        
}



//This plays a sound object, returning (almost) immediately, allowing
//the sound to play in the background.  If you want the function to only return 
//after the sound playing is complete, use PlayForeground();  
Variant PEBLObjects::PlayBackground(Variant v)
{
   //v[1] should have the PlatformAudioOut object
    PList * plist = v.GetComplexData()->GetList();

    Variant v1 = plist->First(); plist->PopFront();      
    PError::AssertType(v1, PEAT_AUDIOOUT, "Argument error in function PlayBackground(<audio-stream>)]: "); 

    PlatformAudioOut * myAudio = dynamic_cast<PlatformAudioOut*>(v1.GetComplexData()->GetObject().get());
    myAudio->Play();
    return Variant(true);        
}

Variant PEBLObjects::PlayForeground(Variant v)
{
   //v[1] should have the PlatformAudioOut object
    PList * plist = v.GetComplexData()->GetList();


    Variant v1 = plist->First(); plist->PopFront();      

    PError::AssertType(v1, PEAT_AUDIOOUT, "Argument error in function PlayForeground(<audio-stream>)]: "); 
    PlatformAudioOut * myAudio = dynamic_cast<PlatformAudioOut*>(v1.GetComplexData()->GetObject().get());
    myAudio->PlayForeground();
    return Variant(true);        
}


Variant PEBLObjects::Stop(Variant v)
{
    //v[1] should have the PlatformAudioOut object.
     PList * plist = v.GetComplexData()->GetList();

    Variant v1 = plist->First(); plist->PopFront();      

    PError::AssertType(v1, PEAT_AUDIOOUT, "Argument error in function Stop(<audio-stream>)]: ");  

    PlatformAudioOut * myAudio = dynamic_cast<PlatformAudioOut*>(v1.GetComplexData()->GetObject().get());

    myAudio->Stop();
    return Variant(true);
}

//Not implemented:
Variant PEBLObjects::MakeSineWave(Variant v)
{

    PError::SignalFatalError("Function [MakeSineWave] Not implemented.");
    return Variant(false);
}

Variant PEBLObjects::MakeSquareWave(Variant v)
{
    PError::SignalFatalError("Function [MakeSquareWave] Not implemented.");

    return Variant(false);
}


Variant PEBLObjects::MakeSawtoothWave(Variant v)
{
    PError::SignalFatalError("Function [MakeSawtoothWave] Not implemented.");
    return Variant(false);
}

Variant PEBLObjects::MakeChirp(Variant v)
{
    PError::SignalFatalError("Function [MakeChirp] Not implemented.");
    return Variant(false);
}



Variant PEBLObjects::Line(Variant v)
{
    // v[1] should be X, v[2] should be Y
    // v[3] should be dx, v[4] should be dy
    // v[5] should be the color.
    PList * plist = v.GetComplexData()->GetList();

    PError::AssertType(plist->First(), PEAT_NUMBER, "Argument error in first parameter of function [Line(<x>, <y>, <dx>, <dy>, <color>)]: "); 
    int x = plist->First(); plist->PopFront();

    PError::AssertType(plist->First(), PEAT_NUMBER, "Argument error in second parameter of function  [Line(<x>, <y>, <dx>, <dy>, <color>)]: "); 
    int y = plist->First(); plist->PopFront();

    PError::AssertType(plist->First(), PEAT_NUMBER, "Argument error in third parameter of function  [Line(<x>, <y>, <dx>, <dy>, <color>)]: "); 
    int dx = plist->First(); plist->PopFront();

    PError::AssertType(plist->First(), PEAT_NUMBER, "Argument error in fourth parameter of function  [Line(<x>, <y>, <dx>, <dy>, <color>)]: "); 
    int dy = plist->First(); plist->PopFront();

    PError::AssertType(plist->First(), PEAT_COLOR, "Argument error in fifth parameter of function  [Line(<x>, <y>, <dx>, <dy>, <color>)]: "); 
    Variant color = plist->First(); plist->PopFront();

    counted_ptr<PEBLObjectBase> myLine = counted_ptr<PEBLObjectBase>(new PlatformLine(x,y,dx,dy,color));
    PComplexData *  pcd = new PComplexData(myLine);
    return Variant(pcd);

}



Variant PEBLObjects::Rectangle(Variant v)
{

    //
    // v[1] should be X, v[2] shoud be Y
    // v[3] should be dx, v[4] should be dy
    // v[5] should be the color, v[6] should be whether it is filled.
    PList * plist = v.GetComplexData()->GetList();

    PError::AssertType(plist->First(), PEAT_NUMBER, "Argument error in first parameter of function [Rectangle(<x>, <y>, <dx>, <dy>, <color>, <filled>)]: "); 
    int x = plist->First(); plist->PopFront();

    PError::AssertType(plist->First(), PEAT_NUMBER, "Argument error in second parameter of function  [Rectangle(<x>, <y>, <dx>, <dy>, <color>, <filled>)]: "); 
    int y = plist->First(); plist->PopFront();

    PError::AssertType(plist->First(), PEAT_NUMBER, "Argument error in third parameter of function  [Rectangle(<x>, <y>, <dx>, <dy>, <color>, <filled>)]: "); 
    int dx = plist->First(); plist->PopFront();

    PError::AssertType(plist->First(), PEAT_NUMBER, "Argument error in fourth parameter of function  [Rectangle(<x>, <y>, <dx>, <dy>, <color>, <filled>)]: "); 
    int dy = plist->First(); plist->PopFront();

    PError::AssertType(plist->First(), PEAT_COLOR, "Argument error in fifth parameter of function  [Rectangle(<x>, <y>, <dx>, <dy>, <color>, <filled>)]: "); 
    Variant color = plist->First(); plist->PopFront();

    PError::AssertType(plist->First(), PEAT_NUMBER, "Argument error in sixth parameter of function  [Rectangle(<x>, <y>, <dx>, <dy>, <color>, <filled>)]: "); 
    int filled = plist->First(); plist->PopFront();

    counted_ptr<PEBLObjectBase> myRect = counted_ptr<PEBLObjectBase>(new PlatformRectangle(x,y,dx,dy,color,filled));
    PComplexData *  pcd = new PComplexData(myRect);
    return Variant(pcd);

}





Variant PEBLObjects::Square(Variant v)
{
    // v[1] should be X, v[2] shoud be Y
    // v[3] should be dx, v[4] should be dy
    // v[5] should be the color, v[6] should be whether it is filled.
    PList * plist = v.GetComplexData()->GetList();

    PError::AssertType(plist->First(), PEAT_NUMBER, "Argument error in first parameter of function [Square(<x>, <y>, <size>, <color>, <filled>)]: "); 
    int x = plist->First(); plist->PopFront();

    PError::AssertType(plist->First(), PEAT_NUMBER, "Argument error in second parameter of function  [Square(<x>, <y>, <size>, <color>, <filled>)]: "); 
    int y = plist->First(); plist->PopFront();

    PError::AssertType(plist->First(), PEAT_NUMBER, "Argument error in third parameter of function  [Square(<x>, <y>, <size>, <color>, <filled>)]: "); 
    int size = plist->First(); plist->PopFront();

    PError::AssertType(plist->First(), PEAT_COLOR, "Argument error in fourth parameter of function  [Square(<x>, <y>, <size>, <color>, <filled>)]: "); 

    Variant color = plist->First(); plist->PopFront();

    PError::AssertType(plist->First(), PEAT_NUMBER, "Argument error in fifth parameter of function  [Square(<x>, <y>, <size>, <color>, <filled>)]: "); 
    int filled = plist->First(); plist->PopFront();

    counted_ptr<PEBLObjectBase> mySquare = counted_ptr<PEBLObjectBase>(new PlatformSquare(x,y,size,color,filled));
    PComplexData *  pcd = new PComplexData(mySquare);
    return Variant(pcd);

}


Variant PEBLObjects::Ellipse(Variant v)
{

    // v[1] should be X, v[2] shoud be Y
    // v[3] should be dx, v[4] should be dy
    // v[5] should be the color.
    PList * plist = v.GetComplexData()->GetList();

    PError::AssertType(plist->First(), PEAT_NUMBER, "Argument error in first parameter of function [Ellipse(<x>, <y>, <rx>, <ry>, <color>, <filled>)]: "); 
    int x = plist->First(); plist->PopFront();

    PError::AssertType(plist->First(), PEAT_NUMBER, "Argument error in second parameter of function  [Ellipse(<x>, <y>, <rx>, <ry>, <color>, <filled>)]: "); 
    int y = plist->First(); plist->PopFront();

    PError::AssertType(plist->First(), PEAT_NUMBER, "Argument error in third parameter of function  [Ellipse(<x>, <y>, <rx>, <ry>, <color>, <filled>)]: "); 
    int rx = plist->First(); plist->PopFront();

    PError::AssertType(plist->First(), PEAT_NUMBER, "Argument error in fourth parameter of function  [Ellipse(<x>, <y>, <rx>, <ry>, <color>, <filled>)]: "); 
    int ry = plist->First(); plist->PopFront();

    PError::AssertType(plist->First(), PEAT_COLOR, "Argument error in fifth parameter of function  [Ellipse(<x>, <y>, <rx>, <ry>, <color>, <filled>)]: "); 
    Variant color = plist->First(); plist->PopFront();

    PError::AssertType(plist->First(), PEAT_NUMBER, "Argument error in sixth parameter of function  [Ellipse(<x>, <y>, <rx>, <ry>, <color>, <filled>)]: "); 
    int filled = plist->First(); plist->PopFront();


    counted_ptr<PEBLObjectBase> myEllipse = counted_ptr<PEBLObjectBase>(new PlatformEllipse(x,y,rx,ry,color,filled));
    PComplexData *  pcd = new PComplexData(myEllipse);
    return Variant(pcd);

}




Variant PEBLObjects::Circle(Variant v)
{

    // v[1] should be X, v[2] shoud be Y
    // v[3] should be dx, v[4] should be dy
    // v[5] should be the color.
    PList * plist = v.GetComplexData()->GetList();

    PError::AssertType(plist->First(), PEAT_NUMBER, "Argument error in first parameter of function [Circle(<x>, <y>, <rx>,  <color>)]: "); 
    int x = plist->First(); plist->PopFront();

    PError::AssertType(plist->First(), PEAT_NUMBER, "Argument error in second parameter of function  [Circle(<x>, <y>, <rx>, <color>)]: "); 
    int y = plist->First(); plist->PopFront();

    PError::AssertType(plist->First(), PEAT_NUMBER, "Argument error in third parameter of function  [Circle(<x>, <y>, <r>,, <color>)]: "); 
    int r = plist->First(); plist->PopFront();


    PError::AssertType(plist->First(), PEAT_COLOR, "Argument error in fourth parameter of function  [Circle(<x>, <y>, <rx>, <color>)]: "); 
    Variant color = plist->First(); plist->PopFront();
    
    PError::AssertType(plist->First(), PEAT_NUMBER, "Argument error in fifth parameter of function  [Circle(<x>, <y>, <rx>, <ry>, <color>, <filled>)]: "); 
    int filled = plist->First(); plist->PopFront();


    counted_ptr<PEBLObjectBase> myCircle = counted_ptr<PEBLObjectBase>(new PlatformCircle(x,y,r,color,filled));
    PComplexData *  pcd = new PComplexData(myCircle);

    return Variant(pcd);
}


Variant PEBLObjects::Polygon(Variant v)
{

    // v[1] should be X, v[2] shoud be Y
    // v[3] list-of-x-points
    // v[4] list-of-y-points
    // v[5] should be should be color
    // v[6] should be whether filled
    PList * plist = v.GetComplexData()->GetList();

    PError::AssertType(plist->First(), PEAT_NUMBER, "Argument error in first parameter of function [Polygon(<x>, <y>, <xpoints>, <ypoints>, <color>, <filled>)]: "); 
    int x = plist->First(); plist->PopFront();

    PError::AssertType(plist->First(), PEAT_NUMBER, "Argument error in second parameter of function  [Polygon(<x>, <y>,<xpoints>, <ypoints>, <color>, <filled>)]: "); 
    int y = plist->First(); plist->PopFront();

    PError::AssertType(plist->First(), PEAT_LIST, "Argument error in third parameter of function  [Polygon(<x>, <y>, <xpoints>, <ypoints>, <color>, <filled>)]: "); 
    Variant xpoints = plist->First(); plist->PopFront();

    PError::AssertType(plist->First(), PEAT_LIST, "Argument error in fourth parameter of function  [Polygon(<x>, <y>, <xpoints>, <ypoints>, <color>, <filled>)]: "); 
    Variant ypoints = plist->First(); plist->PopFront();

    PError::AssertType(plist->First(), PEAT_COLOR, "Argument error in fifth parameter of function  [Polygon(<x>, <y>, <xpoints>, <ypoints>, <color>, <filled>)]: "); 
    Variant color = plist->First(); plist->PopFront();    
    PError::AssertType(plist->First(), PEAT_NUMBER, "Argument error in sixth parameter of function  [Polygon(<x>, <y>, <xpoints>, <ypoints>, <color>, <filled>)]: "); 
    int filled = plist->First(); plist->PopFront();

    counted_ptr<PEBLObjectBase> myPolygon = counted_ptr<PEBLObjectBase>(new PlatformPolygon(x,y,xpoints,ypoints,color,filled));
    PComplexData *  pcd = new PComplexData(myPolygon);

    return Variant(pcd);
}




Variant PEBLObjects::Bezier(Variant v)
{

    // v[1] should be X, v[2] shoud be Y
    // v[3] should be dx, v[4] should be dy
    // v[5] should be the color.
    PList * plist = v.GetComplexData()->GetList();

    PError::AssertType(plist->First(), PEAT_NUMBER, "Argument error in first parameter of function [Bezier(<x>, <y>, <xpoints>, <ypoints>, <steps>, <color>)]: "); 
    int x = plist->First(); plist->PopFront();

    PError::AssertType(plist->First(), PEAT_NUMBER, "Argument error in second parameter of function  [Bezier(<x>, <y>,<xpoints>, <ypoints>, <steps>, <color>)]: "); 
    int y = plist->First(); plist->PopFront();

    PError::AssertType(plist->First(), PEAT_LIST, "Argument error in third parameter of function  [Bezier(<x>, <y>, <xpoints>, <ypoints>, <steps>, <color>)]: "); 
    Variant xpoints = plist->First(); plist->PopFront();

    PError::AssertType(plist->First(), PEAT_LIST, "Argument error in fourth parameter of function  [Bezier(<x>, <y>, <xpoints>, <ypoints>, <steps>, <color>)]: "); 
    Variant ypoints = plist->First(); plist->PopFront();

    PError::AssertType(plist->First(), PEAT_NUMBER, "Argument error in fifth parameter of function  [Bezier(<x>, <y>, <xpoints>, <ypoints>, <steps>, <color>)]: "); 
    int steps = plist->First(); plist->PopFront();

    PError::AssertType(plist->First(), PEAT_COLOR, "Argument error in sixth parameter of function  [Bezier(<x>, <y>, <xpoints>, <ypoints>, <steps>, <color>)]: "); 
    Variant color = plist->First(); plist->PopFront();
    

    counted_ptr<PEBLObjectBase> myBezier = counted_ptr<PEBLObjectBase>(new PlatformBezier(x,y,xpoints,ypoints,steps,color));
    PComplexData *  pcd = new PComplexData(myBezier);

    return Variant(pcd);
}





Variant PEBLObjects::RotoZoom(Variant v)
{

    // v[1] should be an object,
    // v[2] shoud be rotation
    // v[3] should be xzoom, v[4] should be yzoom
    // v[5] should be whether to anti-alias.

    PList * plist = v.GetComplexData()->GetList();

    PError::AssertType(plist->First(), PEAT_WIDGET, "Argument error in first parameter of function [ROTOZOOM(<widget>,<rotation>,<xzoom>, <yzoom>, <smooth>)]: "); 
    Variant v1 = plist->First(); plist->PopFront();
    PlatformWidget * widget = dynamic_cast<PlatformWidget*>(v1.GetComplexData()->GetObject().get());



    PError::AssertType(plist->First(), PEAT_NUMBER, "Argument error in second parameter of function [ROTOZOOM(<widget>,<rotation>,<xzoom>, <yzoom>, <smooth>)]: "); 
    Variant r = plist->First(); plist->PopFront();

    PError::AssertType(plist->First(), PEAT_NUMBER, "Argument error in third parameter of function [ROTOZOOM(<widget>,<rotation>,<xzoom>, <yzoom>, <smooth>)]: "); 
    Variant x = plist->First(); plist->PopFront();


    PError::AssertType(plist->First(), PEAT_NUMBER, "Argument error in fourth parameter of function [ROTOZOOM(<widget>,<rotation>,<xzoom>, <yzoom>, <smooth>)]: "); 
    Variant y = plist->First(); plist->PopFront();
    
    PError::AssertType(plist->First(), PEAT_NUMBER, "Argument error in fifth parameter of function [ROTOZOOM(<widget>,<rotation>,<xzoom>, <yzoom>, <smooth>)]: "); 
    int smooth = plist->First(); plist->PopFront();

    bool result = widget->RotoZoom((long double)r,(long double)x,(long double)y,smooth);

    //if(!result)PError::SignalFatalError("Rotozoom failed.");
    
    return v1.GetComplexData();
}
