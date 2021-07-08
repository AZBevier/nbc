/*~!rm.c*/
/* Name:  rm.c Part No.: _______-____r
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

#ident	"Make4MPX $Id: rm.c,v 1.2 2021/07/05 20:05:34 jbev Exp $"

/* $Log: rm.c,v $
 * Revision 1.2  2021/07/05 20:05:34  jbev
 * Fix warning erors *
 *
 * Revision 1.1  1995/03/14 03:07:55  jbev
 * Initial revision
 *
 */

/*
 * rm [-fir] file ...
 */

#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <limits.h>

#ifndef mpx
#ifndef _NFILE
#define _NFILE	20
#endif
#ifndef DIRBUF
#define DIRBUF	2047
#endif
#ifndef MAXNAMLEN
#define MAXNAMLEN	512
#endif
#endif

#define	DIRECTORY	((buffer.st_mode&S_IFMT) == S_IFDIR)
#define	FAIL		-1
#define MAXFILES        _NFILE - 2	/* Maximum number of open files */
#define	MAXLEN		DIRBUF-24  	/* Name length (1024) is limited */
    					/* stat(2).  DIRBUF (1048) is defined */
    					/* in dirent.h as the max path length */
#define	NAMESIZE	MAXNAMLEN + 1	/* "/" + (file name size) */

#define TRUE		1
#define	WRITE		02
static int errcode;
void exit();
static int interactive, recursive, silent; /* flags for command line options */
void free();
void *malloc();
void perror();
char *strcpy();
int getopt();
int stat();
int access();
int isatty();
int rmdir();
int unlink();

static void rm();
static void undir();
static int yes();
static int mypath();

int main(argc, argv)
int argc;
char *argv[];
{
    extern int optind;
    int errflg = 0;
    int c;

    while ((c = getopt(argc, argv, "FfRrIi")) != EOF)
    	switch (c) {
    	case 'F':
    	case 'f':
    	    silent = TRUE;
    	    break;
    	case 'I':
    	case 'i':
    	    interactive = TRUE;
    	    break;
    	case 'R':
    	case 'r':
    	    recursive = TRUE;
    	    break;
    	case '?':
    	    errflg = 1;
    	    break;
    	}

    /* 
     * For BSD compatibility allow '-' to delimit the end 
     * of options.
     */
    if (optind < argc && !strcmp(argv[optind], "-"))
    	optind++;

    argc -= optind;
    argv = &argv[optind];

    if (argc < 1 || errflg) {
    	(void)fprintf(stderr, "usage: rm [-fir] file ...\n");
    	exit(2);
    }

    while (argc-- > 0) {
#ifdef LATER
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
#endif
    	rm (*argv);
    	argv++;
    }

    exit(errcode ? 2 : 0);
    /* NOTREACHED */
}


static void
rm(path)
char *path;
{
    struct stat buffer;
    /* 
     * Check file to see if it exists.
     */
    if (stat(path, &buffer) == FAIL) {
    	if (!silent) {
    	    perror(path);
    	    ++errcode;
    	}
    	return;
    }

    /*
     * If it's a directory, remove its contents.
     */
    if (DIRECTORY) {
    	undir(path, buffer.st_dev, buffer.st_ino);
    	return;
    }

    /*
     * If interactive, ask for acknowledgement.
     */
    if (interactive) {
    	printf("rm: remove  %s: (y/n)? ", path);
    	if (!yes())
    	    return;
    } else if (!silent) {
    	/* 
    	 * If not silent, and stdin is a terminal, and there's
    	 * no write access, ask for permission.
    	 */
    	if (access(path, WRITE) == FAIL && 
    	  isatty(fileno(stdin))) {
    	    printf("rm: %s: %o mode ? ", path, buffer.st_mode & 0777);
    	    /*
    	     * If permission isn't given, skip the file.
    	     */
    	    if (!yes())
    	    	return;
    	}
    }

    /*
     * If the unlink fails, inform the user if interactive or not silent.
     */
    if (unlink(path) == FAIL && (!silent || interactive)) {
    	fprintf(stderr, "rm: %s not removed.\n", path);
    	perror("");
    	++errcode;
    }
}


static void
undir(path, dev, ino)
char *path;
dev_t	dev;
ino_t	ino;
{
    char *newpath;
    DIR	 *name;
    struct dirent *direct;

    /*
     * If "-r" wasn't specified, trying to remove directories
     * is an error.
     */
    if (!recursive) {
    	fprintf(stderr, "rm: %s directory\n", path);
    	++errcode;
    	return;
    }

    /*
     * If interactive and this file isn't in the path of the
     * current working directory, ask for acknowledgement.
     */
    if (interactive && !mypath(dev, ino)) {
    	printf("rm: directory %s: ? ", path);
    	/*
    	 * If the answer is no, skip the directory.
    	 */
    	if (!yes())
    	    return;
    }

    /*
     * Open the directory for reading.
     */
    if ((name = opendir(path)) == (DIR * )NULL) {
    	fprintf(stderr, "rm: cannot open %s\n", path);
    	perror("");
    	exit(2);
    }

    /*
     * Read every directory entry.
     */
    while ((direct = readdir(name)) != (struct dirent *)NULL) {
    	/*
    	 * Ignore "." and ".." entries.
    	 */
    	if (!strcmp(direct->d_name, ".")
    	   || !strcmp(direct->d_name, ".."))
    	    continue;
    	/*
    	 * Try to remove the file.
    	 */
    	newpath = (char *)malloc((strlen(path) + NAMESIZE + 1));

    	if (newpath == (char *)NULL) {
    	    fprintf(stderr, "rm: Insufficient memory.\n");
    	    perror("");
    	    exit(1);
    	}

    	/*
    	 * Limit the pathname length so that a clear error message
    	 * can be provided.
    	 */
    	if (strlen(path) + strlen(direct->d_name) + 2 >= (size_t)MAXLEN) {
    	    fprintf(stderr, "rm: Path too long (%d/%d).\n",
    	      strlen(path) + strlen(direct->d_name) + 1, MAXLEN);
    	    exit(2);
    	}

    	sprintf(newpath, "%s/%s", path, direct->d_name);

    	/*
    	 * If a spare file descriptor is available, just call the
    	 * "rm" function with the file name; otherwise close the
    	 * directory and reopen it when the child is removed.
    	 */
#ifdef mpx
    	if (name->dd_fd >= MAXFILES) {
#else
        /* this is only to make cc happy, we do not run this ls on Linux */
        if (dirfd(name) >= MAXFILES) {
#endif
    	    closedir(name);
    	    rm(newpath);
    	    if ((name = opendir(path)) == (DIR * )NULL) {
    	    	fprintf(stderr, "rm: cannot open %s\n", path);
    	    	perror("");
    	    	exit(2);
    	    }
    	} else
    	    rm(newpath);

    	free(newpath);
    }

    /*
     * Close the directory we just finished reading.
     */
    closedir(name);

    /*
     * The contents of the directory have been removed.  If the
     * directory itself is in the path of the current working
     * directory, don't try to remove it.
     * When the directory itself is the current working directory, mypath()
     * has a return code == 2.
     */
    switch (mypath(dev, ino)) {
    case 2:
    	fprintf(stderr, "rm: Can't remove directory in my path\n%s\t\n",
    	  path);
    	++errcode;
    	return;
    case 1:
    	return;
    case 0:
    	break;
    }

    /*
     * If interactive, ask for acknowledgement.
     */
    if (interactive) {
    	printf("rm: remove  %s: (y/n)? ", path);
    	if (!yes())
    	    return;
    }
    if (rmdir(path) == FAIL) {
    	fprintf(stderr, "rm: Unable to remove directory\n");
    	perror("");
    	++errcode;
    }
}


static int 
yes()
{
    int i, b;

    i = b = getchar();
    while (b != '\n' && b != '\0' && b != EOF)
    	b = getchar();
    return(i == 'y' || i == 'Y');
}


static int 
mypath(dev, ino)
dev_t	dev;
ino_t	ino;
{
    struct stat buffer;
    dev_t	lastdev = (dev_t) - 1;
    ino_t	lastino = (ino_t) - 1;
    char *path;
    int i, j;

    for (i = 1; ; i++) {
    	/*
    	 * Starting from ".", walk toward the root, looking at
    	 * each directory along the way.
    	 */
    	path = (char *)malloc((3 * (uint)i));

    	if (path == (char *)NULL) {
    	    fprintf(stderr, "rm: Insufficient memory.\n");
    	    perror("");
    	    exit(1);
    	}

    	strcpy(path, ".");
    	for (j = 1; j < i; j++) {
    	    if (j == 1)
    	    	strcpy(path, "..");
    	    else
    	    	strcat(path, "/..");
        }
    	stat(path, &buffer);
    	/*
    	 * If we find a match, the directory (dev, ino) passed to mypath()
    	 * is an ancestor of ours. Indicated by return 1;
    	 *
    	 * If (i == 1) the directory (dev, ino) passed to mypath() is our
    	 * current working directory. Indicated by return 2;
    	 * 
    	 */
    	if ((buffer.st_dev == dev) && (buffer.st_ino == ino)) {
    	    if (i == 1)
    	    	return 2;
    	    else
    	    	return 1;
        }
    	/*
    	 * If we reach the root without a match, the given
    	 * directory is not in our path.
    	 */
    	if (buffer.st_dev == lastdev && buffer.st_ino == lastino)
    	    return 0;

    	/*
    	 * Save the current dev and ino, and loop again to go
    	 * back another level.
    	 */
    	lastdev = buffer.st_dev;
    	lastino = buffer.st_ino;
    	free(path);
    }
}

