 
 
     SED(C)		       UNIX System V			SED(C)
 
 
     Name
	  sed -	Invokes	the stream editor.
 
     Syntax
	  sed [	-n ] [ -e script ] [ -f	sfile ]	[ files	]
 
     Description
	  sed copies the named files (standard input default) to the
	  standard output, edited according to a script	of commands.
	  The -f option	causes the script to be	taken from file	sfile;
	  these	options	accumulate.  If	there is just one -e option
	  and no -f options, the flag -e may be	omitted.  The -n
	  option suppresses the	default	output.	 A script consists of
	  editing commands, one	per line, of the following form:
 
	       [ address [ , address ] ] function [ arguments ]
 
	  In normal operation, sed cyclically copies a line of input
	  into a pattern space (unless there is	something left after a
	  D command), applies in sequence all commands whose addresses
	  select that pattern space, and at the	end of the script
	  copies the pattern space to the standard output (except
	  under	-n) and	deletes	the pattern space.
 
	  A semicolon (;) can be used as a command delimiter.
 
	  Some of the commands use a hold space	to save	all or part of
	  the pattern space for	subsequent retrieval.
 
	  An address is	either a decimal number	that counts input
	  lines	cumulatively across files, a $ that addresses the last
	  line of input, or a context address, i.e., a /regular
	  expression/ in the style of ed(C) modified as	follows:
 
	  -    In a context address, the construction \?regular
	       expression?, where ?  is	any character, is identical to
	       /regular	expression/.  Note that	in the context address
	       \xabc\xdefx, the	second x stands	for itself, so that
	       the regular expression is abcxdef.
 
	  -    The escape sequence \n matches a	newline	embedded in
	       the pattern space.
 
	  -    A period	. matches any character	except the terminal
	       newline of the pattern space.
 
	  -    A command line with no addresses	selects	every pattern
	       space.
 
	  -    A command line with one address selects each pattern
	       space that matches the address.
 
 
     Page 1					      (printed 5/7/94)
 
 
     SED(C)		       UNIX System V			SED(C)
 
 
	  -    A command line with two addresses selects the inclusive
	       range from the first pattern space that matches the
	       first address through the next pattern space that
	       matches the second.  (If	the second address is a	number
	       less than or equal to the line number first selected,
	       only one	line is	selected.)  Thereafter,	the process is
	       repeated, looking again for the first address.
 
	  Editing commands can be applied only to nonselected pattern
	  spaces by use	of the negation	function ! (below).
 
	  In the following list	of functions, the maximum number of
	  permissible addresses	for each function is indicated in
	  parentheses.
 
	  The text argument consists of	one or more lines, all but the
	  last of which	end with backslashes to	hide the newlines.
	  Backslashes in text are treated like backslashes in the
	  replacement string of	an s command, and may be used to
	  protect initial blanks and tabs against the stripping	that
	  is done on every script line.	 The rfile or wfile argument
	  must terminate the command line and must be preceded by
	  exactly one blank.  Each wfile is created before processing
	  begins.  There can be	at most	10 distinct wfile arguments.
 
	  (1)a\
	  text	    Appends text, placing it on	the output before
		    reading the	next input line.
 
	  (2)b label
		    Branches to	the : command bearing the label.  If
		    label is empty, branches to	the end	of the script.
 
	  (2)c\
	  text	    Changes text by deleting the pattern space and
		    then appending text. With 0	or 1 address or	at the
		    end	of a 2-address range, places text on the
		    output and starts the next cycle.
 
	  (2)d	    Deletes the	pattern	space and starts the next
		    cycle.
 
	  (2)D	    Deletes the	initial	segment	of the pattern space
		    through the	first newline and starts the next
		    cycle.
 
	  (2)g	    Replaces the contents of the pattern space with
		    the	contents of the	hold space.
 
	  (2)G	    Appends the	contents of the	hold space to the
		    pattern space.
 
 
     Page 2					      (printed 5/7/94)
 
 
     SED(C)		       UNIX System V			SED(C)
 
 
	  (2)h	    Replaces the contents of the hold space with the
		    contents of	the pattern space.
 
	  (2)H	    Appends the	contents of the	pattern	space to the
		    hold space.
 
	  (1)i\
	  text	    Insert.  Places text on the	standard output.
 
	  (2)l	    Lists the pattern space on the standard output
		    with nonprinting characters	spelled	in two-digit
		    ASCII and long lines folded.
 
	  (2)n	    Copies the pattern space to	the standard output.
		    Replaces the pattern space with the	next line of
		    input.
 
	  (2)N	    Appends the	next line of input to the pattern
		    space with an embedded newline.  (The current line
		    number changes.)
 
	  (2)p	    Prints (copies) the	pattern	space on the standard
		    output.
 
	  (2)P	    Prints (copies) the	initial	segment	of the pattern
		    space through the first newline to the standard
		    output.
 
	  (1)q	    Quits sed by branching to the end of the script.
		    No new cycle is started.
 
	  (2)r rfile
		    Reads the contents of rfile	and places them	on the
		    output before reading the next input line.
 
	  (2)s/regular expression/replacement/flags
		    Substitutes	the replacement	string for instances
		    of the regular expression in the pattern space.
		    Any	character may be used instead of /.  For a
		    more detailed description, see ed(C).  Flags is
		    zero or more of:
 
		    n	 n=1-512.  Substitute for just the nth
			 occurrence of the regular expression.
 
		    g	 Globally substitutes for all nonoverlapping
			 instances of the regular expression rather
			 than just the first one.
 
		    p	 Prints	the pattern space if a replacement was
			 made.
 
 
     Page 3					      (printed 5/7/94)
 
 
     SED(C)		       UNIX System V			SED(C)
 
 
		    w wfile
			 Writes	the pattern space to wfile if a
			 replacement was made.
 
	  (2)t label
		    Branches to	the colon (:) command bearing label if
		    any	substitutions have been	made since the most
		    recent reading of an input line or execution of a
		    t command.	If label is empty, t branches to the
		    end	of the script.
 
	  (2)w wfile
		    Writes the pattern space to	wfile.
 
	  (2)x	    Exchanges the contents of the pattern and hold
		    spaces.
 
	  (2)y/string1/string2/
		    Replaces all occurrences of	characters in string1
		    with the corresponding characters in string2.  The
		    lengths of string1 and string2 must	be equal.
 
	  (2)! function
		    Applies the	function (or group, if function	is {)
		    only to lines not selected by the address(es).
 
	  (0): label
		    This command does nothing; it bears	a label	for b
		    and	t commands to branch to.
 
	  (1)=	    Places the current line number on the standard
		    output as a	line.
 
	  (2){	    Executes the following commands through a matching
		    } only when	the pattern space is selected.
 
	  (0)	    An empty command is	ignored.
 
     See Also
	  awk(C), ed(C), grep(C)
 
     Notes
	  This command is explained in detail in XENIX Text Processing
	  Guide.
 
 
     Page 4					      (printed 5/7/94)
 
 
