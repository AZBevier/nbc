 
 
     ECHO		       MAKE4MPX		       ECHO(C)
 
 
     Name
	  echo - Echoes	arguments.
 
     Syntax
	  echo [ arg ] ...
	  /system/bin/echo [ arg ] ...
 
     Description
	  echo writes its arguments separated by blanks	and terminated
	  by a newline on the standard output.	echo also understands
	  C-like escape	conventions.  The following escape sequences
	  need to be quoted so that the	shell interprets them
	  correctly:
	  \b   Backspace
	  \c   Prints line without newline
	  \f   Form feed
	  \n   Newline
	  \r   Carriage	return
	  \t   Tab
	  \v   Vertical	tab
	  \\   Backslash
	  \n   The 8-bit character whose ASCII code is a 1, 2 or 3-
	       digit octal number.  In all cases, n must start with a
	       zero.  For example:
 
		    echo "\07"	   - Echoes Ctl-G.
		    echo "\007"	   - Also echoes Ctl-G.
		    echo "\065"	   - Echoes the	number ``5''.
		    echo "\0065"   - Also echoes the number ``5''.
		    echo "\0101"   - Echoes the	letter ``A''.
 
	  echo is useful for producing diagnostics in command files
	  and for sending known	data into a file.
 
     See Also
	  sh
 
     Notes
	  The sh has a built-in echo utility which has a different
	  syntax than this echo.  Be aware that	users running under
	  sh will get the built-in echo unless they specify
          /system/bin/echo.
 
 
     (printed 4/29/94)
 
