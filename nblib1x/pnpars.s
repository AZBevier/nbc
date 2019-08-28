*~!pnpars.s*/
* Name:  pnpars.s Part No.: _______-____r
*
* Copyright 1991 - J B Systems, Morrison, CO
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
*ident	"@(#)nbclib:pnpars.s	1.1"
*
************************************************************************
         PROGRAM   PNPARS          FILE:  PNPARS.S
*
         LIST      ON,NOMAC,NOREP
************************************************************************
*   PROGRAM SIZING EQUATES
************************************************************************
*
         DEF       __cassg
         DEF       __rrs
         SPACE     2
************************************************************************
*   REGISTER EQUATES
************************************************************************
         SPACE     1
AP       DEQU      1              ARGUMENT POINTER
X1       DEQU      1
X2       DEQU      2              GENERAL INDEX NUMBER 1
SP       DEQU      3              STACK POINTER
X3       DEQU      3
         SPACE     1
R0       DEQU      0              GENERAL REGISTER EQUATES
R1       DEQU      1
R2       DEQU      2
R3       DEQU      3
R4       DEQU      4
R5       DEQU      5
R6       DEQU      6
R7       DEQU      7
         PAGE
************************************************************************
*   SYSTEM EQUATES                                                     *
************************************************************************
C.DTTA   DEQU      X'00AA0'
C.DTTN   DEQU      X'00CB1'
C.UDTA   DEQU      X'00B38'
C.UDTN   DEQU      X'00C38'
RR.ACCS  DEQU      X'00008'
RR.APPND DEQU      X'00004'
RR.BLK   DEQU      X'00004'
RR.DATE  DEQU      X'00020'
RR.DENS  DEQU      X'00006'
RR.DEV   DEQU      X'00020'
RR.DEVC  DEQU      X'00003'
RR.DT3   DEQU      X'00010'
RR.EXCL  DEQU      X'00011'
RR.LFC   DEQU      X'00000'
RR.LFC2  DEQU      X'00004'
RR.MODFY DEQU      X'00002'
RR.NAME1 DEQU      X'00010'
RR.NBLKS DEQU      X'00014'
RR.OPTS  DEQU      X'0000C'
RR.PATH  DEQU      X'00001'
RR.PLEN  DEQU      X'00006'
RR.READ  DEQU      X'00000'
RR.RID   DEQU      X'00006'
RR.SBO   DEQU      X'00003'
RR.SEP   DEQU      X'0000F'
RR.SFC   DEQU      X'00008'
RR.SGO   DEQU      X'00001'
RR.SHAR  DEQU      X'00010'
RR.SIZE  DEQU      X'00005'
RR.SLO   DEQU      X'00002'
RR.SYC   DEQU      X'00000'
RR.TEMP  DEQU      X'00002'
RR.TYPE  DEQU      X'00004'
RR.UNBLK DEQU      X'00005'
RR.UNFID DEQU      X'00014'
RR.UPDAT DEQU      X'00003'
RR.VLNUM DEQU      X'00011'
RR.WRITE DEQU      X'00001'
UDT.SIZE DEQU      X'00040'
UDT.STAT DEQU      X'00004'
         SPACE     1
************************************************************************
*   LOCAL MACROS
************************************************************************
         SPACE     1
ENTER    DEFM
         TRR       SP,R1           STACK PTR FOR CALLING FUNCTION
         ADI       SP,-8W          DECREMENT SP FOR CALLED ROUTINE A001
         STD       R0,2W,SP        STORE RETURN ADDR IN STACK & PREV. SP
         STF       R4,4W,SP        STORE REGS 4 THROUGH 7 IN STACK
         LA        AP,8W,R1        PUT ARG AREA ADDR IN AP
         STW       SP,SPSAVE      SAVE STACK POINTER
         STW       AP,APSAVE      SAVE COPY OF AP
         ENDM
         SPACE     1
RETURN   DEFM
         LW        SP,SPSAVE      RESTORE OLD STACK PTR FROM SPSAVE
         LF        R2,2W,SP        RESTORE REGISTERS FROM STACK
         TRR       SP,R3           RESTORE OLD STACK PTR TO R3
         TRSW      R2              RETURN TO CALLING ROUTINE
         ENDM
         SPACE     1
************************************************************************
*
*   PROGRAMMING CONVENTIONS
*
*   1) THE ARGUMENT POINTER IS MAINTAINED IN REGISTER AP.  AP IS SAVED
*   AROUND CODE THAT MAY DESTROY IT, IN PARTICULAR, SVC'S.
*
*   2) THE FILE TABLE ENTRY ADDRESS IS TYPICALLY HELD IN REGISTER X2.
*   X2 IS REGENERATED AROUND CODE THAT MAY DESTROY IT, IN PARTICULAR,
*   SVC'S.
*
*   3) ALL ENTRIES INTO THIS PACKAGE ARE FUNCTIONS, THAT IS, THEY RETURN
*   A VALUE.  THE VALUE IS RETURNED IN R0.  ERRORS ARE GENERALLY
*   INDICATED BY -1.  SUCCESS IS GENERALLY INDICATED BY 0.  CREAT AND
*   OPEN RETURN THE FILE DESCRIPTOR TO SHOW SUCCESS.  WRITE RETURNS 0
*   TO INDICATE EOF DETECTED AND N(>0) TO INDICATE THE NUMBER OF
*   CHARACTERS ACTUALLY TRANSFERRED.
*
*   4) UTILITY SUBROUTINES EXPECT AP AND X2 TO BE PROPERLY INITIALIZED.
*   RESULTS ARE RETURNED IN R7.  ERRORS ARE GENERALLY INDICATED BY -1.
*   SUCCESS IS GENERALLY INDICATED BY 0.
*
************************************************************************
*   RETURN WITH AN ERROR
************************************************************************
         SPACE     1
         CSECT
         BOUND     1W
ERRETURN LI        R0,-1          SET ERROR CODE IN RESULT REGISTER
         RETURN                   RETURN TO CALLER
         PAGE
         SPACE     2
************************************************************************
*   RESOURCE REQUIREMENT SUMMARY AND PATHNAME BLOCK
************************************************************************
         SPACE     1
         DSECT
         REL
         bound     1d
__rrs    dequ       $
         SPACE     2
RRS      RES       1W             LFC GOES HERE
         DATAB     1,0,0,0        TYPE 1 RRS
         DATAW     X'D0008000'    ALLOW FOR UPDATE EXPLICIT SHARED
         DATAW     0
         rez       36w
         REL
         BOUND     1D
PNBX     DEQU      $               PNB FOR PATHNAME
         RES       18W
PNB1     DEQU      $
         RES       18W             PNB FOR 1ST  PATHNAME IF 2 ARE REQ'D
PNLENGTH DEQU      52              MAXIMUM PATHNAME LENGTH
PNBVCTOR GEN       8/18W,24/W(PNBX)
*                                  EMPTY PNB VECTOR WORD
         SPACE     1
         BOUND     1D
SPSAVE   DATAW     0
APSAVE   DATAW     0
PNBWRDX  DATAW     0               PATHNAME WORD FOR SINGLE OR 2ND ARG
*
* SIZES OF FIXED LENGTH RRS ENTRIES
*
RR.9.SIZ DEQU      10              MOUNT DEVICE - 10 WORDS
RR.4.SIZ DEQU      4               LFC          -  4 WORDS
RR.2.SIZ DEQU      4               TEMP         -  4 WORDS (+ VOL)
RR.3.SIZ DEQU      6               DEVICE       -  6 WORDS
RR.1.SIZ DEQU      4               PATHNAME     -  4 WORDS (+ PATH)
RR.6.SIZ DEQU      12              RID          - 12 WORDS
RR.D.SIZ DEQU      10              EXTENDED SLO - 10 WORDS          3206
*
* SIZE IN WORDS OF REFORMATTED RRS ENTRIES
*
CASSA.NW DEQU      4               ASSIGN 1
CASSB.NW DEQU      4               ASSIGN 2
CASSC.D1 DEQU      4               ASSIGN 3 (TEMP FILE ANY DEVICE)
CASSC.D2 DEQU      8               ASSIGN 3 (TEMP FILE SPEC. DEV)
CASSC.DV DEQU      6               ASSIGN 3 (DEVICE)
CASSD.NW DEQU      4               ASSIGN 4
*
RRS.SIZE DATAW     0               SIZE OF CURRENT RRS ENTRY
COPT90   RES       1F
CDEV90   RES       1F
*
*  SCRATCH DOUBLE WORD TO COUNT CHARACTERS IN DEVICE MNEMONIC  REV20100
*
CDEV.WRK DATAD     0
CDEV.CNT RES       1B              DEV MNEMONIC CHAR COUNT     REV20100
*
*  CDEV91 IS USED TO CONSTRUCT THE DEV-TYPE/CHAN/SUBCH WORD    REV20100
*
*  BYTE 0: BIT 0    = CHANNEL PRESENT
*          BITS 1-7 = DEVICE TYPE
*  BYTE 2: BIT 0    = SUBCHANNEL PRESENT
*          BITS 1-7 = CHANNEL
*  BYTE 3: BITS 0-7 = SUBCHANNEL
*
CDEV91   RES       1W
SAVER0   RES       8W
         BOUND     1W
STRLEN   RES       1W             LENGTH OF STRING TO BE PARSED     A004
CHARPOS  REZ       1W
BLNKS    REZ       1W              LEADING BLANKS FLAG
         PAGE
CCENT    RES       2D              LEFT JUSTIFIED FILED FROM SCANNER
CCSTRT   RES       1W              START OF CURRENT FILED
CCDLIM   RES       1B              LAST DELIMITTER ENCOUNTERED
CCHRS    RES       1B              NUMBER OF CHARACTERS IN FIELD
CCFLD    RES       1B              NUMBER OF FIELD
MDBUF    RES       1W              ADDRESS OF CURRENT INPUT RECORD
         CSECT
         TITLE  ASSIGN COMMANDS
***********************************************************************
*                                                                     *
*                  CASSG                                              *
*                                                                     *
***********************************************************************
*                                                                     *
*        PROCESS GENERAL ASSIGN DIRECTIVE                             *
*                                                                     *
***********************************************************************
__cassg  ENTER
*
*  ZERO MAXIMUM SIZE RRS
*
         LI        R6,12           12 WORDS MAX                REV20094
         LA        R3,RRS          START OF NEXT RRS           REV20094
         TRN       R6,R6           NEGATE LOOP COUNTER         REV20094
CASSG.05 ZMW       0W,R3           CLEAR RRS WORD              REV20094
         ABR       R3,29           BUMP POINTER                REV20094
         BIB       R6,CASSG.05     DO NEXT WORD                REV20094
         ZR        R6              INITIALIZE LENGTH TO ZERO    A004
         LW        R3,0,AP         GET ADDRESS OF PATHNAME    A004
CAS.LOOP ADI       R6,X'1'        INCREMENT CHARACTER COUNT       A004
         LB        R4,0B,X3       GET PATHNAME CHARACTER
         BEQ       CAS.NULL       STRING TERMINATOR FOUND, BRANCH
         BIB       X3,CAS.LOOP    TRY NEXT CHARACTER
*
CAS.NULL STW       R6,STRLEN       SAVE LENGTH OF PATHNAME      A004
         ZMW       CHARPOS         CLEAR PARSER FLAG
*
         LA        R3,RRS          GET RRS ADDR
*
* NOW GET THE MAIN PART OF THE ASSIGN. THIS WILL ALSO DETERMINE
* THE TYPE OF RRS BEING PRODUCED AND THEREFORE THE SPACE
* REQUIREMENT IN THE RRS TABLE.
*
         BL        STRING          GET THE PRIMARY ASSIGN TYPE
         LB        R5,CCHRS        CHECK FOR BLANK FIELD
         BZ        ERRETURN        BRANCH IF BLANK FIELD
         LB        R4,CCDLIM       SEE IF DELIMITER IS '=' .....
         CI        R4,G'='         ..... AND IF SO GO AND  .....
         BEQ       CASSG.5         ..... IDENTIFY THE KEYWORD
*
         CAMW      R6,=C'SYC '     SEE IF SYC
         BEQ       CASS.SYC        BRANCH IF SYC
*
         CAMW      R6,=C'SGO '     SEE IF SGO
         BEQ       CASS.SGO        BRANCH IF SGO
*
         CAMW      R6,=C'SBO '     SEE IF SBO
         BEQ       CASS.SBO        BRANCH IF SBO
*
         CAMW      R6,=C'SLO '     SEE IF SLO
         BEQ       CASS.SLO        BRANCH IF SLO
*
         CAMW      R6,=C'TEMP'     SEE IF TEMP WITH NO VOLUME
         BNE       CASSG.6         BRANCH IF NOT                    2104
         CI        R5,4            4 CHARS ONLY THIS NAME           2104
         BEQ       CASS.TP5        YES.  DEFINATELY A TEMP ASSIGN   2104
*
* KEYWORD NOT RECOGNIZED SO ASSUME A PATHNAME
*
* THIS FORMS A TYPE 1 RRS WHOS LENGTH IS 4 WORDS PLUS THE NUMBER
* OF WORDS CONSTITUTING THE PATHNAME.
*
CASSG.6  LW        AP,APSAVE       GET ARG POINTER
         LW        X2,0W,AP       PICK UP PATHNAME ADDRESS
*                                 *** ASSUMED TO BE A WORD ADDRESS
         TRR       X2,X3          MAKE ANOTHER COPY
         LA        R1,PNB1         GET ADDR OF TEMP AREA
PAR.L    LB        R4,0B,X3       GET PATHNAME CHARACTER
         BEQ       PAR.N          STRING TERMINATOR FOUND, BRANCH
         CI        R4,X'61'        SEE IF L/C
         BLT       PAR.X           BR IF NOT
         CI        R4,X'7A'        SEE IF L/C
         BGT       PAR.X           BR IF NOT
         SUI       R4,X'20'        MAKE U/C
PAR.X    CI        R4,G' '         SEE IF SPACE
         BEQ       PAR.N           TERM IF YES
         STB       R4,0B,R1        PUT IN TEMP BUFFER
         ADI       R1,1B           BUMP ADR
         BIB       X3,PAR.L       TRY NEXT CHARACTER
PAR.N    SUR       X2,X3          GET PATHNAME LENGTH
         CI        X3,0           SEE IF PATHNAME IS ZERO
         BLE       ERRETURN
         CI        X3,PNLENGTH    COMPARE TO MAXIMUM LENGTH
         BGT       ERRETURN       TOO BIG, RETURN WITH ERROR
         STW       R3,CHARPOS     SET STRING POINTER PAST PATHNAME
         SLL       X3,24          MOVE COUNT LEFT
         LA        R1,PNB1        CONSTRUCT PATHNAME VECTOR WORD
         ORR       X3,R1          PUT IN REGISTER FOR SERVICE
         LW        R4,PNBVCTOR    GET PATHNAME BLOCK VECTOR IN REGISTER
         ZR        R7             NO CNP
         SVC       2,X'2E'        CONVERT PATHNAME TO PATHNAME BLOCK
         LW        AP,APSAVE      RESTORE ARGUMENT POINTER
         TRR       R7,R7          TEST THE RETURN RESULT
         BNE       ERRETURN       DIDNT WORK, RETURN WITH ERROR
         STW       R4,PNBWRDX    SAVE PATHNAME BLOCK VECTOR WORD
         LB        R4,PNBWRDX      GET PATHNAME LENGTH
         TRR       R4,R7           SETUP FOR WORD ADJUSTMENT
         SRL       R7,2            EVALUATE NUMBER OF WORDS
CASS.PA1 ADI       R7,RR.1.SIZ     IN PATHNAME PLUS OVERHEAD
         STW       R7,RRS.SIZE     SAVE FOR RRS POINTER UPDATE LATER
*
* BUILD THE RRS ENTRY
*
         LA        R3,RRS          GET ADDR OF RRS
         LI        R6,RR.PATH      RRS TYPE .....
         STB       R6,RR.TYPE,R3   ..... INTO RRS
*
         STB       R4,RR.PLEN,R3   PATHNAME LENGTH
*
         TRN       R4,R4           LOOP COPYING NAME TO RRS
         TRR       R3,R1           START OF RRS ENTRY
         LA        R2,PNBX         START OF PATHNAME BLOCK
CASS.PA2 LB        R7,0B,R2        NEXT PATHNAME BYTE .....
         STB       R7,RR.NAME1,R1  ..... INTO RRS
         ABR       R1,31           NEXT RRS ENTRY
         ABR       R2,31           NEXT INPUT BYTE
         BIB       R4,CASS.PA2     AND LOOP
*
* ALL DONE, GET ANY OPTIONS AND THEN FINALLY UPDATE THE RRS POINTERS
*
* THE OPTIONS ARE THE SAME AS FOR ASSIGNING TO A TEMPORARY FILE
* SO UTILISE THE SAME CODE
*
         BU        CASS.TP2
*
* CHECK TO SEE IF A VALID KEYWORD.
* IF NOT FOUND IN THE KEYWORD TABLE ASSUME WE ARE ASSIGNING
* TO A PATHNAME BECAUSE '=' COULD APPEAR IN A PATHNAME IN QUOTES.
*
CASSG.5  ZR        R1              INDEX INTO LOCAL KEYWORD TABLE
         LI        R2,-CASSNK1     NUMBER OF KEYWORDS IN TABLE
CASSG.1  CAMD      R6,CASSKEY1,R1  CHECK FOR A MATCH
         BEQ       CASSG.2         BRANCH IF ONE FOUND
         ABR       R1,28           MOVE TO NEXT ENTRY IN TABLE
         BIB       R2,CASSG.1      AND LOOP FOR NEXT
         BU        CASSG.6         NOT THERE, GO TREAT AS PATHNAME
*
* KEYWORD FOUND SO SPLIT TO A SEPARATE ACTION ROUTINE FOR EACH
*
CASSG.2  SRL       R1,1            FORM WORD INDE TO ADDRESS TABLE
         BU        CASSACT1,R1     AND GO TO EACH ACTION ROUTINE
**       LW        R1,CASSACT1,R1  NO INDIRECTION ALLOWED, SO
**       TRSW      R1              USE THIS WAY
*        BU        *CASSACT1,R1    AND GO TO EACH ACTION ROUTINE   A006
*
* ASSIGNMENT TO SYC.
*
* BUILD A TYPE 2 RRS WITH BIT 0 SET IN THE OPTION WORD.
* THE CODE FOR THIS IS THE SAME AS FOR ASSIGNMENT TO SGO
* SO UTILISE COMMON CODE.
*
CASS.SYC ZR        R7              SET UP OPTION WORD .....
         SBR       R7,RR.SYC       ..... IN R7
         BU        CASS.SG1        COMMON WITH SGO
*
* ASSIGNMENT TO SGO.
*
* BUILD A TYPE 2 RRS WITH BIT 1 SET IN THE OPTION WORD.
* THE CODE FOR THIS IS COMMON WITH ASSIGNMENT TO SYC.
*
CASS.SGO ZR        R7              SET UP OPTION WORD .....
         SBR       R7,RR.SGO       ..... IN R7
         BU        CASS.SG1        COMMON MERGE POINT
*
* ASSIGNMENT TO SBO.
*
* BUILD A TYPE 2 RRS WITH BIT 3 SET IN THE OPTION WORD.
* THE CODE FOR THIS IS COMMON WITH ASSIGNMENT TO SYC.
*
CASS.SBO ZR        R7              SET UP OPTION WORD .....
         SBR       R7,RR.SBO       ..... IN R7
         BU        CASS.SG1        COMMON MERGE POINT
*
* ASSIGNMENT TO SLO.
*
* BUILD A TYPE 2 RRS WITH BIT 2 SET IN THE OPTION WORD.
* THE CODE FOR THIS IS COMMON WITH ASSIGNMENT TO SYC.
*
CASS.SLO ZR        R7              SET UP OPTION WORD .....
         SBR       R7,RR.SLO       ..... IN R7
CASS.SG1 LI        R6,RR.2.SIZ     MAKE SURE THERE IS .....
         STB       R6,RR.SIZE,R3   RRS SIZE
         STW       R7,RR.OPTS,R3   OPTION WORD TO RRS
         LI        R6,RR.TEMP      RRS TYPE
*
         STB       R6,RR.TYPE,R3
*
*        CHECK FOR 'DEVICE=' DIRECTIVE FOR SLO FILES                3206
*
         TBR       R7,RR.SLO       IS IT SLO ?                      3206
         BNS       CASS.SG2        NO, CONTINUE                     3206
         BL        STRING          YES, IS THERE A DEVICE DIRECTIVE 3206
         LB        R4,CCHRS                                         3206
         BZ        CASS.SG2        NO, CONTINUE                     3206
         LB        R4,CCDLIM       GET DELIMITER                    3206
         CI        R4,G'='         IS IT '=' ?                      3206
         BNE       ERRETURN        NO, THEN ERROR                   3206
         CAMW      R6,=C'DEVI'     IS IT DEVICE= ?                  3206
         BNE       ERRETURN        NO, THEN ERROR                   3206
         BL        STRING          GET MNEMONIC                     3206
         LI        R5,29           ERROR CODE                       3206
         CAMW      R7,=C'    '     CHANNEL SPECIFIED ?              3206
         BEQ       ERRETURN        NO, THEN ERROR                   3206
         TRR       R6,R4           SAVE IN R4,R5                    3206
         TRR       R7,R5                                            3206
         BL        CDEV            VALIDATE MNEMONIC                3206
         BS        ERRETURN        BRANCH IF ERROR                  3206
         LI        R6,RR.D.SIZ     GET EXTENDED RRS SIZE            3206
         STB       R6,RR.SIZE,R3   SAVE NEW SIZE IN RRS     3206
         STD       R4,RR.DEV,R3    YES, THEN SAVE DEVICE MNEMONIC   3206
         BU        CASSG.8                                          3206
*
* UPDATE THE RRS TABLE POINTERS
*
* FINALLY MAKE SURE THERE ARE NO OPTIONS ON THE LINE
*
CASS.SG2 LI        R6,RR.2.SIZ     SIZE OF ENTRY (FIXED PART ONLY US3206
*
CASSG.8  BL        STRING          GET OPTION FIELD (IF ANY)
         LB        R5,CCHRS        ANY OPTIONS??
         BNZ       ERRETURN        BRANCH TO ERROR IF ANY OPTIONS
         BU        CASSG.7         COMMON EXIT
         PAGE
*
* ASSIGNMENT TO ANOTHER LFC RECOGNIZED
*
* THE LFC MUST BE BETWEEN 1 AND 3 CHARACTERS.
*
* FORM A TYPE 4 RRS.
*
CASS.LFC BL        STRING          GET LFC NAME
         LB        R5,CCHRS        NUMBER OF CHARS IN LFC
         BZ        ERRETURN        BRANCH TO ERROR IF NO LFC
         CI        R5,3            CHECK IF < 3 CHARS
         BGT       ERRETURN        BRANCH TO ERROR IF > 3 CHARS
         SRL       R6,8            FORM FIRST WORD OF RRS
*
         LI        R4,RR.4.SIZ     MAKE SURETHERE IS ROOM .....
*
         STW       R6,RR.SFC,R3    LFC INTO RRS
         STB       R4,RR.SIZE,R3   RRS SIZE
         LI        R6,RR.LFC2      RRS TYPE
         STB       R6,RR.TYPE,R3
         LI        R6,RR.4.SIZ     SIZE OF ENTRY IN WORDS
         BU        CASSG.8         UPDATE RRS PTRS AND CHECK NO OPTIONS
         PAGE
*
* ASSIGNMENT TO RID
*
CASS.RID LI        R4,RR.6.SIZ     MAKE SURE THERE IS ROOM .....
         STW       R4,RRS.SIZE     SAVE FOR COMMON UPDATE LATER
*
         LI        R4,RR.RID       SET UP RRS .....
         STB       R4,RR.TYPE,R3   ..... TYPE
*
         BL        STRING          GET VOLUME NAME
         LB        R5,CCHRS        CHECK BETWEEN 1 AND 16 CHARS .....
         BZ        ERRETURN        ..... ELSE ERROR
         CI        R5,16           .....
         BGT       ERRETURN        ..... AND AGAIN
*
         STD       R6,RR.NAME1,R3  STORE 16 CHAR NAME .....
         LD        R6,CCENT+1D          .....
         STD       R6,RR.NAME1+1D,R3    ..... INTO RRS
*
* LOOP OF 4 OBTAINING BINARY DATE, TIME, BLOCK NUMBER AND RES TYPE
*
         TRR       R3,R2           RRS PTR (GETS UPDATED IN THE LOOP)
         LI        R4,-4           LOOP COUNT
CASS.RD1 BL        STRING          GET NEXT FIELD
         LB        R5,CCHRS        CHECK BETWEEN 1 AND 8 CHARS .....
         BZ        ERRETURN        ..... ELSE ERROR .....
         CI        R5,8            .....
         BGT       ERRETURN        ..... AND AGAIN
         SVC       1,X'29'         CONVERT HEX TO BINARY
         CI        R6,0            CHECK FOR ILLEGAL CHARACTERS .....
         BZ        ERRETURN        ..... AND BRANCH IF FOUND
         STW       R7,RR.DATE,R2   SAVE FIELD IN RRS .....
         ABR       R2,29           ..... AND UPDATE RRS PTR
         BIB       R4,CASS.RD1     LOOP FOR NEXT FIELD
*
* ALL DONE, GO GET OPTIONS
*
         BU        CASS.TP2
         PAGE
*
* ASSIGNMENT TO TEMP
*
* BUILD A TYPE 2 RRS WITH OPTIONAL VOLUME NAME IN PARENTHESES
*
* FORMAT IS:       TEMP[=(VOL)] OPTIONS
*             OR
*                  TEMP OPTIONS
*
* ENTRY POINT CASS.TMP IS USED FOR THE FIRST AND CASS.TP5 FOR
* THE SECOND.
*
*                                  TEMP [OPTIONS] ENTRY POINT
CASS.TP5 LI        R6,RR.2.SIZ     SET UP DEFAULT SIZE .....
         STW       R6,RRS.SIZE     ..... FOR RRS POINTER UPDATES
         BU        CASS.TP3        GO PROCESS OPTIONS
*
*                                  TEMP=(VOL) OPTIONS ENTRY POINT
CASS.TMP BL        STRING          GET OPTIONAL VOLUME FIELD
         LB        R5,CCHRS        MUST BE 0 WITH '(' DELIMITER
         BNZ       ERRETURN        BRANCH IF FIELD PRESENT
*
         LB        R4,CCDLIM       MAKE SURE DELIMITER IS '('
         CI        R4,G'('
         BNE       ERRETURN        BRANCH IF FORMAT ERROR
*
         BL        STRING          GET VOLUME NAME
         LB        R5,CCHRS        CHECK FOR VOLUME PRESENT
         BZ        CASS.TP4        BRANCH IF NOT PRESENT
         CI        R5,16
         BGT       ERRETURN        BRANCH IF TOO LARGE
*
         LI        R4,RR.2.SIZ+4   MAKE SURE THERE IS ROOM .....
         BGT       ERRETURN        ..... BRANCH TO ERROR IF NOT
*
         STW       R4,RRS.SIZE     SAVE RRS SIZE FOR UPDATE LATER
*
         STW       R6,RR.NAME1,R3  PUT NAME .....
         STW       R7,RR.NAME1+1W,R3    .....
         LD        R6,CCENT+1D
         STW       R6,RR.NAME1+2W,R3    .....
         STW       R7,RR.NAME1+3W,R3    ..... INTO RRS
*
CASS.TP4 LB        R4,CCDLIM       MAKE SURE DELIMITER .....
         CI        R4,G')'         ..... WAS ')'
         BNE       ERRETURN        BRANCH IF NOT ')'
*
* NOW GO AND SEE IF THERE WERE ANY OPTIONS
*
* SET UP RRS TYPE FIRST OF ALL BECAUSE THE OPTION HANDLING IS
* USED BY OTHER TYPES OF ASSIGN ALSO
*
CASS.TP3 LI        R6,RR.TEMP      RRS TYPE .....
         STB       R6,RR.TYPE,R3   ..... INTO RRS
*
CASS.TP2 BL        STRING          GET ANY OPTIONS
         LB        R5,CCHRS        CHECK FOR NONE .....
         BNZ       CASS.TP1        ..... AND BRANCH IF SOME
*
CASS.TP6 LW        R6,RRS.SIZE     SIZE OF RRS ENTRY
         STB       R6,RR.SIZE,R3   INTO RRS
*
         BU        CASSG.7         COMMON EXIT
*
* THERE IS AN OPTION, CHECK FOR VALIDITY ON THIS ASSIGN
* CC1 IS SET IF IF OPTION IS DETECTED.
* THE RRS WILL HAVE BEEN UPDATED ALREADY.
* NO RETURN IS MADE IF AN ERROR IS DETECTED.
*
CASS.TP1 BL        CAS.OPT1        SEE IF SHARED/ACCESS/BLOCKED .....
         BS        CASS.TP2        ..... BRANCH IF SO
         BL        CAS.OPT2        SEE IF SLO/SBO .....
         BS        CASS.TP2        ..... BRANCH IF SO
         BU        ERRETURN        ELSE ILLEGAL OPTION - ERROR
         PAGE
*
* ASSIGNMENT TO DEVICE
*
CASS.DEV LI        R4,RR.3.SIZ     MAKE SURE THERE IS .....
         BL        STRING          GET DEVICE ASSIGNMENT .....
         BL        CDEV            ..... AND VALIDATE IT
         BS        ERRETURN        BRANCH IF ERROR             REV20100
*
* ALL IS O.K. SO SET UP RRS ENTRY
*
         STW       R7,RR.DT3,R3    DEVICE TYPE/CHAN/SUB-CHAN WORD
         STB       R4,RR.SIZE,R3   RRS SIZE
*
         LI        R6,RR.DEVC      RRS TYPE .....
         STB       R6,RR.TYPE,R3   ..... INTO RRS
*
* SEE IF ANY OPTIONS
*
CASSG.10 BL        STRING          GET FIRST OPTION STRING
         LB        R5,CCHRS        CHECK FOR NONE .....
         BNZ       CASSG.9         ..... AND BRANCH IF SOME
*
CASSG.11 LI        R6,RR.3.SIZ     UPDATE RRS POINTERS .....
         BU        CASSG.7         AND EXIT
*
* THERE IS AN OPTION, CHECK FOR VALIDITY ON THIS ASSIGN.
* CC1 IS SET IF OPTION IS DETECTED.
* THE RRS WILL HAVE BEEN UPDATED ALREADY.
* NO RETURN IS MADE IF AN ERROR IS DETECTED.
*
CASSG.9  BL        CAS.OPT1        SEE IF SHARED/ACCESS/BLOCKED .....
         BS        CASSG.10        ..... BRANCH IF SO
         BL        CAS.OPT3        SEE IF DENSITY/MULTIVOL/ID .....
         BS        CASSG.10        ..... BRANCH IF SO
         BU        ERRETURN        ELSE AN ILLEGAL OPTION - ERROR
         PAGE
*
* THIS ROUTINE CHECKS TO SEE IF THE OPTION KEYWORD IN R6/R7
* IS ONE OF THE SET:
*
*                  SIZE   = DECIMAL VALUE
*                  SHARED = Y/N
*                  ACCESS = (R,W,M,U,A)
*                  BLOCKED= Y/N
*
* IF SO, THE APPROPRIATE BITS ARE SET IN THE CURRENT RRS ENTRY
* AND CC1 IS SET ON EXIT.
*
* IF A MATCH IS NOT FOUND, CC1 IS RESET ON EXIT.
*
* IF AN ERROR IN FORMAT IS DETECTED, AN ERROR EXIT IS TAKEN
* DIRECTLY, AND NO RETURN IS MADE TO THE CALLER.
*
CAS.OPT1 ZBR       R0,1            CLEAR CC1
         STF       R0,COPT90       SAVE CONTEXT
         LB        R4,CCDLIM       SEE IF '=' WAS DELIMITER
         CI        R4,G'='
         BNE       CAS.1.6         BRANCH TO OPTION NOT FOUND EXIT
*
         CAMW      R6,=C'SIZE'     SEE IF SIZE SPECIFICATION
         BNE       CAS.1.0         BRANCH IF NOT 'SIZE'
*
         BL        STRING          GET SIZE
         SVC       1,X'28'         CONVERT TO BINARY
         TRR       R6,R6           NON DECIMAL CHARACTERS?
         BZ        ERRETURN        YES, ILLEGAL FORMAT
         LB        R6,RR.TYPE,R3   CHECK RRS TYPE
         CI        R6,RR.TEMP      IS THIS A TEMP FILE
         BNE       ERRETURN        NO, ILLEGAL OPTION
         STH       R7,RR.PLEN,R3   ELSE, SAVE THE SIZE
         BU        CAS.1.3         COMMON EXIT
CAS.1.0  CAMW      R6,=C'SHAR'     SEE IF SHARED OPTION
         BNE       CAS.1.1         BRANCH IF NOT 'SHARED'
*
         BL        STRING          GET 'Y' OR 'N'
         LB        R5,CCHRS        CHECK FOR BLANK FIELD
         BZ        ERRETURN        BRANCH IF BLANK FIELD TO ERROR
         LB        R4,CCENT        GET FIRST CHAR OF FIELD
         CI        R4,G'Y'         'YES' ??
         BNE       CAS.1.2         BRANCH IF NOT 'Y'
         SBM       RR.SHAR,RR.ACCS,R3      SET SHARED BIT IN RRS
         BU        CAS.1.3         COMMON EXIT
*
CAS.1.2  CI        R4,G'N'         'NO' ??
         BNE       ERRETURN        BRANCH IF NOT 'Y' OR 'N' TO ERROR
         SBM       RR.EXCL,RR.ACCS,R3      SET EXCLUSIVE BIT IN RRS
         BU        CAS.1.3         COMMON EXIT
*
* CHECK FOR 'BLOCKED' OPTION
*
CAS.1.1  CAMW      R6,=C'BLOC'     SEE IF BLOCKED OPTION
         BNE       CAS.1.4         BRANCH IF NOT 'BLOCKED'
*
         BL        STRING          GET 'Y' OR 'N'
         LB        R5,CCHRS        CHECK FOR BLANK FIELD
         BZ        ERRETURN        BRANCH IF BLANK FIELD TO ERROR
         LB        R4,CCENT        GET FIRST CHAR OF FIELD
         CI        R4,G'Y'         'YES' ??
         BNE       CAS.1.5         BRANCH IF NOT 'Y'
         SBM       RR.BLK,RR.OPTS,R3       SET BLOCKED BIT IN RRS
         BU        CAS.1.3         COMMON EXIT
*
CAS.1.5  CI        R4,G'N'         'NO' ??
         BNE       ERRETURN        BRANCH IF NOT 'Y' OR 'N' TO ERROR
         SBM       RR.UNBLK,RR.OPTS,R3     SET UNBLOCKED BIT IN RRS
         BU        CAS.1.3         COMMON EXIT
*
* CHECK FOR ACCESS OPTION
*
CAS.1.4  CAMW      R6,=C'ACCE'
         BNE       CAS.1.6         OPTION NOT RECOGNIZED EXIT
*
         BL        STRING          GET '('
         LB        R5,CCHRS        SHOULD BE A ZERO COUNT
         BNZ       ERRETURN        BRANCH IF FIELD NOT EMPTY TO ERROR
         LB        R4,CCDLIM       CHECK FOR DELIMITER '('
         CI        R4,G'('
         BNE       ERRETURN        BRANCH IF NOT '(' TO ERROR
*
CAS.1.10 BL        STRING          GET NEXT ACCESS OPTION
         LB        R5,CCHRS        CHECK IF LAST ONE
         BNZ       CAS.1.7         BRANCH IF A FIELD TO LOOK FOR
         LB        R4,CCDLIM       MAKE SURE DELIMITER WAS ')'
         CI        R4,G')'
         BNZ       ERRETURN        BRANCH TO ERROR IF NOT ')'
         BU        CAS.1.3         COMMON EXIT
*
CAS.1.7  ZR        R1              SCAN ACCESS OPTION TABLE
         LI        R2,-CASSNK2     NUMBER OF ENTRIES IN TABLE
         LB        R6,CCENT        GET FIRST CHAR OF OPTION
CAS.1.8  CAMB      R6,CASSKEY2,R1  CHECK FOR A MATCH
         BEQ       CAS.1.9         BRANCH IF A MATCH
         ABR       R1,31           NEXT ENTRY IN TABLE
         BIB       R2,CAS.1.8      ANDLOOP
         BU        ERRETURN        OPTION NOT LEGAL
*
CAS.1.9  SLL       R1,2            WORD INDEX
         EXM       CASSACT2,R1     SET THE APPROPRIATE BIT IN RRS
         LB        R4,CCDLIM       IF DELIMETER WAS ')' .....
         CI        R4,G')'         .....
         BEQ       CAS.1.3         ..... THE EXIT, OPTION FINISHED
         BU        CAS.1.10        ..... LOOP FOR NEXT FIELD
*
* COMMON EXIT TO CALLER WHEN ALL IS O.K.
*
CAS.1.3  SBM       1,COPT90        SET CC1
*
* COMMON EXIT WHEN KEYWORD NOT RECOGNIZED.
*
CAS.1.6  LF        R0,COPT90
         TRSW      R0
         PAGE
*
* THIS ROUTINE CHECKS TO SEE IF THE OPTION KEYWORD IN R6/R7
* IS ONE OF THE SET:
*
*                  PRINT
*                  PUNCH
*
* IF SO, THE APPROPRIATE BITS ARE SET IN THE CURRENT RRS ENTRY
* AND CC1 IS SET ON EXIT.
*
* IF A MATCH IS NOT FOUND, CC1 IS RESET ON EXIT.
*
* IF AN ERROR IN FORMAT IS DETECTED, AN ERROR EXIT IS TAKEN
* DIRECTLY, AND NO RETURN IS MADE TO THE CALLER.
*
CAS.OPT2 ZBR       R0,1            CLEAR CC1
         STF       R0,COPT90       SAVE CONTEXT
         CAMW      R6,=C'PRIN'     SLO ??
         BNE       CAS.2.1         BRANCH IF NOT SLO
         SBM       RR.SLO,RR.OPTS,R3    SET SLO BIT IN RRS
         SBM       RR.SEP,RR.OPTS,R3    SET SEP BIT IN RRS          2111
         BU        CAS.1.3         COMMON EXIT
*
CAS.2.1  CAMW      R6,=C'PUNC'     SBO ??
         BNE       CAS.1.6         KEYWORD NOT RECOGNIZED EXIT
         SBM       RR.SBO,RR.OPTS,R3    SET SBO BIT IN RRS
         SBM       RR.SEP,RR.OPTS,R3    SET SEP BIT IN RRS          2111
         BU        CAS.1.3         COMMON EXIT
         PAGE
*
* THIS ROUTINE CHECKS TO SEE IF THE OPTION KEYWORD IN R6/R7
* IS ONE OF THE SET:
*
*                  DENSITY = N/P/G/800/1600/6250
*                  MULTIV  = NUMBER
*                  ID      = ID
*
* IF SO, THE APPROPRIATE BITS ARE SET IN THE CURRENT RRS ENTRY
* AND CC1 IS SET ON EXIT.
*
* IF A MATCH IS NOT FOUND, CC1 IS RESET ON EXIT.
*
* IF AN ERROR IN FORMAT IS DETECTED, AN ERROR EXIT IS TAKEN
* DIRECTLY, AND NO RETURN IS MADE TO THE CALLER.
*
CAS.OPT3 ZBR       R0,1            CLEAR CC1
         STF       R0,COPT90       SAVE CONTEXT
         LB        R4,CCDLIM       SEE IF '=' WAS DELIMITER
         CI        R4,G'='
         BNE       CAS.1.6         BRANCH TO OPTION NOT FOUND EXIT
*
* CHECK FOR 'DENSITY' OPTION
*
         CAMW      R6,=C'DENS'     SEE IF DENSITY OPTION
         BNE       CAS.3.1         BRANCH IF NOT 'DENSITY'
*
         BL        STRING          GET DENSITY VALUE
         LB        R5,CCHRS        CHECK FOR BLANK FIELD
         BZ        ERRETURN        BRANCH IF BLANK TO ERROR
*
         ZR        R1              SCAN DENSITY OPTION TABLE
         LI        R2,-CASSNK3     NUMBER OF ENTRIES IN TABLE
CAS.3.3  CAMW      R6,CASSKEY3,R1  CHECK FOR A MATCH
         BEQ       CAS.3.4         BRANCH IF A MATCH
         ABR       R1,29           NEXT ENTRY IN TABLE
         BIB       R2,CAS.3.3      AND LOOP
         BU        ERRETURN        OPTION NOT LEGAL
*
CAS.3.4  SRL       R1,2            FORM BYTE INDEX
         LB        R7,CASSACT3,R1  GET DENSITY BIT VALUE AND .....
         STB       R7,RR.DENS,R3   ..... STORE INTO RRS
         BU        CAS.1.3         COMMON EXIT
*
* CHECK FOR 'MULTIVOL' OPTION
*
CAS.3.1  CAMW      R6,=C'MULT'     SEE IF MULTIVOL OPTION
         BNE       CAS.3.2         BRANCH IF NOT 'MULTIVOL'
*
         BL        STRING          GET VOLUME NUMBER
         LB        R5,CCHRS        CHECK FOR NO FIELD
         BZ        ERRETURN        BRANCH IF BLANK FIELD
         SVC       1,X'28'         CONVERT ASCII DEC TO BINARY
         TRR       R6,R6           CHECK FOR ERROR
         BEQ       ERRETURN        BRANCH IF CONVERSION ERROR
         CI        R7,255          MAKE SURE IT FITS IN A BYTE
         BGT       ERRETURN        BRANCH IF TOO LARGE
         STB       R7,RR.VLNUM,R3  INTO RRS
         BU        CAS.1.3         COMMON EXIT
*
* CHECK FOR 'ID' OPTION
*
CAS.3.2  CAMW      R6,=C'ID  '     SEE IF ID OPTION
         BNE       CAS.1.6         OPTION NOT RECOGNIZED EXIT
*
         BL        STRING          GET ID
         LB        R5,CCHRS        MAKE SURE BETWEEN 1 AND 4 CHAR
         BZ        ERRETURN        BRANC IF BLANK FIELD
         CI        R5,4
         BGT       ERRETURN        BRANCH IF >4 CHARS
         STW       R6,RR.UNFID,R3  ID INTO RRS ENTRY
         BU        CAS.1.3         COMMON EXIT
*
* COMMON EXIT FOR END OF ASSIGN COMMAND
*
CASSG.7  ZR        R0
         RETURN
*
* TABLE FOR RECOGNIZING PRIMARY ASSIGN KEYWORDS
*
CASSKEY1 DATAD     C'LFC     '
         DATAD     C'DEV     '
         DATAD     C'TEMP    '
         DATAD     C'RID     '
CASSNK1X DATAD     C'        '     Dummy end
CASSNK1  CEQU      CASSNK1X-CASSKEY1/1D   NUMBER OF ENTRIES
*
* TABLE OF ACTION ROUTINES FOR PRIMARY KEYWORDS
*
CASSACT1 BU        CASS.LFC        LFC=                       A006
         BU        CASS.DEV        DEV=                       A006
         BU        CASS.TMP        TEMP=                      A006
         BU        CASS.RID        RID=                       A006
*
* TABLE FOR RECOGNIZING ACCESS RIGHTS KEYBYTES
*
CASSKEY2 DATAB     C'RWMUA'        READ/WRITE/MOD/UPDATE/APPEND
CASSNK2X DATAB     C' '            Dummy end
CASSNK2  CEQU      CASSNK2X-CASSKEY2   NUMBER OF ENTRIES
         BOUND     1W
CASSACT2 SBM       RR.READ,RR.ACCS,R3
         SBM       RR.WRITE,RR.ACCS,R3
         SBM       RR.MODFY,RR.ACCS,R3
         SBM       RR.UPDAT,RR.ACCS,R3
         SBM       RR.APPND,RR.ACCS,R3
*
* TABLE FOR RECOGNIZING DENSITY KEYWORDS
*
CASSKEY3 DATAW     C'N   '         800
         DATAW     C'P   '         1600
         DATAW     C'G   '         6250
         DATAW     C'800 '         800
         DATAW     C'1600'         1600
         DATAW     C'6250'         6250
CASSNK3X DATAB     C' '            Dummy end
CASSNK3  CEQU      CASSNK3X-CASSKEY3/1W   NUMBER OF ENTRIES
CASSACT3 DATAB     X'80'           800
         DATAB     X'40'           1600
         DATAB     X'02'           6250
         DATAB     X'80'           800
         DATAB     X'40'           1600
         DATAB     X'02'           6250
         BOUND     1W
*
         PAGE
************************************************************************
*                                                                      *
*                  CDEV                                                *
*                                                                      *
************************************************************************
*                                                                      *
*        PRODUCE A DEVICE-TYPE/CHANNEL/SUB-CHANNEL WORD                *
*        FROM AN INPUT DEVICE MNEMONIC (DEVMNC)                        *
*                                                                      *
*        INPUT:    R6/R7 = DEVMNC GIVEN BY USER                        *
*                                                                      *
*        OUTPUT:   R2 = ADDRESS OF DTT ENTRY FOR DEVICE                *
*                  R7 = DEVICE-TYPE/CHANNEL/SUB-CHANNEL WORD           *
*                                                                      *
*        ERRORS:   RETURN TO USER WITH CC1 SET AND R5 = CCERR          *
*                  MESSAGE ID FOR THE FOLLOWING ERRORS:                *
*                                                              (R5)    *
*                  (1) INPUT DEVMNC IS NOT 2/4/6 CHARS LONG    (29)    *
*                  (2) DEVICE IS NOT IN DTT TABLE              (06)    *
*                  (3) NON HEX CHANNEL/SUB-CHANNEL SPECIFIED   (29)    *
*                  (4) DEVICE NOT CONFIGURED IN SYSTEM         (28)    *
*                                                                      *
*        A RETURN IS NOT MADE TO THE CALLER IF ERROR DETECTED          *
*                                                                      *
************************************************************************
CDEV     STF       R0,CDEV90
         ZBM       1,CDEV90        CLEAR CC1 (ERROR RETURN FLAG)REV20100
         ZMW       CDEV91          TO BUILD OUTPUT R7 IN
*
*  COUNT THE CHARACTERS IN THE DEVICE MNEMONIC                 REV20100
*
         STD       R6,CDEV.WRK     SAVE MNEMONIC               REV20100
         LI        R5,-8           LOOP COUNTER                REV20100
         LA        R3,CDEV.WRK+7B  SCAN FROM END OF MNEMONIC   REV20100
         LI        R4,G' '         SCAN FOR FIRST NON-BLANK    REV20100
CDEV.05  CAMB      R4,0B,R3        BLANK?                      REV20100
         BNE       CDEV.06         NO.  EXIT.                  REV20100
         SUI       R3,1B           BACK TO PREVIOUS CHARACTER  REV20100
         BIB       R5,CDEV.05      CHECK IT.                   REV20100
*
CDEV.06  TRN       R5,R5           R5 HOLDS NON BLANK COUNT    REV20100
         STB       R5,CDEV.CNT     SAVE LOCALLY                REV20100
         LD        R6,CDEV.WRK     RESTORE MNEMONIC TO REGS    REV20100
         CI        R5,2
         BEQ       CDEV.0
         CI        R5,4
         BEQ       CDEV.0
         CI        R5,6
         BEQ       CDEV.0                                      REV20100
         LI        R5,29           INVALID DEVICE SPECIFIED    REV20100
         BU        CDEV.ERR        TAKE ERROR EXIT             REV20100
*
* PROCESS DEVICE MNEMONIC FIRST
*
CDEV.0   TRR       R6,R4
         SRL       R4,16           DEVICE MNEMONIC IN BOTTOM OF R4
         LW        R2,C.DTTA       DEVICE TABLE ADDRESS
         LNB       R5,C.DTTN       TOTAL ENTRIES IN TABLE
CDEV.1   CAMH      R4,3H,R2        LOOK FOR MNEMONIC
         BEQ       CDEV.2          BRANCH IF FOUND
         ABR       R2,28           MOVE TO NEXT ENTRY (2 WORDS)
         BIB       R5,CDEV.1       LOOP FOR NEXT ENTRY
         LI        R5,6            ERROR - INVALID MNEMONIC
         BU        CDEV.ERR        TAKE ERROR RETURN.          REV20100
*
* MNEMONIC FOUND, PROCESS CHANNEL/SUB-CHANNEL IF ANY
*
CDEV.2   STW       R2,CDEV90+2W    RETURN ENTRY ADDRESS TO CALLER
         LB        R5,0B,R2        GET DEVICE TYPE FROM TABLE
         STB       R5,CDEV91       INTO RESULT WORD
         LB        R5,CDEV.CNT     SEE IF ANY CHANNEL/SUB-CHANNEL
         CI        R5,2
         BEQ       CDEV.3          BRANCH IF NO CHAN/SUB-CHAN
         SBM       0,CDEV91        INDICATE CHANNEL PRESENT
*
         SLLD      R6,16           CHANNEL/SUB-CHANNEL INTO R6
         ADI       R7,G'  '        ALL SPACES IN R7
         SVC       1,X'29'         CONVERT CHAN/SUB-CHAN TO HEX
         TRR       R6,R6           CHECK FOR NON HEX DATA
         BNZ       CDEV.25         BRANCH IF CONVERSION OK.    REV20100
         LI        R5,29           INVALID DEVICE SPECIFIED.   REV20100
         BU        CDEV.ERR        TAKE ERROR RETURN           REV20100
*
* SET UP THE LOW HALFWORD OF RESULT TO CONTAIN THE CHANNEL
* NUMBER AND THE SUB-CHANNEL NUMBER, IF ANY.
* THE TOP BIT OF THE CHANNEL NUMBER FIELD IS SET IF A SUB-CHANNEL
* EXISTS.
*
CDEV.25  LB        R5,CDEV.CNT     CHECK FOR SUB-CHANNEL
         CI        R5,6
         BNE       CDEV.4          BRANCH IF CHANNEL ONLY
         SBR       R7,16           SET SUB-CHANNEL PRESENT BIT
         BU        CDEV.5          COMMON EXIT
CDEV.4   SLL       R7,8            CHANNEL NUMBER TO TOP BYTE OF .....
*                                  ..... HALFWORD
CDEV.5   STH       R7,CDEV91+1H    STORE IN RESULT
*
*  VERIFY DEVICE CONFIGURED ON SYSTEM                          REV20091
*
CDEV.3   ZR        R4              CLEAR COMPARE MASK REGISTER REV20100
*
*  IF DEVICE TYPE CODE IS A GENERIC (DC, MT, CD) THEN COMPARE
*  MASK WILL BE BUILT TO IGNORE DTC IN UDT.
*
         LB        R7,CDEV91       CHECK THE DTC FOR GENERIC   REV20100
         ZBR       R7,24           REMOVE CHAN FLAG IF PRESENT REV20100
         CI        R7,X'01'        DC?                         REV20100
         BEQ       CDEV.302        YES.  MASK = 0              REV20100
         CI        R7,X'04'        MT?                         REV20100
         BEQ       CDEV.302        YES.                        REV20100
         CI        R7,X'07'        CD?                         REV20100
         BEQ       CDEV.302        YES.                        REV20100
         LW        R4,=X'007F0000' SET MASK TO CHECK DTC       REV20100
*
*  MASK IS NOW SET FOR DTC.  PROCEED WITH CHAN AND SUBCH
*
CDEV.302 TBM       0,CDEV91        CHANNEL SPECIFIED?          REV20100
         BNS       CDEV.31         NO.  CHECK DTC ONLY.        REV20100
         ADI       R4,X'7F00'      ADD MASK FOR CHANNEL        REV20100
         TBM       16,CDEV91       SUB CHAN SPECIFIED?         REV20091
         BNS       CDEV.31         NO.  VERIFY CHAN ONLY       REV20091
         ADI       R4,X'00FF'      ADD MASK FOR SUBCHANNEL     REV20100
*
*  LOOP THRU UDT'S FOR SPECIFIED DEVICE                        REV20091
*
CDEV.31  LW        R1,C.UDTA       START OF UDT'S              REV20091
         LNH       R5,C.UDTN       NEG NUMBER OF UDT'S         REV20091
         LB        R7,CDEV91       DTC TO R7                   REV20100
         SLL       R7,16           TO BYTE 1 FOR UDT COMPARE   REV20100
         ORMH      R7,CDEV91+1H    OR IN CHANNEL AND SUBCH     REV20100
*
CDEV.32  CMMW      R7,UDT.STAT,X1  DEVICE MATCH?               REV20091
         BEQ       CDEV.33         YES.                        REV20091
         ADI       R1,UDT.SIZE     BUMP X1 TO NEXT UDT         REV20091
         BIB       R5,CDEV.32      AND COMPARE IF MORE         REV20091
*
         LI        R5,28           DEVICE NOT CONFIGURED       REV20091
*
*  CDEV.ERR - TAKE ERROR RETURN TO CALLER.
*  SET CC1, RETURN WITH R5 = CCERR MESSAGE INDEX               REV20100
*
CDEV.ERR SBM       1,CDEV90        SET CC1 BIT IN R0           REV20100
         STW       R5,CDEV90+5W    SAVE R5 FOR LOAD FILE       REV20100
*
CDEV.33  LF        R0,CDEV90
         LW        R7,CDEV91       RETURN TYPE/CHAN/SUB-CHAN WORD
         TRSW      R0
         PAGE
************************************************************************
*                                                                      *
*        STRING  - SYNTAX SCANNER FOR CATALOGER COMPATABILITY          *
*                                                                      *
************************************************************************
*
STRING   STF       R0,SAVER0       SAVE GPRS
         LW        AP,APSAVE       GET ARG POINTER
         LD        R6,BLANKS       GET SOME BLANKS
         STD       R6,CCENT        CLEAR TOKEN AREA
         STD       R6,CCENT+1D
         LI        R7,16B          TOKEN BUFFER LENGTH
         LW        R1,0W,AP        GET LINE BUFFER ADDR
         LA        R6,CCENT        PICK UP TOKEN BUFFER ADDRESS
SCANNER  TRR       R1,R0           SAVE LINEBUFFER ADDRESS
         LI        R4,CR           DUMMY TERMINATOR FOR E.O.B   24OCT80A
         ZR        R5              STRING COUNTER FLAG
         TRR       R1,R2           SET UP BUFFER INDEX
         BZ        STR.3           DO NOTHING
         ZBM       31,BLNKS        CLEAR BLANKS ACTIVE FLAG
         TRR       R6,R3           SET UP OUTPUT ADDRESS
         ZBR       R3,12           CLEAR F BIT
         LW        R6,CHARPOS      GET CHARPOS
         CAMW      R6,STRLEN      SEE IF END OF STRING ENCOUNTERED A004
         BLT       STRING0         STILL MORE OF PATHNAME          A004
         ZR        R5              INDICATE PAST END OF PATHNAME A004
         BU        STRING4         DONE .....
STRING0  ADMW      R2,CHARPOS      ADD CURSOR POSITION
STRING1  LI        R1,0
         LB        R4,0B,R2        GET BYTE FROM LINE BUFFER
         BZ        STRING4         IF EOL, DONE
         CI        R4,X'61'        SEE IF L/C
         BLT       STRING1A        BR IF NOT
         CI        R4,X'7A'        SEE IF L/C
         BGT       STRING1A        BR IF NOT
         SUI       R4,X'20'        MAKE U/C
STRING1A CAMB      R4,DELIMS,R1    CHECK AGAINST KNOWN DELIMS
         BNE       STRING1B        OK
         SLL       R1,2            WORD ALIGN INDEX
         BU        ACTIONS,R1      DISPATCH TO ROUTINE
*        LW        R1,ACTIONS,R1   DISPATCH TO ROUTINE
*        BU        0,R1
STRING1B ADI       R1,1
         CI        R1,DELIM#       AT END
         BLT       STRING1A        NOT YET
STRING1C CAR       R7,R5           AMASSED ENTIRE STRING YET
         BGE       NEXTCHAR        YES
         STB       R4,0B,R3        MOVE TO WORK BUFFER
         SBM       31,BLNKS        SET BLANKS NO LONGER ACTIVE FLAG
         ABR       R3,31           OUTPUT STRING BYTE ADDRESS
         ABR       R5,31           BUMP THIS STRING COUNTER
NEXTCHAR ABR       R2,31           INPUT STRING BYTE ADDRESS
         BIB       R6,STRING1      SCAN TILL E.O.B.
STRING2  TRR       R0,R1           RESTORE ADDRESS OF LINEBUFFER
         ADI       R2,1B           BUMP PAST DELIMITER
         SUR       R1,R2           DISTANCE TRAVELED
STR.2    STW       R2,CHARPOS      AND SAVE AS CURSOR NOW
STR.3    STB       R4,CCDLIM       REMEMBER CURRENT DELIMITTER
         STB       R5,CCHRS        REMEMBER FIELD SIZE
         LD        R6,CCENT        GET FIRST 8 CHAR OF TOKEN
         LD        R0,SAVER0       RESTORE R0, R1
         LD        R2,SAVER0+1D    RESTORE R2, R3
         LW        R4,SAVER0+2D    POP R4
         TRSW      R0              RETURN
*
*
*        SKIP LEADING BLANKS
*
         BOUND     1W
STRING3  TBM       31,BLNKS        ARE WE TRAVELING ACROSS LEAD BLANKS ?
         BS        STRING2         NOPE-> THATS A DELIMITER
         ADI       R2,1B           YES--> BUMP OVER THEM
         BIB       R6,STRING1      KEEP SCANNING TIL EOB
         BU        STRING2         DONE AT EOB
*
         BOUND     1W
STRING4  TRR       R0,R1           RESTORE ADDRESS OF LINEBUFFER
         LI        R2,2047         FORCE END OF MEDIUM FOR NEXT CALL
         BU        STR.2           TAKE NORMAL RETURN
*
         BOUND     1W
STRING6  TRR       R0,R1           RESTORE LINEBUFFER ADDRESS
         LB        R1,CHARPOS      GET INITIAL CURSOR POSITION
         CI        R1,5W           IS THIS THE FIRST FIELD
         BEQ       STRING5         IF SO, TREAT LIKE DOLLAR SIGN
         BU        STRING4         ELSE, TREAT AS END OF LINE
*
         BOUND     1W
STRING5  CI        R5,0            FIRST CHARACTER IN FIELD
         BNZ       STRING1C        NO
         STB       R4,0B,R3        SAVE THIS CHARACTER
         ABR       R5,31           BUMP CHARACTERS IN FIELD
         BU        STRING2         COMMON EXIT
         PAGE
*
BLANKS   DATAD     C'        '     BLANKS
*
*        DELIMITER WIDGETS
*
CR       DEQU      X'0D'           CARRIAGE RETURN CHARACTER
         BOUND     1W
DELIMS   DATAB     X'20'           00 - BLANK CHAR
         DATAB     C','            02 - COMMAN CHAR
         DATAB     CR              04 - CARRIAGE RETURN
         DATAB     C'='            03 - EQUAL SIGN
         DATAB     X'0A'           05 - NEW LINE (LINE FEED)
         DATAB     C'('            06 - LEFT PAREN
         DATAB     C')'            07 - RIGHT PAREN
         DATAB     C'";'           08 - SEMI-COLON
         DATAB     C'!'            09 - EXCLAMATION POINT
         DATAB     C'"%'           10 - PERCENT
         DATAB     C'$'            11 - DOLLAR SIGN
         DATAB     X'00'           12 - END OF STRING              A004
DELIMSX  DATAB     X'FF'           Dummy end
DELIM#   CEQU      DELIMSX-DELIMS  COUNT IN TABLE
         BOUND     1W
*
*        ROUTINES TO HANDLER ABOVE DELIMITERS
*
ACTIONS  BU        STRING3         00 - BLANKS
         BU        STRING2         02 - COMMAS
         BU        STRING4         04 - CARRIAGE RETURNS
         BU        STRING2         03 - EQUAL SIGNS
         BU        STRING2         05 - NEW LINES
         BU        STRING2         06 - LEFT PAREN
         BU        STRING2         07 - RIGHT PAREN
         BU        STRING2         08 - SEMI-COLON
         BU        STRING6         09 - EXCLAMATION POINT
         BU        STRING2         10 - PERCENT
         BU        STRING5         11 - DOLLAR SIGN
         END
