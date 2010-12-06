//* -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*- */
/////////////////////////////////////////////////////////////////////////////////
//    Name:       src/platforms/sdl/PlatformNetwork.cpp
//    Purpose:    Class for handling network communication
//    Author:     Shane T. Mueller, Ph.D.
//    Copyright:  (c) 2006- Shane T. Mueller <smueller@obereed.net>
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
#include "PlatformNetwork.h"
#include "../../devices/PNetwork.h"
#include "../../utility/PError.h"
#include "SDL/SDL_net.h"

#include <string>
using std::string;
using std::cout;
using std::endl;


PlatformNetwork::PlatformNetwork()
{
  mAddress = new IPaddress;
  mAddress->host=0;
  mAddress->port=0;
  mSocket = NULL;
}

PlatformNetwork::~PlatformNetwork()
{
  delete mAddress;
  SDLNet_Quit();
}


void PlatformNetwork::Init()
{
  int val = SDLNet_Init();

  if(!val)
	{
	  std::cerr << "Network System Initialized\n";
	}else{

	  PError::SignalFatalError("Network System Failed to Initialize.");
	}
  
}

void PlatformNetwork::SetHostIP(unsigned int ip)
{
  mHost = ip;
  mAddress->host=ip;

}

void PlatformNetwork::SetPort(unsigned int port)
{

    //SDL swaps the byte order in the SDL_Net library for some reason.
    //So we need to pre-swap to ensure we get the right port.

    mPort = SDL_SwapBE16(port);
    mAddress->port = mPort;

    //std::cout << "Port: " << port <<"|"<<mPort << "|"<<mAddress->port<< std::endl;
    //std::cout << "tmp: " <<tmp << std::endl;

}


//This resolves the IP currently stored in 
void PlatformNetwork::SetHostName(std::string hostname)
{

  mHostName = hostname;
  SDLNet_ResolveHost(mAddress,mHostName.c_str(), mAddress->port);


  //std::cout<< "Host address from name ["  << mAddress->host << "]"<< std::endl;
}



void PlatformNetwork::Open()
{
 
  if(mAddress->host == 0)
	PError::SignalFatalError("Trying to open connection to unspecified host");

  mSocket = SDLNet_TCP_Open(mAddress);
 

    if(!mSocket)
	PError::SignalFatalError("Unable to establish connection to " + mHostName);

  mIsOpen = true;
}


void PlatformNetwork::Accept()
{

  //First, create the socket to listen on:

  IPaddress * tmpAddress = new IPaddress;
  tmpAddress->host = INADDR_ANY;
  tmpAddress->port = mPort;

  std::cout << "unable"  << tmpAddress->port << endl;
  TCPsocket listener = SDLNet_TCP_Open(tmpAddress);

  if(!listener)
	PError::SignalFatalError("Unable to listen for connection." );
    
  while(mSocket == NULL)
	mSocket = SDLNet_TCP_Accept(listener);
  mIsOpen = true;
}


void PlatformNetwork::Close()
{
  if(mSocket)
	SDLNet_TCP_Close(mSocket);
  mSocket = NULL;
  mIsOpen = false;
}


void PlatformNetwork::SendString(std::string data)
{

  if(mIsOpen)
	{
	  char* buffer = strdup(data.c_str());

	  int sent = SDLNet_TCP_Send(mSocket, buffer,data.length());
	  free(buffer);

	  if(sent != (int)data.length())
		{
		  PError::SignalFatalError("Error sending data to " + mHostName + ". Entire Message Not Sent.");		  
		}
	}else{
	  PError::SignalFatalError("Trying to send data without an open connection.");
	}

}


void PlatformNetwork::SendByte(int byte)
{

  if(mIsOpen)
	{

	  int sent = SDLNet_TCP_Send(mSocket, &byte,1);
	  if(sent != 1)
		{
		  PError::SignalFatalError("Error sending data to " + mHostName + ". Entire Message Not Sent.");		  
		}
	}else{
	  PError::SignalFatalError("Trying to send data without an open connection.");
	}

}

std::string PlatformNetwork::Receive(int length)
{

  char * message = NULL;
  if(mIsOpen)
	{


	  message = new char[length+1];
	  
	  int result = SDLNet_TCP_Recv(mSocket,message,length);
	 
	  message[length]  = '\0';
	  if(result == -1)
		{
		  PError::SignalFatalError("Error receiving  data from " + mHostName + ".");
		}
	  else if(result == 0)
		{
		  PError::SignalFatalError("Error receiving data from " + mHostName + ". Connection Closed by peer.");
		}
	}else{
	  PError::SignalFatalError("Trying to receive data without an open connection.");
	}

  std::string ret = std::string(message);
  free(message);
  return ret;
}


std::ostream& PlatformNetwork::SendToStream(std::ostream& out)const
{
  out << "<Network Connection: " << mHostName << ">";
	return out;
}
