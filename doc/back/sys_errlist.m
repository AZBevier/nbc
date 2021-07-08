
     NAME
          perror, errno, sys_errlist, sys_nerr - system error messages

     SYNTAX
          void perror (s)
          char *s;

          extern int errno;

          extern char *sys_errlist[ ];

          extern int sys_nerr;

     DESCRIPTION
          Perror produces a message on the standard error output,
          describing the last error encountered during a call to a
          system or library function.  The argument string s is
          printed first, then a colon and a blank, then the message
          and a new-line.  To be of most use, the argument string
          should include the name of the program that incurred the
          error.  The error number is taken from the external variable
          errno, which is set when errors occur but not cleared when
          non-erroneous calls are made.  UNIX compatable errors are
          in the range 1-99, and MPX errors are in the range 100-149.

          To simplify variant formatting of messages, the array of
          message strings sys_errlist is provided; errno can be used
          as an index in this table to get the message string without
          the new-line.  Sys_nerr is the largest message number
          provided for in the table; it should be checked because new
          error codes may be added to the system before they are added
          to the table.

     SEE ALSO
          <errno.h>

          (printed 07/29/92)

