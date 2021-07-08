/*~!pwd.c*/
/* Name:  pwd.c Part No.: _______-____r
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

#ident	"$Id: pwd.c,v 1.2 2021/07/07 23:09:52 jbev Exp $"

/*	$Log $
 */

#include	"defs.h"
#include	<sys/types.h>
#include	<sys/stat.h>
#include	<string.h>

#define	DOT	'.'
#ifndef NULL
#define	NULL	0
#endif
#define	SLASH	'/'
#define MAXPWD	256

extern char longpwd[];

static char cwdname[MAXPWD];
static int didpwd = FALSE;
static void pwd();
static void cwd();
static void rmslash();
extern void prc_buff();
extern void prs_buff();
extern int length();
extern int error();

static void cwd(dir)
register char *dir;
{
    register char *pcwd;
    register char *pdir;

    /* First remove extra /'s */

    rmslash(dir);

    /* Now remove any .'s */

    pdir = dir;
    while (*pdir) {		/* remove /./ by itself */
    	if ((*pdir == DOT) && (*(pdir + 1) == SLASH)) {
    	    movstr(pdir + 2, pdir);
    	    continue;
    	}
    	pdir++;
    	while ((*pdir) && (*pdir != SLASH))
    	    pdir++;
    	if (*pdir)
    	    pdir++;
    }
    if (pdir > dir && *(--pdir) == DOT && pdir > dir && *(--pdir) == SLASH)
    	*pdir = '\0';

    /* Remove extra /'s */

    rmslash(dir);

    /* Now that the dir is canonicalized, process it */

    if (*dir == DOT && *(dir + 1) == (char)0) {
    	return;
    }

    if (*dir == SLASH) {
    	/* Absolute path */

    	pcwd = cwdname;
    	didpwd = TRUE;
    } else {
    	/* Relative path */

    	if (didpwd == FALSE)
    	    pwd();		/* Get absolute pathname into cwdname[] */

    	pcwd = cwdname + length(cwdname) - 1;
    	if (pcwd != cwdname + 1) {
    	    *pcwd++ = SLASH;
    	}
    }
    while (*dir) {
    	if (*dir == DOT && 
    	  *(dir + 1) == DOT && 
    	  (*(dir + 2) == SLASH || *(dir + 2) == (char)0)) {
    	    /* Parent directory, so backup one */

    	    if ( pcwd > cwdname + 2 )
    	    	--pcwd;
    	    while (*(--pcwd) != SLASH)
    	    	;
    	    pcwd++;
    	    dir += 2;
    	    if (*dir == SLASH) {
    	    	dir++;
    	    }
    	    continue;
    	}
    	*pcwd++ = *dir++;
    	while ((*dir) && (*dir != SLASH))
    	    *pcwd++ = *dir++;
    	if (*dir)
    	    *pcwd++ = *dir++;
    }
    *pcwd = '\0';

    --pcwd;
    if (pcwd > cwdname && *pcwd == SLASH) {
    	/* Remove trailing / */
    	*pcwd = '\0';
    }
    return;
}


/*
 *	Print the current working directory.
 */

void cwdprint()
{
    if (didpwd == FALSE)
    	pwd();

    prs_buff(cwdname);
    prc_buff(NL);
    return;
}


/*
 *	This routine will remove repeated slashes from string.
 */

static void rmslash(string)
char *string;
{
    register char *pstring;

    pstring = string;
    while (*pstring) {
    	if (*pstring == SLASH && *(pstring + 1) == SLASH) {
    	    /* Remove repeated SLASH's */

    	    movstr(pstring + 1, pstring);
    	    continue;
    	}
    	pstring++;
    }

    --pstring;
    if (pstring > string && *pstring == SLASH) {
    	/* Remove trailing / */

    	*pstring = (char)0;
    }
    return;
}

#ifdef mpx
extern char *getcwd();

static void pwd()
{
    if (getcwd(cwdname, MAXPWD) == (char*)0)
    	error(dotstat);
}
#endif /* mpx */

#ifndef mpx
/*
 *	Find the current directory the hard way.
 */
#include	<dirent.h>

static char dotdots[] = 
"../../../../../../../../../../../../../../../../../../../../../../../..";

static void pwd()
{
    struct stat cdir;	/* current directory status */
    struct stat tdir;
    struct stat pdir;	/* parent directory status */
    DIR	 * pdfd;	/* parent directory stream */

    struct dirent *dir;
    char *dot = dotdots + sizeof(dotdots) -3;
    int index = sizeof(dotdots) -2;
    int cwdindex = MAXPWD -1;
    int i;

    cwdname[cwdindex] = 0;
    dotdots[index] = 0;

    if (stat(dot, &pdir) < 0) {
    	error(dotstat);
    }

    dotdots[index] = '.';

    for (; ; ) {
    	cdir = pdir;
    	if ((pdfd = opendir(dot)) == (DIR * )0) {

    	    	error(paropen);
    	    }
#ifdef mpx
    	if (fstat(pdfd->dd_fd, &pdir) < 0) {
#else
        /* this is only to make cc happy, we do not run this ls on Linux */
    	if (fstat(dirfd(pdfd), &pdir) < 0) {
#endif

    	    	closedir(pdfd);
    	    	error(parstat);
    	    }

    	if (cdir.st_dev == pdir.st_dev) {
    	    if (cdir.st_ino == pdir.st_ino) {

    	    	didpwd = TRUE;
    	    	closedir(pdfd);
    	    	if (cwdindex == (MAXPWD - 1))
    	    	    cwdname[--cwdindex] = SLASH;
    	    	movstr(&cwdname[cwdindex], cwdname);
    	    	return;
    	    }

    	    do
    	     {
    	    	if ((dir = readdir(pdfd)) == 0) {
    	    	    closedir(pdfd);
    	    	    error(parread);
    	    	}
    	    } while (dir->d_ino != cdir.st_ino);
    	}
    	else
    	 {
    	    char name[MAXPWD];

    	    movstr(dot, name);
    	    i = length(name) - 1;

    	    name[i++] = '/';

    	    tdir.st_dev = pdir.st_dev;
    	    do
    	     {
    	    	if ((dir = readdir(pdfd)) == 0) {
    	    	    closedir(pdfd);
    	    	    error(parread);
    	    	}
    	    	movstr(dir->d_name, &name[i]);
    	    	stat(name, &tdir);
    	    } while (tdir.st_ino != cdir.st_ino || tdir.st_dev != cdir.st_dev);
    	}
    	closedir(pdfd);

    	i = strlen(dir->d_name);

    	if (i > cwdindex - 1)
    	    error(longpwd);
    	else
    	 {
    	    cwdindex -= i;
    	    movstrn(dir->d_name, &cwdname[cwdindex], i);
    	    cwdname[--cwdindex] = SLASH;
    	}

    	dot -= 3;
    	if (dot < dotdots)
    	    error(longpwd);
    }
}
#endif /* mpx */


