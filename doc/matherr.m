
    Name
        matherr - Error-handling function.

    Syntax
        #include <math.h>

        int matherr (x)
        struct exception *x;

    Description
        matherr is invoked by functions in the Math Library when
        errors are detected.  Users may define their own procedures
        for handling errors, by including a function named matherr
        in their programs.  matherr must be of the form described
        above.  When an error occurs, a pointer to the exception
        structure x will be passed to the user-supplied matherr
        function.  This structure, which is defined in the <math.h>
        header file, is as follows:

        struct exception {
            int type;
            char *name;
            double arg1, arg2, retval;
        };

        The element type is an integer describing the type of error
        that has occurred, from the following list of constants
        (defined in the header file):

        DOMAIN     argument domain error
        SING       argument singularity
        OVERFLOW   overflow range error
        UNDERFLOW  underflow range error
        TLOSS      total loss of significance
        PLOSS      partial loss of significance

        The element name points to a string containing the name of
        the function that incurred the error.  The variables arg1
        and arg2 are the arguments with which the function was
        invoked.  retval is set to the default value that will be
        returned by the function unless the user's matherr sets it
        to a different value.

        If the user's matherr function returns non-zero, no error
        message will be printed, and errno will not be set.

        If matherr is not supplied by the user, the default error-
        handling procedures, described with the math functions
        involved, will be invoked upon error.  These procedures are
        also summarized in the table below.  In every case, errno is
        set to EDOM or ERANGE and the program continues.

    Example
        #include <math.h>

        int
        matherr(x)
        register struct exception *x;
        {
        switch (x->type) {
        case DOMAIN:
            /*
             * change sqrt to return sqrt(-arg1), not 0
             */
            if (!strcmp(x->name, ``sqrt'')) {
                x->retval = sqrt(-x->arg1);
                return (0);
                /*
                 * print message and set errno
                 */
            }
        case SING:
            /*
             * all other domain or sing errors,
             * print message and abort
             */
             fprintf(stderr, ``domain error in %s\n'', x->name);
             abort( );
        case PLOSS:
             /*
              * print detailed error message
              */
             fprintf(stderr, ``loss of significance in %s(%g) = %g\n'',
                 x->name, x->arg1, x->retval);
             return (1);
             /*
              * take no other action
              */
        }
        return (0);
        /*
         * all other errors, execute default procedure
         */
        }

    _________________________________________________________________
    |                        DEFAULT ERROR HANDLING PROCEDURES       |
    |___________________|____________________________________________|
    |                   |               Types of Errors              |
    |___________________|_____|______|________|_________|_____|______|
    |        type       |DOMAI|  SING|OVERFLOW|UNDERFLOW|TLOSS| PLOSS|
    |___________________|_____|______|________|_________|_____|______|
    |       errno       | EDOM|  EDOM| ERANGE |  ERANGE |ERANG| ERANG|
    |___________________|_____|______|________|_________|_____|______|
    |BESSEL:            |  -  |   -  |   -    |    -    | M, 0|   *  |
    |y0, y1, yn (arg _ 0|M, -H|   -  |   -    |    -    |  -  |   -  |
    |___________________|_____|______|________|_________|_____|______|
    |EXP:               |  -  |   -  |   H    |    0    |  -  |   -  |
    |___________________|_____|______|________|_________|_____|______|
    |LOG, LOG10:        |     |      |        |         |     |      |
    | (arg < 0)         |M, -H|   -  |   -    |    -    |  -  |   -  |
    | (arg = 0)         |  -  | M, -H|   -    |    -    |  -  |   -  |
    |___________________|_____|______|________|_________|_____|______|
    |POW:               |  -  |   -  |  _H    |    0    |  -  |   -  |
    |neg ** non-int     |M, 0 |   -  |   -    |    -    |  -  |   -  |
    |  0 ** non-pos     |     |      |        |         |     |      |
    |___________________|_____|______|________|_________|_____|______|
    |SQRT:              | M, 0|   -  |   -    |    -    |  -  |   -  |
    |___________________|_____|______|________|_________|_____|______|
    |GAMMA:             |  -  |  M, H|   H    |    -    |  -  |   -  |
    |___________________|_____|______|________|_________|_____|______|
    |HYPOT:             |  -  |   -  |   H    |    -    |  -  |   -  |
    |___________________|_____|______|________|_________|_____|______|
    |SINH:              |  -  |   -  |  _H    |    -    |  -  |   -  |
    |___________________|_____|______|________|_________|_____|______|
    |COSH:              |  -  |   -  |   H    |    -    |  -  |   -  |
    |___________________|_____|______|________|_________|_____|______|
    |SIN, COS, TAN:     |  -  |   -  |   -    |    -    | M, 0|   *  |
    |___________________|_____|______|________|_________|_____|______|
    |ASIN, ACOS,        |     |      |        |         |     |      |
    |ATAN2:             | M, 0|   -  |   -    |    -    |  -  |   -  |
    |___________________|_____|______|________|_________|_____|______|

        _____________________________________________________
        |                    ABBREVIATIONS                   |
        |  *    As much as possible of the value is returned.|
        |  M    Message is printed (EDOM error).             |
        |  H    HUGE is returned.                            |
        |  -H   -HUGE is returned.                           |
        |  _H   HUGE or -HUGE is returned.                   |
        |  0    0 is returned.                               |
        |____________________________________________________|

    Notes
        These routines must be linked by using the -lm linker
        option.

        (printed 07/29/92 - J B Systems)

