
     NAME
          utime - set file access and modification times.

     SYNTAX
          #include <sys/types.h>
          int utime (path, times)
          char *path;
          struct utimbuf *times;

     DESCRIPTION
          Path points to a pathname naming a file.  Utime sets the
          access and modification times of the named file.

          If times is NULL, the access and modification times of the
          file are set to the current time.  A process must be the
          owner of the file or have write permission to use utime in
          this manner.

          If times is not NULL, times is interpreted as a pointer to a
          utimbuf structure and the access and modification times are
          set to the values contained in the designated structure.
          Only the owner of the file or the super-user may use utime
          this way.

          The times in the following structure are measured in seconds
          since 00:00:00 GMT, Jan. 1, 1970.

                struct  utimbuf {
                      time_t actime;    /* access time */
                      time_t modtime;   /* modification time */
                };

          Utime will fail if one or more of the following are true:

                The named file does not exist.  [ENOENT]

                A component of the path prefix is not a directory.
                [ENOTDIR]

                Search permission is denied by a component of the path
                prefix. [EACCES]

                The user is not super-user (system) or not the
                owner of the file and times is not NULL.  [EPERM]

                The user is not super-user (system) or not the
                owner of the file and times is NULL and write access is
                denied. [EACCES]

                Times is not NULL and points outside the process'
                allocated address space.  [EFAULT]

                Path points outside the process' allocated address
                space.  [EFAULT]

     SEE ALSO
          stat.m

     RETURN VALUE
          Upon successful completion, a value of 0 is returned.
          Otherwise, a value of -1 is returned and errno is set to
          indicate the error.

          (printed 05/31/94 - J B Systems)

