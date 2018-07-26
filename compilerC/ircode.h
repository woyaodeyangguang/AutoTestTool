#ifndef IRCODE
#error "define the macro IRCODE before using ircode.h"
#endif

/* IRCODE(ircode, name)*/
IRCODE(BOR, "|")
IRCODE(BXOR, "^")
IRCODE(BAND, "&")
IRCODE(LSH, "<<")
IRCODE(RSH, ">>")
IRCODE(ADD, "+")
IRCODE(SUB, "-")
IRCODE(MUL, "*")
IRCODE(DIV, "/")
IRCODE(MOD, "%")
IRCODE(NEG, "-")
IRCODE(BCOM, "~")

IRCODE(JZ, "JZ")
IRCODE(JNZ, "!")
IRCODE(JE, "==")
IRCODE(JNE, "!=")
IRCODE(JG, ">")
IRCODE(JL, "<")
IRCODE(JGE, ">=")
IRCODE(JLE, "<=")

IRCODE(JMP, "jmp")
IRCODE(IJMP, "ijmp")
IRCODE(DEREF, "*")
IRCODE(ADDR, "&")
IRCODE(CALL, "call")
IRCODE(RET, "ret")
IRCODE(CLR, "clr")
IRCODE(MOV, "=")
IRCODE(IMOV, "*=")

IRCODE(CVTI1I4, "(int)(char)")
IRCODE(CVTI1U4, "(unsigned)(char)")
IRCODE(CVTU1I4, "(int)(unsigned char)")
IRCODE(CVTU1U4, "(unsigned)(unsigned char)")
IRCODE(CVTI2I4, "(int)(short)")
IRCODE(CVTI2U4, "(unsigned)(short)")
IRCODE(CVTU2I4, "(int)(unsigned short)")
IRCODE(CVTU2U4, "(unsigned)(unsigned short)")
IRCODE(CVTI4I1, "(char)(int)")
IRCODE(CVTI4U1, "(unsigned char)(int)")
IRCODE(CVTI4I2, "(short)(int)")
IRCODE(CVTI4U2, "(unsigned short)(int)")
IRCODE(CVTI4I8, "(long long)(int)")
IRCODE(CVTI4U8, "(unsigned long long)(int)")
IRCODE(CVTI4F4, "(float)(int)")
IRCODE(CVTI4F8, "(double)(int)")
IRCODE(CVTU4I8, "(long long)(unsigned)")
IRCODE(CVTU4U8, "(unsigned long long)(unsigned)")
IRCODE(CVTU4F4, "(float)(unsigned)")
IRCODE(CVTU4F8, "(double)(unsigned)")
IRCODE(CVTI8I4, "(int)(long long)")
IRCODE(CVTI8U4, "(unsigned)(long long)")
IRCODE(CVTU8I4, "(int)(unsigned long long)")
IRCODE(CVTU8U4, "(unsigned)(unsigned long long)")
IRCODE(CVTF4I4, "(int)(float)")
IRCODE(CVTF4U4, "(unsigned)(float)")
IRCODE(CVTF4F8, "(double)(float)")
IRCODE(CVTF8I4, "(int)(double)")
IRCODE(CVTF8U4, "(unsigned)(double)")
IRCODE(CVTF8F4, "(float)(double)")
IRCODE(NOP, "NOP")