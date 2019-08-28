/*~!unix2mpx.c*/
/* Name:  unix2mpx.c Part No.: _______-____r
 *
 * Copyright 1993 - J B Systems, Morrison, CO
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

#ident	"@(#)nbclib:unix2mpx.c	1.1"

#include <string.h>

extern char curvol[];
extern char curdir[];
extern void getcwvd();

/* convert unix filename to mpx filename */
/* first char must be / or . to be converted */
/* always converted to uppercase */
/* NOTE: string supplied must be big enough for conversion */

void
unix2mpx(s)
register char *s;
{
        register char *os = s;
        char *tp;

        if (!(s != 0 && *s != 0))return;
        str2up(s);              /* to upper case */
        switch (*os) {
          case '/' :            /* path starts with / put in @ */
            *os++ = '@';
    	    /* check for just a '/', if yes, give system(system) */
    	    if (*os == '\0') {	/* see if just a '/' */
    	      strcat(os, "SYSTEM(SYSTEM)");	/* copy in root */
    	      return;		/* we are done */
    	    }
            if (tp = strchr(os, '/')) {       /* got end of vol */
              *tp++ = '(';      /* terminate volume name */
              os = tp;          /* next char in input */
              if (tp = strchr(os, '/')) {  /* get end of dir */
                *tp++ = ')';    /* terminate directory */
                os = tp;        /* start of file name or null */
              } else {          /* have /vol/, will get error */
    		strcat(os, ")"); /* put on ')' for user */
                return;
              }
            } else {            /* have /vol, just wants volume */
    	      strcat(os, "^");	/* put on '^' for user */
              return;
            }
          return;               /* done with conversion */

          case '.' :            /* curr directory? */
            if (os[1] == '.') { /* have .. now what? */
              if (os[2] == '/') { /* have ../ put in cur vol */
		getcwvd();	/* get current working vol, dir */
                bcopy(&os[3], os+strlen(curvol)+2, strlen(os) - 2);
                *os++ = '@';
                bcopy(curvol, os, strlen(curvol));
#ifdef FIX_02_05_93
                os += (strlen(curvol)+1);
#else
                os += (strlen(curvol));
#endif
                *os++ = '(';
                if (tp = strchr(os, '/'))*tp = ')';
    		else {
    		 os += strlen(os);
    		 *os++ = ')';	/* set end of dir */
    		 *os++ = '\0';	/* terminate it */
    		}
                return;
              }
              if (os[2] == 0) { /* have just .. give vol */
		getcwvd();	/* get current working vol, dir */
                *os++ = '@';
                strcpy (os, curvol);
                return;          /* return @vol */
              }
              return;            /* have ..? just an error */
            }
            if (os[1] == 0 || (os[1] == '/' && os[2] == 0)) {
    	      /* have just . or ./, return curr dir */
              *os++ = '@';
	      getcwvd();	/* get current working vol, dir */
              strcpy(os, curvol); /* copy in volume */
              os += strlen(curvol);
              *os++ = '(';        /* start of dir */
              strcpy(os, curdir); /* copy in dir */
              os += strlen(curdir);
              *os++ = ')';        /* end of dir */
              *os = 0;            /* terminate string */
              return;
            }
            if (os[1] == '/') {  /* have ./, just curr dir */
    	      /* copy down file name */
              bcopy(&os[2], os, strlen(os) - 1);
              return;
            }
            return;              /* have .? just an error */
          default:
            return;              /* everything else o.k. */
        }
}
