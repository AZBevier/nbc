
     NAME
          vprintf, vfprintf, vsprintf - print formatted output of a
          varargs argument list

     SYNTAX
          #include <stdio.h>
          #include <varargs.h>

          int vprintf (format, ap)
          char *format;
          va_list ap;

          int vfprintf (stream, format, ap)
          FILE *stream;
          char *format;
          va_list ap;

          int vsprintf (s, format, ap)
          char *s, *format;
          va_list ap;

     DESCRIPTION
          vprintf, vfprintf, and vsprintf are the same as printf,
          fprintf, and sprintf respectively, except that instead of
          being called with a variable number of arguments, they are
          called with an argument list as defined by <varargs.h>.

     EXAMPLE
          The following demonstrates how vfprintf could be used to
          write an error routine.

          #include <stdio.h>
          #include <varargs.h>
               .
               .
               .
          /*
           *   error should be called like
           *        error(function_name, format, arg1, arg2...);
           */
          /*VARARGS0*/
          void
          error(va_alist)
          /* Note that the function_name and format arguments cannot be
           *      separately declared because of the definition of varargs.
           */
          va_dcl
          {
               va_list args;
               char *fmt;

               va_start(args);

               /* print out name of function causing error */
               (void)fprintf(stderr, "ERROR in %s: ", va_arg(args, char *));
               fmt = va_arg(args, char *);
               /* print out remainder of message */
               (void)vfprintf(fmt, args);
               va_end(args);
               (void)abort( );
          }

     SEE ALSO
          printf.m, varargs.m

          (printed 07/30/92 - J B Systems)

