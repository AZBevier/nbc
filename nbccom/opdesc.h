/* opdesc.h */

/*
 * 	(c) Copyright 1990 J B Systems
 *	This file contains non-based support modifications
 *	for operation under MPX.  Derived from Encores' base
 *	mode C compiler.
 */

/* $Header: /bulk2/simhv/nbc-master/nbccom/RCS/opdesc.h,v 1.3 2019/01/31 22:00:07 jbev Exp $ */

/*
 * $Log: opdesc.h,v $
 * Revision 1.3  2019/01/31 22:00:07  jbev
 * Fix for Linux
 *
 * Revision 1.2  1996/03/22 00:05:49  jbev
 * Cleanup for Alpha port.
 *
 */

/* 

	This file contains items removed from common.h for
	the PCO port.

*/

int         dope[DSIZE];
char       *opst[DSIZE];

struct      dopest
{
    int         dopeop;
    char        opst[8];
    int         dopeval;
}           indope[] =
{

    NAME, "NAME", LTYPE,
    LNAME, "LNAME", LTYPE,
    PNAME, "PNAME", LTYPE,
    STATNAME, "STATNAM", LTYPE,
    TNAME, "TNAME", LTYPE,
    LTEMP, "LTEMP", LTYPE,
    STRING, "STRING", LTYPE,
    REG, "REG", LTYPE,
    TREG, "TREG", LTYPE,
    OREG, "OREG", LTYPE,
    ICON, "ICON", LTYPE,
    STLABEL, "STLAB", LTYPE,
    ADDR, "ADDR", LTYPE,
    LADDR, "LADDR", LTYPE,
    PADDR, "PADDR", LTYPE,
    STADDR, "STADDR", LTYPE,
    FCON, "FCON", LTYPE,
    CCODES, "CCODES", LTYPE,
    LEAFNOP, "LFNOP", LTYPE,
    UNARY MINUS, "U-", UTYPE,
    UNARY MUL, "U*", UTYPE,
    UNARY AND, "U&", UTYPE,
    UNARY CALL, "UCALL", UTYPE | CALLFLG,
    UNARY FORTCALL, "UFCALL", UTYPE | CALLFLG,
    NOT, "!", UTYPE | LOGFLG,
    COMPL, "~", UTYPE,
    FORCE, "FORCE", UTYPE,
    INIT, "INIT", UTYPE,
    SCONV, "SCONV", UTYPE,
    PCONV, "PCONV", UTYPE,
    OCONVLEAF, "OCONVL", UTYPE,
    OCONVTREE, "OCONVT", UTYPE,
    UNARYNOP, "UNYNOP", UTYPE,
    PLUS, "+", BITYPE | FLOFLG | SIMPFLG | COMMFLG | COMMUTEFLG,
    ASG PLUS, "+=", BITYPE | ASGFLG | ASGOPFLG | FLOFLG | SIMPFLG | COMMFLG,
    MINUS, "-", BITYPE | FLOFLG | SIMPFLG,
    ASG MINUS, "-=", BITYPE | FLOFLG | SIMPFLG | ASGFLG | ASGOPFLG,
    MUL, "*", BITYPE | FLOFLG | MULFLG | COMMUTEFLG,
    ASG MUL, "*=", BITYPE | FLOFLG | MULFLG | ASGFLG | ASGOPFLG,
    AND, "&", BITYPE | COMMFLG | BITFLG | COMMUTEFLG,
    ASG AND, "&=", BITYPE | COMMFLG | ASGFLG | ASGOPFLG | BITFLG,
    QUEST, "?", BITYPE,
    COLON, ":", BITYPE,
    ANDAND, "&&", BITYPE | LOGFLG,
    OROR, "||", BITYPE | LOGFLG,
    CM, "CM", BITYPE,
    COMOP, "COMOP", BITYPE,
    ASSIGN, "=", BITYPE | ASGFLG,
    DIV, "/", BITYPE | FLOFLG | MULFLG | DIVFLG,
    ASG DIV, "/=", BITYPE | FLOFLG | MULFLG | DIVFLG | ASGFLG | ASGOPFLG,
    MOD, "%", BITYPE | DIVFLG | MULFLG,
    ASG MOD, "%=", BITYPE | DIVFLG | MULFLG | ASGFLG | ASGOPFLG,
    LS, "<<", BITYPE | SHFFLG,
    ASG LS, "<<=", BITYPE | SHFFLG | ASGFLG | ASGOPFLG,
    RS, ">>", BITYPE | SHFFLG,
    ASG RS, ">>=", BITYPE | SHFFLG | ASGFLG | ASGOPFLG,
    OR, "|", BITYPE | COMMFLG | BITFLG | COMMUTEFLG,
    ASG OR, "|=", BITYPE | COMMFLG | ASGFLG | ASGOPFLG | BITFLG,
    ER, "^", BITYPE | COMMFLG | BITFLG | COMMUTEFLG,
    ASG ER, "^=", BITYPE | COMMFLG | ASGFLG | ASGOPFLG | BITFLG,
    INCR, "++", BITYPE | ASGFLG,
    DECR, "--", BITYPE | ASGFLG,
    STREF, "->", BITYPE,
    CALL, "CALL", BITYPE | CALLFLG,
    FORTCALL, "FCALL", BITYPE | CALLFLG,
    EQ, "==", BITYPE | LOGFLG | COMMUTEFLG,
    NE, "!=", BITYPE | LOGFLG | COMMUTEFLG,
    LE, "<=", BITYPE | LOGFLG,
    LT, "<", BITYPE | LOGFLG,
    GE, ">=", BITYPE | LOGFLG,
    GT, ">", BITYPE | LOGFLG,
    UGT, "UGT", BITYPE | LOGFLG,
    UGE, "UGE", BITYPE | LOGFLG,
    ULT, "ULT", BITYPE | LOGFLG,
    ULE, "ULE", BITYPE | LOGFLG,
    SLA, "SA<<", BITYPE | SHFFLG,
    ASG SLA, "SA<<=", BITYPE | SHFFLG | ASGFLG | ASGOPFLG,
    SRA, "SA>>", BITYPE | SHFFLG,
    ASG SRA, "SA>>=", BITYPE | SHFFLG | ASGFLG | ASGOPFLG,
#ifndef MPX
    ARS, "A>>", BITYPE,
#endif
    TYPE, "TYPE", LTYPE,
    LB, "[", BITYPE,
    CBRANCH, "CBRANCH", BITYPE,
    FLD, "FLD", UTYPE,
    PMCONV, "PMCONV", BITYPE,
    PVCONV, "PVCONV", BITYPE,
    RETURN, "RETURN", BITYPE | ASGFLG | ASGOPFLG,
    CAST, "CAST", BITYPE | ASGFLG | ASGOPFLG,
    GOTO, "GOTO", UTYPE,
    STASG, "STASG", BITYPE | ASGFLG,
    STARG, "STARG", UTYPE,
    STCALL, "STCALL", BITYPE | CALLFLG,
    UNARY STCALL, "USTCALL", UTYPE | CALLFLG,
    INCALL, "INCALL", BITYPE|CALLFLG,
    UNARY INCALL, "UINCALL", UTYPE|CALLFLG,
#ifdef MPX
    UMULP, "U*P", UTYPE,
    ASGP, "=P", BITYPE | ASGFLG,
    UANDP, "U&P", UTYPE,
#endif
    MCON, "MCON", LTYPE,
    -1, 0
};

void mkdope()
{
    register struct dopest *q;

    for (q = indope; q -> dopeop >= 0; ++q) {
	dope[q -> dopeop] = q -> dopeval;
	opst[q -> dopeop] = q -> opst;
    }
}

