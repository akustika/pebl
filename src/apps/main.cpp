#include "../base/Evaluator.h"
#include "../base/grammar.tab.hpp"
#include "../base/PNode.h"
#include <iostream>



PNode *  parse();

int PEBLInterpret( int argc, char **argv )
{
  if(argc !=1)
    {
      std::cout << "Invoke with only one command-line option" << std::endl;
      return 0;
    }
  
  Evaluator* myEval = new Evaluator();
  PNode *node1;
  node1=NULL;

  std::cout << "---------Enter Expression--------" << std::endl;
  node1 = parse();
  
  
  if(node1) 
    {
      std::cout << "---------Expression Parsed---------" << std::endl;   
      std::cout << "---------Evaluating Expression-----" << std::endl;
      //Execute everything
      myEval->Evaluate(node1);
    }
  else
    {
      std::cout << "No Node" << std::endl;
    }

  return 1;
}



//The following is the entry point for the command-line version
int main(int argc, char **argv)
{
    return PEBLInterpret(argc, argv);
}

