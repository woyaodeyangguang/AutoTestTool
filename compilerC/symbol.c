/*
**Symbol table management for HCC 1.0
**This code is based on various open resources, intented for educational
**purposes only. You can access, modify this for your personal use freely,
**but any attempts for comercial exploitation from this code are considered 
**unethical and should be discouraged.
*/

#include "c.h"
#include "parser.h"

/*
** symbol tables
** note we do not need tables for LABELs because LABELs only have function scope
*/
static Symtable symconsts = {SC_CONST};
static Symtable symids = {SC_GLOBAL};
static Symtable symtags = {SC_GLOBAL};
static Symtable symtypes = {SC_GLOBAL};

/* constants in current scope */
static Symtable *constbl = &symconsts;
/* identifiers in current scope */
static Symtable *idtbl = &symids;
/* tags in current scope */
static Symtable *tagtbl = &symtags;
/* types in current scope */
static Symtable *tytbl = &symtypes;

/* current scope */
static int scope = SC_GLOBAL;

/* total number of labels */
static unsigned labelnum;

/* global identifiers */
EXPORT List gids = {NULL,NULL};

/* all constant strings */
static long stringnum = 0;
EXPORT long tempvars = 0;
EXPORT List gstrs = {NULL,NULL};
EXPORT List fpconsts = {NULL,NULL};

/* current function declaration */
extern ASTFunctiondeclaration *curfunc;

static Symbol * symlookup(Symtable *tbl, char *name)
{
  Symbol *p;

  unsigned h = (unsigned long)name & (SYM_HASH_SIZE-1);
  do
    for(p = tbl->buckets[h]; p; p = p->link)
      if(p->symname == name)
        return p;
  while((tbl=tbl->prev) != NULL);  

  return NULL;
}

static void strinstall(Symtable *tbl, Symbol *sym)
{
  unsigned h = (unsigned long)sym->symval.p & (SYM_HASH_SIZE-1);

  sym->symscope = tbl->scope;
  sym->link = tbl->buckets[h];
  tbl->buckets[h] = sym;
}

static void syminstall(Symtable *tbl, Symbol *sym)
{
  unsigned h = (unsigned long)sym->symname & (SYM_HASH_SIZE-1);

  sym->symscope = tbl->scope;
  sym->link = tbl->buckets[h];
  tbl->buckets[h] = sym;
}

EXPORT Symbol * lookupid(char *name)
{
  return symlookup(idtbl, name);
}

EXPORT void installid(Symbol *sym)
{
  syminstall(idtbl,sym);
}

EXPORT Symbol *lookupty(char *typename)
{
  return symlookup(tytbl, typename);
}

EXPORT void installty(Symbol *tysym)
{
  syminstall(tytbl,tysym);
}

EXPORT Symbol *lookuptag(char *tagname)
{
  return symlookup(tagtbl, tagname);
}

EXPORT void installtag(char *name, Type *ty, Coordinate coord)
{
  Symbol *tagsym;

  NEW0(tagsym);
  tagsym->symclass = SYM_TAG;
  tagsym->symname = name;
  tagsym->symty = ty;
  tagsym->defined = 1;
  tagsym->coord = coord;

  syminstall(tagtbl,tagsym);
}

EXPORT void installenumconst(char *name, Type *ty, int enuval, Coordinate coord)
{
  Symbol *p;

  NEW0(p);
  p->symclass = SYM_ENUMCONST;
  p->symname = name;
  p->symty = ty;
  p->symval.i[0] = enuval;
  p->symval.i[1] = 0;
  p->defined = 1;
  p->coord = coord;

  syminstall(constbl,p);
}

static Symbol * installconst(int typeid, char *name, Tvalue val, int *found)
{
  Symbol * sym;
 
  if(found) 
    *found = 1;
  if( (sym = lookupconst(name)) == NULL ){
    if(found)
      *found = 0;
    NEW0(sym);
    //NEW0(sym->defuse);
    sym->symclass = SYM_CONST;
    sym->stclass = STATIC;
    sym->symname = name;
    sym->symty = gettype(typeid);
    sym->symval = val;
    sym->defined = 1;
    syminstall(constbl,sym);
  }
  return sym; 
}

EXPORT Symbol * installllconst(long long ival)
{
  char *name;
  Tvalue v;
  int h = (int)(ival >> 32);
  int l = (int)(ival & 0xffffffff);

  if(!h || h == -1) return installintconst(l);

  name = stringp(stringp("LL:",h),l);
  v.ll = ival;

  return installconst(LONGLONGTYPE,name,v,NULL);
}

EXPORT Symbol * installintconst(int ival)
{
  char *name;
  Tvalue v;

  name = stringp("Int:",ival);
  v.ll = 0ll;
  v.i[0] = ival;
  return installconst(INTTYPE,name,v,NULL);
}

EXPORT Symbol * installfltconst(float f)
{
  char name[256];
  Tvalue v;
  Symbol *sym;
  int found;

  memset(name,0,sizeof(name));
  sprintf(name,"Float%g",f);
  v.ll = 0ll;
  v.f = f;
  sym = installconst(FLOATTYPE,string(name),v,&found);
  if(!found)
    listappend(sym,&fpconsts);
  return sym;
}

EXPORT Symbol * installdblconst(double d)
{
  char name[256];
  Tvalue v;
  Symbol *sym;
  int found;

  memset(name,0,sizeof(name));
  sprintf(name,"Double%g",d);
  v.d = d;
  sym = installconst(DOUBLETYPE,string(name),v,&found);
  if(!found)
    listappend(sym,&fpconsts);
  return sym;
}

EXPORT void installtypedef(char *id, Type *ty, Coordinate coord)
{
  Symbol *p;

  NEW0(p);
  p->symclass = SYM_TYPENAME;
  p->symname = id;
  p->symty = ty;
  p->defined = 1;
  p->coord = coord;

  installty(p);
}

EXPORT Symbol * installfunc(char *funcname,Type *ty,int stclass,Coordinate coord)
{
  Symbol *p;

  NEW0(p);
  p->symclass = SYM_FUNCTION;
  p->symname = funcname;
  p->symty = ty;
  p->stclass = stclass;
  p->coord = coord;
  installid(p);
  return p;
}

EXPORT Symbol * installvar(char *varname, Type *ty, int stclass, int defined, Coordinate coord)
{
  Symbol *p;

  NEW0(p);
  //if(defined || ty->tyclass == ARRAYTYPE && ty->size )
  //  NEW0(p->defuse);
  p->symclass = SYM_VARIABLE;
  p->symname = varname;
  p->symty = ty;
  p->stclass = stclass;
  p->defined = defined;
  p->coord = coord;

  installid(p);
  if(p->symscope != SC_GLOBAL && p->stclass == STATIC)
    p->rname = formatname("%s.%d",p->symname,++tempvars);

  if(p->symscope == SC_GLOBAL || p->stclass == STATIC){
    listappend(p,&gids);
  }else if(p->symscope >= SC_LOCAL && p->stclass != EXTERN){
    assert(curfunc);
    listappend(p,&curfunc->lids);
  }
  return p;
}

EXPORT Symbol * blksym()
{
  Symbol *p;

  NEW0(p);
  p->symclass = SYM_LABEL;
  p->symname = formatname("BB%d",labelnum++);
  return p;
}

EXPORT Symbol * offsetsym(Symbol *b, int off, Type *ty)
{
  Symbol *sym;

  //if(!off)
  //  return b;

  NEW0(sym);
  if(b->symclass == SYM_OFFSET){
    off += sym->off;
    b = b->link;
  }
  sym->aliased = 1;
  sym->symclass = SYM_OFFSET;
  sym->symty = ty;
  sym->link = b;
  sym->off = off;
  sym->symname = formatname("%s[%d]",b->symname,off);
  b->ref++;

  return sym;
}

EXPORT Symbol * newtsym(Type *ty)
{
  Symbol *p;

  NEW0(p);
  p->symname = stringp("_TEMP",++tempvars);
  p->symclass = SYM_TEMP;
  p->symty = ty;

  return p;
}

EXPORT Symbol *lookupconst(char *strval)
{
  return symlookup(constbl, strval);
}

EXPORT Symbol * lookupstrconst(char *strval)
{
  Symbol *p;
  Symtable *tbl = constbl;

  unsigned h = (unsigned long)strval & (SYM_HASH_SIZE-1);
  do
    for(p = tbl->buckets[h]; p; p = p->link)
      if(p->symval.p == strval)
        return p;
  while((tbl=tbl->prev) != NULL);  

  return NULL;
}

EXPORT Symbol * installstrconst(Type *ty, char *val)
{
  Symbol *sym;

  NEW0(sym);
  //NEW0(sym->defuse);
  sym->symclass = SYM_STRING;
  sym->symname = stringp("_STR",stringnum++);
  //sym->symname = val;
  sym->symty = ty;
  sym->symval.p = (void*)val;
  sym->stclass = STATIC;
  strinstall(constbl,sym);

  listappend(sym,&gstrs);
  return sym;
}

EXPORT Symbol * lookuplab(char *labname)
{
  Listnode *p;
  List *l = &curfunc->labels;

  p = l->head;
  while(p){
    Symbol *sym = (Symbol*)p->data;
    if(sym->symname == labname)
      return (Symbol*)p->data;
    p = p->next;
  }
  return NULL;
}

EXPORT Symbol * installlab(char *labname, Coordinate coord, int defined, ASTLabeledstmt *stmt)
{
  Symbol *p;

  NEW0(p);
  p->symname = labname;
  p->defined = defined;
  p->coord = coord;
  p->deflabstmt = stmt;

  listappend(p,&curfunc->labels);
  return p;
}

EXPORT int curscope(void)
{
  return scope;
}

EXPORT void enterscope(void)
{
  Symtable *tbl;

  scope ++;
  /* create symbol tables for constants, tags, identifiers & types in current scope */
#define NEWTBL(tblname) \
  NEW0(tbl);            \
  tbl->scope = scope;   \
  tbl->prev = tblname;  \
  tblname = tbl;       

  NEWTBL(constbl);
  NEWTBL(idtbl);
  NEWTBL(tagtbl);
  NEWTBL(tytbl);
#undef NEWTBL
}

EXPORT void exitscope(void)
{
  scope --;
  constbl = constbl->prev;
  idtbl = idtbl->prev;
  tagtbl = tagtbl->prev;
  tytbl = tytbl->prev;
}
