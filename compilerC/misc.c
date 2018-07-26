/*
**Miscellaneous routines for HCC 1.0
**This code is based on various open resources, intented for educational
**purposes only. You can access, modify this for your personal use freely,
**but any attempts for comercial exploitation from this code are considered 
**unethical and should be discouraged.
*/

#include "c.h"

EXPORT void fatal(Coordinate * coord, const char * format , ...)
{
  va_list ap;
  
  fprintf(stderr,"error:");
  if(coord)
    fprintf(stderr,"(%s,%d) ",coord->file,coord->line);
  va_start(ap,format);
  vfprintf(stderr,format,ap);
  fprintf(stderr,"\n");
  va_end(ap);
  exit(-1);
}

EXPORT void warning(Coordinate * coord, const char * format , ...)
{
  va_list ap;
  
  fprintf(stderr,"warning:");
  if(coord)
    fprintf(stderr,"(%s,%d) ",coord->file,coord->line);
  va_start(ap,format);
  vfprintf(stderr,format,ap);
  fprintf(stderr,"\n");
  va_end(ap);
}

EXPORT void info(Coordinate * coord, const char * format , ...)
{
  va_list ap;
  
  if(coord)
    fprintf(stderr,"(%s:%d,%d) ",coord->file,coord->line,coord->column);
  va_start(ap,format);
  vfprintf(stderr,format,ap);
  fprintf(stderr,"\n");
  va_end(ap);
}

EXPORT void emitstr(const char *str)
{
  const char *p = str;

  while(*p != 0){
    if(*p == '\n'){
      fprintf(stdout,"%c",'\\');
      fprintf(stdout,"%c",'n');
    }else fprintf(stdout,"%c",*p);
    p++;
  }
}

EXPORT void emit(const char * format , ...)
{
  va_list ap;
  
  va_start(ap,format);
  vfprintf(stdout,format,ap);
  va_end(ap);
}

EXPORT void emitchar(const char c)
{
  fprintf(stdout,"%c",c);
}

EXPORT void emitln(const char * format , ...)
{
  va_list ap;
  
  va_start(ap,format);
  vfprintf(stdout,format,ap);
  fprintf(stdout,"\n");
  va_end(ap);
}

EXPORT char * formatname(char *fmt, ...)
{
  char buf[256];
  va_list ap;

  va_start(ap,fmt);
  vsprintf(buf, fmt, ap);
  va_end(ap);

  return string(buf);
}

/* insert an item at the head of the list */
EXPORT void listinsert(void *data, List *l)
{
  Listnode *n;

  assert(data && l);
  NEW0(n);
  n->data = data;

  if(!l->head)
    l->head = l->tail = n;
  else{
    assert(NULL != l->head);
    n->next = l->head;
    l->head->prev = n;
    l->head = n;
  }
}

/* append an item to the tail of the list */
EXPORT void listappend(void *sym, List *l)
{
  Listnode *n;

  assert(sym && l);
  NEW0(n);
  n->data = sym;

  if(!l->head)
    l->head = l->tail = n;
  else{
    assert(l->tail != NULL);
    l->tail->next = n;
    n->prev = l->tail;
    l->tail = n;
  }
}

EXPORT void listremove(void *data, List *l)
{
  Listnode *n = l->head;
  while(n){
    if(n->data == data)
      break;
    n = n->next;
  }
  //if(!n)
  //  irinstecho(((BBlock*)data)->irtail);
  assert(n);
  if(n->prev && n->next){
    n->prev->next = n->next;
    n->next->prev = n->prev;
    return;
  }

  if(!n->prev){
    l->head = n->next;
    if(l->head)
      l->head->prev = NULL;
  }

  if(!n->next){
    l->tail = n->prev;
    if(l->tail)
      l->tail->next = NULL;
  }
}

/*
** Insert a node into the list preserving the assending order.
** The compare operator compares two list nodes (n1,n2), and returns
**  1  if n1>n2
**  -1 if n1<n2
**  0  if n1==n2
*/
typedef int (*Comp)(void *, void *);
EXPORT void listappendsorted(void *sym, List *l, void *cmp)
{
  Listnode *n, *p, *q;
  Comp compare = cmp;

  assert(sym && l && cmp);
  NEW0(n);
  n->data = sym;

  if(!l->head)
    l->head = l->tail = n;
  else{
    if(compare(sym,l->head->data) == -1){
      n->next = l->head;
      l->head->prev = n;
      l->head = n;
    }else if(compare(sym,l->tail->data) == 1){
      l->tail->next = n;
      n->prev = l->tail;
      l->tail = n;
    }else{
      p = l->head;
      while(compare(sym,p->data) == 1)
        p = p->next;
      q = p->prev;
      n->prev = q;
      q->next = n;
      n->next = p;
      p->prev = n;
    }
  }
}

EXPORT void listmodify(List *l, void *origd, void *newd)
{
  Listnode *n = l->head;
  while(n){
    if(n->data == origd){
      n->data = newd;
      //return;
    }
    n = n->next;
  }
}

EXPORT void listrmtail(List *l)
{
  Listnode *p;

  if(l->head == l->tail){
    l->head = l->tail = NULL;
    return;
  }

  p = l->head;
  while(p->next != l->tail)
    p = p->next;
  p->next = NULL;
  l->tail = p;
}

