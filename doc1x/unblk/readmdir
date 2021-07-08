
     NAME
          opendir, readdir, readmdir, telldir, seekdir, rewinddir,
          closedir - directory operations

     SYNTAX
          #include <dir.h>
          #include <sys/types.h>

          DIR *opendir (filename)
          char *filename;

          struct dirent *readdir (dirp)
          DIR *dirp;

          struct dirent *readmdir (dirp)
          DIR *dirp;

          long telldir (dirp)
          DIR *dirp;

          void seekdir (dirp, loc)
          DIR *dirp;
          long loc;

          void rewinddir (dirp)
          DIR *dirp;

          void closedir(dirp)
          DIR *dirp;

     DESCRIPTION
          Opendir opens the directory named by filename, associates a
          ``directory stream'' with it, and returns a pointer to be
          used to identify the directory stream in subsequent
          operations.  NULL is returned if filename cannot be accessed
          or is not a directory, or if not enough memory can be
          obtained via malloc() to hold a DIR structure.

          Readdir returns a pointer to the next directory entry and
          advances the ``current position'' of the directory stream.
          It returns NULL upon reaching the end of the directory or
          upon detecting an invalid previous seekdir operation.  This
          is the UNIX compatable interface and returns UNIX filenames.

          Readmdir returns a pointer to the next directory entry and
          advances the ``current position'' of the directory stream.
          It returns NULL upon reaching the end of the directory or
          upon detecting an invalid previous seekdir operation.  This
          is the MPX interface and returns MPX filenames.

          Telldir returns the current position associated with the
          directory stream.  Always returns 0 for MPX-32 1.X.

          Seekdir sets the position for the next readdir operation on
          the directory stream.  The new position reverts to the one
          associated with the directory stream when the previous
          telldir operation from which loc was obtained was performed.
          Values returned by telldir are good only for the lifetime of
          the DIR structure from which they are derived.  If the
          directory is closed and then reopened, the location value
          from telldir may be invalidated due to undetected directory
          compaction.  It is safe to use a previous telldir value
          immediately after a call to opendir and before any calls to
          readdir.  This entry does nothing on MPX-32 1.X.

          Rewinddir resets the position of the directory stream to the
          beginning of the directory.  This entry does nothing on 
          MPX-32 1.X.

          Closedir closes the directory stream and frees the
          associated DIR structure.

     EXAMPLE
          Sample code that searches a directory for an entry matching
          name:

                    dirp = opendir( "." );
                    while ( (dp = readdir( dirp )) != NULL )
                         if ( strcmp( dp->d_name, name ) == 0 )
                              {
                              closedir( dirp );
                              return FOUND;
                              }
                    closedir( dirp );
                    return NOT_FOUND;

     SEE ALSO
          open.m, close.m, read.m, lseek.m

     WARNINGS
          Rewinddir is implemented as a macro, so its function address
          cannot be taken.

          All UNIX programs that examine directories should be
          converted to use this package, since directory format is no
          longer the same on all UNIX systems.  Unfortunately, this
          package is not yet supplied with all UNIX systems.

          (printed 07/29/92 - J B Systems)

