
     Name
          ls - Gives information about contents of directories.

     Syntax
          ls [ -CRabdefgilmnopqstuxyz ] [ names ]

     Description
          For each directory named, ls lists the contents of that
          directory; for each file named, ls repeats its name and any
          other information requested. By default, the output is
          sorted alphabetically.  When no argument is given, the
          current directory is listed. When several arguments are
          given, the arguments are first sorted appropriately, but
          file arguments are processed before directories and their
          contents.

          There are three major listing formats.  The default format
          is to list one entry per line, the -C and -x options enable
          multi-column formats, and the -m option enables stream
          output format in which files are listed across the page,
          separated by commas. 80 colums are used to determine the
          output format for the -C, -x, and -m options.

          There are many options:

          -a   Lists all entries;  entries whose name begin with a
               period (.) are listed.

          -R   Recursively lists subdirectories encountered.

          -d   If an argument is a directory, lists only its name (not
               its contents); often used with -l to get the status of
               a directory.

          -C   Multi-column output with entries sorted down the
               columns.

          -x   Multi-column output with entries sorted across rather
               than down the page.

          -m   Stream output format.

          -l   Lists in long format, giving mode, file type, size in
               bytes,  and last modification time for each file.

          -n   The same as -l, except that the owner's UID and group's
               GID numbers are printed, rather than the associated
               character strings. (not used on MPX)

          -o   The same as -l, except that the group is not printed.
               (not used on MPX)

          -g   The same as -l, except that the owner is not printed.
               (not used on MPX)

          -z   Reverses the order of sort to get reverse alphabetic or
               oldest first, as appropriate. (was -r on UNIX)

          -t   Sorts by time modified (latest first) instead of by
               name.

          -u   Uses time of last access instead of last modification
               for sorting use with the -t option.

          -y   Uses time of creation instead of last modification
               for sorting use with -t option. (was -c on UNIX)

          -p   Puts a slash (/) after each filename if that file is a
               directory.

          -e   Puts a slash (/) after each filename if that file is a
               directory and puts an asterisk (*) after each filename
               if that file is executable. (was -F on UNIX)

          -b   Forces printing of non-graphic characters to be in the
               octal \ddd notation.

          -q   Forces printing of non-graphic characters in file names
               as the character (?).

          -i   For each file, prints the inode number in the first
               column of the report. (not used on MPX)

          -s   Gives size in blocks for each entry.

          -f   Forces each argument to be interpreted as a directory
               and lists the name found in each slot.  This option
               turns off -l, -t, -s, and -r, and turns on -a; the
               order is the order in which entries appear in the
               directory.

          The mode printed under the -l option consists of 11
          characters.  The first character is:

          -   If the entry is an ordinary file.

          d   If the entry is a directory.

          b   If the entry is a block special file. (not used on MPX)

          c   If the entry is a character special file. (not used on MPX)

          p   If the entry is a named pipe. (not used on MPX)

          s   If the entry is a semaphore. (not used on MPX)

          m   If the entry is a shared data (memory) file. (not used on MPX)

          The next 9 characters are interpreted as 3 sets of 3 bits
          each.  The first set refers to the owner's permissions; the
          next to permissions of others in the user-group of the file;
          and the last to all others.  Within each set, the 3
          characters indicate permission to read, to write, and to
          execute the file as a program, respectively. For a
          directory, ``execute'' permission is interpreted to mean
          permission to search the directory for a specified file.

          The permissions are indicated as follows:

          r   If the file is readable.

          w   If the file is writable.

          x   If the file is executable.

          -   If the indicated permission is not granted.

          The 2 character hex file type is printed for the file.

          When the sizes of the files in a directory are listed, a
          total count of blocks is printed.

     See Also
          chmod(C)

     Notes
          Newline and tab are considered printing characters in
          filenames.

          Unprintable characters in filenames may confuse the columnar
          output options.

          This utility reports sizes in 768 byte blocks.

          (printed 11/30/94 - J B Systems)

