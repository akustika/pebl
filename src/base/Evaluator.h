//* -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*- */
/////////////////////////////////////////////////////////////////////////////////
//    Name:       src/base/Evaluator.h
//    Purpose:    Defines an class that can evaluate PNodes
//    Author:     Shane T. Mueller, Ph.D.
//    Copyright:  (c) 2003 Shane T. Mueller <smueller@umich.edu>
//    License:    GPL 2
//
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

#ifndef __EVALUATOR_H__
#define __EVALUATOR_H__

#include <stack>
//#include "PNode.h"
#include "Variant.h"

#include "FunctionMap.h"
#include "../utility/PEBLPath.h"
#include "VariableMap.h"
//#include "../devices/PEventLoop.h"

class PNode;
class OpNode;
class DataNode;
class Variant;
class FunctionMap;
class VariableMap;
class PEventLoop;



/// This class has got everything you need to evaluate stuff.
class Evaluator
{
public:

    Evaluator();
    Evaluator(Variant  v);
    ~Evaluator();
  
    void CallFunction(const OpNode * node);

    void Evaluate(const PNode * node);
    void Evaluate(const OpNode * node);
    void Evaluate(const DataNode * node);
  
    void Push(Variant v);
    Variant Pop();

    int GetStackDepth(){return mStack.size();};

    /// This holds a pointer to a FunctionMap, which 
    /// is loaded from the initial PNode tree by the loader.
    /// It is static and public, which means that all Evaluators
    /// have access to the same one, and anything else can access it
    /// with Evaluator::mFunctionMap
    static FunctionMap mFunctionMap;
 

    /// The static keyword defines a 'Global' variable map that can be accessed by all
    /// Evaluators. It needs to be initialized somewhere outside the class, however. This
    /// is done in the main program file.
    static VariableMap gGlobalVariableMap;
    
    static PEventLoop mEventLoop;

    static PEBLPath gPath;

    /// This is used for error detection.  Every time mEvalNode is 
    /// updated, this is set to mEvalNode.  But, it is done for 
    /// all evaluators.  Thus, it always points to the last node
    /// processed, and error reporting routines can look for it and
    /// find out where it came from.
    static  const  PNode * gEvalNode;


private:


    /// This is the main data stack for the evaluator
    /// It currently does not have a limit--it probably should
    std::stack<Variant> mStack;

    /// This stack could be done a little smarter.  Limits
    /// the depth of the stack in case problems happen. Checking only
    /// goes on within Push().
    unsigned int mStackMax;


    /// This holds variables local to the current thread.
    VariableMap mLocalVariableMap; 
 
};


#endif
