 
 
     CHOWN(C)		       UNIX System V		      CHOWN(C)
 
 
     Name
	  chown	- Changes owner	ID.
 
     Syntax
	  chown	owner file ...
 
     Description
	  chown	changes	the owner ID of	the files to owner.  The owner
	  may be either	a decimal user ID or a login name found	in the
	  file /etc/passwd.
 
     Files
	  /etc/passwd
 
	  /etc/group
 
     See Also
	  chgrp(C), chown(S), group(F),	passwd(F)
 
     Notes
	  Only the owner or the	super-user can change a	file's owner
	  or group ID.
 
 
     Page 1					      (printed 5/2/94)
 
 
See also chown(S)
