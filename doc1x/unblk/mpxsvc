
     NAME
          mpxsvc - call an MPX service

     SYNTAX
          int mpxsvc (svcno, inregs, outregs)
          int svcno;
          int *inregs, *outregs;

     DESCRIPTION
          This function will call the specified MPX SVC for the user.
          Inregs is an array of eight integers containing the register
          values to use when calling the SVC.  Outregs is an array of
          eight integers where the register values returned from the
          SVC are to be stored.  Inregs and outregs can be the same
          array.  The condition codes returned from the SVC are returned
          by the function.  They are right justified in bits 28-31 of
          the return value.  Svcno is the SVC type and number to call.
          SVC 1,X'31' would be represented as 0x1031.  SVC 2,X'52'
          would be represented as 0x2052.

          This service is re-enterant allowing 20 levels of nested
          calls.  This provides the capability to use this service
          during end action processing.  A -1 will be returned if
          no more storage is available.  DO NOT use this service to
          exit from an end action service.  The internal storage
          space will never be returned as these SVC's do not return
          to the caller.  Use the inline assembler code function
          instead.  I.e. asm(" svc 1,x'70'");.

     RETURN VALUE
          The condition codes are returned right justified in bits
          28-31 of the return value.  A -1 is returned if no internal
          storage space is available.  The SVC return registers are
          stored into the outregs array.

     EXAMPLE
          include <fcb.h>

          static struct fcb iofcb;
          static int cc, regs[8];
          static int buffer[768];

          .
          .
          iofcb.erwa = (char *)buffer;      /* set buffer address */
          iofcb.eqty = 768;                 /* set transfer count */
          regs[1] = (int)iofcb;             /* address of fcb */
          cc = mpxsvc(0x1031, regs, regs);  /* do a read */
          .
          .

          (printed 08/12/92 - J B Systems)

