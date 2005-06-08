//* -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*- */
/////////////////////////////////////////////////////////////////////////////////
//    Name:       src/base/Variant.h
//    Purpose:    Contains the Variant Class
//    Author:     Shane T. Mueller, Ph.D.
//    Copyright:  (c) 2003--2005 Shane T. Mueller <smueller@obereed.net>
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
#ifndef __VARIANT_H__
#define __VARIANT_H__

//#include "PComplexData.h"
#include <iostream>
#include "../utility/rc_ptrs.h"


class PComplexData;
class Variant;

enum VariantDataType { 
    P_DATA_UNDEFINED = 0,    // undefined, error 
    P_DATA_STACK_SIGNAL,     // an enum that signals stuff to the evaluator stack, for internal use only.
    P_DATA_FUNCTION,         // the name of a function.
    P_DATA_FUNCTION_POINTER, // A pointer to a function.  Used for compiled library functions.
    P_DATA_NUMBER_INTEGER,   // an integer
    P_DATA_NUMBER_FLOAT,     // a float
    P_DATA_STRING,           // a string of characters
    P_DATA_LOCALVARIABLE,    // a 'variable'; i.e. a char* symbolizing another piece of data.
    P_DATA_GLOBALVARIABLE,   // a 'variable'; i.e. a char* symbolizing another piece of data.
    P_DATA_COMPLEXDATA       // Any one of a number of complex data 'objects'.
};


enum StackSignalType {
    STACK_UNDEFINED=100,
    STACK_LIST_HEAD,
    STACK_RETURN_DUMMY,
    STACK_TERMINATE_EVENT_LOOP,
    STACK_BREAK
};


//Defines pFunc to be the function-pointer type
typedef  Variant(*pFunc)(Variant);

class Variant
{
public:
  
    Variant();
    ///Standard constructors
    Variant(const long int i);
    Variant(const long unsigned int i);
    Variant(const long double f);
    Variant(const char* string);
    Variant(const char character);
    Variant(const char* string, VariantDataType type);
    Variant(const StackSignalType);
    Variant(pFunc);  //This one takes a function-pointer as an argument.
    Variant(PComplexData * pcd);
    Variant(int i);
    Variant(double f);
    Variant(float f);
    Variant(bool b);
    Variant(const std::string  s);

    ///Standard Destructor
    ~Variant();


    ///Copy Constructor
    Variant(const Variant &v);
 
 
    //Overload the standard operators
    Variant operator + (const Variant & rhs) const;
    Variant operator - (const Variant & rhs) const;
    Variant operator * (const Variant & rhs) const;
    Variant operator / (const Variant & rhs) const;


    //Primitive Comparators
    bool Equal(const Variant & rhs) const;
    bool Less (const Variant & rhs) const;
  
    //Comparison Operators
    bool operator <  (const Variant & rhs) const;
    bool operator >  (const Variant & rhs) const;
    bool operator <= (const Variant & rhs) const;
    bool operator >= (const Variant & rhs) const;
    bool operator == (const Variant & rhs) const;
    bool operator != (const Variant & rhs) const;
 
    //Assignment Operators
    Variant operator = (const Variant & value);
    Variant operator = (const long double & value);
    Variant operator = (const long int & value);
    Variant operator = (const long unsigned int & value);
    Variant operator = (const int & value);
    Variant operator = (const double & value);
    Variant operator = (const float & value);
    Variant operator = (const char * value);
    Variant operator = (const std::string value);

    //Overload of the << operator
    friend std::ostream& operator<<(std::ostream& out, const Variant& v);

    /// Typecast Operators
    operator long double();
    operator long int();
    operator long unsigned int();
    operator int();
    operator const char*();
    operator const std::string() const;
    operator char*();
    operator bool();

    VariantDataType GetDataType() const;
    std::string GetDataTypeName() const;
  
    bool IsNumber() const;
    bool IsFloat() const;
    bool IsInteger() const;
    bool IsVariable() const;
    bool IsLocalVariable() const;
    bool IsGlobalVariable() const;
    bool IsString() const;
    bool IsFunction() const;
    bool IsFunctionPointer() const;
    bool IsComplexData() const;
    bool IsStackSignal() const;
  
    long int GetInteger() const;
    long double GetFloat() const;
    const char * GetVariableName() const;
    const char * GetFunctionName() const;
    const char * GetString() const;
    StackSignalType GetSignal()const;
    pFunc GetFunctionPointer() const;
    PComplexData* GetComplexData() const;

    void SetComplexData(PComplexData * data);      //Set and retrieve something in the complex data slot.


protected:
    void free_mData();
private:
  
    ///This is used as a pointer to a complex data
    ///object, including a list, a (tbd) matrix,
    ///image, (tbd)sound, window object, etc.
    /// The variant does not take care of cleaning up mComplexData
    /// itself automatically; this must be done explicitly
    PComplexData  * mComplexData;
    counted_ptr<PComplexData> mCD;
    VariantDataType  mDataType;          // number, string or array 

    union PValue {
        long int     iNumber; 
        long double  fNumber;      /* number */
        char       * String;
        char       * Variable;     /* The name of a variable */
        char       * Function;
        Variant   (*pFunction)(Variant);
        StackSignalType Signal;  /*A signal type used by Evaluator stack.*/
    } mData;


       
};


#endif
