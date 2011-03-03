//* -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*- */
/////////////////////////////////////////////////////////////////////////////////
//    Name:       src/libs/Functions.h
//    Purpose:    Defines function tables
//    Author:     Shane T. Mueller, Ph.D.
//    Copyright:  (c) 2003-2011 Shane T. Mueller <smueller@obereed.net>
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
#ifndef __FUNCTIONS_H__
#define __FUNCTIONS_H__

#include "PEBLEnvironment.h"
#include "PEBLMath.h"
#include "PEBLStream.h"
#include "PEBLObjects.h"
#include "PEBLList.h"
#include "PEBLString.h"

//A little data structure that holds lcase PEBL function names, the actual names of the functions,
//and the number of arguments to the function.  
struct PEBL_Function_Type {    
    char    *name;
    Variant  (*funcname)(Variant);
    int     minNumArgs; 
    int     maxNumArgs;
};



namespace PEBLMath
{
  
    PEBL_Function_Type  FunctionTable[] =
        { 
            {"LOG10",         Log10,    1, 1},
            {"LOG2",          Log2,     1, 1},
            {"LN",            Ln,       1, 1},
            {"LOGN",          LogN,     2, 2},
            {"EXP",           Exp,      1, 1},
            {"POW",           Pow,      2, 2},
            {"SQRT",          Sqrt,     1, 1},
            {"NTHROOT",       NthRoot,  2, 2},
            
            //Trigonometry
            {"TAN",           Tan,      1, 1},
            {"SIN",           Sin,      1, 1},
            {"COS",           Cos,      1, 1},
            {"ATAN",          ATan,     1, 1},
            {"ASIN",          ASin,     1, 1},
            {"ACOS",          ACos,     1, 1},
            {"DEGTORAD",      DegToRad, 1, 1},
            {"RADTODEG",      RadToDeg, 1, 1},
        
            //Rounding
            {"ROUND",         Round,    1, 2},
            {"FLOOR",         Floor,    1, 1},
            {"CEILING",       Ceiling,  1, 1},
        
            {"ABSFLOOR",      AbsFloor, 1, 1},
         
            //Modular Arithmetic
            {"MOD",           Mod,      2, 2},
            {"DIV",           Div,      2, 2},
        
            //Coercion
            {"TOINTEGER",     ToInt,    1, 1},
            {"TOFLOAT",       ToFloat,  1, 1},
            {"TONUMBER",      ToNumber, 1, 1},
            {"TOSTRING",      ToString, 1, 1},

        
            //Other
            {"SIGN",          Sign,     1, 1},
            {"ABS",           Abs,      1, 1},
             
            //Statistical (operates on a list; ignores non-numeric elements.)
//             {"MEAN",          Mean,     1, 1},
//             {"MIN",           Min,      1, 9999},
//             {"MAX",           Max,      1, 9999},
//             {"STDEV",         StDev,    1, 1},
//             {"MEDIAN",        Median,   1, 1},
//            {"QUANTILE",      Quantile, 2, 2},

            {"RANDOMIZETIMER",     RandomizeTimer,    0, 0},
            {"SEEDRNG",            SeedRNG,           1, 1},
            {"RANDOM",             Random,            0, 0},
            {"RANDOMDISCRETE",     RandomDiscrete,    1, 1},           
            {"RANDOMUNIFORM",      RandomUniform,     1, 1},
            {"RANDOMNORMAL",       RandomNormal,      2, 2},
            {"RANDOMEXPONENTIAL",  RandomExponential, 1, 1},
            {"RANDOMLOGISTIC",     RandomLogistic,    1, 1},
            {"RANDOMLOGNORMAL",    RandomLogNormal,   2, 2},
            {"RANDOMBINOMIAL",     RandomBinomial,    2, 2},           
            {"RANDOMBERNOULLI",    RandomBernoulli,   1, 1},

            {0,            0,  0, 0}
        };
}



namespace PEBLStream
{
    
    PEBL_Function_Type  FunctionTable[] =
        { 
            {"PRINT",                Print,            1, 1},
            {"PRINT_",               Print_,           1, 1},
            {"FORMAT",               Format,           1, 1},
            {"FILEOPENREAD",         FileOpenRead,     1, 1},
            {"FILEOPENWRITE",        FileOpenWrite,    1, 1},
            {"FILEOPENAPPEND",       FileOpenAppend,   1, 1},
            {"FILECLOSE",            FileClose,        1, 1},
            {"FILEPRINT",            FilePrint,        2, 2},
            {"FILEPRINT_",           FilePrint_,       2, 2},
            {"FILEREADCHARACTER",    FileReadCharacter,1, 1},
            {"FILEREADWORD",         FileReadWord,     1, 1},
            {"FILEREADLINE",         FileReadLine,     1, 1},
            {"FILEREADLIST",         FileReadList,     1, 1},
            {"FILEREADTABLE",        FileReadTable,    1, 2},
            {"FILEREADTEXT",         FileReadText,     1, 1},

            {"ENDOFLINE",            EndOfLine,        1, 1},
            {"ENDOFFILE",            EndOfFile,        1, 1},
            {"APPENDFILE",           AppendFile,       2, 2},

            {"CONNECTTOIP", ConnectToIP,               2, 2},
            {"CONNECTTOHOST", ConnectToHost,           2, 2},
            {"WAITFORNETWORKCONNECTION", WaitForNetworkConnection, 1,1},
            {"CLOSENETWORKCONNECTION", CloseNetworkConnection,    1,1},
                
            {"SENDDATA", SendData,                     2,2},
            {"GETDATA", GetData,                       2,2},
            {"WRITEPNG", WritePNG,                     2,2},

            {"OPENPPORT",OpenPPort,                   1,1},
            {"SETPPORTSTATE",SetPPortState,           2,2},
            {"GETPPORTSTATE",GetPPortState,           1,1},
            {"SETPPORTMODE", SetPPortMode,           2,2},

            {"OPENCOMPORT",      OpenComPort,          1,1},
            {"COMPORTSENDBYTE",  ComPortSendByte,      2,2},
            {"COMPORTGETBYTE",   ComPortGetByte,       1,1},



            {0,            0,  0, 0}
        };
}


namespace PEBLObjects
{
    
    PEBL_Function_Type  FunctionTable[] =
        { 
 
            {"MAKEWINDOW",        MakeWindow, 0, 1},
            {"MAKEIMAGE",         MakeImage,  1, 1},
            {"MAKELABEL",         MakeLabel,  2, 2},
            {"MAKETEXTBOX",       MakeTextBox, 4, 4},            
            {"MAKECANVAS",        MakeCanvas, 3,3},            
            {"MAKECOLOR",         MakeColor,  1, 1},
            {"MAKECOLORRGB",      MakeColorRGB, 3, 3},
            {"MAKEFONT",          MakeFont,   6, 6},
            {"MOVE",              Move,       3, 3},
            {"GETSIZE",           GetSize,    1, 1},
            {"ADDOBJECT",         AddObject,  2, 2},
            {"REMOVEOBJECT",      RemoveObject,  2, 2},
            {"SETPOINT",          SetPoint, 4,4},
            {"SETCURSORPOSITION", SetCursorPosition, 2,2},
            {"GETCURSORPOSITION", GetCursorPosition, 1,1},
            {"SETEDITABLE",       SetEditable,  2,2},
            {"SETTEXT",           SetText,      2,2},
            {"GETTEXT",           GetText,      1,1},
            {"SETFONT",           SetFont,      2,2},
            {"SHOW",              Show,       1, 1},
            {"PRINTPROPERTIES",   PrintProperties,  1, 1},
            {"HIDE",              Hide,       1, 1},
            {"DRAW",              Draw,       0, 1},
            {"DRAWFOR",           DrawFor,    2, 2},

            {"SETPIXEL",          SetPoint, 4,4},
            {"LOADSOUND",         LoadSound,        1, 1},
            {"PLAYBACKGROUND",    PlayBackground,   1, 1},
            {"PLAYFOREGROUND",    PlayForeground,   1, 1},
            {"STOP",              Stop,             1, 1},
            {"MAKESINEWAVE",      MakeSineWave,     3, 3},
            {"MAKESQUAREWAVE",    MakeSquareWave,   2, 2},
            {"MAKESAWTOOTHWAVE",  MakeSawtoothWave, 2, 2},
            {"MAKECHIRP",         MakeChirp,        3, 3},
            
            {"LINE",              Line,            5, 5},
            {"RECTANGLE",         Rectangle,       6, 6},
            {"SQUARE",            Square,          5, 5},

            {"ELLIPSE",           Ellipse,      6, 6},
            {"CIRCLE",            Circle,       5, 5},
            {"POLYGON",           Polygon,      6, 6},
            {"BEZIER",           Bezier,      6, 6},

            {"ROTOZOOM",          RotoZoom,     5,5},

            {0,            0,  0, 0}
        };
}

namespace PEBLEnvironment
{

  
    PEBL_Function_Type  FunctionTable[] =
        { 
            {"GETTIME",                         GetTime,           0, 0},
            {"WAIT",                            Wait,              1, 1},

            {"SHOWCURSOR",                      ShowCursor,        1, 1},
            {"SETMOUSECURSORPOSITION",          SetCursorPosition,   2,2},
            {"GETMOUSECURSORPOSITION",          GetCursorPosition,   0,0},



            {"ISKEYDOWN",                       IsKeyDown,         1, 1},
            {"ISKEYUP",                         IsKeyUp,           1, 1},
            {"ISANYKEYDOWN",                    IsAnyKeyDown,      0, 0},
            {"WAITFORKEYDOWN",                  WaitForKeyDown,    1, 1},
            {"WAITFORANYKEYDOWN",               WaitForAnyKeyDown, 0, 0},
            {"WAITFORKEYUP",                    WaitForKeyUp,      1, 1},

            {"WAITFORKEYPRESS",                 WaitForKeyPress,    1, 1},
            {"WAITFORANYKEYPRESS",              WaitForAnyKeyPress, 0, 0},
            {"WAITFORKEYRELEASE",               WaitForKeyRelease,  1, 1},
            {"WAITFORLISTKEYPRESS",             WaitForListKeyPress,  1, 1},

            {"WAITFORALLKEYSUP",                WaitForAllKeysUp,  0, 0},
            {"WAITFORANYKEYDOWNWITHTIMEOUT",    WaitForAnyKeyDownWithTimeout,  1, 1},
            {"WAITFORANYKEYPRESSWITHTIMEOUT",   WaitForAnyKeyPressWithTimeout, 1, 1},
            {"WAITFORKEYLISTDOWN",              WaitForKeyListDown, 1, 1},
            {"WAITFORLISTKEYPRESSWITHTIMEOUT",  WaitForListKeyPressWithTimeout, 3,3},
            {"WAITFORMOUSEBUTTON",              WaitForMouseButton, 0,1},
            {"WAITFORMOUSEBUTTONWITHTIMEOUT",   WaitForMouseButtonWithTimeout, 1,2},


            {"GETNUMJOYSTICKS",                 GetNumJoysticks,      0, 0},
            {"OPENJOYSTICK",                    GetJoystick,       1, 1},
            {"GETNUMJOYSTICKAXES",              GetNumJoystickAxes,   1, 1},
            {"GETNUMJOYSTICKBALLS",             GetNumJoystickBalls,  1, 1},
            {"GETNUMJOYSTICKBUTTONS",           GetNumJoystickButtons,1, 1},
            {"GETNUMJOYSTICKHATS",              GetNumJoystickHats,   1, 1},

            {"GETJOYSTICKBUTTONSTATE",          GetJoystickButtonState, 2, 2},
            {"GETJOYSTICKAXISSTATE",            GetJoystickAxisState,   2, 2},
            {"GETJOYSTICKHATSTATE",             GetJoystickHatState,    2, 2},
            {"GETJOYSTICKBALLSTATE",            GetJoystickBallState,   2, 2},


            {"CLEAREVENTLOOP",                  ClearEventLoop,     0, 0},
            {"GETINPUT",                        GetInput,           2, 2},

            {"REGISTEREVENT",                   RegisterEvent,      5,6},
            {"STARTEVENTLOOP",                  StartEventLoop,      0,0},          
            {"CLEAREVENTLOOP",                  ClearEventLoop,      0,0},


            {"SIGNALFATALERROR",                SignalFatalError,   1,1},
            {"TRANSLATEKEYCODE",                TranslateKeyCode,  1, 1},
            {"TIMESTAMP",                       TimeStamp,         0, 0},

            {"GETVIDEOMODES",                  GetVideoModes,    0, 0},
            {"GETPEBLVERSION",                  GetPEBLVersion,    0, 0},       

            {"GETSYSTEMTYPE",                   GetSystemType,     0, 0},
            {"SYSTEMCALL",                      SystemCall,        1,1},
            {"VARIABLEEXISTS",                  VariableExists,    1,1},

            {"ISDIRECTORY",                     IsDirectory,        1,1},
            {"FILEEXISTS",                      FileExists,        1,1},
            {"GETDIRECTORYLISTING",             GetDirectoryListing,1,1},
            
            {"ISTEXT",                          IsText,          1,1},
            {"ISNUMBER",                        IsNumber,          1,1},
            {"ISINTEGER",                       IsInteger,          1,1},
            {"ISFLOAT",                         IsFloat,            1,1},
            {"ISSTRING",                        IsString,           1,1},
            {"ISLIST",                          IsList,             1,1},
            {"ISTEXTBOX",                       IsTextBox,          1,1},
            {"ISCANVAS",                        IsCanvas,           1,1},
            {"ISIMAGE",                         IsImage,            1,1},
            {"ISLABEL",                         IsLabel,            1,1},
            {"ISAUDIOOUT",                      IsAudioOut,         1,1},
            {"ISFONT",                          IsFont,             1,1},
            {"ISCOLOR",                         IsColor,            1,1},
            {"ISFILESTREAM",                    IsFileStream,       1,1},
            {"ISWIDGET",                        IsWidget,           1,1},
            {"ISWINDOW",                        IsWindow,           1,1},
            {"ISSHAPE",                         IsShape,            1,1},
    
            {0,            0,  0, 0}
        };
}


namespace PEBLList
{
    
    PEBL_Function_Type  FunctionTable[] =
        { 
            
            {"SHUFFLE",                   Shuffle, 1, 1},
            {"REPEAT",                    Repeat,    2, 2},            
            {"REPEATLIST",                RepeatList,2, 2},            
            {"SEQUENCE",                  Sequence,  3, 3},
            {"DESIGNFULLCOUNTERBALANCE",   DesignFullCounterbalance, 2, 2},
            {"CROSSFACTORWITHOUTDUPLICATES", CrossFactorWithoutDuplicates, 1, 1},
            {"ROTATE",                    Rotate,  2, 2},
            {"LENGTH",                    Length, 1, 1},
            {"FIRST",                     First, 1, 1},
            {"SECOND",                    Second, 1, 1},
            {"THIRD",                     Third, 1, 1},
            {"FOURTH",                    Fourth, 1, 1},
            {"FIFTH",                     Fifth, 1, 1},
            {"MERGE",                     Merge, 2, 2},
            {"LIST",                      List,  1, 1000},
            {"APPEND",                    Append, 2, 2},
            {"SORT",                      Sort, 1, 1},
            {"SORTBY",                    SortBy, 2, 2},
            {"NTH",                       Nth, 2, 2},
            {"LAST",                      Last, 1, 1},
            {"ISMEMBER",                  IsMember, 2, 2},
            {"REMOVEDUPLICATES",          RemoveDuplicates, 1, 1},
            {"MAKEMAP",                   MakeMap, 2, 2},
            {"TRANSPOSE",                 Transpose,  1, 1},         
            {"SUBLIST",                   SubList, 3, 3},

            {"REMOVE",                    Remove, 2, 2},
            {0,            0,  0, 0}
        };
}

namespace PEBLString
{
    
    PEBL_Function_Type  FunctionTable[] =
        { 
            
            {"UPPERCASE",                 Uppercase, 1, 1},
            {"LOWERCASE",                 Lowercase, 1, 1},
            {"STRINGLENGTH",              StringLength, 1, 1},
            {"SUBSTRING",                 SubString, 3, 3},
            {"FINDINSTRING",              FindInString, 3, 3},
            //          {"TOKEN",                     TokenMakeWindow, 1, 1},
            //          {"FORMAT",        Format, 1, 1},
            {0,            0,  0, 0}
        };
}



#endif
