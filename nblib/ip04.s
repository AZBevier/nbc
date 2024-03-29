*UNDEFINED INSTRUCTION TRAP PROC.  MPX-32 RELEASE 3.4   HEADER  H.IP04
************************************************************************
*                                                                      *
*                       RESTRICTED RIGHTS                              *
*                       -----------------                              *
*   THE INFORMATION CONTAINED HEREIN IS PROPRIETARY TO GOULD INC.,     *
*   COMPUTER SYSTEMS DIVISION, AND/OR ITS SUPPLIERS, AND ITS USE,      *
*   DISCLOSURE, OR DUPLICATION IS SUBJECT TO THE RESTRICTIONS STATED   *
*   IN THE GOULD INC., COMPUTER SYSTEMS DIVISION LICENSE AGREEMENT OR  *
*   THE APPROPRIATE THIRD-PARTY SUBLICENSE AGREEMENT.  INFORMATION IS  *
*   PROVIDED TO GOVERNMENT CUSTOMERS WITH RESTRICTED RIGHTS AS         *
*   DESCRIBED IN DAR 7-104.9(A).                                       *
*                                                                      *
************************************************************************
* (C) COPYRIGHT 1983 GOULD INC., COMPUTER SYSTEMS DIVISION
* (C) COPYRIGHT 1990 J B Systems, Morrison, CO.                    *JBS*
*     ALL RIGHTS RESERVED
************************************************************************
         PROGRAM   H.IP04          MPX-32_3.4U02.JBS
         M.VRSION
************************************************************************
*        Revised 09/28/90 J B Systems, Morrison CO.                *JBS*
*        Added Floating point reg-reg simulation software          *JBS*
*        This allows NBC compiler and run-time to execute          *JBS*
*        on a 32/27 which does not have reg-reg or int-float       *JBS*
*        or float-int instructions.  This modification also        *JBS*
*        allows Fortran 5.0 to run on a 32/27.                     *JBS*
************************************************************************
****************************************************************ETRA-U2
*                                                               ETRA-U2
*        MPX-32 REVISION 3 RELEASE 3.4.U02 CHANGE HISTORY       ETRA-U2
*                                                               ETRA-U2
****************************************************************ETRA-U2
*                                                               ETRA-U2
*        VERSION   3.4.U02.01                                   ETRA-U2
*                                                               ETRA-U2
*        ETRA-U2   10/19/88 8144 IMPROVE TRAP HANDLING BY       ETRA-U2
*                  FORCING TWO TRAPS. ALSO IN H.IP05 & H.IPU    ETRA-U2
*                                                               ETRA-U2
************************************************************************
*
*        MPX-32 REVISION 3 RELEASE 3.2C CHANGE HISTORY
*
************************************************************************
*
*        VERSION 32C01
*
*        32C01     03/12/85  9198  ADDED PROGRAM ID INFORMATION
*
************************************************************************
*                                                               Q137-33
*        MPX-32 REVISION 3 RELEASE 3.3 CHANGE HISTORY           Q137-33
*                                                               Q137-33
****************************************************************Q137-33
*                                                               Q137-33
*                                                               S840172
*        VERSION   3.3.01                                       Q137-33
*                                                               Q137-33
*        Q137-33   11/25/86  8162  ADDED CHECK OF T.UBRS (USER  Q137-33
*                  BASE REGISTERS STORED) BEFORE STORING USER'S Q137-33
*                  BASE REGISTERS ONTO T.BREGS.                 Q137-33
*                                                               Q137-33
*        VERSION   3.3.02                                       Q137-33A
*                                                               Q137-33A
*        Q137-33A  12/01/86  8162  REMOVE Q137-33 CODE CHANGE.  Q137-33A
*                  IT IS NOW REWORKED AND CONFINED TO H.EXEC.   Q137-33A
*                                                               Q137-33A
***********************************************************************
         SPACE     3
************************************************************************
*                                                                      *
*        H.IP04, UNDEFINED INSTRUCTION TRAP PROCESSOR                  *
*                                                                      *
************************************************************************
         LIST      NOMAC
         M.EQUS
         M.DQE.
DSW.TRAP EQU       2                                                3005
         LIST      NONG
         SPACE     3
         DEF       IP04S
         DEF       IP04.ICB
         DEF       H.IPXX          DEFINE TO H.IPU + H.IP05     ETRA-U2
         DEF       LSTPSW          LAST PSW                     ETRA-U2
         DEF       PV01CT          CNT OF ALL CPU/IPU PV01/UI01 ETRA-U2
         DEF       TIMECK          C.INTC AT LAST TRAP          ETRA-U2
         EXT       S.EXEC5A
         EXT       S.IP1
         EXT       BLANKD
         EXT       BR.DISP                                     3301 3000
         SPACE     3
HAT      DATAW     2
         ACW       IP04.ICB
SG.HAT   EQU       $                                                3302
         ACW       IP04S
         SPACE     3
         BOUND     2W
IP04.ICB EQU       $
IP04.OLD REZ       2W
IP04.NEW GEN       1/1,5/1,7/0,19/W(IP04)   PRIV'D, EXTENDED        3004
         GEN       2/2,12/0,1/0,1/1,1/0,1/1,12/0,2/0
*                   *            *   *   *
*                   *            *   *   *
*                   *            *   *   *49, NEW BLOCK STATE-BEI
*                   *            *   *48, LOAD NEW BLOCK STATE
*                   *            *47,RETAIN OLD MAP
*                   *32-33, MAP MODE (MAPPED)
IP04.ST1 DATAW     0
IP04.ST2 DATAW     0
         SPACE     3
IP04     EQU       $                                                #T#
         ABM       31,C.GINT       INCREMENT GLOBAL INT. COUNT
         STF       R0,IP04.REG     SAVE REGISTERS
         LD        R6,IP04.OLD     GET OLD PSD                  ETRA-U2
         BL        H.IPXX          CONFIRM THE TRAP             ETRA-U2
         BU        IP04.D1         RETURN HERE IF OK            ETRA-U2
         STD       R6,IP04.OLD     SAVE ADJUSTED PSD            ETRA-U2
JBS.COM  LI        R5,-1                                        *JBS*
         ARMW      R5,C.GINT                                    ETRA-U2
         LF        R0,IP04.REG                                  ETRA-U2
         LPSD      IP04.OLD        RE-EXECUTE PREV INSTRUCTION  ETRA-U2
IP04.D1  EQU       $               HERE WHEN TRAP IS CONFIRMED  ETRA-U2
         ZMB       UI02FLAG        PREPARE FOR A UI01/2             3201
*        LB        R5,C.MACH                                        3201
*        CI        R5,2            3227/3287 >= 2                   3201
*        BGE       IP04.F3         BRANCH IF NOT A 7X MACHINE       3201
*P04.83  LI        R5,X'83'        MPL  FOR 7X MACHINE              3201
*        BU        IP04.COM                                         3201
*JBS*    LI        R5,X'F3'        MPL  FOR 2K MAP MACHINE      *JBS*
*JBS*    TBM       6,IP04.OLD      SEE IF THIS IS A BASE TASK   *JBS*
*JBS* IP4.NOP1 BS        IP4.B001        BASE CODE REMOVED?     *JBS*
         BU        IP4.B001        GO SEE IF FP INSTR           *JBS*
*        GO UNMAPPED NOW
IP04.COM EQU       $                                            *JBS*
*JBS*    LI        R5,X'F3'        MPL  FOR 2K MAP MACHINE          3201
         LPSD      IP04.PSD        LOAD NEW, UMAPPED, PSD           3000
         BOUND     1D                                           *JBS*
IP04.PSD GEN       1/1,5/1,7/0,19/W(IP04.UNM)                       3006
         GEN       17/0,1/1,14/0                                    3000
IP04.UNM EQU       $                                                3000
         LI        R5,X'F3'        MPL  FOR 2K MAP MACHINE      *JBS*
         SLL       R5,16           POSITION ADDR IN HW              3000
         LW        R1,C.MPL
         TRSC      R1,R5           INSERT MPL ADDRESS INTO IPU SC PAD
         LW        R2,C.CURR       LOAD DQE ADDRESS
*        LB        R6,C.MACH       GET MACHINE TYPE                 3201
*        CI        R6,2            >= 2 THEN 32/27                  3201
*        BGE       CPIX.27         GO CONSTRUCT 32/27 CPIX          3201
*PIX.7X  LB        R6,DQE.NUM,R2   USED TO CONSTRUCT CPIX           3201
*        SLL       R6,2            POSITION                         3201
*        SBR       R6,1            SET MAP MODE                     3201
*        BU        CPIX.COM                                         3201
         LB        R6,DQE.NUM,R2   GET TASK NUM
         SLL       R6,3            POSITION
         SBR       R6,0            SET MAP MODE
CPIX.COM SBR       R6,16           PRESERVE OLD BLOCK STATE
         STW       R6,IP04.NP2     STORE AS CHANGE MAP PSD
         LW        R5,IP04.A01     GET UI01 ABORT CODE              3201
         TBM       0,UI02FLAG      WHICH TYPE OF ABORT ?            3201
         BNS       $+2W            BR IF A UI01                     3201
         LW        R5,IP04.A02     GET UI02 ABORT CODE              3201
         LPSDCM    IP04.NP1        ESTABLISH NEW MAP
*
         BOUND     1D                                           *JBS*
IP04.NP1 GEN       1/1,5/1,7/0,19/W(IP04.CON)
IP04.NP2 DATAW     0
*
IP04.CON EQU       $
         M.TRAC    7,04
*        LW        R5,IP04.A01     ABORT CODE                       3201
         LA        R1,IP04.OLD
         LA        R6,IP04.REG     ADDRESS OF REG. SAVE BLOCK
         BL        S.IP1           CRASH IF PSD ADDR. IN SYS.
         BU        IP04.1
         LD        R6,BLANKD
IP04.1   EQU       $
         LA        R2,IP04.REG
         LD        R6,IP04.OLD
         M.TRAC    8,04
         BL        S.EXEC5A
         SPACE     3
         BOUND     8W
IP04.REG REZ       8W
IP04.A01 DATAW     C'UI01'
IP04.A02 DATAW     C'UI02'         UNEXPECTED BREAKPOINT FOUND      3201
*                                                                   3201
UI02FLAG DATAB     0               FLAG FOR UI01/UI02 DETERMINATION 3201
*
*        VALIDATE THE TRAP                                      ETRA-U2
*                                                               ETRA-U2
         BOUND     1W                                           ETRA-U2
H.IPXX   EQU       $                                            ETRA-U2
         LW        R4,C.INTC       GET CURR CLOCK TIC COUNT     ETRA-U2
         SUMW      R4,TIMECK                                    ETRA-U2
         BLT       IPXX.1                                       ETRA-U2
         CI        R4,1            1ST OR 2ND TIME THROUGH?     ETRA-U2
         BGT       IPXX.1                                       ETRA-U2
         CAMW      R6,LSTPSW       SAME TRAP?                   ETRA-U2
         BEQ       IPXX.END                                     ETRA-U2
IPXX.1   STW       R6,LSTPSW       SAVE OLD PSW                 ETRA-U2
         LI        R3,X'1FF8'      RIGHT 1/2 W MASK             ETRA-U2
         SUI       R6,1H           WORD ADJUST                  ETRA-U2
         ZBR       R6,31           WAS LAST INST RT 1/2 WD?     ETRA-U2
         BS        IPXX.2                                       ETRA-U2
         ZBR       R6,30           NEXT INSTR RIGHT 1/2 WD?     ETRA-U2
IPXX.2   ANR       R6,R3                                        ETRA-U2
         CAR       R3,R3           GET CC'S                     ETRA-U2
         BNE       0,X3                                         ETRA-U2
         BNE       X'2000',X3                                   ETRA-U2
         BNE       X'4000',X3                                   ETRA-U2
         LW        R4,C.INTC                                    ETRA-U2
         STW       R4,TIMECK                                    ETRA-U2
         LI        R5,1                                         ETRA-U2
         ARMW      R5,PV01CT                                    ETRA-U2
         ABR       R0,29           CHANGE RETURN ADDRES         ETRA-U2
         TRSW      R0                                           ETRA-U2
IPXX.END ZMW       LSTPSW                                       ETRA-U2
         LI        R5,-1                                        ETRA-U2
         ARMW      R5,PV01CT                                    ETRA-U2
         TRSW      R0                                           ETRA-U2
LSTPSW   DATAW     0                                            ETRA-U2
PV01CT   DATAW     0                                            ETRA-U2
TIMECK   DATAW     0                                            ETRA-U2
         LPOOL
IP04.OVY EQU       $                                                3302
IP4.B001 EQU       $                                                3302
         LW        R1,IP04.OLD     GET THE OFFENDING PSW            3000
         ZBR       R1,31           MAKE SURE THE LSB IS OFF         3000
         SEA                       INSURE WE CAN GET IT W/O MF01    3200
IP04.10  SUI      R1,2             BACK UP TO THE BAD INSTRUCTION   3200
         LH       R7,0,R1          GET THE BAD INSTRUCTION          3000
         ANMW     R7,=X'FC0F'      REMOVE BITS 6 TO 11              3202
         CI       R7,X'0002'       IS IT A NOP ? (NEED FOR 32/67)   3200
         BEQ      IP04.10          YES SO EXPLORE BACK              3200
         LH        R7,0,R1         GET THE BAD INSTRUCTION AGAIN    3202
         CI        R7,X'0409'      IS IT A TRAP INSTRUCTION?        3000
         BNE       FPSIM           GO TEST FOR FP SIM OPS       *JBS*
*JBS*    BNE       IP04.COM        BR AS ITS NOT A BREAKPOINT   *JBS*
*                                                                   3000
*        PROCESS BASE REGISTER DEBUG TRAP HERE                      3000
*                                                                   3000
         TBM       6,IP04.OLD      SEE IF THIS IS A BASE TASK   *JBS*
         BNS       IP04.COM        CONTINUE WITH ABORT IF NOT   *JBS*
         SBM       0,UI02FLAG      PREPARE FOR A UI02               3201
         LW        R2,C.CURR       GET DQUE ADDRESS                 3000
         TBM       DQE.DBAT,DQE.USHF,R2  IS THE DEBUGGER THERE?     300A
         BNS       IP04.COM              IF NOT, THEN REAL UI01     300A
         SBM       DQE.ADM,DQE.ATI,R2   SET DEBUG ACTIVE BIT        3000
         LW        R3,C.REGS       GET TSA ADDRESS                  3000
         LI        R7,DSW.TRAP     GET STATUS CODE                  3005
         STB       R7,T.DBSTAT+3B,R3  SAVE IN TSA                   3005
         LD        R6,IP04.REG     GET GPR'S 0,1                    3000
         STD       R6,T.CONTXT,R3  SAVE IN CONTEXT                  3000
         LD        R6,IP04.REG+1D  GET NEXT 2                       3000
         STD       R6,T.CONTXT+1D,R3 AND SAVE                       3000
         LD        R6,IP04.REG+2D  GET NEXT                         3000
         STD       R6,T.CONTXT+2D,R3 AND SAVE                       3000
         LD        R6,IP04.REG+3D  GET LAST 2 REGS                  3000
         STD       R6,T.CONTXT+3D,R3 AND SAVE                       3000
         LD        R6,IP04.OLD     GET OLD PSD                      3000
         TRR       R1,R6           USE MODIFIED PSD1                3200
         STD       R6,T.CONTXT+4D,R3  STORE IN CONTEXT AREA TOO!    3000
*        SBM       T.UBRS,T.BIT5,X3   USERS BR ALREADY STORED?  Q137-33A
*        BS        $+2W               YES, DON'T DESTROY THEM   Q137-33A
         STFBR     R0,T.BREGS,R3   SAVE BASE REGS IN THEIR AREA     3000
         LW        R3,T.DBHAT,R3   FIND DEBUG E.P.                  3000
         LW        R5,3W,R3        ADDR OF EP3                      3000
         LW        R7,IP04.OLD+1W  OLD PSD2                         3002
         STW       R7,D2.PSD+1W    INTO DESTINATION PSD             3002
         LI        R4,-1           DECREMENT C.GINT                 3003
         ARMW      R4,C.GINT       WITH ADD REG TO MEM              3003
         LI        R6,3            DEBUG EP #                       3007
         LW        R7,DB.RTN       EXIT DEBUG SVC                   3001
         LPSD      D2.PSD          GO THERE                         3002
*                                                                   3000
DB.RTN   SVC       2,X'72'         EXIT TO TASK FROM DEBUG          3001
         BOUND     1D                                               3002
D2.PSD   GEN       1/1,7/2,24/BR.DISP                          3301 3002
         DATAW     0
*        END OF BASE REG DEBUG STUFF                                3000
*
**************************FLOATING POINT SIMULATION CODE*********JBS*
*                                                               *JBS*
*        R1 = INSTR ADDR                                        *JBS*
*        R7 = FAULTING INSTR IN RT HW                           *JBS*
*        USER REGS IN IP04.REG                                  *JBS*
*                                                               *JBS*
FPSIM    EQU       $               TEST FOR REG-REG FP INSTR    *JBS*
*                                                               *JBS*
*        COME HERE TO DECODE A HALFWORD INSTRUCTION THAT CAUSED *JBS*
*        AN EXCEPTION TRAP. ALL WILL HAVE AN OPCODE OF X'38'.   *JBS*
*        THE LAST NIBBLE WILL BE USED TO DECODE WHAT KIND OF    *JBS*
*        INSTRUCTION IT IS.                                     *JBS*
*                                                               *JBS*
         LW        R4,=X'FC00'     GET THE OPCODE MASK          *JBS*
         CMMW      R7,=X'3800'     IS IT ONE FOR US TO LOOK AT? *JBS*
         BNE       IP04.COM        NO, REPORT ERROR             *JBS*
*                                                               *JBS*
         LI        R4,X'F'         GET NIBBLE MASK              *JBS*
         TRRM      R7,R3           AND GET LOW 4 BITS OF INST   *JBS*
         SLL       R3,2            WORD ADJUST                  *JBS*
*                                                               *JBS*
         LI        R4,X'70'        MASK FOR SOURCE REG          *JBS*
         TRRM      R7,R2           R2 CONTAINS SOURCE REG       *JBS*
         SRL       R2,2            ADJUST R2 FOR INDEX          *JBS*
*                                                               *JBS*
         LI        R4,X'380'       MASK FOR DEST REG            *JBS*
         TRRM      R7,R1           R1 CONTAINS DEST REG         *JBS*
         SRL       R1,5            ADJUST R1 FOR INDEX          *JBS*
*                                                               *JBS*
         TBR       R7,28           TEST FOR DBL PRECISION       *JBS*
         BS        SET.DP          BRANCH IF DBL PRECISION      *JBS*
         LW        R4,IP04.REG,R1  GET DEST REG VALUE IN R4     *JBS*
         BU        SET.MG          CONTINUE ON                  *JBS*
SET.DP   LD        R4,IP04.REG,R1  GET DEST REG VALUE IN R4&R5  *JBS*
*                                                               *JBS*
*        R1 = DESTINATION REG INDEX INTO IP04.REG               *JBS*
*        R2 = SOURCE REG INDEX INTO IP04.REG                    *JBS*
*        R3 = JUMP TABLE INDEX FOR TYPE OF INSTRUCTION          *JBS*
*        R4 (R5) = DESTINATION REG(S)                           *JBS*
*        R7 = H/W INSTRUCTION                                   *JBS*
*                                                               *JBS*
         EAE                       ENABLE ARITH EXCEP           *JBS*
SET.MG   BU        *JMP.TAB,R3     JUMP TO PROPER ROUTINE       *JBS*
*                                                               *JBS*
*        THIS TABLE HAS THE ADDRESSES OF THE CODE TO HANDLE     *JBS*
*        EACH TYPE OF HALFWORD INSTRUCTION.                     *JBS*
*                                                               *JBS*
JMP.TAB  ACH       IP04.COM        3800 - ADR                   *JBS*
         ACH       ADD.W           3801 - ADRFW                 *JBS*
         ACH       IP04.COM        3802 - MPR                   *JBS*
         ACH       SUB.W           3803 - SURFW                 *JBS*
         ACH       DIV.W           3804 - DVRFW                 *JBS*
         ACH       FIX.W           3805 - FIXW                  *JBS*
         ACH       MPY.W           3806 - MPRFW                 *JBS*
         ACH       FLT.W           3807 - FLTW                  *JBS*
         ACH       IP04.COM        3808 - ADRM                  *JBS*
         ACH       ADD.D           3809 - ADRFD                 *JBS*
         ACH       IP04.COM        380A - UNDEFINED             *JBS*
         ACH       SUB.D           380B - SURFD                 *JBS*
         ACH       DIV.D           380C - DVRFD                 *JBS*
         ACH       FIX.D           380D - FIXD                  *JBS*
         ACH       MPY.D           380E - MPRFD                 *JBS*
         ACH       FLT.D           380F - FLTD                  *JBS*
*                                                               *JBS*
*        DO REG-REG FLOATING MUL, DIV, ADD, AND SUB HERE        *JBS*
*                                                               *JBS*
MPY.W    MPFW      R4,IP04.REG,X2  MUL FLT WORD                 *JBS*
         BL        GETCCS          GET CC'S                     *JBS*
DIV.W    DVFW      R4,IP04.REG,X2  DIV FLT WORD                 *JBS*
         BL        GETCCS          GET CC'S                     *JBS*
ADD.W    ADFW      R4,IP04.REG,X2  ADD FLT WORD                 *JBS*
         BL        GETCCS          GET CC'S                     *JBS*
SUB.W    SUFW      R4,IP04.REG,X2  SUB FLT WORD                 *JBS*
         BL        GETCCS          GET CC'S                     *JBS*
*                                                               *JBS*
*        DO REG-REG DOUBLE MUL, DIV, ADD, AND SUB HERE          *JBS*
*                                                               *JBS*
MPY.D    MPFD      R4,IP04.REG,X2  MUL FLT DBL WORD             *JBS*
         BL        GETCCS          GET CC'S                     *JBS*
DIV.D    DVFD      R4,IP04.REG,X2  DIV FLT DBL WORD             *JBS*
         BL        GETCCS          GET CC'S                     *JBS*
ADD.D    ADFD      R4,IP04.REG,X2  ADD FLT DBL WORD             *JBS*
         BL        GETCCS          GET CC'S                     *JBS*
SUB.D    SUFD      R4,IP04.REG,X2  SUB FLT DBL WORD             *JBS*
         BL        GETCCS          GET CC'S                     *JBS*
*                                                               *JBS*
*        DO FIX AND FLOAT WORD HERE                             *JBS*
*                                                               *JBS*
*                                                               *JBS*
*       CONVERT FROM INT TO FLOAT                               *JBS*
*       INPUT   R4 = VALUE TO BE CONVERTED                      *JBS*
*       OUTPUT  R4 = CONVERTED VALUE                            *JBS*
*                                                               *JBS*
FLT.W   LW      R4,IP04.REG,R2  GET SOURCE REG VALUE IN R4      *JBS*
        ZBR     R0,2            CLEAR NEG VAL FLAG              *JBS*
        TRR     R4,R4           IS VALUE ZERO                   *JBS*
        BGT     POSI            BR IF POSITIVE                  *JBS*
        BEQ     ZERO            BR IF ZERO                      *JBS*
        TRN     R4,R4           REG IS NEGATIVE                 *JBS*
        SBR     R0,2            SET NEG FLAG                    *JBS*
POSI    SCZ     R4,R6           COUNT LEADING ZEROS             *JBS*
        SRL     R4,1            BACK UP BY 1 BIT                *JBS*
        SBR     R4,0            SET SIGN BIT                    *JBS*
        TBR     R6,30           WAS COUNT MOD TWO               *JBS*
        BNS     TEST1           BR IF NOT                       *JBS*
        SRL     R4,2            TWO MORE ZERO'S                 *JBS*
TEST1   TBR     R6,31           WAS CNT ODD                     *JBS*
        BNS     TEST2           BR IF NOT                       *JBS*
        SRL     R4,1            ONE MORE BIT                    *JBS*
TEST2   SRL     R6,2            NORMALIZED RADIX                *JBS*
        SUI     R6,72           EXCESS 64 NOTATION              *JBS*
        TRN     R6,R6           MAKE POSITIVE                   *JBS*
        SRC     R6,8            POSITION IN 1ST BYTE            *JBS*
        SRL     R4,8            MAKE ROOM IN FP NUM             *JBS*
        ORR     R6,R4           PUT IT THERE                    *JBS*
        TBR     R0,2            WAS INPUT NEG                   *JBS*
        BNS     ZERO            BR IF NOT                       *JBS*
        TRN     R4,R4           MAKE NEG AGAIN                  *JBS*
ZERO    TRR     R4,R4           SET CC'S                        *JBS*
        BL      GETCCS          GO PUT CC'S IN PSD              *JBS*
*                                                               *JBS*
*       CONVERT FROM FLOAT TO INT                               *JBS*
*       INPUT   R4 = VALUE TO BE CONVERTED                      *JBS*
*       OUTPUT  R4 = CONVERTED VALUE                            *JBS*
*                                                               *JBS*
FIX.W   LW      R4,IP04.REG,R2  GET SOURCE REG VALUE IN R4      *JBS*
        ZBR     R0,2            CLEAR NEG FLAG                  *JBS*
        TRR     R4,R5           WHAT IS DATA                    *JBS*
        BGT     POSF            BR IF POSITIVE                  *JBS*
        BZ      FIRET           BR IF ZERO                      *JBS*
        TRN     R5,R5           MAKE NEG INTO POS               *JBS*
        SBR     R0,2            SET NEG FLAG                    *JBS*
POSF    ZR      R4              CLEAR FOR SHIFT                 *JBS*
        SLLD    R4,8            GET EXP                         *JBS*
        SUI     R4,64           TAKE OFF EXCESS NOTATION        *JBS*
        BLE     FMIN            BR IF VERY SMALL                *JBS*
        SUI     R4,8            SEE IF IN RANGE                 *JBS*
        BGT     FMAX            BR IF TOO BIG                   *JBS*
        TRN     R4,R4           BACK POS FOR SHIFT CNT          *JBS*
        SLL     R4,2            MAKE SHIFT COUNT                *JBS*
        ORMH    R4,SRLI         OR IN SRL INSTR                 *JBS*
        EXRR    R4              DO THE SHIFT                    *JBS*
        TBR     R4,0            SEE IF OVERFLOW TO NEG          *JBS*
        BS      FMAX            BR IF YES                       *JBS*
        TBR     R0,2            ORIGINAL VAL NEG                *JBS*
        BNS     FIRET           RETURN IF NOT                   *JBS*
        TRN     R5,R5           PUT BACK TO NEG                 *JBS*
        BU      FIRET           GO SET CC'S                     *JBS*
FMIN    ZR      R5              RETURN MIN OF ZERO              *JBS*
        BU      FIRET           GO SET CC'S                     *JBS*
FMAX    LI      R5,-1           GET ALL ONES                    *JBS*
        ZBR     R5,0            MAX POS VALUE NOW               *JBS*
FIRET   TRR     R5,R4           RET VAL IN R4                   *JBS*
        BL      GETCCS          GO PUT CC'S IN PSD              *JBS*
SRLI    SRL     R5,0                                            *JBS*
*                                                               *JBS*
*        DO FIX AND FLOAT DOUBLE HERE                           *JBS*
*                                                               *JBS*
*       FLT.D   - CONVERTS FROM 64 BIT INT TO DOUBLE            *JBS*
*       FIX.D   - CONVERTS FROM DOUBLE TO 64 BIT INT            *JBS*
*       INPUT   R4&R5 = VALUE TO BE CONVERTED                   *JBS*
*       OUTPUT  R4&R5 = CONVERTED VALUE                         *JBS*
*                                                               *JBS*
FLT.D    LD        R4,IP04.REG,R2  GET SOURCE REG VALUE IN R4&R5*JBS*
         SBR       R0,4         THIS IS FLT.D ENTRY             *JBS*
         BU        BEG          MERGE CODE                      *JBS*
*                                                               *JBS*
FIX.D    LD        R4,IP04.REG,R2  GET SOURCE REG VALUE IN R4&R5*JBS*
         ZBR       R0,4         THIS IS FIX.D ENTRY             *JBS*
*                                                               *JBS*
BEG      ZBR       R0,2         CLEAR NEG FLAG                  *JBS*
         TRR       R4,R5        ARG IN R4, R5                   *JBS*
         BGT       POS          NUM IS POS                      *JBS*
         BLT       NEG          NUM IS NEG                      *JBS*
         TRR       R5,R5        LOOK FOR ALL ZERO               *JBS*
         BZ        ZERO         NUM IS ZERO                     *JBS*
         BU        POS          SMALL POS                       *JBS*
NEG      EOMD      R4,ALLFS     NEGATIVE NUM                    *JBS*
         SUMD      R4,ALLFS     MAKE IT POSITIVE                *JBS*
         SBR       R0,2         SET NEG FLAG                    *JBS*
POS      TRR       R4,R6        ARG IN R4 TO R6                 *JBS*
         TBR       R0,4         WHAT ARE WE DOING               *JBS*
         BS        C.LD         GO CONV LONG TO DOUBLE          *JBS*
*                                                               *JBS*
* CONVERT DOUBLE TO LONG                                        *JBS*
* ARG IN R6, R5                                                 *JBS*
*                                                               *JBS*
C.DL     SRL       R6,24        EXPONENT IN R6                  *JBS*
         SLLD      R4,8         PURE FRACTION                   *JBS*
         SUI       R6,64        REMOVE EXCESS 64 NOTATION       *JBS*
         BLE       DZERO        TOO SMALL, RET ZER0             *JBS*
         SUI       R6,16        IN RANGE                        *JBS*
         BGT       DMAX         TOO BIG, RETURN MAX             *JBS*
         TRN       R6,R6        MAKE POS SHIFT CNT              *JBS*
         SLL       R6,2         R6 = 4 * (16 - EXP)             *JBS*
         ZBR       R6,26        SEE IF SHIFT COUNT IS >= 32     *JBS*
         BNS       NOS32        NO, GO DBL SHIFT                *JBS*
         TRR       R4,R5        YES, DO TRR TO SHIFT BY 32 BITS *JBS*
         ZR        R4                                           *JBS*
NOS32    ORMH      R6,SRLDI                                     *JBS*
         EXRR      R6           SHIFT R4, R5                    *JBS*
         TBR       R4,0         GO NEG                          *JBS*
         BS        DMAX         SET TO MAX IF YES               *JBS*
TRET     TBR       R0,2         SEE IF IT WAS NEGATIVE          *JBS*
         BNS       DRET         NO, INPUT WAS POS               *JBS*
         EOMD      R4,ALLFS     NEGATIVE                        *JBS*
         SUMD      R4,ALLFS     RETURN NEG VALUE                *JBS*
DRET     CAMD      R6,L.ZERO    SET CC'S                        *JBS*
         BL        GETCCS       GO PUT CC'S IN RET PSD          *JBS*
DZERO    LD        R6,L.ZERO    JUST ZEROS                      *JBS*
         BU        DRET                                         *JBS*
DMAX     LD        R4,ALLFS     GET ALL THE BITS                *JBS*
         ZBR       R4,0         MAKE MAX VALUE                  *JBS*
         BU        DRET                                         *JBS*
*                                                               *JBS*
L.ZERO   DATAD     0                                            *JBS*
ALLFS    DATAD     X'FFFFFFFFFFFFFFFF'                          *JBS*
SRLDI    SRLD      R4,0                                         *JBS*
*                                                               *JBS*
* CONVERT LONG TO DOUBLE                                        *JBS*
* ARG IN R4, R5    (R4 == R6)                                   *JBS*
* ARG > 0                                                       *JBS*
*                                                               *JBS*
C.LD     ZR        R3           FOR EXPONENT                    *JBS*
         ANMW      R6,=X'FF000000'                              *JBS*
         BEQ       LDA          BR FOR ZERO EXP                 *JBS*
         SRLD      R4,8         VERY LARGE, MAKE ROOM FOR EXP   *JBS*
         LI        R3,-2        SET EXP                         *JBS*
LDA      TRR       R4,R6        COPY HI ORDER REG               *JBS*
         ANMW      R6,=X'00F00000'                              *JBS*
         BNE       LDD          BR IF NORMALIZED                *JBS*
         SLLD      R4,4         SHIFT IN NEXT NIBBLE            *JBS*
         ABR       R3,31        ONE MORE POWER OF 16            *JBS*
         BU        LDA          KEEP TRYING                     *JBS*
LDD      TRN       R3,R3        PREP FOR EXCESS 64 NOTATION     *JBS*
         ADI       R3,X'4E'     MAKE EXCESS 64                  *JBS*
         SRC       R3,8         POSITION EXPONENT               *JBS*
         ORR       R3,R4        PUT WITH FRACTION               *JBS*
         BU        TRET         BAIL OUT OF HERE                *JBS*
*                                                               *JBS*
*        GET CC'S FROM OPERATION AND RETURN VALUE FOR USER      *JBS*
*        MERGE BITS 1-4 OF R0 INTO RET PSD                      *JBS*
*        STORE R4 (R5) INTO DEST REGS                           *JBS*
GETCCS   LW        R6,IP04.OLD  GET OLD PSD WD 1                *JBS*
         ANMW      R6,=X'87FFFFFF' CLEAR OLD CC'S               *JBS*
         ANMW      R0,=X'78000000' ALL BUT CC'S FROM R0         *JBS*
         ORR       R0,R6        PUT IN PLACE                    *JBS*
         STW       R6,IP04.OLD  PUT IN PSD                      *JBS*
         TBR       R7,28        WAS THIS DW INSTR               *JBS*
         BS        GET.DW       BR IF DW                        *JBS*
         STW       R4,IP04.REG,X1   RETURN RESULT TO CALLER     *JBS*
         BU        JBS.COM      GOTO EXIT CODE                  *JBS*
*                                                               *JBS*
GET.DW   STD       R4,IP04.REG,X1   RETURN DW RESULT TO CALLER  *JBS*
         BU        JBS.COM      GOTO EXIT CODE                  *JBS*
*                                                               *JBS*
*******************END OF FLOATING POINT SIMULATION CODE*********JBS*
*
         LPOOL                                                      3302
         PAGE
IP04S    EQU       $               INITIALIZATION ENTRY POINT       #E#
         M.EIR
         TBM       C.NOBASE,C.CONF                                  3302
         BNS       IP04S.1          BASE CODE NOT TO BE OVERLAYED   3302
*JBS*    LA        R5,IP04.OVY      OVERLAY ADDRESS                 3302
*JBS*    STW       R5,SG.HAT        PUT INTO HAT TABLE              3302
*JBS*    LW        R6,=X'00020002'  NOP BRANCH                      3302
*JBS*    STW       R6,IP4.NOP1      TO BASE CODE                    3302
IP04S.1  EQU       $                                                3302
         LB        R6,C.MACH
         CI        R6,2
         BGE       IP04.42
IP04.7X  EQU       $
         LA        R6,IP04.ICB
         STW       R6,X'194'       STORE ICB ADDRESS IN IVL
         LI        R6,X'194'       GET IVL ADDRESS
         LW        R1,C.SPAD       GET BASE ADDRESS
         ADI       R1,X'25'+X'80'*4  ADD IN OFFSET
         STW       R6,0,R1         PUT INTO SPAD IMAGE
         BU        IP04.LT
IP04.42  EQU       $
         M.TRPINT  X'4',IP04.ICB
IP04.LT  EQU       $
         BU        SG.XI
         DATAB     C'(C) COPYRIGHT 1983 GOULD INC.,'
         DATAB     C' COMPUTER SYSTEMS DIVISION'
         DATAB     C' ALL RIGHTS RESERVED'
SG.XI    EQU       $
         M.XIR     HAT
         END
