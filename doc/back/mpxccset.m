
     NAME
          mpxccset - set/clear carriage control flag

     SYNTAX
          int mpxccset (ccflag)
          int ccflag;

     DESCRIPTION
          If ccflag is not zero, output written to terminals or SLO
          files are prepended with a carrage control character.  A
          blank will normally be prepended.  If a formfeed character
          (0x0c) is detected, a '1' is prepended to the output. This
          flag is set by default.

     RETURN VALUE
          No value is returned

     SEE ALSO
          write.m

          (printed 08/03/92 - J B Systems)

