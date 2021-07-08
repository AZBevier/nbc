# Makefile for NBC /system/doc directory on MPX1X

SHELL = /bin/sh

ROOT = /system
D = $(ROOT)/doc1x

##CFLAGS = -O -I$I # -m32

DOC1 =	a64l abort abs access acos alarm asctime \
		asin assert atan2 atan atof atoi atol \
		bcmp bcopy bessel brk bsearch calloc ceil \
		chdir chmod chown chownm chroot chtype clearerr \
		clock closedir close conv cosh cos creatd \
		creat ctime ctype delete directory drand48 dup \
		ecvt erand48 erfc erf errno execle execl.m

DOC2 =	execlp exec execve execv execvp _exit exit \
		_exitmpx exp fabs fcbadr fclose fcvt fdopen \
		feof ferror fflush fgetc fgets fileno floor \
		fmod fopen fork fprintf fputc fputs fread \
		free freopen frexp fscanf fseek fstat ftell \
		fwrite gamma gcvt getacc getchar getc getcwd \
		getenv getgid getopt getpgrp getpid getppid gets.m

DOC3 =	getuid getw gmtime hcreate hdestroy hsearch hypot \
		ieeelib ioctl isalnum isalpha isascii isatty \
		iscntrl isdigit isgraph islower isprint ispunct isspace \
		isupper isxdigit j0 j1 jn jrand48 kill \
		l3tol l64a lcong48 ldexp link localtime log10 \
		log longjmp lrand48 lsearch lseek ltol3 malloc \
		matherr math memccpy memchr memcmp memcpy memory.m

DOC4 =	memset mkdir mktemp modf moelib molib mpxccset \
		mpxsvc mrand48 nbcas nbcat nbcc nbccom nbcpp \
		nblex nbyacc nice nrand48 opendir open pause \
		perror pipe pow printf putchar putc putenv \
		puts putw qsort rand read1ln readdir read \
		readmdir readraw realloc rewinddir rewind rmdir sbrk \
		scanf seed48 seekdir seek setacc setbuf setdft.m

DOC5 = 	setgid setjmp setpgrp setsiz setuid setvbuf signal \
		sinh sin sleep sprintf sqrt srand48 srand \
		sscanf stack stat1x stat stats stdio stime \
		str2lc str2up stradd strcasecmp strcat strccpy strchr \
		strcmp strcpy strcspn strdup strecnt strecpy stricmp \
		string strlen strncasecmp strncat strncmp strncpy strnlen \
		strpbrk strpos strrchr strrpos strspn strtod strtok \

DOC6 =	strtol swab sync sys_errlist sys_nerr tanh tan \
		tdelete telldir tempnam tfind time times tmpfile \
		tmpnam toascii _tolower tolower _toupper toupper trig \
		tsearch twalk types tzset umask ungetc unix2mpx \
		unixio unlink utime values varargs vexecl vexecv \
		vfprintf vprintf vsprintf wait write writraw y0 \
		y1 yn.m

SRN =	srnnbc1x # srn_nbc_1.0.0

DOC = $(DOC1) $(DOC2) $(DOC3) $(DOC4) $(DOC5) $(DOC6) $(SRN)

install	: dir $(DOC)
		@-cp $(DOC1) $(D)
		@-cp $(DOC2) $(D)
		@-cp $(DOC3) $(D)
		@-cp $(DOC4) $(D)
		@-cp $(DOC5) $(D)
		@-cp $(DOC6) $(D)
		@-cp $(SRN)  $(D)
		@-echo "Documentation installation complete"

dir:
		@if [ ! -d $(D) ]; then \
			mkdir $(D); \
			echo "$(D) created"; \
		fi;
#		@if [ -d $(D) ]; then \
#			echo "$(D) created"; \
#		else \
#			mkdir $(D); \
#		fi;

remake	:	clobber
	@make ROOT=$(ROOT)

clean	:
clobber	:	clean
	@-rm -fr $(D)
