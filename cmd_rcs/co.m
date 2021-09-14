
CO(1)                                                       CO(1)


NAME
       co - check out RCS revisions

SYNOPSIS
       co [options] file ...

DESCRIPTION
       co  retrieves  a revision from each RCS file and stores it
       into the corresponding working file.

       Pathnames matching an RCS suffix  denote  RCS  files;  all
       others   denote   working  files.   Names  are  paired  as
       explained in ci.m.

       Revisions of an RCS file may  be  checked  out  locked  or
       unlocked.    Locking   a   revision  prevents  overlapping
       updates.  A revision checked out for reading or processing
       (e.g.,  compiling) need not be locked.  A revision checked
       out for editing and later checkin must normally be locked.
       Checkout  with locking fails if the revision to be checked
       out is currently locked by another user.  (A lock  may  be
       broken  with rcs.m.)   Checkout with locking also requires
       the caller to be on the  access  list  of  the  RCS  file,
       unless  he  is  the owner of the file or the superuser, or
       the access list is empty.  Checkout without locking is not
       subject to accesslist restrictions, and is not affected by
       the presence of locks.

       A revision is selected by options for revision  or  branch
       number,  checkin  date/time,  author,  or state.  When the
       selection options are applied in combination, co retrieves
       the  latest  revision that satisfies all of them.  If none
       of the selection options is specified,  co  retrieves  the
       latest revision on the default branch (normally the trunk,
       see the -b option of rcs.m).   A revision or branch number
       may  be attached to any of the options -f, -I, -l, -M, -p,
       -q, -r, or -u.  The options -d (date), -s (state), and  -w
       (author)  retrieve  from  a  single  branch,  the selected
       branch, which is either specified by one of -f,  ...,  -u,
       or the default branch.

       A co command applied to an RCS file with no revisions cre-
       ates a zero-length working file.  co always performs  key-
       word substitution (see below).

OPTIONS
       -r[rev]
              retrieves  the latest revision whose number is less
              than or equal to rev.  If rev  indicates  a  branch
              rather than a revision, the latest revision on that
              branch is retrieved.  If rev is omitted, the latest
              revision  on  the default branch (see the -b option
              of rcs.m)  is retrieved.  If rev is  $,  co  deter-
              mines  the  revision  number from keyword values in
              the working file.  Otherwise, a  revision  is  com-
              posed  of  one  or  more numeric or symbolic fields
              separated by periods.  The numeric equivalent of  a
              symbolic  field  is specified with the -n option of
              the commands ci.m and rcs.m.

       -l[rev]
              same as -r, except that it also locks the retrieved
              revision for the caller.

       -u[rev]
              same  as  -r,  except that it unlocks the retrieved
              revision if it was locked by the caller.  If rev is
              omitted,  -u  retrieves  the revision locked by the
              caller, if there is one;  otherwise,  it  retrieves
              the latest revision on the default branch.

       -f[rev]
              forces  the overwriting of the working file; useful
              in connection with -q.  See also FILE MODES  below.

       -kkv   Generate  keyword  strings  using the default form,
              e.g. $Revision: 1.1 $ for the Revision keyword.   A
              locker's  name  is  inserted  in  the  value of the
              Header, Id, and Locker keyword strings  only  as  a
              file  is  being  locked,  i.e.  by ci -l and co -l.
              This is the default.

       -kkvl  Like -kkv, except that a locker's  name  is  always
              inserted if the given revision is currently locked.

       -kk    Generate only keyword  names  in  keyword  strings;
              omit their values.  See KEYWORD SUBSTITUTION below.
              For example, for the Revision keyword, generate the
              string  $Revision: 1.1 $  instead  of  $Revision: 1.1 $.
              This option is useful to ignore differences due  to
              keyword substitution when comparing different revi-
              sions of a file.

       -ko    Generate the old keyword  string,  present  in  the
              working  file  just  before it was checked in.  For
              example, for the  Revision  keyword,  generate  the
              string $Revision: 1.1 $ instead of $Revision: 1.1 $
              if that is how the string appeared  when  the  file
              was checked in.  This can be useful for binary file
              formats that cannot tolerate any  changes  to  sub-
              strings  that  happen  to  take the form of keyword
              strings.

       -kv    Generate only keyword values for  keyword  strings.
              For example, for the Revision keyword, generate the
              string 5.7 instead of $Revision: 1.1 $.   This  can
              help  generate files in programming languages where
              it  is  hard  to  strip  keyword  delimiters   like
              $Revision: 1.1 $  from a string.  However, further key-
              word substitution cannot be performed once the key-
              word  names  are  removed, so this option should be
              used with care.  Because of this danger  of  losing
              keywords,  this  option cannot be combined with -l,
              and the owner write permission of the working  file
              is turned off; to edit the file later, check it out
              again without -kv.

       -p[rev]
              prints the retrieved revision on the standard  out-
              put  rather  than  storing  it in the working file.
              This option is useful when co is part of a pipe.

       -q[rev]
              quiet mode; diagnostics are not printed.

       -ddate retrieves  the  latest  revision  on  the  selected
              branch  whose  checkin  date/time  is  less than or
              equal to date.  The date and time may be  given  in
              free  format.   The  time  zone LT stands for local
              time; other common time zone names are  understood.
              For  example, the following dates are equivalent if
              local time is January 11, 1990, 8pm  Pacific  Stan-
              dard  Time, eight hours west of Coordinated Univer-
              sal Time (UTC):

                 8:00 pm lt
                 4:00 AM, Jan. 12, 1990      note: default is UTC
                 1990/01/12 04:00:00         RCS date format
                 Thu Jan 11 20:00:00 1990 LT output of ctime + LT
                 Thu Jan 11 20:00:00 PST 1990  output of date
                 Fri Jan 12 04:00:00 GMT 1990
                 Thu, 11 Jan 1990 20:00:00 -0800
                 Fri-JST, 1990, 1pm Jan 12
                 12-January-1990, 04:00-WET

              Most fields in the date and time may be  defaulted.
              The  default  time zone is UTC.  The other defaults
              are determined in the order year, month, day, hour,
              minute, and second (most to least significant).  At
              least one of these fields must  be  provided.   For
              omitted fields that are of higher significance than
              the highest provided field, the time zone's current
              values  are assumed.  For all other omitted fields,
              the lowest possible values are assumed.  For  exam-
              ple, the date 20, 10:30 defaults to 10:30:00 UTC of
              the 20th of the UTC time zone's current  month  and
              year.   The date/time must be quoted if it contains
              spaces.

       -M[rev]
              Set the modification time on the new  working  file
              to be the date of the retrieved revision.  Use this
              option with care; it can confuse make.

       -sstate
              retrieves  the  latest  revision  on  the  selected
              branch whose state is set to state.

       -w[login]
              retrieves  the  latest  revision  on  the  selected
              branch which was checked in by the user with  login
              name  login.  If the argument login is omitted, the
              caller's login is assumed.

       -jjoinlist
              generates a new revision which is the join  of  the
              revisions  on  joinlist.   This  option  is largely
              obsoleted by rcsmerge(1) but is retained for  back-
              wards compatibility.

              The  joinlist is a comma-separated list of pairs of
              the form rev2:rev3, where rev2 and rev3  are  (sym-
              bolic  or  numeric) revision numbers.  For the ini-
              tial such pair, rev1 denotes the revision  selected
              by  the  above  options -f, ..., -w.  For all other
              pairs, rev1 denotes the revision generated  by  the
              previous  pair.   (Thus,  the  output  of  one join
              becomes the input to the next.)

              For each pair, co joins  revisions  rev1  and  rev3
              with  respect to rev2.  This means that all changes
              that transform rev2 into rev1 are applied to a copy
              of  rev3.   This is particularly useful if rev1 and
              rev3 are the ends of two branches that have rev2 as
              a  common  ancestor.  If rev1<rev2<rev3 on the same
              branch, joining generates a new revision  which  is
              like rev3, but with all changes that lead from rev1
              to rev2 undone.  If changes from rev2 to rev1 over-
              lap  with  changes  from  rev2  to rev3, co reports
              overlaps as described in merge.m.

              For the initial pair, rev2  may  be  omitted.   The
              default  is  the  common  ancestor.   If any of the
              arguments indicate branches, the  latest  revisions
              on  those branches are assumed.  The options -l and
              -u lock or unlock rev1.

       -Vn    Emulate RCS version n, where n may be 3, 4,  or  5.
              This  may  be  useful  when interchanging RCS files
              with others who are running older versions of  RCS.
              To see which version of RCS your correspondents are
              running, have them invoke rlog on an RCS  file;  if
              none  of  the first few lines of output contain the
              string branch: it is version 3; if the dates' years
              have  just  two digits, it is version 4; otherwise,
              it is version 5.  An RCS file generated while  emu-
              lating  version 3 will lose its default branch.  An
              RCS revision generated while emulating version 4 or
              earlier  will have a timestamp that is off by up to
              13 hours.  A  revision  extracted  while  emulating
              version 4 or earlier will contain dates of the form
              yy/mm/dd instead of yyyy/mm/dd and may also contain
              different  white  space  in  the  substitution  for
              $Log: co.m,v $
              Revision 1.1  2021/07/08 22:04:07  jbev
              Initial revision
.

       -xsuffixes
              Use suffixes to characterize RCS  files.  See  ci.m
              for details.

KEYWORD SUBSTITUTION
       Strings  of  the form $keyword$ and $keyword:...$ embedded
       in the text are replaced with strings of  the  form  $key-
       word:value$  where  keyword  and  value  are  pairs listed
       below.  Keywords may be embedded  in  literal  strings  or
       comments to identify a revision.

       Initially,  the user enters strings of the form $keyword$.
       On checkout, co replaces these strings with strings of the
       form $keyword:value$.  If a revision containing strings of
       the latter form is checked back in, the value fields  will
       be  replaced  during the next checkout.  Thus, the keyword
       values are automatically updated on checkout.  This  auto-
       matic substitution can be modified by the -k options.

       Keywords and their corresponding values:

       $Author: jbev $
              The login name of the user who checked in the revi-
              sion.

       $Date: 2021/07/08 22:04:07 $ The date and time (UTC) the  revision  was  checked
              in.

       $Header: /bulk2/simhv/nbc-master/cmd_rcs/RCS/co.m,v 1.1 2021/07/08 22:04:07 jbev Exp $
              A  standard  header containing the full pathname of
              the RCS file, the revision number, the date  (UTC),
              the  author, the state, and the locker (if locked).

       $Id: co.m,v 1.1 2021/07/08 22:04:07 jbev Exp $   Same as $Header: /bulk2/simhv/nbc-master/cmd_rcs/RCS/co.m,v 1.1 2021/07/08 22:04:07 jbev Exp $, except that the RCS  filename  is
              without a path.

       $Locker:  $
              The  login name of the user who locked the revision
              (empty if not locked).

       $Log: co.m,v $
       Revision 1.1  2021/07/08 22:04:07  jbev
       Initial revision
  The log message supplied during  checkin,  preceded
              by  a header containing the RCS filename, the revi-
              sion  number,  the  author,  and  the  date  (UTC).
              Existing  log  messages are not replaced.  Instead,
              the new log message is  inserted  after  $Log: co.m,v $
              the new log message is  inserted  after  Revision 1.1  2021/07/08 22:04:07  jbev
              the new log message is  inserted  after  Initial revision
              the new log message is  inserted  after.
              This  is  useful for accumulating a complete change
              log in a source file.

       $RCSfile: co.m,v $
              The name of the RCS file without a path.

       $Revision: 1.1 $
              The revision number assigned to the revision.

       $Source: /bulk2/simhv/nbc-master/cmd_rcs/RCS/co.m,v $
              The full pathname of the RCS file.

       $State: Exp $
              The state assigned to  the  revision  with  the  -s
              option of rcs or ci.

FILE MODES
       The working file inherits the read and execute permissions
       from the RCS file.  In addition, the owner  write  permis-
       sion  is  turned  on,  unless  -kv  is  set or the file is
       checked out unlocked and locking is  set  to  strict  (see
       rcs.m).

       If a file with the name of the working file exists already
       and has write permission, co aborts the  checkout,  asking
       beforehand  if  possible.  If the existing working file is
       not writable or -f is given, the working file  is  deleted
       without asking.

FILES
       co  accesses files much  as  ci  does, except that it does
       not need to read the working file.

DIAGNOSTICS
       The  RCS  pathname, the working pathname, and the revision
       number retrieved are written  to  the  diagnostic  output.
       The exit status is zero if and only if all operations were
       successful.

IDENTIFICATION
       Author: Walter F. Tichy.
       Revision Number: 5.7; Release Date: 1991/08/19.
       Copyright (C) 1982, 1988, 1989 by Walter F. Tichy.
       Copyright (C) 1990, 1991 by Paul Eggert.
       Ported to MPX-32 05/05/95 by James C. Bevier, J B Systems.

SEE ALSO
       ci.m, ctime.m,  date.m, ident.m, make.m, rcs.m, rcsdiff.m,
       rcsintro.m,  rcsmerge.m,  rlog.m,  rcsfile.m
       Walter  F.  Tichy,  RCS--A  System  for  Version  Control,
       Software--Practice  &  Experience  15,  7   (July   1985),
       637-654.

LIMITS
       Links to the RCS and working files are not preserved.

       There  is  no way to selectively suppress the expansion of
       keywords, except by writing them  differently.   In  nroff
       and troff, this is done by embedding the null-character \&
       into the keyword.

BUGS
       The -d option sometimes gets confused, and accepts no date
       before 1970.

GNU - RCS - CO              J B Systems                  05/05/95

