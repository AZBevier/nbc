 
 
     SUM(C)		       UNIX System V			SUM(C)
 
 
     Name
	  sum -	Calculates checksum and	counts blocks in a file.
 
     Syntax
	  sum [	-r ] file
 
     Description
	  sum calculates and prints a 16-bit checksum for the named
	  file,	and also prints	the number of BSIZE blocks in the
	  file.	 It is typically used to look for bad spots, or	to
	  validate a file communicated over a transmission line.  The
	  option -r causes an alternate	algorithm to be	used in
	  computing the	checksum.
 
     See Also
	  cmchk(C), machine(M),	wc(C)
 
     Diagnostics
	  ``Read error'' is indistinguishable from end-of-file on most
	  devices; check the block count.
 
     Notes
	  Refer	to machine(M) or use the cmchk (C) utility to
	  determine BSIZE for your system.
 
 
     Page 1					      (printed 5/7/94)
 
 
