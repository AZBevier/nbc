  �@        3     CHGRP(C)		       UNIX System V		      CHGRP(C) 3       	     Name 	 	  chgrp	- Changes group	ID.          Syntax  	  chgrp	group file ...          Description  ?	  chgrp	changes	the group ID of	each file to group.  The group ? <	  may be either	a decimal group	ID or a	group name found in < 	  the file /etc/group.     
     Files 
 	  /etc/passwd     	  /etc/group          See Also  *	  chown(C), chown(S), passwd(F), group(F) *    
     Notes 
 >	  Only the owner or the	super-user can change the group	ID of > 
	  a file. 
       &     Page 1					      (printed 5/2/94) &      � �                                                                                                                            @       if(cp == buf && (*path == '@' || *path == '^' || *path == '(')) { E 
    } else 
 #endif      	    *cp++ = '/';  -    	    while(*path != '/' && *path != '\0') -     		*cp++ = *path++;      	}      }      *cp++ = '\0';  }     
#ifdef mpx 
 3/* convert unix or mpx filename to unix filename */ 3 A/* .'s and multiple /'s will have been removed by crunch above */ A 9/* first char must be /, ., @, ^, or ( to be converted */ 9 =/* NOTE: string supplied must be big enough for conversion */ =    static void  conv2unix(s)  register char *s;  {      register char *os = s;      char *tp;     !    if (s == 0 || *s == 0)return; !     	switch (*os) {  6    	    case '/':		/* path starts with /, leave it */ 6                   