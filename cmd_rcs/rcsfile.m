
RCSFILE(5)                                             RCSFILE(5)


NAME
       rcsfile - format of RCS file

DESCRIPTION
       An RCS file's contents are described by the grammar below.

       The text is free format: space, backspace,  tab,  newline,
       vertical  tab,  form  feed,  and  carriage return (collec-
       tively,  white  space)  have  no  significance  except  in
       strings.  However, an RCS file must end in a newline char-
       acter.

       Strings are enclosed by @.  If a string contains a  @,  it
       must  be doubled; otherwise, strings may contain arbitrary
       binary data.

       The meta syntax uses the following conventions: `|'  (bar)
       separates  alternatives;  `{'  and  `}'  enclose  optional
       phrases; `{' and `}*' enclose phrases that may be repeated
       zero or more times; `{' and '}+' enclose phrases that must
       appear at least once and may be repeated; Terminal symbols
       are in boldface; nonterminal symbols are in italics.

       rcstext    ::=  admin {delta}* desc {deltatext}*

       admin      ::=  head       {num};
                       { branch   {num}; }
                       access     {id}*;
                       symbols    {id : num}*;
                       locks      {id : num}*;  {strict  ;}
                       { comment  {string}; }
                       { expand   {string}; }
                       { newphrase }*

       delta      ::=  num
                       date       num;
                       author     id;
                       state      {id};
                       branches   {num}*;
                       next       {num};
                       { newphrase }*

       desc       ::=  desc       string

       deltatext  ::=  num
                       log        string
                       { newphrase }*
                       text       string

       num        ::=  {digit{.}}+

       digit      ::=  0 | 1 | ... | 9

       id         ::=  letter{idchar}*

       letter     ::=  any letter

       idchar     ::=  any visible graphic character except special

       special    ::=  $ | , | . | : | ; | @

       string     ::=  @{any character, with @ doubled}*@

       newphrase  ::=  id word* ;

       word       ::=  id | num | string | :

       Identifiers  are  case  sensitive.   Keywords are in lower
       case only.  The sets of keywords and identifiers may over-
       lap.   In most environments RCS uses the ISO 8859/1 encod-
       ing: letters are octal codes  101-132,  141-172,  300-326,
       330-366  and 370-377, visible graphic characters are codes
       041-176 and 240-377, and white space characters are  codes
       010-015 and 040.

       The  newphrase productions in the grammar are reserved for
       future extensions to the format of  RCS  files.   No  new-
       phrase will begin with any keyword already in use.

       The delta nodes form a tree.  All nodes whose numbers con-
       sist of a single pair (e.g., 2.3, 2.1, 1.3, etc.)  are  on
       the  trunk, and are linked through the next field in order
       of decreasing numbers.  The head field in the  admin  node
       points  to  the  head of that sequence (i.e., contains the
       highest pair).  The branch node in the  admin  node  indi-
       cates the default branch (or revision) for most RCS opera-
       tions.  If empty, the default branch is the highest branch
       on the trunk.

       All  delta nodes whose numbers consist of 2n fields (nP=2)
       (e.g., 3.1.1.1, 2.1.2.2, etc.)   are  linked  as  follows.
       All nodes whose first 2n-1 number fields are identical are
       linked through the next field in order of increasing  num-
       bers.  For each such sequence, the delta node whose number
       is identical to the first 2n-2 number fields of the deltas
       on  that sequence is called the branchpoint.  The branches
       field of a node contains a list  of  the  numbers  of  the
       first  nodes  of  all  sequences for which it is a branch-
       point.  This list is ordered in increasing numbers.

       Example:

                                  Head
                                    |
                                    |
                                    v                        / \
                                ---------                   /   \
          / \          / \      |       |      / \         /     \
         /   \        /   \     |  2.1  |     /   \       /       \
        /     \      /     \    |       |    /     \     /         \
       /1.2.1.3\    /1.3.1.1\   |       |   /1.2.2.2\   /1.2.2.1.1.1\
       ---------    ---------   ---------   ---------   -------------
           ^            ^           |           ^             ^
           |            |           |           |             |
           |            |           v           |             |
          / \           |       ---------      / \            |
         /   \          |       \  1.3  /     /   \           |
        /     \         ---------\     /     /     \-----------
       /1.2.1.1\                  \   /     /1.2.2.1\
       ---------                   \ /      ---------
           ^                        |           ^
           |                        |           |
           |                        v           |
           |                    ---------       |
           |                    \  1.2  /       |
           ----------------------\     /---------
                                  \   /
                                   \ /
                                    |
                                    |
                                    v
                                ---------
                                \  1.1  /
                                 \     /
                                  \   /
                                   \ /

                        Fig. 1: A revision tree


IDENTIFICATION
       Author:  Walter  F.   Tichy,   Purdue   University,   West
       Lafayette, IN, 47907.
       Revision Number: 5.1; Release Date: 1991/08/19.
       Copyright (C) 1982, 1988, 1989 by Walter F. Tichy.
       Copyright (C) 1990, 1991 by Paul Eggert.
       Ported to MPX-32 05/05/95 by James C. Bevier, J B Systems.

SEE ALSO
       ci.m,   co.m,   ident.m,  rcs.m,  rcsdiff.m,   rcsmerge.m,
       rlog.m
       Walter  F.  Tichy,  RCS--A  System  for  Version  Control,
       Software--Practice   &   Experience  15,  7  (July  1985),
       637-654.

GNU - RCS - RCSFILE         J B Systems                  05/05/95

