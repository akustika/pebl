//* -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*- */
/////////////////////////////////////////////////////////////////////////////////
//    Name:       src/libs/PEBLMATH.cpp
//    Purpose:    Built-in math functions for PEBL
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
#include "PEBLMath.h"
#include "../base/Variant.h"
#include "../base/PList.h"
#include "../base/PComplexData.h"
#include "../utility/PEBLUtility.h"
#include "../utility/PError.h"

#include <stdlib.h>          //Used for random numbers
#include <math.h>
#include <list>
#include <string>
#include <strstream>

using std::string;

//Putatively precise to 50 digits:
#define PI 3.141592653589793238462643383279502884197169399375
#define E  2.718281828459045235360287471352662497757247093700

Variant PEBLMath::Recurse(Variant v, Variant (*funcname)(Variant))
{

    //If this function is called, v is a list of elements.
    //We should call the function on each element of the list, creating 
    //a list of the results, turn this into a variant, and return it.

    //Get the list of variants.
    counted_ptr<PList> plist = (v.GetComplexData())->GetList();

    //Make a results list
    counted_ptr<PList> resultslist = counted_ptr<PList>(new PList());
    
    //Declare a temporary argument list.
    counted_ptr<PList> arglist = counted_ptr<PList>(new PList());
   
    //Now, apply 
    std::list<Variant>::iterator p = plist->Begin();
    
    while(p != plist->End())
        {
            //Not sure why I add and then subtract the item from the list.
            arglist->PushFront(*p);                              
            resultslist->PushBack(funcname(*p));
            arglist->PopFront();
            p++;
        }

    //Now, resultslist is a PList.  Put it into a PCD.
    PComplexData * pcd = new PComplexData(resultslist); 
    
    return Variant(pcd);
}


//This is like the recurse above, but is used when there are other arguments
//of interest, such as logn() or round()
Variant PEBLMath::Recurse2(Variant v, Variant (*funcname)(Variant), Variant argument)
{

    //If this function is called, v is a list of elements.
    //We should call the function on each element of the list, creating 
    //a list of the results, turn this into a variant, and return it.

    //Get the list of variants.
    counted_ptr<PList> plist = (v.GetComplexData())->GetList();

    //Make a results list
    counted_ptr<PList> resultslist = counted_ptr<PList>(new PList());
    
   
    //Now, apply 
    std::list<Variant>::iterator p = plist->Begin();

    //Add the argument onto arglist.  argument should be a list of variants.
    //Declare an temporary argument list.
    counted_ptr<PList> arglist = argument.GetComplexData()->GetList();
    PComplexData *pcd;
    while(p != plist->End())
        {
            arglist->PushFront(*p);                          //Add the critical argument 
            pcd = new PComplexData(arglist);
            resultslist->PushBack(funcname(Variant(pcd)));        //Execute
            arglist->PopFront();                             //Pop of argument to move to next one.
            p++;
        }

    //Now, resultslist is a PList.  Put it into a PCD.
    pcd = new PComplexData(resultslist); 

    return Variant(pcd);
}



//Logarithmic Functions
Variant PEBLMath::Log10(Variant v)
{
    counted_ptr<PList> plist = (v.GetComplexData())->GetList();
    Variant v1 = plist->First();
    if(v1.IsNumber())
        {
            return Variant(log10l(v1.GetFloat()));
        }
    else if(v1.GetComplexData()->IsList())
        {
            return Recurse(v, Log10);

        }
    else
        {
            PError::SignalFatalError("Non-numeric argument in Log10");
        }

    return 0;
};

Variant PEBLMath::Log2(Variant v)
{
    counted_ptr<PList> plist = (v.GetComplexData())->GetList();
    Variant v1 = plist->First();
    if(v1.IsNumber())
        {
            return Variant(PEBLUtility::Log2(v1.GetFloat()));
        }
    else if(v1.GetComplexData()->IsList())
        {
            return Recurse(v, Log2);

        }
    else
        {
            PError::SignalFatalError("Non-numeric argument in Log2");
            return 0;
        }

};

Variant PEBLMath::Ln(Variant v)
{
    counted_ptr<PList> plist = (v.GetComplexData())->GetList();
    Variant v1 = plist->First();
    if(v1.IsNumber())
        {
            return Variant(logl(v1.GetFloat()));
        }
    else if(v1.GetComplexData()->IsList())
        {
            return Recurse(v, Ln);

        }
    else
        {
        
            PError::SignalFatalError("Non-numeric argument in Ln");
            return 0;
        }

};


Variant PEBLMath::LogN(Variant v)
{
    //This has two arguments; the number and the base.
    counted_ptr<PList> plist = (v.GetComplexData())->GetList();
    Variant number = plist->First(); plist->PopFront();

    //Don't get the second argument right away--if the first argument is
    //a list, we should just pass it along to the recurse2 function.
    
    if(number.IsNumber())
        {                  
            Variant base = plist->First(); plist->PopFront();   //Get the base argument
            return Variant(logl(number.GetFloat())/ logl(base.GetFloat()));
        }
    else if(number.GetComplexData()->IsList())
        {
            PComplexData * pcd = new PComplexData(plist);
            Variant args = Variant(pcd);
            Variant retval = Recurse2(number, LogN, args);
            delete pcd;
            return retval;
        }
    else
        {
            PError::SignalFatalError("Non-numeric argument in LogN");
            return 0;
        }
}


Variant PEBLMath::Exp(Variant v)
{
    counted_ptr<PList> plist = (v.GetComplexData())->GetList();
    Variant v1 = plist->First();
    if(v1.IsNumber())
        {
            return Variant(expl(v1.GetFloat()));
        }
    else if(v1.GetComplexData()->IsList())
        {
            return Recurse(v, Exp);

        }
    else
        {

            PError::SignalFatalError("Non-numeric argument in Exp");
            return 0;
        }

};


Variant PEBLMath::Pow(Variant v)
{
    //This has two arguments; the number and the base.
    counted_ptr<PList> plist = (v.GetComplexData())->GetList();
    Variant base = plist->First(); plist->PopFront();

    //Don't get the second argument right away--if the first argument is
    //a list, we should just pass it along to the recurse2 function.
    
    if(base.IsNumber())
        {                  
            Variant power = plist->First(); plist->PopFront();   //Get the base argument
            return powl(base, power);
        }
    else if(base.GetComplexData()->IsList())
        {
            PComplexData * pcd = new PComplexData(plist);
            Variant args = Variant(pcd);
            Variant retval = Recurse2(base, Pow, args);
            delete pcd;
            return retval;
        }
    else
        {
            PError::SignalFatalError("Non-numeric argument in Pow");
            return 0;
        }
}

Variant PEBLMath::Sqrt(Variant v)
{
    counted_ptr<PList> plist = (v.GetComplexData())->GetList();
    Variant v1 = plist->First();
    if(v1.IsNumber())
        {
            return Variant(sqrtl(v1.GetFloat()));
        }
    else if(v1.GetComplexData()->IsList())
        {
            return Recurse(v, Sqrt);

        }
    else
        {
            PError::SignalFatalError("Non-numeric argument in Sqrt");
            return 0;
        }

};


Variant PEBLMath::NthRoot(Variant v)
{
    //This has two arguments; the number and the root.
    counted_ptr<PList> plist = (v.GetComplexData())->GetList();
    Variant number = plist->First(); plist->PopFront();

    //Don't get the second argument right away--if the first argument is
    //a list, we should just pass it along to the recurse2 function.
    
    if(number.IsNumber())
        {                  
            Variant root = plist->First(); plist->PopFront();   //Get the base argument
            return powl(number, 1 / root.GetFloat());
        }
    else if(number.GetComplexData()->IsList())
        {
            PComplexData * pcd = new PComplexData(plist);
            Variant args = Variant(pcd);
            Variant retval = Recurse2(number, NthRoot, args);
            delete pcd;
            return retval;

            
        }
    else
        {

            PError::SignalFatalError("Non-numeric argument in NthRoot");
            return 0;
        }
}



    //Trigonometric Functions.


Variant PEBLMath::Tan(Variant v)
{
    counted_ptr<PList> plist = (v.GetComplexData())->GetList();
    Variant v1 = plist->First();
    if(v1.IsNumber())
        {
            return Variant(tanl(v1.GetFloat()));
        }
    else if(v1.GetComplexData()->IsList())
        {
            return Recurse(v, Tan);

        }
    else
        {
            PError::SignalFatalError("Non-numeric argument in Tan");

            return 0;
        }

};



///Sin takes one parameter
Variant PEBLMath::Sin(Variant v)
{
    counted_ptr<PList> plist = (v.GetComplexData())->GetList();
    Variant v1 = plist->First();
    if(v1.IsNumber())
        {
            return Variant(sinl(v1.GetFloat()));
        }
    else if(v1.GetComplexData()->IsList())
        {
            return Recurse(v, Sin);

        }
    else
        {
            PError::SignalFatalError("Non-numeric argument in [Sin]");

            return 0;
        }
};


Variant PEBLMath::Cos(Variant v)
{
    counted_ptr<PList> plist = (v.GetComplexData())->GetList();
    Variant v1 = plist->First();
    if(v1.IsNumber())
        {
            return Variant(cosl(v1.GetFloat()));
        }
    else if(v1.GetComplexData()->IsList())
        {
            return Recurse(v, Cos);
        }
    else
        {

            PError::SignalFatalError("Non-numeric argument in [Cos]");
            return 0;
        }
};


Variant PEBLMath::ATan(Variant v)
{
    counted_ptr<PList> plist = (v.GetComplexData())->GetList();
    Variant v1 = plist->First();
    if(v1.IsNumber())
        {
            return Variant(atan(v1.GetFloat()));
        }
    else if(v1.GetComplexData()->IsList())
        {
            return Recurse(v, ATan);

        }
    else
        {
        
            PError::SignalFatalError("Non-numeric argument in [ATan]");
            return 0;
        }
};

Variant PEBLMath::ASin(Variant v)
{
    counted_ptr<PList> plist = (v.GetComplexData())->GetList();
    Variant v1 = plist->First();
    if(v1.IsNumber())
        {
            return Variant(asinl(v1.GetFloat()));
        }
    else if(v1.GetComplexData()->IsList())
        {
            return Recurse(v, ASin);

        }
    else
        {
            PError::SignalFatalError("Non-numeric argument in [ASin]");
            return 0;
        }
};

Variant PEBLMath::ACos(Variant v)
{   
    counted_ptr<PList> plist = (v.GetComplexData())->GetList();
    Variant v1 = plist->First();
    if(v1.IsNumber())
        {
            return Variant(acosl(v1.GetFloat()));
        }
    else if(v1.GetComplexData()->IsList())
        {
            return Recurse(v, ACos);

        }
    else
        {
            PError::SignalFatalError("Non-numeric argument in [ACos]");
            return 0;
        }
};


//Converts radians to degrees.  Does not truncate at 180.
Variant PEBLMath::DegToRad(Variant v)
{
    counted_ptr<PList> plist = (v.GetComplexData())->GetList();
    Variant v1 = plist->First(); plist->PopFront();

    if(v1.IsNumber())
        {
            return Variant(v1.GetFloat() * 360 / (2*PI));
        }
    else if(v1.GetComplexData()->IsList())
        {
            return Recurse(v, ASin);

        }
    else
        {
            PError::SignalFatalError("Non-numeric argument in [DegToRad]");
            return 0;
        }

  
}


Variant PEBLMath::RadToDeg(Variant v)
{
    
    counted_ptr<PList> plist = (v.GetComplexData())->GetList();
    Variant v1 = plist->First(); plist->PopFront();

    if(v1.IsNumber())
        {
            return Variant(v1.GetFloat() / 360 * (2 * PI));
        }
    else if(v1.GetComplexData()->IsList())
        {
            return Recurse(v, ASin);

        }
    else
        {
            PError::SignalFatalError("Non-numeric argument in [RadToDeg]");
            return 0;
        }
}


//Rounding Functions. Most of these operate on a single number, rounding to the nearest integer.
Variant PEBLMath::Round(Variant v)
{
    counted_ptr<PList> plist = (v.GetComplexData())->GetList();
    Variant v1 = plist->First();
    if(v1.IsNumber())
        {
            return Variant(PEBLUtility::Round(v1.GetFloat()));
        }
    else if(v1.GetComplexData()->IsList())
        {
            return Recurse(v, Round);

        }
    else
        {
            PError::SignalFatalError("Non-numeric argument in [Round]");
            return 0;
        }
}


Variant PEBLMath::Floor(Variant v)
{
    counted_ptr<PList> plist = (v.GetComplexData())->GetList();
    Variant v1 = plist->First();
    if(v1.IsNumber())
        {
            return Variant((long int)(floorl(v1.GetFloat())));
        }
    else if(v1.GetComplexData()->IsList())
        {
            return Recurse(v, Floor);

        }
    else
        {
            PError::SignalFatalError("Non-numeric argument in [Floor]");
            return 0;
        }
}


Variant PEBLMath::Ceiling(Variant v)
{
    counted_ptr<PList> plist = (v.GetComplexData())->GetList();
    Variant v1 = plist->First();
    if(v1.IsNumber())
        {
            return Variant((long int)(ceill(v1.GetFloat())));
        }
    else if(v1.GetComplexData()->IsList())
        {
            return Recurse(v, Ceiling);

        }
    else
        {
            PError::SignalFatalError("Non-numeric argument in [Ceiling]");
            return 0;
        }
}

Variant PEBLMath::AbsFloor(Variant v)
{

    counted_ptr<PList> plist = (v.GetComplexData())->GetList();
    Variant v1 = plist->First();
    if(v1.IsNumber())
        {
            return Variant(PEBLUtility::Truncate(v1.GetFloat()));
        }
    else if(v1.GetComplexData()->IsList())
        {
            return Recurse(v, AbsFloor);

        }
    else
        {
            PError::SignalFatalError("Non-numeric argument in [AbsFloor]");
            return 0;
        }
    
}



//Modular Arithmetic:  This will even work for non-integers.
Variant PEBLMath::Mod(Variant v)
{
 
    counted_ptr<PList> plist = (v.GetComplexData())->GetList();

    
    PError::AssertType( plist->First(), PEAT_NUMBER, "Argument error in first parameter of Mod(<number>,<number>)");
    long int v1 = plist->First(); plist->PopFront(); 


    PError::AssertType( plist->First(), PEAT_NUMBER, "Argument error in second parameter of Mod(<number>,<number>)");
    long int v2 = plist->First(); plist->PopFront(); 

 
    double remainder =((double)v1/v2 - (v1/v2)); 
    if( remainder < 0 ) remainder += 1.0;
    if(remainder >= 1.0) remainder = 0;
    
    return Variant(remainder *  v2);
}



//Modular Arithmetic
Variant PEBLMath::Div(Variant v)
{
    PError::SignalFatalError("Function [Div] Not implemented.");
    return Variant(0);
}


//Coercion
Variant PEBLMath::ToInt(Variant v)
{
    
    return Variant(v.GetInteger());
}

Variant PEBLMath::ToFloat(Variant v)
{
    return Variant(v.GetFloat());
}

Variant PEBLMath::ToString(Variant v)
{
    return Variant(v.GetString());
}


Variant PEBLMath::ToNumber(Variant v)
{
    counted_ptr<PList> plist = (v.GetComplexData())->GetList();
    Variant v1 = plist->First();
    
    //If v is a string, then turn it either into an integer or a float,
    //depending on whether there is a '.' in it.
    
    if(v1.IsString())
        {
            bool hasPoint = false;
            
            const char* tmp = v.GetString();
            int i = 0;
            
            while(tmp[i] != '\0' && hasPoint == false)
                {
                    if(tmp[i] == '.')
                        hasPoint = true;
                    i++;
                }
            
            if(hasPoint)
                {
                    return Variant(v1.GetFloat());
                }
            else
                {
                    return Variant(v1.GetInteger());
                }
                     
        }
    
   return Variant(v1.GetFloat());
}

//Other
Variant PEBLMath::Sign(Variant v)
{

    counted_ptr<PList> plist = (v.GetComplexData())->GetList();
    Variant v1 = plist->First();
    if(v1.IsNumber())
        {
            return (v1.GetFloat()<0)? -1: 1;
        }
    else if(v1.GetComplexData()->IsList())
        {
            return Recurse(v, Sign);

        }
    else
        {
            PError::SignalFatalError("Non-numeric argument in Function [Sign]");
            return 0;
        }
    
}




Variant PEBLMath::Abs(Variant v)
{

    counted_ptr<PList> plist = (v.GetComplexData())->GetList();
    Variant v1 = plist->First();
    if(v1.IsNumber())
        {
            return Variant(fabsl(v1.GetFloat()));
        }
    else if(v1.GetComplexData()->IsList())
        {
            return Recurse(v, Abs);

        }
    else
        {
            PError::SignalFatalError("Non-numeric argument in Function [AbsFloor]");
            return 0;
        }
    
}



//Statistical (operates on a list; ignores non-numeric elements.)
Variant PEBLMath::Mean(Variant v)
{
   PError::SignalFatalError("Function [Mean] Not implemented."); 
   return Variant(0);
}

Variant PEBLMath::Min(Variant v)
{
    counted_ptr<PList> plist = (v.GetComplexData())->GetList();
    if(plist->First().IsComplexData())
        {
            if(plist->First().GetComplexData()->IsList())    
                {
                    Variant retval= Recurse(v, Min);
                    //This is a list; extract the first item and return it.
                    return retval.GetComplexData()->GetList()->First();
                }
            PError::SignalFatalError("Min() can only take numbers or lists as arguments.");
            return Variant(0);
        }
    

    Variant min = plist->First();
    std::list<Variant>::const_iterator i = plist->Begin();
    
    while(i != plist->End())
        {
            PError::AssertType(*i, PEAT_NUMBER, "Arguments of Min must be numbers.");
            if(*i < min)
                min = *i;
            i++;
        } 
    return min;
}



Variant PEBLMath::Max(Variant v)
{
    counted_ptr<PList> plist = (v.GetComplexData())->GetList();
    if(plist->First().IsComplexData())
        {
            if(plist->First().GetComplexData()->IsList())    
                {
                    Variant retval = Recurse(v, Max);
                    return retval.GetComplexData()->GetList()->First();
                }
            PError::SignalFatalError("Min() can only take numbers or lists as arguments.");
            return Variant(0);
        }
    
    Variant max = plist->First();
    std::list<Variant>::const_iterator i = plist->Begin();
    
    while(i != plist->End())
        {
            PError::AssertType(*i, PEAT_NUMBER, "Arguments of Max must be numbers.");
            if(*i > max)
                max = *i;
            i++;
        } 
    return max;
}



Variant PEBLMath::StDev(Variant v)
{
    PError::SignalFatalError("Function [StDev] Not implemented.");
    return Variant(0);
}

Variant PEBLMath::Median(Variant v)
{
    PError::SignalFatalError("Function [Median] Not implemented.");
    return Variant(0);

} 

Variant PEBLMath::Quantile(Variant v)
{
    PError::SignalFatalError("Function [Quantile] Not implemented.");
    return Variant(0);
}



///This will explicitly re-seed the RNG with the time of day.  Useful for
/// multi-session experiments where you want to use the same random seed across
/// days to randomize, but want differences in order between days, etc.

Variant PEBLMath::RandomizeTimer(Variant v)
{
   time_t now = time(0);
   srand(now);
   return Variant(now);
    
}
///This explicitly seeds the Random Number Generator.
///By Default, The PEBL Environment will call this on a time-of-day function on start-up.
Variant  PEBLMath::SeedRNG(Variant v)
{
   //v[1] should have the parameter
    counted_ptr<PList> plist = (v.GetComplexData())->GetList();
    PError::AssertType(plist->First().GetInteger(), PEAT_NUMBER, "Argument error in function [SeedRNG(<number>)]:  ");    
    
    long int seed = plist->First();
    srand(seed);
    
    return Variant(true);
}



/// This function takes no parameters, and returns
/// a floating-point Variant between 0 and 1.
Variant  PEBLMath::Random (Variant v)
{
   //v[1] should have nothing in it.

    return Variant(PEBLUtility::RandomUniform());
}


/// This function takes one parameter, which should be 
/// a positive integer.  It will return an integer between
/// 1 and argument (inclusive), each with equal probability.  If 
/// the argument is a float, it will get truncated down;
/// if it is less than 1,  1 will be returned, but a warning message will be triggered.
Variant  PEBLMath::RandomDiscrete (Variant v)
{
   //v[1] should have the parameter
    counted_ptr<PList> plist = (v.GetComplexData())->GetList();
    PError::AssertType(plist->First(), PEAT_NUMBER, "Argument error in function [RandomDiscrete(<number>)]:  ");    
    
    int v1 = plist->First();
    if(v1 < 1)
        {
            string message = "Function [RandomDiscrete] requires argument >= 1; received ";
            message += v1;
            message += ". Returning 1.";
            PError::SignalWarning(message);
            return Variant(1);
        }
            
    //Since the most-significant digits are a bit predictable, use the remainder function
    unsigned int r = rand();
    return Variant((long int)(r % v1)+ 1 );
    
}


/// This function takes one parameter, which should be a positive
/// number.  It will return a floating-point variant between 0 and 
/// the argument.
Variant  PEBLMath::RandomUniform(Variant v)
{
   //v[1] should have the parameter
    counted_ptr<PList> plist = (v.GetComplexData())->GetList();
    PError::AssertType(plist->First(), PEAT_NUMBER, "Argument error in function [RandomUniform(<number>)]:  ");    
    
    long double upperbound = plist->First(); plist->PopFront();
    if(upperbound < 0)
        {
            std::ostrstream  message;
            message << "Function [RandomUniform] requires argument >= 0; received "
                    << upperbound;
            message.put(0);
            PError::SignalFatalError(message.str());
        }
    
    return Variant(upperbound * PEBLUtility::RandomUniform());
}




/// This function takes two parameters (mean and stdev),  It will return a floating-
/// point number which is a sample from the N(0,1) distribution.
/// Values are calculated using the Box-Mueller technique.
Variant  PEBLMath::RandomNormal(Variant v)
{

    //v[1] should be mean, v[2] should be standard deviation.
    counted_ptr<PList> plist = (v.GetComplexData())->GetList();
    PError::AssertType(plist->First(), PEAT_NUMBER, "Argument error in first parameter of function [RandomNormal(<mean>, <stdev>)]:  ");    
    long double mean = plist->First(); plist->PopFront();

    PError::AssertType(plist->First(), PEAT_NUMBER, "Argument error in second parameter function [RandomNormal(<mean>, <stdev>)]:  ");    
    long double stdev = plist->First(); plist->PopFront();
 
    if(stdev < 0)  PError::SignalFatalError("Standard Deviation parameter of function [RandomNormal(<mean>,<stdev>)] must be positive.");

    return Variant(mean + PEBLUtility::RandomNormal()*stdev);
}

/// This function takes a single parameter; the mean of
/// of an exponential random variable. It will return a floating-point
/// value which is a sample from this distribution.
Variant  PEBLMath::RandomExponential(Variant v)
{
   //v[1] should be lambda, the mean of the Exponential RV.
    counted_ptr<PList> plist = (v.GetComplexData())->GetList();
    PError::AssertType(plist->First(), PEAT_NUMBER, "Argument error in function [RandomExponential(<number>)]:  ");    
    long double lambda = plist->First(); plist->PopFront();
       
    //The value of lambda may not be able to vary freely--It may not be able to be negative.
    //This should be checked for.

    return Variant(-lambda * log(PEBLUtility::RandomUniform()));
}


/// This function takes no  parameters; It will return a floating-point
/// value which is a sample from the vanilla logistic distribution f(x) = exp(x)/(1+exp(x))
Variant  PEBLMath::RandomLogistic(Variant v)
{
   //v should have no parameters
    
    double p = PEBLUtility::RandomUniform();
    
    return Variant(log(p/(1-p)));
}


/// This function takes two parameters, the spread and median
/// of a log-normal random variable.
Variant  PEBLMath::RandomLogNormal(Variant v)
{
  //v[1] should be median, v[2] should be the spread
    counted_ptr<PList> plist = (v.GetComplexData())->GetList();
    PError::AssertType(plist->First(), PEAT_NUMBER, "Argument error in first parameter function [RandomLogNormal(<median>, <spread>)]:  ");    
    long double median = plist->First(); plist->PopFront();
    
    PError::AssertType(plist->First(), PEAT_NUMBER, "Argument error in second parameter function [RandomLogNormal(<median>, <spread>)]:  ");    
    long double spread = plist->First(); plist->PopFront();
    
    return Variant(median * exp(spread * PEBLUtility::RandomNormal()));
}

/// This takes a value p and a value N.  It will generate N random
/// numbers and report the count of the numbers that are below p.
Variant  PEBLMath::RandomBinomial(Variant v)
{
   //v[1] should have the parameter
    counted_ptr<PList> plist = (v.GetComplexData())->GetList();

    PError::AssertType(plist->First(), PEAT_NUMBER, "Argument error in first parameter function [RandomBinomial(<p>, <N>)]:  ");    
    long double p = plist->First(); plist->PopFront();
    PError::AssertType(plist->First(), PEAT_NUMBER, "Argument error in second parameter function [RandomBinomial(<p>, <N>)]:  ");    
    long int N = plist->First(); plist->PopFront();
    
    long int count = 0;
    for(int i = 0; i < N; i++)
        {
            if(PEBLUtility::RandomUniform() < p) count++;
        }
    
 
    return Variant(count);
}


/// This takes a value p and returns either 1 with probability p and 0 
/// with probability 1-p.
Variant  PEBLMath::RandomBernoulli(Variant v)
{
   //v[1] should have the parameter
    counted_ptr<PList> plist = (v.GetComplexData())->GetList();

    PError::AssertType(plist->First(), PEAT_NUMBER, "Argument error in first parameter function [RandomBinomial(<p>, <N>)]:  ");    
    long double p = plist->First(); plist->PopFront();
    
    if(PEBLUtility::RandomUniform() < p) 
        return Variant(1);
    else 
        return Variant(0);
}
