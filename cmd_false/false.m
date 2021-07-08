 
 
     FALSE(C)		       UNIX System V		      FALSE(C)
 
 
     Name
	  false	- Returns with a nonzero exit value.
 
     Syntax
	  false
 
     Description
	  false	does nothing except return with	a nonzero exit value.
	  true(C), false's counterpart,	does nothing except return
	  with a zero exit value.  ``False'' is	typically used in
	  shell	procedures such	as:
 
	       until false
	       do
		    command
	       done
 
     See Also
	  sh(C), true(C)
 
     Diagnostics
	  false	is any non-zero	value.
 
 
     Page 1					      (printed 5/7/94)
 
 
