# Makefile for nbcpp
#
#
# *$Log: Makefile,v $
# *Revision 1.4  1996/03/20 18:44:52  jbev
# *More mods for Alpha port.
# *
# *Revision 1.3  1996/03/20 18:12:43  jbev
# *Mods for alpha port.
# *
# *Revision 1.2  1996/03/20 18:09:10  jbev
# *Add depend and clobber entries.
# *
#

CC = cc
#CFLAGS = -O -taso -xtaso -xtaso_short
CFLAGS = -O # -migrate
CPFLAGS = -M
INSTALL = cp
YACC = yacc
BINDIR = /system/bin
MAKEFILE = Makefile

OBJS = nbcpp.o nbcpy.o
SRCS = nbcpp.c nbcpy.y 

all: nbcpp

nbcpp: $(OBJS)
	$(CC) $(CFLAGS) -o nbcpp $(OBJS)
	/bin/chmod 755 nbcpp

# nbcpp modules

nbcpp.o: nbcpp.c

nbcpy.o: nbcpy.c yylex.c

nbcpy.c: nbcpy.y
	$(YACC) nbcpy.y
	mv y.tab.c nbcpy.c

depend: $(SRCS) $(MAKEFILE)
	$(BINDIR)/dodep $(CPFLAGS) $(MAKEFILE) $(SRCS) >dep.out
	mv dep.out $(MAKEFILE)

clean:
	-rm -f *.o
	-rm -f nbcpy.c

clobber: clean
	-rm -f nbcpp
	-rm -f core

# Copy the file into bindir
install: all
	$(INSTALL) nbcpp $(BINDIR)

# DO NOT DELETE THIS LINE -- the dependencies begin here

