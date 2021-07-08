 
 
     MVDIR(ADM)		       UNIX System V		    MVDIR(ADM)
 
 
     Name
	  mvdir	- Moves	a directory.
 
     Syntax
	  /etc/mvdir dirname name
 
     Description
	  mvdir	moves directories within a file	system.	 The directory
	  ( dirname) must be a directory.  If there is already a
	  directory or file with the same name as name,	mvdir fails.
 
	  Neither name may be a	sub-set	of the other.  For example,
	  you cannot move a directory named /x/y to /x/y/z, and	vice
	  versa.
 
     Notes
	  You must be root to use mvdir.
 
     See Also
	  mkdir(C)
 
 
     Page 1					     (printed 4/20/92)
 
 
