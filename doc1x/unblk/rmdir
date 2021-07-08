
     NAME
          delete, unlink, rmdir - remove file or directory

     SYNTAX
          int delete (path)
          char *path;

          int unlink (path)
          char *path;

          int rmdir (path)
          char *path;

     DESCRIPTION
          Unlink or delete removes the file named by the path
          name pointed to be path.

          Rmdir removes the specified directory.

          The named file/directory is unlinked unless one or more
          of the following are true:

          [ENOTDIR]      A component of the path prefix is not a
                         directory.

          [ENOENT]       The named file/directory does not exist.

          [EACCES]       Search permission is denied for a component
                         of the path prefix.

          [EACCES]       Write permission is denied on the directory
                         containing the link to be removed.

          [EPERM]        The named file is a directory and the
                         directory is not empty.

          [EFAULT]       Path points outside the process's allocated
                         address space.

     RETURN VALUE
          Upon successful completion, a value of 0 is returned.
          Otherwise, a value of -1 is returned and errno is set to
          indicate the error.

     SEE ALSO
          close.m, link.m, open.m

          (printed 08/03/92 - J B Systems)

