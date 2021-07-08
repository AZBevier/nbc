
     NAME
          creat - create a new file or rewrite an existing one

     SYNTAX
          int creat (path, mode)
          char *path;
          int mode;

     DESCRIPTION
          Creat creates a new ordinary file or prepares to rewrite an
          existing file named by the path name pointed to by path.

          If the file exists, the length is left unchanged and the
          mode and owner are unchanged.  Otherwise, the file is
          created with the existing defaults for size (See setsiz.m)
          and access rights (See setacc.m).

          Upon successful completion, the file descriptor is returned
          and the file is open for writing, even if the mode does not
          permit writing.  The file pointer is set to the beginning of
          the file.  No process can have more than _NFILES files open
          simultaneously.  A new file can be created with a mode that
          forbids writing.

          Creat will fail if one or more of the following are true:

          [ENOTDIR]      A component of the path prefix is not a
                         directory.

          [ENOENT]       A component of the path prefix does not
                         exist.

          [EACCES]       Search permission is denied on a component of
                         the path prefix.

          [ENOENT]       The path name is null.

          [EACCES]       The file does not exist and the directory in
                         which the file is to be created does not
                         permit writing.

          [EACCES]       The file exists and write permission is
                         denied.

          [EISDIR]       The named file is an existing directory.

          [EMFILE]       _FILES file descriptors are currently open.

          [EFAULT]       Path points outside the allocated address
                         space of the process.

     RETURN VALUE
          Upon successful completion, a non-negative integer, namely
          the file descriptor, is returned.  Otherwise, a value of -1
          is returned and errno is set to indicate the error.

     SEE ALSO
          chmod.m, close.m, lseek.m, open.m, read.m, write.m, setacc.m,
          setsiz.m

          (printed 07/30/92 - J B Systems)

