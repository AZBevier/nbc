
     NAME
          types - primitive system data types

     SYNTAX
          #include <sys/types.h>

     DESCRIPTION
          The data types defined in the include file are used in UNIX
          system code; some data of these types are accessible to user
          code:

          typedef struct { int r[1]; } *  physadr;
          typedef long                    daddr_t;   /* <disk address> type */
          typedef char *                  caddr_t;   /* ?<core address> type */
          typedef unsigned short          ushort;
          typedef unsigned long           ino_t;     /* <inode> type */
          typedef short                   cnt_t;     /* ?<count> type */
          typedef long                    time_t;    /* <time> type */
          typedef int                     label_t[10];
          typedef short                   dev_t;     /* <device number> type */
          typedef long                    off_t;     /* ?<offset> type */
          typedef long                    paddr_t;   /* <physical address> type */
          typedef int                     key_t;     /* IPC key type */
          typedef unsigned int            uint;
          typedef int                     time_t;    /* <time> type */

          Times are encoded in seconds since 00:00:00 GMT, January 1,
          1970.  The major and minor parts of a device code specify
          kind and unit number of a device and are installation-
          dependent.  Offsets are measured in bytes from the beginning
          of a file.  The label_t variables are used with the setjmp()
          and longjmp() routines to effect non-local jumps.

          (printed 07/30/92 - J B Systems)

