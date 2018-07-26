/*
**Perform some simple optimizations.
**This code is based on various open resources, intented for educational
**purposes only. You can access, modify this for your personal use freely,
**but any attempts for comercial exploitation from this code are considered 
**unethical and should be discouraged.
*/

#include "c.h"

#define DST  ((Symbol*)ir->opr[0])
#define SRC1 ((Symbol*)ir->opr[1])
#define SRC2 ((Symbol*)ir->opr[2])

#define PREDST  ((Symbol*)preir->opr[0])
#define PRESRC1 ((Symbol*)preir->opr[1])
#define PRESRC2 ((Symbol*)preir->opr[2])
static void peephole(Funcir *fir)
{
  IR *ir;
  IR *preir;
  BBlock *blk = fir->bblist;

  while(blk){
    ir = blk->irhead;
    while(ir){
      preir = ir->prev;

      if(ir->op == MOV && SRC1->symclass == SYM_TEMP && 2 == SRC1->ref &&
         preir && PREDST == SRC1 && ( PRESRC1->symclass == SYM_TEMP || PRESRC2) ){
        assert(PREDST->ref >= 2);
        PREDST->ref -= 2;
        preir->opr[0] = DST;
        if(ir->next)
          ir->next->prev = preir;
        preir->next = ir->next;
        if(NULL == ir->next){
          assert(blk->irtail == ir);
          blk->irtail = preir;
        }
        blk->nir--;
      }

      ir = ir->next;
    }
    blk = blk->next;
  }
}

static void eliminateir(Funcir *fir)
{
  BBlock *blk = fir->bblist;
  while(blk){
    IR *ir = blk->irhead;
    while(ir){
      Symbol **opr;
      if(ir->op == CALL){
        opr = (Symbol**)ir->opr;
        if(opr[0] && opr[0]->symclass == SYM_TEMP && opr[0]->ref == 1){
          opr[0]->ref = 0;
          ir->opr[0] = NULL;
        }
      }else if(!branchop(ir->op)){
        opr = (Symbol**)ir->opr;
        assert(opr[0]->ref>0);
        if(opr[0]->ref == 1 && opr[0]->symclass == SYM_TEMP){
          opr[1]->ref --;
          opr[0]->ref = 0;
          if(opr[2])
            opr[2]->ref --;

          if(ir == blk->irtail && ir == blk->irhead)
            blk->irhead = blk->irtail = NULL;
          else if(ir == blk->irtail){
            blk->irtail = ir->prev;
            blk->irtail->next = NULL;
          }else if(ir == blk->irhead){
            blk->irhead = ir->next;
            blk->irhead->prev = NULL;
          }else{
            ir->prev->next = ir->next;
            ir->next->prev = ir->prev;
          }

          blk->nir--;
        }
      }
      ir = ir->next;
    }
    blk=blk->next;
  }
}

static BBlock * mergeblk(BBlock *cblk, BBlock *nblk)
{
  /* the last basic block */
  if(!nblk)
    return nblk;
  
  /* two succesive basic block */
  if(!cblk->takentgts.head && !nblk->jmpsrcs.head){
    Listnode *n;
    //warning(NULL,"merging two successive basic blocks.");
    /* merge taken targets */
    cblk->takentgts = nblk->takentgts;
    n = nblk->takentgts.head;
    while(n){
      BBlock *b;
      b = n->data;
      listmodify(&b->jmpsrcs,nblk,cblk);
      n = n->next;
    }

    /* merge instructions */
    if(!cblk->irhead){
      cblk->irhead = nblk->irhead;
      cblk->irtail = nblk->irtail;
    }else if(nblk->irhead){
      cblk->irtail->next = nblk->irhead;
      nblk->irhead->prev = cblk->irtail;
      cblk->irtail = nblk->irtail;
    }
    cblk->nir += nblk->nir;

    /* remove the block */
    cblk->next = nblk->next;
    if(nblk->next)
      nblk->next->prev = cblk;
    return cblk;
  }

  if(!cblk->nir){
    Listnode *n;

    //warning(NULL,"removing empty basic block");
    n = cblk->jmpsrcs.head;
    while(n){
      BBlock * b = n->data;
      listmodify(&b->takentgts,cblk,nblk);
      instmodify(b,cblk,nblk);
      listappend(b,&nblk->jmpsrcs);
      nblk->nref++;
      n = n->next;
    }
    nblk->prev = cblk->prev;
    if(cblk->prev)
      cblk->prev->next = nblk;
    return cblk->prev;
  }

  if(!nblk->nir && !nblk->jmpsrcs.head){
    //warning(NULL,"removing empty successive block");
    cblk->next = nblk->next;
    if(nblk->next)
      nblk->next->prev = cblk;
    return cblk;
  }

  if(cblk->irtail->op == JMP && cblk->takentgts.head->data == nblk){
    //warning(NULL,"removing the last useless JMP from basic block");
    cblk->nir--;
    nblk->nref--;
    if(cblk->irtail == cblk->irhead)
      cblk->irtail = cblk->irhead = NULL;
    else{
      cblk->irtail = cblk->irtail->prev;
      cblk->irtail->next = NULL;
    }
    listremove(cblk,&nblk->jmpsrcs);
    return cblk;
  }

  return nblk;
}

/* eliminate unreachable basic block */
static void eliminatebb(Funcir *fir)
{
  BBlock *blk,*tgt;

  blk = fir->bblist;
  while(blk){
    if(NULL != blk->prev && /* must not be the first basic block */
       0 == blk->nref &&
       1 == blk->nir && 
       blk->irtail->op == JMP){
      assert(NULL == blk->jmpsrcs.head);
      assert(blk->irhead == blk->irtail);
      
      /* control flow bookkeeping */
      tgt = blk->irtail->opr[0];
      listremove(blk,&tgt->jmpsrcs);
      tgt->nref--;

      /* delete it */
      assert(NULL != blk->prev && NULL != blk->next);
      blk->prev->next = blk->next;
      blk->next->prev = blk->prev;
      blk = blk->prev;
    }
    blk = blk->next;
  }
}

EXPORT void optimize(Funcir *fir)
{
  BBlock *blk;

  /* peephole optimization */
  peephole(fir);

  /* eliminate dead code */
  eliminateir(fir);

  /* eliminate un-reachable basic blocks */
  eliminatebb(fir);

  /* merge basic blocks */
  blk = fir->bblist;
  while(blk)
    blk = mergeblk(blk,blk->next);
}

