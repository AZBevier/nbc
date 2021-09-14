*~!jump.s*/
* Name:  jump.s Part No.: _______-____r
*
* Copyright 1994 - J B Systems, Morrison, CO
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
* #ident	"@(#)nbclib:jump.s	1.1"
         PROGRAM   JUMP
         DEF       _setjmp
         DEF       _longjmp
         SPACE     2
************************************************************************
*   REGISTER EQUATES
************************************************************************
         SPACE     1
AP       DEQU       1              ARGUMENT POINTER
X1       DEQU       2              GENERAL INDEX NUMBER 1
SP       DEQU       3              STACK POINTER
X2       DEQU       3
         SPACE     1
R0       DEQU       0              GENERAL REGISTER EQUATES
R1       DEQU       1
R2       DEQU       2
R3       DEQU       3
R4       DEQU       4
R5       DEQU       5
R6       DEQU       6
R7       DEQU       7
         SPACE     2
************************************************************************
*   LOCAL MACROS
************************************************************************
         SPACE     1
ENTER    DEFM
         TRR       SP,R1           STACK PTR FOR CALLING FUNCTION
         SUI       SP,8W           DECREMENT SP FOR CALLED ROUTINE
         STD       R0,2W,SP        STORE RETURN ADDR IN STACK
         STF       R4,4W,SP        STORE REGS 4 THROUGH 7 IN STACK
         LA        R2,8W,R1        PUT ARG AREA ADDR IN R2
         ENDM
         SPACE     1
RETURN   DEFM
         LF        R2,2W,SP        RESTORE REGISTERS FROM STACK
         TRSW      R2              RETURN TO CALLING ROUTINE
         ENDM
         SPACE     2
* SET THE JUMP LOCATION
         SPACE     1
         CSECT
_setjmp  CEQU        $
         ENTER
         LW        R2,0W,R2        GET THE SAVE AREA ADDRESS
* FIX_032894 - Do word operations to eliminate bounding errors
         STW       R0,0W,R2
         STW       R1,1W,R2
         STW       R4,2W,R2
         STW       R5,3W,R2
         STW       R6,4W,R2
         STW       R7,5W,R2
* OLD         STD       R0,0W,R2
* OLD         STD       R4,2W,R2
* OLD         STD       R6,4W,R2
         ZR        R0
         RETURN
         SPACE     2
* RETURN TO THE JUMP LOCATION
         SPACE     1
_longjmp CEQU        $
         ENTER
         LW        R2,0W,R2        GET THE SAVE AREA ADDRESS
* FIX_032894 - Do word operations to eliminate bounding errors
         LW        R0,0W,R2
         LW        R1,1W,R2
         LW        R4,2W,R2
         LW        R5,3W,R2
         LW        R6,4W,R2
         LW        R7,5W,R2
* OLD         LD        R0,0W,R2
* OLD         LD        R4,2W,R2
* OLD         LD        R6,4W,R2
         STD       R0,2W,R3
         STD       R4,4W,R3
         STD       R6,6W,R3
         LW        R0,17W,R3
         RETURN
         END
