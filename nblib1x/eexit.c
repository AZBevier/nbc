/*~!exit.c*/
/* Name:  exit.c Part No.: _______-____r
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

#ident	"@(#)nbclib:exit.c	1.0"

 /* This routine servies as a common exit routine for all C programs
  * that wish to use it.  Anyone wanting MPX aborts or using C runtime
  * I/O package must call exit when terminating.
  */

#include <stdio.h>
#define NULL 0

 exit(code)
    int    code;                    /* exit code */

 {
    char   *abort;                  /* abort code string address */
    int    i;

    _cleanup();                     /* call standard I/O cleanup routine */
    for (i=0;i<=_NFILE;i++)
       close(i);                    /* close all files */
    if (code == 0)                  /* return code zero? */
       abort = NULL;                /* yes, exit gracefully */
    else if (code <= 99) {
       abort = "CC  ";              /* no, set up abort string */
       *(abort+2) = '0' + ((code/10)%10); /* set up tens digit */
       *(abort+3) = '0' + (code%10); /* set up ones digit */
    } else {
       abort = (char *)(&code);     /* must be abort code pointer */
    }
    _exitmpx(abort);                /* exit or abort */
 }

_exit(code)
    int    code;                    /* exit code */

 {
    char   *abort;                  /* abort code string address */
    int    i;

     if (code == 0)                  /* return code zero? */
       abort = NULL;                /* yes, exit gracefully */
    else if (code <= 99) {
       abort = "CC  ";              /* no, set up abort string */
       *(abort+2) = '0' + ((code/10)%10); /* set up tens digit */
       *(abort+3) = '0' + (code%10); /* set up ones digit */
    } else {
       abort = (char *)(&code);     /* must be abort code pointer */
    }
    _exitmpx(abort);                /* exit or abort */
 }

_exitmpx(abort)
char *abort;
{
 int  i,reg[8],svc;
 union {    char  c[4];
            int   code; } status;

 for(i=0;i<8;i++) reg[i] = 0;

 if (abort) {
                  /* pointer to abort code, so exit with status */
   for(i=0;i<4;i++) status.c[i] = *abort++;
   reg[5] = status.code;
   svc = 0x1056;
 } else {
                  /* no pointer, so good status exit */
   svc = 0x1055;
 }
 mpxsvc(svc,reg,reg);

 return(0);       /* something wrong if it ever gets here! */
}
