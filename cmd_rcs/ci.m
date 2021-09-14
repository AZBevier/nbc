
CI(1)                                                       CI(1)


NAME
       ci - check in RCS revisions

SYNOPSIS
       ci [options] file ...

DESCRIPTION
       ci  stores  new  revisions  into RCS files.  Each pathname
       matching an RCS suffix is taken to be an  RCS  file.   All
       others  are  assumed  to  be  working files containing new
       revisions.  ci deposits the contents of each working  file
       into  the  corresponding RCS file.  If only a working file
       is given, ci tries to find the corresponding RCS  file  in
       an  RCS subdirectory and then in the working file's direc-
       tory.  For more details, see FILE NAMING below.

       For ci to work, the caller's login must be on  the  access
       list,  except if the access list is empty or the caller is
       the superuser or the owner of the file.  To append  a  new
       revision  to  an existing branch, the tip revision on that
       branch must be locked by the caller.   Otherwise,  only  a
       new  branch  can  be  created.   This  restriction  is not
       enforced for the owner of the file if  non-strict  locking
       is  used (see rcs.m).   A lock held by someone else may be
       broken with the rcs command.

       Unless the -f option is given, ci checks whether the revi-
       sion  to  be deposited differs from the preceding one.  If
       not, instead of creating a new revision ci reverts to  the
       preceding one.  To revert, ordinary ci removes the working
       file and any lock; ci -l keeps and ci -u removes any lock,
       and  then they both generate a new working file much as if
       co -l or co -u had been applied to the preceding revision.
       When reverting, any -n and -s options apply to the preced-
       ing revision.

       For each revision deposited, ci prompts for a log message.
       The  log  message  should summarize the change and must be
       terminated by end-of-file or by  a  line  containing  . by
       itself.   If  several files are checked in ci asks whether
       to reuse the previous log message.  If the standard  input
       is  not  a terminal, ci suppresses the prompt and uses the
       same log message for all files.  See also -m.

       If the RCS file does not exist, ci creates it and deposits
       the  contents  of the working file as the initial revision
       (default number: 1.1).  The access list is initialized  to
       empty.   Instead  of the log message, ci requests descrip-
       tive text (see -t below).

       The number rev of the deposited revision can be  given  by
       any of the options -f, -I, -k, -l, -M, -q, -r, or -u.  rev
       may be symbolic, numeric, or  mixed.   If  rev  is  $,  ci
       determines  the revision number from keyword values in the
       working file.

       If rev is a revision number, it must be  higher  than  the
       latest  one  on  the  branch to which rev belongs, or must
       start a new branch.

       If rev is a branch rather than a revision number, the  new
       revision  is appended to that branch.  The level number is
       obtained by incrementing the tip revision number  of  that
       branch.   If  rev  indicates  a  non-existing branch, that
       branch is  created  with  the  initial  revision  numbered
       rev.1.

       If  rev  is  omitted,  ci tries to derive the new revision
       number from the caller's last lock.   If  the  caller  has
       locked  the  tip revision of a branch, the new revision is
       appended to that  branch.   The  new  revision  number  is
       obtained  by incrementing the tip revision number.  If the
       caller locked a non-tip revision, a new branch is  started
       at that revision by incrementing the highest branch number
       at that revision.  The default initial  branch  and  level
       numbers are 1.

       If rev is omitted and the caller has no lock, but owns the
       file and locking is not set to strict, then  the  revision
       is appended to the default branch (normally the trunk; see
       the -b option in rcs.m).

       Exception: On the trunk, revisions can be appended to  the
       end, but not inserted.

OPTIONS
       -r[rev]
              checks  in  a  revision, releases the corresponding
              lock, and removes the working file.   This  is  the
              default.

              The  -r  option  has  an unusual meaning in ci.  In
              other RCS commands, -r merely specifies a  revision
              number,  but  in  ci  it  also  releases a lock and
              removes the working file.   See  -u  for  a  tricky
              example.

       -l[rev]
              works  like  -r,  except  it performs an additional
              co -l  for  the  deposited  revision.   Thus,   the
              deposited revision is immediately checked out again
              and locked.  This is useful for saving  a  revision
              although one wants to continue editing it after the
              checkin.

       -u[rev]
              works like -l, except that the  deposited  revision
              is not locked.  This lets one read the working file
              immediately after checkin.

              The -l, -r, and -u options are  mutually  exclusive
              and  silently  override  each  other.  For example,
              ci -u -r is equivalent to ci -r  because  -r  over-
              rides -u.

       -f[rev]
              forces  a  deposit;  the  new revision is deposited
              even it is not different from the preceding one.

       -k[rev]
              searches the working file  for  keyword  values  to
              determine   its  revision  number,  creation  date,
              state, and  author (see co.m),  and  assigns  these
              values  to the deposited revision, rather than com-
              puting them locally.  It also generates  a  default
              login  message  noting  the login of the caller and
              the actual checkin date.  This option is useful for
              software  distribution.  A revision that is sent to
              several sites should be  checked  in  with  the  -k
              option at these sites to preserve the original num-
              ber, date, author, and state.  The  extracted  key-
              word  values  and  the  default  log message may be
              overridden with the options -d, -m, -s, -w, and any
              option that carries a revision number.

       -q[rev]
              quiet  mode;  diagnostic  output is not printed.  A
              revision that is not different from  the  preceding
              one is not deposited, unless -f is given.

       -d[date]
              uses  date for the checkin date and time.  The date
              is specified in free format as explained  in  co.m.
              This  is  useful  for lying about the checkin date,
              and for -k if no date is  available.   If  date  is
              empty, the working file's time of last modification
              is used.

       -M[rev]
              Set the modification time on any new  working  file
              to  be  the  date  of  the retrieved revision.  For
              example, ci -d -M -u f does not alter f's modifica-
              tion  time, even if f's contents change due to key-
              word substitution.  Use this option with  care;  it
              can confuse make.

       -mmsg  uses  the  string  msg  as  the log message for all
              revisions checked in.

       -nname assigns the symbolic name name to the number of the
              checked-in revision.  ci prints an error message if
              name is already assigned to another number.

       -Nname same as -n, except that  it  overrides  a  previous
              assignment of name.

       -sstate
              sets  the  state  of the checked-in revision to the
              identifier state.  The default state is Exp.

       -tfile writes descriptive text from the  contents  of  the
              named file into the RCS file, deleting the existing
              text.  The file may not begin with -.

       -t-string
              Write descriptive text from the string into the RCS
              file, deleting the existing text.

              The  -t  option, in both its forms, has effect only
              during an initial checkin; it is  silently  ignored
              otherwise.

              During  the initial checkin, if -t is not given, ci
              obtains the text from standard input, terminated by
              end-of-file  or  by  a line containing . by itself.
              The user is prompted for the text if interaction is
              possible.

              For  backward  compatibility with older versions of
              RCS, a bare -t option is ignored.

       -wlogin
              uses login for the author field  of  the  deposited
              revision.   Useful  for lying about the author, and
              for -k if no author is available.

       -Vn    Emulate RCS version n.  See co.m for details.

       -xsuffixes
              specifies the suffixes for RCS files.   A  nonempty
              suffix  matches  any pathname ending in the suffix.
              An empty suffix matches any pathname  of  the  form
              RCS/file or path/RCS/file.  The -x option can spec-
              ify a list of suffixes separated by /.   For  exam-
              ple, -x_v/ specifies two suffixes: _v and the empty
              suffix.  If two or  more  suffixes  are  specified,
              they  are  tried  in  order when looking for an RCS
              file; the first one that works  is  used  for  that
              file.   If no RCS file is found but an RCS file can
              be created, the suffixes  are  tried  in  order  to
              determine the new RCS file's name.  The default for
              suffixes is installation-dependent; normally it  is
              ,v/  for hosts like Unix that permit commas in file
              names, and is empty (i.e. just  the  empty  suffix)
              for other hosts.  For MPX it is _v.

FILE NAMING
       Pairs  of  RCS files and working files may be specified in
       three ways (see also the example section).

       1) Both the RCS file and the working file are given.   The
       RCS  pathname is of the form path1/workfileX and the work-
       ing pathname is of the form  path2/workfile  where  path1/
       and  path2/ are (possibly different or empty) paths, work-
       file is a filename, and X is  an  RCS  suffix.   If  X  is
       empty, path1/ must be RCS/ or must end in /RCS/.

       2)  Only  the RCS file is given.  Then the working file is
       created in the current directory and its name  is  derived
       from  the  name of the RCS file by removing path1/ and the
       suffix X.

       3) Only the working file is given.  Then ci considers each
       RCS  suffix X in turn, looking for an RCS file of the form
       path2/RCS/workfileX or (if the former is not found  and  X
       is nonempty) path2/workfileX.

       If  the RCS file is specified without a path in 1) and 2),
       ci looks for the RCS file first in the directory ./RCS and
       then in the current directory.

       ci  reports  an  error  if  an attempt to open an RCS file
       fails for an unusual reason, even if the RCS file's  path-
       name  is  just one of several possibilities.  For example,
       to suppress use of RCS commands in a directory d, create a
       regular  file  named  d/RCS so that casual attempts to use
       RCS commands in d fail because d/RCS is not a directory.

EXAMPLES
       Suppose ,v is an RCS suffix and the current directory con-
       tains  a  subdirectory  RCS with an RCS file io.c,v.  Then
       each of the following commands check in  a  copy  of  io.c
       into RCS/io.c,v as the latest revision, removing io.c.

              ci  io.c;    ci  RCS/io.c,v;   ci  io.c,v;
              ci  io.c  RCS/io.c,v;    ci  io.c  io.c,v;
              ci  RCS/io.c,v  io.c;    ci  io.c,v  io.c;

       Suppose instead that the empty suffix is an RCS suffix and
       the current directory contains a subdirectory RCS with  an
       RCS  file io.c.  The each of the following commands checks
       in a new revision.

              ci  io.c;    ci  RCS/io.c;
              ci  io.c  RCS/io.c;
              ci  RCS/io.c  io.c;

FILE MODES
       An RCS file created by ci inherits the  read  and  execute
       permissions from the working file.  If the RCS file exists
       already, ci preserves its read  and  execute  permissions.
       ci always turns off all write permissions of RCS files.

FILES
       Several  temporary  files  may be created in the directory
       containing the working file, and  also  in  the  temporary
       directory  (see  TMPDIR  under  ENVIRONMENT).  A semaphore
       file or files are created in the directory containing  the
       RCS  file.   With  a  nonempty suffix, the semaphore names
       begin with the first character of the  suffix;  therefore,
       do  not  specify  an suffix whose first character could be
       that of a working filename.  With  an  empty  suffix,  the
       semaphore names end with _ so working filenames should not
       end in _.

       ci never changes an RCS or  working  file.   Normally,  ci
       unlinks  the  file  and  creates a new one; but instead of
       breaking a chain of one or more symbolic links to  an  RCS
       file, it unlinks the destination file instead.  Therefore,
       ci breaks any hard or symbolic links to any  working  file
       it  changes;  and hard links to RCS files are ineffective,
       but symbolic links to RCS files are preserved.

       The effective user must be able to search  and  write  the
       directory  containing  the  RCS  file.  Normally, the real
       user must be able to read the RCS and working files and to
       search  and  write  the  directory  containing the working
       file; however,  some  older  hosts  cannot  easily  switch
       between  real  and  effective users, so on these hosts the
       effective user is used for all  accesses.   The  effective
       user is the same as the real user unless your copies of ci
       and co have setuid privileges.  As described in  the  next
       section,  these  privileges  yield  extra  security if the
       effective user owns all RCS files and directories, and  if
       only the effective user can write RCS directories.

       Users  can control access to RCS files by setting the per-
       missions of the directory containing the files; only users
       with write access to the directory can use RCS commands to
       change its RCS files.  For example, in hosts that allow  a
       user  to  belong to several groups, one can make a group's
       RCS  directories  writable  to  that  group  only.    This
       approach suffices for informal projects, but it means that
       any group member can arbitrarily change  the  group's  RCS
       files, and can even remove them entirely.  Hence more for-
       mal projects sometimes distinguish between an RCS adminis-
       trator,  who  can  change the RCS files at will, and other
       project members, who can check in new revisions but cannot
       otherwise change the RCS files.

SETUID USE
       To prevent anybody but their RCS administrator from delet-
       ing revisions, a set of users can employ setuid privileges
       as follows.

       o Check  that the host supports RCS setuid use.  Consult a
         trustworthy expert if there are any doubts.  It is  best
         if the seteuid() system call works as described in Posix
         1003.1a Draft 5, because RCS can switch back  and  forth
         easily  between  real  and  effective users, even if the
         real user is root.  If not, the second best  is  if  the
         setuid()   system   call   supports  saved  setuid  (the
         {_POSIX_SAVED_IDS} behavior of Posix 1003.1-1990);  this
         fails only if the real user is root.  If RCS detects any
         failure in setuid, it quits immediately.

       o Choose a user A to serve as RCS  administrator  for  the
         set  of  users.   Only  A will be able to invoke the rcs
         command on the users' RCS files.  A should not  be  root
         or  any other user with special powers.  Mutually suspi-
         cious sets of users should use different administrators.

       o Choose  a  path name B that will be a directory of files
         to be executed by the users.

       o Have A set up B to contain copies of ci and co that  are
         setuid  to A by copying the commands from their standard
         installation directory D as follows:

              mkdir  B
              cp  D/c[io]  B
              chmod  go-w,u+s  B/c[io]

       o Have each user prepend B to their path as follows:

              PATH=B:$PATH;  export  PATH  # ordinary shell
              set  path=(B  $path)  # C shell

       o Have A create each RCS directory  R  with  write  access
         only to A as follows:

              mkdir  R
              chmod  go-w  R

       o If  you  want  to  let  only  certain users read the RCS
         files, put the users into a group G, and have A  further
         protect the RCS directory as follows:

              chgrp  G  R
              chmod  g-w,o-rwx  R

       o Have  A  copy  old  RCS files (if any) into R, to ensure
         that A owns them.

       o An RCS file's access list limits who can  check  in  and
         lock revisions.  The default access list is empty, which
         grants checkin access to anyone who  can  read  the  RCS
         file.   If  you want limit checkin access, have A invoke
         rcs -a  on  the  file;  see  rcs.m.     In   particular,
         rcs -e -aA limits access to just A.

       o Have  A  initialize any new RCS files with rcs -i before
         initial checkin, adding the -a option  if  you  want  to
         limit checkin access.

       o Give  setuid privileges only to ci, co, and rcsclean; do
         not give them to rcs or to any other command.

       o Do not use other setuid commands to invoke RCS commands;
         setuid is trickier than you think!

DIAGNOSTICS
       For  each  revision,  ci  prints the RCS file, the working
       file, and the number of both the deposited and the preced-
       ing  revision.  The exit status is zero if and only if all
       operations were successful.

IDENTIFICATION
       Author: Walter F. Tichy.
       Revision Number: 5.9; Release Date: 1991/10/07.
       Copyright (C) 1982, 1988, 1989 by Walter F. Tichy.
       Copyright (C) 1990, 1991 by Paul Eggert.
       Ported to MPX-32 05/05/95 by James C. Bevier, J B Systems.

SEE ALSO
       co.m,  ident.m,  make.m,  rcs.m,  rcsclean.m,   rcsdiff.m,
       rcsintro.m,  rcsmerge.m,  rlog.m,  rcsfile.m 
       Walter  F.  Tichy,  RCS--A  System  for  Version  Control,
       Software--Practice  &  Experience  15,  7   (July   1985),
       637-654.

GNU - RCS - CI              J B Systems                  05/05/95

