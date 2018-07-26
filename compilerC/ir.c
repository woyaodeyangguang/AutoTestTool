/*
**Intermediate code generation for HCC 1.0
**This code is based on various open resources, intented for educational
**purposes only. You can access, modify this for your personal use freely,
**but any attempts for comercial exploitation from this code are considered 
**unethical and should be discouraged.
*/
#include "c.h"
#include "parser.h"
#include <string.h>
/* Intermediate codes are organized into function bodies */
EXPORT List funcirs;
static Funcir *curfuncir;
static BBlock *curblock;
/* IR table to hold common subexpression */
static IRNode *IRtbl[16];
int BUILTINS;
/* current function declaration */
//extern ASTFunctiondeclaration *curfunc;
extern ASTTranslationunit * translationunit;

char* builtin[BUILTIN] = {
  "login",
  "logout",
  "expectToSee",
  "expectNotToSee",
  "expectToSeeValue",
  "expectNotToSeeValue",
  "expectToSeeLinkText",
  "expectNotToSeeLinkText",
  "expectToSeeTextInTable",
  "expectNotToSeeTextInTable",
  "expectToSeeText",
    "expectToSeePartialText",
  "findFieldTextInTable",
  "clickLink",
  "click",
  "clickTableCheckBox",
  "clickFieldInTable",
  "clickRandomFieldInTable",
  "clickCheckBoxInTree",
  "feedTextBox",
  "selectDropDownBox",
    "selectDropDownBoxByText",
  "closeBrowser",
  "expectNotToSeeRowInTable",
  "dropDownBoxNotToSeeValue",
  "dropDownBoxToSeeValue",
  "dropDownBoxToSeeText",
  "dropDownBoxNotToSeeText",
  "tableNotToSeeItem",
  "tableToSeeItem",
  "expectEnable",
  "expectDisable",
  "expectToSeeAttrValue",
    "expectNotToSeeAttrValue",
    "expectToSeeValueInTextBox",
    "expectToSeeValueInDropDownBox",
    "expectToSeeAttrValueInTable",
    "expectToSeePartialAttrValueInTable",
    "expectToSeeAttrValueForLinkText",
    "expectNotToSeeAttrValueForLinkText",
    "expectToSeeCheckBoxCheckedInTree",
    "sendEnterKey",
    "sendTab",
    "sleep",
    "getFieldTextInTable",
    "clearTextBox",
    "acceptAlert",
    "dismissAlert",
    "switchToFrame",
    "switchToDefaultContent",
    "dropDownBoxToSeeSelectedText",
    "uploadFile",
    "initTableHeaderInfo",
    "selectDropDownBoxByIndex",
    "expectNotToSeeCheckBoxCheckedInTree"
};
static int TEST;
static int numLists;
static char lists[256][256];

/* define them before use */
static void installir(IR *ir);
static void clruses(Symbol *sy);
static void jumpir(BBlock *target);
static void stmtirgen(ASTBase *stmt, int ret);
static Symbol * exprgen(ASTExpression *expr, int print);
static Symbol *cexprgen(ASTExpression *expr, int print);
static Symbol * assignexprgen(ASTExpression *expr, int print);
static void movir(Type *ty, Symbol *d, Symbol *s);
static Symbol *condexprgen(ASTExpression *expr, int print);
static Symbol * rbitfield(Field *fld, Symbol *p);
static void indmovir(Type *ty, Symbol *l, Symbol *r);
//static void initgen(Symbol *b, int off, ASTInitializer *init);
static Symbol * simplify(Type *ty, int op, Symbol *s1, Symbol *s2);
static void branchir(Type *ty,BBlock *target,int opcode, Symbol *s1, Symbol *s2);
FILE* outputf;
static Symbol * tempvar(Type *ty)
{
  Symbol * p = newtsym(ty);
  listappend(p,&curfuncir->lids);
  return p;
}

/* build a new basic block */
static BBlock * newblock()
{
  BBlock *b;

  NEW0(b);
  //b->sym = blksym();
  //if(!curfuncir->bblist)
  //  curfuncir->bblist = b;
  return b;
}
int found_builtin(char* in) {
  int i;
  for(i=0;i<BUILTIN;i++) {
    if(strcmp(builtin[i], in) == 0) {
      return 1;
    }
  }
  return 0;
}
static int found_list(char* in) {
  int i;
   
  for(i=0;i<numLists;i++) {
    char name[256];
    //printf("LIST %s\n", lists[i]);
    sprintf(name, "%s%s", in, ".length");
    if(strcmp(name, lists[i]) == 0) {
      return 1;
    }
  }
  return 0;
}
static void startblock(BBlock *b)
{
  if(curblock){
    b->prev = curblock;
    curblock->next = b;
  }
  curblock = b;
}

/* generate IR code for id label */
static void idlabgen(ASTLabeledstmt *lstmt)
{
  Symbol *sym = (Symbol *)lstmt->idexpr;
  if(sym->ref > 0)
    startblock(newblock());
  stmtirgen(lstmt->stmt,1);
}

/* generate IR code for case label */
static void caselabgen(ASTLabeledstmt *lstmt)
{
  assert(lstmt->labelblk);
  startblock(lstmt->labelblk);
  stmtirgen(lstmt->stmt,1);
}

/* generate IR code for default label */
static void deflabgen(ASTLabeledstmt *lstmt)
{
  assert(lstmt->labelblk);
  startblock(lstmt->labelblk);
  stmtirgen(lstmt->stmt,1);
}

/* generate IR code for labeled statement */
static void labelirgen(ASTLabeledstmt *lstmt)
{
  switch(lstmt->type) {
  case IDLABEL:
    idlabgen(lstmt);
    break;
  case CASELABEL:
    caselabgen(lstmt);
    break;
  case DEFAULTLABEL:
    deflabgen(lstmt);
    break;
  default: assert(0);
  }
}

/* generate IR code to zeroing a memory region */
static void memsetir(Symbol *sym, int size)
{
  IR * ir;

  if(!size) return;

  NEW0(ir);
  ir->op = CLR;
  ir->ty = gettype(UCHARTYPE);
  ir->opr[0] = sym;
  ir->opr[1] = installintconst(size);
  ((Symbol*)ir->opr[1])->ref++;
  sym->ref++;
  installir(ir);  
}

/* generate IR code for local variable initialization */
static void idatagen(Symbol *b, List *offsets)
{
  Type *ty;
  Symbol *s;
  Symbol *d;
  Initdata *idata;
  Listnode *n = offsets->head;
  int count = 0;
  n = offsets->head;

  count = 0;
if(n) {
  idata = n->data;
  if(idata->expr){
    ty = idata->ty;
    //printf("TY is %d\n", ty->tyclass);
    s = exprgen(idata->expr, 1);
    //idata->expr->val.p = s;
    d = offsetsym(b,idata->offset,ty);
    movir(ty,d,s);
  }else{
    ty = idata->ty;
    d = offsetsym(b,idata->offset,ty->bty);
    memsetir(d,idata->size);
  }
  n = n->next;
    count++;
}

  while(n){
    idata = n->data;
    if(idata->expr){
      ty = idata->ty;
      //printf("TY is %d\n", ty->tyclass);

      fprintf(outputf,",");
      s = exprgen(idata->expr, 1);
      //idata->expr->val.p = s;
      d = offsetsym(b,idata->offset,ty);
      movir(ty,d,s);
    }else{
      ty = idata->ty;

      d = offsetsym(b,idata->offset,ty->bty);
      memsetir(d,idata->size);
    }
      count++;
    n = n->next;
  }

}

/* generate IR code for compound statement */
static void cmpdirgen(ASTCmpdstmt *cstmt)
{
  ASTBase *stmt;
  Listnode *localnode;
  Symbol *localsym;

  /* local variable declarations */
  localnode = cstmt->locals.head;
  while(localnode){
    localsym = localnode->data;

    localnode = localnode->next;
    /*if(TEST>0) {
      fprintf(outputf, "private ");
    }*/
    fprintf(outputf, "String");
    //check whether it is a list
    /*if(localsym->irdata.head) {
      int count = 0;
      Listnode * n = localsym->irdata.head;
      while(n) {
	n = n->next;
	count++;
      }
      if(count>1)
	fprintf(outputf, "[]");
    }*/
    if(found_list(localsym->symname)) {
                     fprintf(outputf, "[]");
                     }

    fprintf(outputf," %s", localsym->symname);
    
    if(localsym->irdata.head) {
      fprintf(outputf,"=");
          if(found_list(localsym->symname)) {
                     fprintf(outputf, "{");
                     }
      idatagen(localsym,&localsym->irdata);
          if(found_list(localsym->symname)) {
                     fprintf(outputf, "}");
                     }
    }
    fprintf(outputf, ";\n");
  }

  stmt = cstmt->stmtlist;
  while(stmt){
    stmtirgen(stmt,1);
    stmt = stmt->next;
  }
}

/* create the logical complementry of expression */
static ASTExpression *notexpr(ASTExpression *expr)
{
  ASTExpression *e;

  switch(expr->op){
  case OR_OP:
    expr->op = AND_OP;
    expr->kids[0] = notexpr(expr->kids[0]);
    expr->kids[1] = notexpr(expr->kids[1]);
    return expr;

  case AND_OP:
    expr->op = OR_OP;
    expr->kids[0] = notexpr(expr->kids[0]);
    expr->kids[1] = notexpr(expr->kids[1]);
    return expr;

#define RELOP(opr, cop)				\
    case opr:					\
      expr->op = cop;				\
      return expr;

    RELOP(EQ_OP,NE_OP)
      RELOP(NE_OP, EQ_OP)
      RELOP(GE_OP,'<')
      RELOP(LE_OP,'>')
      RELOP('<',GE_OP)
      RELOP('>',LE_OP)
#undef RELOP

  case '!':
    return expr->kids[0];

  default:
    NEW0(e);
    e->base.astclass = AST_EXPRESSION;
    e->base.coord = expr->base.coord;  
    e->op = '!';
    e->unary = 1;
    e->ty = gettype(INTTYPE);
    e->kids[0] = expr;
    return foldconst(e);
  }
}

/* generate IR code for type casting */
static void castmove(Type *ty, Symbol *sym, int op, Symbol *s1, Symbol *s2)
{
  IR *ir;
  //Defuse *def;

  sym->ref++;
  s1->ref++;
  if(s2) s2->ref++;

  NEW0(ir);
  ir->op = op;
  ir->opr[0] = sym;
  ir->opr[1] = s1;
  ir->opr[2] = s2;
  ir->ty = ty;
  installir(ir);

  sym->ir = ir;
  clruses(sym);
}

/* generate IR code for cast */
//I1,U1,I2,U2,I4,U4,I8,U8,F4,F8,V,B,TYPECODES,
static int cvtops[TYPECODES+1][TYPECODES+1] = 
  {
    /*     I1 U1 I2 U2 I4 U4 I8 U8 F4 F8 V B */
    /*I1*/{-1,-1,-1,-1,CVTI1I4,CVTI1U4,-1,-1,-1,-1,-1,-1 },
    /*U1*/{-1,-1,-1,-1,CVTU1I4,CVTU1U4,-1,-1,-1,-1,-1,-1 },
    /*I2*/{-1,-1,-1,-1,CVTI2I4,CVTI2U4,-1,-1,-1,-1,-1,-1 },
    /*U2*/{-1,-1,-1,-1,CVTU2I4,CVTU2U4,-1,-1,-1,-1,-1,-1 },
    /*I4*/{CVTI4I1,CVTI4U1,CVTI4I2,CVTI4U2,-1,-1,CVTI4I8,CVTI4U8,CVTI4F4,CVTI4F8,-1,-1 },
    /*U4*/{-1,-1,-1,-1,-1,-1,CVTU4I8,CVTU4I8,CVTU4F4,CVTU4F8,-1,-1 },
    /*I8*/{-1,-1,-1,-1,CVTI8I4,CVTI8U4,-1,-1,-1,-1,-1,-1 },
    /*U8*/{-1,-1,-1,-1,CVTU8I4,CVTU8U4,-1,-1,-1,-1,-1,-1 },
    /*F4*/{-1,-1,-1,-1,CVTF4I4,CVTF4U4,-1,-1,-1,CVTF4F8,-1,-1 },
    /*F8*/{-1,-1,-1,-1,CVTF8I4,CVTF8U4,-1,-1,CVTF8F4,-1,-1,-1 },
    /*V */{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1 },
    /*B */{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1 },
  };

static Symbol *castgen(Type *dty, Type *rty, Symbol *sym)
{
  Symbol *dsym;
  int stycode, dtycode, tycode;

  stycode = typecode(rty);
  dtycode = typecode(dty);
  assert(stycode < TYPECODES && dtycode < TYPECODES);
  tycode = cvtops[stycode][dtycode];
  assert(tycode >= 0);

  dsym = tempvar(dty);
  castmove(rty,dsym,tycode,sym,NULL);
  return dsym;
}

/* generate IR code for branch expression */
static void condgen(ASTExpression *expr, BBlock *tb, BBlock *fb, int print)
{
  BBlock *b;
  Symbol *s1, *s2;
  Type *ty;

  if(constop(expr->op)){
    if(expr->val.ll)
      jumpir(tb);
    return;
  }

  switch(expr->op) {
  case AND_OP:
    b = newblock();
    //changed it for Java
    condgen(expr->kids[0],fb,b, print);
    //condgen(notexpr(expr->kids[0]),fb,b, print);
    startblock(b);
    if(print == 1)
      fprintf(outputf,"&&");
    condgen(expr->kids[1],tb,fb, print);
    break;

  case OR_OP:
    b = newblock();
    condgen(expr->kids[0],tb,b, print);
    startblock(b);
    if(print == 1)
      fprintf(outputf,"||");
    condgen(expr->kids[1],tb,fb, print);
    break;

  case '!':
    s1 = exprgen(expr->kids[0], print);
    ty = expr->kids[0]->ty;
    if(ty->tyclass < INTTYPE){
      s1 = castgen(gettype(INTTYPE),ty,s1);
      ty = gettype(INTTYPE);
    }
    branchir(ty,tb,JZ,s1,NULL);
    break;

#define RELOP(tok, opcode)			\
    case tok:					\
      s1 = exprgen(expr->kids[0], print);	\
      s2 = exprgen(expr->kids[1], print);	\
      branchir(s1->symty,tb,opcode,s1,s2);	\
      break;

    //    RELOP(EQ_OP,JE)//case EQ_OP:
    //      RELOP(NE_OP,JNE)//case NE_OP:
      RELOP(GE_OP,JGE)//case GE_OP:
      RELOP(LE_OP,JLE)//case LE_OP:
#undef RELOP
      //    RELOP('>',JG)//case '>':
      //RELOP('<',JL)//case '<':
  case NE_OP:
    s1= exprgen(expr->kids[0], print);
    if(print == 1)
      fprintf(outputf,"!=");
    s2 = exprgen(expr->kids[1], print);
    branchir(s1->symty, tb, JL, s1, s2);
    break;    
  case EQ_OP:
          // fprintf(outputf, "EQ");
    s1= exprgen(expr->kids[0], print);
    if(print == 1)
      fprintf(outputf,"==");
    s2 = exprgen(expr->kids[1], print);
    branchir(s1->symty, tb, JL, s1, s2);
    break;    

  case '<':
    s1= exprgen(expr->kids[0], print);
    if(print == 1)
      fprintf(outputf,"%c", expr->op);
    s2 = exprgen(expr->kids[1], print);
    branchir(s1->symty, tb, JL, s1, s2);
    break;
  case '>':
    s1= exprgen(expr->kids[0], print);
    if(print == 1)
      fprintf(outputf,"%c", expr->op);
    s2 = exprgen(expr->kids[1], print);
    branchir(s1->symty, tb, JG, s1, s2);
    break;

  default:
    s1 = exprgen(expr, print);
    if(s1->symclass == SYM_CONST || s1->symclass == SYM_ENUMCONST){
      if(s1->symval.ll)
	jumpir(tb);
    }else{
      ty = expr->ty;
      if(ty->tyclass < INTTYPE){
	s1 = castgen(gettype(INTTYPE),ty,s1);
	ty = gettype(INTTYPE);
      }
      branchir(ty,tb,JNZ,s1,NULL);
    }
    break;
  }
}

/* append IR to current basic block */
static void installir(IR *ir)
{
  assert(curblock != NULL);
  curblock->nir++;
  ir->blk = curblock;
  if(curblock->irhead == NULL){
    curblock->irhead = curblock->irtail = ir;
    ir->prev = ir->next = NULL;
  }else{
    ir->prev = curblock->irtail;
    curblock->irtail->next = ir;
    curblock->irtail = ir;
  }
  //irinstecho(ir);
}

/* generate branch IR */
static void jumpir(BBlock *target)
{
  IR *ir;

  NEW0(ir);
  ir->op = JMP;
  ir->opr[0] = target;
  
  target->nref++;
  //if(!target->sym)
  //  target->sym = blksym();
  listappend(target,&curblock->takentgts);
  listappend(curblock,&target->jmpsrcs);
  installir(ir);
}

/* generate branch IR */
static void branchir(Type *ty,BBlock *target,int opcode, Symbol *s1, Symbol *s2)
{
  IR *ir;

  s1->ref++;
  if(s2) s2->ref++;

  NEW0(ir);
  ir->op = opcode;
  ir->opr[0] = target;
  ir->opr[1] = s1;
  ir->opr[2] = s2;
  ir->ty = ty;

  target->nref++;
  //if(!target->sym)
  //  target->sym = blksym();
  listappend(target,&curblock->takentgts);
  listappend(curblock,&target->jmpsrcs);
  installir(ir);

  //register the IR in the def-use chain
  /*
    assert(s1->defuse);
    listappend(ir,&s1->defuse->uses);

    if(s2){
    assert(s2->defuse);
    listappend(ir,&s2->defuse->uses);
    }
  */
}

/* generate move IR */
static void movir(Type *ty, Symbol *d, Symbol *s)
{
  IR *ir;
  //Defuse *def;

  d->ref++;
  s->ref++;
  NEW0(ir);
  ir->ty = ty;
  ir->op = MOV;
  ir->opr[0] = d;
  ir->opr[1] = s;
  installir(ir);

  clruses(d);
  d->ir = ir;
}

/* generate assignment IR */
static IR * assignir(Type *ty,Symbol *s,int opcode, Symbol *s1, Symbol *s2)
{
  IR *ir;

  s->ref++;
  s1->ref++;
  if(s2) s2->ref++;

  NEW0(ir);
  ir->op = opcode;
  ir->opr[0] = s;
  ir->opr[1] = s1;
  ir->opr[2] = s2;
  ir->ty = ty;

  installir(ir);

  s->ir = ir;
  clruses(s);
  return ir;
}

/*
**delete irnodes that can no longer be reused in future
*/
static void clruse(IRNode *irnode)
{
  IRNode *pre, *cur;
  IR *ir = irnode->ir;
  Symbol *s1 = ir->opr[1];
  Symbol *s2 = ir->opr[2];
  unsigned h = ((unsigned long)s1 + (unsigned long)s2 + ir->op) & (NELEMS(IRtbl)-1);

  pre = NULL;
  cur = IRtbl[h];
  while(cur){
    if(cur == irnode){
      if(pre)
        pre->link = cur->link;
      else IRtbl[h] = cur->link;
      return;
    }
    pre = cur;
    cur = cur->link;
  }
  assert(0);
}

static void clruses(Symbol *s)
{
  Listnode *p = s->iruses.head;
  while(p){
    clruse(p->data);
    p = p->next;
  }
  s->iruses.head = s->iruses.tail = NULL;
}

/* 
**generate IR for arithmetic (either binary/unary) operator 
**common subexpression elimination is performed here.
*/
static Symbol * arithir(Type *ty, int op, Symbol *s1, Symbol *s2)
{
  Symbol *s;
  IRNode *irnode;
  unsigned h = ((unsigned long)s1 + (unsigned long)s2 + op) & (NELEMS(IRtbl)-1);

  assert(curblock);
  if(op != ADDR && (s1->aliased || (s2 && s2->aliased) ))
    goto newnode;

  /* is there a common subexpression for reuse? */
  irnode = IRtbl[h];
  while(irnode){
    if(irnode->ir->op == op && irnode->ir->opr[1] == s1 && irnode->ir->opr[2] == s2 && 
       curblock == irnode->ir->blk)
      return irnode->ir->opr[0];
    irnode = irnode->link;
  }

  /* if not, build a temp var to hold the subexpression */
 newnode:
  NEW0(irnode);
  s = tempvar(ty);
  irnode->ir = assignir(ty,s,op,s1,s2);
  irnode->link = IRtbl[h];
  IRtbl[h] = irnode;

  listappend(irnode,&s1->iruses);
  if(s2) listappend(irnode,&s2->iruses);
  return s;  
}

/* generate IR code for unary ++/-- expression */
static Symbol * unaryincrgen(ASTExpression *expr, int print)
{
  int op;
  Symbol *s1, *s2, *s;
  ASTExpression *increxpr = expr->kids[0];

  s = tempvar(expr->ty);
  s1 = cexprgen(increxpr->kids[0], print);
  s2 = cexprgen(increxpr->kids[1], print);
  op = expr->op == INC_OP ? ADD:SUB;
  assignir(expr->ty,s,op,s1,s2);
  movir(expr->ty,s1,s);
  return s1;
}

/* generate IR code for & operator */
static Symbol * addrof(Symbol *sym)
{
  if(sym->symclass == SYM_TEMP && sym->ir->op == DEREF)
    return sym->ir->opr[1];

  sym->aliased = 1;

  return arithir(gettype(POINTERTYPE),ADDR,sym,NULL);
}

/* generate IR code for -> operator */
static Symbol * deref(Type *ty, Symbol *sym, Symbol *off)
{
  Symbol *p;

  if(sym->symclass == SYM_TEMP && sym->ir->op == ADDR && !off)
    return sym->ir->opr[1];

  p = tempvar(ty);
  assignir(ty,p,DEREF,sym,off);
  return p;
}

/* calculate array offset */
static Symbol * arrayoff(Type *ty, Symbol *b, Symbol *voff, int coff)
{
  if(voff){
    voff = simplify(gettype(INTTYPE),ADD,voff,installintconst(coff));
    b = simplify(gettype(POINTERTYPE),ADD,b,voff);
    return deref(ty,b,NULL);
  }

  if(b->symclass == SYM_TEMP && b->ir->op == ADDR)
    return offsetsym(b->ir->opr[1],coff,ty);

  return deref(ty,simplify(gettype(POINTERTYPE),ADD,b,installintconst(coff)),NULL);
}

/* generate IR code for array index expression */
static Symbol * indexgen(ASTExpression *expr, int print)
{
  int coff;
  ASTExpression *p;
  Symbol *voff, *base, *tgt;

  coff = 0; voff = NULL;
  p = expr;
  do {
    if(constop(p->kids[1]->op))
      coff += p->kids[1]->val.i[0];
    else if(!voff) {
      /*if(p->kids[1]->kids[0]) {
	//	printf("op %d\n", p->kids[1]->kids[0]->op);
	printf("INDEX %s\n", ((Symbol*)p->kids[1]->kids[0]->val.p)->symname);
	}*/
      voff = exprgen(p->kids[1], 0);
    }
    else 
      voff = simplify(voff->symty, ADD, voff, exprgen(p->kids[1], print));
    p = p->kids[0];
  }while(p->op == INDEX_OP && p->isarray);

  //  if(p->val.p)
  //      printf("INDEX %s\n", ((Symbol*)p->val.p)->symname);

  base = exprgen(p, print);
  fprintf(outputf, "[");
  p = expr;
  if(p->kids[1]->kids[0]) {
    fprintf(outputf, "%s", ((Symbol*)p->kids[1]->kids[0]->val.p)->symname);
  }
  fprintf(outputf, "]");
  tgt = arrayoff(expr->ty,base,voff,coff);
  return expr->isarray ? addrof(tgt) : tgt;
}

/* generate IR code for function call */
static void funcallgen(Type *ty, Symbol *retsym, Symbol *fsym, IRArg *arglist)
{
  IR *ir;
  IRArg *arg;
  //Defuse *def;

  if(retsym) retsym->ref++;
  fsym->ref++;

  NEW0(ir);
  ir->ty = ty;
  ir->op = CALL;
  ir->opr[0] = retsym;
  ir->opr[1] = fsym;
  ir->opr[2] = arglist;
  installir(ir);


  arg = arglist;
  while(arg){
    arg->sym->ref++;
    //listappend(ir,&arg->sym->defuse->uses);
    arg=arg->next;
  }
  fprintf(outputf,")");
  if(retsym){
    clruses(retsym);
    retsym->ir = ir;
  }
}

/* generate IR code for function call expression */
static Symbol * funcexprgen(ASTExpression *expr, int print)
{
  Symbol *fsym, *retsym = NULL;
  ASTBase *argb;
  ASTExpression *arg;
  IRArg *head, **tail;
  /*if(TEST>0) {
    fprintf(outputf, "@Test\npublic void Test%d() {\n", TEST);
    TEST++;
  }*/
  fsym = exprgen(expr->kids[0], print);

  fprintf(outputf,"(");
  argb = (ASTBase *)expr->kids[1];
  head = NULL;
  tail = &head;
  
  if(argb) {
    IRArg *argn;
    
    arg = container_of(argb,ASTExpression,base);
    NEW0(argn);
    argn->ty = arg->ty;
    argn->sym = exprgen(arg, print);
    *tail = argn;
    tail = &argn->next;
    argb = argb->next;
  }
  while(argb){
    IRArg *argn;
    fprintf(outputf,", ");
    arg = container_of(argb,ASTExpression,base);
    NEW0(argn);
    argn->ty = arg->ty;
    argn->sym = exprgen(arg, print);

    *tail = argn;
    tail = &argn->next;
    argb = argb->next;
  }  

  if(expr->ty->tyclass != VOIDTYPE)
    retsym = tempvar(expr->ty);

  funcallgen(expr->ty,retsym,fsym,head);
  /*
  if(TEST>0)
    fprintf(outputf, "}\n");
    */
  return retsym;
}

static Symbol * rbitfield(Field *fld, Symbol *p)
{
  Type *ty = fld->ty;
  int s = 8*fld->ty->size;
  int lb = s - fld->bits - fld->pos;
  int rb = s - fld->bits;
  Symbol *sym;

  assert(ty->tyclass == INTTYPE || ty->tyclass == UINTTYPE);
  if(ty->tyclass == INTTYPE){
    sym = simplify(gettype(INTTYPE),LSH,p,installintconst(lb));
    sym = simplify(gettype(INTTYPE),RSH,sym,installintconst(rb));
  }else {
    sym = simplify(gettype(UINTTYPE),LSH,p,installintconst(lb));
    sym = simplify(gettype(UINTTYPE),RSH,sym,installintconst(rb));
    sym = simplify(gettype(UINTTYPE),BAND,sym,installintconst(MASKBITS(fld->bits)));
  }
  sym->lvalsym = p;
  return sym;
}

/* generate IR code for struct/union member reference */
static Symbol * membergen(ASTExpression *expr, int print)
{
  int coff = 0;
  Field *fld;
  ASTExpression *p;
  Symbol * member, *b;

  p = expr;
  if(p->op == PTR_OP){
    fld = p->val.p;
    coff = fld->offset;
    b = exprgen(p->kids[0], print);
  }else{
    while(p->op == MEMBER_OP){
      fld = p->val.p;
      coff += fld->offset;
      p = p->kids[0];
    }
    b = addrof(exprgen(p, print));
  }
  member = arrayoff(expr->ty,b,NULL,coff);
  fld = member->symval.p = expr->val.p;
  if(fld->bits > 0)
    return rbitfield(fld,member);
  return expr->isarray ? addrof(member) : member;
}

/* generate IR code for post incremental expression */
static Symbol * postincrgen(ASTExpression *expr, int print)
{
  Symbol *t,*p;
  ASTExpression *increxpr;
  ASTExpression *texpr;

  increxpr = expr->kids[0];
  
  p = cexprgen(increxpr->kids[0],print);
  if(print==1)
    fprintf(outputf, "=");
  assert(!increxpr->bitfield);
  t = tempvar(expr->ty);
  movir(expr->ty,t,p);

  /*
  **Be careful here because p can actually be a temp:
  ** for example: foo()->member++
  */
  if(SYM_TEMP == p->symclass){
    NEW0(texpr);
    texpr->op = '=';
    texpr->ty = expr->ty;
    texpr->kids[0] = increxpr->kids[0];
    texpr->kids[1] = increxpr;
    assignexprgen(texpr, print);
  }else
    movir(expr->ty,p,cexprgen(increxpr, print));
  return t;
}

/* generate IR code for unary expression */
static Symbol * unarygen(ASTExpression *expr, int print)
{
  Symbol *sym = NULL;
  //fprintf(outputf,"Unary %d\n", expr->op);
  switch(expr->op) {
    /* unary operators */
  case '!':
    return condexprgen(expr, print);

  case INC_OP:
  case DEC_OP:
    return unaryincrgen(expr, print);

  case '&':
    sym = exprgen(expr->kids[0], print);
    return addrof(sym);

  case '*':
    sym = exprgen(expr->kids[0], print);
    return deref(expr->ty, sym,NULL);

  case '-':
    sym = exprgen(expr->kids[0], print);
    return simplify(expr->ty, NEG, sym, NULL);

  case '~':
    sym = exprgen(expr->kids[0], print);
    return simplify(expr->ty, BCOM, sym, NULL);

  case CAST_OP:
    sym = exprgen(expr->kids[0], print);
    return castgen(expr->ty,expr->kids[0]->ty,sym);

    /* postfix operators */
  case INDEX_OP:
    return indexgen(expr, print);

  case CALL_OP:
    return funcexprgen(expr, print);

  case MEMBER_OP:
  case PTR_OP:
    return membergen(expr, print);

  case POST_INC_DEC_OP:
    return postincrgen(expr, print); 
    break;

    /* primary expression */
  case INTCONST:
  case LINT:
  case UINT:
  case ULINT:
    if(1==print)
      fprintf(outputf,"%d", expr->val.i[0]);
    return installintconst(expr->val.i[0]);
  case LLINT:
  case ULLINT:
    if(1==print)
      fprintf(outputf,"%d", expr->val.i[0]);
    return installllconst(expr->val.ll);
  case DOUBLECONST:
  case LDOUBLECONST:
    return installdblconst(expr->val.d);
  case FLOATCONST:
    return installfltconst(expr->val.f);
  case STRING:
    if(1==print) {
     int len = strlen(((Symbol*)expr->val.p)->symval.p)*4;
     char* whole = malloc(len);
     char* init = malloc(len);
     char* next = malloc(len);
     char* initnext = next;
     strcpy(whole, ((Symbol*)expr->val.p)->symval.p);
     
      //Process "\\"
     //strcpy(whole, ((Symbol*)expr->val.p)->symval.p);
     strcpy(next, whole);
     strcpy(init, whole);
     
     char* sub = malloc(len);
     sub = (char*)strtok(init,"\\");
     
     //printf("Whole %s, %s\n", whole, init);
     if(strcmp(next, init) !=0) {
         next = next+strlen(sub);
         strcpy(whole, sub);
         //printf("OK\n");
         while(next[0]=='\\') {
                 strcat(whole, "\\\\");
                 next += 1;
         }
         //printf("first Sub %s, %s\n", whole, sub);
         sub = strtok(NULL, "\\");  
         strcat(whole,sub);         
         if(sub)
         {
                  next = next+strlen(sub);
         }
         while(next[0]=='\\') {
                 strcat(whole, "\\\\");
                 next += 1;
         }
         //printf("Then Sub %s %s\n", whole, sub);
         while(sub) {
             sub = strtok(NULL,"\\");
             if(sub) {
                      while(next[0]=='\\') {
                      strcat(whole, "\\\\");
                      next += 1;
                      }
                      if(sub)
                       {
                       next = next+strlen(sub);
                       }
                      strcat(whole,sub);
                      //printf("Sub %s, whole %s\n", sub, whole);
             }
         } 
     }

     next = initnext;
     strcpy(next, whole);
     strcpy(init, whole);
     sub = (char*)strtok(init,"\"");

     if(strcmp(next, init) !=0) {
                    
         next = next+strlen(sub);
         strcpy(whole, sub);
         //printf("OK\n");
         while(next[0]=='\"') {
                 strcat(whole, "\\\"");
                 next += 1;
         }
         //printf("first Sub %s, %s\n", whole, sub);
         sub = strtok(NULL, "\"");  
         strcat(whole,sub);         
         if(sub)
         {
                  next = next+strlen(sub);
         }
         while(next[0]=='\"') {
                 strcat(whole, "\\\"");
                 next += 1;
         }
         //printf("Then Sub %s %s\n", whole, sub);
         while(sub) {
             sub = strtok(NULL,"\"");
             if(sub) {
                      while(next[0]=='\"') {
                      strcat(whole, "\\\"");
                      next += 1;
                      }
                      if(sub)
                       {
                       next = next+strlen(sub);
                       }
                      strcat(whole,sub);
                      //printf("Sub %s, whole %s\n", sub, whole);
             }
         } 
     }

     fprintf(outputf,"\"%s\"", whole);//((Symbol*)expr->val.p)->symval.p);
 
     free(whole);
     free(next);
     free(init);
    }
    return addrof(expr->val.p);
  case IDENTIFIER:
    if(expr->isarray) {// || expr->isfunc
      if(1 == print) {
	       fprintf(outputf, "%s", ((Symbol*)expr->val.p)->symname);
        }
      return addrof(expr->val.p);
    }
    if(1==print) {
      if(found_builtin(((Symbol*)expr->val.p)->symname)) {
	fprintf(outputf,"base.%s", ((Symbol*)expr->val.p)->symname);
      }
      else {
	  fprintf(outputf,"%s", ((Symbol*)expr->val.p)->symname);

      }
    }
   
    return expr->val.p;
  default: assert(0);
  }

  return sym;
}

static Symbol *condexprgen(ASTExpression *expr, int print)
{
  Symbol *d, *s1, *s2;
  BBlock *tb, *fb, *cb;

  assert(expr->ty->tyclass != VOIDTYPE);
  d = tempvar(expr->ty);
  tb = newblock();
  fb = newblock();
  cb = newblock();

  condgen(expr->kids[0],tb,fb, print);
  startblock(fb);
  s2 = cexprgen(expr->kids[2], print);
  assert(s2 != NULL);
  movir(expr->ty,d,s2);
  jumpir(cb);
  
  startblock(tb);
  s1 = exprgen(expr->kids[1], print);
  assert(s1 != NULL);
  movir(expr->ty,d,s1);
  startblock(cb);

  return d;
}

/* generate IR code for logical binary expression */
static Symbol *logicalexprgen(ASTExpression * expr, int print)
{
  Symbol *sym;
  BBlock *tb,*fb,*cb;

  sym = tempvar(expr->ty);
  tb = newblock();
  fb = newblock();
  cb = newblock();

  condgen(expr,tb,fb, print);
  startblock(fb);
  movir(expr->ty,sym,installintconst(0));
  jumpir(cb);
  startblock(tb);
  movir(expr->ty,sym,installintconst(1));
  startblock(cb);

  return sym;
}

/* test if power of 2 */
static int powerof2(unsigned long long u)
{
  int i;

  if(u > 1 && (u&(u-1)) == 0){
    for(i=0;u;u>>=1,i++)
      if(u&1)
        return i;
  }
  return 0;
}

/* expression simplication */
static Symbol * simplify(Type *ty, int op, Symbol *s1, Symbol *s2)
{
  long long c1, c2;

  if(fptype(ty) || !s2 || (s2->symclass != SYM_CONST && op != '-'))
    return arithir(ty,op,s1,s2);

  switch(op) {
  case ADD:
    if(s2->symval.ll == 0ll)
      return s1;
    c1 = 0ll;
    if(s1->symclass == SYM_TEMP && s1->ir->opr[2] &&
       ((Symbol*)s1->ir->opr[2])->symclass == SYM_CONST &&
       (s1->ir->op == ADD || s1->ir->op == SUB)){
      s1 = s1->ir->opr[1];
      c1 = (s1->ir->op == ADD ? 1 : -1) * ((Symbol*)s1->ir->opr[2])->symval.ll;
    }
    if(c1)
      s2 = installllconst(c1 + s2->symval.ll);
    break;

  case SUB:
    if(s2->symclass == SYM_CONST && s2->symval.ll == 0ll)
      return s1;
    c1 = c2 = 0ll;
    if(s1->symclass == SYM_TEMP && s1->ir->opr[2] &&
       ((Symbol*)s1->ir->opr[2])->symclass == SYM_CONST &&
       (s1->ir->op == ADD || s1->ir->op == SUB)){
      s1 = s1->ir->opr[1];
      c1 = (s1->ir->op == ADD ? 1 : -1) * ((Symbol*)s1->ir->opr[2])->symval.ll;
    }else if(s1->symclass == SYM_CONST){
      c1 = s1->symval.ll;
      s1 = NULL;
    }

    if(s2->symclass == SYM_TEMP && s2->ir->opr[2] &&
       ((Symbol*)s2->ir->opr[2])->symclass == SYM_CONST &&
       (s2->ir->op == ADD || s2->ir->op == SUB)){
      s2 = s2->ir->opr[1];
      c2 = (s2->ir->op == ADD ? 1 : -1) * ((Symbol*)s2->ir->opr[2])->symval.ll;
    }else if(s2->symclass == SYM_CONST){
      c2 = s2->symval.ll;
      s2 = NULL;
    }

    if(s1 == s2)
      return installllconst(0);
    else if(!s1)
      s1 = installllconst(c1-c2);
    else if(!s2){
      op = ADD;
      s2 = installllconst(c1-c2);
    }
    break;

  case MUL:
  case DIV:
    if(s2->symval.ll == 1ll)
      return s1;
    c1 = powerof2(s2->symval.ll); 
    if(c1){
      s2 = installllconst(c1);
      op = op==MUL ? LSH:RSH;
    }     
    break;

  case MOD:
    if(s2->symval.ll == 1ll)
      return installintconst(0);
    c1 = powerof2(s2->symval.ll);
    if(c1){
      s2 = installllconst(s2->symval.ll-1);
      op = BAND;
    }
    break;

  case LSH:
  case RSH:
    if(s2->symval.ll == 0ll)
      return s1;
    break;

  case BOR:
    if(s2->symval.ll == 0ll)
      return s1;
    if(s2->symval.ll == -1ll)
      return s2;
    break;

  case BAND:
    if(s2->symval.ll == 0ll)
      return s2;
    if(s2->symval.ll == -1ll)
      return s1;
    break;

  case BXOR:
    if(s2->symval.ll == 0ll)
      return s1;
    break;
  default: assert(0);
  }
  return arithir(ty,op,s1,s2);
}

/* generate IR code for conditional expression */
static Symbol *cexprgen(ASTExpression *expr, int print)
{
  Symbol *s1, *s2;

  /* unary expression */
  if(expr->unary) {
    s1 = unarygen(expr, print);
    return s1;
}
  /* conditional expression ? : */
  if(expr->op == COND_OP)
    return condexprgen(expr, print);

  /* binary expression */
  switch(expr->op){
  case OR_OP:
  case AND_OP:
  case EQ_OP:
  case NE_OP:
  case '>':
  case '<':
  case GE_OP:
  case LE_OP:
    return logicalexprgen(expr, print);

#define BINOP(vop,rop)				\
    case vop:					\
      s1 = assignexprgen(expr->kids[0], print);	\
      s2 = cexprgen(expr->kids[1], print);	\
      return simplify(expr->ty,rop,s1,s2);

    BINOP('|',BOR)//case '|':
      BINOP('&',BAND)//case '&':
      BINOP('^',BXOR)//case '^':
      BINOP(RIGHT_SHIFT,RSH)//case RIGHT_SHIFT:
      BINOP(LEFT_SHIFT,LSH)//case LEFT_SHIFT:
      //    BINOP('+',ADD)//case '+':
      BINOP('-',SUB)//case '-':
      BINOP('*',MUL)//case '*':
      BINOP('/',DIV)//case '/':
      BINOP('%',MOD)//case '%':
#undef BINOP
  case '+':
    s1 = assignexprgen(expr->kids[0], print);
    if(1==print)
      fprintf(outputf,"+");
   
    s2 = cexprgen(expr->kids[1], print);
    return simplify(expr->ty,ADD,s1,s2);
      
  default: assert(0);
  }
  return NULL;
}

static void wbitfield(Field *f, Symbol *l, Symbol *r)
{
  unsigned fmask = MASKBITS(f->bits);
  unsigned mask = fmask << f->pos;
  Symbol *p;

  if(r->symclass == SYM_CONST && !r->symval.ll)
    p = simplify(gettype(INTTYPE),BAND,l,installintconst(~mask));
  else if(r->symclass == SYM_CONST && (r->symval.i[0] & fmask) == fmask)
    p = simplify(gettype(INTTYPE),BOR,l,installintconst(mask));
  else{
    if(r->symclass == SYM_CONST)
      r = installintconst((r->symval.i[0] << f->pos) & mask);
    else{
      r = simplify(gettype(INTTYPE),LSH,r,installintconst(f->pos));
      r = simplify(gettype(INTTYPE),BAND,r,installintconst(mask));
    }
    p = simplify(gettype(INTTYPE),BAND,l,installintconst(~mask));
    p = simplify(gettype(INTTYPE),BOR,p,r);
  }

  if(l->symclass == SYM_TEMP && l->ir->op == DEREF){
    Symbol *addrsym = l->ir->opr[1];
    indmovir(f->ty,addrsym,p);
    l = deref(f->ty,addrsym,NULL);
  }else
    movir(f->ty,l,p);
  //return rbitfield(f,l);
}

static void indmovir(Type *ty, Symbol *l, Symbol *r)
{
  IR *ir;

  NEW0(ir);
  ir->op = IMOV;
  ir->ty = ty;
  ir->opr[0] = l;
  ir->opr[1] = r;
  installir(ir);

  l->ref++;
  r->ref++;
  clruses(l);
}

/* generate IR code for assignment expression */
static Symbol * assignexprgen(ASTExpression *expr, int print)
{
  Symbol *l, *r;
  Field *f;
  int flag = 0;
  if(expr->op != '=')
    return cexprgen(expr, print);
//fprintf(outputf, "Left %d %s\n",expr->kids[0]->op, ((Symbol*)expr->kids[0]->val.p)->symname);   
  /* deal with assignment here */
 
                                                          
  l = exprgen(expr->kids[0], print);
  if(1==print) {
    fprintf(outputf,"=");
  }
   if(found_list(((Symbol*)expr->kids[0]->val.p)->symname)) {
                                                            flag = 1;
                             fprintf(outputf, "{");
   }
  r = exprgen(expr->kids[1], print);
  if(1==flag) {
              fprintf(outputf, "}");
              }
  if(expr->kids[0]->bitfield){
    f = l->lvalsym->symval.p;
    wbitfield(f,l->lvalsym,r);
  }else if(l->symclass == SYM_TEMP && l->ir->op == DEREF){
    Symbol *addrsym = l->ir->opr[1];
    indmovir(expr->ty,addrsym,r);
    l = deref(expr->ty,addrsym,NULL);
  }else movir(expr->ty,l,r);

  return l;
}

/* generate IR code for expression */
static Symbol * exprgen(ASTExpression *expr, int print)
{
  if(expr->op == ','){
    exprgen(expr->kids[0], print);
    assert(expr->kids[1]);
    if(print == 1)
      fprintf(outputf,",");
    return assignexprgen(expr->kids[1], print);
  }else return assignexprgen(expr, print);
}

/* generate IR code for expression statement */
static void exprirgen(ASTExprstmt *estmt, int print)
{
  if(estmt->expr)
    exprgen(estmt->expr, print);
}

/* generate IR code for if statement */
static void ifgen(ASTSelstmt *stmt, int print)
{
  BBlock *tb,*cb;

  tb = newblock();
  cb = newblock();
  //printf("condgen %d\n", );
  fprintf(outputf, "if(");
  condgen((stmt->expr),cb,tb, print);
  //condgen(notexpr(stmt->expr),cb,tb, print);
  fprintf(outputf, ") {\n");
  startblock(tb);
  stmtirgen(stmt->truestmt,1);
  fprintf(outputf, "}\n");
  startblock(cb); 
}

/* generate IR code for if/else statement */
static void ifelgen(ASTSelstmt *stmt, int print)
{
  BBlock *tb, *fb, *cb;
  tb = newblock();
  fb = newblock();
  cb = newblock();
  fprintf(outputf, "if(");
  condgen(stmt->expr,fb,tb, print);
  //condgen(notexpr(stmt->expr),fb,tb, print);
  startblock(tb);
  fprintf(outputf, ") {\n");
  stmtirgen(stmt->truestmt,1);
  fprintf(outputf, "}\n else {\n");
  jumpir(cb);
  startblock(fb);
  stmtirgen(stmt->falsestmt,1);
  startblock(cb);
  fprintf(outputf, "}\n");
}

/* generate IR code for indirect jump */
static void indjmpir(BBlock **tgts, int len, Symbol *idxsym)
{
  int i;
  IR *ir;

  idxsym->ref++;
  for(i=0;i<len;i++){
    tgts[i]->nref++;
    listappend(tgts[i],&curblock->takentgts);
    listappend(curblock,&tgts[i]->jmpsrcs);
  }
  NEW0(ir);
  ir->ty = gettype(VOIDTYPE);
  ir->op = IJMP;
  ir->ijmps = len;
  ir->opr[0] = tgts;
  ir->opr[1] = idxsym;
  installir(ir);
  //listappend(ir,&idxsym->defuse->uses);
}

/* generate IR code for switch case buckets */
static void switchbktgen(Switchbkt ** bkt, int l, int h, Symbol *sym, BBlock *currblk, BBlock *defblk)
{
  int m, len, i;
  BBlock *lblk, *rblk, **blks;
  Symbol *idxsym;
  Listnode *p;
  ASTLabeledstmt *c;

  if(l > h) return;

  m = (l+h)/2;
  lblk = (l>m-1) ? defblk:newblock();
  rblk = (m>h-1) ? defblk:newblock();
  len = bkt[m]->max - bkt[m]->min + 1;
  
  blks = allocate((len+1)*sizeof(BBlock*));
  for(i=0;i<len;i++)
    blks[i] = defblk;
  blks[len] = NULL;

  p = bkt[m]->cases.head;
  while(p){
    c = (ASTLabeledstmt *)p->data;
    i = ((ASTExpression*)c->idexpr)->val.i[0] - bkt[m]->min;
    blks[i] = c->labelblk;

    p = p->next;
  }

  if(currblk)
    startblock(currblk);

  branchir(sym->symty,lblk,JL,sym,installintconst(bkt[m]->min));
  startblock(newblock());
  branchir(sym->symty,rblk,JG,sym,installintconst(bkt[m]->max));
  startblock(newblock());
  
  if(len!=1){
    idxsym = tempvar(sym->symty);
    assignir(sym->symty,idxsym,SUB,sym,installintconst(bkt[m]->min));
    indjmpir(blks,len,idxsym);
  }else
    jumpir(blks[0]);
  startblock(newblock());
  switchbktgen(bkt,l,m-1,sym,lblk,defblk);
  switchbktgen(bkt,m+1,h,sym,rblk,defblk);
}

/* merge switch buckets */
static int mergeswbkt(Switchbkt **bkt)
{
  Switchbkt *b = *bkt;
  int n = 0;

  while(b->prev){
    if( (b->ncases + b->prev->ncases)*2 <= (b->max - b->prev->min) )
      break;

    b->prev->ncases += b->ncases;
    b->prev->max = b->max;
    b->prev->cases.tail->next = b->cases.head;
    b->prev->cases.tail = b->cases.tail;
    b = b->prev;
    n++;
  }
  *bkt = b;
  return n;
}


/* generate IR code for switch statement */
static void switchgen(ASTSelstmt *sw)
{
#if 0
  int i;
  Symbol * sym;
  Listnode *p,*q;
  Switchbkt *bkt, *b,**bktarray;

  sym = exprgen(sw->expr, 1);
  bkt = b = NULL;
  p = sw->cases.head;
  while(p){
    int v;
    ASTLabeledstmt *cstmt;

    q = p;
    p = p->next;
    cstmt = q->data;
    
    cstmt->labelblk = newblock();
    v = ((ASTExpression*)cstmt->idexpr)->val.i[0];
    if(bkt && (bkt->ncases+1)*2 > (v-bkt->min)){
      bkt->ncases++;
      bkt->max = v;
      listappend(cstmt,&bkt->cases);
      sw->nbkt -= mergeswbkt(&bkt);
    }else{
      NEW0(b);
      listappend(cstmt,&b->cases);
      b->ncases = 1;
      b->min = b->max = v;
      b->prev = bkt;
      bkt = b;
      sw->nbkt ++;      
    }
  }
  sw->bkts = bkt;
  bktarray = allocate(sw->nbkt * sizeof(Switchbkt*));
  
  for(i=sw->nbkt-1; i>=0; i--){
    bktarray[i] = bkt;
    bkt = bkt->prev;
  }

  sw->defblk = newblock();
  if(sw->defaultstmt){
    sw->defaultstmt->labelblk = sw->defblk;
    sw->cvblk = newblock();
  }else sw->cvblk = sw->defblk;

  switchbktgen(bktarray,0,sw->nbkt-1,sym,NULL,sw->defblk);
  stmtirgen(sw->truestmt,1);
  startblock(sw->cvblk);
#endif
}

/* generate IR code for selection statement */
static void selirgen(ASTSelstmt *stmt)
{
  switch(stmt->type){
  case IFSTMT:
    ifgen(stmt, 1);
    break;

  case IFELSESTMT:
    ifelgen(stmt, 1);
    break;

  case SWITCHSTMT:
    switchgen(stmt);
    break;

  default: assert(0);
  }
}


/* generate IR code for while loop */
static void whilegen(ASTIterationstmt *stmt)
{
#if 0
  stmt->bodyblk = newblock();
  stmt->condblk = newblock();
  stmt->cvblk   = newblock();

  jumpir(stmt->condblk);
  startblock(stmt->bodyblk);
  stmtirgen(stmt->stmt,1);
  startblock(stmt->condblk);
  condgen(stmt->expr,stmt->bodyblk,stmt->cvblk);
  startblock(stmt->cvblk);
#endif
}

/* generate IR code for do loop */
static void dogen(ASTIterationstmt *stmt)
{
#if 0
  stmt->bodyblk = newblock();
  stmt->condblk = newblock();
  stmt->cvblk   = newblock();

  startblock(stmt->bodyblk);
  stmtirgen(stmt->stmt);

  startblock(stmt->condblk);
  condgen(stmt->expr,stmt->bodyblk,stmt->cvblk);

  startblock(stmt->cvblk);
#endif
}

/* generate IR code for for loop */
static void forgen(ASTIterationstmt *stmt)
{
  fprintf(outputf,"for(int ");
  stmt->bodyblk = newblock();
  stmt->condblk = newblock();
  stmt->forblk  = newblock();
  stmt->cvblk   = newblock();

  stmtirgen(&stmt->exprstmt[0]->base, 0);
  //fprintf(outputf, ";");
  jumpir(stmt->forblk);
  //The branch condition is printed here
  if(stmt->exprstmt[1]->expr) {
    condgen(stmt->exprstmt[1]->expr,stmt->bodyblk,stmt->cvblk, 1);
    fprintf(outputf,";");
  }  
  if(stmt->expr) {
    exprgen(stmt->expr, 1);
  }
  fprintf(outputf,") {\n");
 
  
  startblock(stmt->bodyblk);
  stmtirgen(stmt->stmt,1);

  startblock(stmt->condblk);
  if(stmt->expr)
    exprgen(stmt->expr, 0);

  startblock(stmt->forblk);
  if(stmt->exprstmt[1]->expr) {
    condgen(stmt->exprstmt[1]->expr,stmt->bodyblk,stmt->cvblk, 0);
  }
  else jumpir(stmt->bodyblk);
  fprintf(outputf,"}\n");
  startblock(stmt->cvblk);
}

/* generate IR code for iteration statement */
static void iterirgen(ASTIterationstmt *istmt)
{
  switch(istmt->type){
  case WHILESTMT:
    whilegen(istmt);
    break;

  case DOSTMT:
    dogen(istmt);
    break;

  case FORSTMT:
    forgen(istmt);
    break;

  default: assert(0);
  }
}

/* generate IR code for goto statement */
static void gotogen(ASTJumpstmt *stmt)
{
  ASTLabeledstmt *deflab;

  deflab = ((Symbol*)((ASTAtom*)stmt->idexpr)->tval.p)->deflabstmt;
  assert(deflab);
  if(!deflab->labelblk)
    deflab->labelblk = newblock();
  jumpir(deflab->labelblk);
  startblock(newblock());
}

/* generate IR code for break statement */
static void brkgen(ASTJumpstmt *stmt)
{
  assert(stmt->tgtstmt);
  if(stmt->tgtstmt->astclass == AST_SELECTIONSTMT){
    ASTSelstmt *sstmt = container_of(stmt->tgtstmt,ASTSelstmt,base);
    assert(sstmt->type == SWITCHSTMT);
    assert(sstmt->cvblk);
    jumpir(sstmt->cvblk);
  }else if(stmt->tgtstmt->astclass == AST_ITERATIONSTMT){
    ASTIterationstmt *istmt = container_of(stmt->tgtstmt,ASTIterationstmt,base);
    assert(istmt->cvblk);
    jumpir(istmt->cvblk);
  }else assert(0);
  startblock(newblock());
}

/* generate IR code for continue statement */
static void continuegen(ASTJumpstmt *stmt)
{
  ASTIterationstmt *istmt;

  assert(stmt->tgtstmt);
  assert(stmt->tgtstmt->astclass == AST_ITERATIONSTMT);
  istmt = container_of(stmt->tgtstmt,ASTIterationstmt,base);
  assert(istmt->condblk);
  jumpir(istmt->condblk);
  startblock(newblock());
}

/* generate IR code for return expression */
static void returngen(Type *ty, Symbol *sym)
{
  IR *ir;

  NEW0(ir);
  ir->op = RET;
  ir->ty = ty;
  ir->opr[0] = sym;
  installir(ir);

  sym->ref++;
  //listappend(ir,&sym->defuse->uses);
}

/* generate IR code for return statement */
static void retgen(ASTJumpstmt *stmt)
{
  ASTExpression *expr = (ASTExpression *)stmt->idexpr;

  if(expr)
    returngen(expr->ty, exprgen(expr,0));
  jumpir(curfuncir->cvblk);
  startblock(newblock());
  //startblock(curfuncir->cvblk);
}

/* generate IR code for jump statement */
static void jumpirgen(ASTJumpstmt *jstmt)
{
  switch(jstmt->type){
  case GOTOSTMT:
    gotogen(jstmt);
    break;

  case BREAKSTMT:
    brkgen(jstmt);
    break;

  case CONTINUESTMT:
    continuegen(jstmt);
    break;

  case RETURNSTMT:
    retgen(jstmt);
    break;

  default: assert(0);
  }
}

/* generate IR for statement */
static void stmtirgen(ASTBase *stmt, int ret)
{
  switch(stmt->astclass) {
  case AST_LABELEDSTMT:
    labelirgen(container_of(stmt,ASTLabeledstmt,base));
    break;
  case AST_COMPOUNDSTMT:
    cmpdirgen(container_of(stmt,ASTCmpdstmt,base));
    //fprintf(outputf,";\n");
    break;
  case AST_EXPRESSIONSTMT:
    exprirgen(container_of(stmt,ASTExprstmt,base), 1);
    fprintf(outputf,";");
    if(ret)
           fprintf(outputf,"\n");
    break;
  case AST_SELECTIONSTMT:
    selirgen(container_of(stmt,ASTSelstmt,base));
    break;
  case AST_ITERATIONSTMT:
    iterirgen(container_of(stmt,ASTIterationstmt,base));
    break;
  case AST_JUMPSTMT:
    jumpirgen(container_of(stmt,ASTJumpstmt,base));
    break;
  default: assert(0);
  }
}

/* Funtion IR generation */
static void funcirgen(ASTFunctiondeclaration * fdecl)
{
  Funcir *fir = NULL;
  BBlock *blk;
  
  if(fdecl->stmt) {
    NEW0(fir);
    curblock = NULL;
    curfuncir = fir;
    //curfunc = fdecl;
    fir->sym = fdecl->sym;
    //    printf("fdecl->sym %s\n", fdecl->sym->symname);
    if(strcmp(fdecl->sym->symname, "test") == 0) {
      TEST = 1;
      fprintf(outputf, "@Test\npublic void test("); 
    }
    else {
      fprintf(outputf,"public void %s(", fdecl->sym->symname);
    }
    /*
      List head = fdecl->params;
      Parameter* p = (Parameter*)(head.head);
      while(p) {
      printf("PARA %s\n", p->name);
      p = p->next;
      }*/
    if(fdecl->dec && TEST == 0) {
      ASTFunctiondeclarator* func = container_of(fdecl->dec, ASTFunctiondeclarator, base);
      ASTBase* h = func->idlist;
     
      if(h) {
	fprintf(outputf, "String");
	if(found_list(container_of(h, ASTAtom, base)->tval.p)) {
	  fprintf(outputf, "[]");
	}

	fprintf(outputf," %s", container_of(h, ASTAtom, base)->tval.p);
	h = h->next;
      }
      while(h) {
	fprintf(outputf, ", String");
	if(found_list(container_of(h, ASTAtom, base)->tval.p)) {
	  fprintf(outputf, "[]");
	}

	fprintf(outputf," %s", container_of(h, ASTAtom, base)->tval.p);
	h = h->next;
      }
    }

    fir->params = fdecl->params;
    fir->lids = fdecl->lids;
    startblock(fir->bblist = newblock());
    fir->cvblk = newblock();
    listappend(fir, &funcirs);
    memset(IRtbl,0,sizeof(IRtbl));
    //if(TEST==0) 
    {
      fprintf(outputf,") {\n");
    }
    stmtirgen(&fdecl->stmt->base,1);
    //if(TEST==0) 
    {
      fprintf(outputf,"}\n");
    }
    /*else 
      TEST = 0;
*/
    startblock(fir->cvblk);

    blk = fir->bblist;
    while(blk){
      if(blk->nref)
        blk->sym = blksym();
      blk=blk->next;
    }
    optimize(fir);
  }
}

/* modify the jump target for current basic block */
EXPORT void instmodify(BBlock *blk, BBlock *oldblk, BBlock *newblk)
{
  IR *ir = blk->irtail;

  assert(ir && ir->op >= JZ && ir->op <= IJMP);
  if(ir->op>=JZ && ir->op < IJMP){
    assert(ir->opr[0] == oldblk);
    ir->opr[0] = newblk;
    return;
  }

  if(ir->op == IJMP){
    int i;
    BBlock ** bblist = ir->opr[0];
    for(i=0;i<ir->ijmps;i++){
      if(bblist[i] == oldblk)
        bblist[i] = newblk;
    }
  }
}

/* intermediate code generation */
EXPORT void irgen(char* inputfile, char* outputfile, char* testclass, char* module)
{
  ASTBase *extdecls;
  char filename[1024];
  char* linein=(char*)malloc(2048*sizeof(char));
  char package[256];
  char word[256];
  FILE* in, *funcin;
  int linecount = 0, count=0;
  numLists = 0;
  TEST = 0;
  /*
  funcin = fopen("functions", "r");
  while(!feof(funcin)) {
      linecount = fgets(linein, 2048, funcin);
      //strcpy(builtin[linecount++],linein);
      count++;
  }
  BUILTINS = count;
  builtin = (char**)malloc(count*sizeof(char*));
  count = 0;
  fclose(funcin);
  funcin = fopen("functions", "r");
  while(!feof(funcin)) {
      linecount = fgets(linein, 2048, funcin);
      builtin[count] = (char*)malloc(strlen(linein)+1);
      strcpy(builtin[count++],linein);
  }*/
  linecount = 0;
  in = fopen(inputfile, "r");
  memcpy(word, 256, 0);
  while(!feof(in)) {
    int i=0, j=0;
    linecount = fgets(linein, 2048, in);

    while(linein[i]==' ' || linein[i]=='\t') i++;
    if(linein[i] != 'i')break;
    
    strncpy(word, linein+i, 3);
    word[3]='\0';
      //printf("Word %s end, %d\n", word, linecount);
    if(strcmp(word, "int")!=0) break;
    i+=3;
    while(i<linecount) {
                      
      while(linein[i]==' ' || linein[i]=='\t' || linein[i] == ',') i++;
      //printf("Line i is %c\n", linein[i]); 
      if(linein[i] == ';')
        break;
      j=i;
      while(linein[j]!=' ' && linein[j]!='\t' && linein[j]!=',' && linein[j]!=';') j++;
      memcpy(lists[numLists], 256, 0);
      strncpy(lists[numLists], linein+i, j-i);
      lists[numLists][j-i]='\0';
      //printf("List %s %d\n", lists[numLists], j);
      i=j;
      numLists++;
    }
  }
  fclose(in);
  //sprintf(filename, "%s.java", testclass);
  //printf("filename %s\n", filename);
  outputf = fopen(outputfile, "w+");
   
  sprintf(package, "package com.sinosoft.autotest.%s;\n", module);
  fprintf(outputf, package); //"package com.sinosoft.autotest.cloudplatform;\n");
  fprintf(outputf, "import com.sinosoft.autotest.common.BaseCommon;\n");
  fprintf(outputf, "import org.junit.*;\n");
  
  fprintf(outputf, "public class %s {\n", testclass);
  //  fprintf(outputf, "int i,j,k;\n");
  fprintf(outputf, "BaseCommon base = new BaseCommon();\n");
  extdecls = translationunit->extdecls;
  while(extdecls){
    if(extdecls->astclass == AST_FUNCTION)
      funcirgen(container_of(extdecls,ASTFunctiondeclaration,base));
    extdecls = extdecls->next;
  }
  fprintf(outputf,"@Before\n");
    fprintf(outputf,"public void setUp() throws Exception {\n");
    fprintf(outputf,"}\n");

    fprintf(outputf,"@After\n");
    fprintf(outputf,"public void tearDown() throws Exception {\n");
    fprintf(outputf,"\tbase.closeBrowser();\n");
    fprintf(outputf,"}\n");

  fprintf(outputf, "}\n");
  fclose(outputf);
}
