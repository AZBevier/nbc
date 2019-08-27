
     NAME
          getcwd - get pathname of current working directory

     SYNTAX
          char *getcwd (buf, size)
          char *buf;
          int size;

     DESCRIPTION
          Getcwd returns a pointer to the current directory pathname.
          The value of size must be at least two greater than the
          length of the pathname to be returned.

          If buf is a NULL pointer, getcwd will obtain size bytes of
          space using malloc().  In this case, the pointer returned
          by getcwd may be used as the argument in a subsequent call
          to free.

          On MPX-32 2.X and 3.X systems, the path returned will be of
          the form: /volume/directory.

          On MPX-32 1.X systems, the path returned will be of the
          form: /system/username.

          The path returned will always be in lower case.

     EXAMPLE
               char *cwd, *getcwd();
               .
               .
               .
               if ((cwd = getcwd((char *)NULL, 64)) == NULL) {
               perror(``pwd'');
               exit(1);
               }
               printf(``%s\n'', cwd);

     SEE ALSO
          malloc.m

     DIAGNOSTICS
          Returns NULL with errno set if size is not large enough, or
          if an error occurs in a lower-level function.

          (printed 07/29/92 - J B Systems)

