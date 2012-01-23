//* -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*- */
/////////////////////////////////////////////////////////////////////////////////
//    Name:       src/platforms/sdl/PlatformFont.cpp
//    Purpose:    Contains SDL-specific Font Classes
//    Author:     Shane T. Mueller, Ph.D.
//    Copyright:  (c) 2003-2008 Shane T. Mueller <smueller@obereed.net>
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
#include "PlatformFont.h"
#include "../../objects/PFont.h"
#include "../../objects/PColor.h"


#include "../../utility/PEBLPath.h"
#include "../../utility/PError.h"
#include "../../base/Evaluator.h"

#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"
#include <stdio.h>
#include <iostream>

using std::string;
using std::cout;
using std::endl;

// The following is adapted from code put on
// http://stackoverflow.com/questions/1031645/how-to-detect-utf-8-in-plain-c
// It has an implied public domain license

bool is_utf8(std::string str)
{
    if(str.length()==0)
        return false;

    const unsigned char * bytes = (const unsigned char *)(str.c_str());
    while(*bytes)
    {
        if(     (// ASCII
                        bytes[0] == 0x09 ||
                        bytes[0] == 0x0A ||
                        bytes[0] == 0x0D ||
                        (0x20 <= bytes[0] && bytes[0] <= 0x7E)
                )
        ) {
                bytes += 1;
                continue;
        }

        if(     (// non-overlong 2-byte
                        (0xC2 <= bytes[0] && bytes[0] <= 0xDF) &&
                        (0x80 <= bytes[1] && bytes[1] <= 0xBF)
                )
        ) {
                bytes += 2;
                continue;
        }

        if(     (// excluding overlongs
                        bytes[0] == 0xE0 &&
                        (0xA0 <= bytes[1] && bytes[1] <= 0xBF) &&
                        (0x80 <= bytes[2] && bytes[2] <= 0xBF)
                ) ||
                (// straight 3-byte
                        ((0xE1 <= bytes[0] && bytes[0] <= 0xEC) ||
                                bytes[0] == 0xEE ||
                                bytes[0] == 0xEF) &&
                        (0x80 <= bytes[1] && bytes[1] <= 0xBF) &&
                        (0x80 <= bytes[2] && bytes[2] <= 0xBF)
                ) ||
                (// excluding surrogates
                        bytes[0] == 0xED &&
                        (0x80 <= bytes[1] && bytes[1] <= 0x9F) &&
                        (0x80 <= bytes[2] && bytes[2] <= 0xBF)
                )
        ) {
                bytes += 3;
                continue;
        }

        if(     (// planes 1-3
                        bytes[0] == 0xF0 &&
                        (0x90 <= bytes[1] && bytes[1] <= 0xBF) &&
                        (0x80 <= bytes[2] && bytes[2] <= 0xBF) &&
                        (0x80 <= bytes[3] && bytes[3] <= 0xBF)
                ) ||
                (// planes 4-15
                        (0xF1 <= bytes[0] && bytes[0] <= 0xF3) &&
                        (0x80 <= bytes[1] && bytes[1] <= 0xBF) &&
                        (0x80 <= bytes[2] && bytes[2] <= 0xBF) &&
                        (0x80 <= bytes[3] && bytes[3] <= 0xBF)
                ) ||
                (// plane 16
                        bytes[0] == 0xF4 &&
                        (0x80 <= bytes[1] && bytes[1] <= 0x8F) &&
                        (0x80 <= bytes[2] && bytes[2] <= 0xBF) &&
                        (0x80 <= bytes[3] && bytes[3] <= 0xBF)
                )
        ) {
                bytes += 4;
                continue;
        }

        return false;
    }

    return true;
}



///Convenience constructor of PlatformFont:
PlatformFont::PlatformFont(const std::string & filename, int style, int size, PColor fgcolor, PColor bgcolor, bool aa):
    PFont(filename, style, size, fgcolor, bgcolor, aa)

{

    //    cout << "Path:" << Evaluator::gPath << endl;
    string fontname = Evaluator::gPath.FindFile(mFontFileName);
    if(fontname == "")
        PError::SignalFatalError(string("Unable to find font file [")  + mFontFileName + string("]."));

    //These convert above properties to sdl-specific font
    //Open the font.  Should do error checking here.
    mTTF_Font = TTF_OpenFont(fontname.c_str(), mFontSize);
    TTF_SetFontStyle(mTTF_Font, mFontStyle);

   //Translate PColor to SDLcolor for direct use in rendering.
    mSDL_FGColor = SDLUtility::PColorToSDLColor(mFontColor);
    mSDL_BGColor = SDLUtility::PColorToSDLColor(mBackgroundColor);

}



///Copy constructor of PlatformFont:
PlatformFont::PlatformFont(const PlatformFont & font)

{
    mFontFileName    = font.GetFontFileName();
    mFontStyle       = font.GetFontStyle();
    mFontSize        = font.GetFontSize();
    mFontColor       = font.GetFontColor();
    mBackgroundColor = font.GetBackgroundColor();
    mAntiAliased     = font.GetAntiAliased();


    //These convert above properties to sdl-specific font
    //Open the font.  Should do error checking here.
    mTTF_Font  = TTF_OpenFont(mFontFileName.c_str(), mFontSize);
    TTF_SetFontStyle(mTTF_Font, mFontStyle);

    //Translate PColor to SDLcolor for direct use in rendering.
    mSDL_FGColor = SDLUtility::PColorToSDLColor(mFontColor);
    mSDL_BGColor = SDLUtility::PColorToSDLColor(mBackgroundColor);

}



///Standard destructor of PlatformFont
PlatformFont::~PlatformFont()
{


    TTF_CloseFont(mTTF_Font);
    mTTF_Font = NULL;

}



///Set*Color needs to be overridden because it doesn't change the SDL_Color data.
void PlatformFont::SetFontColor(PColor color)
{
    //Chain up to parent method
    PFont::SetFontColor(color);

    //Set child member data.
    mSDL_FGColor = SDLUtility::PColorToSDLColor(mFontColor);
}



///Set*Color needs to be overridden because it doesn't change the SDL_Color data.
void PlatformFont::SetBackgroundColor(PColor color)
{
    //Chain up to parent method
    PFont::SetBackgroundColor(color);

    //Set child member data.
    mSDL_BGColor = SDLUtility::PColorToSDLColor(mBackgroundColor);
}



SDL_Surface * PlatformFont::RenderText(const std::string & text)
{

    #if 0
    cout << "About to render text [" << text  << "] with font " << *this << endl;

    int i  = 0;
    while(i < text.length())
    {

        cout << "[" << text[i] << "|" << (unsigned int)(text[i]) << "]";
        i++;
    }

    cout << endl;
#endif
    //If there is no text, return a null surface.
    if(text=="") return NULL;




    //Get a temporary pointer that we return
    std::string toBeRendered = StripText(text);
    SDL_Surface * tmpSurface = NULL;

    //The text renderer doesn't like to render empty text.
    if(toBeRendered.length() == 0) toBeRendered = " ";

    //Using the RenderUTF8 stuff below has a hard time with 'foreign' characters; possibly because
    //the toberendered needs to be converted to UTF-8????


    if(mAntiAliased)
        {

            // toBeRendered might need to be converted to UTF8
             if(is_utf8(toBeRendered))
              {
                  tmpSurface = TTF_RenderUTF8_Shaded(mTTF_Font, toBeRendered.c_str(), mSDL_FGColor, mSDL_BGColor);
              } else {
                  tmpSurface = TTF_RenderText_Shaded(mTTF_Font, toBeRendered.c_str(), mSDL_FGColor, mSDL_BGColor);
              }

        }
    else
        {
           // tmpSurface = TTF_RenderText_Blended(mTTF_Font,toBeRendered.c_str(), mSDL_FGColor);
            if(is_utf8(toBeRendered) )
             {
               tmpSurface = TTF_RenderUTF8_Blended(mTTF_Font,toBeRendered.c_str(), mSDL_FGColor);
             }
            else
             {
                tmpSurface =  TTF_RenderText_Blended(mTTF_Font, toBeRendered.c_str(), mSDL_FGColor);
             }
        }

    //
    //TTF_RenderText_Blended(
    //TTF_Font *font, // This is the TTF_Font to use.
    //char *cstr, // This is the text to render.
    //                     SDL_Color &clr, // This is the color to use.
    //                     );




    if(tmpSurface)
        {
            return tmpSurface;
        }
    else
        {

            string message =   "Unable to render text  [" +  toBeRendered + "] in PlatformFont::RenderText";
            PError::SignalFatalError(message);
        }

    return NULL;
}


//This transforms an escape-filled text string into its displayable version.
std::string PlatformFont::StripText(const std::string & text)
{
    //First, transform text into the to-be-rendered text.  I.E., replace
    //escape characters etc.
    //This might destroy UTF-formatting and stuff, so we have to be careful.

    std::string toBeRendered;

    for(unsigned int i = 0; i < text.size(); i++)
        {


            if(text[i] == 10 ||
               text[i] == 13 ||
               text[i] == 18)
                {
                    //Do nothing.;

                }
            else if(text[i] == 9)
                {
                    //This is a tab character. First, figure out
                    //what absolute position it should be in: round
                    //the length eof toBeRendered up to the next value
                    //i mod 4.

                    int x = 8*((toBeRendered.length()+1) /8 + 1 );
                    int diff = x-toBeRendered.length();
                    string tmp = " ";
                    for(int j = 0; j < diff; j++)
                        {
                            toBeRendered.push_back(tmp[0]);
                        }

                }
            else
                {
                    toBeRendered.push_back(text[i]);
                }

        }

    return toBeRendered;
}


unsigned int PlatformFont::GetTextWidth(const std::string & text)
{
    int height, width;
    std::string toBeRendered = StripText(text.c_str());
    TTF_SizeText(mTTF_Font,toBeRendered.c_str(),&width,&height);
    unsigned int uwidth = (unsigned int)width;
    return uwidth;
}

unsigned int PlatformFont::GetTextHeight(const std::string & text)
{
    int height, width;

    TTF_SizeText(mTTF_Font,text.c_str(),&width,&height);
    unsigned int uheight = (unsigned int)height;
    return uheight;
}


//This returns the nearest character to the pixel column specified by x
int PlatformFont::GetPosition(const std::string & text, unsigned int x)
{

    //Start at 0 and check until the width of the rendered text is bigger than x

    unsigned int cutoff = 1;

    while(cutoff < text.size())
        {

            //If the width of the rendered text is larger than the x argument,
            unsigned int width = GetTextWidth(text.substr(0,cutoff));
            if(width > x)
                return cutoff-1;
            //cout << "***"<<width<< "<" << x << ":" << cutoff <<endl;
            cutoff++;
        }

    //If we make it this far, we have run out of letters, so return the last character.

    return text.size();
}


 std::ostream & PlatformFont::SendToStream(std::ostream& out) const
{
    out << "<SDL-Specific Font>" << std::flush;
    return out;
}



