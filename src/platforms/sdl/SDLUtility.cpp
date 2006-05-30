//* -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*- */
/////////////////////////////////////////////////////////////////////////////////
//    Name:       src/platforms/sdl/SDLUtility.h
//    Purpose:    Contains miscellaneous utility functions.
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

#include "SDLUtility.h"
#include "../../objects/PColor.h"
#include "SDL/SDL.h"

#include <math.h>
#include <iostream>
using std::cout;
using std::flush;
using std::endl;

/// These are SDL-specific utilities that don't fit into a single class very well.

  
SDL_Color  SDLUtility::PColorToSDLColor(PColor pcolor)
{
  SDL_Color scolor;
  scolor.r = pcolor.GetRed();
  scolor.g = pcolor.GetGreen();
  scolor.b = pcolor.GetBlue();
  scolor.unused = pcolor.GetAlpha();
  
  return scolor;
}

PColor SDLUtility::SDLColorToPColor(SDL_Color scolor)
{
  
  return PColor(scolor.r, scolor.g, scolor.b, scolor.unused);          
}  




///  This sets a pixel to be a certain color.
void SDLUtility::DrawPixel(SDL_Surface *surface, int x, int y, PColor pcolor)
{

    SDL_Color sdlcolor = PColorToSDLColor(pcolor);
    Uint32 pixel = SDL_MapRGBA(surface->format,
                               pcolor.GetRed(), pcolor.GetGreen(),
                               pcolor.GetBlue(), pcolor.GetAlpha());
    
    //Only draw the pixel if it is actually in the surface.
    if(x < 0 
       || x > surface->w
       || y < 0 
       || y > surface->h)
        {
            return;
        }

    int bpp = surface->format->BytesPerPixel;
    /* Here p is the address to the pixel we want to set */
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch(bpp) {
    case 1:
        *p = pixel;
        break;

    case 2:
        *(Uint16 *)p = pixel;
        break;

    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
            p[0] = (pixel >> 16) & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = pixel & 0xff;
        } else {
            p[0] = pixel & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = (pixel >> 16) & 0xff;
        }
        break;
        
    case 4:
        *(Uint32 *)p = pixel;
        break;
    }

}

///  This sets a pixel to be a certain color.
void SDLUtility::DrawLine(SDL_Surface *surface, int x1, int y1, int x2, int y2, PColor pcolor)
{
    //Draw a pixel on every point between (x1,y1) and (x2,y2)
    
    //We need a rough estimate of the number of steps to take.  
    
    int length = (int)(sqrt((double)(x1-x2) * (x1 - x2) + (y1-y2)*(y1-y2)) * 2);
    
    //Draw twice for each intermediate pixel.
    float deltax = (float)(x2 - x1) / length;
    float deltay = (float)(y2 - y1) / length;


    for(int i = 0; i < length; i++)
        {
            DrawPixel( surface, (int)(x1 + deltax * i), (int)( y1 +deltay*i), pcolor);
        }
 
    //Draw the end pixel just for kicks.
    DrawPixel(surface, x2, y2, pcolor);

}

///  This sets a pixel to be a certain color.
void SDLUtility::DrawSmoothLine(SDL_Surface *surface, int x1, int y1, int x2, int y2, PColor pcolor)
{
    //Draw a pixel on every point between (x1,y1) and (x2,y2)
    
    DrawLine(surface, x1, y1, x2, y2, pcolor);


}



/// This extracts the color of a pixel.
PColor SDLUtility::GetPixel(SDL_Surface *surface, int x, int y)
{
    /*int bpp = surface->format->BytesPerPixel;
    // Here p is the address to the pixel we want to retrieve
        Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch(bpp) {
    case 1:
        return *p;

    case 2:
        return *(Uint16 *)p;

    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
            return p[0] << 16 | p[1] << 8 | p[2];
        else
            return p[0] | p[1] << 8 | p[2] << 16;

    case 4:
        return *(Uint32 *)p;

    default:
        return 0;       // shouldn't happen, but avoids warnings 
        }
*/
    return PColor(0,0,0,0);
}
