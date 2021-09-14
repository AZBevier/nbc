  �@  /*~!getenv.c*/  */* Name:  getenv.c Part No.: _______-____r *  *  - * Copyright 1994 - J B Systems, Morrison, CO -  *  G * The recipient of this product specifically agrees not to distribute, G G * disclose, or disseminate in any way, to any one, nor use for its own G G * benefit, or the benefit of others, any information contained  herein G 8 * without the expressed written consent of J B Systems. 8  *  / *                     RESTRICTED RIGHTS LEGEND /  *  D * Use, duplication, or disclosure by the Government is  subject  to D D * restriction  as  set forth in paragraph (b) (3) (B) of the Rights D D * in Technical Data and Computer Software  Clause  in  DAR  7-104.9 D  * (a).   */      #ident	"@(#)nbclib:getenv.c	1.1"      /*      �@   *	getenv(name)  ? *	returns ptr to value associated with name, if any, else NULL ?  */  #define NULL	0     
#ifdef mpx 
 +#include <timeb.h>	/* were TZ is defined */ + #endif  extern char **environ;  static char *nvmatch();     char *  getenv(name)  register char *name;  {  "    register char *v, **p=environ; "        if(p == NULL)      	return(NULL);      while(*p != NULL)  *    	if((v = nvmatch(name, *p++)) != NULL) *     	    return(v);  
#ifdef mpx 
     if (!strcmp(name,"TZ")) {  !    	/* not there, use default */ !     	return(TZ);      }  #endif      return(NULL);  }     /*  # *	s1 is either name, or name=value #  *	s2 is name=value  0 *	if names match, return value of s2, else NULL 0          ,@  - *	used for environment searching: see getenv -  */     static char *  nvmatch(s1, s2)  register char *s1, *s2;  {      while(*s1 == *s2++)      	if(*s1++ == '=')      	    return(s2);  %    if(*s1 == '\0' && *(s2-1) == '=') %     	return(s2);      return(NULL);  } � �                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      @   		p->nd_fvl2 >>= 20;  		p->nd_fvl2 &= 0xfff;  =		p->nd_fval = (p->nd_fval << 12) | p->nd_fvl2 | 0x80000000L; = 		p->nd_fvl2 = 0;  		} else { 	 0		i = (i >> 3) & 0xff;		/* exponent is 8 bits */ 0 		i -= 127;			/* remove bias */  1		p->nd_fval = (p->nd_fval << 23 ) | 0x80000000L; 1 	}  ##else		/* use the UNIFORM format	*/ # 	if( sign ) fneg( p );  	i = p->nd_fval >> 24;  !	i &= 0x7f;				/* get exponent	*/ ! 	i -= 64;				/* remove bias	*/  	p->nd_fvl2 >>= 24;  	p->nd_fvl2 &= 0xff;  -	p->nd_fval = (p->nd_fval << 8) | p->nd_fvl2; - 	p->nd_fvl2 = 0;  #endif  .	if( i < -1 ){				/* no significance at all */ . 		p->nd_fval = 0;  			i = 31; 	 	}  	while( i < 31 ){  		p->nd_fval >>= 1;  		p->nd_fval &= 0x7fffffffL;  		i++;    