
     NAME
          ctime, localtime, gmtime, asctime, tzset -
          convert date and time to ASCII

     SYNOPSIS
          #include <sys/types.h>

          extern char *tzname[2];

          void tzset()

          char *ctime(clock)
          time_t *clock;

          #include <time.h>

          char *asctime(tm)
          struct tm *tm;

          struct tm *localtime(clock)
          time_t *clock;

          struct tm *gmtime(clock)
          time_t *clock;

     DESCRIPTION
          Tzset uses the value of the environment variable TZ to set
          time conversion information used by localtime.  If TZ does
          not appear in the environment, the best available approximation
          to local wall clock time is used by localtime.  If TZ appears
          in the environment but its value is a null string, Greenwich
          Mean Time is used.

          Ctime converts a value of type time_t , pointed to by clock,
          such as returned by time() representing the time in seconds
          since 00:00:00 GMT, January 1, 1970, and returns a pointer
          to a 26-character string of the form

              Thu Nov 24 18:22:48 1986\n\0

          All the fields have constant width.

          Localtime and gmtime return pointers to tm structures,
          described below.  Localtime corrects for the time zone and
          any time zone adjustments (such as Daylight Savings time in
          the U.S.A.).

          Gmtime converts to Greenwich Mean Time (GMT).

          Asctime converts a time value contained in a ``tm''
          structure to a 26-character string, as shown in the above
          example, and returns a pointer to the string.

          Declarations of all the functions and externals, and the tm
          structure is in the <time.h> header file.  The structure
          (of type) struct tm includes the following fields:

                    int tm_sec;      /* seconds (0 - 59) */
                    int tm_min;      /* minutes (0 - 59) */
                    int tm_hour;     /* hours (0 - 23) */
                    int tm_mday;     /* day of month (1 - 31) */
                    int tm_mon;      /* month of year (0 - 11) */
                    int tm_year;     /* year - 1900 */
                    int tm_wday;     /* day of week (Sunday = 0) */
                    int tm_yday;     /* day of year (0 - 365) */
                    int tm_isdst;    /* is DST in effect? */

          There is no guarantee that these fields will continue to
          exist in this form in future releases of this code.

          Tm_isdst is non-zero if a time zone adjustment such as
          Daylight Savings time is in effect.

     SEE ALSO
          getenv.m, time.m

     NOTE
          The return values point to static data whose content is
          overwritten by each call.  The tm_zone field of a returned
          struct tm points to a static array of characters, which will
          also be overwritten at the next call (and by calls to tzset).

          (printed 07/29/92 - J B Systems)

