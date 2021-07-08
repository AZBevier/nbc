 
 
     AR(CP)		       MAKE4MPX				AR(CP)
 
 
     Name
	  ar - Maintains MPX libraries.
 
     Syntax
	  ar -key afile names ...
 
     Description
	  ar maintains groups of files combined	into a single format
	  archive file.	 Its main use is to create and update library
	  files	as used	by the Cataloger though it can be used for
	  any similar purpose.
 
	  key is one character from the	set [drtx], optionally
	  concatenated with one	or more	of [vucn].  afile is the
	  prefix of the archive files as [prefix]lib and [prefix]dir.
    	  The names are constituent files in the archive file.	These
    	  files must be object files.  The meanings of the key characters
    	  are:
 
	  d    Deletes the named files from the	archive	file.
 
	  r    Replaces	the named files	in the archive file.  If the
	       optional	character u is used with r, then only those
	       files with modified dates later than the	archive	files
	       are replaced. New files are placed at the end.
 
	  t    Prints a	table of contents of the archive file.	If no
	       names are given,	all files in the archive are tabled.
	       If names	are given, only	those files are	tabled.
 
	  x    Extracts	the named files to the current directory.  If
    	       no names are given, all files in	the archive are	extracted.
    	       Unless the optional character n is used with x, an extracted
	       file's modification date	will be	set to the date	stored in
    	       that file's archive header.  In neither case does x alter
  	       the archive file.
 
	  v    Verbose.	 Under the verbose option, ar gives a file-
	       by-file description of the making of a new archive file
	       from the	old archive and	the constituent	files.	When
	       used with t, it gives a long listing of all information
	       about the files.	 When used with	x, it precedes each
	       file with a name.
 
	  c    Create.	Normally ar will create	afile when it needs
	       to.  The	create option suppresses the normal message
	       that is produced	when afile is created.
 
	  n    New. When used with the key character x it sets the
	       extracted file's	modification date to the current date.
 
     Notes
	  If the same file is mentioned	twice in an argument list, it
	  may be put in	the archive twice.
 
    	  printed (4/29/94)
