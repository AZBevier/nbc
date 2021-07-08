
     Name
          nbcat - C version of the MPX cataloger.

     Syntax
          nbcat

     Description
    	  Nbcat is a modified version of the MPX cataloger.  It
          has been modified to understand the new object types
          produced by nbcas to support the AID for C source level
          debugger.  All assignments and options are the same as
          the standard Cataloger.  Nbcc uses the parameter activation
          system call to activate nbcat with the required assignments.

     See Also
          nbcc.m

     Diagnostics
          The use of the -Y option to nbcc will allow the load map
          to be output to a file for viewing.  If not specified,
          output will be to the null device and no output is available.

     Notes
          Nbcat can be used in place of the standard cataloger.  Nbcat
          also supports the DEBUGGER command to specify the debugger
          to be used for source level debugging.  MPX release 3.6 must
          be used to support multiple debuggers.  Otherwise the AID
          for C debugger must be named aiddb or mpxdb to be used.  The
          standard AID could not then be used.

          (printed 05/31/94 - J B Systems)

