
     NAME
          open - open for reading or writing

     SYNTAX
          #include <fcntl.h>

          int open (path, oflag [ , mode ] )
          char *path;
          int oflag, mode;

     DESCRIPTION
          Path points to a path name naming a file.  Open opens a file
          descriptor for the named file and sets the file status flags
          according to the value of oflag.  Oflag values are
          constructed by or-ing flags from the following list (only
          one of the first three flags below may be used):

          O_RDONLY Open for reading only.

          O_WRONLY Open for writing only.

          O_RDWR   Open for reading and writing.

          O_NDELAY This flag may affect subsequent reads and writes.
                   See read.m and write.m.  This flag is not supported
                   on MPX.  I/O is always issued as wait mode by the
                   C runtime library.

          O_APPEND If set, the file pointer will be set to the end of
                   the file prior to each write.

          O_CREAT  If the file exists, this flag has no effect.
                   Otherwise, the low-order 9 bits (18 bits) of the
                   file mode are set to the value of mode, if specified.
                   The mode may be specified as MPX bits (RWMUAD) or
                   UNIX style bits (RWX).  If the mode specified is
                   zero, the current default access rights in effect
                   for setacc() will be used.  See setacc.m.

          O_TRUNC  If the file exists, its length is truncated to 0
                   and the mode and owner are unchanged.  This flag
                   is unused on MPX.

          O_EXCL   If O_EXCL and O_CREAT are set, open will fail if
                   the file exists.  This flag is unused on MPX.

          O_UNBLK  This flag specifies that the file is to opened in
                   unblocked mode.  This flag is specific only to MPX.

          O_BIN    This flag specifies that the file is to opened in
                   blocked mode.  No newline translation will be made
                   for read or write operations.  This is useful for
                   reading or writing MPX object files.  This flag is
                   specific only to MPX.

          O_DWAIT  This flag specifies that the file is to be opened
                   only if it must not wait.  If the file is already
                   opened by another task in an incompatable mode, an
                   immediate return is made to the user.  This flag
                   is specific only to MPX.

          The file pointer used to mark the current position within
          the file is set to the beginning of the file.

          The named file is opened unless one or more of the following
          are true:

          [ENOTDIR]      A component of the path prefix is not a
                         directory.

          [ENOENT]       O_CREAT is not set and the named file does
                         not exist.

          [EACCES]       A component of the path prefix denies search
                         permission.

          [EACCES]       Oflag permission is denied for the named
                         file.

          [EISDIR]       The named file is a directory and oflag is
                         write or read/write.

          [EMFILE]       OPEN_MAX file descriptors are currently open.

          [EFAULT]       Path points outside the allocated address
                         space of the process.

          [EEXIST]       O_CREAT and O_EXCL are set, and the named
                         file exists.  Not used on MPX.

     RETURN VALUE
          Upon successful completion, the file descriptor is returned.
          Otherwise, a value of -1 (EOF) is returned and errno is set
          to indicate the error.

     SEE ALSO
          chmod.m, close.m, creat.m, lseek.m, setacc.m, getacc.m,
          setsiz.m, settype.m, read.m, umask.m, write.m

     SPECIAL CONSIDERATIONS
          MPX files are opened in blocked mode by default.  Newline 
          translation is completed during read or write operations.

          All blocked file I/O is handled internally by the unixio
          runtime module.  Eight sectors (6144 bytes) are buffered
          internally.  Blocked files are opened in unblocked mode
          for processing.

          (printed 05/31/94 - J B Systems)

