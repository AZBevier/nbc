
     NAME
          getenv - return value for environment name

     SYNTAX
          char *getenv (name)
          char *name;

     DESCRIPTION
          Getenv searches the environment list for a string of the
          form name=value, and returns a pointer to the value in
          the current environment, if such a string is present,
          otherwise a NULL pointer is returned.

          The variable TZ (for timezone) is special cased for MPX.
          If the variable TZ is not currently defined, the file
          /system/system/timezone is searched for a definition
          of the local TZ value.  A line must appear in the file
          in the form TZ=MST7MDT which specifies the local timezone.
          If the file is not found, the default TZ value of EST5EDT
          is used.

     SEE ALSO
          exec.m, putenv.m

          (printed 05/31/94 - J B Systems)

