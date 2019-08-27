
     NAME
          link - link to a file

     SYNTAX
          int link (path1, path2)
          char *path1, *path2;

     DESCRIPTION
          Path1 points to a pathname naming an existing file.  Path2
          points to a pathname naming the new directory entry to be
          created.  Link creates a new link (directory entry) for the
          existing file.

          Link will fail and no link will be created if one or more of
          the following are true:

          [ENOTDIR]      A component of either path prefix is not a
                         directory.

          [ENOENT]       A component of either path prefix does not
                         exist.

          [EACCES]       A component of either path prefix denies
                         search permission.

          [ENOENT]       The file named by path1 does not exist.

          [EEXIST]       The link named by path2 exists.

          [EPERM]        The file named by path1 is a directory, and
                         the effective user ID is not superuser.

          [EXDEV]        The link named by path2 and the file named by
                         path1 are on different logical devices (file
                         systems).

          [ENOENT]       Path2 points to a null pathname.

          [EACCES]       The requested link requires writing in a
                         directory with a mode that denies write
                         permission.

          [EFAULT]       Path points outside the allocated address
                         space of the process.

     RETURN VALUE

          Upon successful completion, a value of 0 is returned.
          Otherwise, a value of -1 is returned and errno is set to
          indicate the error.

     SEE ALSO
          unlink.m

     SPECIAL CONSIDERATIONS
          For MPX 3.X the rename system service is used.  This 
          requires the destination filename to be on the same
          volume as the source filename.

          For MPX 1.X the rewrite SMD entry service is used.  It
          calls H.FISE,2.  This requires the user to be privledged.

          (printed 07/31/92 - J B Systems)

