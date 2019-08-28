/* caloff.h */

/*
 * 	(c) Copyright 1990 J B Systems
 *	This file contains non-based support modifications
 *	for operation under MPX.  Derived from Encores' base
 *	mode C compiler.
 */

/*
@(#) $Header: /bulk2/simhv/nbc-master/nbccom/RCS/caloff.h,v 1.3 2019/01/31 21:42:15 jbev Exp $	       */
/* 
	This file contains items removed from common.h for
	the PCO port.
*/

unsigned int     offsz;

unsigned int caloff()
{
    register    int i;
    unsigned int    temp;
    unsigned int    off;
    temp = 1;
    i = 0;
    do {
	temp <<= 1;
	++i;
    } while (temp != 0);
    off = (unsigned)1 << (i - 1);
    return(off);
}
