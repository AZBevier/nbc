 
 
     UNIQ(C)		       UNIX System V		       UNIQ(C)
 
 
     Name
	  uniq - Reports repeated lines	in a file.
 
     Syntax
	  uniq [ -udc [	+n ] [ -n ] ] [	input [	output ] ]
 
     Description
	  uniq reads the input file and	compares adjacent lines.  In
	  the normal case, the second and succeeding copies of
	  repeated lines are removed; the remainder is written on the
	  output file.	Input and output should	always be different.
	  Note that repeated lines must	be adjacent in order to	be
	  found; see sort(C).  If the -u flag is used, just the	lines
	  that are not repeated	in the original	file are output.  The
	  -d option specifies that one copy of just the	repeated lines
	  is to	be written.  The normal	mode output is the union of
	  the -u and -d	mode outputs.
 
	  The -c option	supersedes -u and -d and generates an output
	  report in default style but with each	line preceded by a
	  count	of the number of times it occurred.
 
	  The n	arguments specify skipping an initial portion of each
	  line in the comparison:
 
	  -n	  The first n fields together with any blanks before
		  each are ignored.  A field is	defined	as a string of
		  nonspace, nontab characters separated	by tabs	and
		  spaces from its neighbors.
 
	  +n	  The first n characters are ignored.  Fields are
		  skipped before characters.
 
     See Also
	  comm(C), sort(C)
 
 
     Page 1					      (printed 5/7/94)
 
 
