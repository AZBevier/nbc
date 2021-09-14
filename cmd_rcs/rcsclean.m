
RCSCLEAN(1)                                           RCSCLEAN(1)


NAME
       rcsclean - clean up working files

SYNOPSIS
       rcsclean [options] [ file ... ]

DESCRIPTION
       rcsclean  removes  working files that were checked out and
       never modified.  For each file  given,  rcsclean  compares
       the  working  file and a revision in the corresponding RCS
       file.  If it finds a difference, it does nothing.   Other-
       wise,  it  first  unlocks the revision if the -u option is
       given, and then removes the working file unless the  work-
       ing  file is writable and the revision is locked.  It logs
       its actions by outputting the corresponding rcs -u and  rm
       -f commands on the standard output.

       If  no  file  is  given,  all working files in the current
       directory are cleaned.  Pathnames matching an  RCS  suffix
       denote  RCS files; all others denote working files.  Names
       are paired as explained in ci.m.

       The number of the revision to which the  working  file  is
       compared may be attached to any of the options -n, -q, -r,
       or -u.  If no revision number is specified, then if the -u
       option  is  given  and the caller has one revision locked,
       rcsclean uses that revision; otherwise rcsclean  uses  the
       latest  revision on the default branch, normally the root.

       rcsclean is useful for clean targets  in  Makefiles.   See
       also  rcsdiff.m,   which  prints  out the differences, and
       ci.m,  which normally asks whether to check in a  file  if
       it was not changed.

OPTIONS
       -ksubst
              Use  subst style keyword substitution when retriev-
              ing the revision for  comparison.   See  co.m   for
              details.

       -n[rev]
              Do  not  actually  remove  any  files or unlock any
              revisions.  Using this option will  tell  you  what
              rcsclean would do without actually doing it.

       -q[rev]
              Do not log the actions taken on standard output.

       -r[rev]
              This option has no effect other than specifying the
              revision for comparison.

       -u[rev]
              Unlock  the  revision  if  it  is  locked  and   no
              difference is found.

       -Vn    Emulate RCS version n.  See ccoo(1) for details.

       -xsuffixes
              Use  suffixes to characterize RCS files.  See  ci.m
              for details.

EXAMPLES
              rcsclean  *.c  *.h

       removes all working files ending in .c or .h that were not
       changed since their checkout.

              rcsclean

       removes  all  working  files in the current directory that
       were not changed since their checkout.

FILES
       rcsclean accesses files much as ci.m does.

DIAGNOSTICS
       The exit status is zero if and only if all operations were
       successful.   Missing  working  files  and  RCS  files are
       silently ignored.

IDENTIFICATION
       Author: Walter F. Tichy.
       Revision Number: 1.8; Release Date: 1991/11/03.
       Copyright (C) 1982, 1988, 1989 by Walter F. Tichy.
       Copyright (C) 1990, 1991 by Paul Eggert.
       Ported to MPX-32 05/05/95 by James C. Bevier, J B Systems.

SEE ALSO
       ci.m,  co.m,  ident.m,  rcs.m,   rcsdiff.m,    rcsintro.m,
       rcsmerge.m,  rlog.m,  rcsfile. 
       Walter  F.  Tichy,  RCS--A  System  for  Version  Control,
       Software--Practice  &  Experience  15,  7   (July   1985),
       637-654.

BUGS
       At  least  one  file  must be given in older Unix versions
       that do not provide the needed directory  scanning  opera-
       tions.

GNU - RCS - RCSCLEAN        J B Systems                  05/05/95

