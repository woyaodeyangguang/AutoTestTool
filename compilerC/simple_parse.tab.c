/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.

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
#define YYBISON_VERSION "3.0.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "simple_parse.y" /* yacc.c:339  */

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

#line 87 "simple_parse.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif


/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
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
    IFX = 332
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 22 "simple_parse.y" /* yacc.c:355  */

  ASTBase *ast;

#line 206 "simple_parse.tab.c" /* yacc.c:355  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);



/* Copy the second part of user declarations.  */
#line 70 "simple_parse.y" /* yacc.c:358  */

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

#line 243 "simple_parse.tab.c" /* yacc.c:358  */

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
#else
typedef signed char yytype_int8;
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
# elif ! defined YYSIZE_T
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

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
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
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
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
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
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
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

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
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  44
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1598

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  102
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  88
/* YYNRULES -- Number of rules.  */
#define YYNRULES  244
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  380

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   332

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    91,     2,     2,     2,    99,    87,     2,
      86,    83,    82,    88,    78,    89,    92,    98,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    81,   101,
      96,    80,    97,    93,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    85,     2,    84,    95,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   100,    94,    79,    90,     2,     2,     2,
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
      75,    76,    77
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   127,   127,   130,   131,   134,   135,   138,   140,   144,
     148,   149,   152,   154,   156,   160,   161,   164,   165,   168,
     170,   172,   174,   176,   178,   182,   183,   184,   185,   186,
     189,   190,   193,   194,   195,   196,   197,   198,   199,   200,
     201,   202,   203,   204,   207,   209,   211,   213,   215,   219,
     222,   225,   226,   229,   230,   233,   236,   238,   240,   244,
     245,   248,   250,   254,   258,   260,   262,   264,   268,   269,
     272,   274,   276,   280,   284,   286,   288,   290,   294,   298,
     299,   302,   304,   306,   308,   310,   312,   314,   318,   319,
     322,   323,   326,   327,   330,   332,   334,   338,   340,   342,
     346,   348,   350,   352,   354,   356,   358,   360,   362,   366,
     369,   372,   374,   378,   380,   382,   386,   388,   392,   394,
     398,   400,   404,   405,   406,   407,   408,   409,   410,   411,
     412,   413,   414,   417,   419,   421,   423,   425,   429,   430,
     433,   436,   437,   438,   439,   440,   441,   444,   446,   450,
     452,   456,   458,   460,   462,   464,   466,   468,   472,   474,
     478,   480,   482,   484,   486,   488,   490,   492,   494,   496,
     498,   500,   504,   506,   510,   512,   516,   518,   522,   524,
     528,   530,   534,   536,   540,   542,   544,   548,   550,   552,
     554,   556,   560,   562,   564,   568,   570,   572,   576,   578,
     580,   582,   586,   588,   590,   592,   596,   599,   601,   605,
     607,   609,   611,   613,   615,   619,   621,   623,   627,   631,
     635,   637,   641,   644,   646,   648,   651,   653,   655,   659,
     661,   663,   665,   669,   672,   675,   678,   681,   684,   687,
     690,   692,   694,   696,   698
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
  "CALL_OP", "MEMBER_OP", "POST_INC_DEC_OP", "COND_OP", "IFX", "','",
  "'}'", "'='", "':'", "'*'", "')'", "']'", "'['", "'('", "'&'", "'+'",
  "'-'", "'~'", "'!'", "'.'", "'?'", "'|'", "'^'", "'<'", "'>'", "'/'",
  "'%'", "'{'", "';'", "$accept", "translation_unit", "extdecls",
  "extdecl", "declaration", "notype_declaration", "data_declaration",
  "function_declaration", "declaration_list", "init_declarator_list",
  "declaration_specifiers", "storage_class_specifier", "type_qualifier",
  "type_specifier", "enum_specifier", "enum_keyword", "identifier",
  "enumerator_list", "enumerator", "constant_expression",
  "struct_or_union_specifier", "struct_or_union",
  "struct_declaration_list", "struct_declaration",
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
  "jump_statement", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,    44,   125,
      61,    58,    42,    41,    93,    91,    40,    38,    43,    45,
     126,    33,    46,    63,   124,    94,    60,    62,    47,    37,
     123,    59
};
# endif

#define YYPACT_NINF -247

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-247)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    1022,  -247,  -247,  -247,  -247,  -247,  -247,  -247,  -247,  -247,
    -247,  -247,  -247,  -247,  -247,  -247,  -247,  -247,  -247,  -247,
    -247,  -247,  -247,    20,  1022,  -247,  -247,  -247,  -247,  -247,
     -46,    39,  1564,  1564,  1564,  -247,   -16,  -247,  -247,   -16,
     850,   -52,    21,  -247,  -247,  -247,    21,  -247,  -247,   -46,
      43,  -247,  -247,  -247,  -247,  -247,   -85,    13,   -85,   406,
    1211,  -247,   377,    39,  -247,   441,  -247,  1298,  1065,     3,
     -22,  -247,  -247,  -247,    13,   -18,    84,  -247,   406,   406,
     406,  1256,  -247,   -25,  -247,  -247,  -247,  -247,  -247,  -247,
    -247,  -247,  -247,  -247,  -247,  -247,  -247,  -247,  -247,  -247,
    -247,  -247,  -247,  -247,  -247,   895,  -247,  -247,   201,  1443,
    1443,  1443,  -247,   132,  -247,  -247,   -39,    30,    35,    37,
      64,   105,   135,   205,   183,   115,  1211,  -247,  -247,  -247,
    -247,  -247,  -247,  -247,  -247,  -247,  -247,  -247,  -247,  -247,
    -247,   540,    72,   -29,  -247,  -247,   628,  -247,  -247,    74,
    1443,  -247,  -247,    80,    80,  -247,  -247,    80,   804,    80,
      13,    63,    63,  1111,  -247,  -247,   103,  -247,  -247,  -247,
      99,  -247,     7,    95,   120,  -247,  -247,   214,  1443,   -15,
    -247,  1297,  -247,  -247,  -247,  -247,  1443,    15,  -247,   112,
     160,    66,   129,  -247,  -247,  -247,  -247,  -247,  -247,  -247,
    -247,  -247,  -247,  -247,  1443,  1443,  -247,   895,  -247,  -247,
      13,    13,  1443,  1309,  -247,  1443,  1443,  1443,  1443,  1443,
    1443,  1443,  1443,  1443,  1443,  1443,  1443,  1443,  1443,  1443,
    1443,  1443,  1443,  1443,  -247,   216,  -247,   716,   804,  1443,
    -247,  -247,  -247,   804,   166,  1443,  1443,  1443,   215,  1111,
      63,  -247,  -247,   -29,  -247,  -247,  -247,   -52,     9,  -247,
     -52,  1365,   941,    13,  -247,  -247,  1532,   -13,  -247,  -247,
    -247,  -247,  -247,  -247,   -25,  -247,  1443,  -247,   984,  -247,
    1443,  -247,   178,  -247,  -247,    33,  -247,  -247,    94,    30,
      40,    35,    37,    64,   105,   135,   135,   205,   205,   205,
     205,   183,   183,   115,   115,  -247,  -247,  -247,  1144,  -247,
    -247,  -247,  -247,  -247,   804,   123,   151,   157,    80,  1111,
    -247,  -247,   -52,  -247,  -247,     9,  1376,  1098,  -247,   185,
    -247,   190,   192,  -247,  -247,  -247,  -247,  -247,  -247,  -247,
    -247,  -247,  1443,  -247,  1443,  -247,  -247,  -247,   804,   804,
     804,  1443,  1432,  -247,  -247,  -247,   195,  -247,   199,  -247,
    -247,  -247,  -247,  -247,   275,  -247,  -247,   158,   804,   161,
    -247,  -247,  -247,   804,    63,  -247,   804,  -247,  -247,  -247
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    25,    33,    30,    40,    49,    28,    39,    35,    36,
      26,    34,    37,    27,    59,    29,    41,    60,    38,    32,
      31,    50,   110,     0,     2,     3,    10,    11,     6,     5,
       0,     0,    19,    23,    21,    42,     0,    81,    43,     0,
     111,    73,     0,    17,     1,     4,     0,   222,     9,     0,
     111,     8,    20,    24,    22,   206,    44,     0,    56,     0,
       0,    15,     0,     0,    14,     0,   109,     0,     0,     0,
     111,    18,     7,    12,     0,    53,     0,    51,     0,    66,
      64,     0,    61,     0,   140,   161,   162,   163,   164,   165,
     166,   167,   168,   169,   170,   138,   139,    78,   141,   142,
     143,   144,   145,   160,   146,     0,   112,   113,   149,     0,
       0,     0,   198,   133,   151,   120,   172,   174,   176,   178,
     180,   182,   184,   187,   192,   195,     0,    16,    13,   238,
     219,   237,   218,   234,   235,   236,   223,   239,   225,   233,
     202,     0,   160,     0,   118,   210,     0,   207,   209,     0,
       0,   211,   220,     0,     0,   212,   213,     0,     0,     0,
       0,     0,     0,     0,   214,    84,     0,   149,    55,    87,
      94,    88,     0,     0,    90,    92,    82,     0,     0,     0,
      45,     0,    67,    65,    58,    62,     0,     0,    68,    70,
     147,     0,     0,   129,   128,   127,   126,   123,   124,   125,
     130,   132,   131,   122,     0,     0,   134,     0,   136,   135,
       0,     0,     0,     0,   157,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   116,     0,   204,     0,     0,     0,
     221,   203,   208,     0,     0,     0,     0,     0,     0,     0,
       0,   241,   242,     0,   243,    83,    95,    97,    74,    96,
      98,     0,     0,     0,    86,    85,     0,     0,    47,    54,
      46,    52,    57,    71,     0,    63,     0,   148,     0,   171,
       0,   121,     0,   156,   155,     0,   153,   158,     0,   175,
       0,   177,   179,   181,   183,   185,   186,   190,   191,   188,
     189,   194,   193,   196,   197,   199,   200,   201,     0,   114,
     205,   215,   119,   217,     0,     0,     0,     0,     0,     0,
     240,   244,    99,    79,    76,    75,     0,     0,   101,     0,
     105,     0,     0,    89,    91,    93,    48,    69,    72,   150,
     137,   152,     0,   154,     0,   115,   117,   216,     0,     0,
       0,     0,     0,    80,    77,   103,     0,   107,     0,   102,
     106,   100,   159,   173,   226,   228,   229,     0,     0,     0,
     104,   108,   224,     0,     0,   231,     0,   227,   230,   232
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -247,  -247,  -247,   266,   -21,  -247,  -247,  -247,   237,   -23,
     337,  -247,    19,    23,  -247,  -247,     0,   238,  -162,  -105,
    -247,  -247,   254,   -67,     8,  -247,    59,     6,  -246,  -152,
    -247,  -247,  -247,   -63,  -247,    68,   -43,    79,   -37,    29,
     289,  -119,  -247,   -55,   -59,  -247,    98,   228,  -247,  -247,
     136,   -64,  -247,  -247,  -247,   -56,  -247,   127,   128,   134,
     137,   133,    87,    75,    78,    81,    69,   -30,   213,   -10,
    -247,  -247,  -247,  -239,   -28,  -247,  -247,  -247,  -247,  -247,
     107,  -247,  -247,  -247,  -247,  -247,  -247,  -247
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    23,    24,    25,    26,    27,    28,    29,    62,    30,
     170,    32,    33,    34,    35,    36,   103,    76,    77,   166,
      38,    39,    81,    82,    83,   187,   188,    40,   257,   104,
     325,    41,   172,   331,   174,   175,   332,   260,   261,   105,
      43,   106,   235,   143,   144,   204,   108,   109,   110,   111,
     192,   112,   113,   288,   114,   115,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   125,   145,    65,   146,   147,
     148,   149,   150,   151,   152,   153,   373,   154,   155,   156,
     157,   158,   159,   160,   161,   162,   163,   164
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint16 yytable[] =
{
      37,   107,    48,    51,    67,   173,    57,   234,    49,    59,
     319,   168,   324,    21,   185,    55,     3,   271,   258,    61,
      44,    72,    21,    21,    37,    21,    74,   215,    78,    42,
     126,    37,    46,    66,    22,    51,    56,    50,   258,    58,
      49,   127,    37,    20,    61,   244,    37,   209,    69,   239,
     191,    21,    70,    42,   216,    47,   186,    75,    60,    21,
      42,    22,   178,    37,   270,   142,   336,   107,   171,    70,
      68,    42,    47,   269,    75,    42,   212,    21,    79,   354,
     352,   273,    80,    37,    55,   263,   176,   182,   183,   189,
     264,    97,    42,   274,   168,   217,   126,    79,    79,    79,
      79,    80,    80,    80,    80,   271,   258,    22,   253,    64,
     258,   239,    42,   190,   185,   240,    47,   341,   239,    73,
     127,   344,   168,    60,    79,    22,   258,   259,    80,   218,
     168,   128,   219,   251,   252,   254,   242,    21,   205,   207,
      47,   142,   213,    55,   239,   281,   142,   277,   248,   279,
     191,   220,   191,   238,   287,   243,   329,   285,   142,   275,
     250,   290,   179,   180,    47,   167,    22,   305,   306,   307,
      37,   338,   342,   258,   221,   222,   256,   343,   265,    75,
     312,    97,   245,   246,    66,    22,   247,   255,   249,   346,
     315,   316,   317,   276,    95,    96,   210,   231,   266,   262,
      79,   239,   223,   224,    80,   168,   348,   206,   208,   167,
     283,   284,   280,   232,   233,   190,   339,    66,    22,   278,
     168,   356,   320,   326,   211,   321,    79,   242,   311,   239,
      80,   225,   226,   313,   349,   239,   239,   142,   142,   239,
     350,   374,    97,   142,   376,    66,    22,   314,   167,   107,
     139,   193,   194,   195,   196,   197,   198,   199,   200,   201,
     202,   340,    37,   333,   358,   227,   228,    75,    69,   359,
     168,   229,   230,   360,    37,   361,   167,   323,   126,   370,
     189,   203,   371,   362,   167,   326,   278,   372,   363,   327,
      45,   262,   267,   268,   308,   309,   367,   369,   297,   298,
     299,   300,   141,    42,   347,   301,   302,   278,   295,   296,
     303,   304,   177,   167,   142,   167,   167,   167,   167,   167,
     167,   167,   167,   167,   167,   167,   167,   167,   167,   167,
     167,   167,   181,   337,   335,    71,   322,    31,   364,   365,
     366,   214,   289,   282,   353,   291,   378,   351,   142,   142,
     142,   327,   292,   294,   237,   318,   293,     0,   375,   167,
       0,    31,     0,   377,     0,     0,   379,     0,   142,    52,
      53,    54,     0,   142,   167,     0,   142,    63,   167,     0,
       1,     0,     0,     2,     3,     0,     0,     0,     4,     0,
       5,     6,     7,     0,     0,     0,     8,     9,    10,    63,
      11,    12,    63,    13,    14,     0,    15,    16,    17,    18,
      19,    20,     2,     3,     0,     0,     0,     4,     0,     5,
       0,     7,     0,     0,   167,     8,     9,     0,     0,    11,
      12,     0,     0,    14,     0,     0,    16,    17,    18,    19,
      20,     0,   167,     0,     1,   129,   130,     2,     3,   131,
     132,   133,     4,     0,     5,     6,     7,   134,   135,   136,
       8,     9,    10,   137,    11,    12,    84,    13,    14,   138,
      15,    16,    17,    18,    19,    20,   139,    55,    63,    21,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    95,    96,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     140,     0,     0,    97,     0,     0,     0,    22,    98,    99,
     100,   101,   102,     0,     0,     0,     0,     0,     0,     0,
       0,    55,    47,     1,   129,   130,     2,     3,   131,   132,
     133,     4,     0,     5,     6,     7,   134,   135,   136,     8,
       9,    10,   137,    11,    12,    84,    13,    14,   138,    15,
      16,    17,    18,    19,    20,   139,     0,     0,    21,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    94,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    95,    96,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   236,
       0,     0,    97,     0,     0,     0,    22,    98,    99,   100,
     101,   102,   129,   130,     0,     0,   131,   132,   133,     0,
      55,    47,     0,     0,   134,   135,   136,     0,     0,     0,
     137,     0,     0,    84,     0,     0,   138,     0,     0,     0,
       0,     0,     0,   139,     0,     0,    21,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      95,    96,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   241,     0,     0,
      97,     0,     0,     0,    22,    98,    99,   100,   101,   102,
     129,   130,     0,     0,   131,   132,   133,     0,    55,    47,
       0,     0,   134,   135,   136,     0,     0,     0,   137,     0,
       0,    84,     0,     0,   138,     0,     0,     0,     0,     0,
       0,   139,     0,     0,    21,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    95,    96,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   310,     0,     0,    97,     0,
       0,     0,    22,    98,    99,   100,   101,   102,   129,   130,
       0,     0,   131,   132,   133,     0,    55,    47,     0,     0,
     134,   135,   136,     0,     0,     0,   137,     0,     0,    84,
       0,     0,   138,     0,     0,     0,     0,     0,     0,   139,
       0,     0,    21,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,     1,     0,     0,     2,     3,     0,     0,
       0,     4,     0,     5,     6,     7,    95,    96,     0,     8,
       9,    10,     0,    11,    12,     0,    13,    14,     0,    15,
      16,    17,    18,    19,    20,     0,    97,     0,     0,     0,
      22,    98,    99,   100,   101,   102,     0,     0,     0,     0,
       0,     2,     3,     0,    55,    47,     4,     0,     5,     0,
       7,     0,     0,     0,     8,     9,     0,     0,    11,    12,
      84,     0,    14,     0,     0,    16,    17,    18,    19,    20,
      60,     0,     0,    21,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    94,     1,     0,     0,     2,     3,     0,
      55,     0,     4,     0,     5,     6,     7,    95,    96,     0,
       8,     9,    10,     0,    11,    12,     0,    13,    14,     0,
      15,    16,    17,    18,    19,    20,     0,    97,     0,    21,
       0,    22,    98,    99,   100,   101,   102,     1,     0,     0,
       2,     3,     0,     0,     0,     4,     0,     5,     6,     7,
       0,     0,     0,     8,     9,    10,     0,    11,    12,     0,
      13,    14,     0,    15,    16,    17,    18,    19,    20,     0,
       0,     0,     0,    97,   330,     1,    66,    22,     2,     3,
       0,     0,     0,     4,     0,     5,     6,     7,     0,     0,
       0,     8,     9,    10,     0,    11,    12,     0,    13,    14,
       0,    15,    16,    17,    18,    19,    20,     0,     0,     0,
      21,     0,     0,     0,     0,     0,    97,   330,     1,    66,
      22,     2,     3,     0,     0,     0,     4,     0,     5,     6,
       7,     0,     0,     0,     8,     9,    10,     0,    11,    12,
       0,    13,    14,     0,    15,    16,    17,    18,    19,    20,
       0,     1,     0,    21,     2,     3,     0,     0,    22,     4,
       0,     5,     6,     7,     0,     0,     0,     8,     9,    10,
       0,    11,    12,     0,    13,    14,     0,    15,    16,    17,
      18,    19,    20,     0,     0,     0,    84,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   169,    21,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    84,
       0,     0,     0,    95,    96,     0,     0,     0,     0,     0,
       0,   357,    21,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    97,     0,     0,     0,    22,    98,    99,
     100,   101,   102,     0,     0,     0,    95,    96,     0,     0,
       0,     0,    47,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   345,     0,     0,    97,     0,     0,     0,
      22,    98,    99,   100,   101,   102,    84,     0,     0,     0,
       0,     0,     0,     0,    55,     0,     0,     0,     0,    21,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
       0,     0,     2,     3,     0,     0,     0,     4,     0,     5,
       0,     7,     0,    95,    96,     8,     9,     0,     0,    11,
      12,     0,     0,    14,     0,     0,    16,    17,    18,    19,
      20,     0,     0,    97,     0,     0,     0,    22,    98,    99,
     100,   101,   102,     2,     3,     0,     0,     0,     4,     0,
       5,    55,     7,     0,     0,     0,     8,     9,     0,     0,
      11,    12,     0,    84,    14,     0,     0,    16,    17,    18,
      19,    20,     0,     0,    84,   184,    21,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    21,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,     0,     0,
      95,    96,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    95,    96,     0,     0,     0,   272,     0,     0,     0,
      97,     0,   165,     0,    22,    98,    99,   100,   101,   102,
      84,    97,   286,     0,     0,    22,    98,    99,   100,   101,
     102,    84,     0,    21,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    94,    21,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,     0,     0,    95,    96,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    95,    96,
       0,     0,     0,     0,     0,     0,     0,    97,     0,   328,
       0,    22,    98,    99,   100,   101,   102,    84,    97,     0,
     355,     0,    22,    98,    99,   100,   101,   102,    84,     0,
      21,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    21,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,     0,     0,    95,    96,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    95,    96,     0,     0,     0,
       0,     0,     0,     0,    97,   368,     0,     0,    22,    98,
      99,   100,   101,   102,     0,    97,     0,     0,     0,    22,
      98,    99,   100,   101,   102,     1,     0,     0,     2,     3,
       0,     0,     0,     4,     0,     5,     6,     7,     0,     0,
       0,     8,     9,    10,     0,    11,    12,     0,    13,    14,
       0,    15,    16,    17,    18,    19,    20,     1,     0,     0,
       2,     3,     0,     0,     0,     4,     0,     5,     6,     7,
       0,   334,     0,     8,     9,    10,     0,    11,    12,     0,
      13,    14,     0,    15,    16,    17,    18,    19,    20
};

static const yytype_int16 yycheck[] =
{
       0,    60,    30,    31,    41,    68,    36,   126,    31,    39,
     249,    67,   258,    38,    81,   100,     7,   179,   170,    40,
       0,    49,    38,    38,    24,    38,    56,    66,    58,     0,
      60,    31,    78,    85,    86,    63,    36,    31,   190,    39,
      63,    62,    42,    34,    65,   150,    46,   111,    42,    78,
     105,    38,    46,    24,    93,   101,    81,    57,    80,    38,
      31,    86,    80,    63,    79,    65,    79,   126,    68,    63,
      41,    42,   101,   178,    74,    46,   113,    38,    59,   325,
     319,   186,    59,    83,   100,    78,    83,    79,    80,    83,
      83,    82,    63,    78,   150,    65,   126,    78,    79,    80,
      81,    78,    79,    80,    81,   267,   258,    86,   163,    40,
     262,    78,    83,   105,   181,   143,   101,    84,    78,    50,
     141,    81,   178,    80,   105,    86,   278,   170,   105,    94,
     186,    62,    95,   161,   162,   163,   146,    38,   109,   110,
     101,   141,   113,   100,    78,   204,   146,   190,   158,    83,
     205,    87,   207,    81,   213,    81,   261,   212,   158,   187,
     160,   216,    78,    79,   101,    67,    86,   231,   232,   233,
     170,   276,    78,   325,    69,    70,   170,    83,    83,   179,
     239,    82,   153,   154,    85,    86,   157,    84,   159,   308,
     245,   246,   247,    81,    62,    63,    64,    82,    78,   170,
     181,    78,    67,    68,   181,   261,    83,   109,   110,   111,
     210,   211,    83,    98,    99,   207,   280,    85,    86,   190,
     276,   326,   250,   260,    92,   253,   207,   237,   238,    78,
     207,    96,    97,   243,    83,    78,    78,   237,   238,    78,
      83,    83,    82,   243,    83,    85,    86,    81,   150,   308,
      35,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    83,   262,   263,   327,    60,    61,   267,   262,    84,
     326,    88,    89,    83,   274,    83,   178,   258,   308,    84,
     274,    80,    83,   342,   186,   322,   257,    12,   344,   260,
      24,   262,    78,    79,    78,    79,   351,   352,   223,   224,
     225,   226,    65,   274,   314,   227,   228,   278,   221,   222,
     229,   230,    74,   215,   314,   217,   218,   219,   220,   221,
     222,   223,   224,   225,   226,   227,   228,   229,   230,   231,
     232,   233,    78,   274,   266,    46,   257,     0,   348,   349,
     350,   113,   215,   207,   325,   217,   374,   318,   348,   349,
     350,   322,   218,   220,   141,   248,   219,    -1,   368,   261,
      -1,    24,    -1,   373,    -1,    -1,   376,    -1,   368,    32,
      33,    34,    -1,   373,   276,    -1,   376,    40,   280,    -1,
       3,    -1,    -1,     6,     7,    -1,    -1,    -1,    11,    -1,
      13,    14,    15,    -1,    -1,    -1,    19,    20,    21,    62,
      23,    24,    65,    26,    27,    -1,    29,    30,    31,    32,
      33,    34,     6,     7,    -1,    -1,    -1,    11,    -1,    13,
      -1,    15,    -1,    -1,   326,    19,    20,    -1,    -1,    23,
      24,    -1,    -1,    27,    -1,    -1,    30,    31,    32,    33,
      34,    -1,   344,    -1,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    -1,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,   100,   141,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    62,    63,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      79,    -1,    -1,    82,    -1,    -1,    -1,    86,    87,    88,
      89,    90,    91,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   100,   101,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    -1,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    -1,    -1,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    62,    63,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    79,
      -1,    -1,    82,    -1,    -1,    -1,    86,    87,    88,    89,
      90,    91,     4,     5,    -1,    -1,     8,     9,    10,    -1,
     100,   101,    -1,    -1,    16,    17,    18,    -1,    -1,    -1,
      22,    -1,    -1,    25,    -1,    -1,    28,    -1,    -1,    -1,
      -1,    -1,    -1,    35,    -1,    -1,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      62,    63,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    79,    -1,    -1,
      82,    -1,    -1,    -1,    86,    87,    88,    89,    90,    91,
       4,     5,    -1,    -1,     8,     9,    10,    -1,   100,   101,
      -1,    -1,    16,    17,    18,    -1,    -1,    -1,    22,    -1,
      -1,    25,    -1,    -1,    28,    -1,    -1,    -1,    -1,    -1,
      -1,    35,    -1,    -1,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    62,    63,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    79,    -1,    -1,    82,    -1,
      -1,    -1,    86,    87,    88,    89,    90,    91,     4,     5,
      -1,    -1,     8,     9,    10,    -1,   100,   101,    -1,    -1,
      16,    17,    18,    -1,    -1,    -1,    22,    -1,    -1,    25,
      -1,    -1,    28,    -1,    -1,    -1,    -1,    -1,    -1,    35,
      -1,    -1,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,     3,    -1,    -1,     6,     7,    -1,    -1,
      -1,    11,    -1,    13,    14,    15,    62,    63,    -1,    19,
      20,    21,    -1,    23,    24,    -1,    26,    27,    -1,    29,
      30,    31,    32,    33,    34,    -1,    82,    -1,    -1,    -1,
      86,    87,    88,    89,    90,    91,    -1,    -1,    -1,    -1,
      -1,     6,     7,    -1,   100,   101,    11,    -1,    13,    -1,
      15,    -1,    -1,    -1,    19,    20,    -1,    -1,    23,    24,
      25,    -1,    27,    -1,    -1,    30,    31,    32,    33,    34,
      80,    -1,    -1,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,     3,    -1,    -1,     6,     7,    -1,
     100,    -1,    11,    -1,    13,    14,    15,    62,    63,    -1,
      19,    20,    21,    -1,    23,    24,    -1,    26,    27,    -1,
      29,    30,    31,    32,    33,    34,    -1,    82,    -1,    38,
      -1,    86,    87,    88,    89,    90,    91,     3,    -1,    -1,
       6,     7,    -1,    -1,    -1,    11,    -1,    13,    14,    15,
      -1,    -1,    -1,    19,    20,    21,    -1,    23,    24,    -1,
      26,    27,    -1,    29,    30,    31,    32,    33,    34,    -1,
      -1,    -1,    -1,    82,    83,     3,    85,    86,     6,     7,
      -1,    -1,    -1,    11,    -1,    13,    14,    15,    -1,    -1,
      -1,    19,    20,    21,    -1,    23,    24,    -1,    26,    27,
      -1,    29,    30,    31,    32,    33,    34,    -1,    -1,    -1,
      38,    -1,    -1,    -1,    -1,    -1,    82,    83,     3,    85,
      86,     6,     7,    -1,    -1,    -1,    11,    -1,    13,    14,
      15,    -1,    -1,    -1,    19,    20,    21,    -1,    23,    24,
      -1,    26,    27,    -1,    29,    30,    31,    32,    33,    34,
      -1,     3,    -1,    38,     6,     7,    -1,    -1,    86,    11,
      -1,    13,    14,    15,    -1,    -1,    -1,    19,    20,    21,
      -1,    23,    24,    -1,    26,    27,    -1,    29,    30,    31,
      32,    33,    34,    -1,    -1,    -1,    25,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    83,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    25,
      -1,    -1,    -1,    62,    63,    -1,    -1,    -1,    -1,    -1,
      -1,    83,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    82,    -1,    -1,    -1,    86,    87,    88,
      89,    90,    91,    -1,    -1,    -1,    62,    63,    -1,    -1,
      -1,    -1,   101,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    79,    -1,    -1,    82,    -1,    -1,    -1,
      86,    87,    88,    89,    90,    91,    25,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   100,    -1,    -1,    -1,    -1,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      -1,    -1,     6,     7,    -1,    -1,    -1,    11,    -1,    13,
      -1,    15,    -1,    62,    63,    19,    20,    -1,    -1,    23,
      24,    -1,    -1,    27,    -1,    -1,    30,    31,    32,    33,
      34,    -1,    -1,    82,    -1,    -1,    -1,    86,    87,    88,
      89,    90,    91,     6,     7,    -1,    -1,    -1,    11,    -1,
      13,   100,    15,    -1,    -1,    -1,    19,    20,    -1,    -1,
      23,    24,    -1,    25,    27,    -1,    -1,    30,    31,    32,
      33,    34,    -1,    -1,    25,    79,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    -1,    -1,
      62,    63,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    62,    63,    -1,    -1,    -1,    79,    -1,    -1,    -1,
      82,    -1,    84,    -1,    86,    87,    88,    89,    90,    91,
      25,    82,    83,    -1,    -1,    86,    87,    88,    89,    90,
      91,    25,    -1,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    -1,    -1,    62,    63,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    62,    63,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    82,    -1,    84,
      -1,    86,    87,    88,    89,    90,    91,    25,    82,    -1,
      84,    -1,    86,    87,    88,    89,    90,    91,    25,    -1,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    -1,    -1,    62,    63,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    62,    63,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    82,    83,    -1,    -1,    86,    87,
      88,    89,    90,    91,    -1,    82,    -1,    -1,    -1,    86,
      87,    88,    89,    90,    91,     3,    -1,    -1,     6,     7,
      -1,    -1,    -1,    11,    -1,    13,    14,    15,    -1,    -1,
      -1,    19,    20,    21,    -1,    23,    24,    -1,    26,    27,
      -1,    29,    30,    31,    32,    33,    34,     3,    -1,    -1,
       6,     7,    -1,    -1,    -1,    11,    -1,    13,    14,    15,
      -1,    49,    -1,    19,    20,    21,    -1,    23,    24,    -1,
      26,    27,    -1,    29,    30,    31,    32,    33,    34
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     6,     7,    11,    13,    14,    15,    19,    20,
      21,    23,    24,    26,    27,    29,    30,    31,    32,    33,
      34,    38,    86,   103,   104,   105,   106,   107,   108,   109,
     111,   112,   113,   114,   115,   116,   117,   118,   122,   123,
     129,   133,   141,   142,     0,   105,    78,   101,   176,   111,
     129,   176,   112,   112,   112,   100,   118,   169,   118,   169,
      80,   106,   110,   112,   168,   169,    85,   140,   141,   129,
     129,   142,   176,   168,   169,   118,   119,   120,   169,   114,
     115,   124,   125,   126,    25,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    62,    63,    82,    87,    88,
      89,    90,    91,   118,   131,   141,   143,   146,   148,   149,
     150,   151,   153,   154,   156,   157,   158,   159,   160,   161,
     162,   163,   164,   165,   166,   167,   169,   106,   168,     4,
       5,     8,     9,    10,    16,    17,    18,    22,    28,    35,
      79,   110,   118,   145,   146,   168,   170,   171,   172,   173,
     174,   175,   176,   177,   179,   180,   181,   182,   183,   184,
     185,   186,   187,   188,   189,    84,   121,   148,   157,    83,
     112,   118,   134,   135,   136,   137,    83,   119,    80,    78,
      79,   124,   126,   126,    79,   125,    81,   127,   128,   129,
     126,   145,   152,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    80,   147,   141,   148,   141,   148,   153,
      64,    92,   140,   141,   149,    66,    93,    65,    94,    95,
      87,    69,    70,    67,    68,    96,    97,    60,    61,    88,
      89,    82,    98,    99,   143,   144,    79,   170,    81,    78,
     176,    79,   171,    81,   121,   141,   141,   141,   171,   141,
     118,   176,   176,   145,   176,    84,   129,   130,   131,   138,
     139,   140,   141,    78,    83,    83,    78,    78,    79,   121,
      79,   120,    79,   121,    78,   176,    81,   138,   141,    83,
      83,   146,   152,   118,   118,   145,    83,   146,   155,   159,
     145,   160,   161,   162,   163,   164,   164,   165,   165,   165,
     165,   166,   166,   167,   167,   153,   153,   153,    78,    79,
      79,   171,   146,   171,    81,   145,   145,   145,   182,   175,
     176,   176,   139,   114,   130,   132,   140,   141,    84,   121,
      83,   135,   138,   118,    49,   137,    79,   128,   121,   153,
      83,    84,    78,    83,    81,    79,   143,   171,    83,    83,
      83,   141,   175,   114,   130,    84,   121,    83,   135,    84,
      83,    83,   146,   157,   171,   171,   171,   145,    83,   145,
      84,    83,    12,   178,    83,   171,    83,   171,   176,   171
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   102,   103,   104,   104,   105,   105,   106,   106,   107,
     108,   108,   109,   109,   109,   110,   110,   111,   111,   112,
     112,   112,   112,   112,   112,   113,   113,   113,   113,   113,
     114,   114,   115,   115,   115,   115,   115,   115,   115,   115,
     115,   115,   115,   115,   116,   116,   116,   116,   116,   117,
     118,   119,   119,   120,   120,   121,   122,   122,   122,   123,
     123,   124,   124,   125,   126,   126,   126,   126,   127,   127,
     128,   128,   128,   129,   130,   130,   130,   130,   131,   132,
     132,   133,   133,   133,   133,   133,   133,   133,   134,   134,
     135,   135,   136,   136,   137,   137,   137,   138,   138,   138,
     139,   139,   139,   139,   139,   139,   139,   139,   139,   140,
     141,   142,   142,   143,   143,   143,   144,   144,   145,   145,
     146,   146,   147,   147,   147,   147,   147,   147,   147,   147,
     147,   147,   147,   148,   148,   148,   148,   148,   149,   149,
     150,   151,   151,   151,   151,   151,   151,   152,   152,   153,
     153,   154,   154,   154,   154,   154,   154,   154,   155,   155,
     156,   156,   156,   156,   156,   156,   156,   156,   156,   156,
     156,   156,   157,   157,   158,   158,   159,   159,   160,   160,
     161,   161,   162,   162,   163,   163,   163,   164,   164,   164,
     164,   164,   165,   165,   165,   166,   166,   166,   167,   167,
     167,   167,   168,   168,   168,   168,   169,   170,   170,   171,
     171,   171,   171,   171,   171,   172,   172,   172,   173,   174,
     175,   175,   176,   177,   178,   179,   180,   180,   180,   181,
     181,   181,   181,   182,   183,   184,   185,   186,   187,   188,
     189,   189,   189,   189,   189
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     2,     1,     1,     3,     2,     2,
       1,     1,     3,     3,     2,     1,     2,     1,     3,     1,
       2,     1,     2,     1,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     2,     4,     5,     5,     6,     1,
       1,     1,     3,     1,     3,     1,     2,     5,     4,     1,
       1,     1,     2,     3,     1,     2,     1,     2,     1,     3,
       1,     2,     3,     1,     1,     2,     2,     3,     1,     1,
       2,     1,     3,     4,     3,     4,     4,     3,     1,     3,
       1,     3,     1,     3,     1,     2,     2,     1,     1,     2,
       3,     2,     3,     3,     4,     2,     3,     3,     4,     1,
       1,     1,     3,     1,     3,     4,     1,     3,     1,     3,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     2,     2,     2,     4,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     2,     1,
       4,     1,     4,     3,     4,     3,     3,     2,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     1,     5,     1,     3,     1,     3,     1,     3,
       1,     3,     1,     3,     1,     3,     3,     1,     3,     3,
       3,     3,     1,     3,     3,     1,     3,     3,     1,     3,
       3,     3,     2,     3,     3,     4,     1,     1,     2,     1,
       1,     1,     1,     1,     1,     3,     4,     3,     1,     1,
       1,     2,     1,     1,     1,     1,     5,     7,     5,     5,
       7,     6,     7,     1,     1,     1,     1,     1,     1,     1,
       3,     2,     2,     2,     3
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


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
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
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
#ifndef YYINITDEPTH
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
static YYSIZE_T
yystrlen (const char *yystr)
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
static char *
yystpcpy (char *yydest, const char *yysrc)
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
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
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
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
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

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

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
      yychar = yylex ();
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
     '$$ = $1'.

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
#line 127 "simple_parse.y" /* yacc.c:1646  */
    {translationunit = create_translationunit((yyvsp[0].ast));}
#line 1884 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 130 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=(yyvsp[0].ast);}
#line 1890 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 131 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=append_astnode((yyvsp[-1].ast),(yyvsp[0].ast));}
#line 1896 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 134 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=(yyvsp[0].ast);}
#line 1902 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 135 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=(yyvsp[0].ast);}
#line 1908 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 139 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=base_of(create_declaration((yyvsp[-2].ast),(yyvsp[-1].ast)));}
#line 1914 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 141 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=base_of(create_declaration((yyvsp[-1].ast),NULL));}
#line 1920 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 145 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=base_of(create_declaration(NULL,(yyvsp[-1].ast)));}
#line 1926 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 148 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=(yyvsp[0].ast);}
#line 1932 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 149 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=(yyvsp[0].ast);}
#line 1938 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 153 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=base_of(create_functiondeclaration((yyvsp[-2].ast),(yyvsp[-1].ast),NULL,(yyvsp[0].ast)));}
#line 1944 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 155 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=base_of(create_functiondeclaration(NULL,(yyvsp[-2].ast),(yyvsp[-1].ast),(yyvsp[0].ast)));}
#line 1950 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 157 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=base_of(create_functiondeclaration(NULL,(yyvsp[-1].ast),NULL,(yyvsp[0].ast)));}
#line 1956 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 160 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=(yyvsp[0].ast);}
#line 1962 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 161 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=append_astnode((yyvsp[-1].ast),(yyvsp[0].ast));}
#line 1968 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 164 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=(yyvsp[0].ast);}
#line 1974 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 165 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=append_astnode((yyvsp[-2].ast),(yyvsp[0].ast));}
#line 1980 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 169 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast) = base_of(create_declarationspecifier1((yyvsp[0].ast)));}
#line 1986 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 171 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast) = base_of(create_declarationspecifier2((yyvsp[-1].ast),(yyvsp[0].ast)));}
#line 1992 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 173 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast) = base_of(create_declarationspecifier3((yyvsp[0].ast)));}
#line 1998 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 175 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast) = base_of(create_declarationspecifier4((yyvsp[-1].ast),(yyvsp[0].ast)));}
#line 2004 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 177 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast) = base_of(create_declarationspecifier5((yyvsp[0].ast)));}
#line 2010 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 179 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast) = base_of(create_declarationspecifier6((yyvsp[-1].ast),(yyvsp[0].ast)));}
#line 2016 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 182 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast) = base_of(create_atom(AUTO,tval,tcoord));}
#line 2022 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 183 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast) = base_of(create_atom(REGISTER,tval,tcoord));}
#line 2028 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 184 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast) = base_of(create_atom(STATIC,tval,tcoord));}
#line 2034 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 185 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast) = base_of(create_atom(EXTERN,tval,tcoord));}
#line 2040 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 186 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast) = base_of(create_atom(TYPEDEF,tval,tcoord));}
#line 2046 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 189 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast) = base_of(create_atom(CONST,tval,tcoord));}
#line 2052 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 190 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast) = base_of(create_atom(VOLATILE,tval,tcoord));}
#line 2058 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 193 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast) = base_of(create_atom(VOID,tval,tcoord));}
#line 2064 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 194 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast) = base_of(create_atom(CHAR,tval,tcoord));}
#line 2070 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 195 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast) = base_of(create_atom(SHORT,tval,tcoord));}
#line 2076 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 196 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast) = base_of(create_atom(INT,tval,tcoord));}
#line 2082 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 197 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast) = base_of(create_atom(LONG,tval,tcoord));}
#line 2088 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 198 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast) = base_of(create_atom(SIGNED,tval,tcoord));}
#line 2094 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 199 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast) = base_of(create_atom(UNSIGNED,tval,tcoord));}
#line 2100 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 200 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast) = base_of(create_atom(FLOAT,tval,tcoord));}
#line 2106 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 201 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast) = base_of(create_atom(DOUBLE,tval,tcoord));}
#line 2112 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 202 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast) = base_of(create_atom(TYPENAME,tval,tcoord));}
#line 2118 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 203 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 2124 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 204 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 2130 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 208 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=base_of(create_enumspec((yyvsp[-1].ast),(yyvsp[0].ast),NULL));}
#line 2136 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 210 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=base_of(create_enumspec((yyvsp[-3].ast),NULL,(yyvsp[-1].ast)));}
#line 2142 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 212 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=base_of(create_enumspec((yyvsp[-4].ast),NULL,(yyvsp[-2].ast)));}
#line 2148 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 214 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=base_of(create_enumspec((yyvsp[-4].ast),(yyvsp[-3].ast),(yyvsp[-1].ast)));}
#line 2154 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 216 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=base_of(create_enumspec((yyvsp[-5].ast),(yyvsp[-4].ast),(yyvsp[-2].ast)));}
#line 2160 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 219 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=base_of(create_atom(ENUM,tval,tcoord));}
#line 2166 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 222 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast) = base_of(create_atom(IDENTIFIER,tval,tcoord));}
#line 2172 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 225 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=(yyvsp[0].ast);}
#line 2178 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 226 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=append_astnode((yyvsp[-2].ast),(yyvsp[0].ast));}
#line 2184 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 229 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=base_of(create_enumerator((yyvsp[0].ast),NULL));}
#line 2190 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 230 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=base_of(create_enumerator((yyvsp[-2].ast),(yyvsp[0].ast)));}
#line 2196 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 233 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=(yyvsp[0].ast);}
#line 2202 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 237 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=base_of(create_structorunion((yyvsp[-1].ast),(yyvsp[0].ast),NULL));}
#line 2208 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 239 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=base_of(create_structorunion((yyvsp[-4].ast),(yyvsp[-3].ast),(yyvsp[-1].ast)));}
#line 2214 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 241 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=base_of(create_structorunion((yyvsp[-3].ast),NULL,(yyvsp[-1].ast)));}
#line 2220 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 244 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=base_of(create_atom(STRUCT,tval,tcoord));}
#line 2226 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 245 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=base_of(create_atom(UNION,tval,tcoord));}
#line 2232 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 249 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=(yyvsp[0].ast);}
#line 2238 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 251 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=append_astnode((yyvsp[-1].ast),(yyvsp[0].ast));}
#line 2244 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 255 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=base_of(create_structdeclaration((yyvsp[-2].ast),(yyvsp[-1].ast)));}
#line 2250 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 259 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast) = base_of(create_declarationspecifier3((yyvsp[0].ast)));}
#line 2256 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 261 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast) = base_of(create_declarationspecifier4((yyvsp[-1].ast),(yyvsp[0].ast)));}
#line 2262 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 263 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast) = base_of(create_declarationspecifier5((yyvsp[0].ast)));}
#line 2268 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 265 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast) = base_of(create_declarationspecifier6((yyvsp[-1].ast),(yyvsp[0].ast)));}
#line 2274 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 268 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=(yyvsp[0].ast);}
#line 2280 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 269 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=append_astnode((yyvsp[-2].ast),(yyvsp[0].ast));}
#line 2286 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 273 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=base_of(create_structdeclarator((yyvsp[0].ast),NULL));}
#line 2292 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 275 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=base_of(create_structdeclarator(NULL,(yyvsp[0].ast)));}
#line 2298 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 277 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=base_of(create_structdeclarator((yyvsp[-2].ast),(yyvsp[0].ast)));}
#line 2304 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 281 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=(yyvsp[0].ast);}
#line 2310 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 285 "simple_parse.y" /* yacc.c:1646  */
    { (yyval.ast) = base_of(create_pointerdeclarator((yyvsp[0].ast)->coord,NULL,NULL));}
#line 2316 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 287 "simple_parse.y" /* yacc.c:1646  */
    { (yyval.ast) = base_of(create_pointerdeclarator((yyvsp[-1].ast)->coord,(yyvsp[0].ast),NULL));}
#line 2322 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 289 "simple_parse.y" /* yacc.c:1646  */
    { (yyval.ast) = base_of(create_pointerdeclarator((yyvsp[-1].ast)->coord,NULL,(yyvsp[0].ast)));}
#line 2328 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 291 "simple_parse.y" /* yacc.c:1646  */
    { (yyval.ast) = base_of(create_pointerdeclarator((yyvsp[-2].ast)->coord,(yyvsp[-1].ast),(yyvsp[0].ast)));}
#line 2334 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 294 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=base_of(create_atom('*',tval,tcoord));}
#line 2340 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 298 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=(yyvsp[0].ast);}
#line 2346 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 299 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=append_astnode((yyvsp[-1].ast),(yyvsp[0].ast));}
#line 2352 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 303 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=base_of(create_directdeclarator((yyvsp[0].ast)));}
#line 2358 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 305 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=(yyvsp[-1].ast); (yyval.ast)->has_paren = 1;}
#line 2364 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 307 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=base_of(create_arraydeclarator((yyvsp[-3].ast),(yyvsp[-1].ast)));}
#line 2370 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 84:
#line 309 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=base_of(create_arraydeclarator((yyvsp[-2].ast),NULL));}
#line 2376 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 85:
#line 311 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=base_of(create_funcdeclarator((yyvsp[-3].ast),(yyvsp[-1].ast),NULL));}
#line 2382 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 86:
#line 313 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=base_of(create_funcdeclarator((yyvsp[-3].ast),NULL,(yyvsp[-1].ast)));}
#line 2388 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 87:
#line 315 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=base_of(create_funcdeclarator((yyvsp[-2].ast),NULL,NULL));}
#line 2394 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 88:
#line 318 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=(yyvsp[0].ast);}
#line 2400 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 89:
#line 319 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=append_astnode((yyvsp[-2].ast),(yyvsp[0].ast));}
#line 2406 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 90:
#line 322 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=base_of(create_paramtypelist((yyvsp[0].ast),0));}
#line 2412 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 91:
#line 323 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=base_of(create_paramtypelist((yyvsp[-2].ast),1));}
#line 2418 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 92:
#line 326 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=(yyvsp[0].ast);}
#line 2424 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 93:
#line 327 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=append_astnode((yyvsp[-2].ast),(yyvsp[0].ast));}
#line 2430 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 94:
#line 331 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=base_of(create_paramdeclaration((yyvsp[0].ast),NULL));}
#line 2436 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 95:
#line 333 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=base_of(create_paramdeclaration((yyvsp[-1].ast),(yyvsp[0].ast)));}
#line 2442 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 96:
#line 335 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=base_of(create_paramdeclaration((yyvsp[-1].ast),(yyvsp[0].ast)));}
#line 2448 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 97:
#line 339 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=(yyvsp[0].ast);}
#line 2454 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 98:
#line 341 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=(yyvsp[0].ast);}
#line 2460 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 99:
#line 343 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=base_of(chain_pointerdeclarator((yyvsp[-1].ast),(yyvsp[0].ast)));}
#line 2466 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 100:
#line 347 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=(yyvsp[-1].ast); (yyval.ast)->has_paren = 1;}
#line 2472 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 101:
#line 349 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=base_of(create_arraydeclarator(base_of(create_abstractdeclarator((yyvsp[-1].ast)->coord)),NULL));}
#line 2478 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 102:
#line 351 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=base_of(create_arraydeclarator(base_of(create_abstractdeclarator((yyvsp[-2].ast)->coord)),(yyvsp[-1].ast)));}
#line 2484 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 103:
#line 353 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=base_of(create_arraydeclarator((yyvsp[-2].ast),NULL));}
#line 2490 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 104:
#line 355 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=base_of(create_arraydeclarator((yyvsp[-3].ast),(yyvsp[-1].ast)));}
#line 2496 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 105:
#line 357 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=base_of(create_funcdeclarator(base_of(create_abstractdeclarator((yyvsp[-1].ast)->coord)),NULL,NULL));}
#line 2502 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 106:
#line 359 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=base_of(create_funcdeclarator(base_of(create_abstractdeclarator((yyvsp[-2].ast)->coord)),(yyvsp[-1].ast),NULL));}
#line 2508 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 107:
#line 361 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=base_of(create_funcdeclarator((yyvsp[-2].ast),NULL,NULL));}
#line 2514 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 108:
#line 363 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=base_of(create_funcdeclarator((yyvsp[-3].ast),(yyvsp[-1].ast),NULL));}
#line 2520 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 109:
#line 366 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=base_of(create_atom('[',tval,tcoord));}
#line 2526 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 110:
#line 369 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=base_of(create_atom('(',tval,tcoord));}
#line 2532 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 111:
#line 373 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=base_of(create_initdeclarator((yyvsp[0].ast),NULL));}
#line 2538 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 112:
#line 375 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=base_of(create_initdeclarator((yyvsp[-2].ast),(yyvsp[0].ast)));}
#line 2544 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 113:
#line 379 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=base_of(create_initializer(0,(yyvsp[0].ast)));}
#line 2550 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 114:
#line 381 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=base_of(create_initializer(1,(yyvsp[-1].ast)));}
#line 2556 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 115:
#line 383 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=base_of(create_initializer(1,(yyvsp[-2].ast)));}
#line 2562 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 116:
#line 387 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=(yyvsp[0].ast);}
#line 2568 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 117:
#line 389 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=append_astnode((yyvsp[-2].ast),(yyvsp[0].ast));}
#line 2574 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 118:
#line 393 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=(yyvsp[0].ast);}
#line 2580 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 119:
#line 395 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=base_of(create_binaryexpression(',',(yyvsp[-2].ast),(yyvsp[0].ast)));}
#line 2586 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 120:
#line 399 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=(yyvsp[0].ast);}
#line 2592 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 121:
#line 401 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=base_of(create_binaryexpression1((yyvsp[-1].ast),(yyvsp[-2].ast),(yyvsp[0].ast)));}
#line 2598 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 122:
#line 404 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=base_of(create_atom('=',tval,tcoord));}
#line 2604 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 123:
#line 405 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=base_of(create_atom(MUL_ASSIGN,tval,tcoord));}
#line 2610 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 124:
#line 406 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=base_of(create_atom(DIV_ASSIGN,tval,tcoord));}
#line 2616 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 125:
#line 407 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=base_of(create_atom(MOD_ASSIGN,tval,tcoord));}
#line 2622 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 126:
#line 408 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=base_of(create_atom(ADD_ASSIGN,tval,tcoord));}
#line 2628 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 127:
#line 409 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=base_of(create_atom(SUB_ASSIGN,tval,tcoord));}
#line 2634 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 128:
#line 410 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=base_of(create_atom(LEFT_ASSIGN,tval,tcoord));}
#line 2640 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 129:
#line 411 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=base_of(create_atom(RIGHT_ASSIGN,tval,tcoord));}
#line 2646 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 130:
#line 412 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=base_of(create_atom(AND_ASSIGN,tval,tcoord));}
#line 2652 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 131:
#line 413 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=base_of(create_atom(XOR_ASSIGN,tval,tcoord));}
#line 2658 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 132:
#line 414 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=base_of(create_atom(OR_ASSIGN,tval,tcoord));}
#line 2664 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 133:
#line 418 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=(yyvsp[0].ast);}
#line 2670 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 134:
#line 420 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=base_of(create_unaryexpression((yyvsp[-1].ast),(yyvsp[0].ast)));}
#line 2676 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 135:
#line 422 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=base_of(create_unaryexpression((yyvsp[-1].ast),(yyvsp[0].ast)));}
#line 2682 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 136:
#line 424 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=base_of(create_unaryexpression((yyvsp[-1].ast),(yyvsp[0].ast)));}
#line 2688 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 137:
#line 426 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=base_of(create_unaryexpression1((yyvsp[-3].ast),(yyvsp[-1].ast)));}
#line 2694 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 138:
#line 429 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=base_of(create_atom(INC_OP,tval,tcoord));}
#line 2700 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 139:
#line 430 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=base_of(create_atom(DEC_OP,tval,tcoord));}
#line 2706 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 140:
#line 433 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=base_of(create_atom(SIZEOF,tval,tcoord));}
#line 2712 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 141:
#line 436 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=base_of(create_atom('&',tval,tcoord));}
#line 2718 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 142:
#line 437 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=base_of(create_atom('+',tval,tcoord));}
#line 2724 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 143:
#line 438 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=base_of(create_atom('-',tval,tcoord));}
#line 2730 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 144:
#line 439 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=base_of(create_atom('~',tval,tcoord));}
#line 2736 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 145:
#line 440 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=base_of(create_atom('!',tval,tcoord));}
#line 2742 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 146:
#line 441 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=(yyvsp[0].ast);}
#line 2748 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 147:
#line 445 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=base_of(create_typename((yyvsp[0].ast),NULL));}
#line 2754 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 148:
#line 447 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=base_of(create_typename((yyvsp[-1].ast),(yyvsp[0].ast)));}
#line 2760 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 149:
#line 451 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=(yyvsp[0].ast);}
#line 2766 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 150:
#line 453 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=base_of(create_castexpression(CAST_OP,(yyvsp[-2].ast),(yyvsp[0].ast)));}
#line 2772 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 151:
#line 457 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=(yyvsp[0].ast);}
#line 2778 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 152:
#line 459 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=base_of(create_postfixexpression(INDEX_OP,(yyvsp[-3].ast),(yyvsp[-1].ast)));}
#line 2784 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 153:
#line 461 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=base_of(create_postfixexpression(CALL_OP,(yyvsp[-2].ast),NULL));}
#line 2790 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 154:
#line 463 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=base_of(create_postfixexpression(CALL_OP,(yyvsp[-3].ast),(yyvsp[-1].ast)));}
#line 2796 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 155:
#line 465 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=base_of(create_postfixexpression(MEMBER_OP,(yyvsp[-2].ast),(yyvsp[0].ast)));}
#line 2802 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 156:
#line 467 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=base_of(create_postfixexpression(PTR_OP,(yyvsp[-2].ast),(yyvsp[0].ast)));}
#line 2808 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 157:
#line 469 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=base_of(create_postfixexpression(POST_INC_DEC_OP,(yyvsp[-1].ast),(yyvsp[0].ast)));}
#line 2814 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 158:
#line 473 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=(yyvsp[0].ast);}
#line 2820 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 159:
#line 475 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=append_astnode((yyvsp[-2].ast),(yyvsp[0].ast));}
#line 2826 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 160:
#line 479 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=base_of(create_primaryexpression((yyvsp[0].ast)));}
#line 2832 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 161:
#line 481 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=base_of(create_primaryexpression(base_of(create_atom(INTCONST,tval,tcoord))));}
#line 2838 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 162:
#line 483 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=base_of(create_primaryexpression(base_of(create_atom(UINT,tval,tcoord))));}
#line 2844 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 163:
#line 485 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=base_of(create_primaryexpression(base_of(create_atom(LINT,tval,tcoord))));}
#line 2850 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 164:
#line 487 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=base_of(create_primaryexpression(base_of(create_atom(ULINT,tval,tcoord))));}
#line 2856 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 165:
#line 489 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=base_of(create_primaryexpression(base_of(create_atom(LLINT,tval,tcoord))));}
#line 2862 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 166:
#line 491 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=base_of(create_primaryexpression(base_of(create_atom(ULLINT,tval,tcoord))));}
#line 2868 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 167:
#line 493 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=base_of(create_primaryexpression(base_of(create_atom(DOUBLECONST,tval,tcoord))));}
#line 2874 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 168:
#line 495 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=base_of(create_primaryexpression(base_of(create_atom(LDOUBLECONST,tval,tcoord))));}
#line 2880 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 169:
#line 497 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=base_of(create_primaryexpression(base_of(create_atom(FLOATCONST,tval,tcoord))));}
#line 2886 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 170:
#line 499 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=base_of(create_primaryexpression(base_of(create_atom(STRING,tval,tcoord))));}
#line 2892 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 171:
#line 501 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=(yyvsp[-1].ast); (yyval.ast)->has_paren = 1;}
#line 2898 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 172:
#line 505 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=(yyvsp[0].ast);}
#line 2904 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 173:
#line 507 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=base_of(create_conditionalexpression(COND_OP,(yyvsp[-4].ast),(yyvsp[-2].ast),(yyvsp[0].ast)));}
#line 2910 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 174:
#line 511 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=(yyvsp[0].ast);}
#line 2916 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 175:
#line 513 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=base_of(create_binaryexpression(OR_OP,(yyvsp[-2].ast),(yyvsp[0].ast)));}
#line 2922 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 176:
#line 517 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=(yyvsp[0].ast);}
#line 2928 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 177:
#line 519 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=base_of(create_binaryexpression(AND_OP,(yyvsp[-2].ast),(yyvsp[0].ast)));}
#line 2934 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 178:
#line 523 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=(yyvsp[0].ast);}
#line 2940 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 179:
#line 525 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=base_of(create_binaryexpression('|',(yyvsp[-2].ast),(yyvsp[0].ast)));}
#line 2946 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 180:
#line 529 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=(yyvsp[0].ast);}
#line 2952 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 181:
#line 531 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=base_of(create_binaryexpression('^',(yyvsp[-2].ast),(yyvsp[0].ast)));}
#line 2958 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 182:
#line 535 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=(yyvsp[0].ast);}
#line 2964 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 183:
#line 537 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=base_of(create_binaryexpression('&',(yyvsp[-2].ast),(yyvsp[0].ast)));}
#line 2970 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 184:
#line 541 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=(yyvsp[0].ast);}
#line 2976 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 185:
#line 543 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=base_of(create_binaryexpression(EQ_OP,(yyvsp[-2].ast),(yyvsp[0].ast)));}
#line 2982 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 186:
#line 545 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=base_of(create_binaryexpression(NE_OP,(yyvsp[-2].ast),(yyvsp[0].ast)));}
#line 2988 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 187:
#line 549 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=(yyvsp[0].ast);}
#line 2994 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 188:
#line 551 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=base_of(create_binaryexpression('<',(yyvsp[-2].ast),(yyvsp[0].ast)));}
#line 3000 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 189:
#line 553 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=base_of(create_binaryexpression('>',(yyvsp[-2].ast),(yyvsp[0].ast)));}
#line 3006 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 190:
#line 555 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=base_of(create_binaryexpression(LE_OP,(yyvsp[-2].ast),(yyvsp[0].ast)));}
#line 3012 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 191:
#line 557 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=base_of(create_binaryexpression(GE_OP,(yyvsp[-2].ast),(yyvsp[0].ast)));}
#line 3018 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 192:
#line 561 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=(yyvsp[0].ast);}
#line 3024 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 193:
#line 563 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=base_of(create_binaryexpression(LEFT_SHIFT,(yyvsp[-2].ast),(yyvsp[0].ast)));}
#line 3030 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 194:
#line 565 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=base_of(create_binaryexpression(RIGHT_SHIFT,(yyvsp[-2].ast),(yyvsp[0].ast)));}
#line 3036 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 195:
#line 569 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=(yyvsp[0].ast);}
#line 3042 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 196:
#line 571 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=base_of(create_binaryexpression('+',(yyvsp[-2].ast),(yyvsp[0].ast)));}
#line 3048 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 197:
#line 573 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=base_of(create_binaryexpression('-',(yyvsp[-2].ast),(yyvsp[0].ast)));}
#line 3054 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 198:
#line 577 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=(yyvsp[0].ast);}
#line 3060 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 199:
#line 579 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=base_of(create_binaryexpression('*',(yyvsp[-2].ast),(yyvsp[0].ast)));}
#line 3066 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 200:
#line 581 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=base_of(create_binaryexpression('/',(yyvsp[-2].ast),(yyvsp[0].ast)));}
#line 3072 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 201:
#line 583 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=base_of(create_binaryexpression('%',(yyvsp[-2].ast),(yyvsp[0].ast)));}
#line 3078 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 202:
#line 587 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=base_of(create_compoundstmt((yyvsp[-1].ast)->coord,NULL,NULL));}
#line 3084 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 203:
#line 589 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=base_of(create_compoundstmt((yyvsp[-2].ast)->coord,NULL,(yyvsp[-1].ast)));}
#line 3090 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 204:
#line 591 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=base_of(create_compoundstmt((yyvsp[-2].ast)->coord,(yyvsp[-1].ast),NULL));}
#line 3096 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 205:
#line 593 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=base_of(create_compoundstmt((yyvsp[-3].ast)->coord,(yyvsp[-2].ast),(yyvsp[-1].ast)));}
#line 3102 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 206:
#line 596 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=base_of(create_atom('{', tval, tcoord));}
#line 3108 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 207:
#line 600 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=(yyvsp[0].ast);}
#line 3114 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 208:
#line 602 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=append_astnode((yyvsp[-1].ast),(yyvsp[0].ast));}
#line 3120 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 209:
#line 606 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=(yyvsp[0].ast);}
#line 3126 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 210:
#line 608 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=(yyvsp[0].ast);}
#line 3132 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 211:
#line 610 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=(yyvsp[0].ast);}
#line 3138 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 212:
#line 612 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=(yyvsp[0].ast);}
#line 3144 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 213:
#line 614 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=(yyvsp[0].ast);}
#line 3150 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 214:
#line 616 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=(yyvsp[0].ast);}
#line 3156 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 215:
#line 620 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=base_of(create_labelstmt(IDLABEL,(yyvsp[-2].ast)->coord,(yyvsp[-2].ast),(yyvsp[0].ast)));}
#line 3162 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 216:
#line 622 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=base_of(create_labelstmt(CASELABEL,(yyvsp[-3].ast)->coord,(yyvsp[-2].ast),(yyvsp[0].ast)));}
#line 3168 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 217:
#line 624 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=base_of(create_labelstmt(DEFAULTLABEL,(yyvsp[-2].ast)->coord,NULL,(yyvsp[0].ast)));}
#line 3174 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 218:
#line 628 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=base_of(create_atom(DEFAULT,tval,tcoord));}
#line 3180 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 219:
#line 632 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=base_of(create_atom(CASE,tval,tcoord));}
#line 3186 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 220:
#line 636 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=base_of(create_exprstmt((yyvsp[0].ast)->coord,NULL));}
#line 3192 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 221:
#line 638 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=base_of(create_exprstmt((yyvsp[-1].ast)->coord,(yyvsp[-1].ast)));}
#line 3198 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 222:
#line 641 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=base_of(create_atom(';',tval,tcoord));}
#line 3204 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 223:
#line 644 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=base_of(create_atom(IF,tval,tcoord));}
#line 3210 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 224:
#line 646 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=base_of(create_atom(ELSE,tval,tcoord));}
#line 3216 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 225:
#line 648 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=base_of(create_atom(SWITCH,tval,tcoord));}
#line 3222 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 226:
#line 652 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=base_of(create_selstmt(IFSTMT,(yyvsp[-4].ast)->coord,(yyvsp[-2].ast),(yyvsp[0].ast),NULL));}
#line 3228 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 227:
#line 654 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=base_of(create_selstmt(IFELSESTMT,(yyvsp[-6].ast)->coord,(yyvsp[-4].ast),(yyvsp[-2].ast),(yyvsp[0].ast)));}
#line 3234 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 228:
#line 656 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=base_of(create_selstmt(SWITCHSTMT,(yyvsp[-4].ast)->coord,(yyvsp[-2].ast),(yyvsp[0].ast),NULL));}
#line 3240 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 229:
#line 660 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=base_of(create_iterationstmt(WHILESTMT,(yyvsp[-4].ast)->coord,(yyvsp[-2].ast),(yyvsp[0].ast),NULL,NULL));}
#line 3246 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 230:
#line 662 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=base_of(create_iterationstmt(DOSTMT,(yyvsp[-6].ast)->coord,(yyvsp[-2].ast),(yyvsp[-5].ast),NULL,NULL));}
#line 3252 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 231:
#line 664 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=base_of(create_iterationstmt(FORSTMT,(yyvsp[-5].ast)->coord,NULL,(yyvsp[0].ast),(yyvsp[-3].ast),(yyvsp[-2].ast)));}
#line 3258 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 232:
#line 666 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=base_of(create_iterationstmt(FORSTMT,(yyvsp[-6].ast)->coord,(yyvsp[-2].ast),(yyvsp[0].ast),(yyvsp[-4].ast),(yyvsp[-3].ast)));}
#line 3264 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 233:
#line 669 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=base_of(create_atom(WHILE,tval,tcoord));}
#line 3270 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 234:
#line 672 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=base_of(create_atom(DO,tval,tcoord));}
#line 3276 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 235:
#line 675 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=base_of(create_atom(FOR,tval,tcoord));}
#line 3282 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 236:
#line 678 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=base_of(create_atom(GOTO,tval,tcoord));}
#line 3288 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 237:
#line 681 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=base_of(create_atom(CONTINUE,tval,tcoord));}
#line 3294 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 238:
#line 684 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=base_of(create_atom(BREAK,tval,tcoord));}
#line 3300 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 239:
#line 687 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=base_of(create_atom(RETURN,tval,tcoord));}
#line 3306 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 240:
#line 691 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=base_of(create_jumpstmt(GOTOSTMT,(yyvsp[-2].ast)->coord,(yyvsp[-1].ast)));}
#line 3312 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 241:
#line 693 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=base_of(create_jumpstmt(CONTINUESTMT,(yyvsp[-1].ast)->coord,NULL));}
#line 3318 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 242:
#line 695 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=base_of(create_jumpstmt(BREAKSTMT,(yyvsp[-1].ast)->coord,NULL));}
#line 3324 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 243:
#line 697 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=base_of(create_jumpstmt(RETURNSTMT,(yyvsp[-1].ast)->coord,NULL));}
#line 3330 "simple_parse.tab.c" /* yacc.c:1646  */
    break;

  case 244:
#line 699 "simple_parse.y" /* yacc.c:1646  */
    {(yyval.ast)=base_of(create_jumpstmt(RETURNSTMT,(yyvsp[-2].ast)->coord,(yyvsp[-1].ast)));}
#line 3336 "simple_parse.tab.c" /* yacc.c:1646  */
    break;


#line 3340 "simple_parse.tab.c" /* yacc.c:1646  */
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

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
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

  /* Do not reclaim the symbols of the rule whose action triggered
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
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

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
  /* Do not reclaim the symbols of the rule whose action triggered
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
#line 702 "simple_parse.y" /* yacc.c:1906  */


static void yyerror(char *s)
{
  fatal(&tcoord,"syntax error while building abstract syntax tree");
}
