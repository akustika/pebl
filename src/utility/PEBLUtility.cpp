//* -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*- */
/////////////////////////////////////////////////////////////////////////////////
//    Name:       utility/PEBLUtility.cpp
//    Purpose:    Miscellaneous Utility Functions used in PEBL
//    Author:     Shane T. Mueller, Ph.D.
//    Copyright:  (c) 2003-2004 Shane T. Mueller <smueller@obereed.net>
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
#include "PEBLUtility.h"
#include "rc_ptrs.h"
#include "../base/Variant.h"
#include "../base/PComplexData.h"
#include "../base/PList.h"
#include "../devices/PKeyboard.h"
#include "../apps/Globals.h"

#include <ctype.h>
#include <string>
#include <stdlib.h>
#include <cmath>
#include <iostream>
#include <strstream>
#include <algorithm>

//Some math libraries contain this, but let's not take any chances.
#define PI 3.141592653589793238462643383279502884197169399375


using std::cout;


std::string PEBLUtility::ToUpper(const std::string & text)
{
    std::string newtext(text);
    std::transform(newtext.begin(), newtext.end(), newtext.begin(), ::toupper);
    return newtext;
}



std::string PEBLUtility::ToLower(const std::string & text)
{
    std::string newtext(text);
    std::transform(newtext.begin(), newtext.end(), newtext.begin(), ::tolower);
    return newtext;
}


// ///This returns a pointer to an upper-case version of the text.
// ///buffer better be at least n items long.
// void PEBLUtility::ToUpper(const char* text, char* buffer, int n)
// {
//     //Go through each letter, copying the upper-case version to buffer.
//     //Stop before the last letter because we need a \0.
//     int i = 0;
//     while(text[i] != '\0' &&  i < (n-1))
//         {
//             buffer[i] = toupper(text[i]);
//             i++;
//         }
//     //Add an end-of-string character
//     buffer[i] = '\0';
// }



// ///This returns a pointer to a lower-case version of the text.
// void PEBLUtility::ToLower(const char* text, char* buffer, int n)
// {
    
//     //Go through each letter, copying the lower-case version to buffer.
//     //Stop before the last letter because we need a \0.
//     int i = 0;    
//     while(text[i] != '\0' && i < (n-1))
//         {
//             buffer[i] = tolower(text[i]);
//             i++;
//         }
    
//     //Add an end-of-string character
//     buffer[i] = '\0';
    
    
// }


Variant PEBLUtility::Tokenize(const char* line, char separator)
{
    //We have a string with separators in it.  Go through it character by character and
    //form a list out of the tokens.
    

    counted_ptr<PList>  plist = counted_ptr<PList>(new PList());
    int i = 0;
    int begin = 0;
    char * token;

    //Go through each item of the string.  Cut a token whenever you get to a separator or 
    //a character that might be the end of the line.
    while(true)
        {
            if(line[i] == separator
               || line[i] == '\0'
               || line[i] == 10
               || line[i] == 13)
                {  
                    //line[i] is the separator; the token is from
                    //begin to line[i-1]
                    token = (char*)malloc((i-begin+1+1) * sizeof(char));
                    strncpy(token, &line[begin], i-begin);
                    token[i-begin]='\0';
                        
                    plist->PushBack(Variant(token));
                    begin = i+1;
                }
            
            if(line[i] == '\0'|| line[i] == 10  || line[i] == 13)
                break;
            i++;
        }

    counted_ptr<PComplexData> pcd  = counted_ptr<PComplexData>(new PComplexData(plist));
    return Variant(pcd);
}



long double PEBLUtility::StringToLongDouble(const char * mystring)
{
#if defined(strold)
    return strtold(mystring,0);
#else 
    return (long double)strtod(mystring,0);
#endif
}



double PEBLUtility::RandomUniform()
{
    return (double)rand() / RAND_MAX; 
}


/// It will return a floating-
/// point number which is a sample from the N(0,1) distribution.
/// Values are calculated using the Box-Mueller technique.
double PEBLUtility::RandomNormal()
{

    double x1 = RandomUniform();
    double x2 = RandomUniform();
  
    return sqrt(-2 * log(x1)) * cos(2 * PI * x2);
}

long double PEBLUtility::Log2(long double val)
{
#if defined(log2l)
    return log2l(val);
#elif defined(log2)
    return (long double)log2((double)val);
#else 
    return logl(val) / logl(2);
#endif
}

long int PEBLUtility::Round(long double val)
{
#if defined(roundl)
    return roundl(val);
#elif defined(round)
    return round((double)val);
#else
    return (long int) floor(val);
#endif
}

long int PEBLUtility::Truncate(long double val)
{
#if defined(truncl)
    return truncl(val);
#elif defined(trunc)
    return trunc((double)val);
#else 
    int sign = val < 0 ? -1: 1; 
    return sign * Round(sign * val);
#endif

}



///This does as best as it can to translate the letter string
///into a keyboard key.
PEBLKey PEBLUtility::TranslateString(const std::string & letters)
{

    //Use as a default the first letter.
    
    PEBLKey code = PEBLKey(int(letters[0]));
    //First, see if we are only a single character.  If so, rock-n-roll.
    if(letters.length() == 1)
        {
            //recode uppercase letters into lowercase.
            if(code > 64 && code < 91)
                code = PEBLKey(int(code) + 32);
            return code;
        }  
    
    if(letters == "<RETURN>" || letters == "<return>") 
        return PEBLKEY_RETURN;
    if(letters == "<esc>" || letters == "<ESC>")
        return PEBLKEY_ESCAPE;
    if(letters == "<back>" || letters == "<BACK>"
       || letters == "<backspace>" || letters == "<BACKSPACE>"
       )
        return PEBLKEY_BACKSPACE;


    //More extravagent things can be done to get other keys.

    return PEBLKEY_UNKNOWN;
}

//This returns a text-valued description of the key pressed.
std::string PEBLUtility::TranslateKeyCode(const PEBLKey key, int modkeys)
{
    switch(key)
        {
            /* The keyboard syms have been cleverly chosen to map to ASCII */
        case PEBLKEY_UNKNOWN:	     return "<unknown>";
            //   case PEBLKEY_FIRST:	     return "<>";  //same as above
            //  case PEBLKEY_NOTHING:        return "<nothing>";  //same as above
        case PEBLKEY_ANYKEY:	     return "<ANYKEY>";
        case PEBLKEY_BACKSPACE:      return "<backspace>";
        case PEBLKEY_TAB:            return "<tab>";
        case PEBLKEY_CLEAR:          return "<clear>";
        case PEBLKEY_RETURN:         return "<return>";
        case PEBLKEY_PAUSE:          return "<pause>";
        case PEBLKEY_ESCAPE:         return "<esc>";
        case PEBLKEY_SPACE:          return " ";
        case PEBLKEY_EXCLAIM:        return "!";
        case PEBLKEY_QUOTEDBL:       return "\"";
        case PEBLKEY_HASH:           return "#";	
        case PEBLKEY_DOLLAR:         return "$";
        case PEBLKEY_AMPERSAND:      return "&";
        case PEBLKEY_QUOTE:          return "'";
        case PEBLKEY_LEFTPAREN:      return "(";
        case PEBLKEY_RIGHTPAREN:     return ")";
        case PEBLKEY_ASTERISK:       return "*";
        case PEBLKEY_PLUS:           return "+";
        case PEBLKEY_COMMA:          return ",";
        case PEBLKEY_MINUS:          return "-";
        case PEBLKEY_PERIOD:         return ".";
        case PEBLKEY_SLASH:          return "/";
        case PEBLKEY_0:         return "0";
        case PEBLKEY_1:         return "1";
        case PEBLKEY_2:         return "2";
        case PEBLKEY_3:         return "3";
        case PEBLKEY_4:         return "4";
        case PEBLKEY_5:         return "5";
        case PEBLKEY_6:         return "6";
        case PEBLKEY_7:         return "7";
        case PEBLKEY_8:         return "8";
        case PEBLKEY_9:         return "9";
        case PEBLKEY_COLON:         return ":";
        case PEBLKEY_SEMICOLON:     return ";";
        case PEBLKEY_LESS:          return "<";
        case PEBLKEY_EQUALS:        return "=";
        case PEBLKEY_GREATER:       return ">";
        case PEBLKEY_QUESTION:      return "?";
        case PEBLKEY_AT:            return "@";
        /* 
           Skip uppercase letters
        */
        case PEBLKEY_LEFTBRACKET:         return "[";
        case PEBLKEY_BACKSLASH:           return "\\";
        case PEBLKEY_RIGHTBRACKET:        return "]";
        case PEBLKEY_CARET:               return "^";
        case PEBLKEY_UNDERSCORE:          return "_";
        case PEBLKEY_BACKQUOTE:           return "`";
        case PEBLKEY_a:         return ShiftSwitch(modkeys, "a","A");
        case PEBLKEY_b:         return ShiftSwitch(modkeys, "b","B");
        case PEBLKEY_c:         return ShiftSwitch(modkeys, "c","C");
        case PEBLKEY_d:         return ShiftSwitch(modkeys, "d","D");
        case PEBLKEY_e:         return ShiftSwitch(modkeys, "e","E");
        case PEBLKEY_f:         return ShiftSwitch(modkeys, "f","F");
        case PEBLKEY_g:         return ShiftSwitch(modkeys, "g","G");
        case PEBLKEY_h:         return ShiftSwitch(modkeys, "h","H");
        case PEBLKEY_i:         return ShiftSwitch(modkeys, "i","I");
        case PEBLKEY_j:         return ShiftSwitch(modkeys, "j","J");
        case PEBLKEY_k:         return ShiftSwitch(modkeys, "k","K");
        case PEBLKEY_l:         return ShiftSwitch(modkeys, "l","L");
        case PEBLKEY_m:         return ShiftSwitch(modkeys, "m","M");
        case PEBLKEY_n:         return ShiftSwitch(modkeys, "n","N");
        case PEBLKEY_o:         return ShiftSwitch(modkeys, "o","O");
        case PEBLKEY_p:         return ShiftSwitch(modkeys, "p","P");
        case PEBLKEY_q:         return ShiftSwitch(modkeys, "q","Q");
        case PEBLKEY_r:         return ShiftSwitch(modkeys, "r","R");
        case PEBLKEY_s:         return ShiftSwitch(modkeys, "s","S");
        case PEBLKEY_t:         return ShiftSwitch(modkeys, "t","T");
        case PEBLKEY_u:         return ShiftSwitch(modkeys, "u","U");
        case PEBLKEY_v:         return ShiftSwitch(modkeys, "v","V");
        case PEBLKEY_w:         return ShiftSwitch(modkeys, "w","W");
        case PEBLKEY_x:         return ShiftSwitch(modkeys, "x","X");
        case PEBLKEY_y:         return ShiftSwitch(modkeys, "y","Y");
        case PEBLKEY_z:         return ShiftSwitch(modkeys, "z","Z");
        case PEBLKEY_DELETE:         return "<delete>";
        /* End of ASCII mapped keysyms */

        /* International keyboard syms */
        case PEBLKEY_WORLD_0:         return "<PEBL WORLD KEY>";
        case PEBLKEY_WORLD_1:         return "<PEBL WORLD KEY>";
        case PEBLKEY_WORLD_2:         return "<PEBL WORLD KEY>";
        case PEBLKEY_WORLD_3:         return "<PEBL WORLD KEY>";
        case PEBLKEY_WORLD_4:         return "<PEBL WORLD KEY>";
        case PEBLKEY_WORLD_5:         return "<PEBL WORLD KEY>";
        case PEBLKEY_WORLD_6:         return "<PEBL WORLD KEY>";
        case PEBLKEY_WORLD_7:         return "<PEBL WORLD KEY>";
        case PEBLKEY_WORLD_8:         return "<PEBL WORLD KEY>";
        case PEBLKEY_WORLD_9:         return "<PEBL WORLD KEY>";
        case PEBLKEY_WORLD_10:         return "<PEBL WORLD KEY>";
        case PEBLKEY_WORLD_11:         return "<PEBL WORLD KEY>";
        case PEBLKEY_WORLD_12:         return "<PEBL WORLD KEY>";
        case PEBLKEY_WORLD_13:         return "<PEBL WORLD KEY>";
        case PEBLKEY_WORLD_14:         return "<PEBL WORLD KEY>";
        case PEBLKEY_WORLD_15:         return "<PEBL WORLD KEY>";
        case PEBLKEY_WORLD_16:         return "<PEBL WORLD KEY>";
        case PEBLKEY_WORLD_17:         return "<PEBL WORLD KEY>";
        case PEBLKEY_WORLD_18:         return "<PEBL WORLD KEY>";
        case PEBLKEY_WORLD_19:         return "<PEBL WORLD KEY>";
        case PEBLKEY_WORLD_20:         return "<PEBL WORLD KEY>";
        case PEBLKEY_WORLD_21:         return "<PEBL WORLD KEY>";
        case PEBLKEY_WORLD_22:         return "<PEBL WORLD KEY>";
        case PEBLKEY_WORLD_23:         return "<PEBL WORLD KEY>";
        case PEBLKEY_WORLD_24:         return "<PEBL WORLD KEY>";
        case PEBLKEY_WORLD_25:         return "<PEBL WORLD KEY>";
        case PEBLKEY_WORLD_26:         return "<PEBL WORLD KEY>";
        case PEBLKEY_WORLD_27:         return "<PEBL WORLD KEY>";
        case PEBLKEY_WORLD_28:         return "<PEBL WORLD KEY>";
        case PEBLKEY_WORLD_29:         return "<PEBL WORLD KEY>";
        case PEBLKEY_WORLD_30:         return "<PEBL WORLD KEY>";
        case PEBLKEY_WORLD_31:         return "<PEBL WORLD KEY>";
        case PEBLKEY_WORLD_32:         return "<PEBL WORLD KEY>";
        case PEBLKEY_WORLD_33:         return "<PEBL WORLD KEY>";
        case PEBLKEY_WORLD_34:         return "<PEBL WORLD KEY>";
        case PEBLKEY_WORLD_35:         return "<PEBL WORLD KEY>";
        case PEBLKEY_WORLD_36:         return "<PEBL WORLD KEY>";
        case PEBLKEY_WORLD_37:         return "<PEBL WORLD KEY>";
        case PEBLKEY_WORLD_38:         return "<PEBL WORLD KEY>";
        case PEBLKEY_WORLD_39:         return "<PEBL WORLD KEY>";
        case PEBLKEY_WORLD_40:         return "<PEBL WORLD KEY>";
        case PEBLKEY_WORLD_41:         return "<PEBL WORLD KEY>";
        case PEBLKEY_WORLD_42:         return "<PEBL WORLD KEY>";
        case PEBLKEY_WORLD_43:         return "<PEBL WORLD KEY>";
        case PEBLKEY_WORLD_44:         return "<PEBL WORLD KEY>";
        case PEBLKEY_WORLD_45:         return "<PEBL WORLD KEY>";
        case PEBLKEY_WORLD_46:         return "<PEBL WORLD KEY>";
        case PEBLKEY_WORLD_47:         return "<PEBL WORLD KEY>";
        case PEBLKEY_WORLD_48:         return "<PEBL WORLD KEY>";
        case PEBLKEY_WORLD_49:         return "<PEBL WORLD KEY>";
        case PEBLKEY_WORLD_50:         return "<PEBL WORLD KEY>";
        case PEBLKEY_WORLD_51:         return "<PEBL WORLD KEY>";
        case PEBLKEY_WORLD_52:         return "<PEBL WORLD KEY>";
        case PEBLKEY_WORLD_53:         return "<PEBL WORLD KEY>";
        case PEBLKEY_WORLD_54:         return "<PEBL WORLD KEY>";
        case PEBLKEY_WORLD_55:         return "<PEBL WORLD KEY>";
        case PEBLKEY_WORLD_56:         return "<PEBL WORLD KEY>";
        case PEBLKEY_WORLD_57:         return "<PEBL WORLD KEY>";
        case PEBLKEY_WORLD_58:         return "<PEBL WORLD KEY>";
        case PEBLKEY_WORLD_59:         return "<PEBL WORLD KEY>";
        case PEBLKEY_WORLD_60:         return "<PEBL WORLD KEY>";
        case PEBLKEY_WORLD_61:         return "<PEBL WORLD KEY>";
        case PEBLKEY_WORLD_62:         return "<PEBL WORLD KEY>";
        case PEBLKEY_WORLD_63:         return "<PEBL WORLD KEY>";
        case PEBLKEY_WORLD_64:         return "<PEBL WORLD KEY>";
        case PEBLKEY_WORLD_65:         return "<PEBL WORLD KEY>";
        case PEBLKEY_WORLD_66:         return "<PEBL WORLD KEY>";
        case PEBLKEY_WORLD_67:         return "<PEBL WORLD KEY>";
        case PEBLKEY_WORLD_68:         return "<PEBL WORLD KEY>";
        case PEBLKEY_WORLD_69:         return "<PEBL WORLD KEY>";
        case PEBLKEY_WORLD_70:         return "<PEBL WORLD KEY>";
        case PEBLKEY_WORLD_71:         return "<PEBL WORLD KEY>";
        case PEBLKEY_WORLD_72:         return "<PEBL WORLD KEY>";
        case PEBLKEY_WORLD_73:         return "<PEBL WORLD KEY>";
        case PEBLKEY_WORLD_74:         return "<PEBL WORLD KEY>";
        case PEBLKEY_WORLD_75:         return "<PEBL WORLD KEY>";
        case PEBLKEY_WORLD_76:         return "<PEBL WORLD KEY>";
        case PEBLKEY_WORLD_77:         return "<PEBL WORLD KEY>";
        case PEBLKEY_WORLD_78:         return "<PEBL WORLD KEY>";
        case PEBLKEY_WORLD_79:         return "<PEBL WORLD KEY>";
        case PEBLKEY_WORLD_80:         return "<PEBL WORLD KEY>";
        case PEBLKEY_WORLD_81:         return "<PEBL WORLD KEY>";
        case PEBLKEY_WORLD_82:         return "<PEBL WORLD KEY>";
        case PEBLKEY_WORLD_83:         return "<PEBL WORLD KEY>";
        case PEBLKEY_WORLD_84:         return "<PEBL WORLD KEY>";
        case PEBLKEY_WORLD_85:         return "<PEBL WORLD KEY>";
        case PEBLKEY_WORLD_86:         return "<PEBL WORLD KEY>";
        case PEBLKEY_WORLD_87:         return "<PEBL WORLD KEY>";
        case PEBLKEY_WORLD_88:         return "<PEBL WORLD KEY>";
        case PEBLKEY_WORLD_89:         return "<PEBL WORLD KEY>";
        case PEBLKEY_WORLD_90:         return "<PEBL WORLD KEY>";
        case PEBLKEY_WORLD_91:         return "<PEBL WORLD KEY>";
        case PEBLKEY_WORLD_92:         return "<PEBL WORLD KEY>";
        case PEBLKEY_WORLD_93:         return "<PEBL WORLD KEY>";
        case PEBLKEY_WORLD_94:         return "<PEBL WORLD KEY>";
        case PEBLKEY_WORLD_95:         return "<PEBL WORLD KEY>";
        /* Numeric keypad */
        case PEBLKEY_KP0:         return "0";
        case PEBLKEY_KP1:         return "1";
        case PEBLKEY_KP2:         return "2";
        case PEBLKEY_KP3:         return "3";
        case PEBLKEY_KP4:         return "4";
        case PEBLKEY_KP5:         return "5";
        case PEBLKEY_KP6:         return "6";
        case PEBLKEY_KP7:         return "7";
        case PEBLKEY_KP8:         return "8";
        case PEBLKEY_KP9:         return "9";
        case PEBLKEY_KP_PERIOD:   return ".";
        case PEBLKEY_KP_DIVIDE:   return "/";
        case PEBLKEY_KP_MULTIPLY: return "*";
        case PEBLKEY_KP_MINUS:    return "-";
        case PEBLKEY_KP_PLUS:     return "+";
        case PEBLKEY_KP_ENTER:    return "<kp_enter>";
        case PEBLKEY_KP_EQUALS:   return "=";

        /* Arrows + Home/End pad */
        case PEBLKEY_UP:         return "<up>";
        case PEBLKEY_DOWN:       return "<down>";
        case PEBLKEY_RIGHT:      return "<right>";
        case PEBLKEY_LEFT:       return "<left>";
        case PEBLKEY_INSERT:     return "<insert>";
        case PEBLKEY_HOME:       return "<home>";
        case PEBLKEY_END:        return "<end>";
        case PEBLKEY_PAGEUP:     return "<pageup>";
        case PEBLKEY_PAGEDOWN:   return "<pagedown>";

        /* Function keys */
        case PEBLKEY_F1:         return "<F1>";
        case PEBLKEY_F2:         return "<F2>";
        case PEBLKEY_F3:         return "<F3>";
        case PEBLKEY_F4:         return "<F4>";
        case PEBLKEY_F5:         return "<F5>";
        case PEBLKEY_F6:         return "<F6>";
        case PEBLKEY_F7:         return "<F7>";
        case PEBLKEY_F8:         return "<F8>";
        case PEBLKEY_F9:         return "<F9>";
        case PEBLKEY_F10:         return "<F10>";
        case PEBLKEY_F11:         return "<F11>";
        case PEBLKEY_F12:         return "<F12>";
        case PEBLKEY_F13:         return "<F13>";
        case PEBLKEY_F14:         return "<F14>";
        case PEBLKEY_F15:         return "<F15>";

        /* Key state modifier keys */
        case PEBLKEY_NUMLOCK:      return "<numlock>";
        case PEBLKEY_CAPSLOCK:     return "<capslock>";
        case PEBLKEY_SCROLLOCK:    return "<scrollock>";
        case PEBLKEY_RSHIFT:       return "<rshift>";
        case PEBLKEY_LSHIFT:       return "<lshift>";
        case PEBLKEY_RCTRL:        return "<rctrl>";
        case PEBLKEY_LCTRL:        return "<lctrl>";
        case PEBLKEY_RALT:         return "<ralt>";
        case PEBLKEY_LALT:         return "<lalt>";
        case PEBLKEY_RMETA:        return "<rmeta>";
        case PEBLKEY_LMETA:        return "<lmeta>";
        case PEBLKEY_LSUPER:       return "<lsuper>";
        case PEBLKEY_RSUPER:       return "<rsuper>";
        case PEBLKEY_MODE:         return "<mode>";
        case PEBLKEY_COMPOSE:      return "<compose>";

        /* Miscellaneous function keys */
        case PEBLKEY_HELP:         return "<help>";
        case PEBLKEY_PRINT:        return "<print>";
        case PEBLKEY_SYSREQ:       return "<sysreq>";
        case PEBLKEY_BREAK:        return "<break>";
        case PEBLKEY_MENU:         return "<menu>";
        case PEBLKEY_POWER:        return "<power>";
        case PEBLKEY_EURO:         return "<euro>";
        case PEBLKEY_UNDO:         return "<undo>";

        /* Add any other keys here */
        case PEBLKEY_LAST:         return "<LAST KEY: ERROR>";
        default:                   return "<ERROR>";
    };
}


PEBLVideoMode PEBLUtility::GetVideoMode(std::string modeline)
{

	PEBLVideoMode mode;

	if(modeline == "512x384") mode =PVM_512_384;
	else if (modeline =="640x480") mode =	PVM_640_480;
	else if (modeline =="800x600")	mode =	PVM_800_600;
	else if (modeline ==	"960x720")	mode =	PVM_960_720;
	else if (modeline ==	"1024x768")	mode =	PVM_1024_768;
	else if (modeline ==	"1152x864")	mode =	PVM_1152_864;
	else if (modeline ==	"1280x1024")	mode =	PVM_1280_1024;
	else mode  = PVM_640_480;
	return mode;
}


PEBLVideoDepth PEBLUtility::GetVideoDepth(std::string depthline)
{
	PEBLVideoDepth depth;

	if(depthline == "2")       depth =PVD_2;
	else if (depthline =="15") depth =PVD_15;
	else if (depthline =="16") depth =PVD_16;
	else if (depthline =="24") depth =PVD_24;
	else if (depthline =="32") depth =PVD_32;
	else depth  = PVD_16;

	return depth;
}



//This returns upper if a shift key is pressed, otherwise it returns lower.
std::string PEBLUtility::ShiftSwitch(int modkeys, std::string lower, std::string upper)
{
    if( modkeys & PEBLMOD_SHIFT)
        return upper;
    else
        return lower;
}
