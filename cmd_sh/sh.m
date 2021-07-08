 
 
     SH(C)		       UNIX System V			 SH(C)
 
 
     Name
	  sh -	Invokes	the shell command interpreter.
 
     Syntax
	  sh [ -ceiknrstuvx ] [	args ]
 
     Description
	  The shell is the standard command programming	language that
	  executes commands read from a	terminal or a file.  See
	  Invocation below for the meaning of arguments	to the shell.
 
	Commands
	  A simple-command is a	sequence of nonblank words separated
	  by blanks (a blank is	a tab or a space).  The	first word
	  specifies the	name of	the command to be executed.  Except as
	  specified below, the remaining words are passed as arguments
	  to the invoked command.  The command name is passed as
	  argument 0 (see exec(S)).  The value of a simple-command is
	  its exit status if it	terminates normally, or	(octal)
	  1000+status if it terminates abnormally (i.e., if the
	  failure produces a core file). See signal(S) for a list of
	  status values.
 
	  A pipeline is	a sequence of one or more commands separated
	  by a vertical	bar (|).  (The caret (^), is an	obsolete
	  synonym for the vertical bar and should not be used in a
	  pipeline.) The standard output of each command but the last
	  is connected by a pipe(S) to the standard input of the next
	  command.  Each command is run	as a separate process; the
	  shell	waits for the last command to terminate.
 
	  A list is a sequence of one or more pipelines	separated by
	  ;, &,	&&, or ||, and optionally terminated by	; or &.	 Of
	  these	four symbols, ;	and & have equal precedence, which is
	  lower	than that of &&	and ||.	 The symbols &&	and || also
	  have equal precedence.  A semicolon (;) causes sequential
	  execution of the preceding pipeline; an ampersand (&)	causes
	  asynchronous execution of the	preceding pipeline (i.e., the
	  shell	does not wait for that pipeline	to finish).  The
	  symbol && (||	) causes the list following it to be executed
	  only if the preceding	pipeline returns a zero	(nonzero) exit
	  status.  An arbitrary	number of newlines may appear in a
	  list,	instead	of semicolons, to delimit commands.
 
 
     Page 1					      (printed 5/7/94)
 
 
     SH(C)		       UNIX System V			 SH(C)
 
 
	  A command is either a	simple-command or one of the following
	  commands.  Unless otherwise stated, the value	returned by a
	  command is that of the last simple-command executed in the
	  command:
 
     for name [	in word	... ]
     do
       list
     done
 
       Each time a for command is executed, name is set	to the next
       word taken from the in word list.  If in	word is	omitted, then
       the for command executes	the do list once for each positional
       parameter that is set (see Parameter Substitution below).
       Execution ends when there are no	more words in the list.
 
     case word in
     [ pattern [ | pattern ] ... ) list
				   ;;  ]
     esac
       A case command  executes	 the list associated  with  the	first
       pattern that matches word.  The form of the patterns is the
       same as that used for filename generation (see Filename
       Generation below).
 
     if	list then
       list
     [ elif list then
       list ]
     [ else list ]
     fi
       The list	following if is	executed and, if it returns a zero
       exit status, the	list following the first then is executed.
       Otherwise, the list following elif is executed and, if its
       value is	zero, the list following the next then is executed.
       Failing that, the else list is executed.	 If no else list or
       then list is executed, then the if command returns a zero exit
       status.
 
     while list
     do
       list
     done
       A while command repeatedly executes the while list and, if the
       exit status of the last command in the list is zero, executes
       the do list; otherwise the loop terminates.  If no commands in
       the do list are executed, then the while	command	returns	a zero
       exit status; until may be used in place of while	to negate the
       loop termination	test.
 
	  (list)
	       Executes	list in	a subshell.
 
 
     Page 2					      (printed 5/7/94)
 
 
     SH(C)		       UNIX System V			 SH(C)
 
 
	  {list;}
	       list is simply executed.
 
	  name () {list;}
	       Define a	function which is referenced by	name. The body
	       of functions is the list	of commands between { and }.
	       Execution of functions is described later (see
	       Execution.)
 
 
	  The following	words are recognized only as the first word of
	  a command and	when not quoted:
 
	  if then else elif fi case esac for while until do done { }
 
	Comments
	  A word beginning with	# causes that word and all the
	  following characters up to a newline to be ignored.
 
	Command	Substitution
	  The standard output from a command enclosed in a pair	of
	  grave	accents	(``) may be used as part or all	of a word;
	  trailing newlines are	removed.
 
	Parameter Substitution
	  The character	$ is used to introduce substitutable
	  parameters.  Positional parameters may be assigned values by
	  set.	Variables may be set by	writing:
 
	       name=value [ name=value ] ...
 
	  Pattern-matching is not performed on value.
 
	  ${parameter}
	       A parameter is a	sequence of letters, digits, or
	       underscores (a name), a digit, or any of	the characters
	       *, @, #,	?, -, $, and !.	 The value, if any, of the
	       parameter is substituted.  The braces are required only
	       when parameter is followed by a letter, digit, or
	       underscore that is not to be interpreted	as part	of its
	       name.  A	name must begin	with a letter or underscore.
	       If parameter is a digit then it is a positional
	       parameter.  If parameter	is * or	@, then	all the
	       positional parameters, starting with $1,	are
	       substituted (separated by spaces).  Parameter $0	is set
	       from argument zero when the shell is invoked.
 
	  ${parameter:-word}
	       If parameter is set and is not a	null argument,
	       substitute its value; otherwise substitute word.
 
	  ${parameter:=word}
 
 
     Page 3					      (printed 5/7/94)
 
 
     SH(C)		       UNIX System V			 SH(C)
 
 
	       If parameter is not set or is null, then	set it to
	       word; the value of the parameter	is then	substituted.
	       Positional parameters may not be	assigned to in this
	       way.
 
	  ${parameter:?word}
	       If parameter is set and is not a	null argument,
	       substitute its value; otherwise,	print word and exit
	       from the	shell.	If word	is omitted, the	message
	       ``parameter null	or not set'' is	printed.
 
	  ${parameter:+word}
	       If parameter is set and is not a	null argument,
	       substitute word;	otherwise substitute nothing.  In the
	       above, word is not evaluated unless it is to be used as
	       the substituted string, so that in the following
	       example,	pwd is executed	only if	d is not set or	is
	       null:
 
		 echo ${d:-`pwd`}
 
	  If the colon (:) is omitted from the above expressions, then
	  the shell only checks	whether	parameter is set.
 
	  The following	parameters are automatically set by the	shell:
 
	  #    The number of positional	parameters in decimal
 
	  -    Flags supplied to the shell on invocation or by the set
	       command
 
	  ?    The decimal value returned by the last synchronously
	       executed	command
 
	  $    The process number of this shell
 
	  !    The process number of the last background command
	       invoked
 
	  The following	parameters are used by the shell:
 
	  CDPATH
	       Defines search path for the cd command.	See the
	       section Special Commands, ``cd''.
 
	  HOME The default argument (home directory) for the cd
	       command
 
	  PATH The search path for commands (see Execution below)
 
	  MAIL If this variable	is set to the name of a	mail file,
	       then the	shell informs the user of the arrival of mail
 
 
     Page 4					      (printed 5/7/94)
 
 
     SH(C)		       UNIX System V			 SH(C)
 
 
	       in the specified	file
 
	  MAILCHECK
	       This parameter specifies	how often (in seconds) the
	       shell will check	for the	arrival	 of mail  in
	       the files specified by the MAILPATH or MAIL parameters.
	       The default value is 600	seconds	(10 minutes).  If set
	       to 0, the shell will check before each prompt.
 
	  MAILPATH
	       A colon (:) separated list of file names.  If this
	       parameter is set, the shell informs the user of the
	       arrival of mail in any of the specified files.  Each
	       file name can be	followed by % and a message that will
	       be printed when the modification	time changes.  The
	       default message is you have mail.
 
	  PS1  Primary prompt string, by default ``$ ''
 
	  PS2  Secondary prompt	string,	by default ``> ''
 
	  IFS  Internal	field separators, normally space, tab, and
	       newline
 
	  SHACCT
	       If this parameter is set	to the name of a file writable
	       by the user, the	shell will write an accounting record
	       in the file for each shell procedure executed.
	       Accounting routines such	as acctcom(ADM)	and
	       accton(ADM) can be used to analyze the data collected.
	       This feature does not work with all versions of the
	       shell.
 
	  SHELL
	       When the	shell is invoked, it scans the environment
	       (see Environment	below) for this	name.  If it is	found
	       and there is an `r' in the file name part of its	value,
	       the shell becomes a restricted shell.
 
	  The shell gives default values to PATH, PS1, PS2, and	IFS,
	  while	HOME and MAIL are not set at all by the	shell
	  (although HOME is set	by login(M)).
 
	Blank Interpretation
	  After	parameter and command substitution, the	results	of
	  substitution are scanned for internal	field separator
	  characters (those found in IFS) and split into distinct
	  arguments where such characters are found.  Explicit null
	  arguments (""	or '') are retained.  Implicit null arguments
	  (those resulting from	parameters that	have no	values)	are
	  removed.
 
 
     Page 5					      (printed 5/7/94)
 
 
     SH(C)		       UNIX System V			 SH(C)
 
 
	Filename Generation
	  Following substitution, each command word is scanned for the
	  characters *,	?, and [.  If one of these characters appears,
	  the word is regarded as a pattern.  The word is replaced
	  with alphabetically sorted filenames that match the pattern.
	  If no	filename is found that matches the pattern, the	word
	  is left unchanged.  The character . at the start of a
	  filename or immediately following a /, as well as the
	  character / itself, must be matched explicitly. These
	  characters and their matching	patterns are:
 
	  *    Matches any string, including the null string.
 
	  ?    Matches any single character.
 
	  [...]
	       Matches any one of the enclosed characters.  A pair of
	       characters separated by - matches any character
	       lexically between the pair, inclusive.  If the first
	       character following the opening bracket ([) is an
	       exclamation mark	(!), then any character	not enclosed
	       is matched.
 
	Quoting
	  The following	characters have	a special meaning to the shell
	  and cause termination	of a word unless quoted:
 
	       ;  &  (	)  |  ^	 <  >  newline	space  tab
 
	  A character may be quoted (i.e., made	to stand for itself)
	  by preceding it with a \.  The pair \newline is ignored.
	  All characters enclosed between a pair of single quotation
	  marks	(''), except a single quotation	mark, are quoted.
	  Inside double	quotation marks	(""), parameter	and command
	  substitution occurs and \ quotes the characters \, `,	", and
	  $.  "$*" is equivalent to "$1	$2 ...", whereas ``$@''	is
	  equivalent to	"$1" "$2" ...
 
	Prompting
	  When used interactively, the shell prompts with the value of
	  PS1 before reading a command.	 If at any time	a newline is
	  typed	and further input is needed to complete	a command, the
	  secondary prompt (i.e., the value of PS2) is issued.
 
 
     Page 6					      (printed 5/7/94)
 
 
     SH(C)		       UNIX System V			 SH(C)
 
 
	Spelling Checker
	  When using cd(C) the shell checks spelling.  For example, if
	  you change to	a different directory using cd and misspell
	  the directory	name, the shell	repsonds with an alternative
	  spelling of an existing directory.  Enter ``y'' and press
	  RETURN (or just press	RETURN)	to change to the offered
	  directory.  If the offered spelling is incorrect, enter
	  ``n'', then retype the command line.	In this	example	the
	  sh(C)	response is boldfaced:
 
	       $ cd /usr/spol/uucp
	       cd /usr/spool/uucp?y
	       ok
 
	Input/Output
	  Before a command is executed,	its input and output may be
	  redirected using a special notation interpreted by the
	  shell.  The following	may appear anywhere in a
	  simple-command or may	precede	or follow a command. They are
	  not passed on	to the invoked command;	substitution occurs
	  before word or digit is used:
 
	  <word		Use file word as standard input	(file
			descriptor 0).
 
	  >word		Use file word as standard output (file
			descriptor 1).	If the file does not exist, it
			is created; otherwise, it is truncated to zero
			length.
 
	  >>word	Use file word as standard output.  If the file
			exists,	output is appended to it (by first
			seeking	the end-of-file); otherwise, the file
			is created.
 
	  <<[-]word	The shell input	is read	up to a	line that is
			the same as word, or to	an end-of-file.	 The
			resulting document becomes the standard	input.
			If any character of word is quoted, no
			interpretation is placed upon the characters
			of the document; otherwise, parameter and
			command	substitution occurs, (unescaped)
			\newline is ignored, and \ must	be used	to
			quote the characters \,	$, `, and the first
			character of word.  If - is appended to	<< ,
			all leading tabs are stripped from word	and
			from the document.
 
	  <&digit	The standard input is duplicated from file
			descriptor digit (see dup(S)).	Similarly for
			the standard output using >.
 
 
     Page 7					      (printed 5/7/94)
 
 
     SH(C)		       UNIX System V			 SH(C)
 
 
	  <&-		The standard input is closed.  Similarly for
			the standard output using >.
 
	  If one of the	above is preceded by a digit, the file
	  descriptor created is	that specified by the digit (instead
	  of the default 0 or 1).  For example:
 
	       ... 2>&1
 
	  creates file descriptor 2 that is a duplicate	of file
	  descriptor 1.
 
	  If a command is followed by &, the default standard input
	  for the command is the empty file /dev/null.	Otherwise, the
	  environment for the execution	of a command contains the file
	  descriptors of the invoking shell as modified	by
	  input/output specifications.
 
	Environment
	  The environment (see environ(M)) is a	list of	name-value
	  pairs	that is	passed to an executed program in the same way
	  as a normal argument list.  The shell	interacts with the
	  environment in several ways.	On invocation, the shell scans
	  the environment and creates a	parameter for each name	found,
	  giving it the	corresponding value.  Executed commands
	  inherit the same environment.	 If the	user modifies the
	  values of these parameters or	creates	new ones, none of
	  these	affect the environment unless the export command is
	  used to bind the shell's parameter to	the environment.  The
	  environment seen by any executed command is composed of any
	  unmodified name-value	pairs originally inherited by the
	  shell, minus any pairs removed by unset, plus	any
	  modifications	or additions, all of which must	be noted in
	  export commands.
 
	  The environment for any simple-command may be	augmented by
	  prefixing it with one	or more	assignments to parameters.
	  Thus:
 
	       TERM=450	cmd args
 
	  and
 
	       (export TERM; TERM=450; cmd args)
 
	  are equivalent (as far as the	above execution	of cmd is
	  concerned).
 
	  If the -k flag is set, all keyword arguments are placed in
	  the environment, even	if they	occur after the	command	name.
 
	Signals
 
 
     Page 8					      (printed 5/7/94)
 
 
     SH(C)		       UNIX System V			 SH(C)
 
 
	  The INTERRUPT	and QUIT signals for an	invoked	command	are
	  ignored if the command is followed by	&; otherwise signals
	  have the values inherited by the shell from its parent, with
	  the exception	of signal 11.  See the trap command below.
 
	Execution
	  Each time a command is executed, the above substitutions are
	  carried out.	If the command name does not match a Special
	  Command, but matches the name	of a defined function, the
	  function is executed in the shell process (note how this
	  differs from the execution of	shell procedures). The
	  positional parameters	$1, $2,	... are	set to the arguments
	  of the function. If the command name matches neither a
	  Special Command nor the name of a defined function, a	new
	  process is created and an attempt is made to execute the
	  command via exec(S).
 
	  The shell parameter PATH defines the search path for the
	  directory containing the command.  Alternative directory
	  names	are separated by a colon (:).  The default path	is
	  :/bin:/usr/bin (specifying the current directory, /bin, and
	  /usr/bin, in that order).  Note that the current directory
	  is specified by a null pathname, which can appear
	  immediately after the	equal sign or between the colon
	  delimiters anywhere else in the path list.  If the command
	  name contains	a /, then the search path is not used.
	  Otherwise, each directory in the path	is searched for	an
	  executable file.  If the file	has execute permission but is
	  not an a.out file, it	is assumed to be a file	containing
	  shell	commands.  A subshell (i.e., a separate	process) is
	  spawned to read it.  A parenthesized command is also
	  executed in a	subshell.
 
	  Shell	procedures are often used by users running the csh.
	  However, if the first	character of the procedure is a	#
	  (comment character), csh assumes the procedure is a csh
	  script, and invokes /bin/csh to execute it. Always start sh
	  procedures with some other character if csh users are	to run
	  the procedure	at any time.  This invokes the standard	shell
	  /bin/sh.
 
	  The location in the search path where	a command was found is
	  remembered by	the shell (to help avoid unnecessary execs
	  later).  If the command was found in a relative directory,
	  its location must be re-determined whenever the current
	  directory changes.  The shell	forgets	all remembered
	  locations whenever the PATH variable is changed or the
	  hash -r command is executed (see below).
 
	Special	Commands
	  Input/output redirection is permitted	for these commands:
 
 
     Page 9					      (printed 5/7/94)
 
 
     SH(C)		       UNIX System V			 SH(C)
 
 
	  :    No effect; the command does nothing.  A zero exit code
	       is returned.
 
	  . file
	       Reads and executes commands from	file and returns.  The
	       search path specified by	PATH is	used to	find the
	       directory containing file.
 
	  break	[ n ]
	       Exits from the enclosing	for or while loop, if any.  If
	       n is specified, it breaks n levels.
 
	  continue [ n ]
	       Resumes the next	iteration of the enclosing for or
	       while loop.  If n is specified, it resumes at the n-th
	       enclosing loop.
 
	  cd [ arg ]
	       Changes the current directory to	arg.  The shell
	       parameter HOME is the default arg.  The shell parameter
	       CDPATH defines the search path for the directory
	       containing arg.	Alternative directory names are
	       separated by a colon (:).  The default path is <null>
	       (specifying the current directory).  Note that the
	       current directory is specified by a null	path name,
	       which can appear	immediately after the equal sign or
	       between the colon delimiters anywhere else in the path
	       list.  If arg begins with a /, the search path is not
	       used.  Otherwise, each directory	in the path is
	       searched	for arg.
 
	  If the shell is reading its commands from a terminal,	and
	  the specified	directory does not exist (or some component
	  cannot be searched), spelling	correction is applied to each
	  component of directory, in a search for the ``correct''
	  name.	 The shell then	asks whether or	not to try and change
	  directory to the corrected directory name; an	answer of n
	  means	``no'',	and anything else is taken as ``yes''.
 
	  echo [ arg ]
	       Writes arguments	separated by blanks and	terminated by
	       a newline on the	standard output.  Arguments may	be
	       enclosed	in quotes.  Quotes are required	so that	the
	       shell correctly interprets these	special	escape
	       sequences:
 
	    \b	 Backspace
	    \c	 Prints	line without newline.
	    \f	 Form feed
	    \n	 Newline
	    \r	 Carriage return
	    \t	 Tab
 
 
       Page 10						(printed 5/7/94)
 
 
       SH(C)			 UNIX System V			   SH(C)
 
 
	    \v	 Vertical tab
	    \\	 Backslash
	    \n	 The 8-bit character whose ASCII code is the 1,	2 or 3-
	      digit octal number n must	start with a zero
	 eval [	arg ...	]
	      The arguments are	read as	input to the shell and the
	      resulting	command(s) executed.
	 exec [	arg ...	]
	      The command specified by the arguments is	executed in
	      place of this shell without creating a new process.
	      Input/output arguments may appear	and, if	no other
	      arguments	are given, cause the shell input/output	to be
	      modified.
	 exit [	n ]
	      Causes a shell to	exit with the exit status specified
	      by n.  If	n is omitted, the exit status is that of the
	      last command executed.  An end-of-file will also cause
	      the shell	to exit.
	 export	[ name ... ]
	      The given	names are marked for automatic export to the
	      environment of subsequently executed commands.  If no
	      arguments	are given, a list of all names that are
	      exported in this shell is	printed.
	 hash [	-r ] [ name ...	]
	      For each name, the location in the search	path of	the
	      command specified	by name	is determined and remembered
	      by the shell.  The -r option causes the shell to forget
	      all remembered locations.	 If no arguments are given,
	      information about	remembered commands is presented.
	      Hits is the number of times a command has	been invoked
	      by the shell process.  Cost is a measure of the work
	      required to locate a command in the search path.	There
	      are certain situations which require that	the stored
	      location of a command be recalculated.  Commands for
	      which this will be done are indicated by an asterisk
	      (*) adjacent to the hits information.  Cost will be
	      incremented when the recalculation is done.
	 newgrp	[ arg ... ]
	      Equivalent to exec newgrp	arg ...
	 pwd  Print the	current	working	directory.  See	pwd(C) for
	      usage and	description.
	 read [	name ... ]
	      One line is read from the	standard input and the first
	      word is assigned to the first name, the second word to
	      the second name, etc., with leftover words assigned to
	      the last name.  The return code is 0 unless an
	      end-of-file is encountered.
	 readonly [ name ... ]
	      The given	names are marked readonly and the values of
	      the these	names may not be changed by subsequent
	      assignment.  If no arguments are given, a	list of	all
	      readonly names is	printed.
 
 
    Page 11					     (printed 5/7/94)
 
 
    SH(C)		      UNIX System V			SH(C)
 
 
	 return	[ n ]
	      Causes a function	to exit	with the return	value
	      specified	by n.  If n is omitted,	the return status is
	      that of the last command executed.
	 set [ -eknuvx [ arg ... ] ]
	      -e   If the shell	is noninteractive, exits immediately
		   if a	command	exits with a nonzero exit status.
	      -f   Disables file name generation.
	      -h   Locates and remembers function commands as
		   functions are defined (function commands are
		   normally located when the function is executed).
	      -k   Places all keyword arguments	in the environment
		   for a command, not just those that precede the
		   command name.
	      -n   Reads commands but does not execute them.
	      -u   Treats unset	variables as an	error when
		   substituting.
	      -v   Prints shell	input lines as they are	read.
	      -x   Prints commands and their arguments as they are
		   executed.  Although this flag is passed to
		   subshells, it does not enable tracing in those
		   subshells.
	      --   Does	not change any of the flags; useful in
		   setting $1 to -.
	      Using + rather than - causes these flags to be turned
	      off.  These flags	can also be used upon invocation of
	      the shell.  The current set of flags may be found	in
	      $-.  The remaining arguments are positional parameters
	      and are assigned,	in order, to $1, $2, ...  If no
	      arguments	are given, the values of all names are
	      printed.
	 shift
	      The positional parameters	from $2	...  are renamed $1
	      ...
	 test
	      Evaluates	conditional expressions. See test(C) for
	      usage and	description.
	 times
	      Prints the accumulated user and system times for
	      processes	run from the shell.
	 trap [	arg ] [	n ] ...
	      arg is a command to be read and executed when the	shell
	      receives signal(s) n.  (Note that	arg is scanned once
	      when the trap is set and once when the trap is taken.)
	      Trap commands are	executed in order of signal number.
	      The highest signal number	allowed	is 16.	Any attempt
	      to set a trap on a signal	that was ignored on entry to
	      the current shell	is ineffective.	 An attempt to trap
	      on signal	11 (memory fault) produces an error.  If arg
	      is absent, all trap(s) n are reset to their original
	      values.  If arg is the null string, this signal is
	      ignored by the shell and by the commands it invokes.
 
 
    Page 12					     (printed 5/7/94)
 
 
    SH(C)		      UNIX System V			SH(C)
 
 
	      If n is 0, the command arg is executed on	exit from the
	      shell.  The trap command with no arguments prints	a
	      list of commands associated with each signal number.
	 type [	name ... ]
	      For each name, indicate how it would be interpreted if
	      used as a	command	name.
	 ulimit	[ [ -f ] n ]
	      imposes a	size limit of n	blocks on files.
	      -f   imposes a size limit	of n blocks on files written
		   by child processes (files of	any size may be
		   read). Any user may decrease	the file size limit,
		   but only the	super-user (root) can increase the
		   limit.  With	no argument, the current limit is
		   printed.
	      assumed.
	      If no option is given and	a number is specified, -f is
	 unset [ name ... ]
	      For each name, remove the	corresponding variable or
	      function.	 The variables PATH, PS1, PS2, MAILCHECK and
	      IFS cannot be unset.
	 umask [ ooo ]
	      The user file-creation mask is set to the	octal number
	      ooo where	o is an	octal digit (see umask(C)).  If	ooo
	      is omitted, the current value of the mask	is printed.
	 wait [	n ]
	      Waits for	the specified process to terminate, and
	      reports the termination status.  If n is not given, all
	      currently	active child processes are waited for.	The
	      return code from this command is always 0.
       Invocation
	 If the	shell is invoked through exec(S) and the first
	 character of argument 0 is -, commands	are initially read
	 from /etc/profile and then from $HOME/.profile, if such
	 files exist.  Thereafter, commands are	read as	described
	 below,	which is also the case when the	shell is invoked as
	 /bin/sh.  The flags below are interpreted by the shell	on
	 invocation only; note that unless the -c or -s	flag is
	 specified, the	first argument is assumed to be	the name of a
	 file containing commands, and the remaining arguments are
	 passed	as positional parameters to that command file:
	 -c string If the -c flag is present, commands are read	from
		   string.
	 -s	   If the -s flag is present or	if no arguments
		   remain, commands are	read from the standard input.
		   Any remaining arguments specify the positional
		   parameters.	Shell output is	written	to file
		   descriptor 2.
	 -t	   If the -t flag is present, a	single command is
		   read	and executed, and the shell exits.  This flag
		   is intended for use by C programs only and is not
		   useful interactively.
	 -i	   If the -i flag is present or	if the shell input
 
 
    Page 13					     (printed 5/7/94)
 
 
    SH(C)		      UNIX System V			SH(C)
 
 
		   and output are attached to a	terminal, this shell
		   is interactive.  In this case, TERMINATE is
		   ignored (so that kill 0 does	not kill an
		   interactive shell) and INTERRUPT is caught and
		   ignored (so that wait is interruptible).  In	all
		   cases, QUIT is ignored by the shell.
	 -r	   If the -r flag is present, the shell	is a
		   restricted shell (see rsh(C)).
 
	 The remaining flags and arguments are described under the
	 set command above.
 
    Exit Status
	 Errors	detected by the	shell, such as syntax errors, cause
	 the shell to return a nonzero exit status.  If	the shell is
	 being used noninteractively, execution	of the shell file is
	 abandoned.  Otherwise,	the shell returns the exit status of
	 the last command executed. See	the exit command above.
 
    Files
	 /etc/profile	  system default profile if none is present
	 $HOME/.profile	  read by login	shell at login
	 /tmp/sh*	  temporary file for <<
	 /dev/null	  source of empty file
 
    See	Also
	 cd(C),	env(C),	login(M), newgrp(C), rsh(C), test(C),
	 umask(C), dup(S), exec(S), fork(S), pipe(S), signal(S),
	 umask(S), wait(S), a.out(F), profile(M), environ(M)
 
    Notes
	 The command readonly (without arguments) produces the same
	 output	as the command export.
 
	 If << is used to provide standard input to an asynchronous
	 process invoked by &, the shell gets mixed up about naming
	 the input document; a garbage file /tmp/sh* is	created	and
	 the shell complains about not being able to find that file
	 by another name.
 
	 If a command is executed, and a command with the same name
	 is installed in a directory in	the search path	before the
	 directory where the original command was found, the shell
	 will continue to exec the original command.  Use the hash
	 command to correct this situation.
 
	 If you	move the current directory or one above	it, pwd	may
	 not give the correct response.	 Use the cd command with a
	 full path name	to correct this	situation.
 
	 When a	sh(C) user logs	in, the	system reads and executes
	 commands in /etc/profile before executing commands in the
 
 
    Page 14					     (printed 5/7/94)
 
 
    SH(C)		      UNIX System V			SH(C)
 
 
	 user's	$HOME/.profile.	 You can, therefore, modify the
	 environment for all sh(C) users on the	system by editing
	 /etc/profile.
 
 
    Page 15					     (printed 5/7/94)
 
 
