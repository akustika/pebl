//* -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*- */
/////////////////////////////////////////////////////////////////////////////////
//    Name:       libs/PEBLStream.cpp
//    Purpose:    Built-in stream functions for PEBL
//    Author:     Shane T. Mueller, Ph.D.
//    Copyright:  (c) 2003-2010 Shane T. Mueller <smueller@obereed.net>
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
#include "PEBLStream.h"
#include "../base/Variant.h"
#include "../base/PComplexData.h"
#include "../base/PList.h"
#include "../base/Evaluator.h"

#include "../devices/PStream.h"
#include "../utility/PError.h"
#include "../utility/PEBLPath.h"
#include "../utility/PEBLUtility.h"


#include <list>
#include <iostream>

using std::cout;
using std::flush;
using std::cerr;
using std::endl;



Variant PEBLStream::Print(Variant v)
{

    PList * plist = v.GetComplexData()->GetList();
    Variant v1 = plist->First();
    //No type assertion is needed, because everything should work.
    cout << v1 << endl;

    return v1;
}


Variant PEBLStream::Print_(Variant v)
{

    PList * plist = v.GetComplexData()->GetList();
    Variant v1 = plist->First();
    //No type assertion is needed, because everything should work.
    cout << v1 << flush;

    return v1;
}

Variant PEBLStream::Format(Variant v)
{  

    PList * plist = v.GetComplexData()->GetList();
    Variant v1 = plist->First();
    PError::SignalFatalError("Function [Format()] not implemented.");
    return v1;
}


///This opens a filestream for reading.
Variant PEBLStream::FileOpenRead(Variant v)
{
    PList * plist = v.GetComplexData()->GetList();
    Variant v1 = plist->First(); plist->PopFront();
    PError::AssertType(v1, PEAT_STRING, "Argument error in function FileOpenRead(<string>)]: ");  
    
    ///v1 contains the name of a file to open.
    counted_ptr<PEBLObjectBase> mystream = counted_ptr<PEBLObjectBase>(new PStream(v1,sdRead, stASCII));
    PComplexData * pcd = new PComplexData(mystream);
    Variant tmp = Variant(pcd);
    delete pcd;
    pcd=NULL;
    return tmp;
}

///This opens a filestream for writing, replacing current file
Variant PEBLStream::FileOpenWrite(Variant v)
{
    PList * plist = v.GetComplexData()->GetList();
    Variant v1 = plist->First(); plist->PopFront();
    PError::AssertType(v1, PEAT_STRING, "Argument error in function FileOpenWrite(<string>)]: ");  
 
    ///v1 contains the name of a file to open.      
    counted_ptr<PEBLObjectBase> mystream = counted_ptr<PEBLObjectBase>(new PStream(v1,sdWrite, stASCII));
    PComplexData * pcd = new PComplexData(mystream);
    Variant tmp = Variant(pcd);
    delete pcd;
    pcd=NULL;
    return tmp;

}

///This opens a filestream for writing, appending to end of file.
Variant PEBLStream::FileOpenAppend(Variant v)
{
    PList * plist = v.GetComplexData()->GetList();
    Variant v1 = plist->First(); plist->PopFront();
    PError::AssertType(v1, PEAT_STRING, "Argument error in function FileOpenAppend(<string>)]: ");  

    ///v1 contains the name of a file to open.    
    counted_ptr<PEBLObjectBase> mystream = counted_ptr<PEBLObjectBase>(new PStream(v1,sdAppend, stASCII));
    PComplexData * pcd = new PComplexData(mystream);
    Variant tmp = Variant(pcd);
    delete pcd;
    pcd=NULL;
    return tmp;


}

///This Closes a filestream
Variant PEBLStream::FileClose(Variant v)
{
    //v[1] should have the file stream to close
    PList * plist = v.GetComplexData()->GetList();
    
    Variant v1 = plist->First(); plist->PopFront();
    PError::AssertType(v1, PEAT_FILESTREAM, "Argument error in function [FileClose(<file-stream>)]: ");  


    counted_ptr<PEBLObjectBase> tmp2 = (v1.GetComplexData())->GetObject();
    PStream * mystream = dynamic_cast<PStream*>(tmp2.get());
    return Variant(mystream->Close());
}


Variant PEBLStream::FilePrint(Variant v)
{
    //v[1] should have the file stream 
    //v[2] should have the variant to print
    PList * plist = v.GetComplexData()->GetList();

    Variant v1 = plist->First(); plist->PopFront();


    PError::AssertType(v1, PEAT_FILESTREAM, "Argument error in first parameter of function [FilePrint(<file-stream>, <text>)]: ");  

    counted_ptr<PEBLObjectBase> tmp2 = (v1.GetComplexData())->GetObject();
    PStream * mystream = dynamic_cast<PStream*>(tmp2.get());


    Variant v2 = plist->First(); plist->PopFront();
    std::string s = v2.GetString();
        
    mystream->WriteString(s + "\n");
    return (v2+Variant("\n"));
}  

Variant PEBLStream::FilePrint_(Variant v)
{
    //v[1] should have the file stream 
    //v[2] should have the variant to print
    PList * plist = v.GetComplexData()->GetList();

    Variant v1 = plist->First(); plist->PopFront();

    PError::AssertType(v1, PEAT_FILESTREAM, "Argument error in first parameter of function [FilePrint_(<file-stream>, <text>)]: ");  

    counted_ptr<PEBLObjectBase> tmp2 = (v1.GetComplexData())->GetObject();
    PStream * mystream = dynamic_cast<PStream*>(tmp2.get());

    Variant v2 = plist->First(); plist->PopFront();
    mystream->WriteString(v2);
    return v2;
}

Variant PEBLStream::FileReadCharacter(Variant v)
{
    //v[1] should have the file stream 
    PList * plist = v.GetComplexData()->GetList();

    Variant v1 = plist->First(); plist->PopFront();

    PError::AssertType(v1, PEAT_FILESTREAM, "Argument error in function [FileReadCharacter(<file-stream>)]: ");   
    counted_ptr<PEBLObjectBase> tmp2 = (v1.GetComplexData())->GetObject();

    PStream * mystream = dynamic_cast<PStream*>(tmp2.get());
    char c = (mystream->ReadChar());
    return Variant((char)c);
}

Variant PEBLStream::FileReadWord(Variant v)
{
    //v[1] should have the file stream 
    PList * plist = v.GetComplexData()->GetList();

    Variant v1 = plist->First(); plist->PopFront();

    PError::AssertType(v1, PEAT_FILESTREAM, "Argument error in function [FileReadWord(<file-stream>)]: ");   

    counted_ptr<PEBLObjectBase> tmp2 = (v1.GetComplexData())->GetObject();
    PStream * mystream = dynamic_cast<PStream*>(tmp2.get());

    return Variant(mystream->ReadToken(' '));
}


//This takes a filestream and returns the next line.
Variant PEBLStream::FileReadLine(Variant v)
{
    PList * plist = v.GetComplexData()->GetList();
    //v[1] should have the file stream    
    Variant v1 = plist->First(); plist->PopFront();

    PError::AssertType(v1, PEAT_FILESTREAM, "Argument error in function [FileReadLine(<file-stream>)]: ");   
    counted_ptr<PEBLObjectBase> tmp2 = (v1.GetComplexData())->GetObject();
    PStream * mystream = dynamic_cast<PStream*>(tmp2.get());

    return Variant(mystream->ReadLineClean());
}




///This function takes a filename as an argument.  It
///Opens the file, and reads in each line of the file into a string,
///which it places in a list that it returns.  It closes the file afterward.
Variant PEBLStream::FileReadList(Variant v)
{

   //v[1] should have the filename
    PList * plist = v.GetComplexData()->GetList();

    Variant v1 = plist->First(); plist->PopFront();
    PError::AssertType(v1, PEAT_STRING, "Argument error in function [FileReadList(<filename>)]:  ");    
 
    //Search through the paths for the file, because it may be a 'special' file.
    string filename = Evaluator::gPath.FindFile(v1.GetString());
    
    if(filename == "")
        PError::SignalFatalError(string("Unable to find file [")  + v1.GetString() + string("]."));

    //It must be good, so open it.
    PStream *  mystream = new PStream(filename,sdRead, stASCII);
   


    PList * returnlist = new PList();
    std::string  tmpstring;
    while(!mystream->Eof())
        {
            tmpstring = mystream->ReadLineClean();

            if(strcmp("",tmpstring.c_str()) &&       //Ignore blank lines
               strncmp("#",tmpstring.c_str(),1)      //Ignore lines starting with #
               )
                {
                    returnlist->PushBack(tmpstring);
                }
        }
    mystream->Close();
    delete mystream;

    counted_ptr<PEBLObjectBase>  tmp2 = counted_ptr<PEBLObjectBase>(returnlist);
    PComplexData * pcd = new PComplexData(tmp2);
    Variant tmp3 = Variant(pcd);
    delete pcd;
    pcd=NULL;
    return tmp3;
}
    

///Give this function a filename, and it will read it into a list 
///of lists; each line is a list, and the (optional) token-separated elements
///are the items of the list.
Variant PEBLStream::FileReadTable(Variant v)
{
    //v[1] should have the file stream 
    PList * plist = v.GetComplexData()->GetList();
    Variant v1 = plist->First(); plist->PopFront();
    PError::AssertType(v1, PEAT_STRING, "Argument error in first parameter of function [FileReadTable(<list>)]:  ");    
     
    //Search through the paths for the file, because it may be a 'special' file.
    string filename = Evaluator::gPath.FindFile(v1.GetString());
    
    if(filename == "")
        PError::SignalFatalError(string("Unable to find file [")  +v1.GetString() + string("]."));

    //It must be good, so open it.
    PStream *   myStream = new PStream(filename,sdRead, stASCII);
    
    char separator;
    //See if there is another parameter; if there is, it is the token separator.
    if(plist->IsEmpty())
        {
            separator = ' ';
        }
    else
        {
            PError::AssertType(plist->First(), PEAT_STRING, "Argument error in second parameter of function [FileReadTable(<list>)]:  ");    
            std::string tmp = plist->First(); plist->PopFront();
            separator = tmp[0];
        }

    //Make an outer list to put everything in.

    PList * returnlist = new PList();

    //Make an inner list
    Variant innerlist;

    std::string tmpstring;

    while(!myStream->Eof())
        {

            tmpstring = myStream->ReadLineClean();
            if((strcmp("",tmpstring.c_str()) == 0) ||      //Ignore blank lines
               (strncmp("#",tmpstring.c_str(),1)==0)      //Ignore lines starting with #
               )
                {

                    //This line is garbage, so read it and throw it away.
                
                }
            else
                {
                    innerlist =  PEBLUtility::Tokenize(tmpstring.c_str(),separator);
                    returnlist->PushBack(innerlist);
                }
        }
    myStream->Close();
    delete myStream;
    counted_ptr<PEBLObjectBase> tmp2 =  counted_ptr<PEBLObjectBase>(returnlist);
    PComplexData * pcd = new PComplexData(tmp2);
    Variant tmp3 = Variant(pcd);
    delete pcd;
    pcd=NULL;
    return tmp3;

}


///This function takes a filename as an argument.  It
///Opens the file, and reads in the entire file as a string,
///which it  returns, and closes the file afterward. It ignores any
///lines that begin with #, and converts '\n' to [10], which
///is later parsed as a carriage return.
Variant PEBLStream::FileReadText(Variant v)
{

   //v[1] should have the filename
    PList * plist = v.GetComplexData()->GetList();
    Variant v1 = plist->First(); plist->PopFront();
    PError::AssertType(v1, PEAT_STRING, "Argument error in function [FileReadText(<filename>)]:  ");    
 
    //Search through the paths for the file, because it may be a 'special' file.
    string filename = Evaluator::gPath.FindFile(v1.GetString());
    
    if(filename == "")
        PError::SignalFatalError(string("Unable to find file [")  + v1.GetString() + string("]."));

    //It must be good, so open it.
    PStream * mystream = new PStream(filename,sdRead, stASCII);
   

    Variant returnText = "";
    std::string tmpstring;
    while(!mystream->Eof())
        {
            tmpstring = mystream->ReadLine();

            if( strncmp("#",tmpstring.c_str(),1)      //Ignore lines starting with #
               )
                {
                    //This is wrong--it will add extra space where it is not needed.
                    returnText = returnText +  Variant(tmpstring);
                }
        }
    mystream->Close();
    delete mystream;

    return returnText;
}
    


///This detects if you are at the end of a line
Variant PEBLStream::EndOfLine(Variant v)
{
   //v[1] should have the file stream 
    PList * plist = v.GetComplexData()->GetList();
    Variant v1 = plist->First(); plist->PopFront();

    PError::AssertType(v1, PEAT_FILESTREAM, "Argument error in function [EndOfLine(<file-stream>)]: ");   
    counted_ptr<PEBLObjectBase> tmp2 = (v1.GetComplexData())->GetObject();
    PStream * mystream = dynamic_cast<PStream*>(tmp2.get());
    return Variant(mystream->Eol());
}


///This detects if you are at the end of a file
Variant PEBLStream::EndOfFile(Variant v)
{
   //v[1] should have the file stream 
    PList * plist = v.GetComplexData()->GetList();
    Variant v1 = plist->First(); plist->PopFront();

    PError::AssertType(v1, PEAT_FILESTREAM, "Argument error in function [EndOfFile(<file-stream>)]: ");   
    counted_ptr<PEBLObjectBase> tmp2 = (v1.GetComplexData())->GetObject();
    PStream * mystream = dynamic_cast<PStream*>(tmp2.get());
    return Variant(mystream->Eof());
}



Variant PEBLStream::ConnectToIP(Variant v)
{
    //v[1] should have the IP Number as an integer
    //v[2] should have the port number

    PList * plist = v.GetComplexData()->GetList();
    Variant v1 = plist->First(); plist->PopFront();
    PError::AssertType(v1, PEAT_INTEGER, "Argument error in first parameter of function [ConnectToHost(<hostname>,<port>)]: ");

    Variant v2 = plist->First();
    PError::AssertType(v2, PEAT_INTEGER, "Argument error in second parameter of function [ConnectToHost(<hostname>,<port>)]: ");   

    
    counted_ptr<PEBLObjectBase> tmp2 = counted_ptr<PEBLObjectBase>(new PlatformNetwork());
    PlatformNetwork * mynet = dynamic_cast<PlatformNetwork*>(tmp2.get());

    mynet->Init();
    mynet->SetHostIP((long unsigned int)v1);
    mynet->SetPort((int)v2);
    mynet->Open();

    PComplexData * pcd = new PComplexData(tmp2);
    Variant tmp3 = Variant(pcd);
    delete pcd;
    pcd=NULL;
    return tmp3;
}

Variant PEBLStream::ConnectToHost(Variant v)
{

    //v[1] should have the host name
    //v[2] should have the port number
    PList * plist = v.GetComplexData()->GetList();
    Variant v1 = plist->First(); plist->PopFront();
    PError::AssertType(v1, PEAT_STRING, "Argument error in first parameter of function [ConnectToHost(<hostname>,<port>)]: ");

    Variant v2 = plist->First();
    PError::AssertType(v2, PEAT_INTEGER, "Argument error in second parameter of function [ConnectToHost(<hostname>,<port>)]: ");   
    
    
    counted_ptr<PEBLObjectBase> tmp2 = counted_ptr<PEBLObjectBase>(new PlatformNetwork());
    PlatformNetwork * mynet = dynamic_cast<PlatformNetwork*>(tmp2.get());

    mynet->Init();
    mynet->SetHostName(v1);
    mynet->SetPort((int)v2);
    mynet->Open();

    PComplexData * pcd = new PComplexData(tmp2);
    Variant tmp3 = Variant(pcd);
    delete pcd;
    pcd=NULL;
    return tmp3;



}



Variant PEBLStream::WaitForNetworkConnection(Variant v)
{
    //v[1] should have the port number
    PList * plist = v.GetComplexData()->GetList();
    Variant v1 = plist->First(); plist->PopFront();

    PError::AssertType(v1, PEAT_INTEGER, "Argument error in first parameter of function [WaitForNetworkConnection(<port>)]: ");

    
    counted_ptr<PEBLObjectBase> tmp2 = counted_ptr<PEBLObjectBase>(new PlatformNetwork());
    PlatformNetwork * mynet = dynamic_cast<PlatformNetwork*>(tmp2.get());
    mynet->Init();
    mynet->SetHostName("");
    mynet->SetPort((int)v1);
    mynet->Accept();

    PComplexData * pcd = new PComplexData(tmp2);
    Variant tmp3 = Variant(pcd);
    delete pcd;
    pcd=NULL;
    return tmp3;

}

Variant PEBLStream::CloseNetworkConnection(Variant v)
{
    //v[1] should have the network connection
    PList * plist = v.GetComplexData()->GetList();
    Variant v1 = plist->First(); plist->PopFront();
    PError::AssertType(v1, PEAT_NETWORKCONNECTION, "Argument error in function [CloseNetworkConnection(<network>)]: ");   

    counted_ptr<PEBLObjectBase> tmp2 = (v1.GetComplexData())->GetObject();
    PlatformNetwork * mynet = dynamic_cast<PlatformNetwork*>(tmp2.get());
    mynet->Close();

    return Variant(1);
    
}

Variant PEBLStream::SendData(Variant v)
{
    //v[1] should have the Network connection object
    //v[2] should have the data
    PList * plist = v.GetComplexData()->GetList();
    Variant v1 = plist->First(); plist->PopFront();
    PError::AssertType(v1, PEAT_NETWORKCONNECTION, "Argument error in first parameter of function [SendData(<network>,<data>)]: ");   
    counted_ptr<PEBLObjectBase> tmp2 = (v1.GetComplexData())->GetObject();
    PlatformNetwork * mynet = dynamic_cast<PlatformNetwork*>(tmp2.get());

    Variant v2 = plist->First();
    PError::AssertType(v2, PEAT_STRING, "Argument error in second parameter of function [SendData(<network>,<data>)]: ");   
    mynet->SendString(v2);
    return Variant(1);
}

Variant PEBLStream::GetData(Variant v)
{
    //v[1] should have the Network connection object
    //v[2] should have the max length of the data we are looking for.

    PList * plist = v.GetComplexData()->GetList();
    Variant v1 = plist->First(); plist->PopFront();
    PError::AssertType(v1, PEAT_NETWORKCONNECTION, "Argument error in first parameter of function [GetData(<network>,<size>)]: ");   
    counted_ptr<PEBLObjectBase> tmp2 = (v1.GetComplexData())->GetObject();
    PlatformNetwork * mynet = dynamic_cast<PlatformNetwork*>(tmp2.get());

    Variant v2 = plist->First();
    PError::AssertType(v2, PEAT_INTEGER, "Argument error in second parameter of function [GetData(<network>,<size>)]: ");   

    Variant ret = mynet->Receive(v2);
    return ret;

}




Variant PEBLStream::WritePNG(Variant v)
{
    //v[1] should have an object/window name.
    //v[2] should have a filename

    PList * plist = v.GetComplexData()->GetList();
    Variant v1 = plist->First(); plist->PopFront();
    PError::AssertType(v1, PEAT_STRING, "Argument error in first parameter of function [WritePNG(<filename>,<object>)]: ");   


    Variant v2 = plist->First();
    PError::AssertType(v2, PEAT_WIDGET, "Argument error in second parameter of function [WritePNG(<filename>,<object>)]: ");   
    counted_ptr<PEBLObjectBase> tmp2 = (v2.GetComplexData())->GetObject();
    PlatformWidget * myobj = dynamic_cast<PlatformWidget*>(tmp2.get());


    int result = SDLUtility::WritePNG(v1,myobj);

    if(result==0)
        {
            PError::SignalFatalError("Failed to write png file " + v2);
        }

    return Variant(1);
}
