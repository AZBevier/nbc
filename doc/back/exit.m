
     NAME
          exit, _exitmpx - terminate process

     SYNTAX
          void exit (status)
          int status;

          void _exit (status)
          int status;

          void _exitmpx (ecode_str)
          char *ecode_str;

     DESCRIPTION
          Exit terminates the calling process with the following
          consequences:

               All of the file descriptors open in the calling process
               are closed.

          The C function exit may cause cleanup actions before the
          process exits.  The function _exitmpx or _exit circumvents
          all cleanup.

     SEE ALSO
          signal.m

     WARNING
          See WARNING in signal.m

