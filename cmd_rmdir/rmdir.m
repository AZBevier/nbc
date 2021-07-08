 
 
     RMDIR(C)		       UNIX System V		      RMDIR(C)
 
 
     Name
	  rmdir	- Removes directories.
 
     Syntax
	  rmdir	dir ...
 
     Description
	  rmdir	removes	the entries for	one or more subdirectories
	  from a directory.  A directory must be empty before it can
	  be removed.  rmdir enforces a	standard and safe procedure
	  for removing a directory; the	contents of the	directory must
	  be removed before the	directory itself can be	deleted	with
	  rmdir	. Note that the	``rm -r	dir'' command is a more
	  dangerous alternative	to rmdir.
 
     See Also
	  rm(C)
 
     Notes
	  rmdir	will refuse to remove the root directory of a mounted
	  file system.
 
 
     Page 1					      (printed 4/4/94)
 
 
See also rmdir(DOS)
See also rmdir(S)
