/*~!date.c*/
/* Name:  date.c Part No.: _______-____r
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

#ident	"Make4MPX $Id: date.c,v 1.4 2021/07/11 00:12:23 jbev Exp $"

/*
 * $Log: date.c,v $
 * Revision 1.4  2021/07/11 00:12:23  jbev
 * fix warning error.
 *
 * Revision 1.3  2021/07/11 00:10:57  jbev
 * Update linux build to be error free.
 *
 * Revision 1.2  1995/03/14 04:03:41  jbev
 * Correct external errors.
 *
 * Revision 1.1  1995/03/14  01:29:22  jbev
 * Initial revision
 *
 */

/*
 *	date - with format capabilities
 */

#include <stdio.h>
#include <time.h>
#include <sys/types.h>
#include <fcntl.h>
#ifndef mpx
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#endif

#ifdef mpx
extern int ascftime();
extern int setdate();
#else
static int ascftime();
static int setdate();
#endif

#define	year_size(A)	(((A) % 4) ? 365 : 366)

static char buf[100];
static time_t	clock_val;
static short month_size[12] = { 
    31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

#ifdef NOT_USED
static char *usage =
 "usage: date [-u] [+format] [hhmm | mmddhhmm[[cc]yy]]\n";
#endif

int uflag;
char *ap;

int main(argc, argv)
int argc;
char **argv;
{
    register struct tm *tp;
    char *fmt = (char *)NULL;

    /*  Initialize variables  */

    (void)time(&clock_val);

    if (argc > 1) {
    	if (strcmp(argv[1], "-u") == 0) {
    	    argc--; 
    	    argv++;
    	    uflag++;
    	} 
    }
    if (argc > 1) {
    	if (*argv[1] == '+')
    	    fmt = &argv[1][1];
    	else if (setdate(localtime(&clock_val), argv[1]))
    	    exit(1);
    }

    if (uflag) {
    	tp = gmtime(&clock_val);
    	ascftime(buf, "%a %b %e %H:%M:%S GMT %Y", tp);
    } else {
    	tp = localtime(&clock_val);
    	ascftime(buf, fmt, tp);
    }

    puts(buf);

    exit(0);
}

extern time_t timezone;
#ifdef mpx
extern time_t altzone;
#endif

int setdate(current_date, date)
struct tm *current_date;
char *date;
{
    register int i;
    int mm, dd = 0, hh, min, yy;
    int minidx = 6;

    /*  Parse date string  */
    switch (strlen(date)) {
    case 12:
    	yy = atoi(&date[8]);
    	date[8] = '\0';
    	break;
    case 10:
    	yy = 1900 + atoi(&date[8]);
    	date[8] = '\0';
    	break;
    case 8:
    	yy = 1900 + current_date->tm_year;
    	break;
    case 4:
    	yy = 1900 + current_date->tm_year;
    	mm = current_date->tm_mon + 1; 	/* tm_mon goes from 1 to 11*/
    	dd = current_date->tm_mday;
    	minidx = 2;
    	break;
    default:
    	(void) fprintf(stderr, "date: bad conversion\n");
    	return(1);
    }
    min = atoi(&date[minidx]);
    date[minidx] = '\0';
    hh = atoi(&date[minidx-2]);
    date[minidx-2] = '\0';
    if (!dd) {
    	/* if dd is 0 (not between 1 and 31), then 
		 * read the value supplied by the user.
		 */
    	dd = atoi(&date[2]);
    	date[2] = '\0';
    	mm = atoi(&date[0]);
    }
    if (hh == 24)
    	hh = 0, dd++;

    /*  Validate date elements  */
    if (!((mm >= 1 && mm <= 12) && (dd >= 1 && dd <= 31) && 
      (hh >= 0 && hh <= 23) && (min >= 0 && min <= 59))) {
    	(void) fprintf(stderr, "date: bad conversion\n");
    	return(1);
    }

    /*  Build date and time number  */
    for (clock_val = 0, i = 1970; i < yy; i++)
    	clock_val += year_size(i);
    /*  Adjust for leap year  */
    if (year_size(yy) == 366 && mm >= 3)
    	clock_val += 1;
    /*  Adjust for different month lengths  */
    while (--mm)
    	clock_val += (time_t)month_size[mm - 1];
    /*  Load up the rest  */
    clock_val += (time_t)(dd - 1);
    clock_val *= 24;
    clock_val += (time_t)hh;
    clock_val *= 60;
    clock_val += (time_t)min;
    clock_val *= 60;

    /* date program not used in linux, the std one is used. */
#ifdef mpx
    if (!uflag) {
    	/* convert to GMT assuming standard time */
    	/* correction is made in localtime(3C) */

    	clock_val += (time_t)timezone;

    	/* correct if daylight savings time in effect */
    	if (localtime(&clock_val)->tm_isdst)
    	    clock_val = clock_val - (time_t)(timezone - altzone);
    }

    if (stime(&clock_val) < 0) {
    	(void) fprintf(stderr, "date: no permission\n");
    	return(1);
    }
#endif
    return(0);
}

#ifndef mpx
/*~!cftime.c*/
/* Name:  cftime.c Part No.: _______-____r
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
 
#ident	"@(#)nbclib:cftime.c	1.1"
 
/*
 * This routine converts time as follows.  The epoch is 0000  Jan  1
 * 1970  GMT.   The  argument  time  is  in seconds since then.  The
 * localtime(t) entry returns a pointer to an array containing:
 *
 *		  seconds (0-59)
 *		  minutes (0-59)
 *		  hours (0-23)
 *		  day of month (1-31)
 *		  month (0-11)
 *		  year
 *		  weekday (0-6, Sun is 0)
 *		  day of the year
 *		  daylight savings flag
 *
 * The routine corrects for daylight saving time and  will  work  in
 * any  time  zone provided "timezone" is adjusted to the difference
 * between Greenwich and local standard time (measured in seconds).
 *
 *	 ascftime(buf, format, t)	-> where t is produced by localtime
 *				           and returns a ptr to a character
 *				           string that has the ascii time in
 *				           the format specified by the format
 *				           argument (see date(1) for format
 *				           syntax).
 *
 *	 cftime(buf, format, t) 	-> just calls ascftime.
 *
 *
 *
 */
 
#include	<ctype.h>
#include 	<fcntl.h>
#include	<stdio.h>
#include	<time.h>
#include	<sys/types.h>
#include 	<sys/stat.h>
 
#define CFTIME_DIR	"/system/lib/cftime/"
#define LEN_CT_ROOT	sizeof CFTIME_DIR - 1
#define DFL_LANG	"usa_english"
#define MAXLANGLGTH 	64	/* max length of the language string */
 
 
#ifdef NOT_USED
extern char	*getenv(), *malloc(), *memchr();
#endif
static char	*itoa();
static void	setcftime();
static char	language[MAXLANGLGTH] = DFL_LANG;
 
enum STR {
	aJan, aFeb, aMar, aApr, aMay, aJun, aJul, aAug, aSep, aOct, aNov, aDec,
	Jan, Feb, Mar, Apr, May, Jun, Jul, Aug, Sep, Oct, Nov, Dec,
	aSun, aMon, aTue, aWed, aThu, aFri, aSat,
	Sun, Mon, Tue, Wed, Thu, Fri, Sat,
	Local_time, Local_date, DFL_FMT,
	AM, PM,
	LAST
	} ;
static char * _cftime[] = {
	"Jan","Feb","Mar","Apr","May","Jun","Jul", "Aug", "Sep","Oct", "Nov", "Dec",
	"January", "February", "March","April",
	"May","June", "July", "August", "September",
	"October", "November", "December",
	"Sun","Mon", "Tue", "Wed","Thu", "Fri","Sat",
	"Sunday","Monday","Tuesday","Wednesday", "Thursday","Friday","Saturday",
	"%H:%M:%S","%m/%d/%y", "%a %b %e %T %Z %Y",
	"AM", "PM"};
 
#ifdef NOT_USED
static int
cftime(buf, format, t)
char	*buf, *format;
time_t	*t;
{
	return(ascftime(buf, format, localtime(t)));
}
#endif
 
static int
ascftime(buf, format, tm)
char	*buf, *format;
struct tm	*tm;
{
	register char	*cp, *p,  c;
/*	register int	r; */
	int		i,ret_val=0, temp;
/*	char		*ptr; */
 
	setcftime();
	/* Set format string, if not already set */
	if (!(format != NULL && *format != '\0'))
		if (!(((format = getenv("CFTIME")) != 0) && *format != 0))
			format =  _cftime[(int)DFL_FMT];
 
 
	/* Build date string by parsing format string */
	cp = buf;
	while ((c = *format++) != '\0') {
		if (c == '%') {
			switch (*format++) {
			case '%':	/* Percent sign */
				*cp++ = '%';
				continue;
			case 'a':	/* Abbreviated weekday name */
				for(p = _cftime[aSun + tm->tm_wday]; *p != '\0';p++)
					*cp++ = *p;
				continue;
			case 'A':	/* Weekday name */
				for(p =  _cftime[Sun + tm->tm_wday]; *p != '\0';p++)
					*cp++ = *p;
				continue;
			case 'h':
			case 'b':	/* Abbreviated month name */
				for(p = _cftime[aJan + tm->tm_mon];*p != '\0';p++)
					*cp++ = *p;
				continue;
			case 'B':	/* Month name */
				for(p = _cftime[Jan + tm->tm_mon];*p != '\0'; p++)
					*cp++ = *p;
				continue;
			case 'd':	/* Day number */
				cp = itoa(tm->tm_mday, cp, 2);
				continue;
			case 'D':	/* Shorthand for %m/%d/%y */
				cp += ascftime(cp,"%m/%d/%y",tm);
				continue;
			case 'e':       /* Day number without leading zero */
				if (tm->tm_mday < 10) {
					*cp++ = ' ';
                                	cp = itoa(tm->tm_mday, cp, 1);
				}
				else
					cp = itoa(tm->tm_mday, cp, 2);
                                continue;
			case 'H':	/* Hour (24 hour version) */
				cp = itoa(tm->tm_hour, cp, 2);
				continue;
			case 'I':	/* Hour (12 hour version) */
				cp = itoa(tm->tm_hour > 12 ? tm->tm_hour - 12 : tm->tm_hour, cp, 2);
				continue;
			case 'j':	/* Julian date */
				cp = itoa(tm->tm_yday + 1, cp, 3);
				continue;
			case 'm':	/* Month number */
				cp = itoa(tm->tm_mon + 1, cp, 2);
				continue;
			case 'M':	/* Minute */
				cp = itoa(tm->tm_min, cp, 2);
				continue;
			case 'n':	/* Newline */
				*cp++ = '\n';
				continue;
			case 'p':	/* AM or PM */
				if (tm->tm_hour >= 12)
					for (p = _cftime[PM]; *p != '\0'; p++)
						*cp++ = *p;
				else
					for (p = _cftime[AM]; *p != '\0'; p++)
                                                *cp++ = *p;
				continue;
			case 'r':	/* Shorthand for %I:%M:%S AM or PM */
				cp += ascftime(cp,"%I:%M:%S %p",tm);
				continue;
			case 'R':	/* Time as %H:%M */
				cp += ascftime(cp,"%H:%M",tm);
				continue;
			case 'S':	/* Seconds */
				cp = itoa(tm->tm_sec, cp, 2);
				continue;
			case 't':	/* Tab */
				*cp++ = '\t';
				continue;
			case 'T':	/* Shorthand for %H:%M:%S */
				cp += ascftime(cp,"%H:%M:%S",tm);
				continue;
			case 'U':	/* Weekday number, taking Sunday as
					 * the first day of the week */
				temp = tm->tm_yday - tm->tm_wday;
				if (temp >= -3 ) {
					i = (temp + 1) / 7 + 1;	/* +1 for - tm->tm_wday */
					if (temp % 7 >= 4) i++;
				}
				else i = 52;
				cp = itoa(i,cp,2);
				continue;
			case 'w':	/* Weekday number */
				cp = itoa(tm->tm_wday, cp, 1);
				continue;
			case 'W':	/* Week number of year, taking Monday as
					 * first day of week */
				if (tm->tm_wday == 0)
					temp = tm->tm_yday - 6;
				else
					temp = tm->tm_yday - tm->tm_wday + 1;
				if (temp >= -3 ) {
					i = (temp + 1) / 7 + 1;	/* 1 for
								   -tm->tm_wday */
					if (temp % 7 >= 4) i++;
				}
				else  i = 52; /* less than 4 days in the first
							week causes it to belong to
							the tail of prev year */
				cp = itoa(i, cp, 2);
				continue;
			case 'x':	/* Localized date format */
				cp += ascftime(cp, _cftime[Local_date], tm);
				continue;
			case 'X':	/* Localized time format */
				cp += ascftime(cp, _cftime[Local_time], tm);
				continue;
			case 'y':	/* Year in the form yy */
				cp = itoa(tm->tm_year, cp, 2);
				continue;
			case 'Y':	/* Year in the form ccyy */
				cp = itoa(1900 + tm->tm_year, cp, 4);
				continue;
			case 'Z':	/* Timezone */
				for(p = tzname[tm->tm_isdst]; *p != '\0'; p++)
					*cp++ = *p;
				continue;
			default:
				*cp++ = c;
				*cp++ = *(format - 1);
				continue;
			}
		}
	 	*cp++ = c;
	}
	ret_val = (int)(cp - buf);
	*cp = '\0';
	return(ret_val);
}
 
static void
setcftime()
{
	register char *p;
	register int j;
	char *mystr[LAST], *file,  *q;
	static char *ostr = (char *)0 ;
	char *str;
	struct stat buf;
	static char pathname[128] = CFTIME_DIR;
	int fd;
 
 
	if ((file = getenv("LANGUAGE")) == 0 || file[0] == '\0')
	{
		/* Use the default _cftime[] */
 
		if (pathname[LEN_CT_ROOT] == '\0')
			return;
		file = language;
	}	
	else if (strcmp(file,language) == 0)
		return;
 
	(void) strcpy(&pathname[LEN_CT_ROOT],file);
 
	if ( (fd = open(pathname,O_RDONLY)) == -1)
		return;
 
	if( (fstat(fd,&buf)) != 0)
		return;
 
 
	if ( (str = malloc(buf.st_size + 2)) == NULL )
		return;
 
	if ( (read(fd, str, buf.st_size)) != buf.st_size)
	{
		free(str);
		return;
	}
 
	/* Set last character of str to '\0' */
	q = &str[buf.st_size];
	q[0] = '\n';
	q[1] = '\0';
 
	/* p will "walk thru" str */
	p = str;  	
 
	j = -1;
	while (*p != '\0')
	{
		/* "Look for a newline, i.e. end of sub-string
		 * and  change it to a '\0'. If LAST pointers
		 * have been set in mystr, but the newline hasn't been seen
		 * yet, keep going thru the string leaving mystr alone.
		 */
		if (++j < LAST)
			mystr[j] = p;
		p = memchr(p,'\n',buf.st_size + 2);
		*p++ = '\0';
	}
	if (j == LAST)
	{
		memcpy(_cftime, mystr,sizeof(mystr));
		strncpy(language, file, MAXLANGLGTH);
		if (ostr != 0)	 /* free the previoulsy allocated local array*/
			free(ostr);
		ostr = str;
	}
	(void) close(fd);
	return;
	
}
 
static char *
itoa(i, ptr, dig)
register int	i;
register char	*ptr;
register int	dig;
{
	switch(dig) {
	case 4:
		*ptr++ = i / 1000 + '0';
		i = i - i / 1000 * 1000;
	case 3:
		*ptr++ = i / 100 + '0';
		i = i - i / 100 * 100;
	case 2:
		*ptr++ = i / 10 + '0';
	case 1:
		*ptr++ = i % 10 + '0';
	}
 
	return(ptr);
}
#endif
