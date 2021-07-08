 
 
     TRUE(C)		       UNIX System V		       TRUE(C)
 
 
     Name
	  true - Returns with a	zero exit value.
 
     Syntax
	  true
 
     Description
	  true does nothing except return with a zero exit value.
	  false(C), true's counterpart,	does nothing except return
	  with a nonzero exit value.  true is typically	used in	shell
	  procedures such as:
 
	       while true
	       do
		    command
	       done
 
     See Also
	  sh(C), false (C)
 
     Diagnostics
	  true has exit	status zero.
 
 
     Page 1					      (printed 5/7/94)
 
 
