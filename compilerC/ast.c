/*
**Definition of abstract syntax tree for HCC 1.0
**This code is based on various open resources, intented for educational
**purposes only. You can access, modify this for your personal use freely,
**but any attempts for comercial exploitation from this code are considered 
**unethical and should be discouraged.
*/

#include "c.h"
#include "parser.h"

Typename *typedefnames;

extern Coordinate tcoord;

EXPORT int check_typedef(char *id)
{
  Typename *p;

  p = typedefnames;
  while(p) {
    if(!strcmp(id,p->tyname)/* && p->scope <= curscope() && !p->shadow*/)
      return 1;
    p = p->next;
  }
  return 0;
}

static void add_typedef(char *id)
{
  Typename *p;
  NEW0(p);
  p->tyname = id;
  p->next = typedefnames;
  typedefnames = p;
}

EXPORT ASTTranslationunit * create_translationunit(ASTBase* extdecls)
{
  ASTTranslationunit * astTU;

  NEW0(astTU);
  astTU->base.astclass = AST_TRANSLATIONUNIT;
  //for non-terminals, set its coord to its first child's coord
  astTU->base.coord = extdecls->coord;
  astTU->extdecls = extdecls;

  return astTU;
}

static char* tydefid(ASTBase *dec)
{
  switch(dec->astclass){
    case AST_DECLARATOR:
      return container_of(dec,ASTDeclarator,base)->name;
    case AST_POINTERDECLARATOR:
      return tydefid(container_of(dec,ASTPointerdeclarator,base)->dec);
    case AST_ARRAYDECLARATOR:
      return tydefid(container_of(dec,ASTArraydeclarator,base)->decbase);
    case AST_FUNCTIONDECLARATOR:
      return tydefid(container_of(dec,ASTFunctiondeclarator,base)->basedec);
    default: 
      assert(0);
      return NULL;
  }
}

static void create_tydefs(ASTSpecifier *specs, ASTBase *initdecs)
{
  char *id = NULL;
  ASTBase *init = initdecs;

  assert(init);
  while(init){
    id = tydefid(container_of(init,ASTInitdeclarator,base)->dec);
    if(!id)
      warning(&init->coord,"useless type name in empty declaration");
    else
      add_typedef(id);
    init = init->next;
  }
}

/* fake a dummy specifier */
static ASTSpecifier * fakespec(Coordinate coord)
{
  ASTSpecifier *spec;
  Tvalue tval;

  tval.ll = 0ll;
  NEW0(spec);
  spec->base.astclass = AST_SPECIFIER;
  spec->base.coord = coord;
  spec->typespecs = base_of(create_atom(INT,tval,coord));
  return spec;
}

EXPORT ASTDeclaration * create_declaration(ASTBase *specbase, ASTBase *initdecls)
{
  ASTDeclaration *astDecl;
  ASTSpecifier *specs;

  if(!specbase){
    warning(&initdecls->coord,"data/function declaration missing type or storage class (default to int)");
    specs = fakespec(initdecls->coord);
    specbase = &specs->base;
  }else{
    //get the ASTSpecifier pointer from ASTBase pointer member
    specs = container_of(specbase,ASTSpecifier,base);
  }

  if(specs->stclass == TYPEDEF)
    create_tydefs(specs,initdecls);
  NEW0(astDecl);
  //NEW0(astDecl->base);
  astDecl->base.astclass = AST_DECLARATION;
  //for non-terminals, set its coord to its first child's coord
  astDecl->base.coord = specbase->coord;
  astDecl->specs = specs;
  astDecl->initdecls = initdecls;
  return astDecl;
}

EXPORT ASTFunctiondeclaration * create_functiondeclaration(ASTBase *specsbase,
                       ASTBase *decbase, ASTBase *declist, ASTBase *stmtbase) 
{
  ASTFunctiondeclaration * fdecl;
  //  printf("FUNC %x %x\n", declist, specsbase);
  NEW0(fdecl);
  //NEW0(fdecl->base);
  //decbase is the function declarator

  fdecl->base.astclass = AST_FUNCTION;
  //for non-terminals, set its coord to its first child's coord
  if(specsbase!=NULL)
    fdecl->base.coord = specsbase->coord;
  else 
    fdecl->base.coord = decbase->coord;

  if(specsbase)
    fdecl->specs = container_of(specsbase,ASTSpecifier,base);
  fdecl->dec = decbase;
  fdecl->paramdecls = declist;
  fdecl->stmt = container_of(stmtbase,ASTCmpdstmt,base);

  return fdecl;
}

EXPORT ASTEnumspecifier * create_enumspec(ASTBase *enumatom, ASTBase *id, ASTBase *enumerators)
{
  ASTEnumspecifier *enumspec;
  assert(id!=NULL);

  NEW0(enumspec);
  //NEW0(enumspec->base);
  enumspec->base.astclass = AST_ENUMSPECIFIER;
  enumspec->base.coord = enumatom->coord;
  enumspec->id = container_of(id,ASTAtom,base);
  enumspec->enumerators = enumerators;
  return enumspec;
}

/*
static void casechk(ASTBase *b)
{
  int flag = 0;
  ASTLabeledstmt *s;
  while(b){
    if(b->astclass == AST_LABELEDSTMT){
      s = container_of(b,ASTLabeledstmt,base);
      if(s->idexpr)
        printf("fish case %d:\n",((ASTExpression*)s->idexpr)->val.i[0]);
      else printf("fish default:\n");
      flag = 1;
    }
    b = b->next;
  }
  if(flag)
  printf("!!!!!!!!\n");
}
*/

EXPORT ASTBase * append_astnode(ASTBase *astlist, ASTBase *astnode)
{
  ASTBase * p;

  assert(astlist != NULL && astnode != NULL);
  assert(astnode->next == NULL);

  p = astlist;
  while(p->next)
    p = p->next;
  p->next = astnode;

  return astlist;
}

/*
**There are 6 variations for the declaration specifier constructor, for two reasons:
** A. Make sure the top declaration_specifiers nonterminal can track its coord correctly.
** B. To make the code simple, and easily understandable.
*/
EXPORT ASTSpecifier * create_declarationspecifier1(ASTBase *sclass)
{
  ASTAtom *st;
  ASTSpecifier *spec;
  
  NEW0(spec);

  //NEW0(spec->base);
  spec->base.astclass = AST_SPECIFIER;
  spec->base.coord = sclass->coord;
  spec->sclass = sclass;

  st = container_of(sclass,ASTAtom,base);
  if(st->tok == TYPEDEF)
    spec->stclass = st->tok;

  return spec;
}

EXPORT ASTSpecifier * create_declarationspecifier2(ASTBase *sclass, ASTBase * specbase)
{
  ASTAtom *st;
  ASTSpecifier * spec;

  assert(specbase != NULL && sclass != NULL);
  /* adjust the coordinate */
  specbase->coord = sclass->coord;
  spec = container_of(specbase,ASTSpecifier,base);
  sclass->next = spec->sclass;
  spec->sclass = sclass;

  st = container_of(sclass,ASTAtom,base);
  if(st->tok == TYPEDEF)
    spec->stclass = st->tok;

  return spec;
}

EXPORT ASTSpecifier * create_declarationspecifier3(ASTBase *tyspec)
{
  ASTSpecifier *spec;

  NEW0(spec);
  //NEW0(spec->base);
  spec->base.astclass = AST_SPECIFIER;
  spec->base.coord = tyspec->coord;
  spec->typespecs = tyspec;

  return spec;
}

EXPORT ASTSpecifier * create_declarationspecifier4(ASTBase *tyspec, ASTBase * specbase)
{
  ASTSpecifier * spec;

  assert(specbase != NULL);
  /* adjust the coordinate */
  specbase->coord = tyspec->coord;

  /* insert the type specifier */
  spec = container_of(specbase,ASTSpecifier,base);
  tyspec->next = spec->typespecs;
  spec->typespecs = tyspec;

  return spec;
}

EXPORT ASTSpecifier * create_declarationspecifier5(ASTBase *tyqual)
{
  ASTSpecifier *spec;

  NEW0(spec);
  //NEW0(spec->base);
  spec->base.astclass = AST_SPECIFIER;
  spec->base.coord = tyqual->coord;
  spec->qual = tyqual;

  return spec;
}

EXPORT ASTSpecifier * create_declarationspecifier6(ASTBase *tyqual, ASTBase * specbase)
{
  ASTSpecifier * spec;

  assert(specbase != NULL);
  /* adjust the coordinate */
  specbase->coord = tyqual->coord;

  spec = container_of(specbase,ASTSpecifier,base);
  tyqual->next = spec->qual;
  spec->qual = tyqual;

  return spec;
}

EXPORT ASTAtom * create_atom(int tok, Tvalue tval, Coordinate tcoord)
{
  ASTAtom *atom;

  NEW0(atom);
  //NEW0(atom->base);
  atom->base.astclass = AST_ATOM;
  atom->base.coord = tcoord;
  atom->tok = tok;
  atom->tval = tval;
  return atom;
}

EXPORT ASTEnumerator * create_enumerator(ASTBase *id, ASTBase *cexprbase)
{
  ASTEnumerator * enu;
  
  assert(id!=NULL);
  NEW0(enu);
  //NEW0(enu->base);
  enu->base.astclass = AST_ENUMERATOR;
  enu->base.coord = id->coord;
  enu->id = container_of(id,ASTAtom,base);

  if(cexprbase)
    enu->cexpr = container_of(cexprbase,ASTExpression,base);

  return enu;
}

EXPORT ASTSUSpecifier * create_structorunion(ASTBase *subase, ASTBase *id, ASTBase *decls)
{
  ASTSUSpecifier *suspec;
  ASTAtom *su;

  NEW0(suspec);
  //NEW0(suspec->base);

  su = container_of(subase,ASTAtom,base);
  if(su->tok == STRUCT)
    suspec->base.astclass = AST_STRUCTSPECIFIER;
  else
    suspec->base.astclass = AST_UNIONSPECIFIER;
  suspec->base.coord = subase->coord;
  if(id)
    suspec->id = container_of(id,ASTAtom,base);
  suspec->sudecls = decls;

  return suspec;
}

EXPORT ASTStructdeclaration *create_structdeclaration(ASTBase *specs, ASTBase *decls)
{
  ASTStructdeclaration * dec;
  
  NEW0(dec);
  //NEW0(dec->base);
  dec->base.astclass = AST_STRUCTDECLARATION;
  dec->base.coord = specs->coord;
  dec->specs = container_of(specs,ASTSpecifier,base);
  dec->stdecls = decls;

  return dec;
}

EXPORT ASTStructdeclarator * create_structdeclarator(ASTBase *decbase, ASTBase *cexprbase)
{
  ASTStructdeclarator *decl;

  NEW0(decl);
  //NEW0(decl->base);
  decl->base.astclass = AST_STRUCTDECLARATOR;
  if(decbase)
    decl->base.coord = decbase->coord;
  else decl->base.coord = cexprbase->coord;
  decl->dec = decbase;
  if(cexprbase)
    decl->cexpr = container_of(cexprbase,ASTExpression,base);

  return decl; 
}

EXPORT ASTPointerdeclarator * chain_pointerdeclarator(ASTBase *pbase, ASTBase *directbase)
{
  ASTPointerdeclarator * pdec;
  ASTBase *adec;

  assert(pbase!=NULL && directbase!=NULL);
  pdec = container_of(pbase,ASTPointerdeclarator,base);

  if(!pdec->dec){
    pdec->dec = directbase;
    return pdec;
  }

  //pointer chaining
  adec = pdec->dec;
  assert((adec)->astclass == AST_POINTERDECLARATOR);
  while((adec)->astclass == AST_POINTERDECLARATOR){
    ASTPointerdeclarator *p = container_of(adec,ASTPointerdeclarator,base);
    if(p->dec){
      assert(p->dec->astclass == AST_POINTERDECLARATOR);
      adec = p->dec;
    }else{
      p->dec = directbase;
      break;
    }
  }

  return pdec;
}

EXPORT ASTPointerdeclarator * create_pointerdeclarator(Coordinate coord, ASTBase *tyquals, 
                                                       ASTBase *pdeclistbase)
{
  ASTPointerdeclarator * pdec;

  NEW0(pdec);
  //NEW0(pdec->base);
  pdec->base.astclass = AST_POINTERDECLARATOR;
  pdec->base.coord = coord;
  pdec->dec = pdeclistbase;
  pdec->tyquals = tyquals;

  return pdec;
}

/* variable declarator */
EXPORT ASTDeclarator * create_directdeclarator(ASTBase *idbase)
{
  ASTDeclarator *dec;
  ASTAtom *id;

  id = container_of(idbase,ASTAtom,base);
  NEW0(dec);
  //NEW0(dec->base);
  dec->base.astclass = AST_DECLARATOR;
  dec->base.coord = idbase->coord;
  dec->name = (char*)(id->tval.p);

  return dec;
}

EXPORT ASTDeclarator * create_abstractdeclarator(Coordinate coord)
{
  ASTDeclarator *dec;

  NEW0(dec);
  //NEW0(dec->base);
  dec->base.astclass = AST_ABSTRACTDECLARATOR;
  dec->base.coord = coord;

  return dec;
}

EXPORT ASTArraydeclarator * create_arraydeclarator(ASTBase *decbase, ASTBase *exprbase)
{
  ASTArraydeclarator *dec;
  //ASTExpression *cexpr;

  NEW0(dec);
  //NEW0(dec->base);
  dec->base.astclass = AST_ARRAYDECLARATOR;
  dec->base.coord = decbase->coord;
  dec->decbase = decbase;

  if(exprbase)
    dec->cexpr = container_of(exprbase,ASTExpression,base);

  return dec;
}

EXPORT ASTFunctiondeclarator *create_funcdeclarator(ASTBase *dec,
                  ASTBase *paramtypesbase, ASTBase *paramidsbase)
{
  ASTFunctiondeclarator *funcdec;
  //printf("funcdeclarator %x\n", paramidsbase);
  if(paramidsbase) {
    ASTBase* h = paramidsbase;
    while(h) {
      //      printf("ID %s\n", container_of(h, ASTAtom, base)->tval.p);
      h = h->next;
    }
  }
  NEW0(funcdec);
  //NEW0(funcdec->base);
  funcdec->base.coord = dec->coord;
  funcdec->base.astclass = AST_FUNCTIONDECLARATOR;
  funcdec->basedec = dec;
  funcdec->idlist = paramidsbase;
  if(paramtypesbase)
    funcdec->paramtypelist = container_of(paramtypesbase,ASTParamtypelist,base);

  return funcdec;
}

EXPORT ASTParamtypelist * create_paramtypelist(ASTBase *paramlist, int ellipsis)
{
  ASTParamtypelist * pty;

  NEW0(pty);
  //NEW0(pty->base);
  pty->base.astclass = AST_PARAMTYPELIST;
  if(paramlist)
    pty->base.coord = paramlist->coord;
  else pty->base.coord = tcoord;
  pty->paramdecls = paramlist;
  pty->ellipsis = ellipsis;

  return pty;
}

EXPORT ASTParamdeclaration * create_paramdeclaration(ASTBase *specsbase, ASTBase *decbase)
{
  ASTParamdeclaration * paramdecl;

  assert(specsbase!=NULL);
  NEW0(paramdecl);
  //NEW0(paramdecl->base);
  paramdecl->base.astclass = AST_PARAMDECLARATION;
  paramdecl->base.coord = specsbase->coord;
  paramdecl->specs = container_of(specsbase,ASTSpecifier,base);
  paramdecl->dec = decbase;
  
  return paramdecl;
}

EXPORT ASTInitdeclarator * create_initdeclarator(ASTBase *dec, ASTBase *initbase)
{
  ASTInitdeclarator *initdec;

  NEW0(initdec);
  //NEW0(initdec->base);
  initdec->base.astclass = AST_INITDECLARATOR;
  initdec->base.coord = dec->coord;
  initdec->dec = dec;

  if(initbase)
    initdec->init = container_of(initbase,ASTInitializer,base);

  return initdec;
}

EXPORT ASTInitializer * create_initializer(int lbrace,ASTBase * base)
{
  ASTInitializer *init;

  NEW0(init);
  //NEW0(init->base);
  init->base.astclass = AST_INITIALIZER;
  init->base.coord = base->coord;
  init->lbrace = lbrace;
  if(lbrace){
    //printf("init u %d %d\n", init->u.intials);
    init->u.initials = base;
  }
  else {
    init->u.expr = container_of(base,ASTExpression,base);
  }
  return init;
}

EXPORT ASTExpression * create_binaryexpression(int op, ASTBase *l, ASTBase *r)
{
  ASTExpression *e;

  NEW0(e);
  //NEW0(e->base);
  e->base.astclass = AST_EXPRESSION;
  e->base.coord = l->coord;
  e->op = op;
  e->kids[0] = container_of(l,ASTExpression,base);
  e->kids[1] = container_of(r,ASTExpression,base);

  return e;
}

EXPORT ASTExpression * create_binaryexpression1(ASTBase * op, ASTBase *l, ASTBase *r)
{
  ASTExpression *e;

  NEW0(e);
  //NEW0(e->base);
  e->base.astclass = AST_EXPRESSION;
  e->base.coord = l->coord;
  e->op = (container_of(op,ASTAtom,base))->tok;
  e->kids[0] = container_of(l,ASTExpression,base);
  e->kids[1] = container_of(r,ASTExpression,base);

  return e;
}

EXPORT ASTExpression * create_unaryexpression1(ASTBase *op, ASTBase *tyname)
{
  ASTExpression *e;

  NEW0(e);
  //NEW0(e->base);
  e->base.astclass = AST_EXPRESSION;
  e->base.coord = op->coord;
  e->op = (container_of(op,ASTAtom,base))->tok;
  e->unary = 1;
  e->tyname = container_of(tyname,ASTTypename,base);

  return e;
}

EXPORT ASTExpression * create_unaryexpression(ASTBase *op, ASTBase *expr)
{
  ASTExpression *e;

  NEW0(e);
  //NEW0(e->base);
  e->base.astclass = AST_EXPRESSION;
  e->base.coord = op->coord;
  e->op = (container_of(op,ASTAtom,base))->tok;
  e->unary = 1;
  e->kids[0] = container_of(expr,ASTExpression,base);

  return e;
}

EXPORT ASTExpression * create_castexpression(int op,ASTBase *tyname, ASTBase *expr)
{
  ASTExpression *e;

  NEW0(e);
  //NEW0(e->base);
  e->base.astclass = AST_EXPRESSION;
  e->base.coord = tyname->coord;
  e->op = op;
  e->unary = 1; 
  e->tyname = container_of(tyname,ASTTypename,base);
  e->kids[0] = container_of(expr,ASTExpression,base);
  return e;
}

EXPORT ASTExpression * create_postfixexpression(int op,ASTBase *expr1, ASTBase *expr2)
{
  ASTExpression *e;

  NEW0(e);
  //NEW0(e->base);
  e->base.astclass = AST_EXPRESSION;
  e->base.coord = expr1->coord;
  e->op = op; 
  e->unary = 1;
  e->kids[0] = container_of(expr1,ASTExpression,base); 

  /* Note: use this place holder for these ops */
  if(op==CALL_OP || op==MEMBER_OP || op==PTR_OP || op==POST_INC_DEC_OP)
    {
      //      printf("e->kids %s\n", e->kids[0]->val.p);
      e->kids[1] = (ASTExpression*)expr2; 
    }
  else
    e->kids[1] = container_of(expr2,ASTExpression,base);

  return e;
}

EXPORT ASTTypename * create_typename(ASTBase *specbase, ASTBase *dec)
{
  ASTTypename *tn;

  NEW0(tn);
  //NEW0(tn->base);
  tn->base.astclass = AST_TYPENAME;
  tn->base.coord = specbase->coord;
  tn->dec = dec;
  tn->spec = container_of(specbase,ASTSpecifier,base);

  return tn;
}

EXPORT ASTExpression *create_primaryexpression(ASTBase *atombase)
{
  ASTExpression *e;
  ASTAtom * a = container_of(atombase,ASTAtom,base);

  NEW0(e);
  //NEW0(e->base);
  e->base.astclass = AST_EXPRESSION;
  e->base.coord = atombase->coord;
  e->op = a->tok;
  e->unary = 1;
  e->val = a->tval;

  return e;
}

EXPORT ASTExpression *create_conditionalexpression(int op, ASTBase *cond, ASTBase *l, ASTBase *r)
{
  ASTExpression *e;

  NEW0(e);
  //NEW0(e->base);
  e->base.astclass = AST_EXPRESSION;
  e->base.coord = cond->coord;
  e->op = op;
  e->kids[0] = container_of(cond,ASTExpression,base);
  e->kids[1] = container_of(l,ASTExpression,base);
  e->kids[2] = container_of(r,ASTExpression,base);

  return e;
}

EXPORT ASTCmpdstmt *create_compoundstmt(Coordinate coord, ASTBase *declist, ASTBase *stmtlist)
{
  ASTCmpdstmt *cmpd;

  NEW0(cmpd);
  //NEW0(cmpd->base);
  cmpd->base.astclass = AST_COMPOUNDSTMT;
  cmpd->base.coord = coord;
  cmpd->declist = declist;
  cmpd->stmtlist = stmtlist;

  return cmpd;
}

EXPORT ASTLabeledstmt *create_labelstmt(int labeltype, Coordinate coord, ASTBase *idexpr, ASTBase *stmt)
{
  ASTLabeledstmt *lstmt;

  NEW0(lstmt);
  //NEW0(lstmt->base);
  lstmt->base.astclass = AST_LABELEDSTMT;
  lstmt->base.coord = coord;
  lstmt->type = labeltype;
  if(labeltype == IDLABEL)
    lstmt->idexpr = container_of(idexpr,ASTAtom,base);
  else if(labeltype == CASELABEL)
    lstmt->idexpr = container_of(idexpr,ASTExpression,base);
  lstmt->stmt = stmt;

  return lstmt;
}

EXPORT ASTExprstmt *create_exprstmt(Coordinate coord, ASTBase *exprbase)
{
  ASTExprstmt *estmt;

  NEW0(estmt);
  //NEW0(estmt->base);
  estmt->base.astclass = AST_EXPRESSIONSTMT;
  estmt->base.coord = coord;
  if(exprbase)
    estmt->expr = container_of(exprbase,ASTExpression,base);

  return estmt;
}

EXPORT ASTSelstmt *create_selstmt(int type, Coordinate coord, ASTBase *ebase, ASTBase *tstmt, ASTBase *fstmt)
{
  ASTSelstmt *sel;

  NEW0(sel);
  //NEW0(sel->base);
  sel->base.astclass = AST_SELECTIONSTMT;
  sel->base.coord = coord;
  sel->expr = container_of(ebase,ASTExpression,base);
  sel->truestmt = tstmt;
  sel->falsestmt = fstmt;
  sel->type = type;

  return sel;
}

EXPORT ASTIterationstmt *create_iterationstmt(int type, Coordinate coord,
                  ASTBase *exprbase, ASTBase *stmt, ASTBase *exprstmt1, ASTBase *exprstmt2)
{
  ASTIterationstmt *iterstmt;

  NEW0(iterstmt);
  //NEW0(iterstmt->base);
  iterstmt->base.astclass = AST_ITERATIONSTMT;
  iterstmt->base.coord = coord;
  if(exprbase)
    iterstmt->expr = container_of(exprbase,ASTExpression,base);
  iterstmt->stmt = stmt;
  if(exprstmt1)
    iterstmt->exprstmt[0] = container_of(exprstmt1,ASTExprstmt,base);
  if(exprstmt2)
    iterstmt->exprstmt[1] = container_of(exprstmt2,ASTExprstmt,base);
  iterstmt->type = type;

  return iterstmt;
}

EXPORT ASTJumpstmt * create_jumpstmt(int type, Coordinate coord, ASTBase *p)
{
  ASTJumpstmt *jstmt;

  NEW0(jstmt);
  //NEW0(jstmt->base);
  jstmt->base.astclass = AST_JUMPSTMT;
  jstmt->base.coord = coord;
  jstmt->type = type;
  if(type == GOTOSTMT){
    assert(p!=NULL);
    jstmt->idexpr = container_of(p,ASTAtom,base);
  }else if(type == RETURNSTMT) {
    if(p)
      jstmt->idexpr = container_of(p,ASTExpression,base);
  } 

  return jstmt;
}
