 
 
     CMPRS(CP)	       MAKE4MPX				AR(CP)
 
 
     Name
	  cmprs - Compresses multiple object files into a single file.
 
     Syntax
	  cmprs -I namelist -O ofile names ...
 
     Description
	  Cmprs concatinates multiple object files into a single file.
    	  Its main use is to create a file as used by the Cataloger
    	  for SGO input.
 
	  The -I option is used to specify a file that contains a list of
    	  filenames that are to concatinated.  If not specified, the filename
    	  list is taken from the command line.
 
    	  The -O option specifies an output file to place the concatinated
    	  object files.  If no file is specified, files are written to
    	  stdout.  If the specified file is not present, the file is
    	  created.
 
     Notes
	  If the same file is mentioned	twice in an argument list, it
	  may be put in	the output file twice.
 
    	  printed (4/29/94)
