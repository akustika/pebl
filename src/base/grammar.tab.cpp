/* A Bison parser, made by GNU Bison 1.875a.  */

/* Skeleton parser for Yacc-like parsing with Bison,
   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003 Free Software Foundation, Inc.

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
   Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.  */

/* As a special exception, when this file is copied by Bison into a
   Bison output file, you may use that output file without restriction.
   This special exception was added by the Free Software Foundation
   in version 1.24 of Bison.  */

/* Written by Richard Stallman by simplifying the original so called
   ``semantic'' parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0



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
     PEBL_COMMA = 262,
     PEBL_DEFINE = 263,
     PEBL_DIVIDE = 264,
     PEBL_DOT = 265,
     PEBL_ELSE = 266,
     PEBL_END = 267,
     PEBL_EOF = 268,
     PEBL_EQ = 269,
     PEBL_FUNCTION = 270,
     PEBL_FUNCTIONS = 271,
     PEBL_GE = 272,
     PEBL_GT = 273,
     PEBL_IF = 274,
     PEBL_IFELSE = 275,
     PEBL_LAMBDAFUNCTION = 276,
     PEBL_LBRACE = 277,
     PEBL_LBRACKET = 278,
     PEBL_LE = 279,
     PEBL_LIBRARYFUNCTION = 280,
     PEBL_LISTHEAD = 281,
     PEBL_LISTITEM = 282,
     PEBL_LOOP = 283,
     PEBL_LPAREN = 284,
     PEBL_LT = 285,
     PEBL_MULTIPLY = 286,
     PEBL_NE = 287,
     PEBL_NEWLINE = 288,
     PEBL_NOT = 289,
     PEBL_OR = 290,
     PEBL_POWER = 291,
     PEBL_RETURN = 292,
     PEBL_RBRACE = 293,
     PEBL_RBRACKET = 294,
     PEBL_RPAREN = 295,
     PEBL_SUBTRACT = 296,
     PEBL_SEMI = 297,
     PEBL_STATEMENTS = 298,
     PEBL_START = 299,
     PEBL_VARIABLEDATUM = 300,
     PEBL_VARLIST = 301,
     PEBL_WHILE = 302,
     PEBL_FLOAT = 303,
     PEBL_INTEGER = 304,
     PEBL_STRING = 305,
     PEBL_SYMBOL = 306,
     PEBL_LOCALVAR = 307,
     PEBL_GLOBALVAR = 308,
     PEBL_FUNCTIONNAME = 309,
     PEBL_UMINUS = 310
   };
#endif
#define PEBL_AND 258
#define PEBL_ADD 259
#define PEBL_ARGLIST 260
#define PEBL_ASSIGN 261
#define PEBL_COMMA 262
#define PEBL_DEFINE 263
#define PEBL_DIVIDE 264
#define PEBL_DOT 265
#define PEBL_ELSE 266
#define PEBL_END 267
#define PEBL_EOF 268
#define PEBL_EQ 269
#define PEBL_FUNCTION 270
#define PEBL_FUNCTIONS 271
#define PEBL_GE 272
#define PEBL_GT 273
#define PEBL_IF 274
#define PEBL_IFELSE 275
#define PEBL_LAMBDAFUNCTION 276
#define PEBL_LBRACE 277
#define PEBL_LBRACKET 278
#define PEBL_LE 279
#define PEBL_LIBRARYFUNCTION 280
#define PEBL_LISTHEAD 281
#define PEBL_LISTITEM 282
#define PEBL_LOOP 283
#define PEBL_LPAREN 284
#define PEBL_LT 285
#define PEBL_MULTIPLY 286
#define PEBL_NE 287
#define PEBL_NEWLINE 288
#define PEBL_NOT 289
#define PEBL_OR 290
#define PEBL_POWER 291
#define PEBL_RETURN 292
#define PEBL_RBRACE 293
#define PEBL_RBRACKET 294
#define PEBL_RPAREN 295
#define PEBL_SUBTRACT 296
#define PEBL_SEMI 297
#define PEBL_STATEMENTS 298
#define PEBL_START 299
#define PEBL_VARIABLEDATUM 300
#define PEBL_VARLIST 301
#define PEBL_WHILE 302
#define PEBL_FLOAT 303
#define PEBL_INTEGER 304
#define PEBL_STRING 305
#define PEBL_SYMBOL 306
#define PEBL_LOCALVAR 307
#define PEBL_GLOBALVAR 308
#define PEBL_FUNCTIONNAME 309
#define PEBL_UMINUS 310




/* Copy the first part of user declarations.  */
#line 1 "src/base/grammar.y"

  
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




/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

#if ! defined (YYSTYPE) && ! defined (YYSTYPE_IS_DECLARED)
#line 30 "src/base/grammar.y"
typedef union YYSTYPE {
  
  long int    iValue;  /* For the lexical analyser. NUMBER tokens */
  long double fValue;
  char        *strValue; 
  PNode       *exp;    /* For expressions. */
  char        *symbol; /* The name of a variable*/
  char        *function; 
} YYSTYPE;
/* Line 191 of yacc.c.  */
#line 221 "src/base/grammar.tab.cpp"
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 214 of yacc.c.  */
#line 233 "src/base/grammar.tab.cpp"

#if ! defined (yyoverflow) || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# if YYSTACK_USE_ALLOCA
#  define YYSTACK_ALLOC alloca
# else
#  ifndef YYSTACK_USE_ALLOCA
#   if defined (alloca) || defined (_ALLOCA_H)
#    define YYSTACK_ALLOC alloca
#   else
#    ifdef __GNUC__
#     define YYSTACK_ALLOC __builtin_alloca
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning. */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
# else
#  if defined (__STDC__) || defined (__cplusplus)
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   define YYSIZE_T size_t
#  endif
#  define YYSTACK_ALLOC malloc
#  define YYSTACK_FREE free
# endif
#endif /* ! defined (yyoverflow) || YYERROR_VERBOSE */


#if (! defined (yyoverflow) \
     && (! defined (__cplusplus) \
	 || (YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  short yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (short) + sizeof (YYSTYPE))				\
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  register YYSIZE_T yyi;		\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (0)
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (0)

#endif

#if defined (__STDC__) || defined (__cplusplus)
   typedef signed char yysigned_char;
#else
   typedef short yysigned_char;
#endif

/* YYFINAL -- State number of the termination state. */
#define YYFINAL  5
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   452

/* YYNTOKENS -- Number of terminals. */
#define YYNTOKENS  56
/* YYNNTS -- Number of nonterminals. */
#define YYNNTS  18
/* YYNRULES -- Number of rules. */
#define YYNRULES  56
/* YYNRULES -- Number of states. */
#define YYNSTATES  145

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   310

#define YYTRANSLATE(YYX) 						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const unsigned char yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const unsigned char yyprhs[] =
{
       0,     0,     3,     7,    11,    19,    26,    28,    33,    36,
      41,    47,    49,    53,    56,    61,    66,    74,    82,    93,
     103,   106,   109,   114,   119,   123,   125,   130,   132,   137,
     139,   145,   148,   151,   156,   161,   166,   171,   176,   181,
     185,   189,   193,   197,   201,   205,   208,   210,   212,   214,
     216,   218,   220,   222,   223,   225,   227
};

/* YYRHS -- A `-1'-separated list of the rules' RHS. */
static const yysigned_char yyrhs[] =
{
      57,     0,    -1,    72,    58,    72,    -1,    57,    58,    72,
      -1,     8,    54,    29,    68,    40,    72,    59,    -1,     8,
      54,    29,    40,    72,    59,    -1,    61,    -1,    22,    72,
      60,    38,    -1,    64,    72,    -1,    62,    72,    64,    72,
      -1,    22,    72,    62,    72,    38,    -1,    63,    -1,    62,
      72,    63,    -1,    69,    33,    -1,    52,     6,    69,    33,
      -1,    53,     6,    69,    33,    -1,    47,    29,    69,    40,
      72,    61,    33,    -1,    19,    29,    69,    40,    72,    61,
      33,    -1,    19,    29,    69,    40,    72,    61,    11,    72,
      61,    33,    -1,    28,    29,    71,     7,    69,    40,    72,
      61,    33,    -1,    37,    63,    -1,    29,    40,    -1,    29,
      72,    67,    40,    -1,    23,    72,    67,    39,    -1,    23,
      72,    39,    -1,    69,    -1,    69,     7,    72,    67,    -1,
      71,    -1,    71,     7,    72,    68,    -1,    70,    -1,    29,
      72,    69,    72,    40,    -1,    41,    69,    -1,    34,    69,
      -1,    69,     4,    72,    69,    -1,    69,     9,    72,    69,
      -1,    69,    31,    72,    69,    -1,    69,    41,    72,    69,
      -1,    69,    35,    72,    69,    -1,    69,     3,    72,    69,
      -1,    69,    30,    69,    -1,    69,    18,    69,    -1,    69,
      17,    69,    -1,    69,    24,    69,    -1,    69,    14,    69,
      -1,    69,    32,    69,    -1,    54,    65,    -1,    49,    -1,
      48,    -1,    50,    -1,    66,    -1,    71,    -1,    52,    -1,
      53,    -1,    -1,    73,    -1,    33,    -1,    73,    33,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const unsigned short yyrline[] =
{
       0,   117,   117,   125,   133,   139,   149,   150,   154,   155,
     159,   165,   168,   178,   182,   190,   198,   211,   217,   233,
     240,   250,   254,   264,   267,   271,   275,   283,   287,   293,
     296,   299,   305,   308,   312,   315,   318,   321,   324,   328,
     331,   334,   337,   340,   343,   352,   362,   365,   368,   373,
     376,   381,   384,   389,   390,   394,   395
};
#endif

#if YYDEBUG || YYERROR_VERBOSE
/* YYTNME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals. */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "PEBL_AND", "PEBL_ADD", "PEBL_ARGLIST", 
  "PEBL_ASSIGN", "PEBL_COMMA", "PEBL_DEFINE", "PEBL_DIVIDE", "PEBL_DOT", 
  "PEBL_ELSE", "PEBL_END", "PEBL_EOF", "PEBL_EQ", "PEBL_FUNCTION", 
  "PEBL_FUNCTIONS", "PEBL_GE", "PEBL_GT", "PEBL_IF", "PEBL_IFELSE", 
  "PEBL_LAMBDAFUNCTION", "PEBL_LBRACE", "PEBL_LBRACKET", "PEBL_LE", 
  "PEBL_LIBRARYFUNCTION", "PEBL_LISTHEAD", "PEBL_LISTITEM", "PEBL_LOOP", 
  "PEBL_LPAREN", "PEBL_LT", "PEBL_MULTIPLY", "PEBL_NE", "PEBL_NEWLINE", 
  "PEBL_NOT", "PEBL_OR", "PEBL_POWER", "PEBL_RETURN", "PEBL_RBRACE", 
  "PEBL_RBRACKET", "PEBL_RPAREN", "PEBL_SUBTRACT", "PEBL_SEMI", 
  "PEBL_STATEMENTS", "PEBL_START", "PEBL_VARIABLEDATUM", "PEBL_VARLIST", 
  "PEBL_WHILE", "PEBL_FLOAT", "PEBL_INTEGER", "PEBL_STRING", 
  "PEBL_SYMBOL", "PEBL_LOCALVAR", "PEBL_GLOBALVAR", "PEBL_FUNCTIONNAME", 
  "PEBL_UMINUS", "$accept", "functions", "function", "functionblock", 
  "functionsequence", "block", "sequence", "statement", "returnstatement", 
  "arglist", "list", "explist", "varlist", "exp", "datum", "variable", 
  "nlornone", "newlines", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const unsigned short yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const unsigned char yyr1[] =
{
       0,    56,    57,    57,    58,    58,    59,    59,    60,    60,
      61,    62,    62,    63,    63,    63,    63,    63,    63,    63,
      64,    65,    65,    66,    66,    67,    67,    68,    68,    69,
      69,    69,    69,    69,    69,    69,    69,    69,    69,    69,
      69,    69,    69,    69,    69,    69,    70,    70,    70,    70,
      70,    71,    71,    72,    72,    73,    73
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const unsigned char yyr2[] =
{
       0,     2,     3,     3,     7,     6,     1,     4,     2,     4,
       5,     1,     3,     2,     4,     4,     7,     7,    10,     9,
       2,     2,     4,     4,     3,     1,     4,     1,     4,     1,
       5,     2,     2,     4,     4,     4,     4,     4,     4,     3,
       3,     3,     3,     3,     3,     2,     1,     1,     1,     1,
       1,     1,     1,     0,     1,     1,     2
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const unsigned char yydefact[] =
{
      53,    55,     0,     0,    54,     1,     0,    53,    53,    56,
       0,     3,     2,     0,    53,    51,    52,     0,    27,     0,
      53,    53,    53,     5,     6,     0,     0,     0,     4,    28,
       0,    53,     0,    53,     0,     0,     0,     0,    47,    46,
      48,    51,    52,     0,     0,    53,    11,    53,    49,     0,
      29,    50,     0,     0,     0,     0,    32,    20,    31,     0,
       0,     0,    53,    45,     7,     0,     8,    53,    53,    53,
       0,     0,     0,     0,     0,    53,     0,    13,    53,    53,
       0,    24,     0,    25,     0,    53,     0,     0,     0,    21,
       0,    10,    12,    53,     0,     0,     0,    43,    41,    40,
      42,    39,     0,    44,     0,     0,    53,    23,    53,     0,
       0,    53,    14,    15,     0,     9,    38,    33,    34,    35,
      37,    36,     0,     0,     0,    30,     0,    22,    53,     0,
      26,    53,     0,     0,    53,    17,     0,    16,    53,     0,
       0,     0,     0,    19,    18
};

/* YYDEFGOTO[NTERM-NUM]. */
static const yysigned_char yydefgoto[] =
{
      -1,     2,     7,    23,    44,    24,    45,    46,    47,    63,
      48,    82,    17,    49,    50,    51,     3,     4
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -104
static const short yypact[] =
{
     -16,  -104,    10,    12,    -8,  -104,   -25,   -16,   -16,  -104,
       8,  -104,  -104,   -18,   -16,  -104,  -104,     2,    36,    23,
     -16,   -16,   -16,  -104,  -104,    23,   -41,   332,  -104,  -104,
      17,   -16,    18,   -16,   107,   381,   107,    19,  -104,  -104,
    -104,    43,    44,    22,    16,   -16,  -104,   -16,  -104,    49,
    -104,  -104,   107,   398,   -41,   107,   294,  -104,  -104,   107,
     107,   107,   -12,  -104,  -104,   300,  -104,   -16,   -16,   -16,
     107,   107,   107,   107,   107,   -16,   107,  -104,   -16,   -16,
     162,  -104,    20,    88,    50,   181,   206,   225,   250,  -104,
     107,  -104,  -104,   -16,   107,   107,   107,     0,     0,     0,
       0,     0,   107,     0,   107,   107,   -16,  -104,   -16,   107,
      24,   -16,  -104,  -104,    25,  -104,   294,    -4,  -104,  -104,
     294,    -4,    34,   107,   275,  -104,    34,  -104,   -16,    -3,
    -104,   -16,    37,   381,   -16,  -104,    34,  -104,   -16,    34,
      41,   349,    42,  -104,  -104
};

/* YYPGOTO[NTERM-NUM].  */
static const yysigned_char yypgoto[] =
{
    -104,  -104,    66,    51,  -104,  -103,   -56,   -33,    28,  -104,
    -104,   -84,    57,    73,  -104,   -10,    -7,  -104
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const unsigned char yytable[] =
{
      11,    12,    57,    18,    68,    69,   114,    19,   134,    69,
       5,    15,    16,    25,    26,    27,    18,     1,     6,   129,
       6,     1,    14,   132,    53,     9,    55,    75,    89,    10,
     135,    75,    92,   140,    15,    16,   142,    13,    65,   130,
      66,    79,    20,    21,    84,    22,    52,    54,    59,    60,
      61,    62,    67,    68,    64,    90,   128,   109,    69,   107,
      94,    95,    96,    70,   125,   127,    71,    72,   102,     8,
     137,   104,   105,    73,   143,   144,    28,   138,   110,    74,
      75,    76,    77,    29,    78,     0,   115,     0,     0,     0,
      79,    67,    68,    93,     0,   108,     0,    69,     0,   122,
       0,   123,    70,     0,   126,    71,    72,    56,    92,    58,
       0,     0,    73,     0,     0,     0,     0,     0,    74,    75,
      76,   133,     0,    78,   136,    80,    83,   139,    85,    79,
      31,   141,    86,    87,    88,     0,    33,     0,     0,     0,
       0,    34,     0,    97,    98,    99,   100,   101,    36,   103,
       0,     0,     0,     0,     0,    38,    39,    40,     0,    15,
      16,    43,     0,    83,     0,    67,    68,   116,   117,   118,
       0,    69,     0,     0,     0,   119,    70,   120,   121,    71,
      72,     0,   124,     0,    67,    68,    73,     0,     0,     0,
      69,     0,    74,    75,    76,    70,    83,    78,    71,    72,
       0,     0,   106,    79,     0,    73,     0,     0,     0,    67,
      68,    74,    75,    76,     1,    69,    78,     0,     0,     0,
      70,     0,    79,    71,    72,     0,     0,     0,    67,    68,
      73,     0,     0,     0,    69,     0,    74,    75,    76,    70,
       0,    78,    71,    72,     0,     0,   111,    79,     0,    73,
       0,     0,     0,    67,    68,    74,    75,    76,   112,    69,
      78,     0,     0,     0,    70,     0,    79,    71,    72,     0,
       0,     0,     0,     0,    73,     0,     0,     0,    67,    68,
      74,    75,    76,   113,    69,    78,     0,     0,     0,    70,
       0,    79,    71,    72,     0,     0,     0,     0,    68,    73,
       0,     0,     0,    69,     0,    74,    75,    76,    70,     0,
      78,    71,    72,     0,     0,   131,    79,     0,    73,    30,
       0,     0,     0,    31,    74,    75,    76,     0,    32,    33,
       0,     0,     0,     0,    34,    79,     0,    35,    91,     0,
       0,    36,     0,     0,     0,     0,     0,    37,    38,    39,
      40,    30,    41,    42,    43,    31,     0,     0,     0,     0,
      32,    33,     0,     0,     0,     0,    34,     0,    30,    35,
       0,     0,    31,    36,     0,     0,     0,    32,    33,    37,
      38,    39,    40,    34,    41,    42,    43,    91,     0,     0,
      36,     0,     0,     0,     0,     0,    37,    38,    39,    40,
      30,    41,    42,    43,    31,     0,     0,     0,     0,    32,
      33,     0,     0,     0,     0,    34,     0,     0,     0,     0,
       0,    31,    36,     0,     0,     0,     0,    33,    37,    38,
      39,    40,    34,    41,    42,    43,     0,    81,     0,    36,
       0,     0,     0,     0,     0,     0,    38,    39,    40,     0,
      15,    16,    43
};

static const short yycheck[] =
{
       7,     8,    35,    13,     4,     9,    90,    14,    11,     9,
       0,    52,    53,    20,    21,    22,    26,    33,     8,   122,
       8,    33,    40,   126,    31,    33,    33,    31,    40,    54,
      33,    31,    65,   136,    52,    53,   139,    29,    45,   123,
      47,    41,    40,     7,    54,    22,    29,    29,    29,     6,
       6,    29,     3,     4,    38,    62,    22,     7,     9,    39,
      67,    68,    69,    14,    40,    40,    17,    18,    75,     3,
      33,    78,    79,    24,    33,    33,    25,   133,    85,    30,
      31,    32,    33,    26,    35,    -1,    93,    -1,    -1,    -1,
      41,     3,     4,    65,    -1,     7,    -1,     9,    -1,   106,
      -1,   108,    14,    -1,   111,    17,    18,    34,   141,    36,
      -1,    -1,    24,    -1,    -1,    -1,    -1,    -1,    30,    31,
      32,   128,    -1,    35,   131,    52,    53,   134,    55,    41,
      23,   138,    59,    60,    61,    -1,    29,    -1,    -1,    -1,
      -1,    34,    -1,    70,    71,    72,    73,    74,    41,    76,
      -1,    -1,    -1,    -1,    -1,    48,    49,    50,    -1,    52,
      53,    54,    -1,    90,    -1,     3,     4,    94,    95,    96,
      -1,     9,    -1,    -1,    -1,   102,    14,   104,   105,    17,
      18,    -1,   109,    -1,     3,     4,    24,    -1,    -1,    -1,
       9,    -1,    30,    31,    32,    14,   123,    35,    17,    18,
      -1,    -1,    40,    41,    -1,    24,    -1,    -1,    -1,     3,
       4,    30,    31,    32,    33,     9,    35,    -1,    -1,    -1,
      14,    -1,    41,    17,    18,    -1,    -1,    -1,     3,     4,
      24,    -1,    -1,    -1,     9,    -1,    30,    31,    32,    14,
      -1,    35,    17,    18,    -1,    -1,    40,    41,    -1,    24,
      -1,    -1,    -1,     3,     4,    30,    31,    32,    33,     9,
      35,    -1,    -1,    -1,    14,    -1,    41,    17,    18,    -1,
      -1,    -1,    -1,    -1,    24,    -1,    -1,    -1,     3,     4,
      30,    31,    32,    33,     9,    35,    -1,    -1,    -1,    14,
      -1,    41,    17,    18,    -1,    -1,    -1,    -1,     4,    24,
      -1,    -1,    -1,     9,    -1,    30,    31,    32,    14,    -1,
      35,    17,    18,    -1,    -1,    40,    41,    -1,    24,    19,
      -1,    -1,    -1,    23,    30,    31,    32,    -1,    28,    29,
      -1,    -1,    -1,    -1,    34,    41,    -1,    37,    38,    -1,
      -1,    41,    -1,    -1,    -1,    -1,    -1,    47,    48,    49,
      50,    19,    52,    53,    54,    23,    -1,    -1,    -1,    -1,
      28,    29,    -1,    -1,    -1,    -1,    34,    -1,    19,    37,
      -1,    -1,    23,    41,    -1,    -1,    -1,    28,    29,    47,
      48,    49,    50,    34,    52,    53,    54,    38,    -1,    -1,
      41,    -1,    -1,    -1,    -1,    -1,    47,    48,    49,    50,
      19,    52,    53,    54,    23,    -1,    -1,    -1,    -1,    28,
      29,    -1,    -1,    -1,    -1,    34,    -1,    -1,    -1,    -1,
      -1,    23,    41,    -1,    -1,    -1,    -1,    29,    47,    48,
      49,    50,    34,    52,    53,    54,    -1,    39,    -1,    41,
      -1,    -1,    -1,    -1,    -1,    -1,    48,    49,    50,    -1,
      52,    53,    54
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const unsigned char yystos[] =
{
       0,    33,    57,    72,    73,     0,     8,    58,    58,    33,
      54,    72,    72,    29,    40,    52,    53,    68,    71,    72,
      40,     7,    22,    59,    61,    72,    72,    72,    59,    68,
      19,    23,    28,    29,    34,    37,    41,    47,    48,    49,
      50,    52,    53,    54,    60,    62,    63,    64,    66,    69,
      70,    71,    29,    72,    29,    72,    69,    63,    69,    29,
       6,     6,    29,    65,    38,    72,    72,     3,     4,     9,
      14,    17,    18,    24,    30,    31,    32,    33,    35,    41,
      69,    39,    67,    69,    71,    69,    69,    69,    69,    40,
      72,    38,    63,    64,    72,    72,    72,    69,    69,    69,
      69,    69,    72,    69,    72,    72,    40,    39,     7,     7,
      72,    40,    33,    33,    67,    72,    69,    69,    69,    69,
      69,    69,    72,    72,    69,    40,    72,    40,    22,    61,
      67,    40,    61,    72,    11,    33,    72,    33,    62,    72,
      61,    72,    61,    33,    33
};

#if ! defined (YYSIZE_T) && defined (__SIZE_TYPE__)
# define YYSIZE_T __SIZE_TYPE__
#endif
#if ! defined (YYSIZE_T) && defined (size_t)
# define YYSIZE_T size_t
#endif
#if ! defined (YYSIZE_T)
# if defined (__STDC__) || defined (__cplusplus)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# endif
#endif
#if ! defined (YYSIZE_T)
# define YYSIZE_T unsigned int
#endif

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrlab1


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK;						\
      goto yybackup;						\
    }								\
  else								\
    { 								\
      yyerror ("syntax error: cannot back up");\
      YYERROR;							\
    }								\
while (0)

#define YYTERROR	1
#define YYERRCODE	256

/* YYLLOC_DEFAULT -- Compute the default location (before the actions
   are run).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)         \
  Current.first_line   = Rhs[1].first_line;      \
  Current.first_column = Rhs[1].first_column;    \
  Current.last_line    = Rhs[N].last_line;       \
  Current.last_column  = Rhs[N].last_column;
#endif

/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (0)

# define YYDSYMPRINT(Args)			\
do {						\
  if (yydebug)					\
    yysymprint Args;				\
} while (0)

# define YYDSYMPRINTF(Title, Token, Value, Location)		\
do {								\
  if (yydebug)							\
    {								\
      YYFPRINTF (stderr, "%s ", Title);				\
      yysymprint (stderr, 					\
                  Token, Value);	\
      YYFPRINTF (stderr, "\n");					\
    }								\
} while (0)

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (cinluded).                                                   |
`------------------------------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yy_stack_print (short *bottom, short *top)
#else
static void
yy_stack_print (bottom, top)
    short *bottom;
    short *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (/* Nothing. */; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yy_reduce_print (int yyrule)
#else
static void
yy_reduce_print (yyrule)
    int yyrule;
#endif
{
  int yyi;
  unsigned int yylineno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %u), ",
             yyrule - 1, yylineno);
  /* Print the symbols being reduced, and their result.  */
  for (yyi = yyprhs[yyrule]; 0 <= yyrhs[yyi]; yyi++)
    YYFPRINTF (stderr, "%s ", yytname [yyrhs[yyi]]);
  YYFPRINTF (stderr, "-> %s\n", yytname [yyr1[yyrule]]);
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (Rule);		\
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YYDSYMPRINT(Args)
# define YYDSYMPRINTF(Title, Token, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   SIZE_MAX < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#if YYMAXDEPTH == 0
# undef YYMAXDEPTH
#endif

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined (__GLIBC__) && defined (_STRING_H)
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
#   if defined (__STDC__) || defined (__cplusplus)
yystrlen (const char *yystr)
#   else
yystrlen (yystr)
     const char *yystr;
#   endif
{
  register const char *yys = yystr;

  while (*yys++ != '\0')
    continue;

  return yys - yystr - 1;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined (__GLIBC__) && defined (_STRING_H) && defined (_GNU_SOURCE)
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
#   if defined (__STDC__) || defined (__cplusplus)
yystpcpy (char *yydest, const char *yysrc)
#   else
yystpcpy (yydest, yysrc)
     char *yydest;
     const char *yysrc;
#   endif
{
  register char *yyd = yydest;
  register const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

#endif /* !YYERROR_VERBOSE */



#if YYDEBUG
/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yysymprint (FILE *yyoutput, int yytype, YYSTYPE *yyvaluep)
#else
static void
yysymprint (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  /* Pacify ``unused variable'' warnings.  */
  (void) yyvaluep;

  if (yytype < YYNTOKENS)
    {
      YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
# ifdef YYPRINT
      YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
    }
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  switch (yytype)
    {
      default:
        break;
    }
  YYFPRINTF (yyoutput, ")");
}

#endif /* ! YYDEBUG */
/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yydestruct (int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yytype, yyvaluep)
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  /* Pacify ``unused variable'' warnings.  */
  (void) yyvaluep;

  switch (yytype)
    {

      default:
        break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
# if defined (__STDC__) || defined (__cplusplus)
int yyparse (void *YYPARSE_PARAM);
# else
int yyparse ();
# endif
#else /* ! YYPARSE_PARAM */
#if defined (__STDC__) || defined (__cplusplus)
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
# if defined (__STDC__) || defined (__cplusplus)
int yyparse (void *YYPARSE_PARAM)
# else
int yyparse (YYPARSE_PARAM)
  void *YYPARSE_PARAM;
# endif
#else /* ! YYPARSE_PARAM */
#if defined (__STDC__) || defined (__cplusplus)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  
  register int yystate;
  register int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  short	yyssa[YYINITDEPTH];
  short *yyss = yyssa;
  register short *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  register YYSTYPE *yyvsp;



#define YYPOPSTACK   (yyvsp--, yyssp--)

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* When reducing, the number of symbols on the RHS of the reduced
     rule.  */
  int yylen;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed. so pushing a state here evens the stacks.
     */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack. Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	short *yyss1 = yyss;


	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow ("parser stack overflow",
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),

		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyoverflowlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyoverflowlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	short *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyoverflowlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;


      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

/* Do appropriate processing given the current state.  */
/* Read a lookahead token if we need one and don't already have one.  */
/* yyresume: */

  /* First try to decide what to do without reference to lookahead token.  */

  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YYDSYMPRINTF ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Shift the lookahead token.  */
  YYDPRINTF ((stderr, "Shifting token %s, ", yytname[yytoken]));

  /* Discard the token being shifted unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  *++yyvsp = yylval;


  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  yystate = yyn;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 117 "src/base/grammar.y"
    {gParseTreeHead =  new OpNode(PEBL_FUNCTIONS,yyvsp[-1].exp,NULL, sourcefilename, yylineno);

		           yyval.exp = gParseTreeHead;
		;}
    break;

  case 3:
#line 125 "src/base/grammar.y"
    { gParseTreeHead = new OpNode(PEBL_FUNCTIONS, yyvsp[-1].exp, yyvsp[-2].exp, sourcefilename, yylineno);
		           yyval.exp = gParseTreeHead;
		;}
    break;

  case 4:
#line 133 "src/base/grammar.y"
    { ;
		PNode * tmpFN = new OpNode(PEBL_LAMBDAFUNCTION, yyvsp[-3].exp, yyvsp[0].exp, sourcefilename, yylineno);  
		PNode * tmpNode = new DataNode(Variant(yyvsp[-5].function, P_DATA_FUNCTION), sourcefilename, yylineno);
		yyval.exp = new OpNode(PEBL_FUNCTION, tmpNode, tmpFN, sourcefilename, yylineno);;}
    break;

  case 5:
#line 139 "src/base/grammar.y"
    { ;
		PNode * tmpFN = new OpNode(PEBL_LAMBDAFUNCTION, NULL, yyvsp[0].exp, sourcefilename, yylineno);  
		PNode * tmpNode = new DataNode(Variant(yyvsp[-4].function, P_DATA_FUNCTION), sourcefilename, yylineno);
		yyval.exp = new OpNode(PEBL_FUNCTION, tmpNode, tmpFN, sourcefilename, yylineno);;}
    break;

  case 6:
#line 149 "src/base/grammar.y"
    {yyval.exp = yyvsp[0].exp;;}
    break;

  case 7:
#line 150 "src/base/grammar.y"
    {yyval.exp = yyvsp[-1].exp;;}
    break;

  case 8:
#line 154 "src/base/grammar.y"
    { yyval.exp = yyvsp[-1].exp;;}
    break;

  case 9:
#line 155 "src/base/grammar.y"
    { yyval.exp = new OpNode(PEBL_STATEMENTS, yyvsp[-3].exp, yyvsp[-1].exp, sourcefilename, yylineno);;}
    break;

  case 10:
#line 159 "src/base/grammar.y"
    { yyval.exp = yyvsp[-2].exp;;}
    break;

  case 11:
#line 165 "src/base/grammar.y"
    { yyval.exp = yyvsp[0].exp; ;}
    break;

  case 12:
#line 168 "src/base/grammar.y"
    { yyval.exp = new OpNode(PEBL_STATEMENTS, yyvsp[-2].exp, yyvsp[0].exp, sourcefilename, yylineno);;}
    break;

  case 13:
#line 178 "src/base/grammar.y"
    {yyval.exp = yyvsp[-1].exp;;}
    break;

  case 14:
#line 183 "src/base/grammar.y"
    { 
	        Variant tmpV(yyvsp[-3].symbol,P_DATA_LOCALVARIABLE);       /*create a new temporary variant*/
		PNode * tmpNode = new DataNode(tmpV, sourcefilename, yylineno);        /*create basic pnode*/
		yyval.exp = new OpNode(PEBL_ASSIGN, tmpNode, yyvsp[-1].exp, sourcefilename, yylineno);   /*Use symbol node in assignment node*/
		;}
    break;

  case 15:
#line 191 "src/base/grammar.y"
    { 
	        Variant tmpV(yyvsp[-3].symbol,P_DATA_GLOBALVARIABLE);      /*create a new temporary variant*/
		PNode * tmpNode = new DataNode(tmpV, sourcefilename, yylineno);        /*create basic pnode*/
		yyval.exp = new OpNode(PEBL_ASSIGN, tmpNode, yyvsp[-1].exp, sourcefilename, yylineno);   /*Use symbol node in assignment node*/
		;}
    break;

  case 16:
#line 198 "src/base/grammar.y"
    {;
		yyval.exp = new OpNode(PEBL_WHILE, yyvsp[-4].exp, yyvsp[-1].exp, sourcefilename, yylineno); ;}
    break;

  case 17:
#line 211 "src/base/grammar.y"
    {
		yyval.exp = new OpNode(PEBL_IF, yyvsp[-4].exp, yyvsp[-1].exp, sourcefilename, yylineno); ;}
    break;

  case 18:
#line 217 "src/base/grammar.y"
    {
		/*First make the else node*/
		PNode * tmpNode = new OpNode(PEBL_ELSE, yyvsp[-4].exp, yyvsp[-1].exp, sourcefilename, yylineno);
		/*Put the else node in the IF node*/
		yyval.exp = new OpNode(PEBL_IFELSE, yyvsp[-7].exp, tmpNode, sourcefilename, yylineno); ;}
    break;

  case 19:
#line 233 "src/base/grammar.y"
    {
		PNode * tmpNode = new OpNode(PEBL_VARIABLEDATUM, yyvsp[-6].exp, yyvsp[-4].exp, sourcefilename, yylineno);
		yyval.exp = new OpNode(PEBL_LOOP, tmpNode, yyvsp[-1].exp, sourcefilename, yylineno); ;}
    break;

  case 20:
#line 240 "src/base/grammar.y"
    {yyval.exp = new OpNode(PEBL_RETURN, yyvsp[0].exp, NULL, sourcefilename, yylineno);;}
    break;

  case 21:
#line 250 "src/base/grammar.y"
    {yyval.exp = new OpNode(PEBL_ARGLIST, NULL, NULL, sourcefilename, yylineno);;}
    break;

  case 22:
#line 254 "src/base/grammar.y"
    {yyval.exp = new OpNode(PEBL_ARGLIST, yyvsp[-1].exp, NULL, sourcefilename, yylineno);;}
    break;

  case 23:
#line 264 "src/base/grammar.y"
    {yyval.exp = new OpNode(PEBL_LISTHEAD,yyvsp[-1].exp, NULL, sourcefilename, yylineno);;}
    break;

  case 24:
#line 267 "src/base/grammar.y"
    {yyval.exp = new OpNode(PEBL_LISTHEAD, NULL, NULL, sourcefilename, yylineno);;}
    break;

  case 25:
#line 271 "src/base/grammar.y"
    {yyval.exp = new OpNode(PEBL_LISTITEM, yyvsp[0].exp, NULL, sourcefilename, yylineno);;}
    break;

  case 26:
#line 275 "src/base/grammar.y"
    {yyval.exp = new OpNode(PEBL_LISTITEM, yyvsp[-3].exp, yyvsp[0].exp, sourcefilename, yylineno);;}
    break;

  case 27:
#line 283 "src/base/grammar.y"
    {yyval.exp = new OpNode(PEBL_VARLIST, yyvsp[0].exp, NULL, sourcefilename, yylineno);;}
    break;

  case 28:
#line 287 "src/base/grammar.y"
    {yyval.exp = new OpNode(PEBL_VARLIST,yyvsp[-3].exp,yyvsp[0].exp, sourcefilename, yylineno);;}
    break;

  case 29:
#line 293 "src/base/grammar.y"
    { yyval.exp = yyvsp[0].exp;;}
    break;

  case 30:
#line 296 "src/base/grammar.y"
    {yyval.exp = yyvsp[-2].exp;}
    break;

  case 31:
#line 299 "src/base/grammar.y"
    {
		Variant tmpV = 0;
		PNode * tmpNode = new DataNode(tmpV, sourcefilename, yylineno);
		yyval.exp = new OpNode(PEBL_SUBTRACT, tmpNode, yyvsp[0].exp, sourcefilename, yylineno); ;}
    break;

  case 32:
#line 305 "src/base/grammar.y"
    {yyval.exp = new OpNode(PEBL_NOT, yyvsp[0].exp, NULL, sourcefilename, yylineno); ;}
    break;

  case 33:
#line 308 "src/base/grammar.y"
    { yyval.exp = new OpNode(PEBL_ADD, yyvsp[-3].exp, yyvsp[0].exp, sourcefilename, yylineno);  ;}
    break;

  case 34:
#line 312 "src/base/grammar.y"
    { yyval.exp = new OpNode(PEBL_DIVIDE,yyvsp[-3].exp, yyvsp[0].exp, sourcefilename, yylineno);  ;}
    break;

  case 35:
#line 315 "src/base/grammar.y"
    { yyval.exp = new OpNode(PEBL_MULTIPLY, yyvsp[-3].exp, yyvsp[0].exp, sourcefilename, yylineno);;}
    break;

  case 36:
#line 318 "src/base/grammar.y"
    { yyval.exp = new OpNode(PEBL_SUBTRACT, yyvsp[-3].exp, yyvsp[0].exp, sourcefilename, yylineno); ;}
    break;

  case 37:
#line 321 "src/base/grammar.y"
    { yyval.exp = new OpNode(PEBL_OR, yyvsp[-3].exp, yyvsp[0].exp, sourcefilename, yylineno); ;}
    break;

  case 38:
#line 324 "src/base/grammar.y"
    { yyval.exp = new OpNode(PEBL_AND, yyvsp[-3].exp, yyvsp[0].exp, sourcefilename, yylineno); ;}
    break;

  case 39:
#line 328 "src/base/grammar.y"
    { yyval.exp = new OpNode(PEBL_LT,  yyvsp[-2].exp, yyvsp[0].exp, sourcefilename, yylineno);;}
    break;

  case 40:
#line 331 "src/base/grammar.y"
    { yyval.exp = new OpNode(PEBL_GT,  yyvsp[-2].exp, yyvsp[0].exp, sourcefilename, yylineno);;}
    break;

  case 41:
#line 334 "src/base/grammar.y"
    { yyval.exp = new OpNode(PEBL_GE,  yyvsp[-2].exp, yyvsp[0].exp, sourcefilename, yylineno);;}
    break;

  case 42:
#line 337 "src/base/grammar.y"
    { yyval.exp = new OpNode(PEBL_LE,  yyvsp[-2].exp, yyvsp[0].exp, sourcefilename, yylineno);;}
    break;

  case 43:
#line 340 "src/base/grammar.y"
    { yyval.exp = new OpNode(PEBL_EQ,  yyvsp[-2].exp, yyvsp[0].exp, sourcefilename, yylineno);;}
    break;

  case 44:
#line 343 "src/base/grammar.y"
    { yyval.exp = new OpNode(PEBL_NE,  yyvsp[-2].exp, yyvsp[0].exp, sourcefilename, yylineno);;}
    break;

  case 45:
#line 352 "src/base/grammar.y"
    {
		PNode * tmpNode = new DataNode(Variant(yyvsp[-1].function, P_DATA_FUNCTION), sourcefilename, yylineno);
		yyval.exp = new OpNode(PEBL_FUNCTION, tmpNode, yyvsp[0].exp, sourcefilename, yylineno);
		;}
    break;

  case 46:
#line 362 "src/base/grammar.y"
    { yyval.exp = new DataNode (yyvsp[0].iValue, sourcefilename, yylineno); ;}
    break;

  case 47:
#line 365 "src/base/grammar.y"
    { yyval.exp = new DataNode (yyvsp[0].fValue, sourcefilename, yylineno);;}
    break;

  case 48:
#line 368 "src/base/grammar.y"
    {
		Variant tmpV(yyvsp[0].strValue);            /*create a new temporary variant*/
		yyval.exp = new DataNode(tmpV, sourcefilename, yylineno);
                                          ;}
    break;

  case 49:
#line 373 "src/base/grammar.y"
    { yyval.exp = yyvsp[0].exp;;}
    break;

  case 50:
#line 376 "src/base/grammar.y"
    { yyval.exp = yyvsp[0].exp;;}
    break;

  case 51:
#line 381 "src/base/grammar.y"
    { 
		Variant tmpV(yyvsp[0].symbol, P_DATA_LOCALVARIABLE);           /*create a new temporary variant*/;
		yyval.exp = new DataNode(tmpV, sourcefilename, yylineno); ;}
    break;

  case 52:
#line 384 "src/base/grammar.y"
    { 
		Variant tmpV(yyvsp[0].symbol, P_DATA_GLOBALVARIABLE);          /*create a new temporary variant*/;
		yyval.exp = new DataNode(tmpV, sourcefilename, yylineno); ;}
    break;

  case 53:
#line 389 "src/base/grammar.y"
    {/*nothing*/;;}
    break;

  case 54:
#line 390 "src/base/grammar.y"
    {/**/;;}
    break;

  case 55:
#line 394 "src/base/grammar.y"
    {/**/;;}
    break;

  case 56:
#line 395 "src/base/grammar.y"
    {/**/;;}
    break;


    }

/* Line 999 of yacc.c.  */
#line 1610 "src/base/grammar.tab.cpp"

  yyvsp -= yylen;
  yyssp -= yylen;


  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;


  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if YYERROR_VERBOSE
      yyn = yypact[yystate];

      if (YYPACT_NINF < yyn && yyn < YYLAST)
	{
	  YYSIZE_T yysize = 0;
	  int yytype = YYTRANSLATE (yychar);
	  char *yymsg;
	  int yyx, yycount;

	  yycount = 0;
	  /* Start YYX at -YYN if negative to avoid negative indexes in
	     YYCHECK.  */
	  for (yyx = yyn < 0 ? -yyn : 0;
	       yyx < (int) (sizeof (yytname) / sizeof (char *)); yyx++)
	    if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	      yysize += yystrlen (yytname[yyx]) + 15, yycount++;
	  yysize += yystrlen ("syntax error, unexpected ") + 1;
	  yysize += yystrlen (yytname[yytype]);
	  yymsg = (char *) YYSTACK_ALLOC (yysize);
	  if (yymsg != 0)
	    {
	      char *yyp = yystpcpy (yymsg, "syntax error, unexpected ");
	      yyp = yystpcpy (yyp, yytname[yytype]);

	      if (yycount < 5)
		{
		  yycount = 0;
		  for (yyx = yyn < 0 ? -yyn : 0;
		       yyx < (int) (sizeof (yytname) / sizeof (char *));
		       yyx++)
		    if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
		      {
			const char *yyq = ! yycount ? ", expecting " : " or ";
			yyp = yystpcpy (yyp, yyq);
			yyp = yystpcpy (yyp, yytname[yyx]);
			yycount++;
		      }
		}
	      yyerror (yymsg);
	      YYSTACK_FREE (yymsg);
	    }
	  else
	    yyerror ("syntax error; also virtual memory exhausted");
	}
      else
#endif /* YYERROR_VERBOSE */
	yyerror ("syntax error");
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      /* Return failure if at end of input.  */
      if (yychar == YYEOF)
        {
	  /* Pop the error token.  */
          YYPOPSTACK;
	  /* Pop the rest of the stack.  */
	  while (yyss < yyssp)
	    {
	      YYDSYMPRINTF ("Error: popping", yystos[*yyssp], yyvsp, yylsp);
	      yydestruct (yystos[*yyssp], yyvsp);
	      YYPOPSTACK;
	    }
	  YYABORT;
        }

      YYDSYMPRINTF ("Error: discarding", yytoken, &yylval, &yylloc);
      yydestruct (yytoken, &yylval);
      yychar = YYEMPTY;

    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*----------------------------------------------------.
| yyerrlab1 -- error raised explicitly by an action.  |
`----------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;

      YYDSYMPRINTF ("Error: popping", yystos[*yyssp], yyvsp, yylsp);
      yydestruct (yystos[yystate], yyvsp);
      yyvsp--;
      yystate = *--yyssp;

      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  YYDPRINTF ((stderr, "Shifting error token, "));

  *++yyvsp = yylval;


  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#ifndef yyoverflow
/*----------------------------------------------.
| yyoverflowlab -- parser overflow comes here.  |
`----------------------------------------------*/
yyoverflowlab:
  yyerror ("parser stack overflow");
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  return yyresult;
}


#line 401 "src/base/grammar.y"


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
  yylineno = 0;

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


