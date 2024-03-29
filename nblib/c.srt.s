*~!c.srt.s*/
* Name:  c.srt.s Part No.: _______-____r
*
* Copyright 1990 - J B Systems, Morrison, CO
*
* The recipient of this product specifically agrees not to distribute,
* disclose, or disseminate in any way, to any one, nor use for its own
* benefit, or the benefit of others, any information contained  herein
* without the expressed written consent of J B Systems.
*
*                     RESTRICTED RIGHTS LEGEND
*
* Use, duplication, or disclosure by the Government is  subject  to
* restriction  as  set forth in paragraph (b) (3) (B) of the Rights
* in Technical Data and Computer Software  Clause  in  DAR  7-104.9
* (a).
*/
* #ident	"@(#)nbclib:c.srt.s	1.0"
         PROGRAM   C.SRT
         SPACE     1
************************************************************************
*
* _C.SRT IS THE MAIN ROUTINE FOR C PROGRAMS.  IT ESTABLISHES THE
*        STACK AND CALLS A C ROUTINE THAT READS ARGUMENTS AND INVOKES
*        THE C PROGRAM WITH THE ARGUMENTS.  IN ADDITION, IT CALCULATES
*        THE SIZE OF A MAP BLOCK AND SETS A POINTER TO THE END OF THE
*        PROGRAM'S ADDRESS SPACE.
*
************************************************************************
         SPACE     1
         DEF       _c.srt
         DEF       _eas
         DEF       _csect
         DEF       _blksize
         DEF       _bufrsio
         DEF       _runrflg
*                                  ! THESE ARE FROM CFLGS.S
         DEF       u.mbrk,u.endstk
         DEF       c.flgs
*
         EXT       __mpxini
         SPACE     2
************************************************************************
* REGISTER AND CONDITION CODE EQUATES
************************************************************************
         SPACE     1
R0       DEQU       0               ! REGISTER 0 EQUATE
R1       DEQU       1               ! REGISTER 1 EQUATE
R2       DEQU       2               ! REGISTER 2 EQUATE
R3       DEQU       3               ! REGISTER 3 EQUATE
SP       DEQU       3               ! REGISTER 3 EQUATE (STACK POINTER)
R4       DEQU       4               ! REGISTER 4 EQUATE
R5       DEQU       5               ! REGISTER 5 EQUATE
R6       DEQU       6               ! REGISTER 6 EQUATE
R7       DEQU       7               ! REGISTER 7 EQUATE
         SPACE     1
         IFF       C.MPX1X,SKIP
C.MGRAN  DEQU       X'AC4'          CPU MAP GRANULARITY FOR 3X
SKIP     ANOP
         IFT       C.MPX1X,SKIP
C.MGRAN  DEQU       X'ACC'          CPU MAP GRANULARITY FOR 1X
SKIP     ANOP
STK7X    DEQU       -2              ! SIZE OF C STK ON 32/7X
*                                    INCLUDING IO BUFS AT TOP
STK3X    DEQU       -8              ! SIZE OF C STK ON 32/27
*                                    INCLUDING IO BUFS AT TOP
         CSECT
         SPACE     1
CC1      CEQU       1               ! CONDITION CODE 1 EQUATE
         SPACE     1
ABRTCODE DATAW     C'E028'         ! ABORT CODE
         PAGE
_c.srt   CEQU       $
         SPACE     2
************************************************************************
* ESTABLISH THE C STACK
************************************************************************
         SPACE     1
         STW       R1,_runrflg     ! NON ZERO IF RUN REQ'D
         LW        R6,C.MGRAN      ! GET C. CONTAINING BLKSIZE
         STW       R6,_blksize     ! STORE IN BLKSIZE
         LI        R7,STK3X        ! Assume Concept machine
         CI        R6,X'2000'      ! Concept machine
         BEQ       $+2W            ! Branch if Concept machine
         LI        R7,STK7X        ! It is a 32/7X
LOOP     SVC       1,X'67'         ! GET A MAP BLOCK OF BUF SPACE
         TRR       R3,R3
         BZ        ABORT
         TRN       R6,R5           ! NEG MAP SIZE
         ZMD       0D,R3           ! ZERO A DOUBLE WD
         ADI       R3,1D           ! BUMP POINTER
         BID       R5,$-2W         ! CLEAR THE WHOLE MAP
         BIB       R7,LOOP         ! LOOP FOR ALL MAP BLOCKS
         SVC       1,X'65'         ! GET PROGRAM ADDRESS LIMITS
         ADI       R5,1W           ! START OF NEXT MAP
*jcb*    SRL       R5,5            ! ROUND STACK ADDR TO FILE BOUND
*jcb*    SLL       R5,5
         TRR       R5,R3           ! SET STACK POINTER ADDR
         STW       R5,_eas         ! SET EAS TO END OF ADDRESS SPACE
         SUI       R3,X'4000'      ! LEAVE BUFFER SPACE (2 MAP'S)
*jcb*    TRR       R3,R4           ! START OF BUFFERS
*jcb*    ADI       R4,X'20'        ! MAP BLOCK BOUND
         STW       R3,_bufrsio     ! POINTER TO IO BUFFERS
         STW       R6,_csect       ! SET EAS TO START OF CSECT
         SEA                       ! RUN EXTENDED ANYWAY
         BL        __mpxini        ! CALL THE ARGUMENT INIT ROUTINE
* ABORT IF ANY PROBLEMS
         SPACE     1
ABORT    LW        R5,ABRTCODE
         SVC       1,X'57'
*
         DSECT
_eas     REZ       1W       ! POINTER TO END OF ADDRESS SPACE
_csect   REZ       1W       ! POINTER TO START OF CSECT
_blksize REZ       1W       ! MAP BLOCK SIZE
_bufrsio REZ       1W       ! POINTER TO IO BUFFERS
_runrflg REZ       1W       ! RUN REQUESTED TASK
c.flgs   DATAW     0
u.mbrk   DATAW     0
u.endstk DATAW     0
         END       _c.srt
