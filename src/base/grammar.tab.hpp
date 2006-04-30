/* A Bison parser, made by GNU Bison 2.1a.  */

/* Skeleton parser for Yacc-like parsing with Bison,
   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006 Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

/* As a special exception, when this file is copied by Bison into a
   Bison output file, you may use that output file without restriction.
   This special exception was added by the Free Software Foundation
   in version 1.24 of Bison.  */

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     PEBL_AND = 258,
     PEBL_ADD = 259,
     PEBL_ARGLIST = 260,
     PEBL_ASSIGN = 261,
     PEBL_BREAK = 262,
     PEBL_COMMA = 263,
     PEBL_DEFINE = 264,
     PEBL_DIVIDE = 265,
     PEBL_DOT = 266,
     PEBL_ELSE = 267,
     PEBL_END = 268,
     PEBL_EOF = 269,
     PEBL_EQ = 270,
     PEBL_FUNCTION = 271,
     PEBL_FUNCTIONS = 272,
     PEBL_GE = 273,
     PEBL_GT = 274,
     PEBL_IF = 275,
     PEBL_IFELSE = 276,
     PEBL_LAMBDAFUNCTION = 277,
     PEBL_LBRACE = 278,
     PEBL_LBRACKET = 279,
     PEBL_LE = 280,
     PEBL_LIBRARYFUNCTION = 281,
     PEBL_LISTHEAD = 282,
     PEBL_LISTITEM = 283,
     PEBL_LOOP = 284,
     PEBL_LPAREN = 285,
     PEBL_LT = 286,
     PEBL_MULTIPLY = 287,
     PEBL_NE = 288,
     PEBL_NEWLINE = 289,
     PEBL_NOT = 290,
     PEBL_OR = 291,
     PEBL_POWER = 292,
     PEBL_RETURN = 293,
     PEBL_RBRACE = 294,
     PEBL_RBRACKET = 295,
     PEBL_RPAREN = 296,
     PEBL_SUBTRACT = 297,
     PEBL_SEMI = 298,
     PEBL_STATEMENTS = 299,
     PEBL_START = 300,
     PEBL_VARIABLEDATUM = 301,
     PEBL_VARLIST = 302,
     PEBL_WHILE = 303,
     PEBL_FLOAT = 304,
     PEBL_INTEGER = 305,
     PEBL_STRING = 306,
     PEBL_SYMBOL = 307,
     PEBL_LOCALVAR = 308,
     PEBL_GLOBALVAR = 309,
     PEBL_FUNCTIONNAME = 310,
     PEBL_UMINUS = 311
   };
#endif
/* Tokens.  */
#define PEBL_AND 258
#define PEBL_ADD 259
#define PEBL_ARGLIST 260
#define PEBL_ASSIGN 261
#define PEBL_BREAK 262
#define PEBL_COMMA 263
#define PEBL_DEFINE 264
#define PEBL_DIVIDE 265
#define PEBL_DOT 266
#define PEBL_ELSE 267
#define PEBL_END 268
#define PEBL_EOF 269
#define PEBL_EQ 270
#define PEBL_FUNCTION 271
#define PEBL_FUNCTIONS 272
#define PEBL_GE 273
#define PEBL_GT 274
#define PEBL_IF 275
#define PEBL_IFELSE 276
#define PEBL_LAMBDAFUNCTION 277
#define PEBL_LBRACE 278
#define PEBL_LBRACKET 279
#define PEBL_LE 280
#define PEBL_LIBRARYFUNCTION 281
#define PEBL_LISTHEAD 282
#define PEBL_LISTITEM 283
#define PEBL_LOOP 284
#define PEBL_LPAREN 285
#define PEBL_LT 286
#define PEBL_MULTIPLY 287
#define PEBL_NE 288
#define PEBL_NEWLINE 289
#define PEBL_NOT 290
#define PEBL_OR 291
#define PEBL_POWER 292
#define PEBL_RETURN 293
#define PEBL_RBRACE 294
#define PEBL_RBRACKET 295
#define PEBL_RPAREN 296
#define PEBL_SUBTRACT 297
#define PEBL_SEMI 298
#define PEBL_STATEMENTS 299
#define PEBL_START 300
#define PEBL_VARIABLEDATUM 301
#define PEBL_VARLIST 302
#define PEBL_WHILE 303
#define PEBL_FLOAT 304
#define PEBL_INTEGER 305
#define PEBL_STRING 306
#define PEBL_SYMBOL 307
#define PEBL_LOCALVAR 308
#define PEBL_GLOBALVAR 309
#define PEBL_FUNCTIONNAME 310
#define PEBL_UMINUS 311




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 30 "src/base/grammar.y"
{
  
  long int    iValue;  /* For the lexical analyser. NUMBER tokens */
  long double fValue;
  char        *strValue; 
  PNode       *exp;    /* For expressions. */
  char        *symbol; /* The name of a variable*/
  char        *function; 
}
/* Line 1538 of yacc.c.  */
#line 161 "src/base/grammar.tab.hpp"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;



