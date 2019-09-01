/*~!stdio.h*/
/* Name:  stdio.h Part No.: _______-____r
 *
 * Copyright 1990 - J B Systems, Morrison, CO
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

#ifndef STDIO_H
#define STDIO_H

#ident	"@(#)nbinclude:stdio.h	1.0"

#ifndef _NFILE
#define _NFILE	20

#ifndef mpx
#define BUFSIZ	1024
#endif
#ifdef mpx
#define BUFSIZ	768
#endif

/* buffer size for multi-character output to unbuffered files */
#define _SBFSIZ 8

typedef struct {
	int	_cnt;
	unsigned char	*_ptr;
	unsigned char	*_base;
	short	_flag;		/* expanded to short for mpx */
	char	_file;
} FILE;

/*
 * _IOLBF means that a file's output will be buffered line by line
 * In addition to being flags, _IONBF, _IOLBF and _IOFBF are possible
 * values for "type" in setvbuf.
 */
#define _IOFBF		0000
#define _IOREAD		0001
#define _IOWRT		0002
#define _IONBF		0004
#define _IOMYBUF	0010
#define _IOEOF		0020
#define _IOERR		0040
#define _IOLBF		0100
#define _IORW		0200
#ifdef mpx
#define _IOUBLK		0400	/* unblocked read requested */
#define _IOBIN		01000	/* binary mode requested */
#endif

#ifndef NULL
#define NULL		0
#endif
#ifndef EOF
#define EOF		(-1)
#endif
#ifndef EOM
#define EOM		(-2)
#endif

#define stdin		(&_iob[0])
#define stdout		(&_iob[1])
#define stderr		(&_iob[2])

#define _bufend(p)	_bufendtab[(p)->_file]
#define _bufsiz(p)	(_bufend(p) - (p)->_base)

#ifndef lint
#define getc(p)		(--(p)->_cnt < 0 ? _filbuf(p) : (int) *(p)->_ptr++)
#define putc(x, p)	(--(p)->_cnt < 0 ? \
			_flsbuf((unsigned char) (x), (p)) : \
			(int) (*(p)->_ptr++ = (unsigned char) (x)))
#define getchar()	getc(stdin)
#define putchar(x)	putc((x), stdout)
#define clearerr(p)	((void) ((p)->_flag &= ~(_IOERR | _IOEOF)))
#define feof(p)		((p)->_flag & _IOEOF)
#define ferror(p)	((p)->_flag & _IOERR)
#define fileno(p)	(p)->_file
#endif

extern FILE	_iob[_NFILE];
extern FILE	*fopen(), *fdopen(), *freopen(), *tmpfile();
extern long	ftell();
extern void	rewind(), setbuf();
extern char	*fgets(), *gets(), *tempnam(), *tmpnam();
extern int	fclose(), fflush(), fread(), fwrite(), fseek(), fgetc(),
		getw(), printf(), fprintf(), sprintf(),
		vprintf(), vfprintf(), vsprintf(), fputc(), putw(),
		puts(), fputs(), scanf(), fscanf(), sscanf(),
		setvbuf(), ungetc();
extern unsigned char *_bufendtab[];

#define L_ctermid	9
#define L_cuserid	9
#define P_tmpdir	"/system/tmp/"
#define L_tmpnam	(sizeof(P_tmpdir) + 15)
#endif
#ifndef _MYID
extern struct _myidbl {
  int _taskno;
  char _lm [8];
  char _on [8];
  char _pn [8];
  char _cd [8];
  short _dummy;
  short _key;
  int _flags;
}
_myid;
#endif
#define _MYID struct _myidbl

#endif
