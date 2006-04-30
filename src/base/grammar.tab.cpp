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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.1a"

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

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

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
/* Line 198 of yacc.c.  */
#line 233 "src/base/grammar.tab.cpp"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 221 of yacc.c.  */
#line 246 "src/base/grammar.tab.cpp"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
            && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
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
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  5
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   441

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  57
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  20
/* YYNRULES -- Number of rules.  */
#define YYNRULES  61
/* YYNRULES -- Number of states.  */
#define YYNSTATES  146

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   311

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
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
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     7,    11,    19,    26,    28,    33,    36,
      41,    47,    51,    57,    59,    63,    66,    69,    71,    74,
      78,    82,    89,    96,   106,   115,   118,   121,   126,   131,
     135,   137,   142,   144,   149,   151,   157,   160,   163,   168,
     173,   178,   183,   188,   193,   197,   201,   205,   209,   213,
     217,   220,   222,   224,   226,   228,   230,   232,   234,   235,
     237,   239
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      58,     0,    -1,    75,    59,    75,    -1,    58,    59,    75,
      -1,     9,    55,    30,    71,    41,    75,    60,    -1,     9,
      55,    30,    41,    75,    60,    -1,    62,    -1,    23,    75,
      61,    39,    -1,    67,    75,    -1,    63,    75,    67,    75,
      -1,    23,    75,    63,    75,    39,    -1,    23,    75,    65,
      -1,    23,    75,    63,    75,    65,    -1,    64,    -1,    63,
      75,    64,    -1,    66,    34,    -1,    66,    39,    -1,    72,
      -1,     7,    34,    -1,    53,     6,    72,    -1,    54,     6,
      72,    -1,    48,    30,    72,    41,    75,    62,    -1,    20,
      30,    72,    41,    75,    62,    -1,    20,    30,    72,    41,
      75,    62,    12,    75,    62,    -1,    29,    30,    74,     8,
      72,    41,    75,    62,    -1,    38,    64,    -1,    30,    41,
      -1,    30,    75,    70,    41,    -1,    24,    75,    70,    40,
      -1,    24,    75,    40,    -1,    72,    -1,    72,     8,    75,
      70,    -1,    74,    -1,    74,     8,    75,    71,    -1,    73,
      -1,    30,    75,    72,    75,    41,    -1,    42,    72,    -1,
      35,    72,    -1,    72,     4,    75,    72,    -1,    72,    10,
      75,    72,    -1,    72,    32,    75,    72,    -1,    72,    42,
      75,    72,    -1,    72,    36,    75,    72,    -1,    72,     3,
      75,    72,    -1,    72,    31,    72,    -1,    72,    19,    72,
      -1,    72,    18,    72,    -1,    72,    25,    72,    -1,    72,
      15,    72,    -1,    72,    33,    72,    -1,    55,    68,    -1,
      50,    -1,    49,    -1,    51,    -1,    69,    -1,    74,    -1,
      53,    -1,    54,    -1,    -1,    76,    -1,    34,    -1,    76,
      34,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   118,   118,   126,   134,   143,   155,   156,   160,   161,
     165,   166,   167,   175,   178,   182,   186,   195,   197,   199,
     208,   216,   229,   235,   251,   258,   268,   272,   282,   285,
     289,   293,   301,   305,   311,   314,   317,   323,   326,   330,
     333,   336,   339,   342,   346,   349,   352,   355,   358,   361,
     370,   380,   383,   386,   393,   396,   401,   406,   413,   414,
     418,   419
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
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
  "endstatement", "ustatement", "returnstatement", "arglist", "list",
  "explist", "varlist", "exp", "datum", "variable", "nlornone", "newlines", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
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
static const yytype_uint8 yyr1[] =
{
       0,    57,    58,    58,    59,    59,    60,    60,    61,    61,
      62,    62,    62,    63,    63,    64,    65,    66,    66,    66,
      66,    66,    66,    66,    66,    67,    68,    68,    69,    69,
      70,    70,    71,    71,    72,    72,    72,    72,    72,    72,
      72,    72,    72,    72,    72,    72,    72,    72,    72,    72,
      72,    73,    73,    73,    73,    73,    74,    74,    75,    75,
      76,    76
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     3,     3,     7,     6,     1,     4,     2,     4,
       5,     3,     5,     1,     3,     2,     2,     1,     2,     3,
       3,     6,     6,     9,     8,     2,     2,     4,     4,     3,
       1,     4,     1,     4,     1,     5,     2,     2,     4,     4,
       4,     4,     4,     4,     3,     3,     3,     3,     3,     3,
       2,     1,     1,     1,     1,     1,     1,     1,     0,     1,
       1,     2
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
      58,    60,     0,     0,    59,     1,     0,    58,    58,    61,
       0,     3,     2,     0,    58,    56,    57,     0,    32,     0,
      58,    58,    58,     5,     6,     0,     0,     0,     4,    33,
       0,     0,    58,     0,    58,     0,     0,     0,     0,    52,
      51,    53,    56,    57,     0,     0,    58,    13,    11,     0,
      58,    54,    17,    34,    55,    18,     0,     0,     0,     0,
      37,    25,     0,    36,     0,     0,     0,    58,    50,     7,
       0,    15,    16,     8,    58,    58,    58,     0,     0,     0,
       0,     0,    58,     0,    58,    58,     0,    29,     0,    30,
       0,    58,     0,    19,    20,    26,     0,    10,    14,    12,
      58,     0,     0,     0,    48,    46,    45,    47,    44,     0,
      49,     0,     0,    58,    28,    58,     0,     0,    58,     0,
       9,    43,    38,    39,    40,    42,    41,     0,     0,     0,
      35,     0,    27,    58,    22,    31,    58,    21,     0,    58,
       0,    58,     0,    24,     0,    23
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     2,     7,    23,    45,    24,    46,    47,    48,    49,
      50,    68,    51,    88,    17,    52,    53,    54,     3,     4
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -94
static const yytype_int16 yypact[] =
{
     -22,   -94,    17,    13,    10,   -94,   -10,   -22,   -22,   -94,
       3,   -94,   -94,   -33,   -22,   -94,   -94,     5,    50,    36,
     -22,   -22,   -22,   -94,   -94,    36,   -23,   132,   -94,   -94,
      27,    33,   -22,    41,   -22,   386,   200,   386,    43,   -94,
     -94,   -94,    59,    68,    46,    42,   -22,   -94,   -94,    23,
     -22,   -94,   346,   -94,   -94,   -94,   386,   369,   -23,   386,
     365,   -94,    48,   -94,   386,   386,   386,   -25,   -94,   -94,
      -1,   -94,   -94,   -94,   -22,   -22,   -22,   386,   386,   386,
     386,   386,   -22,   386,   -22,   -22,   242,   -94,    40,   261,
      75,   286,   306,   346,   346,   -94,   386,   -94,   -94,   -94,
     -22,   386,   386,   386,     0,     0,     0,     0,     0,   386,
       0,   386,   386,   -22,   -94,   -22,   386,    44,   -22,    45,
     -94,   365,     8,   -94,   -94,   365,     8,    64,   386,   326,
     -94,    64,   -94,   -22,    76,   -94,   -22,   -94,   200,   -22,
      64,   -22,    64,   -94,   164,   -94
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -94,   -94,    86,    65,   -94,   -76,   -43,   -34,   -65,    60,
      28,   -94,   -94,   -93,    71,    35,   -94,    -2,    -7,   -94
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      11,    12,    61,   119,    75,    99,    30,    19,    14,     1,
      76,    18,     1,    25,    26,    27,    95,     5,    76,    31,
      15,    16,     6,    32,    18,    57,     6,    59,    33,    34,
      15,    16,    82,    13,    35,   135,    98,    36,    97,    70,
      82,    37,    85,    73,     9,    10,    20,    38,    39,    40,
      41,   134,    42,    43,    44,   137,    90,    71,    21,    22,
      96,    55,    72,    56,   143,    65,   145,   101,   102,   103,
      60,    58,    63,    64,    66,   109,    67,   111,   112,    99,
     114,    69,    71,   116,   117,   130,   132,   133,   139,     8,
      28,    86,    89,   120,    91,   141,    62,    29,   100,    92,
      93,    94,     0,     0,     0,     0,   127,     0,   128,     0,
      98,   131,   104,   105,   106,   107,   108,     0,   110,     0,
       0,     0,     0,     0,     0,     0,   138,     0,     0,   140,
       0,    89,   142,     0,   144,     0,   121,   122,   123,    30,
       0,     0,     0,     0,   124,     0,   125,   126,     0,     0,
       0,   129,    31,     0,     0,     0,    32,     0,     0,     0,
       0,    33,    34,    89,     0,     0,     0,    35,     0,     0,
      36,    30,     0,     0,    37,     0,     0,     0,     0,     0,
      38,    39,    40,    41,    31,    42,    43,    44,    32,     0,
       0,     0,     0,    33,    34,     0,     0,     0,     0,    35,
       0,     0,     0,    97,     0,     0,    37,    30,     0,     0,
       0,     0,    38,    39,    40,    41,     0,    42,    43,    44,
      31,     0,     0,     0,    32,     0,     0,     0,     0,    33,
      34,     0,     0,     0,     0,    35,     0,     0,     0,     0,
       0,     0,    37,     0,     0,    74,    75,     0,    38,    39,
      40,    41,    76,    42,    43,    44,     0,    77,     0,     0,
      78,    79,     0,     0,    74,    75,     0,    80,     0,   115,
       0,    76,     0,    81,    82,    83,    77,     0,    84,    78,
      79,     0,     0,   113,    85,     0,    80,     0,     0,    74,
      75,     0,    81,    82,    83,     0,    76,    84,     0,     0,
       0,    77,     0,    85,    78,    79,     0,     0,     0,    74,
      75,    80,     0,     0,     0,     0,    76,    81,    82,    83,
       1,    77,    84,     0,    78,    79,     0,     0,    85,    74,
      75,    80,     0,     0,     0,     0,    76,    81,    82,    83,
       0,    77,    84,     0,    78,    79,     0,   118,    85,    74,
      75,    80,     0,     0,     0,     0,    76,    81,    82,    83,
       0,    77,    84,     0,    78,    79,     0,   136,    85,    75,
       0,    80,     0,     0,     0,    76,     0,    81,    82,    83,
      77,     0,    84,    78,    79,     0,     0,     0,    85,     0,
      80,     0,     0,    32,     0,     0,    81,    82,    83,    34,
       0,     0,     0,     0,    35,     0,     0,    85,     0,    87,
      32,    37,     0,     0,     0,     0,    34,     0,    39,    40,
      41,    35,    15,    16,    44,     0,     0,     0,    37,     0,
       0,     0,     0,     0,     0,    39,    40,    41,     0,    15,
      16,    44
};

static const yytype_int16 yycheck[] =
{
       7,     8,    36,    96,     4,    70,     7,    14,    41,    34,
      10,    13,    34,    20,    21,    22,    41,     0,    10,    20,
      53,    54,     9,    24,    26,    32,     9,    34,    29,    30,
      53,    54,    32,    30,    35,   128,    70,    38,    39,    46,
      32,    42,    42,    50,    34,    55,    41,    48,    49,    50,
      51,   127,    53,    54,    55,   131,    58,    34,     8,    23,
      67,    34,    39,    30,   140,     6,   142,    74,    75,    76,
      35,    30,    37,    30,     6,    82,    30,    84,    85,   144,
      40,    39,    34,     8,    91,    41,    41,    23,    12,     3,
      25,    56,    57,   100,    59,   138,    36,    26,    70,    64,
      65,    66,    -1,    -1,    -1,    -1,   113,    -1,   115,    -1,
     144,   118,    77,    78,    79,    80,    81,    -1,    83,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   133,    -1,    -1,   136,
      -1,    96,   139,    -1,   141,    -1,   101,   102,   103,     7,
      -1,    -1,    -1,    -1,   109,    -1,   111,   112,    -1,    -1,
      -1,   116,    20,    -1,    -1,    -1,    24,    -1,    -1,    -1,
      -1,    29,    30,   128,    -1,    -1,    -1,    35,    -1,    -1,
      38,     7,    -1,    -1,    42,    -1,    -1,    -1,    -1,    -1,
      48,    49,    50,    51,    20,    53,    54,    55,    24,    -1,
      -1,    -1,    -1,    29,    30,    -1,    -1,    -1,    -1,    35,
      -1,    -1,    -1,    39,    -1,    -1,    42,     7,    -1,    -1,
      -1,    -1,    48,    49,    50,    51,    -1,    53,    54,    55,
      20,    -1,    -1,    -1,    24,    -1,    -1,    -1,    -1,    29,
      30,    -1,    -1,    -1,    -1,    35,    -1,    -1,    -1,    -1,
      -1,    -1,    42,    -1,    -1,     3,     4,    -1,    48,    49,
      50,    51,    10,    53,    54,    55,    -1,    15,    -1,    -1,
      18,    19,    -1,    -1,     3,     4,    -1,    25,    -1,     8,
      -1,    10,    -1,    31,    32,    33,    15,    -1,    36,    18,
      19,    -1,    -1,    41,    42,    -1,    25,    -1,    -1,     3,
       4,    -1,    31,    32,    33,    -1,    10,    36,    -1,    -1,
      -1,    15,    -1,    42,    18,    19,    -1,    -1,    -1,     3,
       4,    25,    -1,    -1,    -1,    -1,    10,    31,    32,    33,
      34,    15,    36,    -1,    18,    19,    -1,    -1,    42,     3,
       4,    25,    -1,    -1,    -1,    -1,    10,    31,    32,    33,
      -1,    15,    36,    -1,    18,    19,    -1,    41,    42,     3,
       4,    25,    -1,    -1,    -1,    -1,    10,    31,    32,    33,
      -1,    15,    36,    -1,    18,    19,    -1,    41,    42,     4,
      -1,    25,    -1,    -1,    -1,    10,    -1,    31,    32,    33,
      15,    -1,    36,    18,    19,    -1,    -1,    -1,    42,    -1,
      25,    -1,    -1,    24,    -1,    -1,    31,    32,    33,    30,
      -1,    -1,    -1,    -1,    35,    -1,    -1,    42,    -1,    40,
      24,    42,    -1,    -1,    -1,    -1,    30,    -1,    49,    50,
      51,    35,    53,    54,    55,    -1,    -1,    -1,    42,    -1,
      -1,    -1,    -1,    -1,    -1,    49,    50,    51,    -1,    53,
      54,    55
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    34,    58,    75,    76,     0,     9,    59,    59,    34,
      55,    75,    75,    30,    41,    53,    54,    71,    74,    75,
      41,     8,    23,    60,    62,    75,    75,    75,    60,    71,
       7,    20,    24,    29,    30,    35,    38,    42,    48,    49,
      50,    51,    53,    54,    55,    61,    63,    64,    65,    66,
      67,    69,    72,    73,    74,    34,    30,    75,    30,    75,
      72,    64,    66,    72,    30,     6,     6,    30,    68,    39,
      75,    34,    39,    75,     3,     4,    10,    15,    18,    19,
      25,    31,    32,    33,    36,    42,    72,    40,    70,    72,
      74,    72,    72,    72,    72,    41,    75,    39,    64,    65,
      67,    75,    75,    75,    72,    72,    72,    72,    72,    75,
      72,    75,    75,    41,    40,     8,     8,    75,    41,    70,
      75,    72,    72,    72,    72,    72,    72,    75,    75,    72,
      41,    75,    41,    23,    62,    70,    41,    62,    75,    12,
      75,    63,    75,    62,    75,    62
};

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
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
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
    while (YYID (0))
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
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, const YYSTYPE * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    const YYSTYPE * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, const YYSTYPE * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    const YYSTYPE * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, 
		   int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule
		   )
    YYSTYPE *yyvsp;
    
		   int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      fprintf (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

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
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      size_t yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn < YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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
  YYUSE (yyvaluep);

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
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  
  int yystate;
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

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
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;


	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),

		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
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

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

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

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

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
    {gParseTreeHead =  new OpNode(PEBL_FUNCTIONS,(yyvsp[(2) - (3)].exp),NULL, sourcefilename, yylineno);

		           (yyval.exp) = gParseTreeHead;
		;}
    break;

  case 3:
#line 126 "src/base/grammar.y"
    { gParseTreeHead = new OpNode(PEBL_FUNCTIONS, (yyvsp[(2) - (3)].exp), (yyvsp[(1) - (3)].exp), sourcefilename, yylineno);
		           (yyval.exp) = gParseTreeHead;
		;}
    break;

  case 4:
#line 134 "src/base/grammar.y"
    { ;
		PNode * tmpFN = new OpNode(PEBL_LAMBDAFUNCTION, (yyvsp[(4) - (7)].exp), (yyvsp[(7) - (7)].exp), sourcefilename, yylineno);  
		PNode * tmpNode = new DataNode(Variant((yyvsp[(2) - (7)].function), P_DATA_FUNCTION), sourcefilename, yylineno);
		free((yyvsp[(2) - (7)].function));
		(yyval.exp) = new OpNode(PEBL_FUNCTION, tmpNode, tmpFN, sourcefilename, yylineno);

        ;}
    break;

  case 5:
#line 143 "src/base/grammar.y"
    { ;
		PNode * tmpFN = new OpNode(PEBL_LAMBDAFUNCTION, NULL, (yyvsp[(6) - (6)].exp), sourcefilename, yylineno);  
		PNode * tmpNode = new DataNode(Variant((yyvsp[(2) - (6)].function), P_DATA_FUNCTION), sourcefilename, yylineno);
		(yyval.exp) = new OpNode(PEBL_FUNCTION, tmpNode, tmpFN, sourcefilename, yylineno);
        free((yyvsp[(2) - (6)].function));
		  ;}
    break;

  case 6:
#line 155 "src/base/grammar.y"
    {(yyval.exp) = (yyvsp[(1) - (1)].exp);;}
    break;

  case 7:
#line 156 "src/base/grammar.y"
    {(yyval.exp) = (yyvsp[(3) - (4)].exp);;}
    break;

  case 8:
#line 160 "src/base/grammar.y"
    { (yyval.exp) = (yyvsp[(1) - (2)].exp);;}
    break;

  case 9:
#line 161 "src/base/grammar.y"
    { (yyval.exp) = new OpNode(PEBL_STATEMENTS, (yyvsp[(1) - (4)].exp), (yyvsp[(3) - (4)].exp), sourcefilename, yylineno);;}
    break;

  case 10:
#line 165 "src/base/grammar.y"
    { (yyval.exp) = (yyvsp[(3) - (5)].exp);;}
    break;

  case 11:
#line 166 "src/base/grammar.y"
    {(yyval.exp) = (yyvsp[(3) - (3)].exp);;}
    break;

  case 12:
#line 167 "src/base/grammar.y"
    {
                     (yyval.exp)  = new OpNode(PEBL_STATEMENTS, (yyvsp[(3) - (5)].exp), (yyvsp[(5) - (5)].exp), sourcefilename, yylineno);
;}
    break;

  case 13:
#line 175 "src/base/grammar.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); ;}
    break;

  case 14:
#line 178 "src/base/grammar.y"
    { (yyval.exp) = new OpNode(PEBL_STATEMENTS, (yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp), sourcefilename, yylineno);;}
    break;

  case 15:
#line 182 "src/base/grammar.y"
    {(yyval.exp) = (yyvsp[(1) - (2)].exp);;}
    break;

  case 16:
#line 186 "src/base/grammar.y"
    {(yyval.exp) = (yyvsp[(1) - (2)].exp);;}
    break;

  case 17:
#line 195 "src/base/grammar.y"
    {(yyval.exp) = (yyvsp[(1) - (1)].exp);;}
    break;

  case 18:
#line 197 "src/base/grammar.y"
    {(yyval.exp) = new OpNode(PEBL_BREAK, NULL, NULL, sourcefilename, yylineno);;}
    break;

  case 19:
#line 200 "src/base/grammar.y"
    { 
	        Variant tmpV((yyvsp[(1) - (3)].symbol),P_DATA_LOCALVARIABLE);       /*create a new temporary variant*/
		    free((yyvsp[(1) - (3)].symbol));
			PNode * tmpNode = new DataNode(tmpV, sourcefilename, yylineno);        /*create basic pnode*/
		    (yyval.exp) = new OpNode(PEBL_ASSIGN, tmpNode, (yyvsp[(3) - (3)].exp), sourcefilename, yylineno);   /*Use symbol node in assignment node*/
		;}
    break;

  case 20:
#line 209 "src/base/grammar.y"
    { 
	        Variant tmpV((yyvsp[(1) - (3)].symbol),P_DATA_GLOBALVARIABLE);      /*create a new temporary variant*/
		PNode * tmpNode = new DataNode(tmpV, sourcefilename, yylineno);        /*create basic pnode*/
		(yyval.exp) = new OpNode(PEBL_ASSIGN, tmpNode, (yyvsp[(3) - (3)].exp), sourcefilename, yylineno);   /*Use symbol node in assignment node*/
		;}
    break;

  case 21:
#line 216 "src/base/grammar.y"
    {;
		(yyval.exp) = new OpNode(PEBL_WHILE, (yyvsp[(3) - (6)].exp), (yyvsp[(6) - (6)].exp), sourcefilename, yylineno); ;}
    break;

  case 22:
#line 229 "src/base/grammar.y"
    {
		(yyval.exp) = new OpNode(PEBL_IF, (yyvsp[(3) - (6)].exp), (yyvsp[(6) - (6)].exp), sourcefilename, yylineno); ;}
    break;

  case 23:
#line 235 "src/base/grammar.y"
    {
		/*First make the else node*/
		PNode * tmpNode = new OpNode(PEBL_ELSE, (yyvsp[(6) - (9)].exp), (yyvsp[(9) - (9)].exp), sourcefilename, yylineno);
		/*Put the else node in the IF node*/
		(yyval.exp) = new OpNode(PEBL_IFELSE, (yyvsp[(3) - (9)].exp), tmpNode, sourcefilename, yylineno); ;}
    break;

  case 24:
#line 251 "src/base/grammar.y"
    {
		PNode * tmpNode = new OpNode(PEBL_VARIABLEDATUM, (yyvsp[(3) - (8)].exp), (yyvsp[(5) - (8)].exp), sourcefilename, yylineno);
		(yyval.exp) = new OpNode(PEBL_LOOP, tmpNode, (yyvsp[(8) - (8)].exp), sourcefilename, yylineno); ;}
    break;

  case 25:
#line 258 "src/base/grammar.y"
    {(yyval.exp) = new OpNode(PEBL_RETURN, (yyvsp[(2) - (2)].exp), NULL, sourcefilename, yylineno);;}
    break;

  case 26:
#line 268 "src/base/grammar.y"
    {(yyval.exp) = new OpNode(PEBL_ARGLIST, NULL, NULL, sourcefilename, yylineno);;}
    break;

  case 27:
#line 272 "src/base/grammar.y"
    {(yyval.exp) = new OpNode(PEBL_ARGLIST, (yyvsp[(3) - (4)].exp), NULL, sourcefilename, yylineno);;}
    break;

  case 28:
#line 282 "src/base/grammar.y"
    {(yyval.exp) = new OpNode(PEBL_LISTHEAD,(yyvsp[(3) - (4)].exp), NULL, sourcefilename, yylineno);;}
    break;

  case 29:
#line 285 "src/base/grammar.y"
    {(yyval.exp) = new OpNode(PEBL_LISTHEAD, NULL, NULL, sourcefilename, yylineno);;}
    break;

  case 30:
#line 289 "src/base/grammar.y"
    {(yyval.exp) = new OpNode(PEBL_LISTITEM, (yyvsp[(1) - (1)].exp), NULL, sourcefilename, yylineno);;}
    break;

  case 31:
#line 293 "src/base/grammar.y"
    {(yyval.exp) = new OpNode(PEBL_LISTITEM, (yyvsp[(1) - (4)].exp), (yyvsp[(4) - (4)].exp), sourcefilename, yylineno);;}
    break;

  case 32:
#line 301 "src/base/grammar.y"
    {(yyval.exp) = new OpNode(PEBL_VARLIST, (yyvsp[(1) - (1)].exp), NULL, sourcefilename, yylineno);;}
    break;

  case 33:
#line 305 "src/base/grammar.y"
    {(yyval.exp) = new OpNode(PEBL_VARLIST,(yyvsp[(1) - (4)].exp),(yyvsp[(4) - (4)].exp), sourcefilename, yylineno);;}
    break;

  case 34:
#line 311 "src/base/grammar.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp);;}
    break;

  case 35:
#line 314 "src/base/grammar.y"
    {(yyval.exp) = (yyvsp[(3) - (5)].exp);}
    break;

  case 36:
#line 317 "src/base/grammar.y"
    {
		Variant tmpV = 0;
		PNode * tmpNode = new DataNode(tmpV, sourcefilename, yylineno);
		(yyval.exp) = new OpNode(PEBL_SUBTRACT, tmpNode, (yyvsp[(2) - (2)].exp), sourcefilename, yylineno); ;}
    break;

  case 37:
#line 323 "src/base/grammar.y"
    {(yyval.exp) = new OpNode(PEBL_NOT, (yyvsp[(2) - (2)].exp), NULL, sourcefilename, yylineno); ;}
    break;

  case 38:
#line 326 "src/base/grammar.y"
    { (yyval.exp) = new OpNode(PEBL_ADD, (yyvsp[(1) - (4)].exp), (yyvsp[(4) - (4)].exp), sourcefilename, yylineno);  ;}
    break;

  case 39:
#line 330 "src/base/grammar.y"
    { (yyval.exp) = new OpNode(PEBL_DIVIDE,(yyvsp[(1) - (4)].exp), (yyvsp[(4) - (4)].exp), sourcefilename, yylineno);  ;}
    break;

  case 40:
#line 333 "src/base/grammar.y"
    { (yyval.exp) = new OpNode(PEBL_MULTIPLY, (yyvsp[(1) - (4)].exp), (yyvsp[(4) - (4)].exp), sourcefilename, yylineno);;}
    break;

  case 41:
#line 336 "src/base/grammar.y"
    { (yyval.exp) = new OpNode(PEBL_SUBTRACT, (yyvsp[(1) - (4)].exp), (yyvsp[(4) - (4)].exp), sourcefilename, yylineno); ;}
    break;

  case 42:
#line 339 "src/base/grammar.y"
    { (yyval.exp) = new OpNode(PEBL_OR, (yyvsp[(1) - (4)].exp), (yyvsp[(4) - (4)].exp), sourcefilename, yylineno); ;}
    break;

  case 43:
#line 342 "src/base/grammar.y"
    { (yyval.exp) = new OpNode(PEBL_AND, (yyvsp[(1) - (4)].exp), (yyvsp[(4) - (4)].exp), sourcefilename, yylineno); ;}
    break;

  case 44:
#line 346 "src/base/grammar.y"
    { (yyval.exp) = new OpNode(PEBL_LT,  (yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp), sourcefilename, yylineno);;}
    break;

  case 45:
#line 349 "src/base/grammar.y"
    { (yyval.exp) = new OpNode(PEBL_GT,  (yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp), sourcefilename, yylineno);;}
    break;

  case 46:
#line 352 "src/base/grammar.y"
    { (yyval.exp) = new OpNode(PEBL_GE,  (yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp), sourcefilename, yylineno);;}
    break;

  case 47:
#line 355 "src/base/grammar.y"
    { (yyval.exp) = new OpNode(PEBL_LE,  (yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp), sourcefilename, yylineno);;}
    break;

  case 48:
#line 358 "src/base/grammar.y"
    { (yyval.exp) = new OpNode(PEBL_EQ,  (yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp), sourcefilename, yylineno);;}
    break;

  case 49:
#line 361 "src/base/grammar.y"
    { (yyval.exp) = new OpNode(PEBL_NE,  (yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp), sourcefilename, yylineno);;}
    break;

  case 50:
#line 370 "src/base/grammar.y"
    {
		PNode * tmpNode = new DataNode(Variant((yyvsp[(1) - (2)].function), P_DATA_FUNCTION), sourcefilename, yylineno);
		(yyval.exp) = new OpNode(PEBL_FUNCTION, tmpNode, (yyvsp[(2) - (2)].exp), sourcefilename, yylineno);
        free((yyvsp[(1) - (2)].function));
		;}
    break;

  case 51:
#line 380 "src/base/grammar.y"
    { (yyval.exp) = new DataNode ((yyvsp[(1) - (1)].iValue), sourcefilename, yylineno); ;}
    break;

  case 52:
#line 383 "src/base/grammar.y"
    { (yyval.exp) = new DataNode ((yyvsp[(1) - (1)].fValue), sourcefilename, yylineno);;}
    break;

  case 53:
#line 386 "src/base/grammar.y"
    {
	  Variant tmpV((yyvsp[(1) - (1)].strValue));            /*create a new temporary variant*/
	  free((yyvsp[(1) - (1)].strValue));
	  (yyval.exp) = new DataNode(tmpV, sourcefilename, yylineno);

                        ;}
    break;

  case 54:
#line 393 "src/base/grammar.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp);;}
    break;

  case 55:
#line 396 "src/base/grammar.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp);;}
    break;

  case 56:
#line 401 "src/base/grammar.y"
    { 
		Variant tmpV((yyvsp[(1) - (1)].symbol), P_DATA_LOCALVARIABLE);           /*create a new temporary variant*/;
		(yyval.exp) = new DataNode(tmpV, sourcefilename, yylineno);                        /*Make a new variable node here.*/
        free((yyvsp[(1) - (1)].symbol));
        ;}
    break;

  case 57:
#line 406 "src/base/grammar.y"
    { 
		Variant tmpV((yyvsp[(1) - (1)].symbol), P_DATA_GLOBALVARIABLE);          /*create a new temporary variant*/;
		(yyval.exp) = new DataNode(tmpV, sourcefilename, yylineno);  /*Make a new variable node here.*/
		free((yyvsp[(1) - (1)].symbol));
		 ;}
    break;

  case 58:
#line 413 "src/base/grammar.y"
    {/*nothing*/;;}
    break;

  case 59:
#line 414 "src/base/grammar.y"
    {/**/;;}
    break;

  case 60:
#line 418 "src/base/grammar.y"
    {/**/;;}
    break;

  case 61:
#line 419 "src/base/grammar.y"
    {/**/;;}
    break;


/* Line 1272 of yacc.c.  */
#line 1988 "src/base/grammar.tab.cpp"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
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
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
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


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;


  /* Shift the error token.  */
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
  yyresult = 1;
  goto yyreturn;

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}


#line 425 "src/base/grammar.y"


void yyerror (char *error)
{

    std::cerr << "line " << yylineno << " of "<< sourcefilename<<": " << error << endl;
    exit(1);
}

extern int yy_flex_debug;

PNode * parse (const char* filename)
{
  //yydebug=1;          /*Bison must be run with -t option to use debugging*/
  //yy_flex_debug = 1;   /*Flex must be run with -d option to use*/
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


