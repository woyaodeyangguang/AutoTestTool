/*
**This code should not be used for commercial purposes.
**This code is adapted from LCC-4.1 source.
**Please pass your credits to LCC developpers.
**/
#include "c.h"

struct block {
  struct block *next;
  char *limit;
  char *avail;
};
union align {
  long l;
  char *p;
  double d;
  int (*f)(void);
};
union header {
  struct block b;
  union align a;
};

static struct block
   first = { NULL },
  *arena = &first;

static struct block *freeblocks;

EXPORT void *allocate(unsigned long n)
{
  struct block *ap;
  
  assert(n > 0);
  ap = arena;
  n = roundup(n, sizeof (union align));
  while (n > ap->limit - ap->avail) {
    if ((ap->next = freeblocks) != NULL) {
      freeblocks = freeblocks->next;
      ap = ap->next;
    } else {
      unsigned m = sizeof (union header) + n + roundup(10*1024, sizeof (union align));
      ap->next = malloc(m);
      ap = ap->next;
      if (ap == NULL) {
      	fprintf(stderr,"insufficient memory\n");
      	exit(1);
      }
      ap->limit = (char *)ap + m;
    }
    ap->avail = (char *)((union header *)ap + 1);
    ap->next = NULL;
    arena = ap;
  }
  ap->avail += n;
  return ap->avail - n;
}

/*
static void *newarray(unsigned long m, unsigned long n)
{
  return allocate(m*n);
}
*/

EXPORT void deallocate() 
{
  arena->next = freeblocks;
  freeblocks = first.next;
  first.next = NULL;
  arena = &first;
}
