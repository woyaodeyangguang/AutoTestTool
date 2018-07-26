/*
**Intermediate code generation for HCC 1.0
**This code is based on various open resources, intented for educational
**purposes only. You can access, modify this for your personal use freely,
**but any attempts for comercial exploitation from this code are considered 
**unethical and should be discouraged.
*/
#include "c.h"
#include "parser.h"

extern List funcirs;

static char *irops[] =
{
#define IRCODE(op,name) name,
#include "ircode.h"
#undef IRCODE
};

/* export this for debug purposes */
EXPORT void irinstecho(IR *ir)
{
#define DST  ((Symbol*)ir->opr[0])
#define SRC1 ((Symbol*)ir->opr[1])
#define SRC2 ((Symbol*)ir->opr[2])
  assert(ir->op < IRCODES);
  emit("\t");
  switch(ir->op){
    case BOR:
    case BAND:
    case BXOR:
    case LSH:
    case RSH:
    case ADD:
    case SUB:
    case MUL:
    case DIV:
    case MOD:
      emit("%s = %s %s %s",DST->symname,SRC1->symname,irops[ir->op],SRC2->symname);
      break;

    //case INC:
    //case DEC:
    //  emit("%s %s",irops[ir->op],DST->symname);
    //  break;

    case DEREF:
      if(SRC2)
        emit("%s = %s (%s+%s)",DST->symname,irops[ir->op],SRC1->symname,SRC2->symname);
      else
        emit("%s = %s %s",DST->symname,irops[ir->op],SRC1->symname);
      break; 

    case BCOM:
    case ADDR:
    case NEG:
      emit("%s = %s %s",DST->symname,irops[ir->op],SRC1->symname);
      break;

    case MOV:
      emit("%s = %s",DST->symname,SRC1->symname);
      break;

    case IMOV:
      emit("%s *= %s",DST->symname,SRC1->symname);
      break;

    case JE:
    case JNE:
    case JG:
    case JL:
    case JLE:
    case JGE:
      if(((BBlock*)DST)->sym)
        emit("if (%s %s %s) goto %s", SRC1->symname,irops[ir->op],SRC2->symname,((BBlock*)DST)->sym->symname);
      else
        emit("if (%s %s %s) goto BB?", SRC1->symname,irops[ir->op],SRC2->symname);
      break;

    case JZ:
      if(((BBlock*)DST)->sym)
        emit("if (! %s) goto %s",SRC1->symname,((BBlock*)DST)->sym->symname);
      else
        emit("if (! %s) goto BB?",SRC1->symname);
      break;

    case JNZ:
      emit("if (%s) goto %s",SRC1->symname,((BBlock*)DST)->sym->symname);
      break;

    case JMP:
      if(((BBlock*)DST)->sym)
        emit("goto %s",((BBlock*)DST)->sym->symname);
      else
        emit("goto BB?");
      break;

    case IJMP:
    {
      BBlock **p = (BBlock**)DST;
      emit("goto (");
      while(*p){
        emit("%s,",(*p)->sym->symname);
        p++;
      }
      emit(")[%s]",SRC1->symname);
    }
      break;

    case CALL:
    {
      IRArg *iarg = (IRArg*)SRC2;
      if(DST && DST->ref)
        emit("%s = ",DST->symname);
      emit("%s(",SRC1->symname);
      if(iarg){
        while(iarg->next){
          emit("%s, ",iarg->sym->symname);
          iarg = iarg->next;
        }
        if(iarg) emit("%s",iarg->sym->symname);
      }
      emit(")");
    }
      break;

    case RET:
      emit("return %s",DST->symname);
      break;

    default:
      emit("%s = %s%s",DST->symname,irops[ir->op],SRC1->symname);
      break;
  }
  emitln(";");
#undef SRC2
#undef SRC1
#undef DST
}

static void funcirecho(Funcir *fir)
{
  BBlock *blk;

  emitln("function %s",fir->sym->symname);
  blk = fir->bblist;
  while(blk){
    IR *ir;

    if(blk->nref)
      emitln("%s:",blk->sym->symname);
      //emitln("%s-%d:",blk->sym->symname,blk->nir);
    ir = blk->irhead;
    while(ir){
      irinstecho(ir);
      ir = ir->next;
    }

    blk = blk->next;
  }
  emitln("\tret");
}

EXPORT void irecho(void)
{
  Funcir *fir;
  Listnode *n;

  n = funcirs.head;
  while(n){
    fir = n->data;
    funcirecho(fir);
    n = n->next;
  }
}
