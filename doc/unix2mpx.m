
     NAME
          unix2mpx - convert UNIX style pathname to MPX pathname

     SYNTAX
          void unix2mpx(path)
          char *path;

     DESCRIPTION
          Unix2mpx converts a UNIX pathname to an MPX pathname.
          If the UNIX pathname starts with / or . it will be
          converted.  The pathanme is translated in place.  There
          must be enough room for the converted name.  The
          pathname is always converted to uppercase.

     SEE ALSO
          fopen.c, creat.m, open.m, unixio.m

          (printed 08/05/92 - J B Systems)

