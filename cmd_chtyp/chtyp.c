/*~!chtyp.c*/
/* Name:  chtyp.c Part No.: _______-____r
 *
 * Copyright 1995 - J B Systems, Morrison, CO
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

#ident	"Make4MPX $Id: chtyp.c,v 1.4 2021/07/05 16:11:40 jbev Exp $"

/*
 * $Log: chtyp.c,v $
 * Revision 1.4  2021/07/05 16:11:40  jbev
 * Correct type's/
 *
 * Revision 1.3  2021/07/02 23:02:17  jbev
 * Correct warnings.
 *
 * Revision 1.2  2021/07/02 22:12:40  jbev
 * Correct warnings.
 *
 * Revision 1.1  1995/03/14 01:21:33  jbev
 * Initial revision
 *
 */

/*
 * chtyp command:
 *	chtyp type file1 file2 ....
 */

#include <stdio.h>
#include <sys/fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <string.h>
#include <ctype.h>
#ifndef mpx
#include <stdlib.h>
#include <unistd.h>
#endif

extern int chtype();
extern void usage();
extern char *getcwd();
static char *cvtfname();
static char *pathname();
static void crunch();
#ifdef mpx
extern char curvol[];
extern char curdir[];
extern char *getcwvd();
extern char *str2lc();
static void conv2unix();
static void blcpy();
static void strlcpy();
#endif

#define	MAXN	128

struct stat stbuf;

int main(argc, argv)
int argc;
char *argv[];
{
    int type = 0;
    int i;
    int rc = 0;
    char *ip;
    char *fn;

    ip = argv[1];		/* get type */

    /* get type */
    if (islower(*ip))
    	toupper(*ip);
    if (islower(ip[1]))
    	toupper(ip[1]);
    if(!(isxdigit(*ip) && isxdigit(ip[1]))) {
    	fprintf(stderr, "chtye: type must be two hex digits\n");
    	usage();
    }
    if (isdigit(*ip))
    	*ip -= '0';
    else
    	*ip -= '7';
    if (isdigit(ip[1]))
    	ip[1] -= '0';
    else
    	ip[1] -= '7';
    type = ((ip[0] & 0xf) << 4) | (ip[1] & 0xf);

    if(argc < 3)
    	usage();

    for (i = 2; i < argc; i++) {
    	/* convert each input file name */
    	if((fn = cvtfname(argv[i])) == (char *)0) {
    	    fprintf(stderr, "chtyp: can't resolve path %s\n", argv[i]);
    	    rc++;		/* show error */
    	    continue;
    	}
    	/* see if file there */
    	if(stat(fn, &stbuf) < 0) {
    	    fprintf(stderr, "chtyp: can't locate file %s\n", argv[i]);
    	    rc++;		/* show error */
    	    continue;
    	}
    	/* change the file type */
    	if (chtype(fn, type) < 0) {
    	    fprintf(stderr, "chtyp: can't change type, file %s\n", argv[i]);
    	    rc++;
    	    continue;
    	}
    }
    exit(rc ? 2 : 0);
}

void usage()
{
    fprintf(stderr, "Usage: chtyp type f1 f2 ... fn\n");
    exit(2);
}

#ifndef mpx
int chtype(path, type)
char *path;
int type;
{
    return 0;		/* always ok on unix */
}
#endif

/* cvtfname
 * convert an arbitrary filename to a qualified unix pathname.
 * return pointer to malloc'd name or null if error.
 */
static char *
cvtfname(path)
char *path;
{
    char *dirp, *retp;

#ifdef mpx
    /* make sure pathname is l/c */
    str2lc(path);
#endif
    /* get default working directory */
    dirp = getcwd(0, MAXN);
    retp = pathname(dirp, path);
    if (dirp)
    	free(dirp);
    return(retp);
}

/* Convert relative to absolute pathnames */

/* Given a working directory and an arbitrary pathname, resolve them into
 * an absolute pathname. Memory is allocated for the result, which
 * the caller must free
 */
static char *
pathname(cd,path)
char *cd;	/* Current working directory */
char *path;	/* Pathname argument */
{
    register char *buf;

    if(cd == (char *)0 || path == (char *)0)
    	return (char *)0;

    /* Strip any leading white space on args */
    while(*cd == ' ' || *cd == '\t')
    	cd++;
    while(*path == ' ' || *path == '\t')
    	path++;

    /* Allocate and initialize output buffer; user must free
     * add fudge factor to malloc size in case user specified
     * just a / and we must replace it with /system/system
     */
    buf = (char *)malloc((unsigned)strlen(cd) + strlen(path) + 16);
    buf[0] = '\0';

    /* Interpret path relative to cd only if it doesn't begin with "/" */
    /* for MPX also see if @, ^, or ( */
    if(*path == '/'
#ifdef mpx
      || *path == '@' || *path == '^' || *path == '('
#endif
      ) {
    	crunch(buf,path);
    } else {
    	crunch(buf,cd);
    	crunch(buf,path);
    }

    /* Special case: null final path means the root directory */
    if(buf[0] == '\0'){
    	buf[0] = '/';
    	buf[1] = '\0';
    }
#ifdef mpx
    /* now convert to a qualified unix name if it was entered
     * as an MPX name
     */
    conv2unix(buf);
#endif

    return buf;
}

/* Process a path name string, starting with and adding to
 * the existing buffer
 */
static void
crunch(buf,path)
char *buf;
register char *path;
{
    register char *cp;
	
    cp = buf + strlen(buf);	/* Start write at end of current buffer */
	
    /* Now start crunching the pathname argument */
    for(;;){
    	/* Strip leading /'s; one will be written later */
    	while(*path == '/')
    	    path++;
    	if(*path == '\0')
    	    break;		/* no more, all done */
    	/* Look for parent directory references, either at the end
    	 * of the path or imbedded in it
    	 */
    	if(strcmp(path,"..") == 0 || strncmp(path,"../",3) == 0) {
    	    /* Hop up a level */
    	    if((cp = strrchr(buf,'/')) == (char *)0)
    		    cp = buf;		/* Don't back up beyond root */
    		*cp = '\0';		/* In case there's another .. */
    		path += 2;		/* Skip ".." */
    		while(*path == '/')	/* Skip one or more slashes */
    		    path++;
    		/* Look for current directory references, either at the end */
    		/* of the path or imbedded in it */
    	} else if(strcmp(path,".") == 0 || strncmp(path,"./",2) == 0) {
    	    /* "no op" */
    	    path++;			/* Skip "." */
    	    while(*path == '/')		/* Skip one or more slashes */
    		path++;
    	} else {
    	    /* Ordinary name, copy up to next '/' or end of path */
#ifdef mpx
    if(cp == buf && (*path == '@' || *path == '^' || *path == '(')) {
    } else
#endif
    	    *cp++ = '/';
    	    while(*path != '/' && *path != '\0')
    		*cp++ = *path++;
    	}
    }
    *cp++ = '\0';
}

#ifdef mpx
/* convert unix or mpx filename to unix filename */
/* .'s and multiple /'s will have been removed by crunch above */
/* first char must be /, ., @, ^, or ( to be converted */
/* NOTE: string supplied must be big enough for conversion */

static void
conv2unix(s)
register char *s;
{
    register char *os = s;
    char *tp;

    if (s == 0 || *s == 0)return;
    	switch (*os) {
    	    case '/':		/* path starts with /, leave it */
    		/* check for just a '/', if yes, give /system/system */
    		if (*++os == '\0') {	/* see if just a '/' */
    		    strcat(os, "system/system"); /* copy in root */
    		    return;		/* we are done */
    		}
    		return;		/* done with conversion */

    	    case '^':		/* path starts with ^ put in /curvol */
    		getcwvd();	/* get current working vol, dir */
    		/* move over other "stuff" to make room for vol */
    		bcopy(&os[1], os+strlen(curvol)+1, strlen(os));
    		blcpy(curvol, os+1, strlen(curvol));
    		/* go to process dir name, if any */
    		goto dodir;

    	    case '(':		/* path starts with ( put in /curvol */
    		getcwvd();	/* get current working vol, dir */
    		/* move over other "stuff" to make room for vol */
    		bcopy(os, os+strlen(curvol)+1, strlen(os)+1);
    		blcpy(curvol, os+1, strlen(curvol));
    		/* drop thru to process dir name, if any */

    	    case '@':		/* path starts with @ put in / */
dodir:
    		*os++ = '/';
    		/* check for just an '@', if yes, give /system */
    		if (*os == '\0') {	/* see if just a '@' */
    		    strcat(os, "system/system"); /* copy in root */
    		    return;		/* we are done */
    		}
    		/* check to see if @vol^dir or @vol^(dir) */
    		if (tp = strchr(os, '^')) {       /* got end of vol */
    		    /* check to see if next char is '('.  If yes,
    		     * just delete the ^ and continue
    		     */
    		    if (tp[1] == '(') {		/* see if '(' */
    			bcopy(&tp[1], tp, strlen(tp));
    		    } else {
    			*tp++ = '/';	/* terminate volume name */
    		    }
    		    os = tp;		/* next char in input */
    		}
    		if (tp = strchr(os, '(')) {	/* got end of vol */
    		    *tp++ = '/';	/* terminate volume name */
    		    os = tp;		/* next char in input */
    		    if (tp = strchr(os, ')')) {  /* get end of dir */
    			if (tp[1] == '\0')  /* see if a file name */
    			    *tp = '\0';	/* no, leave off last / */
    			else
    			    *tp++ = '/';    /* terminate directory */
    			os = tp;        /* start of file name or null */
    		    } else {		/* have /vol/, will get error */
    			return;
    		    }
    		} else {		/* have /vol, just wants volume */
    		    return;
    		}
    		return;			/* done with conversion */

    	    case '.' :            /* curr directory? */
    		if (os[1] == '.') { /* have .. now what? */
    		    if (os[2] == '/') { /* have ../ put in cur vol */
    			getcwvd();	/* get current working vol, dir */
    			bcopy(&os[3], os+strlen(curvol)+2, strlen(os) - 1);
    			*os++ = '/';
    			blcpy(curvol, os, strlen(curvol));
    			os += (strlen(curvol)+1);
    			*os++ = '/';
    			return;
    		    }
    		    if (os[2] == 0) { /* have just .. give vol */
    			getcwvd();	/* get current working vol, dir */
    			*os++ = '/';
    			strlcpy (os, curvol);
    			os += strlen(curvol);
    			*os++ = '\0';        /* end of volume */
    			return;          /* return /vol */
    		    }
    		    return;            /* have ..? just an error */
    		}
    		if (os[1] == '/') {  /* have ./, just curr dir */
    		    /* copy down file name */
    		    bcopy(&os[2], os, strlen(os));
    		    return;
    		}
    		if (os[1] == 0) {    /* have just ., return curr dir */
    		    *os++ = '/';
    		    getcwvd();	/* get current working vol, dir */
    		    strlcpy(os, curvol); /* copy in volume */
    		    os += strlen(curvol);
    		    *os++ = '/';        /* start of dir */
    		    strlcpy(os, curdir); /* copy in dir */
    		    os += strlen(curdir);
    		    *os++ = '\0';        /* terminate dir */
    		    return;
    		}
    		return;              /* have .? just an error */
    	    default:
    		return;              /* everything else o.k. */
    	}
}

/*
 * copy string p2 to string p1, converting to l/c as we go.
 */
static void
strlcpy(p1, p2)
char * p1;
char * p2;
{
    int c;
    /* copy p2 to p1 */
    while (c = *p2++) {
    	if (isupper(c))
    	    c = tolower(c);
    	*p1++ = c;
    }
    *p1 = '\0';
}

/*
 * copy string b1 to l/c string b2, with overlap testing
 */
static void
blcpy (b1, b2, length)
     register char *b1;
     register char *b2;
     register int length;
{
    register int c;
    /* handle buffer overlap case */
    if (b1 < b2)	/* possible overlap */
    	for (b1 += length, b2 += length; length--; ) {
    	    c = *--b1;
    	    if (isupper(c))
    		c = tolower(c);
    	    *--b2 = c;
    	}
    else
    	for (;length--;) {
    	    c = *b1++;
    	    if (isupper(c))
    		c = tolower(c);
    	    *b2++ = c;
    	}
}

#endif /* mpx */
