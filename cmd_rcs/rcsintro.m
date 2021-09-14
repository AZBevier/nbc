
RCSINTRO(1)                                           RCSINTRO(1)


NAME
       rcsintro - introduction to RCS commands

DESCRIPTION
       The  Revision  Control System (RCS) manages multiple revi-
       sions of files.  RCS  automates  the  storing,  retrieval,
       logging, identification, and merging of revisions.  RCS is
       useful for text that is revised  frequently,  for  example
       programs,  documentation,  graphics, papers, and form let-
       ters.

       The basic user interface is extremely simple.  The  novice
       only  needs  to  learn  two  commands:  ci  and  co.   ci,
       short for "check in", deposits the contents of a file into
       an archival file called an RCS file.  An RCS file contains
       all revisions of a particular file.  co, short for  "check
       out", retrieves revisions from an RCS file.

   Functions of RCS
       o      Store and retrieve multiple revisions of text.  RCS
              saves all old revisions in a space  efficient  way.
              Changes no longer destroy the original, because the
              previous revisions  remain  accessible.   Revisions
              can  be  retrieved  according to ranges of revision
              numbers,  symbolic  names,  dates,   authors,   and
              states.

       o      Maintain  a  complete history of changes.  RCS logs
              all changes automatically.   Besides  the  text  of
              each  revision, RCS stores the author, the date and
              time of check-in, and a log message summarizing the
              change.  The logging makes it easy to find out what
              happened to a module,  without  having  to  compare
              source listings or having to track down colleagues.

       o      Resolve access conflicts.  When two  or  more  pro-
              grammers  wish  to  modify  the  same revision, RCS
              alerts the programmers and prevents  one  modifica-
              tion from corrupting the other.

       o      Maintain  a  tree  of  revisions.  RCS can maintain
              separate lines of development for each module.   It
              stores  a tree structure that represents the ances-
              tral relationships among revisions.

       o      Merge revisions and resolve conflicts.   Two  sepa-
              rate  lines  of development of a module can be coa-
              lesced by merging.  If the revisions to  be  merged
              affect  the  same  sections of code, RCS alerts the
              user about the overlapping changes.

       o      Control releases and configurations.  Revisions can
              be  assigned symbolic names and marked as released,
              stable, experimental, etc.  With these  facilities,
              configurations  of  modules can be described simply
              and directly.

       o      Automatically identify  each  revision  with  name,
              revision  number,  creation time, author, etc.  The
              identification is like a stamp that can be embedded
              at  an appropriate place in the text of a revision.
              The identification makes  it  simple  to  determine
              which  revisions  of  which modules make up a given
              configuration.

       o      Minimize secondary storage.  RCS needs little extra
              space for the revisions (only the differences).  If
              intermediate revisions are deleted, the correspond-
              ing deltas are compressed accordingly.

   Getting Started with RCS
       Suppose  you  have  a  file f.c that you wish to put under
       control of RCS.  If you have not already done so, make  an
       RCS directory with the command

              mkdir  RCS

       Then invoke the check-in command

              ci  f.c

       This  command  creates  an  RCS file in the RCS directory,
       stores f.c into it as revision 1.1, and deletes  f.c.   It
       also  asks  you for a description.  The description should
       be a synopsis of the contents  of  the  file.   All  later
       check-in  commands  will  ask  you  for a log entry, which
       should summarize the changes that you made.

       Files in the RCS directory are called RCS files; the  oth-
       ers  are  called  working  files.  To get back the working
       file f.c in the previous example, use the  check-out  com-
       mand

              co  f.c

       This  command  extracts  the  latest revision from the RCS
       file and writes it into f.c.  If you want to edit f.c, you
       must lock it as you check it out with the command

              co  -l  f.c

       You can now edit f.c.

       Suppose  after  some editing you want to know what changes
       that you have made.  The command

              rcsdiff  f.c

       tells  you  the  difference  between  the  most   recently
       checked-in  version  and  the working file.  You can check
       the file back in by invoking

              ci  f.c

       This increments the revision number properly.

       If ci complains with the message

              ci error: no lock set by your name

       then you have tried to check in a file even though you did
       not lock it when you checked it out.  Of course, it is too
       late now to do the check-out with locking, because another
       check-out  would  overwrite  your modifications.  Instead,
       invoke

              rcs  -l  f.c

       This command will lock the latest revision for you, unless
       somebody  else  got  ahead  of you already.  In this case,
       you'll have to negotiate with that person.

       Locking assures that you, and only you, can check  in  the
       next  update,  and avoids nasty problems if several people
       work on the same file.  Even if a revision is  locked,  it
       can still be checked out for reading, compiling, etc.  All
       that locking prevents is a check-in  by  anybody  but  the
       locker.

       If  your  RCS  file  is private, i.e., if you are the only
       person who is going to deposit revisions into  it,  strict
       locking  is not needed and you can turn it off.  If strict
       locking is turned off, the owner of the RCS file need  not
       have  a  lock  for check-in; all others still do.  Turning
       strict locking off and on is done with the commands

              rcs  -U  f.c     and     rcs  -L  f.c

       If you don't want to clutter your working  directory  with
       RCS  files, create a subdirectory called RCS in your work-
       ing directory, and move all your  RCS  files  there.   RCS
       commands  will  look  first  into  that  directory to find
       needed files.  All the commands discussed above will still
       work,  without  any modification.  (Actually, pairs of RCS
       and working files can be specified in three ways: (a) both
       are  given,  (b)  only the working file is given, (c) only
       the RCS file is given.  Both RCS  and  working  files  may
       have  arbitrary  path  prefixes; RCS commands pair them up
       intelligently.)

       To avoid the deletion of the working file during  check-in
       (in  case  you  want  to  continue  editing or compiling),
       invoke

              ci  -l  f.c     or     ci  -u  f.c

       These commands check in  f.c  as  usual,  but  perform  an
       implicit check-out.  The first form also locks the checked
       in revision, the second one doesn't.  Thus, these  options
       save  you one check-out operation.  The first form is use-
       ful if you want to continue editing, the second one if you
       just  want  to read the file.  Both update the identifica-
       tion markers in your working file (see below).

       You can give ci the number you want assigned to a  checked
       in revision.  Assume all your revisions were numbered 1.1,
       1.2, 1.3, etc., and you would like  to  start  release  2.
       The command

              ci  -r2  f.c     or     ci  -r2.1  f.c

       assigns the number 2.1 to the new revision.  From then on,
       ci will number the subsequent  revisions  with  2.2,  2.3,
       etc.  The corresponding co commands

              co  -r2  f.c     and     co  -r2.1  f.c

       retrieve the latest revision numbered 2.x and the revision
       2.1, respectively.  co without a revision  number  selects
       the  latest  revision on the trunk, i.e. the highest revi-
       sion with a number consisting of two fields.  Numbers with
       more  than  two fields are needed for branches.  For exam-
       ple, to start a branch at revision 1.3, invoke

              ci  -r1.3.1  f.c

       This command starts a branch numbered 1 at  revision  1.3,
       and  assigns  the number 1.3.1.1 to the new revision.  For
       more information about branches, see rcsfile.m.

   Automatic Identification
       RCS can put special strings for identification  into  your
       source  and  object  code.  To obtain such identification,
       place the marker

              $Id: rcsintro.m,v 1.1 2021/07/08 22:04:07 jbev Exp $

       into your text, for instance inside a comment.   RCS  will
       replace this marker with a string of the form

                filename  revision  date  time  author  state
              $

       With such a marker on the first page of each  module,  you
       can  always  see with which revision you are working.  RCS
       keeps the markers up to date automatically.  To  propagate
       the  markers  into  your object code, simply put them into
       literal character strings.  In C, this is done as follows:

              static char rcsid[] = "$Id: rcsintro.m,v 1.1 2021/07/08 22:04:07 jbev Exp $";

       The  command  ident  extracts  such markers from any file,
       even object code and dumps.  Thus, ident lets you find out
       which revisions of which modules were used in a given pro-
       gram.

       You may also find it useful to put the marker  $Log: rcsintro.m,v $
       You may also find it useful to put the marker  Revision 1.1  2021/07/08 22:04:07  jbev
       You may also find it useful to put the marker  Initial revision
       You may also find it useful to put the marker  into
       your  text, inside a comment.  This marker accumulates the
       log messages that are requested  during  check-in.   Thus,
       you  can  maintain  the  complete  history  of  your  file
       directly inside it.  There are several additional  identi-
       fication markers; see co.m for details.

IDENTIFICATION
       Author: Walter F. Tichy.
       Revision Number: 5.1; Release Date: 1991/04/21.
       Copyright (C) 1982, 1988, 1989 by Walter F. Tichy.
       Copyright (C) 1990, 1991 by Paul Eggert.
       Ported to MPX-32 05/05/95 by James C. Bevier, J B Systems.

SEE ALSO
       ci.m,   co.m,   ident.m,  rcs.m,  rcsdiff.m,  rcsintro.m, 
       rcsmerge.m,  rlog.m
       Walter  F.  Tichy,  RCS--A  System  for  Version  Control,
       Software--Practice   &   Experience  15,  7  (July  1985),
       637-654.

GNU - RCS - RCSINTRO        J B Systems                  05/05/95

