
     NAME
          varargs - handle variable argument list

     SYNTAX
          #include <varargs.h>

          va_alist

          va_dcl

          void va_start(pvar)
          va_list pvar;

          type va_arg(pvar, type)
          va_list pvar;

          void va_end(pvar)
          va_list pvar;

     DESCRIPTION
          This set of macros allows portable procedures that accept
          variable argument lists to be written.  Routines that have
          variable argument lists (such as printf()) but do not use
          varargs are inherently nonportable, as different machines
          use different argument-passing conventions.

          va_alist defines the parameter list in a function header.

          va_dcl defines a declaration for va_alist.  No semicolon
          should follow va_dcl.

          va_list defines a type defined for the variable used to
          traverse the list.

          va_start initializes pvar to the beginning of the list.

          va_arg returns the next argument in the list pointed to by
          pvar.  Type is the type the argument is expected to be.
          Different types can be mixed, but it is up to the routine to
          know what type of argument is expected, as it cannot be
          determined at runtime.

          va_end defines a variable to clean up.

          Multiple traversals, each bracketed by va_start ...  va_end,
          are possible.

     EXAMPLE
          This example is a possible implementation of vexecl().

                    #include <varargs.h>
                    #define MAXARGS     100

                    /*  vexecl is called by
                             vexecl(file, arg1, arg2, ..., (char *)0);
                    */
                    vexecl(va_alist)
                    va_dcl
                    {
                         va_list ap;
                         char *file;
                         char *args[MAXARGS];
                         int argno = 0;

                         va_start(ap);
                         file = va_arg(ap, char *);
                         while ((args[argno++] = va_arg(ap, char *)) != (char *)0)
                              ;
                         va_end(ap);
                         return vexecv(file, args);
                    }

     SEE ALSO
          exec.m, printf.m

     SPECIAL CONSIDERATIONS
          It is up to the calling routine to specify how many
          arguments there are, since it is not always possible to
          determine this from the stack frame.  For example, vexecl is
          passed a zero pointer to signal the end of the list.  Printf
          can tell how many arguments are there by the format.
          It is nonportable to specify a second argument of char,
          short, or float to va_arg, since arguments seen by the
          called function are not char, short, or float.  C converts
          char and short arguments to int and converts float arguments
          to double before passing them to a function.

          (printed 07/30/92 - J B Systems)

