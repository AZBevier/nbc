
RCS(1)                                                     RCS(1)


NAME
       rcs - change RCS file attributes

SYNOPSIS
       rcs [ options ] file ...

DESCRIPTION
       rcs  creates new RCS files or changes attributes of exist-
       ing ones.  An RCS  file  contains  multiple  revisions  of
       text,  an access list, a change log, descriptive text, and
       some control attributes.  For rcs to  work,  the  caller's
       login  name  must  be  on  the  access list, except if the
       access list is empty, the caller is the owner of the  file
       or the superuser, or the -i option is present.

       Pathnames  matching  an  RCS  suffix denote RCS files; all
       others  denote  working  files.   Names  are   paired   as
       explained  in  ci.m.    Revision  numbers  use  the syntax
       described in ci.m.

OPTIONS
       -i     Create and initialize a new RCS file,  but  do  not
              deposit  any revision.  If the RCS file has no path
              prefix, try to place it first into the subdirectory
              ./RCS, and then into the current directory.  If the
              RCS file already exists, print an error message.

       -glogins
              Append the login  names  appearing  in  the  comma-
              separated list logins to the access list of the RCS
              file.

       -Aoldfile
              Append the access list of  oldfile  to  the  access
              list of the RCS file.

       -e[logins]
              Erase  the  login  names  appearing  in  the comma-
              separated list logins from the access list  of  the
              RCS  file.   If logins is omitted, erase the entire
              access list.

       -b[rev]
              Set the default branch to rev.  If rev is  omitted,
              the  default  branch  is reset to the (dynamically)
              highest branch on the trunk.

       -cstring
              sets the comment leader  to  string.   The  comment
              leader  is  printed  before  every log message line
              generated by the keyword $Log: rcs.m,v $
              generated by the keyword Revision 1.1  2021/07/08 22:04:07  jbev
              generated by the keyword Initial revision
              generated by the keyword during checkout (see
              co.m).   This  is  useful for programming languages
              without multi-line comments.  An initial ci , or an
              rcs -i  without -c, guesses the comment leader from
              the suffix of the working file.

       -ksubst
              Set the default keyword substitution to subst.  The
              effect  of  keyword  substitution  is  described in
              co.m.   Giving an explicit -k option to  co,  rcsd-
              iff,  and  rcsmerge overrides this default.  Beware
              rcs -kv, because -kv is  incompatible  with  co -l.
              Use  rcs -kkv to restore the normal default keyword
              substitution.

       -l[rev]
              Lock the revision with number rev.  If a branch  is
              given, lock the latest revision on that branch.  If
              rev is omitted, lock the  latest  revision  on  the
              default   branch.    Locking  prevents  overlapping
              changes.  A lock is removed with ci or rcs -u  (see
              below).

       -u[rev]
              Unlock  the  revision with number rev.  If a branch
              is  given,  unlock  the  latest  revision  on  that
              branch.   If rev is omitted, remove the latest lock
              held by the caller.  Normally, only the locker of a
              revision  may unlock it.  Somebody else unlocking a
              revision breaks the lock.  This causes a mail  mes-
              sage  to  be sent to the original locker.  The mes-
              sage  contains  a  commentary  solicited  from  the
              breaker.   The  commentary is terminated by end-of-
              file or by a line containing . by itself.

       -Y     Set locking to strict.  Strict locking  means  that
              the owner of an RCS file is not exempt from locking
              for checkin.  This option should be used for  files
              that are shared.

       -Z     Set  locking  to  non-strict.   Non-strict  locking
              means that the owner of a  file  need  not  lock  a
              revision  for  checkin.   This option should not be
              used for files that are  shared.   Whether  default
              locking  is  strict  is  determined  by your system
              administrator, but it is normally strict.

       -mrev:msg
              Replace revision rev's log message with msg.

       -nname[:[rev]]
              Associate the symbolic name name with the branch or
              revision  rev.   Delete the symbolic name if both :
              and rev are omitted; otherwise, print an error mes-
              sage  if  name  is  already associated with another
              number.  If rev is symbolic, it is expanded  before
              association.   A  rev consisting of a branch number
              followed by a  .  stands  for  the  current  latest
              revision  in  the  branch.   A  : with an empty rev
              stands for  the  current  latest  revision  on  the
              default  branch,  normally the trunk.  For example,
              rcs -nname: RCS/* associates name with the  current
              latest  revision  of  all the named RCS files; this
              contrasts with rcs -nname:$ RCS/* which  associates
              name  with the revision numbers extracted from key-
              word strings in the corresponding working files.

       -Rname[:[rev]]
              Act like -n, except override any  previous  assign-
              ment of name.

       -orange
              deletes  ("outdates") the revisions given by range.
              A range consisting  of  a  single  revision  number
              means  that  revision.   A  range  consisting  of a
              branch number means the  latest  revision  on  that
              branch.   A range of the form rev1:rev2 means revi-
              sions rev1 to rev2 on the same branch,  :rev  means
              from  the beginning of the branch containing rev up
              to and including rev, and rev: means from  revision
              rev  to the end of the branch containing rev.  None
              of the outdated  revisions  may  have  branches  or
              locks.

       -q     Run quietly; do not print diagnostics.

       -sstate[:rev]
              Set the state attribute  of  the  revision  rev  to
              state .  If rev is a branch number, assume the lat-
              est revision on that branch.  If  rev  is  omitted,
              assume  the  latest revision on the default branch.
              Any identifier is acceptable for state.   A  useful
              set  of states is Exp (for experimental), Stab (for
              stable), and Rel  (for released).  By  default,  ci
              sets the state of a revision to Exp.

       -t[file]
              Write  descriptive  text  from  the contents of the
              named file into the RCS file, deleting the existing
              text.   The file pathname may not begin with -.  If
              file is omitted,  obtain  the  text  from  standard
              input,  terminated by end-of-file or by a line con-
              taining . by itself.  Prompt for the text if inter-
              action  is  possible.  With -i, descriptive text is
              obtained even if -t is not given.

       -t-string
              Write descriptive text from the string into the RCS
              file, deleting the existing text.

       -Vn    Emulate RCS version n.  See co.m for details.

       -xsuffixes
              Use  suffixes to characterize RCS files.   See ci.m
              for details.

COMPATIBILITY
       The -brev option generates an  RCS  file  that  cannot  be
       parsed by RCS version 3 or earlier.

       The  -ksubst  options  (except  -kkv) generate an RCS file
       that cannot be parsed by RCS version 4 or earlier.

       Use rcs -Vn to make an RCS file acceptable to RCS  version
       n  by discarding information that would confuse version n.

       RCS version 5.5  and  earlier  does  not  support  the  -x
       option, and requires a _v suffix on an RCS pathname.

FILES
       rcs accesses files much  as  ci  does, except that it uses
       the effective user for all accesses, it does not write the
       working  file  or its directory, and it does not even read
       the working file unless a revision number of $  is  speci-
       fied.

DIAGNOSTICS
       The RCS pathname and the revisions outdated are written to
       the  diagnostic  output.   The  exit status is zero if and
       only if all operations were successful.

IDENTIFICATION
       Author: Walter F. Tichy.
       Revision Number: 5.6; Release Date: 1991/09/26.
       Copyright (C) 1982, 1988, 1989 by Walter F. Tichy.
       Copyright (C) 1990, 1991 by Paul Eggert.
       Ported to MPX-32 05/05/95 by James C. Bevier, J B Systems.

SEE ALSO
       co.m,    ci.m,    ident.m,     rcsdiff.m,      rcsintro.m,
       rcsmerge.m,  rlog.m,  rcsfile.m
       Walter  F.  Tichy,  RCS--A  System  for  Version  Control,
       Software--Practice  &  Experience  15,  7   (July   1985),
       637-654.

BUGS
       The separator for revision ranges in the -o option used to
       be - instead of :, but this leads to confusion  when  sym-
       bolic names contain -.  For backwards compatibility rcs -o
       still supports the old - separator,  but  it  warns  about
       this obsolete use.

       Symbolic  names  need  not  refer to existing revisions or
       branches.  For example, the --oo option does not remove sym-
       bolic names for the outdated revisions; you must use -n to
       remove the names.

GNU - RCS - RCS             J B Systems                  05/05/95

