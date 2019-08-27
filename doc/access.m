
     NAME
          access - determine accessibility of a file

     SYNTAX
          int access (path, amode)
          char *path;
          int amode;

     DESCRIPTION
          Path points to a path name naming a file.  Access checks the
          named file for accessibility according to the bit pattern
          contained in amode, or checks the named file for existence.
          An amode value other than zero is ignored on MPX and always
          return a valid access.

          The constants for the argument amode are defined as follows:

               Value     Description
               4         test for read permission
               2         test for write permission
               1         test for execute (search) permission
               0         test for existence of file

          The argument amode is either the logical OR of one or more
          of the values or is the value of zero.

          Access to the file is denied if one or more of the following
          are true: 
              [ENOTDIR] A component of the path prefix is not a directory.
              [ENOENT]  Read, write, or execute (search) permission is
                        requested for a null path name.
              [ENOENT]  The named file does not exist.
              [ENOENT]  The path name is longer than PATH_MAX
                        characters.
              [EACCES]  Search permission is denied on a component
                        of the path prefix.
              [EACCESS] Permission bits of the file mode do not permit
                        the requested access.
              [EFAULT]  Path points outside the allocated address
                        space for the process.

          When checking for accessibility, the owner of a file has
          permission checked with respect to the ``owner'' read,
          write, and execute mode bits.  Members of the file's group
          other than the owner have permissions checked with respect
          to the ``group'' mode bits, and all others have permissions
          checked with respect to the ``other'' mode bits.

     RETURN VALUE
          If the requested access is permitted, a value of 0 is
          returned.  This is always the case on MPX.  Otherwise, a
          value of -1 is returned and errno is set to indicate the error.

     SEE ALSO
          chmod.m, stat.m

          (printed 07/30/92 - J B Systems)

