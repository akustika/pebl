%{
  
#include "PNode.h"


#include <stdio.h>
#include <iostream.h>
#include <cctype>
#include <cstring>
#include <vector>
#include <stack>

  
  // Prototypes to keep the compiler happy
  void yyerror (char *error);
  int  yylex ();
  extern FILE * yyin;
  PNode * gParseTreeHead;
  PNode * parse(const char* filename);
  extern int yylineno;
  char* sourcefilename;


%}

/*These are the types that are used during the parsing.
 *The numbers get transformed into pVariants during exectution*/


%union {
  
  long int    iValue;  /* For the lexical analyser. NUMBER tokens */
  long double fValue;
  char        *strValue; 
  PNode       *exp;    /* For expressions. */
  char        *symbol; /* The name of a variable*/
  char        *function; 
}

%token   PEBL_AND
%token   PEBL_ADD
%token   PEBL_ARGLIST		      
%token   PEBL_ASSIGN
%token   PEBL_BREAK
%token   PEBL_COMMA
%token   PEBL_DEFINE
%token   PEBL_DIVIDE
%token   PEBL_DOT
%token   PEBL_ELSE
%token   PEBL_END
%token   PEBL_EOF
%token   PEBL_EQ
%token   PEBL_FUNCTION
%token   PEBL_FUNCTIONS
%token   PEBL_GE
%token   PEBL_GT
%token   PEBL_IF
%token   PEBL_IFELSE
%token   PEBL_LAMBDAFUNCTION
%token   PEBL_LBRACE
%token   PEBL_LBRACKET
%token   PEBL_LE
%token   PEBL_LIBRARYFUNCTION
%token   PEBL_LISTHEAD
%token   PEBL_LISTITEM
%token   PEBL_LOOP
%token   PEBL_LPAREN
%token   PEBL_LT
%token   PEBL_MULTIPLY
%token   PEBL_NE
%token   PEBL_NEWLINE
%token   PEBL_NOT
%token   PEBL_OR
%token   PEBL_POWER
%token   PEBL_RETURN
%token   PEBL_RBRACE
%token   PEBL_RBRACKET
%token   PEBL_RPAREN
%token   PEBL_SUBTRACT
%token   PEBL_SEMI
%token   PEBL_STATEMENTS
%token   PEBL_START
%token   PEBL_VARIABLEDATUM
%token   PEBL_VARLIST
%token   PEBL_WHILE


%token  <fValue>      PEBL_FLOAT
%token  <iValue>      PEBL_INTEGER
%token  <strValue>    PEBL_STRING
%token  <symbol>      PEBL_SYMBOL
%token  <symbol>      PEBL_LOCALVAR
%token  <symbol>      PEBL_GLOBALVAR
%token  <function>    PEBL_FUNCTIONNAME


/* Lets inform Bison about the type of each terminal and non-terminal */
%type <exp>  variable exp function functions varlist list explist arglist datum 
%type <exp>  statement sequence block
%type <exp>   newlines  nlornone
%type <exp>  functionsequence returnstatement functionblock

			

/* Precedence information to resolve ambiguity */
%left PEBL_NEWLINE
%left PEBL_ASSIGN
%left PEBL_AND PEBL_OR PEBL_NOT
%left PEBL_GE PEBL_LE PEBL_EQ PEBL_NE PEBL_GT PEBL_LT
%left PEBL_ADD PEBL_SUBTRACT
%left PEBL_MULTIPLY PEBL_DIVIDE
%nonassoc PEBL_UMINUS 
%%



		/*============================================================================*/
functions:	nlornone function nlornone {gParseTreeHead =  new OpNode(PEBL_FUNCTIONS,$2,NULL, sourcefilename, yylineno);

		           $$ = gParseTreeHead;
		}



		/******************************************************************************/
	|	functions function nlornone { gParseTreeHead = new OpNode(PEBL_FUNCTIONS, $2, $1, sourcefilename, yylineno);
		           $$ = gParseTreeHead;
		}
;

		/*============================================================================*/
                /******************************************************************************/
function:	/*Syntax allows there to be a newline between the varlist and the block*/
		PEBL_DEFINE PEBL_FUNCTIONNAME PEBL_LPAREN varlist PEBL_RPAREN  nlornone functionblock  { ;
		PNode * tmpFN = new OpNode(PEBL_LAMBDAFUNCTION, $4, $7, sourcefilename, yylineno);  
		PNode * tmpNode = new DataNode(Variant($2, P_DATA_FUNCTION), sourcefilename, yylineno);
		$$ = new OpNode(PEBL_FUNCTION, tmpNode, tmpFN, sourcefilename, yylineno);
        }

	       /******************************************************************************/
	|	PEBL_DEFINE PEBL_FUNCTIONNAME PEBL_LPAREN PEBL_RPAREN  nlornone functionblock    { ;
		PNode * tmpFN = new OpNode(PEBL_LAMBDAFUNCTION, NULL, $6, sourcefilename, yylineno);  
		PNode * tmpNode = new DataNode(Variant($2, P_DATA_FUNCTION), sourcefilename, yylineno);
		$$ = new OpNode(PEBL_FUNCTION, tmpNode, tmpFN, sourcefilename, yylineno);
		  }
	;	


functionblock:	/*============================================================================*/
		/******************************************************************************/
		/*A functionblock can either be a block or a block with a return token at the end*/
		block                                               {$$ = $1;}
	|	PEBL_LBRACE nlornone functionsequence PEBL_RBRACE   {$$ = $3;}
;


functionsequence:   returnstatement  nlornone          { $$ = $1;}
	|	    sequence nlornone returnstatement  nlornone { $$ = new OpNode(PEBL_STATEMENTS, $1, $3, sourcefilename, yylineno);}
;

		/*============================================================================*/
block:		PEBL_LBRACE nlornone sequence nlornone PEBL_RBRACE   { $$ = $3;}
	;


		/*============================================================================*/
		/******************************************************************************/
sequence:	statement              { $$ = $1; }

		/******************************************************************************/
	|	sequence nlornone statement        { $$ = new OpNode(PEBL_STATEMENTS, $1, $3, sourcefilename, yylineno);}

;

statement: 	/*============================================================================*/




		/******************************************************************************/
	 	exp PEBL_NEWLINE                 {$$ = $1;}

    |   PEBL_BREAK PEBL_NEWLINE           {$$ = new OpNode(PEBL_BREAK, NULL, NULL, sourcefilename, yylineno);}
		/******************************************************************************/
	| 	PEBL_LOCALVAR PEBL_ASSIGN exp  PEBL_NEWLINE 
		{ 
	        Variant tmpV($1,P_DATA_LOCALVARIABLE);       /*create a new temporary variant*/
		PNode * tmpNode = new DataNode(tmpV, sourcefilename, yylineno);        /*create basic pnode*/
		$$ = new OpNode(PEBL_ASSIGN, tmpNode, $3, sourcefilename, yylineno);   /*Use symbol node in assignment node*/
		}

		/******************************************************************************/
	| 	PEBL_GLOBALVAR PEBL_ASSIGN exp  PEBL_NEWLINE 
		{ 
	        Variant tmpV($1,P_DATA_GLOBALVARIABLE);      /*create a new temporary variant*/
		PNode * tmpNode = new DataNode(tmpV, sourcefilename, yylineno);        /*create basic pnode*/
		$$ = new OpNode(PEBL_ASSIGN, tmpNode, $3, sourcefilename, yylineno);   /*Use symbol node in assignment node*/
		}

		/******************************************************************************/
	| 	PEBL_WHILE PEBL_LPAREN exp PEBL_RPAREN nlornone block PEBL_NEWLINE {;
		$$ = new OpNode(PEBL_WHILE, $3, $6, sourcefilename, yylineno); }
 

		/******************************************************************************
		*** The operation of if-then and if-then-else:
		*** a PEBL_IF node has two children; the left is the test expression and the
		*** right is the code block.  This is fine for a simple if-then statement.
		*** else is written like in c except it requires braces: if(){}else{}
		*** This is put into two nodes; the top one which is the PEBL_IF, holding
		*** the test on the left and a PEBL_ELSE node on the right.  PEBL_ELSE
		*** just pops the stack and executes left if true, right if false.*/

        | 	PEBL_IF PEBL_LPAREN exp PEBL_RPAREN nlornone block  PEBL_NEWLINE {
		$$ = new OpNode(PEBL_IF, $3, $6, sourcefilename, yylineno); }



		/******************************************************************************/
        | 	PEBL_IF PEBL_LPAREN exp PEBL_RPAREN nlornone block  PEBL_ELSE nlornone block PEBL_NEWLINE {
		/*First make the else node*/
		PNode * tmpNode = new OpNode(PEBL_ELSE, $6, $9, sourcefilename, yylineno);
		/*Put the else node in the IF node*/
		$$ = new OpNode(PEBL_IFELSE, $3, tmpNode, sourcefilename, yylineno); }
 


	|	/******************************************************************************
		***The operation of the 'loop' function:
		*** A PEBL_LOOP has two children, the left which is a PEBL_VARIABLEDATUM node pair, 
		*** and the right which is a code block.  The PEBL_VARIABLEDATUM has a variable on
		*** the left and a datum on the right; the elements of the datum are assigned
		*** iteratively to the variable and the code block is executed, until
		*** the datum is finished.
		***/
		PEBL_LOOP PEBL_LPAREN variable PEBL_COMMA exp PEBL_RPAREN nlornone  block PEBL_NEWLINE {
		PNode * tmpNode = new OpNode(PEBL_VARIABLEDATUM, $3, $5, sourcefilename, yylineno);
		$$ = new OpNode(PEBL_LOOP, tmpNode, $8, sourcefilename, yylineno); }
        
	
;

returnstatement: PEBL_RETURN statement    {$$ = new OpNode(PEBL_RETURN, $2, NULL, sourcefilename, yylineno);}
		
	;


arglist:	/*============================================================================*/
		/******************************************************************************
		***An arglist is a list of arguments for a function. It appears similar to
		*** a list, but it should appear in () instead of [].
		***/
                PEBL_LPAREN PEBL_RPAREN                     {$$ = new OpNode(PEBL_ARGLIST, NULL, NULL, sourcefilename, yylineno);}

                /******************************************************************************/

       |  	PEBL_LPAREN nlornone explist PEBL_RPAREN    {$$ = new OpNode(PEBL_ARGLIST, $3, NULL, sourcefilename, yylineno);}
		;


		/******************************************************************************/
		/** list is a first-class data structure in PEBL that is defined by 
		*** putting a bunch of expressions within brackets [].
		***/
		/*============================================================================*/
		/******************************************************************************/
list:		PEBL_LBRACKET nlornone explist PEBL_RBRACKET {$$ = new OpNode(PEBL_LISTHEAD,$3, NULL, sourcefilename, yylineno);}


         |        PEBL_LBRACKET nlornone PEBL_RBRACKET         {$$ = new OpNode(PEBL_LISTHEAD, NULL, NULL, sourcefilename, yylineno);}
		;
		/*============================================================================*/
		/******************************************************************************/
explist:    	exp                                   {$$ = new OpNode(PEBL_LISTITEM, $1, NULL, sourcefilename, yylineno);}


		/******************************************************************************/
	|	exp PEBL_COMMA nlornone explist       {$$ = new OpNode(PEBL_LISTITEM, $1, $4, sourcefilename, yylineno);}
;


varlist:	/*============================================================================*/
		/******************************************************************************
		/*** A varlist is a list of variables.  It is used in a function declaration.
		***/
		variable                     {$$ = new OpNode(PEBL_VARLIST, $1, NULL, sourcefilename, yylineno);}


                /******************************************************************************/
        |       variable PEBL_COMMA  nlornone varlist  {$$ = new OpNode(PEBL_VARLIST,$1,$4, sourcefilename, yylineno);}
		;


		/*============================================================================*/
		/******************************************************************************/
exp:	        datum                   { $$ = $1;}
		/******************************************************************************/

	|	PEBL_LPAREN nlornone exp nlornone PEBL_RPAREN    {$$ = $3}

		/******************************************************************************/
	|        PEBL_SUBTRACT exp %prec PEBL_UMINUS    {
		Variant tmpV = 0;
		PNode * tmpNode = new DataNode(tmpV, sourcefilename, yylineno);
		$$ = new OpNode(PEBL_SUBTRACT, tmpNode, $2, sourcefilename, yylineno); }

		/******************************************************************************/
         |        PEBL_NOT exp                      {$$ = new OpNode(PEBL_NOT, $2, NULL, sourcefilename, yylineno); }

		/******************************************************************************/
	| 	exp PEBL_ADD nlornone exp         { $$ = new OpNode(PEBL_ADD, $1, $4, sourcefilename, yylineno);  }


		/******************************************************************************/
	| 	exp PEBL_DIVIDE  nlornone exp      { $$ = new OpNode(PEBL_DIVIDE,$1, $4, sourcefilename, yylineno);  } 

		/******************************************************************************/
	| 	exp PEBL_MULTIPLY nlornone exp    { $$ = new OpNode(PEBL_MULTIPLY, $1, $4, sourcefilename, yylineno);} 

		/******************************************************************************/
	| 	exp PEBL_SUBTRACT nlornone exp    { $$ = new OpNode(PEBL_SUBTRACT, $1, $4, sourcefilename, yylineno); } 

		/******************************************************************************/
	| 	exp PEBL_OR nlornone exp    { $$ = new OpNode(PEBL_OR, $1, $4, sourcefilename, yylineno); } 

		/******************************************************************************/
	| 	exp PEBL_AND nlornone exp   { $$ = new OpNode(PEBL_AND, $1, $4, sourcefilename, yylineno); } 


		/******************************************************************************/
	| 	exp PEBL_LT exp          { $$ = new OpNode(PEBL_LT,  $1, $3, sourcefilename, yylineno);}

		/******************************************************************************/
	| 	exp PEBL_GT exp          { $$ = new OpNode(PEBL_GT,  $1, $3, sourcefilename, yylineno);}

		/******************************************************************************/
	| 	exp PEBL_GE exp          { $$ = new OpNode(PEBL_GE,  $1, $3, sourcefilename, yylineno);}

		/******************************************************************************/
	| 	exp PEBL_LE exp          { $$ = new OpNode(PEBL_LE,  $1, $3, sourcefilename, yylineno);}

		/******************************************************************************/
	| 	exp PEBL_EQ exp          { $$ = new OpNode(PEBL_EQ,  $1, $3, sourcefilename, yylineno);}

		/******************************************************************************/
	| 	exp PEBL_NE exp          { $$ = new OpNode(PEBL_NE,  $1, $3, sourcefilename, yylineno);}


	|	/******************************************************************************/
		/** The following determines how functions are evaluated. 
		*** A function evaluates as an expression; thus it always has
		*** an implicit return value. Just put the function name followed 
		*** by its list of arguments in parentheses.  This does not check for
		*** legality; this type of checking is done later by the loader.*/
		PEBL_FUNCTIONNAME arglist {
		PNode * tmpNode = new DataNode(Variant($1, P_DATA_FUNCTION), sourcefilename, yylineno);
		$$ = new OpNode(PEBL_FUNCTION, tmpNode, $2, sourcefilename, yylineno);
		}
		;


		/*============================================================================*/
		/******************************************************************************/
datum:         	PEBL_INTEGER             { $$ = new DataNode ($1, sourcefilename, yylineno); }

		/******************************************************************************/
	| 	PEBL_FLOAT               { $$ = new DataNode ($1, sourcefilename, yylineno);}

		/******************************************************************************/
	|	PEBL_STRING              {
		Variant tmpV($1);            /*create a new temporary variant*/
		$$ = new DataNode(tmpV, sourcefilename, yylineno);
                                          }
		/******************************************************************************/
	|	list                     { $$ = $1;}

		/******************************************************************************/
	|	variable                 { $$ = $1;}
;
 
		/*============================================================================*/
		/******************************************************************************/
variable:	PEBL_LOCALVAR              { 
		Variant tmpV($1, P_DATA_LOCALVARIABLE);           /*create a new temporary variant*/;
		$$ = new DataNode(tmpV, sourcefilename, yylineno);                        /*Make a new variable node here.*/
        free($1);
        };
         |	PEBL_GLOBALVAR              { 
		Variant tmpV($1, P_DATA_GLOBALVARIABLE);          /*create a new temporary variant*/;
		$$ = new DataNode(tmpV, sourcefilename, yylineno);  /*Make a new variable node here.*/
		free($1);
		 };
		;

nlornone:	/**/   {/*nothing*/;}
		|       newlines {/**/;}
;


newlines:	PEBL_NEWLINE          {/**/;}
|	newlines PEBL_NEWLINE         {/**/;}

;



%%

void yyerror (char *error)
{

    std::cerr << "line " << yylineno << " of "<< sourcefilename<<": " << error << endl;
    exit(1);
}

extern int yy_flex_debug;

PNode * parse (const char* filename)
{
  //  yydebug=1;          /*Bison must be run with -t option to use debugging*/
  //    yy_flex_debug = 1;   /*Flex must be run with -d option to use*/
  /*This is currently only called once, so use
   *it to open a hard-coded file for testing
   */
  
  ///Reset the linecounter
  yylineno = 1;

    FILE * filein = fopen(filename,"r");
    if(!filein) 
	{
	    fprintf(stderr,"Could not open %s\n",filename);
	    exit(1);
	}
    fprintf(stderr,"File [%s] opened successfully.\n", filename);
    yyin=filein;
    
    //Set global filename indicator to current filename for use in error reporting.
    sourcefilename = strdup(filename);

    yyparse ();

    free(sourcefilename);
    return gParseTreeHead;
}

