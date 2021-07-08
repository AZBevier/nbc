
     NAME
          chdir - change working directory

     SYNTAX
          int chdir (path)
          char *path;

     DESCRIPTION
          Path points to the path name of a directory.  Chdir causes
          the named directory to become the current working directory,
          the starting point for path searches for path names not
          beginning with /.

          Chdir will fail and the current working directory will be
          unchanged if one or more of the following are true:

          [ENOTDIR]      A component of the path name is not a
                         directory.

          [ENOENT]       The named directory does not exist.

          [EACCES]       Search permission is denied for any component
                         of the path name.

          [EFAULT]       Path points outside the allocated address
                         space of the process.

     RETURN VALUE
          Upon successful completion, a value of 0 is returned.
          Otherwise, a value of -1 is returned and errno is set to
          indicate the error.

     SPECIAL CONSIDERATIONS
          Under MPX 1.X the username is changed.  MPX or UNIX pathnames
          are accepted.

          (printed 07/30/92 - J B Systems)

