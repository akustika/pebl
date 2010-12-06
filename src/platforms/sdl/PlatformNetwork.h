//* -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*- */
/////////////////////////////////////////////////////////////////////////////////
//    Name:       src/devices/PNetwork.h
//    Purpose:    Class for handling network communication (tcpip)
//    Author:     Shane T. Mueller, Ph.D.
//    Copyright:  (c) 2006-2010  Shane T. Mueller <smueller@obereed.net>
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
#ifndef __PLATFORM_NETWORK_H__
#define __PLATFORM_NETWORK_H__

#include "../../devices/PNetwork.h"
#include "SDL/SDL_net.h"

class PlatformNetwork: public PNetwork
{
    
public:    


    ///The Standard constructor.  
  PlatformNetwork();
    
    ///The Standard destructor.  
  virtual ~PlatformNetwork();
  

  virtual void Init();
  
  virtual void SetHostIP(unsigned int);
  virtual void SetPort(unsigned int);
  virtual void SetHostName(std::string hostname);

  virtual void Open();
  virtual void Accept();
  virtual void Close();


  virtual void SendString(std::string message);
  virtual void SendByte(int byte);

  virtual std::string Receive(int length);

protected:

    //Inheritable printing Method.
    virtual std::ostream& SendToStream(std::ostream& out)const; 

private:

	//pointer to a TCPSocket object used by SDL_net.
	IPaddress * mAddress;
	TCPsocket  mSocket;

};


#endif
