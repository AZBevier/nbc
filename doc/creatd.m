
     NAME
          creatd, mkdir - create a new directory

     SYNTAX
          int creatd (path, mode)
          char *path;
          int mode;

          int mkdir (path, mode)
          char *path;
          int mode;

     DESCRIPTION
          Creatd creates a new directory with the specified access
          mode named by the path name pointed to by path.

          The directory is created with the existing defaults for size
          (See setsiz.m) and access rights (See setacc.m).

          Upon successful completion, a zero is returned. A new
          directory can be created with a mode that forbids writing.

          Creatd will fail if one or more of the following are true:

          [ENOTDIR]      A component of the path prefix is not a
                         directory.

          [ENOENT]       A component of the path prefix does not
                         exist.

          [EACCES]       Search permission is denied on a component of
                         the path prefix.

          [ENOENT]       The path name is null.

          [EISDIR]       The named directory is an existing directory.

          [EFAULT]       Path points outside the allocated address
                         space of the process.

     RETURN VALUE
          Upon successful completion, a zero is returned.  Otherwise,
          a value of -1 is returned and errno is set to indicate the error.

     SEE ALSO
          chmod.m, close.m, lseek.m, open.m, read.m, write.m, setacc.m,
          setsiz.m

     SPECIAL CONSIDERATIONS
          This service does nothing on MPX 1.X systems.

          (printed 07/30/92 - J B Systems)

