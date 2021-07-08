 
 
     MV(C)		       UNIX System V			 MV(C)
 
 
     Name
	  mv  -	 Moves or renames files	and directories.
 
     Syntax
	  mv [ -f ] file1 file2
 
	  mv [ -f ] file ... directory
 
     Description
	  mv moves (changes the	name of) file1 to file2.
 
	  If file2 already exists, it is removed before	file1 is
	  moved.  If file2 has a mode which forbids writing, mv	prints
	  the mode (see	chmod(S)) and reads the	standard input to
	  obtain a line.  If the line begins with y, the move takes
	  place; if not, mv exits.
 
	  In the second	form, one or more files	are moved to the
	  directory with their original	filenames.
 
	  No questions are asked when the -f option is given.
 
	  mv refuses to	move a file onto itself.
 
	  mv can only rename directories, not physically move them.
	  mvdir(ADM) should be used to move directories	within a
	  filesystem.
 
     See Also
	  cp(C), chmod(S), copy(C)
 
     Notes
	  If file1 and file2 lie on different file systems, mv must
	  copy the file	and delete the original.  In this case the
	  owner	name becomes that of the copying process and any
	  linking relationship with other files	is lost.
 
 
     Page 1					      (printed 5/7/94)
 
 
