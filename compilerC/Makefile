#you can make your cunstomizations in custum.mk
include custom.mk

CC=gcc
LD=gcc
RM=rm -f
CFLAGS=-g -Wall
LDFLAGS=-g
OBJPATH=$(BUILDDIR)/
YACC=bison
LEX=flex

all: $(OBJPATH)hcc

HCCOBJS = $(OBJPATH)parser.o  \
          $(OBJPATH)simple.o \
          $(OBJPATH)alloc.o \
          $(OBJPATH)misc.o \
          $(OBJPATH)type.o \
          $(OBJPATH)string.o \
          $(OBJPATH)ast.o \
          $(OBJPATH)semantic.o \
          $(OBJPATH)symbol.o \
          $(OBJPATH)ir.o \
          $(OBJPATH)opt.o \
          $(OBJPATH)irecho.o \
          $(OBJPATH)x86gen.o \
          $(OBJPATH)main.o 

$(OBJPATH)hcc: $(HCCOBJS)	
	$(LD) $(LDFLAGS) -g -o $@ $(HCCOBJS) 

$(OBJPATH)parser.o:	parser.c;	$(CC) $(CFLAGS) -c -g -o $@ parser.c
$(OBJPATH)simple.o:	simple.c;	$(CC) $(CFLAGS) -c -g -o $@ simple.c
$(OBJPATH)misc.o:	misc.c;		$(CC) $(CFLAGS) -c -g -o $@ misc.c
$(OBJPATH)alloc.o:	alloc.c;	$(CC) $(CFLAGS) -c -o $@ alloc.c
$(OBJPATH)string.o:	string.c;	$(CC) $(CFLAGS) -c -o $@ string.c
$(OBJPATH)type.o:	type.c;		$(CC) $(CFLAGS) -c -o $@ type.c
$(OBJPATH)ast.o:	ast.c;		$(CC) $(CFLAGS) -c -o $@ ast.c
$(OBJPATH)semantic.o:	semantic.c;	$(CC) $(CFLAGS) -c -o $@ semantic.c
$(OBJPATH)symbol.o:	symbol.c;	$(CC) $(CFLAGS) -c -o $@ symbol.c
$(OBJPATH)ir.o:		ir.c;		$(CC) $(CFLAGS) -c -g -o $@ ir.c
$(OBJPATH)opt.o:	opt.c;		$(CC) $(CFLAGS) -c -o $@ opt.c
$(OBJPATH)irecho.o:	irecho.c;	$(CC) $(CFLAGS) -c -o $@ irecho.c
$(OBJPATH)x86gen.o:	x86gen.c;	$(CC) $(CFLAGS) -c -o $@ x86gen.c
$(OBJPATH)main.o:	main.c;		$(CC) $(CFLAGS) -c -o $@ main.c

#generate C files from lex/yacc specifications
parser.c: hcc.y
	$(YACC) -d hcc.y -y -o $@ 
lexer.c: simple.l
	$(LEX)  -o $@ simple.l

clean:
	$(RM) $(OBJPATH)*  simple.c parser.c parser.h 
