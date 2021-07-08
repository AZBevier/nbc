
     NAME
          chtype - changes the type of a file.

     SYNTAX
          int chtype (path, type)
          char *path;
          int type;

     DESCRIPTION
          Path points to a pathname naming a file.  It may be an
          MPX or UNIX pathname.  The specified file's type is changed
          to the user specified value.

          Only the file owner or super-user (system) may change the
          filetype of a file.

          Chtype will fail and the filetype will remain unchanged if
          one or more of the following are true:

               A component of the path prefix is not a directory.
               [ENOTDIR]

               The named file does not exist.  [ENOENT]

               Search permission is denied on a component of the path
               prefix. [EACCES]

               The caller is not the owner of the file or super-user
               (system).  [EPERM]

               Path points outside the process' allocated address
               space.  [EFAULT]

     RETURN VALUE
          Upon successful completion, a value of 0 is returned.
          Otherwise, a value of -1 is returned and errno is set to
          indicate the error.

     SEE ALSO
          chmod.m, chown.m, chownm.m

          (printed 05/31/94 - J B Systems)

