/*~!fopen.c*/
/* Name:  fopen.c Part No.: _______-____r
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

#ident	"@(#)nbclib:xx.c	1.1"

#include "stdio.h"
#include <fcntl.h>

extern int open(), fclose();
extern long lseek();
extern FILE *_findiop(), *_endopen();

FILE *
fopen(file, mode)
char	*file, *mode;
{
	return (_endopen(file, mode, _findiop()));
}

FILE *
freopen(file, mode, iop)
char	*file, *mode;
register FILE *iop;
{
	(void) fclose(iop); /* doesn't matter if this fails */
	return (_endopen(file, mode, iop));
}

static FILE *
_endopen(file, mode, iop)
char	*file, *mode;
register FILE *iop;
{
	register int	plus, fd;
	register int oflag = 0;
	int value;
	char * tmode = mode;

	if (!(iop != NULL && file != NULL && file[0] != '\0'))
		return (NULL);
	plus = strchr(mode, '+');
        while (value = *mode++)  {
	switch (value) {
	case 'w':
		oflag |= ((plus ? O_RDWR : O_WRONLY) | O_TRUNC | O_CREAT);
		break;
	case 'a':
		oflag |= ((plus ? O_RDWR : O_WRONLY) | O_APPEND | O_CREAT);
		break;
	case 'r':
		oflag |= (plus ? O_RDWR : O_RDONLY);
		break;
#ifdef mpx
	case 'u':
		oflag |= O_UNBLK;
		break;
	case 'b':
		oflag |= O_BIN;
		break;
	case '+':
		break;
#endif
	default:
		return (NULL);
	}
	}
	if ((fd = open(file, oflag, 0666)) < 0)
		return (NULL);
	iop->_cnt = 0;
	iop->_file = fd;
	iop->_flag = plus ? _IORW : (strchr(tmode, 'r')) ? _IOREAD : _IOWRT;
	if (oflag & O_UNBLK) iop->_flag |= _IOUBLK;
	if (oflag & O_BIN) iop->_flag |= _IOBIN;
	if (oflag & O_APPEND) {
		if (!plus)  {
			/* if update only mode, move file pointer to the end
			   of the file */
			if ((lseek(fd,0L,2)) < 0)  {
				return NULL;
			}
		}
	}
	_bufend(iop) = iop->_base = iop->_ptr = NULL;
	return (iop);
}
