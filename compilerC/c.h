#ifndef __C_H_
#define __C_H_

/*
**Common headers for HCC-1.0.
**This code is based on various open resources, intented for educational
**purposes only. You can access, modify this for your personal use freely,
**but any attempts for comercial exploitation from this code are considered 
**unethical and should be discouraged.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <assert.h>
#include <limits.h>
#include <errno.h>

/////////////////////////////////////////////GLOBAL MACROS////////////////////////////////////
#define EXPORT 
#define NELEMS(a) ((int)(sizeof (a)/sizeof ((a)[0])))
#define BITS(v,n) (n < 32 ? ( (v) & ((1<<(n))-1) ) : v )
#define MASKBITS(n) ( n < 32 ? (1<<(n))-1 : 0xffffffff )

/*
**Note: These neat macros are inspired from the Linux kernel source.
*/
/*
**offsetof - Get the offset of a member from a struct definition
**@TYPE:     the type of the structure
**@MEMBER:   the member we are interested
*/
#define offsetof(TYPE, MEMBER) ((size_t) & ((TYPE *)0)->MEMBER )

/**
 * container_of - cast a member of a structure out to the containing structure
 * @ptr:        the pointer to the member.
 * @type:       the type of the container struct this is embedded in.
 * @member:     the name of the member within the struct.
 *
 */

#define container_of(ptr, type, member) ({                      \
        const typeof( ((type *)0)->member ) *__mptr = (ptr);    \
        assert(__mptr != NULL);                                 \
        (type *)( (char *)__mptr - offsetof(type,member) );})

//#define container_of(ptr, type, member) (type*)( (char*)ptr - offsetof(type,member))

/*
** base_of  - get the base type given a derived type
** @deriv:    the derived type
*/
#define base_of(deriv) (&(deriv)->base)

/* we define an abstract list structure to hold arbitrary things */
typedef struct listnodetag {
  void *data;
  struct listnodetag *next, *prev;
}Listnode;

typedef struct listtag {
  Listnode *head;
  Listnode *tail;
}List;

typedef struct linecoordinate {
       int myline;
       int original;
} linecoord;

//WARNING: suppose less than 1024 lines in each Java file.
extern linecoord linenumbers[1024];
/////////////////////////////////C LEXICAL PROCESSING/////////////////////////////////////
//#define ULONG_MAX  (~0UL)
//#define LONG_MAX   (0x7fffffff)
//#define LONG_MIN   (-LONG_MAX-1)
#define ULLINT_MAX (~0ULL)

#define isdigit(c)     ( (c) >= '0' && (c) <= '9' )
#define ishexdigit(c)  ( isdigit(c) || ((c) >= 'A' && (c) <= 'F') || ((c) >= 'a' && (c) <= 'f') )
#define isoctdigit(c)  ( (c) >= '0' && (c) <= '7' )
#define toupper(c)     ( (c) & ~0x20 )
#define UBITS4(v)      ( (v) >> (8*sizeof(int) - 4) & 0xf )            
#define UBITS3(v)      ( (v) >> (8*sizeof(int) - 3) & 0x7 )
#define binop(op)      ( (op) == OR_OP || (op) == AND_OP || (op) == '|' || (op) == '&' || (op) == '^' ||\
                         (op) == EQ_OP || (op) == NE_OP || (op) == '>' || (op) == '<' || (op) == GE_OP ||\
                         (op) == LE_OP || (op) == RIGHT_SHIFT || (op) == LEFT_SHIFT || (op) == '+' ||\
                         (op) == '-'   || (op) == '*'         || (op) == '/' || (op) == '%' )
#define lintconst(op)   ( (op) == LLINT || (op) == ULLINT )
#define intconst(op)    ( (op) == INTCONST || (op) == UINT || (op) == LINT || (op) == ULINT )
#define fpconst(op)     ((op) == DOUBLECONST || (op) == LDOUBLECONST || (op) == FLOATCONST)
#define constop(op)     ( intconst(op) || lintconst(op) || fpconst(op) || (op) == STRING)
#define unaryop(op)    ( (op) == '+' || (op) == '-' || (op) == '~' )

/* coordinates in the source file */
typedef struct
{
  char * file;
  int line, column;
} Coordinate;

/* Token value representation */
typedef union
{
  //to take 64 bit long integers into consideration
  int i[2];
  long long ll;
  float f;
  double d;
  void * p;
} Tvalue;

extern int yylex(void);
extern int yyparse(void);
///////////////////////////////////////C TYPE SYSTEM/////////////////////////////////////
#define chartype(ty) ((ty)->tyclass == CHARTYPE || (ty)->tyclass == UCHARTYPE)
#define scalartype(ty) ((ty)->tyclass <= POINTERTYPE)
#define scalarsize(ty) (ty->size == 1 || ty->size == 2 || ty->size == 4 || ty->size == 8)
#define structuniontype(ty) ((ty)->tyclass == UNIONTYPE || (ty)->tyclass == STRUCTTYPE)
#define unsignedtype(ty) (ty->tyclass & 0x1)
#define arithtype(ty) ((ty)->tyclass <= LONGDOUBLETYPE)
#define qualable(lty,rty) ( (lty->qual & rty->qual) == rty->qual )
#define funcptr(ty) ( ty->tyclass == POINTERTYPE && ty->bty->tyclass == FUNCTIONTYPE )
#define functype(ty) ( ty->tyclass == FUNCTIONTYPE)
#define voidptr(ty) ( ty->tyclass == POINTERTYPE && ty->bty->tyclass == VOIDTYPE )
#define voidtype(ty) (ty->tyclass == VOIDTYPE)
#define objectptr(ty) ( ty->tyclass == POINTERTYPE && ty->bty->size != 0 && ty->bty->tyclass != FUNCTIONTYPE )
#define incompleteptr(ty) (ty->tyclass == POINTERTYPE && ty->bty->size == 0)
#define pointertype(ty) ( ty->tyclass == POINTERTYPE )
#define arraytype(ty) ( ty->tyclass == ARRAYTYPE)
#define integertype(ty) ( ty->tyclass <= ENUMTYPE )
#define fptype(ty) ( ty->tyclass >= FLOATTYPE && ty->tyclass <= LONGDOUBLETYPE)
#define ALIGN(size,align) ( ((size) + (align) - 1) & (~( (align) - 1)))

//type size configuration
#define CHAR_SIZE        1
#define SHORT_SIZE       2
#define INT_SIZE         4
#define LONG_SIZE        4
#define LONG_LONG_SIZE   8
#define FLOAT_SIZE       4
#define DOUBLE_SIZE      8
#define LONG_DOUBLE_SIZE 8

/* type qualifiers */
enum 
{
  STC_CONST = 0x1,
  STC_VOLATILE = 0x2,
};

/* type codes */
enum
{
  I1,U1,I2,U2,I4,U4,I8,U8,F4,F8,V,B,TYPECODES,
};

/* type categories */
enum
{
  /* 0*/CHARTYPE,
  /* 1*/UCHARTYPE,
  /* 2*/SHORTTYPE,
  /* 3*/USHORTTYPE,
  /* 4*/INTTYPE,
  /* 5*/UINTTYPE,
  /* 6*/LONGTYPE,
  /* 7*/ULONGTYPE,
  /* 8*/LONGLONGTYPE,
  /* 9*/ULONGLONGTYPE,
  /*10*/ENUMTYPE,
  /*11*/FLOATTYPE,
  /*12*/DOUBLETYPE,
  /*13*/LONGDOUBLETYPE,
  /*14*/POINTERTYPE,
  /*15*/VOIDTYPE,
  /*16*/UNIONTYPE,
  /*17*/STRUCTTYPE,
  /*18*/ARRAYTYPE,
  /*19*/FUNCTIONTYPE,
  /*20*/TOTALTYPES
};

/* type representation */
typedef struct typebase
{
  int tyclass;
  int qual;
  int align;
  int size;
  struct typebase * bty;
} Type;

typedef struct paramtypetag
{
  Type *ty;
  char *name;
  int inreg;
  Coordinate coord;
  struct paramtypetag *next;
} Parameter;

typedef struct functypetag
{
  Type base;
  int hasproto;
  int hasellipsis;
  Parameter * params;
  Parameter **paramtail;
}Functype;

typedef struct enumtypetag
{
  Type base;
  char *name;
}Enumtype;

typedef struct fieldtag
{
  Type *ty;
  int offset;
  char *name;
  int bits;
  int pos;
  int bitfield;
  struct fieldtag *next;
} Field;

typedef struct sutypetag
{
  Type base;
  char *name;
  Field *fields;
  Field **fldtail;
  int hasconst;
  int hasflexarray;
}SUtype;

//used to store user defined type names
typedef struct usertypename
{
  char *tyname;
  int scope;
  int shadow;
  struct usertypename *next;
}Typename;

//exported procedures
extern void inittypes(void);
extern Type * gettype(int tyid);
extern Type * getdummyfunc(void);
extern Type * qual(int qual, Type *ty);
extern Type *arrayof(int len, Type *bty);
extern Type *enumof(char *id);
extern Type *structunionof(char *name, int tyclass);
extern int typecode(Type *ty);
extern Type * commonarithtype(Type *ty1, Type *ty2);
extern void structunion(Type *ty);
extern void installfld(Type *ty, char *fldname, Type *fldty, int bits, int bitfield);
extern Field * lookupfld(SUtype *ty, char *name);
extern Type *pointerto(Type *bty);
extern Type *makepointer(Type *ty);
extern Type * qualify(int qual, Type *ty);
extern Type *composetypes(Type *ty1, Type *ty2);
extern Type * unqual(Type *ty);
extern int check_typedef(char *id);
extern int compatibletypes(Type *ty1, Type *ty2);

////////////////////////////////SYMBOL TABLE MANAGEMENT/////////////////////////////

/* C symbol scope */
enum
{
  SC_CONST,
  SC_LABEL,
  SC_GLOBAL,
  SC_PARAM,
  SC_LOCAL,
};

/* various kinds of symbols */
enum
{
  SYM_TAG,
  SYM_TYPENAME,
  SYM_ENUMCONST,
  SYM_CONST,
  SYM_VARIABLE,
  SYM_TEMP,
  SYM_STRING,
  SYM_LABEL,
  SYM_FUNCTION,
  SYM_OFFSET,
  SYM_REG,
  SYM_IREG,
};

/* the symbol data structure */
struct astinitializer;
//struct defusechaintag;
struct labelstmt;
struct irtag;
typedef struct symboltag
{
  int symclass;
  int stclass;
  int ref, off;
  char *symname;
  char *aname;
  char *rname;
  int symscope;
  Type *symty;
  Tvalue symval;
  int defined;
  int aliased, dirty;
  Coordinate coord;
  List irdata;
  List iruses;
  struct symboltag *reg, *lvalsym;
  //struct defusechaintag *defuse;
  struct irtag *ir;
  struct labelstmt *deflabstmt;
  /* next symbol in the same bucket */
  struct symboltag *link, *next;
}Symbol;

/* symbol table */
typedef struct symtable
{
  int scope;
  struct symtable *prev;
  Symbol *buckets[256];
}Symtable;
#define SYM_HASH_SIZE NELEMS(((Symtable*)0)->buckets)

//exported symbol management routines
extern Symbol * lookuplab(char *labname);
extern Symbol * lookupid(char *name);
extern Symbol *lookupty(char *type_name);
extern Symbol *lookuptag(char *tagname);
extern void installid(Symbol *sym);
extern void installty(Symbol *tysym);
extern Symbol * installlab(char *labname, Coordinate coord, int defined, struct labelstmt *stmt);
extern void installtag(char *name, Type *ty, Coordinate coord);
extern void installenumconst(char *name, Type *ty, int enuval, Coordinate coord);
extern void installtypedef(char *id, Type *ty, Coordinate coord);
extern Symbol * installfunc(char *funcname, Type *ty, int stclassm, Coordinate coord);
extern Symbol * installvar(char *varname, Type *ty, int stclass, int defined, Coordinate coord);
extern Symbol * installstrconst(Type *ty, char *val);
extern Symbol * installintconst(int ival);
extern Symbol * installdblconst(double d);
extern Symbol * installfltconst(float f);
extern Symbol * installllconst(long long ival);
extern Symbol *lookupconst(char *strval);
extern Symbol * lookupstrconst(char *strval);
extern Symbol * newtsym(Type *ty);
extern Symbol * offsetsym(Symbol *b, int off, Type *ty);
extern Symbol * blksym();
extern int curscope(void);
extern void enterscope(void);
extern void exitscope(void);
extern void listremove(void *data, List *l);
extern void listappend(void *data, List *l);
extern void listinsert(void *data, List *l);
extern void listappendsorted(void *sym, List *l, void *cmp);
extern void listmodify(List *l, void *origdata, void *newdata);
extern void listrmtail(List *l);
extern char * formatname(char *fmt, ...);

////////////////////////////////ABSTRACT SYNTAX TREE////////////////////////////////
//various tree types
enum
{
  AST_TRANSLATIONUNIT,
  AST_DECLARATION,
  AST_SPECIFIER,
  AST_STRUCTSPECIFIER,
  AST_UNIONSPECIFIER,
  AST_ENUMSPECIFIER,
  AST_ARRAYDECLARATOR,
  AST_FUNCTIONDECLARATOR,
  AST_POINTERDECLARATOR,
  AST_DECLARATOR,
  AST_ABSTRACTDECLARATOR,
  AST_INITDECLARATOR,
  AST_INITIALIZER,
  AST_FUNCTION,
  AST_ATOM,
  AST_ENUMERATOR,
  AST_EXPRESSION,
  AST_STRUCTDECLARATION,
  AST_STRUCTDECLARATOR,
  AST_PARAMTYPELIST,
  AST_PARAMDECLARATION,
  AST_TYPENAME,

  AST_COMPOUNDSTMT /*22*/,
  AST_LABELEDSTMT /*23*/,
  AST_EXPRESSIONSTMT /*24*/,
  AST_SELECTIONSTMT /*25*/,
  AST_ITERATIONSTMT /*26*/,
  AST_JUMPSTMT,
};

typedef struct astbase 
{
  int astclass;
  Coordinate coord;
  struct astbase *next;
  /* used to denote whether there is a parenthesis */
  /* only for AST checking, shall be removed shortly */
  int has_paren;
}ASTBase;

typedef struct astspecifier
{
  ASTBase base;
  ASTBase *sclass;
  ASTBase *qual;
  ASTBase *typespecs;
  int stclass;
  Type *ty;
}ASTSpecifier;

typedef struct astatom
{
  ASTBase base;
  int tok;
  Tvalue tval;
}ASTAtom;

typedef struct asttypename
{
  ASTBase base;
  ASTSpecifier *spec;
  ASTBase *dec;
}ASTTypename;

typedef struct astexpression
{
  ASTBase base;
  Type *ty;
  Tvalue val;
  ASTTypename *tyname;
  struct astexpression *kids[3];
  int op, unary, isfunc, lvalue;
  int bitfield, inreg, isarray;
}ASTExpression;

typedef struct astcmpdstmt
{
  ASTBase base;
  ASTBase *declist;
  ASTBase *stmtlist;
  List locals;
}ASTCmpdstmt;

/*
**types of labeled statement
*/
enum 
{
  IDLABEL,
  CASELABEL,
  DEFAULTLABEL,
};

struct bbtag;
typedef struct labelstmt
{
  ASTBase base;
  ASTBase *stmt;
  void *idexpr;
  int type;
  //for IR generation
  struct bbtag *labelblk;
}ASTLabeledstmt;

typedef struct astexprstmt
{
  ASTBase base;
  ASTExpression *expr;
}ASTExprstmt;

/*
**types of selection statements
*/
enum
{
  IFSTMT,
  IFELSESTMT,
  SWITCHSTMT,
};

struct switchbkttag;
typedef struct astselstmt
{
  ASTBase base;
  ASTExpression *expr;
  ASTBase *truestmt;
  ASTBase *falsestmt;
  int type;
  //switch statement fields
  List cases;
  ASTLabeledstmt *defaultstmt; 
  // for IR generation
  int nbkt;
  struct bbtag *defblk, *cvblk;
  struct switchbkttag *bkts;
}ASTSelstmt;

/*
**types of iteration statement
*/
enum
{
  WHILESTMT,
  DOSTMT,
  FORSTMT,
};
typedef struct astiterationstmt
{
  ASTBase base;
  ASTExpression *expr;
  ASTBase *stmt;
  ASTExprstmt *exprstmt[2];
  int type;
  // for IR generation
  struct bbtag *bodyblk, *condblk, *forblk, *cvblk;
}ASTIterationstmt;

/*
**types for jump statements
*/
enum
{
  GOTOSTMT,
  CONTINUESTMT,
  BREAKSTMT,
  RETURNSTMT,
};
typedef struct astjumpstmt
{
  ASTBase base;
  void *idexpr;
  int type;
  //used by goto/continue/break
  ASTBase *tgtstmt;
}ASTJumpstmt;

typedef struct asttranslationunit
{
  ASTBase base;
  ASTBase * extdecls;
}ASTTranslationunit;

typedef struct astdeclaration
{
  ASTBase base;
  ASTSpecifier *specs;
  ASTBase * initdecls;
} ASTDeclaration;

typedef struct aststructdeclaration
{
  ASTBase base;
  ASTSpecifier * specs;
  ASTBase * stdecls;
} ASTStructdeclaration;

typedef struct aststructdeclarator
{
  ASTBase base;
  ASTBase *dec;
  ASTExpression *cexpr;
} ASTStructdeclarator;

typedef struct astdeclarator
{
  ASTBase base;
  char *name;
  Type *ty;
}ASTDeclarator;

typedef struct astinitializer
{
  ASTBase base;
  int lbrace;
  union {
    ASTBase *initials;
    ASTExpression *expr;
  }u;
}ASTInitializer;

typedef struct astinitdeclarator
{
  ASTBase base;
  ASTBase *dec;
  ASTInitializer *init;
}ASTInitdeclarator;

typedef struct astpointerdeclarator
{
  ASTBase base;
  char *name;
  Type *ty;
  ASTBase *dec;
  ASTBase *tyquals;
}ASTPointerdeclarator;

typedef struct astarraydeclarator
{
  ASTBase base;
  char *name;  
  Type *ty;
  ASTBase *decbase;
  ASTExpression *cexpr;
}ASTArraydeclarator;

typedef struct astparamtype
{
  ASTBase base;
  ASTBase *paramdecls;
  int ellipsis;
}ASTParamtypelist;

typedef struct astparamdeclaration
{
  ASTBase base;
  ASTSpecifier * specs;
  ASTBase * dec;
}ASTParamdeclaration;

typedef struct astfunctiondeclarator
{
  ASTBase base;
  char *name;
  Type *ty;
  ASTBase *basedec;
  ASTBase *idlist;
  ASTParamtypelist* paramtypelist;
}ASTFunctiondeclarator;

typedef struct astfunctiondeclaration
{
  ASTBase base;
  ASTSpecifier *specs;
  ASTBase *dec;
  ASTBase *paramdecls;
  ASTCmpdstmt *stmt;
  Symbol *sym;
  List labels;
  List lids;
  List params;
  List sws;
  List loops;
  List brks;
  int hasreturn;
} ASTFunctiondeclaration; 

typedef struct astenumerator
{
  ASTBase base;
  ASTAtom *id;
  ASTExpression *cexpr;
}ASTEnumerator;

typedef struct astenumspecifier
{
  ASTBase base;
  ASTAtom *id;
  ASTBase * enumerators;
} ASTEnumspecifier;

typedef struct astsuspecifier
{
  ASTBase base;
  ASTAtom *id;
  ASTBase *sudecls;
}ASTSUSpecifier;

//exported routines for AST construction
extern ASTTranslationunit * create_translationunit(ASTBase* extdecls);
extern ASTBase * append_astnode(ASTBase *astlist, ASTBase *astnode);
extern ASTDeclaration * create_declaration(ASTBase *specs, ASTBase *initdecls);
extern ASTFunctiondeclaration * create_functiondeclaration(ASTBase *specsbase,
                       ASTBase *decbase, ASTBase *declist, ASTBase *stmtbase); 
extern ASTSpecifier * create_declarationspecifier1(ASTBase *sclass);
extern ASTSpecifier * create_declarationspecifier2(ASTBase *sclass, ASTBase * specbase);
extern ASTSpecifier * create_declarationspecifier3(ASTBase *tyspec);
extern ASTSpecifier * create_declarationspecifier4(ASTBase *tyspec, ASTBase * specbase);
extern ASTSpecifier * create_declarationspecifier5(ASTBase *tyqual);
extern ASTSpecifier * create_declarationspecifier6(ASTBase *tyqual, ASTBase * specbase);
extern ASTAtom * create_atom(int tok, Tvalue tval, Coordinate coord);
extern ASTEnumspecifier * create_enumspec(ASTBase *enumatom, ASTBase *id,ASTBase *enumerators);
extern ASTSUSpecifier * create_structorunion(ASTBase *subase, ASTBase *id, ASTBase *decls);
extern ASTStructdeclaration *create_structdeclaration(ASTBase *specs, ASTBase *decls);
extern ASTStructdeclarator * create_structdeclarator(ASTBase *decbase, ASTBase *cexprbase);
extern ASTPointerdeclarator * chain_pointerdeclarator(ASTBase *pbase, ASTBase *directbase);
extern ASTPointerdeclarator * create_pointerdeclarator(Coordinate coord, ASTBase *tyquals, 
                                                       ASTBase *pdeclistbase);
extern ASTDeclarator * create_directdeclarator(ASTBase *idbase);
extern ASTDeclarator * create_abstractdeclarator(Coordinate coord);
extern ASTArraydeclarator * create_arraydeclarator(ASTBase *decbase, ASTBase *exprbase);
extern ASTFunctiondeclarator *create_funcdeclarator(ASTBase *dec,
                  ASTBase *paramtypesbase, ASTBase *paramidsbase);
extern ASTParamtypelist * create_paramtypelist(ASTBase *paramlist, int ellipsis);
extern ASTParamdeclaration * create_paramdeclaration(ASTBase *specsbase, ASTBase *decsbase);
extern ASTInitdeclarator * create_initdeclarator(ASTBase *dec, ASTBase *init);
extern ASTInitializer * create_initializer(int lbrace,ASTBase * base);
extern ASTExpression * create_binaryexpression(int op, ASTBase *l, ASTBase *r);
extern ASTExpression * create_binaryexpression1(ASTBase * op, ASTBase *l, ASTBase *r);
extern ASTExpression * create_unaryexpression(ASTBase *op, ASTBase *expr);
extern ASTExpression * create_unaryexpression1(ASTBase *op, ASTBase *tyname);
extern ASTTypename * create_typename(ASTBase *specbase, ASTBase *dec);
extern ASTExpression * create_castexpression(int op,ASTBase *tyname, ASTBase *expr);
extern ASTExpression * create_postfixexpression(int op,ASTBase *expr1, ASTBase *expr2);
extern ASTExpression * create_postfixexpression_login(ASTBase *expr2);

extern ASTExpression *create_primaryexpression(ASTBase *atombase);
extern ASTExpression *create_conditionalexpression(int op, ASTBase *cond, ASTBase *l, ASTBase *r);
extern ASTCmpdstmt *create_compoundstmt(Coordinate coord, ASTBase *declist, ASTBase *stmtlist);
extern ASTLabeledstmt *create_labelstmt(int labeltype, Coordinate coord, ASTBase *expr, ASTBase *stmt);
extern ASTExprstmt *create_exprstmt(Coordinate coord, ASTBase *exprbase);
extern ASTSelstmt *create_selstmt(int type, Coordinate coord, ASTBase *ebase, ASTBase *tstmt, ASTBase *fstmt);
extern ASTIterationstmt *create_iterationstmt(int type, Coordinate coord,
                  ASTBase *exprbase, ASTBase *stmt, ASTBase *exprstmt1, ASTBase *exprstmt2);
extern ASTJumpstmt * create_jumpstmt(int type, Coordinate coord, ASTBase *p);
extern ASTEnumerator * create_enumerator(ASTBase *id, ASTBase *cexprbase);

//exported routines for symantic checks of the abstract syntax tree
extern void astecho(void);
extern void astchk(void);
extern ASTExpression * foldconst(ASTExpression *expr);

#define BUILTIN 55
extern char* builtin[BUILTIN];
extern int found_builtin(char* in);
////////////////////////////////////INTERMEDIATE CODE GENERATION//////////////////////////////////
#define branchop(op) (op >= JZ && op <= IJMP)
enum 
{
  #define IRCODE(a,b) a,
  #include "ircode.h"
  #undef IRCODE
  IRCODES,
};

typedef struct initdata
{
  Type *ty;
  int offset,pos,size;
  int bitfield, lastfld;
  ASTExpression *expr;
}Initdata;

typedef struct irargtag
{
  Type *ty;
  Symbol *sym;
  struct irargtag *next;
}IRArg;

struct bbtag;
typedef struct irtag
{
  int op,ijmps;
  Type *ty;
  void *opr[3];  
  struct irtag *prev, *next;
  struct bbtag *blk;
}IR;

typedef struct bbtag
{
  struct bbtag *prev, *next;
  List takentgts, jmpsrcs;
  IR *irhead, *irtail;
  int nir,nref;
  Symbol *sym;
}BBlock;

/*
typedef struct defusechaintag
{
  IR *def;
  List uses;
  struct defusechaintag *next;
}Defuse;
*/

typedef struct IRnodetag
{
  IR *ir;
  struct IRnodetag *link;  
}IRNode;

typedef struct funcirtag
{
  BBlock *bblist;
  Symbol *sym;
  BBlock *cvblk;
  Symbol *retsym;
  List params;
  List lids;
}Funcir;

typedef struct switchbkttag
{
  int ncases;
  int min, max;
  List cases;
  struct switchbkttag *prev;
} Switchbkt;

#define hasdef(s) !(s->symclass == SYM_CONST || \
                  s->symclass == SYM_STRING && s->stclass == STATIC)
//////////////////////////////////////////EXPORTED ROUTINES///////////////////////////////////////
extern void instmodify(BBlock *blk, BBlock *oldblk, BBlock *newblk);
extern void irgen(char* inputfile, char* outputfile, char* testclass, char* module);
extern void optimize(Funcir *fir);
extern void irecho(void);
extern void x86gen(void);

////////////////////////////////MISCELANEOUS EXPORTED ROUTINES////////////////////////////////////
//error handling
extern void fatal(Coordinate * coord, const char * format , ...);
extern void warning(Coordinate * coord, const char * format , ...);
extern void info(Coordinate * coord, const char * format , ...);
extern void emit(const char * format , ...);
extern void emitln(const char * format , ...);
extern void emitstr(const char *str);
extern void emitchar(const char c);

//string operations
extern char *stringd(long n);
extern char *string(const char *str);
extern char *stringp(const char *prefix, long n); 
extern char *stringn(const char *str, int len);

/////////////////////////////////Memory Management STUFF////////////////////////////////////////
extern void deallocate();
extern void *allocate(unsigned long n);
#undef roundup
#define roundup(x,n) (((x)+((n)-1))&(~((n)-1)))
#define NEW(p) ((p) = allocate(sizeof *(p)))
#define NEW0(p) memset(NEW((p)), 0, sizeof *(p))

#endif
