/*~!username.c*/
/* Name:  username.c Part No.: _______-____r
 *
 * Copyright 1992 - J B Systems, Morrison, CO
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

#ident	"@(#)nbclib:username.c	1.0"

#ifdef MPX1X

#include <finfo.h>
#include <limits.h>
#include <string.h>

/* these routines only used in MPX 1X */

/* setuser
 * will set current username to that specified by caller
 * old username and key will be saved so it can be restored
 * by restuser routine defined below
 * returns 0 for O.K., 1 for error
 */
static int tmpuser[2];	/* where we save username for restuser */
    			/* if tmpuser[0] == 0:  -> no username */
    			/* if tmpuser[0] != 0:  -> ascii username */
static short tmpkey;	/* where we save compressed key */
static short chgun;	/* set non zero if username changed */

extern short userkey;	/* defined in mpxini.c */
extern int curwdir[];	/* defined in mpxini.c */

setuser(un, ky)
int * un;	/* new username to set */
    		/* if un[0] == 0: -> no username */
    		/* if un[0] and un[1] == 'SYSTEM': -> no username */
    		/* if un[0] and un[1] == all blanks: -> no username */
    		/* if un[0] != 0: -> have username */

int * ky;	/* new userkey to set */
    		/* if ky[0] == 0 and ky[1] == val: -> comp key */
    		/* if ky[0] == 0 and ky[1] == 0: -> no key */
    		/* if ky[0] and ky[1] are ascii blanks: -> no key */
    		/* if ky[0] != 0: -> ascii key */
{
    int tempuser[2];
    int tempkey[2];
    int reg[8];

    getcwvd();			/* get current username info */
    chgun = 0;			/* username not changed yet */
    tmpuser[0] = curwdir[0];	/* save curr username */
    tmpuser[1] = curwdir[1];	/* save curr username */
    tmpkey = userkey;   	/* save compressed key */

    /* if curwdir is null, no username associated with task */
    /* i.e., it is system.  Userkey would also be null */
    /* set up new username, assume system fisrt */
    tempuser[0] = 0;		/* assume no username */
    tempuser[1] = 0;		/* assume no username */
    tempkey[0] = 0;		/* assume no userkey */
    tempkey[1] = 0;		/* assume no userkey */

    if (un[0] != 0) {
      /* we have a name, check for system or blanks */
      if (strnicmp ((char *)un, "SYSTEM  ", 8) == 0)
    	;
      else if (strncmp ((char *)un, "        ", 8) == 0)
    	;
      /* not system or blanks, must have username */
      else strncpy ((char *)tempuser, (char *)un, 8);
    }

    /* tempuser now has null or username, check if the same as old */
    /* see if using same username */
    if ((tempuser[0] != tmpuser[0]) || (tempuser[1] != tmpuser[1])) {
      /* we need to change username, first determine key */
      if (strncmp ((char *)ky, "        ", 8) == 0)
    	;
      /* not blanks, copy userkey, could be null or ascii */
      else {
    	tempkey[0] = ky[0]; /* set userkey */
    	tempkey[1] = ky[1]; /* set userkey */
      }

      /* set key in r4 & r5 */
      reg[4] = tempkey[0];
      reg[5] = tempkey[1];

      /* set username in r6 & r7 */
      reg[6] = tempuser[0];
      reg[7] = tempuser[1];
      mpxsvc (0x1074, reg, reg);	/* set new username, m.user */
      if (reg[6] != tempuser[0])	/* if changed, not valid */
        return (1);			/* return error */
      /* we have valid username, key */
      chgun = 1;			/* show we changed username */
    }
    return (0);				/* success */
}

/* resetuser
 * will reset the username to what it was before calling setuser
 * only reset if chgun flag was set
 */
resetuser()
{
    int reg[8];

    if (chgun == 0)
      return;			/* not changed, return */

    /* set old key in r4 & r5 */
    reg[4] = 0;
    reg[5] = tmpkey;

    /* set old username in r6 & r7 */
    reg[6] = tmpuser[0];
    reg[7] = tmpuser[1];

    mpxsvc (0x1074, reg, reg);	/* reset username, m.user */
    /* we have reset username, key */
    chgun = 0;			/* show we changed username */
}

/* the following finfo is used by pn2fib to store converted path */
/* it's definition is in unixio.h */

static struct finfo fibx;

/* pn2fib converts a pathname to file infomation block
 * path has following forms: @SYSTEM(USERNAME,USERKEY)FILENAME,PASSWORD
 *           ^(USERNAME,USERKEY)FILENAME,PASSWORD
 *           (USERNAME)FILENAME
 *           FILENAME
 * Note: USERNAME, USERKEY, or PASSWORD can be blanks to represent NULL
 *
 * address of fibx above is returned if O.K., else 0
 */

/* set l chars in array p to blanks */
#define SETBLK(p,l) memset((p),' ',(l))
char * xt8ch();

struct finfo *
pn2fib(path)
char * path;
{
    int i;
    char *p = path;
    char *tp;

    ZINT ((int *)&fibx,9);		/* clear temp fib */
    if ( !p || !(*p))
      return(NULL);			/* error if no path */

    /* set current username as default directory */
    getcwvd();		/* get current stuff */
    fibx.username[0] = curwdir[0];
    fibx.username[1] = curwdir[1];
    fibx.userkey[1] = userkey;

    /* see if pseudo volume name present, if so, strip path to '(' */
    if (*p == '@' || *p == '^')
      if ((p = strchr(p, '(')) == NULL)
    	return(NULL);

    /* see if username present, if so, copy up to ',' or ')' found */
    if (*p == '(') {
      p++;				/* skip over '(' */
      tp = (char *)fibx.username;

      /* extract username, stop on ',' or ')' */
      if ((p = xt8ch(p, tp, ')')) == NULL)
    	return(NULL);
      if (!(*p))
    	return(NULL);			/* if no more chars, error */

      /* if we have a ',' userkey is present */
      if (*p == ',') {
        p++;				/* skip over ',' */
    	tp = (char *)fibx.userkey;

    	/* extract userkey, stop on ',' or ')' */
    	if ((p = xt8ch(p, tp, ')')) == NULL)
    	  return(NULL);
    	if (!(*p))
    	  return(NULL);			/* if no more chars, error */
    	if (*p == ',')
    	  return(NULL);			/* bad delimiter */
      }

      /* here, we should be pointing at a ')'. Skip over it */
      ++p;  /* skip over ')' */
    }

    /* now we can process filename and maybe password */
    tp = (char *)fibx.filename;
    if (!(*p)) {
      /* We will let this be O.K. when just the username is given */
      SETBLK(tp,8);			/* blank the filename */
      return (&fibx);			/* return O.K. */
/*      return(NULL);			/* if no more chars, error */
    }

    /* extract filename, stop on ',' or EOL */
    if ((p = xt8ch(p, tp, '\0')) == NULL)
      return(NULL);

    /* if we have a ',' password is present */
    if (*p == ',') {
      p++;				/* skip over ',' */
      tp = (char *)fibx.password;

      /* extract password, stop on ',' or EOL */
      if ((p = xt8ch(p, tp, '\0')) == NULL)
    	return(NULL);
      if (*p == ',')
    	return(NULL);			/* bad delimiter */
    }

    /* now we are at end of line, exit if no more chars */
    if ((*p))
      return(NULL);			/* if more chars, error */
    return (&fibx);
}

/* extract an 8 char name and blank fill if required */
/* ignore any characters past 8
/* NOTE: we may also want to do translation of filename characters
/* return updated pointer on sucess or NULL on failure */

char *
xt8ch(p, tp, tc)
char * p;		/* input char string */
char * tp;		/* output char string */
char   tc;		/* secondary delimiter to check for */
    			/* for none, use ' ' */
    			/* if EOL ('\0') allowed, use '\0' */
{
    int i;

    for (i=0; i < 8; i++) {
      /* char must be 0x20 -> 5f */
      /* blanks will specify null */
      if (!(*p) || (*p < 0x20 || *p > 0x5f))
    	if (tc != '\0')
    	  return(NULL);
      if(*p == ',' || *p == tc)
    	break;
      *tp++ = *p++;
    }

    /* error if no chars found, report error */
    /* if tc is ')' then '()' sequence is ok, null username defined */
    if (tc != ')')
      if (i == 0)
    	return (NULL);

    /* if less than 8 chars, blank fill */
    if (i < 8)
      SETBLK(tp,(8-i));

    /* if username is > 8 chars, skip over unused chars */
    while (*p && *p != ',' && *p != tc)
      ++p;

    return(p);			/* return updated pointer */
}

#endif
