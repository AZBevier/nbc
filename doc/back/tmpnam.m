
     NAME
          tmpnam, tempnam - create a name for a temporary file

     SYNTAX
          #include <stdio.h>

          char *tmpnam (s)
          char *s;

          char *tempnam (dir, pfx)
          char *dir, *pfx;

     DESCRIPTION
          These functions generate file names that can safely be used
          for a temporary file.

          Tmpnam always generates a file name using the path-prefix
          defined as P_tmpdir in the <stdio.h> header file.  If s is
          NULL, tmpnam leaves its result in an internal static area
          and returns a pointer to that area.  The next call to tmpnam
          will destroy the contents of the area.  If s is not NULL, it
          is assumed to be the address of an array of at least
          L_tmpnam bytes, where L_tmpnam is a constant defined in
          <stdio.h>; tmpnam places its result in that array and
          returns s.

          Tempnam allows the user to control the choice of a
          directory.  The argument dir points to the name of the
          directory in which the file is to be created.  If dir is
          NULL or points to a string which is not a name for an
          appropriate directory, the path-prefix defined as P_tmpdir
          in the <stdio.h> header file is used.  If that directory is
          not accessible, /tmp will be used as a last resort.  This
          entire sequence can be up-staged by providing an environment
          variable TMPDIR in the user's environment, whose value is
          the name of the desired temporary-file directory.

          Many applications prefer their temporary files to have
          certain initial letter sequences in their names.  Use the
          pfx argument for this.  This argument may be NULL or point
          to a string of up to five characters to be used as the first
          few characters of the temporary-file name.

          Tempnam uses malloc() to get space for the constructed
          file name, and returns a pointer to this area.  Thus, any
          pointer value returned from tempnam may serve as an argument
          to free (refer to malloc.m).  If tempnam cannot return the
          expected result for any reason, i.e.  malloc() failed, or
          none of the above mentioned attempts to find an appropriate
          directory was successful, a NULL pointer will be returned.

     NOTES
          These functions generate a different file name each time
          they are called.

          Files created using these functions and either fopen() or
          creat() are temporary only in the sense that they reside in
          a directory intended for temporary use, and their names are
          unique.  It is the user's responsibility to use unlink() to
          remove the file when its use is ended.

     SEE ALSO
          creat.m, unlink.m, fopen.m, malloc.m, mktemp.m, tmpfile.m

     SPECIAL CONSIDERATIONS
          If called more than 17,576 times in a single process, these
          functions will start recycling previously used names.
          Between the time a file name is created and the file is
          opened, it is possible for some other process to create a
          file with the same name.  This can never happen if that
          other process is using these functions or mktemp, and the
          file names are chosen so as to render duplication by other
          means unlikely.

          (printed 07/30/92 - J B Systems)

