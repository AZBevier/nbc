
RCSDIFF(1)                                             RCSDIFF(1)


NAME
       rcsdiff - compare RCS revisions

SYNOPSIS
       rcsdiff [ -ksubst ] [ -q ] [ -rrev1 [ -rrev2 ] ] [ -Vn ] [
       -xsuffixes ] [ diff options ] file ...

DESCRIPTION
       rcsdiff runs diff to compare  two  revisions  of each  RCS
       file given.

       Pathnames  matching  an  RCS  suffix denote RCS files; all
       others  denote  working  files.   Names  are   paired   as
       explained in ci.m.

       The option -q suppresses diagnostic output.  Zero, one, or
       two revisions  may  be  specified  with  -r.   The  option
       -ksubst affects keyword substitution when extracting revi-
       sions, as described in  co.m; for example, -kk -r1.1 -r1.2
       ignores differences in keyword values when comparing revi-
       sions 1.1 and 1.2.  To avoid  excess  output  from  locker
       name  substitution,  -kkvl  is  assumed if (1) at most one
       revision option is given, (2) no -k option is  given,  (3)
       -kkv  is  the  default  keyword  substitution, and (4) the
       working file's mode would be produced by co -l.  See  co.m
       for  details  about  -V and -x.  Otherwise, all options of
       diff that  apply to  regular files  are accepted, with the
       same meaning as for diff.

       If  both  rev1  and rev2 are omitted, rcsdiff compares the
       latest revision on the  default  branch  (by  default  the
       trunk)  with  the  contents  of  the corresponding working
       file.  This is useful for  determining  what  you  changed
       since the last checkin.

       If  rev1  is  given, but rev2 is omitted, rcsdiff compares
       revision rev1 of the RCS file with  the  contents  of  the
       corresponding working file.

       If  both  rev1  and rev2 are given, rcsdiff compares revi-
       sions rev1 and rev2 of the RCS file.

       Both rev1 and rev2 may be given  numerically  or  symboli-
       cally.

EXAMPLE
       The command

               rcsdiff  f.c

       compares  the latest revision on the default branch of the
       RCS file to the contents of the working file f.c.

DIAGNOSTICS
       Exit status is 0 for no differences during any comparison,
       1 for some differences, 2 for trouble.

IDENTIFICATION
       Author: Walter F. Tichy.
       Revision Number: 5.3; Release Date: 1991/04/21.
       Copyright (C) 1982, 1988, 1989 by Walter F. Tichy.
       Copyright (C) 1990, 1991 by Paul Eggert.
       Ported to MPX-32 05/05/95 by James C. Bevier, J B Systems.

SEE ALSO
       ci.m,   co.m,   diff.m,   ident.m,   rcs.m,    rcsintro.m, 
       rcsmerge.m,  rlog.m
       Walter  F.  Tichy,  RCS--A  System  for  Version  Control,
       Software--Practice  &  Experience  15,  7   (July   1985),
       637-654.

GNU - RCS - RCSDIFF         J B Systems                  05/05/95

