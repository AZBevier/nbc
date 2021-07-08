
     NAME
          This a definition of the NBC stack layout

     DESCRIPTION
          NBC uses a stack in extended or non-extended memory
          depending on the startup code linked with the users
          task.  C.srt.o is for a non-extended stack, and
          c.srte.o is for an extended stack.  The stack grows
          from high memory to low memory.  It is aligned on
          a file (8 word) boundry and is modulo 8 words.  The
          stack pointer is kept in r3 and should not be modified
          by the users program.  If an inline assembler call is
          made to a non C function, the stack pointer should
          be saved around the call.

          current stack pointer -> | not used                 |
              (r3, sp)             | not used                 |
                                   | return address           |
                                   | old stack pointer        |
                                   | r4 save                  |
                                   | r5 save                  |
                                   | r6 save                  |
                                   | r7 save                  |
          local call values (CALL?)| call parameter 1         |     
              (2 word bound)       | call parameter 2         |
                                   | call parameter n         |
          local storage (LOC?)     | automatic variable 1     |
              (2 word bound)       | automatic variable 2     |
                                   | automatic variable n     |
          local temp (L_TMP?)      | temp variable 1          |
              (2 word bound)       | temp variable 2          |
                                   | temp variable n          |
          filler for 8w bounding   | bounding                 |
          frame size (LA?)         ---------------------------- 
          previous stack pointer-> | previous frame           |
                                   | 8 word save area         |
          call parameters          | call parameter 1         |
                                   | call parameter n         |
          rest of previous frame   |                          |

          Review an assembler output of a C program to see the
          stack usage by a function.  The ? is the relative
          function number within the source file.

          All stack storage is double word aligned as required
          by the variable type.  Stack frames are always file
          (8 word) aligned.  Character and halfword variables
          are right justified within a word and sign extended
          as required.  A minimum of 8 words is allocated on
          the stack.  The stack size is fixed in length.  It
          is defined in c.srt?.o and can be modified by the
          user.

     EXAMPLE
          Following is a code sample for calling a C program from
          an end action level.  It could also be in assembler:

          #include <stdio.h>
          #include <fcntl.h>

          static char buffer(80);
          static int *fcba, infd;
          static char devp="DEV=CA18";
          static char mpxdev[16];
          static int rderr, rddone;
          static int errcnt;
          static int notdone = 1;
          static int total = 10;
          
          int main(argc, argv)
          int argc;
          char **argv;
          {
              /* set up HSD device */
              strcpy (mpxdev, devp);    /* copy in controller address */
              strcat (mpxdev, "02");    /* 02 is for status read */

              infd = open(mpxdev, O_RDWR);
              if (infd < 0){
                  perror(mpxdev);
                  exit(1);
              }
              /* get fcb address */
              fcba = (int *)fcbadr(infd);

              /* set up errea and iodone addresses */
              asm(" la 1,REREA");
              asm(" stw 1,_rderr");
              asm(" la 1,RIOEA");
              asm(" stw 1,_rddone");

              setfcb (fcba, rddone, rderr);  /* setup fcb */
              asm(" lw r1,_fcba");      /* get fcb address */
              asm(" svc 1,x'31'");      /* do next I/O */
              while (notdone) {
                  pause(10);            /* do anywait, 10 timer units */
              }
              close(infd);              /* close the device */
              exit(0);                  /* get out */
          }

          static
          ec_dummy()    /* dummy subroutine for end action code */
          {
              /* define end action stack */
              asm(" dsect");
              asm(" bound 1f");         /* file bound */
              asm(" res 512w");         /* room for nested calls */
              asm("STACKE res 1f");     /* points to end of stack */
              asm("PARAM1 dataw 0");    /* 1st parameter storage location */
              asm("PARAM2 dataw 0");    /* 2nd parameter storage location */
              asm(" csect");

              /* ignore any read errors for now */
              /* r1 has completing FCB address */
              asm(" bound 4");
              asm("REREA abm 31,_errcnt"); /* bump count */
              asm(" sea");              /* must be extended */
              asm(" la 3,STACKE");      /* get stack address */
              /* just reissue read using same buffer */
              asm(" svc 1,x'31'");      /* do next I/O */
              asm(" svc 1,x'2c'");      /* exit error end action */

              /* go process input data buffer and exit end action */
              /* r1 has completing FCB address */
              asm("RIOEA sea");         /* must be extended */
              asm(" la 3,STACKE");      /* get stack address */
              asm(" stw r1,PARAM1");    /* put fcb address on stack */
              asm(" bl _rtdoit");       /* go process buffer */
              asm(" svc 1,x'2c'");      /* exit I/O end action */
          }

          setfcb(fcb, iodone, errea)
          int *fcb;
          int iodone;      /* I/O end action address */
          int errea;       /* error end action address */
          {
              fcb[2] = 0x82000000;      /* nowait, ext fcb */
              fcb[8] = (int)&buffer;    /* set buffer address */
              fcb[9] = 80;              /* set buffer size */
              fcb[13] = (int)iodone;    /* set end action address */
              fcb[14] = (int)errea;     /* set error end action address */
          }

          static
          int rtdoit(fcb)
          register int *fcb;            /* FCB just completing write */
          {
              if (--total <= 0) {
                  notdone = 0;          /* show we are done */
                  return;               /* last I/O */
              }
              /* code here to process buffer */

              /* note 1st register variable is in r7 */
              asm(" trr r7,r1");        /* get fcb address */
              asm(" svc 1,x'31'");      /* do next I/O */
          }


     SEE ALSO
          read.m, write.m, open.m, readraw.m, writraw.m, close.m

          (printed 08/05/92 - J B Systems)

