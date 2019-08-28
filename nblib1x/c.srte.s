*~!c.srte.s*/
* Name:  c.srte.s Part No.: _______-____r
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
* #ident	"@(#)nbclib:c.srte.s	1.0"
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
* REGISTER AND CONDITION CO[[BDE EQUATES
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
         STW       R1,_runrflg     !NON ZERO IF RUN REQ'D
         LW        R6,C.MGRAN      ! GET C. CONTAINING BLKSIZE
         STW       R6,_blksize     ! STORE IN BLKSIZE
         LI        R7,STK3X        ! Assume Concept machine
         CI        R6,X'2000'      ! Concept machine
         BEQ       $+2W            ! Branch if Concept machine
         LI        R7,STK7X        ! It is a 32/7X
         SEA                       !SET EXTENDED ADDRESSING
LOOP     SVC       1,X'69'         !GET A MAP BLOCK OF STACK
         TRR       R3,R3
         BZ        ABORT           ! ABORT IF CAN'T GET MEMORY
         TRN       R6,R5           ! GET NEG MAP SIZE
         ZMD       0D,R3	   !CLEAR A DOUBLE WORD
         ADI       R3,1D           !NEXT DOUBLE WORD
         BID       R5,$-2W         !LOOP FOR ALL
         BIB       R7,LOOP         ! GET NEXT MAP
         ADI       R4,1W           ! POINT TO START OF NEXT BLK
         TRR       R4,R7           ! GET LAST ALLOC ADDRESS
         TRR       R7,SP           ! SET STACK POINTER TO EAS
         SUI       SP,X'4000'      ! LEAVE BUFFER SPACE (2 MAP BL)
         TRR       SP,R4           ! START OF BUFFERS
         STW       R4,_bufrsio     ! POINTER TO IO BUFFERS
         STW       R7,_eas         ! SET EAS TO END OF ADDRESS SPACE
         LW        R6,=X'80000'    ! Csect starts at 80000
         STW       R6,_csect       ! SET EAS TO START OF CSECT
         BL        __mpxini        ! CALL THE ARGUMENT INIT ROUTINE
* ABORT IF ANY PROBLEMS
         SPACE     1
ABORT    LW        R5,ABRTCODE
         CEA                       !CLR EXTENDED ADDRESSING
         SVC       1,X'57'
*
         DSECT
_eas     rez       1w              ! POINTER TO END OF ADDRESS SPACE
_csect   rez       1w              ! POINTER TO START OF CSECT
_blksize rez       1w              ! MAP BLOCK SIZE
_bufrsio rez       1w              ! POINTER TO IO BUFFERS
_runrflg rez       1w              ! RUN REQUESTED TASK
c.flgs   DATAW     0
u.mbrk   DATAW     0
u.endstk DATAW     0
         END       _c.srt
