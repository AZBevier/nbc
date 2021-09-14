
RCSFREEZE(1)                                         RCSFREEZE(1)


NAME
       rcsfreeze  -  freeze a configuration of sources checked in
       under RCS

SYNOPSIS
       rcsfreeze [name]

DESCRIPTION
       rcsfreeze assigns a symbolic revision  number to a set  of
       RCS files that form a valid configuration.

       The  idea  is  to run rcsfreeze each time a new version is
       checked in.  A unique symbolic name (CC_number, where num-
       ber  is  increased  each  time  rcsfreeze  is run) is then
       assigned to the most recent revision of each RCS  file  of
       the main trunk.

       An  optional  name  argument to rcsfreeze gives a symbolic
       name to the configuration.  The unique identifier is still
       generated  and  is  listed in the log file but it will not
       appear as part of the symbolic revision name in the actual
       RCS files.

       A log message is requested from the user for future refer-
       ence.

       The shell script works only on all RCS files at one  time.
       All  changed  files  must  be  checked  in  already.   Run
       rcsclean(1) first and see whether any  sources  remain  in
       the current directory.

FILES
       RCS/.rcsfreeze.ver
       version number

       RCS/.rcsfreeze.log
       log messages, most recent first

AUTHOR
Stephan v. Bechtolsheim

SEE ALSO
       co.m, rcs.m, rcsclean.m, rlog.m

BUGS
       rcsfreeze  does  not check whether any sources are checked
       out and modified.

       Although both source file names and  RCS  file  names  are
       accepted,  they are not paired as usual with RCS commands.

       Error checking is rudimentary.

       rcsfreeze is just an optional example  shell  script,  and
       should  not  be  taken  too seriously.  See CVS for a more
       complete solution.


GNU - RCS - RCSFREEZE            J B Systems             05/05/95

