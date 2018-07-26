/*
**Type manipulations for HCC 1.0
**This code is based on various open resources, intented for educational
**purposes only. You can access, modify this for your personal use freely,
**but any attempts for comercial exploitation from this code are considered 
**unethical and should be discouraged.
*/
#include "c.h"

//static Type * unqual(Type *ty);

static Type types[TOTALTYPES];
EXPORT Type *dummyfunctype;
EXPORT Type wchartype;

static void bldinstallty(char *name, int scope, Type *ty, int defined)
{
  Symbol *tysym;

  NEW0(tysym);
  tysym->symname = name;
  tysym->symclass = SYM_TYPENAME;
  tysym->symscope = scope;
  tysym->symty = ty;
  tysym->defined = defined;
  
  installty(tysym);
}

EXPORT void inittypes(void)
{
  int i;
  Functype *fty;

  /* initialize basic types */
  types[CHARTYPE].size = types[UCHARTYPE].size = CHAR_SIZE;
  types[SHORTTYPE].size = types[USHORTTYPE].size = SHORT_SIZE;
  types[INTTYPE].size = types[UINTTYPE].size = INT_SIZE;
  types[LONGTYPE].size = types[ULONGTYPE].size = INT_SIZE;
  types[LONGLONGTYPE].size = types[ULONGLONGTYPE].size = LONG_LONG_SIZE;
  types[FLOATTYPE].size = FLOAT_SIZE;
  types[DOUBLETYPE].size = DOUBLE_SIZE;
  types[LONGDOUBLETYPE].size = LONG_DOUBLE_SIZE;
  types[ENUMTYPE].size = INT_SIZE;
  types[POINTERTYPE].size = INT_SIZE;

  for(i=0;i<TOTALTYPES;i++){
    types[i].tyclass = i;
    types[i].align = types[i].size;
  }
  
  /* insert basic types into type symbol table */
  bldinstallty(string("char"),SC_GLOBAL,&types[CHARTYPE],1);
  bldinstallty(string("unsigned char"),SC_GLOBAL,&types[UCHARTYPE],1);
  bldinstallty(string("short"),SC_GLOBAL,&types[SHORTTYPE],1);
  bldinstallty(string("unsigned short"),SC_GLOBAL,&types[USHORTTYPE],1);
  bldinstallty(string("int"),SC_GLOBAL,&types[INTTYPE],1);
  bldinstallty(string("unsigned int"),SC_GLOBAL,&types[INTTYPE],1);
  bldinstallty(string("long"),SC_GLOBAL,&types[LONGTYPE],1);
  bldinstallty(string("unsigned long"),SC_GLOBAL,&types[ULONGTYPE],1);
  bldinstallty(string("long long"),SC_GLOBAL,&types[LONGLONGTYPE],1);
  bldinstallty(string("unsigned long long"),SC_GLOBAL,&types[ULONGLONGTYPE],1);
  bldinstallty(string("float"),SC_GLOBAL,&types[FLOATTYPE],1);
  bldinstallty(string("double"),SC_GLOBAL,&types[DOUBLETYPE],1);
  bldinstallty(string("long double"),SC_GLOBAL,&types[LONGDOUBLETYPE],1);
  bldinstallty(string("pointer"),SC_GLOBAL,&types[POINTERTYPE],1);
  bldinstallty(string("void"),SC_GLOBAL,&types[VOIDTYPE],1);

  /*initialize wchar type */
  wchartype = types[CHARTYPE];
  bldinstallty(string("wide char"),SC_GLOBAL,&wchartype,1);
  
  NEW0(fty);
  fty->base.tyclass = FUNCTIONTYPE;
  fty->base.align = fty->base.size = types[POINTERTYPE].size;
  fty->base.bty = &types[INTTYPE];
  dummyfunctype = &fty->base;
  bldinstallty(string("dummy function"),SC_GLOBAL,dummyfunctype,1);
}

EXPORT int typecode(Type *ty)
{
  static int typecodes[] = {I1,U1,I2,U2,I4,U4,I4,U4,I8,U8,I4,F4,F8,F8,U4,V,B,B,B};
  assert(!functype(ty));
  return typecodes[ty->tyclass];
}

EXPORT Type * commonarithtype(Type *ty1, Type *ty2)
{
  if(ty1->tyclass == LONGDOUBLETYPE || ty2->tyclass == LONGDOUBLETYPE)
    return gettype(LONGDOUBLETYPE);

  if(ty1->tyclass == DOUBLETYPE || ty2->tyclass == DOUBLETYPE)
    return gettype(DOUBLETYPE);

  if(ty1->tyclass == FLOATTYPE || ty2->tyclass == FLOATTYPE)
    return gettype(FLOATTYPE);

  ty1 = ty1->tyclass < INTTYPE ? gettype(INTTYPE) : ty1;
  ty2 = ty2->tyclass < INTTYPE ? gettype(INTTYPE) : ty2;
  if(ty1->tyclass == ty2->tyclass)
    return ty1;
  if(unsignedtype(ty1) == unsignedtype(ty2))
    return ty1->tyclass > ty2->tyclass ? ty1 : ty2;

  if(unsignedtype(ty1)){
    Type *ty;

    ty = ty1;
    ty1 = ty2;
    ty2 = ty;
  }

  if(ty1->tyclass >= ty2->tyclass)
    return ty1;

  if(ty1->size < ty2->size)
    return ty2;

  return gettype(ty2->tyclass + 1);
}

/* build a struct/union type */
EXPORT Type *structunionof(char *name, int tyclass)
{
  SUtype *ty;

  NEW0(ty);
  ty->base.tyclass = tyclass;
  ty->name = name;
  ty->fldtail = &ty->fields;
  
  return &ty->base;
}

/* adjust offset for anonymous struct/union members */
static void adjustoffset(SUtype *ty, int offset)
{
  Field *field = ty->fields;

  while(field) {
    field->offset += offset;
    if(field->name == NULL && structuniontype(field->ty))
      adjustoffset(container_of(field->ty,SUtype,base),field->offset);
    field = field->next;
  }
}

/* finalize a struct/union type */
EXPORT void structunion(Type *tybase)
{
  SUtype *ty = container_of(tybase,SUtype,base);
  Field *field = ty->fields;
  int bits = 0;
  int maxbitlen = gettype(INTTYPE)->size << 3;

  if(tybase->tyclass == UNIONTYPE) {
    while(field) {
      if(field->ty->align > tybase->align)
        tybase->align = field->ty->align;
      if(field->ty->size > tybase->size)
        tybase->size = field->ty->size;
      field = field->next;
    }
  }else{
    assert(tybase->tyclass == STRUCTTYPE);
    while(field) {
      field->offset = tybase->size = ALIGN(tybase->size, field->ty->align);
      if(!field->name && structuniontype(field->ty))
        adjustoffset(container_of(field->ty,SUtype,base),field->offset);
      if(!field->bitfield){
        if(bits)
          field->offset = tybase->size = ALIGN(tybase->size + gettype(INTTYPE)->size,field->ty->align);
        bits = 0;
        tybase->size += field->ty->size;
      }else if(field->bits + bits <= maxbitlen){
        field->pos = LITTLE_ENDIAN ? bits : maxbitlen-bits;
        if( (bits += field->bits) == maxbitlen){
          tybase->size += gettype(INTTYPE)->size;
          bits = 0;
        }
      }else {
        tybase->size += gettype(INTTYPE)->size;
        field->offset += gettype(INTTYPE)->size;
        field->pos = LITTLE_ENDIAN ? 0 : maxbitlen-field->bits;
        bits = field->bits;
      }

      if(field->ty->align > tybase->align)
        tybase->align = field->ty->align;

      field = field->next;
    }
    if(bits > 0)
      tybase->size += gettype(INTTYPE)->size;
    tybase->size = ALIGN(tybase->size,tybase->align);
  }
}

/* install a filed to a struct/union type */
EXPORT void installfld(Type *tybase, char *fldname, Type *fldty, int bits, int bitfield)
{
  SUtype *ty;
  Field *field;

  ty=container_of(tybase,SUtype,base);
  if(fldty->size == 0) {
    assert(fldty->tyclass == ARRAYTYPE);
    ty->hasflexarray = 1;
  } 
  if(fldty->qual & STC_CONST)
    ty->hasconst = 1;

  NEW0(field);
  field->name = fldname;
  field->ty = fldty;
  field->bits = bits;
  field->bitfield = bitfield;
  *ty->fldtail = field;
  ty->fldtail = &field->next;
}

/* lookup a field from struct/union type */
EXPORT Field * lookupfld(SUtype *ty, char *name)
{
  Field * field = ty->fields;

  while(field) {
    if(!field->name && structuniontype(field->ty)) {
      Field *p;
      p = lookupfld(container_of(field->ty,SUtype,base),name);
      if(p) return p;
    }else if(name == field->name)
      return field;

    field = field->next;
  }
  return NULL;
} 

/* build an ENUM type */
EXPORT Type *enumof(char *id)
{
  Enumtype *ety;

  NEW0(ety);
  ety->name = id;
  ety->base.tyclass = ENUMTYPE;
  ety->base.bty = gettype(INTTYPE);
  ety->base.size = ety->base.bty->size;
  ety->base.align = ety->base.bty->align;

  return &ety->base;
}

/* build an array of bty */
EXPORT Type *arrayof(int len, Type *bty)
{
  Type *ty;

  assert(bty);

  NEW0(ty);
  ty->tyclass = ARRAYTYPE;
  ty->size = len * bty->size;
  ty->align = bty->align;
  ty->bty = bty;

  return ty;
}

/* build a pointer to bty */
EXPORT Type *pointerto(Type *bty)
{
  Type *ty;

  NEW0(ty);
  *ty = *gettype(POINTERTYPE);
  ty->bty = bty;
  ty->qual = 0;

  return ty;
}

/* adjust array/function type in parameter declaration */
EXPORT Type *makepointer(Type *ty)
{
  ty = unqual(ty);

  if(ty->tyclass == ARRAYTYPE)
    return pointerto(ty->bty);

  if(ty->tyclass == FUNCTIONTYPE)
    return pointerto(ty->bty);

  return ty;
}

/* build a qualified type */
EXPORT Type * qualify(int qual, Type *ty)
{
  Type *qty;

  if(!qual || ty->qual == qual)
    return ty;

  NEW(qty);
  *qty = *ty;
  qty->qual |= qual; 
  if(ty->qual != 0)
    qty->bty = ty->bty;
  else
    qty->bty = ty;

  return qty; 
}

/* unqualify a type */
EXPORT Type * unqual(Type *ty)
{
  if(!ty->qual)
    return ty;
  else 
    return unqual(ty->bty);
}

/* check compatible functions */
static int compatiblefuncs(Type *ty1, Type *ty2)
{
  Functype *fty1 = container_of(ty1,Functype,base);
  Functype *fty2 = container_of(ty2,Functype,base);

  if(!compatibletypes(fty1->base.bty,fty2->base.bty))
    return 0;

  if(!fty1->hasproto && !fty2->hasproto)
    return 1;

  if(fty1->hasellipsis ^ fty2->hasellipsis)
    return 0;

  if(!fty1->params || !fty2->params)
    return 1;

  if(fty1->hasproto && fty2->hasproto) {
    Parameter *p1,*p2;
    p1 = fty1->params;
    p2 = fty2->params;
    while(p1 && p2){
      if(!compatibletypes(p1->ty,p2->ty))
        return 0;
      p1 = p1->next;
      p2 = p2->next;
    }
    if(p1 || p2)
      return 0;
    return 1;
  }else
    return 0;
}

/* check compatible types */
EXPORT int compatibletypes(Type *ty1, Type *ty2)
{
  if(ty1 == ty2)
    return 1;

  if(ty1->qual != ty2->qual)
    return 0;

  ty1 = unqual(ty1);
  ty2 = unqual(ty2);

  if((ty1->tyclass == ENUMTYPE && ty2 == ty1->bty) ||
     (ty2->tyclass == ENUMTYPE && ty1 == ty2->bty))
    return 1;

  if(ty1->tyclass != ty2->tyclass && 
     !(ty1->tyclass == ARRAYTYPE && ty2->tyclass == POINTERTYPE) && 
     !(ty1->tyclass == POINTERTYPE && ty2->tyclass == ARRAYTYPE))
    return 0;

  if( ((ty1->tyclass == ARRAYTYPE && ty2->tyclass == POINTERTYPE) ||
       (ty2->tyclass == ARRAYTYPE && ty1->tyclass == POINTERTYPE)) &&
       compatibletypes(ty1->bty,ty2->bty) )
    return 1;

  switch(ty1->tyclass) {
    case POINTERTYPE:
      return compatibletypes(ty1->bty,ty2->bty);

    case ARRAYTYPE:
      return compatibletypes(ty1->bty,ty2->bty) &&
             (ty1->size == ty2->size || !ty1->size || !ty2->size);

    case FUNCTIONTYPE:
      return compatiblefuncs(ty1,ty2);

    default: assert(0);
  }
}

/* composition of two compatible types */
EXPORT Type *composetypes(Type *ty1, Type *ty2)
{
  //warning(NULL,"warning: make sure to check carefully before trying to compose types");
  assert(compatibletypes(ty1,ty2));
  if(ty1 == ty2)
    return ty1;

  if(ty1->tyclass == ENUMTYPE)
    return ty1;

  if(ty2->tyclass == ENUMTYPE)
    return ty2;

  switch(ty1->tyclass) {
    case POINTERTYPE:
      return qualify(ty1->qual, pointerto(composetypes(ty1->bty,ty2->bty)));

    case ARRAYTYPE:
      return ty1->size ? ty1 : ty2;

    case FUNCTIONTYPE:
    {
      Functype *fty1 = container_of(ty1,Functype,base);
      Functype *fty2 = container_of(ty2,Functype,base);

      fty1->base.bty = composetypes(fty1->base.bty, fty2->base.bty);
      if(fty1->hasproto && fty2->hasproto) {
        Parameter *p1, *p2;
        p1 = fty1->params;
        p2 = fty2->params;
        while(p1 && p2) {
          composetypes(p1->ty,p2->ty);
          p1 = p1->next;
          p2 = p2->next;
        }
        return &fty1->base;
      }

      assert(0);
      return fty1->hasproto ? &fty1->base : &fty2->base;
    }

    default: assert(0);
  }
}

EXPORT Type * gettype(int tyid)
{
  assert(tyid >= 0 && tyid < TOTALTYPES);
  return &types[tyid];
}

EXPORT Type * getdummyfunc(void)
{
  return dummyfunctype;
} 

