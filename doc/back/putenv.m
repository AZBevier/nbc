
     NAME
          putenv - change or add value to environment

     SYNTAX
          int putenv (string)
          char *string;

     DESCRIPTION
          String points to a string of the form ``name=value.'' Putenv
          makes the value of the environment variable name equal to
          value by altering an existing variable or creating a new
          one.  In either case, the string pointed to by string
          becomes part of the environment, so altering the string will
          change the environment.  The space used by string is no
          longer used once a new string-defining name is passed to
          putenv.

     DIAGNOSTICS
          Putenv returns non-zero if it was unable to obtain enough
          space via malloc for an expanded environment, otherwise
          zero.

     SEE ALSO
          exec.m, getenv.m, malloc.m, environ.m

     WARNINGS
          Putenv manipulates the environment pointed to by environ,
          and can be used in conjunction with getenv.  However, envp
          (the third argument to main) is not changed.

          This routine uses malloc() to enlarge the environment.
          After putenv is called, environmental variables are not in
          alphabetical order.

          A potential error is to call putenv with an automatic
          variable as the argument, then exit the calling function
          while string is still part of the environment.

          (printed 07/29/92 - J B Systems)

