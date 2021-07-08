
     NAME
          chown, chownm - changes the owner and/or group of a file.

     SYNTAX
          int chown (path, owner, group)
          char *path;
          int owner, group;

          int chownm (path, ownername, project)
          char *path, *ownername, *project;

     DESCRIPTION
          Path points to a pathname naming a file.  If an owner ID
          of zero is specified, the ownername of the file is changed
          to SYSTEM, else it is ignored.  If a group ID of zero is
          specified, the project group is changed to SYSTEM, else it
          is ignored.  The chownm function is called by chown to
          change the ownername and project name.

          Chownm is an MPX version of chown.  Ownername and project
          are pointers to new names for the owner and project.  A
          maximum of 8 characters are copied.  If ownername or project
          are null pointers, that name is not changed.  Uppercase
          names must be specified.  Any character string is valid.
          The key or project files are not searched.

          Only the file owner or super-user (system) may change the
          ownership of a file.

          Chown/chownm will fail and the owner and group of the named
          file will remain unchanged if one or more of the following
          are true:

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
          chmod.m, chtype.m

          (printed 05/31/94 - J B Systems)

