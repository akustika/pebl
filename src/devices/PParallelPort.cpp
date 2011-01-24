//* -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*- */
/////////////////////////////////////////////////////////////////////////////////
//    Name:       src/devices/PParellelPort.cpp
//    Purpose:    Class for handling parallel port
//    Author:     Shane T. Mueller, Ph.D.
//    Copyright:  (c) 2010 Shane T. Mueller <smueller@obereed.net>
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
#include "PParallelPort.h"
#include "../utility/PError.h"

#if defined (PEBL_LINUX)
#include "sys/io.h"
#endif

using std::ostream;
using std::fstream;
using std::flush;
using std::string;
using std::cout;



enum PEBLPPort
    {
        PEBLPPortLPT1=0x378,
        PEBLPPortLPT2=0x278,
        PEBLPPortLPTX=0x3BC
    }

PParallelPort::PParallelPort():
    mPort(PEBLPPortLPT1),
    mIsOpen(false)
{
    mCDT = CDT_PARALLELPORT;
}


PParallelPort::~PParallelPort()
{
}



void PParallelPort::Init()
{

}

void PParallelPort::SetPort(Variant v)
{
    if(v=="LPT1")
        {
            mPort = PEBLPPortLPT1;
        
        }else if(v=="LPT2")
        {
            mPort = PEBLPPortLPT2;
        } else if(v=="LPTX")
        {
            mPort = PEBLPPortLPTX;
        }else{
        std::cerr << "Cannot set port to ["<<v<<"].  Setting to LPT1.\n";
    }

}


void PParallelPort::SendByte()
{
}

void PParallelPort::Close()
{
}


//Returns a byte (char) with five lowest bits
//indicating state of pins:
// 15, Error
// 13, Select
// 12, Paper empty
// 10, ACK
// 11. Busy

char PParallelPort::GetStatusState()
{
    return (inb(mPort+1)>>3)^0x10;
}

//Gets a byt whos bits are pins 2...9
char PParallelPort::GetDataState()
{
    return (inb(mPort));
}

// Sets port to output mode
//
void PParallelPort::SetOutputMode()
{
    char x;
    x = inb(mPort+2);
    outb(x & 0xdf, mPort+2);
}



// Sets port to output mode
//
void PParallelPort::SetInputMode()
{
    char x;
    x = inb(mPort+2);
    outb(x | 0x20, mPort+2);
}

char PParallelPort::

ostream & PParallelPort::SendToStream(ostream & out) const
{
    out << "<Generic Parallel Port Object>" << flush;
    return out;
}
