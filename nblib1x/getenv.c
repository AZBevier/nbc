/*~!getenv.c*/
/* Name:  getenv.c Part No.: _______-____r
 *
 * Copyright 1994 - J B Systems, Morrison, CO
 *
 * The recipient of this product specifically agrees not to distribute,
 * disclose, or disseminate in any way, to any one, nor use for its own
 * benefit, or the benefit of others, any information contained  herein
 * without the expressed written consent of J B Systems.
 *
 *                     RESTRICTED RIGHTS LEGEND
 *
 * Use, duplication, or disclosure by the Government is  subject  to
 * restriction  as  set forth in paragraph (b) (3) (B) of the Rights
 * in Technical Data and Computer Software  Clause  in  DAR  7-104.9
 * (a).
 */

#ident	"@(#)nbclib:getenv.c	1.2"

/*
 *	getenv(name)
 *	returns ptr to value associated with name, if any, else NULL
 */
#define NULL	0

#include <stdio.h>
#ifdef mpx
#include <timeb.h>	/* were TZ is defined */
static int do_once;
#endif
extern char **environ;
static char *nvmatch();

char *
getenv(name)
register char *name;
{
    register char *v, **p=environ;
    char input[128];
    FILE *fp;

    if(p == NULL)
    	return(NULL);
    while(*p != NULL)
    	if((v = nvmatch(name, *p++)) != NULL)
    	    return(v);
#ifdef mpx
    if (!strcmp(name,"TZ")) {
    	if (do_once)
    	    return(TZ);
    	do_once++;
    	/* see if /system/system/timezone is present */
    	/* If so, get users TZ definition, else use default */
    	/* file must have format of TZ=MST7MDT */
    	if ((fp = fopen("/system/system/timezone", "r")) == (FILE *)0) {
    	    /* not there, use default */
    	    return(TZ);
    	}
    	/* We have the file, find TZ line */
    	while (fgets(input, 128, fp) != (char *)0) {
    	    /* ignore blank lines and lines starting with # */
    	    if (*input == '#' || *input == ' ' ||
    	      *input == '\n' || *input == '\t')
    		continue;		/* next line */
    	    if (*input == 'T' && input[1] == 'Z' && input[2] == '=') {
    		/* null terminate the command line */
    		for (v = input; *v; v++) {
    		    if (*v == ' ' || *v == '\n' || *v == ';' || *v == '\t') {
    			*v++ = ';';
    			*v = '\0';
 			break;
    		    }
    		}
    		/* we have the line, set the env TZ and return it's value */
    		fclose(fp);
    		v = (char *)malloc(strlen(input));
    		if (v != NULL) {
    		    strcpy(v, input);
    		    putenv(v);
    		}
    		return(&input[3]);
    	    }
    	}
    	fclose(fp);
    	/* not there, use default */
    	return(TZ);
    }
#endif
    return(NULL);
}

/*
 *	s1 is either name, or name=value
 *	s2 is name=value
 *	if names match, return value of s2, else NULL
 *	used for environment searching: see getenv
 */

static char *
nvmatch(s1, s2)
register char *s1, *s2;
{
    while(*s1 == *s2++)
    	if(*s1++ == '=')
    	    return(s2);
    if(*s1 == '\0' && *(s2-1) == '=')
    	return(s2);
    return(NULL);
}
