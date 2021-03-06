
     NAME
          stat, fstat, stat1x - get file status

     SYNTAX
          #include <sys/types.h>
          #include <sys/stat.h>

          int stat (path, buf)
          char *path;
          struct stat *buf;

          int fstat (fildes, buf)
          int fildes;
          struct stat *buf;

          int stat1x (path, smdbuf)
          char *path;
          unsigned int *smdbuf;

     DESCRIPTION
          Path points to a path name naming a file.  Read, write, or
          execute permission of the named file is not required, but
          all directories listed in the path name leading to the file
          must be searchable.  Stat obtains information about the
          named file.

          Similarly, fstat obtains information about an open file
          known by the file descriptor fildes, obtained from a
          successful open or creat system call.

          Buf is a pointer to a stat structure into which information
          is placed concerning the file.

          On MPX 1.X, the stat1x service return the eight word SMD
          entry for the specified file in the users buffer pointed
          to by the variable smdbuf.

          The contents of the structure pointed to by buf include the
          following members:
               dev_t   st_dev;     ID of device containing a
                                   directory entry for this file.
                                   On MPX 1.X it is the UDT index.
                                   Unused on MPX 3.X, set to zero.
               ushort  st_ino;     Inode number.  On MPX 1.X it is
                                   the starting disk address (16 bits).
                                   On MPX 3.X it is the block number.
               ushort  st_mode;    File mode; On MPX 1.X it is set to
                                   0666 (RWRWRW).  If the MPX 1.X file
                                   type is 0, 0x40, 0xee, or 0xed the
                                   S_IFCHR flag is also set, else the
                                   S_IFREG flag is set.  On MPX 3.X it
                                   is the MPX access flags converted to
                                   UNIX style (RWXRWXRWX) flags.  If
                                   a directory is found, the S_IFDIR
                                   flag is set.  If the type is a temp
                                   or perm file, the S_IFREG flag is
                                   partition or other type.
               short   st_nlink;   Number of links.  On MPX, it is
                                   the MPX file type with a value of
                                   0 - 0xff.
               ushort  st_uid;     User ID of the file's owner.  On
                                   MPX 1.X it is the file indicators.
                                   Unused on MPX 3.X.
               ushort  st_gid;     Group ID of the file's group.  Not
                                   used on MPX, set to zero.
                                   Unused on MPX 3.X.
               dev_t   st_rdev;    ID of device.  On MPX 1.X this is
                                   the compressed 16 bit password.
                                   Unused on MPX 3.X.
               off_t   st_size;    File size in bytes.  On MPX 1.X it
                                   the EOM size.  On MPX 3.X it is the
                                   EOF size.
               time_t  st_atime;   Time of last access.  On MPX 1.X it
                                   is set to current time (time(0)).
                                   On MPX 3.X it is the last read or
                                   modification time.
               time_t  st_mtime;   Time of last data modification.  On
                                   MPX 1.X it is the current time.  On
                                   MPX 3.X it is the last modification
                                   time.
               time_t  st_ctime;   Time of last file status change.  On
                                   MPX 1.X it is the current time.  On
                                   MPX 3.X it is the last read or
                                   modification time.
                                   Times measured in seconds since
                                   00:00:00 GMT, Jan. 1, 1970
               long    st_blksize; Unused on MPX.
               long    st_blocks;  On MPX 1.X it is starting disk
                                   address (24 bits).

          st_atime  Time when file data was last accessed.  Changed by
                    the following system calls: creat(), write(), utime(),
                    and read().

          st_mtime  Time when data was last modified.  Changed by the
                    following system calls: creat(), utime(), and write().

          st_ctime  Time when file status was last changed.  Changed
                    by the following system calls: creat(), link(),
                    unlink(), utime(), and write(2).

          st_dev    ID of device containing a directory entry for this
                    file.

          st_rdev   This entry is defined only for character special
                    or block special files.

          Stat will fail if one or more of the following are true:

          [ENOTDIR]      A component of the path prefix is not a
                         directory.

          [ENOENT]       The named file does not exist.

          [EACCES]       Search permission is denied for a component
                         of the path prefix.

          [EFAULT]       Buf or path points to an invalid address.

          Fstat will fail if one or more of the following are true:

          [EBADF]        Fildes is not a valid open file descriptor.

          [EFAULT]       Buf points to an invalid address.

          Stat1x will fail if the following is true:

          [ENOENT]       The named file does not exist.

     RETURN VALUE
          Upon successful completion a value of 0 is returned.
          Otherwise, a value of -1 is returned and errno is set to
          indicate the error.

     SEE ALSO
          chmod.m, chown.m, creat.m, link.m, mknod.m, pipe.m,
          read.m, unlink.m, utime.m, write.m

          (printed 05/31/94 - J B Systems)

