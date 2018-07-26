/*
**Semantic checker for HCC 1.0
**This code is based on various open resources, intented for educational
**purposes only. You can access, modify this for your personal use freely,
**but any attempts for comercial exploitation from this code are considered 
**unethical and should be discouraged.
*/

#include "c.h"
#include "parser.h"

static int initoffset;

/* current function declaration */
extern ASTFunctiondeclaration *curfunc;
extern ASTTranslationunit * translationunit;

static void dectyid(ASTBase *decbase, Type **ty, char **id);
static ASTBase * initchk(ASTInitializer *init, Type *ty, List *l);
static int assignable(Type *ty, ASTExpression *expr);
static int nullconst(ASTExpression *expr);
static void adjustexpr(ASTExpression *expr, int rvalue);
static ASTExpression * scalepointer(ASTExpression *expr, int scale);
static ASTExpression * exprchk(ASTExpression *expr);
static ASTExpression *cast(Type *ty, ASTExpression *expr);
static ASTExpression * unarychk(ASTExpression *expr);
static void decchk(ASTBase *dec, Type *ty);
static ASTExpression * cexprchk(ASTExpression *expr);
static ASTExpression * assignexprchk(ASTExpression *aexpr);
static void specchk(ASTSpecifier *spec);
static void exprstmtchk(ASTExprstmt *estmt);
static void stmtchk(ASTBase *stmt);
static void cmpdstmtchk(ASTCmpdstmt *cstmt,int toplevel);
static ASTExpression * constexpr(Coordinate coord, Type *ty, Tvalue v);
static ASTExpression * promoteint(ASTExpression *expr);

/* apply the operation to all items of the list */
typedef void (*chk_t)(ASTBase *);
static void foreach(ASTBase *list, chk_t chk )
{
  ASTBase *p = list;
  while(p) {
    chk(p);
    p=p->next;
  }
}

/* check direct declarator */
static void directdecchk(ASTDeclarator *dec,Type *bty)
{
  assert(dec->ty == NULL);
  dec->ty = bty;
}

/* check pointer declarator */
static void pointerdecchk(ASTPointerdeclarator *dec, Type *bty)
{
  ASTBase *p;
  int qual = 0;
  char *id;
  Type *ty;

  /* check pointer qualifiers */
  p = dec->tyquals;
  while(p) {
    ASTAtom * q = container_of(p,ASTAtom,base);
    qual |= q->tok == CONST ? STC_CONST : STC_VOLATILE;
    p = p->next;
  }

  /* type composition */
  assert(dec->ty == NULL);
  ty = qualify(qual,pointerto(bty));
  if(dec->dec){
    decchk(dec->dec,ty);
    dectyid(dec->dec,&ty,&id); 
    dec->ty = ty;
    dec->name = id;
  }else{
    dec->ty = ty;
    dec->name = NULL;
  }
}

/* check array declarator */
static void arraydecchk(ASTArraydeclarator *dec, Type *bty)
{
  int len;
  char *id;
  Type *ty;

  /* parse the array length if necessary */
  if(dec->cexpr && (dec->cexpr = cexprchk(dec->cexpr)) == NULL )
    fatal(&dec->base.coord,"array declarator has invalid length");

  /* build a type for array declarator */
  len = dec->cexpr ? dec->cexpr->val.i[0] : 0; 
  assert(dec->ty == NULL);
  ty = arrayof(len,bty);

  decchk(dec->decbase,ty);
  dectyid(dec->decbase,&ty,&id); 
  dec->ty = ty;
  dec->name = id;
}

/* add a parameter to function parameter list */
static void addparam(Parameter *param, Functype *fty)
{
  if(!fty->params){
    fty->params = param;
    fty->paramtail = &param->next;
  }else {
    *fty->paramtail = param;
    fty->paramtail = &param->next;
  }
}

/* check parameter declaration */
static void paramdecchk(ASTBase *decbase, Functype *fty)
{
  Type *ty,*bty;
  char *id;
  Parameter *param;
  ASTParamdeclaration * dec = container_of(decbase,ASTParamdeclaration,base);

  specchk(dec->specs);
  bty = dec->specs->ty;
  if(dec->specs->stclass && dec->specs->stclass != REGISTER)
    fatal(&dec->base.coord,"function parameter declaration has invalid storage class");

  if(bty->tyclass != VOIDTYPE){
    decchk(dec->dec,bty);
    dectyid(dec->dec,&ty,&id);
  }else{
    /* check void parameter type */
    if(dec->dec){
      fatal(&decbase->coord,"parameter declarator has \"void\" type");
      return;
    }
    if(decbase->next || bty->qual || dec->specs->stclass){
      fatal(&decbase->coord,"\"void\" must be the only parameter in function declaration");
      return;
    }
    ty = bty;
    id = NULL;
  }

  /* change to the pointer type for array/function type */
  if(!ty/* || ty->size == 0*/ )
    fatal(&decbase->coord,"parameter declaration has an invalid type");
  if(ty)
    ty = makepointer(ty);

  /* build a new parameter */
  NEW0(param);
  param->ty = ty;
  param->name = id;
  param->coord = dec->base.coord;
  addparam(param,fty);
}

/* check parameter type list */
static void paramtypelistchk(ASTParamtypelist *paramtypelist, Functype *fty)
{
  ASTBase *p;
  //ASTParamdeclaration *pdec;

  fty->hasellipsis = paramtypelist->ellipsis;
  p = paramtypelist->paramdecls;
  while(p) {
    paramdecchk(p,fty);
    p = p->next;
  }
}

/* check param id list */
static void paramidlistchk(ASTBase *idlist, Functype *fty)
{
  ASTBase *p;
  ASTAtom *id;

  p = idlist;
  while(p) {
    Parameter *param;

    id = container_of(p,ASTAtom,base);
    if(!id->tval.p)
      fatal(&idlist->coord,"old style function definition has an empty parameter identifier");
    NEW0(param);
    param->name = (char*)id->tval.p;
    param->coord = id->base.coord;
    addparam(param,fty);

    p = p->next;
  }
}

/* check function declarator */
static void funcdecchk(ASTFunctiondeclarator *dec, Type *rty)
{
  char *id;
  Type *ty;
  Functype *fty;

  assert( !(dec->idlist && dec->paramtypelist) );

  NEW0(fty);
  fty->base = *getdummyfunc(); 
  fty->base.bty = rty;
  fty->hasproto = dec->paramtypelist != NULL;

  if(fty->hasproto)
    paramtypelistchk(dec->paramtypelist,fty);
  else paramidlistchk(dec->idlist,fty); 

  /* check base declarator */
  decchk(dec->basedec,&fty->base);
  dectyid(dec->basedec,&ty,&id);

  dec->ty = ty; 
  dec->name = id;
}

/* check declarator */
static void decchk(ASTBase *dec, Type *bty)
{
  switch(dec->astclass) {
    case AST_DECLARATOR:
      directdecchk(container_of(dec,ASTDeclarator,base),bty);
      break;
    case AST_POINTERDECLARATOR:
      pointerdecchk(container_of(dec,ASTPointerdeclarator,base),bty);
      break;
    case AST_ARRAYDECLARATOR:
      arraydecchk(container_of(dec,ASTArraydeclarator,base),bty);
      break;
    case AST_FUNCTIONDECLARATOR:
      funcdecchk(container_of(dec,ASTFunctiondeclarator,base),bty);
      break;
    default: assert(0);
  }
}

/* check type_name */
static Type * tynamechk(ASTTypename *tyname)
{
  Type *ty;
  char *id;

  specchk(tyname->spec);
  if(tyname->dec){
    decchk(tyname->dec,tyname->spec->ty);
    dectyid(tyname->dec,&ty,&id);
    //if(!ty)
    //  ty = tyname->spec->ty;
    //else ty->bty = tyname->spec->ty;
  }else ty = tyname->spec->ty;
  
  return ty;
}

/* check increment/decrement expression */
static ASTExpression *incrchk(ASTExpression *expr)
{
  Tvalue v;
  ASTExpression * increxpr;

  if(expr->kids[0]->bitfield){
    fatal(&expr->kids[0]->base.coord,"can not apply ++/-- operator before a bitfield");
    return NULL;
  }
  assert(expr->op == INC_OP || expr->op == DEC_OP);
  v.i[0] = 1; v.i[1] = 0;
  NEW0(increxpr);
  increxpr->base.astclass = AST_EXPRESSION;
  increxpr->base.coord = expr->base.coord;
  increxpr->op = expr->op == INC_OP ? '+' : '-';
  increxpr->kids[0] = expr->kids[0];
  increxpr->kids[1] = constexpr(expr->base.coord,gettype(INTTYPE),v);

  expr->kids[0] = cexprchk(increxpr);
  expr->kids[1] = NULL;
  expr->ty = expr->kids[0]->ty;
  return expr; 
}

/* check address expression */
static ASTExpression * addrchk(ASTExpression *expr)
{
  ASTExpression *kid;

  assert(expr->op == '&');
  expr->kids[0] = cexprchk(expr->kids[0]);
  kid = expr->kids[0];
  if(kid->unary && kid->op == '*'){
    kid->kids[0]->lvalue = 0;
    return kid->kids[0];
  }else if(kid->op == INDEX_OP){
    kid->op = '+';
    kid->ty = pointerto(kid->ty);
    kid->lvalue = 0;
    kid->unary = 0;
    return kid;
  }else if(functype(kid->ty) || 
           (kid->lvalue && !kid->bitfield && !kid->inreg)) {
    expr->ty = pointerto(kid->ty);
    return expr;
  }
  fatal(&expr->base.coord, "invalid lvalue for pointer reference");
  return NULL;
}

/* check pointer dereference */
static ASTExpression * derefchk(ASTExpression *expr)
{
  ASTExpression *kid;

  assert(expr->op == '*');
  adjustexpr((expr->kids[0] = cexprchk(expr->kids[0])),1);
  kid = expr->kids[0];
  if(kid->unary && kid->op == '&'){
    kid->kids[0]->ty = kid->ty->bty;
    return kid->kids[0];
  }
  if(!kid->unary && kid->op == '+' && kid->kids[0]->isarray){
    kid->op = INDEX_OP;
    kid->ty = kid->ty->bty;
    kid->lvalue = 1;
    return kid;
  }
  if(pointertype(kid->ty)){
    expr->ty = kid->ty->bty;
    if(functype(expr->ty))
      return expr->kids[0];
    expr->lvalue = 1;
    return expr;
  }
  fatal(&expr->base.coord, "syntax error for pointer dereference");
  return NULL;
}

/* check positive/negtive unary expression */
static ASTExpression * posnegchk(ASTExpression *expr)
{
  assert(expr->op == '+' || expr->op == '-');
  adjustexpr((expr->kids[0] = cexprchk(expr->kids[0])),1);
  expr->kids[0] = promoteint(expr->kids[0]);
  expr->ty = expr->kids[0]->ty;
  return expr->op == '+' ? expr->kids[0] : foldconst(expr);
}

/* check ~ unary expression */
static ASTExpression * compchk(ASTExpression *expr)
{
  assert(expr->op == '~');
  adjustexpr((expr->kids[0] = cexprchk(expr->kids[0])),1);
  if(integertype(expr->kids[0]->ty)){
    expr->kids[0] = promoteint(expr->kids[0]);
    expr->ty = expr->kids[0]->ty;
    return foldconst(expr);
  }
  fatal(&expr->base.coord, "operand of ~ operator needs to be integer type");
  return NULL;
}

/* check ! unary expression */
static ASTExpression *notchk(ASTExpression *expr)
{
  assert(expr->op == '!');
  adjustexpr((expr->kids[0] = cexprchk(expr->kids[0])),1);
  if(scalartype(expr->kids[0]->ty)){
    expr->ty = gettype(INTTYPE);
    return foldconst(expr);
  }
  fatal(&expr->base.coord, "operand of ! operator needs to be scalar type");
  return NULL;
}

/* check sizeof expression */
static ASTExpression * sizeofchk(ASTExpression *expr)
{
  Type *ty;
  Tvalue v;

  if(expr->tyname){
    ty = tynamechk(expr->tyname);
  }else{
    assert(expr->kids[0] != NULL);
    expr->kids[0] = unarychk(expr->kids[0]);
    if(expr->kids[0]->bitfield)
      fatal(&expr->base.coord, "can not use sizeof operator on bit fields");
    ty = expr->kids[0]->ty;
  }
  v.i[0] = ty->size;
  v.i[1] = 0;
  return constexpr(expr->base.coord,gettype(UINTTYPE),v);
}

/* check type cast expression */
static ASTExpression * tycastchk(ASTExpression *expr)
{
  Type *ty;

  ty = tynamechk(expr->tyname);
  adjustexpr((expr->kids[0] = exprchk(expr->kids[0])),1);

  if(! ((scalartype(ty) && scalartype(expr->kids[0]->ty)) || voidtype(ty) ) )
    fatal(&expr->base.coord, "type casting between incompatible types");
  return cast(ty,expr->kids[0]);
}

/* check array index expression */
static ASTExpression * arrayidxchk(ASTExpression *expr)
{
  adjustexpr((expr->kids[0] = cexprchk(expr->kids[0])),1);
  adjustexpr((expr->kids[1] =  exprchk(expr->kids[1])),1);
  //    printf("Arraycheck %s\n", ((Symbol*)expr->kids[0]->val.p)->symname);
  //    printf("Arraycheck %s\n", ((Symbol*)expr->kids[1]->val.p)->symname);

  if(0) //integertype(expr->kids[0]->ty))
  {    
    ASTExpression *e = expr->kids[0];
    expr->kids[0] = expr->kids[1];
    expr->kids[1] = e;
  }
  //  printf("Arraycheck %s\n", ((Symbol*)expr->kids[0]->val.p)->symname);
  //    printf("Arraycheck %s\n", ((Symbol*)expr->kids[1]->val.p)->symname);
  //printf("arrayidxchk %d %d %d\n", expr->ty->bty, expr->kids[0]->op, expr->ty->size);
  if((arraytype(expr->kids[0]->ty) || objectptr(expr->kids[0]->ty)) && 
     integertype(expr->kids[1]->ty))
  {
    expr->ty = expr->kids[0]->ty->bty;
    expr->lvalue = 1;
    expr->kids[1] = promoteint(expr->kids[1]);
    expr->kids[1] = scalepointer(expr->kids[1],expr->ty->size);
    return expr; 
   }
  else {    
    expr->ty = expr->kids[1]->ty->bty;
    expr->lvalue = 1;
    expr->kids[1] = promoteint(expr->kids[1]);
    expr->ty = gettype(INTTYPE);
    expr->kids[1] = scalepointer(expr->kids[1], expr->ty->size);
    return expr; 
  }
  
  //  fatal(&expr->base.coord,"invalid array index expression");
  //WARNING: it doesn't matter for Java
  return expr;
  //  return NULL;
}

/* argument type promotion */
static Type * promote(Type *ty)
{
  if(ty->tyclass < INTTYPE)
    return gettype(INTTYPE);

  if(ty->tyclass == FLOATTYPE)
    return gettype(DOUBLETYPE);
  
  return ty;
}

/* promote argument expression */
static ASTExpression * promotearg(ASTExpression *expr)
{
  return cast(promote(expr->ty),expr);
}

/* check function argument */
static ASTExpression *argchk(Type *ty, ASTBase *argbase, int argno, int *allchecked)
{
  int i;
  Functype *fty;
  ASTExpression *arg;
  Parameter *param;

  fty = container_of(ty,Functype,base);
  arg = container_of(argbase,ASTExpression,base);
  adjustexpr((arg=assignexprchk(arg)),1);

  i = 1;
  param = fty->params;
  if(!param){
    *allchecked = !argbase->next;
    return promotearg(arg);
  }

  while(param && i<argno){
    param = param->next;
    i++;
  }

  if(param){
            
    if(!param->next && !fty->hasellipsis)
      *allchecked = 1;
      //removed the else for Java generation (error when not enough arguments)
    /*else
      *allchecked = !argbase->next;
      */
    if(!assignable(param->ty, arg))
      fatal(&argbase->coord, "function argument has incompatible type with definition");

    if(param->ty->tyclass < INTTYPE)
      arg = cast(gettype(INTTYPE),arg);
    else arg = cast(param->ty,arg);
    return arg;
  }else{
    if(!fty->hasellipsis)
      *allchecked = 1;
    else
      *allchecked = !argbase->next;
    return promotearg(arg);
  }
}

/* check function call expression */
static ASTExpression * funcallchk(ASTExpression *expr)
{
  Type *ty;
  int argno, allchecked;
  ASTBase *argbase;
  ASTBase *argbasechecked;
  ASTBase **argchecked;

  if(expr->kids[0]->op == IDENTIFIER && lookupid(expr->kids[0]->val.p) == NULL){
    expr->kids[0]->ty = getdummyfunc();
    expr->kids[0]->val.p = installfunc(expr->kids[0]->val.p,getdummyfunc(),EXTERN,expr->kids[0]->base.coord);
    if(!found_builtin(((Symbol*)expr->kids[0]->val.p)->symname)) {
        fatal(&expr->base.coord, "no such function");
    }
  }else expr->kids[0] = cexprchk(expr->kids[0]);

  adjustexpr(expr->kids[0],1);
  ty = expr->kids[0]->ty;
  
  if(! (pointertype(ty) && functype(ty->bty))){
    fatal(&expr->base.coord, "invalid function call syntax");
    return NULL;
  }else ty = ty->bty;

  argbasechecked = NULL;
  if(expr->kids[1]) {
    argbase = (ASTBase *)expr->kids[1];
    argchecked = &argbasechecked;
    allchecked = 0; argno = 1;
    while(argbase && !allchecked){
      *argchecked = &(argchk(ty,argbase,argno++,&allchecked))->base;

      argchecked = &(*argchecked)->next;
      
      argbase = argbase->next;
    }
    if(argbase)
      fatal(&expr->base.coord, "too many arguments for function");
    else if(!allchecked)
      fatal(&expr->base.coord, "too few arguments for function");
  }

  expr->ty = ty->bty;
  expr->kids[1] = (ASTExpression *)argbasechecked;
  return expr;
}

/* check struct/union member/pointer check */
static ASTExpression * memptrchk(ASTExpression *expr)
{
  Type *ty;
  Field *field;
  ASTAtom *fldast;

  assert(expr->op == MEMBER_OP || expr->op == PTR_OP);
  expr->kids[0] = exprchk(expr->kids[0]);
  if(expr->op == MEMBER_OP){
    adjustexpr(expr->kids[0],0);
    ty = expr->kids[0]->ty;
    if(!structuniontype(ty))
      fatal(&expr->base.coord, "member access from not a struct/union type");
    expr->lvalue = expr->kids[0]->lvalue;
  }else{
    adjustexpr(expr->kids[0],1);
    ty = expr->kids[0]->ty;
    if(! (pointertype(ty) && structuniontype(ty->bty)))
      fatal(&expr->base.coord, "pointer member(->) access from not a struct/union pointer");
    ty = ty->bty;
    expr->lvalue = 1;
  }

  fldast = container_of((ASTBase*)expr->kids[1],ASTAtom,base);
  field = lookupfld(container_of(unqual(ty),SUtype,base),fldast->tval.p);
  if(!field)
    fatal(&expr->base.coord, "struct/union type does not have member: %s",(char*)fldast->tval.p);

  expr->ty = qualify(ty->qual,field->ty);
  expr->val.p = field;
  expr->bitfield = field->bits != 0;
  return expr;
}

/* check post increment/decrement expression */
static ASTExpression * postincrchk(ASTExpression *expr)
{
  ASTExpression *increxpr;
  Tvalue v;
  ASTAtom *postop;

  if(expr->kids[0]->bitfield){
    fatal(&expr->kids[0]->base.coord,"can not apply ++/-- operator after a bitfield");
    return NULL;
  }

  v.i[0] = 1; v.i[1] = 0;
  NEW0(increxpr);
  increxpr->base.astclass = AST_EXPRESSION;
  increxpr->base.coord = expr->base.coord;
  postop = container_of((ASTBase*)expr->kids[1],ASTAtom,base);
  increxpr->op = postop->tok == INC_OP ? '+' : '-';
  increxpr->kids[0] = expr->kids[0];
  increxpr->kids[1] = constexpr(expr->base.coord,gettype(INTTYPE),v); 

  expr->kids[1] = NULL;
  expr->kids[0] = cexprchk(increxpr);
  expr->ty = expr->kids[0]->ty;
  return expr;
}

/* check identifier expression */
static ASTExpression *idchk(ASTExpression *expr)
{
  Symbol *sym;

  sym = lookupid((char*)expr->val.p);
  
  if(!sym){
    
    fatal(&expr->base.coord, "undefined identifier: %s",(char*)expr->val.p);
    return NULL;
    /*
    //    expr->ty = gettype(IDENTI);
    expr->ty = gettype(POINTERTYPE);    
    expr->val.p = (char*)expr->val.p;
    expr->inreg = 0;
    expr->lvalue = 1;
    */
    }else 
  if(sym->symclass == SYM_TYPENAME){
    fatal(&expr->base.coord, "use typename as variable: %s",(char*)expr->val.p);
    return NULL;
  }else if(sym->symclass == SYM_ENUMCONST){
    expr->op = INTCONST;
    expr->val = sym->symval;
    expr->ty = gettype(INTTYPE);
  }else
  {
    expr->ty = sym->symty;
    expr->val.p = sym;
    expr->inreg = sym->symclass == REGISTER;
    expr->lvalue = expr->ty->tyclass != FUNCTIONTYPE;
  }
  return expr;
}

/* check unary expression */
static ASTExpression * unarychk(ASTExpression *expr)
{
  Symbol *p;
  //printf("ID %d\n", expr->op); 
  switch(expr->op){
    /* unary operators */
    case INC_OP:
    case DEC_OP:
      return incrchk(expr);

    case '&':
      return addrchk(expr);

    case '*':
      return derefchk(expr);

    case '+':
    case '-':
      return posnegchk(expr);

    case '~':
      return compchk(expr);
 
    case '!':
      return notchk(expr);

    case SIZEOF:
      return sizeofchk(expr);

    case CAST_OP:
      return tycastchk(expr);

    /* postfix expressions */
    case INDEX_OP:
      return arrayidxchk(expr);

    case CALL_OP:
      return funcallchk(expr);

    case MEMBER_OP:
    case PTR_OP:
      return memptrchk(expr);

    case POST_INC_DEC_OP:
      return postincrchk(expr);

    /* primary expression */
    case INTCONST:
    case LINT:
      expr->ty = gettype(INTTYPE);
      return expr;
    case UINT:
    case ULINT:
      expr->ty = gettype(UINTTYPE);
      return expr;
    case LLINT:
      expr->ty = gettype(LONGLONGTYPE);
      return expr;
    case ULLINT:
      expr->ty = gettype(ULONGLONGTYPE);
      return expr;
    case DOUBLECONST:
      expr->ty = gettype(DOUBLETYPE);
      return expr;
    case LDOUBLECONST:
      expr->ty = gettype(LONGDOUBLETYPE);
      return expr;
    case FLOATCONST:
      expr->ty = gettype(FLOATTYPE);
      return expr;

    case STRING:
      expr->ty = arrayof(strlen((char*)expr->val.p)+1,gettype(CHARTYPE));
      //expr->ty = pointerto(gettype(CHARTYPE));
      if(!(p = lookupstrconst(expr->val.p)))
        p = installstrconst(expr->ty,expr->val.p);
      expr->val.p = p;
      expr->lvalue = 1;
      return expr;

    case IDENTIFIER:
      return idchk(expr);
    
    default: 

      assert(0);
  }
}

/* build a constant expression */
static ASTExpression * constexpr(Coordinate coord, Type *ty, Tvalue v)
{
  ASTExpression *expr;

  NEW0(expr);
  expr->base.astclass = AST_EXPRESSION;
  expr->base.coord = coord;
  expr->ty = ty;
  expr->unary = 1;
  if(ty->tyclass < ULONGTYPE)
    expr->op = INTCONST;
  else if(ty->tyclass == ULONGTYPE)
    expr->op = UINT;
  else if(ty->tyclass == LONGLONGTYPE)
    expr->op = LLINT;
  else if(ty->tyclass == ULONGLONGTYPE)
    expr->op = ULLINT;
  else if(ty->tyclass == FLOATTYPE)
    expr->op = FLOATCONST;
  else if(ty->tyclass <= LONGDOUBLETYPE)
    expr->op = DOUBLECONST;
  else assert(0);
  expr->val = v;
  return expr;
}

/* folding unary constant expression */
static ASTExpression * unaryfold(ASTExpression *expr)
{
  int typeop;
  Tvalue v;
  ASTExpression *e;

  if(/*unaryop(expr->op) && */!constop(expr->kids[0]->op))
    return expr;

  v.i[0] = v.i[1] = 0;
  e = expr->kids[0];
  typeop = typecode(expr->kids[0]->ty);  

  switch(expr->op){
    case '-':
      if(typeop == I4 || typeop == U4)
        v.i[0] = -e->val.i[0];
      else if(typeop == I8)
        v.ll = -e->val.ll;
      else if(typeop == U8)
        v.ll = -e->val.ll;
      else if(typeop == F4)
        v.f = -e->val.f;
      else if(typeop == F8)
        v.d = -e->val.d;
      else assert(0);
      break;
        
    case '+':
      assert(typeop == I4 || typeop == U4 || typeop == I8 || 
             typeop == U8 || typeop == F4 || typeop == F8);
      break;

    case '~':
      if(typeop == I4 || typeop == U4)
        v.i[0] = ~e->val.i[0];
      else if(typeop == I8)
        v.ll = ~e->val.ll;
      else if(typeop == U8)
        v.ll = ~e->val.ll;
      else assert(0);
      break;

    case '!':
      if(typeop == I4 || typeop == U4)
        v.i[0] = ! e->val.i[0];
      else if(typeop == I8 || typeop == U8)
        v.i[0] = !e->val.i[0] && !e->val.i[1];
      else if(typeop == F4)
        v.i[0] = !e->val.f;
      else if(typeop == F8)
        v.i[0] = !e->val.d;
      else assert(0);
      break;

    default: assert(0);
  }

  return constexpr(expr->base.coord,expr->ty,v);
}

/* constant folding of expression */
EXPORT ASTExpression * foldconst(ASTExpression *expr)
{
  int typeop;
  Tvalue v;
  ASTExpression *l, *r;

  if(expr->unary)
    return unaryfold(expr);

  if(binop(expr->op) && !( constop(expr->kids[0]->op) && constop(expr->kids[1]->op) ))
    return expr;

  if(expr->op == COND_OP){
    if( intconst(expr->kids[0]->op) && integertype(expr->kids[0]->ty) )
      return expr->kids[0]->val.i[0] ? expr->kids[1] : expr->kids[2];
    else if(lintconst(expr->kids[0]->op) && integertype(expr->kids[0]->ty) )
      return expr->kids[0]->val.ll ? expr->kids[1] : expr->kids[2];
    else if(expr->kids[0]->op == FLOATCONST && fptype(expr->kids[0]->ty))
      return expr->kids[0]->val.f ? expr->kids[1] : expr->kids[2];
    else if((expr->kids[0]->op == DOUBLECONST || expr->kids[1]->op == LDOUBLECONST) && fptype(expr->kids[0]->ty) )
      return expr->kids[0]->val.d ? expr->kids[1] : expr->kids[2];
    return expr;
  }

  v.i[0] = v.i[1] = 0;
  l = expr->kids[0];
  r = expr->kids[1];
  typeop = typecode(expr->kids[0]->ty);  
  switch(expr->op) {
  #define LOGICAL_OP(opcode,op)             \
    case opcode:                            \
      v.i[0] = l->val.i[0] op r->val.i[0];\
      v.i[1] = l->val.i[1] op r->val.i[1];\
      break;

    LOGICAL_OP('|',|)
    LOGICAL_OP('&',&)
    LOGICAL_OP('^',^)
  #undef LOGICAL_OP

  #define RELATIONAL_OP(opcode,op)                                                   \
    case opcode:                                                                     \
      if(typeop == I4)                                                               \
        v.i[0] = l->val.i[0] op r->val.i[0];                                         \
      else if(typeop == U4)                                                          \
        v.i[0] = (unsigned)l->val.i[0] op (unsigned)r->val.i[0];                     \
      else if(typeop == I8)                                                          \
        v.i[0] = l->val.ll op r->val.ll;                     \
      else if(typeop == U8)                                                          \
        v.i[0] = (unsigned long long)l->val.ll op (unsigned long long)r->val.ll;   \
      else if(typeop == F4)                                                          \
        v.i[0] = l->val.f op r->val.f;                                               \
      else if(typeop == F8)                                                          \
        v.i[0] = l->val.d op r->val.d;                                               \
      else assert(0);                                                                \
      break;

    RELATIONAL_OP(OR_OP,||)
    RELATIONAL_OP(AND_OP,&&)
    RELATIONAL_OP(EQ_OP,==)
    RELATIONAL_OP(NE_OP,!=)
    RELATIONAL_OP(GE_OP,>=)
    RELATIONAL_OP(LE_OP,<=)
    RELATIONAL_OP('>',>)
    RELATIONAL_OP('<',<)
  #undef RELATIONAL_OP

  #define BINARY_OP(opcode,op)                                                                          \
    case opcode:                                                                                        \
      if(typeop == I4)                                                                                  \
        v.i[0] = l->val.i[0] op r->val.i[0];                                                          \
      else if(typeop == U4)                                                                             \
        v.i[0] = (unsigned)l->val.i[0] op (unsigned)r->val.i[0];                                      \
      else if(typeop == I8)                                                                             \
        v.ll = l->val.ll op r->val.ll;                            \
      else if(typeop == U8)                                                                             \
        v.ll = (unsigned long long)l->val.ll op (unsigned long long)r->val.ll; \
      else if(typeop == F4)                                                                             \
        v.f = l->val.f op r->val.f;                                                                   \
      else if(typeop == F8)                                                                             \
        v.d = l->val.d op r->val.d;                                                                   \
      else assert(0);                                                                                   \
      break;

    BINARY_OP('+',+)
    BINARY_OP('-',-)
    BINARY_OP('*',*)
    BINARY_OP('/',/)
  #undef BINARY_OP

    case '%':                                                                                      
      if(typeop == I4)                                                                               
        v.i[0] = l->val.i[0] % r->val.i[0];                                                        
      else if(typeop == U4)                                                                        
        v.i[0] = (unsigned)l->val.i[0] % (unsigned)r->val.i[0];                                   
      else if(typeop == I8)                                                                       
        v.ll = l->val.ll % r->val.ll;                        
      else if(typeop == U8)                                                                      
        v.ll = (unsigned long long)l->val.ll % (unsigned long long)r->val.ll; 
      else assert(0);                                                                            
      break;


  #define SHIFT_OP(opcode,op)                                                                           \
    case opcode:                                                                                        \
      if(typeop == I4)                                                                                  \
        v.i[0] = l->val.i[0] op r->val.i[0];                                                          \
      else if(typeop == U4)                                                                             \
        v.i[0] = (unsigned)l->val.i[0] op r->val.i[0];                                                \
      else if(typeop == I8)                                                                             \
        v.ll = l->val.ll op r->val.ll;                            \
      else if(typeop == U8)                                                                             \
        v.ll = (unsigned long long)l->val.ll op (unsigned long long)r->val.ll; \
      else assert(0);                                                                                   \
      break;

    SHIFT_OP(RIGHT_SHIFT,>>)
    SHIFT_OP(LEFT_SHIFT,<<)
  #undef SHIFT_OP

    default: assert(0);
  }

  return constexpr(expr->base.coord,expr->ty,v);
}

/* cast a constant expression to a specific type */
static ASTExpression * constcast(Type *ty, ASTExpression *expr)
{
  int src, dst;

  src = typecode(expr->ty);
  dst = typecode(ty);

  if(src == dst)
    goto fini;

  /* to use this routine, the type of expr must have been promoted */
  switch(src) {
    case I4:
      if(dst == F4){
        expr->val.f = (float)expr->val.i[0];
        expr->op = FLOATCONST;
      }else if(dst == F8){
        expr->val.d = (double)expr->val.i[0];
        expr->op = DOUBLECONST;
      }else if(dst == I1)
        expr->val.i[0] = (char)expr->val.i[0];
      else if(dst == U1)
        expr->val.i[0] = (unsigned char)expr->val.i[0];
      else if(dst == I2)
        expr->val.i[0] = (short)expr->val.i[0];
      else if(dst == U2)
        expr->val.i[0] = (unsigned short)expr->val.i[0];
      else assert(0);
      break;

    case U4:
      if(dst == F4){
        expr->val.f = (float)((unsigned)expr->val.i[0]);
        expr->op = FLOATCONST;
      }else if(dst == F8){
        expr->val.d = (double)((unsigned)expr->val.i[0]);
        expr->op = DOUBLECONST;
      }else if(dst == I1){
        expr->val.i[0] = (char)((unsigned)expr->val.i[0]);
        expr->op = INTCONST;
      }else if(dst == U1){
        expr->val.i[0] = (unsigned char)((unsigned)expr->val.i[0]);
        expr->op = INTCONST;
      }else if(dst == I2){
        expr->val.i[0] = (short)((unsigned)expr->val.i[0]);
        expr->op = INTCONST;
      }else if(dst == U2){
        expr->val.i[0] = (unsigned short)((unsigned)expr->val.i[0]);
        expr->op = INTCONST;
      }else assert(0);
      break;

    case F4:
      if(dst == I4){
        expr->val.i[0] = (int)expr->val.f;
        expr->op = INTCONST;
      }else if(dst == U4){
        expr->val.i[0] = (unsigned)expr->val.f;
        expr->op = UINT;
      }else if(dst == F8){
        expr->val.d = (double)expr->val.f;
        expr->op = DOUBLECONST;
      }else if(dst == I1){
        expr->val.i[0] = (char)expr->val.f;
        expr->op = INTCONST;
      }else if(dst == U1){
        expr->val.i[0] = (unsigned char)expr->val.f;
        expr->op = INTCONST;
      }else if(dst == I2){
        expr->val.i[0] = (short)expr->val.f;
        expr->op = INTCONST;
      }else if(dst == U2){
        expr->val.i[0] = (unsigned short)expr->val.f;
        expr->op = INTCONST;
      }else assert(0);
      break;

    case F8:
      if(dst == I4){
        expr->val.i[0] = (int)expr->val.d;
        expr->op = INTCONST;
      }else if(dst == U4){
        expr->val.i[0] = (unsigned)expr->val.d;
        expr->op = UINT;
      }else if(dst == F4){
        expr->val.f = (float)expr->val.d;
        expr->op = FLOATCONST;
      }else if(dst == I1){
        expr->val.i[0] = (char)expr->val.d;
        expr->op = INTCONST;
      }else if(dst == U1){
        expr->val.i[0] = (unsigned char)expr->val.d;
        expr->op = INTCONST;
      }else if(dst == I2){
        expr->val.i[0] = (short)expr->val.d;
        expr->op = INTCONST;
      }else if(dst == U2){
        expr->val.i[0] = (unsigned short)expr->val.d;
        expr->op = INTCONST;
      }else assert(0);
      break;

    default: assert(0);
  }
fini:
  expr->ty = ty;
  return expr;
}

static int reducety(Type *ty)
{
  switch(ty->tyclass){
    case CHARTYPE:
    case UCHARTYPE:
      return CHARTYPE;

    case SHORTTYPE:
    case USHORTTYPE:
      return SHORTTYPE;

    case INTTYPE:
    case UINTTYPE:
    case LONGTYPE:
    case ULONGTYPE:
      return INTTYPE;

    case FLOATTYPE:
      return FLOATTYPE;

    case LONGLONGTYPE:
    case ULONGLONGTYPE:
      return LONGLONGTYPE;

    case DOUBLETYPE:
    case LONGDOUBLETYPE:
      return DOUBLETYPE;

    default: assert(0);
  }
}

/* create a cast node if necessary */
static ASTExpression * exprcast(Type *ty, ASTExpression *expr)
{
  ASTExpression *cexpr;

  if(constop(expr->op) && ty->tyclass != VOIDTYPE)
    return constcast(ty,expr);

  if(ty == expr->ty)
    return expr;

  if(reducety(expr->ty) == reducety(ty)) {
    expr->ty = ty;
    return expr;
  }
  /* create a cast expression */
  NEW0(cexpr);
  cexpr->base.astclass = AST_EXPRESSION;
  cexpr->base.coord = expr->base.coord;
  cexpr->op = CAST_OP;
  cexpr->unary = 1;
  cexpr->ty = ty;
  cexpr->kids[0] = expr;

  return cexpr;
}

/*
** cast the expression into type "ty".
** Refer to LCC compiler source and the textbook for more details.
*/
static ASTExpression *cast(Type *ty, ASTExpression *expr)
{
  int src, dst;
  
  src = typecode(expr->ty);
  dst = typecode(ty);

  /* if dest type is void, then cast directly */
  if(dst == V)
    return exprcast(ty,expr);

  /* if both types are integer and have the same size, no cast is necessary */
  if(src < F4 && dst < F4 && src/2 == dst/2){
    expr->ty = ty;
    return expr;
  }

  /* first, promote the expression to integer type */
  if(src < I4){
    expr = exprcast(gettype(INTTYPE),expr);
    src = I4;
  }

  if(src != dst){
    /* promote dest type if necessary */
    if(dst < I4)
      expr = exprcast(gettype(INTTYPE),expr);
    /* then make the final cast to dest type */
    expr = exprcast(ty,expr);
  }

  return expr;
}

/* check conditional expression like: a ? b : c; */
static ASTExpression *condexprchk(ASTExpression *expr)
{
  int qual;
  Type *ty1, *ty2;

  adjustexpr((expr->kids[0] = cexprchk(expr->kids[0])),1);
  if(!scalartype(expr->kids[0]->ty))
    fatal(&expr->base.coord, "the first argument of a conditional expression must be a scalar"); 
  adjustexpr((expr->kids[1] = exprchk(expr->kids[1])),1);
  adjustexpr((expr->kids[2] = cexprchk(expr->kids[2])),1);

  ty1 = expr->kids[1]->ty;
  ty2 = expr->kids[2]->ty;
  if(arithtype(ty1) && arithtype(ty2)){
    expr->ty = commonarithtype(ty1,ty2);
    expr->kids[1] = cast(expr->ty,expr->kids[1]);
    expr->kids[2] = cast(expr->ty,expr->kids[2]);
    return foldconst(expr);
  }else if(structuniontype(ty1) && ty1 == ty2)
    expr->ty = ty1;
  else if(ty1->tyclass == VOIDTYPE && ty2->tyclass == VOIDTYPE)
    expr->ty = gettype(VOIDTYPE);
  else if(compatibletypes(ty1,ty2)){
    qual = ty1->qual | ty2->qual;
    expr->ty = pointerto(qualify(qual,composetypes(unqual(ty1->bty),unqual(ty2->bty))));
  }else if(pointertype(ty1) && nullconst(expr->kids[2]))
    expr->ty = ty1;
  else if(pointertype(ty2) && nullconst(expr->kids[1]))
    expr->ty = ty2;
  else if((!functype(ty1) && voidptr(ty2)) ||
          (!functype(ty2) && voidptr(ty1))) {
    qual = ty1->bty->qual | ty2->bty->qual;
    expr->ty = pointerto(qualify(qual,gettype(VOIDTYPE)));
  }else
    fatal(&expr->base.coord, "invalid operand for conditional expression");
  
  return expr;
}

/* build a node to compute pointer difference */
static ASTExpression * pointerdiff(ASTExpression *expr, int size)
{
  Tvalue v;
  ASTExpression *diffexpr;

  NEW0(diffexpr);
  diffexpr->base.astclass = AST_EXPRESSION;
  diffexpr->base.coord = expr->base.coord;
  diffexpr->ty = expr->ty;
  diffexpr->op = '/';
  diffexpr->kids[0] = expr;
  v.i[0] = size;
  v.i[1] = 0;
  diffexpr->kids[1] = constexpr(expr->base.coord,expr->ty,v);

  return diffexpr;
}

/* build a node to scale pointer offset */
static ASTExpression * scalepointer(ASTExpression *expr, int scale)
{
  Tvalue v;
  ASTExpression *scalexpr;
  NEW0(scalexpr);
  scalexpr->base.astclass = AST_EXPRESSION;
  scalexpr->base.coord = expr->base.coord;
  scalexpr->ty = expr->ty;
  scalexpr->op = '*';

  scalexpr->kids[0] = expr;
  v.i[0] = scale;
  v.i[1] = 0;
  scalexpr->kids[1] = constexpr(expr->base.coord,expr->ty,v);
  return foldconst(scalexpr);
}

/* promote expression to integer type */
static ASTExpression * promoteint(ASTExpression *expr)
{
  return expr->ty->tyclass < INTTYPE ? cast(gettype(INTTYPE),expr) : expr;
}

/* check constant expression */
static ASTExpression * cexprchk(ASTExpression *expr)
{
  /* unary expression */
  if(expr->unary)
    return unarychk(expr);

  /* conditional expression: ? : */
  if(expr->op == COND_OP)
    return condexprchk(expr);

  /* binary expression */
  adjustexpr((expr->kids[0] = exprchk(expr->kids[0])),1);
  adjustexpr((expr->kids[1] = exprchk(expr->kids[1])),1);

  switch(expr->op){
    Type *ty1, *ty2, *ty;
    case OR_OP: case AND_OP:
      if(scalartype(expr->kids[0]->ty) && scalartype(expr->kids[1]->ty)) {
                                       ASTExpression * ex;
        expr->ty = gettype(INTTYPE);
        ex = foldconst(expr);
        return foldconst(expr);
      }
      fatal(&expr->base.coord, "operands of logical expression should have scalar types");
      break;

    case '|': case '&': case '^':
      if(integertype(expr->kids[0]->ty) && integertype(expr->kids[1]->ty)){
        expr->ty = commonarithtype(expr->kids[0]->ty,expr->kids[1]->ty);
        expr->kids[0] = cast(expr->ty,expr->kids[0]);
        expr->kids[1] = cast(expr->ty,expr->kids[1]); 
        return foldconst(expr);
      }
      fatal(&expr->base.coord, "operands of bitwise expression should have integer types");
      break;

    case EQ_OP: case NE_OP:
      expr->ty = gettype(INTTYPE);
      ty1 = expr->kids[0]->ty;
      ty2 = expr->kids[1]->ty;
      if(arithtype(ty1) && arithtype(ty2)){
        ty = commonarithtype(ty1,ty2);
        expr->kids[0] = cast(ty,expr->kids[0]);
        expr->kids[1] = cast(ty,expr->kids[1]);
        expr->ty = gettype(INTTYPE);
        //printf("That case %d %d\n", expr->kids[0]->op, expr->kids[1]->op);
        return foldconst(expr);
      }
      if(compatibletypes(ty1,ty2) ||
         (!funcptr(ty1) && voidptr(ty2)) ||
         (!funcptr(ty2) && voidptr(ty1)) ||
         (pointertype(ty1) && nullconst(expr->kids[1])) ||
         (pointertype(ty2) && nullconst(expr->kids[0])) ) {
         //printf("Actual case\n");
        return expr;
        }
        //Added this return for Java
        //printf("This case\n");
      return expr;
      //      fatal(&expr->base.coord, "operands of equality expression have illegal types");
      break;

    case '>': case '<':
    case GE_OP: case LE_OP:
      expr->ty = gettype(INTTYPE);
      ty1 = expr->kids[0]->ty;
      ty2 = expr->kids[1]->ty;
      if(arithtype(ty1) && arithtype(ty2)){
        ty = commonarithtype(ty1,ty2);
        expr->kids[0] = cast(ty,expr->kids[0]);
        expr->kids[1] = cast(ty,expr->kids[1]);
        expr->ty = gettype(INTTYPE);
        return foldconst(expr);
      }

      if(objectptr(ty1) && objectptr(ty2) && 
         compatibletypes(unqual(ty1->bty),unqual(ty2->bty)))
        return expr;

      if(incompleteptr(ty1) && incompleteptr(ty2) && 
         compatibletypes(unqual(ty1->bty),unqual(ty2->bty)))
        return expr;

      fatal(&expr->base.coord, "operands of equality expression have illegal types");
      break;

    case RIGHT_SHIFT:
    case LEFT_SHIFT:
      if(integertype(expr->kids[0]->ty) && integertype(expr->kids[1]->ty)){
        expr->kids[0] = promoteint(expr->kids[0]);
        expr->kids[1] = promoteint(expr->kids[1]);
        expr->ty = expr->kids[0]->ty;
        return foldconst(expr);
      }
      fatal(&expr->base.coord, "operands of shift expression have illegal types");
      break;

    case '+':
      if(constop(expr->kids[0]->op) || 
         (objectptr(expr->kids[1]->ty) && integertype(expr->kids[0]->ty))){
       ASTExpression *e;
       //WARNING: removed it for Java
       /* e = expr->kids[0];
        expr->kids[0] = expr->kids[1];
        expr->kids[1] = e;*/
        //printf("This one\n");
      }
      ty1 = expr->kids[0]->ty;
      ty2 = expr->kids[1]->ty;
      //printf("TWO %d %d\n", expr->kids[0]->op, expr->kids[1]->op);
      if(arithtype(ty1) && arithtype(ty2)){
                        
        expr->ty = ty = commonarithtype(ty1,ty2);
        expr->kids[0] = cast(ty,expr->kids[0]);
        expr->kids[1] = cast(ty,expr->kids[1]);
        return foldconst(expr);
      }

      if(objectptr(ty1) && integertype(ty2)){
        expr->kids[1] = promoteint(expr->kids[1]);
        if(!(expr->kids[0]->op == 303) ) 
        {
        //Don't scale pointer for Java.
                //expr->kids[1] = scalepointer(expr->kids[1],ty1->bty->size);
        }
        expr->ty = ty1;
       
        return expr;
      }
      //
      else {
           //WARNING: added this block for Java (string+string).
          
           if(objectptr(ty1)) {
               expr->kids[0] = promoteint(expr->kids[0]);
           }
           expr->ty = ty2;
           return expr;
      }
      //fatal(&expr->base.coord, "operands of arithmetic expression(+) have illegal types");
      break;

    case '-':
      ty1 = expr->kids[0]->ty;
      ty2 = expr->kids[1]->ty;
      if(arithtype(ty1) && arithtype(ty2)){
        expr->ty = ty = commonarithtype(ty1,ty2);
        expr->kids[0] = cast(ty,expr->kids[0]);
        expr->kids[1] = cast(ty,expr->kids[1]);
        return foldconst(expr);
      }

      if(objectptr(ty1) && integertype(ty2)){
        expr->kids[1] = promoteint(expr->kids[1]);
        expr->kids[1] = scalepointer(expr->kids[1],ty1->bty->size);
        expr->ty = ty1;
        return expr;
      }

      if(pointertype(ty1) && pointertype(ty2) && compatibletypes(ty1,ty2)){
        expr->ty = gettype(INTTYPE);
        expr = pointerdiff(expr,ty1->bty->size);
        return expr;
      }
      fatal(&expr->base.coord, "operands of arithmetic expression(-) have illegal types");
      break;

    case '*': case '/':
      ty1 = expr->kids[0]->ty;
      ty2 = expr->kids[1]->ty;
      if(arithtype(ty1) && arithtype(ty2)){
        expr->ty = ty = commonarithtype(ty1,ty2);
        expr->kids[0] = cast(ty,expr->kids[0]);
        expr->kids[1] = cast(ty,expr->kids[1]);
        return foldconst(expr);
      }

      fatal(&expr->base.coord, "operands of arithmetic expression(* /) have illegal types");
      break;

    case '%':
      ty1 = expr->kids[0]->ty;
      ty2 = expr->kids[1]->ty;
      if(integertype(ty1) && integertype(ty2)){
        expr->ty = ty = commonarithtype(ty1,ty2);
        expr->kids[0] = cast(ty,expr->kids[0]);
        expr->kids[1] = cast(ty,expr->kids[1]);
        return foldconst(expr);
      }

      fatal(&expr->base.coord, "operands of arithmetic expression(MOD) have illegal types");
      break;

    default: assert(0);
  }
  return NULL;
}

/* check if an expression is read-only */
static int modifiable(ASTExpression *expr)
{
  SUtype *suty;

  if(expr->lvalue && !(expr->ty->qual & STC_CONST) && !structuniontype(expr->ty))
    return 1;

  if(structuniontype(expr->ty)){
    suty = container_of(expr->ty,SUtype,base);
    return !suty->hasconst;
  }
  return 0;
}

/* check argument(assignment) expression */
static ASTExpression * assignexprchk(ASTExpression *expr)
{
  int ops[] = {
    RIGHT_SHIFT, LEFT_SHIFT,
    '-','+','*','/','%',
    '&','|','^'
  };

  if(expr->op == '=' || (expr->op >= RIGHT_ASSIGN && expr->op <= XOR_ASSIGN)){
    Type *ty;

    /* check children */
    if(expr->op != '='){
      ASTExpression *subexpr;
      NEW0(subexpr);
      //subexpr->base = expr->base;
      subexpr->base.astclass = AST_EXPRESSION;
      subexpr->base.coord = expr->base.coord;
      subexpr->op = ops[expr->op - RIGHT_ASSIGN];
      subexpr->kids[0] = expr->kids[0];
      subexpr->kids[1] = expr->kids[1];
      expr->op = '=';
      expr->kids[1] = cexprchk(subexpr);
      expr->kids[0] = expr->kids[1]->kids[0];
      adjustexpr(expr->kids[0],0);
      adjustexpr(expr->kids[1],1);
    }else{
      expr->kids[0] = unarychk(expr->kids[0]);
      adjustexpr(expr->kids[0], 0);
      expr->kids[1] = exprchk(expr->kids[1]);
      adjustexpr(expr->kids[1], 1);
    }
//WARNING: removed it for Java
    //    if(!modifiable(expr->kids[0]))
    //      fatal(&expr->base.coord, "assignment of readonly left operand");
 
    ty = expr->kids[0]->ty;
    if(assignable(ty,expr->kids[1]))
      expr->kids[1] = cast(ty,expr->kids[1]);
    else
      fatal(&expr->base.coord,"incompatible types in assignment");
    expr->ty = ty;
  }else{

    expr = cexprchk(expr);
  
    adjustexpr(expr, 1);
  }

  return expr;
}

/* check expressions */
static ASTExpression * exprchk(ASTExpression *expr)
{
  if(expr->op == ',') {
    expr->kids[0] = exprchk(expr->kids[0]);
    adjustexpr(expr->kids[0], 1);

    expr->kids[1] = assignexprchk(expr->kids[1]);
    adjustexpr(expr->kids[1], 1);

    expr->ty = expr->kids[1]->ty;
  }else{
    expr = assignexprchk(expr);
    adjustexpr(expr,1);
  }
  return expr;
}

/* check enumerator */
static int enumchk(ASTBase *enubase, Type *ty, int enumlab)
{
  int enuval = 0;
  ASTEnumerator *enu = container_of(enubase,ASTEnumerator,base);

  if(!enu->cexpr) {
    installenumconst(enu->id->tval.p, ty, enumlab, enu->base.coord);
    return enumlab + 1;
  }else {
    enu->cexpr = cexprchk(enu->cexpr);
    if(!enu->cexpr)
      fatal(&enubase->coord,"enumerator value is not an integer const");
    enuval = enu->cexpr->val.i[0];
    installenumconst(enu->id->tval.p, ty, enuval, enu->base.coord);
    return enuval + 1;
  }
}

/* check enum specifier */
static Type * enumspecchk(ASTEnumspecifier *enumspec)
{
  ASTBase *enu;
  Symbol *etag;
  Type *ty;
  int enumlab;

  ty = NULL;
  if(!enumspec->id && !enumspec->enumerators)
    fatal(&enumspec->base.coord,"enum specifier has no name or enumerators");

  /* check enumspec identifier and type */
  if(enumspec->id && !enumspec->enumerators){
    etag = lookuptag(enumspec->id->tval.p);
    if(!etag || (etag->symscope == curscope() && etag->symty->tyclass != ENUMTYPE) )
      fatal(&enumspec->base.coord,"use of undefined enum specifier");
    return etag->symty;
  } else if(!enumspec->id && enumspec->enumerators) {
    ty = gettype(INTTYPE);
  } else {
    etag = lookuptag(enumspec->id->tval.p);
    ty = enumof(enumspec->id->tval.p);
    if(!etag || etag->symscope < curscope() ) 
      installtag(enumspec->id->tval.p, ty, enumspec->base.coord);
    else if(etag->symty->tyclass != ENUMTYPE)
      fatal(&enumspec->base.coord,"redefinition of enum specifier that has already been defined");
  }

  /* check enum enumerators */
  enu = enumspec->enumerators;
  enumlab = 0;
  while(enu) {
    enumlab = enumchk(enu, ty, enumlab);
    enu = enu->next;
  }
  return ty;
}

/* check struct declarator */
static void structdecchk(ASTStructdeclarator *sdec, Type *tybase, Type *bty)
{
  char *id = NULL;
  int bits = 0, isbitfld = 0;
  Type *fty = bty;
  SUtype *ty;

  if(sdec->dec) {
    decchk(sdec->dec,bty);
    dectyid(sdec->dec,&fty,&id);
  }

  ty = container_of(tybase,SUtype,base);
  if(ty->hasflexarray)
    fatal(&sdec->base.coord,"illegal struct declarator after a dynamic array member");
  if(structuniontype(fty)) {
    SUtype *suty = container_of(fty,SUtype,base);
    if(suty->hasflexarray)
      fatal(&sdec->base.coord,"struct/union specifier with dynamic array should not be a member of another struct/union specifier");
  }
  if(id && lookupfld(ty,id))
    fatal(&sdec->base.coord,"another struct/union member with the same name has already been defined");

  if(sdec->cexpr) {
    isbitfld = 1;
    sdec->cexpr = cexprchk(sdec->cexpr);
    if(!sdec->cexpr)
      fatal(&sdec->base.coord,"width of bit fields must be constant integer");
    else if(id && sdec->cexpr->val.i[0] == 0)
      fatal(&sdec->base.coord,"width of bit fields should not be zero");
    if(fty->tyclass != INTTYPE && fty->tyclass != UINTTYPE)
      fatal(&sdec->base.coord,"bit fields must have int/uint types");
    bits = sdec->cexpr ? sdec->cexpr->val.i[0] : 0;
    if(bits < 0)
      fatal(&sdec->base.coord,"bit field size should >= zero");
    if(bits > gettype(INTTYPE)->size * 8)
      fatal(&sdec->base.coord,"bit field size exceeds the width of integer");
  }

  installfld(tybase, id, fty, bits, isbitfld);
}

/* check struct declaration */
static void structdeclchk(ASTStructdeclaration *sdecl, Type *ty)
{
  ASTBase *decbase;

  assert(sdecl->specs != NULL);
  specchk(sdecl->specs);

  decbase = sdecl->stdecls;
  if(!decbase) {
    installfld(ty, NULL, sdecl->specs->ty, 0,0);
    warning(&sdecl->base.coord,"struct declaration has no declarator");
  }
  while(decbase){
    structdecchk(container_of(decbase,ASTStructdeclarator,base), ty, sdecl->specs->ty); 
    decbase = decbase->next;
  }
}

/* check struct/union specifier */
static Type * structunionspecchk(ASTBase *suspecbase)
{
  Type *ty = NULL;
  int sutype;
  Symbol *sutag;
  ASTBase *sudeclbase;
  ASTSUSpecifier *suspec;

  sutype = suspecbase->astclass == AST_STRUCTSPECIFIER ? STRUCTTYPE : UNIONTYPE;
  suspec = container_of(suspecbase,ASTSUSpecifier,base);

  //check specifier name
  if(suspec->id && !suspec->sudecls) {
    sutag = lookuptag(suspec->id->tval.p);
    if(!sutag) {
      ty = structunionof(suspec->id->tval.p,sutype);
      installtag(suspec->id->tval.p, ty, suspec->base.coord);
    }else if(sutag->symty->tyclass != sutype)
      fatal(&suspecbase->coord,"struct/union specifier name has been declared before");
    return sutag ? sutag->symty : ty;
  }else if(!suspec->id && suspec->sudecls) {
    ty = structunionof(NULL,sutype);
  }else if(suspec->id->tval.p && suspec->sudecls) {
    sutag = lookuptag(suspec->id->tval.p);
    if(!sutag || sutag->symscope < curscope()){
      ty = structunionof(suspec->id->tval.p,sutype);
      installtag(suspec->id->tval.p,ty,suspec->base.coord);
    }else if(sutag->symty->tyclass == sutype && sutag->symty->size == 0)
      ty = sutag->symty;
    else fatal(&suspecbase->coord,"named struct/union specifier has already been defined");
  }else fatal(&suspecbase->coord,"unamed struct/union specifier that defines no instances");

  //check struct/union declarations
  assert(ty);
  sudeclbase = suspec->sudecls;
  while(sudeclbase) {
    structdeclchk(container_of(sudeclbase,ASTStructdeclaration,base),ty);
    sudeclbase = sudeclbase->next;
  }

  //finalize struct/union type
  structunion(ty);
  return ty;
}

/* check declaration_specifier */
static void specchk(ASTSpecifier *spec)
{
  Type *type;
  ASTAtom *term;
  ASTBase *p;
  int qual = 0;
  int sign,size;
  int signs, sizes, tys;
  Symbol *sym;

  //storage class
  p = spec->sclass;
  if(p) {
    if(p->next)
      fatal(&spec->base.coord,"multiple storage classes in declaration specifiers");
    term = container_of(p,ASTAtom,base);
    spec->stclass = term->tok;
  }

  //type qualifier
  p = spec->qual;
  while(p) {
    term = container_of(p,ASTAtom,base);
    qual |= (term->tok == CONST ? STC_CONST : STC_VOLATILE);
    p = p->next;
  }

  //type specifier
  sign = size = 0;
  signs = sizes = tys = 0;
  p = spec->typespecs;
  while(p) {
    if(p->astclass == AST_STRUCTSPECIFIER || p->astclass == AST_UNIONSPECIFIER) {
      type = structunionspecchk(p);
      tys++;
      goto fini;
    }
    
    if(p->astclass == AST_ENUMSPECIFIER) {
      type = enumspecchk(container_of(p,ASTEnumspecifier,base));
      tys++;
      goto fini;
    }

    assert(p->astclass == AST_ATOM);
    term = container_of(p,ASTAtom,base);
    switch(term->tok) {
      case TYPENAME:
        assert((sym = lookupty((char*)term->tval.p))!=NULL);
        type = sym->symty;
        tys++;
        break;

      case SIGNED:
      case UNSIGNED:
        sign = term->tok;
        signs ++;
        break;

      case SHORT:
      case LONG:
        if(size == LONG && sizes == 1) {
          size = LONG + LONG;
        }else {
          size = term->tok;
          sizes ++;
        } 
        break;

      case CHAR:
        type = gettype(CHARTYPE);
        tys ++;
        break;

      case INT:
        type = gettype(INTTYPE);
        tys ++;
        break;

      case FLOAT:
        type = gettype(FLOATTYPE);
        tys ++;
        break;

      case DOUBLE:
        type = gettype(DOUBLETYPE);
        tys ++;
        break;

      case VOID:
        type = gettype(VOIDTYPE);
        tys ++;
        break;

      default: assert(0);
    }

  fini:
    p = p->next;
  }

  //sanity checks for type specifiers
  if(tys == 0) {
    if(size == 0 && sign == 0)
      warning(&spec->base.coord,"data declaration has type or storage class");
    type = gettype(INTTYPE);
  }

  if(sizes > 1 || signs > 1 || tys > 1)
    fatal(&spec->base.coord,"data declaration has multiple size/sign/type specifiers");

  if(type == gettype(DOUBLETYPE) && size == LONG) {
    type = gettype(LONGDOUBLETYPE);
    size = 0;
  } else if (type == gettype(CHARTYPE)) {
    sign = sign == UNSIGNED;
    type = gettype(CHARTYPE + sign);
    sign = 0;
  }

  if(type == gettype(INTTYPE)) {
    sign = sign == UNSIGNED;

    switch(size) {
      case SHORT:
        type = gettype(SHORTTYPE+sign);
        break;

      case LONG:
        type = gettype(LONGTYPE+sign);
        break;

      case LONG + LONG:
        type = gettype(LONGLONGTYPE+sign);
        break;

      default:
        assert(size==0);
        type = gettype(INTTYPE+sign);
        break;
    }
  }else if(size != 0 || sign != 0)
    fatal(&spec->base.coord,"data declaration has invalid type size/sign specifier");

  //fill the type field after all checks
  spec->ty = qualify(qual,type);
}

/* adjust an expression */
static void adjustexpr(ASTExpression *expr, int rvalue)
{
  //if(rvalue){
  //  expr->ty = unqual(expr->ty);
  //  expr->lvalue = 0;
  //}

  if(expr->ty->tyclass == FUNCTIONTYPE){
    expr->isfunc = 1;
    expr->ty = pointerto(expr->ty);
  }

  if(expr->ty->tyclass == ARRAYTYPE) {
    expr->lvalue = 0;
    expr->isarray = 1;
    expr->ty = pointerto(expr->ty->bty);
  }
}

/* check if an expression is a null constant */
static int nullconst(ASTExpression *expr)
{
  return constop(expr->op) && expr->val.i[0] == 0 && expr->val.i[1] == 0;
}

/* check if it's legal to assign the result of an expression to its lvalue */
static int assignable(Type *ty, ASTExpression *expr)
{
  Type *ety = expr->ty;

  ty = unqual(ty);
  ety = unqual(ety);

  if(ty == ety)
    return 1;

  if(arithtype(ty) && arithtype(ety))
    return 1;

  if(compatibletypes(ty,ety) && (!ty->bty || qualable(ty->bty,ety->bty)) )
    return 1;

  if( pointertype(ty) && nullconst(expr))
    return 1;

  if( ((!funcptr(ty) && voidptr(ety)) || (voidptr(ty) && !funcptr(ety))) &&
     (!ty->bty || qualable(ty->bty,ety->bty)) )
    return 1;

  if( pointertype(ty) && pointertype(ety) ){
    warning(&expr->base.coord, "assignment from incompatible pointer type");
    return 1;
  }

  if( ((pointertype(ty) && integertype(ety)) || (pointertype(ety) && integertype(ty))) &&
      ty->size == ety->size ) {
    //warning(&expr->base.coord, "conversion between integer and pointer without a cast");
    return 1;
  }

  return 0;
}

/* check scalar initializer */
static ASTExpression * scalarinitchk(ASTInitializer *init, Type *ty)
{
  if(init->lbrace) {
    /* initialization from constant expression */
    if(!init->u.initials){
      fatal(&init->base.coord,"empty scalar initializer");
      return NULL;
    }else{
      if(init->u.initials->next)
        warning(&init->base.coord,"excess elements in scalar initializer");
      ASTInitializer * initia = container_of(init->u.initials,ASTInitializer,base);
      if(initia->lbrace)
        warning(&initia->base.coord, "braces around scalar initializer");
      return scalarinitchk(initia,ty);
    }
  }else{
    /* initialization from assignment expression */
    ASTExpression *expr;

    if(!init->u.expr)
      fatal(&init->base.coord, "expected expression in initialization");
    expr = assignexprchk(init->u.expr);
    adjustexpr(expr,1);
    //WARNING: deleted it just for String in Java
    /*
    if(!assignable(ty, expr))
    fatal(&init->base.coord, "incompatible types in initialization");*/
    return expr;
  }
}

static void addinit(Type *ty, ASTExpression *expr, int size, List *l)
{
  Initdata *idata;

  NEW0(idata);
  idata->ty = ty;
  idata->expr = expr;
  if(!size)
    idata->size = ty->size;
  else idata->size = size;
  idata->offset = initoffset;
  listappend(idata,l);
}

/* check struct/union initialization from assignment expression */
static void commoninitchk(ASTInitializer *init, Type *ty/*, List *initdata*/)
{
  ASTExpression *expr;

  if(!init->u.expr){
    fatal(&init->base.coord, "expected expression in initialization");
    return;
  }
  expr = assignexprchk(init->u.expr);
  adjustexpr(expr,1);
  if(!assignable(ty, expr) && !(ty->tyclass == ARRAYTYPE && expr->ty->tyclass == ARRAYTYPE &&
                                ty->bty == expr->ty->bty &&
                             (ty->bty->tyclass == CHARTYPE || ty->bty->tyclass == UCHARTYPE))){
    fatal(&init->base.coord, "incompatible types in initialization");
    return;
  }
  init->u.expr = expr;
  //addinit(ty,expr,initdata);
}

/* check union initializer */
static ASTBase * unioninitchk(ASTInitializer *init, Type *ty, List *initdata)
{
  SUtype *suty;

  suty = container_of(ty,SUtype,base);
  assert(suty->fields);
  ty = suty->fields->ty;

  /* initialization from assignment expression */
  if(!init->lbrace){
    return initchk(init,ty,initdata);
  } 

  /*
  **This is not symmetrical though, 
  ** namely, only the type of the first field is checked here.
  **This simplifies our symantic checking work.
  */
  if(init->u.initials->next){
    warning(&init->base.coord, "excess elements in union initializer");
    /* just truncate the list */
    init->u.initials->next = NULL;
  }
  return initchk(container_of(init->u.initials,ASTInitializer,base),ty,initdata);
}

/* check struct initializer */
static ASTBase * structinitchk(ASTInitializer *init, Type *ty, List *initdata)
{
  SUtype *sutype;
  Field *field;
  ASTBase *initiabase;
  ASTInitializer *initia;

  sutype = container_of(ty,SUtype,base);
  assert(sutype->fields);

  /* initialization from assignment expression */
  if(!init->lbrace)
    initiabase = &init->base;
  else initiabase = init->u.initials;
  field = sutype->fields;
  while(field && initiabase){
    ASTBase *p;

    initia = container_of(initiabase,ASTInitializer,base);
    if(!field->bitfield){
      p = initchk(initia,field->ty,initdata);
      if(!field->next && field->offset + field->ty->size < ty->size){
        addinit(gettype(CHARTYPE),NULL,ty->size - field->ty->size - field->offset, initdata);
        initoffset += ty->size - field->offset - field->ty->size;
      }else if(field->next && field->offset + field->ty->size < field->next->offset){
        addinit(gettype(CHARTYPE),NULL,field->next->offset - field->offset - field->ty->size, initdata);
        initoffset += field->next->offset - field->offset - field->ty->size;
      }
    }else{
      Initdata *idata;

      assert(field->ty->tyclass == INTTYPE || field->ty->tyclass == UINTTYPE);
      if(!field->pos && !field->bits)
        fatal(&init->base.coord,"Invalid bit field: %s",field->name);

      /* ignore dummy bit fields */
      if(!field->name){
        field = field->next;
        continue;
      }

      initia->u.expr = scalarinitchk(initia,field->ty);
      addinit(field->ty,initia->u.expr,0,initdata);
      idata = initdata->tail->data;
      idata->bitfield = 1;
      idata->size = field->bits;
      idata->pos = field->pos;
      if(!field->next || field->next->offset != field->offset){
        initoffset += field->ty->size;
        idata->lastfld = 1;

        if(!field->next && field->offset + field->ty->size < ty->size){
          addinit(gettype(CHARTYPE),NULL,ty->size - field->ty->size - field->offset, initdata);
          initoffset += ty->size - field->offset - field->ty->size;
        }else if(field->next && field->offset + field->ty->size < field->next->offset){
          addinit(gettype(CHARTYPE),NULL,field->next->offset - field->offset - field->ty->size, initdata);
          initoffset += field->next->offset - field->offset - field->ty->size;
        }
      }
      p = initia->base.next;
    }

    field = field->next;
    if(!p)
      initiabase = initiabase->next;
    else initiabase = p;
  }
  if(field){
    addinit(gettype(CHARTYPE),NULL,ty->size-field->offset,initdata);
    initoffset += ty->size-field->offset;
  }

  return initiabase;
}

/* check array initializer */
static ASTBase * arrayinitchk(ASTInitializer *init, Type *ty,List *initdata)
{
  ASTBase *initiabase;
  ASTInitializer *initia;
  int len = 0, initlen = 0;

  if(ty->size){
    assert((ty->size % ty->bty->size) == 0);
    len = ty->size/ty->bty->size;
  }

  if(!init->lbrace)
    initiabase = &init->base;
  else
    initiabase = init->u.initials;
  initia = container_of(initiabase,ASTInitializer,base);

  /* check string */
  if(chartype(ty->bty) && initia->u.expr->op == STRING){
    char *p;

    commoninitchk(initia,ty/*,initdata*/);
    p = ((Symbol*)initia->u.expr->val.p)->symval.p;
    initlen = strlen(p)+1;
    if(len && initlen > len) {
      warning(&initia->base.coord,"initializer-string for array of chars is too long");
      *(p+len) = 0;
    }else if(len == 0)
      ty->size = initlen;
    addinit(ty,initia->u.expr,0,initdata);
    initoffset += ty->size;
    if(len > initlen){
      addinit(gettype(CHARTYPE),NULL,len-initlen,initdata);
      initoffset += len-initlen;
    }
    return initia->base.next;
  }

  while(initiabase) {
    ASTBase *p=NULL;

    initia = container_of(initiabase,ASTInitializer,base);
    p = initchk(initia,ty->bty,initdata);

    initlen++;
    if(initia->lbrace)
      initiabase = initiabase->next;
    else initiabase = p;

    if(len > 0 && initlen == len)
      break;
  }

  if(len == 0 && initlen > 0)
    ty->size = initlen * ty->bty->size;
  if(len > initlen){
    addinit(gettype(CHARTYPE),NULL,(len-initlen)*ty->bty->size,initdata);
    initoffset += (len-initlen)*ty->bty->size;
  }
  return initiabase;
}

/* check initializer */
static ASTBase * initchk(ASTInitializer *init, Type *ty, List *initdata)
{
  /*
  **we split the checking into separate routines.
  **This may not be necessary, but easy to understand.
  */
  switch(ty->tyclass) {
    /* scalar types */
    case CHARTYPE: case UCHARTYPE:
    case SHORTTYPE: case USHORTTYPE:
    case INTTYPE: case UINTTYPE:
    case LONGTYPE: case ULONGTYPE:
    case LONGLONGTYPE: case ULONGLONGTYPE:
    case ENUMTYPE: case FLOATTYPE:
    case DOUBLETYPE: case LONGDOUBLETYPE:
    case POINTERTYPE: case FUNCTIONTYPE:
      init->u.expr = scalarinitchk(init,ty);
      addinit(ty,init->u.expr,0,initdata);
      initoffset += ty->size;
      return init->base.next;

    case UNIONTYPE:
      return unioninitchk(init,ty,initdata);

    case STRUCTTYPE:
      return structinitchk(init,ty,initdata);

    case ARRAYTYPE:
      return arrayinitchk(init,ty,initdata);
    default: assert(0);
  }
}

static void initializerchk(ASTInitializer *init, Type *ty, List *initdata)
{
  initoffset = 0;
  if((ty->tyclass == UNIONTYPE || ty->tyclass == STRUCTTYPE) &&
     !init->lbrace){
    commoninitchk(init,ty/*,initdata*/);
    addinit(ty,init->u.expr,0,initdata);
    initoffset += ty->size;
    return;
  }

  if(ty->tyclass == ARRAYTYPE && !init->lbrace){
    fatal(&init->base.coord,"initializer list should be in braces");
    return;
  }
  initchk(init,ty,initdata);
}

/* get type & id from checked declaration */
static void dectyid(ASTBase *decbase, Type **ty, char **id)
{
  ASTDeclarator *dec;
  ASTArraydeclarator *adec;
  ASTPointerdeclarator *pdec;
  ASTFunctiondeclarator *fdec;

  switch(decbase->astclass) {
    case AST_DECLARATOR:
      dec = container_of(decbase,ASTDeclarator,base);
      *ty = dec->ty;
      *id = dec->name;
      break;

    case AST_ARRAYDECLARATOR:
      adec = container_of(decbase,ASTArraydeclarator,base);
      *ty = adec->ty;
      *id = adec->name;
      break;

    case AST_POINTERDECLARATOR:
      pdec = container_of(decbase,ASTPointerdeclarator,base);
      *ty = pdec->ty;
      *id = pdec->name;
      break;

    case AST_FUNCTIONDECLARATOR:
      fdec = container_of(decbase,ASTFunctiondeclarator,base);
      *ty = fdec->ty;
      *id = fdec->name;
      break;

    default: assert(0);
  }
}

/* check typedef declaration */
static void typedefchk(ASTDeclaration *decl)
{
  Type *bty,*ty;
  ASTBase *p;
  char *id;
  Symbol *sym;
  ASTInitdeclarator *initdec;

  bty = decl->specs->ty;
  p = decl->initdecls;
  while(p) {
    initdec = container_of(p,ASTInitdeclarator,base);
    if(initdec->init){
      fatal(&p->coord,"A typedef name can not be initialized");
      return;
    }
    decchk(initdec->dec,bty);
    ty = NULL; id = NULL;

    dectyid(initdec->dec,&ty,&id);
    /* combine types */
    //if(!ty)
    //  ty = bty;
    //else{
    //  assert(!ty->bty);
    //  ty->bty = bty;
    //}

    if(!id)
      goto fini;
    if(!ty)
      fatal(&decl->base.coord,"typedef declaration has an invalid type");
   
    if(lookupid(id)){
      fatal(&decl->base.coord,"typedef id has been used as variable name before");
      return;
    }
    sym = lookupty(id);
    if(sym && sym->symscope == curscope() && 
       (sym->symclass != SYM_TYPENAME || !compatibletypes(sym->symty,ty)))
      fatal(&decl->base.coord,"redefinition of typedef names");
    else
      installtypedef(id,ty,p->coord);

  fini:
    p = p->next;
  }
}

static int constaddr(ASTExpression *expr)
{
  if(!pointertype(expr->ty) && !arraytype(expr->ty))
    return 0;

  if(expr->op == '+' || expr->op == '-')
    if(!constaddr(expr->kids[0]) || constop(expr->kids[1]->op))
      return 0;

  if(expr->op == '&')
    if(!constaddr(expr->kids[0]))
      return 0;

  if(expr->op == INDEX_OP)
    if(constaddr(expr->kids[0]) && constop(expr->kids[1]->op))
      return 1;

  if(expr->op == '.' && !constaddr(expr->kids[0]))
    return 0;

  return expr->op == IDENTIFIER;
}

/* check if the expression in initializer is constant */
static void initconstchk(ASTBase *initbase)
{
  ASTInitializer *init = container_of(initbase,ASTInitializer,base);

  if(!init->lbrace){
    if(!constop(init->u.expr->op) && !constaddr(init->u.expr) )
      fatal(&initbase->coord, "initializer expression must be constant");
  }else foreach(init->u.initials,initconstchk);
}

/* check global data declaration */
static void gdeclchk(ASTDeclaration *decl)
{
  ASTBase *p;
  int stclass;
  Type *bty;

  assert(decl->specs!=NULL);
  specchk(decl->specs);

  bty = decl->specs->ty;

  stclass = decl->specs->stclass;
  if(stclass == AUTO || stclass == REGISTER)
    fatal(&decl->base.coord,"external data declaration has invalid storage class");
  if(stclass == TYPEDEF){
    typedefchk(decl);
    return;
  }

  p = decl->initdecls;
  while(p) {
    ASTInitdeclarator *initdec;
    char *id;
    Type *ty;
    Symbol *sym;

    ty = NULL; id = NULL;    
    initdec = container_of(p,ASTInitdeclarator,base);
    decchk(initdec->dec,bty);
    dectyid(initdec->dec,&ty,&id);
    if(!id)
      goto fini;

    /* check function declaration */
    if(ty->tyclass == FUNCTIONTYPE) {
      /* adjust function type */
      //ty = pointerto(ty);
      Functype *fty = container_of(ty,Functype,base);
      fty->hasproto = 1;

      if(initdec->init)
        fatal(&decl->base.coord,"function declaration should not have an initializer");
      
      if( (sym=lookupid(id)) == NULL)
        installfunc(id,ty,stclass,initdec->base.coord);
      else {
        if((sym->stclass == EXTERN && stclass == STATIC) ||
           (stclass == EXTERN && sym->stclass == STATIC) )
          fatal(&decl->base.coord,"function declaration has conflict linkage classes");

        if(!compatibletypes(ty,sym->symty))
          fatal(&decl->base.coord,"function declaration has an incompatible previous declaration");
        else 
          sym->symty = composetypes(ty,sym->symty);
      }

      goto fini;
    }

    /* OK. Now let's check normal variable declaration */
    if(lookupty(id)){
      fatal(&decl->base.coord, "variable name has already been used as type name before");
      return;
    }
    if( (sym = lookupid(id)) == NULL )
      sym = installvar(id,ty,stclass,(initdec->init != NULL),initdec->base.coord);
    else{
      if(sym->stclass == EXTERN)
        sym->stclass = stclass;
      if(stclass != EXTERN && stclass != sym->stclass)
        fatal(&decl->base.coord,"data declaration has conflict linkage classes");
      if(!compatibletypes(ty,sym->symty))
        fatal(&decl->base.coord,"data declaration has incompatible type with previous declaration");
      else if(sym->symty != ty)
        sym->symty = composetypes(sym->symty,ty);
      if(sym->defined && initdec->init)
        fatal(&decl->base.coord,"redefinition of data declaration");
    }

    if(initdec->init){
      initializerchk(initdec->init,ty,&sym->irdata);
      initconstchk(&initdec->init->base);
      //sym->initdata = initdec->init;
    }

    if(ty->size == 0 && !(stclass == EXTERN && (ty->tyclass == STRUCTTYPE || ty->tyclass == UNIONTYPE))
                     && !(stclass != STATIC && ty->tyclass == ARRAYTYPE) )
      fatal(&decl->base.coord,"The data type of the declaration has unknown size");

  fini:
    p = p->next;
  }
}

static int compare(ASTLabeledstmt *c1, ASTLabeledstmt *c2)
{
  int d = ((ASTExpression*)c1->idexpr)->val.i[0] -
          ((ASTExpression*)c2->idexpr)->val.i[0];
  if(d>0)
    return 1;
  else if(d<0)
    return -1;
  else{
    fatal(&c1->base.coord, "redefinition of case constant expression");
    return 0;
  }
}

static ASTExpression * foldcast(Type *ty, ASTExpression *expr)
{
  int src = typecode(expr->ty);
  int dst = typecode(ty);

  switch(src) {
    case I1: case U1:
    case I2: case U2:
      assert(0);
      break;

    case I4:
      switch(dst){
        case I1:
          expr->val.i[0] = (char)expr->val.i[0];
          break;
        case U1:
          expr->val.i[0] = (unsigned char)expr->val.i[1];
          break;
        case I2:
          expr->val.i[0] = (short)expr->val.i[0];
          break;
        case U2:
          expr->val.i[0] = (unsigned short)expr->val.i[0];
          break;
        case I4:
        case U4:
          break;
        case F4:
          expr->val.f = (float)expr->val.i[0];
          break;
        case F8:
          expr->val.d = (double)expr->val.i[0];
        default: assert(0);
      }
      break;

    case U4:
      switch(dst){
        case F4:
          expr->val.f = (float)expr->val.i[0];
          break;
        case F8:
          expr->val.d = (double)expr->val.i[0];
        default: assert(0);
      }
      break;

    case I8:
      switch(dst){
        case I1:
          expr->val.i[0] = (char)expr->val.ll;
          break;
        case U1:
          expr->val.i[0] = (unsigned char)expr->val.ll;
          break;
        case I2:
          expr->val.i[0] = (short)expr->val.ll;
          break;
        case U2:
          expr->val.i[0] = (unsigned short)expr->val.ll;
          break;
        case I4:
          expr->val.i[0] = (int)expr->val.ll;
          break;
        case U4:
          expr->val.i[0] = (unsigned int)expr->val.ll;
          break;
        case F4:
          expr->val.f = (float)expr->val.ll;
          break;
        case F8:
          expr->val.d = (double)expr->val.ll;
        default: assert(0);
      }
      break;

    case U8:
      switch(dst){
        case F4:
          expr->val.f = (float)expr->val.ll;
          break;
        case F8:
          expr->val.d = (double)expr->val.ll;
        default: assert(0);
      }
      break;

    case F4:
      switch(dst){
        case I4:
          expr->val.i[0] = (int)expr->val.f;
          break;
        case U4:
          expr->val.i[0] = (unsigned int)expr->val.f;
          break;
        case F4:
          expr->val.f = (float)expr->val.f;
          break;
        case F8:
          expr->val.d = (double)expr->val.f;
        default: assert(0);
      }
      break;

    case F8:
      switch(dst){
        case I4:
          expr->val.i[0] = (int)expr->val.d;
          break;
        case U4:
          expr->val.i[0] = (unsigned int)expr->val.d;
          break;
        case F4:
          expr->val.f = (float)expr->val.d;
          break;
        case F8:
          expr->val.d = (double)expr->val.d;
        default: assert(0);
      }
      break;

    default: assert(0);
  }
  return expr;
}

/* check labeled statement */
static void labelstmtchk(ASTLabeledstmt *lstmt)
{
  Symbol *sym;
  ASTAtom *id;
  ASTExpression *expr;
  ASTSelstmt *sw;

  switch(lstmt->type) {
    case IDLABEL:
      id = (ASTAtom*)lstmt->idexpr;
      if( !(sym = lookuplab(id->tval.p)) )
        sym = installlab(id->tval.p,id->base.coord,1,lstmt);
      else if(sym->defined)
        fatal(&id->base.coord, "label redefinition in function scope");
      else sym->defined = 1;
      lstmt->idexpr = sym;
      stmtchk(lstmt->stmt);
      break;

    case CASELABEL:
      sw = NULL;
      if(curfunc->sws.tail)
        sw = (ASTSelstmt*)curfunc->sws.tail->data;
      if(!sw)
        fatal(&lstmt->base.coord, "case label can only appear in switch statement");
      assert(sw->base.astclass == AST_SELECTIONSTMT);
      expr = (ASTExpression *)lstmt->idexpr;
      if(!(expr = cexprchk(expr)))
        fatal(&lstmt->base.coord, "invalid case expression");
      lstmt->idexpr = foldcast(sw->expr->ty,expr);
      stmtchk(lstmt->stmt);
      listappendsorted(lstmt,&sw->cases,compare);
      break;

    case DEFAULTLABEL:
      sw = NULL;
      if(curfunc->sws.tail)
        sw = (ASTSelstmt*)curfunc->sws.tail->data;
      if(!sw)
        fatal(&lstmt->base.coord, "default label can only appear in switch statement");
      if(sw->defaultstmt)
        fatal(&lstmt->base.coord, "only one default statement is allowed in switch block");
      stmtchk(lstmt->stmt);
      sw->defaultstmt = lstmt;
      break;
    default: assert(0);
  }
}

/* check expression statement */
static void exprstmtchk(ASTExprstmt *estmt)
{
  if(estmt->expr) 
    estmt->expr = exprchk(estmt->expr);
}

/* check selection statement */
static void selstmtchk(ASTSelstmt *sstmt)
{
  switch(sstmt->type) {
    case IFSTMT:
      sstmt->expr = exprchk(sstmt->expr);
     
      if(!scalartype(sstmt->expr->ty))
        fatal(&sstmt->expr->base.coord, "if expression has non-scalar type");
      stmtchk(sstmt->truestmt);
      break;

    case IFELSESTMT:
      sstmt->expr = exprchk(sstmt->expr);
      if(!scalartype(sstmt->expr->ty))
        fatal(&sstmt->expr->base.coord, "if expression has non-scalar type");
      stmtchk(sstmt->truestmt);
      stmtchk(sstmt->falsestmt);
      break;

    case SWITCHSTMT:
      listappend(sstmt,&curfunc->sws);
      listappend(sstmt,&curfunc->brks);
      adjustexpr((sstmt->expr = exprchk(sstmt->expr)),1);
      if(!integertype(sstmt->expr->ty))
        fatal(&sstmt->expr->base.coord, "switch expression has non-integer type");
      if(sstmt->expr->ty->tyclass < INTTYPE)
        sstmt->expr = cast(gettype(INTTYPE),sstmt->expr);
      stmtchk(sstmt->truestmt);
      listrmtail(&curfunc->sws);
      listrmtail(&curfunc->brks);
      break;

    default: assert(0);
  }
}

/* check iteration statement */
static void iterstmtchk(ASTIterationstmt *istmt)
{
  switch(istmt->type) {
    case WHILESTMT:
    case DOSTMT:
      listappend(istmt,&curfunc->loops);
      listappend(istmt,&curfunc->brks);
      istmt->expr = exprchk(istmt->expr);
      if(!scalartype(istmt->expr->ty))
        fatal(&istmt->expr->base.coord, "loop condition expression has non-scalar type");
      stmtchk(istmt->stmt);
      listrmtail(&curfunc->loops);
      listrmtail(&curfunc->brks);
      break;
 
    case FORSTMT:
      listappend(istmt,&curfunc->loops);
      listappend(istmt,&curfunc->brks);
      exprstmtchk(istmt->exprstmt[0]);
      if(istmt->exprstmt[0]->expr && !scalartype(istmt->exprstmt[0]->expr->ty))
        fatal(&istmt->exprstmt[0]->expr->base.coord, "the second expression of for statement should be scalar type");
      exprstmtchk(istmt->exprstmt[1]);
      if(istmt->expr)
        istmt->expr = exprchk(istmt->expr);
      stmtchk(istmt->stmt);
      listrmtail(&curfunc->loops);
      listrmtail(&curfunc->brks);
      break;

    default: assert(0);
  }
}

/* check jump statement */
static void jumpstmtchk(ASTJumpstmt *jstmt)
{
  Type *ty;
  Symbol *sym;
  ASTAtom *id;
  ASTExpression *expr;
  ASTIterationstmt *tgtstmt;

  switch(jstmt->type) {
    case GOTOSTMT:
      assert(jstmt->idexpr != NULL);
      id = (ASTAtom*)jstmt->idexpr;
      if(!(sym=lookuplab(id->tval.p)))
        sym = installlab(id->tval.p,id->base.coord,0,NULL);
      sym->ref ++;
      id->tval.p = sym;
      break;

    case CONTINUESTMT:
      if(curfunc->loops.tail)
        tgtstmt = (ASTIterationstmt*)curfunc->loops.tail->data;
      if(!tgtstmt)
        fatal(&jstmt->base.coord, "continue statement can only appear in loop statement");
      assert(tgtstmt->base.astclass == AST_ITERATIONSTMT);
      jstmt->tgtstmt = &tgtstmt->base;
      break;

    case BREAKSTMT:
      if(curfunc->brks.tail)
        tgtstmt = (ASTIterationstmt*)curfunc->brks.tail->data;
      if(!tgtstmt)
        fatal(&jstmt->base.coord, "break statement can only appear in loop/switch statement");
      assert(tgtstmt->base.astclass == AST_ITERATIONSTMT ||
             tgtstmt->base.astclass == AST_SELECTIONSTMT);
      jstmt->tgtstmt = &tgtstmt->base;
      break;

    case RETURNSTMT:
      curfunc->hasreturn = 1;
      /* return type */
      ty = curfunc->sym->symty->bty;
      assert(ty!=NULL);
      expr = (ASTExpression*)jstmt->idexpr;
      if(expr){
        adjustexpr((expr = exprchk(expr)),1);
        if(ty->tyclass == VOIDTYPE)
          fatal(&expr->base.coord, "return value for void function");
        if(!assignable(ty,expr))
          fatal(&expr->base.coord, "the type of return expression is incompatible with function definition");
        jstmt->idexpr = cast(ty,expr);
      }else if(ty->tyclass != VOIDTYPE)
        warning(&jstmt->base.coord, "function should return a value");
      break;

    default: assert(0);
  }
}

/* check statement */
static void stmtchk(ASTBase *stmt)
{
  switch(stmt->astclass) {
    case AST_LABELEDSTMT:
      labelstmtchk(container_of(stmt,ASTLabeledstmt,base));
      break;
    case AST_COMPOUNDSTMT:
      cmpdstmtchk(container_of(stmt,ASTCmpdstmt,base),0);
      break;
    case AST_EXPRESSIONSTMT:
      exprstmtchk(container_of(stmt,ASTExprstmt,base));
      break;
    case AST_SELECTIONSTMT:
      selstmtchk(container_of(stmt,ASTSelstmt,base));
      break;
    case AST_ITERATIONSTMT:
      iterstmtchk(container_of(stmt,ASTIterationstmt,base));
      break;
    case AST_JUMPSTMT:
      jumpstmtchk(container_of(stmt,ASTJumpstmt,base));
      break;
    default: assert(0);
  }
}

/* check local data declaration */
static void ldeclchk(ASTDeclaration *decl, List *locals)
{
  ASTBase *p;
  int stclass;
  Type *bty;

  assert(decl->specs!=NULL);
  specchk(decl->specs);
  bty = decl->specs->ty;
  stclass = decl->specs->stclass;
  if(stclass == TYPEDEF){
    typedefchk(decl);
    return;
  }
  if(stclass == 0)
    stclass = AUTO;

  p = decl->initdecls;
  while(p) {
    ASTInitdeclarator *initdec;
    char *id;
    Type *ty;
    Symbol *sym;

    ty = NULL; id = NULL;    
    initdec = container_of(p,ASTInitdeclarator,base);
    decchk(initdec->dec,bty);
    dectyid(initdec->dec,&ty,&id);
    if(!id)
      goto fini;

    /* combine types */
    //if(!ty)
    //  ty = bty;
    //else{
    //  assert(!ty->bty);
    //  ty->bty = bty;
    //}
    
    /* check function declaration */
    if(ty->tyclass == FUNCTIONTYPE) {
      /* adjust function type */
      ty = pointerto(ty);

      if(stclass == STATIC)
        fatal(&initdec->base.coord, "local function declaration should not be static");

      if(initdec->init)
        fatal(&initdec->base.coord, "function declaration should not have an initializer");
      
      if( (sym=lookupid(id)) == NULL)
        installfunc(id,ty,EXTERN,initdec->base.coord);
      else if(!compatibletypes(ty,sym->symty))
        fatal(&initdec->base.coord, "function declaration has an incompatible previous declaration");
      else 
        sym->symty = composetypes(ty,sym->symty);

      goto fini;
    }

    /* OK. Now let's check normal variable declaration */
    if(stclass == EXTERN && initdec->init)
      fatal(&initdec->base.coord, "can not initialize an extern variable in function scope");

    if(lookupty(id)){
      fatal(&decl->base.coord, "variable name has already been used as type name before");
      return;
    }
    if( (sym = lookupid(id)) == NULL || sym->symscope != curscope()) {
      sym = installvar(id,ty,stclass,(initdec->init != NULL),initdec->base.coord);
      if(initdec->init) {
        initializerchk(initdec->init,ty,&sym->irdata);
        //sym->initdata = initdec->init;
        if(stclass == STATIC)
          initconstchk(&initdec->init->base);
        else listappend(sym,locals);
      }else listappend(sym,locals);
    }else if(! (sym->symclass == EXTERN && stclass == EXTERN && compatibletypes(ty,sym->symty)))
      fatal(&initdec->base.coord, "local variable redefinition in function scope");
    
  fini:
    p = p->next;
  }
}

/* check compound statement */
static void cmpdstmtchk(ASTCmpdstmt *cstmt, int toplevel)
{
  ASTBase *p;

  if(!toplevel)
    enterscope();
  if(cstmt->declist){
    p = cstmt->declist;
    while(p) {
      ldeclchk(container_of(p,ASTDeclaration,base),&cstmt->locals);
      p = p->next;
    }
  }

  if(cstmt->stmtlist)
    foreach(cstmt->stmtlist,stmtchk);
  if(!toplevel)
    exitscope();
}

/* check old-style parameter */
static void paramchk(Coordinate *coord, Functype *fty, Type *ty, char *paramname, int stclass)
{
  Parameter *param = fty->params;
  while(param){
    if(param->name == paramname){
      if(param->ty){
        fatal(coord, "redefine parameter name %s in old-style function definition",paramname);
        return;
      }
      if(ty->tyclass == ARRAYTYPE && ty->size == 0)
        param->ty = pointerto(ty->bty);
      else param->ty = ty;
      param->inreg = stclass == REGISTER;
      return;
    }
    param = param->next;
  }
  fatal(coord, "old-style function definition has inconsistant parameter name list and declarators");
}

/* check old-style function parameter declaration */
static void paramdeclchk(ASTDeclaration *decl, Functype *fty)
{
  Type *ty, *bty;
  char *pname;
  int stclass;
  ASTBase *initbase;
  ASTInitdeclarator *initdec;

  if(fty->hasproto){
    fatal(&decl->base.coord, "function definition has mixed new-style and old-style parameter declaration");
    return;
  }

  /* check declaration specifiers */
  specchk(decl->specs);
  bty = decl->specs->ty;
  stclass = decl->specs->stclass;
  if(stclass != 0 && stclass != REGISTER){
    fatal(&decl->base.coord, "parameter declaration has invalid storage class");
    return;
  }

  /* check init declarators */
  initbase = decl->initdecls;
  if(!initbase){
    fatal(&decl->base.coord, "parameter declaration does not have declarator");
    return;
  }
  while(initbase){
    initdec = container_of(initbase,ASTInitdeclarator,base);
    if(initdec->init){
      fatal(&initdec->base.coord,"parameter declaration should not have initializer");
      return;
    }
    decchk(initdec->dec,bty);
    dectyid(initdec->dec,&ty,&pname);
    //if(!ty)
    //  ty = bty;
    //else{
    //  assert(!ty->bty);
    //  ty->bty = bty;
    //}
    if(!pname){
      fatal(&initdec->base.coord, "parameter declaration has unnamed declarator");
      return;
    }
    paramchk(&initdec->base.coord,fty,ty,pname,stclass);
    initbase = initbase->next;
  }
}

/* check function definition */
static void funcchk(ASTFunctiondeclaration *funcdecl)
{
  Type *bty, *ty;
  Functype *fty;
  int stclass;
  char *funcname;
  Symbol *sym;
  Listnode *n;
  Parameter * param;

  /* check declaration specifier */
  if(funcdecl->specs) {
    specchk(funcdecl->specs);
    bty = funcdecl->specs->ty;
    stclass = funcdecl->specs->stclass;
  }else{
    bty = gettype(INTTYPE);
    stclass = 0;
  }
  if(stclass == 0)
    stclass = EXTERN;

  /* check function declarator */
  ty = NULL; funcname = NULL;
  assert(funcdecl->dec != NULL);
  decchk(funcdecl->dec,bty);
  dectyid(funcdecl->dec,&ty,&funcname);
  if(!funcname){
    fatal(&funcdecl->base.coord, "function definition without a name");
    return;
  }
  //assert(ty && !ty->bty);
  //ty->bty = bty;
  fty = container_of(ty,Functype,base);

  /* check parameter declaration for old-style function definition */
  if(funcdecl->paramdecls) {
    ASTBase *p = funcdecl->paramdecls;
    while(p) {
      paramdeclchk(container_of(p,ASTDeclaration,base),fty);
      p = p->next;
    }
  }

  /* there may still be some parameters not typed */
  param = fty->params;
  while(param){
    if(!param->ty)
      param->ty = gettype(INTTYPE);
    param = param->next;
  }

  /* now the function must have prototype */
  fty->hasproto = 1;

  /* check the function name */
  sym = lookupid(funcname);
  if(!sym)
    sym = installfunc(funcname,ty,stclass,funcdecl->dec->coord);
  //else if(sym->symty->tyclass != POINTERTYPE || sym->symty->bty->tyclass != FUNCTIONTYPE){
  else if(sym->symty->tyclass != FUNCTIONTYPE){
    fatal(&funcdecl->base.coord, "redeclaration of symbol %s as function",funcname);
    return;
  }else{
    if(sym->symclass == EXTERN && stclass == STATIC){
      fatal(&funcdecl->base.coord, "function definition has conflict linkage class");
      return;
    }
    if(!compatibletypes(ty,sym->symty)){
      fatal(&funcdecl->base.coord, "function definition has incompatible types with previous declaration");
      return;
    }else
      sym->symty = composetypes(ty,sym->symty);
 
   if(sym->defined){
      fatal(&funcdecl->base.coord, "trying to redefine a function");
      return;
    }
  }

  /* add all parameter variables into symbol table & check compound statement */
  funcdecl->sym = sym;
  curfunc = funcdecl;
  enterscope();
  param = fty->params;
  while(param){
    Symbol *paramsym;
    if(lookupty(param->name)){
      fatal(&funcdecl->base.coord, "parameter name has already been used as type name before");
      return;
    }
    paramsym = installvar(param->name,param->ty,param->inreg ? REGISTER : AUTO,0,param->coord);
    listappend(paramsym,&curfunc->params);
    //NEW0(paramsym->defuse);
    param = param->next;
  }
  assert(funcdecl->stmt);
  cmpdstmtchk(funcdecl->stmt,0);
  exitscope();

  /* check undefined labels and return type for function definition */
  n = funcdecl->labels.head;
  while(n){
    sym = (Symbol*)n->data;
    if(!sym->defined){
      fatal(&sym->coord, "label %s not defined in function declaration",sym->symname);
      return;
    }
    n = n->next;
  }
  if(fty->base.bty != gettype(VOIDTYPE) && !funcdecl->hasreturn)
    warning(&funcdecl->base.coord, "function definition %s missing return value",funcdecl->sym->symname);
}

static void extdeclchk(ASTBase *dec)
{
  if(dec->astclass == AST_DECLARATION)
    gdeclchk(container_of(dec,ASTDeclaration,base));
  else if(dec->astclass == AST_FUNCTION)
    funcchk(container_of(dec,ASTFunctiondeclaration,base));
  else assert(0);
}

void astchk(void)
{
  foreach(translationunit->extdecls,extdeclchk);
}
