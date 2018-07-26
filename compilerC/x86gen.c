/*
**Intermediate code generation for HCC 1.0
**This code is based on various open resources, intented for educational
**purposes only. You can access, modify this for your personal use freely,
**but any attempts for comercial exploitation from this code are considered 
**unethical and should be discouraged.
*/
#include "c.h"
#include "parser.h"

/* expose this for debug purposes only */
EXPORT char * iropstrs[] = 
{
  #define IRCODE(a,b) b,
  #include "ircode.h"
  #undef IRCODE
};

/* short cut for accessing IR members */
#define DST  ((Symbol*)ir->opr[0])
#define SRC1 ((Symbol*)ir->opr[1])
#define SRC2 ((Symbol*)ir->opr[2])

/* list of IR functions */
extern List funcirs;
extern List gstrs;
extern List fpconsts;
extern List gids;

static Funcir *currfir;
static int ijmptblnum;
static int varoff;
/* code generator for x86 architecture */
/* X86 register file */
enum { EAX, ECX, EDX, EBX, ESP, EBP, ESI, EDI, };
#define NULL_REG -1
static Symbol * x86regs[EDI+1];
static Symbol * x86wregs[EDI+1];
static Symbol * x86bregs[EDI+1];
static int usemask;

/* object code sectios */
enum { CODE, DATA, BSS,};

/* X86 stack constraints */
#define PARAMSTART 4
#define STACK_ELEM_SIZE 4
/* x86 assembly codes */
enum 
{
#define TEMPLATE(code, asmstr) code,
#include "x86linux.tpl"
#undef TEMPLATE
};

static char * x86asm[] =
{
#define TEMPLATE(code, asmstr) asmstr,
#include "x86linux.tpl"
#undef TEMPLATE
};

/* dealing with X86 floating point stack */
static Symbol *fpsym; /* the symbol on the fp stack */
static int fpcode;    /* single precision or double */

/* say hello before calling them*/
static void addvar(Symbol *r, Symbol *p);
static void emitasm(int idx, Symbol *ops[]);

static Symbol * createreg(char *name, char *iname, int n)
{
  Symbol *s;

  assert(name);
  NEW0(s);
  s->symclass = SYM_REG;
  s->symname = name;
  s->symval.i[0] = n;

  if(iname){
    NEW0(s->next);
    s->next->symclass = SYM_IREG;
    s->next->symname = iname;
    s->next->symval.i[0] = n;
  }
  return s;
}

static void x86regfileinit(void)
{
  x86regs[EAX] = createreg("%eax","(%eax)",EAX);
  x86regs[ECX] = createreg("%ecx","(%ecx)",ECX);
  x86regs[EDX] = createreg("%edx","(%edx)",EDX);
  x86regs[EBX] = createreg("%ebx","(%ebx)",EBX);
  x86regs[ESI] = createreg("%esi","(%esi)",ESI);
  x86regs[EDI] = createreg("%edi","(%edi)",EDI);

  x86wregs[EAX] = createreg("%ax",NULL,EAX);
  x86wregs[ECX] = createreg("%cx",NULL,ECX);
  x86wregs[EDX] = createreg("%dx",NULL,EDX);
  x86wregs[EBX] = createreg("%bx",NULL,EBX);
  x86wregs[ESI] = createreg("%si",NULL,ESI);
  x86wregs[EDI] = createreg("%di",NULL,EDI);

  x86bregs[EAX] = createreg("%al",NULL,EAX);
  x86bregs[ECX] = createreg("%cl",NULL,ECX);
  x86bregs[EDX] = createreg("%dl",NULL,EDX);
  x86bregs[EBX] = createreg("%bl",NULL,EBX);
}

static void segment(int seg)
{
  assert(seg == CODE || seg == DATA || seg == BSS);
  if(seg == CODE)
    emitln("\n.text");
  else if(seg == DATA)
    emitln(".data");
  else emitln("\n.bss");
}

static void strdef(char *str, int size)
{
  int i = 0;
  emit(".string \"");
  for(i=0;i<size;i++)
    switch(str[i]){
      case '\a':
        emitchar('\\');
        emitchar('a');
        break;
      case '\b':
        emitchar('\\');
        emitchar('b');
        break;
      case '\f':
        emitchar('\\');
        emitchar('f');
        break;
      case '\n':
        emitchar('\\');
        emitchar('n');
        break;
      case '\r':
        emitchar('\\');
        emitchar('r');
        break;
      case '\t':
        emitchar('\\');
        emitchar('t');
        break;
      case '\v':
        emitchar('\\');
        emitchar('v');
        break;
      default: 
        emitchar(str[i]);
        break;
    }
  emitln("\"");
}

static void alignvar(Symbol *p)
{
  int align = p->symty->align;

  if(varoff % align != 0){
    emitln(".align %d",align);
    varoff = ALIGN(varoff,align);
  }
  varoff += p->symty->size;
}

static void defglobl(Symbol *p)
{
  alignvar(p);
  if(p->stclass != STATIC)
    emitln(".globl %s",p->symname);
  emit(".%s: ",p->symname);
}

static void gstrgen(void)
{
  Symbol *p;
  Listnode *n;

  n = gstrs.head;
  while(n){
    int len;

    p = n->data;
    defglobl(p);
    if( !(p->symty->tyclass == ARRAYTYPE &&
        (p->symty->bty->tyclass == CHARTYPE || p->symty->bty->tyclass == UCHARTYPE)))
      fatal(NULL,"Only 1 byte characters are allowed in string");
    len = strlen(p->symval.p);
    strdef(p->symval.p,len);
    n = n->next;
  }
  //emit("\n");
}

static void fpconstgen(void)
{
  Symbol *p;
  Listnode *n;

  n = fpconsts.head;
  while(n){
    p = n->data;
    defglobl(p);
    if(p->symty->tyclass == FLOATTYPE)
      emitln(".long %u",*((unsigned*)(&p->symval.f)));
    else if(p->symty->tyclass == DOUBLETYPE)
      emitln(".quad %llu",*((unsigned long long*)&p->symval.d));
    else assert(0);
    n = n->next;
  }
}

static void emitpconst(ASTExpression *expr)
{
  Symbol * sym;

  switch(expr->op){
    case IDENTIFIER:
      sym = expr->val.p;
      if(sym->symclass == STATIC)
        emitln(".long %s",sym->rname);
      else 
        emitln(".long %s",sym->symname);
      break;
    case STRING:
      emitln(".long .%s",((Symbol*)expr->val.p)->symname);
      break;

    case INDEX_OP:
      assert(expr->kids[0]->op == IDENTIFIER);
      assert(constop(expr->kids[1]->op));
      if(expr->kids[1]->val.i[0] == 0)
        emitln(".long %s",((Symbol*)expr->kids[0]->val.p)->symname);
      else emitln(".long %s+%d",((Symbol*)expr->kids[0]->val.p)->symname,expr->kids[1]->val.i[0]);
      break;

    default:
      assert(expr->op == INTCONST && expr->val.i[0] == 0);
      emitln(".long 0");
      break;
  }
}

static void emitinitdata(List *l)
{
  Type *ty;
  Initdata *idata;
  Listnode *n = l->head;
  char *p;
  int bitv = 0, bitfldv = 0;

  while(n){
    idata = n->data;
    if(idata->expr){
      ty = idata->ty;
      switch(ty->tyclass){
        case CHARTYPE:
        case UCHARTYPE:
          emitln(".byte %d",idata->expr->val.i[0]);
          break;

        case SHORTTYPE:
        case USHORTTYPE:
          emitln(".word %d",idata->expr->val.i[0]);
          break;
 
        case INTTYPE:
        case UINTTYPE:
          if(idata->bitfield){
            bitv = BITS(idata->expr->val.i[0],idata->size);
            bitfldv |= (bitv << idata->pos);
            if(idata->lastfld){
              emitln(".long %u",bitfldv);
              bitfldv = 0;
            }
            break;
          }
        case LONGTYPE:
        case ULONGTYPE:
          emitln(".long %u",idata->expr->val.i[0]);
          break;

        case LONGLONGTYPE:
        case ULONGLONGTYPE:
          emitln(".quad %llu",idata->expr->val.ll);
          break;

        case FLOATTYPE:
          emitln(".long %u",*((unsigned*)&idata->expr->val.f));
          break;

        case DOUBLETYPE:
        case LONGDOUBLETYPE:
          emitln(".quad %llu",*((unsigned long long*)&idata->expr->val.d));
          break;

        case POINTERTYPE:
          emitpconst(idata->expr);
          break;

        case ARRAYTYPE:
          assert(ty->bty->tyclass == CHARTYPE || ty->bty->tyclass == UCHARTYPE);
          p = ((Symbol*)idata->expr->val.p)->symval.p;
          emitln(".string \"%s\"",p);
          break;

        default: assert(0);
      }
    }else
      emitln(".space %d",idata->size);

    n = n->next;
  }
}

static void globlvargen(Symbol *p)
{
  if(p->stclass != STATIC)
    emitln(".globl %s",p->symname);
  emitln(".align %d",p->symty->align);
  emitln(".type %s,@object",p->symname);
  emitln(".size %s,%d",p->symname,p->symty->size);
  if(p->stclass != STATIC)
    emitln("%s:",p->symname);
  else emitln("%s:",p->rname);
  emitinitdata(&p->irdata);  
}

static void bssvargen(Symbol *p)
{
  switch(p->symty->tyclass){
#define EMITVAR(p)\
      if(p->stclass != STATIC)\
        emitln(".globl %s",p->symname);\
      emitln(".align %d",p->symty->align);\
      emitln(".type %s,@object",p->symname);\
      emitln(".size %s,%d",p->symname,p->symty->size);

#define EMITCOMM(p) \
      if(p->stclass != STATIC)\
        emitln(".comm %s,%d",p->symname,p->symty->size);\
      else emitln(".lcomm %s,%d",p->symname,p->symty->size);

    case CHARTYPE:
    case UCHARTYPE:
      EMITVAR(p)
      EMITCOMM(p)
      break;

    case SHORTTYPE:
    case USHORTTYPE:
      EMITVAR(p)
      EMITCOMM(p)
      break;

    case INTTYPE:
    case UINTTYPE:
    case LONGTYPE:
    case ULONGTYPE:
      EMITVAR(p)
      EMITCOMM(p)
      break;

    case LONGLONGTYPE:
    case ULONGLONGTYPE:
      EMITVAR(p)
      EMITCOMM(p)
      break;

    case FLOATTYPE:
      EMITVAR(p)
      EMITCOMM(p)
      break;

    case POINTERTYPE:
      EMITVAR(p)
      EMITCOMM(p)
      break;

    case DOUBLETYPE:
    case LONGDOUBLETYPE:
      EMITVAR(p)
      EMITCOMM(p)
      break;

    case ARRAYTYPE:
      if(!p->symty->size)
        fatal(NULL,"array %s has unknown size",p->symname);
      EMITVAR(p)
      EMITCOMM(p)
      break;

    default:
      assert(0);
      break;
#undef EMITCOMM
#undef EMITVAR
  }
}

static void globlgen(void)
{
  Symbol *p;
  Listnode *n;

  n = gids.head;
  while(n){
    p = n->data;
    if(p->irdata.head)
      globlvargen(p);
    n = n->next;
  }

  segment(BSS);
  n = gids.head;
  while(n){
    p = n->data;
    if(!p->irdata.head)
      bssvargen(p);
    n = n->next;
  }
}

static int  initstack(List *params,List *lids,int start)
{
  int off;
  Listnode *n;
  Symbol *sym;

  off = start * STACK_ELEM_SIZE;
  n = params->head;
  while(n){
    sym = n->data;
    sym->off = off;
    off += ALIGN(sym->symty->size,STACK_ELEM_SIZE);

    n = n->next;
  }

  off = 0;
  n = lids->head;
  while(n){
    sym = n->data;
    if(sym->ref){
      off += ALIGN(sym->symty->size,STACK_ELEM_SIZE);
      sym->off = -off;
    }
    n = n->next;
  }
  return off;
}

static char * transname(Symbol *s)
{
  Symbol *b;

  if(s->aname)
    return s->aname;

  switch(s->symclass){
    case SYM_CONST:
      //if(strncmp(s->symname,"Float",5) && strncmp(s->symname,"Double",6))
      if(s->symty->tyclass != FLOATTYPE && s->symty->tyclass != DOUBLETYPE)
        s->aname = formatname("$%lld",s->symval.ll);
      else
        s->aname = formatname(".%s",s->symname);
      break;

    case SYM_STRING:
    case SYM_LABEL:
      s->aname = formatname(".%s",s->symname);
      break;

    case SYM_VARIABLE:
    case SYM_TEMP:
      if(s->symscope == SC_GLOBAL){
        s->aname = s->symname;
      }else if(s->stclass == STATIC)
        s->aname = s->rname;
      else s->aname = formatname("%d(%%ebp)",s->off);
      break;

    case SYM_FUNCTION:
      s->aname = s->symname;
      break;

    case SYM_OFFSET:
      b = s->link;
      if(b->symscope == SC_GLOBAL || b->stclass == STATIC)
        s->aname = formatname("%s%s%d",transname(b),s->off >= 0?"+":"-",s->off);
      else
        s->aname = formatname("%d(%%ebp)",s->off+b->off);
      break;

    case SYM_IREG:
      if(s->off){
        s->aname = formatname("%d%s",s->off,s->symname);
        break;
      }
    case SYM_REG:
      s->aname = s->symname;
      break;

    default: assert(0);
  }
  return s->aname;
}

static void emitasm(int idx, Symbol *ops[])
{
  int i;
  char *tpl = x86asm[idx];
  while(*tpl){
    switch(*tpl){
      case ';':
        emit("\n");
        break;

      case '%':
        tpl++;
        if(*tpl == '%')
          emit("%s","%");
        else{
          i = *tpl - '0';
          if(ops[i]->reg)
            emit("%s",ops[i]->reg->symname);
          else
            emit("%s",transname(ops[i]));
        }
        break;

      default:
        emit("%c",*tpl);
        break;
    }
    tpl++;
  }
  emit("\n");
}

static void funcprolog(int s)
{
  emitasm(X86_PROLOGUE,NULL);
  if(s){
    Symbol *sym = installintconst(s);
    emitasm(X86_EXPANDF,&sym);
  }
}

static void funcepilog(int s)
{
  emitasm(X86_EPILOGUE,NULL);
}

static void mov(int code, Symbol *d, Symbol *s)
{
  Symbol *ops[2];

  ops[0] = d;
  ops[1] = s;
  emitasm(code,ops);
}

static void svvar(Symbol *r, Symbol *s)
{
  mov(X86_MOVI4,s,r);
}

static void spill(Symbol *reg)
{
  Symbol *p = reg->link;
  while(p){
    p->reg = NULL;
    if(p->dirty && p->ref>0){
      p->dirty = 0;
      svvar(reg,p);
    }
    p = p->link;
  }
  reg->link = NULL;
}

static void svregs(void)
{
  int i;
  for(i=0;i<=EDI;i++)
    if(x86regs[i])
      spill(x86regs[i]);
}

static void svfpstk(void)
{
  if(!fpsym)
    return;

  if(fpsym->dirty && (fpsym->ref > 0 || fpsym->symclass == SYM_VARIABLE))
    emitasm(X86_STF4+fpcode-F4,&fpsym);
  fpsym = NULL;
}

static void emitfpmov(IR *ir, int tycode)
{
  if(fpsym != SRC1){
    svfpstk();
    emitasm(X86_LDF4+tycode-F4,(Symbol**)&ir->opr[1]);
  }

  if(DST->symclass != SYM_TEMP){
    emitasm(X86_STF4+tycode-F4,(Symbol**)&ir->opr[0]);
    fpsym = NULL;
  }else{
    DST->dirty = 1;
    fpsym = DST;
    fpcode = tycode;
  }
}

static void emitbmov(IR *ir)
{
  spill(x86regs[ESI]);
  spill(x86regs[EDI]);
  spill(x86regs[ECX]);

  ir->opr[2] = installintconst(ir->ty->size);
  emitasm(X86_MOVB,(Symbol**)ir->opr);
}

/* find a empty register */
static int allocr(int e)
{
  int i;
  for(i=EAX;i<=e;i++)
    if(x86regs[i] && !x86regs[i]->link && !(1<<i & usemask))
      return i;
  return NULL_REG; 
}

/* find a register to spill into memory */
static int selectreg(int e)
{
  int i,r = NULL_REG;
  Symbol *p;
  int ref, mref = INT_MAX;

  for(i=EAX;i<=e;i++){
    if(!x86regs[i] || (1<<i & usemask))
      continue;
    ref = 0;
    p = x86regs[i]->link;
    while(p){
      if(p->dirty && p->ref > 0)
        ref += p->ref;
      p = p->next;
    }
    if(ref < mref){
      mref = ref;
      r = i;
    }
  }
  assert(r != NULL_REG);
  return r;
}

static Symbol *allocreg(int w)
{
  int s, e;
  Symbol **r; 

  switch(w) {
    case 1:
      e = EDX;
      r = x86bregs;
      break;
    case 2:
      e = EDI;
      r = x86wregs;
      break;
    case 4:
      e = EDI;
      r = x86regs; 
      break;
    default: assert(0);
  }
  s = allocr(e);
  if(s == NULL_REG){
    s = selectreg(e);
    spill(x86regs[s]);
  }
  usemask |= 1<<s;
  return r[s];
}

static void allocatereg(IR *ir, int idx)
{
  Symbol *r;
  Symbol *p;

  p = ir->opr[idx];
  if(p->symclass != SYM_TEMP)
    return;

  if(p->reg){
    usemask &= 1<<p->reg->symval.i[0];
    return;
  }

  if(idx == 0 && SRC1->ref == 1 && SRC1->reg){
    r = SRC1->reg;
    r->link = NULL;
    addvar(r,p);
    return;
  }

  r = allocreg(4);
  if(idx)
    mov(X86_MOVI4,r,SRC1);
  addvar(r,p);
}

static void addvar(Symbol *r, Symbol *p)
{
  assert(!r->link);
  p->link = r->link;
  r->link = p;
  p->reg = r;
}

static void varchanged(Symbol *s)
{
  Symbol *r;

  if(!s->reg) return;

  s->dirty = 0;
  r = s->reg;
  spill(r);

  addvar(r,s);
  s->dirty = 1;
}

static void emitmov(IR *ir)
{
  int tycode = typecode(ir->ty);
  Symbol *r;

  if(tycode == F4 || tycode == F8){
    emitfpmov(ir,tycode);
    return;
  }

  if(tycode == B){
    emitbmov(ir);
    return;
  }  

  switch(tycode) {
    case I1: case U1:
      if(SRC1->symclass == SYM_CONST)
        mov(X86_MOVI1,DST,SRC1);
      else{
        r = allocreg(1);
        mov(X86_MOVI1,r,SRC1);
        mov(X86_MOVI1,DST,r);
      }
      break;

    case I2: case U2:
      if(SRC1->symclass == SYM_CONST)
        mov(X86_MOVI2,DST,SRC1);
      else{
        r = allocreg(2);
        mov(X86_MOVI2,r,SRC1);
        mov(X86_MOVI2,DST,r);
      }
      break;

    case I4: case U4:
      if(SRC1->symclass == SYM_CONST)
        mov(X86_MOVI4,DST,SRC1);
      else{
        allocatereg(ir,1);
        allocatereg(ir,0);
        if(!DST->reg && !SRC1->reg){
          r = allocreg(4);
          mov(X86_MOVI4,r,SRC1);
          mov(X86_MOVI4,DST,r);
        }else
          mov(X86_MOVI4,DST,SRC1);      
      }
      varchanged(DST);
      break;

    case I8: case U8:
      fatal(NULL,"64 bit mov is not supported yet");
      break;

    default: assert(0);
  }
}

static Symbol * sym2reg(Symbol *s)
{
  Symbol *r;

  if(s->reg)
    return s->reg;
  r = allocreg(4);
  mov(X86_MOVI4,r,s);
  return r;
}

static void emitimov(IR *ir)
{
  Symbol *r;

  r = sym2reg(DST);
  ir->op = MOV;
  ir->opr[0] = r->next;
  emitmov(ir);
}

static void emitjmp(IR *ir)
{
  BBlock *b = ir->opr[0];

  ir->opr[0] = b->sym;
  svregs();
  svfpstk();
  emitasm(X86_JMP,(Symbol**)ir->opr);
}

static void defaddr(Symbol *sym)
{
  emitln(".long .%s",sym->symname);
}

static void emitijmp(IR *ir)
{
  BBlock **btbl;
  Symbol *base;
  Symbol *r;

  SRC1->ref--;
  btbl = (BBlock**)ir->opr[0];
  r = sym2reg(SRC1);

  segment(DATA);
  NEW0(base);
  base->symclass = SYM_VARIABLE;
  base->symty = gettype(POINTERTYPE);
  base->symname = formatname("ijmptbl%d",ijmptblnum++);
  base->stclass = STATIC;
  base->symscope = SC_GLOBAL;
  //defglobl(base);
  emitln("%s:",base->symname);
  ir->opr[0] = base;
  while(*btbl){
    defaddr((*btbl)->sym);
    btbl++;
  }

  segment(CODE);
  ir->opr[1] = r;
  svregs();
  svfpstk();
  emitasm(X86_IJMP,(Symbol**)ir->opr);
}

static int asmcode(int op,int off)
{
  assert(op<DEREF);
  assert( off >= I4 && off<=F8 && off != I8 && off != U8);
  if(off >= F4) off -= 2;
  off -= I4;
  return (op<<2) + off;
}

static void emitfpbranch(IR *ir, int tycode)
{
  spill(x86regs[EAX]);
  emitasm(X86_LDF4+tycode-F4,(Symbol**)&ir->opr[1]);
  emitasm(asmcode(ir->op,tycode),(Symbol**)ir->opr);
}

static void emitbranch(IR *ir)
{
  int tycode = typecode(ir->ty);
  BBlock * b = (BBlock*)ir->opr[0];

  ir->opr[0] = b->sym;
  if(tycode == F4 || tycode == F8){
    emitfpbranch(ir,tycode);
    return;
  }

  assert(tycode >= I4);
  if(SRC2 && SRC2->symclass != SYM_CONST)
    ir->opr[1] = sym2reg(SRC1);
  SRC1->ref--;
  if(SRC1->reg)
    ir->opr[1] = SRC1->reg;
  if(SRC2){
    SRC2->ref--;
    if(SRC2->reg)
      ir->opr[2] = SRC2->reg;
  }
  svregs();
  svfpstk();
  emitasm(asmcode(ir->op,tycode),(Symbol**)ir->opr);
}

static void emitcast(IR *ir)
{
  Symbol *dst,*r;
  int code = ir->op;

  dst = ir->opr[0];
  switch(code){
    case CVTI1I4:
    case CVTI1U4:
    case CVTU1I4:
    case CVTU1U4:
    case CVTI2I4:
    case CVTI2U4:
    case CVTU2I4:
    case CVTU2U4:
      allocatereg(ir,0);
      assert(DST);
      emitasm(code-CVTI1I4 + X86_CVTI1I4,(Symbol**)ir->opr);
      if(dst != DST)
        mov(X86_MOVI4,dst,DST);
      break;

    case CVTI4I1:
    case CVTI4U1:
      r = NULL;
      if(SRC1->reg)
        r = x86bregs[SRC1->reg->symval.i[0]];
      if(!r){
        r = allocreg(1);
        mov(X86_MOVI4,x86regs[r->symval.i[0]],SRC1);
      }
      mov(X86_MOVI1,DST,r);
      break;

    case CVTI4I2:
    case CVTI4U2:
      r = NULL;
      if(SRC1->reg)
        r = x86wregs[SRC1->reg->symval.i[0]];
      if(!r){
        r = allocreg(2);
        mov(X86_MOVI4,x86regs[r->symval.i[0]],SRC1);
      }
      mov(X86_MOVI2,DST,r);
      break;

    case CVTI4F4:
      assert(fpsym != DST);
      emitasm(X86_CVTI4F4, (Symbol**)ir->opr);
      break;

    case CVTU4F4:
      assert(fpsym != DST);
      emitasm(X86_CVTU4F4, (Symbol**)ir->opr);
      break;

    case CVTF8F4:
      assert(fpsym != DST);
      emitasm(X86_CVTF8F4, (Symbol**)ir->opr);
      break;

    case CVTI4F8:
      assert(fpsym != DST);
      emitasm(X86_CVTI4F8, (Symbol**)ir->opr);
      break;

    case CVTF4F8:
      assert(fpsym != DST);
      emitasm(X86_CVTF4F8, (Symbol**)ir->opr);
      break;

    case CVTU4F8:
      assert(fpsym != DST);
      emitasm(X86_CVTU4F8, (Symbol**)ir->opr);
      break;

#define CVTF2I(asmcode)\
      if(SRC1 == fpsym)\
         svfpstk();\
      spill(x86regs[EAX]);\
      allocatereg(ir,0);\
      emitasm(asmcode,(Symbol**)ir->opr);\
      if(DST->reg && DST->reg != x86regs[EAX])\
        mov(X86_MOVI4,DST,x86regs[EAX]);
 
    case CVTF4I4:
      CVTF2I(X86_CVTF4I4);
      break;

    case CVTF4U4:
      CVTF2I(X86_CVTF4U4);
      break;

    case CVTF8I4:
      CVTF2I(X86_CVTF8I4)
      break;

    case CVTF8U4:
      CVTF2I(X86_CVTF8U4)
      break;
#undef CVTF2I

   default: assert(0);
  }
  varchanged(dst);
}

static void emitfpbinary(IR *ir, int tycode)
{
  if(SRC1 != fpsym){
    svfpstk();
    emitasm(X86_LDF4+tycode-F4,(Symbol**)&ir->opr[1]);
  }
  emitasm(asmcode(ir->op,tycode),(Symbol**)ir->opr);
  if(DST->symclass != SYM_TEMP){
    emitasm(X86_STF4+tycode-F4,(Symbol**)ir->opr);
    fpsym = NULL;
  }else{
    DST->dirty = 1;
    fpsym = DST;
    fpcode = tycode;
  }
}

static void emitbinary(IR *ir)
{
  Symbol *d;
  int code, tycode;

  tycode = typecode(ir->ty);
  if(tycode == F4 || tycode == F8){
    emitfpbinary(ir,tycode);
    return;
  }

  d = ir->opr[0];
  code = asmcode(ir->op,tycode);
  switch(code){
    case X86_DIVI4: case X86_DIVU4:
    case X86_MODI4: case X86_MODU4:
    case X86_MULU4:
      if(SRC1->reg == x86regs[EAX]){
        SRC1->dirty = 0;
        spill(x86regs[EAX]);
      }else{
        spill(x86regs[EAX]);
        mov(X86_MOVI4,x86regs[EAX],SRC1);
      }
      spill(x86regs[EDX]);
      usemask |= 1<<EAX | 1<<EDX;
      if(SRC2->symclass == SYM_CONST){
        Symbol *r = allocreg(4);
        mov(X86_MOVI4,r,SRC2);
        ir->opr[2] = r;
      }else allocatereg(ir,2);
      ir->opr[0] = x86regs[EAX];
      emitasm(code,(Symbol**)ir->opr);
      if(code == X86_MODI4 || code == X86_MODU4)
        ir->opr[0] = x86regs[EDX];
      break;

    case X86_LSHI4: case X86_LSHU4:
    case X86_RSHI4: case X86_RSHU4:
      allocatereg(ir,1);
      if(SRC2->symclass != SYM_CONST){
        if(SRC2->reg != x86regs[ECX]){
          spill(x86regs[ECX]);
          mov(X86_MOVI4,x86regs[ECX],SRC2);
        }
        ir->opr[2] = x86bregs[ECX];
        usemask |= 1<<ECX;
      }
      goto fish;

    case X86_NEGI4: case X86_NEGU4:
    case X86_COMPI4: case X86_COMPU4:
      allocatereg(ir,1);
      goto fish;

    default:
      allocatereg(ir,1);
      allocatereg(ir,2);
fish:
      allocatereg(ir,0);
      if(DST == SRC1 && DST->symclass == SYM_VARIABLE && 
         (SRC2->symclass == SYM_CONST || SRC2->reg)){
        emitasm(code,(Symbol**)ir->opr);
        break;
      }
      if(!DST->reg){
        ir->opr[0] = allocreg(4);
        mov(X86_MOVI4,DST,SRC1);
      }else if(DST->reg != SRC1->reg)
        mov(X86_MOVI4,DST,SRC1);
      emitasm(code,(Symbol**)ir->opr);
      break;
  }

  if(d != DST)
    mov(X86_MOVI4,d,DST);
  varchanged(d);
}

static void emitderef(IR *ir)
{
  Symbol *r;
 
  r = sym2reg(SRC1);
  ir->op = MOV;
  ir->opr[1] = r->next;
  if(SRC2)
    r->next->off = SRC2->symval.i[0];
  emitmov(ir);
  r->next->off = 0;  
  varchanged(DST);
}

static void emitaddr(IR *ir)
{
  Symbol *d;

  d = DST;
  allocatereg(ir,0);
  if(!DST->reg)
    ir->opr[0] = allocreg(4);
  emitasm(X86_ADDR,(Symbol**)ir->opr);
  if(d != DST)
    mov(X86_MOVI4,d,DST);
  varchanged(d);
}

static IRArg * reverse(IRArg *args)
{
  IRArg *prev, *cur, *next;
 
  if(!args || !args->next)
    return args;

  prev = args;
  cur = prev->next;
  prev->next = NULL;
  while(cur){
    next = cur->next;
    cur->next = prev;
    prev = cur;
    cur = next;
  }
  return prev;
}

static void pusharg(Symbol *sym, Type *ty)
{
  int tycode = typecode(ty);

  if(tycode == F4)
    emitasm(X86_PUSHF4,&sym);
  else if(tycode == F8)
    emitasm(X86_PUSHF8,&sym);
  else if(tycode == B){
    Symbol *opr[3];
    spill(x86regs[ECX]);
    spill(x86regs[EDI]);
    spill(x86regs[ESI]);
    opr[0] = sym;
    opr[1] = installintconst(ty->size);
    opr[2] = installintconst(ALIGN(ty->size,STACK_ELEM_SIZE));
    emitasm(X86_PUSHB,opr);
  }else
    emitasm(X86_PUSH,&sym);
}

static void emitcall(IR *ir)
{
  IRArg *args;
  Type *rty;
  int stksize;
  Symbol *p;

  args = ir->opr[2];
  stksize = 0;
  rty = ir->ty;

  args = reverse(args);
  while(args){
    pusharg(args->sym,args->ty);
    if(args->sym->symclass != SYM_FUNCTION)
      args->sym->ref--;
    stksize += ALIGN(args->ty->size,STACK_ELEM_SIZE);
    args = args->next;
  }
  spill(x86regs[EAX]);
  spill(x86regs[ECX]);
  spill(x86regs[EDX]);

  if(structuniontype(rty) && !scalarsize(rty)){
    Symbol *opr[2];
    opr[0] = allocreg(4);
    opr[1] = DST;
    emitasm(X86_ADDR,opr);
    emitasm(X86_PUSH,opr);
    stksize += 4;
    ir->opr[0] = NULL;
  }

  emitasm(SRC1->symclass == SYM_FUNCTION ? X86_CALL : X86_ICALL,(Symbol**)ir->opr);
  p = installintconst(stksize);
  emitasm(X86_REDUCEF,&p);

  if(DST)
    DST->ref--;
  if(SRC1->symclass != SYM_FUNCTION)
    SRC1->ref--;
  if(!DST)
    return;

  if(fptype(rty)){
    emitasm(X86_STF4+(rty->tyclass != FLOATTYPE),(Symbol**)ir->opr);
    return;
  }

  switch(rty->size){
    case 1:
      mov(X86_MOVI1,DST,x86bregs[EAX]);
      break;

    case 2:
      mov(X86_MOVI2,DST,x86wregs[EAX]);
      break;

    case 4:
      allocatereg(ir,0);
      if(DST->reg != x86regs[EAX])
        mov(X86_MOVI4,DST,x86regs[EAX]);
      varchanged(DST);
      break;

    case 8:
      mov(X86_MOVI4,DST,x86regs[EAX]);
      mov(X86_MOVI4,offsetsym(DST,4,gettype(INTTYPE)),x86regs[EDX]);
      break;

    default: assert(0);
  }
}

static void emitret(IR *ir)
{
  Type *ty = ir->ty;

  if(fptype(ty)){
    if(fpsym != DST){
      svfpstk();
      emitasm(X86_LDF4+fpcode-F4,(Symbol**)ir->opr);
    }
    fpsym = NULL;
    return;
  }

  if(structuniontype(ty) && !scalarsize(ty)){
    ir->op = IMOV;
    ir->opr[1] = DST;
    ir->opr[0] = currfir->retsym;
    emitimov(ir);
    return;
  }

  switch(ty->size){
    case 1:
      mov(X86_MOVI1,x86bregs[EAX],DST);
      break;

    case 2:
      mov(X86_MOVI2,x86wregs[EAX],DST);
      break;

    case 4:
      if(DST->reg != x86regs[EAX])
        mov(X86_MOVI4,x86regs[EAX],DST);
      break;

    case 8:
      mov(X86_MOVI4,x86regs[EAX],DST);
      mov(X86_MOVI4,x86regs[EDX],offsetsym(DST,4,gettype(INTTYPE)));
      break;

    default: assert(0);
  }
}

static void emitclr(IR *ir)
{
  int size = SRC1->symval.i[0];
  Symbol *p = installintconst(0);
  switch(size){
    case 1:
      mov(X86_MOVI1,DST,p);
      break;

    case 2:
      mov(X86_MOVI2,DST,p);
      break;

    case 4:
      mov(X86_MOVI4,DST,p);
      break;

    default:
      spill(x86regs[EAX]);
      emitasm(X86_CLEAR,(Symbol**)ir->opr);
      break;
  }
}

static void instgen(IR *ir)
{
  switch(ir->op){
    case MOV:
      emitmov(ir);
      break;

    case IMOV:
      emitimov(ir);
      break;

    case JMP:
      emitjmp(ir);
      break;

    case IJMP:
      emitijmp(ir);
      break;

    case JE:
    case JNE:
    case JG:
    case JL:
    case JZ:
    case JNZ:
    case JGE:
    case JLE:
      emitbranch(ir);
      break;

    case CVTI1I4:
    case CVTI1U4:
    case CVTU1I4:
    case CVTU1U4:
    case CVTI2I4:
    case CVTI2U4:
    case CVTU2I4:
    case CVTU2U4:
    case CVTI4I1:
    case CVTI4U1:
    case CVTI4I2:
    case CVTI4U2:
    case CVTI4I8:
    case CVTI4U8:
    case CVTI4F4:
    case CVTI4F8:
    case CVTU4I8:
    case CVTU4U8:
    case CVTU4F4:
    case CVTU4F8:
    case CVTI8I4:
    case CVTI8U4:
    case CVTU8I4:
    case CVTU8U4:
    case CVTF4I4:
    case CVTF4U4:
    case CVTF4F8:
    case CVTF8I4:
    case CVTF8U4:
    case CVTF8F4:
      emitcast(ir);
      break;

    case BOR:
    case BAND:
    case BXOR:
    case RSH:
    case LSH:
    case ADD:
    case SUB:
    case MUL:
    case DIV:
    case MOD:
    case NEG:
    case BCOM:
      emitbinary(ir);
      break;

    case DEREF:
      emitderef(ir);
      break;

    case ADDR:
      emitaddr(ir);
      break;

    case CALL:
      emitcall(ir);
      break;

    case RET:
      emitret(ir);
      break;

    case CLR:
      emitclr(ir);
      break;
    default: assert(0);
  }
}

static void blkgen(BBlock *blk)
{
  Symbol *opr[3];
  IR *ir = blk->irhead;
  while(ir){
#define SAVE_OPRS \
    do {\
      opr[0] = ir->opr[0];\
      opr[1] = ir->opr[1];\
      opr[2] = ir->opr[2];\
    }while(0);

#define RESTORE_OPRS \
    do {\
      ir->opr[0] = opr[0];\
      ir->opr[1] = opr[1];\
      ir->opr[2] = opr[2];\
    }while(0);

    usemask = 0;
    SAVE_OPRS
    instgen(ir);
    RESTORE_OPRS
    svfpstk();

    if((ir->op < JZ || ir->op > IJMP) && ir->op != CALL){
      DST->ref--;
      if(SRC1 && SRC1->symclass != SYM_FUNCTION)
        SRC1->ref--;
      if(SRC2 && SRC2->symclass != SYM_FUNCTION)
        SRC2->ref--;
    }
    ir = ir->next;
    //if(ir==blk->irhead)
    //  break;
#undef RESTORE_OPRS
#undef SAVE_OPRS
  }
  svregs();
  //svfpstk();
}

static void funcgen(Funcir *fir)
{
  BBlock *blk;
  Symbol *sym;
  Type *rty;
  int ssize;
 
  currfir = fir; 
  sym = fir->sym;
  if(sym->stclass != STATIC)
    emitln(".global %s",sym->symname);
  emitln("%s:",sym->symname);  

  rty = sym->symty->bty;
  if(structuniontype(rty) && !scalarsize(rty)){
    Symbol *p;

    NEW0(p);
    p->symclass = SYM_VARIABLE;
    p->symname = string("retaddr");
    p->symty = gettype(POINTERTYPE);
    p->symscope = SC_PARAM;
    p->stclass = AUTO;
    fir->retsym = p;
    listinsert(p,&fir->params);
  }
  ssize = initstack(&fir->params,&fir->lids,PARAMSTART+1);
  funcprolog(ssize);
  blk = fir->bblist;
  while(blk){
    if(blk->nref)
      emitln(".%s:",blk->sym->symname);
    blkgen(blk);
    blk = blk->next;
  }
  funcepilog(ssize);
  emit("\n");
}

static void codegen(void)
{
  Listnode *n;
  Funcir *fir;

  segment(CODE);

  n = funcirs.head;
  while(n){
    fir = n->data;
    funcgen(fir);
    n = n->next;
  }
  emitln(".ident \"HCC 1.0\"");
}

EXPORT void x86gen(void)
{
  x86regfileinit();
  segment(DATA);
  gstrgen();
  fpconstgen();
  globlgen();
  codegen();
}

#undef DST
#undef SRC1
#undef SRC2
