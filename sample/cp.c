/*~!cp.c*/
/* Name:  cp.c Part No.: _______-____r
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

#ident	"Make4MPX $Id: cp.c,v 1.4 1995/10/17 23:23:24 jbev Exp $"

/* $Log: cp.c,v $
 * Revision 1.4  1995/10/17  23:23:24  jbev
 * Bad test in determining file type.  Should be 768 instead of 255.
 * Caused files to be created as unblocked file when really blocked.
 *
 * Revision 1.3  1995/10/17  23:20:29  jbev
 * Always delete target file before creation of new one.
 * Delete code to test for same file on MPX.  Didn't work.
 *
 * Revision 1.2  1995/03/14  04:03:41  jbev
 * Correct external errorrs.
 *
 * Revision 1.1  1995/03/14  01:27:56  jbev
 * Initial revision
 *
 */

/*
 * cp command:
 *	cp -uoa file1 file2
 *	cp -uoa file1 ... filen dir1
 */

#include <stdio.h>
#include <sys/fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <string.h>
#include <ctype.h>

char *dname();
extern char *getcwd();
static char *cvtdname();
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

#ifndef mpx
#define O_UNBLK	0
#define O_BIN	0
#endif

#define	DOT	"."
#define	DELIM	'/'
#define	MAXN	128
#define BLKSIZE    2048

unsigned char fbuf[BLKSIZE];

struct stat s1, s2;

int aflg = 0;		/* copy in ascii mode (default) */
int oflg = 0;		/* copy in object mode */
int uflg = 0;		/* copy in unblocked mode */

main(argc, argv)
int argc;
char *argv[];
{
    int i, rc, optc;
    extern int optind;
    int errflg = 0;
    char *ip, *op;

    while ((optc=getopt(argc, argv, "AaOoUu")) != EOF)
    	switch(optc) {
    	    case 'A':		/* user wants ascii copy */
   	    case 'a':
    		aflg++;
    		oflg=0;
    		uflg=0;
    		break;
    	    case 'O':		/* user wants blocked object copy */
    	    case 'o':
    		oflg++;
    		aflg=0;
    		uflg=0;
    		break;
    	    case 'U':		/* user wants unblocked copy */
    	    case 'u':
    		uflg++;
    		aflg=0;
    		oflg=0;
    		break;
    	    case '?':		/* who knows what he wants */
    		errflg++;
    	}
    if(((argc-optind) < 2) || errflg)
    	usage();

    /* convert 1st arg to file pathname */
    if((ip = cvtfname(argv[optind])) == (char *)0) {
    	fprintf(stderr, "cp: can't resolve path %s\n", argv[optind]);
    	usage();
    }
    /* see if 1st arg is a file */
    stat(ip, &s1);

    /* if not regular file, error */
    if ((s1.st_mode & S_IFMT) != S_IFREG)
    	usage();

    setuid(getuid());
    /* if more than two args, last one must be directory */
    if ((argc-optind) > 2) {
    	/* convert last arg to a directory */
    	if((op = cvtdname(argv[argc - 1])) == (char *)0) {
    	    fprintf(stderr, "cp: can't resolve path %s\n", argv[argc - 1]);
    	    exit(2);
    	}
    	/* see if last arg is a directory */
    	if (stat(argv[argc - 1], &s2) < 0) {
    	    fprintf(stderr, "cp: directory %s not found\n", argv[argc - 1]);
    	    exit(2);
    	} 
    	if ((s2.st_mode & S_IFMT) != S_IFDIR)
    	    usage();
    	rc = 0;
    	for (i = optind; i < argc - 1; i++) {
    	    /* convert each input file name */
    	    if((ip = cvtfname(argv[i])) == (char *)0) {
    		fprintf(stderr, "cp: can't resolve path %s\n", argv[i]);
    		rc++;		/* show error */
    		continue;
    	    }
    	    rc += move(ip, op);
    	}
    	exit(rc ? 2 : 0);
    }
    /* Here we have exactly two args, the 2nd of which can be a file
     * or directory.  We will assume that if just a plain name is
     * given, it is file.  If it starts with a /, @, ^, .., or (,
     * then it is a directory.
     */
    op = argv[argc - 1];
    if (*op == '/' || *op == '@' || *op == '^' || *op == '(' ||
      (*op == '.' && op[1] == '.') || (*op == '.' && op[1] == '\0')) {
    	/* we have a directory, process it */
    	/* convert last arg to a directory */
    	if((op = cvtdname(argv[argc - 1])) == (char *)0) {
    	    fprintf(stderr, "cp: can't resolve path %s\n", argv[argc - 1]);
    	    exit(2);
    	}
    } else {
    	/* we have a file, process it */
    	/* convert last arg to a file name */
    	if((op = cvtfname(argv[argc - 1])) == (char *)0) {
    	    fprintf(stderr, "cp: can't resolve path %s\n", argv[argc - 1]);
    	    exit(2);
    	}
    }
    /* now move the file */
    if(move(ip, op))
    	exit(2);		/* got an error */
    exit(0);			/* all was O.K. */
}


move(source, target)
char *source, *target;
{
    char buf[MAXN];
    int from, to, cnt, mflg;
    int size, type;
    int iflag = O_RDONLY;
    int oflag = O_WRONLY | O_TRUNC | O_CREAT;
    int udflag = (aflg | oflg | uflg);

    /* set open type, from user */
    if(uflg) {			/* unblocked code */
    	iflag |= O_UNBLK;
    	oflag |= O_UNBLK;
    } else if (oflg) {		/* object code */
    	iflag |= O_BIN;
    	oflag |= O_BIN;
    }

    /* get status of from file */
    if (stat(source, &s1) < 0) {
    	fprintf(stderr, "cp: cannot access %s\n", source);
    	return(1);
    }
    /* if directory, error */
    if ((s1.st_mode & S_IFMT) == S_IFDIR) {
    	fprintf(stderr, "cp: <%s> directory\n", source);
    	return(1);
    }
    /* from is a file, so get its type/size for to file creation */
    type = s1.st_nlink;
    size = s1.st_size/768;	/* disk blocks */
#ifdef mpx
    setdft(type);		/* set new creat type */
    setsiz(size,size/16,size/16);	/* set default size */

    if (!udflag && type == 0xCA) {
    	iflag |= O_UNBLK;
    	oflag |= O_UNBLK;
    	udflag = 1;
    }
#endif

    /* if in=out, error, if out is a directory append name to path */
    if (stat(target, &s2) >= 0) {
    	if ((s2.st_mode & S_IFMT) == S_IFDIR) {
    	    sprintf(buf, "%s/%s", target, dname(source));
    	    target = buf;
    	}
    	if (stat(target, &s2) >= 0) {
#ifndef mpx
    	    if (s1.st_dev == s2.st_dev && s1.st_ino == s2.st_ino) {
    	    	fprintf(stderr, "cp: %s and %s are identical\n",
    		  source, target);
    	    	return(1);
    	    }
#endif
    	}
    }

    /* see if user supplied file type */
    if (udflag) {
    	/* yes, use what was given */
    	if ((from = open(source, iflag, 0666)) < 0) {
    	    fprintf(stderr, "cp: cannot open %s\n", source);
    	    return 1;
    	}
    } else {
    	/* no, find out what it is */
    	/* open unblocked */
    	if ((from = open(source, O_RDONLY | O_UNBLK, 0666)) < 0) {
    	    fprintf(stderr, "cp: cannot open %s\n", source);
    	    return 1;
    	}
    	read(from, fbuf, BLKSIZE);
    	if(fbuf[0] == 0 && fbuf[1] == 0 && ((fbuf[2] << 8 | fbuf[3]) < 768) &&
    	  fbuf[4] == 0x40 && fbuf[5] == 0) {
    	    /* we have a blocked file, see if an object file */
    	    if (fbuf[8] == 0xff || fbuf[8] == 0xdf) {
    		iflag |= O_BIN;
    		oflag |= O_BIN;
    	    }
    	} else {
    	    /* we have unblocked */
    	    iflag |= O_UNBLK;
    	    oflag |= O_UNBLK;
    	}
    	close (from);
    	/* now open in correct mode */
    	if ((from = open(source, iflag, 0666)) < 0) {
    	    fprintf(stderr, "cp: cannot open %s\n", source);
    	    return 1;
    	}
    }
    /* from is now open, let's do to */
    unlink(target);		/* delete the target file */
    /* see if we need to set mode */
    mflg = access(target, 0) == -1;
    if ((to = open(target, oflag, 0666)) < 0) {
    	fprintf(stderr, "cp: cannot open/create %s\n", target);
    	return 1;
    }
    /* to is now open, copy the file */
    while ((cnt = read(from, fbuf, BLKSIZE)) != 0)
    	if (cnt < 0 || write(to, fbuf, cnt) != cnt) {
    	    fprintf(stderr, "cp: bad copy to %s\n", target);
    	    if ((s2.st_mode & S_IFMT) == S_IFREG)
    		unlink(target);
    		return 1;
        }
    close(from), close(to);
    /* if created, change mode of to file */
    if (mflg)
#ifdef mpx
    	chmod(target, s1.st_mode & 0777);	/* just set mode bits */
#else
    	chmod(target, s1.st_mode);
#endif
    return 0;
}


char *
dname(name)
register char *name;
{
    register char *p;

    p = name;
    while (*p)
    	if (*p++ == DELIM && *p)
    	    name = p;
    return name;
}


usage()
{
    fprintf(stderr, "Usage: cp [-aou] f1 f2\n       cp [-aou] f1 ... fn d1\n");
    exit(2);
}

/* cvtdname
 * convert an arbitrary directory name to a qualified unix pathname.
 * return pointer to malloc'd name or null if error.
 */
static char *
cvtdname(path)
char *path;
{
    char *dirp, *dbuf, *retp;

    dbuf = (char *)malloc(MAXN);
#ifdef mpx
    /* make sure pathname is l/c */
    str2lc(path);
#endif
    /* get default working directory */
    dirp = getcwd(0, MAXN);
#ifdef mpx
    /* see if just a name, if so add () around name */
    if (*path != '/' && *path != '@' && *path != '^' && *path != '('
      && *path != '.') {
    	/* put () around dir name to see if o.k. */
    	dbuf[0] = '(';		/* start with ( */
    	strcpy(&dbuf[1], path);	/* copy name */
    	strcat(dbuf, ")");	/* put on ) */
    	retp = pathname(dirp, dbuf);
    } else {
    	retp = pathname(dirp, path);
    }
#else
    retp = pathname(dirp, path);
#endif
    if (dbuf)
    	free(dbuf);
    if (dirp)
    	free(dirp);
    return(retp);
}

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
    	    /* Look for current directory references, either at the end
    	     * of the path or imbedded in it
    	     */
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
