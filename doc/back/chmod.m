
     NAME
          chmod - change mode of file

     SYNTAX
          int chmod (path, mode)
          char *path;
          int mode;

     DESCRIPTION
          Path points to a pathname naming a file.  It can be either
          MPX or UNIX format.  Chmod sets the access permission portion
          of the named file's mode.  It sets the access permission
          portion according to the bit pattern contained in mode.

          Access permission bits for mode can be formed by adding any
          combination of the following:

               00400 Read by owner
               00200 Write by owner
               00100 Execute (or search if a directory) by owner
               00040 Read by group
               00020 Write by group
               00010 Execute (or search) by group
               00004 Read by others
               00002 Write by others
               00001 Execute (or search) by others

          To change the mode of a file, the caller must be the owner
          of the file or must be super-user (system).

          Chmod will fail and the file mode will be unchanged if one
          or more of the following are true:

               A component of the path prefix is not a directory.
               [ENOTDIR]

               The named file does not exist.  [ENOENT]

               Search permission is denied on a component of the path
               prefix.  [EACCES]

               The caller is not the owner of the file or not super-user
               (system).  [EPERM]

               path points outside the process' allocated address
               space.  [EFAULT]

     RETURN VALUE
          Upon successful completion, a value of 0 is returned.
          Otherwise, a value of -1 is returned and errno is set to
          indicate the error.

     SEE ALSO
          chown.m, setacc.m, getacc.m, access.m, stat.m

          (printed 05/31/94 - J B Systems)

