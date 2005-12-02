//* -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*- */
/////////////////////////////////////////////////////////////////////////////////
//    Name:       src/base/PList.h
//    Purpose:    Contains declaration for the list structure.
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
#ifndef __PLIST_H__
#define __PLIST_H__

#include "Variant.h"
#include "../utility/rc_ptrs.h"
#include "PEBLObject.h"

#include <list>
#include <iostream>


class Variant;

/// This class is a simple list
/// of Variants.  It is implemented as an STL list, but
/// does not currently expose all of the STL list methods.
class PList:  public PEBLObjectBase
{

public:
  
    PList();
    virtual ~PList();
  
    ///Copy Constructor
    PList(PList & list);
  
    ///Makes and returns a deep copy
    virtual PList * Clone();

    std::list<Variant>::const_iterator  Begin() const;
    std::list<Variant>::const_iterator  End() const; 

    std::list<Variant>::iterator  Begin();
    std::list<Variant>::iterator  End() ; 

    //    std::list<Variant>::iterator  GetNext(std::list<Variant>::iterator i){return i->next(); }
    //    std::list<Variant>::iterator  GetPrev(std::list<Variant>::iterator i){return i->previous(); }
    void PushFront(const Variant & v);
    void PopFront();
    void PushBack(const Variant & v);
    void PopBack();


    bool IsEmpty(){return mList.empty();};
    void Remove(Variant v){mList.remove(v);};
    void Clear(){mList.clear();};

    Variant First();
    Variant Rest();
    Variant Nth(unsigned int n);
    Variant Last();
    counted_ptr<PList> SortBy(const PList & key);

    unsigned int Length(){return mList.size();}

    bool IsMember(Variant v);


    std::list<Variant> * GetList();
    
    //Overload of the << operator
    friend std::ostream & operator <<(std::ostream & out, const PList & pcd );



protected:   
    std::ostream & SendToStream(std::ostream& out) const;

private:
    std::list<Variant> mList;
};


#endif
