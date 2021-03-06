 
 
     DATE		       MAKE4MPX		       DATE(C)
 
 
     Name
	  date - Prints	the date.
 
     Syntax
	  date [ mmddhhmm[yy] ]	[ +format ]
 
     Description
	  If no	argument is given, or if the argument begins with +,
	  the current date and time are	printed.  Otherwise, the
	  current date is set.	The first mm is	the month number; dd
	  is the day number in the month; hh is	the hour number	(24-
	  hour system);	the second mm is the minute number; yy is the
	  last 2 digits	of the year number and is optional.  For
	  example:
 
	       date 10080045
 
	  sets the date	to Oct 8, 12:45	AM.  The current year is the
	  default if no	year is	mentioned.  The	system operates	in
	  GMT.	date takes care	of the conversion to and from local
	  standard and daylight	time.
 
	  If the argument begins with +, the output of date is under
	  the control of the user.  The	format for the output is
	  similar to that of the first argument	to printf(S).  All
	  output fields	are of fixed size (zero	padded if necessary).
	  Each field descriptor	is preceded by a percent sign (%) and
	  will be replaced in the output by its	corresponding value.
	  A single percent sign	is encoded by doubling the percent
	  sign,	i.e., by specifying ``%%''.  All other characters are
	  copied to the	output without change.	The string is always
	  terminated with a newline character.
 
	  Field	Descriptors:
 
	  n   Inserts a	newline	character
 
	  t   Inserts a	tab character
 
	  m   Month of year - 01 to 12
 
	  d   Day of month - 01	to 31
 
	  y   Last 2 digits of year - 00 to 99
 
	  D   Date as mm/dd/yy
 
	  H   Hour - 00	to 23
 
	  M   Minute - 00 to 59
 
	  S   Second - 00 to 59
 
 
     Page 1					     (printed 4/29/94)
 
 
     DATE(C)		       UNIX System V		       DATE(C)
 
 
	  T   Time as HH:MM:SS
 
	  j   Julian date - 001	to 366
 
	  w   Day of the week -	Sunday = 0
 
	  a   Abbreviated weekday - Sun	to Sat
 
	  h   Abbreviated month	- Jan to Dec
 
	  r   Time in AM/PM notation
 
     Example
	  The line
 
	       date '+DATE: %m/%d/%y%nTIME: %H:%M:%S'
 
	  generates as output:
 
	       DATE: 08/01/76
	       TIME: 14:45:05
 
     Diagnostics
	  no permission		 You aren't the	super-user and you are
				 trying	to change the date.
 
 
	  bad conversion	 The date set is syntactically
				 incorrect.
 
 
	  bad format character	 The field descriptor is not
				 recognizable.
 
 
     Page 2					     (printed 4/29/94)
 
 
