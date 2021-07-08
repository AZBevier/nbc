 
 
     CP		       MAKE4MPX				 CP(C)
 
 
     Name
	  cp - Copies files.
 
     Syntax
	  cp file1 file2
 
	  cp files directory
 
     Description
	  There	are two	ways to	use the	cp command.  With the first
	  way, file1 is	copied to file2.  Under	no circumstance	can
	  file1	and file2 be identical.	 With the second way,
	  directory is the location of a directory into	which one or
	  more files are copied.  The specified file type and size
    	  are tested and the destination file size and are set to
    	  match the input file.
 
     See Also
	  ln, mv, rm, mvdir
 
     Notes
	  It is illegal to copy a directory to a file.
    	  If the destination file is present, it is copied
    	  unconditionally to the specified file.  If the file
    	  is a load module, which is non extendable, and the
    	  source file is larger than the destination file, the
    	  file will not be copied.  Also the destination file
    	  will maintain its file type.
 
     (printed 4/29/94)
 
 
