/* A Bison parser, made by GNU Bison 2.7.  */

/* Bison implementation for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2012 Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

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
#define YYBISON_VERSION "2.7"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
/* Line 371 of yacc.c  */
#line 1 "hcc.y"

/*
**Grammatical specification for HCC 1.0
**This code is based on various open resources, intented for educational
**purposes only. You can access, modify this for your personal use freely,
**but any attempts for comercial exploitation from this code are considered 
**unethical and should be discouraged.
*/
#include "c.h"

static void yyerror(char *s);

/* current translation unit */
ASTTranslationunit * translationunit;
/* current function declaration */
ASTFunctiondeclaration *curfunc;

extern Coordinate tcoord;
extern Tvalue tval;

/* Line 371 of yacc.c  */
#line 89 "parser.c"

# ifndef YY_NULL
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULL nullptr
#  else
#   define YY_NULL 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "parser.h".  */
#ifndef YY_YY_PARSER_H_INCLUDED
# define YY_YY_PARSER_H_INCLUDED
/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     AUTO = 258,
     BREAK = 259,
     CASE = 260,
     CHAR = 261,
     CONST = 262,
     CONTINUE = 263,
     DEFAULT = 264,
     DO = 265,
     DOUBLE = 266,
     ELSE = 267,
     ENUM = 268,
     EXTERN = 269,
     FLOAT = 270,
     FOR = 271,
     GOTO = 272,
     IF = 273,
     INT = 274,
     LONG = 275,
     REGISTER = 276,
     RETURN = 277,
     SHORT = 278,
     SIGNED = 279,
     SIZEOF = 280,
     STATIC = 281,
     STRUCT = 282,
     SWITCH = 283,
     TYPEDEF = 284,
     TYPENAME = 285,
     UNION = 286,
     UNSIGNED = 287,
     VOID = 288,
     VOLATILE = 289,
     WHILE = 290,
     LOGIN = 291,
     LOGOUT = 292,
     IDENTIFIER = 293,
     INTCONST = 294,
     UINT = 295,
     LINT = 296,
     ULINT = 297,
     LLINT = 298,
     ULLINT = 299,
     DOUBLECONST = 300,
     LDOUBLECONST = 301,
     FLOATCONST = 302,
     STRING = 303,
     ELLIPSIS = 304,
     RIGHT_ASSIGN = 305,
     LEFT_ASSIGN = 306,
     SUB_ASSIGN = 307,
     ADD_ASSIGN = 308,
     MUL_ASSIGN = 309,
     DIV_ASSIGN = 310,
     MOD_ASSIGN = 311,
     AND_ASSIGN = 312,
     OR_ASSIGN = 313,
     XOR_ASSIGN = 314,
     RIGHT_SHIFT = 315,
     LEFT_SHIFT = 316,
     INC_OP = 317,
     DEC_OP = 318,
     PTR_OP = 319,
     AND_OP = 320,
     OR_OP = 321,
     LE_OP = 322,
     GE_OP = 323,
     EQ_OP = 324,
     NE_OP = 325,
     CAST_OP = 326,
     INDEX_OP = 327,
     CALL_OP = 328,
     MEMBER_OP = 329,
     POST_INC_DEC_OP = 330,
     COND_OP = 331,
     CALL_LOGIN = 332,
     CALL_LOGOUT = 333,
     IFX = 334
   };
#endif
/* Tokens.  */
#define AUTO 258
#define BREAK 259
#define CASE 260
#define CHAR 261
#define CONST 262
#define CONTINUE 263
#define DEFAULT 264
#define DO 265
#define DOUBLE 266
#define ELSE 267
#define ENUM 268
#define EXTERN 269
#define FLOAT 270
#define FOR 271
#define GOTO 272
#define IF 273
#define INT 274
#define LONG 275
#define REGISTER 276
#define RETURN 277
#define SHORT 278
#define SIGNED 279
#define SIZEOF 280
#define STATIC 281
#define STRUCT 282
#define SWITCH 283
#define TYPEDEF 284
#define TYPENAME 285
#define UNION 286
#define UNSIGNED 287
#define VOID 288
#define VOLATILE 289
#define WHILE 290
#define LOGIN 291
#define LOGOUT 292
#define IDENTIFIER 293
#define INTCONST 294
#define UINT 295
#define LINT 296
#define ULINT 297
#define LLINT 298
#define ULLINT 299
#define DOUBLECONST 300
#define LDOUBLECONST 301
#define FLOATCONST 302
#define STRING 303
#define ELLIPSIS 304
#define RIGHT_ASSIGN 305
#define LEFT_ASSIGN 306
#define SUB_ASSIGN 307
#define ADD_ASSIGN 308
#define MUL_ASSIGN 309
#define DIV_ASSIGN 310
#define MOD_ASSIGN 311
#define AND_ASSIGN 312
#define OR_ASSIGN 313
#define XOR_ASSIGN 314
#define RIGHT_SHIFT 315
#define LEFT_SHIFT 316
#define INC_OP 317
#define DEC_OP 318
#define PTR_OP 319
#define AND_OP 320
#define OR_OP 321
#define LE_OP 322
#define GE_OP 323
#define EQ_OP 324
#define NE_OP 325
#define CAST_OP 326
#define INDEX_OP 327
#define CALL_OP 328
#define MEMBER_OP 329
#define POST_INC_DEC_OP 330
#define COND_OP 331
#define CALL_LOGIN 332
#define CALL_LOGOUT 333
#define IFX 334



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{
/* Line 387 of yacc.c  */
#line 22 "hcc.y"

  ASTBase *ast;


/* Line 387 of yacc.c  */
#line 295 "parser.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;

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

#endif /* !YY_YY_PARSER_H_INCLUDED  */

/* Copy the second part of user declarations.  */
/* Line 390 of yacc.c  */
#line 70 "hcc.y"

/* operator precedence and associativity definition */
/* currently, I simply rewrite the garmmer to deal with this. */
/* we should switch to this precedence table later */
/*
%left ','
%right ADD_ASSIGN SUB_ASSIGN MUL_ASSIGN DIV_ASSIGN AND_ASSIGN XOR_ASSIGN OR_ASSIGN LEFT_ASSIGN RIGHT_ASSIGN
%right '?' ':'
%left OR_OP
%left AND_OP
%left '|'
%left '^'
%left '&'
%left EQ_OP NE_OP
%left '<' LE_OP GE_OP '>'
%left LEFT_SHIFT RIGHT_SHIFT
%left '+' '-'
%left '*' '/' '%'
%right '!' '~' INC_OP DEC_OP SIZEOF CAST_OP 
%left '(' '[' PTR_OP '.'
*/

/* Line 390 of yacc.c  */
#line 346 "parser.c"

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
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(N) (N)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
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
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
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
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  47
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1775

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  104
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  88
/* YYNRULES -- Number of rules.  */
#define YYNRULES  247
/* YYNRULES -- Number of states.  */
#define YYNSTATES  391

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   334

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    93,     2,     2,     2,   101,    89,     2,
      88,    85,    84,    90,    80,    91,    94,   100,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    83,   103,
      98,    82,    99,    95,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    87,     2,    86,    97,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   102,    96,    81,    92,     2,     2,     2,
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
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     7,    10,    12,    14,    18,    21,
      24,    26,    28,    33,    37,    41,    44,    46,    49,    51,
      55,    57,    60,    62,    65,    67,    70,    72,    74,    76,
      78,    80,    82,    84,    86,    88,    90,    92,    94,    96,
      98,   100,   102,   104,   106,   108,   111,   116,   122,   128,
     135,   137,   139,   141,   145,   147,   151,   153,   156,   162,
     167,   169,   171,   173,   176,   180,   182,   185,   187,   190,
     192,   196,   198,   201,   205,   208,   210,   212,   215,   218,
     222,   224,   226,   229,   231,   235,   240,   244,   249,   254,
     258,   260,   264,   266,   270,   272,   276,   278,   281,   284,
     286,   288,   291,   295,   298,   302,   306,   311,   314,   318,
     322,   327,   329,   331,   333,   337,   339,   343,   348,   350,
     354,   356,   360,   362,   366,   368,   370,   372,   374,   376,
     378,   380,   382,   384,   386,   388,   390,   393,   396,   399,
     404,   406,   408,   410,   412,   414,   416,   418,   420,   422,
     424,   427,   429,   434,   436,   441,   445,   450,   454,   458,
     461,   463,   467,   469,   471,   473,   475,   477,   479,   481,
     483,   485,   487,   489,   493,   497,   499,   505,   507,   511,
     513,   517,   519,   523,   525,   529,   531,   535,   537,   541,
     545,   547,   551,   555,   559,   563,   565,   569,   573,   575,
     579,   583,   585,   589,   593,   597,   600,   604,   608,   613,
     615,   617,   620,   622,   624,   626,   628,   630,   632,   636,
     641,   645,   647,   649,   651,   654,   656,   658,   660,   662,
     668,   676,   682,   688,   696,   703,   711,   713,   715,   717,
     719,   721,   723,   725,   729,   732,   735,   738
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     105,     0,    -1,   106,    -1,   107,    -1,   106,   107,    -1,
     111,    -1,   110,    -1,   114,   113,   178,    -1,   114,   178,
      -1,   113,   178,    -1,   108,    -1,   109,    -1,   114,   131,
     112,   170,    -1,   114,   131,   170,    -1,   131,   112,   170,
      -1,   131,   170,    -1,   108,    -1,   112,   108,    -1,   144,
      -1,   113,    80,   144,    -1,   115,    -1,   115,   114,    -1,
     117,    -1,   117,   114,    -1,   116,    -1,   116,   114,    -1,
       3,    -1,    21,    -1,    26,    -1,    14,    -1,    29,    -1,
       7,    -1,    34,    -1,    33,    -1,     6,    -1,    23,    -1,
      19,    -1,    20,    -1,    24,    -1,    32,    -1,    15,    -1,
      11,    -1,    30,    -1,   118,    -1,   124,    -1,   119,   120,
      -1,   119,   171,   121,    81,    -1,   119,   171,   121,    80,
      81,    -1,   119,   120,   171,   121,    81,    -1,   119,   120,
     171,   121,    80,    81,    -1,    13,    -1,    38,    -1,   122,
      -1,   121,    80,   122,    -1,   120,    -1,   120,    82,   123,
      -1,   159,    -1,   125,   120,    -1,   125,   120,   171,   126,
      81,    -1,   125,   171,   126,    81,    -1,    27,    -1,    31,
      -1,   127,    -1,   126,   127,    -1,   128,   129,   178,    -1,
     117,    -1,   117,   128,    -1,   116,    -1,   116,   128,    -1,
     130,    -1,   129,    80,   130,    -1,   131,    -1,    83,   123,
      -1,   131,    83,   123,    -1,   132,   135,    -1,   135,    -1,
     133,    -1,   133,   134,    -1,   133,   132,    -1,   133,   134,
     132,    -1,    84,    -1,   116,    -1,   134,   116,    -1,   120,
      -1,   143,   131,    85,    -1,   135,   142,   123,    86,    -1,
     135,   142,    86,    -1,   135,   143,   137,    85,    -1,   135,
     143,   136,    85,    -1,   135,   143,    85,    -1,   120,    -1,
     136,    80,   120,    -1,   138,    -1,   138,    80,    49,    -1,
     139,    -1,   138,    80,   139,    -1,   114,    -1,   114,   131,
      -1,   114,   140,    -1,   132,    -1,   141,    -1,   132,   141,
      -1,   143,   140,    85,    -1,   142,    86,    -1,   142,   123,
      86,    -1,   141,   142,    86,    -1,   141,   142,   123,    86,
      -1,   143,    85,    -1,   143,   137,    85,    -1,   141,   143,
      85,    -1,   141,   143,   137,    85,    -1,    87,    -1,    88,
      -1,   131,    -1,   131,    82,   145,    -1,   148,    -1,   171,
     146,    81,    -1,   171,   146,    80,    81,    -1,   145,    -1,
     146,    80,   145,    -1,   148,    -1,   147,    80,   148,    -1,
     159,    -1,   150,   149,   148,    -1,    82,    -1,    54,    -1,
      55,    -1,    56,    -1,    53,    -1,    52,    -1,    51,    -1,
      50,    -1,    57,    -1,    59,    -1,    58,    -1,   156,    -1,
     151,   150,    -1,   153,   155,    -1,   152,   150,    -1,   152,
     143,   154,    85,    -1,    62,    -1,    63,    -1,    25,    -1,
      89,    -1,    90,    -1,    91,    -1,    92,    -1,    93,    -1,
     133,    -1,   128,    -1,   128,   140,    -1,   150,    -1,   143,
     154,    85,   155,    -1,   158,    -1,   156,   142,   147,    86,
      -1,   156,   143,    85,    -1,   156,   143,   157,    85,    -1,
     156,    94,   120,    -1,   156,    64,   120,    -1,   156,   151,
      -1,   148,    -1,   157,    80,   148,    -1,   120,    -1,    39,
      -1,    40,    -1,    41,    -1,    42,    -1,    43,    -1,    44,
      -1,    45,    -1,    46,    -1,    47,    -1,    48,    -1,   143,
     147,    85,    -1,   171,   147,    81,    -1,   160,    -1,   160,
      95,   147,    83,   159,    -1,   161,    -1,   160,    66,   161,
      -1,   162,    -1,   161,    65,   162,    -1,   163,    -1,   162,
      96,   163,    -1,   164,    -1,   163,    97,   164,    -1,   165,
      -1,   164,    89,   165,    -1,   166,    -1,   165,    69,   166,
      -1,   165,    70,   166,    -1,   167,    -1,   166,    98,   167,
      -1,   166,    99,   167,    -1,   166,    67,   167,    -1,   166,
      68,   167,    -1,   168,    -1,   167,    61,   168,    -1,   167,
      60,   168,    -1,   169,    -1,   168,    90,   169,    -1,   168,
      91,   169,    -1,   155,    -1,   169,    84,   155,    -1,   169,
     100,   155,    -1,   169,   101,   155,    -1,   171,    81,    -1,
     171,   172,    81,    -1,   171,   112,    81,    -1,   171,   112,
     172,    81,    -1,   102,    -1,   173,    -1,   172,   173,    -1,
     174,    -1,   170,    -1,   177,    -1,   182,    -1,   183,    -1,
     191,    -1,   120,    83,   173,    -1,   176,   123,    83,   173,
      -1,   175,    83,   173,    -1,     9,    -1,     5,    -1,   178,
      -1,   147,   178,    -1,   103,    -1,    18,    -1,    12,    -1,
      28,    -1,   179,   143,   147,    85,   173,    -1,   179,   143,
     147,    85,   173,   180,   173,    -1,   181,   143,   147,    85,
     173,    -1,   184,   143,   147,    85,   173,    -1,   185,   173,
     184,   143,   147,    85,   178,    -1,   186,   143,   177,   177,
      85,   173,    -1,   186,   143,   177,   177,   147,    85,   173,
      -1,    35,    -1,    10,    -1,    16,    -1,    17,    -1,     8,
      -1,     4,    -1,    22,    -1,   187,   120,   178,    -1,   188,
     178,    -1,   189,   178,    -1,   190,   178,    -1,   190,   147,
     178,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   127,   127,   130,   131,   134,   135,   138,   140,   144,
     148,   149,   152,   154,   156,   158,   162,   163,   166,   167,
     170,   172,   174,   176,   178,   180,   184,   185,   186,   187,
     188,   191,   192,   195,   196,   197,   198,   199,   200,   201,
     202,   203,   204,   205,   206,   209,   211,   213,   215,   217,
     221,   224,   228,   229,   232,   233,   236,   239,   241,   243,
     247,   248,   251,   253,   257,   261,   263,   265,   267,   271,
     272,   275,   277,   279,   283,   285,   289,   291,   293,   295,
     299,   302,   303,   306,   308,   310,   312,   314,   316,   318,
     322,   323,   326,   327,   330,   331,   334,   336,   338,   342,
     344,   346,   350,   352,   354,   356,   358,   360,   362,   364,
     366,   370,   373,   376,   378,   382,   384,   386,   390,   392,
     396,   398,   402,   404,   408,   409,   410,   411,   412,   413,
     414,   415,   416,   417,   418,   421,   423,   425,   427,   429,
     433,   434,   437,   440,   441,   442,   443,   444,   445,   448,
     450,   454,   456,   460,   462,   464,   466,   468,   470,   472,
     476,   478,   482,   484,   486,   488,   490,   492,   494,   496,
     498,   500,   502,   504,   506,   510,   512,   516,   518,   522,
     524,   528,   530,   534,   536,   540,   542,   546,   548,   550,
     554,   556,   558,   560,   562,   566,   568,   570,   574,   576,
     578,   582,   584,   586,   588,   592,   594,   596,   598,   602,
     605,   607,   611,   613,   615,   617,   619,   621,   625,   627,
     629,   633,   637,   641,   643,   647,   650,   652,   654,   657,
     659,   661,   665,   667,   669,   671,   675,   678,   681,   684,
     687,   690,   693,   696,   698,   700,   702,   704
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "AUTO", "BREAK", "CASE", "CHAR", "CONST",
  "CONTINUE", "DEFAULT", "DO", "DOUBLE", "ELSE", "ENUM", "EXTERN", "FLOAT",
  "FOR", "GOTO", "IF", "INT", "LONG", "REGISTER", "RETURN", "SHORT",
  "SIGNED", "SIZEOF", "STATIC", "STRUCT", "SWITCH", "TYPEDEF", "TYPENAME",
  "UNION", "UNSIGNED", "VOID", "VOLATILE", "WHILE", "LOGIN", "LOGOUT",
  "IDENTIFIER", "INTCONST", "UINT", "LINT", "ULINT", "LLINT", "ULLINT",
  "DOUBLECONST", "LDOUBLECONST", "FLOATCONST", "STRING", "ELLIPSIS",
  "RIGHT_ASSIGN", "LEFT_ASSIGN", "SUB_ASSIGN", "ADD_ASSIGN", "MUL_ASSIGN",
  "DIV_ASSIGN", "MOD_ASSIGN", "AND_ASSIGN", "OR_ASSIGN", "XOR_ASSIGN",
  "RIGHT_SHIFT", "LEFT_SHIFT", "INC_OP", "DEC_OP", "PTR_OP", "AND_OP",
  "OR_OP", "LE_OP", "GE_OP", "EQ_OP", "NE_OP", "CAST_OP", "INDEX_OP",
  "CALL_OP", "MEMBER_OP", "POST_INC_DEC_OP", "COND_OP", "CALL_LOGIN",
  "CALL_LOGOUT", "IFX", "','", "'}'", "'='", "':'", "'*'", "')'", "']'",
  "'['", "'('", "'&'", "'+'", "'-'", "'~'", "'!'", "'.'", "'?'", "'|'",
  "'^'", "'<'", "'>'", "'/'", "'%'", "'{'", "';'", "$accept",
  "translation_unit", "extdecls", "extdecl", "declaration",
  "notype_declaration", "data_declaration", "function_declaration",
  "declaration_list", "init_declarator_list", "declaration_specifiers",
  "storage_class_specifier", "type_qualifier", "type_specifier",
  "enum_specifier", "enum_keyword", "identifier", "enumerator_list",
  "enumerator", "constant_expression", "struct_or_union_specifier",
  "struct_or_union", "struct_declaration_list", "struct_declaration",
  "specifier_qualifier_list", "struct_declarator_list",
  "struct_declarator", "declarator", "pointer", "pointer_mark",
  "type_qualifier_list", "direct_declarator", "identifier_list",
  "parameter_type_list", "parameter_list", "parameter_declaration",
  "abstract_declarator", "direct_abstract_declarator", "left_bracket",
  "left_paren", "init_declarator", "initializer", "initializer_list",
  "expression", "assignment_expression", "assignment_operator",
  "unary_expression", "inc_dec_op", "sizeof_op", "unary_operator",
  "type_name", "cast_expression", "postfix_expression",
  "argument_expression_list", "primary_expression",
  "conditional_expression", "logical_or_expression",
  "logical_and_expression", "inclusive_or_expression",
  "exclusive_or_expression", "and_expression", "equality_expression",
  "relational_expression", "shift_expression", "additive_expression",
  "multiplicative_expression", "compound_statement", "left_brace",
  "statement_list", "statement", "labeled_statement", "default_keyword",
  "case_keyword", "expression_statement", "semicolon", "if_keyword",
  "else_keyword", "switch_keyword", "selection_statement",
  "iteration_statement", "while_keyword", "do_keyword", "for_keyword",
  "goto_keyword", "continue_keyword", "break_keyword", "return_keyword",
  "jump_statement", YY_NULL
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
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
      44,   125,    61,    58,    42,    41,    93,    91,    40,    38,
      43,    45,   126,    33,    46,    63,   124,    94,    60,    62,
      47,    37,   123,    59
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   104,   105,   106,   106,   107,   107,   108,   108,   109,
     110,   110,   111,   111,   111,   111,   112,   112,   113,   113,
     114,   114,   114,   114,   114,   114,   115,   115,   115,   115,
     115,   116,   116,   117,   117,   117,   117,   117,   117,   117,
     117,   117,   117,   117,   117,   118,   118,   118,   118,   118,
     119,   120,   121,   121,   122,   122,   123,   124,   124,   124,
     125,   125,   126,   126,   127,   128,   128,   128,   128,   129,
     129,   130,   130,   130,   131,   131,   132,   132,   132,   132,
     133,   134,   134,   135,   135,   135,   135,   135,   135,   135,
     136,   136,   137,   137,   138,   138,   139,   139,   139,   140,
     140,   140,   141,   141,   141,   141,   141,   141,   141,   141,
     141,   142,   143,   144,   144,   145,   145,   145,   146,   146,
     147,   147,   148,   148,   149,   149,   149,   149,   149,   149,
     149,   149,   149,   149,   149,   150,   150,   150,   150,   150,
     151,   151,   152,   153,   153,   153,   153,   153,   153,   154,
     154,   155,   155,   156,   156,   156,   156,   156,   156,   156,
     157,   157,   158,   158,   158,   158,   158,   158,   158,   158,
     158,   158,   158,   158,   158,   159,   159,   160,   160,   161,
     161,   162,   162,   163,   163,   164,   164,   165,   165,   165,
     166,   166,   166,   166,   166,   167,   167,   167,   168,   168,
     168,   169,   169,   169,   169,   170,   170,   170,   170,   171,
     172,   172,   173,   173,   173,   173,   173,   173,   174,   174,
     174,   175,   176,   177,   177,   178,   179,   180,   181,   182,
     182,   182,   183,   183,   183,   183,   184,   185,   186,   187,
     188,   189,   190,   191,   191,   191,   191,   191
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     2,     1,     1,     3,     2,     2,
       1,     1,     4,     3,     3,     2,     1,     2,     1,     3,
       1,     2,     1,     2,     1,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     2,     4,     5,     5,     6,
       1,     1,     1,     3,     1,     3,     1,     2,     5,     4,
       1,     1,     1,     2,     3,     1,     2,     1,     2,     1,
       3,     1,     2,     3,     2,     1,     1,     2,     2,     3,
       1,     1,     2,     1,     3,     4,     3,     4,     4,     3,
       1,     3,     1,     3,     1,     3,     1,     2,     2,     1,
       1,     2,     3,     2,     3,     3,     4,     2,     3,     3,
       4,     1,     1,     1,     3,     1,     3,     4,     1,     3,
       1,     3,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     2,     2,     2,     4,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       2,     1,     4,     1,     4,     3,     4,     3,     3,     2,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     3,     3,     1,     5,     1,     3,     1,
       3,     1,     3,     1,     3,     1,     3,     1,     3,     3,
       1,     3,     3,     3,     3,     1,     3,     3,     1,     3,
       3,     1,     3,     3,     3,     2,     3,     3,     4,     1,
       1,     2,     1,     1,     1,     1,     1,     1,     3,     4,
       3,     1,     1,     1,     2,     1,     1,     1,     1,     5,
       7,     5,     5,     7,     6,     7,     1,     1,     1,     1,
       1,     1,     1,     3,     2,     2,     2,     3
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    26,    34,    31,    41,    50,    29,    40,    36,    37,
      27,    35,    38,    28,    60,    30,    42,    61,    39,    33,
      32,    51,    80,   112,     0,     2,     3,    10,    11,     6,
       5,     0,     0,    20,    24,    22,    43,     0,    83,    44,
       0,   113,     0,    76,    75,     0,    18,     1,     4,     0,
     225,     9,     0,   113,     8,    21,    25,    23,   209,    45,
       0,    57,     0,     0,    16,     0,     0,    15,     0,    74,
      81,    78,    77,   111,     0,     0,     0,   113,    19,     7,
       0,    13,     0,    54,     0,    52,     0,    67,    65,     0,
      62,     0,   142,   163,   164,   165,   166,   167,   168,   169,
     170,   171,   172,   140,   141,   143,   144,   145,   146,   147,
     162,   148,     0,   114,   115,   151,     0,     0,     0,   201,
     135,   153,   122,   175,   177,   179,   181,   183,   185,   187,
     190,   195,   198,     0,    17,    14,   241,   222,   240,   221,
     237,   238,   239,   226,   242,   228,   236,   205,     0,   162,
       0,   120,   213,     0,     0,   210,   212,     0,     0,   214,
     223,     0,     0,   215,   216,     0,     0,     0,     0,     0,
       0,     0,   217,    82,    79,    86,     0,   151,    56,     0,
      89,    96,    90,     0,     0,    92,    94,    84,    12,     0,
       0,     0,    46,     0,    68,    66,    59,    63,     0,     0,
      69,    71,   149,     0,     0,   131,   130,   129,   128,   125,
     126,   127,   132,   134,   133,   124,     0,     0,   136,     0,
     138,   137,     0,     0,     0,     0,   159,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   118,     0,     0,   115,
     207,     0,     0,     0,   224,     0,   206,   211,     0,     0,
       0,     0,     0,     0,     0,     0,   244,   245,     0,   246,
      85,    97,    99,    98,   100,     0,     0,     0,    88,    87,
       0,     0,    48,    55,    47,    53,    58,    72,     0,    64,
       0,    99,   150,     0,   173,     0,   123,     0,   158,   157,
       0,   155,   160,     0,   178,     0,   180,   182,   184,   186,
     188,   189,   193,   194,   191,   192,   197,   196,   199,   200,
     202,   203,   204,     0,   116,   174,   208,   218,   121,   220,
       0,     0,     0,     0,     0,     0,   243,   247,   101,     0,
       0,   103,     0,   107,     0,     0,    91,    93,    95,    49,
      70,    73,   152,   139,   154,     0,   156,     0,   117,   119,
     219,     0,     0,     0,     0,     0,   105,     0,   109,     0,
     104,   108,   102,   161,   176,   229,   231,   232,     0,     0,
       0,   106,   110,   227,     0,     0,   234,     0,   230,   233,
     235
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    24,    25,    26,    64,    28,    29,    30,   148,    31,
      66,    33,    34,    35,    36,    37,   110,    84,    85,   176,
      39,    40,    89,    90,    91,   199,   200,    41,    42,   111,
      72,    44,   183,   344,   185,   186,   345,   274,   275,   112,
      46,   113,   247,   150,   151,   216,   115,   116,   117,   118,
     204,   119,   120,   303,   121,   122,   123,   124,   125,   126,
     127,   128,   129,   130,   131,   132,   152,   179,   154,   155,
     156,   157,   158,   159,   160,   161,   384,   162,   163,   164,
     165,   166,   167,   168,   169,   170,   171,   172
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -250
static const yytype_int16 yypact[] =
{
    1249,  -250,  -250,  -250,  -250,  -250,  -250,  -250,  -250,  -250,
    -250,  -250,  -250,  -250,  -250,  -250,  -250,  -250,  -250,  -250,
    -250,  -250,  -250,  -250,    39,  1249,  -250,  -250,  -250,  -250,
    -250,   -72,    29,  1087,  1087,  1087,  -250,   -24,  -250,  -250,
     -24,   994,   -18,    10,   153,    45,  -250,  -250,  -250,    45,
    -250,  -250,   -72,   994,  -250,  -250,  -250,  -250,  -250,   -50,
      23,   -50,  1741,  1653,  -250,   724,    29,  -250,   577,   153,
    -250,  -250,    10,  -250,  1350,  1282,    16,    26,  -250,  -250,
     724,  -250,    23,    43,   179,  -250,  1741,  1741,  1741,   814,
    -250,   -12,  -250,  -250,  -250,  -250,  -250,  -250,  -250,  -250,
    -250,  -250,  -250,  -250,  -250,  -250,  -250,  -250,  -250,  -250,
    -250,  -250,  1041,  -250,  -250,   471,  1653,  1653,  1653,  -250,
     167,  -250,  -250,    33,    -2,    35,    37,    53,   194,    95,
     206,   189,    86,  1653,  -250,  -250,  -250,  -250,  -250,  -250,
    -250,  -250,  -250,  -250,  -250,  -250,  -250,  -250,   678,    66,
     -39,  -250,  -250,   577,   768,  -250,  -250,    81,  1653,  -250,
    -250,    83,    83,  -250,  -250,    83,   948,    83,    23,    79,
      79,  1318,  -250,  -250,  -250,  -250,    89,  -250,  -250,  1653,
    -250,    68,  -250,    87,   123,   100,  -250,  -250,  -250,   210,
    1653,   -22,  -250,   903,  -250,  -250,  -250,  -250,  1653,    15,
    -250,   133,   131,    93,   129,  -250,  -250,  -250,  -250,  -250,
    -250,  -250,  -250,  -250,  -250,  -250,  1653,  1653,  -250,  1041,
    -250,  -250,    23,    23,  1653,  1419,  -250,  1653,  1653,  1653,
    1653,  1653,  1653,  1653,  1653,  1653,  1653,  1653,  1653,  1653,
    1653,  1653,  1653,  1653,  1653,  1653,  -250,   218,   223,  -250,
    -250,   858,   948,  1653,  -250,    42,  -250,  -250,   948,   137,
    1653,  1653,  1653,   191,  1318,    79,  -250,  -250,   -39,  -250,
    -250,  -250,    72,  -250,   153,  1451,  1133,    23,  -250,  -250,
     623,   -19,  -250,  -250,  -250,  -250,  -250,  -250,   -12,  -250,
    1653,   153,  -250,  1166,  -250,  1653,  -250,   147,  -250,  -250,
     -29,  -250,  -250,    94,    -2,    36,    35,    37,    53,   194,
      95,    95,   206,   206,   206,   206,   189,   189,    86,    86,
    -250,  -250,  -250,  1520,  -250,  -250,  -250,  -250,  -250,  -250,
     948,   104,   116,   124,    83,  1318,  -250,  -250,   153,  1552,
    1315,  -250,   148,  -250,   157,   165,  -250,  -250,  -250,  -250,
    -250,  -250,  -250,  -250,  -250,  1653,  -250,  1653,  -250,  -250,
    -250,   948,   948,   948,  1653,  1621,  -250,   176,  -250,   183,
    -250,  -250,  -250,  -250,  -250,   232,  -250,  -250,   126,   948,
     132,  -250,  -250,  -250,   948,    79,  -250,   948,  -250,  -250,
    -250
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -250,  -250,  -250,   245,     9,  -250,  -250,  -250,   -20,    64,
      13,  -250,   352,   159,  -250,  -250,     0,   200,  -179,  -140,
    -250,  -250,   187,   -79,   -58,  -250,     6,    24,   -37,    55,
    -250,   -35,  -250,   -71,  -250,    21,   -55,  -248,   -41,   158,
     260,  -128,  -250,   193,   -40,  -250,   275,   198,  -250,  -250,
      92,  -107,  -250,  -250,  -250,   -47,  -250,    97,    84,    98,
      96,    82,    74,    49,    77,    80,    12,    44,   181,    99,
    -250,  -250,  -250,  -249,   -30,  -250,  -250,  -250,  -250,  -250,
      69,  -250,  -250,  -250,  -250,  -250,  -250,  -250
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint16 yytable[] =
{
      38,    51,    54,    74,   184,   246,    71,    69,    49,    27,
     197,   221,   285,    32,    21,   335,    21,     3,   259,    21,
      21,    65,    79,   114,   338,    38,    21,   178,    74,   194,
     195,    50,    38,    80,    27,   174,    54,    59,    32,    47,
      61,   253,    38,   338,    20,    38,    55,    56,    57,    38,
     283,   253,    58,    67,   202,    43,    53,   354,   287,   284,
      83,    21,   349,   229,    50,    81,    38,    21,   149,    76,
      23,   198,    22,    77,   134,   182,    23,   135,    58,   224,
      43,    60,    83,    21,    62,    68,   365,    43,   181,   134,
      77,    38,   188,   249,    22,   288,    52,    68,    43,   227,
      43,   187,   285,    82,    43,    86,    21,   133,    63,    68,
      21,   178,   153,    22,   197,   201,   253,    23,    50,   357,
     254,    43,   253,   325,    68,   190,   273,    43,   228,    22,
      52,   230,    50,    23,   231,   342,   320,   321,   322,   266,
     267,   269,   232,   178,   272,    50,    43,   292,   149,   252,
     351,   178,    22,   149,   149,    73,    23,   134,    45,    73,
      23,   202,   235,   236,   258,   291,   149,   277,   265,   289,
     243,    23,   278,   253,   355,   270,   296,   133,   294,   356,
     280,    38,    50,    45,   253,   302,   244,   245,   352,   361,
      45,    83,   153,   237,   238,   359,   253,   153,   153,   367,
      45,   362,    75,    45,   253,   271,   253,    45,   279,   363,
     153,   385,   253,   328,   295,    22,   290,   387,    73,    23,
     330,    88,   298,   299,    45,   254,   146,    75,   178,   103,
     104,   222,   353,   339,   370,   336,    43,    69,   337,   272,
      73,    23,   371,   178,   383,    88,    88,    88,    88,    45,
     372,   149,   149,   257,    73,    23,   291,    43,   149,   191,
     192,   223,   381,   233,   234,   263,   239,   240,   382,   369,
      48,    88,    38,   193,   217,   219,    38,   346,   225,   241,
     242,    83,   189,   114,   312,   313,   314,   315,    38,   181,
     281,   282,   178,   181,   350,   153,   153,   339,   323,   324,
      76,   348,   153,   253,   325,   203,   181,   310,   311,    78,
     374,   297,   201,   306,   309,   373,   316,   317,   226,   260,
     261,   318,   319,   262,   304,   264,   248,   308,   307,   251,
     149,    43,   334,     0,     0,     0,     0,     0,     0,   276,
       0,     0,     0,    43,     0,     0,   255,     0,    43,   177,
     257,   327,    88,   181,     0,   389,     0,   329,     0,     0,
     293,   149,   149,   149,   268,     0,     0,   133,     0,     0,
       0,     0,   248,     0,   153,     0,     0,     0,    88,   149,
       0,     0,     0,     0,   149,     0,     0,   149,     0,     0,
       0,   218,   220,   177,     0,    70,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   153,   153,   153,     0,     0,
     203,     0,   203,     0,    87,     0,     0,   300,     0,     0,
       0,   305,     0,   153,   173,     0,     0,     0,   153,   360,
     276,   153,   340,   177,   276,     0,     0,     0,    87,    87,
      87,    87,     0,     0,     0,     0,    45,     0,     0,   293,
       0,   293,     0,   331,   332,   333,     0,     0,     0,     0,
     375,   376,   377,     0,    87,   177,     0,     0,     0,     0,
       0,     0,     0,   177,     0,     0,     0,     0,   386,     0,
       0,     0,     0,   388,     0,     0,   390,     0,     0,     0,
       0,     0,   364,     0,     0,     0,   340,     0,     0,     0,
       0,     0,   177,     0,   177,   177,   177,   177,   177,   177,
     177,   177,   177,   177,   177,   177,   177,   177,   177,   177,
     177,   205,   206,   207,   208,   209,   210,   211,   212,   213,
     214,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    87,     0,     0,     0,     0,
     177,     0,     0,   215,     0,     0,     0,   378,   380,     0,
       0,     0,     0,     0,     0,   177,     0,     0,     0,     0,
     177,    87,     0,     0,     0,     0,     0,     0,     0,     0,
       1,   136,   137,     2,     3,   138,   139,   140,     4,     0,
       5,     6,     7,   141,   142,   143,     8,     9,    10,   144,
      11,    12,    92,    13,    14,   145,    15,    16,    17,    18,
      19,    20,   146,     0,   177,    21,    93,    94,    95,    96,
      97,    98,    99,   100,   101,   102,     1,     0,     0,     2,
       3,     0,   177,     0,     4,     0,     5,     6,     7,   103,
     104,     0,     8,     9,    10,     0,    11,    12,     0,    13,
      14,     0,    15,    16,    17,    18,    19,    20,   147,     0,
       0,    22,     0,     0,     0,    23,   105,   106,   107,   108,
     109,     0,   347,     0,     0,     0,     0,     0,     0,    58,
      50,     1,   136,   137,     2,     3,   138,   139,   140,     4,
       0,     5,     6,     7,   141,   142,   143,     8,     9,    10,
     144,    11,    12,    92,    13,    14,   145,    15,    16,    17,
      18,    19,    20,   146,     0,     0,    21,    93,    94,    95,
      96,    97,    98,    99,   100,   101,   102,     1,     0,     0,
       2,     3,     0,     0,     0,     4,     0,     5,     6,     7,
     103,   104,     0,     8,     9,    10,     0,    11,    12,     0,
      13,    14,     0,    15,    16,    17,    18,    19,    20,   250,
       0,     0,    22,     0,     0,     0,    23,   105,   106,   107,
     108,   109,   136,   137,     0,     0,   138,   139,   140,     0,
      58,    50,     0,     0,   141,   142,   143,     0,     0,     0,
     144,     0,     0,    92,     0,     0,   145,     0,     0,     0,
       0,     0,     0,   146,     0,     0,    21,    93,    94,    95,
      96,    97,    98,    99,   100,   101,   102,     0,     0,     0,
       2,     3,     0,     0,     0,     4,    58,     5,     0,     7,
     103,   104,     0,     8,     9,     0,     0,    11,    12,     0,
       0,    14,     0,     0,    16,    17,    18,    19,    20,   256,
       0,     0,    22,     0,     0,     0,    23,   105,   106,   107,
     108,   109,   136,   137,     0,     0,   138,   139,   140,     0,
      58,    50,     0,     0,   141,   142,   143,     0,     0,     0,
     144,     0,     0,    92,     0,     0,   145,     0,     0,     0,
       0,     0,     0,   146,     0,   196,    21,    93,    94,    95,
      96,    97,    98,    99,   100,   101,   102,     0,     0,     2,
       3,     0,     0,     0,     4,     0,     5,     0,     7,     0,
     103,   104,     8,     9,     0,     0,    11,    12,     0,     0,
      14,     0,     0,    16,    17,    18,    19,    20,     0,   326,
       0,     0,    22,     0,     0,     0,    23,   105,   106,   107,
     108,   109,   136,   137,     0,     0,   138,   139,   140,     0,
      58,    50,     0,     0,   141,   142,   143,     0,     0,     0,
     144,     0,     0,    92,     0,     0,   145,     0,     0,     0,
       0,     0,     0,   146,   286,     0,    21,    93,    94,    95,
      96,    97,    98,    99,   100,   101,   102,     1,     0,     0,
       2,     3,     0,     0,     0,     4,     0,     5,     6,     7,
     103,   104,     0,     8,     9,    10,     0,    11,    12,     0,
      13,    14,     0,    15,    16,    17,    18,    19,    20,     0,
       0,     0,    22,     0,     0,     0,    23,   105,   106,   107,
     108,   109,     0,     0,     0,     0,     0,     2,     3,     0,
      58,    50,     4,     0,     5,     0,     7,     0,     0,     0,
       8,     9,     0,     0,    11,    12,    92,     0,    14,     0,
       0,    16,    17,    18,    19,    20,    63,     0,     0,    21,
      93,    94,    95,    96,    97,    98,    99,   100,   101,   102,
       1,     0,     0,     2,     3,     0,    58,     0,     4,     0,
       5,     6,     7,   103,   104,     0,     8,     9,    10,     0,
      11,    12,     0,    13,    14,     0,    15,    16,    17,    18,
      19,    20,     0,     0,     0,    22,     0,     0,     0,    23,
     105,   106,   107,   108,   109,     0,     1,     0,     0,     2,
       3,     0,     0,    58,     4,     0,     5,     6,     7,     0,
       0,     0,     8,     9,    10,     0,    11,    12,     0,    13,
      14,     0,    15,    16,    17,    18,    19,    20,     0,     1,
       0,    21,     2,     3,     0,     0,     0,     4,     0,     5,
       6,     7,     0,     0,     0,     8,     9,    10,     0,    11,
      12,     0,    13,    14,     0,    15,    16,    17,    18,    19,
      20,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    22,   343,     0,
      73,    23,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      22,   343,     1,    73,    23,     2,     3,     0,     0,     0,
       4,     0,     5,     6,     7,     0,     0,     0,     8,     9,
      10,     0,    11,    12,     0,    13,    14,     0,    15,    16,
      17,    18,    19,    20,     0,     1,     0,    21,     2,     3,
       0,     0,     0,     4,     0,     5,     6,     7,     0,     0,
       0,     8,     9,    10,     0,    11,    12,     0,    13,    14,
       0,    15,    16,    17,    18,    19,    20,     0,     1,     0,
      21,     2,     3,     0,     0,     0,     4,     0,     5,     6,
       7,     0,     0,    22,     8,     9,    10,    23,    11,    12,
       0,    13,    14,    92,    15,    16,    17,    18,    19,    20,
       0,     0,     0,     0,     0,     0,    21,    93,    94,    95,
      96,    97,    98,    99,   100,   101,   102,   180,     0,     0,
       0,     0,     0,     0,     0,    92,     0,     0,     0,     0,
     103,   104,     0,     0,     0,     0,     0,     0,    21,    93,
      94,    95,    96,    97,    98,    99,   100,   101,   102,     0,
     368,     0,    22,     0,     0,     0,    23,   105,   106,   107,
     108,   109,   103,   104,     0,     0,     0,     0,     0,     0,
      58,    50,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    22,     0,   175,     0,    23,   105,
     106,   107,   108,   109,    92,     0,     0,     0,     0,     0,
       0,     0,    58,     0,     0,     0,     0,    21,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,     0,     0,
       0,     0,     0,     0,     0,     0,    92,     0,     0,     0,
       0,   103,   104,     0,     0,     0,     0,     0,     0,    21,
      93,    94,    95,    96,    97,    98,    99,   100,   101,   102,
       0,     0,     0,    22,   301,     0,     0,    23,   105,   106,
     107,   108,   109,   103,   104,     0,     0,     0,     0,     0,
       0,    58,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    22,     0,   341,     0,    23,
     105,   106,   107,   108,   109,    92,     0,     0,     0,     0,
       0,     0,     0,    58,     0,     0,     0,     0,    21,    93,
      94,    95,    96,    97,    98,    99,   100,   101,   102,     0,
       0,     0,     0,     0,     0,     0,     0,    92,     0,     0,
       0,     0,   103,   104,     0,     0,     0,     0,     0,     0,
      21,    93,    94,    95,    96,    97,    98,    99,   100,   101,
     102,   358,     0,     0,    22,     0,     0,     0,    23,   105,
     106,   107,   108,   109,   103,   104,     0,     0,     0,     0,
       0,     0,    58,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    22,     0,   366,     0,
      23,   105,   106,   107,   108,   109,    92,     0,     0,     0,
       0,     0,     0,     0,    58,     0,     0,     0,     0,    21,
      93,    94,    95,    96,    97,    98,    99,   100,   101,   102,
       0,     0,     0,     0,     0,     0,     0,     0,    92,     0,
       0,     0,     0,   103,   104,     0,     0,     0,     0,     0,
       0,    21,    93,    94,    95,    96,    97,    98,    99,   100,
     101,   102,     0,     0,     0,    22,   379,     0,     0,    23,
     105,   106,   107,   108,   109,   103,   104,     0,     0,     0,
       0,     0,     0,    58,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    22,     0,     0,
       0,    23,   105,   106,   107,   108,   109,     2,     3,     0,
       0,     0,     4,     0,     5,    58,     7,     0,     0,     0,
       8,     9,     0,     0,    11,    12,     0,     0,    14,     0,
       0,    16,    17,    18,    19,    20
};

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-250)))

#define yytable_value_is_error(Yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
       0,    31,    32,    44,    75,   133,    43,    42,    80,     0,
      89,   118,   191,     0,    38,   264,    38,     7,   158,    38,
      38,    41,    52,    63,   272,    25,    38,    74,    69,    87,
      88,   103,    32,    53,    25,    72,    66,    37,    25,     0,
      40,    80,    42,   291,    34,    45,    33,    34,    35,    49,
     190,    80,   102,    41,   112,     0,    32,    86,   198,    81,
      60,    38,    81,    65,   103,    53,    66,    38,    68,    45,
      88,    83,    84,    49,    65,    75,    88,    65,   102,   120,
      25,    37,    82,    38,    40,    41,   335,    32,    75,    80,
      66,    91,    80,   133,    84,    80,    32,    53,    43,    66,
      45,    85,   281,    59,    49,    61,    38,    63,    82,    65,
      38,   158,    68,    84,   193,    91,    80,    88,   103,    83,
     150,    66,    80,    81,    80,    82,   181,    72,    95,    84,
      66,    96,   103,    88,    97,   275,   243,   244,   245,   169,
     170,   171,    89,   190,   181,   103,    91,   202,   148,    83,
     290,   198,    84,   153,   154,    87,    88,   148,     0,    87,
      88,   219,    67,    68,    83,   202,   166,    80,   168,   199,
      84,    88,    85,    80,    80,    86,   216,   133,    85,    85,
      80,   181,   103,    25,    80,   225,   100,   101,   295,    85,
      32,   191,   148,    98,    99,   323,    80,   153,   154,   339,
      42,    85,    44,    45,    80,   181,    80,    49,    85,    85,
     166,    85,    80,   253,    85,    84,    83,    85,    87,    88,
      83,    62,   222,   223,    66,   255,    35,    69,   275,    62,
      63,    64,    85,   274,    86,   265,   181,   272,   268,   276,
      87,    88,    85,   290,    12,    86,    87,    88,    89,    91,
      85,   251,   252,   154,    87,    88,   293,   202,   258,    80,
      81,    94,    86,    69,    70,   166,    60,    61,    85,   340,
      25,   112,   272,    86,   116,   117,   276,   277,   120,    90,
      91,   281,    82,   323,   235,   236,   237,   238,   288,   276,
      80,    81,   339,   280,   288,   251,   252,   338,    80,    81,
     276,   280,   258,    80,    81,   112,   293,   233,   234,    49,
     357,   219,   288,   229,   232,   355,   239,   240,   120,   161,
     162,   241,   242,   165,   227,   167,   133,   231,   230,   148,
     330,   276,   263,    -1,    -1,    -1,    -1,    -1,    -1,   181,
      -1,    -1,    -1,   288,    -1,    -1,   153,    -1,   293,    74,
     251,   252,   193,   340,    -1,   385,    -1,   258,    -1,    -1,
     202,   361,   362,   363,   171,    -1,    -1,   323,    -1,    -1,
      -1,    -1,   179,    -1,   330,    -1,    -1,    -1,   219,   379,
      -1,    -1,    -1,    -1,   384,    -1,    -1,   387,    -1,    -1,
      -1,   116,   117,   118,    -1,    43,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   361,   362,   363,    -1,    -1,
     217,    -1,   219,    -1,    62,    -1,    -1,   224,    -1,    -1,
      -1,   228,    -1,   379,    72,    -1,    -1,    -1,   384,   330,
     272,   387,   274,   158,   276,    -1,    -1,    -1,    86,    87,
      88,    89,    -1,    -1,    -1,    -1,   288,    -1,    -1,   291,
      -1,   293,    -1,   260,   261,   262,    -1,    -1,    -1,    -1,
     361,   362,   363,    -1,   112,   190,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   198,    -1,    -1,    -1,    -1,   379,    -1,
      -1,    -1,    -1,   384,    -1,    -1,   387,    -1,    -1,    -1,
      -1,    -1,   334,    -1,    -1,    -1,   338,    -1,    -1,    -1,
      -1,    -1,   227,    -1,   229,   230,   231,   232,   233,   234,
     235,   236,   237,   238,   239,   240,   241,   242,   243,   244,
     245,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   193,    -1,    -1,    -1,    -1,
     275,    -1,    -1,    82,    -1,    -1,    -1,   364,   365,    -1,
      -1,    -1,    -1,    -1,    -1,   290,    -1,    -1,    -1,    -1,
     295,   219,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    -1,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    -1,   339,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,     3,    -1,    -1,     6,
       7,    -1,   357,    -1,    11,    -1,    13,    14,    15,    62,
      63,    -1,    19,    20,    21,    -1,    23,    24,    -1,    26,
      27,    -1,    29,    30,    31,    32,    33,    34,    81,    -1,
      -1,    84,    -1,    -1,    -1,    88,    89,    90,    91,    92,
      93,    -1,    49,    -1,    -1,    -1,    -1,    -1,    -1,   102,
     103,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      -1,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    -1,    -1,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,     3,    -1,    -1,
       6,     7,    -1,    -1,    -1,    11,    -1,    13,    14,    15,
      62,    63,    -1,    19,    20,    21,    -1,    23,    24,    -1,
      26,    27,    -1,    29,    30,    31,    32,    33,    34,    81,
      -1,    -1,    84,    -1,    -1,    -1,    88,    89,    90,    91,
      92,    93,     4,     5,    -1,    -1,     8,     9,    10,    -1,
     102,   103,    -1,    -1,    16,    17,    18,    -1,    -1,    -1,
      22,    -1,    -1,    25,    -1,    -1,    28,    -1,    -1,    -1,
      -1,    -1,    -1,    35,    -1,    -1,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    -1,    -1,    -1,
       6,     7,    -1,    -1,    -1,    11,   102,    13,    -1,    15,
      62,    63,    -1,    19,    20,    -1,    -1,    23,    24,    -1,
      -1,    27,    -1,    -1,    30,    31,    32,    33,    34,    81,
      -1,    -1,    84,    -1,    -1,    -1,    88,    89,    90,    91,
      92,    93,     4,     5,    -1,    -1,     8,     9,    10,    -1,
     102,   103,    -1,    -1,    16,    17,    18,    -1,    -1,    -1,
      22,    -1,    -1,    25,    -1,    -1,    28,    -1,    -1,    -1,
      -1,    -1,    -1,    35,    -1,    81,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    -1,    -1,     6,
       7,    -1,    -1,    -1,    11,    -1,    13,    -1,    15,    -1,
      62,    63,    19,    20,    -1,    -1,    23,    24,    -1,    -1,
      27,    -1,    -1,    30,    31,    32,    33,    34,    -1,    81,
      -1,    -1,    84,    -1,    -1,    -1,    88,    89,    90,    91,
      92,    93,     4,     5,    -1,    -1,     8,     9,    10,    -1,
     102,   103,    -1,    -1,    16,    17,    18,    -1,    -1,    -1,
      22,    -1,    -1,    25,    -1,    -1,    28,    -1,    -1,    -1,
      -1,    -1,    -1,    35,    81,    -1,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,     3,    -1,    -1,
       6,     7,    -1,    -1,    -1,    11,    -1,    13,    14,    15,
      62,    63,    -1,    19,    20,    21,    -1,    23,    24,    -1,
      26,    27,    -1,    29,    30,    31,    32,    33,    34,    -1,
      -1,    -1,    84,    -1,    -1,    -1,    88,    89,    90,    91,
      92,    93,    -1,    -1,    -1,    -1,    -1,     6,     7,    -1,
     102,   103,    11,    -1,    13,    -1,    15,    -1,    -1,    -1,
      19,    20,    -1,    -1,    23,    24,    25,    -1,    27,    -1,
      -1,    30,    31,    32,    33,    34,    82,    -1,    -1,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
       3,    -1,    -1,     6,     7,    -1,   102,    -1,    11,    -1,
      13,    14,    15,    62,    63,    -1,    19,    20,    21,    -1,
      23,    24,    -1,    26,    27,    -1,    29,    30,    31,    32,
      33,    34,    -1,    -1,    -1,    84,    -1,    -1,    -1,    88,
      89,    90,    91,    92,    93,    -1,     3,    -1,    -1,     6,
       7,    -1,    -1,   102,    11,    -1,    13,    14,    15,    -1,
      -1,    -1,    19,    20,    21,    -1,    23,    24,    -1,    26,
      27,    -1,    29,    30,    31,    32,    33,    34,    -1,     3,
      -1,    38,     6,     7,    -1,    -1,    -1,    11,    -1,    13,
      14,    15,    -1,    -1,    -1,    19,    20,    21,    -1,    23,
      24,    -1,    26,    27,    -1,    29,    30,    31,    32,    33,
      34,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    84,    85,    -1,
      87,    88,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      84,    85,     3,    87,    88,     6,     7,    -1,    -1,    -1,
      11,    -1,    13,    14,    15,    -1,    -1,    -1,    19,    20,
      21,    -1,    23,    24,    -1,    26,    27,    -1,    29,    30,
      31,    32,    33,    34,    -1,     3,    -1,    38,     6,     7,
      -1,    -1,    -1,    11,    -1,    13,    14,    15,    -1,    -1,
      -1,    19,    20,    21,    -1,    23,    24,    -1,    26,    27,
      -1,    29,    30,    31,    32,    33,    34,    -1,     3,    -1,
      38,     6,     7,    -1,    -1,    -1,    11,    -1,    13,    14,
      15,    -1,    -1,    84,    19,    20,    21,    88,    23,    24,
      -1,    26,    27,    25,    29,    30,    31,    32,    33,    34,
      -1,    -1,    -1,    -1,    -1,    -1,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    85,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    25,    -1,    -1,    -1,    -1,
      62,    63,    -1,    -1,    -1,    -1,    -1,    -1,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    -1,
      85,    -1,    84,    -1,    -1,    -1,    88,    89,    90,    91,
      92,    93,    62,    63,    -1,    -1,    -1,    -1,    -1,    -1,
     102,   103,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    84,    -1,    86,    -1,    88,    89,
      90,    91,    92,    93,    25,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   102,    -1,    -1,    -1,    -1,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    25,    -1,    -1,    -1,
      -1,    62,    63,    -1,    -1,    -1,    -1,    -1,    -1,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      -1,    -1,    -1,    84,    85,    -1,    -1,    88,    89,    90,
      91,    92,    93,    62,    63,    -1,    -1,    -1,    -1,    -1,
      -1,   102,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    84,    -1,    86,    -1,    88,
      89,    90,    91,    92,    93,    25,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   102,    -1,    -1,    -1,    -1,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    25,    -1,    -1,
      -1,    -1,    62,    63,    -1,    -1,    -1,    -1,    -1,    -1,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    81,    -1,    -1,    84,    -1,    -1,    -1,    88,    89,
      90,    91,    92,    93,    62,    63,    -1,    -1,    -1,    -1,
      -1,    -1,   102,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    84,    -1,    86,    -1,
      88,    89,    90,    91,    92,    93,    25,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   102,    -1,    -1,    -1,    -1,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    25,    -1,
      -1,    -1,    -1,    62,    63,    -1,    -1,    -1,    -1,    -1,
      -1,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    -1,    -1,    -1,    84,    85,    -1,    -1,    88,
      89,    90,    91,    92,    93,    62,    63,    -1,    -1,    -1,
      -1,    -1,    -1,   102,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    84,    -1,    -1,
      -1,    88,    89,    90,    91,    92,    93,     6,     7,    -1,
      -1,    -1,    11,    -1,    13,   102,    15,    -1,    -1,    -1,
      19,    20,    -1,    -1,    23,    24,    -1,    -1,    27,    -1,
      -1,    30,    31,    32,    33,    34
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     6,     7,    11,    13,    14,    15,    19,    20,
      21,    23,    24,    26,    27,    29,    30,    31,    32,    33,
      34,    38,    84,    88,   105,   106,   107,   108,   109,   110,
     111,   113,   114,   115,   116,   117,   118,   119,   120,   124,
     125,   131,   132,   133,   135,   143,   144,     0,   107,    80,
     103,   178,   113,   131,   178,   114,   114,   114,   102,   120,
     171,   120,   171,    82,   108,   112,   114,   170,   171,   135,
     116,   132,   134,    87,   142,   143,   131,   131,   144,   178,
     112,   170,   171,   120,   121,   122,   171,   116,   117,   126,
     127,   128,    25,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    62,    63,    89,    90,    91,    92,    93,
     120,   133,   143,   145,   148,   150,   151,   152,   153,   155,
     156,   158,   159,   160,   161,   162,   163,   164,   165,   166,
     167,   168,   169,   171,   108,   170,     4,     5,     8,     9,
      10,    16,    17,    18,    22,    28,    35,    81,   112,   120,
     147,   148,   170,   171,   172,   173,   174,   175,   176,   177,
     178,   179,   181,   182,   183,   184,   185,   186,   187,   188,
     189,   190,   191,   116,   132,    86,   123,   150,   159,   171,
      85,   114,   120,   136,   137,   138,   139,    85,   170,   121,
      82,    80,    81,   126,   128,   128,    81,   127,    83,   129,
     130,   131,   128,   147,   154,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    82,   149,   143,   150,   143,
     150,   155,    64,    94,   142,   143,   151,    66,    95,    65,
      96,    97,    89,    69,    70,    67,    68,    98,    99,    60,
      61,    90,    91,    84,   100,   101,   145,   146,   147,   148,
      81,   172,    83,    80,   178,   147,    81,   173,    83,   123,
     143,   143,   143,   173,   143,   120,   178,   178,   147,   178,
      86,   131,   132,   140,   141,   142,   143,    80,    85,    85,
      80,    80,    81,   123,    81,   122,    81,   123,    80,   178,
      83,   132,   140,   143,    85,    85,   148,   154,   120,   120,
     147,    85,   148,   157,   161,   147,   162,   163,   164,   165,
     166,   166,   167,   167,   167,   167,   168,   168,   169,   169,
     155,   155,   155,    80,    81,    81,    81,   173,   148,   173,
      83,   147,   147,   147,   184,   177,   178,   178,   141,   142,
     143,    86,   123,    85,   137,   140,   120,    49,   139,    81,
     130,   123,   155,    85,    86,    80,    85,    83,    81,   145,
     173,    85,    85,    85,   143,   177,    86,   123,    85,   137,
      86,    85,    85,   148,   159,   173,   173,   173,   147,    85,
     147,    86,    85,    12,   180,    85,   173,    85,   173,   178,
     173
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
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))

/* Error token number */
#define YYTERROR	1
#define YYERRCODE	256


/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
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
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
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
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
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
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
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
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
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
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
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
      YYSIZE_T yyn = 0;
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

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULL, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULL;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULL, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
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




/* The lookahead symbol.  */
int yychar;


#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval YY_INITIAL_VALUE(yyval_default);

/* Number of syntax errors so far.  */
int yynerrs;

linecoord linenumbers[1024];
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
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));
 FILE* in;
      char inputfile[256], linein[64];
      char* word;
      int linecount, next = 0;
      //linecoord linenumbers[1024];
      strcpy(inputfile, "index_final");
      in = fopen(inputfile, "r");
      
      while(!feof(in)) {
        int i=0, j=0;
        linecount = fgets(linein, 2048, in);
        word = strtok(linecount, " ");
        //printf("Line %s\n", word);
        if(word==NULL)
          break;
        linenumbers[next].myline = atoi(word);
        word = strtok(NULL, " ");
        linenumbers[next].original = atoi(word);
        next++;
      }
      fclose(in);
      
      
  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
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
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
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

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
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
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
/* Line 1792 of yacc.c  */
#line 127 "hcc.y"
    {translationunit = create_translationunit((yyvsp[(1) - (1)].ast));}
    break;

  case 3:
/* Line 1792 of yacc.c  */
#line 130 "hcc.y"
    {(yyval.ast)=(yyvsp[(1) - (1)].ast);}
    break;

  case 4:
/* Line 1792 of yacc.c  */
#line 131 "hcc.y"
    {(yyval.ast)=append_astnode((yyvsp[(1) - (2)].ast),(yyvsp[(2) - (2)].ast));}
    break;

  case 5:
/* Line 1792 of yacc.c  */
#line 134 "hcc.y"
    {(yyval.ast)=(yyvsp[(1) - (1)].ast);}
    break;

  case 6:
/* Line 1792 of yacc.c  */
#line 135 "hcc.y"
    {(yyval.ast)=(yyvsp[(1) - (1)].ast);}
    break;

  case 7:
/* Line 1792 of yacc.c  */
#line 139 "hcc.y"
    {(yyval.ast)=base_of(create_declaration((yyvsp[(1) - (3)].ast),(yyvsp[(2) - (3)].ast)));}
    break;

  case 8:
/* Line 1792 of yacc.c  */
#line 141 "hcc.y"
    {(yyval.ast)=base_of(create_declaration((yyvsp[(1) - (2)].ast),NULL));}
    break;

  case 9:
/* Line 1792 of yacc.c  */
#line 145 "hcc.y"
    {(yyval.ast)=base_of(create_declaration(NULL,(yyvsp[(1) - (2)].ast)));}
    break;

  case 10:
/* Line 1792 of yacc.c  */
#line 148 "hcc.y"
    {(yyval.ast)=(yyvsp[(1) - (1)].ast);}
    break;

  case 11:
/* Line 1792 of yacc.c  */
#line 149 "hcc.y"
    {(yyval.ast)=(yyvsp[(1) - (1)].ast);}
    break;

  case 12:
/* Line 1792 of yacc.c  */
#line 153 "hcc.y"
    {(yyval.ast)=base_of(create_functiondeclaration((yyvsp[(1) - (4)].ast),(yyvsp[(2) - (4)].ast),(yyvsp[(3) - (4)].ast),(yyvsp[(4) - (4)].ast)));}
    break;

  case 13:
/* Line 1792 of yacc.c  */
#line 155 "hcc.y"
    {(yyval.ast)=base_of(create_functiondeclaration((yyvsp[(1) - (3)].ast),(yyvsp[(2) - (3)].ast),NULL,(yyvsp[(3) - (3)].ast)));}
    break;

  case 14:
/* Line 1792 of yacc.c  */
#line 157 "hcc.y"
    {(yyval.ast)=base_of(create_functiondeclaration(NULL,(yyvsp[(1) - (3)].ast),(yyvsp[(2) - (3)].ast),(yyvsp[(3) - (3)].ast)));}
    break;

  case 15:
/* Line 1792 of yacc.c  */
#line 159 "hcc.y"
    {(yyval.ast)=base_of(create_functiondeclaration(NULL,(yyvsp[(1) - (2)].ast),NULL,(yyvsp[(2) - (2)].ast)));}
    break;

  case 16:
/* Line 1792 of yacc.c  */
#line 162 "hcc.y"
    {(yyval.ast)=(yyvsp[(1) - (1)].ast);}
    break;

  case 17:
/* Line 1792 of yacc.c  */
#line 163 "hcc.y"
    {(yyval.ast)=append_astnode((yyvsp[(1) - (2)].ast),(yyvsp[(2) - (2)].ast));}
    break;

  case 18:
/* Line 1792 of yacc.c  */
#line 166 "hcc.y"
    {(yyval.ast)=(yyvsp[(1) - (1)].ast);}
    break;

  case 19:
/* Line 1792 of yacc.c  */
#line 167 "hcc.y"
    {(yyval.ast)=append_astnode((yyvsp[(1) - (3)].ast),(yyvsp[(3) - (3)].ast));}
    break;

  case 20:
/* Line 1792 of yacc.c  */
#line 171 "hcc.y"
    {(yyval.ast) = base_of(create_declarationspecifier1((yyvsp[(1) - (1)].ast)));}
    break;

  case 21:
/* Line 1792 of yacc.c  */
#line 173 "hcc.y"
    {(yyval.ast) = base_of(create_declarationspecifier2((yyvsp[(1) - (2)].ast),(yyvsp[(2) - (2)].ast)));}
    break;

  case 22:
/* Line 1792 of yacc.c  */
#line 175 "hcc.y"
    {(yyval.ast) = base_of(create_declarationspecifier3((yyvsp[(1) - (1)].ast)));}
    break;

  case 23:
/* Line 1792 of yacc.c  */
#line 177 "hcc.y"
    {(yyval.ast) = base_of(create_declarationspecifier4((yyvsp[(1) - (2)].ast),(yyvsp[(2) - (2)].ast)));}
    break;

  case 24:
/* Line 1792 of yacc.c  */
#line 179 "hcc.y"
    {(yyval.ast) = base_of(create_declarationspecifier5((yyvsp[(1) - (1)].ast)));}
    break;

  case 25:
/* Line 1792 of yacc.c  */
#line 181 "hcc.y"
    {(yyval.ast) = base_of(create_declarationspecifier6((yyvsp[(1) - (2)].ast),(yyvsp[(2) - (2)].ast)));}
    break;

  case 26:
/* Line 1792 of yacc.c  */
#line 184 "hcc.y"
    {(yyval.ast) = base_of(create_atom(AUTO,tval,tcoord));}
    break;

  case 27:
/* Line 1792 of yacc.c  */
#line 185 "hcc.y"
    {(yyval.ast) = base_of(create_atom(REGISTER,tval,tcoord));}
    break;

  case 28:
/* Line 1792 of yacc.c  */
#line 186 "hcc.y"
    {(yyval.ast) = base_of(create_atom(STATIC,tval,tcoord));}
    break;

  case 29:
/* Line 1792 of yacc.c  */
#line 187 "hcc.y"
    {(yyval.ast) = base_of(create_atom(EXTERN,tval,tcoord));}
    break;

  case 30:
/* Line 1792 of yacc.c  */
#line 188 "hcc.y"
    {(yyval.ast) = base_of(create_atom(TYPEDEF,tval,tcoord));}
    break;

  case 31:
/* Line 1792 of yacc.c  */
#line 191 "hcc.y"
    {(yyval.ast) = base_of(create_atom(CONST,tval,tcoord));}
    break;

  case 32:
/* Line 1792 of yacc.c  */
#line 192 "hcc.y"
    {(yyval.ast) = base_of(create_atom(VOLATILE,tval,tcoord));}
    break;

  case 33:
/* Line 1792 of yacc.c  */
#line 195 "hcc.y"
    {(yyval.ast) = base_of(create_atom(VOID,tval,tcoord));}
    break;

  case 34:
/* Line 1792 of yacc.c  */
#line 196 "hcc.y"
    {(yyval.ast) = base_of(create_atom(CHAR,tval,tcoord));}
    break;

  case 35:
/* Line 1792 of yacc.c  */
#line 197 "hcc.y"
    {(yyval.ast) = base_of(create_atom(SHORT,tval,tcoord));}
    break;

  case 36:
/* Line 1792 of yacc.c  */
#line 198 "hcc.y"
    {(yyval.ast) = base_of(create_atom(INT,tval,tcoord));}
    break;

  case 37:
/* Line 1792 of yacc.c  */
#line 199 "hcc.y"
    {(yyval.ast) = base_of(create_atom(LONG,tval,tcoord));}
    break;

  case 38:
/* Line 1792 of yacc.c  */
#line 200 "hcc.y"
    {(yyval.ast) = base_of(create_atom(SIGNED,tval,tcoord));}
    break;

  case 39:
/* Line 1792 of yacc.c  */
#line 201 "hcc.y"
    {(yyval.ast) = base_of(create_atom(UNSIGNED,tval,tcoord));}
    break;

  case 40:
/* Line 1792 of yacc.c  */
#line 202 "hcc.y"
    {(yyval.ast) = base_of(create_atom(FLOAT,tval,tcoord));}
    break;

  case 41:
/* Line 1792 of yacc.c  */
#line 203 "hcc.y"
    {(yyval.ast) = base_of(create_atom(DOUBLE,tval,tcoord));}
    break;

  case 42:
/* Line 1792 of yacc.c  */
#line 204 "hcc.y"
    {(yyval.ast) = base_of(create_atom(TYPENAME,tval,tcoord));}
    break;

  case 43:
/* Line 1792 of yacc.c  */
#line 205 "hcc.y"
    {(yyval.ast) = (yyvsp[(1) - (1)].ast);}
    break;

  case 44:
/* Line 1792 of yacc.c  */
#line 206 "hcc.y"
    {(yyval.ast) = (yyvsp[(1) - (1)].ast);}
    break;

  case 45:
/* Line 1792 of yacc.c  */
#line 210 "hcc.y"
    {(yyval.ast)=base_of(create_enumspec((yyvsp[(1) - (2)].ast),(yyvsp[(2) - (2)].ast),NULL));}
    break;

  case 46:
/* Line 1792 of yacc.c  */
#line 212 "hcc.y"
    {(yyval.ast)=base_of(create_enumspec((yyvsp[(1) - (4)].ast),NULL,(yyvsp[(3) - (4)].ast)));}
    break;

  case 47:
/* Line 1792 of yacc.c  */
#line 214 "hcc.y"
    {(yyval.ast)=base_of(create_enumspec((yyvsp[(1) - (5)].ast),NULL,(yyvsp[(3) - (5)].ast)));}
    break;

  case 48:
/* Line 1792 of yacc.c  */
#line 216 "hcc.y"
    {(yyval.ast)=base_of(create_enumspec((yyvsp[(1) - (5)].ast),(yyvsp[(2) - (5)].ast),(yyvsp[(4) - (5)].ast)));}
    break;

  case 49:
/* Line 1792 of yacc.c  */
#line 218 "hcc.y"
    {(yyval.ast)=base_of(create_enumspec((yyvsp[(1) - (6)].ast),(yyvsp[(2) - (6)].ast),(yyvsp[(4) - (6)].ast)));}
    break;

  case 50:
/* Line 1792 of yacc.c  */
#line 221 "hcc.y"
    {(yyval.ast)=base_of(create_atom(ENUM,tval,tcoord));}
    break;

  case 51:
/* Line 1792 of yacc.c  */
#line 224 "hcc.y"
    {(yyval.ast) = base_of(create_atom(IDENTIFIER,tval,tcoord));}
    break;

  case 52:
/* Line 1792 of yacc.c  */
#line 228 "hcc.y"
    {(yyval.ast)=(yyvsp[(1) - (1)].ast);}
    break;

  case 53:
/* Line 1792 of yacc.c  */
#line 229 "hcc.y"
    {(yyval.ast)=append_astnode((yyvsp[(1) - (3)].ast),(yyvsp[(3) - (3)].ast));}
    break;

  case 54:
/* Line 1792 of yacc.c  */
#line 232 "hcc.y"
    {(yyval.ast)=base_of(create_enumerator((yyvsp[(1) - (1)].ast),NULL));}
    break;

  case 55:
/* Line 1792 of yacc.c  */
#line 233 "hcc.y"
    {(yyval.ast)=base_of(create_enumerator((yyvsp[(1) - (3)].ast),(yyvsp[(3) - (3)].ast)));}
    break;

  case 56:
/* Line 1792 of yacc.c  */
#line 236 "hcc.y"
    {(yyval.ast)=(yyvsp[(1) - (1)].ast);}
    break;

  case 57:
/* Line 1792 of yacc.c  */
#line 240 "hcc.y"
    {(yyval.ast)=base_of(create_structorunion((yyvsp[(1) - (2)].ast),(yyvsp[(2) - (2)].ast),NULL));}
    break;

  case 58:
/* Line 1792 of yacc.c  */
#line 242 "hcc.y"
    {(yyval.ast)=base_of(create_structorunion((yyvsp[(1) - (5)].ast),(yyvsp[(2) - (5)].ast),(yyvsp[(4) - (5)].ast)));}
    break;

  case 59:
/* Line 1792 of yacc.c  */
#line 244 "hcc.y"
    {(yyval.ast)=base_of(create_structorunion((yyvsp[(1) - (4)].ast),NULL,(yyvsp[(3) - (4)].ast)));}
    break;

  case 60:
/* Line 1792 of yacc.c  */
#line 247 "hcc.y"
    {(yyval.ast)=base_of(create_atom(STRUCT,tval,tcoord));}
    break;

  case 61:
/* Line 1792 of yacc.c  */
#line 248 "hcc.y"
    {(yyval.ast)=base_of(create_atom(UNION,tval,tcoord));}
    break;

  case 62:
/* Line 1792 of yacc.c  */
#line 252 "hcc.y"
    {(yyval.ast)=(yyvsp[(1) - (1)].ast);}
    break;

  case 63:
/* Line 1792 of yacc.c  */
#line 254 "hcc.y"
    {(yyval.ast)=append_astnode((yyvsp[(1) - (2)].ast),(yyvsp[(2) - (2)].ast));}
    break;

  case 64:
/* Line 1792 of yacc.c  */
#line 258 "hcc.y"
    {(yyval.ast)=base_of(create_structdeclaration((yyvsp[(1) - (3)].ast),(yyvsp[(2) - (3)].ast)));}
    break;

  case 65:
/* Line 1792 of yacc.c  */
#line 262 "hcc.y"
    {(yyval.ast) = base_of(create_declarationspecifier3((yyvsp[(1) - (1)].ast)));}
    break;

  case 66:
/* Line 1792 of yacc.c  */
#line 264 "hcc.y"
    {(yyval.ast) = base_of(create_declarationspecifier4((yyvsp[(1) - (2)].ast),(yyvsp[(2) - (2)].ast)));}
    break;

  case 67:
/* Line 1792 of yacc.c  */
#line 266 "hcc.y"
    {(yyval.ast) = base_of(create_declarationspecifier5((yyvsp[(1) - (1)].ast)));}
    break;

  case 68:
/* Line 1792 of yacc.c  */
#line 268 "hcc.y"
    {(yyval.ast) = base_of(create_declarationspecifier6((yyvsp[(1) - (2)].ast),(yyvsp[(2) - (2)].ast)));}
    break;

  case 69:
/* Line 1792 of yacc.c  */
#line 271 "hcc.y"
    {(yyval.ast)=(yyvsp[(1) - (1)].ast);}
    break;

  case 70:
/* Line 1792 of yacc.c  */
#line 272 "hcc.y"
    {(yyval.ast)=append_astnode((yyvsp[(1) - (3)].ast),(yyvsp[(3) - (3)].ast));}
    break;

  case 71:
/* Line 1792 of yacc.c  */
#line 276 "hcc.y"
    {(yyval.ast)=base_of(create_structdeclarator((yyvsp[(1) - (1)].ast),NULL));}
    break;

  case 72:
/* Line 1792 of yacc.c  */
#line 278 "hcc.y"
    {(yyval.ast)=base_of(create_structdeclarator(NULL,(yyvsp[(2) - (2)].ast)));}
    break;

  case 73:
/* Line 1792 of yacc.c  */
#line 280 "hcc.y"
    {(yyval.ast)=base_of(create_structdeclarator((yyvsp[(1) - (3)].ast),(yyvsp[(3) - (3)].ast)));}
    break;

  case 74:
/* Line 1792 of yacc.c  */
#line 284 "hcc.y"
    {(yyval.ast)=base_of(chain_pointerdeclarator((yyvsp[(1) - (2)].ast),(yyvsp[(2) - (2)].ast)));}
    break;

  case 75:
/* Line 1792 of yacc.c  */
#line 286 "hcc.y"
    {(yyval.ast)=(yyvsp[(1) - (1)].ast);}
    break;

  case 76:
/* Line 1792 of yacc.c  */
#line 290 "hcc.y"
    { (yyval.ast) = base_of(create_pointerdeclarator((yyvsp[(1) - (1)].ast)->coord,NULL,NULL));}
    break;

  case 77:
/* Line 1792 of yacc.c  */
#line 292 "hcc.y"
    { (yyval.ast) = base_of(create_pointerdeclarator((yyvsp[(1) - (2)].ast)->coord,(yyvsp[(2) - (2)].ast),NULL));}
    break;

  case 78:
/* Line 1792 of yacc.c  */
#line 294 "hcc.y"
    { (yyval.ast) = base_of(create_pointerdeclarator((yyvsp[(1) - (2)].ast)->coord,NULL,(yyvsp[(2) - (2)].ast)));}
    break;

  case 79:
/* Line 1792 of yacc.c  */
#line 296 "hcc.y"
    { (yyval.ast) = base_of(create_pointerdeclarator((yyvsp[(1) - (3)].ast)->coord,(yyvsp[(2) - (3)].ast),(yyvsp[(3) - (3)].ast)));}
    break;

  case 80:
/* Line 1792 of yacc.c  */
#line 299 "hcc.y"
    {(yyval.ast)=base_of(create_atom('*',tval,tcoord));}
    break;

  case 81:
/* Line 1792 of yacc.c  */
#line 302 "hcc.y"
    {(yyval.ast)=(yyvsp[(1) - (1)].ast);}
    break;

  case 82:
/* Line 1792 of yacc.c  */
#line 303 "hcc.y"
    {(yyval.ast)=append_astnode((yyvsp[(1) - (2)].ast),(yyvsp[(2) - (2)].ast));}
    break;

  case 83:
/* Line 1792 of yacc.c  */
#line 307 "hcc.y"
    {(yyval.ast)=base_of(create_directdeclarator((yyvsp[(1) - (1)].ast)));}
    break;

  case 84:
/* Line 1792 of yacc.c  */
#line 309 "hcc.y"
    {(yyval.ast)=(yyvsp[(2) - (3)].ast); (yyval.ast)->has_paren = 1;}
    break;

  case 85:
/* Line 1792 of yacc.c  */
#line 311 "hcc.y"
    {(yyval.ast)=base_of(create_arraydeclarator((yyvsp[(1) - (4)].ast),(yyvsp[(3) - (4)].ast)));}
    break;

  case 86:
/* Line 1792 of yacc.c  */
#line 313 "hcc.y"
    {(yyval.ast)=base_of(create_arraydeclarator((yyvsp[(1) - (3)].ast),NULL));}
    break;

  case 87:
/* Line 1792 of yacc.c  */
#line 315 "hcc.y"
    {(yyval.ast)=base_of(create_funcdeclarator((yyvsp[(1) - (4)].ast),(yyvsp[(3) - (4)].ast),NULL));}
    break;

  case 88:
/* Line 1792 of yacc.c  */
#line 317 "hcc.y"
    {(yyval.ast)=base_of(create_funcdeclarator((yyvsp[(1) - (4)].ast),NULL,(yyvsp[(3) - (4)].ast)));}
    break;

  case 89:
/* Line 1792 of yacc.c  */
#line 319 "hcc.y"
    {(yyval.ast)=base_of(create_funcdeclarator((yyvsp[(1) - (3)].ast),NULL,NULL));}
    break;

  case 90:
/* Line 1792 of yacc.c  */
#line 322 "hcc.y"
    {(yyval.ast)=(yyvsp[(1) - (1)].ast);}
    break;

  case 91:
/* Line 1792 of yacc.c  */
#line 323 "hcc.y"
    {(yyval.ast)=append_astnode((yyvsp[(1) - (3)].ast),(yyvsp[(3) - (3)].ast));}
    break;

  case 92:
/* Line 1792 of yacc.c  */
#line 326 "hcc.y"
    {(yyval.ast)=base_of(create_paramtypelist((yyvsp[(1) - (1)].ast),0));}
    break;

  case 93:
/* Line 1792 of yacc.c  */
#line 327 "hcc.y"
    {(yyval.ast)=base_of(create_paramtypelist((yyvsp[(1) - (3)].ast),1));}
    break;

  case 94:
/* Line 1792 of yacc.c  */
#line 330 "hcc.y"
    {(yyval.ast)=(yyvsp[(1) - (1)].ast);}
    break;

  case 95:
/* Line 1792 of yacc.c  */
#line 331 "hcc.y"
    {(yyval.ast)=append_astnode((yyvsp[(1) - (3)].ast),(yyvsp[(3) - (3)].ast));}
    break;

  case 96:
/* Line 1792 of yacc.c  */
#line 335 "hcc.y"
    {(yyval.ast)=base_of(create_paramdeclaration((yyvsp[(1) - (1)].ast),NULL));}
    break;

  case 97:
/* Line 1792 of yacc.c  */
#line 337 "hcc.y"
    {(yyval.ast)=base_of(create_paramdeclaration((yyvsp[(1) - (2)].ast),(yyvsp[(2) - (2)].ast)));}
    break;

  case 98:
/* Line 1792 of yacc.c  */
#line 339 "hcc.y"
    {(yyval.ast)=base_of(create_paramdeclaration((yyvsp[(1) - (2)].ast),(yyvsp[(2) - (2)].ast)));}
    break;

  case 99:
/* Line 1792 of yacc.c  */
#line 343 "hcc.y"
    {(yyval.ast)=(yyvsp[(1) - (1)].ast);}
    break;

  case 100:
/* Line 1792 of yacc.c  */
#line 345 "hcc.y"
    {(yyval.ast)=(yyvsp[(1) - (1)].ast);}
    break;

  case 101:
/* Line 1792 of yacc.c  */
#line 347 "hcc.y"
    {(yyval.ast)=base_of(chain_pointerdeclarator((yyvsp[(1) - (2)].ast),(yyvsp[(2) - (2)].ast)));}
    break;

  case 102:
/* Line 1792 of yacc.c  */
#line 351 "hcc.y"
    {(yyval.ast)=(yyvsp[(2) - (3)].ast); (yyval.ast)->has_paren = 1;}
    break;

  case 103:
/* Line 1792 of yacc.c  */
#line 353 "hcc.y"
    {(yyval.ast)=base_of(create_arraydeclarator(base_of(create_abstractdeclarator((yyvsp[(1) - (2)].ast)->coord)),NULL));}
    break;

  case 104:
/* Line 1792 of yacc.c  */
#line 355 "hcc.y"
    {(yyval.ast)=base_of(create_arraydeclarator(base_of(create_abstractdeclarator((yyvsp[(1) - (3)].ast)->coord)),(yyvsp[(2) - (3)].ast)));}
    break;

  case 105:
/* Line 1792 of yacc.c  */
#line 357 "hcc.y"
    {(yyval.ast)=base_of(create_arraydeclarator((yyvsp[(1) - (3)].ast),NULL));}
    break;

  case 106:
/* Line 1792 of yacc.c  */
#line 359 "hcc.y"
    {(yyval.ast)=base_of(create_arraydeclarator((yyvsp[(1) - (4)].ast),(yyvsp[(3) - (4)].ast)));}
    break;

  case 107:
/* Line 1792 of yacc.c  */
#line 361 "hcc.y"
    {(yyval.ast)=base_of(create_funcdeclarator(base_of(create_abstractdeclarator((yyvsp[(1) - (2)].ast)->coord)),NULL,NULL));}
    break;

  case 108:
/* Line 1792 of yacc.c  */
#line 363 "hcc.y"
    {(yyval.ast)=base_of(create_funcdeclarator(base_of(create_abstractdeclarator((yyvsp[(1) - (3)].ast)->coord)),(yyvsp[(2) - (3)].ast),NULL));}
    break;

  case 109:
/* Line 1792 of yacc.c  */
#line 365 "hcc.y"
    {(yyval.ast)=base_of(create_funcdeclarator((yyvsp[(1) - (3)].ast),NULL,NULL));}
    break;

  case 110:
/* Line 1792 of yacc.c  */
#line 367 "hcc.y"
    {(yyval.ast)=base_of(create_funcdeclarator((yyvsp[(1) - (4)].ast),(yyvsp[(3) - (4)].ast),NULL));}
    break;

  case 111:
/* Line 1792 of yacc.c  */
#line 370 "hcc.y"
    {(yyval.ast)=base_of(create_atom('[',tval,tcoord));}
    break;

  case 112:
/* Line 1792 of yacc.c  */
#line 373 "hcc.y"
    {(yyval.ast)=base_of(create_atom('(',tval,tcoord));}
    break;

  case 113:
/* Line 1792 of yacc.c  */
#line 377 "hcc.y"
    {(yyval.ast)=base_of(create_initdeclarator((yyvsp[(1) - (1)].ast),NULL));}
    break;

  case 114:
/* Line 1792 of yacc.c  */
#line 379 "hcc.y"
    {(yyval.ast)=base_of(create_initdeclarator((yyvsp[(1) - (3)].ast),(yyvsp[(3) - (3)].ast)));}
    break;

  case 115:
/* Line 1792 of yacc.c  */
#line 383 "hcc.y"
    {(yyval.ast)=base_of(create_initializer(0,(yyvsp[(1) - (1)].ast)));}
    break;

  case 116:
/* Line 1792 of yacc.c  */
#line 385 "hcc.y"
    {(yyval.ast)=base_of(create_initializer(1,(yyvsp[(2) - (3)].ast)));}
    break;

  case 117:
/* Line 1792 of yacc.c  */
#line 387 "hcc.y"
    {(yyval.ast)=base_of(create_initializer(1,(yyvsp[(2) - (4)].ast)));}
    break;

  case 118:
/* Line 1792 of yacc.c  */
#line 391 "hcc.y"
    {(yyval.ast)=(yyvsp[(1) - (1)].ast);}
    break;

  case 119:
/* Line 1792 of yacc.c  */
#line 393 "hcc.y"
    {(yyval.ast)=append_astnode((yyvsp[(1) - (3)].ast),(yyvsp[(3) - (3)].ast));}
    break;

  case 120:
/* Line 1792 of yacc.c  */
#line 397 "hcc.y"
    {(yyval.ast)=(yyvsp[(1) - (1)].ast);}
    break;

  case 121:
/* Line 1792 of yacc.c  */
#line 399 "hcc.y"
    {(yyval.ast)=base_of(create_binaryexpression(',',(yyvsp[(1) - (3)].ast),(yyvsp[(3) - (3)].ast)));}
    break;

  case 122:
/* Line 1792 of yacc.c  */
#line 403 "hcc.y"
    {(yyval.ast)=(yyvsp[(1) - (1)].ast);}
    break;

  case 123:
/* Line 1792 of yacc.c  */
#line 405 "hcc.y"
    {(yyval.ast)=base_of(create_binaryexpression1((yyvsp[(2) - (3)].ast),(yyvsp[(1) - (3)].ast),(yyvsp[(3) - (3)].ast)));}
    break;

  case 124:
/* Line 1792 of yacc.c  */
#line 408 "hcc.y"
    {(yyval.ast)=base_of(create_atom('=',tval,tcoord));}
    break;

  case 125:
/* Line 1792 of yacc.c  */
#line 409 "hcc.y"
    {(yyval.ast)=base_of(create_atom(MUL_ASSIGN,tval,tcoord));}
    break;

  case 126:
/* Line 1792 of yacc.c  */
#line 410 "hcc.y"
    {(yyval.ast)=base_of(create_atom(DIV_ASSIGN,tval,tcoord));}
    break;

  case 127:
/* Line 1792 of yacc.c  */
#line 411 "hcc.y"
    {(yyval.ast)=base_of(create_atom(MOD_ASSIGN,tval,tcoord));}
    break;

  case 128:
/* Line 1792 of yacc.c  */
#line 412 "hcc.y"
    {(yyval.ast)=base_of(create_atom(ADD_ASSIGN,tval,tcoord));}
    break;

  case 129:
/* Line 1792 of yacc.c  */
#line 413 "hcc.y"
    {(yyval.ast)=base_of(create_atom(SUB_ASSIGN,tval,tcoord));}
    break;

  case 130:
/* Line 1792 of yacc.c  */
#line 414 "hcc.y"
    {(yyval.ast)=base_of(create_atom(LEFT_ASSIGN,tval,tcoord));}
    break;

  case 131:
/* Line 1792 of yacc.c  */
#line 415 "hcc.y"
    {(yyval.ast)=base_of(create_atom(RIGHT_ASSIGN,tval,tcoord));}
    break;

  case 132:
/* Line 1792 of yacc.c  */
#line 416 "hcc.y"
    {(yyval.ast)=base_of(create_atom(AND_ASSIGN,tval,tcoord));}
    break;

  case 133:
/* Line 1792 of yacc.c  */
#line 417 "hcc.y"
    {(yyval.ast)=base_of(create_atom(XOR_ASSIGN,tval,tcoord));}
    break;

  case 134:
/* Line 1792 of yacc.c  */
#line 418 "hcc.y"
    {(yyval.ast)=base_of(create_atom(OR_ASSIGN,tval,tcoord));}
    break;

  case 135:
/* Line 1792 of yacc.c  */
#line 422 "hcc.y"
    {(yyval.ast)=(yyvsp[(1) - (1)].ast);}
    break;

  case 136:
/* Line 1792 of yacc.c  */
#line 424 "hcc.y"
    {(yyval.ast)=base_of(create_unaryexpression((yyvsp[(1) - (2)].ast),(yyvsp[(2) - (2)].ast)));}
    break;

  case 137:
/* Line 1792 of yacc.c  */
#line 426 "hcc.y"
    {(yyval.ast)=base_of(create_unaryexpression((yyvsp[(1) - (2)].ast),(yyvsp[(2) - (2)].ast)));}
    break;

  case 138:
/* Line 1792 of yacc.c  */
#line 428 "hcc.y"
    {(yyval.ast)=base_of(create_unaryexpression((yyvsp[(1) - (2)].ast),(yyvsp[(2) - (2)].ast)));}
    break;

  case 139:
/* Line 1792 of yacc.c  */
#line 430 "hcc.y"
    {(yyval.ast)=base_of(create_unaryexpression1((yyvsp[(1) - (4)].ast),(yyvsp[(3) - (4)].ast)));}
    break;

  case 140:
/* Line 1792 of yacc.c  */
#line 433 "hcc.y"
    {(yyval.ast)=base_of(create_atom(INC_OP,tval,tcoord));}
    break;

  case 141:
/* Line 1792 of yacc.c  */
#line 434 "hcc.y"
    {(yyval.ast)=base_of(create_atom(DEC_OP,tval,tcoord));}
    break;

  case 142:
/* Line 1792 of yacc.c  */
#line 437 "hcc.y"
    {(yyval.ast)=base_of(create_atom(SIZEOF,tval,tcoord));}
    break;

  case 143:
/* Line 1792 of yacc.c  */
#line 440 "hcc.y"
    {(yyval.ast)=base_of(create_atom('&',tval,tcoord));}
    break;

  case 144:
/* Line 1792 of yacc.c  */
#line 441 "hcc.y"
    {(yyval.ast)=base_of(create_atom('+',tval,tcoord));}
    break;

  case 145:
/* Line 1792 of yacc.c  */
#line 442 "hcc.y"
    {(yyval.ast)=base_of(create_atom('-',tval,tcoord));}
    break;

  case 146:
/* Line 1792 of yacc.c  */
#line 443 "hcc.y"
    {(yyval.ast)=base_of(create_atom('~',tval,tcoord));}
    break;

  case 147:
/* Line 1792 of yacc.c  */
#line 444 "hcc.y"
    {(yyval.ast)=base_of(create_atom('!',tval,tcoord));}
    break;

  case 148:
/* Line 1792 of yacc.c  */
#line 445 "hcc.y"
    {(yyval.ast)=(yyvsp[(1) - (1)].ast);}
    break;

  case 149:
/* Line 1792 of yacc.c  */
#line 449 "hcc.y"
    {(yyval.ast)=base_of(create_typename((yyvsp[(1) - (1)].ast),NULL));}
    break;

  case 150:
/* Line 1792 of yacc.c  */
#line 451 "hcc.y"
    {(yyval.ast)=base_of(create_typename((yyvsp[(1) - (2)].ast),(yyvsp[(2) - (2)].ast)));}
    break;

  case 151:
/* Line 1792 of yacc.c  */
#line 455 "hcc.y"
    {(yyval.ast)=(yyvsp[(1) - (1)].ast);}
    break;

  case 152:
/* Line 1792 of yacc.c  */
#line 457 "hcc.y"
    {(yyval.ast)=base_of(create_castexpression(CAST_OP,(yyvsp[(2) - (4)].ast),(yyvsp[(4) - (4)].ast)));}
    break;

  case 153:
/* Line 1792 of yacc.c  */
#line 461 "hcc.y"
    {(yyval.ast)=(yyvsp[(1) - (1)].ast);}
    break;

  case 154:
/* Line 1792 of yacc.c  */
#line 463 "hcc.y"
    {(yyval.ast)=base_of(create_postfixexpression(INDEX_OP,(yyvsp[(1) - (4)].ast),(yyvsp[(3) - (4)].ast)));}
    break;

  case 155:
/* Line 1792 of yacc.c  */
#line 465 "hcc.y"
    {(yyval.ast)=base_of(create_postfixexpression(CALL_OP,(yyvsp[(1) - (3)].ast),NULL));}
    break;

  case 156:
/* Line 1792 of yacc.c  */
#line 467 "hcc.y"
    {(yyval.ast)=base_of(create_postfixexpression(CALL_OP,(yyvsp[(1) - (4)].ast),(yyvsp[(3) - (4)].ast)));}
    break;

  case 157:
/* Line 1792 of yacc.c  */
#line 469 "hcc.y"
    {(yyval.ast)=base_of(create_postfixexpression(MEMBER_OP,(yyvsp[(1) - (3)].ast),(yyvsp[(3) - (3)].ast)));}
    break;

  case 158:
/* Line 1792 of yacc.c  */
#line 471 "hcc.y"
    {(yyval.ast)=base_of(create_postfixexpression(PTR_OP,(yyvsp[(1) - (3)].ast),(yyvsp[(3) - (3)].ast)));}
    break;

  case 159:
/* Line 1792 of yacc.c  */
#line 473 "hcc.y"
    {(yyval.ast)=base_of(create_postfixexpression(POST_INC_DEC_OP,(yyvsp[(1) - (2)].ast),(yyvsp[(2) - (2)].ast)));}
    break;

  case 160:
/* Line 1792 of yacc.c  */
#line 477 "hcc.y"
    {(yyval.ast)=(yyvsp[(1) - (1)].ast);}
    break;

  case 161:
/* Line 1792 of yacc.c  */
#line 479 "hcc.y"
    {(yyval.ast)=append_astnode((yyvsp[(1) - (3)].ast),(yyvsp[(3) - (3)].ast));}
    break;

  case 162:
/* Line 1792 of yacc.c  */
#line 483 "hcc.y"
    {(yyval.ast)=base_of(create_primaryexpression((yyvsp[(1) - (1)].ast)));}
    break;

  case 163:
/* Line 1792 of yacc.c  */
#line 485 "hcc.y"
    {(yyval.ast)=base_of(create_primaryexpression(base_of(create_atom(INTCONST,tval,tcoord))));}
    break;

  case 164:
/* Line 1792 of yacc.c  */
#line 487 "hcc.y"
    {(yyval.ast)=base_of(create_primaryexpression(base_of(create_atom(UINT,tval,tcoord))));}
    break;

  case 165:
/* Line 1792 of yacc.c  */
#line 489 "hcc.y"
    {(yyval.ast)=base_of(create_primaryexpression(base_of(create_atom(LINT,tval,tcoord))));}
    break;

  case 166:
/* Line 1792 of yacc.c  */
#line 491 "hcc.y"
    {(yyval.ast)=base_of(create_primaryexpression(base_of(create_atom(ULINT,tval,tcoord))));}
    break;

  case 167:
/* Line 1792 of yacc.c  */
#line 493 "hcc.y"
    {(yyval.ast)=base_of(create_primaryexpression(base_of(create_atom(LLINT,tval,tcoord))));}
    break;

  case 168:
/* Line 1792 of yacc.c  */
#line 495 "hcc.y"
    {(yyval.ast)=base_of(create_primaryexpression(base_of(create_atom(ULLINT,tval,tcoord))));}
    break;

  case 169:
/* Line 1792 of yacc.c  */
#line 497 "hcc.y"
    {(yyval.ast)=base_of(create_primaryexpression(base_of(create_atom(DOUBLECONST,tval,tcoord))));}
    break;

  case 170:
/* Line 1792 of yacc.c  */
#line 499 "hcc.y"
    {(yyval.ast)=base_of(create_primaryexpression(base_of(create_atom(LDOUBLECONST,tval,tcoord))));}
    break;

  case 171:
/* Line 1792 of yacc.c  */
#line 501 "hcc.y"
    {(yyval.ast)=base_of(create_primaryexpression(base_of(create_atom(FLOATCONST,tval,tcoord))));}
    break;

  case 172:
/* Line 1792 of yacc.c  */
#line 503 "hcc.y"
    {(yyval.ast)=base_of(create_primaryexpression(base_of(create_atom(STRING,tval,tcoord))));}
    break;

  case 173:
/* Line 1792 of yacc.c  */
#line 505 "hcc.y"
    {(yyval.ast)=(yyvsp[(2) - (3)].ast); (yyval.ast)->has_paren = 1;}
    break;

  case 174:
/* Line 1792 of yacc.c  */
#line 507 "hcc.y"
    {(yyval.ast)=(yyvsp[(2) - (3)].ast); (yyval.ast)->has_paren = 1;}
    break;

  case 175:
/* Line 1792 of yacc.c  */
#line 511 "hcc.y"
    {(yyval.ast)=(yyvsp[(1) - (1)].ast);}
    break;

  case 176:
/* Line 1792 of yacc.c  */
#line 513 "hcc.y"
    {(yyval.ast)=base_of(create_conditionalexpression(COND_OP,(yyvsp[(1) - (5)].ast),(yyvsp[(3) - (5)].ast),(yyvsp[(5) - (5)].ast)));}
    break;

  case 177:
/* Line 1792 of yacc.c  */
#line 517 "hcc.y"
    {(yyval.ast)=(yyvsp[(1) - (1)].ast);}
    break;

  case 178:
/* Line 1792 of yacc.c  */
#line 519 "hcc.y"
    {(yyval.ast)=base_of(create_binaryexpression(OR_OP,(yyvsp[(1) - (3)].ast),(yyvsp[(3) - (3)].ast)));}
    break;

  case 179:
/* Line 1792 of yacc.c  */
#line 523 "hcc.y"
    {(yyval.ast)=(yyvsp[(1) - (1)].ast);}
    break;

  case 180:
/* Line 1792 of yacc.c  */
#line 525 "hcc.y"
    {(yyval.ast)=base_of(create_binaryexpression(AND_OP,(yyvsp[(1) - (3)].ast),(yyvsp[(3) - (3)].ast)));}
    break;

  case 181:
/* Line 1792 of yacc.c  */
#line 529 "hcc.y"
    {(yyval.ast)=(yyvsp[(1) - (1)].ast);}
    break;

  case 182:
/* Line 1792 of yacc.c  */
#line 531 "hcc.y"
    {(yyval.ast)=base_of(create_binaryexpression('|',(yyvsp[(1) - (3)].ast),(yyvsp[(3) - (3)].ast)));}
    break;

  case 183:
/* Line 1792 of yacc.c  */
#line 535 "hcc.y"
    {(yyval.ast)=(yyvsp[(1) - (1)].ast);}
    break;

  case 184:
/* Line 1792 of yacc.c  */
#line 537 "hcc.y"
    {(yyval.ast)=base_of(create_binaryexpression('^',(yyvsp[(1) - (3)].ast),(yyvsp[(3) - (3)].ast)));}
    break;

  case 185:
/* Line 1792 of yacc.c  */
#line 541 "hcc.y"
    {(yyval.ast)=(yyvsp[(1) - (1)].ast);}
    break;

  case 186:
/* Line 1792 of yacc.c  */
#line 543 "hcc.y"
    {(yyval.ast)=base_of(create_binaryexpression('&',(yyvsp[(1) - (3)].ast),(yyvsp[(3) - (3)].ast)));}
    break;

  case 187:
/* Line 1792 of yacc.c  */
#line 547 "hcc.y"
    {(yyval.ast)=(yyvsp[(1) - (1)].ast);}
    break;

  case 188:
/* Line 1792 of yacc.c  */
#line 549 "hcc.y"
    {(yyval.ast)=base_of(create_binaryexpression(EQ_OP,(yyvsp[(1) - (3)].ast),(yyvsp[(3) - (3)].ast)));}
    break;

  case 189:
/* Line 1792 of yacc.c  */
#line 551 "hcc.y"
    {(yyval.ast)=base_of(create_binaryexpression(NE_OP,(yyvsp[(1) - (3)].ast),(yyvsp[(3) - (3)].ast)));}
    break;

  case 190:
/* Line 1792 of yacc.c  */
#line 555 "hcc.y"
    {(yyval.ast)=(yyvsp[(1) - (1)].ast);}
    break;

  case 191:
/* Line 1792 of yacc.c  */
#line 557 "hcc.y"
    {(yyval.ast)=base_of(create_binaryexpression('<',(yyvsp[(1) - (3)].ast),(yyvsp[(3) - (3)].ast)));}
    break;

  case 192:
/* Line 1792 of yacc.c  */
#line 559 "hcc.y"
    {(yyval.ast)=base_of(create_binaryexpression('>',(yyvsp[(1) - (3)].ast),(yyvsp[(3) - (3)].ast)));}
    break;

  case 193:
/* Line 1792 of yacc.c  */
#line 561 "hcc.y"
    {(yyval.ast)=base_of(create_binaryexpression(LE_OP,(yyvsp[(1) - (3)].ast),(yyvsp[(3) - (3)].ast)));}
    break;

  case 194:
/* Line 1792 of yacc.c  */
#line 563 "hcc.y"
    {(yyval.ast)=base_of(create_binaryexpression(GE_OP,(yyvsp[(1) - (3)].ast),(yyvsp[(3) - (3)].ast)));}
    break;

  case 195:
/* Line 1792 of yacc.c  */
#line 567 "hcc.y"
    {(yyval.ast)=(yyvsp[(1) - (1)].ast);}
    break;

  case 196:
/* Line 1792 of yacc.c  */
#line 569 "hcc.y"
    {(yyval.ast)=base_of(create_binaryexpression(LEFT_SHIFT,(yyvsp[(1) - (3)].ast),(yyvsp[(3) - (3)].ast)));}
    break;

  case 197:
/* Line 1792 of yacc.c  */
#line 571 "hcc.y"
    {(yyval.ast)=base_of(create_binaryexpression(RIGHT_SHIFT,(yyvsp[(1) - (3)].ast),(yyvsp[(3) - (3)].ast)));}
    break;

  case 198:
/* Line 1792 of yacc.c  */
#line 575 "hcc.y"
    {(yyval.ast)=(yyvsp[(1) - (1)].ast);}
    break;

  case 199:
/* Line 1792 of yacc.c  */
#line 577 "hcc.y"
    {(yyval.ast)=base_of(create_binaryexpression('+',(yyvsp[(1) - (3)].ast),(yyvsp[(3) - (3)].ast)));}
    break;

  case 200:
/* Line 1792 of yacc.c  */
#line 579 "hcc.y"
    {(yyval.ast)=base_of(create_binaryexpression('-',(yyvsp[(1) - (3)].ast),(yyvsp[(3) - (3)].ast)));}
    break;

  case 201:
/* Line 1792 of yacc.c  */
#line 583 "hcc.y"
    {(yyval.ast)=(yyvsp[(1) - (1)].ast);}
    break;

  case 202:
/* Line 1792 of yacc.c  */
#line 585 "hcc.y"
    {(yyval.ast)=base_of(create_binaryexpression('*',(yyvsp[(1) - (3)].ast),(yyvsp[(3) - (3)].ast)));}
    break;

  case 203:
/* Line 1792 of yacc.c  */
#line 587 "hcc.y"
    {(yyval.ast)=base_of(create_binaryexpression('/',(yyvsp[(1) - (3)].ast),(yyvsp[(3) - (3)].ast)));}
    break;

  case 204:
/* Line 1792 of yacc.c  */
#line 589 "hcc.y"
    {(yyval.ast)=base_of(create_binaryexpression('%',(yyvsp[(1) - (3)].ast),(yyvsp[(3) - (3)].ast)));}
    break;

  case 205:
/* Line 1792 of yacc.c  */
#line 593 "hcc.y"
    {(yyval.ast)=base_of(create_compoundstmt((yyvsp[(1) - (2)].ast)->coord,NULL,NULL));}
    break;

  case 206:
/* Line 1792 of yacc.c  */
#line 595 "hcc.y"
    {(yyval.ast)=base_of(create_compoundstmt((yyvsp[(1) - (3)].ast)->coord,NULL,(yyvsp[(2) - (3)].ast)));}
    break;

  case 207:
/* Line 1792 of yacc.c  */
#line 597 "hcc.y"
    {(yyval.ast)=base_of(create_compoundstmt((yyvsp[(1) - (3)].ast)->coord,(yyvsp[(2) - (3)].ast),NULL));}
    break;

  case 208:
/* Line 1792 of yacc.c  */
#line 599 "hcc.y"
    {(yyval.ast)=base_of(create_compoundstmt((yyvsp[(1) - (4)].ast)->coord,(yyvsp[(2) - (4)].ast),(yyvsp[(3) - (4)].ast)));}
    break;

  case 209:
/* Line 1792 of yacc.c  */
#line 602 "hcc.y"
    {(yyval.ast)=base_of(create_atom('{', tval, tcoord));}
    break;

  case 210:
/* Line 1792 of yacc.c  */
#line 606 "hcc.y"
    {(yyval.ast)=(yyvsp[(1) - (1)].ast);}
    break;

  case 211:
/* Line 1792 of yacc.c  */
#line 608 "hcc.y"
    {(yyval.ast)=append_astnode((yyvsp[(1) - (2)].ast),(yyvsp[(2) - (2)].ast));}
    break;

  case 212:
/* Line 1792 of yacc.c  */
#line 612 "hcc.y"
    {(yyval.ast)=(yyvsp[(1) - (1)].ast);}
    break;

  case 213:
/* Line 1792 of yacc.c  */
#line 614 "hcc.y"
    {(yyval.ast)=(yyvsp[(1) - (1)].ast);}
    break;

  case 214:
/* Line 1792 of yacc.c  */
#line 616 "hcc.y"
    {(yyval.ast)=(yyvsp[(1) - (1)].ast);}
    break;

  case 215:
/* Line 1792 of yacc.c  */
#line 618 "hcc.y"
    {(yyval.ast)=(yyvsp[(1) - (1)].ast);}
    break;

  case 216:
/* Line 1792 of yacc.c  */
#line 620 "hcc.y"
    {(yyval.ast)=(yyvsp[(1) - (1)].ast);}
    break;

  case 217:
/* Line 1792 of yacc.c  */
#line 622 "hcc.y"
    {(yyval.ast)=(yyvsp[(1) - (1)].ast);}
    break;

  case 218:
/* Line 1792 of yacc.c  */
#line 626 "hcc.y"
    {(yyval.ast)=base_of(create_labelstmt(IDLABEL,(yyvsp[(1) - (3)].ast)->coord,(yyvsp[(1) - (3)].ast),(yyvsp[(3) - (3)].ast)));}
    break;

  case 219:
/* Line 1792 of yacc.c  */
#line 628 "hcc.y"
    {(yyval.ast)=base_of(create_labelstmt(CASELABEL,(yyvsp[(1) - (4)].ast)->coord,(yyvsp[(2) - (4)].ast),(yyvsp[(4) - (4)].ast)));}
    break;

  case 220:
/* Line 1792 of yacc.c  */
#line 630 "hcc.y"
    {(yyval.ast)=base_of(create_labelstmt(DEFAULTLABEL,(yyvsp[(1) - (3)].ast)->coord,NULL,(yyvsp[(3) - (3)].ast)));}
    break;

  case 221:
/* Line 1792 of yacc.c  */
#line 634 "hcc.y"
    {(yyval.ast)=base_of(create_atom(DEFAULT,tval,tcoord));}
    break;

  case 222:
/* Line 1792 of yacc.c  */
#line 638 "hcc.y"
    {(yyval.ast)=base_of(create_atom(CASE,tval,tcoord));}
    break;

  case 223:
/* Line 1792 of yacc.c  */
#line 642 "hcc.y"
    {(yyval.ast)=base_of(create_exprstmt((yyvsp[(1) - (1)].ast)->coord,NULL));}
    break;

  case 224:
/* Line 1792 of yacc.c  */
#line 644 "hcc.y"
    {(yyval.ast)=base_of(create_exprstmt((yyvsp[(1) - (2)].ast)->coord,(yyvsp[(1) - (2)].ast)));}
    break;

  case 225:
/* Line 1792 of yacc.c  */
#line 647 "hcc.y"
    {(yyval.ast)=base_of(create_atom(';',tval,tcoord));}
    break;

  case 226:
/* Line 1792 of yacc.c  */
#line 650 "hcc.y"
    {(yyval.ast)=base_of(create_atom(IF,tval,tcoord));}
    break;

  case 227:
/* Line 1792 of yacc.c  */
#line 652 "hcc.y"
    {(yyval.ast)=base_of(create_atom(ELSE,tval,tcoord));}
    break;

  case 228:
/* Line 1792 of yacc.c  */
#line 654 "hcc.y"
    {(yyval.ast)=base_of(create_atom(SWITCH,tval,tcoord));}
    break;

  case 229:
/* Line 1792 of yacc.c  */
#line 658 "hcc.y"
    {(yyval.ast)=base_of(create_selstmt(IFSTMT,(yyvsp[(1) - (5)].ast)->coord,(yyvsp[(3) - (5)].ast),(yyvsp[(5) - (5)].ast),NULL));}
    break;

  case 230:
/* Line 1792 of yacc.c  */
#line 660 "hcc.y"
    {(yyval.ast)=base_of(create_selstmt(IFELSESTMT,(yyvsp[(1) - (7)].ast)->coord,(yyvsp[(3) - (7)].ast),(yyvsp[(5) - (7)].ast),(yyvsp[(7) - (7)].ast)));}
    break;

  case 231:
/* Line 1792 of yacc.c  */
#line 662 "hcc.y"
    {(yyval.ast)=base_of(create_selstmt(SWITCHSTMT,(yyvsp[(1) - (5)].ast)->coord,(yyvsp[(3) - (5)].ast),(yyvsp[(5) - (5)].ast),NULL));}
    break;

  case 232:
/* Line 1792 of yacc.c  */
#line 666 "hcc.y"
    {(yyval.ast)=base_of(create_iterationstmt(WHILESTMT,(yyvsp[(1) - (5)].ast)->coord,(yyvsp[(3) - (5)].ast),(yyvsp[(5) - (5)].ast),NULL,NULL));}
    break;

  case 233:
/* Line 1792 of yacc.c  */
#line 668 "hcc.y"
    {(yyval.ast)=base_of(create_iterationstmt(DOSTMT,(yyvsp[(1) - (7)].ast)->coord,(yyvsp[(5) - (7)].ast),(yyvsp[(2) - (7)].ast),NULL,NULL));}
    break;

  case 234:
/* Line 1792 of yacc.c  */
#line 670 "hcc.y"
    {(yyval.ast)=base_of(create_iterationstmt(FORSTMT,(yyvsp[(1) - (6)].ast)->coord,NULL,(yyvsp[(6) - (6)].ast),(yyvsp[(3) - (6)].ast),(yyvsp[(4) - (6)].ast)));}
    break;

  case 235:
/* Line 1792 of yacc.c  */
#line 672 "hcc.y"
    {(yyval.ast)=base_of(create_iterationstmt(FORSTMT,(yyvsp[(1) - (7)].ast)->coord,(yyvsp[(5) - (7)].ast),(yyvsp[(7) - (7)].ast),(yyvsp[(3) - (7)].ast),(yyvsp[(4) - (7)].ast)));}
    break;

  case 236:
/* Line 1792 of yacc.c  */
#line 675 "hcc.y"
    {(yyval.ast)=base_of(create_atom(WHILE,tval,tcoord));}
    break;

  case 237:
/* Line 1792 of yacc.c  */
#line 678 "hcc.y"
    {(yyval.ast)=base_of(create_atom(DO,tval,tcoord));}
    break;

  case 238:
/* Line 1792 of yacc.c  */
#line 681 "hcc.y"
    {(yyval.ast)=base_of(create_atom(FOR,tval,tcoord));}
    break;

  case 239:
/* Line 1792 of yacc.c  */
#line 684 "hcc.y"
    {(yyval.ast)=base_of(create_atom(GOTO,tval,tcoord));}
    break;

  case 240:
/* Line 1792 of yacc.c  */
#line 687 "hcc.y"
    {(yyval.ast)=base_of(create_atom(CONTINUE,tval,tcoord));}
    break;

  case 241:
/* Line 1792 of yacc.c  */
#line 690 "hcc.y"
    {(yyval.ast)=base_of(create_atom(BREAK,tval,tcoord));}
    break;

  case 242:
/* Line 1792 of yacc.c  */
#line 693 "hcc.y"
    {(yyval.ast)=base_of(create_atom(RETURN,tval,tcoord));}
    break;

  case 243:
/* Line 1792 of yacc.c  */
#line 697 "hcc.y"
    {(yyval.ast)=base_of(create_jumpstmt(GOTOSTMT,(yyvsp[(1) - (3)].ast)->coord,(yyvsp[(2) - (3)].ast)));}
    break;

  case 244:
/* Line 1792 of yacc.c  */
#line 699 "hcc.y"
    {(yyval.ast)=base_of(create_jumpstmt(CONTINUESTMT,(yyvsp[(1) - (2)].ast)->coord,NULL));}
    break;

  case 245:
/* Line 1792 of yacc.c  */
#line 701 "hcc.y"
    {(yyval.ast)=base_of(create_jumpstmt(BREAKSTMT,(yyvsp[(1) - (2)].ast)->coord,NULL));}
    break;

  case 246:
/* Line 1792 of yacc.c  */
#line 703 "hcc.y"
    {(yyval.ast)=base_of(create_jumpstmt(RETURNSTMT,(yyvsp[(1) - (2)].ast)->coord,NULL));}
    break;

  case 247:
/* Line 1792 of yacc.c  */
#line 705 "hcc.y"
    {(yyval.ast)=base_of(create_jumpstmt(RETURNSTMT,(yyvsp[(1) - (3)].ast)->coord,(yyvsp[(2) - (3)].ast)));}
    break;


/* Line 1792 of yacc.c  */
#line 3713 "parser.c"
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
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
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
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

  /* Else will try to reuse lookahead token after shifting the error
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
      if (!yypact_value_is_default (yyn))
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

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


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

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
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
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


/* Line 2055 of yacc.c  */
#line 708 "hcc.y"


static void yyerror(char *s)
{
  fatal(&tcoord,"syntax error while building abstract syntax tree");
}
