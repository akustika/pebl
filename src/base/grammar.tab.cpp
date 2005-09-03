/* A Bison parser, made by GNU Bison 2.0.  */

/* Skeleton parser for Yacc-like parsing with Bison,
   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004 Free Software Foundation, Inc.

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
/* Line 190 of yacc.c.  */
#line 223 "src/base/grammar.tab.cpp"
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 213 of yacc.c.  */
#line 235 "src/base/grammar.tab.cpp"

#if ! defined (yyoverflow) || YYERROR_VERBOSE

# ifndef YYFREE
#  define YYFREE free
# endif
# ifndef YYMALLOC
#  define YYMALLOC malloc
# endif

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   else
#    define YYSTACK_ALLOC alloca
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
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
# endif
#endif /* ! defined (yyoverflow) || YYERROR_VERBOSE */


#if (! defined (yyoverflow) \
     && (! defined (__cplusplus) \
	 || (defined (YYSTYPE_IS_TRIVIAL) && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  short int yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (short int) + sizeof (YYSTYPE))			\
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined (__GNUC__) && 1 < __GNUC__
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
   typedef short int yysigned_char;
#endif

/* YYFINAL -- State number of the termination state. */
#define YYFINAL  5
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   479

/* YYNTOKENS -- Number of terminals. */
#define YYNTOKENS  57
/* YYNNTS -- Number of nonterminals. */
#define YYNNTS  18
/* YYNRULES -- Number of rules. */
#define YYNRULES  57
/* YYNRULES -- Number of states. */
#define YYNSTATES  147

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   311

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
      55,    56
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const unsigned char yyprhs[] =
{
       0,     0,     3,     7,    11,    19,    26,    28,    33,    36,
      41,    47,    49,    53,    56,    59,    64,    69,    77,    85,
      96,   106,   109,   112,   117,   122,   126,   128,   133,   135,
     140,   142,   148,   151,   154,   159,   164,   169,   174,   179,
     184,   188,   192,   196,   200,   204,   208,   211,   213,   215,
     217,   219,   221,   223,   225,   226,   228,   230
};

/* YYRHS -- A `-1'-separated list of the rules' RHS. */
static const yysigned_char yyrhs[] =
{
      58,     0,    -1,    73,    59,    73,    -1,    58,    59,    73,
      -1,     9,    55,    30,    69,    41,    73,    60,    -1,     9,
      55,    30,    41,    73,    60,    -1,    62,    -1,    23,    73,
      61,    39,    -1,    65,    73,    -1,    63,    73,    65,    73,
      -1,    23,    73,    63,    73,    39,    -1,    64,    -1,    63,
      73,    64,    -1,    70,    34,    -1,     7,    34,    -1,    53,
       6,    70,    34,    -1,    54,     6,    70,    34,    -1,    48,
      30,    70,    41,    73,    62,    34,    -1,    20,    30,    70,
      41,    73,    62,    34,    -1,    20,    30,    70,    41,    73,
      62,    12,    73,    62,    34,    -1,    29,    30,    72,     8,
      70,    41,    73,    62,    34,    -1,    38,    64,    -1,    30,
      41,    -1,    30,    73,    68,    41,    -1,    24,    73,    68,
      40,    -1,    24,    73,    40,    -1,    70,    -1,    70,     8,
      73,    68,    -1,    72,    -1,    72,     8,    73,    69,    -1,
      71,    -1,    30,    73,    70,    73,    41,    -1,    42,    70,
      -1,    35,    70,    -1,    70,     4,    73,    70,    -1,    70,
      10,    73,    70,    -1,    70,    32,    73,    70,    -1,    70,
      42,    73,    70,    -1,    70,    36,    73,    70,    -1,    70,
       3,    73,    70,    -1,    70,    31,    70,    -1,    70,    19,
      70,    -1,    70,    18,    70,    -1,    70,    25,    70,    -1,
      70,    15,    70,    -1,    70,    33,    70,    -1,    55,    66,
      -1,    50,    -1,    49,    -1,    51,    -1,    67,    -1,    72,
      -1,    53,    -1,    54,    -1,    -1,    74,    -1,    34,    -1,
      74,    34,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const unsigned short int yyrline[] =
{
       0,   118,   118,   126,   134,   143,   155,   156,   160,   161,
     165,   171,   174,   184,   186,   188,   197,   205,   218,   224,
     240,   247,   257,   261,   271,   274,   278,   282,   290,   294,
     300,   303,   306,   312,   315,   319,   322,   325,   328,   331,
     335,   338,   341,   344,   347,   350,   359,   369,   372,   375,
     382,   385,   390,   395,   402,   403,   407,   408
};
#endif

#if YYDEBUG || YYERROR_VERBOSE
/* YYTNME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals. */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "PEBL_AND", "PEBL_ADD", "PEBL_ARGLIST",
  "PEBL_ASSIGN", "PEBL_BREAK", "PEBL_COMMA", "PEBL_DEFINE", "PEBL_DIVIDE",
  "PEBL_DOT", "PEBL_ELSE", "PEBL_END", "PEBL_EOF", "PEBL_EQ",
  "PEBL_FUNCTION", "PEBL_FUNCTIONS", "PEBL_GE", "PEBL_GT", "PEBL_IF",
  "PEBL_IFELSE", "PEBL_LAMBDAFUNCTION", "PEBL_LBRACE", "PEBL_LBRACKET",
  "PEBL_LE", "PEBL_LIBRARYFUNCTION", "PEBL_LISTHEAD", "PEBL_LISTITEM",
  "PEBL_LOOP", "PEBL_LPAREN", "PEBL_LT", "PEBL_MULTIPLY", "PEBL_NE",
  "PEBL_NEWLINE", "PEBL_NOT", "PEBL_OR", "PEBL_POWER", "PEBL_RETURN",
  "PEBL_RBRACE", "PEBL_RBRACKET", "PEBL_RPAREN", "PEBL_SUBTRACT",
  "PEBL_SEMI", "PEBL_STATEMENTS", "PEBL_START", "PEBL_VARIABLEDATUM",
  "PEBL_VARLIST", "PEBL_WHILE", "PEBL_FLOAT", "PEBL_INTEGER",
  "PEBL_STRING", "PEBL_SYMBOL", "PEBL_LOCALVAR", "PEBL_GLOBALVAR",
  "PEBL_FUNCTIONNAME", "PEBL_UMINUS", "$accept", "functions", "function",
  "functionblock", "functionsequence", "block", "sequence", "statement",
  "returnstatement", "arglist", "list", "explist", "varlist", "exp",
  "datum", "variable", "nlornone", "newlines", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const unsigned short int yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const unsigned char yyr1[] =
{
       0,    57,    58,    58,    59,    59,    60,    60,    61,    61,
      62,    63,    63,    64,    64,    64,    64,    64,    64,    64,
      64,    65,    66,    66,    67,    67,    68,    68,    69,    69,
      70,    70,    70,    70,    70,    70,    70,    70,    70,    70,
      70,    70,    70,    70,    70,    70,    70,    71,    71,    71,
      71,    71,    72,    72,    73,    73,    74,    74
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const unsigned char yyr2[] =
{
       0,     2,     3,     3,     7,     6,     1,     4,     2,     4,
       5,     1,     3,     2,     2,     4,     4,     7,     7,    10,
       9,     2,     2,     4,     4,     3,     1,     4,     1,     4,
       1,     5,     2,     2,     4,     4,     4,     4,     4,     4,
       3,     3,     3,     3,     3,     3,     2,     1,     1,     1,
       1,     1,     1,     1,     0,     1,     1,     2
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const unsigned char yydefact[] =
{
      54,    56,     0,     0,    55,     1,     0,    54,    54,    57,
       0,     3,     2,     0,    54,    52,    53,     0,    28,     0,
      54,    54,    54,     5,     6,     0,     0,     0,     4,    29,
       0,     0,    54,     0,    54,     0,     0,     0,     0,    48,
      47,    49,    52,    53,     0,     0,    54,    11,    54,    50,
       0,    30,    51,    14,     0,     0,     0,     0,    33,    21,
      32,     0,     0,     0,    54,    46,     7,     0,     8,    54,
      54,    54,     0,     0,     0,     0,     0,    54,     0,    13,
      54,    54,     0,    25,     0,    26,     0,    54,     0,     0,
       0,    22,     0,    10,    12,    54,     0,     0,     0,    44,
      42,    41,    43,    40,     0,    45,     0,     0,    54,    24,
      54,     0,     0,    54,    15,    16,     0,     9,    39,    34,
      35,    36,    38,    37,     0,     0,     0,    31,     0,    23,
      54,     0,    27,    54,     0,     0,    54,    18,     0,    17,
      54,     0,     0,     0,     0,    20,    19
};

/* YYDEFGOTO[NTERM-NUM]. */
static const yysigned_char yydefgoto[] =
{
      -1,     2,     7,    23,    45,    24,    46,    47,    48,    65,
      49,    84,    17,    50,    51,    52,     3,     4
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -99
static const short int yypact[] =
{
     -26,   -99,    11,    10,   -13,   -99,   -31,   -26,   -26,   -99,
      18,   -99,   -99,   -36,   -26,   -99,   -99,     8,    51,    37,
     -26,   -26,   -26,   -99,   -99,    37,   -18,   150,   -99,   -99,
      31,    36,   -26,    38,   -26,   424,   218,   424,    39,   -99,
     -99,   -99,    61,    65,    42,    40,   -26,   -99,   -26,   -99,
      19,   -99,   -99,   -99,   424,   407,   -18,   424,   403,   -99,
     -99,   424,   424,   424,    13,   -99,   -99,   114,   -99,   -26,
     -26,   -26,   424,   424,   424,   424,   424,   -26,   424,   -99,
     -26,   -26,   260,   -99,    41,   279,    69,   304,   324,   344,
     364,   -99,   424,   -99,   -99,   -26,   424,   424,   424,     0,
       0,     0,     0,     0,   424,     0,   424,   424,   -26,   -99,
     -26,   424,    44,   -26,   -99,   -99,    45,   -99,   403,    -4,
     -99,   -99,   403,    -4,    64,   424,   384,   -99,    64,   -99,
     -26,    -3,   -99,   -26,    55,   218,   -26,   -99,    64,   -99,
     -26,    64,    56,   182,    57,   -99,   -99
};

/* YYPGOTO[NTERM-NUM].  */
static const yysigned_char yypgoto[] =
{
     -99,   -99,    89,    73,   -99,   -98,   -35,   -34,    35,   -99,
     -99,   -80,    78,    21,   -99,   -10,    -7,   -99
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const unsigned char yytable[] =
{
      11,    12,    59,    18,    70,    14,    71,    19,     1,   136,
      71,     5,   116,    25,    26,    27,    18,    15,    16,     6,
       6,     9,    69,    70,    10,    55,   131,    57,    77,    71,
     134,   137,    77,    94,    72,    15,    16,    73,    74,    67,
     142,    68,    81,   144,    75,   132,    86,     1,    13,    20,
      76,    77,    78,    79,    91,    80,    58,    92,    60,    21,
      22,    81,    96,    97,    98,    53,    54,    62,    56,    61,
     104,    63,    64,   106,   107,    82,    85,   111,    87,    66,
     112,   109,    88,    89,    90,   127,   129,   130,   117,   139,
     145,   146,     8,    99,   100,   101,   102,   103,    28,   105,
     140,   124,    95,   125,    29,     0,   128,     0,     0,    94,
       0,     0,     0,    85,     0,     0,     0,   118,   119,   120,
       0,    30,     0,   135,     0,   121,   138,   122,   123,   141,
       0,     0,   126,   143,    31,     0,     0,     0,    32,     0,
       0,     0,     0,    33,    34,     0,    85,     0,     0,    35,
       0,     0,    36,    93,     0,     0,    37,    30,     0,     0,
       0,     0,    38,    39,    40,    41,     0,    42,    43,    44,
      31,     0,     0,     0,    32,     0,     0,     0,     0,    33,
      34,     0,     0,     0,     0,    35,     0,     0,    36,    30,
       0,     0,    37,     0,     0,     0,     0,     0,    38,    39,
      40,    41,    31,    42,    43,    44,    32,     0,     0,     0,
       0,    33,    34,     0,     0,     0,     0,    35,     0,     0,
       0,    93,     0,     0,    37,    30,     0,     0,     0,     0,
      38,    39,    40,    41,     0,    42,    43,    44,    31,     0,
       0,     0,    32,     0,     0,     0,     0,    33,    34,     0,
       0,     0,     0,    35,     0,     0,     0,     0,     0,     0,
      37,     0,     0,    69,    70,     0,    38,    39,    40,    41,
      71,    42,    43,    44,     0,    72,     0,     0,    73,    74,
       0,     0,    69,    70,     0,    75,     0,   110,     0,    71,
       0,    76,    77,    78,    72,     0,    80,    73,    74,     0,
       0,   108,    81,     0,    75,     0,     0,    69,    70,     0,
      76,    77,    78,     0,    71,    80,     0,     0,     0,    72,
       0,    81,    73,    74,     0,     0,     0,    69,    70,    75,
       0,     0,     0,     0,    71,    76,    77,    78,     1,    72,
      80,     0,    73,    74,     0,     0,    81,    69,    70,    75,
       0,     0,     0,     0,    71,    76,    77,    78,     0,    72,
      80,     0,    73,    74,     0,   113,    81,    69,    70,    75,
       0,     0,     0,     0,    71,    76,    77,    78,   114,    72,
      80,     0,    73,    74,     0,     0,    81,    69,    70,    75,
       0,     0,     0,     0,    71,    76,    77,    78,   115,    72,
      80,     0,    73,    74,     0,     0,    81,    70,     0,    75,
       0,     0,     0,    71,     0,    76,    77,    78,    72,     0,
      80,    73,    74,     0,     0,   133,    81,     0,    75,     0,
       0,    32,     0,     0,    76,    77,    78,    34,     0,     0,
       0,     0,    35,     0,     0,    81,     0,    83,    32,    37,
       0,     0,     0,     0,    34,     0,    39,    40,    41,    35,
      15,    16,    44,     0,     0,     0,    37,     0,     0,     0,
       0,     0,     0,    39,    40,    41,     0,    15,    16,    44
};

static const short int yycheck[] =
{
       7,     8,    36,    13,     4,    41,    10,    14,    34,    12,
      10,     0,    92,    20,    21,    22,    26,    53,    54,     9,
       9,    34,     3,     4,    55,    32,   124,    34,    32,    10,
     128,    34,    32,    67,    15,    53,    54,    18,    19,    46,
     138,    48,    42,   141,    25,   125,    56,    34,    30,    41,
      31,    32,    33,    34,    41,    36,    35,    64,    37,     8,
      23,    42,    69,    70,    71,    34,    30,     6,    30,    30,
      77,     6,    30,    80,    81,    54,    55,     8,    57,    39,
      87,    40,    61,    62,    63,    41,    41,    23,    95,    34,
      34,    34,     3,    72,    73,    74,    75,    76,    25,    78,
     135,   108,    67,   110,    26,    -1,   113,    -1,    -1,   143,
      -1,    -1,    -1,    92,    -1,    -1,    -1,    96,    97,    98,
      -1,     7,    -1,   130,    -1,   104,   133,   106,   107,   136,
      -1,    -1,   111,   140,    20,    -1,    -1,    -1,    24,    -1,
      -1,    -1,    -1,    29,    30,    -1,   125,    -1,    -1,    35,
      -1,    -1,    38,    39,    -1,    -1,    42,     7,    -1,    -1,
      -1,    -1,    48,    49,    50,    51,    -1,    53,    54,    55,
      20,    -1,    -1,    -1,    24,    -1,    -1,    -1,    -1,    29,
      30,    -1,    -1,    -1,    -1,    35,    -1,    -1,    38,     7,
      -1,    -1,    42,    -1,    -1,    -1,    -1,    -1,    48,    49,
      50,    51,    20,    53,    54,    55,    24,    -1,    -1,    -1,
      -1,    29,    30,    -1,    -1,    -1,    -1,    35,    -1,    -1,
      -1,    39,    -1,    -1,    42,     7,    -1,    -1,    -1,    -1,
      48,    49,    50,    51,    -1,    53,    54,    55,    20,    -1,
      -1,    -1,    24,    -1,    -1,    -1,    -1,    29,    30,    -1,
      -1,    -1,    -1,    35,    -1,    -1,    -1,    -1,    -1,    -1,
      42,    -1,    -1,     3,     4,    -1,    48,    49,    50,    51,
      10,    53,    54,    55,    -1,    15,    -1,    -1,    18,    19,
      -1,    -1,     3,     4,    -1,    25,    -1,     8,    -1,    10,
      -1,    31,    32,    33,    15,    -1,    36,    18,    19,    -1,
      -1,    41,    42,    -1,    25,    -1,    -1,     3,     4,    -1,
      31,    32,    33,    -1,    10,    36,    -1,    -1,    -1,    15,
      -1,    42,    18,    19,    -1,    -1,    -1,     3,     4,    25,
      -1,    -1,    -1,    -1,    10,    31,    32,    33,    34,    15,
      36,    -1,    18,    19,    -1,    -1,    42,     3,     4,    25,
      -1,    -1,    -1,    -1,    10,    31,    32,    33,    -1,    15,
      36,    -1,    18,    19,    -1,    41,    42,     3,     4,    25,
      -1,    -1,    -1,    -1,    10,    31,    32,    33,    34,    15,
      36,    -1,    18,    19,    -1,    -1,    42,     3,     4,    25,
      -1,    -1,    -1,    -1,    10,    31,    32,    33,    34,    15,
      36,    -1,    18,    19,    -1,    -1,    42,     4,    -1,    25,
      -1,    -1,    -1,    10,    -1,    31,    32,    33,    15,    -1,
      36,    18,    19,    -1,    -1,    41,    42,    -1,    25,    -1,
      -1,    24,    -1,    -1,    31,    32,    33,    30,    -1,    -1,
      -1,    -1,    35,    -1,    -1,    42,    -1,    40,    24,    42,
      -1,    -1,    -1,    -1,    30,    -1,    49,    50,    51,    35,
      53,    54,    55,    -1,    -1,    -1,    42,    -1,    -1,    -1,
      -1,    -1,    -1,    49,    50,    51,    -1,    53,    54,    55
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const unsigned char yystos[] =
{
       0,    34,    58,    73,    74,     0,     9,    59,    59,    34,
      55,    73,    73,    30,    41,    53,    54,    69,    72,    73,
      41,     8,    23,    60,    62,    73,    73,    73,    60,    69,
       7,    20,    24,    29,    30,    35,    38,    42,    48,    49,
      50,    51,    53,    54,    55,    61,    63,    64,    65,    67,
      70,    71,    72,    34,    30,    73,    30,    73,    70,    64,
      70,    30,     6,     6,    30,    66,    39,    73,    73,     3,
       4,    10,    15,    18,    19,    25,    31,    32,    33,    34,
      36,    42,    70,    40,    68,    70,    72,    70,    70,    70,
      70,    41,    73,    39,    64,    65,    73,    73,    73,    70,
      70,    70,    70,    70,    73,    70,    73,    73,    41,    40,
       8,     8,    73,    41,    34,    34,    68,    73,    70,    70,
      70,    70,    70,    70,    73,    73,    70,    41,    73,    41,
      23,    62,    68,    41,    62,    73,    12,    34,    73,    34,
      63,    73,    62,    73,    62,    34,    34
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
#define YYERROR		goto yyerrorlab


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


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (N)								\
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (0)
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
              (Loc).first_line, (Loc).first_column,	\
              (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
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

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)		\
do {								\
  if (yydebug)							\
    {								\
      YYFPRINTF (stderr, "%s ", Title);				\
      yysymprint (stderr, 					\
                  Type, Value);	\
      YYFPRINTF (stderr, "\n");					\
    }								\
} while (0)

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yy_stack_print (short int *bottom, short int *top)
#else
static void
yy_stack_print (bottom, top)
    short int *bottom;
    short int *top;
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
  unsigned int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %u), ",
             yyrule - 1, yylno);
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
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
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
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);


# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
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
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  /* Pacify ``unused variable'' warnings.  */
  (void) yyvaluep;

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

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



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
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
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  short int yyssa[YYINITDEPTH];
  short int *yyss = yyssa;
  register short int *yyssp;

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


  yyvsp[0] = yylval;

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
	short int *yyss1 = yyss;


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
	short int *yyss1 = yyss;
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
/* Read a look-ahead token if we need one and don't already have one.  */
/* yyresume: */

  /* First try to decide what to do without reference to look-ahead token.  */

  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
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
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
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

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

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
#line 118 "src/base/grammar.y"
    {gParseTreeHead =  new OpNode(PEBL_FUNCTIONS,(yyvsp[-1].exp),NULL, sourcefilename, yylineno);

		           (yyval.exp) = gParseTreeHead;
		;}
    break;

  case 3:
#line 126 "src/base/grammar.y"
    { gParseTreeHead = new OpNode(PEBL_FUNCTIONS, (yyvsp[-1].exp), (yyvsp[-2].exp), sourcefilename, yylineno);
		           (yyval.exp) = gParseTreeHead;
		;}
    break;

  case 4:
#line 134 "src/base/grammar.y"
    { ;
		PNode * tmpFN = new OpNode(PEBL_LAMBDAFUNCTION, (yyvsp[-3].exp), (yyvsp[0].exp), sourcefilename, yylineno);  
		PNode * tmpNode = new DataNode(Variant((yyvsp[-5].function), P_DATA_FUNCTION), sourcefilename, yylineno);
		free((yyvsp[-5].function));
		(yyval.exp) = new OpNode(PEBL_FUNCTION, tmpNode, tmpFN, sourcefilename, yylineno);

        ;}
    break;

  case 5:
#line 143 "src/base/grammar.y"
    { ;
		PNode * tmpFN = new OpNode(PEBL_LAMBDAFUNCTION, NULL, (yyvsp[0].exp), sourcefilename, yylineno);  
		PNode * tmpNode = new DataNode(Variant((yyvsp[-4].function), P_DATA_FUNCTION), sourcefilename, yylineno);
		(yyval.exp) = new OpNode(PEBL_FUNCTION, tmpNode, tmpFN, sourcefilename, yylineno);
        free((yyvsp[-4].function));
		  ;}
    break;

  case 6:
#line 155 "src/base/grammar.y"
    {(yyval.exp) = (yyvsp[0].exp);;}
    break;

  case 7:
#line 156 "src/base/grammar.y"
    {(yyval.exp) = (yyvsp[-1].exp);;}
    break;

  case 8:
#line 160 "src/base/grammar.y"
    { (yyval.exp) = (yyvsp[-1].exp);;}
    break;

  case 9:
#line 161 "src/base/grammar.y"
    { (yyval.exp) = new OpNode(PEBL_STATEMENTS, (yyvsp[-3].exp), (yyvsp[-1].exp), sourcefilename, yylineno);;}
    break;

  case 10:
#line 165 "src/base/grammar.y"
    { (yyval.exp) = (yyvsp[-2].exp);;}
    break;

  case 11:
#line 171 "src/base/grammar.y"
    { (yyval.exp) = (yyvsp[0].exp); ;}
    break;

  case 12:
#line 174 "src/base/grammar.y"
    { (yyval.exp) = new OpNode(PEBL_STATEMENTS, (yyvsp[-2].exp), (yyvsp[0].exp), sourcefilename, yylineno);;}
    break;

  case 13:
#line 184 "src/base/grammar.y"
    {(yyval.exp) = (yyvsp[-1].exp);;}
    break;

  case 14:
#line 186 "src/base/grammar.y"
    {(yyval.exp) = new OpNode(PEBL_BREAK, NULL, NULL, sourcefilename, yylineno);;}
    break;

  case 15:
#line 189 "src/base/grammar.y"
    { 
	        Variant tmpV((yyvsp[-3].symbol),P_DATA_LOCALVARIABLE);       /*create a new temporary variant*/
		    free((yyvsp[-3].symbol));
			PNode * tmpNode = new DataNode(tmpV, sourcefilename, yylineno);        /*create basic pnode*/
		    (yyval.exp) = new OpNode(PEBL_ASSIGN, tmpNode, (yyvsp[-1].exp), sourcefilename, yylineno);   /*Use symbol node in assignment node*/
		;}
    break;

  case 16:
#line 198 "src/base/grammar.y"
    { 
	        Variant tmpV((yyvsp[-3].symbol),P_DATA_GLOBALVARIABLE);      /*create a new temporary variant*/
		PNode * tmpNode = new DataNode(tmpV, sourcefilename, yylineno);        /*create basic pnode*/
		(yyval.exp) = new OpNode(PEBL_ASSIGN, tmpNode, (yyvsp[-1].exp), sourcefilename, yylineno);   /*Use symbol node in assignment node*/
		;}
    break;

  case 17:
#line 205 "src/base/grammar.y"
    {;
		(yyval.exp) = new OpNode(PEBL_WHILE, (yyvsp[-4].exp), (yyvsp[-1].exp), sourcefilename, yylineno); ;}
    break;

  case 18:
#line 218 "src/base/grammar.y"
    {
		(yyval.exp) = new OpNode(PEBL_IF, (yyvsp[-4].exp), (yyvsp[-1].exp), sourcefilename, yylineno); ;}
    break;

  case 19:
#line 224 "src/base/grammar.y"
    {
		/*First make the else node*/
		PNode * tmpNode = new OpNode(PEBL_ELSE, (yyvsp[-4].exp), (yyvsp[-1].exp), sourcefilename, yylineno);
		/*Put the else node in the IF node*/
		(yyval.exp) = new OpNode(PEBL_IFELSE, (yyvsp[-7].exp), tmpNode, sourcefilename, yylineno); ;}
    break;

  case 20:
#line 240 "src/base/grammar.y"
    {
		PNode * tmpNode = new OpNode(PEBL_VARIABLEDATUM, (yyvsp[-6].exp), (yyvsp[-4].exp), sourcefilename, yylineno);
		(yyval.exp) = new OpNode(PEBL_LOOP, tmpNode, (yyvsp[-1].exp), sourcefilename, yylineno); ;}
    break;

  case 21:
#line 247 "src/base/grammar.y"
    {(yyval.exp) = new OpNode(PEBL_RETURN, (yyvsp[0].exp), NULL, sourcefilename, yylineno);;}
    break;

  case 22:
#line 257 "src/base/grammar.y"
    {(yyval.exp) = new OpNode(PEBL_ARGLIST, NULL, NULL, sourcefilename, yylineno);;}
    break;

  case 23:
#line 261 "src/base/grammar.y"
    {(yyval.exp) = new OpNode(PEBL_ARGLIST, (yyvsp[-1].exp), NULL, sourcefilename, yylineno);;}
    break;

  case 24:
#line 271 "src/base/grammar.y"
    {(yyval.exp) = new OpNode(PEBL_LISTHEAD,(yyvsp[-1].exp), NULL, sourcefilename, yylineno);;}
    break;

  case 25:
#line 274 "src/base/grammar.y"
    {(yyval.exp) = new OpNode(PEBL_LISTHEAD, NULL, NULL, sourcefilename, yylineno);;}
    break;

  case 26:
#line 278 "src/base/grammar.y"
    {(yyval.exp) = new OpNode(PEBL_LISTITEM, (yyvsp[0].exp), NULL, sourcefilename, yylineno);;}
    break;

  case 27:
#line 282 "src/base/grammar.y"
    {(yyval.exp) = new OpNode(PEBL_LISTITEM, (yyvsp[-3].exp), (yyvsp[0].exp), sourcefilename, yylineno);;}
    break;

  case 28:
#line 290 "src/base/grammar.y"
    {(yyval.exp) = new OpNode(PEBL_VARLIST, (yyvsp[0].exp), NULL, sourcefilename, yylineno);;}
    break;

  case 29:
#line 294 "src/base/grammar.y"
    {(yyval.exp) = new OpNode(PEBL_VARLIST,(yyvsp[-3].exp),(yyvsp[0].exp), sourcefilename, yylineno);;}
    break;

  case 30:
#line 300 "src/base/grammar.y"
    { (yyval.exp) = (yyvsp[0].exp);;}
    break;

  case 31:
#line 303 "src/base/grammar.y"
    {(yyval.exp) = (yyvsp[-2].exp);}
    break;

  case 32:
#line 306 "src/base/grammar.y"
    {
		Variant tmpV = 0;
		PNode * tmpNode = new DataNode(tmpV, sourcefilename, yylineno);
		(yyval.exp) = new OpNode(PEBL_SUBTRACT, tmpNode, (yyvsp[0].exp), sourcefilename, yylineno); ;}
    break;

  case 33:
#line 312 "src/base/grammar.y"
    {(yyval.exp) = new OpNode(PEBL_NOT, (yyvsp[0].exp), NULL, sourcefilename, yylineno); ;}
    break;

  case 34:
#line 315 "src/base/grammar.y"
    { (yyval.exp) = new OpNode(PEBL_ADD, (yyvsp[-3].exp), (yyvsp[0].exp), sourcefilename, yylineno);  ;}
    break;

  case 35:
#line 319 "src/base/grammar.y"
    { (yyval.exp) = new OpNode(PEBL_DIVIDE,(yyvsp[-3].exp), (yyvsp[0].exp), sourcefilename, yylineno);  ;}
    break;

  case 36:
#line 322 "src/base/grammar.y"
    { (yyval.exp) = new OpNode(PEBL_MULTIPLY, (yyvsp[-3].exp), (yyvsp[0].exp), sourcefilename, yylineno);;}
    break;

  case 37:
#line 325 "src/base/grammar.y"
    { (yyval.exp) = new OpNode(PEBL_SUBTRACT, (yyvsp[-3].exp), (yyvsp[0].exp), sourcefilename, yylineno); ;}
    break;

  case 38:
#line 328 "src/base/grammar.y"
    { (yyval.exp) = new OpNode(PEBL_OR, (yyvsp[-3].exp), (yyvsp[0].exp), sourcefilename, yylineno); ;}
    break;

  case 39:
#line 331 "src/base/grammar.y"
    { (yyval.exp) = new OpNode(PEBL_AND, (yyvsp[-3].exp), (yyvsp[0].exp), sourcefilename, yylineno); ;}
    break;

  case 40:
#line 335 "src/base/grammar.y"
    { (yyval.exp) = new OpNode(PEBL_LT,  (yyvsp[-2].exp), (yyvsp[0].exp), sourcefilename, yylineno);;}
    break;

  case 41:
#line 338 "src/base/grammar.y"
    { (yyval.exp) = new OpNode(PEBL_GT,  (yyvsp[-2].exp), (yyvsp[0].exp), sourcefilename, yylineno);;}
    break;

  case 42:
#line 341 "src/base/grammar.y"
    { (yyval.exp) = new OpNode(PEBL_GE,  (yyvsp[-2].exp), (yyvsp[0].exp), sourcefilename, yylineno);;}
    break;

  case 43:
#line 344 "src/base/grammar.y"
    { (yyval.exp) = new OpNode(PEBL_LE,  (yyvsp[-2].exp), (yyvsp[0].exp), sourcefilename, yylineno);;}
    break;

  case 44:
#line 347 "src/base/grammar.y"
    { (yyval.exp) = new OpNode(PEBL_EQ,  (yyvsp[-2].exp), (yyvsp[0].exp), sourcefilename, yylineno);;}
    break;

  case 45:
#line 350 "src/base/grammar.y"
    { (yyval.exp) = new OpNode(PEBL_NE,  (yyvsp[-2].exp), (yyvsp[0].exp), sourcefilename, yylineno);;}
    break;

  case 46:
#line 359 "src/base/grammar.y"
    {
		PNode * tmpNode = new DataNode(Variant((yyvsp[-1].function), P_DATA_FUNCTION), sourcefilename, yylineno);
		(yyval.exp) = new OpNode(PEBL_FUNCTION, tmpNode, (yyvsp[0].exp), sourcefilename, yylineno);
        free((yyvsp[-1].function));
		;}
    break;

  case 47:
#line 369 "src/base/grammar.y"
    { (yyval.exp) = new DataNode ((yyvsp[0].iValue), sourcefilename, yylineno); ;}
    break;

  case 48:
#line 372 "src/base/grammar.y"
    { (yyval.exp) = new DataNode ((yyvsp[0].fValue), sourcefilename, yylineno);;}
    break;

  case 49:
#line 375 "src/base/grammar.y"
    {
	  Variant tmpV((yyvsp[0].strValue));            /*create a new temporary variant*/
	  free((yyvsp[0].strValue));
	  (yyval.exp) = new DataNode(tmpV, sourcefilename, yylineno);

                        ;}
    break;

  case 50:
#line 382 "src/base/grammar.y"
    { (yyval.exp) = (yyvsp[0].exp);;}
    break;

  case 51:
#line 385 "src/base/grammar.y"
    { (yyval.exp) = (yyvsp[0].exp);;}
    break;

  case 52:
#line 390 "src/base/grammar.y"
    { 
		Variant tmpV((yyvsp[0].symbol), P_DATA_LOCALVARIABLE);           /*create a new temporary variant*/;
		(yyval.exp) = new DataNode(tmpV, sourcefilename, yylineno);                        /*Make a new variable node here.*/
        free((yyvsp[0].symbol));
        ;}
    break;

  case 53:
#line 395 "src/base/grammar.y"
    { 
		Variant tmpV((yyvsp[0].symbol), P_DATA_GLOBALVARIABLE);          /*create a new temporary variant*/;
		(yyval.exp) = new DataNode(tmpV, sourcefilename, yylineno);  /*Make a new variable node here.*/
		free((yyvsp[0].symbol));
		 ;}
    break;

  case 54:
#line 402 "src/base/grammar.y"
    {/*nothing*/;;}
    break;

  case 55:
#line 403 "src/base/grammar.y"
    {/**/;;}
    break;

  case 56:
#line 407 "src/base/grammar.y"
    {/**/;;}
    break;

  case 57:
#line 408 "src/base/grammar.y"
    {/**/;;}
    break;


    }

/* Line 1037 of yacc.c.  */
#line 1668 "src/base/grammar.tab.cpp"

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
	  const char* yyprefix;
	  char *yymsg;
	  int yyx;

	  /* Start YYX at -YYN if negative to avoid negative indexes in
	     YYCHECK.  */
	  int yyxbegin = yyn < 0 ? -yyn : 0;

	  /* Stay within bounds of both yycheck and yytname.  */
	  int yychecklim = YYLAST - yyn;
	  int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
	  int yycount = 0;

	  yyprefix = ", expecting ";
	  for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	    if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	      {
		yysize += yystrlen (yyprefix) + yystrlen (yytname [yyx]);
		yycount += 1;
		if (yycount == 5)
		  {
		    yysize = 0;
		    break;
		  }
	      }
	  yysize += (sizeof ("syntax error, unexpected ")
		     + yystrlen (yytname[yytype]));
	  yymsg = (char *) YYSTACK_ALLOC (yysize);
	  if (yymsg != 0)
	    {
	      char *yyp = yystpcpy (yymsg, "syntax error, unexpected ");
	      yyp = yystpcpy (yyp, yytname[yytype]);

	      if (yycount < 5)
		{
		  yyprefix = ", expecting ";
		  for (yyx = yyxbegin; yyx < yyxend; ++yyx)
		    if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
		      {
			yyp = yystpcpy (yyp, yyprefix);
			yyp = yystpcpy (yyp, yytname[yyx]);
			yyprefix = " or ";
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
      /* If just tried and failed to reuse look-ahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* If at end of input, pop the error token,
	     then the rest of the stack, then return failure.  */
	  if (yychar == YYEOF)
	     for (;;)
	       {

		 YYPOPSTACK;
		 if (yyssp == yyss)
		   YYABORT;
		 yydestruct ("Error: popping",
                             yystos[*yyssp], yyvsp);
	       }
        }
      else
	{
	  yydestruct ("Error: discarding", yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse look-ahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

#ifdef __GNUC__
  /* Pacify GCC when the user code never invokes YYERROR and the label
     yyerrorlab therefore never appears in user code.  */
  if (0)
     goto yyerrorlab;
#endif

yyvsp -= yylen;
  yyssp -= yylen;
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
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


      yydestruct ("Error: popping", yystos[yystate], yyvsp);
      YYPOPSTACK;
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;


  /* Shift the error token. */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

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
  yydestruct ("Error: discarding lookahead",
              yytoken, &yylval);
  yychar = YYEMPTY;
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


#line 414 "src/base/grammar.y"


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


