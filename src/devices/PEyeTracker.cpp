//* -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*- */
/////////////////////////////////////////////////////////////////////////////////
//    Name:       src/devices/PEyeTracker.cpp
//    Purpose:    Class for handling gazelib eyetracker device
//                (TheEyeTribe eyetracker)
//    Author:     Shane T. Mueller, Ph.D.
//    Copyright:  (c) 2016 Shane T. Mueller <smueller@obereed.net>
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
//
//  This class is targeted to gazelib developed by theeyetribe, a $100 eyetracker.



#ifdef PEBL_GAZELIB

#include "PEyeTracker.h"
#include "../objects/PCustomObject.h"
#include "../base/PComplexData.h"
#include "../base/Variant.h"

//#include "../../../libs/tet-cpp-client-master/include/libs/gazeapi.h"

// --- MyGaze implementation
PEyeTracker::PEyeTracker()
{
  // Connect to the server in push mode on the default TCP port (6555)
  // open in pull_mode
    if( !m_api.connect( false ) )
    {
      //warning or error should be flagged here.
      
      // Enable GazeData notifications
      //m_api.add_listener( *this );
    }
}

PEyeTracker::~PEyeTracker()
{
  //m_api.remove_listener( *this );
    m_api.disconnect();
}

gtl::GazeData *  PEyeTracker::GetGazeFrame() 
{
  //This blocks until it gets the next gaze frame.
  gtl::GazeData *gd = new gtl::GazeData;
  m_api.get_frame(*gd);
 
//GazeData contains:
//enum tracking state
//.time=timestamp
//.fix ==is fixated
//.state = 32 bit state integer???
//.raw raw gaze coordinates in pixels
//.avg smoothed coordinates in pixels
//.lefteye data for left eye
//.righteye data for right eye


  return gd;
}


//This doesn't need to be a method.
//This creates a custom object containing the infromation in gd
 Variant PEyeTracker::ConvertGazeData(const gtl::GazeData* gd) const
{

  PCustomObject * po = new PCustomObject("gazedata");

  po->SetProperty("timestamp",gd->time);
  po->SetProperty("fix",gd->fix);
  po->SetProperty("state",gd->state);
  po->SetProperty("rawX",gd->raw.x);
  po->SetProperty("rawY",gd->raw.y);
  po->SetProperty("avgX",gd->avg.x);
  po->SetProperty("avgY",gd->avg.y);

  po->SetProperty("lefteyerawx",gd->lefteye.raw.x);
  po->SetProperty("lefteyerawy",gd->lefteye.raw.y);
  po->SetProperty("leftAvgX",gd->lefteye.avg.x);
  po->SetProperty("leftAvgY",gd->lefteye.avg.y);
  po->SetProperty("lefteyepsize",gd->lefteye.psize);
  po->SetProperty("lefteyecenterx",gd->lefteye.pcenter.x);
  po->SetProperty("lefteyecentery",gd->lefteye.pcenter.y);

  po->SetProperty("righteyerawx",gd->righteye.raw.x);
  po->SetProperty("righteyerawy",gd->righteye.raw.y);
  po->SetProperty("rightAvgX",gd->righteye.avg.x);
  po->SetProperty("rightAvgY",gd->righteye.avg.y);
  po->SetProperty("righteyepsize",gd->righteye.psize);
  po->SetProperty("righteyecenterx",gd->righteye.pcenter.x);
  po->SetProperty("righteyecentery",gd->righteye.pcenter.y);



  counted_ptr<PEBLObjectBase> tmpObject = counted_ptr<PEBLObjectBase>(po);
  PComplexData *  pcd = new PComplexData(tmpObject);
  Variant tmp = Variant(pcd);
  delete pcd;
  pcd=NULL;
  return tmp;
}



bool PEyeTracker::SetProperty(std::string name, Variant v)
{
    //We won't do any validation here.  Maybe in the future
    //some validation cuold be done here; allowing the user
    //to specify things like value type, or a subset of values.

    mProperties[name]=v;
    return true;
}


 ObjectValidationError PEyeTracker::ValidateProperty(std::string name, Variant v)const
{
    return ValidateProperty(name);
}

ObjectValidationError PEyeTracker::ValidateProperty(std::string name)const
{
   ObjectValidationError ove = PEBLObjectBase::ValidateProperty(name);
    if(ove == OVE_VALID)
        return ove;
    else
        return OVE_INVALID_PROPERTY_NAME;

}

 

#endif


