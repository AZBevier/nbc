 
 
     MKDIR(C)		       UNIX System V		      MKDIR(C)
 
 
     Name
	  mkdir	- Makes	a directory.
 
     Syntax
	  mkdir	dirname	...
 
     Description
	  mkdir	creates	directories.  The standard entries ``dot''
	  (.), for the directory itself, and ``dot dot'' (..), for its
	  parent, are made automatically.
 
	  mkdir	requires write permission in the parent	directory.
	  The permissions assigned to the new directory	are modified
	  by the current file creation mask set	by umask(C).
 
     See Also
	  rmdir(C), umask(C)
 
     Diagnostics
	  mkdir	returns	exit code 0 if all directories were
	  successfully made; otherwise,	it prints a diagnostic and
	  returns nonzero.
 
 
     Page 1					      (printed 5/7/94)
 
 
See also mkdir(DOS)
See also mkdir(S)
