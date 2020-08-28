/*
 * obd.c
 *
 * This program uncompresses MPX compressed files and
 * dumps the object records in a readable form.
 * input - stdin or specified file name
 * output - stdout
 */

#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#ifdef i386
#include <stdlib.h>
#include <unistd.h>
#endif
void exit();
int getloi();
void putloi();
int rbl();
int plredf();
int bfredf();
int rmread();
int rmclose();
int rmopen();

int binary = 1;
int dounix;	/* set if doing unix object */
int first;	/* set after 1st time */
int ifd;	/* input file number */

int main (argc, argv)
int	argc;
char *	argv[];
{
    unsigned char s [BUFSIZ];
    int i;

    if (argc == 1) {	/* no file given, use stdin */
    	ifd = fileno(stdin);
    } else {
#ifdef mpx
    	if((ifd = open(*++argv, O_RDWR | O_UNBLK, 0666)) < 0) {
    	    fprintf(stderr, "file %s not found\n", *argv);
    	    exit (1);
    	}
#else
    	if((ifd = open(*++argv, O_RDWR)) < 0) {
    	    fprintf(stderr, "file %s not found\n", *argv);
    	    exit (1);
    	}
#endif
    }

    while (1) {
    	memset (s, '\0', BUFSIZ);
    	if ((i = rbl(s, (int)BUFSIZ)) <= 0) exit(0);
    	s [i] = '\0';
    	putloi (s, i);
    }
}
		
/* get a line of input. */

int getloi ( s, lim )                    /*  right from the book.  */
unsigned char s [];
int lim;
{
    int c, i, j;

#ifdef OLD_WAY_TOO
    j = rmread(fileno(stdin), s);
#else
    j = rmread(ifd, s);
#endif
    if (j <= 0) return (0);
    if (!binary) {
    	s[j] = '\n';
	for(i=0; --lim > 0 && i < j; ) {
    	  c = s[i];
    
	  s[i++] = c;
	  if ((*s != 0xbf) && (*s != 0x9f)) {
	    if (c == '\n') {
		if ((s[i-1] == '\n') && (i > 1)) {
			while ((s[i-2] == ' ') && (i > 1)) --i;
				s[i-1] = '\n';
		}
		s [ i ] = '\0';
		return (i);
	    }
          }
	}
    	return (i);
    }
    return (j);
}

/*
 **  output line of text from the source
 */
void putloi(s, cnt)
unsigned char *s;
int	cnt;
{
    int k;
    int seq;
    int bc = s[1];
    int type, objcnt, repeat, bound;
    int exttype, offset;

/*    if(*s == 0xdf)printf("**last record\n"); */
    seq = s[4] << 8 | s[5];
    printf("**record %x cnt %d\n", seq, bc);
    offset = 6;
doit:
    if(offset >= bc + 6)return;
    type = (s[offset] >> 4) & 0x0f;	/* get object record type */
    objcnt = s[offset] & 0x0f;		/* get object record count */
    if (objcnt == 0)objcnt = 16;	/* zero cnt means 16 */

    switch (type) {
    	case 0:			/* absolute data */
    	    printf("abs data cnt = %d data = ", objcnt);
    	    for (k = 0; k < objcnt; k++) {
    		if (k > 0 && (k % 4 == 0))printf(" ");
    		printf("%.2x", s[k + offset + 1]);
    	    }
    	    if (!first) {
    		first = 1;	/* we been here */
    		type = 0;
    		for (k = 0; k < 4; k++) {
    		    type |= (s[k+offset+1] << ((3-k)*8));
    		}
    		if (type == 0x2243223a)
    		    dounix = 1;		/* doing c object */
    	    }
    	    printf("\n");
    	    offset += (objcnt + 1);
    	    break;
    	case 1:			/* program origin */
    	    printf("%s program origin addr = ",
    	      (s[offset + 1] & 0x80) ? "rel" : "abs");
    	    s[offset + 1] &= 0x7f;	/* turn off rel bit */
    	    for (k = 0; k < objcnt; k++) {
    		printf("%.2x", s[k + offset + 1]);
    	    }
    	    printf("\n");
    	    offset += (objcnt + 1);
    	    break;
    	case 2:			/* absolute data repeat */
#ifdef OLD_JUNK
printf("DUMP abs data repeat cnt = %d\n", objcnt);
for (k = 0; k < objcnt + 1; k++) {
    if (k > 0 && (k % 20 == 0)) printf("\n");
    printf("%.2x ", s[offset + k]);
}
printf("\n");
#endif
    	    repeat = s[offset + 1];
    	    if (repeat == 0)repeat = 1;
    	    printf("abs data repeat cnt = %d\n", repeat);
    	    for (k = 0; k < objcnt - 1; k++) {
    		printf("%.2x ", s[k + offset + 2]);
    	    }
    	    printf("\n");
    	    offset += (objcnt + 1);
    	    break;
    	case 3:			/* transfer address */
#ifdef OLD_JUNK
printf("DUMP transfer address cnt = %d\n", objcnt);
for (k = 0; k < objcnt + 1; k++) {
    if (k > 0 && (k % 20 == 0)) printf("\n");
    printf("%.2x ", s[offset + k]);
}
printf("\n");
#endif
    	    printf("transfer address cnt = %d addr = ", objcnt);
    	    s[offset + 1] &= 0x7f;	/* turn off rel bit */
    	    for (k = 0; k < objcnt; k++) {
    		printf("%.2x", s[k + offset + 1]);
    	    }
    	    printf("\n");
    	    offset += (objcnt + 1);
    	    break;
    	case 4:			/* relocatable data */
    	    printf("rel data cnt = %d data = ", objcnt);
    	    for (k = 0; k < objcnt; k++) {
    		if (k > 0 && (k % 4 == 0))printf(" ");
    		printf("%.2x", s[k + offset + 1]);
    	    }
    	    printf("\n");
    	    offset += (objcnt + 1);
    	    break;
    	case 5:			/* program name */
#ifdef OLD_WAY
    	    bound = s[offset + 1 + objcnt - 3] << 16 |
    		s[offset + 1 + objcnt - 2] << 8 |
    		s[offset + 1 + objcnt - 1];
#else
    	    bound = s[offset + 1 + objcnt - 1];
    	    repeat = s[offset + 1 + objcnt - 2];
    	    /* see if 'C' object */
    	    if (repeat == 0x04)
    		dounix = 1;		/* doing c object */
#endif
    	    printf("program name = ");
    	    for (k = 0; k < objcnt - 3; k++) {
    		printf("%c", s[k + offset + 1]);
    	    }
#ifdef OLD_WAY
    	    printf(" bound = %x\n", bound);
#else
    	    printf(" bound = %x obj type = %x\n", bound, repeat);
#endif
    	    offset += (objcnt + 1);
    	    break;
    	case 6:			/* relocatable data repeat */
    	    repeat = s[offset + 1];
    	    if (repeat == 0)repeat = 1;
    	    printf("rel data repeat cnt = %d\n", repeat);
    	    for (k = 0; k < objcnt - 1; k++) {
    		printf("%.2x ", s[k + offset + 2]);
    	    }
    	    printf("\n");
    	    offset += (objcnt + 1);
    	    break;
    	case 7:			/* external definition */
    	    printf("%s external def name = ",
    	      (s[offset + 1 + objcnt - 3] & 0x80) ? "rel" : "abs");
    	    s[offset + 1 + objcnt - 3] &= 0x7f;	/* turn off rel bit */
    	    bound = s[offset + 1 + objcnt - 3] << 16 |
    		s[offset + 1 + objcnt - 2] << 8 |
    		s[offset + 1 + objcnt - 1];
    	    for (k = 0; k < objcnt - 3; k++) {
    		printf("%c", s[k + offset + 1]);
    	    }
    	    printf(" address = %x\n", bound);
    	    offset += (objcnt + 1);
    	    break;
    	case 8:			/* forward reference */
    	    printf("%s forward reference addr = ",
    	      (s[offset + 1] & 0x80) ? "rel" : "abs");
    	    s[offset + 1] &= 0x7f;	/* turn off rel bit */
    	    for (k = 0; k < objcnt - 3; k++) {
    		printf("%.2x", s[k + offset + 1]);
    	    }
    	    printf(" sb addr = ");
    	    for (k = 3; k < objcnt; k++) {
    		printf("%.2x", s[k + offset + 1]);
    	    }
    	    printf("\n");
    	    offset += (objcnt + 1);
    	    break;
    	case 9:			/* external reference */
    	    printf("%s external ref name = ",
    	      (s[offset + 1 + objcnt - 3] & 0x80) ? "rel" : "abs");
    	    s[offset + 1 + objcnt - 3] &= 0x7f;	/* turn off rel bit */
    	    bound = s[offset + 1 + objcnt - 3] << 16 |
    		s[offset + 1 + objcnt - 2] << 8 |
    		s[offset + 1 + objcnt - 1];
    	    for (k = 0; k < objcnt - 3; k++) {
    		printf("%c", s[k + offset + 1]);
    	    }
    	    printf(" sb addr = %x\n", bound);
    	    offset += (objcnt + 1);
    	    break;
    	case 10:		/* common definition */
    	    printf("common def name = ");
    	    /* get common block number */
    	    repeat = s[offset + 1 + objcnt - 3];
    	    /* get common size */
    	    bound = s[offset + 1 + objcnt - 2] << 8 |
    		s[offset + 1 + objcnt - 1];
    	    for (k = 0; k < objcnt - 3; k++) {
    		printf("%c", s[k + offset + 1]);
    	    }
    	    printf(" block = %d size = %x\n", repeat, bound);
    	    offset += (objcnt + 1);
    	    break;
    	case 11:		/* common reference */
    	    /* get common block number */
    	    repeat = s[offset + 1];
    	    printf("common ref block = %d data = ", repeat);
    	    for (k = 0; k < objcnt - 1; k++) {
    		if (k == 4 || k == 8 || k == 12)printf(" ");
    		printf("%.2x", s[k + offset + 2]);
    	    }
    	    printf("\n");
    	    offset += (objcnt + 1);
    	    break;
    	case 12:		/* datapool reference */
    	    printf("datapool ref name = ");
    	    for (k = 0; k < objcnt - 4; k++) {
    		printf("%c", s[k + offset + 1]);
    	    }
    	    printf(" addr = ");
    	    for (k = 0; k < 4; k++) {
    		printf("%.2x", s[k + offset + objcnt + 1 - 4]);
    	    }
    	    printf("\n");
    	    offset += (objcnt + 1);
    	    break;
    	case 13:		/* escape to extended functions */
    	    objcnt = s[offset] & 0x0f;		/* get sub type */
    	    exttype = s[offset + 1];		/* get ext type */

    	    switch (exttype) {
    		case 0:			/* undefined */
    	    for (k = 0; k < s[offset+2]; k++) {
    		if (k > 0 && (k % 20 == 0)) printf("\n");
    		printf("%.2x ", s[offset + k]);
    	    }
    	    printf("\n");
    		    offset += s[offset + 2];
    		    break;
    		case 1:			/* section definition */
    		    printf("section def bound = %x num = %d size = ",
    		      s[offset + 3], s[offset + 4]);
    		    for (k = 0; k < 3; k++) {
    			printf("%.2x", s[offset + 5 + k]);
    		    }
    		    printf(" name = ");
    		    for (k = 0; k < 8; k++) {
    			printf("%c", s[offset + 8 + k]);
    		    }
    		    printf("\n");
    		    offset += s[offset + 2];
    		    break;
    		case 2:			/* section origin */
    		    printf("section origin bound = %x num = %d origin = ",
    		      s[offset + 3], s[offset + 4]);
    		    for (k = 0; k < 3; k++) {
    			printf("%.2x", s[offset + 5 + k]);
    		    }
    		    printf("\n");
    		    offset += s[offset + 2];
    		    break;
    		case 3:			/* section relocatable ref */
    		    repeat = s[offset + 5];
    		    if (repeat == 0)repeat = 1;	/* 0 is 1 */
    		    printf("section rel ref %s rep cnt = %d data = ",
    		      s[offset + 4] == 0 ? "DSECT" : s[offset + 4] == 1 ?
    		      "CSECT" : "UNKNOWN", repeat);
    		    for (k = 0; k < (s[offset + 2] - 6); k++) {
    			if (k > 0 && (k % 4 == 0)) printf(" ");
    			if (k > 0 && (k % 20 == 0)) printf("\n");
    			printf("%.2x", s[offset + 6 + k]);
    		    }
    		    if (k % 20 != 0)printf("\n");
    		    offset += s[offset + 2];
    		    break;
    		case 4:			/* section transfer address */
    		    printf("section transfer address num = %d address = ",
    		      s[offset + 4]);
    		    for (k = 0; k < 3; k++) {
    			printf("%.2x", s[offset + 5 + k]);
    		    }
    		    printf("\n");
    		    offset += s[offset + 2];
    		    break;
    		case 5:			/* section external def */
    		    printf("section ext def num = %d address = ",
    		      s[offset + 4]);
    		    for (k = 0; k < 3; k++) {
    			printf("%.2x", s[offset + 5 + k]);
    		    }
    		    printf(" name = ");
    		    for (k = 0; k < s[offset + 2] - 8; k++) {
    			printf("%c", s[offset + 8 + k]);
    		    }
    		    printf("\n");
    		    offset += s[offset + 2];
    		    break;
    		case 6:			/* section external ref */
    		    printf("section ext ref num = %d sb address = ",
    		      s[offset + 4]);
    		    for (k = 0; k < 3; k++) {
    			printf("%.2x", s[offset + 5 + k]);
    		    }
    		    printf(" name = ");
    		    for (k = 0; k < s[offset + 2] - 8; k++) {
    			printf("%c", s[offset + 8 + k]);
    		    }
    		    printf("\n");
    		    offset += s[offset + 2];
    		    break;
    		case 7:			/* section forward ref */
    		    printf("sect forward ref num = %d address = ",
    		      s[offset + 4]);
    		    for (k = 0; k < 3; k++) {
    			printf("%.2x", s[offset + 5 + k]);
    		    }
    		    printf(" num = %d sb addr = ", s[offset + 8]);
    		    for (k = 0; k < 3; k++) {
    			printf("%.2x", s[offset + 9 + k]);
    		    }
    		    printf("\n");
    		    offset += s[offset + 2];
    		    break;
    		case 8:			/* large common def */
    		    printf("large com def num = %d sb size = ",
    		      s[offset + 4]);
    		    for (k = 0; k < 3; k++) {
    			printf("%.2x", s[offset + 5 + k]);
    		    }
    		    printf(" name = ");
    		    for (k = 0; k < s[offset + 2] - 8; k++) {
    			printf("%c", s[offset + 8 + k]);
    		    }
    		    printf("\n");
    		    offset += s[offset + 2];
    		    break;
    		case 9:			/* large common origin */
    		    printf("large com origin num = %d sb origin = ",
    		      s[offset + 4]);
    		    for (k = 0; k < 3; k++) {
    			printf("%.2x", s[offset + 5 + k]);
    		    }
    		    printf("\n");
    		    offset += s[offset + 2];
    		    break;
    		case 10:		/* large common ref */
    		    repeat = s[offset + 5];
    		    if (repeat == 0)repeat = 1;	/* 0 is 1 */
    		    printf("large com ref num = %d rep cnt = %d data = ",
    		      s[offset + 4], repeat);
    		    for (k = 0; k < (s[offset + 2] - 6); k++) {
    			if (k > 0 && (k % 4 == 0)) printf(" ");
    			if (k > 0 && (k % 20 == 0)) printf("\n");
    			printf("%.2x", s[offset + 6 + k]);
    		    }
    		    if (k % 20 != 0)printf("\n");
    		    offset += s[offset + 2];
    		    break;
    		case 11:		/* debugger information */
    		    printf("debugger info: flg: %d len: %d %s %s type: ",
    		      objcnt, s[offset + 2], s[offset + 3] & 2 ? "abs" : "rel",
    		      s[offset + 3] & 1 ? "CSECT" : "DSECT");
    		    switch (s[offset + 4]) {
    			case 0: printf("int * 1"); break;
    			case 1: printf("int * 2"); break;
    			case 2: printf("int * 4"); break;
    			case 3: printf("int * 8"); break;
    			case 4: printf("real * 4"); break;
    			case 5: printf("real * 8"); break;
    			case 6: printf("complex * 8"); break;
    			case 7: printf("complex * 16"); break;
    			case 8: printf("bit logical"); break;
    			case 9: printf("logical * 1"); break;
    			case 10: printf("logical * 4"); break;
    			case 11: printf("char * n"); break;
    			case 12: printf("type 12"); break;
    			case 13: printf("type 13"); break;
    			case 14: printf("statement label"); break;
    			case 15: printf("proceedure"); break;
    			default: printf("unknown type %d", s[offset + 4]);
    			    break;
    		    }
    		    bound = 0;
    		    for (k = 0; k < 3; k++) {
    			bound = (bound << 8) | (s[offset + 5 + k]);
    		    }
    		    printf("\n* %s address: %x bitnum: %x",
    		      s[offset + 3] & 1 ? "csect" : "dsect", 
    		      bound >> 3, bound & 7);
    		    printf(" size: %d symbol: ",
    		      s[offset + 8] << 8 | s[offset + 9]);
    		    /* now print the 8 chars of the symbol */
    		    for (k = 0; k < s[offset + 2] - 10; k++) {
    			printf("%c", s[offset + 10 + k]);
    		    }
    		    /* see if common */
    		    if (s[offset + 2] == 26) {
    			printf(" common: ");
    			for (k = 0; k < 8; k++) {
    			    printf("%c", s[offset + 18 + k]);
    			}
    		    }
    		    printf("\n");
    		    offset += s[offset + 2];
    		    break;
    		case 12:		/* object creation information */
    		    /* object creation date/time */
    		    if (objcnt == 0) {
    			printf("object creation: ");
    			for (k = 0; k < 8; k++) {
    			    printf("%c", s[offset + 4 + k]);
    			}
    			printf(" ");
    			for (k = 0; k < 8; k++) {
    			    printf("%c", s[offset + 12 + k]);
    			}
    			printf("\n");
    			offset += s[offset + 2];
    			break;
    		    }
    		    /* product id leader */
    		    if (objcnt == 1) {
    			printf("product id: ");
    			for (k = 0; k < s[offset + 2] - 4; k++) {
    			    printf("%c", s[offset + 4 + k]);
    			}
    			printf("\n");
    			offset += s[offset + 2];
    			break;
    		    }
    		    /* generating processor info */
    		    if (objcnt == 2) {
    			printf("generating processor info: opt wd1 = ");
    			for (k = 0; k < 4; k++) {
    			    printf("%.2x", s[offset + 4 + k]);
    			}
    			printf(" opt wd2 = ");
    			for (k = 0; k < 4; k++) {
    			    printf("%.2x", s[offset + 8 + k]);
    			}
#ifdef FUTURE
    			printf(" rev lev = ");
    			for (k = 0; k < 4; k++) {
    			    printf("%.2x", s[offset + 12 + k]);
    			}
#endif
    			printf("\nrrs cnt = ");
    			for (k = 0; k < 2; k++) {
    			    printf("%.2x", s[offset + 16 + k]);
    			}
    			printf(" incl cnt = ");
    			for (k = 0; k < 2; k++) {
    			    printf("%.2x", s[offset + 18 + k]);
    			}
/*    			printf("\n"); */
    			printf(" pathname: ");
    			for (k = 0; k < s[offset + 2] - 20; k++) {
    			    printf("%c", s[offset + 20 + k]);
    			}
    			printf("\n");
    			offset += s[offset + 2];
    			break;
    		    }
    		    /* required resources info */
    		    if (objcnt == 3) {
    			repeat = s[offset + 3];
    			printf("required resource info: %s lfc = ", 
    			  repeat & 1 ? "FORT incl file" : "req obj file");
    			for (k = 0; k < 3; k++) {
    			    printf("%c", s[offset + 5 + k]);
    			}
    			printf("\n");
    			repeat = s[offset + 10];
    			printf("* acc mode = ");
    			for (k = 0; k < 4; k++) {
    			    printf("%.2x", s[offset + 12 + k]);
    			}
    			printf(" opts = ");
    			for (k = 0; k < 4; k++) {
    			    printf("%.2x", s[offset + 16 + k]);
    			}
    			printf(" pathname: ");
#ifdef OLDWAY
    			for (k = 0; k < repeat; k++) {
    			    printf("%c", s[offset + 20 + k]);
    			}
#else
    			for (k = 0; k < s[offset + 2] - 20; k++) {
    			    printf("%c", s[offset + 20 + k]);
    			}
#endif
    			printf("\n");
#ifdef OLD_JUNK
printf("PNAM LEN %d PATH LEN %d\n", repeat, s[offset + 2] - 20);
#endif
    			offset += s[offset + 2];
    			break;
    		    }
    	    for (k = 0; k < s[offset+2]; k++) {
    		if (k > 0 && (k % 20 == 0)) printf("\n");
    		printf("%.2x ", s[offset + k]);
    	    }
    	    printf("\n");
    		    offset += s[offset + 2];
    		    break;
      		case 13:		/* multiple datapool ref */
    		    printf("multiple datapool ref sym =");
    		    for (k = 0; k < (s[offset + 2] - 12); k++) {
    			printf("%c ", s[offset + 4 + k]);
    		    }
    		    printf("\naddr = ");
    		    for (k = 0; k < 4; k++) {
    			printf("%.2x ", s[offset + 2] - 8 + k);
    		    }
    		    printf(" pool num = ");
    		    for (k = 0; k < 4; k++) {
    			printf("%.2x ", s[offset + 2] - 4 + k);
    		    }
    		    printf("\n");
    		    offset += s[offset + 2];
    		    break;
      		case 14:		/* new debugger information */
#ifdef NOT_NOW
    		    printf("new debugger info (hex dump)\n");
    		    for (k = 0; k < s[offset+2]; k++) {
    			if (k > 0 && (k % 20 == 0)) printf("\n");
    			printf("%.2x ", s[offset + k]);
    		    }
    		    printf("\n");
#endif
    		    printf("new debugger info: flags: %x type: ",
    		      s[offset + 3]);
    		if (dounix) {
    		    /* see if we have an enum */
    		    if (s[offset + 4] & 0x20) {
    			printf ("enum ");
    		    }
    		    /* see if stack variable */
    		    if (s[offset + 3] & 0x10) {
    			printf("stack ");
    		    }
    		    /* see if register variable */
    		    if (s[offset + 3] & 0x04) {
    			printf("register ");
    		    }
    		    /* see if pointer */
    		    if (s[offset + 3] & 0x20) {
    			int indcnt = s[offset + 5];
    			/* print number of indirections */
    			while (indcnt--)
    			    printf("*");
    		    }
    		    switch (s[offset + 4] & ~0x20) {
    			case 0: printf("char"); break;
    			case 1: printf("short"); break;
    			case 2: printf("int"); break;
    			case 3: printf("long"); break;
    			case 4: printf("float"); break;
    			case 5: printf("double"); break;
    			case 6:
    			    printf("struct ");
    			    for (k = 0; k < 8; k++) {
    				printf("%c", s[offset + 20 + k]);
    			    }
    			    break;
    			case 7:
    			    printf("union ");
    			    for (k = 0; k < 8; k++) {
    				printf("%c", s[offset + 20 + k]);
    			    }
    			    break;
    			case 8: printf("uchar"); break;
    			case 9: printf("ushort"); break;
    			case 10: printf("uint"); break;
    			case 11: printf("ulong"); break;
    			case 12: printf("enum"); break;
    			case 13: printf("struct def"); break;
    			case 14: printf("statement label"); break;
    			case 15: printf("entry point"); break;
    			case 16: printf("illegal"); break;
    			case 17: printf("CSECT load origin"); break;
    			case 18: printf("DSECT load origin"); break;
    			default: printf("unknown type %d", s[offset + 4]);
    			    break;
    		    }
    		} else {
    		    /* see if we have a parameter */
    		    if ((s[offset + 4] & 0x60) == 0x20) {
    			printf ("parameter ");
    		    }
    		    switch (s[offset + 4] & ~0x20) {
    			case 0: printf("int * 1"); break;
    			case 1: printf("int * 2"); break;
    			case 2: printf("int * 4"); break;
    			case 3: printf("int * 8"); break;
    			case 4: printf("real * 4"); break;
    			case 5: printf("real * 8"); break;
    			case 6: printf("complex * 8"); break;
    			case 7: printf("complex * 16"); break;
    			case 8: printf("bit logical"); break;
    			case 9: printf("logical * 1"); break;
    			case 10: printf("logical * 4"); break;
    			case 11: printf("char * n"); break;
    			case 12: printf("type 12"); break;
    			case 13: printf("type 13"); break;
    			case 14: printf("statement label"); break;
    			case 15: printf("proceedure"); break;
    			default: printf("unknown type %d", s[offset + 4]);
    			    break;
    		    }
    		}
    		    printf(" rsvd: %x size: %d\n",
    		      s[offset + 5], s[offset + 6] * 256 + s[offset + 7]);
    		    repeat = 0;
    		    for (k = 0; k < 4; k++) {
    			repeat = (repeat << 8) | s[offset + 8 + k];
    		    }
    		    printf("* %s address: %x, bitnum: %d symbol: ",
    		        s[offset + 3] & 1 ? "csect" : "dsect", 
    			repeat >> 3, repeat & 7);
    		    for (k = 0; k < 8; k++) {
    			printf("%c", s[offset + 12 + k]);
    		    }
    		    printf("\n");
    		    /* only look at ISC type if len is > 20 */
    		    if (s[offset + 2] <= 20) goto wedone;
    		    /* only look at ISC type if flags is zero */
    		    /* and not a parameter */
    		if (s[offset + 3] <= 1 && s[offset + 4] < 0x20) {
    		    /* do ISC record */
    		    printf("* ISC type: ");
    		    switch (s[offset + 20] & 0x7f) {
    			case 0: printf("no src"); break;
    			case 1: printf("declaration"); break;
    			case 2: printf("xeq statement"); break;
    			case 3: printf("cont line"); break;
    			case 4: printf("comment"); break;
    			case 5: printf("FORTRAN err"); break;
    			default:
    			    printf("undefined %x", s[offset + 20] & 0x7f);
    			    break;
    		    }
    		    printf(" caret %d\n", s[offset + 21]);
    		    /* only process source if caret is zero */
    		    if (s[offset + 21] != 0) goto wedone;
    		    if (s[offset + 20] & 0x80) {
    			/* uncompressed source */
    			int srccnt = s[offset + 22];
    			int blkcnt = s[offset + 23];

    			for (k = 0; k < blkcnt; k++) {
    			    printf(" ");	/* blanks */
    			}
    			for (k = 0; k < srccnt; k++) {
    			    printf("%c", s[offset + 24 + k]);	/* source */
    			}
    		    } else {
    			/* compressed source */
    			unsigned char chr;
    			int srccnt = s[offset + 22];
    			int blkcnt = s[offset + 23];
    			int j = 0;
    			int l = offset + 24;

    			for (k = 0; k < blkcnt; k++) {
    			    printf(" ");	/* blanks */
    			}
    			for (k = 0; k < srccnt; k++) {
    			    switch (j) {
    				case 0:
    				    chr = ((s[offset + l]) >> 2) & 0x3f + 32;
    				    j++;
    				    break;
    				case 1:
    				    chr = (((s[offset + l++] & 3) << 4) |
    				      ((s[offset + l] & 0xf0) >> 4) + 32);
    				    j++;
    				    break;
    				case 2:
    				    chr = (((s[offset + l++] & 0xf) << 2) |
    				      ((s[offset + l] & 0xc0) >> 6) + 32);
    				    j++;
    				    break;
    				case 3:
    				    chr = ((s[offset + l] & 0x3f) + 32);
    				    j = 0;
    				    break;
    			    }
    			    printf("%c", chr);	/* source */
    			}
    		    }
    		    printf("\n");
    		} else {	/* else handle Encore debug record */
    		    int srccnt;
    		    unsigned int srcval;
    		    unsigned int srcval2;
    		    int sv;		/* switch value */
    		    int xx = 20;	/* array info offset */

    		    /* First look for a parameter.  Flags will be zero. */
    		    /* Type will be >= 32 (0x20) */
    		    if (dounix) {
    			sv = s[offset + 3] & 0x48;
    		    } else {
    			sv = s[offset + 3];
    		    }
    		    switch (s[offset + 3]) {	/* switch on flags */
    			case 0x00:		/* parameter */
    			    switch (s[offset + 4] & 0x1f) {
    				case 0:		/* int * 1 */
    				case 9:		/* logical * 1 */
    				    /* wd 5 byte 0 has value */
    				    printf("* param value: 0x");
    				    printf ("%.2x", s[offset + 20]);
    				    printf ("\n");
    				    break;
    				case 1:		/* int * 2 */
    				    /* wd 5 bytes 0-1 has value */
    				    srcval = s[offset + 20] << 8
    				      | s[offset + 21];
    				    printf("* param value: 0x");
    				    printf ("%.4x", srcval);
    				    printf ("\n");
    				    break;
    				case 2:		/* int * 4 */
    				case 4:		/* real * 4 */
    				case 10:	/* logical * 4 */
    				    /* wd 5 bytes 0-3 has value */
    				    srcval = s[offset + 20] << 24
    				      | s[offset + 21] << 16
    				      | s[offset + 22] << 8
    				      | s[offset + 23];
    				    printf("* param value: 0x");
    				    printf ("%.8x", srcval);
    				    printf ("\n");
    				    break;
    				case 3:		/* int * 8 */
    				case 5:		/* real * 8 */
    				case 6:		/* complex * 8 */
    				    /* wd 5-6 bytes 0-3 has value */
    				    srcval = s[offset + 20] << 24
    				      | s[offset + 21] << 16
    				      | s[offset + 22] << 8
    				      | s[offset + 23];
    				    srcval2 = s[offset + 24] << 24
    				      | s[offset + 25] << 16
    				      | s[offset + 26] << 8
    				      | s[offset + 27];
    				    printf("* param value: 0x");
    				    printf ("%.8x %.8x", srcval, srcval2);
    				    printf ("\n");
    				    break;
    				case 7:		/* complex * 16 */
    				    /* wd 5-6 bytes 0-3 has value */
    				    srcval = s[offset + 20] << 24
    				      | s[offset + 21] << 16
    				      | s[offset + 22] << 8
    				      | s[offset + 23];
    				    srcval2 = s[offset + 24] << 24
    				      | s[offset + 25] << 16
    				      | s[offset + 26] << 8
    				      | s[offset + 27];
    				    printf("* param value: 0x");
    				    printf ("%.8x %.8x ", srcval, srcval2);
    				    /* wd 7-8 bytes 0-3 has value */
    				    srcval = s[offset + 28] << 24
    				      | s[offset + 29] << 16
    				      | s[offset + 30] << 8
    				      | s[offset + 31];
    				    srcval2 = s[offset + 32] << 24
    				      | s[offset + 33] << 16
    				      | s[offset + 34] << 8
    				      | s[offset + 35];
    				    printf ("%.8x %.8x", srcval, srcval2);
    				    printf ("\n");
    				    break;
    				case 8:		/* bit logical */
    				    /* wd 5 bit 0 has value */
    				    printf("* param value: ");
    				    printf ("%s\n", s[offset + 20] & 0x80 ?
    				      ".TRUE. (1)" : ".FALSE. (0)");
    				    break;
    				case 11:	/* char * n */
    				    /* size has array length */
    				    /* wds 5 - 8 has char values */
    				    srccnt = s[offset + 6] << 8 | s[offset + 7];
    				    printf("* param value (%d): ", srccnt);
    				    if (srccnt > 16) srccnt = 16;
    				    for (k = 0; k < srccnt; k ++) {
    					printf ("%c", s[offset + 20 + k]);
    				    }
    				    printf ("\n");
    				    break;
    				default:
    				    goto jumpit;
    			    }
    			    break;
    			case 0x04:		/* datapool */
    			    if (dounix) {
    				/* register variable, ignore */
    				break;
    			    } else {
    				/* print datapool name */
    				printf("* len = %d Dpool: ", s[offset + 2]);
    			    }
    			    for (k = 0; k < 8; k++) {
    				printf("%c", s[offset + 20 + k]);
    			    }
    			    printf("\n");
    			    break;
    			case 0x08:		/* common symbol */
    			    if (dounix) {
    				/* print struct/union ref name */
    				printf("* len = %d S/U ref: ", s[offset + 2]);
    			    } else {
    				/* print common name */
    				printf("* len = %d Common: ", s[offset + 2]);
    			    }
    			    for (k = 0; k < 8; k++) {
    				printf("%c", s[offset + 20 + k]);
    			    }
    			    printf("\n");
    			    break;
    			case 0x48:		/* array of structures */
    			    xx = 28;		/* account for struct name */
    			case 0x40:		/* array info present */
printf("* array dims: %d bnds: %d len: %d lbflags %x sbflags %x\n",
s[offset + xx + 0], s[offset + xx + 1], s[offset + xx + 4],
s[offset + xx + 2] << 8 | s[offset + xx + 3],
s[offset + xx + 6] << 8 | s[offset + xx + 7]);
printf("* wds: ");
for (k = 0; k < s[offset+xx+4] - 8; k++) {
  if (k > 0 && (k % 4 == 0)) {
   if ((k % 20 == 0)) printf("\n");
   else printf(" ");
  }
  printf("%.2x", s[offset + xx + 8 + k]);
}
printf("\n");
    			    break;
    			case 0x50:		/* array parameters */
printf("* array param dims: %d bnds: %d len: %d lbflags %x sbflags %x\n",
s[offset + 20], s[offset + 21], s[offset + 24],
s[offset + 22] << 8 | s[offset + 23],
s[offset + 26] << 8 | s[offset + 27]);
printf("* wds: ");
for (k = 0; k < s[offset+24] - 8; k++) {
  if (k > 0 && (k % 20 == 0)) printf("\n");
  printf("%.2x ", s[offset + 28 + k]);
}
printf("\n");
    			    break;
    			case 0x01:		/* CSECT */
    			case 0x02:		/* absolute address */
    			case 0x10:		/* parameter/stack variable */
    			case 0x20:		/* ext memory address/pointer */
printf("* unprocessed flags %x\n", s[offset+3]);
    			default:
jumpit:
    			    printf("* Encore record flags = %x\n",
    			      s[offset + 3]);
    		    printf("Encore debugger info (hex dump)\n");
    		    for (k = 0; k < s[offset+2]; k++) {
    			if (k > 0 && (k % 20 == 0)) printf("\n");
    			printf("%.2x ", s[offset + k]);
    		    }
    		    printf("\n");
    			    break;
    		    }
    		}
wedone:
    		    offset += s[offset + 2];
    		    break;
    		case 15:		/* undefined */
    		    for (k = 0; k < s[offset+2]; k++) {
    			if (k > 0 && (k % 20 == 0)) printf("\n");
    			printf("%.2x ", s[offset + k]);
    		    }
    		    printf("\n");
    		    offset += s[offset + 2];
    		    break;
    	    }
    	    break;
    	case 14:		/* common origin */
    	    /* get common block number */
    	    repeat = s[offset + 1];
    	    /* get common size */
    	    bound = s[offset + 2] << 8 |
    		s[offset + 3];
    	    printf("common origin block = %x origin = %x\n",
    	      repeat, bound);
    	    offset += (objcnt + 1);
    	    break;
    	case 15:		/* object termination */
    	    printf("program object termination\n");
    	    offset += (objcnt + 1);
    	    break;
    }
    goto doit;
}

unsigned char line [BUFSIZ];
int cmpop =0;
int cmpflg =0;
int bcnt = 0;
unsigned char *bptr = 0;
int recl = 0;

int rbl (buf, n)
unsigned char *buf;
int n;
{
  int count = 0;
  unsigned char *cp;
  int i;

  unsigned char *linadrs = line;

  if (!cmpop) {    /* see if we tested for compressed */
    cmpop = 1;     /* set comp tested flag */
    /* read in the first record */
    if ((recl = getloi(line, BUFSIZ)) == 0)return (0);	/* this means eof */
    linadrs = line;
    if (*linadrs == 0xbf || *linadrs == 0x9f) { /* is this file compressed */
      cmpflg = 1; /* set comp data flag */
      bcnt = linadrs[1];     /* set record count */
      bptr = &linadrs[6];      /* set data address */
    } else goto re00;
  }

  if (cmpflg) {      /* reading compressed data? */
    if (bcnt == 0) { /* any data left in buffer */
re18:
      /* read in a data record */
    if ((recl = getloi(line, BUFSIZ)) == 0)return (0);	/* this means eof */
      linadrs = line;
      if ((*linadrs & 0xdf) != 0x9f)    /* is this valid rec */
        return (EOF);         /* error if not */
      bcnt = linadrs[1];     /* set record count */
      bptr = &linadrs[6];      /* set data address */
    }
re20:
    /* see if any blanks */
    if (i = *bptr++) {       /* next buffer pointer */
      if (i == 0xff)goto re60;      /* if eol, get out */
      while (i--) {
        if(count < n) {
          *buf++ = ' ';       /* put blank in buffer */
          count++;
        }
      }
    }
      if (--bcnt <= 0)goto re18; /* read next record */

    if (i = *bptr++) {       /* next buffer pointer */
      while (i--) {
        if(count < n)
          *buf++ = *bptr;  /* put char in buffer */
          bcnt--;        /* decr count */
        bptr++;        /* next buffer pointer */
        count++;
      }
    }
      if (--bcnt <= 0)goto re18; /* read next record */
    goto re20;

re60:
    bcnt--;		/* decr count */
    if ((*--buf == ' ') && (count == 1)) {
      *buf = '\n';	/* put new line at eol */
      *++buf = '\0';    /* put new line at eol */
    } else {
      count++;
      *++buf = '\n';    /* put new line at eol */
      *++buf = '\0';    /* put new line at eol */
    }
/* printf("ret cnt = %ld\n", count); */
    return (count);

  } else {

    /* non compressed read here */

    /* read the next record */
    if ((recl = getloi(line, BUFSIZ)) == 0)return (0);	/* this means eof */

re00:
    /* here we need to strip off blank put in during write */
    /* this is because mpx does not support zero length blocks */
    if(!binary) {
    	if ((recl == 1) && (*linadrs == ' ')) recl = 0;
    	/* now append new line to end of buffer */
    	*(cp = linadrs + recl) = '\n';       /* point to last char */
    } else {
    	cp = linadrs + recl - 1;       /* point to last char */
    }

    /* copy this layer buffer to upper caller's buffer */

/* printf ("recl = %x, cp = %x, linadrs = %x\n", recl, cp, linadrs); */
    while (count < n) {
      if (linadrs > cp) break;
      *buf++ = *linadrs++;
      count++;
    }
  }

/* printf("ret1 cnt = %ld\n", count); */
  return (count);

}

/*~!bbio.c*/
/* Name:  bbio.c Part No.: _______-____r
 *
 * Copyright 1991 - J B Systems, Morrison, CO
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

#ident	"@(#)nbrtl:bbio.c	1.0"

#include <stdio.h>

/********************************************************************/
/* These routines handle blocked and optionally compressed MPX files */

#define IOCMAX 10	/* start with 10 for now */

struct ioc {
    int 	iofcb;	/* fcb for i/o */
    int		afcb;	/* callers fcb address */
    unsigned char *	bufaddr;/* callers buffer address */
    int		bufcnt;	/* callers buffer size */
    unsigned char *	cba;	/* current buffer address */
    unsigned char *	rcba;	/* record control block pointer */
    int		cpp;	/* current pool position */
    int		cfp;	/* current file position */
    char	cbn;	/* current buffer number */
    char	nab;	/* number of active buffers */
    struct {		/* ioc bit flags */
    	unsigned openop	 : 1;	/* open flag */
    	unsigned writop	 : 1;	/* last op was write */
    	unsigned outaop	 : 1;	/* output active flag */
	unsigned compop	 : 1;	/* if set, tested for comp'ed file */
	unsigned cmpflg	 : 1;	/* if set, reading comp'ed file */
	unsigned iocaloc : 1;	/* ioc allocated */
	unsigned free	 : 3;	/* free flags, available */
    } flag;
    int	bcnt;	/* compressed rec cur count */
    unsigned char *	bptr;	/* compressed rec pointer */
    unsigned char *	bufa;	/* start of contiguous buffers */
};

struct ioc iocx[IOCMAX];

#define ERRFLAG 0x04000000
#define EOFFLAG 0x02000000
#define EOMFLAG 0x01000000

#define RCBEOF 0x80 /* bit 0 */
#define RCBBOB 0x40 /* bit 1 */
#define RCBEOB 0x20 /* bit 2 */
#define RCBNULL 0x10 /* bit 3 */
#define RCBCONT 0x08 /* bit 4 */

#define SBLR 0
#define BCLR 1
#define SBTR 2
#define BCTR 3

#define BLKSIZE 768
#define BLKS (10*BLKSIZE)

/* ircont - establish ioc address for this fcb */
/* input - file number */
/* output - ioc address */
struct ioc * ircont (cfcb)
int cfcb;
{
    int	i;
    struct ioc * wioc;	/* current ioc */

    for (i = 0, wioc = &iocx[0]; i < IOCMAX; wioc = &iocx[++i]) {
    	if (wioc->flag.iocaloc)
    	    if (wioc->afcb == cfcb) {
    		return(wioc);
    	    }
    }
    /* not yet allocated, get a new one */
    for (i = 0, wioc = &iocx[0]; i < IOCMAX; wioc = &iocx[++i]) {
    	if (!wioc->flag.iocaloc) {
    	    wioc->flag.iocaloc = 1;	/* ioc allocated */
    	    if((wioc->bufa = (unsigned char *)malloc(BLKS)) <= 0) {
    		fprintf(stderr, "ioc malloc error\n");
    		return (0);
    	    }
    	    /* initialize new ioc */
    	    wioc->afcb = cfcb;		/* save callers fcb address */
    	    wioc->iofcb = cfcb;		/* use callers fcb for I/O */
    	    wioc->cba = wioc->bufa;	/* set buffer addr in fcb */
    	    wioc->cbn = 0;		/* no curr buf number */
    	    wioc->nab = 0;		/* no active bufs */
    	    /* clear flags */
    	    wioc->flag.openop = 0;	/* open ioc */
    	    wioc->flag.writop = 0;
    	    wioc->flag.outaop = 0;
    	    wioc->flag.compop = 0;
    	    wioc->flag.cmpflg = 0;
    	    wioc->cpp = 0;		/* pool empty */
    	    wioc->bcnt = 0;		/* no compress cnt */
    	    wioc->bptr = 0;		/* no pointer either */
    	    wioc->cfp = 1;		/* curr position is 1st blk */
    	    return (wioc);
    	}
    }
    fprintf(stderr, "no ioc space left\n");
    return (0);
}

/* rmopen - open up a file stream */
int rmopen (cfcb)
int cfcb;
{
    struct ioc * wioc;

    wioc = ircont(cfcb);
    if(wioc->flag.openop)
    	return(1);		/* return o.k. */
    /* not open yet, do open */
    wioc->flag.openop = 1;	/* mark open */
    return(1);			/* return o.k. */
}

/* rmclose - close a file stream */
int rmclose (cfcb)
int cfcb;
{
    struct ioc * wioc;

    wioc = ircont (cfcb);
    if(!wioc->flag.openop)
    	return(1);		/* if not open, return o.k. */
    /* open, do close */
    wioc->flag.openop = 0;	/* mark closed */
    wioc->flag.iocaloc = 0;	/* mark unallocated */
    free (wioc->bufa);		/* free buffer */
    return (1);
}

/* rmread - read from file stream */
int rmread (cfcb, buffer)
int cfcb;
unsigned char * buffer;
{
    struct ioc * wioc;
    int	fillcnt, i, bytecnt;
    unsigned char * buffp;

    rmopen(cfcb);		/* make sure open */
    wioc = ircont (cfcb);
    if (wioc->flag.writop)
    	fprintf(stderr, "read after write not allowed");
    if (wioc->cpp == 0) {	/* if no data in pool yet, read it in */
    	bfredf (wioc);		/* read in a block */
    	wioc->rcba = wioc->cba + 4;
    	/* have we tested for comp data yet */
    	if(!wioc->flag.compop) {
    	    wioc->flag.compop = 1;
    	    /* test for comp rec */
    	    if (wioc->rcba[4] == 0xbf || wioc->rcba[4] == 0x9f) {
    		wioc->flag.cmpflg = 1;	/* this is comp data */
    		wioc->bcnt = 0;		/* init pointer */
    	    }
    	}
    }
    bytecnt = 0;		/* no bytes to caller yet */
    buffp = buffer;		/* save caller buff addr */
    if (wioc->flag.cmpflg) 	/* reading compressed */
    	if (wioc->bcnt)
    	    goto re07; 		/* any data left */
re18:
    if (wioc->rcba[SBLR] & RCBEOB) {
re06:
    	if (bfredf(wioc) == -1)
    	    return(-1);
    	wioc->rcba = wioc->cba + 4;
    }
#define JIM	/* define for non-library reading */
#ifdef JIM
    if (wioc->rcba[SBTR] & RCBEOF) {
#else
    if (wioc->rcba[SBTR] & RCBEOF) {
    	wioc->rcba[SBTR] &= ~RCBEOF;
    	goto re06;
#endif
re05:
    	return(-1);	/* return EOF */
    }
    if (wioc->flag.cmpflg) {	/* reading compressed */
    	if ((wioc->rcba[4] & 0xdf) != 0x9f) {
    	    return(-1);		/* return EOF */
    	}
    	wioc->bptr = wioc->rcba + 10;	/* first data byte */
    	wioc->bcnt = wioc->rcba[5];	/* get bytes this record */
    	if (wioc->bcnt == 0) {
re10:
    	    wioc->rcba += (wioc->rcba[BCTR] + 4);
    	    goto re18;
    	}
re07:
    	if (*wioc->bptr) {		/* got blanks */
    	    if (*wioc->bptr == 0xff) {
    		wioc->bptr++;
    		if(--wioc->bcnt == 0) {
    		    wioc->rcba += (wioc->rcba[BCTR] + 4);
    		    wioc->bptr = wioc->rcba + 10;
    		}
    		wioc->bufcnt = bytecnt;
    		return (bytecnt);
    	    }
    	    for (i = *wioc->bptr; i; *buffp++ = ' ', i--, bytecnt++);
    	}
    	wioc->bptr++;
    	if (--wioc->bcnt > 0) {
    	    if (i = *wioc->bptr) {
    		wioc->bptr++;
    		wioc->bcnt--;
    		for (; i; i--) {
    		    *buffp++ = *wioc->bptr++;
    		    bytecnt++;
    		    wioc->bcnt--;
    		}
    		if (wioc->bcnt)
    		    goto re07;
    		goto re10;
    	    }
re24:
    	    wioc->bptr++;
    	    if (--wioc->bcnt > 0)
    		goto re07;
    	}
    	goto re10;
    }

    /* process uncompressed record */
    wioc->bufcnt = wioc->rcba[BCTR];
    for (i = 0; i < wioc->bufcnt; i++)
    	buffer[i] = wioc->rcba[i+4];
    wioc->rcba += (wioc->rcba[BCTR] + 4);
    return (wioc->bufcnt);
}

/* bfredf - read next buffer from file stream */
int bfredf (wioc)
struct ioc * wioc;
{
    unsigned char * cbaddr;

    /* see if next buffer in memory */
    if (wioc->cbn >= wioc->nab) {
    	/* no, read in next pool */
    	if (plredf(wioc) == -1)	/* read next pool */
    	    return(-1);		/* show EOF */
    	wioc->cbn = 1;	/* we start at 1st buffer */
    	cbaddr = wioc->bufa;	/* reset address pointer */
    } else {
    	wioc->cbn++;	/* bump buffer number */
    	cbaddr = wioc->cba + BLKSIZE;	/* next buffer address */
    }
    wioc->cba = cbaddr;	/* set new address */
    /* check for cnt < 0x300 (768) */
    /* check for BOB on in control bits */
    return(1);			/* return O.K. */
}

/* plredf - read next buffer pool from file stream */
int plredf (wioc)
struct ioc * wioc;
{
    int retc;

    /* read the file */
    retc = read(wioc->iofcb, wioc->bufa, BLKS);
    if (retc <= 0) {
    	return (-1);		/* show EOF for error */
    }
    /* compute # of block we read */
    wioc->nab = (retc + BLKSIZE-1) / BLKSIZE;
    wioc->cpp = wioc->cfp;	/* update curr pool position */
    wioc->cfp += wioc->nab;	/* update current file position */
    return(1);			/* return O.K. */
}
