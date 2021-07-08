 
 
     BASENAME(C)	       MAKE4MPX			   BASENAME(C)
 
 
     Name
	  basename - Removes directory names from pathnames.
 
     Syntax
	  basename string [ suffix ]
 
     Description
	  basename deletes any prefix ending in	/ and the suffix (if
	  present in string) from string, and prints the result	on the
	  standard output.  The	result is the ``base'' name of the
	  file,	i.e., the filename without any preceding directory
	  path and without an extension.  It is	used inside
	  substitution marks (``) in shell procedures to construct new
	  filenames.
 
     Examples
	  The following	command	displays the filename memos on the
	  standard output:
 
	       basename	/usr/johnh/memos.old .old
 
          (printed 4/29/94)
 
