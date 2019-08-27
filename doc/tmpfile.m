
     NAME
          tmpfile - create a temporary file

     SYNTAX
          #include <stdio.h>

          FILE *tmpfile ()

     DESCRIPTION
          Tmpfile creates a temporary file using the MPX system
          service, and returns a corresponding FILE pointer.  If
          the file cannot be opened, an error message is printed using
          perror(), and a NULL pointer is returned.  The file will
          automatically be deleted when the process using it
          terminates.  The file is opened for update ("w+").
          The file will default to an MPX blocked file.

     SEE ALSO
          creat.m, unlink.m, fopen.m, mktemp.m, perror.m, tmpnam.m

          (printed 07/30/92 - J B Systems)

