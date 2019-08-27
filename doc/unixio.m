
     NAME
          unixio - information on simulated UNIX I/O on MPX

          
     I/O REDIRECTION

          The non-based C runtime library supports I/O redirection
          from the command line.  The defaults for interactive
          tasks are for stdin, stdout, and stderr to be assigned
          to the current terminal (UT).  If the task is activated,
          the defaults are assigned to DEV=NU.  The following
          examples show how to redirect stdin, stdout, and stderr:

          TSM>prog <input >output
              This command line entry will request that standard
              input (stdin) be read from the file "input".  The
              standard output (stdout) will be sent to the file
              "output".  If the file is not present, it is created.

          TSM>prog >>output
              This command line entry will request that stdin be
              read from the terminal.  The stdout from program "prog"
              will be appended to the file "output".  If the file is
              not present, it is created.

          TSM>prog 2>/system/userdir/output
              This command line entry will request that stdin be
              read from the terminal.  Stdout will be sent to the
              terminal.  The stderr from program "prog" will be
              will be sent to the file "output" in directory 
              userdir.  For MPX 1.X, it will be placed in the file
              "output" under username "userdir".  If the file is
              not present, it is created.

          TSM>prog >output 2>&1
              This command line entry will request that stdin be
              read from the terminal.  Stdout will be sent to the
              file "output".  The stderr from program "prog" will be
              will be sent to where stdout is assigned.  In this case
              it is to file "output".  If the file is not present,
              it is created.

              
          Devices, files, or logical file codes may be assigned from
          the command line in several formats.  This also holds true
          for open() or fopen().  Multiple field entries must be 
          enclosed in single quotes ('field1, field2').  Following
          are some example assignments:

              /volume1/source/file1       assign to file, UNIX format
              @volume1(source)file1       assign to file, MPX format
              ^(source)file1              assign to file, MPX format
              'file2 blocked=n'           assign to unblocked file
              SLO                         assign to SLO
              PRINT                       assign to SLO
              TEMP                        assign to MPX temp file
              'TEMP size=100'             assign to MPX temp file
              'dev=mt bloc=n'             assign to mag tape unblocked
              'dev=m91000 bloc=n'         assign to mag tape unblocked
              lfc=abc                     assign to LFC
              dev=nu                      assign to NULL device
          
          Most of the NBC subroutine library will accept the MPX or UNIX
          form of pathnames.  They will be converted to MPX form.

     DEFINITIONS
        Process ID
          Each active process in the system is uniquely identified by
          a positive integer called a process ID.  On MPX this is the
          task number.  

        Parent Process ID
          A new process is created by a currently active process. The
          parent process ID (MPX task number) of a process is the
          process ID of the task creator.
          
        File Descriptor
          A file descriptor is a small integer used to do I/O on a
          file.  The value of a file descriptor is from 0 to
          _NFILE-1.  A process may have no more than OPEN_MAX file
          descriptors open simultaneously.  A file descriptor is
          returned by system calls such as open() or creat().  The
          file descriptor is used as an argument by calls such as
          read(), write(), and close().

        File Name
          Names consisting of 1 to PATH_MAX characters may be used to
          name an ordinary file or directory.

          These characters may be selected from the set of all
          character values excluding \0 (null) and the ASCII code for
          / (slash).

          Note that it is generally unwise to use *, ?, [, or ] as
          part of file names because of the special meaning attached
          to these characters by UNIX.

        Path Name and Path Prefix
          A path name is a null-terminated character string starting
          with an optional slash (/), followed by zero or more
          directory names separated by slashes, optionally followed by
          a file name.  The path name can also be an MPX file name of
          the form @volume(directory)file and it's variations.

          If a path name begins with a slash, the path search begins
          at the root directory.  Otherwise, the search begins from
          the current working directory.

          A slash by itself names the root directory.  On MPX this is
          @system(system) or /system/system.

          Unless specifically stated otherwise, the null path name is
          treated as if it named a non-existent file.

        Directory
          Directory entries are called links.  By convention, a
          directory contains at least two links, . and .., referred to
          as dot and dot-dot respectively.  Dot refers to the
          directory itself and dot-dot refers to its parent directory.

        Root Directory and Current Working Directory
          Each process has associated with it a concept of a root
          directory and a current working directory for the purpose of
          resolving path name searches.

     SEE ALSO
          creat.m, read.m, write.m, seek.m, open.m, fopen.m

          (printed 08/04/92 - J B Systems)

