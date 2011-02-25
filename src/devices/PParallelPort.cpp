/* -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*- */
////////////////////////////////////////////////////////////////////////////////
//    Name:       src/devices/PParellelPort.cpp
//    Purpose:    Class for handling parallel port
//    Author:     Shane T. Mueller, Ph.D.
//    Copyright:  (c) 2010-2011 Shane T. Mueller <smueller@obereed.net>
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

#endif
#include <sys/io.h>
using std::ostream;
using std::fstream;
using std::flush;
using std::string;
using std::cout;
using std::endl;

#define mPort 0x378

enum PEBLPPort
    {
        PEBLPPortLPT1=0x378,
        PEBLPPortLPT2=0x278,
        PEBLPPortLPTX=0x3BC
    };

PParallelPort::PParallelPort():
    mmPort(PEBLPPortLPT1),
    mIsOpen(false)
{
    mCDT = CDT_PARALLELPORT;
}


PParallelPort::~PParallelPort()
{
    if(mIsOpen)
        Close();
}



void PParallelPort::Init()
{

           
    //This works on linux: open 3 bytes to access
    int out = ioperm(mPort, 3, 1);
    //int out = iopl(3);
    mIsOpen = true;
    std::cerr << "Initiating parallel port.  Return value :["<<out<<"]\n";

    //    EmulateStandardPort();
    if(out)
        {
            PError::SignalFatalError("Unable to Access Parallel Port.  Make sure script is run with root access.\n");
        }


}

void PParallelPort::SetPort(Variant v)
{
    if(v=="LPT1")
        {
            mmPort = PEBLPPortLPT1;
        
        }else if(v=="LPT2")
        {
            mmPort = PEBLPPortLPT2;
        } else if(v=="LPTX")
        {
            mmPort = PEBLPPortLPTX;
        }else{
        std::cerr << "Cannot set port to ["<<v<<"].  Setting to LPT1.\n";
    }

}


void PParallelPort::Close()
{
    int out =ioperm(mPort,3,0);
    mIsOpen = false;
}


////////////////////////////////////////////////
//Returns a byte (char) with five lowest bits
//indicating state of pins:
// 15, Error
// 13, Select
// 12, Paper empty
// 10, ACK
// 11. Busy

char PParallelPort::GetStatusState()
{

    return inb(mPort+1);
    //    return (inb(mPort+1)>>3)^0x10;
}

//Gets a byte whos bits are pins 2...9 (for dual-mode ports)
// 
char PParallelPort::GetDataState()
{
    
    return (inb(mPort));
}

//sets the data bytes (pins 2..9) to the specified state.
void PParallelPort::SetDataState(char x)
{
    outb(x,mPort);
}


void PParallelPort::EmulateStandardPort()
{


}


// Sets port to output mode.  This works for dual-mode ports.
//
void PParallelPort::SetOutputMode()
{

    unsigned char x;
    x = inb(mPort+2);  //get state of control register

    outb(x & ~0x20, mPort+2);
}


// Sets port to input mode
//
void PParallelPort::SetInputMode()
{


    unsigned char x = 0;
    x = inb(mPort+2);
    //  turns 7th bit of the control byte  on
    outb( x | 0x20, mPort+2);

}

ostream & PParallelPort::SendToStream(ostream & out) const
{
    out << "<Generic Parallel Port Object>" << flush;
    return out;
}



//Interface: 0 for data bits; 1 for status bits
int PParallelPort::GetState(int iface)
{
    int out =0;
    if(iface==0)
        {
            SetOutputMode();
            SetDataState(255);
            SetInputMode();
            out = GetDataState();
        } else 
        if(iface==1)
            {
                out = GetStatusState();
            }

     return out;
}
