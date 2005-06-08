//* -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*- */
/////////////////////////////////////////////////////////////////////////////////
//    Name:       src/base/Variant.cpp
//    Purpose:    Contains the Variant Class
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


#include "Variant.h"
#include "PComplexData.h"
#include "../utility/PEBLUtility.h"
#include "../utility/PError.h"

#include <iostream>
#include <sstream> 

#include <math.h>
#include <string>
#include <stdlib.h>

using std::cerr;
using std::cout;
using std::endl;
using std::flush;
using std::ostream;
using std::string;

//Constructor

Variant::Variant():
    mComplexData(NULL),
    mDataType(P_DATA_UNDEFINED)

{
    
    mData.iNumber = 0;
}


//Constructor
Variant::Variant(const long int i):
    mComplexData(NULL),
    mDataType(P_DATA_NUMBER_INTEGER)

{
    mData.iNumber = i;
      
}



//Constructor
Variant::Variant(const long unsigned int i):
    mComplexData(NULL),
    mDataType(P_DATA_NUMBER_INTEGER)
{
    mData.iNumber = static_cast<long int>(i);
      
}



//Constructor
Variant::Variant(const long double f):
    mComplexData(NULL),
    mDataType(P_DATA_NUMBER_FLOAT)
{
    mData.fNumber = f;
}


//String Constructor
Variant::Variant(const char *  mystring):
    mComplexData(NULL),
    mDataType(P_DATA_STRING)
{
    mData.String = strdup(mystring);
    if(!mData.String)
        PError::SignalFatalError("Failed to copy string.");
} 


//Character Constructor
Variant::Variant(const char character):
    mComplexData(NULL),
    mDataType(P_DATA_STRING)
{
    //Make a dummy string to place the character into.
    char * dummy = (char*)malloc(2*sizeof(char));
    dummy[0]=character;
    dummy[1]='\0';
    mData.String = dummy;

}

//standard string constructor
Variant::Variant(std::string  mystring):
    mComplexData(NULL),
    mDataType(P_DATA_STRING)
{
    const char* dummy = mystring.c_str();

    mData.String = strdup(dummy);

}


Variant::Variant(const char* mystring, VariantDataType type):
    mComplexData(NULL),
    mDataType(type)

{
    switch(type)
        {
        case P_DATA_FUNCTION:
            mData.Function= strdup(mystring); break;
        case P_DATA_STRING:
            mData.String= strdup(mystring); break;
        case P_DATA_LOCALVARIABLE:
        case P_DATA_GLOBALVARIABLE:
            mData.Variable= strdup(mystring); break;

        case P_DATA_UNDEFINED:
        case P_DATA_NUMBER_INTEGER:
        case P_DATA_NUMBER_FLOAT:
        case P_DATA_COMPLEXDATA:
        default:
            //If it isn't one of the above, change it into a string
            mDataType = P_DATA_STRING;
            mData.String = strdup(mystring);
            break;
        }
}

//Constructor
Variant::Variant(int i):
    mComplexData(NULL),
    mDataType(P_DATA_NUMBER_INTEGER)

{
    mData.iNumber = (long int)i;
  
}


Variant::Variant(PComplexData * pcd):
    mDataType(P_DATA_COMPLEXDATA)
{
    mComplexData = pcd;  
}


///This is an internal data type used by the stack evaluator.
Variant::Variant(const StackSignalType signal):
    mComplexData(NULL),
    mDataType(P_DATA_STACK_SIGNAL)

{
    mData.Signal = signal;
}


Variant::Variant(pFunc pfunc ):
    mComplexData(NULL),
    mDataType(P_DATA_FUNCTION_POINTER)

{
    mData.pFunction = pfunc;
}


//Constructor
Variant::Variant(double f):
    mComplexData(NULL),
    mDataType(P_DATA_NUMBER_FLOAT)

{
    mData.fNumber=(long double)f;
}


//Constructor
Variant::Variant(float f):
    mComplexData(NULL),
    mDataType(P_DATA_NUMBER_FLOAT)

{
    mData.fNumber = (long double)f;
      
}

//Constructor
Variant::Variant(bool b):
    mComplexData(NULL),
    mDataType(P_DATA_NUMBER_INTEGER)

{
    mData.iNumber = (long int)b;
}


///
/// Copy Constructor for variant
/// 

Variant::Variant(const Variant &v):
    mComplexData(NULL)
{
    //This should behave differently depending on what type of variant v is

    mDataType = v.GetDataType();
    switch(mDataType)
        {
	
        case P_DATA_NUMBER_INTEGER:  // an integer
            mData.iNumber = v.GetInteger();
            break;
	    
        case P_DATA_NUMBER_FLOAT:    // a float
            mData.fNumber = v.GetFloat();
            break;

        case P_DATA_STRING:
            mData.String = strdup(v.GetString());
            break;
	    
        case P_DATA_LOCALVARIABLE:        // a variable name    
        case P_DATA_GLOBALVARIABLE:        // a variable name    
            mData.Variable = strdup(v.GetVariableName());
            break;

        case P_DATA_FUNCTION:
            mData.Function = strdup(v.GetFunctionName());
            break;

        case P_DATA_FUNCTION_POINTER:
            mData.pFunction = v.GetFunctionPointer();
            break;

	
        case P_DATA_STACK_SIGNAL:
            mData.Signal = v.GetSignal();
            break;

            //This needs to  make a deep copy

        case P_DATA_COMPLEXDATA:
            {
                //First, retrieve the list from v.
                mComplexData  = new PComplexData(v.GetComplexData());
            }
            break;

        case P_DATA_UNDEFINED: // undefined, not an error 
            break;
        default:

            cerr << "Undefined Data Type in Variant copy constructor. Type: " << mDataType << endl;
            cerr << v << endl;
            PError::SignalFatalError("Undefined Data Type.");
        break;
    
        }
    
}



///
/// Standard destructor.  This should take care of cleaning
/// up after data subtypes that put stuff on the stack.
Variant::~Variant()
{
    free_mData();  
}


///This overloads the + operator for Variants.
///for strings, this concatenates them.
Variant Variant::operator +(const Variant & rhs) const
{
    long int i;
    long double f;

    if(this->IsInteger()  && rhs.IsInteger())
        {
            i = this->GetInteger() + rhs.GetInteger();
            return Variant(i);
        }
    else if (this->IsNumber() && rhs.IsNumber())
        {
            f = this->GetFloat() + rhs.GetFloat();
            return Variant(f);
        }
    else if (this->IsString() || rhs.IsString())
        {
            std::string  tmp1, tmp2;
            tmp1 = GetString();
            tmp2 = rhs.GetString();
            tmp1 += tmp2;
            return Variant(tmp1.c_str());
        }
    else
        //There should be an error emmitted here
        i=0;
    return Variant(i);

}


///This overloads the - operator for Variants
Variant Variant::operator -(const Variant & rhs) const
{
    long int i;
    long double f;

    if(this->IsInteger()  && rhs.IsInteger())
        {
            i = this->GetInteger() - rhs.GetInteger();
            return Variant(i);
        }
    else if (this->IsNumber() && rhs.IsNumber())
        {

            f = this->GetFloat() - rhs.GetFloat();
            return Variant(f);
        }
    else
        i=0;
    return Variant(i);

}




///This overloads the * operator for Variants
Variant Variant::operator *(const Variant & rhs) const
{
    long int i;
    long double f;

    if(this->IsInteger()  && rhs.IsInteger())
        {
            i = this->GetInteger() * rhs.GetInteger();
            return Variant(i);
        }
    else if (this->IsNumber() && rhs.IsNumber())
        {

            f = this->GetFloat() * rhs.GetFloat();
            return Variant(f);
        }
    else
        i=0;
    return Variant(i);

}



///This overloads the / operator for Variants
Variant Variant::operator /(const Variant & rhs) const
{
    long int i;
    long double f;

    if(this->IsNumber() && rhs.IsNumber())
        {
		  
            f = this->GetFloat() / rhs.GetFloat();
            return Variant(f);
        }
    else
        i=0;
    return Variant(i);

}




/// Primitive Compare Method
///
bool Variant::Equal(const Variant & rhs) const
{
    //If they are both integers, make equality be exact.
    //If one is a float, make equality be with some tolerance.
    
    if(this->IsInteger()  && rhs.IsInteger())
        {
            return (this->GetInteger() == rhs.GetInteger());
        }
    else if (this->IsNumber() && rhs.IsNumber())
        {
            return (fabs(this->GetFloat() - rhs.GetFloat()) < .00000000001);
        }
    else if (this->IsString() && rhs.IsString())
        { //If both are strings, compare them
	    
            //Get copies of the strings.
            const char * str1 = this->GetString();
            const char * str2 = rhs.GetString();
	    
            //strcmp returns 0 if they are identical, a number otherwise
            bool b = !strcmp(str1, str2);
            return b;
        }
    else if (this->IsStackSignal() && rhs.IsStackSignal())
        {
            return (this->GetSignal() == rhs.GetSignal());
        }
    return false;
}


///
/// Primitive Comparing Method
bool Variant::Less(const Variant & rhs) const
{

	if (this->IsNumber() && rhs.IsNumber())
		{
			return (fabs(this->GetFloat() <  rhs.GetFloat()));
		}
	else if (this->IsString() && rhs.IsString())
	    { //If both are strings, compare them
	    
            //Get copies of the strings.
            const char * str1 = this->GetString();
            const char * str2 = rhs.GetString();
	    
            //strcmp returns 0 if they are identical, a number otherwise
            bool b = (strcmp(str1, str2)<0);
            return b;
	    }
	else if (this->IsFunction() && rhs.IsFunction())
        {
                 //Get copies of the strings.
            const char * str1 = this->GetFunctionName();
            const char * str2 = rhs.GetFunctionName();
	    
            //strcmp returns 0 if they are identical, a number otherwise
            bool b = (strcmp(str1, str2)<0);
            return b;
  

        }
	    //This should be handled more elegantly.
	    return false;
}



//The following overloaded operators use the above
//::Equal() and ::Less() methods, and each other.
bool Variant::operator == ( const Variant & rhs) const
{ return Equal(rhs); } 



bool Variant::operator != ( const Variant & rhs) const
{ return ! ((*this) == rhs); }



bool Variant::operator < ( const Variant & rhs) const
{ return Less(rhs); }



bool Variant::operator > ( const Variant & rhs) const
{ return rhs < (*this); }



bool Variant::operator <= ( const Variant & rhs) const
{ return ! ((*this) > rhs); } 



bool Variant::operator >= ( const Variant & rhs) const
{ return rhs <= (*this); }





///
/// Assignment Operator (overloaded)
Variant Variant::operator = (const Variant & value)
{
    //First, clean up 'this' if it contains data on free store
    // (e.g., a Variable or a string)
    free_mData();
   
    mDataType=value.GetDataType();
    switch(mDataType)
        {    
        case P_DATA_NUMBER_INTEGER:  // an integer
            mData.iNumber = value.GetInteger();
            break;

        case P_DATA_NUMBER_FLOAT:    // a float
            mData.fNumber = value.GetFloat();
            break;    

        case P_DATA_STRING:
            mData.String = strdup(value.GetString());
            break;

        case P_DATA_LOCALVARIABLE:        // a char* variable name
        case P_DATA_GLOBALVARIABLE:        // a char* variable name
            mData.Variable = strdup(value.GetVariableName());
            break;
      
        case P_DATA_FUNCTION:
            mData.Function = strdup(value.GetFunctionName());
            break;

        case P_DATA_FUNCTION_POINTER:
            mData.pFunction = value.GetFunctionPointer();
            break;
      
        case P_DATA_STACK_SIGNAL:
            mData.Signal = value.GetSignal();
            break;
            
        case P_DATA_COMPLEXDATA:
            mComplexData = new PComplexData(value.GetComplexData());
            break;            

        case P_DATA_UNDEFINED: // undefined, error 
        default:
            PError::SignalFatalError( "Undefined Variant type in Variant::operator = (Variant).");
            break;
        }
    return (*this);
}

Variant Variant::operator = (const long double & value)
{
    //First, clean up 'this' if it contains data on free store
    // (e.g., a Variable or a string)
    free_mData();
  
    mDataType = P_DATA_NUMBER_FLOAT;
    mData.fNumber = value;
    return *this;
}


Variant Variant::operator = (const long int & value)
{
    //First, clean up 'this' if it contains data on free store
    // (e.g., a Variable or a string)
    free_mData();
   

    mDataType = P_DATA_NUMBER_INTEGER;
    mData.iNumber = value;
    return *this;
} 


Variant Variant::operator = (const long unsigned int & value)
{
    //First, clean up 'this' if it contains data on free store
    // (e.g., a Variable or a string)
    free_mData();
   

    mDataType = P_DATA_NUMBER_INTEGER;
    mData.iNumber = value;
    return *this;
} 


Variant Variant::operator = (const int & value)
{
    //First, clean up 'this' if it contains data on free store
    // (e.g., a Variable or a string)
    free_mData();
  
    mDataType = P_DATA_NUMBER_INTEGER;
    mData.iNumber = (long int)value;
    return *this;
} 

Variant Variant::operator = (const double & value)
{
    //First, clean up 'this' if it contains data on free store
    // (e.g., a Variable or a string)
    free_mData();
  
    mDataType = P_DATA_NUMBER_FLOAT;
    mData.fNumber = (long double)value;
    return *this;
}


Variant Variant::operator = (const float & value)
{
    //First, clean up 'this' if it contains data on free store
    // (e.g., a Variable or a string)
    free_mData();
    
    mDataType = P_DATA_NUMBER_FLOAT;
    mData.fNumber = (long double)value;
    return *this;
}




Variant Variant::operator = (const  char * value)
{
    //First, clean up 'this' if it contains data on free store
    // (e.g., a Variable or a string)
    free_mData();
    
    mDataType = P_DATA_STRING;
    mData.String = strdup(value);
    return *this;
}


    
Variant Variant::operator = (const  std::string  value)
{
    //First, clean up 'this' if it contains data on free store
    // (e.g., a Variable or a string)
    free_mData();
    
    mDataType = P_DATA_STRING;
    const char * dummy = string(value).c_str();
    mData.String = strdup(dummy);
    return *this;
}


///overload operator<<

ostream & operator << (ostream& out, const Variant& v)
{
	
    switch(v.GetDataType())
        {
	    
        case P_DATA_NUMBER_INTEGER:  // an integer
            out << v.GetInteger();
            break;
	    
        case P_DATA_NUMBER_FLOAT:    // a float
            out << v.GetFloat();
            break;
	    
        case P_DATA_STRING:          // a string
            out <<  v.GetString();
            break;

        case P_DATA_LOCALVARIABLE:        // a variable
        case P_DATA_GLOBALVARIABLE:        // a variable
            out << v.GetVariableName();
            break;  

        case P_DATA_FUNCTION:        // a function name
            out << v.GetFunctionName();
            break;

        case P_DATA_FUNCTION_POINTER:
            out << "Function Pointer" ;
            break;

        case P_DATA_COMPLEXDATA:
            {
                out << *( v.GetComplexData());
            }
            break;

        case P_DATA_STACK_SIGNAL:
            out << v.GetSignal();
            break;


        case P_DATA_UNDEFINED: // undefined, error 
        default:
            out << "Trying to print undefined data type in Variant::<<: " << v.GetDataType() << "name: " << v.GetDataTypeName() << endl ;
            break;
        }
    
    return out;
}


//Casting operators
Variant::operator long int()
{
    return GetInteger();
}

Variant::operator int()
{
    return static_cast<int>(GetInteger());
}

Variant::operator long unsigned int()
{
    return static_cast<long unsigned int>(GetInteger());
}



Variant::operator long double()
{
    return GetFloat();
}

Variant::operator const char* ()
{
    return GetString();
}


Variant::operator const std::string () const
{
    return string(GetString());
}

Variant::operator char* ()
{
    return strdup(GetString());
}


Variant::operator bool ()
{
    if((*this) == Variant((long int)0) ||
       (*this) == Variant((long double)0.0) ||
       (*this) == Variant("") ||
       (*this) == Variant("F") ||
       (*this) == Variant("FALSE")
       )
     
        return false;
    else
        return true;
}

///
///Data Accessors
///

///This returns the type as an enum
VariantDataType Variant::GetDataType() const
{
    return mDataType;
}

///This returns the type as a char*
std::string Variant::GetDataTypeName() const
{
    switch(mDataType)
        {
        case P_DATA_NUMBER_INTEGER:
            return "PEBL Integer Type";

        case P_DATA_NUMBER_FLOAT:
            return "PEBL Floating-Point Type";

        case P_DATA_STRING:
            return "PEBL String Type";

        case P_DATA_LOCALVARIABLE:
            return "PEBL Local Variable Type";

        case P_DATA_GLOBALVARIABLE:
            return "PEBL Global Variable Type";

        case P_DATA_FUNCTION:
            return "PEBL Function Type";
	
        case P_DATA_FUNCTION_POINTER:
            return "PEBL Function Pointer Type";

        case P_DATA_STACK_SIGNAL:
            return "PEBL Internal Stack Signal Type";

        case P_DATA_COMPLEXDATA:
            return "PEBL Complex data within Variant";
    
        case P_DATA_UNDEFINED:
        default:
            return "Undefined PEBL Variant Type";
        }
}


///This tests whether the Variant is a number (i.e., a float or an integer.)
bool Variant::IsNumber() const
{
    return ( mDataType == P_DATA_NUMBER_INTEGER ||
             mDataType == P_DATA_NUMBER_FLOAT); 
}


bool Variant::IsFloat() const
{
    return mDataType == P_DATA_NUMBER_FLOAT;
}

bool Variant::IsInteger() const
{
    return  mDataType == P_DATA_NUMBER_INTEGER;
    
}

bool Variant::IsString() const
{
    return mDataType == P_DATA_STRING;
}


bool Variant::IsVariable() const
{
    return( mDataType == P_DATA_LOCALVARIABLE || mDataType == P_DATA_GLOBALVARIABLE);
}

bool Variant::IsLocalVariable() const
{
    return  mDataType == P_DATA_LOCALVARIABLE;
}

bool Variant::IsGlobalVariable() const
{
    return  mDataType == P_DATA_GLOBALVARIABLE;
}


bool Variant::IsFunction() const
{
    return mDataType == P_DATA_FUNCTION;
}


bool Variant::IsFunctionPointer() const
{
    return mDataType == P_DATA_FUNCTION_POINTER;
}




bool Variant::IsComplexData() const
{
    return mDataType == P_DATA_COMPLEXDATA;
}

bool Variant::IsStackSignal() const
{
    return mDataType == P_DATA_STACK_SIGNAL;
}




long int Variant::GetInteger() const
{
    switch(mDataType)
        {
        case P_DATA_NUMBER_INTEGER: // an integer
            return mData.iNumber;
      
        case P_DATA_NUMBER_FLOAT:   // a float
            return (long int)mData.fNumber;

        case P_DATA_STRING:
            return strtol(mData.String,0,10);

        case P_DATA_STACK_SIGNAL:
        case P_DATA_LOCALVARIABLE:       //
        case P_DATA_GLOBALVARIABLE:       //
        case P_DATA_FUNCTION:       //
        case P_DATA_FUNCTION_POINTER:
        case P_DATA_UNDEFINED:      // undefined, error 
        default:
            PError::SignalWarning("Erroneous Data type in Variant::GetInteger(); returning 0");
            return (long int)0;
            break;
        }
 
}


long double Variant::GetFloat() const
{
    switch(mDataType)
        {
        case P_DATA_NUMBER_INTEGER: // an integer
            return (long double)mData.iNumber;
	
        case P_DATA_NUMBER_FLOAT:   // a float
            return mData.fNumber;

        case P_DATA_STRING:

            return PEBLUtility::StringToLongDouble(mData.String);
	
        case P_DATA_STACK_SIGNAL:
        case P_DATA_LOCALVARIABLE:
        case P_DATA_GLOBALVARIABLE:
        case P_DATA_FUNCTION:
        case P_DATA_FUNCTION_POINTER:
        case P_DATA_UNDEFINED:      // undefined, error 
        default:
            PError::SignalWarning("Erroneous Data type in Variant::GetFloat(); returning 0");
            return (long double)0;

        }
 
}




const char *  Variant::GetString() const
{

    switch(mDataType)
        {
        case P_DATA_NUMBER_INTEGER: // an integer
            {
                std::stringstream tmp;
                tmp << mData.iNumber;
                
                std::string tmpstring;
                tmp >> tmpstring;

                return tmpstring.c_str();
            }

        case P_DATA_NUMBER_FLOAT:   // a float
            {
                std::stringstream tmp;
                tmp << mData.fNumber;
                
                std::string tmpstring;
                tmp >> tmpstring;

                return tmpstring.c_str();

            }


        case P_DATA_STRING:
            return mData.String;
        case P_DATA_FUNCTION:
            return mData.Function;


        case P_DATA_LOCALVARIABLE:
        case P_DATA_GLOBALVARIABLE:
            return mData.Variable;

        case P_DATA_COMPLEXDATA:
            {
                 std::stringstream tmp;
                 tmp <<  GetComplexData();
                 std::string tmpstring;
                 tmp >> tmpstring;
                 return tmpstring.c_str();
            }
        	
        case P_DATA_STACK_SIGNAL:
        case P_DATA_FUNCTION_POINTER:
    
        case P_DATA_UNDEFINED:      // undefined, error 
        default:
            cout << mDataType << endl;
            PError::SignalWarning("Erroneous Data type in Variant::GetString");
            return "";

        }
 

}


//This returns a pointer to the name of the variable.
const char *  Variant::GetVariableName() const
{

    if( mDataType == P_DATA_LOCALVARIABLE || mDataType == P_DATA_GLOBALVARIABLE)
        {
            return mData.Variable;
        }
    else
        {
            
            PError::SignalFatalError("Erroneous Data type in Variant::GetVariableName()");
            return NULL;

        }
}



//This returns a pointer to the name of the function.
const char *  Variant::GetFunctionName() const
{

    if( mDataType == P_DATA_FUNCTION)
        {
            return mData.Function;
        }
    else
        {

            PError::SignalFatalError("Erroneous Data type in Variant::GetFunctionName()");
            return NULL;
        }
}


//This returns a pointer to the name of the function.
StackSignalType  Variant::GetSignal() const
{

    if( mDataType == P_DATA_STACK_SIGNAL)
        {
            return mData.Signal;
        }
    else
        {
            return STACK_UNDEFINED;
        }
}



//This returns a pointer to the name of the function.
pFunc Variant::GetFunctionPointer() const
{

    if( mDataType == P_DATA_FUNCTION_POINTER)
        {
            return mData.pFunction;
        }
    else
        {
            return NULL;
        }
}






/// This will return a pointer to the complex data
/// held within the variant.
PComplexData * Variant::GetComplexData() const
{
    if(mDataType == P_DATA_COMPLEXDATA)
        return mComplexData;
    else 
        return 0;
}



/// This sets the complex data type to the argument.
/// It does not delete the complex data currently held
/// in the pointer.
void Variant::SetComplexData(PComplexData* data)
{
    mComplexData = data;
}



///This method just clears out any part of mData
///That is on the free store, including any PComplexData that is 
///held by the variant.  PCDs are 1-1 with variants; they should not be shared
/// by multiple variants, although the data they reference is ref-counted and may be shared.
void Variant::free_mData()
{

    
    if(mDataType == P_DATA_STRING )
        {
            if(mData.String)
                {
                    free(mData.String);
                    mData.String = NULL;
                }
        }
    else if(IsVariable())
        {
            if(mData.Variable)
                {
                    free(mData.Variable);
                    mData.Variable = NULL;
                }
        }
    else if(mDataType == P_DATA_FUNCTION)
        {
            if(mData.Function)
                {
                    free(mData.Function);
                    mData.Function = NULL;
                }
        }

    else if(mDataType == P_DATA_COMPLEXDATA)
        {
            if(mComplexData)
                {
                    
                    delete mComplexData;
                    mComplexData = NULL;
                }
        }

    //    mDataType = P_DATA_UNDEFINED;
}
