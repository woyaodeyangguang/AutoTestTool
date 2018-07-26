%{
/*
**Lexical specification for HCC 1.0
**This code is based on various open resources, intented for educational
**purposes only. You can access, modify this for your personal use freely,
**but any attempts for comercial exploitation from this code are considered 
**unethical and should be discouraged.
*/
#include "c.h"
#include "parser.h"

//file under current compilation
extern char * file;

//column number and line number of current token
//Note that yylineno denotes the line of current token by default,
//but lineno takes the preprocessing pragmas into account
static int yycolno=1;
//static int lineno;

//current token value and coordinates
Tvalue tval;
Coordinate tcoord;

//helper routines

//check if IDENTIFIER is a type name
static int check_type();

//save the coordinate for current token
static void savecoord(void);
//static void printcoord(void);

//deal with C block comments
static void comment(void);

//adjust yycolno
static void advcol(void);

//parse line numbers in preprocessing pragmas
static int icon(void);

//integer parsing
static int parsehexint(void);
static int parseoctint(void);
static int parsedecint(void);
static int parseint(char *s, int len, int base);
static void setint(int tok, int overflow, unsigned int i[], int *l, int *h);

//floating point number
static int parsenumber(void);

//char literal
extern Type wchartype;
static int parsescapechar(char **p, int wide);
static int parsechar(void);

//string literal
static int parsestring(void);
static void expandstr(char **str, char carr[], int len);

//#define LEXER_DEBUG

#ifdef  LEXER_DEBUG
enum 
{
  DUMMYTOKEN = 256,
  #define TK(a,b) a,
  #include "token.h"
  #undef TK
};

static char * tokenstrs[] =
{
  #define TK(a,b) b,
  #include "token.h"
  #undef TK
};
#endif

%}

D                   [0-9]
L                   [a-zA-Z_.]
H                   [a-fA-F0-9]
E                   [Ee][+-]?{D}+
FS                  (f|F|l|L)
IS                  (u|U|l|L)*
C					[\u4e00-\u9fa5]
S					[^\x00-\xff]

%option noyywrap
%option yylineno

%x PRAGMA 
%x PRAGMA1 
%x PRAGMA2 
%x PRAGMA3 
%x PRAGMA4 
%x PRAGMA5 

%%

"auto"                  {savecoord(); advcol(); return (AUTO);}
"break"                 {savecoord(); advcol(); return (BREAK);}
"case"                  {savecoord(); advcol(); return (CASE);}
"char"                  {savecoord(); advcol(); return (CHAR);}
"String"                  {savecoord(); advcol(); return (CHAR);}
"const"                 {savecoord(); advcol(); return (CONST);}
"continue"              {savecoord(); advcol(); return (CONTINUE);}
"default"               {savecoord(); advcol(); return (DEFAULT);}
"do"                    {savecoord(); advcol(); return (DO);}
"double"                {savecoord(); advcol(); return (DOUBLE);}
"else"                  {savecoord(); advcol(); return (ELSE);}
"enum"                  {savecoord(); advcol(); return (ENUM);}
"extern"                {savecoord(); advcol(); return (EXTERN);}
"float"                 {savecoord(); advcol(); return (FLOAT);}
"for"                   {savecoord(); advcol(); return (FOR);}
"goto"                  {savecoord(); advcol(); return (GOTO);}
"if"                    {savecoord(); advcol(); return (IF);}
"int"                   {savecoord(); advcol(); return (INT);}
"long"                  {savecoord(); advcol(); return (LONG);}
"register"              {savecoord(); advcol(); return (REGISTER);}
"return"                {savecoord(); advcol(); return (RETURN);}
"short"                 {savecoord(); advcol(); return (SHORT);}
"signed"                {savecoord(); advcol(); return (SIGNED);}
"sizeof"                {savecoord(); advcol(); return (SIZEOF);}
"static"                {savecoord(); advcol(); return (STATIC);}
"struct"                {savecoord(); advcol(); return (STRUCT);}
"switch"                {savecoord(); advcol(); return (SWITCH);}
"typedef"               {savecoord(); advcol(); return (TYPEDEF);}
"union"                 {savecoord(); advcol(); return (UNION);}
"unsigned"              {savecoord(); advcol(); return (UNSIGNED);}
"void"                  {savecoord(); advcol(); return (VOID);}
"volatile"              {savecoord(); advcol(); return (VOLATILE);}
"while"                 {savecoord(); advcol(); return (WHILE);}
"null"                  {savecoord(); advcol(); tval.p = string("null"); return IDENTIFIER;}
{L}({L}|{D})*           {savecoord(); advcol(); 
                         tval.p = string(yytext); return IDENTIFIER;}


0[xX]{H}+{IS}?          {savecoord(); advcol(); return parsehexint();}
0{D}+{IS}?              {savecoord(); advcol(); return parseoctint();}
{D}+{IS}?               {savecoord(); advcol(); return parsedecint();}

{D}+{E}{FS}?            {savecoord(); advcol(); return parsenumber();}
"."{D}+({E})?{FS}?      {savecoord(); advcol(); return parsenumber();}
{D}+"."{D}*({E})?{FS}?  {savecoord(); advcol(); return parsenumber();}

L?'(\\.|[^\\'])+'       {savecoord(); advcol(); return parsechar();}
L?\"(\\.|[^\\"])*\"     {savecoord(); advcol(); return parsestring();}

"..."                   {savecoord(); advcol(); return (ELLIPSIS);}
">>="                   {savecoord(); advcol(); return (RIGHT_ASSIGN);}
"<<="                   {savecoord(); advcol(); return (LEFT_ASSIGN);}
"+="                    {savecoord(); advcol(); return (ADD_ASSIGN);}
"-="                    {savecoord(); advcol(); return (SUB_ASSIGN);}
"*="                    {savecoord(); advcol(); return (MUL_ASSIGN);}
"/="                    {savecoord(); advcol(); return (DIV_ASSIGN);}
"%="                    {savecoord(); advcol(); return (MOD_ASSIGN);}
"&="                    {savecoord(); advcol(); return (AND_ASSIGN);}
"^="                    {savecoord(); advcol(); return (XOR_ASSIGN);}
"|="                    {savecoord(); advcol(); return (OR_ASSIGN);}
">>"                    {savecoord(); advcol(); return (RIGHT_SHIFT);}
"<<"                    {savecoord(); advcol(); return (LEFT_SHIFT);}
"++"                    {savecoord(); advcol(); return (INC_OP);}
"--"                    {savecoord(); advcol(); return (DEC_OP);}
"->"                    {savecoord(); advcol(); return (PTR_OP);}
"&&"                    {savecoord(); advcol(); return (AND_OP);}
"||"                    {savecoord(); advcol(); return (OR_OP);}
"<="                    {savecoord(); advcol(); return (LE_OP);}
">="                    {savecoord(); advcol(); return (GE_OP);}
"=="                    {savecoord(); advcol(); return (EQ_OP);}
"!="                    {savecoord(); advcol(); return (NE_OP);}
";"                     {savecoord(); advcol(); return ';';}
("{"|"<%")              {savecoord(); advcol(); return '{';}
("}"|"%>")              {savecoord(); advcol(); return '}';}
","                     {savecoord(); advcol(); return ',';}
":"                     {savecoord(); advcol(); return ':';}
"="                     {savecoord(); advcol(); return '=';}
"("                     {savecoord(); advcol(); return '(';}
")"                     {savecoord(); advcol(); return ')';}
("["|"<:")              {savecoord(); advcol(); return '[';}
("]"|":>")              {savecoord(); advcol(); return ']';}
"."                     {savecoord(); advcol(); return '.';}
"&"                     {savecoord(); advcol(); return '&';}
"!"                     {savecoord(); advcol(); return '!';}
"~"                     {savecoord(); advcol(); return '~';}
"-"                     {savecoord(); advcol(); return '-';}
"+"                     {savecoord(); advcol(); return '+';}
"*"                     {savecoord(); advcol(); return '*';}
"/"                     {savecoord(); advcol(); return '/';}
"%"                     {savecoord(); advcol(); return '%';}
"<"                     {savecoord(); advcol(); return '<';}
">"                     {savecoord(); advcol(); return '>';}
"^"                     {savecoord(); advcol(); return '^';}
"|"                     {savecoord(); advcol(); return '|';}
"?"                     {savecoord(); advcol(); return '?';}

[ \t\v\n\f]+            {advcol();}

"/*"                    {comment();}

"//"[^\n]*"\n"          {yycolno = 1;}

"#"                          {yycolno++; BEGIN(PRAGMA);}
<PRAGMA>[ \t]*"include"      {savecoord(); 
                              fatal(&tcoord,"Running preprocessor before compiling the program"); 
                              BEGIN(0);}
<PRAGMA>[ \t]*"define"       {savecoord(); 
                              fatal(&tcoord,"Running preprocessor before compiling the program"); 
                              BEGIN(0);}
<PRAGMA>[ \t]+               {yycolno++; BEGIN(PRAGMA1);}
<PRAGMA1>{D}+                {yylineno = icon() - 1; yycolno++; BEGIN(PRAGMA2);}
<PRAGMA2>[ \t]+"\""          {yycolno++; BEGIN(PRAGMA3);}
<PRAGMA3>[a-zA-Z_\-\.<>]+    {file = string(yytext); BEGIN(PRAGMA4);}
<PRAGMA4>[^\n]+              {yycolno++; BEGIN(PRAGMA5);}
<PRAGMA5>"\n"                {yycolno=1; BEGIN(0);}

.                       {savecoord(); fatal(&tcoord,"Unknown character");}

%%

static int parsenumber(void)
{
  int tok;
  double v;
  char *p = yytext;

  while( isdigit(*p) ) p++;
  if(*p=='.') p++;
  while( isdigit(*p) ) p++;
  if(*p=='E' || *p=='e') {
    p++;
    if(*p=='+' || *p=='-')
      p++;
  }
  while( isdigit(*p) ) p++;

  errno = 0;
  v = strtod(yytext,NULL);
  if(errno == ERANGE)
    warning(&tcoord,"float constant overflow.");
  tval.d = v;

  tok = DOUBLECONST;
  if(*p == 'F' || *p == 'f'){
    p++;
    tval.f = (float)v;
    tok = FLOATCONST;
  }else if(*p == 'l' || *p == 'L') {
    p++;
    tok = LDOUBLECONST;
  }

  if(*p != 0)
    fatal(&tcoord,"invalid float constant");

  return tok;
}

static void expandstr(char **str, char carr[], int len)
{
  char *p;
  
  if(len<=0) 
    return;
  p = (char*)allocate(len+1);
  memcpy(p,(char*)carr,(size_t)len);
  p[len]=0;
  *str = p;
}

static int parsestring(void)
{
  char *p = yytext;
  int ch=0;
  int wide=0;
  char tchar[512];
  int maxlen = 511;
  int i = 0;
  char *str = NULL;

  if( *p == 'L' ) {
    warning(&tcoord,"attempting to use wide string.");
    p++; wide = 1;
  }

  assert(*p++ == '"');

  while(*p != '"') {
    ch = (*p == '\\')?parsescapechar(&p,wide) : *p++;
//    if(ch > 0xff)
//      fatal(&tcoord,"unsupported character in wide string constant");
    tchar[i++] = ch;
    if(i>=maxlen){
      expandstr(&str,tchar,i);
      i = 0;
    }
  }
  expandstr(&str,tchar,i);
  p++; //skip '"'

  if(i>0)
    tval.p = string(str);
  else
    tval.p = "";

  return STRING;
}

static int parsescapechar(char **s, int wide)
{
  unsigned v;
  unsigned maxlimit;
  char *p = *s;

  p++;
  switch(*p++) {
    case 'a': *s = p; return '\a';
    case 'b': *s = p; return '\b';
    case 'f': *s = p; return '\f';
    case 'n': *s = p; return '\n';
    case 'r': *s = p; return '\r';
    case 't': *s = p; return '\t';
    case 'v': *s = p; return '\v';

    case '\'':
    case '\"':
    case '\\':
    case '\?': *s = p; return *(p-1);

    case 'x':
      if(!ishexdigit(*p))
        fatal(&tcoord,"illegal escape sequence constant.");
      v = 0;
      while(ishexdigit(*p)) {
        if(isdigit(*p))
          v = (v<<4) + *p - '0';
        else v = (v<<4) + toupper(*p) - 'A' + 10;
        p++;
      }
      if(wide) {
        switch(wchartype.size) {
          case 1: maxlimit = 0xff; break;
          case 2: maxlimit = 0xffff; break;
          case 4: maxlimit = 0xffffffff; break;
          default: fatal(&tcoord,"wide char size is too large");
        }
      }else maxlimit = 0xff;

      if(v > maxlimit)
        fatal(&tcoord,"hexadecimal escape sequence too large.");
      *s = p;
      return v;

    case '0': case '1': case '2': case '3':
    case '4': case '5': case '6': case '7':
      v = *(p-1) - '0';
      if( isoctdigit(*p)) {
        v = (v<<3) + *p++ - '0';
        if( isoctdigit(*p)) 
          v = (v<<3) + *p++ - '0';
      }
      *s = p;
      return v;

    default: fatal(&tcoord,"unknown escape sequence.");
  }
  return 0;
}

static int parsechar(void)
{
  char *p = yytext;
  int ch=0;
  int wide=0;

  if( *p == 'L' ) {
    warning(&tcoord,"attempting to use wide char.");
    p++; wide = 1;
  }

  assert(*p++ == '\'');
  ch = (*p == '\\')?parsescapechar(&p,wide) : *p++;
  if(*p != '\'')
    fatal(&tcoord,"illegal char constant.");

  tval.i[0] = ch;
  tval.i[1] = 0;
  return INTCONST;
}

static void setint(int tok, int overflow, unsigned int i[], int *l, int *h)
{
  switch(tok) {
    case INTCONST: case LINT:
      if(overflow || i[1] || (i[0] & 0x80000000)) {
        *l = INT_MAX; *h = 0;
        warning(&tcoord,"Integer overflow");
      }else {
        *l = i[0]; *h = 0;
      }
      break;
    case UINT: case ULINT:
      if(overflow || i[1]) {
        *l = UINT_MAX; *h = 0;
        warning(&tcoord,"Unsigned integer overflow");
      }else {
        *l = i[0]; *h = 0;
      }
      break;
    case LLINT:
      if(overflow || (i[1] & 0x80000000)) {
        *l = 0xffffffff;
        *h = 0x7fffffff;
        warning(&tcoord,"Long long integer overflow");
      }else {
        *l = i[0];
        *h = i[1];
      } 
      break;
    case ULLINT:
      if(overflow) {
        *l = 0xffffffff;
        *h = 0xffffffff;
        warning(&tcoord,"unsigned long long integer overflow");
      }else {
        *l = i[0];
        *h = i[1];
      }
      break;
    default: assert(0);
  }
}

static int parseint(char *s, int len, int base)
{
  int tok;
  int overflow = 0;
  int d = 0;
  unsigned int i[2];
  unsigned long long v = 0ull;
  char * p = s;
  char * q = s + len;

  while (p < q) {
    if( (*p >= 'A' && *p <= 'F') || (*p >= 'a' && *p <= 'f') )
      d = toupper(*p) - 'A' + 10;
    else
      d = *p - '0';

    if(v >= ULLINT_MAX - (unsigned long long)d / (unsigned long long)base)
      overflow = 1;
    v = v*(unsigned long long)base+(unsigned long long)d;
    p++;
  }


  i[0] = (unsigned int)(v & (unsigned long long)0xffffffff);
  i[1] = (unsigned int)( (v >> 32) & (unsigned long long)0xffffffff);
  tok = INTCONST;

  if( *p == 'u' || *p == 'U' ) {
    p++;
    tok = UINT;
  }  

  if( *p == 'l' || *p == 'L' ) {
    p++;
    if(tok == INTCONST)
      tok = LINT;
    else if(tok == UINT)
      tok = ULINT;

    if( *p == 'l' || *p == 'L' ) {
      p++;
      if(tok == LINT)
        tok = LLINT;
      else if(tok == ULINT)
        tok = ULLINT;
    }
  }

  if(*p != 0)
    fatal(&tcoord,"Invalid integer constant specification: %s",yytext);

  //printf("tok: %s overflow: %d val: %d %d\n",tokenstrs[tok-DUMMYTOKEN-1],overflow,i[0],i[1]);
  setint(tok,overflow,i,&tval.i[0],&tval.i[1]);
  return tok;
}

static int parsedecint(void)
{
  char *p;

  p = yytext;
  while( isdigit(*p) ) p++;

  return parseint(yytext,p-yytext,10);
}

static int parseoctint(void)
{
  char *p, *s;

  s = p = yytext+1;
  while( isoctdigit(*p) ) p++;

  return parseint(s,p-s,8);
}

static int parsehexint(void)
{
  char *p, *s;

  s = p = yytext+2;

  while( ishexdigit(*p) ) p++;

  return parseint(s,p-s,16);
}

static void comment(void)
{
  char c, c1;

loop:
  while( (c=input()) != '*' && c!=0) {
    if( c== '\n') {
      yycolno = 1; 
    } else 
      yycolno ++;
    //putchar(c);
  }

  if( (c1=input()) != '/' && c!=0 ){
    unput(c1);
    goto loop;
  }

  if(c != 0) {
    //putchar(c1);
    yycolno += 2; 
  }
}

static void advcol(void)
{
  int i;
  for(i=0; yytext[i] != 0; i++)
    if( yytext[i] == '\n'){
      yycolno = 1;
    } else// if (yytext[i] == '\t')
      yycolno ++; //treat TAB as space
}

/*
**Parse the line number in preprocessing directives.
**Examples:
** # line 6 "C:\\path\\to\\header\\file.h" or
** # 6 "/path/to/header/file.h"
**Other directives are ignored 
*/

static int icon(void)
{
  int line;
  int i;

  line = 0;
  for(i=0; yytext[i] != 0; i++,yycolno++){
    assert(isdigit(yytext[i]));
    line = 10 * line + yytext[i] - '0';
  }
  return line;
}

static void savecoord(void)
{
  tcoord.file = file;
  tcoord.line = yylineno;
  tcoord.column = yycolno;
}

/*
static void printcoord(void)
{
  fprintf(stderr,"file: %s line: %d\n",tcoord.file,tcoord.line);
}
*/

static int check_type()
{
  if(check_typedef(yytext))
    return TYPENAME;

  return IDENTIFIER;
}

#ifdef LEXER_DEBUG
//Sample lexical inputs for test purposes

#if 0
/*
**Comments test
*/

//keywords
auto break case char const continue default do double
else enum extern float for /* more 
comments test*/goto if int long register return
short signed sizeof static struct
switch typedef union unsigned void
volatile
while

//identifiers
abcded, fjdkls;afds

//normal integer constants
0x1234ab
0X32cdef
0x123u
0x13adcbul
0x13adcbull
012345670
012345670ULL
1234567U

//overflow test
0xffffffff
0xffffffffu
0xfffffffffu
0xfffffffffll
0xffffffffffffffffll
0xffffffffffffffffull
0xfffffffffffffffffull

//floating point numbers
3e2
4e+4
738e-2f
738e-2F
738e-2l
738e-2Lf //pay special attention to this case
463724e-2
463724e-2f
.3243e2
.3243e2f
7932.213e-3l

//characters
't' 'N'
'\n'
'\r' '\a' '\v' '\f'
'\'' '\"' '\\' 
'\?'
'\034'
'\346'
'\x4f'
L'\n'

//string
"abcdefghdfadfefjdkas;lfjds"
"a\nbcd\tefg\rhdfadfefjdkas;lfjds"
L"abcdefghdfadfefjdkas;lfjds"

//multi-character tokens
"..."
">>="
"<<="
"+="
"-="
"*="
"/="
"%="
"&="
"|="
"^="
"|="
">>"
"<<"
"++"
"--"
"->"
"&&"
"||"
"<="
">="
"=="
"!="
#endif

#if 0
/*
**AD-HOC token.h for testing this lexer.
*/

#ifndef TK
#error "You must define the macro TK before including token.h"
#endif

/*TK(token,      name)*/
TK(AUTO,         "auto")
TK(BREAK,        "break")
TK(CASE,         "case")
TK(CHAR,         "char")
TK(CONST,        "const")
TK(CONTINUE,     "continue")
TK(DEFAULT,      "default")
TK(DO,           "do")
TK(DOUBLE,       "double")
TK(ELSE,         "else")
TK(ENUM,         "enum")
TK(EXTERN,       "extern")
TK(FLOAT,        "float")
TK(FOR,          "for")
TK(GOTO,         "goto")
TK(IF,           "if")
TK(INT,          "int")
TK(LONG,         "long")
TK(REGISTER,     "register")
TK(RETURN,       "return")
TK(SHORT,        "short")
TK(SIGNED,       "signed")
TK(SIZEOF,       "sizeof")
TK(STATIC,       "static")
TK(STRUCT,       "struct")
TK(SWITCH,       "switch")
TK(TYPEDEF,      "typedef")
TK(UNION,        "union")
TK(UNSIGNED,     "unsigned")
TK(VOID,         "void")
TK(VOLATILE,     "volatile")
TK(WHILE,        "while")
TK(IDENTIFIER,   "IDENTIFIER")
TK(INTCONST,     "integer")
TK(UINT,         "unsigned integer")
TK(LINT,         "long integer")
TK(ULINT,        "unsigned long integer")
TK(LLINT,        "long long integer")
TK(ULLINT,       "unsigned long long integer")
TK(DOUBLECONST,  "double const")
TK(LDOUBLECONST, "long double")
TK(FLOATCONST,   "float const")
TK(STRING,       "const string")
TK(ELLIPSIS,     "...")
TK(RIGHT_ASSIGN, ">>=")
TK(LEFT_ASSIGN,  "<<=")
TK(ADD_ASSIGN,   "+=")
TK(SUB_ASSIGN,   "-=")
TK(MUL_ASSIGN,   "*=")
TK(DIV_ASSIGN,   "/=")
TK(MOD_ASSIGN,   "%=")
TK(AND_ASSIGN,   "&=")
TK(XOR_ASSIGN,   "^=")
TK(OR_ASSIGN,    "|=")
TK(RIGHT_SHIFT,  ">>")
TK(LEFT_SHIFT,   "<<")
TK(INC_OP,       "++")
TK(DEC_OP,       "--")
TK(PTR_OP,       "->")
TK(AND_OP,       "&&")
TK(OR_OP,        "||")
TK(LE_OP,        "<=")
TK(GE_OP,        ">=")
TK(EQ_OP,        "==")
TK(NE_OP,        "!=")
/*TK(SEMI,         ";")*/
/*TK(LCURLY,       "{")*/
/*TK(RCURLY,       "}")*/
/*TK(COMMA,        ",")*/
/*TK(COLON,        ":")*/
/*TK(ASSIGN,       "=")*/
/*TK(LP,           "(")*/
/*TK(RP,           ")")*/
/*TK(LB,           "[")*/
/*TK(RB,           "]")*/
/*TK(DOT,          ".")*/
/*TK(AND,          "&")*/
/*TK(NOT,          "!")*/
/*TK(COMP,         "~")*/
/*TK(SUB,          "-")*/
/*TK(ADD,          "+")*/
/*TK(MUL,          "*")*/
/*TK(DIV,          "/")*/
/*TK(MOD,          "%")*/
/*TK(LESS,         "<")*/
/*TK(GREATER,      ">")*/
/*TK(XOR,          "^")*/
/*TK(OR,           "|")*/
/*TK(QUESTION,     "?")*/

#endif

static void input_init(char *f)
{
  file = f;
}

int main(int argc, char *argv[]) 
{
  char * infile;
  int tok;

  if(argc != 2){
    fprintf(stderr,"usage: hcc input-file-name.hcc\n");
    return 1;
  }

  input_init(argv[1]);
  infile = argv[1];
  if(!infile || freopen(infile, "r", stdin)==NULL) {
    fprintf(stderr,"%s: can not read file: '%s'\n", argv[0], infile);
    exit(1);
  } 

  while(1) {
    tok = yylex();
    
    if(tok == 0) break;

    if(tok < 256) {
      info(&tcoord,"%c",tok);
      continue;
    }

    switch(tok) {
      case AUTO: case BREAK: case CASE: case CHAR:
      case CONST: case CONTINUE: case DEFAULT: case DO:
      case DOUBLE: case ELSE: case ENUM: case EXTERN:
      case FLOAT: case FOR: case GOTO: case IF: case INT:
      case LONG: case REGISTER: case RETURN: case SHORT:
      case SIGNED: case SIZEOF: case STATIC: case STRUCT:
      case SWITCH: case TYPEDEF: case UNION: case UNSIGNED:
      case VOID: case VOLATILE: case WHILE: 
        info(&tcoord,"string token: %s",tokenstrs[tok-DUMMYTOKEN-1]);
        break;
      case IDENTIFIER:
        info(&tcoord,"identifier: %s",(char*)tval.p);
        break;
      case INTCONST:
        info(&tcoord,"const: %s val: %d",tokenstrs[tok-DUMMYTOKEN-1], tval.i[0]);
        break;
      case UINT:
        info(&tcoord,"const: %s val: %u",tokenstrs[tok-DUMMYTOKEN-1], tval.i[0]);
        break;
      case LINT:
        info(&tcoord,"const: %s val: %ld",tokenstrs[tok-DUMMYTOKEN-1],tval.i[0]);
        break;
      case ULINT:
        info(&tcoord,"const: %s val: %lu",tokenstrs[tok-DUMMYTOKEN-1],tval.i[0]);
        break;
      case LLINT:
        info(&tcoord,"const: %s val: %lld",tokenstrs[tok-DUMMYTOKEN-1],*((long long *)tval.i));
        break;
      case ULLINT:
        info(&tcoord,"const: %s val: %llu",tokenstrs[tok-DUMMYTOKEN-1],*((unsigned long long*)tval.i));
        break;
      case FLOATCONST:
        info(&tcoord,"const: %s val: %f",tokenstrs[tok-DUMMYTOKEN-1],tval.f);
        break;
      case DOUBLECONST:
        info(&tcoord,"const: %s val: %f",tokenstrs[tok-DUMMYTOKEN-1],tval.d);
        break;
      case LDOUBLECONST:
        info(&tcoord,"const: %s val: %f",tokenstrs[tok-DUMMYTOKEN-1],tval.d);
        break;
      case STRING:
        info(&tcoord,"const string: %s",(char*)tval.p);
        break;
      case ELLIPSIS:
        info(&tcoord,"multi-character token: ELLIPSIS");
        break;
      case RIGHT_ASSIGN:
        info(&tcoord,"multi-character token: RIGHT_ASSIGN");
        break;
      case LEFT_ASSIGN:
        info(&tcoord,"multi-character token: LEFT_ASSIGN");
        break;
      case ADD_ASSIGN:
        info(&tcoord,"multi-character token: ADD_ASSIGN");
        break;
      case SUB_ASSIGN:
        info(&tcoord,"multi-character token: SUB_ASSIGN");
        break;
      case MUL_ASSIGN:
        info(&tcoord,"multi-character token: MUL_ASSIGN");
        break;
      case DIV_ASSIGN:
        info(&tcoord,"multi-character token: DIV_ASSIGN");
        break;
      case MOD_ASSIGN:
        info(&tcoord,"multi-character token: MOD_ASSIGN");
        break;
      case AND_ASSIGN:
        info(&tcoord,"multi-character token: AND_ASSIGN");
        break;
      case XOR_ASSIGN:
        info(&tcoord,"multi-character token: XOR_ASSIGN");
        break;
      case OR_ASSIGN:
        info(&tcoord,"multi-character token: OR_ASSIGN");
        break;
      case RIGHT_SHIFT:
        info(&tcoord,"multi-character token: RIGHT_SHIFT");
        break;
      case LEFT_SHIFT:
        info(&tcoord,"multi-character token: LEFT_SHIFT");
        break;
      case INC_OP:
        info(&tcoord,"multi-character token: INC_OP");
        break;
      case DEC_OP:
        info(&tcoord,"multi-character token: DEC_OP");
        break;
      case PTR_OP:
        info(&tcoord,"multi-character token: PTR_OP");
        break;
      case AND_OP:
        info(&tcoord,"multi-character token: AND_OP");
        break;
      case OR_OP:
        info(&tcoord,"multi-character token: OR_OP");
        break;
      case LE_OP:
        info(&tcoord,"multi-character token: LE_OP");
        break;
      case GE_OP:
        info(&tcoord,"multi-character token: GE_OP");
        break;
      case EQ_OP:
        info(&tcoord,"multi-character token: EQ_OP");
        break;
      case NE_OP:
        info(&tcoord,"multi-character token: NE_OP");
        break;

      default: assert(0);
    }
  }

  deallocate();
  return 0;
}
#endif
