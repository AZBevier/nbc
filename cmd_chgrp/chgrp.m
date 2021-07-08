 
 
     CHGRP(C)		       UNIX System V		      CHGRP(C)
 
 
     Name
	  chgrp	- Changes group	ID.
 
     Syntax
	  chgrp	group file ...
 
     Description
	  chgrp	changes	the group ID of	each file to group.  The group
	  may be either	a decimal group	ID or a	group name found in
	  the file /etc/group.
 
     Files
	  /etc/passwd
 
	  /etc/group
 
     See Also
	  chown(C), chown(S), passwd(F), group(F)
 
     Notes
	  Only the owner or the	super-user can change the group	ID of
	  a file.
 
 
     Page 1					      (printed 5/2/94)
 
 
