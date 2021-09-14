/*~!conprint.c*/
/* Name:  conprint.c Part No.: _______-____r
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

#ident	"@(#)nbclib:conprint.c	1.1"

#ifndef FIX_032894
static char msg[82];
#else
static char msg[80];
#endif
static int tcp[3];

conprint(p)
char *p;
{
  int reg[8];
#ifndef FIX_032894
  int i;
  char *op = &msg[2];
#endif

  msg[0] = '\r';
  msg[1] = '\n';
#ifdef FIX_032894
  strcpy(&msg[2],p);
  tcp[0] = (strlen(msg) << 24) | (int)msg;
#else
  for (i=0; i<80; i++) {
    if (*p == '\0')break;
    *op++ = *p++;
  }
  tcp[0] = ((i+2) << 24) | (int)msg;
#endif
  tcp[1] = 0;
  tcp[2] = 0x40000000;
  reg[1] = (int)tcp;
  mpxsvc (0x103f, reg, reg);
}
