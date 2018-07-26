/* A Bison parser, made by GNU Bison 2.7.  */

/* Bison interface for Yacc-like parsers in C
   
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
/* Line 2058 of yacc.c  */
#line 22 "hcc.y"

  ASTBase *ast;


/* Line 2058 of yacc.c  */
#line 220 "parser.h"
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
