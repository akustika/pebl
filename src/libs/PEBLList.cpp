//* -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*- */
/////////////////////////////////////////////////////////////////////////////////
//    Name:       src/libs/PEBLList.cpp
//    Purpose:    List Processing Function Library for PEBL
//    Author:     Shane T. Mueller, Ph.D.
//    Copyright:  (c) 2003 Shane T. Mueller <smueller@umich.edu>
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
#include "PEBLList.h"
#include "../base/Variant.h"
#include "../base/PComplexData.h"
#include "../base/PList.h"

#include "../utility/PEBLUtility.h"
#include "../utility/PError.h"
#include "../utility/rc_ptrs.h"

#include <list>
#include <sstream>
#include <string>
#include <vector>

#include <iostream.h>

using std::ostream;
using std::cerr;
using std::endl;
using std::list;
using PEBLUtility::RandomUniform;
using std::string;


Variant PEBLList::Shuffle (Variant v)
{
    //v is a list.  v[1] should be have a list in it.
    counted_ptr<PList> plist = (v.GetComplexData())->GetList();
    Variant v1 = plist->First(); plist->PopFront();

    //v1 should be a list.
    PError::AssertType(v1, PEAT_LIST, "Argument error in function [Shuffled(<list>)]:  ");    


    // cout << "Name: " <<  (v1.GetComplexData())->GetTypeName() << endl;
                  
    counted_ptr<PList> dataList = v1.GetComplexData()->GetList();
    
    //Now, make a keylist of random numbers, the length of datalist.
    counted_ptr<PList> keyList = counted_ptr<PList>(new PList());
    for(unsigned int i = 0; i < dataList->Length(); i++)
        {
            keyList->PushFront(RandomUniform());
        }
    
    
    //Now, sort by the key list        
    counted_ptr<PList> newList = dataList->SortBy(*keyList);
    counted_ptr<PComplexData> PCD =counted_ptr<PComplexData>( new PComplexData(newList));
    
    return Variant(PCD);
            
  }


/// Repeat(value, number)
/// This function returns a list with <value> repeated <number> times
/// The expression is evaluated before it is repeated.
Variant PEBLList::Repeat (Variant v)
{
   //v is a list; v[1] is the object to repeat (can be anything)
    counted_ptr<PList> plist = (v.GetComplexData())->GetList();
    Variant v1 = plist->First(); plist->PopFront();


    //v[2] is the number of repeats: should be an integer.
    PError::AssertType(plist->First(), PEAT_INTEGER, "Argument error in second parameter of function [Repeat(<object>,<integer>)]:  ");    

    int number = plist->First(); plist->PopFront();


    counted_ptr<PList> returnList = counted_ptr<PList>(new PList());
    for(int i=0;i<number;i++)
        {
            returnList->PushBack(v1);
        }
    
    PComplexData * tmpPCD= new PComplexData(returnList);
    return Variant(tmpPCD);

}

/// This creates a list functionally, rather than syntactically using the [] operators.
Variant PEBLList::List(Variant v)
{
    return v;
}


/// RepeatList(list, n)
/// This creates a new list consisting of the original list 
/// repeated n times.
Variant PEBLList::RepeatList(Variant v)
{
   //v[1] should be a list.  Just extract the iterators.
    counted_ptr<PList> plist = (v.GetComplexData())->GetList();
    



    Variant v1 = plist->First(); plist->PopFront();
    PError::AssertType(v1, PEAT_LIST, "Argument error in first parameter of function [RepeatList(<list>, <int>)]:  ");    
    
    list<Variant>::iterator p;
    list<Variant>::iterator pstart = v1.GetComplexData()->GetList()->Begin();    
    list<Variant>::iterator pend   = v1.GetComplexData()->GetList()->End();
    
    
    //v[2] is the number of repeats: should be a number.
    PError::AssertType(plist->First(), PEAT_INTEGER, "Argument error in second parameter of function [RepeatList(<list>, <int>)]:  ");    
    int number = plist->First(); plist->PopFront();
    
    
    //There is now an iterator p, and and end to compare it to, and
    //an iterator to the pstart for resetting.
    //Make a new list to return.

    counted_ptr<PList> returnList = counted_ptr<PList>(new PList());
 
    for(int i=0; i<number; i++)
        {
            p=pstart;
            while (p != pend)
                {
                    returnList->PushBack(*p);
                    p++;
                }            
        }
    
    PComplexData * tmpPCD= new PComplexData(returnList);
    return Variant(tmpPCD);
}



/// Sequence constructs a sequence of numbers between the low and high, 
/// with step-size increments between.  Attempts to stay in integers when
/// the low and step are integers.

Variant PEBLList::Sequence(Variant v)
{
    //v is a list; v[1] is the bottom of the sequence
    counted_ptr<PList> plist = (v.GetComplexData())->GetList();
    PError::AssertType(plist->First(), PEAT_NUMBER, "Argument error in first parameter of function [Sequence(<first>, <last>, <step>)]");
    Variant start = plist->First(); plist->PopFront();

    //v[2] is the last number in the sequence
    PError::AssertType(plist->First(), PEAT_NUMBER, "Argument error in second parameter of function [Sequence(<first>, <last>, <step>)]:  ");    
    Variant end = plist->First(); plist->PopFront();

    //v[3] is the increment step of the sequence.
    PError::AssertType(plist->First(), PEAT_NUMBER, "Argument error in second parameter of function [Sequence(<first>, <last>, <step>)]:  ");    
    Variant step = plist->First(); plist->PopFront();


    //Make sure that the step is not equal to 0--we will never end if it is.
    if(step == Variant(0))
        {
            PError::SignalFatalError("Step size in Sequence(<start>, <end>, <step>) is 0.");
        }

    Variant tolerance = .00000001;

    counted_ptr<PList> returnList = counted_ptr<PList>(new PList());
    returnList->Clear();

    Variant current;

    //We need to operate differently if step is positive vs. negative.

    if(step > Variant(0))
        {
            //If step is positive, end better be greater than start.
            if(end < start)
                {
                    PError::SignalFatalError("For positive <step>s, <end> must be greater than <start> in [Sequence(<start>, <end>, <step>)]");
                }
            
            //Step is positive, continue while less-than end
            for(current = start; current <= end + tolerance; current = current + step)
                {
                    returnList->PushBack(current);
                }           
        }
    else
        {
            //If step is negative, end better be smaller than start.
            if(end > start)
                {
                    PError::SignalFatalError("For negative <step>s, <end> must be less than <start> in [Sequence(<start>, <end>, <step>)]");
                }

            //Step is negative, continue while greater-than end.
            for(current = start; current >= end - tolerance ; current = current + step)
                {
                    returnList->PushBack(current);
                }
            
            
        }

    
    PComplexData * tmpPCD= new PComplexData(returnList);
    return Variant(tmpPCD);  
}


/// RepeatExpression(<name_of_function>, <list_of_parameters>, <number>)
/// This function returns a list <number> long that is produced by the 
/// return value of <name_of_function>, evaluated with <list_of_parameters>
/// as parameters. <name_of_function> can be either a standard library function
/// or a user-defined function.
///  This is most useful for generating randomized
/// values, but can also be used to created complex designs by storing
/// global variables. 
Variant PEBLList::RepeatExpression (Variant v)
{
   //v[1] should be a list
    /*   counted_ptr<PList> plist = (v.GetComplexData())->GetList();
         Variant v1 = plist->First(); plist->PopFront();
         counted_ptr<PList> myList = v1.GetComplexData()->GetList();
    */

    PError::SignalFatalError("Function [RepeatExpression] not implemented");
    return Variant(true);
}



/// This takes two lists as parameters, and returns a nested
/// list of lists that includes the full counterbalancing of a and b.
/// Use cautiously; this gets mxn large
Variant PEBLList::DesignFullCounterbalance (Variant v)
{

    counted_ptr<PList> plist = (v.GetComplexData())->GetList();
    
    Variant v1 = plist->First(); plist->PopFront();
    //v[1] should be a list.  Just extract the iterators.    
    PError::AssertType(v1, PEAT_LIST, "Argument error in first parameter of function [DesignFullCounterbalance(<list>, <list>)]:  ");    
    list<Variant>::iterator p1 = v1.GetComplexData()->GetList()->Begin();
    list<Variant>::iterator p1end = v1.GetComplexData()->GetList()->End();
    


    Variant v2 = plist->First(); plist->PopFront();
    //v[1] should be a list.  Just extract the iterators.    
    PError::AssertType(v2, PEAT_LIST, "Argument error in second parameter of function [DesignFullCounterbalance(<list>, <list>)]:  ");    

    list<Variant>::iterator p2start = v2.GetComplexData()->GetList()->Begin();
    list<Variant>::iterator p2;
    list<Variant>::iterator p2end   = v2.GetComplexData()->GetList()->End();

    //There are now 2 list iterators: p1 and p2, and two ends to compare them to,
    //and an iterator to the p2start for resetting.
    //Make a new list to return.

    counted_ptr<PList> returnList = counted_ptr<PList>(new PList());
    counted_ptr<PList> tmpList;
    PComplexData * tmpPCD=NULL;
    Variant tmpVariant;

    while(p1 != p1end)
        {
            p2 = p2start;
            while (p2 != p2end)
                {
                    ///Make sublist with the pair in it.
                    tmpList = counted_ptr<PList>(new PList());
                    tmpList->PushFront(*p2);
                    tmpList->PushFront(*p1);

                    tmpPCD = new PComplexData(tmpList);
                    tmpVariant = Variant(tmpPCD);
                    
                    //Put the sublist in the outer list
                    returnList->PushBack(tmpVariant);
                    p2++;
                }            
            
            p1++;
        }
    
    tmpPCD= new PComplexData(returnList);
    return Variant(tmpPCD);
}


///This function takes a single list, and returns a list of
///all pairs, excluding the pairs that have two of the same item.
/// CrossFactorWithoutDuplicates([a,b,c]) = [[a,b],[a,c],[b,a],[b,c],[c,a],[c,b]]
/// To achieve the same effect but include the duplicates, use DesignFullCounterBalance(x,x)
Variant PEBLList::CrossFactorWithoutDuplicates(Variant v)
{
   //v[1] should be a list.  Just extract the iterators.
    counted_ptr<PList> plist = (v.GetComplexData())->GetList();

    Variant v1 = plist->First(); plist->PopFront();
    PError::AssertType(v1, PEAT_LIST, "Argument error in function [CrossFactorWithoutDuplicates(<list>)]:  ");    
    list<Variant>::iterator p1 = v1.GetComplexData()->GetList()->Begin();
    list<Variant>::iterator p2;
    list<Variant>::iterator pstart = p1;
    list<Variant>::iterator pend = v1.GetComplexData()->GetList()->End();

    //There are now 2 list iterators: p1 and p2,
    //and an iterator to the p2start for resetting.
    //Make a new list to return.

    counted_ptr<PList> returnList = counted_ptr<PList>(new PList());
    counted_ptr<PList> tmpList;
    PComplexData * tmpPCD = NULL;
    Variant tmpVariant;

    int i1=0;
    int i2=0;
    while(p1 != pend)
        {
            p2 = pstart;
            i2=0;
            while (p2 != pend)
                {
                    if(i1 != i2)
                        {
                            ///Make sublist with the pair in it.
                            tmpList = counted_ptr<PList>(new PList());
                            tmpList->PushFront(*p2);
                            tmpList->PushFront(*p1);

                            tmpPCD = new PComplexData(tmpList);
                            tmpVariant = Variant(tmpPCD);
                    
                            //Put the sublist in the outer list
                            returnList->PushBack(tmpVariant);
                        }
                    p2++;
                    i2++;
                }            
            
            p1++;
            i1++;
        }
    
    tmpPCD= new PComplexData(returnList);
    return Variant(tmpPCD);
}

Variant PEBLList::Rotate(Variant v)
{
   //v[1] should be a list.  Just extract the iterators.
    counted_ptr<PList> plist = (v.GetComplexData())->GetList();

    Variant v1 = plist->First(); plist->PopFront();
    PError::AssertType(v1, PEAT_LIST, "Argument error in first parameter of function [Rotate(<list>, <n>)]:  ");    

    Variant v2 = plist->First(); plist->PopFront();
    PError::AssertType(v2, PEAT_INTEGER, "Argument error in second parameter of function [Rotate(<list>, <n>)]:  ");    


    list<Variant>::iterator pi = v1.GetComplexData()->GetList()->Begin();
    list<Variant>::iterator pStart = pi;
    list<Variant>::iterator pListStart = pi;
    list<Variant>::iterator pEnd = v1.GetComplexData()->GetList()->End();


    //startpoint is the 0-based index of which item to start the new list with.
    int rotation = (int)v2;

    int length =  (v1.GetComplexData()->GetList()->Length());
        
    //We need to find a startpoint as a positive number between 0 and length.
    //The normal % and mod functions will not produce this.
    double remainder = (((double)rotation/length) - (rotation/length));

    //Adjust for negative remainders.
    if(remainder < 0) remainder += 1.0;
    if(remainder == 1.0) remainder =0;

    double startpoint =(remainder * length);

    //Move pListStart to the startpoint.
    for(int i = 0; i < startpoint; i++)
        {
            pListStart++;
        }
    
    //Make a new list, starting with pListStart, and moving to
    //the end, and then attaching pStart to pListStart.
    counted_ptr<PList> returnList = counted_ptr<PList>(new PList());



    PComplexData * tmpPCD = NULL;
    Variant tmpVariant;

    //Adjust the iterator to the start of the list.
    pi=pListStart;
    while(pi != pEnd)
        {
            
            //Put the item on the list
            returnList->PushBack(*pi);
            pi++;
        }
    
    pi=pStart;
    while(pi != pListStart)
        {
            
            //Put the item on the list
            returnList->PushBack(*pi);
            pi++;
        }
    
    
    tmpPCD= new PComplexData(returnList);
    return Variant(tmpPCD);

}

/// This returns the number of items in the list.
Variant PEBLList::Length (Variant v)
{
 
    counted_ptr<PList> plist = (v.GetComplexData())->GetList();

    //v[1] should be a list
    Variant v1 = plist->First(); plist->PopFront();
    PError::AssertType(v1, PEAT_LIST, "Argument error in function [Length(<list>)]:  ");    

    counted_ptr<PList> myList = v1.GetComplexData()->GetList();
    return Variant((long unsigned int)(myList->Length()));
}


/// This function returns the first variant in the PList
/// passed in as an argument.
Variant PEBLList::First (Variant v)
{
   //v[1] should be a list
    counted_ptr<PList> plist = (v.GetComplexData())->GetList();

    Variant v1 = plist->First(); plist->PopFront();
    PError::AssertType(v1, PEAT_LIST, "Argument error in function [First(<list>)]:  ");    

    counted_ptr<PList> myList = v1.GetComplexData()->GetList();
    return Variant(myList->First());
}


//This returns the nth element of the list, counting from 1.
//if it is longer than the list, it returns the last item.
Variant PEBLList::Nth (Variant v)
{
    counted_ptr<PList> plist = (v.GetComplexData())->GetList();

    //v[1] should be a list
    Variant v1 = plist->First(); plist->PopFront();
    PError::AssertType(v1, PEAT_LIST, "Argument error in first parameter of function [Nth(<list>, <integer>)]:  ");    
    counted_ptr<PList> myList = v1.GetComplexData()->GetList();

    //v[2] should be an integer
    PError::AssertType(plist->First(), PEAT_INTEGER, "Argument error in second parameter of function [Nth(<list>, <integer>)]:  ");    
    int n = plist->First(); plist->PopFront();
    return Variant(myList->Nth(n));
}


Variant PEBLList::Last(Variant v)
{
   //v[1] should be a list
    counted_ptr<PList> plist = (v.GetComplexData())->GetList();

    Variant v1 = plist->First(); plist->PopFront();
    PError::AssertType(v1, PEAT_LIST, "Argument error in function [Last(<list>)]:  ");    

    counted_ptr<PList> myList = v1.GetComplexData()->GetList();
    return Variant(myList->Last());
}

/// This takes two lists and returns a single list
///
Variant PEBLList::Merge (Variant v)
{
    counted_ptr<PList> plist = (v.GetComplexData())->GetList();
    
    Variant v1 = plist->First(); plist->PopFront();
    //v[1] should be a list.  Just extract the iterators.    
    PError::AssertType(v1, PEAT_LIST, "Argument error in first parameter of function [Merge(<list>, <list>)]:  ");    
    list<Variant>::iterator p1start = v1.GetComplexData()->GetList()->Begin();
    list<Variant>::iterator p1 = p1start;
    list<Variant>::iterator p1end = v1.GetComplexData()->GetList()->End();
    


    Variant v2 = plist->First(); plist->PopFront();
    //v[1] should be a list.  Just extract the iterators.    
    PError::AssertType(v2, PEAT_LIST, "Argument error in second parameter of function [Merge(<list>, <list>)]:  ");    

    list<Variant>::iterator p2start = v2.GetComplexData()->GetList()->Begin();
    list<Variant>::iterator p2 = p2start;
    list<Variant>::iterator p2end   = v2.GetComplexData()->GetList()->End();

    //There are now 2 list iterators: p1 and p2, and two ends to compare them to,
    //and an iterator to the p2start for resetting.
    //Make a new list to return.

    counted_ptr<PList> returnList = counted_ptr<PList>(new PList());

    PComplexData * tmpPCD=NULL;
    Variant tmpVariant;

    //Add the first list.
    while(p1 != p1end)
        {
            returnList->PushBack(*p1);
            p1++;
        }
    
    //Add the second list.
    while (p2 != p2end)
        {
            returnList->PushBack(*p2);
            p2++;
        }
    
    tmpPCD= new PComplexData(returnList);
    return Variant(tmpPCD);
}



/// This adds an element to a list
/// Given Merge([a,b,c],d), will return [a,b,c,d]
Variant PEBLList::Append (Variant v)
{

    counted_ptr<PList> plist = (v.GetComplexData())->GetList();
    
    Variant v1 = plist->First(); plist->PopFront();
    //v[1] should be a list.  Just extract the iterators.    
    PError::AssertType(v1, PEAT_LIST, "Argument error in first parameter of function [Append(<list>, <list>)]:  ");    

    list<Variant>::iterator p1 = v1.GetComplexData()->GetList()->Begin();
    list<Variant>::iterator p1end = v1.GetComplexData()->GetList()->End();
   
    Variant v2 = plist->First(); plist->PopFront();
    //v[2] can be anything.


    //Make a new list to return.
    counted_ptr<PList> returnList = counted_ptr<PList>(new PList());

    PComplexData * tmpPCD=NULL;
    Variant tmpVariant;

    //Add the first list.
    while(p1 != p1end)
        {
            returnList->PushBack(*p1);
            p1++;
        }
    
    //Append v2.
    returnList->PushBack(v2);

    tmpPCD= new PComplexData(returnList);
    return Variant(tmpPCD);
    
}



///This just sorts the list.  
Variant PEBLList::Sort (Variant v)
{
   //v[1] should be a list
    counted_ptr<PList> plist = (v.GetComplexData())->GetList();

    Variant v1 = plist->First(); plist->PopFront();
    PError::AssertType(v1, PEAT_LIST, "Argument error in function [Sort(<list>)]:  ");    
    
    counted_ptr<PList> dataList = v1.GetComplexData()->GetList();
    
    counted_ptr<PList> newList = dataList->SortBy(*dataList);
    PComplexData * PCD = new PComplexData(newList);
    return Variant(PCD);    
}


///This sorts the list by another list.
Variant PEBLList::SortBy (Variant v)
{
    //v[1] should be a list
    counted_ptr<PList> plist = (v.GetComplexData())->GetList();

    Variant v1 = plist->First(); plist->PopFront();
    PError::AssertType(v1, PEAT_LIST, "Argument error in first parameter of function [SortBy(<list>, <list>)]:  ");    

    counted_ptr<PList> dataList = v1.GetComplexData()->GetList();   


    //v[2] should be the keys which the list should be sorted by. 
    Variant v2 = plist->First(); plist->PopFront();
    PError::AssertType(v2, PEAT_LIST, "Argument error in second parameter of function [SortBy(<list>, <list>)]:  ");    
    counted_ptr<PList> keyList = v2.GetComplexData()->GetList();
    
    counted_ptr<PList> newList = dataList->SortBy(*keyList);
    PComplexData * PCD = new PComplexData(newList);
    return Variant(PCD);
}



Variant PEBLList::IsMember (Variant v)
{
    //v[1] should be a list
    counted_ptr<PList> plist = (v.GetComplexData())->GetList();

    //v[1] should be an item to check for membership.
    Variant v1 = plist->First(); plist->PopFront();


    Variant v2 = plist->First();    plist->PopFront();
    PError::AssertType(v2, PEAT_LIST, "Argument error in second parameter of function [IsMember(<list>, <item>)]:  ");    
    
    list<Variant>::iterator p = v2.GetComplexData()->GetList()->Begin();
    list<Variant>::iterator pEnd = v2.GetComplexData()->GetList()->End();

     
    while(p != pEnd)
        {
            if(*p == v1)
                return Variant(true);
            p++;
        }
    return Variant(false);
}

Variant PEBLList::RemoveDuplicates (Variant v)
{
   //v[1] should be a list
    /*    counted_ptr<PList> plist = (v.GetComplexData())->GetList();
    Variant v1 = plist->First(); plist->PopFront();
    counted_ptr<PList> myList = v1.GetComplexData()->GetList();
    */  
    PError::SignalFatalError("Function [RemoveDuplicates] not implemented");
    return Variant(true);
}

Variant PEBLList::MakeMap (Variant v)
{
   //v[1] should be a list
    /*    counted_ptr<PList> plist = (v.GetComplexData())->GetList();
    Variant v1 = plist->First(); plist->PopFront();
    counted_ptr<PList> myList = v1.GetComplexData()->GetList();
    */
    PError::SignalFatalError("Function [MakeMap] not implemented");
    return Variant(true);
}





/// v[1] MUST be a list of lists, and each of the sub-lists
/// must be of the same length.
Variant PEBLList::Transpose (Variant v)
{
   //v[1] should be a list
    
    counted_ptr<PList> plist = (v.GetComplexData())->GetList();
    Variant v1 = plist->First(); plist->PopFront();
    PError::AssertType(v1, PEAT_LIST, "Argument error in function [Transpose(<list-of-lists>)]:  ");    

    list<Variant>::iterator pstart = v1.GetComplexData()->GetList()->Begin();    
    list<Variant>::iterator p;
    list<Variant>::iterator pend   = v1.GetComplexData()->GetList()->End();

    unsigned int outerLength = v1.GetComplexData()->GetList()->Length();
    unsigned int innerLength=0;

    //Create a vector of iterators to elements of each sublist.
    std::vector<list<Variant>::iterator> listIterators(outerLength,pstart);

    p = pstart;

    for(unsigned int j = 0; j < outerLength; j++)
        {
            PError::AssertType(*p, PEAT_LIST, "Every item in Transpose(<list-of-lists>) must be a list. ");

            if(j == 0)
                {
                    innerLength = (*p).GetComplexData()->GetList()->Length();
                }
            else
                {
                    if((*p).GetComplexData()->GetList()->Length() != innerLength)
                        {
                            PError::SignalFatalError("All sublists must be of the same length in Transpose(<list-of-lists>).");
                        }
                }

            //assign the iterator to the first element of the sublist.
            listIterators[j] = (*p).GetComplexData()->GetList()->Begin();  
            p++;
        }



    //Now, everything is in the clear, so transpose.

    counted_ptr<PList> returnList = counted_ptr<PList>(new PList());
    counted_ptr<PList> tmpList;
    PComplexData * tmpPCD = NULL;
    Variant tmpVariant;

    for(unsigned int i = 0; i < innerLength; i++)
        {
            tmpList = counted_ptr<PList>(new PList());
         
            for(unsigned int j = 0; j < outerLength; j++)
                {
                    tmpList->PushBack(*listIterators[j]); //Grab the item from the list
                    listIterators[j]++;                   //iterate
                }
            //The first item of each list has been added to tmpList, so add
            //it to returnList.
            tmpPCD = new PComplexData(tmpList);
            tmpVariant = Variant(tmpPCD);
            returnList->PushBack(tmpVariant);
        }

    
    tmpPCD = new PComplexData(returnList);
    return Variant(tmpPCD);
}

/// This makes a list out of a sublist of a list.  Or something like that.
Variant PEBLList::SubList(Variant v)
{

  //v[1] should be a list.  Just extract the iterators.
    counted_ptr<PList> plist = (v.GetComplexData())->GetList();
    Variant v1 = plist->First(); plist->PopFront();
    PError::AssertType(v1, PEAT_LIST, "Argument error in first parameter of function [SubList(<list>, <int>, <int>)]:  ");    

    list<Variant>::iterator pstart = v1.GetComplexData()->GetList()->Begin();    
    list<Variant>::iterator p;
    list<Variant>::iterator pend   = v1.GetComplexData()->GetList()->End();


    PError::AssertType(plist->First(), PEAT_INTEGER, "Argument error in second parameter of function [SubList(<list>, <int>, <int>)]:  ");    
    int start = plist->First(); plist->PopFront();
       
    PError::AssertType(plist->First(), PEAT_INTEGER, "Argument error in third  parameter of function [SubList(<list>, <int>, <int>)]:  ");    
    int end   = plist->First(); plist->PopFront();
    

    //Check to see if everything is in bounds.
    if(start < 1 
       || end > (int)(v1.GetComplexData()->GetList()->Length())
       || start > end )
        {
            std::stringstream message;
            
            message << "[SubList] tried to extract items " << start << " to "  << end;
            message <<  " of a " <<  v1.GetComplexData()->GetList()->Length() << " item list.";
            
            std::string tmp;
            message >> tmp;
            PError::SignalFatalError(tmp);
        }



    //There is now an iterator p, and an end to compare it to, and
    //an iterator to the pstart for resetting.
    //Make a new list to return.

    counted_ptr<PList> returnList = counted_ptr<PList>(new PList());
    PComplexData * tmpPCD=0;
    Variant tmpVariant;
    
    //Start at the beginning of the list. Keep count; if the count is
    //between the two boundaries, add it to the list.
    p=pstart;
    int i = 0;
    while (p != pend)
        {
            i++;
            //If i is big enough, consider adding it to the list
            if(i>=start)
                if( i <=end)  //But only if it isn't too big
                    {
                        returnList->PushBack(*p);
                    }
                else         //If it is too big, get out of the while loop.
                    {   
                        break;
                    }
            p++;
        }
    
    tmpPCD= new PComplexData(returnList);
    return Variant(tmpPCD);
}



//This will remove the nth item from a list
Variant PEBLList::Remove(Variant v)
{

    PError::SignalFatalError("Function [Remove] not implemented");
    return Variant(1);
}

