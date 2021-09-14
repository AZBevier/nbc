  �@  /*~!myatof.c*/  */* Name:  myatof.c Part No.: _______-____r *  *  - * Copyright 1995 - J B Systems, Morrison, CO -  *  G * The recipient of this product specifically agrees not to distribute, G G * disclose, or disseminate in any way, to any one, nor use for its own G G * benefit, or the benefit of others, any information contained  herein G 8 * without the expressed written consent of J B Systems. 8  *  / *                     RESTRICTED RIGHTS LEGEND /  *  D * Use, duplication, or disclosure by the Government is  subject  to D D * restriction  as  set forth in paragraph (b) (3) (B) of the Rights D D * in Technical Data and Computer Software  Clause  in  DAR  7-104.9 D  * (a).   */     #ident	"@(#)nblib:myatof.c	1.0"                �@  #ifdef MYATOF     #include <ctype.h>  #include "float.h"     J/*  Note : this atof() generates an internal floating point representation J D *	   of a number.  If we are in IEEE mode, the number is translated D C *	   to IEEE format.  Otherwise it is translated to Encore format. C  */     .FPN ifpn;	/* internal floating point number */ .    /* #define FLOATDEB */     #ifdef FLOATDEB  extern int sdump();  unsigned char ss[100];  #else  unsigned char ss[100];  #endif     FPN *  	myatof(s) 	 register  unsigned char  *s;  {  	register int i;  	int	tz;  		int	exp; 	 
	int	sign; 
 	int	esign;     #ifdef FLOATDEB  !	printf("myatof entry: %s\n", s); ! 	strcpy(ss,s);  	s = ss;  #else  
	*ss='\0'; 
         �@  	strcpy(ss,s);  	s = ss;  #endif  0	zerof( &ifpn );		/* clear destination number */ 0 7	esign = sign = exp = tz = 0;	/* and local variables */ 7    	i = *s++;		/* get 1st char */     #ifdef FLOATDEB  8	printf("tz = %x, exp = %x, next c = %x\n", tz, exp, i); 8 .	printf("myatof start: exp %d man ", ifpn.ne); . 	sdump(&ifpn.nf, NF);  #endif  $	/* skip any leading white spaces */ $ (	while( i == ' ' || i == '\t') i = *s++; ( 	/* see if a sign given */  	if( i == '-' ) {  			sign++; 	 		i = *s++;  	} else if( i == '+' )  		i = *s++;  !	/* skip any more white spaces */ ! (	while( i == ' ' || i == '\t') i = *s++; ( 	/* skip any leading zero's */  	while( i == '0') i = *s++;  $	/* now process any number digits */ $               �@  	while( i >= '0' && i <= '9' ){  !		tz = dodig( &ifpn, i-'0', tz ); ! 		i = *s++;  #ifdef FLOATDEB  8	printf("tz = %x, exp = %x, next c = %x\n", tz, exp, i); 8 *	printf("myatof 1: exp %d man ", ifpn.ne); * 	sdump(&ifpn.nf, NF);  #endif  	}  )	/* now process a fraction, if present */ ) 	if( i == '.' ){  		/* do the fraction */  		i = *s++;   		while( i >= '0' && i <= '9' ){   "			tz = dodig( &ifpn, i-'0', tz ); " 				exp--; 	 			i = *s++;  		}  	}  #ifdef FLOATDEB  8	printf("tz = %x, exp = %x, next c = %x\n", tz, exp, i); 8 *	printf("myatof 2: exp %d man ", ifpn.ne); * 	sdump(&ifpn.nf, NF);  #endif  	/* now see if exponent */  	exp = (tz + exp);  *	tz = 0;			/* zero trailing zeros count */ *                              �@  !	/* skip any more white spaces */ ! (	while( i == ' ' || i == '\t') i = *s++; ( #ifdef FLOATDEB  8	printf("tz = %x, exp = %x, next c = %x\n", tz, exp, i); 8 *	printf("myatof 3: exp %d man ", ifpn.ne); * 	sdump(&ifpn.nf, NF);  #endif  *	/* now process an exponent, if present */ * 	if( i == 'e' || i == 'E' ){  		/* do the exponent */  		i = *s++;  		/* see if a sign given */  		if( i == '-' ) {  			esign++;  			i = *s++;  		} else if( i == '+' )  			i = *s++;  		/* skip any leading zero's */  		while( i == '0') i = *s++;   		while( i >= '0' && i <= '9' ){   			tz = tz * 10 + i-'0';  			i = *s++;  		}  	}  #ifdef FLOATDEB  8	printf("tz = %x, exp = %x, next c = %x\n", tz, exp, i); 8                                     �@  *	printf("myatof 4: exp %d man ", ifpn.ne); * 	sdump(&ifpn.nf, NF);  #endif  	/* we are done with number */  	if (esign) tz = -tz;  	/* set the exponent */  	ifpn.ne += (tz + exp);  #ifdef FLOATDEB  8	printf("tz = %x, exp = %x, next c = %x\n", tz, exp, i); 8 *	printf("myatof 5: exp %d man ", ifpn.ne); * 	sdump(&ifpn.nf, NF);  #endif  $	/* if negative, negate the value */ $ 	if( sign ) negf( &ifpn );  #ifdef FLOATDEB  8	printf("tz = %x, exp = %x, next c = %x\n", tz, exp, i); 8 ,	printf("ret myatof: exp %d man ", ifpn.ne); , 	sdump(&ifpn.nf, NF);  #endif  	return (&ifpn);  }     #endif /* MYATOF */ � �                                                                                                                           @   #endif  + /* wander thru a tree with a stack finding + 7  * its structure so the next header can be located. */ 7 	mlsp = mlstack;     	for (;; ++n) {  *	    if ((mlop = n->mlnode.op) < OPSIMP) { * 		switch (optype(mlop)) {     		    default:  )			cerror("(1)unknown opcode: %x", mlop); ) 		    case BITYPE:  			goto binary;  		    case UTYPE:  				break; 	 		    case LTYPE:  			goto leaf;  		}  	    }  	    else {  		if (mamask[mlop - OPSIMP] &  F			(SIMPFLG | COMMFLG | MULFLG | DIVFLG | LOGFLG | FLOFLG | SHFFLG)) { F 	    binary:  		    *mlsp++ = BITYPE;  		}  		else  -		    if (!(mamask[mlop - OPSIMP] & UTYPE)) { - 		/* includes OPANY */     		leaf:  			if (mlsp == mlstack)  			    goto tree_end;     