*MPX-32 MACRO ASSEMBLER 3.4.0  MPX-32 UTILITIES 3.4.0 HEADER    SJ.ASSM
UNIXF    SETT                      SET FOR UNIX VER OF ASSEMBLE *JCB*
ULC      SETT                      SET FOR UPPER/LOWER CASE SYM *JCB*
CAID     SETT                      SET FOR C AID DEBUGGER VER   *CAID*
         SPACE     2
************************************************************************
*                                                                      *
*                        RESTRICTED RIGHTS                             *
*                        -----------------                             *
*    THE INFORMATION CONTAINED HEREIN IS PROPRIETARY TO ENCORE         *
*    COMPUTER CORPORATION, AND/OR ITS SUPPLIERS, AND ITS USE,          *
*    DISCLOSURE, OR DUPLICATION IS SUBJECT TO THE RESTRICTIONS STATED  *
*    IN THE ENCORE COMPUTER CORPORATION LICENSE AGREEMENT OR           *
*    THE APPROPRIATE THIRD-PARTY SUBLICENSE AGREEMENT.  INFORMATION IS *
*    PROVIDED TO GOVERNMENT CUSTOMERS WITH RESTRICTED RIGHTS AS        *
*    DESCRIBED IN DAR 7-104.9(A).                                      *
*                                                                      *
************************************************************************
*
* (C) COPYRIGHT 1983 ENCORE COMPUTER CORPORATION
*     ALL RIGHTS RESERVED
************************************************************************
         SPACE     2
         IFF       UNIXF,SKIP                                   *JCB*
         PROGRAM   ASSEMBLE        ASSEMBLE.R3.4.0.05
SKIP     ANOP                                                   *JCB*
         IFT       UNIXF,SKIP                                   *JCB*
*        PROGRAM   NBCAS           ASSEMBLE.R3.4.0.05           *JCB*
*        PROGRAM   NBCAS           ASSEMBLE.R3.4.0.06           *JCB*
*        PROGRAM   NBCAS           ASSEMBLE.R3.4.0.07           *JCB*
*        PROGRAM   NBCAS           ASSEMBLE.R3.4.0.08           *JCB*
         PROGRAM   NBCAS           ASSEMBLE.R3.4.0.09           *JCB*
SKIP     ANOP                                                   *JCB*
         SPACE     2
         TITLE     ASSEMBLE - MODIFICATION HISTORY
*                                                                1.3#03
*CHANGE MARKER    1.3#03                                         1.3#03
*                                                                1.3#03
*  MODIFICATION TO CORRECT VALUE IN THE FINAL ORG OBJECT TOKEN   1.3#03
*                                                                1.3#03
*    PART OF PASS 2 END STATEMENT PROCESSING IS TO OUTPUT A      1.3#03
*  PROGRAM ORIGIN TO THE OBJECT CODE STREAM AS THE FINAL ITEM.   1.3#03
*  THE VALUE OF THIS ITEM SHOULD BE THE NEXT AVAILABLE ADDRESS   1.3#03
*  OF THE IMPLICIT DSECT (EXPLITLY SECTIONED CODE WILL CONTAIN   1.3#03
*  THE SECTION SIZES IN THE SECTION DEFINITIONS AND THE ORG IS   1.3#03
*  SUPPRESSED). PRIOR TO THIS CORRECTIVE ACTION, THE VALUE USED  1.3#03
*  WAS ACTUALLY THE NEXT AVAILABLE LOCATION IN THE AREA ACTIVE   1.3#03
*  WHEN THE END STATEMENT WAS REACHED, INCLUDING A COMON AREA.   1.3#03
*  THE CORRECTIVE ACTION IS TO OUTPUT THE VALUE FROM VARIABLE    1.3#03
*  "DSIZE" INSTEAD OF FROM "HWLTPE". THIS ALLOWS THE LITERAL     1.3#03
*  POOL TO BE IMPLICITLY DEPOSITED IN ANY AREA WHILE ASSURING    1.3#03
*  THAT THE FINAL ORG SHOWS THE REQUIRED VALUE.                  1.3#03
*                                                                1.3#03
*   UPDATES PROGRAM DIRECTIVE TO VERSION 1.3.03                  1.3#03
*                                                                1.3#03
*--------------------------------------------------------------- 1.3#03
*
* CHANGE MARKERS   |YY.NNNN   CORRECT THE FOLLOWING SPR'S:
*
*                   85.0780
*                   85.1166
*                   85.1302
*                   86.0324
*                   86.0696
*                   86.952
*
*     UPDATES VERSION TO 1.3.04
*
*-----------------------------------------------------------------------
*
*        CHANGE MARKER 1.3#05
*
*    REMOVE OPTION 16 AS AN EXTERNALLY CONTROLLED OPTION.
*
*    UPDATES VERSION TO 1.3.05
*
*-----------------------------------------------------------------------
*
*        CHANGE MARKER 1.3#06
*
*    MODIFIED TO ALWAYS WRITE PRODUCT/COPYRIGHT ON LFC=UT
*
*-----------------------------------------------------------------------
*
*        CHANGE MARKER |1.3Q32
*
*        TO CORRECT PROBLEM IN 2.3 RELATING TO OUTPUT TO SLO
*        USING UTFCB.
*
************************************************************************
*
*        ASSEMBLE REVISION 3 RELEASE 3.0 CHANGE HISTORY (SUSTAINING)
*
************************************************************************
*
*        VERSION   3.0.01
*
*        S8700508  04/22/87  10032 ADDED CODE TO DETECT         S8700508
*                                  ATTEMPTS TO ORG PAST THE     S8700508
*                                  END OF A COMMON AREA AND     S8700508
*                                  FLAG IT AS AN ERROR.         S8700508
*
*        S8700512  04/22/87  10032 ADDED CODE TO CORRECTLY      S8700512
*                                  HANDLE BACKWARD ORG'S        S8700512
*                                  AND REPORT THE CORRECT       S8700512
*                                  LOAD MODULE SIZE TO THE      S8700512
*                                  CATALOGER.                   S8700512
*
*        VERSION   3.0.02
*
*        S8700512B 06/22/87  10032 FURTHER CORRECTIONS MADE TO S8700512B
*                                  CODE RELATED TO SPR FIX     S8700512B
*                                  S8700512.                   S8700512B
*
*        VERSION   3.0.03
*
*        C007-30   08/21/87  10032 REPOSITIONED A LINE OF CODE  C007-30
*                                  THAT WAS MOVED BY AN SPR FIX C007-30
*                                  THIS CAUSED ADDRESSING       C007-30
*                                  PROBLEMS WHEN "ORGING" INTO  C007-30
*                                  COMMON BLOCKS.               C007-30
*
*        VERSION   3.0.04
*
*        S8701703  11/09/87  10032 FIXED CODE ADDED FOR SPR #   S8701703
*                                  S8700508. COMMON BLOCK SIZES S8701703
*                                  WERE NOT COMPUTED CORRECTLY  S8701703
*                                  WHICH CAUSED VALID 'ORG'     S8701703
*                                  STATEMENTS TO BE FLAGGED AS  S8701703
*                                  ERRORS (TRYING TO ORG BEYOND S8701703
*                                  END OF COMMON).              S8701703
*                                  THIS FIX IS AN UPDATE TO THE S8701703
*                                  RELEASED VERSION (3.0.03) OF S8701703
*                                  THE ASSEMBLER. THIS FIX ALSO S8701703
*                                  CORRECTS SPR #'S 87001812 &  S8701703
*                                  87001832.                    S8701703
*
*        VERSION   3.0.05
*
*        S8702087  02/11/88  10032 ADDED CODE TO BYPASS EXPONENTS8702087
*                                  PROCESSING CODE FOR FLOAT-   S8702087
*                                  ING POINT DATA WHEN THE      S8702087
*                                  EXPONENT IS ZERO. E'-5.0'    S8702087
*                                  AND E'-5.0E0' BOTH GENERATE  S8702087
*                                  THE SAME HEX REPRESENTATION. S8702087
*
************************************************************************
*
*        ASSEMBLE REVISION 3 RELEASE 3.1 CHANGE HISTORY (SUSTAINING)
*
************************************************************************
*
*        VERSION   3.1.01
*
*        ELFC-31   09/07/88  10032 CODE ADDED TO SUPPORT        ELFC-31
*                                  CONSISTENT LFC'S.            ELFC-31
*
*        VERSION   3.1.02
*
*        S880752   11/07/88  5199                               S880752
*                  CODE ADDED TO MOVE THE SYMBOL TABLE STORAGE  S880752
*                  TO EXTENDED MEMORY TO ALLOW A LARGER NUMBER  S880752
*                  OF SYMBOLS IN A PROGRAM. TO ACCOMPLISH THIS, S880752
*                  THE LINKED LISTS FOR MACRO PROTOTYPE STORAGE S880752
*                  AND THE SYMBOL TABLE ARE INTER-MIXED IN      S880752
*                  EXTENDED MEMORY. THIS REQUIRES A COMMON      S880752
*                  POINT OF ALLOCATION FOR EXTENDED MEMORY      S880752
*                  WHICH IS NOT CURRENTLY THE CASE. THE         S880752
*                  FOLLOWING STEPS ARE IMPLEMENTED:             S880752
*                                                               S880752
*                - REMOVE ALL "RECORD MANAGER" CALLS FROM THE   S880752
*                  ASSEMBLER. CONVERT ALL FCB'S TO 16 WORDS.    S880752
*                  ESTABLISH PERMANENT EXTENDED MEMORY.         S880752
*                  REORGANIZE THE CROSS REFERENCE LISTING       S880752
*                  GENERATOR SO AS TO SEPARATE THE LIST         S880752
*                  FORMATTING AND "SHELL SORT" CODE INTO        S880752
*                  CALLABLE SUBROUTINES. THIS LAST STEP IS      S880752
*                  PRELIMINARY TO REPLACING THE REMAINDER OF    S880752
*                  THIS CODE WITH NEW CODE THAT UTILIZES        S880752
*                  EXTENDED MEMORY FOR ITS SORT AND MERGE       S880752
*                  BUFFERS.                                     S880752
*                                                               S880752
*                  NOTE: IN MAKING THESE CHANGES, THE           S880752
*                  "CKBYTCNT" ROUTINE BECAME USELESS AND WAS    S880752
*                  REMOVED                                      S880752
*                                                               S880752
*                - MODIFY THE SYMBOL TABLE WORKER ROUTINES SO   S880752
*                  THAT THE SYMBOL TABLE ENTRIES ARE PUT INTO   S880752
*                  THE EXTENDED MEMORY AREA. THE CONTROL        S880752
*                  VARIABLES USED FOR MACRO STORAGE MANAGEMENT  S880752
*                  ARE NOW ALSO USED BY THE SYMBOL TABLE        S880752
*                  ROUTINES. THE 6TH WORD OF THE SYMBOL TABLE   S880752
*                  ENTRY IS NOW USED TO LINK THE ENTRIES        S880752
*                  TOGETHER IN THE ORDER OF ALLOCATION.         S880752
*                                                               S880752
*                - A NEW VERSION OF THE CROSS REFERENCE         S880752
*                  GENERATOR IS ADDED. THIS IS NECCESSARY       S880752
*                  BECAUSE THE OLD VERSION OVERLAYS THE SYMBOL  S880752
*                  TABLE AREA WITH ITS SORT BUFFER. THE OLD     S880752
*                  ALGORITHM COULD NOT BE MODIFIED TO USE       S880752
*                  EXTENDED MEMORY. THE NEW VERSION OVERLAYS    S880752
*                  ALL OF THE SYMBOL TABLE AND MACRO STORAGE.   S880752
*                  THERE IS NO CHANGE IN FUNCTIONALITY.         S880752
*
*        EINS-31   11/07/88  5199                               EINS-31
*        IMPLEMENTATION OF SUPPORT FOR UN-MAPPED INSTRUCTIONS.  EINS-31
*        THE FOLLOWING MNEMONICS ARE ADDED TO THE NON-BASE      EINS-31
*        OPCODE TABLE:                                          EINS-31
*                                                               EINS-31
*             LCB     LOAD THROUGH CONTEXT BYTE                 EINS-31
*             LCH       "     "       "    HALFWORD             EINS-31
*             LCW       "     "       "    WORD                 EINS-31
*             LCD       "     "       "    DOUBLEWORD           EINS-31
*                                                               EINS-31
*             STCB    STORE THROUGH CONTEXT BYTE                EINS-31
*             STCH      "      "       "    HALFWORD            EINS-31
*             STCW      "      "       "    WORD                EINS-31
*             STCD      "      "       "    DOUBLEWORD          EINS-31
*                                                               EINS-31
*             LCRA    LOAD THROUGH CONTEXT REAL ADDRESS         EINS-31
*                                                               EINS-31
*        THE "THROUGH CONTEXT" DESCRIPTION MEANS THAT WHEN      EINS-31
*        OPERATING UN-MAPPED, THE PROCESSOR WILL TREAT THE      EINS-31
*        EFFECTIVE OPERAND ADDRESS AS A LOGICAL ADDRESS AND     EINS-31
*        CONVERT IT BASED ON THE CURRENT CONTENTS OF THE MAP    EINS-31
*        RAM (I.E. THIS CAN BE VIEWED AS MAKING THE PROCESSOR   EINS-31
*        GO "MAPPED-RETAIN" FOR THE DURATION OF THIS            EINS-31
*        INSTRUCTION). THESE MNEMONICS ACT EXACTLY LIKE         EINS-31
*        "NORMAL" LOADS/STORES WHEN EXECUTED IN A MAPPED        EINS-31
*        ENVIRONMENT.                                           EINS-31
*                                                               EINS-31
*        THE PURPOSE OF THESE INSTRUCTIONS IS TO SUPPORT AND    EINS-31
*        ALLOW THE IMPLEMENTATION OF RESIDENT OPERATING SYSTEMS EINS-31
*        WHICH EXECUTE "UN-MAPPED" FROM THE LOGICAL TASK SPACE. EINS-31
*        THERE IS NO REASON TO EVER UTILIZE THESE INSTRUCTIONS  EINS-31
*        IN TASK LEVEL CODE (BECAUSE THE INSTRUCTIONS ACT LIKE  EINS-31
*        NORMAL LOAD/STORE'S WHEN MAPPED, NO HARM IS DONE BY    EINS-31
*        SUCH USE).                                             EINS-31
*                                                               EINS-31
*        THE "THROUGH CONTEXT" INSTRUCTIONS ARE PART OF AN      EINS-31
*        "ENHANCED INSTRUCTION SET" WHICH IS NOT AVAILABLE TO   EINS-31
*        ALL PROCESSORS. IN ORDER THAT A SINGLE OPERATING       EINS-31
*        SYSTEM IS ABLE TO EXECUTE ON BOTH PROCESSOR TYPES      EINS-31
*        (I.E. THOSE WITH AND THOSE WITHOUT THE ENHANCED        EINS-31
*        INSTRUCTIONS), A SCHEME HAS BEEN DEVISED THAT ALLOWS   EINS-31
*        THE OBJECT CODE PRODUCED FROM A "THROUGH CONTEXT"      EINS-31
*        MNEMONIC TO VARY DEPENDING ON THE INTENDED TARGET.     EINS-31
*        TWO DISTINCT MODES OF KERNEL OPERATION ARE SUPPORTED.  EINS-31
*        THE "MAPPED" MODE IMPLIES THAT THE KERNEL EXECUTES     EINS-31
*        MAPPED INTO THE TASK LOGICAL ADDRESS SPACE (I.E. THE   EINS-31
*        TRADITIONAL MODE). THE "UN-MAPPED" MODE IMPLIES THAT   EINS-31
*        THE KERNEL EXECUTES OUTSIDE THE LOGICAL ADDRESS SPACE  EINS-31
*        OF THE TASK. PROCESSORS WHICH DO NOT SUPPORT THE       EINS-31
*        ENHANCED INSTRUCTION SET MAY EXECUTE THE KERNEL ONLY   EINS-31
*        IN "MAPPED" MODE. PROCESSORS WHICH DO HAVE THE         EINS-31
*        ENHANCED INSTRUCTION SET WILL SUPPORT EITHER MODE OF   EINS-31
*        OPERATION.                                             EINS-31
*                                                               EINS-31
*        THE OBJECT CODE PRODUCED BY THE "THROUGH CONTEXT"      EINS-31
*        MNEMONICS IS CONTROLLED BY THE "SET ENHANCED           EINS-31
*        INSTRUCTION SET" (SEIS) AND "RESET ENHANCED            EINS-31
*        INSTRUCTION SET" (REIS) ASSEMBLER DIRECTIVES. WHEN IN  EINS-31
*        "REIS" MODE (WHICH IS THE DEFAULT), THE ASSEMBLER      EINS-31
*        PRODUCES THE MACHINE CODE FOR NORMAL LOADS AND STORES  EINS-31
*        FROM THE THROUGH CONTEXT MNEMONICS. WHEN IN "SEIS"     EINS-31
*        MODE THE ASSEMBLER WILL PRODUCE THE ENHANCED MACHINE   EINS-31
*        CODE.                                                  EINS-31
*                                                               EINS-31
*        TO UTILIZE THIS CAPABILITY, RESIDENT OPERATING SYSTEM  EINS-31
*        MODULES ARE CODED USING THE "THROUGH CONTEXT" MNEMONIC EINS-31
*        WHERE EVER THE CODE REFERENCES ANY TASK ADDRESS SPACE  EINS-31
*        DATA. THE CODE MAY THEN BE TARGETED TO EITHER THE      EINS-31
*        "MAPPED" OR "UNMAPPED" ENVIRONMENT VIA THE CONDITIONAL EINS-31
*        ASSEMBLY OF THE APPROPRIATE "REIS" OR "SEIS"           EINS-31
*        DIRECTIVES RESPECTIVELY.                               EINS-31
*
*        VERSION   3.1.03
*
*        01/10/89  10032   FURTHER CODE CHANGES MADE TO FIX     S880752
*                          SPR #88000752.                       S880752
*
************************************************************************
*
*        ASSEMBLE REVISION 3 RELEASE 3.2 CHANGE HISTORY (SUSTAINING)
*
************************************************************************
*
*        VERSION   3.2.01
*
*        EBMI-32   02/14/89  10032 ADDED UNMAPPED MPX SUPPORT   EBMI-32
*                                  INSTRUCTIONS TO THE BASE     EBMI-32
*                                  MODE OPCODE TABLE.           EBMI-32
*
*        VERSION   3.2.02
*
*
*        ENIS-32   02/28/89  10032 ADDED NEW CONCEPT 32/2000    ENIS-32
*                                  INSTRUCTIONS TO THE OPCODE   ENIS-32
*                                  TABLE AS WELL AS CEQU/DEQU   ENIS-32
*                                  AND CORG/DORG FOR AUTO       ENIS-32
*                                  SECTIONING. IN THIS VERSION  ENIS-32
*                                  HOWEVER, CEQU/DEQU AND CORG/ ENIS-32
*                                  DORG DO NOT HAVE THE NEEDED  ENIS-32
*                                  FUNCTIONALITY FOR AUTO       ENIS-32
*                                  SECTIONING. BOTH VERSIONS    ENIS-32
*                                  OF EACH DIRECTIVE WORK THE   ENIS-32
*                                  SAME AS THE CURRENT EQU AND  ENIS-32
*                                  ORG DIRECTIVES.              ENIS-32
*
*        VERSION 3.2.03
*
*        EASC-32   04/04/89   AUTO SECTIONED CODE OPTION        EASC-32
*                                                               EASC-32
*            THIS ENHANCEMENT PROVIDES OPTION 18 TO INVOKE      EASC-32
*          AUTO-SECTIONED CODE GENERATION. UNDER THE OPTION,    EASC-32
*          EACH LINE OF SOURCE CODE IS DIRECTED TO THE CSECT    EASC-32
*          OR DSECT DEPENDING ON THE OPCODE FIELD. IN GENERAL   EASC-32
*          CODE GENERATING OPCODES ARE DIRECTED TO THE CSECT    EASC-32
*          AND DATA GENERATING OPCODES ARE DIRECTED TO THE      EASC-32
*          DSECT.                                               EASC-32
*                                                               EASC-32
*        IN ADDITION:                                           EASC-32
*                                                               EASC-32
*      - ANY DSECT/CSECT DIRECTIVES ARE IGNORED.                EASC-32
*      - THE SYMBOL $ IS ILLEGAL IN ANY EXPRESION RELATED TO    EASC-32
*        AN "EQU" OR "ORG" DIRECTIVE. THESE MUST BE CHANGED     EASC-32
*        TO THE NEW DIRECTIVES "CEQU"/"DEQU" AND "CORG"/"DORG"  EASC-32
*        RESPECTIVELY.                                          EASC-32
*      - A "BOUND" DIRECTIVE IS DEFERRED UNTIL THE NEXT LINE    EASC-32
*        OF SOURCE CODE. THE BOUND IS THEN APPLIED TO THE       EASC-32
*        SECTION ESTABLISHED BY THAT LINE. THEREFORE, MULTIPLE  EASC-32
*        SEQUENTIAL BOUND DIRECTIVES IS NOT SUPPORTED.          EASC-32
*
*
*        VERSION 3.2.04
*
*        ESCT-32   04/04/89        MODIFY ASSEMBLER CODE TO     ESCT-32
*                                  ALLOW IT TO BE AUTO          ESCT-32
*                                  SECTIONED.                   ESCT-32
*
*        VERSION   3.2.05
*
*        ELST-32   05/03/89  10032 ADDED CODE TO PLACE OBJECT   ELST-32
*                                  TYPE VALUE INTO PROGRAM NAME ELST-32
*                                  OBJECT RECORD. THIS SUPPORTS ELST-32
*                                  GENERATION OF 2.5 MB TASKS.  ELST-32
*
*        C009-32   05/03/89  10032 CHANGED DI/SI FILE ACCESS    C009-32
*                                  MODE FROM UPDATE TO READ.    C009-32
*
*        VERSION   3.2.06
*
*        ELST-32   05/24/89  10032 MODIFIED SECTION EXTERNAL    ELST-32
*                                  REFERENCE PROCESSING SO AS   ELST-32
*                                  TO SUPPORT THE GENERATION OF ELST-32
*                                  2.5 MB SEGMENTED TASKS. TWO  ELST-32
*                                  SEPERATE STRINGBACK LISTS    ELST-32
*                                  ARE MAINTAINED. ONE FOR REFS ELST-32
*                                  IN THE DSECT AND ONE FOR     ELST-32
*                                  CSECT REFERENCES.            ELST-32
*
*        VERSION   3.2.07
*
*        ETCM-32   09/21/89  10032 CODE ADDED TO PROVIDE SOURCE ETCM-32
*                                  PROCESSOR TASK CODE          ETCM-32
*                                  MANAGEMENT SUPPORT. OUTPUT   ETCM-32
*                                  OF DATE/TIME OBJECT RECORD   ETCM-32
*                                  (OPTION 15) IS NOW AUTOMATIC ETCM-32
*
*        C010-32   10/30/89  10032 CODE ADDED TO CORRECT A      C010-32
*                                  PROBLEM WITH CREATING CROSS  C010-32
*                                  REFERENCES.                  C010-32
*
*        PR10988   10/30/89  10032 CODE ADDED TO CHECK IF       PR10988
*                                  LFC'S LO,GO, AND BO(DO) ARE  PR10988
*                                  ASSIGNED TO VOLUME RESOURCES PR10988
*                                  AND TO NOT SET UP THEIR      PR10988
*                                  BLOCKING BUFFERS IF THEY ARE PR10988
*                                  NOT VOLUME RESOURCES.        PR10988
*
*        VERSION   3.2.08
*
*        PR10574   11/03/89  10032 MODIFIED ENTRIES IN BOTH     PR10574
*                                  OPSTAB AND OPSTABBA FOR      PR10574
*                                  ZBDMS AND SBDMS INSTRUCTIONS PR10574
*                                  THE AUGMENT CODE WAS NOT     PR10574
*                                  CORRECT.                     PR10574
*
************************************************************************
*
*        ASSEMBLE REVISION 3 RELEASE 3.2U01 CHANGE HISTORY
*
************************************************************************
*
*        VERSION   3.2.09
*
*        ENIS-32B  03/09/90  10032 ADDED PINTV AND RINTV        ENIS-32B
*                                  INSTRUCTIONS.                ENIS-32B
*
*        EIFD-32   03/09/90  10032 ADDED IFTDEF AND IFFDEF      EIFD-32
*                                  ASSEMBLE DIRECTIVES          EIFD-32
*
*        VERSION   3.2.10
*
*        ENIS-32C  03/14/90  10032 CORRECTIONS TO PINTV/RINTV   ENIS-32C
*                                  INSTRUCTION IMPLEMENTATION   ENIS-32C
*
************************************************************************
*
*        ASSEMBLE REVISION 3 RELEASE 3.2U02 CHANGE HISTORY
*
************************************************************************
*
*        VERSION   3.2.11
*
*        S900289   05/29/90  10032 CORRECTED PROBLEM WITH       S900289
*                                  IMPROPER REQUIRED FILES      S900289
*                                  COUNTS BEING PLACED IN TCM   S900289
*                                  RECORDS FOR PROGRAMS         S900289
*                                  FOLLOWING THE FIRST PROGRAM  S900289
*
*
*        VERSION 3.2.12
*
*                06/06/90   5199  ADDED NEW MNEMONICS FOR THE IEEE
*                                 FLOATING POINT CONVERSION INSTR.
*                                 ADDED MNEMONICS FOR THE SA2000
*                                 INSTRUCTIONS.
*
*       THERE IS NO TAGS FOR THIS CHANGE DUE TO THE FORMAT OF THE
*       INSTRUCTION TABLE
*
************************************************************************
*
*        ASSEMBLE REVISION 3 RELEASE 3.2U04 CHANGE HISTORY
*
************************************************************************
*
*        VERSION   3.2.13
*
*        ERSC-32   10/10/90  10032 ADDED RISC INSTRUCTIONS      ERSC-32
*
*        VERSION   3.2.14
*
*        ERSC-32B  10/25/90  10032 CORRECTED BOUNDING ON        ERSC-32B
*                                  SEVERAL RISC INSTRUCTIONS    ERSC-32B
*
************************************************************************
*
*        VERSION   3.2.15
*
*        S910307   04/19/91  10032 CORRECT GFPC AND RFPD        S910307
*                                  INSTRUCTIONS. WRONG REGISTER S910307
*                                  WAS BEING CHECKED FOR EVEN   S910307
*                                  (DOUBLEWORD) NUMBER.         S910307
*
*        THIS VERSION OF ASSEMBLE IS AVAILABLE AS A PATCH FROM
*        CUSTOMER SERVICE.
*
************************************************************************
*
*        ASSEMBLE REVISION 3 RELEASE 3.2U06 CHANGE HISTORY
*
************************************************************************
*
*        VERSION   3.2.16
*
*        ETCM-32B  07/08/91  10032 ADDED OPTIONAL CONTROL FOR   ETCM-32B
*                                  PLACEMENT OF TCM RECORDS     ETCM-32B
*                                  IN OBJECT FILE.              ETCM-32B
*
*        VERSION   3.2.17
*
*        PR12035   07/23/91  10032 ADDED CODE TO CORRECT A      PR12035
*                                  PROBLEM WITH GENERATING      PR12035
*                                  NEGATIVE FLOATING POINT      PR12035
*                                  NUMBERS WITH A ZERO EXPONENT PR12035
*
*        VERSION   3.2.18
*
*        ETCM-32C  08/08/91  10032 THE OPTIONAL CONTROL FOR     ETCM-32C
*                                  TCM RECORD PLACEMENT ALSO    ETCM-32C
*                                  CONTROLS THE PLACEMENT OF    ETCM-32C
*                                  THE DATE/TIME RECORD INTO    ETCM-32C
*                                  THE OBJECT FILE.             ETCM-32C
*
************************************************************************
*
*        ASSEMBLE REVISION 3 RELEASE 3.3 CHANGE HISTORY
*
************************************************************************
*
*        VERSION   3.3.01
*
*        EIEE-33   06/06/91  10032 CODE ADDED TO GENERATE       EIEE-33
*                                  IEEE-754 FORMAT FLOATING     EIEE-33
*                                  POINT NUMBERS WHEN OPTION    EIEE-33
*                                  55 IS SET.                   EIEE-33
*
*        VERSION   3.3.02
*
*        EIEE-33B  10/15/91  10032 FURTHER MODIFICATIONS MADE   EIEE-33B
*                                  IEEE-754 FLOATING POINT      EIEE-33B
*                                  SUPPORT CODE.                EIEE-33B
*
*        PR12063   10/16/91  10032 CODE ADDED TO REACTIVATE     PR12063
*                                  OPTION 15 WHEN OPTION 17 IS  PR12063
*                                  SET. WHEN OPTION 17 IS SET,  PR12063
*                                  OPTION 15 CAN BE SET OR      PR12063
*                                  RESET AS DESIRED BY THE USER.PR12063
*                                  WHEN OPTION 17 IS RESET,     PR12063
*                                  OPTION 15 IS SET BY DEFAULT  PR12063
*                                  AND THE OBJECT PRODUCED WILL PR12063
*                                  HAVE A DATE/TIME RECORD.     PR12063
*
*        ENPC-33   10/25/91  10032 MODIFIED SOURCE LINE         ENPC-33
*                                  PROCESSING TO INHIBIT OUTPUT ENPC-33
*                                  OF SOURCE LINES BEGINNING    ENPC-33
*                                  WITH *! WHEN OPTION 56 IS    ENPC-33
*                                  SET. THIS PROVIDES FOR       ENPC-33
*                                  NON-PRINTING COMMENT LINES.  ENPC-33
*
*        VERSION   3.3.03
*
*        EBAC-33   11/04/91  10032 CODE ADDED TO GENERATE       EBAC-33
*                                  D00F TYPE OBJECT RECORDS FOR EBAC-33
*                                  24 BIT BIASED ADDRESS        EBAC-33
*                                  CONSTANTS (BACW,BACH).       EBAC-33
*
*        VERSION   3.3.04
*
*        EBAC-33B  11/12/91  10032 MORE CODE ADDED FOR BACX     EBAC-33B
*                                  SUPPORT. THE SECTION NUMBER  EBAC-33B
*                                  THAT THE ADDRESS IS IN IS    EBAC-33B
*                                  NOW PLACED IN THE OBJECT     EBAC-33B
*                                  RECORD. THIS ALLOWS CATALOG  EBAC-33B
*                                  TO PROPERLY RELOCATE THE     EBAC-33B
*                                  ADDRESS.                     EBAC-33B
*
*        VERSION   3.3.05
*
*        EBAC-33C  12/03/91  10032 CODE ADDED TO ALLOW A BACX   EBAC-33C
*                                  TO AN EXTERNAL TO TERMINATE  EBAC-33C
*                                  THE STRINGBACK LIST. A       EBAC-33C
*                                  SPECIAL TERMINATOR VALUE OF  EBAC-33C
*                                  8FFFF SIGNALS THE END OF THE EBAC-33C
*                                  LIST AND THAT THIS FINAL     EBAC-33C
*                                  VALUE SHOULD HAVE THE CSECT  EBAC-33C
*                                  ORIGIN ADDRESS ADDED TO IT.  EBAC-33C
*
*        VERSION   3.3.06
*
*        C011-33   01/24/92  10032 ADDED CODE TO FORCE          C011-33
*                                  NORMALIZATION OF SINGLE      C011-33
*                                  PRECISION FLOATING POINT     C011-33
*                                  NUMBERS AFTER THEY HAVE BEEN C011-33
*                                  TRUNCATED FROM DOUBLE        C011-33
*                                  PRECISION.                   C011-33
*
*        VERSION   3.3.07
*
*        ENSB-33   03/4/92  10032  ADDED OPTION 11 TO CONTROL   ENSB-33
*                                  STRINGBACK OF NON-BRANCH     ENSB-33
*                                  CSECT EXTERNAL REFERENCES.   ENSB-33
*                                  IF SET, THESE REFERENCES     ENSB-33
*                                  ARE NOT STRUNGBACK. CORRECTS ENSB-33
*                                  PROBLEM WITH CATALOG         ENSB-33
*                                  BEING UNABLE TO RELOCATE     ENSB-33
*                                  STRINGBACK ADDRESSES ABOVE   ENSB-33
*                                  .5 MB.                       ENSB-33
*
************************************************************************
*
*        ASSEMBLE REVISION 3 RELEASE 3.4.0 CHANGE HISTORY
*
************************************************************************
*
*        VERSION   3.4.0.01
*
*        S900555   05/05/92  10032 ADDED CODE TO IGNORE BLANK   S900555
*                                  LINES IN THE SOURCE FILE.    S900555
*
*        S920209   05/05/92  10032 ADDED CODE TO CHECK FOR      S920209
*                                  PROGRAM COUNTER OVERFLOW     S920209
*                                  ABOVE 80000(16).             S920209
*
*        VERSION   3.4.0.02
*
*        C012-34   07/07/92  10032 MODIFIED PROGRAM DIRECTIVE   C012-34
*                                  PROCESSOR TO ALLOW A COMMA   C012-34
*                                  TO TERMINATE THE NAME FIELD. C012-34
*                                  ALSO REMOVED LINES THAT      C012-34
*                                  CAUSED THE PROGRAM ID INFO   C012-34
*                                  TO BE PROCESSED ONLY DURING  C012-34
*                                  THE SECOND PASS. THIS ALLOWS C012-34
*                                  MACRO CODING OF THE PROGRAM  C012-34
*                                  DIRECTIVE.                   C012-34
*
*        S920183   07/10/92  10032 CODE WAS ADDED TO THE SYMBOL S920183
*                                  TABLE WORKER ROUTINE TO      S920183
*                                  CORRECTLY PROCESS EXTERNAL   S920183
*                                  REFERENCES THAT APPEAR       S920183
*                                  PRIOR TO THE EXT DIRECTIVE   S920183
*                                  THAT IDENTIFIES THE SYMBOL   S920183
*                                  THEY REFERENCE AS EXTERNAL.  S920183
*
*        VERSION   3.4.0.03
*
*        S900542   08/03/92  10032 CODE ADDED TO DETECT IF THE  S900542
*                                  RESULT OF AN EXPRESSION IS   S900542
*                                  NEGATIVE. A TYPE N ASSEMBLE  S900542
*                                  ERROR IS OUTPUT TO INFORM    S900542
*                                  THE USER. ALSO CORRECTS      S900542
*                                  SPR 89001042.                S900542
*
*        EIEE-34C  08/27/92  10032 CORRECT BIT SETTINGS IN THE  EIEE-34C
*                                  FLOATING POINT CONTEXT REG.  EIEE-34C
*
*        VERSION   3.4.0.04
*
*        S900542B  09/17/92  10032 CODE ADDED TO ONLY REPORT    S900542B
*                                  NEGATIVE EXPRESSION RESULTS  S900542B
*                                  AS ERRORS WHEN THEY APPEAR   S900542B
*                                  IN RES AND REZ STATEMENTS.   S900542B
*
*        VERSION   3.4.0.05
*
*        EIEE-34D  11/13/92  10032 CHANGED BRANCH IN ATOF       EIEE-34D
*                                  ROUTINE SO VALUES WITH AN    EIEE-34D
*                                  EXPONENT OF 7FF OR ABOVE     EIEE-34D
*                                  ARE TREATED AS OUT OF RANGE  EIEE-34D
*                                  VALUES.                      EIEE-34D
*
*        VERSION   3.4.0.09
*
*        IEEE-MOD  08/09/95  *JCB* Support for .cd2f/.cf2d      IEEE-MOD
*
************************************************************************
* END OF MODIFICATION HISTORY
         TITLE     ASSEMBLE
*        THE FOLLOWING DEFS ARE FOR DEBUGGING AND CAN BE REMOVED IF
*        DESIRED.
         SPACE     2
         DEF ORG3,CCP7.MDP,BB8,AGEN,GRPS,VAL,TALL,EQU,SSU15
         DEF SDIRS,SORG,SEXT,SSECT,ORG,CCP1,REF,SORG3,SORG3.1
         DEF REPTM2,BFCX,XRGETI9,SETPRO
         SPACE     2
         IFF       C.MPX1X,SKIP                                 *JCB*
         M.VRSION  ONLY ON MPX3X
SKIP     ANOP                                                   *JCB*
         SPACE 2
         LIST      NOMAC,NODATA,NONG
         IFT       UNIXF,SKIP                                   *JCB*
         EXT       _c.srt                                       *JCB*
         DEF       _main                                        *JCB*
         EXT       _read                                        *JCB*
         EXT       _read1ln                                     *JCB*
         EXT       _readraw                                     *JCB*
         EXT       _writraw                                     *JCB*
         EXT       _write                                       *JCB*
         EXT       _open                                        *JCB*
         EXT       _seek                                        *JCB*
         EXT       _fcbadr                                      *JCB*
         EXT       _close                                       *JCB*
         EXT       _creat                                       *JCB*
         EXT       _unlink                                      *JCB*
         EXT       _malloc                                      *JCB*
         EXT       _free                                        *JCB*
         EXT       _brk                                         *JCB*
         EXT       _exit                                        *JCB*
         EXT       _eas            CONTAINS END OF ADDR SPACE   *JCB*
         SPACE     5                                            *JCB*
CCALL    DEFM      ENTRY,ARG0,ARG1,ARG2,ARG3,ARG4               *JCB*
         LW        .SP,STACKPTR                                 *JCB*
         PUSH      %ARG0,0                                      *JCB*
         PUSH      %ARG1,1                                      *JCB*
         PUSH      %ARG2,2                                      *JCB*
         PUSH      %ARG3,3                                      *JCB*
         PUSH      %ARG4,4                                      *JCB*
         BL        %ENTRY                                       *JCB*
         ENDM                                                   *JCB*
         SPACE     5                                            *JCB*
PUSH     DEFM      ARG,N                                        *JCB*
         IFP       %ARG,%EITHER                                 *JCB*
         IFT       G'%ARG' .LT. G'R0.',%LW                      *JCB*
         LW        R1.,%ARG                                     *JCB*
         STW       R1.,CALL.+%N:W,.SP                           *JCB*
%LW      ANOP                                                   *JCB*
         IFT       G'%ARG' .GT. G'R7.',%LW1                     *JCB*
         LW        R1.,%ARG                                     *JCB*
         STW       R1.,CALL.+%N:W,.SP                           *JCB*
%LW1     ANOP                                                   *JCB*
         IFT       G'%ARG' .GE. G'R0.',%STW                     *JCB*
         IFT       G'%ARG' .LE. G'R7.',%STW                     *JCB*
         STW       %ARG,CALL.+%N:W,.SP                          *JCB*
%STW     ANOP                                                   *JCB*
*         IFF       G'%ARG' .LT. G'R0.',%LW                      *JCB*
*         IFF       G'%ARG' .LE. G'R7.',%STW                     *JCB*
*%LW      ANOP                                                   *JCB*
*         LW        R1.,%ARG                                     *JCB*
*         STW       R1.,CALL.+%N:W,.SP                           *JCB*
*         GOTO      %EITHER                                      *JCB*
*%STW     ANOP                                                   *JCB*
*         STW       %ARG,CALL.+%N:W,.SP                          *JCB*
%EITHER  ANOP                                                   *JCB*
         ENDM                                                   *JCB*
         LIST      MAC,NONG                                     *JCB*
         PAGE                                                   *JCB*
SKIP     ANOP                                                   *JCB*
         TITLE     STORAGE FOR ASSEMBLER
HWLSTR   RES       4W              THE ABSOLUTE, DATA SECTION,
*                                  COMMON, AND CONTROL SECTION
*                                  PROGRAM COUNTERS IN THAT
*                                  ORDER. THE FORMAT IS
*                                  THE STANDARD SYMBOL
*                                  DEFINITION ONE.
HWCMSIZE RES     256W              SAVE AREA FOR COMMON PC'S
MAX      REZ       1W              MAXIMUM PROGRAM SIZE         S8700512
BLKNUM   REZ       1W              COMMON AREA BLOCK NUMBER     S8700508
SIZE     REZ       1W              SIZE OF COMMON AREA ORG.     S8700508
ACCUM    REZ       1W              2ND EXPRESSION ACCUMULATOR   S900542
HWLSTS   RES       1W              THE DEFINED ADDRESS OF THE LEFT MOST
*        BYTE BEING GENERATED FOR THIS LINE OF CODING
*        IT IS SET AFTER AN NECESSARY BOUNDING, AND IS USED TO ALLOCATE
*        ANY LABEL THAT MAY HAVE APPEARED ON THE INPUT LINE
*        IT IS TAKEN FROM THE PROPER PROGRAM COUNTER IN REGION LSTR
HWBYTE   RES       1W              THIS WORD CONTAINS THE GENERATED CODE
*        FOR THE CURRENT LINE OF ASSEMBLY BROKEN DOWN INTO UP TO 4 BYTES
*        THIS WORD IS SET UP AS IF IT WOULD MAP INTO THE H MEMORY, I.E.
*        THE LEFT MOST BYTE IS FOR BYTE 0, THE RIGHTMOST BYTES IS FOR BY
*        TE 3 OF THE WORD ADDRESS CONTAINED IN LSTS
HWBYTF   RES       1W              EACH BYTE IN THIS WORD CONTAINS A FLA
*        G TELLING WHETHER THE CORRESPONDING BYTE OF HWBYTE CONTAINS A
*        VALID BYTE FOR OUTPUT
HWERRF   RES       1W              THIS WORD CONTAINS 32 BIT FLAGS INDIC
*        ATING THE TYPE OF ERRORS FOUND SINCE THE LAST ERROR FLAGS WERE
*        PRINTED.  EACH BIT POSITION WILL CAUSE A SPECIFIC CHARACTER TO
*        BE PRINTED.     BIT 0 THE CODE FOR ASCII   X'40' , BIT 1 FOR
*        X'41', BIT 31 FOR ASCII X'5F' AND SO FORTH
HWERRFA  RES       1W              HOLDS HWERRF CONTENTS DURING LITERALS
HWERCT   RES       1W              KEEP COUNT OF THE CUMULATIVE ERRORS
*        DURING THIS PASS
UNSTNP   RES       1W              STORE POINTER FOR UNST
HWLICT   RES       1W              4 CHARACTERS OF THE CURRENT LINE NUMB
LICE     RES       1W              HOLDS BINARY LINE COUNT
HBSTAC   RES       1W              THIS A A LEFT TO RIGHT PICTURE OF
*        THE LATEST TERMINATORS DETECTED BY THE UNSTRING ROUTINE
         BOUND     1D
HWLABL   RES       2W              THE LEFTMOST 8 ASCII CHARACTERS OF TH
*        LABEL THAT WAS ASSIGNED TO THIS LINE OF CODE, IF ANY
HWNAME   RES       6W              CONTAINS 24 CHARACTERS OF ASCII NAME
*        THAT WAS LAST UNSTRUNG BY BY THE MAIN INPUT UNSTRINGER ROUTINE
MAXCHARSINHWNAME   DEQU     $-HWNAME   CHARS IN ABOVE           EASC-32
HWEVAL   RES       1W              THE MODE EVALUATION OF THE WORD IN HW
*        BYTE. THIS WORD IS IN THE SYMBOL DESCRIPTION FORMAT
HWINAG   RES       1W              AUGEND TYPE AND VALUE
HWINAC   RES       1W              ACCUMULAND TYPE AND VALUE
HWINAGV  RES       1W              AUGEND VALUE
HWINACV  RES       1W              ACCUMULAND VALUE
HWINAGT  RES       1W              AUGEND TYPE
HWINACT  RES       1W              ACCUMULAND TYPE
HWINAGBN EQU       HWINAGT+1B      BLOCK NUMBER FOR COMMON
HWINACBN EQU       HWINACT+1B      BLOCK NUMBER FOR COMMON
HWDP     DATAW     0               DATAPOOL NUMBER
HWDPNUM  EQU       HWDP+1B
HWINDR   RES       1W              CONTAINS THE INDIRECT FLAG, IF ANY
*        TO BE MERGED INTO THE CURRENT INSTRUCTION FORMAT
HWNL1    RES       1W              FIRST TYPE AND VALUE FROM EXPRESSIONS
HWNL2    RES       1W               2ND  TYPE AND VALUE FROM EXPRESSIONS
HWNL3    RES       1W               3RD  TYPE AND VALUE FROM EXPRESSIONS
HWNL4    RES       1W               4TH  TYPE AND VALUE FROM EXPRESSIONS
HWNL5    RES       1W               5TH  TYPE AND VALUE FROM EXPRESSIONS
HWNM1    RES       1W              1ST NON-NUMERIC TERMIANTION DESCRIPTI
HWNM2    RES       1W              2ND NON-NUMERIC TERMIANTION DESCRIPTI
HWNM3    RES       1W              3RD NON-NUMERIC TERMIANTION DESCRIPTI
HWNM4    RES       1W              4TH NON-NUMERIC TERMIANTION DESCRIPTI
HWNM5    RES       1W              5TH NON-NUMERIC TERMIANTION DESCRIPTI
HWCMPB   RES       2W              HOLDS BOUNDING REQ. FOR DSECT AND
*                                  CSECT IN WORDS 0 AND 1 RESPECTIVELY
HWUSED   RES       1W              NUMBER OF SYMBOL TBL ITEMS USED
HWBBLS   RES       1W              CONTAINS THE PROGRAM COUNTER FOR THE
*        BINARY OUTPUT PACKGE, FORMAT IS THAT OF MAIN PROGRAM COUNTERS
HWLTBS   RES       1W              BASE ADDRESS OF THE LITERAL POOL,
*        FORMAT IS THAT OF THE PROGRAM COUNTERS
HWLTCT   RES       1W              NUMBER OF ITEMS THAT HAVE BEEN PLACED
*        INTO THE LITERAL POOL
HWLTPE   RES       1W              HOLDS ENDING ADDRESS OF THE LITERAL P
*        OOL SO THAT WE MAY TELL THE LOADER ABOUT ANY RES'S AT THE END O
*        F A PROGRAM  AND SO KEEP THE LOADER FROM OVERLAYING  THEM.
HWACT    RES       1W              HOLDS THE CONETNTS OF ELEMENTS 2-7 OF
*        THE CURRENT MNEMONIC CODE /OP CODE DESCRIPTOR
HWENDL   RES       1W              T. S. FOR END PROCESSOR
HHVFX    RES       1H              THIS IS A RIGHT TO LEFT PUSHING BIT S
*        TACK FOR VFD/GEN DATA
HHVFO    RES       1H              THE NUMBER OF BITS IN THE BIT STACK
*        THAT HAVE NOT BEEN RELEASED
HHVFS    RES       1H              NUMBER OF BITS DESIRED IN THE CURRENT
*        ELEMENT OF THE GEN STATEMENT
HHVFF    RES       1H              NUMBER OF BITS OF DATA SENT TO THE
*        VFD/GEN PACKING ROUTINE
HHVFGB   RES       1H              NUMBER OF BITS OF DATA ACCEPTED BY TH
*        E VFD/GEN PACKER FOR OUTPUT TO THE STACK
HHBITS   RES       1H              THIS ITEM CONTAINS MANY BITS THAT ARE
*        USED FOR CONTROL OF THE PRINTOUT AND PROCESSING OF LINE INFO
LPOOL31  EQU       0               1 INDICATES 31 LPOOL DIRECTIVES
*                                  HAVE BEEN PROCESSED.
         IFT       CAID,SKIP                                    *CAID*
SUDO     EQU       1               1 MEANS PROCESSING STAB ENTRY*CAID*
*                                  EXPAND UNIX TABS MOD 4       *CAID*
SKIP     ANOP                                                   *CAID*
ESCAPE2  EQU       2               CHARACTER COMING THROUGH IS PROTECTED
BNDWS3   EQU       3
BNDWS4   EQU       4               EXPAND MODE BITS STORE
*                  SAVE BIT 5 FOR MACRO ASSEMBLER
TGSIGN   EQU       6               SIGN BIT FOR IMPLICIT DATA TYPES
TFSIGN   EQU       7               0=+, 1=- FOR DECIMAL CONSTANT
PROGF    EQU       8               1 MEANS PROGRAM HAS BEEN ENTERED
XPONENT  EQU       9               1 MEANS USER ENTERED AN EXPON 83-308
NGPRINT  EQU       10              0 MEANS PRINT SUPPRESSED CODE GENRTN
         IFT       CAID,SKIP                                    *CAID*
INSTAB   EQU       11              1 MEANS PROCESSING STAB ENTRY*CAID*
*                                  SO IGNORE ; AND " CHARS      *CAID*
SKIP     ANOP                                                   *CAID*
APON     EQU       12              0 MEANS ALLOW LIST, NON-ZERO MEANS NO
APEX     EQU       13              0 MEANS ALLOW LISTING OF EXTENSION
*        IMAGES (I.E. EXTRA WORDS FROM DATA STATEMENTS), ELSE DONT
CVFL     EQU       14              0 MEANS PROG COUNTER NOT TO BE PRINTE
*                                  1 MEANS PROG COUNTER TO BE PRINTED
IMIN     EQU       15              0 IF THE BUFFER IMAGE HAS ALREADY
*        BEEN PRINTED, NON-ZERO IF IT HAS NOT BEEN PRINTED YET
HHODP    RES       1H              MASTER VARIABLE FOR OUTPUT INFO
HHODPA   RES       1H              ALTERNATE FOR HHODP
TOT      EQU       HHODP           LENGTH CONSTANT FOR TDAT
*                                  TOT=1,2,4,OR 8 DEPENDING ON DATA BND
HBTTTF   EQU       HHODP+1B        VALUE IS A POINTER  FOR DATA BEING
*        GENERATED BY THE TRANSLATORS, 0 MEANS FOR DATA, 1 FOR GEN, 2
*        FOR LITERALS, 3 FOR VALUE EXPRESSION
HHTDB    RES       1H              B+-N DATA ENTERED IN CONSTANT
HHTDE    RES       1H              E+-N DATA ENTERED IN CONSTANT
HHTDBN   RES       1H              HOLDS DESIRED B SCALING CONSTANT
HBPASS   RES       1B              ZERO MEANS PASS 2, ELSE PASS 1
PAS2     EQU       HBPASS          ZERO MEANS PASS 2,1 MEANS PASS 1
HBLABS   RES       1B              0W - PROG IN ABS MODE
*                                  1W - PROG IN DSECT MODE
*                                  2W - PROG IN COMMON MODE
*                                  3W - PROG IN CSECT MODE
HBIBYI   RES       1B              THE CHARACTER NUMBER OF THE INPUT SCA
*        NNER ROUTINE. RANGES FROM 0-71 LEGALLY
HBIBYIT  RES       1B              TEMP HOLDS HBIBYI DURING TMD ROUTINE
HBIBYIS  RES       1B              TEMP HOLDS HBIBYI DURING SORG ROUTINE
HBAVAR   RES       1B              HOLDS ADDRESSING VARIANT TO BE USED
*        TO MAKE THE ADDRESS FILED OF THE CURRENT WORD, IT IS USED AS
*        INPUT ARGUMENT FOR ROUTINES AGEQ, ETC
HBBBFB   RES       1B              0 MEANS NO DATA BYTES HAVE GONE OUT
*        WHILE NON-ZERO MEANS THAT SOME HAVE GONE ALREADY
         BOUND     1W
         IFT       CAID,SKIP                                    *CAID*
HBBS     RES       120B            BINARY OUTPUT STRING STACK   *CAID*
SKIP     ANOP                                                   *CAID*
         IFF       CAID,SKIP                                    *CAID*
HBBS     RES       80B             BINARY OUTPUT STRING STACK   ETCM-32
SKIP     ANOP                                                   *CAID*
HBBBCT   RES       1B              NUMBER OF BYTES GENERATED FOR THIS LI
*        NE OF SOURCE OR OBJECT
ENDFLAG  RES       1B              END CARD FOUND LAST FLAG
HBCCCT   RES       1B              NUMBER FOR NEXT COMMON BLOCK
HBBN     RES       1B              COMMON BLOCK/SECTION NUMBER
HBNPLC   RES       1B              NUMBER OF LINES ALREADY ON PAGE
OPTION   RES       1W              OPTION WORD.
OPTION2  RES       1W              2ND OPTION WORD SAVE AREA    EIEE-33
OPTSAV   RES       1W              OPTION WORD SAVE AREA        EBRM-33
DBG      EQU       13              ! OPTION 19 DEBUGGER SYMBOLS (1=YES)
ASCT.OPT EQU       14              OPTION 18 FOR AUTO-SECTION   EASC-32
DT.OPT   EQU       17              OPTION 15 FOR DATE/TIME IN OBJ  11005
ID.OPT   EQU       18              OPTION 14 FOR ID INFO FROM PROG 11007
BM.OPT   EQU       16              OPTION 16 FOR BASE MODE FMT  EBRM-33
*                                    DIRECTIVE IN OBJ              11007
OPT11    EQU       21     OPTION 11 STRINGBACK CONTROL          ENSB-33
NOMAC    EQU       22              MACRO STORAGE INDICATOR(1=NO,0=YES)
CMDK     EQU       25              (1=CMDK,0=NOCMDK)
GO       EQU       27              (1=GO,0=NOGO)
XREF     EQU       28              (0=YES,1=NO)
XREFINT  EQU       29              XREF INT SYM WITH XREF(1=YES,0=NO)
BO       EQU       30              BINARY OUTPUT  (0=BO,1=NOBO)
LO       EQU       31              LIST OPTION BIT(1=NOLO,0=LO)
NPLC     EQU       HBNPLC
HWBAHDR  RES       1W              BASE ADDRESS OF HEADER INFO
BARA     RES       1W              BASE ADR OF USER'S AREA AND QTY
READSIP  RES       1W
READPIP  RES       1W
READSKP  RES       1W
PREFLG   RES       1W              PRE FILE FLAGS
DCMPRS3  RES       1W
EORA     RES       1W
CMPRFR   RES       1W              LOCATION AND LGTH OF SOURCE BUFFER
CMPRTO   RES       1W              LOCATION AND LGTH OF DESTINATION BUF
* 0-11 EQ LGTH, 12-31 = ADR. SET BY CALLING ROUTINE
CMPRLOB  RES       1B              LENGHT OF OUTPUT BUF IN BYTES
IMIP     RES       1B              IMAGE IN PROCESS IND
CMPRLIB  RES       1B              LENGHT OF INPUT BUF IN BYTES
CMPRQTYR RES       1B              QTY READ
CMPRSTC  RES       1B              STRING COUNT
CMPRSPC  RES       1B              SPCAE COUNT
CMPRTSPC EQU       CMPRSPC         TRAILING SPACE COUNT
READCKSM RES       1H              CHECK SUM FOR COSY RECORD
         RES       8W              FIRST SAFETY FILE
RELEASF  RES       8W              FILE STORAGE BLOCK FOR RELEAS
         RES       8W              LAST SAFETY FILE
GBYC     RES       1W              GBYT TERMINATOR LIST
UNSTC    RES       1W              THE TERMINATROS FOR THIS UNSTRING
HHHHS1   RES       1W              BYTE DISPLACEMENT OF HIT IN KINT
HDUN00   RES       2D
HDUNJF   RES       1D              HOLDS UNDEFS FOR LISTING
HDERCT   RES       4D
CNUB     RES       1D              DOUBLEWORD AUGEND IN CNUM
CNUA     RES       1D              DOUBLEWORD CONVERTAND IN CNUM
SSUFB    RES       1D              DOUBLEWORD SCRATCH FOR ROUTINE SS
GRPV     RES       1D              ADR OF HWNL1 IN 1ST WORD,HWNM1 IN 2ND
HDTDS    RES       1D              INTEGER  PART OF CONSTANT
HDTDF    RES       1D              FRACTION PART OF CONSTANT
INPTS0   RES       1W              RETURN ADDRESS
BTXA     RES       1W              T.S. FOR BTX
BTXB     RES       1W              T.S. FOR BTX
HBTDFN   RES       1B
HBCNUL   RES       1B              BIT 7 HOLDS POS/NEG INTEGER FLAG
HBTFN1   RES       1B              PREVIOUS TERMINATOR POINTER
HBTFN2   RES       1B              LATEST   TERMINATOR POINTER
HBTFN3   RES       1B              CHARACTER STORE POINTER
HBTITM   RES       1B              CHAR COUNT FOR TITLE
GRPSS1   RES       1B              T.S. FOR ADDRESSING TYPE
VALS1    RES       1B              TS FOR VAL
VDAP     RES       1B              POINTER TO OPERATION TO BE DONE
VALT     RES       1B              NUMERIC EQU OF NON-NUMERIC TERMINATOR
PPT      RES       1B              BINARY RECORD LENGTH, 0=UNUSABLE DEV
PBNB     RES       1B              NUMBER OF BYTES
PBNC     RES       1B              LOADER FUNC CODE
PBSQ     RES       1H              BINARY REC SEQ NO.
GRPW     RES       1W              EXPRESSION COUNTER
LOCHS1   RES       1W
TDGS6    RES       1W              HOLDS BYTE FOR OUTPUT DURING TDG MESS
TDGS1    RES       1W
VFDOS1   RES       1W
CCTU     RES       1W              HOLD QUERY FLAG
CCTW     RES       1W              RUNNING PROG CT DURING BLOCK MAKE-UP
SECTLGF  EQU       64W             SIZE OF BI/SI/BO/UT BUFFERS
         BOUND     1W
PBL      RES       SECTLGF         BO INTERMEDIATE BUFFER
PBLF     EQU       PBL+0B          LOC OF BIN. OUTPUT FUNC CODE
PBLB     EQU       PBL+1B          LOC FOR BYTE CT IN BUFFER
PBLC     EQU       PBL+2B          LOC FOR HALFWORD CHECKSUM
PBLS     EQU       PBL+4B          LOC FOR HALFWORD SEQ NUMBER
PBLP     EQU       PBL+6B          LOC FOR DATA
PRNT     RES       30W             SPACE FOR 120 CHARACTER OUTPUT  LINE
         IFT       UNIXF,SKIP                                   *JCB*
EOL.J    DATAW     X'0A000000'     LINEFEED TERMINATOR          *JCB*
SKIP     ANOP                                                   *JCB*
IN       EQU       PRNT+10W        LOCATION OF INPUT IMAGE AREA
*
BLKBUFSS EQU       20              BLOCKING BUFF. SIZE (SECTORS)S880752
BLKBUFSB EQU       BLKBUFSS*768    BLOCKING BUFF. SIZE (BYTES)  S880752
BLKBUFVR GEN       8/BLKBUFSS,24/0 BLOCKING BUFFER VECTOR       S880752
*
         BOUND     1D              DOUBLE WORD ALIGNMENT
         RES       1W
TCWD     DATAW     C'-   '         NEW PAGE CHARACTER
TCWPROG  DATAW     C'            ' PROGRAM NAME PLUS 4 BLANKS
*
*                                MODIFY THE TITLE LINE STRUCTURE 83-451
*
TCWDATE  RES       5W              ASSEMBLY DATE AND TIME (20 BYTES)
TCWTITL  RES       16W             TITLE AREA (64 BYTES)
TCWTTLE  DATAW     C'    '         LAST BYTE OF TITLE (AND EXTRA)  11010
TCWSIZE  DEQU      $-TCWD          SIZE OF TITLE BUFFER         ESCT-32
*
* THE PRODUCT, REV, AND COPYRIGHT INFO IS ORDER DEPENDENT.         11010
* DO NOT MOVE WITHOUT THOROUGH INVESTIGATION.                      11010
*
         BOUND     1W
PRODRTCW GEN       12/A(CPYR.MSG-PRODREV),20/B(PRODREV)            11010
HDRL1TCW GEN       12/A(CPYR.END-PRODREV),20/B(PRODREV)            11010
PRODREV  DATAB     C' MPX-32 UTILITIES RELEASE 3.4.0 '
*         DATAB     C'(ASSEMBLE R3.4.0.05) '
*         DATAB     C'(NBCAS R3.4.0.06) '
*        DATAB     C'(NBCAS R3.4.0.07) '
*        DATAB     C'(NBCAS R3.4.0.08) '
         DATAB     C'(NBCAS R3.4.0.09) '
*
*        DATA FOR COPYRIGHT MESSAGE AND TCW
*
*        ALSO SERVES FOR MESSAGE IN OBJECT
*
CPYR.MSG DATAB C' (C) COPYRIGHT 1983 ENCORE COMPUTER CORPORATION '
         DATAB C', ALL RIGHTS RESERVED'
CPYR.END DEQU      $                                            ESCT-32
         BOUND     1W
CPYR.TCW GEN       12/A(CPYR.END-CPYR.MSG),20/B(CPYR.MSG)
*
CARR.C1  DATAB     C'-'            CARRIAGE CONTROL FOR HDR LINE 1 11010
CARR.C2  DATAB     C'-'            CARRIAGE CONTROL FOR HDR LINE 2 11010
*
LO.TSMD  DATAB     0               0 IF LO NOT A TSM ASSOC FAT     11011
*
DATETIME RES       4W              BUFFER FOR SYSTEM DATE AND TIME
         SPACE     2
PROD.IDL DATAB     0               LENGTH OF PRODUCT ID INPUT      11005
PROD.ID  RES       6W              PRODUCT ID (0 TO 20 BYTES)      11005
*
* THIS FIELD IS PULLED FROM THE PROGRAM DIRECTIVE AFTER THE PROG   11005
* NAME. IF NOT SPECIFIED, LENGTH IS ZERO AND NO PROCESSING OCCURS. 11005
* THE SIZE IS LIMITED TO 20 BYTES BECAUSE OF THE 26 BYTE OUTPUT    11006
* BUFFER THAT THE ASSEMBLER USES FOR 'PUBLISHING' BINARY.          11006
*
FMTD.DT  RES       2D              FORMATTED DATE AND TIME         11005
*
* THIS FIELD IS ALREADY FORMATTED AND READY FOR INCLUSION IN OBJ   11005
*
         SPACE     1
T.CREF   DATAW     C'CROSS REFERENCE'
T.CREF.E DEQU      $                                            ESCT-32
SBUF     RES       SECTLGF         SCRATCH BUFFER FOR UT1
IBUF     RES       SECTLGF         SI INPUT BUFFER
IBUF2    RES       SECTLGF         PRE INPUT BUFFER
REFS1    RES       1W              T.S.
BFCS2    RES       1W              T.S.
PBBA     RES       1W              BASE ADR OF DATA TO OUTPUT
UOUTS2   RES       1W              T.S.
REFS2    RES       1W
READS0   RES       1W              RETURN ADDRESS FROM READ
HHHHS0   RES       1W              RETURN ADDRESS FROM HHHH
BNDWS0   RES       1W              STORAGE FOR RETURN ADDRESS FROM BNDW
IGENS0   RES       1W              RETURN ADDRESS FROM IGEN
RSETS0   RES       1W              RETURN ADDRESS FROM RSET
BOUCS0   RES       1W              RETURN ADDRESS FROM BOUC
POUTS0   RES       1W              RETURN ADDRESS FROM POUT
PPPS0    RES       1W              RETURN ADR FROM PPP
CPASS0   RES       1W              RETURN ADR FROM CPAS
TALLS0   RES       1W              RETURN ADR FROM TALL
LOCHS0   RES       1W              RETURN PSWR FOR LOCH
PTH1R    RES       1W              PSWR T.S. FOR PTH1
GRPSS0   RES       1W              RETURN ADDRESS
VALS0    RES       1W              RETURN ADDRESS FROM VAL
UNSTS0   RES       1W
TDATS0   RES       1W              T.S. FOR TDAT RETURN ADR
TDGS0    RES       1W
TCYS0    RES       1W
TMDS0    RES       1W              RETURN ADR
TFNS0    RES       1W              RETURN ADDRESS FOR TFN
VFDOS0   RES       1W
GBYX     RES       1W              RETURN FOR GBYT
PBS0     RES       1W              RETURN ADDRESS
LITORGS  RES       32W
PRLITT0  RES       1W
HHBITS2  RES       1W              HOLDS SEVERAL FLAGS AFFECTING ASSEM.
ADDRERR  EQU       0               1 INDICATES A REFERENCE IS BEING
*                                  MADE TO AN ILLEGAL BOUNDARY FOR THE
*                                  CURRENT INSTRUCTION.
ALVAL    EQU       1               1 INDICATES TO VAL THAT THE CURRENT
*                                  OPERAND HAS ALREADY BEEN EVALUATED.
MACPRINT EQU       2               1=DON'T LIST MACRO EXPANSIONS
REPPRINT EQU       3               1=DON'T LIST REPT EXPANSIONS
NONGITEM EQU       4               1=CURR. OPER. IS LIST NONG
*                                    SUPPRESSABLE
HHBITS3  RES       1B              VARIOUS FLAGS INITIALIZED ONLY
*                                    BEFORE PASS 1
EXPLFC   EQU       0               1 = USE EXPANDED LOADER FUNC CODES
SECNUMAG RES       2W              SECT NUM OF AUGEND
SECNUMAC EQU       SECNUMAG+1W     SECT NUM OF ACCUMULAND
DSIZE    RES       1W              DSECT SIZE FOR SECTION DEFINITION
CSIZE    RES       1W              CSECT SIZE FOR SECTION DEFINITION
HHBITS4  RES       1B              UNINITIALIZED FLAGS
MA2PRES  EQU       0               1=MA2 FILE HAS BEEN ASSIGNED
MA2SRCH  EQU       1               0-SEARCH MAC FILE , 1-SEARCH MA2 FILE
LABLSCAN RES       1D              HOLDS THE LABEL THAT WE WILL RESUME
*        ASSEMBLY AT
MGBD     RES       4D
MUNSTA   RES       2D              HOLDS NAME FOR SUBSTITUTION
         BOUND     8W
REGSAV   RES       8W              HOLDS REGS WHILE SS PROCESSES AN
*                                  INTERNALLY GENERATED SYMBOL
HWSCNHP  RES       1D              HOLDS PROSPECTIVE NAME FOR COND,GOTO
STCKCHK1 RES       1W              HOLDS REG 1 DURING STACKCHK ROUTINE
INSIG    EQU       5               1 MEAN THE NEXT SPACE IS INSIGNIGANT
MACPRO   EQU       0               PROTO PTR ENTRY CODE.
MACBAS   EQU       1               BASE PTR ENTRY CODE.
MACARG   EQU       2               ARG PTR ENTRY CODE.
MACIUP   EQU       3               INT SYM UNASSEM PASSED ENTRY CODE.
MACIU    EQU       4               INT SYM UNASSEM ENTRY CODE.
MACIA    EQU       5               INT SYM ASSEM ENTRY CODE.
MACIAP   EQU       6               INT SYM ASSEM PASSED ENTRY CODE.
HWMSP    RES       1W              DEFINTIION HOLD AREA
HWMRQ    RES       1W              MACRO REQUEST CHECK
SETPROV  RES       1W              HOLDS VALUE OF THE SET
HWMSB    RES       1W              HOLDS BASE OF THE MACRO INFO
HWCMAC   RES       1W              HOLDS POINTER TO BODY OF LATEST MACRO
HWCMACP  RES       1W              HOLDS A CHAINING POINTER TO FORM LIST
PBYTS1   RES       1W              HOLDS R1 FOR PBYT
MUNSTAP  RES       1W
HWREPSP  RES       1W         TEMP BASE ADDRESS OF THE REPEATED CODE STO
HWREPSS  RES       1W         PERM BASE ADDRESS OF THE REPEATED CODE STO
GOTOC    RES       1W              HOLDS COUNT DURING GOTO LIST SCAN
EPHEMS1  RES       1W
PREVRELO RES       1W              HOLDS PREVIOUS IF RELATION OPERAOTR
IFET     RES       1W              HOLDS TEMP TRUE/FALSE
INTTAG   RES       1W              INTERNALLY GENERATED TAG COUNTER
MUNSTS6  RES       1W              HOLDS POINTER TO EXPND AREA
HWMSPBUF RES       1W              HOLDS POINTER TO MACRO PRINT STORAGE
MPBUF    RES       80              HOLDS EXPANDED MACRO BYTES
MACSTATE RES       1H              ONE BYTE CONTAINS MANY FLAGS CONCERNI
*        THE MACRO PROCESSOR STATUS.  THE BITS ARE DETAILED BELOW.
MACREP   EQU       0               1 INDICATES A REPT WITHIN A MACRO EXP
FORMGET  EQU       1               1 MEANS GENERATING A FORM CALL
CALLUS   EQU       2               SET WHILE A CALL IS IN PROCESS
EXPAND   EQU       3               IF ON MEANS THAT A MACRO IS EXPANDING
UNSTFLAG EQU       4      IF ON MEANS UNST HAS A DUMMY ARGUMETT
REUNSTF  EQU       5               ON MEANS PART-WAY THRU A MACRO STRING
DEFMBODY EQU       6               THIS BIT IF ON MEANS THE MACRO PRO-
*        CESSOR IS WORKING ON THE BODY OF A MACRO PROTOTYPE
CONDSCAN EQU       8               IF ON THIS MEANS THE THE ASSEMBLER
*        IS SCANNING FOR THE LABEL SPECIFIED BY AN IFT,IFF, OR GOTO
INTGEN   EQU    9   1 MEANS AN INTERNAL LABEL HAS BEEN ENCOUNTERED
RSCAN    EQU       10              IF ON MEANS INITIAL SCAN OF REPT AREA
RPTGEN   EQU       11              IF ON MEANS GENERATING CODE FROM REPT
FORMSCAN EQU       12              BIT ON MEANS SCANNING A FORM
INTGEN2  EQU       13              PREVIOUS STATE OF INTGEN
COMMENT  EQU       14              0= * IN COL 1, 1=ELSE
FALSE    EQU       15              ALWAYS A 0 (I.E. FALSE)
INPTSTAT RES       1H              HOLDS COPY OF MACSTATE FOR INPT
HHRCOUNT RES       1H              NUMBER OF TIMES TO REPEAT
HHRDCOLC RES       1H              NUMBER OF TIMES WE HAVE REPEATED SO F
GOTOCB   RES       1B              FLAG FOR GOTO LIST FIND/NO FIND
MGBS7    RES       1B              HOLDS THE TERMINATING CHARACTER
SPMAC    RES       1B              HOLDS FLAGS FOR SPECIAL CONDITIONS
*                                  IN MACRO PROCESSING.  THE BITS
*                                  ARE DETAILED BELOW.
DUMMY    EQU       0               1 INDICATES UNSTRUNG NAME IS
*                                  A DUMMY ARGUMENT.
LPOOLM   EQU       1               1 INDICATES AN LPOOL DIRECTIVE IS
*                                  BEING PROCESSED IN A MACRO EXPANSION.
NOPGEN   EQU       2               1 INDICATES A NOP IS BEING
*                                  GENERATED TO GET TO THE CORRECT
*                                  BOUNDARY.
INTSS    EQU       3               1 INDICATES SS IS PROCESSING AN
*                                  INTERNALLY GENERATED SYMBOL.
UNS      EQU       4               INDICATES TO ROUTINE GBYT THAT IT
*                                  WAS CALLED BY UNST.
INTGEN3  EQU       5               INDICATES TO GBYT & UNST THAT AN
*                                  INTERNAL SYMBOL HAS BEEN UNSTRUNG.
MBUFSW   EQU       6               1 INDICATES PRNT BUFS WERE SWITCHED.
DEFFRM2  EQU       7               SET WHILE PROCESSING A FORM DIR. OR
*                                  A MACRO PROTO IN PASS 2.
INSYMARG RES       1B              HOLD % NUMBER OF UNSTRUNG DUMMYS
*                                  DURING EXPANSION
VALUNDF  DATAB     0               BIT 0 SET INDICATES UNDEF IN VAL FOR
UNSTCK   DATAB     0               INVALID PARAMETER CHECK BIT      AS19
LEVEL    RES       1W              HOLDS NUMBER OF LEVELS BELOW REPT
****                                                                  **
         IFT       UNIXF,SKIP                                   *JCB*
*                                                               *JCB*
STACKPTR RES       1W              UNIX STACK POINTER           *JCB*
ARGC     RES       1W              NUMBER OF PASSED ARGUMENTS   *JCB*
ARGV     RES       1W              POINTER TO PASSED ARGUMENTS  *JCB*
FILEPTR  RES       1W              POINTER TO STANDARD INPUT    *JCB*
SKFILPTR DATAW     SK.PATH         POINTER TO UT1 PATHNAME      *JCB*
XRFILPTR DATAW     XR.PATH         POINTER TO UT2 PATHNAME      *JCB*
LOFILPTR DATAW     LO.PATH         POINTER TO LISTING PATHNAME  *JCB*
BOFILPTR DATAW     BO.PATH         POINTER TO BO PATHNAME       *JCB*
MCFILPTR DATAW     MC.PATH         POINTER TO MAC PATHNAME      *JCB*
SKCNT    DATAW     0               TRANSFER CNT FOR SK FILE     *JCB*
XR.FCBA  DATAW     0               ADDRESS OF UT2 FCB           *JCB*
*                                                               *JCB*
SK.PATH  DATAB     C'TEMP SIZE=800"@'                           *JCB*
XR.PATH  DATAB     C'TEMP SIZE=800 BLOC=N"@'                    *JCB*
LO.PATH  DATAB     C'SLO"@'                                     *JCB*
BO.PATH  DATAB     C'SBO"@'                                     *JCB*
MC.PATH  DATAB     C'@SYSTEM(SYSTEM)M.MPXMAC BLOC=N"@'          *JCB*
*                                                               *JCB*
SI.FD    DATAW     0               DESCR FOR SI (ASSUME STDIN)  *JCB*
SK.FD    DATAW     0               DESCRIPTOR FOR UT1 (SCRATCH) *JCB*
XR.FD    DATAW     0               DESCRIPTOR FOR UT2 (XREF)    *JCB*
LO.FD    DATAW     0               DESCRIPTOR FOR LISTING       *JCB*
BO.FD    DATAW     0               DESCRIPTOR FOR BINARY OUTPUT *JCB*
MC.FD    DATAW     0               DESCRIPTOR FOR MACRO LIBRARY *JCB*
HWPCMODE RES       1B              MODE OF PC WHEN SYMBOL WAS   *JCB*
*                                  EVALUATED BEFORE PASS 1      *JCB*
*                                                               *JCB*
         SPACE     3                                            *JCB*
CALL.    EQU       8W                                           *JCB*
.ARGS    EQU       8W                                           *JCB*
*                                                               *JCB*
R0.      EQU       0                                            *JCB*
R1.      EQU       1                                            *JCB*
R2.      EQU       2                                            *JCB*
R3.      EQU       3                                            *JCB*
R4.      EQU       4                                            *JCB*
R5.      EQU       5                                            *JCB*
R6.      EQU       6                                            *JCB*
R7.      EQU       7                                            *JCB*
*                                                               *JCB*
.SP      EQU       3                                            *JCB*
.AP      EQU       1                                            *JCB*
*                                                               *JCB*
OFF1.    EQU       -64                                          *JCB*
AUT1.    EQU       64                                           *JCB*
TMP1.    EQU       64                                           *JCB*
ARG1.    EQU       96                                           *JCB*
*                                                               *JCB*
NEWLINE  EQU       X'A'            NEW LINE CHARACTER (LINEFEED)*JCB*
TABCHAR  EQU       X'9'            ASCII TAB                    *JCB*
*                                                               *JCB*
SKIP     ANOP                                                   *JCB*
************************************************************************
         SPACE     1
         M.EQUS                                                83-725
         M.TBLS                                                  11003
*
*        MACROS FOR BUILDING LFC TABLE USED IN LFC SUBSTITUTION ELFC-31
*                                                               ELFC-31
*        UTL:LFC - BUILDS LFC SUBSECTIONS OF TABLE ENTRIES      ELFC-31
*                                                               ELFC-31
UTL:LFC  DEFM      1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16       ELFC-31
UTL:LCT  SET       0                                            ELFC-31
         IFP       %1,N2           DETERMINE NUMBER OF LFC'S    ELFC-31
UTL:LCT  SET       UTL:LCT+1                                    ELFC-31
N2       IFP       %2,N3                                        ELFC-31
UTL:LCT  SET       UTL:LCT+1                                    ELFC-31
N3       IFP       %3,N4                                        ELFC-31
UTL:LCT  SET       UTL:LCT+1                                    ELFC-31
N4       IFP       %4,N5                                        ELFC-31
UTL:LCT  SET       UTL:LCT+1                                    ELFC-31
N5       IFP       %5,N6                                        ELFC-31
UTL:LCT  SET       UTL:LCT+1                                    ELFC-31
N6       IFP       %6,N7                                        ELFC-31
UTL:LCT  SET       UTL:LCT+1                                    ELFC-31
N7       IFP       %7,N8                                        ELFC-31
UTL:LCT  SET       UTL:LCT+1                                    ELFC-31
N8       IFP       %8,N9                                        ELFC-31
UTL:LCT  SET       UTL:LCT+1                                    ELFC-31
N9       IFP       %9,N10                                       ELFC-31
UTL:LCT  SET       UTL:LCT+1                                    ELFC-31
N10      IFP       %10,N11                                      ELFC-31
UTL:LCT  SET       UTL:LCT+1                                    ELFC-31
N11      IFP       %11,N12                                      ELFC-31
UTL:LCT  SET       UTL:LCT+1                                    ELFC-31
N12      IFP       %12,N13                                      ELFC-31
UTL:LCT  SET       UTL:LCT+1                                    ELFC-31
N13      IFP       %13,N14                                      ELFC-31
UTL:LCT  SET       UTL:LCT+1                                    ELFC-31
N14      IFP       %14,N15                                      ELFC-31
UTL:LCT  SET       UTL:LCT+1                                    ELFC-31
N15      IFP       %15,N16                                      ELFC-31
UTL:LCT  SET       UTL:LCT+1                                    ELFC-31
N16      IFP       %16,N17                                      ELFC-31
UTL:LCT  SET       UTL:LCT+1                                    ELFC-31
N17      ANOP                                                   ELFC-31
*                                                               ELFC-31
*   GENERATE TABLE DATA - NUMBER OF LFC'S FOLLOWED BY THE LFC   ELFC-31
*   STRINGS.                                                    ELFC-31
*                                                               ELFC-31
         GEN       24/0,8/UTL:LCT*1W                            ELFC-31
         IFP       %1,G2                                        ELFC-31
         GEN       8/0,24/C'%1'                                 ELFC-31
G2       IFP       %2,G3                                        ELFC-31
         GEN       8/0,24/C'%2'                                 ELFC-31
G3       IFP       %3,G4                                        ELFC-31
         GEN       8/0,24/C'%3'                                 ELFC-31
G4       IFP       %4,G5                                        ELFC-31
         GEN       8/0,24/C'%4'                                 ELFC-31
G5       IFP       %5,G6                                        ELFC-31
         GEN       8/0,24/C'%5'                                 ELFC-31
G6       IFP       %6,G7                                        ELFC-31
         GEN       8/0,24/C'%6'                                 ELFC-31
G7       IFP       %7,G8                                        ELFC-31
         GEN       8/0,24/C'%7'                                 ELFC-31
G8       IFP       %8,G9                                        ELFC-31
         GEN       8/0,24/C'%8'                                 ELFC-31
G9       IFP       %9,G10                                       ELFC-31
         GEN       8/0,24/C'%9'                                 ELFC-31
G10      IFP       %10,G11                                      ELFC-31
         GEN       8/0,24/C'%10'                                ELFC-31
G11      IFP       %11,G12                                      ELFC-31
         GEN       8/0,24/C'%11'                                ELFC-31
G12      IFP       %12,G13                                      ELFC-31
         GEN       8/0,24/C'%12'                                ELFC-31
G13      IFP       %13,G14                                      ELFC-31
         GEN       8/0,24/C'%13'                                ELFC-31
G14      IFP       %14,G15                                      ELFC-31
         GEN       8/0,24/C'%14'                                ELFC-31
G15      IFP       %15,G16                                      ELFC-31
         GEN       8/0,24/C'%15'                                ELFC-31
G16      IFP       %16,G17                                      ELFC-31
         GEN       8/0,24/C'%16'                                ELFC-31
G17      ANOP                                                   ELFC-31
         ENDM                                                   ELFC-31
*                                                               ELFC-31
*        UTL:REF1 - BUILDS LFC REFERENCE SUBSECTION OF TABLE    ELFC-31
*                   ENTRIES.                                    ELFC-31
*                                                               ELFC-31
UTL:REF1 DEFM      1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16       ELFC-31
UTL:RCT1 SET       0                                            ELFC-31
         IFP       %1,N2           DETERMINE NUM. OF REFERENCES ELFC-31
UTL:RCT1 SET       UTL:RCT1+1                                   ELFC-31
N2       IFP       %2,N3                                        ELFC-31
UTL:RCT1 SET       UTL:RCT1+1                                   ELFC-31
N3       IFP       %3,N4                                        ELFC-31
UTL:RCT1 SET       UTL:RCT1+1                                   ELFC-31
N4       IFP       %4,N5                                        ELFC-31
UTL:RCT1 SET       UTL:RCT1+1                                   ELFC-31
N5       IFP       %5,N6                                        ELFC-31
UTL:RCT1 SET       UTL:RCT1+1                                   ELFC-31
N6       IFP       %6,N7                                        ELFC-31
UTL:RCT1 SET       UTL:RCT1+1                                   ELFC-31
N7       IFP       %7,N8                                        ELFC-31
UTL:RCT1 SET       UTL:RCT1+1                                   ELFC-31
N8       IFP       %8,N9                                        ELFC-31
UTL:RCT1 SET       UTL:RCT1+1                                   ELFC-31
N9       IFP       %9,N10                                       ELFC-31
UTL:RCT1 SET       UTL:RCT1+1                                   ELFC-31
N10      IFP       %10,N11                                      ELFC-31
UTL:RCT1 SET       UTL:RCT1+1                                   ELFC-31
N11      IFP       %11,N12                                      ELFC-31
UTL:RCT1 SET       UTL:RCT1+1                                   ELFC-31
N12      IFP       %12,N13                                      ELFC-31
UTL:RCT1 SET       UTL:RCT1+1                                   ELFC-31
N13      IFP       %13,N14                                      ELFC-31
UTL:RCT1 SET       UTL:RCT1+1                                   ELFC-31
N14      IFP       %14,N15                                      ELFC-31
UTL:RCT1 SET       UTL:RCT1+1                                   ELFC-31
N15      IFP       %15,N16                                      ELFC-31
UTL:RCT1 SET       UTL:RCT1+1                                   ELFC-31
N16      IFP       %16,N17                                      ELFC-31
UTL:RCT1 SET       UTL:RCT1+1                                   ELFC-31
N17      ANOP                                                   ELFC-31
*                                                               ELFC-31
*   GENERATE TABLE DATA - NUMBER OF REFERENCE ADDRESSES         ELFC-31
*   FOLLOWED BY REFERENCE ADDRESSES.                            ELFC-31
*                                                               ELFC-31
         GEN       24/0,8/UTL:RCT1*1W                           ELFC-31
         IFP       %1,G2                                        ELFC-31
         ACW       %1                                           ELFC-31
G2       IFP       %2,G3                                        ELFC-31
         ACW       %2                                           ELFC-31
G3       IFP       %3,G4                                        ELFC-31
         ACW       %3                                           ELFC-31
G4       IFP       %4,G5                                        ELFC-31
         ACW       %4                                           ELFC-31
G5       IFP       %5,G6                                        ELFC-31
         ACW       %5                                           ELFC-31
G6       IFP       %6,G7                                        ELFC-31
         ACW       %6                                           ELFC-31
G7       IFP       %7,G8                                        ELFC-31
         ACW       %7                                           ELFC-31
G8       IFP       %8,G9                                        ELFC-31
         ACW       %8                                           ELFC-31
G9       IFP       %9,G10                                       ELFC-31
         ACW       %9                                           ELFC-31
G10      IFP       %10,G11                                      ELFC-31
         ACW       %10                                          ELFC-31
G11      IFP       %11,G12                                      ELFC-31
         ACW       %11                                          ELFC-31
G12      IFP       %12,G13                                      ELFC-31
         ACW       %12                                          ELFC-31
G13      IFP       %13,G14                                      ELFC-31
         ACW       %13                                          ELFC-31
G14      IFP       %14,G15                                      ELFC-31
         ACW       %14                                          ELFC-31
G15      IFP       %15,G16                                      ELFC-31
         ACW       %15                                          ELFC-31
G16      IFP       %16,G17                                      ELFC-31
         ACW       %16                                          ELFC-31
G17      ANOP                                                   ELFC-31
         ENDM                                                   ELFC-31
*                                                               ELFC-31
*        UTL:REF2 - BUILDS LFC 'C' STRING REFERENCE SUBSECTION  ELFC-31
*                   OF LFC TABLE ENTRIES                        ELFC-31
*                                                               ELFC-31
UTL:REF2 DEFM      1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16       ELFC-31
UTL:RCT2 SET       0                                            ELFC-31
         IFP       %1,N2           DETERMINE NUM. OF REFERENCES ELFC-31
UTL:RCT2 SET       UTL:RCT2+1                                   ELFC-31
N2       IFP       %2,N3                                        ELFC-31
UTL:RCT2 SET       UTL:RCT2+1                                   ELFC-31
N3       IFP       %3,N4                                        ELFC-31
UTL:RCT2 SET       UTL:RCT2+1                                   ELFC-31
N4       IFP       %4,N5                                        ELFC-31
UTL:RCT2 SET       UTL:RCT2+1                                   ELFC-31
N5       IFP       %5,N6                                        ELFC-31
UTL:RCT2 SET       UTL:RCT2+1                                   ELFC-31
N6       IFP       %6,N7                                        ELFC-31
UTL:RCT2 SET       UTL:RCT2+1                                   ELFC-31
N7       IFP       %7,N8                                        ELFC-31
UTL:RCT2 SET       UTL:RCT2+1                                   ELFC-31
N8       IFP       %8,N9                                        ELFC-31
UTL:RCT2 SET       UTL:RCT2+1                                   ELFC-31
N9       IFP       %9,N10                                       ELFC-31
UTL:RCT2 SET       UTL:RCT2+1                                   ELFC-31
N10      IFP       %10,N11                                      ELFC-31
UTL:RCT2 SET       UTL:RCT2+1                                   ELFC-31
N11      IFP       %11,N12                                      ELFC-31
UTL:RCT2 SET       UTL:RCT2+1                                   ELFC-31
N12      IFP       %12,N13                                      ELFC-31
UTL:RCT2 SET       UTL:RCT2+1                                   ELFC-31
N13      IFP       %13,N14                                      ELFC-31
UTL:RCT2 SET       UTL:RCT2+1                                   ELFC-31
N14      IFP       %14,N15                                      ELFC-31
UTL:RCT2 SET       UTL:RCT2+1                                   ELFC-31
N15      IFP       %15,N16                                      ELFC-31
UTL:RCT2 SET       UTL:RCT2+1                                   ELFC-31
N16      IFP       %16,N17                                      ELFC-31
UTL:RCT2 SET       UTL:RCT2+1                                   ELFC-31
N17      ANOP                                                   ELFC-31
*                                                               ELFC-31
*   GENERATE TABLE DATA - NUMBER OF REFERENCE ADDRESSES         ELFC-31
*   FOLLOWED BY REFERENCE ADDRESSES.                            ELFC-31
*                                                               ELFC-31
         GEN       24/0,8/UTL:RCT2*1W                           ELFC-31
         IFP       %1,G2                                        ELFC-31
         ACW       %1                                           ELFC-31
G2       IFP       %2,G3                                        ELFC-31
         ACW       %2                                           ELFC-31
G3       IFP       %3,G4                                        ELFC-31
         ACW       %3                                           ELFC-31
G4       IFP       %4,G5                                        ELFC-31
         ACW       %4                                           ELFC-31
G5       IFP       %5,G6                                        ELFC-31
         ACW       %5                                           ELFC-31
G6       IFP       %6,G7                                        ELFC-31
         ACW       %6                                           ELFC-31
G7       IFP       %7,G8                                        ELFC-31
         ACW       %7                                           ELFC-31
G8       IFP       %8,G9                                        ELFC-31
         ACW       %8                                           ELFC-31
G9       IFP       %9,G10                                       ELFC-31
         ACW       %9                                           ELFC-31
G10      IFP       %10,G11                                      ELFC-31
         ACW       %10                                          ELFC-31
G11      IFP       %11,G12                                      ELFC-31
         ACW       %11                                          ELFC-31
G12      IFP       %12,G13                                      ELFC-31
         ACW       %12                                          ELFC-31
G13      IFP       %13,G14                                      ELFC-31
         ACW       %13                                          ELFC-31
G14      IFP       %14,G15                                      ELFC-31
         ACW       %14                                          ELFC-31
G15      IFP       %15,G16                                      ELFC-31
         ACW       %15                                          ELFC-31
G16      IFP       %16,G17                                      ELFC-31
         ACW       %16                                          ELFC-31
G17      ANOP                                                   ELFC-31
         ENDM                                                   ELFC-31
*                                                               ELFC-31
*        GENERATE LFC TABLE                                     ELFC-31
*                                                               ELFC-31
TABADDR  UTL:LFC   CI,PRE          COMMAND INPUT ENTRY          ELFC-31
         UTL:REF1  FCBPRE                                       ELFC-31
         UTL:REF2                                               ELFC-31
*                                                               ELFC-31
         UTL:LFC   DI,SI           DATA INPUT ENTRY             ELFC-31
         UTL:REF1  FCBSI                                        ELFC-31
         UTL:REF2                                               ELFC-31
*                                                               ELFC-31
         UTL:LFC   LO              AUDIT OUTPUT ENTRY           ELFC-31
         UTL:REF1  FCBLO                                        ELFC-31
         UTL:REF2                                               ELFC-31
*                                                               ELFC-31
         UTL:LFC   DO,BO           DATA OUTPUT ENTRY            ELFC-31
         UTL:REF1  FCBBO                                        ELFC-31
         UTL:REF2                                               ELFC-31
*                                                               ELFC-31
         UTL:LFC                   ERROR OUTPUT ENTRY, NOT USED ELFC-31
         UTL:REF1                                               ELFC-31
         UTL:REF2                                               ELFC-31
TABEND   DEQU      $                                            ESCT-32
*                                                               ELFC-31
*
* (C) COPYRIGHT 1983 ENCORE COMPUTER CORPORATION
*     ALL RIGHTS RESERVED
*
         TITLE     MACRO ASSEMBLER ADAPTER
************************************************************************
*                                                                      *
*            MPX-32 MACRO ASSEMBLER ADAPTER                 12NOV80    *
*                                                                      *
************************************************************************
         SPACE     3
*        BEGIN LIST OF SYMBOL TABLE TYPE CODES FOR VARIOUS USES
TYPU     EQU       X'01'           UNDEFINED SYMBOL TYPE CODE
TYPL     EQU       X'02'           LITERAL ITEM CODE
TYPC     EQU       X'03'           DEFINE A SYMBOL WITHIN COMMON BLOCK
TYPP     EQU       X'04'           NORMAL PROGRAM DEFINED SYMBOL CODE
TYPM     EQU       X'05'           MULTIPLY DEFINED SYMBOL TYPE CODE
TYPX     EQU       X'06'           EXTERNAL TYPE SYMBOL CODE
TYPD     EQU       X'07'           COMMON BLOCK DEFINITION NUMBER
TYSETSYM EQU       X'08'           SYMBOL ENTERED WITH A SET
TYMACDEF EQU       X'09'           MACRO DEFINITIION TYPE CODE
TYFRM    EQU       X'0A'           FORM DIRECTORY ITEM
TYPDP    EQU       X'0C'           DATAPOOL ITEM
TYMACREQ EQU       X'0E'           MACRO DATA REQUEST FLAG
TYPC2    EQU       2               TWO BIT TYPE CODE FOR COMMON
TYPREL   EQU       1               2 BIT TYPE CODE FOR RELOCATABLE TYPES
* LOADER FUNCTION CODES FOR OBJECT OUTPUT
PTA      EQU       0               ABSOLUTE DATA
PTO      EQU       1               ABSOLUTE/RELOCATABLE ORIGIN
PTTR     EQU       3               ABS/REL TRANSFER ADDRESS
PTR      EQU       4               RELOCATABLE DATA
PTPN     EQU       5               PROGRAM NAME
PTED     EQU       7               DEFINE LOCAL SYM ABS/REL ADR (EX DEF)
PTEX     EQU       9               EXT STRINGBACK TERMINATION (EX REF)
PTCD     EQU       10         X'A' COMMON BLOCK DEFINITION
PTCR     EQU       11         X'B' DATA REFERRING TO COMMON
PTCO     EQU       14         X'E' COMMON ORIGIN
EXPFUNC  EQU       X'D'            EXPANDED LOADER FUNCTION CODE
LF.SDEF  EQU       1          EXP.LDR.SUB.FUNC. FOR SECTION DEFINITION
LF.SORIG EQU       2          EXP.LDR.SUB.FUNC. FOR SECTION ORIGIN
LF.SREL  EQU       3          EXP.LDR.SUB.FUNC. FOR SECTION RELOCATABLE
LF.TRANS EQU       4          EXP.LDR.SUB.FUNC. FOR TRANSFER ADDRESS
LF.EXTDF EQU       5          EXP.LDR.SUB.FUNC. FOR EXTERNAL DEFINITION
LF.EXTRF EQU       6          EXP.LDR.SUB.FUNC. FOR EXTERNAL REFERENCE
*                  11 IS USED FOR SYMBOLIC DEBUGGER                11006
LF.DTID  EQU       12              DATA/TIME AND PRODUCT ID INFO   11006
*                                  FLAG=0 FOR DATE/TIME            11006
*                                  FLAG=1 FOR PRODUCT ID INFO      11006
LF.MULDP EQU        13        EXP.LDR.SUB.FUNC. FOR MULTIPLE DATAPOOL
         TITLE     FIXED CONSTANTS FOR THE H ASSEMBLER
HAERCT   GEN       12/32,20/B(HDERCT)
HAUN00   GEN       12/24,20/B(HDUN00)
HAIN     GEN       12/80,20/B(IN)  BASE ADDRESS OF INPUT AREA AND BYTE C
HATCWD   GEN       12/TCWSIZE,20/B(TCWD)   LENGTH/ADDRESS OF HEADER BUFF
QAFCBLO  GEN       12/40,20/B(PRNT)    PRNT QTY AND ADR OF PRINT BUFFER
         GEN       12/120,20/B(PRNT)     LONG LINE FOR IMAGE OUTPUT
HABS     ACB       HBBS            BASE ADR OF BINARY BYTE STREAM STACK
CSNAME   DATAD     C'**CSECT*'     NAME FOR 'CSECT' SECTION DEFINITION
DSNAME   DATAD     C'**DSECT*'     NAME FOR 'DSECT' SECTION DEFINITION
UNDEFC   DATAD     C' UNDEFINED'
EOFCONT  GEN       12/21,20/B(EOFMESS)  ABORT MESSAGE FOR FAULTY INPUT.
EOFMESS  DATA      C' EOF WITHOUT END CARD'
ERRORS   DATAD     C'0*        ERRORS'       CONSTANT FOR ERROR COUNT
ERRORS2  DATAW     C' IN '
ERRORS3  DATAW     C'    '
SYMOFLOW GEN       12/28,20/B(STOFMESS)  FOR OUTPUT OF MESSAGE.
STOFMESS DATAB     C'1** SYMBOL TABLE OVERFLOW **'
*
MSG1.A   DATAB     C' ASSEMBLE<<FATAL>> IEEE-754 OPTION 55 SET' EIEE-33
         DATAB     C' WITHIN SOURCE CODE WITHOUT OPTION '       EIEE-33
MSG1.L   DATAB     $-MSG1.A                                     EIEE-33
*
MSG2.A   DATAB     C'                  18 BEING SET PRIOR TO '  EIEE-33
         DATAB     C'ASSEMBLE EXECUTION.'                       EIEE-33
MSG2.L   DATAB     $-MSG2.A                                     EIEE-33
*
MSG3.A   DATAB     C' ASSEMBLE(WARNING) IEEE-754 OPTION 55 '    EIEE-33
         DATAB     C'SPECIFIED WITHOUT OPTION 18 BEING '        EIEE-33
MSG3.L   DATAB     $-MSG3.A                                     EIEE-33
*
MSG4.A   DATAB     C'                  SET. OPTION 18 HAS BEEN ' EIEE-33
         DATAB     C'SET, OBJECT WILL BE PURELY SECTIONED.'     EIEE-33
MSG4.L   DATAB     $-MSG4.A                                     EIEE-33
*
MSG5.A   DATAB     C' ASSEMBLE<<FATAL>> CANNOT GENERATE '       EIEE-33
         DATAB     C'IEEE-754 FORMATTED DATA ON A NON-IEEE '    EIEE-33
         DATAB     C'MACHINE.'                                  EIEE-33
MSG5.L   DATAB     $-MSG5.A                                     EIEE-33
*
         BOUND     1W
*        TABLE OF LOGICAL OPERATORS
CONDBEG  DEQU      $                                            ESCT-32
         DATAW     C'.AND'         CONDITIONAL TEST
         DATAW     C'.OR.'
         DATAW     C'.LT.'
         DATAW     C'.GT.'
         DATAW     C'.GE.'
         DATAW     C'.LE.'
         DATAW     C'.EQ.'
         DATAW     C'.NE.'
CONDLIST DEQU      $                                            ESCT-32
SIZCOND  DEQU      $-CONDBEG                                    ESCT-32
         BU        IFPRAND         .AND.
         BU        IFPROR          .OR.
         BCF    LE,IFPRO5          MAKE .TRUE. FOR .LT.
         BCF    GE,IFPRO5          .GT. IS THE .TRUE. CASE
         BCT    LE,IFPRO5          .GE. IS THE .TRUE. CASE
         BCT    GE,IFPRO5          .LE. IS THE .TRUE. CASE
         BCT    EQ,IFPRO5          .EQ. IS THE .TRUE. CASE
         BCF    EQ,IFPRO5          .NE. IS THE .TRUE. CASE
IFCONDBR CEQU      $                                            ESCT-32
         BU        IFINIT          INITIAL CASE
OVFLCONT GEN       12/21,20/B(OVFLMESS)    FOR OUTPUT OF MESSAGE
OVFLMESS DATAB     C' MACRO TABLE OVERFLOW'
STERMESS DATA      C' MACRO STACK ERROR'
         BOUND     1W
STERCONT GEN       12/18,20/B(STERMESS)  OUTPUT MESSAGE FOR ABORT.
* LIST OF LEGAL DIRECTIVES FOR LIST PSEUDO-OP
         DATAW     C'REP '         LIST REPT EXPANSIONS
         DATAW     C'NORE'         DON'T LIST REPT EXPANSIONS
         DATAW     C'MAC '         LIST MACRO EXPANSIONS
         DATAW     C'NOMA'         DON'T LIST MACRO EXPANSIONS
         DATAW     C'NGLI'         LIST ALL SOURCE LINES
         DATAW     C'NONG'         DONT LIST NON-ASSEMBLED SOURCE
         DATAW     C'ON '          LISTING ON
         DATAW     C'OFF '         LISTING OFF
         DATAW     C'DATA'         ALLOW LISTING OF EXTENSIONS
LISTD    DATAW     C'NODA'         DON'T ALLOW LISTING OF EXTENSIONS
* LIST OF ADDRESSES OF LISTING CONTROL FLAGS
         ZBM       REPPRINT,HHBITS2  LIST REPT EXPANSIONS
         SBM       REPPRINT,HHBITS2  DON'T LIST REPT EXPANSIONS
         ZBM       MACPRINT,HHBITS2  LIST MACRO EXPANSIONS
         SBM       MACPRINT,HHBITS2  DON'T LIST MACRO EXPANSIONS
         ZBM       NGPRINT,HHBITS  LIST ALL SOURCE LINES
         SBM       NGPRINT,HHBITS  DONT LIST NON-ASSEMBLED SOURCE
         ZBM       APON,HHBITS     ALLOW LISTING
         SBM       APON,HHBITS     DONT ALLOW LISTING
         ZBM       APEX,HHBITS     ALLOW EXTENSIONS
LISTP    SBM       APEX,HHBITS     DONT ALLOW EXTENSIONS
         BOUND     1W
TCTS     GEN     8/00,24/H(TCD1)   C TYPE CONSTANT
         GEN     8/00,24/H(TGD1)   G TYPE CONSTANT
         GEN     8/00,24/H(TXD1)   X TYPE CONSTANT
         GEN     8/31,24/H(TNFER)  N TYPE CONSTANT
         GEN     8/63,24/H(TNFER)  F TYPE CONSTANT
         GEN     8/08,24/H(TNFER)  E TYPE CONSTANT
         GEN     8/40,24/H(TNFER)  R TYPE CONSTANT
TFDD     GEN       8/C' ',24/H(TFI) 0W
         GEN       8/C'.',24/H(TFF) 1W      -5W
         GEN       8/C'E',24/H(TFX) 2W      -4W
         GEN       8/C'B',24/H(TFB) 3W      -3W
         GEN       8/C',',24/H(TFO) 4W      -2W  ALL DONE
         GEN      8/C'"'',24/H(TFO) 5W      -1W  ALL DONE
TFDE     DEQU      $                                            ESCT-32
TDMP     DATA      0,0,0,0         0X16 IN DIGIT DECIMAL INVERTED FORM
         DATA      6,1,0,0         1X16
         DATA      2,3,0,0         2X16
         DATA      8,4,0,0         3X16
         DATA      4,6,0,0         4X16
         DATA      0,8,0,0         5X16
         DATA      6,9,0,0         6X16
         DATA      2,1,1,0         7X16
         DATA      8,2,1,0         8X16
         DATA      4,4,1,0         9X16
BNDWS1   DATAB     2,0,1,0,3,0,1,0 PROGRAM COUNTER STATUS INDICATORS
BNDWS2   DATAB     X'1',X'3',X'7'  MODULO 2,4,8 MASKS
GRPSS2   DATAB     3,2,0,0,0       OFFSET FOR B,H,W,D,A TYPE ADR RESP.
TCTG     DATA      1,2,4,8
VALS     DATAB     9,C' ,"'()+-*/'   GENERAL LIST OF TERMINATORS
VDDC     DATAB     0,0,0,0,0,0,1,2,3  POINTERS FOR ABOVE LIST
VDT      DATAB     0,0             NULL
         DATAB     0,1             UNDEFINED
         DATAB     0,0             LITERAL
         DATAB     2,2             COMMON
         DATAB     0               PROGRAM ABSOLUTE
         DATAB     1               PROGRAM RELATIVE
         DATAB     0,1             MULTIPLY DEFINED
         DATAB     3,3             EXTERNAL
         DATAB     2,2             COMMON
         DATA      0,1,0,0,0,0,0,0,0,0  EXTENSIONS FOR SET,MACRO,FORM
VDC      DATAD     X'080C0C0408040404'   + OPERATOR
         DATAD     X'0804040418040404'   + OPERATOR
         DATAD     X'100C0C0420100404'  - OPERATOR
         DATAD     X'0404140404040404'   - OPERATOR
         DATAD     X'1004040404040404'   * OPERATOR
         DATAD     X'0404040404040404'   * OPERATOR
         DATAD     X'1004040404040404'   / OPERATOR
         DATAD     X'0404040404040404'   / OPERATOR
AGER     DATAW     X'0007FFFF'     BYTE ADDRESS MASK
         DATAW     X'0107FFFE'     HALFWORD ADR MASK AND ERROR MASK
         DATAW     X'0307FFFC'    WORD ADDR MASK AND ERROR MASK
         DATAW     X'0707FFFC'     DOUBLWORD ADR MASK AND ERROR MASK
         DATAW     X'0007FFFF'     FULL RANGE ADR MASK
         DATAW     X'000FFFFF'     ADR MASK TO LEAVE ADR AS IS
         DATAW     X'0307FFFC'     BASE REG MODE MASK
         DATAW     X'0007FFFF'     FULL RANGE FOR SUABR         EBRM-33
         DATAW     X'0007FFFF'     FULL RANGE FOR LABR          EBRM-33
AGES     DATAW     X'00080000'     BYTE F AND CC BITS
         DATAW     1               HALFWORD F AND CC BITS
         DATAW     0               WORD F AND CC BITS
         DATAW     2               DOUBLE WORD F AND CC BITS
         DATAW     0               A TYPE F AND CC BITS (PSEUDOS ONLY)
         DATAW     0               LEAVE F AND CC BITS AS THEY ARE
         DATAW     X'00080000'     BASE REG MODE NEEDS F BIT
         DATAW     0               SUABR DOESN'T NEED F BIT     EBRM-33
         DATAW     X'00080000'     LABR DOES NEED F BIT         EBRM-33
         SPACE                                                  EBRM-33
MSKTBL   DEQU      $                                            ESCT-32
         DATAW     X'00000001'                                  EBRM-33
         DATAW     X'00000002'                                  EBRM-33
         DATAW     X'00000004'                                  EBRM-33
         DATAW     X'00000008'                                  EBRM-33
         DATAW     X'00000010'                                  EBRM-33
         DATAW     X'00000020'                                  EBRM-33
         DATAW     X'00000040'                                  EBRM-33
         DATAW     X'00000080'                                  EBRM-33
         DATAW     X'00000100'                                  EBRM-33
         DATAW     X'00000200'                                  EBRM-33
         DATAW     X'00000400'                                  EBRM-33
         DATAW     X'00000800'                                  EBRM-33
         DATAW     X'00001000'                                  EBRM-33
         DATAW     X'00002000'                                  EBRM-33
         DATAW     X'00004000'                                  EBRM-33
         DATAW     X'00008000'                                  EBRM-33
         DATAW     X'00010000'                                  EBRM-33
         DATAW     X'00020000'                                  EBRM-33
         DATAW     X'00040000'                                  EBRM-33
         DATAW     X'00080000'                                  EBRM-33
         DATAW     X'00100000'                                  EBRM-33
         DATAW     X'00200000'                                  EBRM-33
         DATAW     X'00400000'                                  EBRM-33
         DATAW     X'00800000'                                  EBRM-33
         DATAW     X'01000000'                                  EBRM-33
         DATAW     X'02000000'                                  EBRM-33
         DATAW     X'04000000'                                  EBRM-33
         DATAW     X'08000000'                                  EBRM-33
         DATAW     X'10000000'                                  EBRM-33
         DATAW     X'20000000'                                  EBRM-33
         DATAW     X'40000000'                                  EBRM-33
         DATAW     X'80000000'                                  EBRM-33
OPTMSK   DATAW     X'000C63FF'     MASKS OPTS 11-13,16-18,21-32 EBRM-33
CNUE     SLLD      6,5             PSEUDO MULTIPLIER FOR F
         SLLD      6,0                                   BLANK
         SLLD      6,0                                   B
         SLLD      6,1                                   H
         SLLD      6,2                                   W
         SLLD      6,3                                   D
         SLLD      6,0                                    B
         SLLD      6,1                                    H
         SLLD      6,2                                    W
         SLLD      6,3                                    D
CNUD     DATAB     N'32',N'1',N'1',N'2',N'4',N'8' ASSOCIATED MULTIPLIERS
CNUC     DATAB     C'F'            'FILE' TERMINATOR
         DATAB     C' BHW'         CONSTANT TYPE AND TERMINATOR LIST
TCTF     DATAB     C'DACGXNFE'
TCTE     DATAB     C'R'
ARGMIN   DATA      1,1,2,2         MINIMUM NUMBER OF OPERANDS FOR VARIOU
ARGMAX   DATA      1,2,2,3         MAXIMUM NUMBER OF OPERANDS FOR VARIOU
*        BEGIN LIST OF SYMBOL TYPES FOR PRINTING USE.  THIS LIST
*        IS LAID OUT FOR LOOK-UP FROM THE SYMBOL TYPE CODE AND ABS/REL
*        BIT .
SSTL     DATA      C'NNUULLCC PMMXYDD'  NULL,UNDEF,LIT,COMM,PROG,
*        MULT, EXTERNAL, AND BLOCK IN THAT ORDER BY TWOS
         DATA      C'JKBBFF  '     ADD ON TO ABOVE FOR MACRO TYPE ITEMS
*        LIST OF CONVERSION FACTORS FROM VAL INTERNAL CODES TO
*        NORMAL SYMBOL TABLE CODES
VDTO     GEN       8/A(TYPP*2),8/A(TYPP*2+1),8/A(TYPC*2),8/A(TYPX*2)
* ID FOR ABOVE       PROG ABS    PROG REL      COMMON      EXTERNAL
BTX4     DATA      C'0123456789ABCDEF'   HEX DIGIT TO ASCII LOOK-UP TABL
DSRC     SRC       3,0
DSLLD    SLLD      2,0
DSRL     SRL       2,0
         IFT       UNIXF,SKIP                                   *JCB*
HWKSPA   DATAW     C'    ',0                                    *JCB*
SKIP     ANOP                                                   *JCB*
         IFF       UNIXF,SKIP                                   *JCB*
HWKSPA   DATAW     C'    '
SKIP     ANOP                                                   *JCB*
HWUP1    GEN       12/4,20/B(HWKSPA)       GETS A VERY SHORT BLANK LINE
TALLS1   GEN       8/A(TYPU),24/0  REQUEST INDICATOR. CK LABL VS SYM TBL
SECTYPES DATAB     TYPU,TYPL,TYPP,TYPM,TYPX,TYSETSYM
NSECTYPS DEQU      $                                            ESCT-32
*
* (C) COPYRIGHT 1983 ENCORE COMPUTER CORPORATION
*     ALL RIGHTS RESERVED
*
*!!!!!!!!!!TITLE!!!!!OPERATOR!PROCESSOR!DIRECTORY!!!!!!!!!!!!!!!EASC-32
*!!!!!!!!!!BOUND!!!!!1W!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!EASC-32
*!KINT!!!!!EQU!!!!!!!$!!!!!!!!!BASE!OF!PROCESSOR!DIRECTORY!LIST!EASC-32
*!!!!!!!!!!BU!!!!!!!!AERR!!!!!!!!!!!!ENTRY!!0!-!ERROR!!!!!!!!!!!EASC-32
*!!!!!!!!!!BU!!!!!!!!NSS!!!!!!!!!!!!!ENTRY!!1!-!NOP,HALT,WAIT!!!EASC-32
*!KINTL1!!!EQU!!!!!!!$-KINT!!!!!!!!!!NO!AUTOMATIC!OPERAND!STRIP!EASC-32
*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!THIS!POINT!!!!!!!!!!!!!!!!!EASC-32
*!!!!!!!!!!BU!!!!!!!!CALM!!!!!!!!!!!!ENTRY!!2!-!CALL!MONITOR!!!!EASC-32
*!!!!!!!!!!BU!!!!!!!!BM!!!!!!!!!!!!!!ENTRY!3!-!SBM,ZBM,ABM,TBM!!EASC-32
*!!!!!!!!!!BU!!!!!!!!RRO!!!!!!!!!!!!!ENTRY!!4!-!REGISTER-REGIST!EASC-32
*!!!!!!!!!!BU!!!!!!!!LER!!!!!!!!!!!!!ENTRY!!5!-!LCS,ES,RND!!!!!!EASC-32
*!!!!!!!!!!BU!!!!!!!!TRSW!!!!!!!!!!!!ENTRY!!6!-!TRSW!!!!!!!!!!!!EASC-32
*!!!!!!!!!!BU!!!!!!!!RTB!!!!!!!!!!!!!ENTRY!!7!-!SBR,TBR,ABR,ZBR!EASC-32
*!!!!!!!!!!BU!!!!!!!!SHF!!!!!!!!!!!!!ENTRY!!8!-!SHIFTS!!!!!!!!!!EASC-32
*!!!!!!!!!!BU!!!!!!!!NORDS!!!!!!!!!!!ENTRY!9!-!NOR,NORD,SCZ!!!!!EASC-32
*!!!!!!!!!!BU!!!!!!!!ZRX!!!!!!!!!!!!!ENTRY!10!-!ZR!!!!!!!!!!!!!!EASC-32
*!!!!FOLLOWING!ENTRY!(#11)!CHANGED!FROM!ERROR!TO!BU!TO!SEPARATE!!EASC-32
*!!!!AC?!DIRECTIVES!FROM!OTHER!VECTOR!14!DIRECTIVES.!SEE!CHANGE!!EASC-32
*!!!!IN!OPSTABLE!LAYOUT.!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!EASC-32
*!!!!!!!!!!BU!!!!!!!!AERR!!!!!!!!!!!!ENTRY!11!-!SPARE!!!!!!!!!!!!EASC-32
*!!!!!!!!!!BU!!!!!!!!BU!!!!!!!!!!!!!!ENTRY!11!-!AC?!(TREAT!AS!BU)EASC-32
*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!EASC-32
*!!!!!!!!!!BU!!!!!!!!TRIP!!!!!!!!!!!!ENTRY!12!-!TRP,TPR!!!!!!!!!EASC-32
*!!!!!!!!!!BU!!!!!!!!AGEN!!!!!!!!!!!!ENTRY!13!-!MOST!MEMORY!REF!EASC-32
*!!!!!!!!!!BU!!!!!!!!BU!!!!!!!!!!!!!!ENTRY!14!-!BU,BFT,ZM!,EXM,!EASC-32
*!!!!!!!!!!BU!!!!!!!!BI!!!!!!!!!!!!!!ENTRY!15!-!BIB,BIW,BIH,BID!EASC-32
*!!!!!!!!!!BU!!!!!!!!FPP!!!!!!!!!!!!!ENTRY!16!-!FLOATING!POINT!!EASC-32
*!!!!!!!!!!BU!!!!!!!!IMOP!!!!!!!!!!!!ENTRY!17!-!IMMEDIATE!OPS!!!EASC-32
*!!!!!!!!!!BU!!!!!!!!EXR!!!!!!!!!!!!!ENTRY!18!-!EXR,EXRR!!!!!!!!EASC-32
*!!!!!!!!!!BU!!!!!!!!CDL!!!!!!!!!!!!!ENTRY!19!-!CDL!SEMI-PSEUDO!EASC-32
*!!!!!!!!!!BU!!!!!!!!IO!!!!!!!!!!!!!!ENTRY!20!-!CD,TD!!!!!!!!!!!EASC-32
*!!!!!!!!!!BU!!!!!!!!INT!!!!!!!!!!!!!ENTRY!21!-!EI,DI,RI,AI,DAI!EASC-32
*!KINTL2!!!EQU!!!!!!!$-KINT!!!!!!!!!!NO!AUTOMATIC!OPERAND!STRIP!EASC-32
*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!THIS!POINT!!!!!!!!!!!!!!!!!EASC-32
*!!!!!!!!!!BU!!!!!!!!DATA!!!!!!!!!!!!ENTRY!22!-!DATA,DATAH,DATA!EASC-32
*!!!!!!!!!!BU!!!!!!!!VFD!!!!!!!!!!!!!ENTRY!23!-!GEN!PSEUDO!!!!!!EASC-32
*!!!!!!!!!!BU!!!!!!!!AERR!!!!!!!!!!!!ENTRY!24!-!SPARE!!!!!!!!!!!!!EINS-3
*!KINTL3!!!EQU!!!!!!!$-KINT!!!!!!!!!!NO!BOUNDING!CHECKS!WILL!BE!EASC-32
*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!THIS!POINT!!!!!!!!!!!!!!!!!EASC-32
*!!!!!!!!!!ENTRY!24!MOVED!BELOW!KINTL3!-!USED!FOR!REIS/SEIS!!!!!!!EINS-3
*!!!!!!!!!!BU!!!!!!!!RS.EIS!!!!!!!!!!ENTRY!24!-!REIS,SEIS!!!!!!!!!EINS-3
*!!!!!!!!!!BU!!!!!!!!END!!!!!!!!!!!!!ENTRY!25!-!END!!!!!!!!!!!!!!EASC-32
*!!!!!!!!!!BU!!!!!!!!PROG!!!!!!!!!!!!ENTRY!26!-!PROGRAM!!!!!!!!!EASC-32
*!!!!!!!!!!BU!!!!!!!!REF!!!!!!!!!!!!!ENTRY!27!-!REF,DEF!!!!!!!!!EASC-32
*!!!!!!!!!!BU!!!!!!!!ORG!!!!!!!!!!!!!ENTRY!28!-!ORG!!!!!!!!!!!!!EASC-32
*!!!!!!!!!!BU!!!!!!!!AREL!!!!!!!!!!!!ENTRY!29!-!ABS,!REL,!DSECT!EASC-32
*!!!!!!!!!!BU!!!!!!!!BOUND!!!!!!!!!!!ENTRY!30!-!BOUND!!!!!!!!!!!EASC-32
*!!!!!!!!!!BU!!!!!!!!EQU!!!!!!!!!!!!!ENTRY!31!-!EQU!!!!!!!!!!!!!EASC-32
*!!!!!!!!!!BU!!!!!!!!RES!!!!!!!!!!!!!ENTRY!32!-!RES!!!!!!!!!!!!!EASC-32
*!!!!!!!!!!BU!!!!!!!!CCP1!!!!!!!!!!!!ENTRY!33!-!COMMON!!!!!!!!!!EASC-32
*!!!!!!!!!!BU!!!!!!!!TITL!!!!!!!!!!!!ENTRY!34!-!TITLE!!!!!!!!!!!EASC-32
*!!!!!!!!!!BU!!!!!!!!PAGP!!!!!!!!!!!!ENTRY!35!-!PAGE!!!!!!!!!!!!EASC-32
*!!!!!!!!!!BU!!!!!!!!LIST!!!!!!!!!!!!ENTRY!36!-!LIST!!!!!!!!!!!!EASC-32
*!!!!!!!!!!BU!!!!!!!!SPACE!!!!!!!!!!!ENTRY!37!-!SPACE!!!!!!!!!!!EASC-32
*!!!!!!!!!!BU!!!!!!!!AERR!!!!!!!!!!!!ENTRY!38!-!SPARE!!!!!!!!!!!EASC-32
*!!!!!!!!!!BU!!!!!!!!SDIRS!!!!!!!!!!!ENTRY!38!-!S!DIRECTIVES!!!!EASC-32
*!!!!!!!!!!SPACE!!!!!1!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!EASC-32
*!!!BEGIN!ENTRIES!FOR!MNEMONICS!WHICH!ARE!SUPPRESSED!!!!!!!!!!!!EASC-32
*!!!VIA!LIST!NONG!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!EASC-32
*!KINTLN1!!EQU!!!!!!!$-KINT!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!EASC-32
*!!!!!!!!!!BU!!!!!!!!NEXT!!!!!!!!!!!!ENTRY!39!-!ANOP,!DO!NOTHIN!EASC-32
*!!!!!!!!!!BU!!!!!!!!IFPRO!!!!!!!!!!!ENTRY!40-IFT/IFF!PROCESSOR!EASC-32
*!!!!!!!!!!BU!!!!!!!!DEFMPRO!!!!!!!!!ENTRY!41!-!DEFM!!!!!!!!!!!!EASC-32
*!!!!!!!!!!BU!!!!!!!!ENDMPRO!!!!!!!!!ENTRY!42!-!ENDM!!!!!!!!!!!!EASC-32
*!!!!!!!!!!BU!!!!!!!!SETPRO!!!!!!!!!!ENTRY!43!-!SET,SE3F#0ET3!!!EASC-32
*!!!!!!!!!!BU!!!!!!!!GOTOP!!!!!!!!!!!ENTRY!44!-!GOTO!!!!!!!!!!!!EASC-32
*!!!!!!!!!!BU!!!!!!!!ENDRP!!!!!!!!!!!ENTRY!45!-!ENDR!!!!!!!!!!!!EASC-32
*!!!!!!!!!!BU!!!!!!!!REPTP!!!!!!!!!!!ENTRY!46!-!REPT!!!!!!!!!!!!EASC-32
*!!!!!!!!!!BU!!!!!!!!EXITMP!!!!!!!!!!ENTRY!47!-!EXITM!!!!!!!!!!!EASC-32
*!!!!!!!!!!BU!!!!!!!!FORMP!!!!!!!!!!!ENTRY!48!-!FORM!!!!!!!!!!!!EASC-32
*!KINTLN2!!EQU!!!!!!!$-KINT!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!EASC-32
*!!!END!ENTRIES!FOR!MNEMONICS!WHICH!ARE!SUPPRESSED!!!!!!!!!!!!!!EASC-32
*!!!VIA!LIST!NONG!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!EASC-32
*!!!!!!!!!!SPACE!!!!!1!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!EASC-32
*!!!!!!!!!!BU!!!!!!!!LPOP!!!!!!!!!!!!ENTRY!49!-!LPOOL!!!!!!!!!!!EASC-32
*!!!!!!!!!!BU!!!!!!!!REZ!!!!!!!!!!!!!ENTRY!50!-!REZ!!!!!!!!!!!!!EASC-32
*!KINTL4!!!EQU!!!!!!!$-KINT!!!!!!!!!!MARK!END!OF!THE!OPERATION!!EASC-32
*!!!!!!!!!!BU!!!!!!!!SETCPU!!!!!!!!!!ENTRY!51!-!SETCPU!,!RDSTS!!EASC-32
*!!!!!!!!!!BU!!!!!!!!SVC!!!!!!!!!!!!!ENTRY!52!-!SVC!!!!!!!!!!!!!EASC-32
*!!!!!!!!!!BU!!!!!!!!EXTIO!!!!!!!!!!!ENTRY!53!-!EXTIO!!!!!!!!!!!!!ENIS-3
*!!!!!!!!!!BU!!!!!!!!TRAP!!!!!!!!!!!!ENTRY!53!-!TC!!!!!!!!!!!!!!!!ENIS-3
*!!!!!!!!!!BU!!!!!!!!EXTIO!!!!!!!!!!!ENTRY!54!-!EXTIO!!!!!!!!!!!!!ENIS-3
         SPACE     3
TEMP     RES       1D
BASE     DATAD     X'41A0000000000000'      10.**1    DO NOT MOVE
         DATAD     X'4264000000000000'      10.**2    DO NOT MOVE
         DATAD     X'4427100000000000'      10.**4    DO NOT MOVE
         DATAD     X'475F5E1000000000'      10.**8    DO NOT MOVE
         DATAD     X'4E2386F26FC10000'      10.**16   DO NOT MOVE
         DATAD     X'5B4EE2D6D415B85A'      10.**32   DO NOT MOVE
         DATAD     X'76184F03E93FF9F4'      10.**64   DO NOT MOVE
ONE      DATAD     X'4110000000000000'
*
RECSIZ   EQU       120B
         IFF       UNIXF,SKIP                                   *JCB*
         TITLE     MACRO ASSEMBLER ADAPTER - TST4DISC
* FOR LFCS BO, SI, PRE, AND UT1
*
*
* TEST LOGICAL FILE CODE FOR NON SYS DISC FILE
* R1=FCB ADDR ON CALL
* CC1 SET - NON SYS DISC FILE, USE RM. CC1 RESET - USE NORMAL I/O
*
TST4DISC ZBR       R0,1            CLEAR CC1                      AS21
         STF       R0,S4R          SAVE REGS
         LI        R0,X'10'        SET UP FOR BLOCKED            11004
         TBM       5,2W,R1         DOES FCB SHOW UNBLOCKED
         BNS       RET4D.UN        UNBLOCKED, USE NORMAL I/O     11004
         LW        R4,0W,R1        GET LFC                       11003
         ANMW      R4,=X'FFFFFF'   MASK IT                       11003
         LA        R1,INQ.INFO     SET UP INQUIRY INFO AREA      11003
         ZR        R5              CLEAR R5                      11003
         ZR        R7              NO CNP                        11003
         SVC       2,X'48'         M.INQUIRY                     11003
         LW        R1,S4R+1W       RE-LOAD LFC ADDR INTO R1      11003
         CI        R7,29           IS IT ASSIGNED ??             11003
         BEQ       RET4DX          NO                            11003
         LW        R2,INQ.INFO+3W  GET DTT ADDRESS               11003
         LB        R6,0,R2         GET DEV TYPE                  11003
         CI        R6,3            IS IT A DISC
         BGT       RET4D           BR IF NOT DISC
         LW        R2,INQ.INFO+1W  GET FAT ADDR                  11003
         LB        R6,DFT.ACF,R2   GET ACCESS FLAGS/SYS FILE CODE  11003
         ANMW      R6,=X'7'        MASK ALL BUT SYS FILE CODE      11009
         BU        RET4D           NEVER USE RM ROUTINES        S880752
*!!!!!!!!CI!!!!!!!!R6,0!!!!!!!!!!!!IS!IT!SYS!FILE!!!!!!!!!!!!!!!S880752
*!!!!!!!!BNE!!!!!!!RET4D!!!!!!!!!!!RET!IF!IT!IS!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!SBM!!!!!!!1,S4R!!!!!!!!!!!SET!CC1!FOR!RET!TO!USE!RM!ROUS880752
*!!!!!!!!BL!!!!!!!!RM.OPEN!!!!!!!!!OPEN!VIA!REC!MGR!!!!!!!!!!!!!S880752
*!!!!!!!!BU!!!!!!!!RET4DX!!!!!!!!!!RESTORE!REGS!AND!RETURN!!!!!!S880752
         SPACE     1
RET4D.UN CEQU      $                                            ESCT-32
         LI        R0,X'20'        SET UP FOR UNBLOCKED          11004
RET4D    CEQU      $                                            ESCT-32
         STB       R0,CNPXX+2W+1B  STORE IN USAGE FIELD OF CNP   11004
         CI        R6,2            IS THIS SGO ??                  11009
         BEQ       RET4D.0         YES - FORCE BLK, APPEND         11009
         CI        R6,4            IS THIS SBO ??              11003
         BNE       RET4D.1         NO - CONTINUE               11003
RET4D.0  CEQU      $                                            ESCT-32
         LI        R0,X'10'        SET UP FOR BLOCKED            11004
         STB       R0,CNPXX+2W+1B  STORE IN USAGE FIELD OF CNP   11004
         LI        R7,5            SET UP APPEND ACCESS        11003
         STB       R7,CNPXX+2W     STORE ACCESS INTO CNP       11003
RET4D.1  CEQU      $                                            ESCT-32
         LW        R7,6W,R1        GET ERROR RETURN ADDRESS    11003
         STW       R7,IOERXX       PUT IN CNP                  11003
         LA        R7,CNPXX        GET CNP ADDRESS             11003
         SVC       2,X'42'         M.OPENR                     11003
RET4DX   LF        R0,S4R          RESTORE REGS
         TRSW      R0              RETURN
S4R      RES       1F              REG SAVE AREA
*
*        LFC SUBSTITUTION ROUTINE - READS FPT AND LFC TABLE AND ELFC-31
*        SUBSTITUTES ASSIGNED LFC'S INTO REFERENCING DATA       ELFC-31
*        STRUCTURES                                             ELFC-31
*                                                               ELFC-31
LFCSUB   CEQU      $               ROUTINE TO SUBSTITUTE LFC'S  ESCT-32
         LW        R2,C.TSAD       GET TSA ADDRESS              ELFC-31
         LA        R1,TABADDR      LFC TABLE ADDRESS TO R1      ELFC-31
LSUB.0   LA        R7,TABEND       GET END ADDRESS OF TABLE     ELFC-31
         CAR       R1,R7           ARE WE AT THE END?           ELFC-31
         BLE       LSUB.7          RETURN IF SO                 ELFC-31
         LB        R5,3B,R1        GET NUMBER OF LFC'S IN ENTRY ELFC-31
         BZ        LSUB.3          NO ENTRY IF ZERO             ELFC-31
         TRN       R5,R5                                        ELFC-31
LSUB.1   ADI       R1,1W           POINT TO FIRST LFC           ELFC-31
         LW        R3,T.FPTA,R2    GET FPT ADDRESS              ELFC-31
         LNB       R4,T.FILES,R2   GET NUMBER OF FILES          ELFC-31
         LW        R6,0,R1         GET LFC                      ELFC-31
LSUB.2   CAMW      R6,0,R3         COMPARE TABLE LFC TO FPT LFC ELFC-31
         BEQ       LSUB.4          DO THEY MATCH?               ELFC-31
         ADI       R3,3W           CONTINUE IF NOT              ELFC-31
         BIB       R4,LSUB.2                                    ELFC-31
         BIW       R5,LSUB.1       GOTO NEXT LFC IN TABLE       ELFC-31
LSUB.3   ADI       R1,1W           NO MATCH FOUND, NEXT ENTRY   ELFC-31
         ADMW      R1,0,R1                                      ELFC-31
         ADI       R1,1W                                        ELFC-31
         ADMW      R1,0,R1                                      ELFC-31
         ADI       R1,1W                                        ELFC-31
         BU        LSUB.0                                       ELFC-31
LSUB.4   TRN       R5,R5           REMAINING LFC ENTRIES        ELFC-31
         ADR       R5,R1           ADD TO TABLE POINTER         ELFC-31
         LNB       R4,3B,R1        GET NUMBER OF REFERENCES     ELFC-31
         BEQ       LSUB.5B         SKIP IF ZERO                 ELFC-31
LSUB.5   ADI       R1,1W                                        ELFC-31
         LW        R3,0,R1                                      ELFC-31
         STW       R6,0,R3         SAVE LFC INTO REFERENCES     ELFC-31
         BIW       R4,LSUB.5                                    ELFC-31
LSUB.5B  ADI       R1,1W                                        ELFC-31
         LNB       R4,3B,R1        GET NUMBER OF C STRING REFS. ELFC-31
         BEQ       LSUB.6B                                      ELFC-31
         SLL       R6,8            SHIFT LFC STRING             ELFC-31
         SBR       R6,26           BLANK LAST BYTE              ELFC-31
LSUB.6   ADI       R1,1W                                        ELFC-31
         LW        R3,0,R1                                      ELFC-31
         STW       R6,0,R3         SAVE INTO REFERENCES         ELFC-31
         BIW       R4,LSUB.6                                    ELFC-31
LSUB.6B  ADI       R1,1W                                        ELFC-31
         BU        LSUB.0          NEXT ENTRY                   ELFC-31
LSUB.7   TRSW      R0                                           ELFC-31
*                                                               ELFC-31
*-----------------------------------------------------------------------
*                                                               ETCM-32
*        TASK CODE MANAGEMENT OBJECT RECORD DEFINITIONS         ETCM-32
*                                                               ETCM-32
*-----------------------------------------------------------------------
*                                                               ETCM-32
*        COMMON HEADER DEFINITON                                ETCM-32
*                                                               ETCM-32
TMO.CB   EQU       0B                  COMMAND BYTE             ETCM-32
TMO.BC   EQU       TMO.CB+1B           BYTE COUNT               ETCM-32
TMO.LEN  EQU       TMO.BC+1B           LENGTH                   ETCM-32
TMO.FLAG EQU       TMO.LEN+1B          FLAGS                    ETCM-32
*                                                               ETCM-32
*        TYPE 2 RECORD DEFINITONS                               ETCM-32
*                                                               ETCM-32
TMO.TOW1 EQU       TMO.CB+1W           TASK OPTION WORD 1       ETCM-32
TMO.TOW2 EQU       TMO.TOW1+1W         TASK OPTION WORD 2       ETCM-32
TMO.TRL  EQU       TMO.TOW2+1W         TASK REVISION LEVEL      ETCM-32
TMO.RRSC EQU       TMO.TRL+1W          RRS COUNT                ETCM-32
TMO.INCC EQU       TMO.RRSC+1H         INCLUDE COUNT            ETCM-32
TMO.TPN  EQU       TMO.INCC+1H         TASK PATHNAME            ETCM-32
*                                                               ETCM-32
*        TYPE 3 RECORD DEFINITIONS                              ETCM-32
*                                                               ETCM-32
TMO.RRS  EQU       TMO.CB+1W           TYPE 1 RRS ENTRY         ETCM-32
*-----------------------------------------------------------------------
         TITLE     BLD_PRCT - BUILD PROCESSOR TOKEN             ETCM-32
*-----------------------------------------------------------------------
* SUBROUTINE TO BUILD PROCESSOR TOKEN:                          ETCM-32
*                                                               ETCM-32
*        BLD_PRCT                                               ETCM-32
*                                                               ETCM-32
*  IN:   NONE                                                   ETCM-32
*                                                               ETCM-32
* OUT:   R2 = ADDR OF TYPE 2 OBJECT RECORD                      ETCM-32
*        R7 = ACTUAL LENGTH OF TOKEN BUFFER                     ETCM-32
*             or ERROR STATUS CODE IF CC1 SET                   ETCM-32
*        ALL OTHER REGISTERS ???????                            ETCM-32
*                                                               ETCM-32
*-----------------------------------------------------------------------
*                                                               ETCM-32
BLD_PRCT EQU       $                                            ETCM-32
         STF       R0,TCM.SAVE                                  ETCM-32
         M.MYID    IDSTAT          GET TASK ID NUMBER           ETCM-32
         LB        R1,IDSTAT       GET DQE INDEX                ETCM-32
         SLL       R1,2            CONVERT TO BYTE COUNT        ETCM-32
         ADMW      R1,C.ADAT       ADD DQE TABLE BASE ADDR      ETCM-32
         LW        R1,0,X1         GET POINTER TO DQE           ETCM-32
         LD        R4,DQE.CVOL,X1      GET RID FOR CURRENT TASK ETCM-32
         STD       R4,TCM.RID                  .                ETCM-32
         LD        R6,DQE.CVOL+1D,X1           .                ETCM-32
         STD       R6,TCM.RID+1D               .                ETCM-32
         LD        R4,DQE.CVOL+2D,X1           .                ETCM-32
         STD       R4,TCM.RID+2D               .                ETCM-32
         LD        R6,DQE.CVOL+3D,X1           .                ETCM-32
         STD       R6,TCM.RID+3D               .                ETCM-32
         M.LOC     TCM.RIDV,TCM.XRD    GET RD FOR TASK          ETCM-32
         BS        BLD_PRCX            BRANCH IF ERROR          ETCM-32
         LI        R7,1                INIT LENGTH COUNTER      ETCM-32
         LA        R1,TCM.XRD+RD.IDNAM ADDR OF VOL NAME IN RD   ETCM-32
         LA        R2,TCM.T2PN+1B      ADDR OF PATHNAME IN OBJ  ETCM-32
         BL        TCM.MVST            MOVE VOL INTO PATHNAME   ETCM-32
         LI        R4,G'('                                      ETCM-32
         STB       R4,0,X2          IDENTIFY START OF DIRECTORY ETCM-32
         ABR       R2,31            INCREMENT DESTINATION INDEX ETCM-32
         ABR       R7,31               INCREMENT LENGTH COUNTER ETCM-32
         LA        R1,TCM.XRD+RD.DNAME ADDR OF DIR NAME IN RD   ETCM-32
         BL        TCM.MVST            PUT DIR NAME IN PATHNAME ETCM-32
         LI        R4,G')'                                      ETCM-32
         STB       R4,0,X2           IDENTIFY END OF DIRECTORY  ETCM-32
         ABR       R2,31             INCREMENT DESTINATION INDX ETCM-32
         ABR       R7,31               INCREMENT LENGTH COUNTER ETCM-32
         LA        R1,TCM.XRD+RD.DIRP  ADDR OF FILE NAME IN RD  ETCM-32
         BL        TCM.MVST            PUT FILE NAME IN PATHNAM ETCM-32
         LA        R2,TCM.RT2          ADDR OF OBJECT RECORD    ETCM-32
         STW       R2,TCM.SAVE+2W                               ETCM-32
         ADI       R7,TMO.TPN     ADJUST LENGTH FOR FIXED INFO  ETCM-32
         STB       R7,TMO.LEN,X2       STORE AS OBJ REC LENGTH  ETCM-32
         STW       R7,TCM.SAVE+7W                               ETCM-32
         M.PGOD                   GET PROGRAM OPTION WORDS      EIEE-33
*!!!!!!!!ZR!!!!!!!!R6!!!!!!!!!!!!!!NO!OPTIONS!FOR!OPTION!WD!2!!!EIEE-33
         STW       R6,TMO.TOW2,X2      PUT 2ND OPTION WD IN REC ETCM-32
         STW       R7,TMO.TOW1,X2      PUT 1ST OPTION WD IN REC ETCM-32
BLD_PRCX EQU       $                                            ETCM-32
         LF        R0,TCM.SAVE                                  ETCM-32
         TRSW      R0                                           ETCM-32
*                                                               ETCM-32
TCM.SAVE REZ       8W                                           ETCM-32
TCM.BUFA DATAW     0         START ADDR OF TCM RECORD BUFFER    ETCM-32
TCM.PNTR DATAW     0         POINTER INTO TCM RECORD BUFFER     ETCM-32
IDSTAT   REZ       11W             M.MYID DATA AREA             ETCM-32
*-----------------------------------------------------------------------
         TITLE     BLD_PLFC - BUILD PROCESSOR LFC TOKEN         ETCM-32
*-----------------------------------------------------------------------
* SUBROUTINE TO BUILD A PROCESSOR REQUIRED RRS TOKEN            ETCM-32
*                                                               ETCM-32
*        BLD_PLFC                                               ETCM-32
*                                                               ETCM-32
*  IN:   R1 = ADDR OF FCB OR LFC FOR ASSIGNED RESOURCE          ETCM-32
*                                                               ETCM-32
*                                                               ETCM-32
* OUT:   TCM.PNTR IS ADJUSTED TO POINT TO NEXT FREE WORD IN     ETCM-32
*        THE TCM RECORD BUFFER                                  ETCM-32
*                                                               ETCM-32
*-----------------------------------------------------------------------
*                                                               ETCM-32
BLD_PLFC EQU       $                                            ETCM-32
         LW        R2,TCM.PNTR     GET CURRENT BUFFER POINTER   ETCM-32
         ZMB       3,X2            SHOW AS A PROCESSOR RECORD   ETCM-32
         ZBM       0,INCFLAG                    "               ETCM-32
BLD_OBJ3 EQU       $                                            ETCM-32
         LW        R4,TCM.PNA          GET PATHNAME ADDRESS     ETCM-32
         ZR        R7                                           ETCM-32
         SVC       2,X'2F'             M.PNAM                   ETCM-32
         BS        BLD_OBJX            BRANCH IF ERRORS         ETCM-32
         LI        R5,1         PREPARE TO INC RRS/INCLUDE CNT  ETCM-32
         TBM       0,INCFLAG       IS IT AN INCLUDE             ETCM-32
         BNS       BLD.0           NO INC PROCESSOR COUNT       ETCM-32
         ABM       31,TCM.INCC     INCREMENT INCLUDE COUNT      ETCM-32
         ZBM       0,INCFLAG       CLEAR FLAG                   ETCM-32
         BU        BLD.01          CONTINUE                     ETCM-32
BLD.0    ABM       15,TCM.RRSC     INCREMENT PROCESSOR COUNT    ETCM-32
BLD.01   LW        R5,0,X1         GET LFC                      ETCM-32
         ANMW      R5,=X'00FFFFFF'   MASK OUT TOP BYTE          ETCM-32
         LW        R1,TCM.PNTR     GET CURRENT BUFFER POINTER   ETCM-32
         STW       R5,1W,X1        PUT LFC IN RECORD            ETCM-32
         LI        R5,1            TYPE 1 RRS                   ETCM-32
         STB       R5,8,X1         STORE IN BUFFER              ETCM-32
         TRR       R4,R3           MOVE PATHNAME VECTOR TO R3   ETCM-32
         ZR        R2                                           ETCM-32
         SLLD      R2,8            GET PATHNAME LENGTH          ETCM-32
         STB       R2,10,X1        STORE IN BUFFER              ETCM-32
         TRR       R2,R5           COPY TO R5                   ETCM-32
         ADI       R5,5W           ADD LENGTH OF REST OF RECORD ETCM-32
         STB       R5,2,X1         PUT IN RECORD HEADER         ETCM-32
         ZMB       11,X1           CLEAR LAST BYTE IN WORD 2    ETCM-32
         SRL       R3,8            GET PATHNAME ADDRESS         ETCM-32
         ADI       R1,5W           PUT PATHNAME IN WORD 5       ETCM-32
BLD.1    CI        R2,0            DONE WITH PATHNAME?          ETCM-32
         BEQ       BLD.2           YES...BRANCH                 ETCM-32
         LB        R5,0,X3         GET PATHNAME CHARACTER       ETCM-32
         STB       R5,0,X1         PUT IN BUFFER                ETCM-32
         SUI       R2,1            ADJUST POINTERS              ETCM-32
         ADI       R3,1                                         ETCM-32
         ADI       R1,1                                         ETCM-32
         BU        BLD.1           KEEP GOING                   ETCM-32
BLD.2    LW        R1,TCM.PNTR     GET CURRENT BUFFER ADDR
         ZMW       3W,X1           CLEAR WORD 3                 ETCM-32
         ZMW       4W,X1           CLEAR WORD 4                 ETCM-32
         LB        R2,10,X1        GET PATHNAME LENGTH          ETCM-32
         ZR        R3                                           ETCM-32
         SRLD      R2,2            CONVERT TO WORD COUNT        ETCM-32
         TRR       R3,R5           SAVE REMAINDER               ETCM-32
         TRR       R2,R3                                        ETCM-32
         MPI       R2,4            CONVERT TO BYTE COUNT        ETCM-32
         TRR       R5,R5           ANY REMAINDER?               ETCM-32
         BZ        $+2W            NO...BRANCH                  ETCM-32
         ADI       R3,4            ADD ANOTHER WORD             ETCM-32
         ADI       R3,4W           ADD FIXED LENGTH             ETCM-32
         SRL       R3,2            CONVERT TO WORD COUNT        ETCM-32
         STB       R3,9,X1         SAVE IN BUFFER               ETCM-32
         SLL       R3,2            CONVERT TO BYTE COUNT        ETCM-32
         ADI       R3,1W           ADD 1W FOR OBJECT HEADER     ETCM-32
         LI        R5,X'D30C'      GET OBJECT RECORD TYPE       ETCM-32
         STH       R5,0,X1         STORE IN BUFFER              ETCM-32
         ARMW      R3,TCM.PNTR     ADJUST BUFFER POINTER        ETCM-32
BLD_OBJX EQU       $                                            ETCM-32
         TRSW      R0                                           ETCM-32
*                                                               ETCM-32
*-----------------------------------------------------------------------
         TITLE     BLD_ILFC - BUILD INCLUDE FILE ID TOKEN       ETCM-32
*-----------------------------------------------------------------------
* SUBROUTINE TO BUILD AN INCLUDE FILE RRS TOKEN                 ETCM-32
*                                                               ETCM-32
*        BLD_ILFC                                               ETCM-32
*  IN:   R1 = ADDR OF FCB OR LFC FOR ASSIGNED RESOURCE          ETCM-32
*                                                               ETCM-32
* OUT:   TCM.PNTR IS ADJUSTED TO POINT TO THE NEXT FREE WORD    ETCM-32
*        IN THE TCM RECORD BUFFER                               ETCM-32
*                                                               ETCM-32
*-----------------------------------------------------------------------
*                                                               ETCM-32
BLD_ILFC EQU       $                                            ETCM-32
         LW        R2,TCM.PNTR     GET CURRENT BUFFER ADDRESS   ETCM-32
         SBM       31,0,X2         SHOW AS AN INCLUDE RECORD    ETCM-32
         SBM       0,INCFLAG                    "               ETCM-32
         BU        BLD_OBJ3        USE COMMON CODE IN BLD_PLFC  ETCM-32
*                                                               ETCM-32
*-----------------------------------------------------------------------
         TITLE     TCM.MVST - MOVE STRING SUBROUTINE            ETCM-32
*-----------------------------------------------------------------------
* MOVE STRING                                                   ETCM-32
*                                                               ETCM-32
*   R1=ADDR OF SOURCE STRING                                    ETCM-32
*   R2=ADDR OF DESTINATION STRING                               ETCM-32
*   R7=COUNT OF CHARACTERS MOVED ACCUMULATED IN R3              ETCM-32
*      (R7 IS NOT RESET ON ENTRY)                               ETCM-32
*                                                               ETCM-32
*   MOVES FROM SOURCE TO DESTINATION UNTIL FIRST BLANK          ETCM-32
*                                                               ETCM-32
*-----------------------------------------------------------------------
TCM.MVST EQU       $                                            ETCM-32
         LB        R4,0,X1             GET SOURCE STRING BYTE   ETCM-32
         CI        R4,G' '             CHECK FOR BLANK          ETCM-32
         BEQ       TCM.MVS2            BRANCH IS BLANK          ETCM-32
         STB       R4,0,X2             PUT BYTE IN DEST. STRING ETCM-32
         ABR       R1,31               INCREMENT SOURCE INDEX   ETCM-32
         ABR       R2,31               INCREMENT DEST. INDEX    ETCM-32
         BIB       R7,TCM.MVST         INCREMENT COUNTER & LOOP ETCM-32
TCM.MVS2 TRSW      R0                  RETURN                   ETCM-32
*                                                               ETCM-32
*-----------------------------------------------------------------------
         TITLE     TASK CODE MANAGEMENT DATA AREAS              ETCM-32
*-----------------------------------------------------------------------
*                                                               ETCM-32
*        TASK CODE MANAGEMENT DATA AREAS                        ETCM-32
*                                                               ETCM-32
*-----------------------------------------------------------------------
*                                                               ETCM-32
         BOUND     1W                                           ETCM-32
TCM.RIDV GEN       8/32,24/A(TCM.RID)                           ETCM-32
TCM.PNA  GEN       8/54,24/A(PATHBUF)                           ETCM-32
         BOUND     1D                                           ETCM-32
TCM.RID  REZ       8W                                           ETCM-32
*                                                               ETCM-32
*======================================================================
*                                                               ETCM-32
*                         NOTICE!!!                             ETCM-32
*                                                               ETCM-32
*        THE ORDER OF THE REMAINING DATA IS CRITICAL!           ETCM-32
*        DO NOT ADD, REMOVE OR CHANGE ANY DATA IN THIS AREA!    ETCM-32
*                                                               ETCM-32
*======================================================================
*                                                               ETCM-32
         BOUND     1D                                           ETCM-32
TCM.RT2  DATAW     X'D20C0000'         OBJECT TYPE 2 RECORD     ETCM-32
         DATAW     0,0,0                                        ETCM-32
TCM.RRSC DATAH     0                                            ETCM-32
TCM.INCC DATAH     0                                            ETCM-32
TCM.T2PN DATAB     G'@',0                                       ETCM-32
         RES       1W                                           ETCM-32
         BOUND     1D                                           ETCM-32
TCM.XRD  RES       1024            TCM RECORD BUFFER            ETCM-32
PATHBUF  REZ       54B                                          ETCM-32
INCFLAG  REZ       1B                                           ETCM-32
*                                                               ETCM-32
         BOUND     1W                                           ETCM-32
         TITLE     XANOZ - ANNOUNCE NAME AND COPYRIGHT ON UT
*-------------------------------------------------------------------1.3
*                                                                   1.3
*  XANOZ    EXPLICITLY OPENS LFC UT IN "UPDATE" OR "APPEND"         1.3
*           MODE AS APPROPRIATE FOR TERMINAL OR SLO AND             1.3
*           WRITES PRODUCT ID AND COPYRIGHT MESSAGE.                1.3
*                                                                   1.3
*           ANY ERRORS ON OPEN CAUSE AN ABORT WITH THE              1.3
*           POSTED RM STATUS AND LFC IN THE ABORT MESSAGE           1.3
*           THE LFC IS ALWAYS LISTED AS "SLO"                       1.3
*                                                                   1.3
*    IN     R5 = TCW FOR PRODUCT ID MESSAGE.                        1.3
*                                                                   1.3
*   OUT     ALL REGS RETURNED INTACT.                               1.3
*                                                                   1.3
*-------------------------------------------------------------------1.3
*                                                                   1.3
XANOZ    CEQU      $                                            ESCT-32
         STF       R0,XANOZ.99                                      1.3
         M.INQUIRY XANOZ.97,XANOZ.98    GET POINTERS                1.3
         BS        XANOZ.11             REPORT ERROR IF ONE         1.3
         LW        R1,XANOZ.97+1W  GET FAT ADDR                     1.3
         LI        R7,4            DEFAULT IS UPDATE MODE           1.3
         TBM       5,DFT.STB,X1    IS IT A VOLUME RESOURCE          1.3
         BNS       XANOZ.1         SKIP IF NOT VOLUME               1.3
         LI        R4,X'F'         SYS CODE MASK                    1.3
         LMB       R3,DFT.ACF,X1   GET POSSIBLE SYS FILE CODE       1.3
         CI        R3,3            IS IT SLO                        1.3
         BNE       XANOZ.1         SKIP IF NOT SLO                  1.3
         LI        R7,5            ELSE SET MODE TO APPEND          1.3
XANOZ.1  CEQU      $                                            ESCT-32
         ZMD       XANOZ.96                                         1.3
         SBM       31,XANOZ.96     MAKE CNP IMMEDIATE RETRUN        1.3
         STB       R7,XANOZ.96+8B  SET INTO 1ST OPTION BYTE         1.3
         ZMD       XANOZ.98+1D                                      1.3
         ZMD       XANOZ.98+2D                                      1.3
         ZMD       XANOZ.98+3D                                      1.3
         M.OPENR   XANOZ.98,XANOZ.96   OPEN UT IN REQUIRED MODE     1.3
         BS        XANOZ.10        REPORT ERROR                     1.3
         LW        R5,XANOZ.99+5W  RECOVER MSG PARAMETERS           1.3
         ZR        R4
         SLLD      R4,12           EXTRACT COUNT                 |1.3Q32
         SLL       R5,1            SCRAP F- BIT                  |1.3Q32
         SRL       R5,13           AND REPOSITION                |1.3Q32
         STW       R4,XANOZ.98+FCB.EQTY     SET COUNT INTO FCB   |1.3Q32
         STW       R5,XANOZ.98+FCB.ERWA     SET ADDR INTO FCB    |1.3Q32
         ZMD       XANOZ.98+5D              ZERO WRDS USED IN CNP|1.3Q32
         SBM       6,XANOZ.98+FCB.GCFG       INDICATE 16W FCB    |1.3Q32
*!!!!!!!!!!STW!!!!!!!R5,XANOZ.98+1W!!PUT!IN!FCB!FOR!'UT!'!!!!!!!!|1.3Q32
         M.WRIT    XANOZ.98        WRITE TO UT                      1.3
*!!!!!!!!!!LW!!!!!!!!R7,XANOZ.95!!!!!GET!COPYRIGHT!TCW!!!!!!!!!!!|1.3Q32
*!!!!!!!!!!STW!!!!!!!R7,XANOZ.98+1W!!PUT!IN!FCB!FOR!'UT!'!!!!!!!!|1.3Q32
         LB        R7,XANOZ.93     GET LENGTH                    |1.3Q32
         STW       R7,XANOZ.98+FCB.EQTY                          |1.3Q32
         LA        R7,XANOZ.94     GET ADDR                      |1.3Q32
         STW       R7,XANOZ.98+FCB.ERWA                          |1.3Q32
         M.WRIT    XANOZ.98        WRITE TO UT                      1.3
         LF        R0,XANOZ.99                                      1.3
         TRSW      R0              RETURN TO CALLER                 1.3
*                                                                   1.3
         BOUND     1W                                               1.3
XANOZ.10 CEQU      $                                            ESCT-32
         LH        R7,XANOZ.96+3H  GET STATUS                       1.3
XANOZ.11 CEQU      $                                            ESCT-32
         TRR       R7,R5           MOVE STATUS                      1.3
         M.CONBAD                  CONVERT TO DECIMAL               1.3
         ANMW      R7,=X'0000FFFF'   KEEP TWO DIGITS                1.3
         ORMW      R7,=G'RM"@"@'     OR IN "RM"                     1.3
         LW        R2,=G' OPN'       SET EXTENDED MESSAGE           1.3
         LW        R3,=G' SLO'                                      1.3
         TRR       R7,R5             SET ABORT CODE                 1.3
         ZR        R6                                               1.3
         ZR        R7              SET THIS TASK                    1.3
         SVC       1,X'62'         AND ABORT                        1.3
*
*                                                                   1.3
         BOUND     1F                                               1.3
XANOZ.99 RES       1F              REG STORAGE                      1.3
XANOZ.98 DATAW     G'UT '          LFC TO M.INQUIRY,THEN FCB        1.3
         DATAW     0               FOR M.INQUIRY THEN FCB           1.3
XANOZ.97 DATAW     0               POINTERS FROM M.INQUIRY          1.3
         DATAW     0                                                1.3
         DATAW     0                                                1.3
         DATAW     0                                                1.3
         DATAW     0                                                1.3
         DATAW     0                                                1.3
XANOZ.96 DATAW     0             POINTER THEN CNP                   1.3
         DATAW     0                                                1.3
         DATAW     0                                                1.3
         DATAW     0                                                1.3
         DATAW     0                                                1.3
         DATAW     0                                                1.3
         DATAW     0                                             |1.3Q32
         DATAW     0                                             |1.3Q32
XANOZ.94 DATAB C' (C) COPYRIGHT 1983 ENCORE COMPUTER'               1.3
         DATAB C' CORPORATION, ALL RIGHTS RESERVED'                 1.3
XANOZ.93 DATAB     $-XANOZ.94                                       1.3
         BOUND     1W                                               1.3
*                                                                   1.3
*---------------------------------------------------------------    1.3
SKIP     ANOP                                                   *JCB*
         TITLE     A0 - START EXECUTION
A0       CEQU      $        START MACRO ASSEMBLER EXECUTION     ESCT-32
         IFT       UNIXF,SKIP                                   *JCB*
*****************************************************************JCB*
*                                                               *JCB*
* GASM -LFILE -G -X -A -D -E -1 -OFILE -TFILE -MFILE INPT INPTN *JCB*
*                                                               *JCB*
*       IF FILE NOT SPECIFIED, STDIN IS USED                    *JCB*
*       -L  MAKE LISTING ON STDOUT OR FILE                      *JCB*
*       -G  DO DEBUG SYMBOLS                                    *JCB*
*       -X  DO CROSS REFERENCE                                  *JCB*
*       -D  CHANGE CSECT TO DSECT                               *JCB*
*       -E  DO IEEE FLOATING POINT                              *JCB*
*       -A  DO AUTO-SECTIONING                                  *JCB*
*       -O  OBJECT REQUESTED ON SBO OR FILE                     *JCB*
*       -T  TEMP FILE (UT1) DEFINITION                          *JCB*
*       -M  MACRO FILE DEFINITION (M.MPXMAC)                    *JCB*
*       -1  DO NOT OUTPUT DATE/TIME/PROGRAM INFORMATION 1X      *JCB*
*                                                               *JCB*
*****************************************************************JCB*
_main    CEQU      $                                            *JCB*
         TRR       .SP,R1.                                      *JCB*
         ADI       .SP,OFF1.                                    *JCB*
         STD       R0.,2W,.SP                                   *JCB*
         STF       R4.,4W,.SP                                   *JCB*
         STW       .SP,STACKPTR    SAVE UNIX STACK POINTER      *JCB*
         LA        .AP,8W,R1.      ADJUST ARGUMENT POINTER      *JCB*
         LW        R7,0,.AP        GET # OF PASSED ARGUMENTS    *JCB*
         LW        R1,1W,.AP       GET VECTOR TO ARGUMENT LIST  *JCB*
         ZR        R3              DEFAULT TO SI FILE PTR       *JCB*
* SET DEFAULT OPTIONS NO LO, NO BO, NO XREF                     *JCB*
         SBM       LO,OPTION       NO LISTING                   *JCB*
         SBM       DT.OPT,OPTION   HAVE DATE AND TIME           *JCB*
         SBM       ID.OPT,OPTION   SAVE PROGRAM INFO            *JCB*
         SBM       XREF,OPTION     NO XREF YET                  *JCB*
         SBM       BO,OPTION       NO BO YET                    *JCB*
         ZBM       ASCT.OPT,OPTION NO AUTO-SECTIONING YET       *JCB*
         ZMB       HHBITS3         CLEAR THESE FLAGS AT START   *JCB*
A0.NEXT  CEQU      $                                            *JCB*
         SUI       R7,1            --ARGC>0                     *JCB*
         STW       R7,ARGC                                      *JCB*
         BLE       A0.01           IF NONE, USE STANDARD INPUT  *JCB*
         ADI       R1,1W           ARGV++                       *JCB*
         STW       R1,ARGV         UPDATE POINTER               *JCB*
         LW        R2,0,R1         GET POINTER FOR NEXT FILE    *JCB*
         LB        R0,0,R2         CHECK FIRST BYTE             *JCB*
         CI        R0,G'-'         IS IT AN OPTION              *JCB*
         BNE       A0.0            NO, ASSUME A FILE NAME       *JCB*
         LB        R0,1B,R2        CHECK OPTION TYPE            *JCB*
         CI        R0,G'l'         IS IT THE LISTING OPTION     *JCB*
         BEQ       $+3W            DO LISTING                   *JCB*
         CI        R0,G'L'         IS IT THE LISTING OPTION     *JCB*
         BNE       A0.O            NO, CHECK FOR OBJECT SPEC    *JCB*
         ZBM       LO,OPTION       DO LISTING                   *JCB*
         LI        R0,1            STD OUT FILE DESCR           *JCB*
         STW       R0,LO.FD        DEFAULT TO STD OUT           *JCB*
         LB        R0,2B,X2        IS NEW FILE SPECIFIED        *JCB*
         BZ        A0.NEXT         NO, USED DEFAULT             *JCB*
         ADI       R2,2            POINT AT FILENAME            *JCB*
         ZMW       LO.FD           SHOW STD OUT NOT DEFAULT     *JCB*
         LA        R3,LOFILPTR     POINT TO LO FILE PTR         *JCB*
         STW       R2,0W,X3        SAVE POINTER TO NEW FILENAME *JCB*
         ZR        R3              NO FILENAME EXPECTED         *JCB*
         BU        A0.NEXT         GET NEXT FIELD               *JCB*
A0.O     CEQU      $                                            *JCB*
         CI        R0,G'o'         IS IT AN OBJECT SPEC         *JCB*
         BEQ       $+3W            OBJECT REQUESTED             *JCB*
         CI        R0,G'O'         IS IT AN OBJECT SPEC         *JCB*
         BNE       A0.T            NO, TRY TEMP FILE OPTION     *JCB*
         ZBM       BO,OPTION       OUTPUT OBJECT                *JCB*
         LB        R0,2B,X2        IS NEW FILE SPECIFIED        *JCB*
         BZ        A0.NEXT         NO, USED DEFAULT             *JCB*
         ADI       R2,2            POINT AT FILENAME            *JCB*
         LA        R3,BOFILPTR     ELSE, POINT TO BO FILE PTR   *JCB*
         STW       R2,0W,X3        SAVE POINTER TO NEW FILENAME *JCB*
         ZR        R3              NO FILENAME EXPECTED         *JCB*
         BU        A0.NEXT                                      *JCB*
A0.T     CEQU      $                                            *JCB*
         CI        R0,G't'         IS IT TEMP FILE SPEC         *JCB*
         BEQ       $+3W            TEMP FILE SPECIFIED          *JCB*
         CI        R0,G'T'         IS IT TEMP FILE SPEC         *JCB*
         BNE       A0.M            NO, TRY MACRO OPTION         *JCB*
         LB        R0,2B,X2        IS NEW FILE SPECIFIED        *JCB*
         BZ        A0.NEXT         NO, USED DEFAULT             *JCB*
         ADI       R2,2            POINT AT FILENAME            *JCB*
         LA        R3,SKFILPTR     ELSE, POINT TO SK FILE PTR   *JCB*
         STW       R2,0W,X3        SAVE POINTER TO NEW FILENAME *JCB*
         ZR        R3              NO FILENAME EXPECTED         *JCB*
         BU        A0.NEXT                                      *JCB*
A0.M     CEQU      $                                            *JCB*
         CI        R0,G'm'         IS MACRO FILE SPECIFIED      *JCB*
         BEQ       $+3W            MACRO FILE SPECIFIED         *JCB*
         CI        R0,G'M'         IS MACRO FILE SPEC           *JCB*
         BNE       A0.D            NO, TRY DSECT ONLY OPTION    *JCB*
         LB        R0,2B,X2        IS NEW FILE SPECIFIED        *JCB*
         BZ        A0.NEXT         NO, USED DEFAULT             *JCB*
         ADI       R2,2            POINT AT FILENAME            *JCB*
         LA        R3,MCFILPTR     ELSE, POINT TO MAC FILE PTR  *JCB*
         STW       R2,0W,X3        SAVE POINTER TO NEW FILENAME *JCB*
         ZR        R3              NO FILENAME EXPECTED         *JCB*
         BU        A0.NEXT                                      *JCB*
A0.D     CEQU      $                                            *JCB*
         ZR        R3              CLEAR FILE PTR TARGET        *JCB*
         CI        R0,G'd'         IS THIS DSECT ONLY REQUEST   *JCB*
         BEQ       $+3W            CHANGE CSECT TO DSECT        *JCB*
         CI        R0,G'D'         IS THIS DSECT ONLY REQUEST   *JCB*
         BNE       A0.A            NO, TRY AUTO-SECT OPTION     *JCB*
         ZBM       8,SECT.FLG      DISABLE SECTIONED CODE PROC  *JCB*
         ZBM       8,SECT.FLH      DISABLE SECTIONED CODE PROC  *JCB*
         BU        A0.NEXT         GET NEXT FIELD               *JCB*
A0.A     CEQU      $                                            *JCB*
         CI        R0,G'a'         IS IT AUTO-SECT OPTION       *JCB*
         BEQ       $+3W            SET AUTO-SECT                *JCB*
         CI        R0,G'A'         IS IT AUTO-SECT OPTION       *JCB*
         BNE       A0.E            NO, TRY IEEE OPTION          *JCB*
         SBM       ASCT.OPT,OPTION SET AUTO-SECTIONING          *JCB*
         SBM       ASCT.OPT,OPTSAV    HERE ALSO                 *JCB*
         SBM       EXPLFC,HHBITS3  AND IMPLY A "CSECT"          *JCB*
         BU        A0.NEXT         GET NEXT FIELD               *JCB*
A0.E     CEQU      $                                            *JCB*
         CI        R0,G'e'         IS IT IEEE OPTION            *JCB*
         BEQ       $+3W            SET IEEE OPTION              *JCB*
         CI        R0,G'E'         IS IT IEEE OPTION            *JCB*
         BNE       A0.G            NO, TRY DEBUG SYM OPTION     *JCB*
         SBM       9,OPTION2       SET IEEE OPTION              *JCB*
         SBM       2,FPFLAG        HERE ALSO                    *JCB*
         SBM       14,OPTION       OPTION 18 ALSO               *JCB*
         SBM       EXPLFC,HHBITS3  AND IMPLY A "CSECT"          *JCB*
         BU        A0.NEXT         GET NEXT FIELD               *JCB*
A0.G     CEQU      $                                            *JCB*
         CI        R0,G'g'         IS IT DEBUGGER SYMBOLS OPTION*JCB*
         BEQ       $+3W            EMIT SYMBOLS                 *JCB*
         CI        R0,G'G'         IS IT DEBUGGER SYMBOLS OPTION*JCB*
         BNE       A0.O1           NO, try 1X code option       *JCB*
         SBM       DBG,OPTION      SET SYMBOLS REQUIRED         *JCB*
         BU        A0.NEXT         GET NEXT FIELD               *JCB*
A0.O1    CEQU      $                                            *JCB*
         CI        R0,G'1'         IS IT 1X option              *JCB*
         BNE       A0.X            NO, TRY CROSS REF            *JCB*
         ZBM       DT.OPT,OPTION   NO DATE AND TIME             *JCB*
         ZBM       ID.OPT,OPTION   NO PROGRAM INFO              *JCB*
         BU        A0.NEXT         GET NEXT FIELD               *JCB*
A0.X     CEQU      $                                            *JCB*
         CI        R0,G'x'         IS IT CROSS REF OPTION       *JCB*
         BEQ       $+3W            EMIT SYMBOLS                 *JCB*
         CI        R0,G'X'         IS IT CROSS REF OPTION       *JCB*
         BNE       A0.NEXT         NO, SKIP IT (UNDEFINED?)     *JCB*
         ZBM       XREF,OPTION     SET XREF REQUIRED            *JCB*
         BU        A0.NEXT         GET NEXT FIELD               *JCB*
A0.0     TRR       R3,R3           IS THERE AN OPT FILE PENDING *JCB*
         BZ        A0.SI           NO, ASSUME THIS IS SI FILE   *JCB*
         STW       R2,0,R3         UPDATE THE FILE POINTER      *JCB*
         ZR        R3              RESET BACK TO SI FILE PTR    *JCB*
         BU        A0.NEXT         GO GET NEXT OPTION           *JCB*
A0.SI    CEQU      $                                            *JCB*
         STW       R2,FILEPTR      SAVE FILENAME POINTER        *JCB*
         CCALL     _open,FILEPTR,=0   OPEN THE INPUT FILE       *JCB*
         TRR       R0,R0           ANY ERROR                    *JCB*
         BLT       A0.01           YES, TRY STANDARD INPUT      *JCB*
         STW       R0,SI.FD        SAVE SI FILE DESCRIPTOR      *JCB*
*                                                               *JCB*
A0.01    CEQU      $                                            *JCB*
         ZBM       ERROCCUR,FLAGS  INDICATE NO ERRORS YET       *JCB*
         SBM       0,HWCALM        DELETE HALF WORD CALM ENTRY  *JCB*
         ZBM       MA2PRES,HHBITS4 INDICATE MA2 NOT ASSIGNED    *JCB*
         ZMW       PREFLG          CLEAR PRE FLAG WORD          *JCB*
         LW        R7,OPTION       GET OPTIONS FOR PASS2        *JCB*
         STW       R7,OPTSAV       SAVE OPTION WORD FOR PASS 2  *JCB*
*                                                               *JCB*
         CCALL     _malloc,=8192W  GET A 8KW BUFFER TO ALLOW    *JCB*
*                                  MALLOC TO HAVE SPACE BEFORE  *JCB*
*                                  THE ASSEMBLER.               *JCB*
         CCALL     _free,R0.       NOW GIVE IT BACK             *JCB*
         SPACE     2                                            *JCB*
SKIP     ANOP                                                   *JCB*
*!!!!!!!!!!M.MYID!!!!PARAMBLK!!!!!!!!FIND!OUT!IF!'TSM.'!!!!!!!!!!1.3#06
*!!!!!!!!!!LW!!!!!!!!R1,PARAMBLK+5W!!GET!FIRST!HALF!OF!PSEUDONYM!1.3#06
*!!!!!!!!!!CAMW!!!!!!R1,=C'TSM.'!!!!!IS!IS!TSM!??!!!!!!!!!!!!!!!!1.3#06
*!!!!!!!!!!BNE!!!!!!!A0.001!!!!!!!!!!NO!-!DON'T!'GREET'!!!!!!!!!!1.3#06
*!!!!!!!!!!LW!!!!!!!!R7,PRODRTCW!!!!!GET!PRODUCT!REV!TCW!!!!!!!!!1.3#06
*!!!!!!!!!!STW!!!!!!!R7,UTFCB+1W!!!!!PUT!IN!FCB!FOR!'UT!'!!!!!!!!1.3#06
*!!!!!!!!!!M.WRIT!!!!UTFCB!!!!!!!!!!!WRITE!TO!UT!!!!!!!!!!!!!!!!!1.3#06
*!!!!!!!!!!LW!!!!!!!!R7,CPYR.TCW!!!!!GET!COPYRIGHT!TCW!!!!!!!!!!!1.3#06
*!!!!!!!!!!STW!!!!!!!R7,UTFCB+1W!!!!!PUT!IN!FCB!FOR!'UT!'!!!!!!!!1.3#06
*!!!!!!!!!!M.WRIT!!!!UTFCB!!!!!!!!!!!WRITE!TO!UT!!!!!!!!!!!!!!!!!1.3#06
*!A0.001!!!EQU!!!!!!!$!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1.3#06!
*
         IFF       UNIXF,SKIP                                   *JCB*
         BL        LFCSUB          SUBSTITUTE ASSIGNED LFC'S    ELFC-31
         SEA                       SET EXTENDED MODE FOR GOOD   S880752
         ZMW       FCBSK+FCB.BBA   INDICATE NO BUFFER ON UT1    S880752
SKIP     ANOP                                                   *JCB*
         SBM       2,PGATE         FIRST TIME THRU EVER?        S880752
         BS        A0.GOON         BR IF NOT                    S880752
         SVC       1,X'69'         M.GD - GET EXT DATA SPACE    S880752
         TRR       R3,R3           SET CC'S                     S880752
         BZ        MNOK            BR IF NO SPACE               S880752
         STW       R3,LOW          SAVE START ADDR.             S880752
         STW       R4,HIGH         SAVE LAST ADDR.              S880752
         STW       R3,CURRP        INIT STACK POINTER           S880752
         ZMW       MACP            INIT MAC POINTER             S880752
         ZMW       MA2P            INIT MA2 POINTER             S880752
A0.GOON  CEQU      $                                            ESCT-32
         IFF       UNIXF,SKIP                                   *JCB*
*
*        DETERMINE IF THERE IS A PREFIX SOURCE FILE, PRE,
*        PRESENT...INITIALIZE FILE CONTROL APPROPRIATELY
*
         ZMW       PREFLG          CLEAR PRE FLAG WORD
*        LW        R4,=G'PRE'      LOGICAL FILE CODE            ELFC-31
         LW        R4,FCBPRE       LOGICAL FILE CODE            ELFC-31
         LA        R1,INQ.INFO     SET UP INQUIRY INFO AREA      11003
         ZR        R5              CLEAR R5                      11003
         ZR        R7              NO CNP                        11003
         SVC       2,X'48'         M.INQUIRY                     11003
         CI        R7,29           IS IT ASSIGNED ??             11003
         BEQ       A0.0            NO, BRANCH                    11003
         LA        R1,FCBPRE       ADDR OF PRE FCB
         STW       R1,FCBA         READ SOURCE FROM PRE FIRST
         LA        R7,READ7        ADDR OF PRE EOF PROCESSOR
         STW       R7,EOFA         SET AS SOURCE EOF PROCESSOR
         LA        R7,READPIP      ADDR OF PRE RECORD PTR
         STW       R7,READPTR      SET AS SOURCE RECORD PTR
         LA        R7,IBUF2        ADDR OF PRE INPUT BUFFER
         STW       R7,IBUFA        SET AS SOURCE INPUT BUFFER
         LW        R7,READPRPC     INITIALIZE PRE FOR DE-COMPR
         STW       R7,READPIP
         SBM       0,PREFLG        SET PRE FILE PRESENT
         BU        A0.01
A0.0     LA        R1,FCBSI        ADDR OF SI FCB
         STW       R1,FCBA         READ SOURCE FROM SI
*!!!!!!!!LEA!!!!!!!R7,READ8!!!!!!!!ADDR!OF!SI!EOF!PROCESSOR!!AS1S880752
         LA        R7,READ8        ADDR OF SI EOF PROC. (AS12)  S880752
         STW       R7,EOFA         SET AS SOURCE EOF PROCESSOR
         LA        R7,READSIP      ADDR OF SI RECORD PTR
         STW       R7,READPTR      SET AS SOURCE RECORD PTR
         LA        R7,IBUF         ADDR OF SI INPUT BUFFER
         STW       R7,IBUFA        SET AS SOURCE INPUT BUFFER
         SPACE     2
*!A0.01!!SVC!!!!!!!1,X'4C'!!!!!!!!!GET!USER'S!OPTION!WORD.!!!!!!EIEE-33
A0.01    M.PGOD                    GET PROGRAM OPTION WORDS     EIEE-33
*                                                                1.3#05
*  FOLLOWING TURNS OFF OPTION 16 UNCONDITIONALLY TO REMOVE       1.3#05
*  ANY POSSIBILTY OF IT BEING SET INADVERTENTLY.                 1.3#05
*                                                                1.3#05
         ZBR       R7,16           OPTION 16 IS BIT 16           1.3#05
*                                                                1.3#05
         ZBM       ERROCCUR,FLAGS  INDICATE NO ERRORS DETECTED YET
         LA        R1,FCBSI        RELOAD ADDR FOR SI FOR BLK TST  11004
         SBM       5,2W,R1         DEFAULT SI BLOCKED
         ZBR       R7,24           CHECK FOR UNBLOCKED INPUT (OPTION 8)
         BCF       SET,A0.02        NO - SKIP IT
         ZBM       5,2W,R1         RESET BLOCKING BIT IN FCBSI
A0.02    ZBR       R7,23           CHECK FOR UNBLOCKED OUTPUT (OPTION 9)
         BCF       SET,A0.1        NO - SKIP IT
         LA        R1,FCBLO        YES - RESET BLOCKING
         ZBM       5,2W,R1         BIT IN FCBLO
         LA        R1,FCBBO        AND IN FCBBO
         ZBM       5,2W,R1
         LA        R1,FCBCS        AND IN FCBCS
         ZBM       5,2W,R1
A0.1     TBR       R7,12           ! CHECK FOR FULL WORD CALM OPTION 20
         BS        A0.2            ! BRANCH IF FULL WORD CALM SELECTED
         SBM       0,FWCALM        ! DELETE FULL WORD CALM ENTRY
         BU        A0.3            ! CONTINUE
A0.2     SBM       0,HWCALM        ! DELETE HALF WORD CALM ENTRY
A0.3     STW       R7,OPTION       SAVE OPTION WORD.
         STW       R6,OPTION2      SAVE OPTION WORD 2           EIEE-33
         STW       R7,OPTSAV       SAVE OPTION WORD FOR PASS 2 EBRM-33
         TBR       R6,9            IS OPTION 55 SET?            EIEE-33
         BNS       A0.3C           NO...BRANCH                  EIEE-33
         SBM       2,FPFLAG        SET $OPTION 55 FLAG          EIEE-33
         SPACE     2
*===============================================================EASC-32
*                                                               EASC-32
*   TEST FOR OPTION 18 AND SET AND INIT AUTO SECTIONING         EASC-32
*                                                               EASC-32
A0.3C    ZMB       HHBITS3         CLEAR THESE FLAGS AT START   EASC-32
         ZBR       R7,14           IS OPTION 18 SET             EASC-32
         BNS       ASCT.0          SKIP IF NOT SET              EASC-32
         SBM       ASCT.OPT,OPTION    ELSE SET FLAG BIT         EASC-32
         SBM       ASCT.OPT,OPTSAV    HERE ALSO                 EASC-32
         SBM       EXPLFC,HHBITS3  AND IMPLY A "CSECT"          EASC-32
SKIP     ANOP                                                   *JCB*
         BU        ASCT.0          AND CONTINUE                 EASC-32
*                                                               EASC-32
*     AUTO SECTIONING SUPPORT ROUTINES                          EASC-32
*     ================================                          EASC-32
*                                                               EASC-32
* PROCESS DATAONLY AND ENDDATA OPERATIONS                       EASC-32
*-----------------------------------------                      EASC-32
*                                                               EASC-32
DTONLY   CEQU      $                                            ESCT-32
         SBM       ASCT.DTO,ASCT.FLG      SET "DATAONLY'        EASC-32
         BU        NEXT      GO GET NEXT DIRECTIVE              EASC-32
*--------                                                       EASC-32
ENDDT    CEQU      $                                            ESCT-32
         ZBM       ASCT.DTO,ASCT.FLG   RESET "DATAONLY"         EASC-32
         BU        NEXT      GO GET NEXT DIRECTIVE              EASC-32
*                                                               EASC-32
*===============================================================EASC-32
*                                                               EASC-32
* DETERMINE WHICH SECTION TO ESTABLISH FOR CURRENT OPCODE.      EASC-32
*----------------------------------------------------------     EASC-32
*                                                               EASC-32
*  ASCT.TST  EXAMINES OPTABLE ENTRY FOR CURRENT OPERATION       EASC-32
*            AND SELECTS EITHER DSECT OR CSECT AS NEEDED.       EASC-32
*                                                               EASC-32
*            THE OPERATIONS "BOUND", "EQU" AND "ORG" ARE        EASC-32
*            NOT PROCESSED TO ESTABLISH A SECTION.              EASC-32
*                                                               EASC-32
*           BOUND DIRECTIVES ARE DEFERRED UNTIL THE NEXT        EASC-32
*           INSTRUCTION LINE. THE BOUND IS THEN APPLIED TO      EASC-32
*           THE SECTION ESTABLISHED BY THAT LINE.               EASC-32
*                                                               EASC-32
*           EQU AND ORG DIRECTIVES MAKE THE '$' SYMBOL          EASC-32
*           ILLEGAL IN THE SUBSEQUENT EXPRESSION EVALUATION     EASC-32
*                                                               EASC-32
*   ENTRY   R1 = ADDR OF OPSTABLE ENTRY FOR THIS CODE           EASC-32
*                                                               EASC-32
*   EXIT  IMPLICITLY, DSECT OR CSECT MODE AS REQUIRED.          EASC-32
*         ALL REGS RETURNED.                                    EASC-32
*                                                               EASC-32
*---------------------------------------------------------------EASC-32
ASCT.TST CEQU      $                                            ESCT-32
         TBM       ASCT.OPT,OPTION  ARE WE IN "AUTO" MODE       EASC-32
         BS        ASCT.TS0         ENTER IF WE ARE             EASC-32
         TRSW      R0          ELSE RETURN                      EASC-32
         NOP                                                    EASC-32
*--------------------------------                               EASC-32
ASCT.TS0 CEQU      $                                            ESCT-32
         STF       R0,ASCT.RSV     SAVE CALLER                  EASC-32
*                                                               EASC-32
* DO NOTHING IF "BOUND", "EQU" OR "ORG".                        EASC-32
*--------------------------------------------------------       EASC-32
         LB        R6,23B,X1       GET OP-CODE VECTOR FROM TAB  EASC-32
         CAMB      R6,ASCT.NCH     IS IT "BOUND"                EASC-32
         BEQ       ASCT.TS6        DON'T DO ANYTHING            EASC-32
         CAMB      R6,ASCT.NCH+1B  IS IT "EQU"                  EASC-32
         BEQ       ASCT.TS6        DON'T DO ANYTHING            EASC-32
         CAMB      R6,ASCT.NCH+2B  IS IT "ORG'                  EASC-32
         BEQ       ASCT.TS6        DON'T DO ANYTHING            EASC-32
*                                                               EASC-32
* ELSE CHECK FOR DATA GENERATING OPCODE AND SET DSECT.          EASC-32
*-----------------------------------------------------          EASC-32
         TBM       ASCT.DTO,ASCT.FLG   "DATAONLY" SET?          EASC-32
         BS        ASCT.TS4           ESTABLISH DSECT IF YES    EASC-32
         LI        R2,-ASCT.TTL                                 EASC-32
ASCT.TS3 CEQU      $                                            ESCT-32
         CAMB      R6,ASCT.TYP+ASCT.TTL,X2                      EASC-32
         BEQ       ASCT.TS4        PROCESS IF MATCH             EASC-32
         BIB       R2,ASCT.TS3     LOOP THROUGH ALL             EASC-32
*                                                               EASC-32
* ITS NOT A DATA GENERATOR, SO ESTABLISH CSECT.                 EASC-32
*----------------------------------------------                 EASC-32
         LB        R1,HBLABS     GET CURRENT MODE               EASC-32
         CI        R1,3W         IS IT CSECT                    EASC-32
         BEQ       ASCT.TS5        RETURN IF IT IS              EASC-32
*                                                               EASC-32
         LW        R2,HWLSTS       GET CURRENT PC               EASC-32
         STW       R2,HWLSTR,X1    AND SAVE                     EASC-32
         LI        R1,3W           ESTABLISH CSECT              EASC-32
         STB       R1,HBLABS       AS CURRENT                   EASC-32
         LW        R2,HWLSTR,X1                                 EASC-32
         STW       R2,HWLSTS       WITH ITS PC VALUE            EASC-32
         BU        ASCT.TS5        AND RETURN                   EASC-32
*                                                               EASC-32
* ESTABLISH DSECT FOR DATA GENERATING OPCODES.                  EASC-32
*---------------------------------------------                  EASC-32
ASCT.TS4 CEQU      $                                            ESCT-32
         LB        R1,HBLABS       GET CURRENT MODE             EASC-32
         CI        R1,1W           IS IT DSECT                  EASC-32
         BEQ       ASCT.TS5        CONTINUE IF IT IS            EASC-32
         CI        R1,2W           IS IT IN COMMON?             EASC-32
         BEQ       ASCT.TS5        LEAVE IT THERE.              EASC-32
         LW        R2,HWLSTS       GET CURRENT PC               EASC-32
         STW       R2,HWLSTR,X1    AND SAVE                     EASC-32
         LI        R1,1W           ESTABLISH DSECT              EASC-32
         STB       R1,HBLABS       AS CURRENT                   EASC-32
         LW        R2,HWLSTR,X1                                 EASC-32
         STW       R2,HWLSTS       WITH ITS PC VALUE            EASC-32
ASCT.TS5 CEQU      $               RETURN                       ESCT-32
         ZBM       ASCT.BND,ASCT.FLG      ANY BOUND?            EASC-32
         BNS       ASCT.TS6               OUT IF NONE           EASC-32
         LW        R7,ASCT.BVL        ELSE GET VALUE            EASC-32
         BL        BOUC               AND BOUND SELECTED LC     EASC-32
         LD        R6,HWLABL         SAVE ANY CURRENT LABEL     EASC-32
         STD       R6,ASCT.SLB                                  EASC-32
         LW        R6,ASCT.BLC     GET HWLICT FROM BOUND        EASC-32
         LW        R7,HWLICT       SAVE CURRENT LINE COUNT      EASC-32
         STW       R6,HWLICT       SET OLD LINE COUNT           EASC-32
         STW       R7,ASCT.SLC     SAVE CURRENT                 EASC-32
         LD        R6,ASCT.BLB       GET ANY LABEL FROM BOUND   EASC-32
         STD       R6,HWLABL         INOT FIELD                 EASC-32
         BL        TALL              AND GO ALLOCATE            EASC-32
         LD        R6,ASCT.SLB     RECOVER CURRENT LABEL        EASC-32
         STD       R6,HWLABL         RESTORE THIS LABEL         EASC-32
         LW        R6,ASCT.SLC       RECOVER CURRENT LINE CNT   EASC-32
         STW       R6,HWLICT         AND RESTORE                EASC-32
ASCT.TS6 CEQU      $                 AND GET OUT                ESCT-32
         LF        R0,ASCT.RSV                                  EASC-32
         TRSW      R0                                           EASC-32
         NOP                                                    EASC-32
*---------------------------------------------------------------EASC-32
         BOUND     1D                                           EASC-32
ASCT.RSV REZ       8W                                           EASC-32
*                                                               EASC-32
ASCT.FLG DATAW     0               CONTROL FLAGS AS FOLLOWS:    EASC-32
ASCT.BND EQU       0               SET INDICATES DEFERRED BND   EASC-32
ASCT.NOD EQU       1               SET BY EQU & ORG PROCESSORS  EASC-32
*                          TO INDICATE $ SYMBOL IS ILLEGAL.     EASC-32
ASCT.DTO EQU       2       SET DURING "DATAONLY" SEQUENCE       EASC-32
ASCT.FND EQU       3       SET BY VAL WHEN $ SYMBOL IS FOUND    EASC-32
*
ASCT.BVL DATAW     0               HOLDS VALUE FROM BOUND PROC  EASC-32
ASCT.BLB DATAD     0               HOLDS LABEL FROM BOUND PROC  EASC-32
ASCT.BLC DATAW     0               HOLDS HWLICT FROM BOUND      EASC-32
ASCT.SLC DATAW     0               SAVE CURRENT HWLICT          EASC-32
ASCT.SLB DATAD     0               SAVE CURRENT LABEL           EASC-32
*                                                               EASC-32
ASCT.NCH DATAB     39              "BOUND"                      EASC-32
         DATAB     40              "EQU  "                      EASC-32
         DATAB     37              "ORG  "                      EASC-32
*                                                               EASC-32
ASCT.TYP DATAB     13      AC?     TYPE OPCODE                  EASC-32
         DATAB     23      BACW/BACH TYPE OPCODE                EBAC-33
         DATAB     29      DATA?   TYPE OPCODE                  EASC-32
         DATAB     30      GEN     TYPE OPCODE                  EASC-32
         DATAB     41      RES     TYPE OPCODE                  EASC-32
         DATAB     57      FORM    TYPE OPCODE   ?????????      EASC-32
*        DATAB     64      LPOOL   TYPE OPCODE                  EASC-32
         DATAB     65      REZ     TYPE OPCODE                  EASC-32
         DATAB     66      DEQU    TYPE OPCODE                  EASC-32
         DATAB     67      DORG    TYPE OPCODE                  EASC-32
ASCT.TTL DEQU      $-ASCT.TYP      TABLE LENGTH                 ESCT-32
         BOUND     1W                                           EASC-32
*                                                               EASC-32
ASCT.0   CEQU      $                                            ESCT-32
*----------------------BACK TO MAIN LINE CODE-------------------EASC-32
*===============================================================EASC-32
         IFF       UNIXF,SKIP                                   *JCB*
         SPACE     2
         ZBM       MA2PRES,HHBITS4 INDICATE MA2 NOT ASSIGNED
         LW        R4,=G'MA2'      LOGICAL FILE CODE             11003
         LA        R1,INQ.INFO     SET UP INQUIRY INFO AREA      11003
         ZR        R5              CLEAR R5                      11003
         ZR        R7              NO CNP                        11003
         SVC       2,X'48'         M.INQUIRY                     11003
         CI        R7,29           IS IT ASSIGNED ??             11003
         BEQ       MAC1            NO, BRANCH                    11003
         SBM       MA2PRES,HHBITS4 INDICATE MA2 FILE ASSIGNED
MAC1     LW        2,READSIPC      INITIALIZE SI FOR DE-COMPRESS.
         STW       2,READSIP
         SVC       1,X'44'         GET MEMORY HIGH ADDEESS R7.
A0.4     TRR       R7,R5           SAVE ENDING ADDR  AS11
         LA        R6,THEEND       GET ENDING ADDR   AS11
         SUR       R6,R5           DETERMINE ALLOCATION AS11
         CAMW      R5,=X'8000'     IS IT MORE THAN 8KW AS11
         BLE       A0.5            BR IF <8KW  AS11
         SVC       1,X'68'         M.FE FREE A MAP BLOCK AS11
         TRR       R3,R7           GET NEW ENDING ADDR AS11
         BU        A0.4            TRY AGAIN AS11
         SPACE     1
A0.5     STW       R7,SYMEND       SAVE END OF SYMTAB ADDRESS AS11
SKIP     ANOP                                                   *JCB*
         SPACE     1
******** PERFORM OPCODE TABLE INITIALIZATION *********
         SPACE     1
         BL        OPINITBA
         BL        OPINITNB
*        BL        OPINIT          GO INITIALIZE TABLE
         TITLE     TEST OPTIONS AND OPEN FILES
*        TEST OPTIONS AND OPEN ALL NECESSARY FILES.
*
*                  OPTIONS LO SET-NOLO RESET-LO  (OPT 1)
*                          BO SET-NOBO RESET-BO  (OPT 2).
*                          XREF SET-NOXREF RESET-XREF  ( OPT 4)
*                          GO SET-GO RESET-NOGO  (OPT 5).
*                          CMDK SET-CMDK RESET-NOCMDK  (OPT 7)
*
*
* (C) COPYRIGHT 1983 ENCORE COMPUTER CORPORATION
*     ALL RIGHTS RESERVED
*
         ZMB       PPT             SET DEFAULT ILLEGAL BO.
         IFF       UNIXF,SKIP                                   *JCB*
         LA        R1,INQ.INFO     GET ADDR FOR INQUIRY DATA     11003
*        LW        R4,=G'LO '      SET LFC                      ELFC-31
         LW        R4,FCBLO        SET LFC                      ELFC-31
         ZR        R5              CLEAR R5                      11003
         ZR        R7              NO CNP                        11003
         SVC       2,X'48'         M.INQUIRY                     11003
         LI        R7,5            SET UP APPEND ACCESS MODE (SLO) 11003
         LW        R1,INQ.INFO+1W  GET FAT ADDR                  11003
         LB        R4,DFT.ACF,R1   GET ACCESS FLAGS/SYS FILE CODE 11003
         CI        R4,3            IS IT SLO ??                  11003
         BEQ       FIL.1           YES - CONTINUE                11003
         LI        R7,2            SET UP FOR WRITE ACCESS       11003
FIL.1    STB       R7,CNPLO+2W     STORE ACCESS BYTE INTO CNP    11003
         TBM       7,DFT.STB,R1    IS THIS A TSM ASSOCIATED FAT    11010
         BNS       FIL.2           NO - CONTINUE
         LI        R7,1            1 MEANS LO IS A TSM ASSOC FAT   11011
         STB       R7,LO.TSMD      TEST LATER                      11011
         LI        R7,G' '         SET UP CARR CNTRL               11011
         STB       R7,CARR.C2      ONLY HDR LINE 2 WILL BE OUTPUT  11010
         BU        FIL.3             (TO TERMINAL)                 11010
         SPACE     1
FIL.2    LB        R7,DFT.ACF,R1   CHECK SYSTEM FILE CODE          11010
         ANMW      R7,=X'7'        CLEAR ALL BUT BITS 5-7          11010
         CI        R7,3            IS IT SLO ??                    11010
         BEQ       FIL.3           YES - LEAVE CARR CNTRL AS '-'   11010
         LI        R7,G'1'         SET UP EJECT                    11010
         STB       R7,CARR.C1          FOR 1ST HDR LINE            11010
         LI        R7,G' '         SET UP SINGLE SPACE             11010
         STB       R7,CARR.C2          FOR 2ND HDR LINE            11010
FIL.3    CEQU      $                                            ESCT-32
         TBM       5,DFT.STB,X1    LO ASSIGNED TO VOL RESOURCE  PR10988
         BNS       FIL.33          DON'T SET UP BLOCKING BUFF   PR10988
         LW        R5,LOW          GET START OF EXTENDED MEM    S880752
         STW       R5,FCBLO+FCB.BBA                             S880752
         LI        R4,BLKBUFSS     GET SIZE OF BLOCKING BUFFER  S880752
         STB       R4,FCBLO+FCB.BBA  AND SET INTO FCB           S880752
         ADI       R5,BLKBUFSB     BUMP BY REQUESTED SIZE       S880752
FIL.31   CEQU      $                                            ESCT-32
         CAMW      R5,HIGH         IS THERE ENOUGH?             S880752
         BLT       FIL.32          CONTINUE IF THERE IS         S880752
         SVC       1,X'69'         ELSE GET SOME MORE           S880752
         TRR       R3,R3           DID WE GET IT?               S880752
         BZ        MNOK            REPORT NO MEMORY             S880752
         STW       R4,HIGH         ELSE UPDATE END POINT        S880752
         BU        FIL.31          NOW SEE IF ENOUGH            S880752
FIL.32   CEQU      $               CONTINUE                     ESCT-32
         STW       R5,LOW          UPDATE "LOW" (MEM NOT RETRN) S880752
         STW       R5,CURRP        AND CURRENT POINTER          S880752
FIL.33   ZR        R3              INDICATE WAIT FOR FILE       PR10988
         M.OPENR   FCBLO,CNPLO     OPEN LFC LO                 11003
*!!!!!!!!!!LB!!!!!!!!R7,LO.TSMD!!!!!!IS!LO!A!TSM!ASSOC!FAT!??!!!!1.3#06
*!!!!!!!!!!BNZ!!!!!!!FIL.5!!!!!!!!!!TSM!ASSOC!FAT.!NO!MSG!NEEDED!1.3#06
*!!!!!!!!!!LI!!!!!!!!R7,G'0'!!!!!!!!!GET!DOUBLE!SPACE!CARR!CNTRL!1.3#06
*!!!!!!!!!!STB!!!!!!!R7,PRODREV!!!!!!PUT!IN!MSG!!!!!!!!!!!!!!!!!!1.3#06
*!!!!!!!!!!LW!!!!!!!!R7,HDRL1TCW!!!!!GET!PROD,!REV,!COPYRIGHT!TC!1.3#06
*!!!!!!!!!!STW!!!!!!!R7,FCBLO+1W!!!!!PUT!IN!FCB!FOR!LO!!!!!!!!!!!1.3#06
*!!!!!!!!!!M.WRIT!!!!FCBLO!!!!!!!!!!!WRITE!THE!MSG!!!!!!!!!!!!!!!1.3#06
*!!!!!!!!!!LB!!!!!!!!R7,CARR.C1!!!!!!GET!REAL!CARR.!CNTRL!!!!!!!!1.3#06
*!!!!!!!!!!STB!!!!!!!R7,PRODREV!!!!!!RESTORE!REAL!CARR.!CNTRL!!!!1.3#06
*!FIL.5!!!!EQU!!!!!!!$!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1.3#06!
*                                                                1.3#06
         LW        R5,PRODRTCW     PRODUCT ANNOUNCEMENT          1.3#06
         BL        XANOZ                                         1.3#06
         TBM       9,OPTION2       IS OPTION 55 CURRENTLY SET?  EIEE-33
         BNS       A0.3B           NO...BRANCH                  EIEE-33
         TBM       14,OPTION       IS OPTION 18 SET?            EIEE-33
         BS        A0.3B           YES, ALL O.K.                EIEE-33
         SBM       14,OPTION       ELSE SET OPTION 18           EIEE-33
         SBM       14,OPTSAV              ''                    EIEE-33
         SBM       EXPLFC,HHBITS3                               EIEE-33
         LB        R1,MSG3.L       GET MESSAGE LENGTH           EIEE-33
         STW       R1,FCBLO+9W     SAVE IN FCB                  EIEE-33
         LA        R4,MSG3.A       GET MESSAGE ADDRESS          EIEE-33
         STW       R4,FCBLO+8W     SAVE IN FCB                  EIEE-33
         LA        R1,FCBLO        GET LO FCB ADDRESS           EIEE-33
         SVC       1,X'32'         WRITE OUT MESSAGE            EIEE-33
         LB        R4,MSG4.L       WRITE OUT SECOND HALF        EIEE-33
         STW       R4,FCBLO+9W                                  EIEE-33
         LA        R4,MSG4.A                                    EIEE-33
         STW       R4,FCBLO+8W                                  EIEE-33
         SVC       1,X'32'                                      EIEE-33
*                                                                1.3#06
A0.3B    TBM       BO,OPTION
         BS        DEALCBO      NO BO - DEALLOCATE BO FILE
         LI        R1,2            SET UP WRITE ACCESS           11004
         STB       R1,CNPXX+2W     PUT IN CNP                    11004
         LA        R1,INQ.INFO     SET ADDR FOR INQUIRY DATA    PR10988
         LW        R4,FCBBO        SET LFC                      PR10988
         ZR        R5              CLEAR R5                     PR10988
         ZR        R7              NO CNP                       PR10988
         SVC       2,X'48'         M.INQUIRY                    PR10988
         LW        R1,INQ.INFO+1W  GET FAT ADDRESS              PR10988
         TBM       5,DFT.STB,X1    IS BO A VOLUME RESOURCE      PR10988
         BNS       FILE1.3         DON'T SET UP BLOCKING BUFF   PR10988
         LW        R5,LOW          GET BUFFER ADDRESS           S880752
         STW       R5,FCBBO+FCB.BBA  AND SET INTO FCB           S880752
         LI        R4,BLKBUFSS     GET SIZE OF BUFFER           S880752
         STB       R4,FCBBO+FCB.BBA  AND SET INTO FCB           S880752
         ADI       R5,BLKBUFSB     INCREMENT BY BUFFER SIZE     S880752
FILE1.1  CEQU      $                                            ESCT-32
         CAMW      R5,HIGH         IS THER ENOUGH?              S880752
         BLT       FILE1.2         CONTINUE IF THER IS          S880752
         SVC       1,X'69'         ELSE GET MORE                S880752
         TRR       R3,R3           DID WE GET IT?               S880752
         BZ        MNOK            ERROR OUT IF NOT             S880752
         STW       R4,HIGH         ELSE UPDATE END POINT        S880752
         BU        FILE1.1         AND RECHECK SIZE             S880752
FILE1.2  CEQU      $                                            ESCT-32
         STW       R5,LOW          UPDATE "LOW" (MEM NOT RETRN) S880752
         STW       R5,CURRP        AND CURRENT POINTER          S880752
FILE1.3  LA        R1,FCBBO        YES-OPEN BO FILE.            PR10988
         SBR       R1,1            SET FOR WRITE.
         BL        TST4DISC        OPEN  BO
*!!!!!!!!BNS!!!!!!!BONRM!!!!!!!!!!!BR!IF!NORMAL!I/O!!!!!!!!!!!!!S880752
*!!!!!!!!SBM!!!!!!!BOAD,FLAGS!!!!!!SET!RM!IN!USE!FOR!BO!FLAG!!!!S880752
*!BONRM!!LI!!!!!!!!R1,RECSIZ!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!S880752
         LI        R1,RECSIZ                                    S880752
         STB       R1,PPT          SET BO RECORD SIZE TO 120B.
FILE2    CEQU      $                                            ESCT-32
         TBM       GO,OPTION
         BNS       DEALCGO      NO GO - DEALLOCATE GO FILE
         LA        R1,INQ.INFO     GET ADDR FOR INQUIRY DATA     11003
         LW        R4,=G'GO '      SET LFC                       11003
         ZR        R5              CLEAR R5                      11003
         ZR        R7              NO CNP                        11003
         SVC       2,X'48'         M.INQUIRY                     11003
         LI        R7,5            SET UP APPEND ACCESS MODE (SGO) 11003
         LW        R1,INQ.INFO+1W  GET FAT ADDR                  11003
         LB        R4,DFT.ACF,R1   GET ACCESS FLAGS/SYS FILE CODE 11003
         CI        R4,2            IS IT SGO ??                  11003
         BEQ       FILE2.2         YES - CONTINUE                  11011
         CI        R4,4            NO - IS IT SBO ??               11011
         BEQ       FILE2.2         YES - CONTINUE                  11011
         LI        R7,2            NO - SET UP FOR WRITE ACCESS    11011
FILE2.2  CEQU      $                                            ESCT-32
         STB       R7,CNPGO+2W     STORE ACCESS BYTE INTO CNP    11003
         TBM       5,DFT.STB,X1    IS GO A VOLUME RESOURCE      PR10988
         BNS       FILE2.5         DON'T SET UP BLOCKING BUFF   PR10988
         LW        R5,LOW          GET BUFFER ADDRESS           S880752
         STW       R5,FCBGO+FCB.BBA  AND SET INTO FCB           S880752
         LI        R4,BLKBUFSS     GET SIZE OF BUFFER           S880752
         STB       R4,FCBGO+FCB.BBA  AND SET INTO FCB           S880752
         ADI       R5,BLKBUFSB     INCREMENT BY BUFFER SIZE     S880752
FILE2.3  CEQU      $                                            ESCT-32
         CAMW      R5,HIGH         IS THERE ENOUGH?             S880752
         BLT       FILE2.4         CONTINUE IF THERE IS         S880752
         SVC       1,X'69'         ELSE GET MORE                S880752
         TRR       R3,R3           DID WE GET IT?               S880752
         BZ        MNOK            ERROR OUT IF NOT             S880752
         STW       R4,HIGH         ELSE UPDATE END POINT        S880752
         BU        FILE2.3         AND RECHECK SIZE             S880752
FILE2.4  CEQU      $                                            ESCT-32
         STW       R5,LOW          UPDATE "LOW" (MEM NOT RETRN) S880752
         STW       R5,CURRP        AND CURRENT POINTER          S880752
FILE2.5  M.OPENR   FCBGO,CNPGO     OPEN LFC GO                  PR10988
         LI        R1,RECSIZ
         STB       R1,PPT          SET GO RECORD SIZE.
FILE3    CEQU      $                                            ESCT-32
         TBM       CMDK,OPTION
         BNS       DEALCCS      NO CS - DEALLOCATE CS FILE
         M.OPENR   FCBCS,CNPCS     OPEN LFC CS                 11003
FILE4    CEQU      $                                            ESCT-32
*!!!!!!!!LI!!!!!!!!R1,4!!!!!!!!!!!!SET!UP!UPDATE!ACCESS!!!!!!!!!C009-32
         LI        R1,1            SET UP READ ACCESS           C009-32
         STB       R1,CNPXX+2W     PUT IN CNP                    11004
         LW        R5,LOW          GET BUFFER ADDRESS           S880752
         STW       R5,FCBSI+FCB.BBA  AND SET INTO FCB           S880752
         LI        R4,BLKBUFSS     AND GET SIZE OF BUFFER       S880752
         STB       R4,FCBSI+FCB.BBA  AND SET INTO FCB           S880752
         ADI       R5,BLKBUFSB     INCREMENT BY BUFFER SIZE     S880752
FILE4.1  CEQU      $                                            ESCT-32
         CAMW      R5,HIGH         IS THERE ENOUGH?             S880752
         BLT       FILE4.2         CONTINUE IF THERE IS         S880752
         SVC       1,X'69'         ELSE GET MORE                S880752
         TRR       R3,R3           DID WE GET IT?               S880752
         BZ        MNOK            ERROR OUT IF NOT             S880752
         STW       R4,HIGH         ELSE UPDATE END POINT        S880752
         BU        FILE4.1         AND RECHECK SIZE             S880752
FILE4.2  CEQU      $                                            ESCT-32
         STW       R5,LOW          UPDATE "LOW" (MEM NOT RETRN) S880752
         STW       R5,CURRP        AND CURRENT POINTER          S880752
         LA        R1,FCBSI        OPEN SOURCE INPUT.
         BL        TST4DISC        OPEN  SI
*!!!!!!!!BNS!!!!!!!SINRM!!!!!!!!!!!BR!IF!NORM!I/O!!!!!!!!!!!!!!!S880752
*!!!!!!!!SBM!!!!!!!SIAD,FLAGS!!!!!!SET!USE!RM!FOR!SI!FLAG!!!!!!!S880752
*!SINRM!!TBM!!!!!!!0,PREFLG!!!!!!!!PRE!FILE!PRESENT?!!!!!!!!!!!!S880752
         BNS       A01             NO, BRANCH
         LI        R1,1            SET UP READ ACCESS            11004
         STB       R1,CNPXX+2W     PUT IN CNP                    11004
         LA        R1,FCBPRE       OPEN PRE SOURCE INPUT
         BL        TST4DISC        OPEN  PRE
*!!!!!!!!BNS!!!!!!!A01!!!!!!!!!!!!!BR!IF!NORMAL!I/O!!!!!!!!!!!!!S880752
*!!!!!!!!SBM!!!!!!!PREAD,FLAGS!!!!!SET!RM!IN!USE!FOR!PRE!FLAG!!!S880752
         BU        A01             START ASSEMBLY
         TITLE     DEALLOCATE UNUSED FILES
************************************************************************
*           D E A L L O C A T E  U N U S E D  F I L E S                *
************************************************************************
         SPACE     2
DEALCBO  LA        R1,FCBBO        DEASSIGN BO LOGICAL FILE CODE 11003
         ZR        R7              NO CNP                        11003
         SVC       2,X'53'         M.DASN                        11003
         BU        FILE2           GO CHECK NEXT FILE
         SPACE     1
DEALCGO  LA        R1,FCBGO        DEASSIGN GO LOGICAL FILE CODE 11003
         ZR        R7              NO CNP                        11003
         SVC       2,X'53'         M.DASN                        11003
         BU        FILE3           GO CHECK NEXT FILE
         SPACE     1
DEALCCS  LA        R1,FCBCS        DEASSIGN CS LOGICAL FILE CODE 11003
         ZR        R7              NO CNP                        11003
         SVC       2,X'53'         M.DASN                        11003
         BU        FILE4           GO CHECK NEXT FILE
SKIP     ANOP                                                   *JCB*
         IFT       UNIXF,SKIP                                   *JCB*
         TBM       LO,OPTION       IS LISTING REQUESTED         *JCB*
         BS        TBO             NO, CHECK OBJECT             *JCB*
         LW        R0,LO.FD        IS LO ASSIGNED TO STD OUT    *JCB*
         BNZ       TBO             BR IF YES                    *JCB*
         CCALL     _open,LOFILPTR,=X'1101',=X'1B6' OPEN W BIN   *JCB*
         TRR       R0,R0           TEST FOR ERROR               *JCB*
         BLT       LOER            ABORT ON ERROR               *JCB*
         STW       R0,LO.FD        ELSE, SAVE THE FILE DESCR    *JCB*
TBO      CEQU      $                                            *JCB*
         TBM       BO,OPTION                                    *JCB*
         BS        BONRM           NO BO - DEALLOCATE BO FILE   *JCB*
         CCALL     _open,BOFILPTR,=X'1101',=X'1B6' OPEN W BIN   *JCB*
         TRR       R0,R0           TEST FOR ERROR               *JCB*
         BLT       BOER            ABORT ON ERROR               *JCB*
TBO.2    STW       R0,BO.FD        ELSE, SAVE THE FILE DESCR    *JCB*
         LI        R1,RECSIZ                                    *JCB*
         STB       R1,PPT          SET BO RECORD SIZE TO 120B.  *JCB*
BONRM    CEQU      $                                            *JCB*
SKIP     ANOP                                                   *JCB*
         TITLE     A01 - START ASSEMBLING
A01      CEQU      $               START ASSEMBLER              ESCT-32
         LI        R3,-RECSIZ
         ZMW       RECSIZ+PBL,R3   INITIALIZE BO BUFFER.
         BIW       R3,$-1W
         IFF       UNIXF,SKIP                                   *JCB*
         M.QATIM   DATETIME        GET CURRENT DATE AND TIME IN ASCII
SKIP     ANOP                                                   *JCB*
         IFT       UNIXF,SKIP                                   *JCB*
         LA        R7,DATETIME                                  *JCB*
         SVC       1,X'15'         GET DATE AND TIME IN ASCII   *JCB*
         SVC       1,X'4E'         GET CURRENT TIME IN BINARY   *JCB*
         STW       R7,DATETIME+4W  TEMP LOCATION                *JCB*
         LB        R5,DATETIME+4W  GET HOURS                    *JCB*
         BL        CONBAD          CONVERT TO ASCII             *JCB*
         STH       R7,DATETIME+4H  PUT HOURS IN ASCII           *JCB*
         LB        R5,DATETIME+4W+1B  GET MINUTES               *JCB*
         BL        CONBAD          CONVERT TO ASCII             *JCB*
         STH       R7,DATETIME+5H  PUT MINUTES IN ASCII         *JCB*
         LB        R5,DATETIME+4W+2B  GET SECONDS               *JCB*
         BL        CONBAD          CONVERT TO ASCII             *JCB*
         STH       R7,DATETIME+6H  PUT SECONDS IN ASCII         *JCB*
SKIP     ANOP                                                   *JCB*
         LI        R2,G'  '        LOAD TWO SPACES INTO R2
         LD        R0,C.DATE       GET DATE (AS ENTERED BY USER) 83-725
         STD       R0,FMTD.DT      SAVE DATE FOR POSS INCL IN OBJ  11005
         STW       R0,TCWDATE      STORE IT (WORD BY WORD TO BE  83-725
         STW       R1,TCWDATE+1W     SURE OF BOUNDING)           83-725
         STH       R2,TCWDATE+8B   STORE TWO SPACES
         LI        R1,G':'
         LH        R0,DATETIME+4H  GET HOURS IN ASCII
         STH       R0,TCWDATE+10B
         STH       R0,FMTD.DT+1D   SAVE HOURS FOR POS INCL IN OBJ  11005
         STB       R1,TCWDATE+12B  STORE :
         STB       R1,FMTD.DT+1D+2B                                11005
         LH        R0,DATETIME+5H  GET MINUTES IN ASCII
         STB       R0,TCWDATE+14B
         STB       R0,FMTD.DT+1D+4B   SAVE 2ND DIGIT OF MIN        11005
         SRL       R0,8
         STB       R0,TCWDATE+13B
         STB       R0,FMTD.DT+1D+3B   SAVE 1ST DIGIT OF MIN        11005
         STB       R1,TCWDATE+15B  STORE :
         STB       R1,FMTD.DT+1D+5B                                11005
         LH        R0,DATETIME+6H  GET SECONDS IN ASCII
         STH       R0,TCWDATE+16B
         STH       R0,FMTD.DT+1D+3H   SAVE SECONDS                 11005
         STH       R2,TCWDATE+18B  STORE TWO SPACES
         ZR        R3              CLEAN UP REG FOR MANIPULATION.
         ABR       R3,1            INDICATE AN OPTION COMMAND.
         TBM       XREF,OPTION     IS XREF WANTED?
         BNS       A01.1        YES
         SBR       R3,2            NO- TELL REPORTER.
A01.1    CEQU      $                                            ESCT-32
         SBR       R3,0            COMMAND REPORTER.
         SBM       0,REPTYPE       INDICATE XREF COMMAND
         BL        REPTR          SEND XREF OPTION TO REPTR.
         IFF       UNIXF,SKIP                                   *JCB*
         LW        7,READSKPC      INITIALIZE SK FOR DE-COMPRESS.
         STW       R7,READSKP
SKIP     ANOP                                                   *JCB*
         ZMW       SBUF            BLANK OUT FIRST WORD OF BUFFER.
         ZMH       SBUF+1W+0H      ZERO SEQUENCE NUMBER OF SCRATCH.
         ZBM       7,IMIP          CLEAR IMAGE IN PROGRESS FLAG.
         LI        R1,1            INDICATE PASS 1.
         BL        CPAS            SET UP FOR THE PASS.
         ZMH       PBLC            CLEAR BO CKSUM ACCUMULATOR.
         ZMH       PBSQ            CLEAR BO SEQ. NO.
         LB        R1,PAS2
         BL        HHHH            GO TO ASSEMBLER NUGGET TO RUN ASSEM.
         BU        A03             RETURN FOR EOF/EOJ ON SOURCE INPUT.
         LI        R6,X'DF'        INDICATE LAST BINARY OBJECT RECORD.
         BL        PBP             PUBLISH LAST BINARY OBJECT RECORD.
         TBM       XREF,OPTION     CHECK IF XREF WANTED BY USER.
         BS        A02.0        NO-GO CHECK CMDK.
         LW        R0,HWKSPA       LOAD WORD OF SPACES
         LA        R1,TCWTITL      ADDRESS OF TITLE BUFFER
A01.2    STW       R0,0,R1         BLANK BUFFER
         ADI       R1,4            INCREMENT POINTER
         CAMW      R1,=TCWTTLE     IS END OF BUFFER HERE?        83-451
         BLT       A01.2           BRANCH IF NOT DONE
         LA        R1,TCWTITL      ADDRESS OF TITLE BUFFER
         LA        R2,T.CREF       ADDRESS OF 'CROSS REFERENCE'
A01.3    LW        R0,0,R2         PICK UP 4 CHARACTERS
         STW       R0,0,R1         STORE IN TITLE BUFFER
         ABR       R1,29           INCREMENT POINTER
         ABR       R2,29           INCREMENT POINTER
         CAMW      R2,=T.CREF.E    IS END OF STRING REACHED
         BLT       A01.3           BRANCH IF NOT DONE YET
         LI        R7,120B         NO. OF CHARACTERS ON A PRINTER.
         BL        WRITEREP        DO CROSS,REFERENCE.
A02.0    CEQU      $                                            ESCT-32
         IFF       UNIXF,SKIP                                   *JCB*
         LA        R1,FCBSK
*!!!!!!!!TBM!!!!!!!UT1AD,FLAGS!!!!!IS!RM!IN!USE!FOR!UT1!!!!!!!!!S880752
*!!!!!!!!BNS!!!!!!!A02.03!!!!!!!!!!BR!IF!NOT!!!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!BL!!!!!!!!RM.CLSE!!!!!!!!!CLOSE!UT1!!!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!BU!!!!!!!!A02.06!!!!!!!!!!CONTINUE!!!!!!!!!!!!!!!!!!!!!S880752
*!A02.03!!SVC!!!!!!1,X'39'!!!!!!!!!CLOSE!UT1!!!!!!!!!!!!!!!!!!!!S880752
*!A02.06!!TBM!!!!!!0,PREFLG!!!!!!!!PRE!FILE!PRESENT?!!!!!!!!!!!!S880752
         SVC       1,X'39'         CLOSE UT1                    S880752
         TBM       0,PREFLG        PRE FILE PRESENT?            S880752
         BNS       A02.1           NO, BRANCH
         LA        R1,FCBPRE       ADDR OF PRE FCB
         STW       R1,FCBA         READ SOURCE FROM PRE AGAIN
         LA        R7,READ7        ADDRESS OF PRE EOF PROCESSOR
         STW       R7,EOFA         SET AS SOURCE EOF PROCESSOR
         ZMB       READPIP         INITIALIZE PRE RECORD PTR
         LA        R7,READPIP      ADDR OF PRE RECORD PTR
         STW       R7,READPTR      SET AS SOURCE RECORD PTR
         LA        R7,IBUF2        ADDR OF PRE INPUT BUFFER
         STW       R7,IBUFA        SET AS SOURCE INPUT BUFFER
A02.1    CEQU      $                                            ESCT-32
SKIP     ANOP                                                   *JCB*
         IFT       UNIXF,SKIP                                   *JCB*
         CCALL     _close,SK.FD    CLOSE UT1                    *JCB*
SKIP     ANOP                                                   *JCB*
         LW        3,HWERCT        FETCH NUMBER OF ERRORS
         BZ        A01             NO ERRORS - CONTINUE ASSEMBLY
         SBM       ERROCCUR,FLAGS  INDICATE ERROR HAS OCCURRED
         BU        A01             RESTART PASS 1.
         TITLE     A03 - TERMINATE ASSEMBLER
************************************************************************
*                                                                      *
*        T E R M I N A T E    A S S E M B L E R                        *
*                                                                      *
************************************************************************
         SPACE     2
A03      CEQU      $                                            ESCT-32
         IFF       UNIXF,SKIP                                   *JCB*
         TBM       CMDK,OPTION
         BNS       A03.1        IS CMDK REQUESTED?
         LA        R1,FCBCS
         SVC       1,X'38'         WEOF ON CMDK FILE.
A03.1    CEQU      $                                            ESCT-32
SKIP     ANOP                                                   *JCB*
         TBM       BO,OPTION       BINARY OUTPUT REQUIRED?
         BS        A03.4        NO.
         IFT       UNIXF,SKIP                                   *JCB*
         CCALL     _close,BO.FD    CLOSE BO                     *JCB*
SKIP     ANOP                                                   *JCB*
         IFF       UNIXF,SKIP                                   *JCB*
         LA        R1,FCBBO        'BO' FCB ADDR
         LW        R4,=X'00FFFFFF'
         LMW       R5,0,1          MASK IN LOGICAL FILE CODE
*!!!!!!!!TBM!!!!!!!BOAD,FLAGS!!!!!!TEST!IF!RM!IN!USE!!!!!!!!!!!!S880752
*!!!!!!!!BNS!!!!!!!A03.2!!!!!!!!!!!BR!IF!NOT!!!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!BL!!!!!!!!RM.CLSE!!!!!!!!!CLOSE!'BO'!FILE!!!!!!!!!!!!!!S880752
*!!!!!!!!BU!!!!!!!!A03.3!!!!!!!!!!!CONTINUE!!!!!!!!!!!!!!!!!!!!!S880752
*!A03.2!!SVC!!!!!!!1,X'39'!!!!!!!!!CLOSE!BO!USING!NORM!I/O!!!!!!S880752
*!A03.3!!LA!!!!!!!!R1,FCBBO!!!!!!!!GET!ADDR!OF!LFC!BO!!!!!!!!!!!S880752
         SVC       1,X'39'         CLOSE BO USING NORM I/O      S880752
         LA        R1,FCBBO        GET ADDR. OF LFC BO          S880752
         ZR        R7              NO CNP                        11003
         SVC       2,X'53'         DEASSIGN                      11003
SKIP     ANOP                                                   *JCB*
A03.4    CEQU      $                                            ESCT-32
         IFT       UNIXF,SKIP                                   *JCB*
         ZR        R5              NO ERROR CODE YET            *JCB*
SKIP     ANOP                                                   *JCB*
         TBM       ERROCCUR,FLAGS  DID AN ERROR OCCUR IN ANY PROGRAM?
         BNS       A03.5           NO - TAKE NORMAL EXIT
         LW        5,AS31          GENERAL ABORT CODE FOR ASSEMBLER
         BU        ABRTM1          GO TO ABORT PROCESSING
A03.5    CEQU      $                                            ESCT-32
         IFF       UNIXF,SKIP                                   *JCB*
         SVC       1,X'55'         EXIT.
SKIP     ANOP                                                   *JCB*
         IFT       UNIXF,SKIP                                   *JCB*
         CCALL     _exit,R5.       EXIT WITH ABORT STATUS       *JCB*
SKIP     ANOP                                                   *JCB*
*
* (C) COPYRIGHT 1983 ENCORE COMPUTER CORPORATION
*     ALL RIGHTS RESERVED
*
         TITLE     CPAS - SET UP FOR BEGINNING OF A PASS
************************************************************************
*        SET UP FOR THE BEGINNING OF A PASS.                           *
************************************************************************
         SPACE     3
CPAS     CEQU      $                                            ESCT-32
         STW       R0,CPASS0       SAVE RETURN ADDRESS.
         STB       R1,PAS2         SAVE THE PASS INDICATOR.
         ZMW       LICE            SET LINE COUNT TO ZERO.
         ZMW       MAX             ZERO MAX PROGRAM SIZE       S8700512B
         BL        EIS.RSET        FORCE OPCODES TO REIS MODE   EINS-31
         TBM       7,PAS2          CHECK WHICH PASS.
         BS        CPAS3        PASS1.
         LW        R7,OPTSAV       GET ORIGINAL OPTIONS        EBRM-33
         STW       R7,OPTION       RESTORE THEM                EBRM-33
         IFF       UNIXF,SKIP                                   *JCB*
         LI        R7,X'9F'        INDICATE LAST COSY RECORD.
         BL        SKOUT           DONE ONLY AT START OF PASS 2.
         LA        R1,FCBSK
         ZBR       R1,1            SET TO READ.
*!!!!!!!!TBM!!!!!!!UT1AD,FLAGS!!!!!RM!IN!USE!FOR!UT1!!!!!!!!!!!!S880752
*!!!!!!!!BNS!!!!!!!CPAS1!!!!!!!!!!!USE!NORMAL!I/O!IF!NOT!!!!!!!!S880752
*!!!!!!!!BL!!!!!!!!RM.CLSE!!!!!!!!!CLSE!UT1!TO!PURGE!SYSTEM!BLKGS880752
*!!!!!!!!BL!!!!!!!!RM.OPEN!!!!!!!!!OPEN!'SK'!FOR!READ!AND!IOCS!IS880752
*!CPAS0!!BL!!!!!!!!RM.RWND!!!!!!!!!REWIND!'SK'!FOR!PASS!1/!PASS!S880752
*!!!!!!!!BU!!!!!!!!*CPASS0!!!!!!!!!RETURN!!!!!!!!!!!!!!!!!!!!!!!S880752
*!CPAS1!!!SVC!!!!!!1,X'39'!!!!!!!!!CLOSE!UT1!!!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!LA!!!!!!!!R7,CNPSK!!!!!!!!CNP!ADDRESS!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!SVC!!!!!!!2,X'42'!!!!!!!!!M.OPENR!!!!!!!!!!!!!!!!!!!!!!S880752
CPAS2    SVC       1,X'37'         REWIND
SKIP     ANOP                                                   *JCB*
         IFT       UNIXF,SKIP                                   *JCB*
         CCALL     _seek,SK.FD,=0,=0  REWIND UT1                *JCB*
SKIP     ANOP                                                   *JCB*
         BU        *CPASS0         RETURN
CPAS3    CEQU      $                                            ESCT-32
         IFF       UNIXF,SKIP                                   *JCB*
         LI        R1,2            SET UP WRITE ACCESS           11004
         STB       R1,CNPXX+2W     PUT IN CNP                    11004
         LW        R5,FCBSK+FCB.BBA  GET BLOCKING BUFF VECTOR   S880752
         BNZ       CPAS3.3         DON'T GET ONE IF SET         S880752
         LW        R5,LOW          GET BUFFER ADDRESS           S880752
         STW       R5,FCBSK+FCB.BBA  AND SET INTO FCB           S880752
         LI        R4,BLKBUFSS     GET SIZE OF BUFFER           S880752
         STB       R4,FCBSK+FCB.BBA  AND SET INTO FCB           S880752
         ADI       R5,BLKBUFSB     INCREMENT BY BUFFER SIZE     S880752
CPAS3.1  CEQU      $                                            ESCT-32
         CAMW      R5,HIGH         IS THERE ENOUGH?             S880752
         BLT       CPAS3.2         CONTINUE IF THERE IS         S880752
         SVC       1,X'69'         ELSE GET MORE                S880752
         TRR       R3,R3           DID WE GET IT?               S880752
         BZ        MNOK            ERROR OUT IF NOT             S880752
         STW       R4,HIGH         ELSE UPDATE END POINT        S880752
         BU        CPAS3.1         AND RECHECK SIZE             S880752
CPAS3.2  CEQU      $                                            ESCT-32
         STW       R5,LOW          UPDATE "LOW" (MEM NOT RETRN) S880752
         STW       R5,CURRP        AND CURRENT POINTER          S880752
CPAS3.3  CEQU      $                                            ESCT-32
         LA        R1,FCBSK        OPEN SCRATCH (UT1).
         SBR       R1,1            SET FOR WRITE.
         BL        TST4DISC        OPEN UT1
         BU        CPAS2           AND REWIND                   S880752
SKIP     ANOP                                                   *JCB*
         IFT       UNIXF,SKIP                                   *JCB*
         CCALL     _open,SKFILPTR,=X'1102',=X'1B6' OPEN R/W BIN *JCB*
         TRR       R0,R0           TEST FOR ERROR               *JCB*
         BLT       SKER            ABORT IF ERROR               *JCB*
         STW       R0,SK.FD        ELSE SAVE FILE DESCRIPTOR    *JCB*
         BU        *CPASS0         RETURN                       *JCB*
SKIP     ANOP                                                   *JCB*
*!!!!!!!!BNS!!!!!!!CPAS2!!!!!!!!!!!USE!NORMAL!I/O!IF!NOT!SET!!!!S880752
*!!!!!!!!SBM!!!!!!!UT1AD,FLAGS!!!!!SET!RM!IN!USE!FOR!UT1!!!!!!!!S880752
*!!!!!!!!BU!!!!!!!!CPAS0!!!!!!!!!!!GO!REWIND!SK!AND!RETURN.!!!!!S880752
         TITLE     ABORTM - COMMON ABORT MESSAGE ROUTINE
************************************************************************
*                                                                      *
*        COMMON ABORT MESSAGE ROUTINE                                  *
*                                                                      *
************************************************************************
         SPACE     3
ABORTM   CEQU      $                                            ESCT-32
         CI        R1,0
         BEQ       ABRTM1
         STW       R1,ABRTM.R1     SAVE R1                      S880752
         ZR        R0              CLEAR OUT R0                 S880752
         SLLD      R0,12           GET BYTE COUNT INTO R0       S880752
         ZBR       R1,0            RESET BYTE TAG BIT           S880752
         SRL       R1,12           REPOSITION ADDR              S880752
         IFF       UNIXF,SKIP                                   *JCB*
         STW       R0,FCBLO+9W     STORE BYTE COUNT             S880752
         STW       R1,FCBLO+8W     AND ADDR                     S880752
         CI        R0,8            IS XFER < 8B                 S880752
         BGT       $+3W            SKIP CKBYTCNT IF NOT         S880752
         LW        R1,ABRTM.R1     RESTORE R1 FOR CALL          S880752
*!!!!!!!!STW!!!!!!!R1,FCBLO+1W!!!!!PRINT!ERROR!MESSAGE.!!!!!!!!!S880752
         BL        CKBYTCNT        CHECK FOR AT LEAST 8 BYTES
         LA        R1,FCBLO
         SVC       1,X'32'         WRITE MESSAGE TO LO
         LW        R5,AS31         ! LOAD ABORT CODE 'AS31'
ABRTM1   CEQU      $                                            ESCT-32
         SVC       1,X'57'          ABORT
SKIP     ANOP                                                   *JCB*
         IFT       UNIXF,SKIP                                   *JCB*
         TRR       R1,R2           MOVE BUF ADDR IN REG 2       *JCB*
         TRR       R0,R1           SET BYTE COUNT               *JCB*
         BL        PSTDERR         PRINT MESSAGE ON STD ERROR   *JCB*
         LW        R5,AS31         ! LOAD ABORT CODE 'AS31'     *JCB*
ABRTM1   CEQU      $                                            *JCB*
         BU        A03.5           COMMON EXIT                  *JCB*
SKIP     ANOP                                                   *JCB*
*
ABRTM.R1 DATAW     0               HOLDER FOR R1 INPUT          S880752
         IFT       UNIXF,SKIP                                   *JCB*
         TITLE     PSTDERR - OUTPUT MSG TO STD ERR              *JCB*
*        R1 = BUFFER COUNT                                      *JCB*
*        R2 = BUFFER ADDRESS                                    *JCB*
PSTDERR  TRR       R2,R3           COPY BUF ADDR IN REG 3       *JCB*
         ADR       R1,R3           POINT TO END OF BUFFER       *JCB*
         ADI       R1,1            BUMP BYTE COUNT              *JCB*
         LB        R4,0B,R3        GET CHAR AT END OF BUFFER    *JCB*
         STW       R4,UNIXBP       SAVE THE CHAR THERE          *JCB*
         STW       R3,UNIXXR       SAVE THE POINTER TO IT       *JCB*
         LI        R4,X'A'         GET A N/L                    *JCB*
         STB       R4,0B,R3        PUT AT END OF BUFFER         *JCB*
         CCALL     _write,=2,R2.,R1. PUT MSG TO STD ERROR       *JCB*
         LW        R4,UNIXBP       GET THE CHAR SAVED           *JCB*
         LW        R3,UNIXXR       GET THE POINTER TO IT        *JCB*
         STB       R4,0B,R3        RESTORE CHAR AT END OF BUFF  *JCB*
         TRSW      R0              RETURN                       *JCB*
SKIP     ANOP                                                   *JCB*
         TITLE     PPP - OUTPUT DATA TO LO
* CODE DELETED FOR REALLOCATION OF SLO   AS16
************************************************************************
*--------OUTPUT DATA TO LO                                             *
*                                                                      *
*--------INPUT R1(0-11)=NUMBER OF BYTES TO PRINT                       *
*              R1(12-31)=BASE ADR. OF LINE TO PRINT                    *
*              R7=0 INDICATES PRINT LINE ONLY IF LISTING IS DESIRED    *
*              R7>0 OR R7<0 INDICATES PRINT LINE UNCONDITIONALLY.      *
*                                                                      *
*--------OUTPUT R7=0 MEANS LINE PRINTED ON SAME PAGE AS PREVIOUS LINE  *
*              R7=1 MEANS A NEW PAGE WAS STARTED                       *
*                                                                      *
*        R5 MUST NOT BE ALTERED                                        *
************************************************************************
         SPACE     3
PPP      CEQU      $                                            ESCT-32
         STW       R0,PPPS0        SAVE RETURN ADDRESS.
         STW       R1,PPPR1        SAVE PRINT LINE TCW.
         TRR       7,7             DID THE LINE HAVE ANY ERRORS?
         IFT       UNIXF,SKIP                                   *JCB*
         BZ        PPPTEST         NO, CHECK IF PRINTING IS OFF *JCB*
         ZR        R0              CLEAR FOR XFER COUNT         *JCB*
         SLLD      R0,12           GET COUNT IN R0              *JCB*
         ZBR       R1,0            CLEAR BYTE ADDRESSING        *JCB*
         SRL       R1,12           MOVE COUNT BACK              *JCB*
         TRR       R1,R2           SAVE BUF ADDR IN REG 2       *JCB*
         ADR       R0,R2           POINT TO END OF BUFFER       *JCB*
         ADI       R0,1            BUMP BYTE COUNT              *JCB*
         LB        R3,0B,R2        GET CHAR AT END OF BUFFER    *JCB*
         STW       R3,UNIXBP       SAVE THE CHAR THERE          *JCB*
         STW       R2,UNIXXR       SAVE THE POINTER TO IT       *JCB*
         LI        R3,X'A'         GET A N/L                    *JCB*
         STB       R3,0B,R2        PUT AT END OF BUFFER         *JCB*
         TRR       R1,R2           SAVE BUF ADDR IN REG 2       *JCB*
         CCALL     _write,=2,R2.,R0. PUT ERROR TO STD ERROR     *JCB*
         LW        R3,UNIXBP       GET THE CHAR SAVED           *JCB*
         LW        R2,UNIXXR       GET THE POINTER TO IT        *JCB*
         STB       R3,0B,R2        RESTORE CHAR AT END OF BUFF  *JCB*
PPPTEST  TBM       LO,OPTION       CHECK IF LO DESIRED.         *JCB*
         BS        PPP1            LO NOT ENABLED , RETURN.     *JCB*
PPPW     CEQU      $                                            *JCB*
         LW        R1,PPPR1                                     *JCB*
         ZR        R0              CLEAR FOR XFER COUNT         *JCB*
         SLLD      R0,12           GET COUNT IN R0              *JCB*
         ZBR       R1,0            CLEAR BYTE ADDRESSING        *JCB*
         SRL       R1,12           MOVE COUNT BACK              *JCB*
         LW        R2,LO.FD        GET LISTING FD               *JCB*
         CI        R2,1            IS IT STD OUT                *JCB*
         BNE       PPPW.0          BR IF NOT                    *JCB*
         TRR       R1,R2           SAVE BUF ADDR IN REG 2       *JCB*
         ADR       R0,R2           POINT TO END OF BUFFER       *JCB*
         ADI       R0,1            BUMP BYTE COUNT              *JCB*
         LB        R3,0B,R2        GET CHAR AT END OF BUFFER    *JCB*
         STW       R3,UNIXBP       SAVE THE CHAR THERE          *JCB*
         STW       R2,UNIXXR       SAVE THE POINTER TO IT       *JCB*
         LI        R3,X'A'         GET A N/L                    *JCB*
         STB       R3,0B,R2        PUT AT END OF BUFFER         *JCB*
PPPW.0   TRR       R1,R2           SAVE BUF ADDR IN REG 2       *JCB*
         CCALL     _write,LO.FD,R2.,R0.   OUTPUT LISTING RECORD *JCB*
         LW        R2,LO.FD        GET LISTING FD               *JCB*
         CI        R2,1            IS IT STD OUT                *JCB*
         BNE       PPPW.1          BR IF NOT                    *JCB*
         LW        R3,UNIXBP       GET THE CHAR SAVED           *JCB*
         LW        R2,UNIXXR       GET THE POINTER TO IT        *JCB*
         STB       R3,0B,R2        RESTORE CHAR AT END OF BUFF  *JCB*
PPPW.1   TRR       R0,R0           TEST FOR ERROR               *JCB*
         BLT       LOER            EOF ON WRITE--ABORT USER AS16*JCB*
SKIP     ANOP                                                   *JCB*
         IFF       UNIXF,SKIP                                   *JCB*
         BCF       EQ,$+3W         YES, GO PRINT OUT THE LINE.
         TBM       LO,OPTION       CHECK IF LO DESIRED.
         BS        PPP1         LO NOT ENABLED , RETURN.
PPPW     CEQU      $                                            ESCT-32
         BL        TTOR            CHECK FOR TOF AND PRINT HEADER IF TOF
         LW        R1,PPPR1
*!!!!!!!!STW!!!!!!!R1,FCBLO+1W!!!!!SET!TCW!IN!FCBLO.!!!!!!!!!!!!S880752
         ZR        R0              CLEAR OUT RECEIVER           S880752
         SLLD      R0,12           EXTRACT BYTE COUNT           S880752
         ZBR       R1,0            RESET BYTE INDICATOR         S880752
         SRL       R1,12           REPOSITION ADDR              S880752
         STW       R0,FCBLO+9W     STORE BUFFER LENGTH          S880752
         STW       R1,FCBLO+8W     AND BUFFER ADDR              S880752
         CI        R0,8            IS XFER < 8B                 S880752
         BGT       $+3W            SKIP CKBYTCNT IF NOT         S880752
         LW        R1,PPPR1        RESTORE R1 FOR CALL          S880752
         BL        CKBYTCNT        CHECK FOR AT LEAST 8 BYTES
         LA        R1,FCBLO
         SVC       1,X'32'         WRITE.
         TBM       7,FCBLO+3W      TEST FOR EOM     AS17
         BS        LOER            EOF ON WRITE--ABORT USER AS16
SKIP     ANOP                                                   *JCB*
PPP1     BU        *PPPS0          RETURN
         SPACE     2
PPPR1    RES       1W
         IFT       UNIXF,SKIP                                   *JCB*
UNIXBP   RES       1W              CHAR TO SAVE                 *JCB*
UNIXXR   RES       1W              POINTER TO CHAR              *JCB*
SKIP     ANOP                                                   *JCB*
         TITLE     EJCT - PAGE EJECT FOR LO
*
* ENTRY POINT EJCT WILL SET FOR PAGE EJECT ON NEXT PRINT ONLY IF LO IS
* ENABLED.
*
* ENTRY POINT EJCT2 WILL UNCONDITIONALLY SET FOR PAGE EJECT
*                                  ON NEXT PRINT
*
* SEND EJECT COMMAND TO THE LO DEVICE EXCEPT WHEN IT IS ALREADY AT
* TOP OF FORM. SAVE ADR OF HEADER FOR HEADER PRINT ROUTINE
*---INPUT R6, 0-11 EQ LENGTH OF HEADING LINE BUFFER IN BYTES
*---      R6, 12-31 EQ BASE ADDRESS OF THE HEADING LINE BUFFER
         SPACE     2
EJCT     CEQU      $                                            ESCT-32
         TBM       LO,OPTION       IS LO ENABLED?
         BNS       EJCT2        YES, PROCESS PAGE EJECT.
         BU        EJCTR           RETURN.
EJCT2    CEQU      $                                            ESCT-32
         STW       6,HWBAHDR       SAVE BASE ADR AND QTY OF HEADER BUF
         ZMB       NPLC            ZERO LINES PRINTED COUNT
EJCTR    TRSW      0               RETURN
         IFF       UNIXF,SKIP                                   *JCB*
         TITLE     TTOR - WRITE LO
************************************************************************
*                                                                      *
*                  T T O R                                             *
*                  R5 MUST NOT BE ALTERED.                             *
*                                                                      *
************************************************************************
         SPACE     3
TTOR     CEQU      $                                            ESCT-32
         STW       R0,TTORRET      SAVE RETURN ADDRESS
         LI        R7,0            DEFAULT,LINE ON SAME PAGE.
         SBM       7,NPLC
         BNS       TTOR1        PAGE EJECT WANTED.
         TBM       25,FCBLO+3W     CHECK BOF.
         BNS       TTORR
TTOR1    CEQU      $                                            ESCT-32
         LB        R6,CARR.C1      GET HDR LINE 1 CARRIAGE CNTRL   11010
         STB       R6,PRODREV      SET UP CARRIAGE CONTROL         11010
         LW        R1,PRODRTCW     GET PROD, REV, INFORMATION      11011
*!!!!!!!!STW!!!!!!!R1,FCBLO+1W!!!!!!!TCW!AND!PUT!IN!FCB!!!!!!!!!S880752
         ZR        R0              CLEAR OUT RECEIVER           S880752
         SLLD      R0,12           EXTRACT BYTE COUNT           S880752
         ZBR       R1,0            RESET BYTE INDICATOR         S880752
         SRL       R1,12           REPOSITION ADDR              S880752
         STW       R0,FCBLO+9W     STORE BUFFER LENGTH          S880752
         STW       R1,FCBLO+8W     AND BUFFER ADDR              S880752
         LA        R1,FCBLO                                        11010
         SVC       1,X'32'         WRITE HEADER LINE               11010
         LW        R1,HWBAHDR      GET HEADER BUFFER ADDRESS.
         LB        R6,CARR.C2      GET HDR LINE 2 CARRIAGE CNTRL   11010
*!!!!!!!!STB!!!!!!!R6,0,X1!!!!!!!!!PUT!EJECT!COMMAND!IN!HEADER!BS880752
*!!!!!!!!STW!!!!!!!R1,FCBLO+1W!!!!!SET!UP!FCB!FOR!HEADER.!!!!!!!S880752
         ZR        R0              CLEAR OUT RECEIVER           S880752
         SLLD      R0,12           EXTRACT BYTE COUNT           S880752
         ZBR       R1,0            RESET BYTE INDICATOR         S880752
         SRL       R1,12           REPOSITION ADDR              S880752
         STW       R0,FCBLO+9W     STORE BUFFER LENGTH          S880752
         STW       R1,FCBLO+8W     AND BUFFER ADDR              S880752
         STB       R6,0,X1         PUT CC CHAR INTO HEADER      S880752
         CI        R0,8            IS XFER < 8B                 S880752
         BGT       $+3W            SKIP CKBYTCNT IF NOT         S880752
         LW        R1,HWBAHDR      RESTORE R1 FOR CALL          S880752
         BL        CKBYTCNT        CHECK FOR AT LEAST 8 BYTES
         LA        R1,FCBLO
TTOR2    CEQU      $                                            ESCT-32
         SVC       1,X'32'         WRITE LO
         TBM       7,FCBLO+3W      TEST FOR EOM     AS17
         BS        LOER            EOF ON WRITE--ABORT AS16
TTOR3    LI        R7,1            SIGNAL THAT JUST HEADED A PAGE.
TTORR    CEQU      $                                            ESCT-32
         LW        R0,TTORRET      RESTORE RETURN ADDRESS
         TRSW      R0              RETURN.
         TITLE     CKBYTCNT - ENSURES A MINIMUM OUTPUT OF 8 BYTES
************************************************************************
*                                                                      *
*        CHECK BYTE COUNT IN OUTPUT RECORD                             *
*        IF LESS THAN EIGHT (8) MOVE TO INTERMEDIATE BUFFER            *
*        AND BLANK FILL BUFFER TO EIGHT (8) BYTES                      *
*                                                                      *
************************************************************************
         SPACE     1
CKBYTCNT STD       R0,R0SAV        SAVE R0,R1
         STW       R2,R2SAV        SAVE R2
         STW       R4,R4SAV        SAVE R4
         STW       R6,R6SAV        SAVE R6
         LD        R0,BLANKS       BLANK OUT BUFFER
         STD       R0,BUFF
         LD        R0,R0SAV
         TBR       R1,12           IS IT A BYTE ADDRESS?
         BCT       SET,BYTE        YES, DO BYTE CONVERSION
         TBR       R1,31           IS IT A HALFWORD ADDRESS?
         BCT       SET,HALFWORD    YES, FO HALFWORD CONVERSION
         BU        WORD
BYTE     SRL       R1,1            DIVIDE BY TWO
HALFWORD SRL       R1,1            DIVIDE BY TWO
WORD     SRL       R1,18           THIS IS THE BYTE COUNT
         CI        R1,8            IS IT LESS THAN EIGHT?
         BGE       OUT          NO -EXIT
         TRN       R1,R1           YES - NEGATE BYTE COUNT
         ZR        R2              CLEAR R2
         LW        R4,=X'000FFFFF' ADDRESS MASK
         LMW       R4,R1SAV        BUFFER ADDRESS
         STW       R4,R1SAV        SAVE IT
LOOP     LB        R6,*R1SAV,R2    MOVE DATA TO
         STB       R6,BUFF,R2      INTERMEDIATE BUFFER
         ADI       R2,1            BUMP BYTE POINTER
         BIB       R1,LOOP         LOOP AND BUMP BYTE COUNT
         LW        R1,BUFFTCW      SET UP TO PRINT FROM
*!!!!!!!!STW!!!!!!!R1,FCBLO+1W!!!!!INTERMEDIATE!BUFFER!!!!!!!!!!S880752
         ZR        R0              CLEAR OUT RECEIVER           S880752
         SLLD      R0,12           EXTRACT BYTE COUNT           S880752
         ZBR       R1,0            RESET BYTE INDICATOR         S880752
         SRL       R1,12           REPOSITION ADDR              S880752
         STW       R0,FCBLO+9W     STORE BUFFER LENGTH          S880752
         STW       R1,FCBLO+8W     AND BUFFER ADDR              S880752
OUT      LW        R2,R2SAV
         LW        R4,R4SAV
         LW        R6,R6SAV
         BU        *R0SAV          RETURN
TTORRET  DATAW     0               TTOR RETURN ADDRESS
R2SAV    DATAW     0               REGISTER
R4SAV    DATAW     0               SAVE
R6SAV    DATAW     0               AREA
         BOUND     2W
R0SAV    DATAW     0               RETURN ADDRESS
R1SAV    DATAW     0               PRINT TCW
BUFF     DATAD     0
SKIP     ANOP                                                   *JCB*
BLANKS   DATAW     C'        '     USED TO BLANK BUFF
         IFF       UNIXF,SKIP                                   *JCB*
BUFFTCW  GEN       12/8,20/B(BUFF)
SKIP     ANOP                                                   *JCB*
         TITLE     PB - 'PUBLISH' BINARY
************************************************************************
* PUBLISH BINARY DATA
* INPUT-R1=BASE ADR OF BINARY STREAM STACK
*
*        R6=LOADER FUNCTION CODE
*        R4=FUNCTION SUB-CODE FOR INFO RECORDS (X FOR DX0C)
*
************************************************************************
*
* (C) COPYRIGHT 1983 ENCORE COMPUTER CORPORATION
*     ALL RIGHTS RESERVED
*
         SPACE     1
         BOUND     1W
PB       STW       0,PBS0          SAVE RETURN ADR
         ANMW      R1,=X'0007FFFF' KEEP ONLY ADDR PART OF INPUT S880752
         TBM       BO,OPTION       IS BINARY OUTPUT REQUIRED
         BNS       PB1          YES-PROCESS OBJ. INFO.
         TBM       GO,OPTION       IS GO OPTION ON?
         BNS       *PBS0        NO-RETURN.
PB1      CI        6,X'D'          SEE IF EXPANDED LDR.FUNC.
         BNE       PB4             NO - OUTPUT STANDARD FUNCTION CODES
*        EXPANDED LOADER FUNCTION CODES
         LB        7,0,1           GET BYTE COUNT (HBBS)
         ABR       7,31            INCREMENT BY 1 (FOR CODE)
         STB       7,2,1           SAVE AS BYTE COUNT IN LDR DATA
         STB       7,PBNB          SAVE NO. OF BYTES BEING PASSED OUT
         STW       1,PBBA          SAVE BASE ADDRESS OF BYTES
         SLL       6,4             SHIFT FUNC.CODE
         LB        5,1,1           FETCH SUB-CODE
         CI        5,11            ! IS THIS A DEBUG ITEM
         BEQ       PB1.1           ! BRANCH IF DEBUG ITEM
         CI        5,12            IS THIS DATE/TIME OR PROD ID?   11006
         BEQ       PB1.01          YES - SET UP FLAG ENTRY         11006
         LB        5,4,1           GET SECTION NUMBER FROM BINARY STACK
         BZ        PB1.1           ZERO (DSECT) NO FLAG BITS SET
*!!!!!!!!SBR!!!!!!!6,29!!!!!!!!!!!!SET!CSECT!FLAG!(BIT!5!IN!LFC!EBAC-33B
         BU        PB1.1           READY TO OUTPUT
         SPACE
PB1.01   CEQU      $                                            ESCT-32
         ADI       7,3             ADD IN 3 BYTES FOR CONTROL      11006
*                                    INFO. 1 BYTE FOR CODE WAS     11006
*                                    ADDED IN PB1.                 11006
         STB       7,2,1           SAVE AS BYTE COUNT IN LDR DATA  11006
         STB       7,PBNB          SAVE NO. OF BYTES BEING OUTPUT  11006
*!!!!!!!!ORMB!!!!!!6,3B,1!!!!!!!!!!OR!IN!FLAG!FROM!BO!STACK!!!!!ETCM-32
*!!!!!!!!ZMB!!!!!!!3B,1!!!!!!!!!!!!CLEAR!BYTE!FOR!'CLEANLINESS'!ETCM-32
         ORR       R4,R6           PUT SUB-CODE INTO RECORD     ETCM-32
         BU        PB1.1           CONTINUE AS NORMAL EXPANDED     11006
         SPACE
PB4      LB        7,0,1           NO. OF BYTES BEING PASSED OUT
         STB       7,PBNB          NO. OF BYTES BEING PASSED OUT
         STW       1,PBBA          BASE ADR OF BYTES
         STB       6,PBNC          LOADER FUNC CODE
         ABM       7,PBNB          INCR BYTE COUNT TO INCL FUNC CODE BYT
         SRC       7,4             NO. OF BYTES LT JUSTIFIED
         SLLD      6,4             CONCATENATE FUNC CODE AND BYTE COUNT
PB1.1    STB       6,0,1           PUT IN FIRST BYTE
         LB        4,PPT           LENGTH OF BINARY RECORD
         BEQ       *PBS0        RETURN, DEVICE UNUSABLE FOR BO
         SUI       4,6             FOR CONTROL BYTES
         SUMB      4,PBLB          RECORD LGTH - NO. OF BYTES IN BUF NOW
         SUMB      4,PBNB          - NO. COMING IN = SPACE IN BUFFER
         BLT       PB3          WOULD OVERFLOW, DUMP STACK
* PACK THE LATEST STRING INTO THE STACK
PB2      LB        3,PBLB          POSITION IN STACK FOR NEXT BYTE
         LNB       2,PBNB          NEG NO. OF BYTES TO BE TRANSFERRED
PB2A     LB        5,0,1           FETCH BYTE OF DATA
         ABR       1,31            INCR READ POINTER
         ARMH      5,PBLC          CHECKSUM IT
         STB       5,PBLP,3        PUT IT IN BYTE STACK
         ABR       3,31            INCR STORE POINTER
         BIB       2,PB2A          LOOP TO GET ALL INPUT BYTES
         STB       3,PBLB          SAVE NUMBER OF BYTES IN STACK PBL
         BU        *PBS0
* DUMP BUFFER STACK ON BO DEVICE
PB3      LI        6,X'FF'         BINARY OUTPUT FUNCTION CODE
         BL        PBP             OUTPUT CURRENT BUFFER STACK ON BO
         LW        1,PBBA          RESTORE R1 TO BASE ADR OF STRING
         BU        PB2             GO LOAD BYTES INTO BUFFER
         SPACE     1
* FINISH BUFFER COMPUTATIONS AND OUTPUT, NO WAIT MODE
* R6 = BINARY OUTPUT FUNCTION CODE
         SPACE     1
PBP      STW       R0,PBPRET       SAVE RET ADDR
         TBM       BO,OPTION           BO OPTION?
         BNS       PB0          BO?
         TBM       GO,OPTION       NO
         BNS       PBPR         GO?
PB0      STB       6,PBLF          BO FUNC CODE INTO BUFFER
         LB        6,PPT
         BEQ       PBPR         ILLEGAL BO DEVICE-IGNORE OUTPUT
         ABM       15,PBSQ         INCR SEQUENCE NUMBER
         LH        5,PBSQ          SEQ NO.
         STH       5,PBLS          STORE SEQ NO. IN BUFFER
         TBM       BO,OPTION       IS BINARY OUTPUT REQUIRED
         BS        PBP1         NOT-REQUIRED-GO CHECK FOR 'GO'
PBPW     CEQU      $                                            ESCT-32
         IFT       UNIXF,SKIP                                   *JCB*
         CCALL     _write,BO.FD,=PBL,=RECSIZ  WRITE THE BO      *JCB*
         TRR       R0,R0           ANY ERRORS                   *JCB*
         BLT       BOER            EOF ON BO                    *JCB*
SKIP     ANOP                                                   *JCB*
         IFF       UNIXF,SKIP                                   *JCB*
         LA        1,FCBBO         BASE ADDRESS OF THE BO FILE CONTROL
*!!!!!!!!TBM!!!!!!!BOAD,FLAGS!!!!!!RM!IN!USE!FOR!BO?!!!!!!!!!!!!S880752
*!!!!!!!!BNS!!!!!!!PBP2!!!!!!!!!!!!BR!IF!NOT!!!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!BL!!!!!!!!RM.WRIT!!!!!!!!!OUTPUT!RECORD!TO!BO!DEVICE!!!S880752
*!!!!!!!!BU!!!!!!!!PBP3!!!!!!!!!!!!CONTINUE!!!!!!!!!!!!!!!!!!!!!S880752
*!PBP2!!!SVC!!!!!!!1,X'32'!!!!!!!!!WRITE!BO!USING!STD!I/O!!!!!!!S880752
*!PBP3!!!TBM!!!!!!!7,FCBBO+3W!!!!!!TEST!FOR!EOM!!!!!AS17!!!!!!!!S880752
         SVC       1,X'32'         WRITE BO USING STD I/O       S880752
         TBM       7,FCBBO+3W      TEST FOR EOM   AS17          S880752
         BS        BOER            EOF ON WRITE--ERROR AS16
SKIP     ANOP                                                   *JCB*
*
* CODE DELETED FOR REALLOCATION OF SBO AS16
PBP1     TBM       GO,OPTION
         BNS       PB5          IS GO OPTION ON?
         LA        R1,FCBGO        YES.
         SVC       1,X'32'         WRITE GO
         TBM       7,FCBGO+3W      TEST FOR EOM     AS17
         BS        GOER         ERROR IF EOF ON WRITE.
PB5      CEQU      $                                            ESCT-32
         LI        R2,-RECSIZ
         ZMW       RECSIZ+PBL,R2   CLEAR INPUT AREA.
         BIW       R2,$-1W
         ZMH       PBLC            CLEAR CHECKSUM
         ZMB       PBLB            CLEAR BYTE COUNT
PBPR     BU        *PBPRET         RETURN
         SPACE     1
PBPRET   DATAW     0               RETURN ADDR SAVE AREA
         TITLE     READ - READS INPUT FROM SI AND PRE
************************************************************************
*--------READ A SYMBOLIC INPUT RECORD
*--------FIRST PASS READ FROM INITIAL UNIT AND COPY ONTO THE SECOND
*--------PASS FILE IF USED. ALWAYS COMPRESS BEFORE STORING
*--------SECOND PASS READ BACK THE SECOND PASS FILE IF AVAILABLE
*--------CALLING SEQUENCE INPUT R3,0-11 = NUMBER OF BYTES TO READ
*                           R3,12-24 BASE ADR OF AREA TO RECEIVE IMAGE
*                           OUTPUT R7=0 FOR EOF, ELSE R7= LINE NUMBER
************************************************************************
         SPACE     2
         IFF       UNIXF,SKIP                                   *JCB*
READ     CEQU      $                                            ESCT-32
         STW       0,READS0
         STW       3,BARA          SAVE INPUT ARGUMENT
*!!!!!!!!STW!!!!!!!3,DCMPRS3!!!!!!!SET!INPUT!ARGUMENT!FOR!DCMPR!S880752
         LW        R7,=C'    '     GET SOME SPACES              S880752
         LA        R1,IN           ADDRESS OF IN BUFFER         S880752
         LI        R6,-20W         LENGTH OF IN BUFFER          S880752
         STW       R7,0W,R1        BLANK OUT IN BUFFER          S880752
         ADI       R1,1W           NEXT WORD                    S880752
         BIW       R6,$-2W                                      S880752
         TBM       7,PAS2          IS THIS PASS 1
         BS        $+2W         YES, PASS 1
         BU        READ4           GO READ SCRATCH IN.
         SPACE     2
*                  P A S S  1                                          *
         SPACE     2
READ0    CEQU      $                                            ESCT-32
         LB        6,*READPTR      DO WE HAVE A COSY RECORD TO FINISH
*
         BCF       EQ,READ2        YES
         LW        7,=C'    '      WORD OF SPACES.
         LW        1,IBUFA         GET INPUT BUFFER ADDRESS
         LI        6,-64W          SIZE OF INPUT BUFFER
         STW       7,0W,1          FILL WITH SPACES.
         ADI       R1,1W           NEXT WORD                    S880752
         BIW       6,$-2W          DO ALL OF BUFFER             S880752
*!!!!!!!!BIW!!!!!!!6,$-1W!!!!!!!!!!DO!ALL!OF!BUFFER!!!!!!!!!!!!!S880752
READ1    LW        1,FCBA          BASE ADDRESS OF THE SOURCE FCB
*!!!!!!!!LB!!!!!!!!R4,3B,R1!!!!!!!!!!!!!!!GET!LAST!CHAR!OF!LFC!!S880752
*!!!!!!!!CI!!!!!!!!R4,G'!'!!!!!!!!!IS!IT!SI?!!!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!BNE!!!!!!!READ1.1!!!!!!!!!BR!IF!'PRE'!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!TBM!!!!!!!SIAD,FLAGS!!!!!!IS!IT!RM!I/O!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!BU!!!!!!!!READ1.2!!!!!!!!!GO!TEST!IT!!!!!!!!!!!!!!!!!!!S880752
*!READ1.1!!!TBM!!!!PREAD,FLAGS!!!!!IS!IT!RM!I/O!!!!!!!!!!!!!!!!!S880752
*!READ1.2!!!BNS!!!!READ1.4!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!BL!!!!!!!!RM.READ!!!!!!!!!READ!RECORD!FROM!SOURCE!FILE!S880752
*!!!!!!!!BU!!!!!!!!READ1.5!!!!!!!!!CONTINUE!!!!!!!!!!!!!!!!!!!!!S880752
*!READ1.4!!!SVC!!!!1,X'31'!!!!!!!!!READ!USING!REG!I/O!!!!!!!!!!!S880752
*!READ1.5!!!ZR!!!!!7!!!!!!!!!!!!!!!DEFAULT!CASE!FOR!EOF!!!!!!!!!S880752
         SVC       1,X'31'         READ USING REG I/O           S880752
         ZR        R7              DEFAULT CASE FOR EOF         S880752
         TBM       6,3W,1          WAS RECORD AN EOF
         BS        *EOFA           YES, GO TO EOF PROCESSOR
         LB        4,*IBUFA        FIRST BYTE OF INPUT
         SBR       4,26           CONVERT A POSSIBLE 9 TO A B
         CI        4,X'BF'         IS INPUT COMPRESSED
         BCF       EQ,READ5        NO, PROCESS NORMAL INPUT
         BL        READCCS
         SPACE     1
* R3 CONTAINS QTY AND ADR OF RECEIVING AREA
         SPACE     1
         ZMB       *READPTR        INITIALIZE TO FIRST POSITION
READ2    LW        1,*READPTR      BASE ADR OF CMPR DATA AND POINTER
*
         BL        DCMPR
         BCT       1,READ1         IMAGE IN PROCESS
         STW       1,*READPTR      SAVE POINTER FOR NEXT READ
READ2A   CEQU      $                                            ESCT-32
         LW        2,BARA          FROM ADR - USER BUFFER
         STW       2,CMPRFR
*!!!!!!!!LW!!!!!!!!3,FCBSK+1W!!!!!!TO!ADR!-!SCRATCH!BUFFER!!!!!!S880752
         LW        R3,FCBSK+8W     GET TO ADDR OF BUFFER        S880752
         ANMW      R3,=X'000FFFFF' KEEP LOWER 20 BITS ONLY      S880752
         SBR       R3,12           FORCE ON BYTE INDICATOR      S880752
         LW        R7,FCBSK+9W     GET BUFFER LENGTH            S880752
         ANMW      R7,=X'00000FFF' KEEP ONLY BOTTOM 12 BITS     S880752
         SLL       R7,20           POSITION TO TOP OF REG       S880752
         ORR       R7,R3           FORM UP TCW                  S880752
         STW       3,CMPRTO        SET UP FOR COMPRESSION ROUTINE
         BL        CMPR
         BCF       1,READ3         BUFFER NOT FULL
         LI        7,X'BF'         INDICATE NON-LAST COSY RECORD
         BL        SKOUT           WRITE OUT SCRATCH FILE
         BL        CMPR            FINISH PROCESSING IMAGE
READ3    ABM       31,LICE         INCREMENT LINE COUNTER
         LW        7,LICE          GET THE BINARY LINE COUNT
READ8    BU        *READS0          RETURN                   AS12
         SPACE     1
* PASS 2 WITH SCRATCH
         SPACE     1
READ4    LB        6,READSKP       DO WE HAVE A COSY RECORD TO FINISH
         BCF       EQ,READ4B       YES
READ4A   LA        1,FCBSK         BASE ADDRESS OF THE SK FILE CONTROL
*!!!!!!!!TBM!!!!!!!UT1AD,FLAGS!!!!!USING!RM!!!!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!BNS!!!!!!!READ4A1!!!!!!!!!USE!REG!I/O!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!BL!!!!!!!!RM.READ!!!!!!!!!READ!UT1!FILE!!!!!!!!!!!!!!!!S880752
*!!!!!!!!BU!!!!!!!!READ4A2!!!!!!!!!CONT!!!!!!!!!!!!!!!!!!!!!!!!!S880752
*!READ4A1!!!SVC!!!!1,X'31'!!!!!!!!!READ!UT1!WITH!REG!I/O!!!!!!!!S880752
*!READ4A2!!!TBM!!!!6,FCBSK+3W!!!!!!WAS!RECORD!AN!EOF!!!!!!!!!!!!S880752
         SVC       1,X'31'         READ UT1 WITH REG I/O        S880752
         TBM       6,FCBSK+3W      WAS RECORD AN EOF?           S880752
         BS        *READS0      YES, RETURN
         BL        READCCS
         ZMB       READSKP         ZERO READ POINTER
READ4B   LW        1,READSKP
         BL        DCMPR
         BCT       1,READ4A        IMAGE IN PROCESS
         STW       1,READSKP       SAVE POINTER
         BU        READ3
         SPACE     1
* NORMAL INPUT
         SPACE     1
*!READ5!!!LW!!!!!!!2,1W,1!!!!!!!!!!FROM!ADR!-!SOURCE!BUFFER!!!!!S880752
READ5    LW        2,8W,1          FROM ADR - SOURCE BUFFER     S880752
         LW        3,BARA          TO ADR - USER BUFFER
         ANMW      3,=X'0007FFFF'  USE JUST ADDR PART           S880752
         SPACE     1
* MOVE DATA FROM ADDRESS SPECIFIED IN R2 TO ADDRESS SPECIFIED IN R3
         SPACE     1
         LI        1,-80           81 OR MORE SO WE LIMIT TRANSFER
READ6    LB        6,0,2           GET ONE BYTE FORM INPUT BUFFER
         STB       6,0,3           PLACE IT INTO USERS BUFFER
         ABR       2,31            ADVANCE READ POINTER
         ABR       3,31            ADVANCE STORE POINTER
         BIB       1,READ6         TRANSFER ALL THE BYTES
         BU        READ2A          BUFFER FULL
*
*        EOF ON PRE...REWIND PRE AND START READING FROM SI (R1 POINTS
*        TO PRE FILE CONTROL BLOCK)
*
READ7    CEQU      $                                            ESCT-32
*!READ7!!!TBM!!!!!!PREAD,FLAGS!!!!!IS!PRE!USING!RM!!!!!!!!!!!!!!S880752
*!!!!!!!!BNS!!!!!!!READ7.1!!!!!!!!!BR!IF!NOT!!!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!BL!!!!!!!!RM.RWND!!!!!!!!!REWIND!PRE!!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!BU!!!!!!!!READ7.2!!!!!!!!!CONTINUE!!!!!!!!!!!!!!!!!!!!!S880752
*!READ7.1!!!SVC!!!!1,X'37'!!!!!!!!!REWIND!PRE!!!!!!!!!!!!!!!!!!!S880752
*!READ7.2!!!LA!!!!!R1,FCBSI!!!!!!!!ADDR!OF!SI!FCB!!!!!!!!!!!!!!!S880752
         SVC       1,X'37'         REWIND PRE                   S880752
         LA        R1,FCBSI        ADDR OF SI FCB               S880752
         STW       R1,FCBA         READ SOURCE FROM SI
*!!!!!!!!LEA!!!!!!!R7,READ8!!!!!!!!ADDRESS!OF!SI!EOF!PROCESSOR!!S880752
         LA        R7,READ8        ADDR OF SI EOF PROC. (AS12)  S880752
         STW       R7,EOFA         SET AS SOURCE EOF PROCESSOR
         LA        R7,READSIP      ADDR OF SI RECORD PTR
         STW       R7,READPTR      SET AS SOURCE RECORD PTR
         LA        R7,IBUF         ADDR OF SI INPUT BUFFER
         STW       R7,IBUFA        SET AS SOURCE INPUT BUFFER
         SBM       1,PREFLG        INDICATE EOF ON PRE
         BU        READ0           READ RECORD FROM SI
SKIP     ANOP                                                   *JCB*
         IFT       UNIXF,SKIP                                   *JCB*
READ     CEQU      $                                            *JCB*
         STW       0,READS0                                     *JCB*
         STW       3,BARA          SAVE INPUT ARGUMENT          *JCB*
         LW        R7,=C'    '     GET SOME SPACES              *JCB*
         LA        R1,IN           ADDRESS OF IN BUFFER         *JCB*
         LI        R6,-20W         LENGTH OF IN BUFFER          *JCB*
         STW       R7,0W,R1        BLANK OUT IN BUFFER          *JCB*
         ADI       R1,1W           NEXT WORD                    *JCB*
         BIW       R6,$-2W                                      *JCB*
         TRR       R3,R6           GET USER'S TCW               *JCB*
         SRLD      R6,20           GET BYTE COUNT IN R6         *JCB*
         ABR       R6,31           ADD BYTE FOR NEW LINE CHAR   *JCB*
         SRL       R7,12           RIGHT JUSTIFY BUF ADDR       *JCB*
         ZBR       R7,12           CLEAR BYTE ADDRESSING MODE   *JCB*
READX    TBM       7,PAS2          IS THIS PASS 1               *JCB*
         BS        READ1           GO READ STD INPUT IN         *JCB*
         SPACE     2                                            *JCB*
* PASS 2 WITH SCRATCH                                           *JCB*
         TRR       R3,R5           SAVE BASE ADDRESS POINTER    *JCB*
         CCALL     _readraw,SK.FD,R7.,R6. GET INPUT RECORD      *JCB*
         TRR       R7,R1           POINT TO THE CHARACTER       *JCB*
         TRR       R5,R3           RESTORE POINTER              *JCB*
         TRR       R0,R0           TEST FOR EOF                 *JCB*
         BGT       READ4           PROCESS THE CHAR             *JCB*
         ZR        R7              SET EOF FOUND                *JCB*
         BU        *READS0         RETURN TO CALLER             *JCB*
READ4    ADR       R0,R1           BUFF START + COUNT           *JCB*
         LI        R7,NEWLINE      GET LF CHAR                  *JCB*
         STB       R7,EOL.J        PUT AT END OF LINE           *JCB*
         BU        READ3           GO RETURN TO CALLER          *JCB*
*                  P A S S  1                                   *JCB*
         SPACE     2                                            *JCB*
READ1    CCALL     _read1ln,SI.FD,=IBUF,=120  GET INPUT RECORD  *JCB*
         TRR       R7,R1           POINT TO THE CHARACTER       *JCB*
         TRR       R0,R0           IS IT EOF                    *JCB*
         BGT       READ0           NO, PROCESS CHARACTER        *JCB*
         CCALL     _close,SI.FD    CLOSE THE INPUT FILE         *JCB*
         TRR       R7,R5           SAVE BUFFER ADDRESS          *JCB*
READ.EOF CEQU      $                                            *JCB*
         ZR        R7              ASSUME EOF STATUS            *JCB*
         LW        R1,ARGC         GET REMAINING COUNT FROM ARG *JCB*
         SUI       R1,1            DECR. ARGC                   *JCB*
         BLE       READ8           IF, NO MORE, RET EOF STATUS  *JCB*
         STW       R1,ARGC         ARGC--                       *JCB*
         LW        R1,ARGV         GET NEXT ARG VECTOR          *JCB*
         ADI       R1,1W           ARGV++                       *JCB*
         STW       R1,ARGV         SAVE IT                      *JCB*
         LW        R1,0,R1         GET FILENAME                 *JCB*
         STW       R1,FILEPTR      SAVE IT                      *JCB*
         CCALL     _open,FILEPTR,=0  OPEN NEXT FILE IN LIST     *JCB*
         TRR       R0,R0           TEST FOR ERROR               *JCB*
         BLT       READ.EOF        IF SO, SKIP THIS FILE        *JCB*
         STW       R0,SI.FD        IF OKAY, SAVE FILE DESCRIPTOR*JCB*
         TRR       R5,R7           RESTORE BUFFER ADDRESS       *JCB*
         BU        READ1           GO READ THE FILE             *JCB*
*                                                               *JCB*
READ0    CEQU      $               PROCESS INPUT LINE           *JCB*
         TRN       R0,R5           R5 HAS ACTUAL READ COUNT     *JCB*
         TRN       R6,R6           R6 HAS REQUESTED COUNT       *JCB*
         LA        R2,IBUF         WHERE DATA IS                *JCB*
READ0.1  CEQU      $                                            *JCB*
         LB        R0,0,R2         GET THE CHARACTER            *JCB*
         CI        R0,NEWLINE      IS IT THE END?               *JCB*
         BNE       READ0.2         NO, GET THE NEXT CHAR        *JCB*
         LI        R0,G' '         ELSE, GET A BLANK            *JCB*
         STB       R0,0,R1         CHANGE LAST CHAR TO BLANK    *JCB*
         ABR       R1,31           BUMP POINTER                 *JCB*
         BIB       R6,$-2W         PAD WITH BLANKS              *JCB*
         BU        READ5           PROCESS THE RECORD           *JCB*
*                                                               *JCB*
READ0.2  CEQU      $                                            *JCB*
         CI        R0,TABCHAR      IS IT A TAB                  *JCB*
         BNE       READ0.3         NO, NORMAL CHARACTER         *JCB*
         ABR       R2,31           BUMP INPUT POINTER           *JCB*
         LI        R0,G' '         CHANGE LAST CHAR TO BLANK    *JCB*
         IFT       CAID,SKIPC                                   *CAID*
         LB        R3,IBUF         GET 1ST CHAR OF LINE         *CAID*
         CI        R3,G'*'         IS IT A COMMENT              *CAID*
         BEQ       READ0.2X        YES, USE UNIX TABS           *CAID*
         TBM       SUDO,HHBITS     PROCESSING PSEUDO-OP         *CAID*
         BS        READ0.2X        YES, USE UNIX TABS           *CAID*
         CI        R3,G' '         IS COL 1 BLANK               *CAID*
         BNE       READ0.2A        NO, USE MPX TABS             *CAID*
         LB        R3,IBUF+1B      GET 2ND CHAR OF LINE         *CAID*
         CI        R3,G'.'         IS IT A "."                  *CAID*
         BNE       READ0.2A        NO, USE MPX TABS             *CAID*
READ0.2X LI        R3,-UTABCNT     SET UP UNIX TAB LOOP         *CAID*
         STB       R0,0,R1         PAD BLANKS                   *CAID*
         ABR       R1,31           PUSH CURSOR                  *CAID*
READ0.2Y CAMH      R6,UTABLIST+UTABCNT,R3 CHK FOR MATCHING TAB  *CAID*
         BEQ       READ0.1         IF MATCH THEN OKAY TO READ   *CAID*
         BIH       R3,READ0.2Y     ELSE, CHECK NEXT TAB         *CAID*
         BIB       R6,READ0.2X     TRY AGAIN                    *CAID*
         BU        READ5           STOP WHEN LINE IS FULL       *CAID*
SKIPC    ANOP                                                   *CAID*
READ0.2A LI        R3,-TABCNT      ELSE, SET UP TAB LOOP        *JCB*
         STB       R0,0,R1         ELSE PAD BLANKS              *JCB*
         ABR       R1,31           PUSH CURSOR                  *JCB*
READ0.2B CAMH      R6,TABLIST+TABCNT,R3 CHECK FOR MATCHING TAB  *JCB*
         BEQ       READ0.1         IF MATCH THEN OKAY TO READ   *JCB*
         BIH       R3,READ0.2B     ELSE, CHECK NEXT TAB         *JCB*
         BIB       R6,READ0.2A     TRY AGAIN                    *JCB*
         BU        READ5           STOP WHEN LINE IS FULL       *JCB*
*                                                               *JCB*
READ0.3  CEQU      $                                            *JCB*
         STB       R0,0,R1         PUT LAST CHAR IN BUFFER      *JCB*
         ABR       R1,31           BUMP OUTPUT POINTER          *JCB*
         ABR       R2,31           BUMP INPUT POINTER           *JCB*
         BIB       R6,READ0.1      GET NEXT CHAR                *JCB*
*                                                               *JCB*
READ5    CEQU      $                                            *JCB*
         LW        R6,BARA         GET USER'S TCW               *JCB*
         SRLD      R6,20           GET BYTE COUNT IN R6         *JCB*
         SRL       R7,12           RIGHT JUSTIFY BUF ADDR       *JCB*
         ZBR       R7,12           CLEAR BYTE ADDRESSING MODE   *JCB*
         TRR       R7,R2           GET BUFFER ADDR              *JCB*
         ADR       R6,R2           BUFFER END + 1B              *JCB*
         SUI       R2,1            LAST CHAR                    *JCB*
READ5.0  LB        R0,0B,R2        GET A CHAR                   *JCB*
         CI        R0,G' '         SEE IF SPACE                 *JCB*
         BNE       READ5.1         BR IF NOT                    *JCB*
         SUI       R2,1            BACK UP DATA POINTER         *JCB*
         SUI       R6,1            BACK UP CNT                  *JCB*
         CI        R6,1            SEE IF LAST CHAR             *JCB*
         BGT       READ5.0         LOOP TIL DONE                *JCB*
READ5.1  STW       R6,SKCNT        PUT IT AWAY                  *JCB*
         CCALL     _writraw,SK.FD,READSKPC,SKCNT                *JCB*
         TRR       R0,R0           TEST FOR EOM                 *JCB*
         BLE       SKER            ERROR IF EOF ON WRITE        *JCB*
READ3    ABM       31,LICE         INCREMENT LINE COUNTER       *JCB*
         LI        R0,NEWLINE      GET LF CHAR                  *JCB*
         STB       R0,EOL.J        SET STOP CHAR AT END OF DATA *JCB*
         LW        7,LICE          GET THE BINARY LINE COUNT    *JCB*
READ8    BU        *READS0          RETURN                      *JCB*
         SPACE     2                                            *JCB*
TABLIST  DATAH     10-81,20-81,36-81,48-81,72-81                *JCB*
TABCNT   EQU       $-TABLIST                                    *JCB*
         IFT       CAID,SKIPC                                   *CAID*
UTABLIST DATAH     4-81,8-81,12-81,16-81,20-81,24-81,28-81      *CAID*
         DATAH     32-81,36-81,40-81,44-81,48-81,52-81,56-81    *CAID*
         DATAH     60-81,64-81,68-81,72-81                      *CAID*
UTABCNT  EQU       $-UTABLIST                                   *CAID*
SKIPC    ANOP                                                   *CAID*
SKIP     ANOP                                                   *JCB*
         IFF       UNIXF,SKIP                                   *JCB*
         TITLE     CMPR - COMPRESS
************************************************************************
* INPUT---CMPRFR B0-11=NUMBER OF BYTES OF DATA TO COMPRESS
*                B12-31=BASE ADR OF DATA TO BE COMPRESSED
* CALLING SEQUENCE
*        STW       R,CMPRFR        INPUT PARAMETER FOR CMPR
*        STW       R,CMPRTO        INPUT PARAMETER FOR CMPR
*        BL        CMPR
*        BCF       1,CONTINUE      CMPR NEED BE CALLED ONLY IF
*                                  CC NOT SET
*        BL        PROCESS         THE BUFFER IS FULL AND MUST BE PROCES
*        BL        CMPR            CALL CMPR TO FINISH IMAGE
* OUTPUT--CC BIT 1 IS SET IF THE OUTPUT BUFFER IS FULL AND AN IMAGE IS I
*         THE USER MUST PROCESS THE BUFFER AND CALL CMPR TO FINISH THE I
************************************************************************
         SPACE     1
CMPR     CEQU      $                                            ESCT-32
*!CMPR!!!LW!!!!!!!!3,CMPRTO!!!!!!!!BASE!ADR!OF!OUTPUT!BUFFER!!!!S880752
         LW        R4,=X'0007FFFF' SET UP 19BIT ADDR MASK       S880752
         LMW       R3,CMPRTO       NOW GET ADDR OF OUTPUT BUFF  S880752
         ZBM       7,IMIP          CLEAR THE IMAGE IN PROGRESS FLAG
         BS        CMPRIIP      AN IMAGE WAS IN PROCESS PREVIOUSLY
* SAVE LENGTH OF OUTPUT BUFFER FOR EOR CHECK
         LH        6,CMPRTO
         SRL       6,4
         SUI       6,6
         STB       6,CMPRLOB
* SAVE LENGTH OF INPUT BUFFER FOR EOI CHECK
         LH        6,CMPRFR        QTY + 4 BITS OF GRABAGE
         SRL       6,4             ELIMINATE GARBAGE
         STB       6,CMPRLIB
         ZMB       CMPRQTYR        CLEAR QTY READ
         ZMB       CMPRSPC         ZERO SPACE COUNT
* SET R1 AS STORE PRINTER
CMPR1    TRR       3,1             SET R1 TO BASE OF OUTPUT BUFFER
         ADMB      1,1,3           ADD BYTE COUNT TO GET STORE POINTER
         ADI       1,6             MOVE PAST FIXED FORMAT DATA
* SET R2 AS READ POINTER
*!!!!!!!!LW!!!!!!!!2,CMPRFR!!!!!!!!SET!R2!TO!BASE!OF!INPUT!BUFFES880752
         LMW       2,CMPRFR        SET R2 TO BASE OF INP BUFF   S880752
         ADMB      2,CMPRQTYR      ADD QTY READ TO GET READ POINTER
* START A NEW STRING
         ZMB       CMPRSTC         ZERO STRING COUNT
* CHECK FOR AT LEAST 3 BYTES LEFT IN OUTPUT BUFFER. IF NOT DON'T START
* A NEW STRING
CMPR2    LB        7,1,3           BYTE COUNT
         ADI       7,3             ACCOUNT FOR WASTE AT REAR OF BUFFER
         CAMB      7,CMPRLOB       COMPARE TO LENGTH OF BUFFER
         BGT       CMPR6A       THERE IS NOT ENOUGH ROOM (EOR)
CMPR3    LB        6,CMPRQTYR      QUANTITY READ
         SUMB      6,CMPRLIB       - QTY TO BE READ
         BGE       CMPR5        ALL OF INPUT READ
         LB        6,0,2           GET BYTE OF INPUT
         ABM       7,CMPRQTYR      INCR QTY READ
         ABR       2,31            INCR READ POINTER
         CI        6,G' '          WAS A SPACE READ
         BEQ       CMPR4        SPACE FOUND
         LB        7,CMPRSPC       SPACE COUNT
         STB       7,0,1           STORE IT IN TO BUFFER
         ARMH      7,2,3           CHECKSUM IT
         LI        7,2             INCREMENT TO SKIP SPACE FOR ST CT
         ARMB      7,1,3           INCREMENT BYTE COUNT BY 2
         ABR       1,30            INCR STORE POINTER BY 2
         ZMB       CMPRTSPC        ZERO TRAILING SPACE COUNT
         BU        CMPR9           GO PROCESS BYTE
* LEADING SPACE FOUND. HAVE WE READ THE LAST BYTE OF INPUT
CMPR4    LB        6,CMPRQTYR      QUANTITY READ
         SUMB      6,CMPRLIB       SUBTRACT NUMBER OF BYTES TO READ
         BGE       CMPR5        END OF INPUT
         ABM       7,CMPRSPC       INCR SPACE COUNT
         BU        CMPR3
* END OF INPUT
CMPR4A   LNB       2,CMPRSTC       NEG STRING COUNT
         TRN       2,4             STRING CONT
         ADR       1,2             STORE POINTER - STRING COUNT
         SUI       2,1             -1=STORE LOC
         STB       4,0,2           STORE STRING COUNT
         ARMH      4,2,3           CHECKSUM IT
CMPR5    LI        6,X'FF'         END OF COSY INDICATOR
         STB       6,0,1           STORE IT IN BUFFER
         ARMH      6,2,3           CHECKSUM IT
         ABM       7,1,3           INCR BYTE COUNT
         ZMB       IMIP            CLEAR IMAGE IN PROCESS IND
         ZBR       0,1             MAKE SURE NO BIT IS ON. TNX WALFISH
         TRSW      0               RETURN
* END OF OUTPUT BUFFER
CMPR6    LB        2,CMPRSTC       STRING COUNT
         SUR       2,1             STORE POINT - STRING COUNT
         SUI       1,1             -1 = STORE LOC FOR STRING COUNT
         STB       2,0,1           STORE STRING COUNT
         ARMH      2,2,3           CHECKSUM IT
CMPR6A   SBM       7,IMIP          SET IMAGE IN PROCESS INDICATOR
         ABM       7,5,3           INCR SEQUENCE NUMBER
         SBR       0,1             SET EOR IND FOR USER
         TRSW      0               RETURN
* STRING PROCESSING
CMPR7    LB        6,CMPRQTYR      QTY READ
         SUMB      6,CMPRLIB       QTY REQD TO READ
         BGE       CMPR4A       END OF INPUT
         LB        6,0,2           FETCH BYTE OF INPUT
         ABM       7,CMPRQTYR      INCR QTY READ
         ABR       2,31            INCR READ POINTER
         CI        6,G' '          IS IT A SPACE
         BEQ       CMPR10       SPACE FOUND IN STRING
         LNB       7,CMPRTSPC      FETCH TRAILING SPACE COUNT
         BEQ       CMPR9        SPACE COUNT EQ 0
         LI        5,G' '          SPACE
CMPR8    STB       5,0,1           SPACE TO OUTPUT BUFFER
         ARMH      5,2,3           CHECKSUM IT
         ABM       7,1,3           INCR BYTE COUNT
         ABM       7,CMPRSTC       INCR STRING COUNT
         ABR       1,31            INCR STORE POINTER
         ABR       7,31            INCR NEGATIVE LOOP COUNT
         BCF       EQ,CMPR8        LOOP TO FILL IN SPACES
         ZMB       CMPRTSPC        ZERO TRAILING SPACE COUNT (ALL CLEAR)
CMPR9    STB       6,0,1           STORE BYTE IN BUFFER
         ARMH      6,2,3           CHECKSUM IT
         ABM       7,1,3           INCR BYTE COUNT
         ABR       1,31            INCR STORE POINTER
         ABM       7,CMPRSTC       INCR STRING COUNT
* CHECK FOR END OF OUTPUT BUFFER
         LB        7,1,3           BYTE COUNT
         CAMB      7,CMPRLOB       IS BYTE COUNT EQ(BUF LENGTH -6)
         BGE       CMPR6        EOR
         BU        CMPR7           NOT END OF OUTPUT BUFFER
* SPACE FOUND IN STRING
CMPR10   ABM       7,CMPRTSPC      INCR TRAILING SPACE COUNT
         LB        7,CMPRTSPC      TRAILING SPACE COUNT
         CI        7,3
         BLT       CMPR11       SPACE COUNT LESS THAN 3
* IF SPACE COUNT REACHES 3 WE WILL CLOSE OUT STRING AND START A NEW ONE
         TRR       2,4             SAVE READ POINTER
         TRR       1,5
         LB        2,CMPRSTC       GET STRING COUNT
         SUR       2,1             STORE POINT-STRING COUNT
         SUI       1,1             -1 EQ STORE LOC FOR STRING COUNT
         STB       2,0,1           STORE STRING COUNT
         ARMH      2,2,3           CHECKSUM IT
         TRR       4,2             RESTORE READ POINTER
         TRR       5,1
         ZMB       CMPRSTC         ZERO STRING COUNT
* TRAILING SPACE LOC AND LEADING SPACE LOC ARE SAME SO LEADING SPACE
* COUNT IS SET TO 3
         BU        CMPR2           START NEW STRING
* SPACE IN STRING BUT LESS THAN 3 SPACES
CMPR11   XCR       7,2             SAVE READ POINT. TRAIL SP CT IN R2
         LB        6,1,3           BYTE COUNT
         ADMB      6,CMPRS1,2      ACCOUNT FOR WASTE AT END OF BUFFER
         XCR       7,2             RESTORE READ POINTER
         CAMB      6,CMPRLOB       COMPARE TO LENGTH OF BUFFER
         BGT       CMPR6        THERE IS NOT ENOUGH ROOM
         BU        CMPR7
* IMAGE IN PROCESS SETUP
CMPRIIP  ZMH       2,3             ZERO CHECKSUM (R3 = BASE OF TO BUF)
         ZMB       1,3             ZERO BYTE COUNT
         BU        CMPR1
         TITLE     DCMPR - DECOMPRESS
* DE-COMPRESS ONE IMAGE
* INPUT -R1,B0-7   NUMBER OF BYTES OF RECORD ALREADY PROCESSED
*           B12-31 BASE ADR OF COMPRESSED DATA
*        R3,B0-11  LENGTH OF RECEIVING AREA IN BYTES
*          B12-31  BASE ADR OF RECEIVING AREA
*! DCMPRS3 IS REMOVED AS A PARAMETER, VALUE SET LOCALLY FROM R3 S880752
*!!!!!!!!DCMPRS3!!!B0-11=LGTH!OF!RECEIVING!AREA!IN!BYTES!!!!!!!!S880752
*!!!!!!!!!!!!!!!!!!B12-31=BASE!ADDRESS!FO!RECEIVENG!AREA!!!!!!!!S880752
*
* OUTPUT-R0,B1 = 1 COMPRESSED INPUT EXHAUSTED WITH IMAGE IN PROCESS
*        R1,B0-7   NUMBER OF BYTES OF RECORD ALREADY PROCESSED
*        R1,B12-31 BASE ADR OF COMPRSSED DATA
         SPACE     1
* SET UP READ POINT
*!DCMPR!!!LW!!!!!!!4,=X'FF000000'!!BYTE!MASK!!!!!!!!!!!!!!!!!!!!S880752
DCMPR    CEQU      $                                            ESCT-32
         STW       R3,DCMPRS3      SAVE RECEIVING BUFFER DATA   S880752
         LW        R4,=X'FF000000' BYTE MASK                    S880752
         TRRM      1,2             BYTES PROCESSED
         SLC       2,8             RT JUSTIFIED
*!!!!!!!!LW!!!!!!!!4,=X'000FFFFF'!!ADR!MASK!!!!!!!!!!!!!!!!!!!!!S880752
         LW        R4,=X'0007FFFF' ADR MASK FOR 19 BIT ADDR'S   S880752
         TRRM      R3,R3           KEEP ONLY THE ADDRESS PART   S880752
         ADRM      1,2             BASE ADR + BYTES DONE = READ POINT-6
* SET UP END OF RECORD ADDRESS
         LB        5,1,1           NUMBER OF BYTES IN RECORD
         TRRM      1,6             BASE ADR OF DATA
         ADR       6,5             BASE ADR + NO. OF BYTES = END ADR +1
         STW       5,EORA
         CAR       5,2             CHECK IF WE ARE ALREADY AT THE EOR
         BGE       DCMPR4B      EOR HAS OCCURRED AT SAME TIME AS EOI
* SPACE PROCESSOR
DCMPR1   LB        5,6,2           BYTE OF DATA - NUMBER OF SPACES OR EO
         ABR       2,31            INCR READ ADDRESS
         TRR       5,5             SET CC BITS
         BEQ       DCMPR2       NO SPACES TO FILL IN
         CI        5,X'FF'         IS IT EOI
         BEQ       DCMPR4       YES, EOI
         LI        6,G' '          SPACE CODE
         TRN       5,5             SET LOOP COUNTER
         STB       6,0,3           PUT SPACE IN RECEIVING AREA
         ABR       3,31            INCR STORE ADR
         BIB       5,$-2W          LOOP TO STORE REQD NO. OF SPACES
DCMPR2   CAMW      2,EORA          IS IT EOR
         BGE       DCMPR4B      YES, EOR
* STRING PROCESSING
         LNB       5,6,2           NEGATIVE STRING COUNT
         ABR       2,31            INCR READ ADR
DCMPR3A  CAMW      2,EORA          EOR
         BGE       DCMPR4B      YES, EOR
         LB        6,6,2           LOAD BYTE OF STRING
         STB       6,0,3           STORE IT
         ABR       3,31            INCR STORE ADR
         ABR       2,31            INCR READ ADR
         BIB       5,DCMPR3A       LOOP TO STORE ENTIRE STRING
         CAMW      2,EORA          EOR ?
         BGE       DCMPR4B
         BU        DCMPR1          GO PROCESS SPACE COUNT OR EOI
* EOI
* FILL USER AREA WITH SPACES
DCMPR4   LMW       5,DCMPRS3       BASE ADR OF RECEIVING AREA
         LH        6,DCMPRS3       LGTH OF REC AREA + 4 BITS OF GARBAGE
         SRL       6,4             DUMP GARBAGE
         ADR       5,6             BASE ADR + LGTH = END ADR +1
         TRRM      3,7             NEXT STORE LOCATION
         SUR       7,6             (END ADR+1)-(NEXT STR LOC)=NUMB OF SP
         TRN       6,6             NEGATIVE NUMBER OF SPACES
         BGE       DCMPR4A      NO SPACES REQD
         LI        7,G' '          SPACE CODE
         STB       7,0,3           TO REC AREA
         ABR       3,31            INCR STORE ADR
         BIB       6,$-2W          LOOP TO FILL REC AREA
         CAMW      2,EORA          EOR
         BGE       DCMPR4C      YES, EOI AND EOR
DCMPR4A  TRRM      1,1             BASE ADR OF CMPR DATA
         SUR       1,2             NEXT ADR - BASE ADR =NUMBER PROCESSED
         SRC       2,8             LEFT JUSTIFY NUMBER DONE
         ORR       2,1             NUMBER DONE AND BASE ADR INTO R1
         TRSW      0               RETURN
* EOR
DCMPR4B  SBR       0,1             REQUEST MORE DATA
* EOR AND EOI
DCMPR4C  TRRM      1,1             ZERO BYTES DONE
         TRSW      0               RETURN
         SPACE     1
* COMPUTE AND CHECK CHECKSUM FOR COSY RECORD
* INPUT R1 = BASE ADR OF FCB
         SPACE     1
READCCS  ZMH       READCKSM        INITIALIZE CHECKSUM
*!!!!!!!!LW!!!!!!!!2,1W,1!!!!!!!!!!ADR!OF!COMPRESSED!DATA!!!!!!!S880752
         LW        R2,8W,X1        GET ADDR OF COMPRESSED DATA  S880752
         TRR       2,1             SAVE BASE ADR OF CMPR DATA
         LNB       6,1,2           NEG NUMBER OF BYTES
         BEQ       CKSMERMB     BETTER NOT HAVE ZERO BYTES IN RECORD
         LB        7,6,2           BYTE OF DATA (SKIPPING UN-CKSM DATA)
         ABR       2,31            INCR READ ADDRESS
         ARMH      7,READCKSM      CHECKSUM IT
         BIB       6,$-3W          LOOP TO COMPUTE CHECKSUM
         LH        5,2,1           CHECKSUM FROM INPUT DATA
         CAMH      5,READCKSM      COMPARE IT TO COMPUTED CHECKSUM
         BEQ       READCCSR     CHECKSUM OK
CKSMERMB BU        CKER
READCCSR TRSW      0               RETURN
         SPACE     1
* WRITE SCRATCH BUFFER OUT ON SCRATCH FILE
         SPACE     1
*
* (C) COPYRIGHT 1983 ENCORE COMPUTER CORPORATION
*     ALL RIGHTS RESERVED
*
SKOUT    STW       R0,SKRET        SAVE RETURN.
         STB       7,SBUF          SAVE THE FLAG BYTE IN THE RECORD
         LA        1,FCBSK         BASE ADDRESS OF THE SK FILE CONTROL
*!!!!!!!!TBM!!!!!!!UT1AD,FLAGS!!!!!IS!UT1!USING!RM!!!!!!!!!!!!!!S880752
*!!!!!!!!BNS!!!!!!!SKOUT.1!!!!!!!!!BR!IF!NOT!!!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!BL!!!!!!!!RM.WRIT!!!!!!!!!WRITE!OUT!SCRATCH!BUFFER!UT1!S880752
*!!!!!!!!BU!!!!!!!!SKOUT.2!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!S880752
*!SKOUT.1!!!SVC!!!!1,X'32'!!!!!!!!!WRITE!UT1!WITH!REG!I/O!!!!!!!S880752
*!SKOUT.2!!!TBM!!!!7,FCBSK+3W!!!!!!TEST!FOR!EOM!!!!!AS17!!!!!!!!S880752
         SVC       1,X'32'         WRITE UT1 WITH REG I/O       S880752
         TBM       7,FCBSK+3W      TEST FOR EOM    AS17         S880752
         BS        SKER         ERROR IF EOF ON WRITE.
         TBM       CMDK,OPTION
         BNS       *SKRET       CMDK?
         LA        R1,FCBCS
         SVC       1,X'32'         WRITE CS
         TBM       7,FCBCS+3W      CHECK FOR EOM.   AS17
         BCT       SET,CSER
         BU        *SKRET
         SPACE     2
SKRET    RES       1W
SKIP     ANOP                                                   *JCB*
         TITLE     ABORT ROUTINES
************************************************************************
*                                                                      *
*                  ABORT CODE ROUTINES                                 *
*                                                                      *
************************************************************************
         SPACE     3
GOER     LW        R5,AS01         ABORT CODE TO R5.
         BU        ABRTM1
         SPACE     2
BOER     LW        R5,AS02         ABORT CODE TO R5.
         BU        ABRTM1
         SPACE     2
LOER     LW        R5,AS03         ABORT CODE TO R5.
         BU        ABRTM1
         SPACE     2
SKER     LW        R5,AS04         ABORT CODE TO R5.
         BU        ABRTM1
         SPACE     2
IOERBO   LW        R5,AS07         ABORT CODE.
         TBM       2,3W,1          BLOCKING ERROR FLAG
         BNS       $+2W         BRANCH IF NOT SET-I/O ERROR
         LW        5,AS18          ABORT CODE
         BU        ABRTM1
         SPACE     2
IOERGO   LW        R5,AS08         ABORT CODE.
         TBM       2,3W,1          BLOCKING ERROR FLAG
         BNS       $+2W         BRANCH IF NOT SET-I/O ERROR
         LW        5,AS19          ABORT CODE
         BU        ABRTM1
         SPACE     2
IOERLO   LW        R5,AS09         ABORT CODE.
         TBM       2,3W,1          BLOCKING ERROR FLAG
         BNS       $+2W         BRANCH IF NOT SET-I/O ERROR
         LW        5,AS20          ABORT CODE
         BU        ABRTM1
         SPACE     2
         BOUND     1W
IOERPR   LW        R5,AS32         ABORT CODE
         TBM       2,3W,R1         BLOCKING ERROR FLAG
         BNS       $+2W            BRANCH IF NOT SET - I/O ERR
         LW        R5,AS33         ABORT CODE
         BU        ABRTM1
         SPACE     2
         BOUND     1W
*        MOVED PRE ERROR PROCESSING TO IOERPR
IOERSI   LW        R5,AS10         ABORT CODE.
         TBM       2,3W,1          BLOCKING ERROR FLAG
         BNS       $+2W         BRANCH IF NOT SET-I/O ERROR
         LW        5,AS21          ABORT CODE
         BU        ABRTM1
         SPACE     2
IOERSK   LW        R5,AS11         ABORT CODE.
         TBM       2,3W,1          BLOCKING ERROR FLAG
         BNS       $+2W         BRANCH IF NOT SET-I/O ERROR
         LW        5,AS22          ABORT CODE
         BU        ABRTM1
         SPACE     2
IOERCS   LW        R5,AS17         ABORT CODE
         TBM       2,3W,1          BLOCKING ERROR FLAG
         BNS       $+2W         BRANCH IF NOT SET-I/O ERROR
         LW        5,AS23          ABORT CODE
         BU        ABRTM1
         SPACE     2
CSER     LW        R5,AS12         ABORT CODE.
         BU        ABRTM1
         SPACE     2
CKER     LW        R5,AS13         ABORT CODE.
         BU        ABRTM1
         SPACE     3
AS01     DATAW     C'AS01'         EOF ON GO DURING WRITE.
AS02     DATAW     C'AS02'          "  "  BO    "     "
AS03     DATAW     C'AS03'          "  "  LO    "     "
AS04     DATAW     C'AS04'          "  "  UT1   "     "
AS07     DATAW     C'AS07'         UNRECOVERABLE I/O ERROR BO.
AS08     DATAW     C'AS08'               "        "    "   GO.
AS09     DATAW     C'AS09'               "        "    "   LO.
AS10     DATAW     C'AS10'               "        "    "   SI.
AS11     DATAW     C'AS11'               "        "    "   UT1.
AS12     DATAW     C'AS12'         EOF ON CS DURING WRITE.
AS13     DATAW     C'AS13'         CHECKSUM ERROR COMPRESSED INPUT.
AS17     DATAW     C'AS17'         UNRECOVERABLE I/O ERROR CS.
AS18     DATAW     C'AS18'         INVALID BLOCKING BUFF CTRL PTR  BO.
AS19     DATAW     C'AS19'         INVALID BLOCKING BUFF CTRL PTR  GO.
AS20     DATAW     C'AS20'         INVALID BLOCKING BUFF CTRL PTR  LO.
AS21     DATAW     C'AS21'         INVALID BLOCKING BUFF CTRL PTR  SI.
AS22     DATAW     C'AS22'         INVALID BLOCKING BUFF CTRL PTR  UT1.
AS23     DATAW     C'AS23'         INVALID BLOCKING BUFF CTRL PTR  CS.
AS31     DATAW     C'AS31'         MACRO ASSEMBLER GENERAL ABORT CODE
AS32     DATAW     C'AS32'         UNRECOVERABLE I/O ERROR PRE.
AS33     DATAW     C'AS33'         INVALID BLOCKING BUFF CTRL PTR PRE.
         TITLE     MACRO ASSEMBLER ADAPTER - DATA AREA
************************************************************************
*        D A T A    A R E A                                            *
************************************************************************
         SPACE     1
         BOUND     1W
READSIPC GEN       8/0,4/0,20/A(IBUF)
READPRPC GEN       8/0,4/0,20/A(IBUF2)
         IFF       UNIXF,SKIP                                   *JCB*
READSKPC GEN       8/0,4/0,20/A(SBUF)
SKIP     ANOP                                                   *JCB*
         IFT       UNIXF,SKIP                                   *JCB*
READSKPC ACW       IN              INPUT BUFFER POINTER         *JCB*
SBUFTCW  GEN       12/A(RECSIZ),20/B(SBUF)                      *JCB*
EJECTTCW GEN       12/8,20/B(EJECT)                             *JCB*
EJECT    DATAW     C'-       '                                  *JCB*
SKIP     ANOP                                                   *JCB*
         SPACE     1
CMPRS1   DATAB     0,2,3           NUMBER OF BYTES REQD IN BUFFER
         SPACE     1
PARAMBLK RES       11W             PARAMETER BLOCK               11010
*!!!!!!!!SPACE!!!!!1!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!S880752
*!UTFCB!!!DATAW!!!!G'UT!'!!!!!!!!!!FCB!FOR!GREETING!!!!!!!!!!!!!S880752
*!!!!!!!!RES!!!!!!!7W!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!SPACE!!!!!1!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!S880752
         BOUND     1F
         SPACE     1
*!FCBBO!!!DATAW!!!!G'BO!'!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!GEN!!!!!!!12/A(RECSIZ),20/B(PBL)!!!!!!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!GEN!!!!!!!8/4,24/0!!!!!!!!JCB!!!!!!!!!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!DATAW!!!!!0!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!DATAW!!!!!0!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!DATAW!!!!!0!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!ACW!!!!!!!IOERBO!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!DATAW!!!!!0!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!S880752
FCBBO    DATAW     G'BO '                                       S880752
         DATAW     0                                            S880752
         GEN       1/0,1/0,1/0,1/0,1/0,1/1,1/1,1/0,4/0,20/0     S880752
         DATAW     0,0,0                                        S880752
         ACW       IOERBO                                       S880752
         DATAW     0                                            S880752
         DATAW     A(PBL)                                       S880752
         DATAW     RECSIZ                                       S880752
         DATAW     0,0,0,0,0,0                                  S880752
         SPACE     2
*!FCBGO!!!DATAW!!!!G'GO!'!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!GEN!!!!!!!12/A(RECSIZ),20/B(PBL)!!!!!!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!GEN!!!!!!!8/4,24/0!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!DATAW!!!!!0!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!DATAW!!!!!0!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!DATAW!!!!!0!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!ACW!!!!!!!IOERGO!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!DATAW!!!!!0!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!S880752
FCBGO    DATAW     G'GO '                                       S880752
         DATAW     0                                            S880752
         GEN       1/0,1/0,1/0,1/0,1/0,1/1,1/1,1/0,4/0,20/0     S880752
         DATAW     0,0,0                                        S880752
         ACW       IOERGO                                       S880752
         DATAW     0                                            S880752
         DATAW     A(PBL)                                       S880752
         DATAW     RECSIZ                                       S880752
         DATAW     0,0,0,0,0,0                                  S880752
         SPACE     2
*!FCBLO!!!DATAW!!!!G'LO!'!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!DATAW!!!!!0!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!GEN!!!!!!!8/4,24/0!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!DATAW!!!!!0!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!DATAW!!!!!0!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!DATAW!!!!!0!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!ACW!!!!!!!IOERLO!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!DATAW!!!!!0!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!S880752
FCBLO    DATAW     G'LO '                                       S880752
         DATAW     0                                            S880752
         GEN       1/0,1/0,1/0,1/0,1/0,1/1,1/1,1/0,4/0,20/0     S880752
         DATAW     0,0,0                                        S880752
         ACW       IOERLO                                       S880752
         DATAW     0                                            S880752
         DATAW     0               BUFFER ADDR                  S880752
         DATAW     0               RECLEN                       S880752
         DATAW     0,0,0,0,0,0                                  S880752
         SPACE     2
*!FCBSI!!!DATAW!!!!G'SI!'!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!GEN!!!!!!!12/A(RECSIZ),20/B(IBUF)!!!!!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!GEN!!!!!!!8/4,24/0!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!DATAW!!!!!0!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!DATAW!!!!!0!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!DATAW!!!!!0!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!ACW!!!!!!!IOERSI!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!DATAW!!!!!0!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!S880752
FCBSI    DATAW     G'SI '                                       S880752
         DATAW     0                                            S880752
         GEN       1/0,1/0,1/0,1/0,1/0,1/1,1/1,1/0,4/0,20/0     S880752
         DATAW     0,0,0                                        S880752
         ACW       IOERSI                                       S880752
         DATAW     0                                            S880752
         DATAW     A(IBUF)                                      S880752
         DATAW     RECSIZ                                       S880752
         DATAW     0,0,0,0,0,0                                  S880752
         SPACE     2
*!FCBSK!!!DATAW!!!!G'UT1'!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!GEN!!!!!!!12/A(RECSIZ),20/B(SBUF)!!!!!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!GEN!!!!!!!8/4,24/0!!!!!JCB!!!!!!!!!!!!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!DATAW!!!!!0!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!DATAW!!!!!0!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!DATAW!!!!!0!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!ACW!!!!!!!IOERSK!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!DATAW!!!!!0!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!S880752
FCBSK    DATAW     G'UT1'                                       S880752
         DATAW     0                                            S880752
         GEN       1/0,1/0,1/0,1/0,1/0,1/1,1/1,1/0,4/0,20/0     S880752
         DATAW     0,0,0                                        S880752
         ACW       IOERSK                                       S880752
         DATAW     0                                            S880752
         DATAW     A(SBUF)                                      S880752
         DATAW     RECSIZ                                       S880752
         DATAW     0,0,0,0,0,0                                  S880752
         SPACE     2
*!FCBCS!!!DATAW!!!!G'CS!'!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!GEN!!!!!!!12/A(RECSIZ),20/B(SBUF)!!!!!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!GEN!!!!!!!8/4,24/0!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!DATAW!!!!!0!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!DATAW!!!!!0!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!DATAW!!!!!0!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!ACW!!!!!!!IOERCS!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!DATAW!!!!!0!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!S880752
FCBCS    DATAW     G'CS '                                       S880752
         DATAW     0                                            S880752
         GEN       1/0,1/0,1/0,1/0,1/0,1/1,1/1,1/0,4/0,20/0     S880752
         DATAW     0,0,0                                        S880752
         ACW       IOERCS                                       S880752
         DATAW     0                                            S880752
         DATAW     A(SBUF)                                      S880752
         DATAW     RECSIZ                                       S880752
         DATAW     0,0,0,0,0,0                                  S880752
         SPACE     2
*!FCBPRE!!!DATAW!!!G'PRE'!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!GEN!!!!!!!12/A(RECSIZ),20/B(IBUF2)!!!!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!GEN!!!!!!!8/4,24/0!!!!!JCB!!!!!!!!!!!!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!DATAW!!!!!0!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!DATAW!!!!!0!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!DATAW!!!!!0!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!ACW!!!!!!!IOERPR!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!DATAW!!!!!0!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!S880752
FCBPRE   DATAW     G'PRE'                                       S880752
         DATAW     0                                            S880752
         GEN       1/0,1/0,1/0,1/0,1/0,1/1,1/1,1/0,4/0,20/0     S880752
         DATAW     0,0,0                                        S880752
         ACW       IOERPR                                       S880752
         DATAW     0                                            S880752
         DATAW     A(IBUF2)                                     S880752
         DATAW     RECSIZ                                       S880752
         DATAW     0,0,0,0,0,0                                  S880752
         SPACE     2                                            S880752
*!FCBXR!!!DATAW!!!!G'UT2'!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!GEN!!!!!!!12/768,20/B(XRBUF)!!!!!!!!!!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!DATAW!!!!!0,0,0,0!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!ACW!!!!!!!IOERUT2!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!DATAW!!!!!0!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!S880752
XRSECSIZ EQU       768*20          SIZE EQUATE                  S880752
FCBXR    GEN       8/0,24/C'UT2'                                S880752
         DATAW     0                                            S880752
         GEN       1/0,1/0,1/0,1/0,1/0,1/1,1/1,1/0,4/0,20/0     S880752
         DATAW     0,0,0                                        S880752
         ACW       IOERUT2                                      S880752
         DATAW     0                                            S880752
         DATAW     A(XRBUF)                                     S880752
         DATAW     XRSECSIZ                                     S880752
         DATAW     0,0,0,0,0,0                                  S880752
         BOUND     1D                                           S880752
XRBUF    RES       XRSECSIZ        REPORT RECORD BUFFER         S880752
XRBUFP   RES       1W                                           S880752
BUFFADD  DATAW     A(XRBUF)        ADDR AND SIZE OF XRBUF FOR   S880752
         DATAW     XRSECSIZ        FCBXR INITIALIZATION         S880752
         SPACE     2
         BOUND     1F                                            11003
INQ.INFO RES       1F              8W FOR M.INQUIRY INFO         11003
         SPACE     2
*        CNPS FOR NATIVE MODE OPENS
         SPACE     1
CNPXX    DATAW     1               IMMEDIATE RETURN IF DENIED    11003
IOERXX   DATAW     0               ABNORMAL RETURN ADDRESS       11003
         DATAB     0               ACCESS (SET UP DEPENDING      11003
*                                  ON DEVICE/SYSTEM FILE)        11003
         DATAB     0               USAGE                         11003
         DATAH     0               STATUS                        11003
         DATAW     0               RESERVED                      11003
         DATAW     0               RESERVED                      11003
         DATAW     0               PARAMETER LINK                11003
         SPACE     1
CNPGO    DATAW     1               IMMEDIATE RETURN IF DENIED    11003
         ACW       IOERGO          ABNORMAL RETURN ADDRESS       11003
         DATAB     2               ACCESS (WRITE)                11003
         DATAB     0               USAGE                         11003
         DATAH     0               STATUS                        11003
         DATAW     0               RESERVED                      11003
         DATAW     0               RESERVED                      11003
         DATAW     0               PARAMETER LINK                11003
         SPACE     1
CNPLO    DATAW     1               IMMEDIATE RETURN IF DENIED    11003
         ACW       IOERLO          ABNORMAL RETURN ADDRESS       11003
         DATAB     0               ACCESS (SET UP DEPENDING      11003
*                                  ON DEVICE)                    11003
         DATAB     0               USAGE                         11003
         DATAH     0               STATUS                        11003
         DATAW     0               RESERVED                      11003
         DATAW     0               RESERVED                      11003
         DATAW     0               PARAMETER LINK                11003
         SPACE     1
CNPSK    DATAW     1               IMMEDIATE RETURN IF DENIED    11003
         ACW       IOERSK          ABNORMAL RETURN ADDRESS       11003
         DATAB     2               ACCESS (WRITE)                11003
         DATAB     0               USAGE                         11003
         DATAH     0               STATUS                        11003
         DATAW     0               RESERVED                      11003
         DATAW     0               RESERVED                      11003
         DATAW     0               PARAMETER LINK                11003
         SPACE     1
CNPCS    DATAW     1               IMMEDIATE RETURN IF DENIED    11003
         ACW       IOERCS          ABNORMAL RETURN ADDRESS       11003
         DATAB     2               ACCESS (WRITE)                11003
         DATAB     0               USAGE                         11003
         DATAH     0               STATUS                        11003
         DATAW     0               RESERVED                      11003
         DATAW     0               RESERVED                      11003
         DATAW     0               PARAMETER LINK                11003
         SPACE     1
FLAGS    DATAW     0
ERROCCUR EQU       0               0 - NO ERROR HAS OCCURRED
*                                  1 - AN ERROR HAS OCCURRED
*!SIAD!!!EQU!!!!!!!1!!!!!!!!!!!!!!!SI!USING!RM!ROUTINES!!!!!!!!!S880752
*!PREAD!!EQU!!!!!!!2!!!!!!!!!!!!!!!PRE!USEING!RM!ROUTINES!!!!!!!S880752
*!BOAD!!!EQU!!!!!!!3!!!!!!!!!!!!!!!BO!USING!RM!ROUTINES!!!!!!!!!S880752
*!UT1AD!!EQU!!!!!!!4!!!!!!!!!!!!!!!UT1!USING!RM!ROUTINES!!!!!!!!S880752
*
EOFA     RES       1W
FCBA     RES       1W
IBUFA    RES       1W
READPTR  RES       1W
MPP      DATAW     0               ADDR OF CURR LEVEL IN MACRO STACK
MACT     DATAW     0               TEMP STKP LOCATION DURING MACRO CALL
DEFCNT   DATAW     0               # PARMS BYT 0, MACRO BYT CNT IN 1-3
STACKP   DATAW     STACK           INTERNAL MACRO PARAMETER STACK
STACK    RES       768W            ENOUGH FOR 256 PARAMETERS
*
PCCHK    STF       R0,PCFILE       SAVE REGISTERS               S920209
         LW        R4,=X'007FFFFF' LOAD MASK                    S920209
         LMW       R5,HWLSTR       LOAD CSECT PROGRAM COUNTER   S920209
         LMW       R6,HWLSTR+1W    LOAD DSECT PROGRAM COUNTER   S920209
         CAMW      R5,=X'00080000' DID WE OVERFLOW?             S920209
         BGE       PCCHK1          YES...BRANCH                 S920209
         CAMW      R6,=X'00080000' CHECK DSECT ALSO             S920209
         BGE       PCCHK1          BRANCH IF OVERFLOW           S920209
         LF        R0,PCFILE       ELSE RETURN                  S920209
         TRSW      R0                                           S920209
         IFF       UNIXF,SKIP                                   *JCB*
PCCHK1   LB        R5,PCMSG.L      GET MESSAGE LENGTH           S920209
         STW       R5,FCBLO+9W     SAVE IN FCB                  S920209
         LA        R5,PCMSG.A      GET MESSAGE ADDRESS          S920209
         STW       R5,FCBLO+8W     SAVE IN FCB                  S920209
         LA        R1,FCBLO        GET FCB ADDRESS              S920209
         SVC       1,X'32'         OUTPUT MESSAGE               S920209
         LB        R5,PCMSG.2L                                  S920209
         STW       R5,FCBLO+9W                                  S920209
         LA        R5,PCMSG.2A                                  S920209
         STW       R5,FCBLO+8W                                  S920209
         LA        R1,FCBLO                                     S920209
         SVC       1,X'32'         OUTPUT SECOND PART           S920209
SKIP     ANOP                                                   *JCB*
         IFT       UNIXF,SKIP                                   *JCB*
PCCHK1   LB        R1,PCMSG.L      GET MESSAGE LENGTH           *JCB*
         LA        R2,PCMSG.A      GET MESSAGE ADDRESS          *JCB*
         BL        PSTDERR         PRINT MESSAGE ON STD ERROR   *JCB*
         LB        R1,PCMSG.2L     GET MESSAGE LENGTH           *JCB*
         LA        R2,PCMSG.2A     GET MESSAGE ADDRESS          *JCB*
         BL        PSTDERR         PRINT MESSAGE ON STD ERROR   *JCB*
SKIP     ANOP                                                   *JCB*
         BL        ABRTM1-1W       AND ABORT                    S920209
*
PCFILE   REZ       1F                                           S920209
PCMSG.A  DATAB     C' ASSEMBLE<<FATAL>> PROGRAM COUNTER '       S920209
         DATAB     C'OVERFLOW. A MAXIMUM OF .5 MB OF CODE'      S920209
PCMSG.L  DATAB     $-PCMSG.A                                    S920209
*
PCMSG.2A DATAB     C'                   AND/OR DATA CAN BE '    S920209
         DATAB     C'ASSEMBLED IN A SINGLE PROGRAM.'            S920209
PCMSG.2L DATAB     $-PCMSG.2A                                   S920209
*
         TITLE     READ-ONLY ASSEMBLER CODING
************************************************************************
*
*-----------------------BEGINNING OF ASSEMBLER EXECUTIVE----------------
*
************************************************************************
         SPACE
HHHH     STW       0,HHHHS0
         BL        RSET            INITIALIZE ASMBLR FOR THIS PASS
         BL        CEXT
         SPACE     1
*---------------COME HERE TO OBTAIN A NEW INPUT IMAGE-------------------
         SPACE     1
*
* (C) COPYRIGHT 1983 ENCORE COMPUTER CORPORATION
*     ALL RIGHTS RESERVED
*
NEXT     BL        INPT            RELEASE IMAGE AND FETCH NEXT ONE
         ZBM       ASCT.NOD,ASCT.FLG   CLEAR THE NO $  FLAG     EASC-32
         ZBM       3,BACFLAG       CLEAR BAC EXTERNAL FLAG     EBAC-33C
         STW       7,HWLICT        SAVE THE BINARY LINE SERIAL NUMBER
         TRR       7,7             WAS IT AN EOF OR EOJ
         BEQ       A111         BR IF FOUND
         ZBM       1,PREFLG        CLEAR PRE EOF INDICATOR
         ZBM       NONGITEM,HHBITS2     CLEAR LIST NONG SUPP. FLAG
         LI        R6,-18          18 WORDS TO CHECK            S900555
         ZR        R2                                           S900555
NXT.0    LW        R4,IN,X2        GET WORD FROM INPUT LINE     S900555
         CAMW      R4,BLANKS       SPACES?                      S900555
         BNE       NXT.00          NO...PROCESS LINE            S900555
         ADI       R2,1W           NEXT WORD                    S900555
         BIB       R6,NXT.0                                     S900555
         BU        NXT.000         SKIP BLANK LINE              S900555
NXT.00   ZBM       0,ENDFLAG       ASSUME NO END CARD COMING
         LI        6,G'*'          CHECK FOR * IN COL 1
         CAMB      6,IN
*!!!!!!!!BEQ!!!!!!!NEXT!!!!!!!!!*!IS!IN!COL!1,!LIST!ONLY!!!!!!!!ENPC-33
         BNE       NXT.1           NOT A COMMENT...CONTINUE     ENPC-33
         TBM       8,OPTION2       OPTION 56 SET?               ENPC-33
         BNS       NEXT            NO...PRINT COMMENT           ENPC-33
         LI        R6,G'!'         IS * FOLLOWED BY A !         ENPC-33
         CAMB      R6,IN+1B                                     ENPC-33
         BNE       NEXT            NO...PRINT COMMENT           ENPC-33
NXT.000  LA        R6,NEXT+1W      ELSE DON'T PRINT COMMENT     ENPC-33
         STW       R6,INPTS0       SAVE RETURN ADDRESS          ENPC-33
         BU        INPT0           MERGE                        ENPC-33
NXT.1    SBM     COMMENT,MACSTATE  0= * IN COL 1, 1=ELSE
         LW        1,=X'80000000'     TERMINATE ONLY ON A SPACE
         BL        RUNST           UNSTRING LABEL-SKIP NO LEADING SPACES
         LD        6,HWNAME        MOVE UNSTRUNG LABEL TO LABEL AREA
         STD       6,HWLABL        8 BYTES OF A POSSIBLE LABEL
         ZBM       INTGEN,MACSTATE CLR INDICATION  OF INTERNAL LABEL
         CAMD      6,LABLSCAN      CHECK THE RECENT LABEL AGAINST THE
*                                         ONE WE ARE LOOKING FOR
         BNE       HM1          THIS IS NOT IT-DO NOT CHANGE THE STAT
         ZBM       CONDSCAN,MACSTATE      WE HAVE FOUND THE PLACE-NORMAL
HM1      LW        1,=X'80000000'     TERMINATE ONLY ON A SPACE
         BL        UNST            IGNORE LEADING SPACES,UNSTR OPERATOR
*.----------------------------                                 EASC-32
*.       BL        ASCT.OT         REVERT TO CSECT             EASC-32
*.----------------------------                                 EASC-32
         LI        7,TYMACREQ      SET POINTER FOR MACRO DATA REQUEST
         STB       7,HWMRQ         SET THE TYPE CODE FOR CHECKING
         LND       4,HWNAME        THE UNSTRUNG OPERATOR NAME(NEGATED)
         LW        1,HWMRQ         REQUEST DATA
         BL        SS              CHECK FOR NAME
         STW       3,HWCMAC        SAVE A POINTER TO POSSIBLE MACRO PROT
         ZR        2
         SLLD      2,8             GET THE TYPE CODE TO R2
         ZBR       2,24            CLEAR DSECT/CSECT FLAG
         CI        2,TYMACDEF      WAS A MACRO DEFINED FOR THAT NAME
         BEQ       MACEXP       YES-THEN WE MUST EXPAND THE MACRO
         CI        2,TYFRM         WAS IT A DEFINED FORM SKELETON
         BEQ       FORMEXP      YES-THEN EXPAND A FORM
         TBM       MA2PRES,HHBITS4 IS MA2 FILE ASSIGNED?
         BNS       HHHH01          NO
         SBM       MA2SRCH,HHBITS4 INDICATE SEARCH MA2 FILE
         BL        YEANAY          ARE WE ASSEMBLING    AS14
         BS        AERR2           YES, GO SEARCH MA2 FILE AS14
HHHH01   ZBM       MA2SRCH,HHBITS4 INDICATE SEARCH MAC FILE
         SPACE
* SEARCH OPSTAB FOR VALID OPERATOR
         SPACE
         LD        4,HWNAME        OP CODE IN 4 + 5
         BL        OPSCAN          GO SCAN OP CODE TABLE
*                                  R1=TABLE ADDR ON RETURN IF FOUND
*                                  R1=ZERO IF NOT FOUND
*                                  R2=DESCRIPTOR WORD
         TRR       1,1             SET CC'S
         NOP
*-------------------------------                               EASC-32
         BL        ASCT.TST        SET UP APPROPRIATE SECTION  EASC-32
*-------------------------------                               EASC-32
         BZ        AERR            IF ZERO, OPCODE NOT FOUND, ERROR
         STW       2,HWACT         SAVE ELEMENTS 2-7 OF OP CODE DESCR
         LI        4,X'F'          SET UP MASK
         LMB       2,HWACT+1       ELEMENT 4, ADR VARIANT
         STB       2,HBAVAR
         LB        2,HWACT+3       ELEMENT 7, OPERATION PROCESSOR NO.
         CI        R2,15           IS IT A MEMORY REF. INSTR.   ENSB-33
         BEQ       HHHH02          YES...BRANCH                 ENSB-33
         CI        R2,5            IS IT A BIT IN MEMORY INSTR  ENSB-33
         BEQ       HHHH02          YES...BRANCH                 ENSB-33
         CI        R2,18           IS IT A FLOATING POINT INSTR ENSB-33
         BEQ       HHHH02          YES...BRANCH                 ENSB-33
         CI        R2,24           IS IT A ZERO MEMORY INSTR    ENSB-33
         BNE       HHHH03          NO...BRANCH                  ENSB-33
HHHH02   SBM       2,EXTFLG        SHOW AS NON-BRANCH CSECT REF ENSB-33
HHHH03   SLL       2,2             CONVERT TO BYTE DISPLACEMENT
         TRR       2,3
         CI        2,KINTLN1       IS ENTRY BELOW LIST NONG PTR LOW
         BLT       HHHH8.5      YES - DON'T SUPPRESS LIST
         CI        2,KINTLN2       IS ENTRY ABOVE LIST NONG PTR HIGH
         BGE       HHHH8.5      YES - DON'T SUPPRESS LIST
         SBM       NONGITEM,HHBITS2  MARK OPER. AS LIST NONG SUPPRESSABL
HHHH8.5  LA        R3,KINT,R3      BUILD ADR FOR SWITCH BY OPERATOR
         STW       3,HHHHS1        SAVE ADDRESS
         CI        2,KINTL3
         BLT       HHHH8.6         GO BOUND AND ALLOCATE LABEL
         CI        2,KINTL4
         BLT       HHHH9           NO ACTION REQUIRED
HHHH8.6  BL        BNDW            ADJUST TO PROPER BOUNDARY FOR NEXT LI
         BL        TALL            ALLOCATE CURRENT LABEL
         LB        2,HWACT+3B
         SLL       2,2             RESULT IS BYTE DISPLACEMENT IN KINT
         CI        2,KINTL1        KINTL1 TO KINTL2 REQ GRPS
         BLT       HHHH9
         CI        2,KINTL2
         BLT       HHHH8.7         GO PICK UP ARGUMENTS
         CI        2,KINTL4
         BLT       HHHH9           DON'T PICK UP ARGUMENTS
HHHH8.7  BL        GRPS
         SPACE     1
         LW        1,HWNL1         SET UP VALUES FROM GRPS IN REGISTERS
         LW        2,HWNL2
         LW        3,HWNL3
HHHH9    LB        5,HWACT+1B      FETCH AUGMENT
         SRL       5,4             RIGHT JUSTIFY IT
         BU        *HHHHS1         TO SWITCHER FOR THIS OPERATOR
         TITLE     READ-ONLY       AERR
AERR     BL        YEANAY          ARE WE ASSEMBLING?
         BNS       MACAERR8     NO.
AERR2    LD        6,HWNAME        GET THE NAME OF POSSIBLE MACRO AS14
         IFF       UNIXF,SKIP                                   *JCB*
         TBM       MA2SRCH,HHBITS4 SEARCHING MA2 FILE ?
         BNS       MACAE2.1        NO
         BL        LIBSCH1         SEARCH MA2 FILE
         BU        MACAE2.2        CONTINUE
         SPACE
SKIP     ANOP                                                   *JCB*
MACAE2.1 BL        LIBSCH          SEARCH THE MACRO LIBRARY
         SPACE
*        R6=#PARS,#CHARS
         SPACE
MACAE2.2 CAMD      6,HWNAME        DID THE LIBRARIAN FIND ANYTHING
         BEQ       AERR0        NOTHING OF THAT NAME IN THE LIBRARY
         STW       R1,HWCMAC       SAVE ADDR OF MACRO IN EXT MEM
         LND       4,HWNAME        THE NAME OF THE NEW MACRO
         LI        1,TYMACDEF      SHOW THIS AS A MACRO DEFINITION
         STB       1,HWCMAC        ID IT
         LW        1,HWCMAC        DEFINTIION INFO FOR TH NEW MACRO
         BL        SS              DEFINE FOR USE LATER
         BU        MACEXP          EXPAND THE MACRO WE HAVE GOTTEN
MACAERR8 LI        2,0             SIGNIFY THAT WE DONT HAVE ANYTHING UN
         BL        VAL             GO UNSTRING AND EVALUATE ONE ARGUMENT
         LB        7,HBSTAC        CHECK THE TERMINATOR
         CI        7,G','          WAS TERMINATOR A COMMA
         BEQ       MACAERR8     YES-THEN GO GET THE NEXT ARGUMENT
         BU        NEXT            GO TO NEXT STATEMENT
A111     TBM       1,PREFLG        EOF ON FIRST READ OF SI
*                                   AFTER EOF FOUND ON PRE?
         BS        A119         IF SO, SKIP END CARD TEST
         TBM       0,ENDFLAG       CHECK IF LAST CARD WAS AN END CARD
         BS        A119         THE CARD BEFORE THE EOF WAS AN END CA
         LW        1,EOFCONT       THE CARD BEFORE THE EOF WAS NOT AN
         SPACE
*        END CARD--SO ERROR OUT TO THE USER
         SPACE
         BL        ABORTM         ABORT WITH MESSAGE SERVICE
A119     BU        *HHHHS0         RETURN
         SPACE     1
AERR0    TBM       MA2SRCH,HHBITS4 SEARCHING MA2 FILE ?
         BS        HHHH01          YES - DON'T GIVE UP HOPE YET.
         SBM       G'B'-X'40',HWERRF   MARK 'B' ERROR
         ABM       31,HWERCT           COUNT THE ERROR
         LI        R5,2            DEFAULT TO NOP
         ZMW       HWACT           CLEAR PREVIOUS CONTENTS
         BU        NSS             MERGE WITH NOP CODE
         TITLE     READ-ONLY       CDL, RTB, LER, CALM
* FORM LEFT HALF OF CD (SEMI-PSEUDO OP)
         SPACE
CDL      TRR       5,6             FETCH AUGMENT
         SRLD      6,3             SHIFT INTO R7,B0-2 FOR B13-15 OF INST
         TRR       1,6             DEVICE NUMBER FROM INPUT ARGUMENT
         SRLD      6,7             RIGHTMOST 10 BITS OF HALFWD IN R7,0-9
         BU        A16             FINISH IN COMMON 16 BIT NODE
         SPACE
* REGISTER TEST BIT OP DECODE
         SPACE
RTB      LW        4,=X'007FFFFF'  MASK FOR THE VALUE PART ONLY.
         TRRM      2,6             GET BIT NUMBER.
         CAMW      6,=X'0000001F'  MAX. BIT NUMBER.
         BLE       RTB1         WITHIN VALUE PERMITTED.
         BL        YEANAY          ASSEMBLY GOING ON?
         BNS       RTB1         NO.
         SBM       G'B'-X'40',HWERRF   MARK 'B' ERROR
         ABM       31,HWERCT           COUNT THE ERROR
RTB1     ANMW      6,=X'0000001F'  LIMIT BIT NUMBER TO 31.
*        SRLD      6,7             R7, B0-6 NOW CONTAINS 2 BITEBRM-33
         SRLD      6,5             R7, B0-6 NOW CONTAINS      EBRM-33
*                                 ,2 BITS OF BYTE #, 3 BITS OF BIT # .
         LB        6,HWACT+1B      GET AUGMENT CODE           EBRM-33
         SRL       6,4             INTO L.O. BITS             EBRM-33
         SRLD      6,2             PUT INTO R7                EBRM-33
         TRR       1,6             REGISTER NUMBER TO R6
*        SRLD      6,3             R7 B0-2=R NO.,B2-4=0,B5-6=EBRM-33
         SRLD      6,3             R7 B0-2=R NO.,B2-4=AUG,   EBRM-33
*                                  B5-6=BYTE NO.             EBRM-33
         ANMW      6,=X'000FFFFF'  THROW AWAY TYPE CODE
         CI        6,0             MAX. GENERAL REG. NO. IS 7
         BLE       RTB2         WITHIN PERMITTED VALUE
         BL        YEANAY          ASSEMBLY GOING ON?
         BNS       RTB2         NO.
         SBM       G'B'-X'40',HWERRF  MARK 'B' ERROR.
         ABM       31,HWERCT           COUNT THE ERROR.
RTB2     TRR       2,6             GET BIT NUMBER.
         SRLD      6,3             PUT IN R7 B0-2
         BU        A16             GO RELEASE BYTES.
         SPACE
* 16 BIT ONE SYLLABLE INSTRUCTION DECODE
         SPACE
NSS      ZR        1
         SPACE
* GENERAL REGISTER UNARY OPS(LCS,ES,RND)
         SPACE
LER      SRC       5,7             AUG TO R5,B4-7,B0-3=0
         TRR       5,7             BRING IN AUGMENT
A16A     TRR       1,6             THE GENERAL REGISTER NUMBER
         LI        4,-2            2 BYTES TO BE GENERATED
         BU        A16C            GO TO COMMON PROCESSING
         SPACE
* PROCESS CALM OPERATOR
         SPACE
CALM     TBM       12,OPTION       ! TEST FOR SVC 15 (OPTION 20)
         BNS       CALM2           ! NO, BRANCH
         TRR       1,2             ! SVC CALL NUMBER
         LI        1,15            ! SVC INDEX (15)
         LI        7,-4            ! FAKE EXPRESSION COUNT
         STW       7,GRPW          ! SAVE IT
         LW        7,=X'CA600134'  ! SVC OP DESCRIPTOR
         STW       7,HWACT         ! REPLACE CALM DESCRIPTOR
         LI        5,6             ! SVC OP AUGMENT
         BU        SVC             ! PROCESS AS SVC
         SPACE
CALM2    SLL       1,22            ! LEFT JUSTIFY THE PROGRAM FLAGS
         TRR       1,7             ! TRANSFER FLAGS TO R7
         SBR       7,24            ! RIGHT HALF OF WORD WILL BE 'NOP'
         LI        3,-2            ! 2 BYTES OF OUTPUT
         BU        AGEPB           ! OUTPUT HALF WORD CALM INSTRUCTION
*
         TITLE     RSC - RISC FLOATING POINT INSTR. PROCESSOR   ERSC-32
*        CF2D - convert float ieee to double ieee               IEEE-MOD
CF2D     TBM       2,FPFLAG        WAS $OPTION 55 SPECIFIED?    IEEE-MOD
         BNS       X64N            No, standard excess 64 FP    IEEE-MOD
         LW        R7,=X'080E290F' Get TRFW & TDPR instructions IEEE-MOD
         ANMW      R1,=X'7'        Just the reg number          IEEE-MOD
         TRR       R1,R6           GET RS FIELD                 IEEE-MOD
         SLL       R6,20           POSITION IN REG for TRFW     IEEE-MOD
         ORR       R6,R7           AND ADD IN                   IEEE-MOD
         TRR       R1,R6           GET RS FIELD                 IEEE-MOD
         SLL       R6,4            POSITION IN REG for TDPR     IEEE-MOD
         ORR       R6,R7           AND ADD IN                   IEEE-MOD
         LI        R3,-4           SET NUMBER OF BYTES          IEEE-MOD
         BU        AGEPC           NOW GOTO COMMON PROCESSOR    IEEE-MOD
X64N     LW        R7,=X'0C000000' GET ZR instruction           IEEE-MOD
         ANMW      R1,=X'7'        Just the reg number          IEEE-MOD
         TRR       R1,R6           GET RS/RD FIELD              IEEE-MOD
         ADI       R6,1            Zero odd register            IEEE-MOD
         SLL       R6,20           POSITION IN REG for ZR       IEEE-MOD
         ORR       R6,R7           AND ADD IN                   IEEE-MOD
         SLL       R6,3            POSITION IN REG for ZR       IEEE-MOD
         ORR       R6,R7           AND ADD IN                   IEEE-MOD
         LI        R3,-2           SET NUMBER OF BYTES          IEEE-MOD
         BU        AGEPC           NOW GOTO COMMON PROCESSOR    IEEE-MOD
*---------------------------------------------------------------IEEE-MOD
*        CD2F - convert double ieee to float ieee               IEEE-MOD
CD2F     TBM       2,FPFLAG        WAS $OPTION 55 SPECIFIED?    IEEE-MOD
         BNS       NEXT            No, no conversion to do      IEEE-MOD
         LW        R7,=X'080F290D' Get TRFD & TSPR instructions IEEE-MOD
         TRR       R1,R6           GET RS FIELD                 IEEE-MOD
         SLL       R6,20           POSITION IN REG for TRFD     IEEE-MOD
         ORR       R6,R7           AND ADD IN                   IEEE-MOD
         TRR       R1,R6           GET RS FIELD                 IEEE-MOD
         SLL       R6,4            POSITION IN REG for TSPR     IEEE-MOD
         ORR       R6,R7           AND ADD IN                   IEEE-MOD
         LI        R3,-4           SET NUMBER OF BYTES          IEEE-MOD
         BU        AGEPC           NOW GOTO COMMON PROCESSOR    IEEE-MOD
*---------------------------------------------------------------IEEE-MOD
RSC1     CEQU      $                                            ERSC-32
         LB        R6,HWACT+1B     GET AUX CODE VALUES          ERSC-32
         ZR        R7                                           ERSC-32
         SRLD      R6,4            GET SECOND LEVEL AUX IN R7   ERSC-32
         SRL       R7,5            AND POSITION TO BITS 6-8     ERSC-32
         SLL       R6,16           MOVE PRIMARY AUX TO POSITION ERSC-32
         ORR       R6,R7           AND MOVE INTO R7             ERSC-32
         LB        R6,HWACT        GET OPCODE                   ERSC-32
         SRL       R6,2            STRIP BOUNDING CODE          ERSC-32
         SLL       R6,26           POSITION IN R6               ERSC-32
         ORR       R6,R7           AND MOVE INTO R7             ERSC-32
         TRR       R1,R6           GET RS FIELD                 ERSC-32
         SLL       R6,20           POSITION IN REG              ERSC-32
         ORR       R6,R7           AND ADD IN                   ERSC-32
         LI        R3,-2           SET NUMBER OF BYTES          ERSC-32
         BU        AGEPC           NOW GOTO COMMON PROCESSOR    ERSC-32
*---------------------------------------------------------------ERSC-32
RSC2     CEQU      $                                            ERSC-32
         LB        R6,HWACT+1B     GET AUX CODE VALUES          ERSC-32
         ZR        R7                                           ERSC-32
         SRLD      R6,4            GET SECOND LEVEL AUX IN R7   ERSC-32
         SRL       R7,5            AND POSITION TO BITS 6-8     ERSC-32
         SLL       R6,16           MOVE PRIMARY AUX TO POSITION ERSC-32
         ORR       R6,R7           AND MOVE INTO R7             ERSC-32
         LB        R6,HWACT        GET OPCODE                   ERSC-32
         SRL       R6,2            STRIP BOUNDING CODE          ERSC-32
         SLL       R6,26           POSITION IN R6               ERSC-32
         ORR       R6,R7           AND MOVE INTO R7             ERSC-32
         LI        R3,-2           SET NUMBER OF BYTES          ERSC-32
         BU        AGEPC           NOW GOTO COMMON PROCESSOR    ERSC-32
*
*---------------------------------------------------------------EINS-31
  TITLE     REIS/SEIS  RESET/SET ENHANCED INSTRUCTION SET MODE  EINS-31
*                                                               EINS-31
*---------------------------------------------------------------EINS-31
*                                                               EINS-31
RS.EIS   CEQU      $                                            ESCT-32
         BL        YEANAY          ARE WE ASSEMBLING            EINS-31
         BNS       EIS.XIT         RETURN IF NOT                EINS-31
         TBM       7,PAS2          IS THIS PASS 2               EINS-31
         BS        EIS.XIT         IGNORE DIRECTIVE IF NOT      EINS-31
         LW        R4,HWNAME       GET OPCODE                   EINS-31
         IFT       ULC,SKIP                                     *JCB*
         LI        R0,-4           FOUR BYTES TO TEST           *JCB*
REIS.U   TBR       R4,1            THIS A LETTER                *JCB*
         BNS       REIS.U1         BR IF NOT                    *JCB*
         ZBR       R4,2            YES, CONVER TO UPPER CASE    *JCB*
REIS.U1  SRC       R4,8            NEXT BYTE                    *JCB*
         BIB       R0,REIS.U       DO 4 BYTES                   *JCB*
SKIP     ANOP                                                   *JCB*
         CAMW      R4,EIS.SEIS     IS IT SEIS                   EINS-31
         BNE       EIS.GOON        TRY  REIS                    EINS-31
         BL        EIS.SET         ELSE  SET MODE               EINS-31
         BU        EIS.XIT         AND RETURN                   EINS-31
EIS.GOON CEQU      $                                            ESCT-32
         CAMW      R4,EIS.REIS     IS IT REIS                   EINS-31
         BNE       EIS.XIT         RETURN IF NOT                EINS-31
         BL        EIS.RSET        ELSE RESET THE MODE          EINS-31
EIS.XIT  CEQU      $                                            ESCT-32
         BU        NEXT                                         EINS-31
*                                                               EINS-31
*---------------------------------------------------------------EINS-31
*                                                               EINS-31
EIS.SET  CEQU      $               SET ENTRY POINT              ESCT-32
         SBM       EIS.ON,EISFLG   MARK EIS MODE ON             EINS-31
         BU        EIS.MRGE        AND CONTINUE                 EINS-31
*                                                               EINS-31
EIS.RSET CEQU      $               RESET ENTRY POINT            ESCT-32
         ZBM       EIS.ON,EISFLG   MARK EIS MODE OFF            EINS-31
*                                                               EINS-31
EIS.MRGE CEQU      $               CONTINUE                     ESCT-32
         LI        R4,-4           SET LOOP COUNT               EINS-31
         LB        R6,EIS.RLD      GET OPCODE FOR RESET LOAD    EINS-31
         TBM       EIS.ON,EISFLG   ARE WE SETTING EIS MODE      EINS-31
         BNS       $+2W            SKIP IF NOT                  EINS-31
         LB        R6,EIS.SLD      ELSE GET OPCODE FOR SET LOAD EINS-31
         ZR        R3              INIT INDEX                   EINS-31
         NOP                                                    EINS-31
EIS.LDL  CEQU      $                                            ESCT-32
         STB       R6,EIS.LDI+20B,X3  AND SET ENTRY             EINS-31
         ADI       R3,24B          INCREMENT TO NEXT            EINS-31
         BIB       R4,EIS.LDL      AND LOOP                     EINS-31
*                                                               EINS-31
         LI        R4,-4           SET LOOP COUNT               EINS-31
         LB        R6,EIS.RST      GET OPCODE FOR RESET STORE   EINS-31
         TBM       EIS.ON,EISFLG   ARE WE SETTING EIS MODE      EINS-31
         BNS       $+2W            SKIP IF NOT                  EINS-31
         LB        R6,EIS.SST      ELSE GET OPCODE FOR SET STOREEINS-31
         ZR        R3              INIT INDEX                   EINS-31
         NOP                                                    EINS-31
EIS.STL  CEQU      $                                            ESCT-32
         STB       R6,EIS.STI+20B,X3  AND SET ENTRY             EINS-31
         ADI       R3,24B          INCREMENT TO NEXT            EINS-31
         BIB       R4,EIS.STL      AND LOOP                     EINS-31
*                                                               EINS-31
         LB        R6,EIS.RLR      GET OPCDE FOR RST LD REAL ADREINS-31
         TBM       EIS.ON,EISFLG   ARE WE SETTING EIS MODE      EINS-31
         BNS       $+2W            SKIP IF NOT                  EINS-31
         LB        R6,EIS.SLR      ELSE GET OPCODE FOR SET MODE EINS-31
         STB       R6,EIS.LRI+20B  AND STORE INTO ENTRY         EINS-31
         TRSW      R0              RETURN                       EINS-31
*---------------------------------------------------------------EINS-31
*                                                               EINS-31
EIS.REIS DATAW     C'REIS'                                      EINS-31
EIS.SEIS DATAW     C'SEIS'                                      EINS-31
EISFLG   DATAB     0               EIS MODE FLAGS               EINS-31
EIS.ON   EQU       0       BIT 0 =1 SEIS MODE                   EINS-31
*                                =0 REIS MODE                   EINS-31
EIS.OPC  EQU       1       BIT 1 SET FOR CONTEXT TYPE INSTS.    EINS-31
*                      ELSE      RESET                          EINS-31
*                                                               EINS-31
*                                                               EINS-31
* OPCODES FOR UNMAPPED INSTRUCTIONS:                            EINS-31
*                                                               EINS-31
*   IN RESET ENHANCED INSTRUCTION SET (REIS) MODE               EINS-31
*                                                               EINS-31
EIS.RLD  DATAB   X'AE'        OPCODE FOR LB,LH,LW,LD            EINS-31
EIS.RST  DATAB   X'D6'        OPCODE FOR STB,STH,STW,STD        EINS-31
EIS.RLR  DATAB   X'82'        OPCODE FOR LEAR                   EINS-31
*                                                               EINS-31
*    IN SET ENHANCED INSTRUCTION SET (SEIS) MODE                EINS-31
*                                                               EINS-31
EIS.SLD  DATAB   X'5E'        OPCODE FOR LCB,LCH,LCW,LCD        EINS-31
EIS.SST  DATAB   X'56'        OPCODE FOR STCB,STCH,STCW,STCD    EINS-31
EIS.SLR  DATAB   X'5A'        OPCODE FOR LCRA                   EINS-31
*                                                               EINS-31
*---------------------------------------------------------------EINS-31
         TITLE     READ-ONLY       TRAW, SHF, ZRX, NORDS, RRO
* PROCESS TRSW OPERATOR
         SPACE
TRSW     ZR        6               THESE WILL FINALLY BE BITS 9-15 OF TH
         SPACE
* PROCESSOR FOR MOST SHIFTS
         SPACE
SHF      TRR       2,6             SHIFT COUNT TO R6
         TBM       DEFMBODY,MACSTATE  CHECK FOR BEING IN BODY OF A DEF
         BS        A16A         NOTHING TO DO IN THAT CASE
         TBM       RSCAN,MACSTATE     CHECK FOR BEING IN A REPEAT SCAN
         BS        A16A         NO GEN
         ANMW      6,=X'007FFFFF'  ALLOW ONLY THE VALUE PART THROUGH
         CI        6,31            CHECK FOR ABOVE MAXIMUM
         BLE       SHF1         WITHIN ALLOWABLE RANGE.
         BL        YEANAY          ARE WE ASSEMBLING?
         BNS       $+3W         NO.
         SBM       G'N'-X'40',HWERRF   MARK N ERROR
         ABM       31,HWERCT       COUNT THE ERROR
         LI        R6,31           LIMIT TO MAX SHIFT COUNT OF 31
SHF1     TBM       3,HWACT+1B      IS THIS A LEFT SHIFT
         BNS       $+3H         NO
         SBR       6,25            YES, SET LEFT SHIFT BIT
         TBM       2,HWACT+1B      SET BIT 10? (BASE REG OP'S) EBRM-33
         BNS       $+3H            NO,BRANCH                   EBRM-33
         SBR       6,26            OTHERWISE, SET IT           EBRM-33
         SRLD      6,7             POSITION DIR IND AND SHIFT CT R7,B0-6
         BU        A16A            FINISH IN COMMON 16 BIT PROCESSING
         SPACE
* PROCESSOR FOR RISC FLOATING POINT CONTEXT INSTRUCTIONS        ERSC-32
FPCTX    LI        R4,-4           WRITE OUT 4 BYTES            ERSC-32
         BU        RRO.1           MERGE WITH REG-TO-REG CODE   ERSC-32
* PROCESSOR FOR ZERO REGISTER
         SPACE
ZRX      TRR       1,2             SET UP R2 AND PROCESS AS REG-REG OP
         SPACE
* PROCESSOR FOR NOR, NORD, SCZ
         SPACE
NORDS    XCR       1,2             PROCESSING SAME AS RRO EXCEPT DATA
         SPACE
* REGISTER-REGISTER OPS TRANSLATION
         SPACE
RRO      LI        4,-2            2 BYTES TO BE GENERATED
RRO.1    TRR       5,6             AUGMENT TO R6 B28-31
         SRLD      6,4             AUGMENT TO R7 B0-3
         TRR       1,6             SOURCE REGISTER
         SRLD      6,3             INTO R7,B 0-2 AUG TO 3-6
         ANMW      6,=X'000FFFFF'  THROW AWAY TYPE CODE.
         CI        6,0             MAX. GENERAL REG. NUMBER IS 7
         BLE       A16B         WITHIN VALUE PERMITTED.
         BL        YEANAY          ASSEMBLY GOING ON?
         BNS       A16B         NO.
         SBM       G'B'-X'40',HWERRF   MARK 'B' ERROR
         ABM       31,HWERCT           COUNT THE ERROR
A16B     TRR       2,6             BIT NUMBER/DESTINATION REGISTER,ETC
         SPACE
* NODE HERE FOR 16 BIT INST WHEN RIGHTMOST 7 BITS OF INST IN R7,B0-6
* AND NEXT 3 BITS ARE IN R6 RIGHT JUSTIFIED
         SPACE
A16C     SRLD      6,3             PUT IT IN R7,B0-2
         ANMW      6,=X'000FFFFF'  THROW AWAY TYPE CODE.
         CI        6,0             MAX. GENERAL REG. NUMBER IS 7.
         BLE       A16D            WITHIN PERMITTED VALUE
         BL        YEANAY          ASSEMBLY GOING ON?
         BNS       A16D         NO
         SBM       G'B'-X'40',HWERRF   MARK 'B' ERROR
         ABM       31,HWERCT           COUNT THE ERROR
         SPACE
* THE RIGHTMOST 10 BITS OF A 16 BIT INST ARE IN R7 0-9
*  OR THE RIGHTMOST 26 BITS OF A 32 BIT INST ARE IN R7 BITS 0-25
         SPACE
A16D     TRR       4,3             NEG NUM OF BYTES TO BE GENERATED
         BU        AGEPB           GO RELEASE THE BYTES
A16      LI        3,-2            INDICATE 2 BYTES TO BE GENERATED
         BU        AGEPB           GO RELEASE THE BYTES
*
* PROCESSOR FOR RISC REVERSED REG-TO-REG OPERANDS               ERSC-32
*
REVRRO   LI        R4,-2           WRITE OUT 2 BYTES            ERSC-32
         TRR       R5,R6           AUGMENT TO R6 BITS 28-31     ERSC-32
         SRLD      R6,4            AUGMENT TO R7 BITS 0-3       ERSC-32
         TRR       R2,R6           GET DESTINATION REG NUMBER   ERSC-32
         SRLD      R6,3            INTO R7 BITS 0-2 AUGMENT 3-6 ERSC-32
         ANMW      R6,=X'000FFFFF' GET RID OF TYPE CODE         ERSC-32
         CI        R6,0            MAX GENERAL REG NUMBER IS 7  ERSC-32
         BLE       REVRO1          WITHIN VALUE PERMITTED       ERSC-32
         BL        YEANAY          IS ASSEMBLY GOING ON?        ERSC-32
         BNS       REVRO1          NO...SKIP ERROR REPORT       ERSC-32
         SBM       G'B'-X'40',HWERRF    MARK 'B' ERROR          ERSC-32
         ABM       31,HWERCT       COUNT THE ERROR              ERSC-32
REVRO1   TRR       R1,R6           GET SOURCE REGISTER NUMBER   ERSC-32
         SRLD      R6,3            INTO R7 BITS 0-2             ERSC-32
         ANMW      R6,=X'000FFFFF' THROW AWAY TYPE CODE         ERSC-32
         CI        R6,0            MAX GENERAL REG NUMBER IS 7  ERSC-32
         BLE       REVRO2          WITHIN VALUE PERMITTED       ERSC-32
         BL        YEANAY          ASSEMBLY GOING ON ?          ERSC-32
         BNS       REVRO2          NO...SKIP ERROR REPORT       ERSC-32
         SBM       G'B'-X'40',HWERRF   MARK 'B' ERROR           ERSC-32
         ABM       31,HWERCT       COUNT THE ERROR              ERSC-32
REVRO2   TRR       R4,R3           NEG. NUM. OF BYTES TO WRITE  ERSC-32
         BU        AGEPB           WRITE OUT INSTRUCTION        ERSC-32
*
         TITLE     READ-ONLY       AGEN
* PROCESS NORMAL 32 BIT REGISTER-MEMORY INSTRUCTION
         SPACE
*
* (C) COPYRIGHT 1983 ENCORE COMPUTER CORPORATION
*     ALL RIGHTS RESERVED
*
AGEN     STW       2,HWEVAL        SAVE ADDRESS FIELD FOR PRINTOUT
         BL        AGEQ            PUT ADDRESS WORD TOGETHER WITH F,CC,I
         SLL       7,11            ADDRESS AND INDR IN R7,B0-20
AGEM     TRR       3,6             GET INDEX REG NUMBER
         SRLD      6,2             INTO R7,B0,1 (B2-22=ADR)
         LI        3,X'03'         LOOK ONLY AT 2 BITS.
         ANMB      3,HWACT+2B      GET ARGUMENT MAX-MIN DESCRIPTOR.
         LB        3,ARGMAX,3      GET MAX. NO. OF EXPRESSIONS.
         SUMW      3,GRPW          SUBTRACT NO. OF EXPRESSIONS PRESENT.
         SUI       3,6             CONVERT TO 0 - 5 RANGE.
         BEQ       AGEM0        INDEX REG. WAS SPECIFIED.
         TBM       11,HWINDR       IS INDIRECT ADDRESSING SPECIFIED?
         BS        AGEM2        YES.
         TBM       ADDRERR,HHBITS2   WAS THERE AN ADDRESSING BOUNDARY
*                                    ERROR?
         BNS       AGEM2        NO.
         BU        AGEM1           GO MARK B ERROR.
AGEM0    ANMW      6,=X'001FFFFF'  THROW AWAY TYPE CODE
         CI        6,0             MAX INDEX REG VALUE SHOULD BE 3
         BCF       LE,AGEM1        INDEX REGISTER VALUE TOO LARGE.
         TBR       7,0             IS THE REGISTER 2 OR 3?
*        BS        AGEM2        YES, OKAY.
         BS        AGEM0.A      YES, OKAY.
         TBR       7,1             IS IT REGISTER 1?
*        BS        AGEM2        YES, OKAY.
         BNS       AGEM1        NO
AGEM0.A  TBM       BM.OPT,OPTION   CHECK IF BASE MODE
         BNS       AGEM2          NO, OKAY
         SLLD      6,2            FIX UP INDEX REG. FIELD, SHIFT REG.
         SLL       7,1            GET 20 BIT ADDRESS
         SRLD      6,2            PUT BACK INDEX REGISTER
         SRL       7,1            ADJUST TO 3 BIT FIELD
         BU        AGEM2
AGEM1    BL        YEANAY          ASSEMBLY GOING ON?
         BNS       AGEM2        NO
         SBM       G'B'-X'40',HWERRF   FLAG THE ERROR AND COUNT IT
         ABM       31,HWERCT
AGEM2    TRR       1,6             GET GENERAL REGISTER VALUE
         ZBM       ADDRERR,HHBITS2   CLEAR ADDRESSING BOUNDARY ERROR
*                                  FLAG.
         SPACE
* COME HERE TO ISSUE 32 BIT INSTRUCTION
* R7,B0-22 EQUAL B9-31 OF INSTRUCTION, R6,B29-31 EQUAL B6-8 OF INST
         SPACE
AGEP     SRLD      6,3             R7,B0-25 EQUAL B6-31 OF INST
         ANMW      6,=X'000FFFFF'  THROW AWAY TYPE CODE
         CI        6,0             MAXIMUM GENERAL REGISTER NUMBER IS 7
         BCF       LE,AGEPA        TOO LARGE, GO MARK ERROR.
         ZR        6               ZERO REGISTER 6.
         LW        4,=X'E0000000'  MASK TO GET GEN. REG. NUMBER.
         TRRM      7,6             GET GEN. REG. NUMBER.
         BNE       AGEP2        IT IS NOT ZERO--OK.
         LW        6,HWACT         GET OPERATION DESCRIPTOR WORD.
         CAMW      6,=X'EE01230D'  IS OPERATION BCT ?
         BEQ       AGEPA        YES, GO MARK ERROR.
         CAMW      6,=X'F201230D'  IS OPERATION BCF ?
         BNE       AGEP2        NO--OK.
AGEPA    BL        YEANAY          ASSEMBLY GOING ON?
         BNS       AGEP2        NO
         SBM       G'B'-X'40',HWERRF
         ABM       31,HWERCT
AGEP2    LI        3,-4            INDICATE RELEASE OF 4 EIGHT BIT BYTES
AGEPB    LB        6,HWACT         OP CODE PLUS BOUND INFO
         ZBM       EIS.OPC,EISFLG  RESET THRU CONTEXT INST FLAG EINS-31
         CI        R6,X'56'        IS IT STCX?                  EINS-31
         BEQ       AGEPB.1         BR IF IT IS                  EINS-31
         CI        R6,X'5A'        IS IT LCRA?                  EINS-31
         BEQ       AGEPB.1         BR IF IT IS                  EINS-31
         CI        R6,X'5E'        IS IT LCX?                   EINS-31
         BNE       AGEPC.1         BR IF NOT                    EINS-31
AGEPB.1  SBM       EIS.OPC,EISFLG SET TASK SPACE IND. FOR LSTNG EINS-31
AGEPC.1  CEQU      $                                            ESCT-32
         SRL       6,2             R6 EQUALS OP CODE
         SRLD      6,6             PUT WHOLE INSTRUCTION INTO R7
         SPACE
*        AN INSTRUCTION IS NOW LEFT JUSTIFIED IN R7
         SPACE
AGEPC    SLLD      6,8             GET ONE BYTE OF INSTUCTION
         BL        IGEN            GEN BYTE 1
         BIB       3,AGEPC         DO ALL OF THE REQUIRED BYTES
         BU        NEXT            GO PRINT INST AND CONTINUE
         TITLE     READ-ONLY       BM, BI, BU, FPP
* PROCESS SBM, ZBM, ABM, TBM
* R1 = BIT NUMBER, R2 = ADDRESS
         SPACE
BM       LW        4,=X'007FFFFF'  MASK FOR THE VALUEPART ONLY
         TRRM      1,0             TAKE THE VALUE OF THE BIT NUMBER .B0
         SPACE
*        R1   WILL GET TRUNCATED LATER IN AGEN
         SPACE
         SRL       0,3             EFFECTIVE DIVISION BY 8 TO GET BYTE D
*                                                               |86.0952
         STW       R1,BM.TMP       SAVE R1                      |86.0952
         TRR       R2,R1           COPY R2                      |86.0952
         SRL       R1,24           EXTRACT TYPE CODE            |86.0952
         CI        R1,6            IS THE ADDRESS EXTERNAL      |86.0952
         BNE       BM.01           SKIP IF IT IS                |86.0952
         CI        R0,3            IS EFFECTIVE ADDR >1W DISP   |86.0952
         BLE       BM.01           SKIP IF NOT                  |86.0952
         SBM       G'B'-X'40',HWERRF   ELSE ISSUE A BOUND MSG   |86.0952
         ABM       31,HWERCT           AND COUNT IT             |86.0952
         ZR        R0       0 THE BUMP SO STRNGBCK WON'T ABORT  |86.0952
         BU        BM.01           AND CONTINUE                 |86.0952
BM.TMP   DATAW     0               HOLD R1 DURING TEST          |86.0952
BM.01    LW        R1,BM.TMP       RECOVER R1                   |86.0952
*                                                               |86.0952
         ADR       0,2             ADD THE DISPLACEMENT TO THE ADDRESS
         ANMW      1,=X'00000007'  LEAVE ONLY THE BIT NUMBER
         BU        AGEN            PROCESS IN MEMORY REFERENCE NODE
         SPACE
* PROCESS BIB,BIH,BIW,BID
         SPACE
BI       STW       2,HWEVAL        SAVE ADDRESS FIELD FOR PRINTOUT.
         BL        AGEQ            PUT ADDRESS WORD TOGETHER WITH F,CC,I
         SLL       7,11            ADDRESS AND INDR IN R7,B0-20
         TRR       5,6             GET AUGMENT CODE.
         SRLD      6,2             INTO R7,B0-1 (B2-22=ADDR)
         BU        AGEM2           PROCESS AS NORMAL INSTRUCTION.
         SPACE
* PROCESS BRANCH UNCONDITIONAL,EXM,ZM,BL,BRI,BFT
         SPACE
ZMX      CEQU      $               ZERO MEMORY ENTRY POINT      ENSB-33
BU       TRR       2,3             TRANSFER INDEX TO NORMAL PLACE
         TRR       1,2             ADDRESS FIELD TO NORMAL PLACE
         TRR       5,1             AUGMENT RT JUST FOR B6-8 OF INST
         BU        AGEN            PROCESS AS NORMAL INST
         SPACE
*  BIASED ADDRESS CONSTANT PROCESSOR                            EBAC-33
         SPACE
BACX     TBM       ASCT.OPT,OPTION   AUTO SECTIONING ON?        EBAC-33
         BNS       BU              GENERATE ACW/ACH IF NOT      EBAC-33
         SBM       1,BACFLAG       SHOW BACX READ               EBAC-33
         TBR       R1,0            IS THIS A CSECT ADDRESS?     EBAC-33B
         BNS       $+2W            NO...BRANCH                  EBAC-33B
         SBM       2,BACFLAG       ELSE SET FLAG FOR CSECT ADDR EBAC-33B
         TRR       2,3             TRANSFER INDEX TO R3         EBAC-33
         TRR       1,2             TRANSFER ADDR FIELD TO R2    EBAC-33
         TBM       3,BACFLAG       BAC OF AN EXTERNAL ADDRESS?  EBAC-33C
         BNS       $+2W            NO...BRANCH                  EBAC-33C
         ORMW      R2,=X'0608FFFF'  ELSE FILL WITH TERMINAL VAL EBAC-33C
         TRR       5,1             AUGMENT CODE TO R1           EBAC-33
         STW       R2,HWEVAL       SAVE ADDR FOR PRINTOUT       EBAC-33
         BL        AGEQ            FORM ADDRESS                 EBAC-33
         ANMW      R7,=X'00FFFFFF' MASK ADDR TO 24 BITS         EBAC-33B
         LI        R3,-4           FOUR BYTES TO OUTPUT         EBAC-33
BACX.1   SLLD      R6,8            GET ONE BYTE                 EBAC-33
         BL        IGEN            GENERATE ONE BYTE            EBAC-33
         BIB       R3,BACX.1       DO ALL FOUR                  EBAC-33
         BU        NEXT            PRINT THIS INSTR, GET NEXT   EBAC-33
         SPACE
BACFLAG  REZ       1B                                           EBAC-33
         BOUND     1W
* FLOATING POINT INSTRUCTION SET PROCESSOR
         SPACE
FPP      STW       2,HWEVAL        SAVE ADDRESS FIELD FOR PRINTOUT
         BL        AGEQ            PUT ADDRESS WORD TOGETHER WITH F,CC,I
         SRC       5,2             AUGMENT TO BIT 1
         SLL       7,11            MOVE ADDRESS TO B0-20
         ZBR       7,1             CLEAR AUGMENT
         ORR       5,7             SET AUGMENT (R7 B020 = INST B11-31)
         BU        AGEM            PROCESS IN MAIN 32 BIT NODE
         TITLE     READ-ONLY       TRIP, EXR, IMOP
*        PROCESS 32 BIT NON-MEMORY REFERENCE INSTRUCTIONS
* TRANSLATE REGISTER/PROTECT REGISTER OPS
         SPACE
TRIP     TRR       1,6             REGISTER NO. TO R6
         SRLD      6,3             REGISTER NO. TO R7,B0-2
         ANMW      6,=X'000FFFFF'  THROW AWAY TYPE CODE.
         CI        6,0             MAX. GENERAL REG. NUMBER IS 7.
         BLE       TRIP1        WITHIN VALUE PERMITTED.
         BL        YEANAY          ASSEMBLY GOING ON?
         BNS       TRIP1        NO.
         SBM       G'B'-X'40',HWERRF   MARK 'B' ERROR
         ABM       31,HWERCT           COUNT THE ERROR
TRIP1    SLL       5,4             4 ZEROES ON RIGHT OF AUGMENT
         ANMB      2,=X'F'         RESTRICT VALUE OF PROTECT REG.
         ORR       2,5             COMBINE AUGMENT AND PROTECT REG.
*                                  INTO A 7 BIT FIELD.
         TRR       5,6             AUGMENT,PROTECT REG. TO R6
         SRLD      6,7             R7,B0-25 CONTAIN B6-31 OF
*                                  INSTRUCTION.
         BU        AGEP2           GO RELEASE THE BYTES.
         SPACE
*!INT!!!!!!ZR!!!!!!!!2!!!!!!!!!!!!!!!THIS!WILL!EVENTUALLY!BE!RI!EASC-32
*!!!!!!!!!!BU!!!!!!!!IO!!!!!!!!!!!!!!MAKE!A!32!BIT!INSTRUCTION!!EASC-32
         SPACE
* EXECUTE REGISTER PROCESSOR
         SPACE
EXR      LI        2,X'F'          GET A MASK FOR THE RIGHT/LEFT AUFMENT
         ANMB      2,HWACT+1B      FETCH DESIGNATOR FOR EXT OR EXRR
         SPACE
* PROCESS IMMEDIATE TYPE OPERATIONS
         SPACE
IMOP     SLL       1,4             PUT 4 BITS OF ZEROS IN FOR FILLING
IO       TRR       2,6             FETCH IMMEDIATE QTY
         CI        R5,10           TEST AUGMENT VALUE           ENIS-32B
         BNE       IO.0            BRANCH IF NOT RINTV INSTR.   ENIS-32B
         SRL       R7,8            CLEAR BITS 24-31 OF QTY      ENIS-32B
         SRLD      R6,8            SHIFT IN IMMEDIATE QTY       ENIS-32B
         BU        IO.01           CONTINUE                     ENIS-32B
IO.0     SRLD      6,16            POSITION IN B0-15 OF R7
IO.01    TRR       5,6             FETCH AUGMENT
         CI        R6,9            IS IT A PINTV INSTR?         ENIS-32C
         BEQ       IO.02           BRANCH IF SO                 ENIS-32C
         CI        R6,10           IS IT A RINTV INSTR?         ENIS-32C
         BNE       IO.03           BRANCH IF NOT                ENIS-32C
IO.02    SRLD      6,4             POSITION AUGMENT             ENIS-32B
         BU        IO.1            CONTINUE                     ENIS-32B
IO.03    CEQU      $                                            ENIS-32C
         SRLD      6,3             PLACE THE AUGMENT FIELD INTO INSTRUCT
IO.1     TRR       1,6             REGISTER NO. TO R6
         ANMW      6,=X'007FFFFF'  LOP OFF ANY TYPE CODES
         CI        R5,9            IS IT A PINTV INSTR?         ENIS-32C
         BEQ       IO.04           BRANCH IF SO                 ENIS-32C
         CI        R5,10           IS IT A RINTV INSTR?         ENIS-32C
         BNE       IO.2            BRANCH IF NOT                ENIS-32C
IO.04    SRLD      R6,3            SHIFT IN SOME ZEROS          ENIS-32B
         SRL       R6,1            POSITION REGISTER NUMBER     ENIS-32B
         BU        AGEP            FINISH GENERATING INSTR      ENIS-32B
IO.2     SRLD      6,4             AUGMENT OR DEVICE SPLIT IN R6 AND R7
         BU        AGEP            FINISH INST IN COMMON NODE
         TITLE     READ-ONLY       SETCPU, SVC, EXTIO
*PROCESS SETCPU AND RDSTS INSTRUCTION
         SPACE
SETCPU   TRR       1,2             PUT SOURCE REG INTO DEST REG POSITION
         ZR        1               ZERO SOURCE REG POSITION
         BU        RRO             CONTINUE AT COMMON NODE
         SPACE     1
*PROCESS SERVICE CALL INSTRUCTION
         SPACE
SVC      TRR       2,3             CALL NUMBER OR NULL
         TRR       1,2             INDEX VECTOR OR CONSTANT
         ZR        1               ZERO REG NUM
         LW        6,GRPW          NUM OF ARGS PRESENT COUNTER
         ADI       6,6             CONVERT TO A 0-5 RANGE
         CI        6,1             IS NUM OF ARGS = 1 ?
         BEQ       IMOP            YES - FINISH AS IMM MODE INSTRUCTION
         SLL       2,12            LEFT JUSTIFY INDEX VECTOR
         ADR       3,2             COMBINE WITH CALL NUMBER
         BU        IMOP            FINISH AS IMM MODE INSTRUCTION
         SPACE     1
* PROCESS TRAP CONTROL INSTRUCTION                              ENIS-32
         SPACE                                                  ENIS-32
TRAP     LW        R4,=X'0000001F' 5 BIT FIELD MASK             ENIS-32
         TRRM      R2,R3           FUNCTION SELECT TO R3        ENIS-32
         TRRM      R1,R2           TRAP SELECT TO R2            ENIS-32
         SLL       R2,8            TRAP SELECT TO 2ND BYTE      ENIS-32
         ADR       R3,R2           COMBINE TRAP AND FUNCTION    ENIS-32
         TRR       R2,R6                                        ENIS-32
         SRLD      R6,16           POSITION IN INSTRUCTION      ENIS-32
         TRR       R5,R6           GET AUGMENT CODE             ENIS-32
         SRLD      R6,4            POSITION IN INSTRUCTION      ENIS-32
         SRL       R7,6            SET UP FOR OPCODE            ENIS-32
         LB        R6,HWACT        GET INSTRUCTION DESCRIPTOR   ENIS-32
         SRL       R6,2            REMOVE BOUNDING BITS         ENIS-32
         SRLD      R6,6            POSITION OPCODE IN INSTR.    ENIS-32
         LI        R3,-4           PROCESS 4 BYTES              ENIS-32
         BU        AGEPC           PROCESS INSTRUCTION          ENIS-32
         SPACE     1                                            ENIS-32
* PROCESS EXTENDED I/O INSTRUCTIONS
         SPACE
EXTIO    LW        6,GRPW          NUM OF ARGS PRESENT COUNTER
         ADI       6,6             CONVERT TO A 0-5 RANGE
         CI        6,2             IS NUM OF ARGS = 2 ?
         BEQ       EXTIO1          YES - OK
         SLL       2,8             LEFT JUSTIFY CHANNEL ADDRESS
         ADR       3,2             ADD IN SUBCHANNEL ADDRESS
EXTIO1   TRR       1,6             REG NUM TO R6
         LB        7,HWACT+1B      FETCH SUB-OPERATION CODE
         SLL       7,28            LEFT JUSTIFY SUB-OPERATION CODE
         SLLD      6,4             COMBINE REG NUM AND SUB-OP CODE
         TRR       6,1             REG NUM AND SUB-OP CODE TO R1
         BU        IO              CONTINUE AS AN IMM MODE INSTRUCTION
         TITLE     READ-ONLY       SPACE
* PROCESS SPACE PSEUDO-OP
         SPACE
SPACE    LI        2,2             SIGNAL VAL TO SKIP LEADING SPACES
         BL        VAL             EVALUATE EXPRESSION
         ANMW      R7,=X'7FFFFF'   LOP OFF ANY TYPE CODES
         CI        7,1             LOWER THAN THIS DEFAULTS TO 1
         BGE       $+2W            IT IS HIGHER-THEN DONT DEFAULT
         LI        7,1             DEFAULT SPACE COUNT
         CI        7,60            MAX NO. OF SPACES ALLOWED
         BLT       SPACEA
         BL        YEANAY          ARE WE ASSEMBLING?
         BNS       NEXT         NO.
         SBM       G'G'-X'40',HWERRF  MARK G ERROR
         ABM       31,HWERCT       COUNT THE ERROR
         BU        NEXT            GO RELEASE IMAGE AND DON'T SPACE.
SPACEA   TRN       7,5             NEG NUMBER OF LINES TO SPACE
         TBM       7,HBPASS        IS THIS PASS 2
         BS        NEXT         NO, IGNORE SPACE PSEUDO
         TBM       APON,HHBITS     CHECK WHETHER LISTING IS ALLOWED.
         BS        NEXT         NO LISTING REQUIRED.
         TBM       EXPAND,MACSTATE EXPANDING?
         BNS       SPACEA1      NO.
         TBM       MACPRINT,HHBITS2  EXPANSION LIST ALLOWED?
         BS        NEXT         NO.
SPACEA1  TBM       RPTGEN,MACSTATE  GENERATING REPEATED CODE?
         BNS       SPACE1       NO.
         TBM       REPPRINT,HHBITS2   REPEAT EXPANSION LIST ALLOWED?
         BS        NEXT         NO.
SPACE1   LW        1,HWUP1         TCW FOR A SHORT BLANK LINE
         BL        YEANAY          CHECK WHETHER ASSEMBLY IS ALLOWED
         BNS    NEXT            DONT ASSEMBLE
         ZR        7               SIGNALS CPPP THAT NO ERRORS EXIST
*                                  FOR THIS LINE.
         BL        PPP            PRINT ONE SPACE EQ BLANK LINE
         TBR       7,31            DID WE GO TO A NEW PAGE
         BS        $+2W         YES, ON A NEW PAGE NO MORE SPACES
         BIB       5,SPACE1
         ZBM       IMIN,HHBITS     INDICATE NO BUFFER IMAGE READY
         BU        NEXT            GO GET NEXT INPUT ITEM
         TITLE     READ-ONLY       LIST
* PROCESS LIST PSEUDO-OP TO CONTROL PRINTOUTS
         SPACE
LIST     TBM       APON,HHBITS     IS 'LIST OFF' ?
         BS        LIST00       YES.
         TBM       EXPAND,MACSTATE   EXPANDING?
         BNS       LIST01       NO.
         TBM       MACPRINT,HHBITS2  EXPANSION LIST ALLOWED?
         BS        LIST00       NO.
LIST01   TBM       RPTGEN,MACSTATE  GENERATING REPEATED CODE?
         BNS       LIST0        NO.
         TBM       REPPRINT,HHBITS2   REPEAT EXPANSION LIST ALLOWED?
         BNS       LIST0        YES.
LIST00   ZBM       IMIN,HHBITS     SUPPRESS P/O OF LIST DIRECTIVE.
LIST0    LW        1,=X'80080000'  SP AND ,
         BL        UNST            UNSTRING ONE DESIGNATOR (TERM.IN R7)
         LW        6,HWNAME        FETCH UNSTRUNG DESIGNATOR
         IFT       ULC,SKIP                                     *JCB*
         LI        R0,-4           FOUR BYTES TO TEST           *JCB*
LIST.U   TBR       R6,1            THIS A LETTER                *JCB*
         BNS       LIST.U1         BR IF NOT                    *JCB*
         ZBR       R6,2            YES, CONVER TO UPPER CASE    *JCB*
LIST.U1  SRC       R6,8            NEXT BYTE                    *JCB*
         BIB       R0,LIST.U       DO 4 BYTES                   *JCB*
SKIP     ANOP                                                   *JCB*
         LI        1,-10W          NEGATIVE NUMBER OF LIST OPTIONS
         CAMW      6,LISTD+1W,1    COMPARE AGAINST ITEM IN LIST
         BEQ       LIST1        A FIND
         BIW       1,$-2W          NO FIND, SEARCH ALL OF LIST
         BL        YEANAY          ARE WE ASSEMBLING?
         BNS       LIST2        NO.
         SBM       G'K'-X'40',HWERRF  MARK K ERROR
         ABM       31,HWERCT       COUNT THE ERROR
         BU        LIST2           CHECK TERMINATOR
         SPACE
* COME HERE WHEN A MATCH IS FOUND IN THE DIRECTIVE LIST
         SPACE
LIST1    BL        YEANAY          CHECK WHETHER ASSEMBLY IS ALLOWED
         BNS    LIST2           DONT ASSEMBLE
         EXM         LISTP+1W,1    FLAG VALUE FOR FIND
LIST2    CI        7,G','          IS TERMINATOR A COMMA
         BEQ       LIST0        YES--GO PROCESS OTHER DIRECTIVES.
         BU        NEXT            NO, PRINT CARD OUT
*
* (C) COPYRIGHT 1983 ENCORE COMPUTER CORPORATION
*     ALL RIGHTS RESERVED
*
         TITLE     READ-ONLY       TITL
* TITLE PSEUDO-OP TRANSLATION
         SPACE
TITL     ZMB       HBTITM          CHAR COUNT FOR TITLE
         LW        R0,HWKSPA       WORD OF SPACES TO CLEAR TITLE BUFFER
         LA        R1,TCWTITL      ADDRESS O TITLE BUFFER
TITL0    STW       R0,0,R1         CLEAR TITLE BUFFER
         ADI       R1,4            INCREMENT POINTER
         CAMW      R1,=TCWTTLE     CHECK FOR END OF TITLE BUFFER  83-451
         BLT       TITL0           BRANCH IF NOT DONE
TITL1    LW        1,=X'80800000'  TERMINATORS IGNORED-CONVENTION ONLY
         BL        GBYT            READ CHARACTER INTO R6
         LB        R7,HBIBYI       CHECK INPUT CHAR POSITION
         CI        R7,72           HAS END OF LINE BEEN REACHED?
         BGT       PAGP            BRANCH IF END OF LINE (NO TITLE)
         CI        R6,G' '         IS CHARACTER A SPACE
         BEQ       TITL1           SKIP LEADING SPACES
         BU        TITN0           GO STORE FIRST CHARACTER IN TITLE
TITN     LW        1,=X'80800000'  TERMINATORS IGNORED-CONVENTION ONLY
         BL        GBYT            GET ONE FULL ASCII BYTE
TITN0    TBM       7,HBPASS        WHICH PASS?
         BS        TITN1        PASS 1 - DON'T STORE TITLE.
         BL        YEANAY          ASSEMBLY GOING ON?
         BNS       $+4W         NO, DON'T STORE TITLE.
         LB        1,HBTITM        CHAR COUNT FOR TITLE
         STB       R6,TCWTITL+1,R1  STORE CHARACTER
         ABM       7,HBTITM        CHAR COUNT FOR TITLE
TITN1    LB        7,HBIBYI        GET INPUT POINTER
         CI        7,72            CHECK FOR ALL DONE (COL 72)
         BGT       PAGP         72 FOUND, THAT IS ALL
         CI        R1,TCWTTLE-TCWTITL-2 IS TITLE BUFFER FULL      83-451
         BLT       TITN
         TITLE     READ-ONLY       PAGP
* PAGE PSEUDO-OP COMES HERE AND TITLE FALLS THRU HERE ALSO
         SPACE
PAGP     TBM       APON,HHBITS     CHECK WHETHER LISTING IS ALLOWED
         BS        NEXT         NO LISTING REQD
         TBM       EXPAND,MACSTATE   EXPANDING?
         BNS       PAGP11       NO.
         TBM       MACPRINT,HHBITS2  EXPANSION LIST ALLOWED?
         BS        NEXT         NO.
PAGP11   TBM       RPTGEN,MACSTATE  GENERATING REPEATED CODE?
         BNS       PAGP1        NO.
         TBM       REPPRINT,HHBITS2   REPEAT EXPANSION LIST ALLOWED?
         BS        NEXT         NO.
PAGP1    CEQU      $                                            ESCT-32
         TBM       7,HBPASS        WHICH PASS
         BS        NEXT         PASS 1 - NO PROCESSING
         BL        YEANAY          CHECK WHETHER ASSEMBLY IS ALLOWED
         BNS    NEXT            DONT ASSEMBLE
         LW        6,HATCWD        LGTH AND ADR OF HEADING LINE.
         BL        EJCT            TOP-OF-FORM IF LO IS ALLOWED.
         ZBM       IMIN,HHBITS     INDICATE NO BUFFER IMAGE READY
         BU        NEXT
         TITLE     READ-ONLY       PROG
* PROCESS PROGRAM PSEUDO-OP
         SPACE
PROG     CEQU      $                                            ESCT-32
         BL        YEANAY          CHECK WHETHER ASSEMBLY IS ALLOWED
         BNS    PROG1           DONT ASSEMBLE
         SBM       PROGF,HHBITS    FLAG THE PROGRAM STATEMENT
         BNS       PROG1        THIS WAS THE FIRST PROGRAM STATEMENT
         SBM       G'P'-X'40',HWERRF  MARK P ERROR
         ABM       31,HWERCT       COUNT THE ERROR
         BU        NEXT
PROG1    CEQU      $                                            ESCT-32
*!!!!!!!!LW!!!!!!!!1,=X'80000000'!!TERMINATE!ON!A!SPACE!!!!!!!!!C012-34
         LW        R1,=X'80080000'  TERMINATE ON SPACE,COMMA    C012-34
         BL        UNST            UNSTRING PROGRAM NAME
*     ALWAYS PROCESS PROG NAME AND UNSTRING ID INFO IF OPT. 14  C012-34
*!!!!!!!!BL!!!!!!!!YEANAY!!!!!!!!!!CHECK!WHETHER!ASSEMBLY!IS!!!!C012-34
*!!!!!!!!BNS!!!!NEXT!!!!!!!!!!!!DONT!ASSEMBLE!!!!!!!!!!!!!!!!!!!C012-34
         LD        6,HWNAME        FETCH 8 CHAR PROGRAM NAME
         STD       6,TCWPROG       STORE PROGRAM NAME
         ZMB       PROD.IDL        CLEAR PROD ID LENGTH            11007
         TBM       ID.OPT,OPTION   IS ID PERMITTED??               11007
         BNS       NEXT            NO - DON'T LOOK FOR MORE ON PROG11007
         LW        1,=X'80000000'  TERMINATE ON A SPACE            11005
         BL        UNST            UNSTRING PRODUCT ID INFO        11005
         BL        YEANAY          CHECK IF ASSEMBLY ALLOWED       11005
         BNS    NEXT            DONT ASSEMBLE                      11005
         LW        R3,UNSTNP       GET UNST POINTER (BYTE COUNT)   11005
         ADI       R3,3            ADD IN BYTES FOR 'WORD ROUNDING'11006
*                                  SHIFT RT THEN LF (DIV BY 4,     11006
*                                    THEN MULT BY 4)               11006
         SRL       R3,2            HOW MANY WORDS? IGNORE REMAINDER11006
         SLL       R3,2            TAKE BACK TO BYTES              11006
         CI        R3,20           CHECK FOR MAX SIZE FOR ID INFO  11005
         BLE       $+2W            OK - CONTINUE                   11005
         LI        R3,20           IF GT, FORCE TO MAX FOR ID INFO 11005
         STB       R3,PROD.IDL     SAVE IN PRODUCT ID LENGTH       11005
         ZR        R2              INITIALIZE INDEX                11005
         TRN       R3,R3           SET UP TO MOVE DATA             11005
         BZ        NEXT            NO DATA TO MOVE                 11005
PROG2    LB        R6,HWNAME,R2    GET BYTE                        11005
         STB       R6,PROD.ID,R2   SAVE FOR XFER TO OBJECT LATER   11005
         ABR       R2,31           INCREMENT INDEX                 11005
         BIB       R3,PROG2        DO NECESSARY NUMBER             11005
         BU        NEXT            FINISHED THIS STATEMENT
         IFT       CAID,SKIP                                    *CAID*
         TITLE     READ-ONLY       STAB                         *CAID*
* PROCESS CAID PSEUDO-OPS                                       *CAID*
* .SRC   SOURCE COMMAND                                         *CAID*
* .COM   COMMENT LINE                                           *CAID*
* .ARG   ARGUMENT DEFINITION                                    *CAID*
* .XEQ   EXECUTABLE SOURCE LINE                                 *CAID*
* .SYM   SYMBOL DEFINITION                                      *CAID*
* .STAB  STRUCT/ENUM DEFINITION                                 *CAID*
* .STABC STRUCT/ENUM COMPONENT                                  *CAID*
         SPACE                                                  *CAID*
* LOCAL VARIABLES                                               *CAID*
DUMMYN   DATAD     0               DUMMY LOC FOR USNAME         *CAID*
SUNAME   DATAD     0               STRUCT/UNION NAME            *CAID*
STEMP    DATAW     0               JUST A TEMP                  *CAID*
STEMP2   DATAW     0               JUST A TEMP                  *CAID*
VSIZE    DATAW     0               VARIABLE SIZE                *CAID*
STKOFF   DATAW     0               STACK OFFSET OF VARIABLE     *CAID*
LOWER    REZ       16W             LOWER ARRAY BOUNDS (ZERO)    *CAID*
UPPER    REZ       16W             UPPER ARRAY BOUNDS (SIZE-1)  *CAID*
SLINE    RES       80B             THE SOURCE LINE              *CAID*
SCHAR    RES       1B              THE CHARACTER READ IN        *CAID*
CHARCNT  DATAB     0               CHARS IN SOURCE LINE         *CAID*
BLNKCNT  DATAB     0               BLANKS AT START OF LINE      *CAID*
PTRCNT   DATAB     0               POINTER CMDS FOUND           *CAID*
ARYCNT   DATAB     0               ARRAY CMDS FOUND             *CAID*
VTYPE    DATAB     0               VARIABLE TYPE                *CAID*
REGVAL   DATAB     0               REGISTER VARIABLE NUMBER     *CAID*
NOSYM    DATAB     0               AUTO, REG, OR HSYM IF SET    *CAID*
SFLAGS   DATAB     0               FLAG BYTE TO OUTPUT          *CAID*
         SPACE                                                  *CAID*
         BOUND     1W                                           *CAID*
STAB     CEQU      $                                            *CAID*
         LI        R7,2            DEFAULT TO INTEGER TYPE      *CAID*
         STB       R7,VTYPE        SET VARIABLE TYPE            *CAID*
         ZMB       PTRCNT          CLEAR POINTER COUNT          *CAID*
         ZMB       ARYCNT          CLEAR ARRAY COUNT            *CAID*
         ZMB       REGVAL          CLEAR REGISTER VAR NUMBER    *CAID*
         ZMB       NOSYM           CLEAR NO SYM FLAG            *CAID*
         ZMB       SFLAGS          CLEAR FLAGS BYTE             *CAID*
         LB        R7,HWACT+1B     FETCH SUB-OPERATION CODE     *CAID*
         SRL       R7,4            JUST THE AUG CODE            *CAID*
         CI        R7,4            IS IT .SYM                   *CAID*
         BNE       STAB.50         CONTINUE IF NOT              *CAID*
* PROCESS .SYM PSEUDO OP                                        *CAID*
* UNSTRING ONE ELEMENT SKIPPING LEADING BLANKS                  *CAID*
         LW        R1,=X'80000000' TERMINATE ON A SPACE         *CAID*
* GET _SYMBOL WE ARE DEFINING.  SYMBOL IN HWNAME                *CAID*
         BL        UNST            UNSTRING SYMBOL NAME         *CAID*
         LD        R6,HWNAME       FETCH 8 CHAR SYMBOL NAME     *CAID*
         CAMW      R6,BLANKS       ANY NAME GIVEN               *CAID*
         BNE       STAB.01         YES, WE HAVE ONE             *CAID*
* BAD INPUT, GIVE 'F' ERROR                                     *CAID*
         SBM       G'F'-X'40',HWERRF  MARK F ERROR              *CAID*
         ABM       31,HWERCT       COUNT THE ERROR              *CAID*
         BU        NEXT            WE ARE DONE HERE             *CAID*
STAB.01  STD       R6,DUMMYN       STORE PROGRAM NAME           *CAID*
* NOW SCAN OFF THE PARAMETERS FOR THE SYMBOL                    *CAID*
STAB.02  LW        R1,=X'80000000' TERMINATE ON A SPACE         *CAID*
         BL        UNST            UNSTRING PARAMETER           *CAID*
         LD        R6,HWNAME       FETCH PARAMETER              *CAID*
         CAMW      R6,BLANKS       ANYTHING THERE?              *CAID*
         BEQ       STAB.40         NO, BUILD THE DEBUG INFO     *CAID*
* MAKE COMMAND UPPER CASE                                       *CAID*
         LI        R1,-8           SET UP FOR 8 BYTES           *CAID*
STAB.03  CI        R1,-4           ARE WE HALF WAY YET?         *CAID*
         BNE       STAB.04         NO, KEEP CONVERTING          *CAID*
         XCR       R6,R7           SWITCH REGS                  *CAID*
STAB.04  TBR       R6,1            IS IT A LETTER               *CAID*
         BNS       STAB.05         NO, LEAVE IT ALONE           *CAID*
         ZBR       R6,2            FORCE TO UPPER CASE          *CAID*
STAB.05  SRC       R6,8            POSITION NEXT BYTE           *CAID*
         BIB       R1,STAB.03      GO TEST FOR END OF WORD      *CAID*
         XCR       R6,R7           PUT BACK REGS                *CAID*
* R6 AND R7 HAVE U/C PARAMETER, SEE WHAT IT IS                  *CAID*
         CAMW      R6,=C'PTR '     IS IT A POINTER              *CAID*
         BNE       STAB.06         NO, KEEP LOOKING             *CAID*
         ABM       7,PTRCNT        BUMP POINTER COUNT           *CAID*
         SBM       2,SFLAGS        SET POINTER TYPE FLAG        *CAID*
         BU        STAB.02         GO GET NEXT PARAMETER        *CAID*
STAB.06  CAMW      R6,=C'ARY '     IS IT AN ARRAY               *CAID*
         BNE       STAB.07         NO, KEEP LOOKING             *CAID*
* GET ARRAY BOUNDS                                              *CAID*
         LI        R2,2            SKIP BLANKS                  *CAID*
         BL        VAL             GET ARRAY VALUE              *CAID*
         ANMW      R7,=X'7FFFFF'   JUST THE VALUE               *CAID*
         LB        R3,ARYCNT       GET ARRAY COUNTER            *CAID*
         SLL       R3,2            MAKE WORD OFFSET             *CAID*
         STW       R7,LOWER,X3     SAVE THE VALUE               *CAID*
         LI        R2,2            SKIP BLANKS                  *CAID*
         BL        VAL             GET ARRAY VALUE              *CAID*
         ANMW      R7,=X'7FFFFF'   JUST THE VALUE               *CAID*
         LB        R3,ARYCNT       GET ARRAY COUNTER            *CAID*
         SLL       R3,2            MAKE WORD OFFSET             *CAID*
         STW       R7,UPPER,X3     SAVE THE VALUE               *CAID*
         ABM       7,ARYCNT        BUMP ARRAY COUNT             *CAID*
         SBM       1,SFLAGS        SET ARRAY TYPE FLAG          *CAID*
         BU        STAB.02         GO GET NEXT PARAMETER        *CAID*
STAB.07  CAMW      R6,=C'CHAR'     IS IT A CHARACTER            *CAID*
         BNE       STAB.08         NO, KEEP LOOKING             *CAID*
* SET TYPE TO 0                                                 *CAID*
         ZMB       VTYPE           CHAR IS 0                    *CAID*
         BU        STAB.02         GO GET NEXT PARAMETER        *CAID*
STAB.08  CAMW      R6,=C'SHOR'     IS IT A SHORT                *CAID*
         BNE       STAB.09         NO, KEEP LOOKING             *CAID*
         CAMW      R7,=C'T   '     IS IT A SHORT                *CAID*
         BNE       STAB.09         NO, KEEP LOOKING             *CAID*
* SET TYPE TO 1                                                 *CAID*
         LI        R7,1            SHORT IS 1                   *CAID*
         STB       R7,VTYPE        SET TYPE                     *CAID*
         BU        STAB.02         GO GET NEXT PARAMETER        *CAID*
STAB.09  CAMW      R6,=C'INT '     IS IT A INT                  *CAID*
         BNE       STAB.10         NO, KEEP LOOKING             *CAID*
* SET TYPE TO 2                                                 *CAID*
         LI        R7,2            INT IS 2                     *CAID*
         STB       R7,VTYPE        SET TYPE                     *CAID*
         BU        STAB.02         GO GET NEXT PARAMETER        *CAID*
STAB.10  CAMW      R6,=C'LONG'     IS IT A LONG                 *CAID*
         BNE       STAB.11         NO, KEEP LOOKING             *CAID*
* SET TYPE TO 3                                                 *CAID*
         LI        R7,3            LONG IS 3                    *CAID*
         STB       R7,VTYPE        SET TYPE                     *CAID*
         BU        STAB.02         GO GET NEXT PARAMETER        *CAID*
STAB.11  CAMW      R6,=C'FLOA'     IS IT A FLOAT                *CAID*
         BNE       STAB.12         NO, KEEP LOOKING             *CAID*
         CAMW      R7,=C'T   '     IS IT A FLOAT                *CAID*
         BNE       STAB.12         NO, KEEP LOOKING             *CAID*
* SET TYPE TO 4                                                 *CAID*
         LI        R7,4            FLOAT IS 4                   *CAID*
         STB       R7,VTYPE        SET TYPE                     *CAID*
         BU        STAB.02         GO GET NEXT PARAMETER        *CAID*
STAB.12  CAMW      R6,=C'DOUB'     IS IT A DOUBLE               *CAID*
         BNE       STAB.13         NO, KEEP LOOKING             *CAID*
         CAMW      R7,=C'LE  '     IS IT A DOUBLE               *CAID*
         BNE       STAB.13         NO, KEEP LOOKING             *CAID*
* SET TYPE TO 5                                                 *CAID*
         LI        R7,5            DOUBLE IS 5                  *CAID*
         STB       R7,VTYPE        SET TYPE                     *CAID*
         BU        STAB.02         GO GET NEXT PARAMETER        *CAID*
STAB.13  CAMW      R6,=C'STRU'     IS IT A STRUCT               *CAID*
         BNE       STAB.14         NO, KEEP LOOKING             *CAID*
         CAMW      R7,=C'CT  '     IS IT A STRUCT               *CAID*
         BNE       STAB.14         NO, KEEP LOOKING             *CAID*
* SET TYPE TO 6                                                 *CAID*
         LI        R7,6            STRUCT IS 6                  *CAID*
         STB       R7,VTYPE        SET TYPE                     *CAID*
* UNSTRING STRUCTURE NAME SKIPPING LEADING BLANKS               *CAID*
         LW        R1,=X'80000000' TERMINATE ON A SPACE         *CAID*
* GET _SYMBOL WE ARE DEFINING.  SYMBOL IN HWNAME                *CAID*
         BL        UNST            UNSTRING STRUCTURE NAME      *CAID*
         LD        R6,HWNAME       FETCH 8 CHAR STRUCTURE NAME  *CAID*
         STD       R6,SUNAME       SAVE STRUCTURE NAME          *CAID*
         SBM       4,SFLAGS        SET STRUCTURE TYPE FLAG      *CAID*
         BU        STAB.02         GO GET NEXT PARAMETER        *CAID*
STAB.14  CAMW      R6,=C'UNIO'     IS IT A UNION                *CAID*
         BNE       STAB.15         NO, KEEP LOOKING             *CAID*
         CAMW      R7,=C'N   '     IS IT A UNION                *CAID*
         BNE       STAB.15         NO, KEEP LOOKING             *CAID*
* SET TYPE TO 7                                                 *CAID*
         LI        R7,7            UNION IS 7                   *CAID*
         STB       R7,VTYPE        SET TYPE                     *CAID*
* UNSTRING UNION NAME SKIPPING LEADING BLANKS                   *CAID*
         LW        R1,=X'80000000' TERMINATE ON A SPACE         *CAID*
* GET _SYMBOL WE ARE DEFINING.  SYMBOL IN HWNAME                *CAID*
         BL        UNST            UNSTRING UNION NAME          *CAID*
         LD        R6,HWNAME       FETCH 8 CHAR UNION NAME      *CAID*
         STD       R6,SUNAME       SAVE UNION NAME              *CAID*
         SBM       4,SFLAGS        SET UNION TYPE FLAG          *CAID*
         BU        STAB.02         GO GET NEXT PARAMETER        *CAID*
STAB.15  CAMW      R6,=C'UCHA'     IS IT A UCHAR                *CAID*
         BNE       STAB.16         NO, KEEP LOOKING             *CAID*
         CAMW      R7,=C'R   '     IS IT A UCHAR                *CAID*
         BNE       STAB.16         NO, KEEP LOOKING             *CAID*
* SET TYPE TO 8                                                 *CAID*
         LI        R7,8            UCHAR IS 8                   *CAID*
         STB       R7,VTYPE        SET TYPE                     *CAID*
         BU        STAB.02         GO GET NEXT PARAMETER        *CAID*
STAB.16  CAMW      R6,=C'USHO'     IS IT A USHORT               *CAID*
         BNE       STAB.17         NO, KEEP LOOKING             *CAID*
         CAMW      R7,=C'RT  '     IS IT A USHORT               *CAID*
         BNE       STAB.17         NO, KEEP LOOKING             *CAID*
* SET TYPE TO 9                                                 *CAID*
         LI        R7,9            USHORT IS 9                  *CAID*
         STB       R7,VTYPE        SET TYPE                     *CAID*
         BU        STAB.02         GO GET NEXT PARAMETER        *CAID*
STAB.17  CAMW      R6,=C'UINT'     IS IT A UINT                 *CAID*
         BNE       STAB.18         NO, KEEP LOOKING             *CAID*
         CAMW      R7,=C'    '     IS IT A UINT                 *CAID*
         BNE       STAB.18         NO, KEEP LOOKING             *CAID*
* SET TYPE TO 10                                                *CAID*
         LI        R7,10           UINT IS 10                   *CAID*
         STB       R7,VTYPE        SET TYPE                     *CAID*
         BU        STAB.02         GO GET NEXT PARAMETER        *CAID*
STAB.18  CAMW      R6,=C'ULON'     IS IT A ULONG                *CAID*
         BNE       STAB.19         NO, KEEP LOOKING             *CAID*
         CAMW      R7,=C'G   '     IS IT A ULONG                *CAID*
         BNE       STAB.19         NO, KEEP LOOKING             *CAID*
* SET TYPE TO 11                                                *CAID*
         LI        R7,11           ULONG IS 11                  *CAID*
         STB       R7,VTYPE        SET TYPE                     *CAID*
         BU        STAB.02         GO GET NEXT PARAMETER        *CAID*
STAB.19  CAMW      R6,=C'ENUM'     IS IT AN ENUM                *CAID*
         BNE       STAB.20         NO, KEEP LOOKING             *CAID*
* SET TYPE TO 12                                                *CAID*
         LI        R7,12           ENUM IS 12                   *CAID*
         STB       R7,VTYPE        SET TYPE                     *CAID*
* UNSTRING ENUM NAME SKIPPING LEADING BLANKS                    *CAID1*
         LW        R1,=X'80000000' TERMINATE ON A SPACE         *CAID1*
* GET _SYMBOL WE ARE DEFINING.  SYMBOL IN HWNAME                *CAID1*
         BL        UNST            UNSTRING STRUCTURE NAME      *CAID1*
         LD        R6,HWNAME       FETCH 8 CHAR STRUCTURE NAME  *CAID1*
         STD       R6,SUNAME       SAVE ENUM NAME               *CAID1*
         SBM       4,SFLAGS        SET STRUCTURE TYPE FLAG      *CAID1*
         BU        STAB.02         GO GET NEXT PARAMETER        *CAID*
STAB.20  CAMW      R6,=C'GSYM'     IS IT A GLOBAL SYMBOL (DEF)  *CAID*
         BNE       STAB.21         NO, KEEP LOOKING             *CAID*
* GET VARIABLE SIZE                                             *CAID*
         LI        R2,2            SKIP BLANKS                  *CAID*
         BL        VAL             GET SIZE                     *CAID*
         ANMW      R7,=X'7FFFFF'   JUST THE VALUE               *CAID*
         STW       R7,VSIZE        SAVE THE SIZE                *CAID*
         BU        STAB.02         GO GET NEXT PARAMETER        *CAID*
STAB.21  CAMW      R6,=C'ESYM'     IS IT A GLOBAL SYMBOL (EXT)  *CAID*
         BNE       STAB.22         NO, KEEP LOOKING             *CAID*
* DO NOT OUTPUT EXTERNS                                         *CAID*
         LI        R7,255          INVALID TYPE                 *CAID*
         STB       R7,VTYPE        SET TYPE                     *CAID*
* GET VARIABLE SIZE                                             *CAID*
         LI        R2,2            SKIP BLANKS                  *CAID*
         BL        VAL             GET SIZE                     *CAID*
         ANMW      R7,=X'7FFFFF'   JUST THE VALUE               *CAID*
         STW       R7,VSIZE        SAVE THE SIZE                *CAID*
         BU        STAB.02         GO GET NEXT PARAMETER        *CAID*
STAB.22  CAMW      R6,=C'LSYM'     IS IT A LOCAL SYMBOL (DEF)   *CAID*
         BNE       STAB.23         NO, KEEP LOOKING             *CAID*
* GET VARIABLE SIZE                                             *CAID*
         LI        R2,2            SKIP BLANKS                  *CAID*
         BL        VAL             GET SIZE                     *CAID*
         ANMW      R7,=X'7FFFFF'   JUST THE VALUE               *CAID*
         STW       R7,VSIZE        SAVE THE SIZE                *CAID*
         BU        STAB.02         GO GET NEXT PARAMETER        *CAID*
STAB.23  CAMW      R6,=C'GFTN'     IS IT A GLOBAL FUNCTION      *CAID*
         BNE       STAB.24         NO, KEEP LOOKING             *CAID*
* GET VARIABLE SIZE                                             *CAID*
         LI        R2,2            SKIP BLANKS                  *CAID*
         BL        VAL             GET SIZE                     *CAID*
         ANMW      R7,=X'7FFFFF'   JUST THE VALUE               *CAID*
         STW       R7,VSIZE        SAVE THE SIZE                *CAID*
         BU        STAB.02         GO GET NEXT PARAMETER        *CAID*
STAB.24  CAMW      R6,=C'SFTN'     IS IT A STATIC FUNCTION      *CAID*
         BNE       STAB.25         NO, KEEP LOOKING             *CAID*
* GET VARIABLE SIZE                                             *CAID*
         LI        R2,2            SKIP BLANKS                  *CAID*
         BL        VAL             GET SIZE                     *CAID*
         ANMW      R7,=X'7FFFFF'   JUST THE VALUE               *CAID*
         STW       R7,VSIZE        SAVE THE SIZE                *CAID*
         BU        STAB.02         GO GET NEXT PARAMETER        *CAID*
STAB.25  CAMW      R6,=C'PARM'     IS IT A PARAMETER            *CAID*
         BNE       STAB.26         NO, KEEP LOOKING             *CAID*
* GET VARIABLE SIZE                                             *CAID*
         LI        R2,2            SKIP BLANKS                  *CAID*
         BL        VAL             GET SIZE                     *CAID*
         ANMW      R7,=X'7FFFFF'   JUST THE VALUE               *CAID*
         STW       R7,VSIZE        SAVE THE SIZE                *CAID*
* GET STACK OFFSET                                              *CAID*
         LI        R2,2            SKIP BLANKS                  *CAID*
         BL        VAL             GET STACK OFFSET             *CAID*
         ANMW      R7,=X'7FFFFF'   JUST THE VALUE               *CAID*
         STW       R7,STKOFF       SAVE STACK OFFSET            *CAID*
         SBM       7,NOSYM         NOT IN SYMBOL TABLE          *CAID*
         SBM       3,SFLAGS        STACK VARIABLE FLAG          *CAID*
         SBM       6,SFLAGS        ABS ADDRESS FLAG             *CAID*
         BU        STAB.02         GO GET NEXT PARAMETER        *CAID*
STAB.26  CAMW      R6,=C'USYM'     IS IT AN UNKNOWN SYMBOL      *CAID*
         BNE       STAB.27         NO, KEEP LOOKING             *CAID*
* GET VARIABLE SIZE                                             *CAID*
         LI        R2,2            SKIP BLANKS                  *CAID*
         BL        VAL             GET SIZE                     *CAID*
         ANMW      R7,=X'7FFFFF'   JUST THE VALUE               *CAID*
         STW       R7,VSIZE        SAVE THE SIZE                *CAID*
         BU        STAB.02         GO GET NEXT PARAMETER        *CAID*
STAB.27  CAMW      R6,=C'RSYM'     IS IT A REGISTER SYMBOL      *CAID*
         BNE       STAB.28         NO, KEEP LOOKING             *CAID*
* GET VARIABLE SIZE                                             *CAID*
         LI        R2,2            SKIP BLANKS                  *CAID*
         BL        VAL             GET SIZE                     *CAID*
         ANMW      R7,=X'7FFFFF'   JUST THE VALUE               *CAID*
         STW       R7,VSIZE        SAVE THE SIZE                *CAID*
* GET REGISTER NUMBER                                           *CAID*
         LI        R2,2            SKIP BLANKS                  *CAID*
         BL        VAL             GET REG NUMBER               *CAID*
         ANMW      R7,=X'7FFFFF'   JUST THE VALUE               *CAID*
         STB       R7,REGVAL       SAVE REG NUMBER              *CAID*
         STW       R7,STKOFF       SAVE REG NUMBER              *CAID*
         SBM       7,NOSYM         NOT IN SYMBOL TABLE          *CAID*
         SBM       5,SFLAGS        REG VARIABLE FLAG            *CAID*
         SBM       6,SFLAGS        ABS ADDRESS FLAG             *CAID*
         BU        STAB.02         GO GET NEXT PARAMETER        *CAID*
STAB.28  CAMW      R6,=C'AUTO'     IS IT A STACK SYMBOL         *CAID*
         BNE       STAB.29         NO, KEEP LOOKING             *CAID*
* GET VARIABLE SIZE                                             *CAID*
         LI        R2,2            SKIP BLANKS                  *CAID*
         BL        VAL             GET SIZE                     *CAID*
         ANMW      R7,=X'7FFFFF'   JUST THE VALUE               *CAID*
         STW       R7,VSIZE        SAVE THE SIZE                *CAID*
* GET STACK OFFSET                                              *CAID*
         LI        R2,2            SKIP BLANKS                  *CAID*
         BL        VAL             GET STACK OFFSET             *CAID*
         ANMW      R7,=X'7FFFFF'   JUST THE VALUE               *CAID*
         STW       R7,STKOFF       SAVE STACK OFFSET            *CAID*
         SBM       7,NOSYM         NOT IN SYMBOL TABLE          *CAID*
         SBM       3,SFLAGS        STACK VARIABLE FLAG          *CAID*
         SBM       6,SFLAGS        ABS ADDRESS FLAG             *CAID*
         BU        STAB.02         GO GET NEXT PARAMETER        *CAID*
STAB.29  CAMW      R6,=C'HSYM'     IS IT A HIDDEN STATIC SYMBOL *CAID*
         BNE       STAB.30         NO, KEEP LOOKING             *CAID*
* GET VARIABLE SIZE                                             *CAID*
         LI        R2,2            SKIP BLANKS                  *CAID*
         BL        VAL             GET SIZE                     *CAID*
         ANMW      R7,=X'7FFFFF'   JUST THE VALUE               *CAID*
         STW       R7,VSIZE        SAVE THE SIZE                *CAID*
* GET ASSIGNED LABEL ADDRESS                                    *CAID*
         LI        R2,2            SKIP BLANKS                  *CAID*
         BL        VAL             GET ADDRESS                  *CAID*
         ANMW      R7,=X'7FFFFF'   JUST THE VALUE               *CAID*
         STW       R7,STKOFF       SAVE ADDRESS                 *CAID*
         SBM       7,NOSYM         NOT IN SYMBOL TABLE          *CAID*
         BU        STAB.02         GO GET NEXT PARAMETER        *CAID*
* BAD INPUT, GIVE 'K' ERROR                                     *CAID*
STAB.30  BL        YEANAY          ARE WE ASSEMBLING?           *CAID*
         BNS       NEXT            NO                           *CAID*
         SBM       G'K'-X'40',HWERRF  MARK K ERROR              *CAID*
         ABM       31,HWERCT       COUNT THE ERROR              *CAID*
         BU        NEXT            WE ARE DONE HERE             *CAID*
* OUTPUT DEBUG RECORD                                           *CAID*
STAB.40  ZMB       CHARCNT         CHAR CNT FOR SRC LINE        *CAID*
         ZMB       BLNKCNT         BLANK CNT FOR SRC LINE       *CAID*
         LI        R3,-80B         LENGTH OF SLINE              *CAID*
         LI        R7,G' '         A BLANK CHAR                 *CAID*
         STB       R7,SLINE+80B,X3 BLANK BUFFER                 *CAID*
         BIB       R3,$-1W         LOOP FOR ALL                 *CAID*
         TBM       7,HBPASS        FIRST PASS?                  *CAID*
         BS        NEXT            IF YES, THEN WAIT FOR PASS 2 *CAID*
         TBM       DBG,OPTION      IS DEBUG OPTION SET          *CAID*
         BNS       NEXT            RETURN IF NOT                *CAID*
         LB        R7,VTYPE        GET TYPE                     *CAID*
         CI        R7,255          IS IT EXTERNAL               *CAID*
         BEQ       NEXT            YES, DON'T OUTPUT SYMBOL     *CAID*
         TBM       7,NOSYM         SYMBOL IN SYMBOL TABLE       *CAID*
         BNS       STAB.41         YES, LOOK IT UP              *CAID*
* NOT IN SYMBOL TABLE, IN STACK, REG, OR DSECT                  *CAID*
* USE UNDEFINED ENTRY                                           *CAID*
* DUMMY UP AN UNDEFINED ENTRY IN REG 3                          *CAID*
         LI        R3,TYPU         UNDEFINED TYPE               *CAID*
         SRC       R3,8            INTO TYPE POSITION           *CAID*
         ORMW      R3,STKOFF       INSERT OFFSET VALUE          *CAID*
         BU        STAB.42         MERGE CODE                   *CAID*
STAB.41  LI        R1,TYPU         UNDEFINED INDICATOR          *CAID*
         SRC       R1,8            INTO TYPE POSITION           *CAID*
         LD        R4,DUMMYN       GET OUR SYMBOL               *CAID*
         BL        SS              SEARCH SYMBOL TABLE          *CAID*
STAB.42  STW       R3,TEMP         SAVE THE DEFINITION          *CAID*
         ZMB       HBBS            RESET BO STACK POINTER       *CAID*
         LI        R7,14           DEBUG LOADER FUNCTION CODE   *CAID*
         BL        BFB             OUTPUT LOADER CODE           *CAID*
         LI        R7,0            DUMMY BYTE COUNT             *CAID*
         BL        BFB             OUTPUT COUNT                 *CAID*
         LB        R7,SFLAGS       GET FLAGS BYTE SO FAR        *CAID*
         TBR       R3,0            IS SYMBOL IN CSECT           *CAID*
         BNS       $+2W            NO, DSECT                    *CAID*
         SBR       R7,31           SHOW IN CSECT                *CAID*
         BL        BFB             OUTPUT FLAGS BYTE            *CAID*
         SBM       CVFL,HHBITS     SIGNAL TO PRINT PROG CNTR    *CAID*
         LB        R7,VTYPE        GET TYPE                     *CAID*
         BL        BFB             OUTPUT BASE TYPE             *CAID*
         LB        R7,PTRCNT       GET POINTER LEVEL BYTE       *CAID*
         BL        BFB             OUTPUT POINTER LEVEL         *CAID*
         LW        R7,VSIZE        GET SIZE                     *CAID*
         BL        BFH             OUTPUT VARIABLE SIZE         *CAID*
         TRR       R3,R7           GET SYMBOL VALUE             *CAID*
         ANMW      R7,=X'7FFFFF'   JUST THE VALUE               *CAID*
         SLL       R7,3            SETUP FOR OUTPUT             *CAID*
         BL        BFW             OUTPUT 4 BYTES OF ADDRESS    *CAID*
         LD        R4,DUMMYN       GET SYMBOL NAME              *CAID*
         STD       R4,HWNAME       SET FOR OUTPUT CALL          *CAID*
         BL        BFN.0A          OUTPUT 8 BYTES               *CAID*
         TBM       4,SFLAGS        SEE IF STRUCTURE REFERENCE   *CAID*
         BNS       STAB.43         BR IF NOT                    *CAID*
         LD        R4,SUNAME       GET STRUCT/UNION NAME        *CAID*
         STD       R4,HWNAME       SET FOR OUTPUT CALL          *CAID*
         BL        BFN.0A          OUTPUT 8 BYTES               *CAID*
STAB.43  LB        R7,ARYCNT       SEE IF ARRAY DEFINED         *CAID*
         BZ        STAB.46         BR IF NOT                    *CAID*
         BL        BFB             OUTPUT ARRAY INDEX           *CAID*
         SLL       R7,1            ALWAYS UPPER/LOWER BOUNDS    *CAID*
         BL        BFB             OUTPUT TOTAL NUMBER INDEXES  *CAID*
         LNB       R6,ARYCNT       NUMBER OF INDEXES TO DO      *CAID*
         ZR        R7              WHERE WE WILL SET FLAGS      *CAID*
STAB.44  SLL       R7,2            SETUP FOR NEXT BIT           *CAID*
         SBR       R7,31           SET FLAG BIT                 *CAID*
         BIB       R6,STAB.44      SET REQUIRED NUMBER OF BITS  *CAID*
         BL        BFH             OUTPUT 16 BITS OF INFO       *CAID*
         LB        R7,ARYCNT       GET COUNT AGAIN              *CAID*
         SLL       R7,3            * 8 FOR UPPER/LOWER          *CAID*
         ADI       R7,8            + 8 YIELDS TOTAL BYTES       *CAID*
         BL        BFB             OUTPUT BYTE COUNT            *CAID*
         ZR        R7              NULL BYTE                    *CAID*
         BL        BFB             OUTPUT BYTE                  *CAID*
         BL        BFH             OUTPUT 2 BYTES OF SYM BITS   *CAID*
         ZR        R3              INITIAL INDEX OF ZERO        *CAID*
         LNB       R5,ARYCNT       GET COUNT AGAIN              *CAID*
STAB.45  LW        R7,LOWER,X3     GET LOWER BOUND INFO         *CAID*
         BL        BFW             OUTPUT 4 BYTES               *CAID*
         LW        R7,UPPER,X3     GET UPPER BOUND INFO         *CAID*
         BL        BFW             OUTPUT 4 BYTES               *CAID*
         ADI       R3,1W           NEXT ENTRY                   *CAID*
         BIB       R5,STAB.45      DO ALL ARRAY INDEXES         *CAID*
STAB.46  LI        R6,EXPFUNC      EXPANDED LOADER FUNCT CODE   *CAID*
         LW        R1,HABS         GET ADDRESS OF BO STACK      *CAID*
         ZR        R4              NO SUBCODE                   *CAID*
         BL        PB              PUBLISH BO STACK             *CAID*
         BU        NEXT            ALL DONE, GET OUT            *CAID*
* NOT .SYM, IS IT .SRC, .COM, OR .XEQ                           *CAID*
STAB.50  CI        R7,0            IS IT .SRC                   *CAID*
         BEQ       STAB.51         PROCESS IF YES               *CAID*
         CI        R7,1            IS IT .COM                   *CAID*
         BEQ       STAB.51         PROCESS IF YES               *CAID*
         CI        R7,6            IS IT .XEQ                   *CAID*
         BNE       STAB.60         CONTINUE IF NOT              *CAID*
* PROCESS .SRC, .COM, OR .XEQ PSEUDO OP                         *CAID*
* UNSTRING ONE ELEMENT SKIPPING LEADING BLANKS                  *CAID*
STAB.51  LW        R1,=X'80000000' TERMINATE ON A SPACE         *CAID*
* GET S.NN, C.NN, OR E.NN.  SYMBOL IN HWNAME                    *CAID*
         BL        UNST            UNSTRING SYMBOL NAME         *CAID*
         LD        R6,HWNAME       FETCH 8 CHAR SYMBOL NAME     *CAID*
         STD       R6,DUMMYN       STORE SOURCE s.xxxxxx        *CAID*
         LB        R6,HWNAME       FETCH 1ST CHAR OF SYMBOL     *CAID*
         CI        R6,G's'         IS IT SOURCE LINE            *CAID*
         BEQ       STAB.52         YES, PROCESS IT              *CAID*
* BAD INPUT, GIVE 'F' ERROR                                     *CAID*
         SBM       G'F'-X'40',HWERRF  MARK F ERROR              *CAID*
         ABM       31,HWERCT       COUNT THE ERROR              *CAID*
         BU        NEXT            WE ARE DONE HERE             *CAID*
STAB.52  ZMB       CHARCNT         CHARS IN SOURCE LINE         *CAID*
         ZMB       BLNKCNT         BLANK CNT FOR SRC LINE       *CAID*
         LI        R3,-80B         LENGTH OF SLINE              *CAID*
         LI        R7,G' '         A BLANK CHAR                 *CAID*
         STB       R7,SLINE+80B,X3 BLANK BUFFER                 *CAID*
         BIB       R3,$-1W         LOOP FOR ALL                 *CAID*
         SBM       INSTAB,HHBITS   IGNORE ';' OR '"' IN SRC     *CAID*
         SBM       SUDO,HHBITS     DO UNIX TABS                 *CAID*
STAB.53  LW        R1,=X'80800000' TERMINATORS IGNORED          *CAID*
         BL        GBYT            READ CHARACTER INTO R6       *CAID*
         LB        R7,HBIBYI       CHECK INPUT CHAR POSITION    *CAID*
         CI        R7,72           HAS END OF LINE BEEN REACHED?*CAID*
         BGT       STAB.57         BR IF END OF LINE (NO SRC)   *CAID*
         CI        R6,G' '         IS CHARACTER A SPACE         *CAID*
         BNE       STAB.55         NO, GO GET REST OF LINE      *CAID*
         ABM       7,BLNKCNT       INCR LEADING BLANK COUNT     *CAID*
         BU        STAB.53         GO GET NEXT CHAR             *CAID*
STAB.54  LW        R1,=X'80800000' TERMINATORS IGNORED          *CAID*
         BL        GBYT            GET ONE FULL ASCII BYTE      *CAID*
STAB.55  TBM       7,HBPASS        WHICH PASS?                  *CAID*
         BS        STAB.56         PASS 1 - DON'T STORE SRC     *CAID*
         BL        YEANAY          ASSEMBLY GOING ON?           *CAID*
         BNS       STAB.56         NO, DON'T STORE SRC          *CAID*
         LB        R1,CHARCNT      CHAR COUNT FOR LINE          *CAID*
         STB       R6,SLINE,R1     STORE SOURCE CHARACTER       *CAID*
         ABM       7,CHARCNT       CHAR COUNT FOR LINE          *CAID*
STAB.56  LB        R7,HBIBYI       GET INPUT POINTER            *CAID*
         CI        R7,72           CHECK FOR ALL DONE (COL 72)  *CAID*
         BGT       STAB.57         72 FOUND, THAT IS ALL        *CAID*
         LB        R1,CHARCNT      CHAR COUNT FOR LINE          *CAID*
         CI        R1,80           IS LINE BUFFER FULL          *CAID*
         BLT       STAB.54         GO GET NEXT CHAR             *CAID*
* SOURCE LINE NOW STORED IN SLINE                               *CAID*
STAB.57  ZBM       INSTAB,HHBITS   ALLOW ';' OR '"' IN SRC      *CAID*
         ZBM       SUDO,HHBITS     DO NORMAL TABS               *CAID*
STAB.58  LB        R1,CHARCNT      GET OUR LINE COUNT           *CAID*
         CI        R1,1            NEED AT LEAST 1 CHAR         *CAID*
         BLE       STAB.70         WE ARE DONE                  *CAID*
         LB        R7,SLINE-1B,R1  GET LAST CHAR                *CAID*
         CI        R7,G' '         IS IT A BLANK                *CAID*
         BEQ       $+3W            YES, BACKUP COUNT            *CAID*
         CI        R7,X'09'        IS IT A TAB                  *CAID*
         BNE       STAB.70         CHAR FOUND, WE ARE DONE      *CAID*
         SUI       R1,1            BACKUP COUNT                 *CAID*
         STB       R1,CHARCNT      AND SAVE IT                  *CAID*
         BU        STAB.58         DELETE TRAILING BLANKS       *CAID*
* NOT .SYM, .SRC, .COM, OR .XEQ. IS IT                          *CAID*
STAB.60  CI        R7,2            IS IT .STAB                  *CAID*
         BEQ       NEXT            IGNORE FOR NOW               *CAID*
         CI        R7,3            IS IT .STABC                 *CAID*
         BEQ       NEXT            IGNORE FOR NOW               *CAID*
         CI        R7,5            IS IT .END                   *CAID*
         BEQ       NEXT            IGNORE FOR NOW               *CAID*
         CI        R7,7            IS IT .ARG                   *CAID*
         BEQ       NEXT            IGNORE FOR NOW               *CAID*
         BU        NEXT            FINISHED THIS STATEMENT      *CAID*
* NOW OUTPUT THE DEBUG RECORD                                   *CAID*
STAB.70  TBM       7,HBPASS        WHICH PASS?                  *CAID*
         BS        NEXT            PASS 1 - DON'T OUTPUT SRC    *CAID*
         BL        YEANAY          ASSEMBLY GOING ON?           *CAID*
         BNS       NEXT            NO, DON'T OUTPUT SRC         *CAID*
         TBM       DBG,OPTION      IS DEBUG OPTION SET          *CAID*
         BNS       NEXT            RETURN IF NOT                *CAID*
         ZMB       HBBS            RESET BO STACK POINTER       *CAID*
         LI        R7,14           DEBUG LOADER FUNCTION CODE   *CAID*
         BL        BFB             OUTPUT LOADER CODE           *CAID*
         LI        R7,0            DUMMY BYTE COUNT             *CAID*
         BL        BFB             OUTPUT COUNT                 *CAID*
* OUTPUT SECTION NUMBER TO FLAGS BYTE                           *CAID*
         LI        R7,1            ASSUME CSECT                 *CAID*
         LB        R6,HWACT+1B     FETCH SUB-OPERATION CODE     *CAID*
         SRL       R6,4            JUST THE AUG CODE            *CAID*
         CI        R6,6            IS OP .XEQ                   *CAID*
         BNE       STAB.71         BR IF NOT                    *CAID*
* OUTPUT ACTUAL SECTION                                         *CAID*
         LW        R3,HWLSTS       GET CURRENT PC               *CAID*
         TBR       R3,0            IS SYMBOL IN CSECT           *CAID*
         BS        $+2W            YES, ALREADY SET             *CAID*
* NASA FIX 03/27/94 - static initialization in function caused
* statements to not be traced.
* NASA   ZBR       R7,31           SHOW IN DSECT                *CAID*
         SBR       R7,31           SHOW IN CSECT ALWAYS (NASA)  *CAID*
         SBM       CVFL,HHBITS     SIGNAL TO PRINT PROG CNTR    *CAID*
STAB.71  BL        BFB             OUTPUT FLAGS BYTE            *CAID*
         LI        R7,14           STATEMENT LABEL TYPE         *CAID*
         BL        BFB             OUTPUT TYPE 14, STMT LABEL   *CAID*
         LI        R7,0            UNUSED NULL BYTE             *CAID*
         BL        BFB             OUTPUT BYTE                  *CAID*
         BL        BFH             OUTPUT SIZE OF ZERO          *CAID*
         LW        R7,HWLSTR+3W    GET CSECT PC                 *CAID*
         ANMW      R7,=X'7FFFFF'   JUST THE PC VALUE            *CAID*
         SLL       R7,3            BIT NUMBER OF ZERO           *CAID*
         BL        BFW             OUTPUT 4 BYTES TO BO         *CAID*
         LD        R4,DUMMYN       GET SYMBOL NAME              *CAID*
         STD       R4,HWNAME       SET FOR OUTPUT CALL          *CAID*
         BL        BFN.0A          OUTPUT 8 BYTE STMT NUMBER    *CAID*
* SET ISC TYPE, SOURCE IS UNCOMPRESSED (BIT 0)                  *CAID*
         LI        R7,X'81'        DEFAULT TO DECLARATION       *CAID*
         LB        R6,HWACT+1B     FETCH SUB-OPERATION CODE     *CAID*
         SRL       R6,4            JUST THE AUG CODE            *CAID*
         CI        R6,0            IS OP .SRC                   *CAID*
         BNE       $+2W            NO, TRY NEXT TYPE            *CAID*
         LI        R7,X'81'        DECLARATION                  *CAID*
         CI        R6,1            IS OP .COM                   *CAID*
         BNE       $+2W            NO, TRY NEXT TYPE            *CAID*
         LI        R7,X'84'        COMMENT                      *CAID*
         CI        R6,6            IS OP .XEQ                   *CAID*
         BNE       $+2W            NO, TRY NEXT TYPE            *CAID*
         LI        R7,X'82'        EXECUTABLE                   *CAID*
         BL        BFB             OUTPUT ISC TYPE              *CAID*
         LI        R7,0            CARET VALUE IS ZERO          *CAID*
         BL        BFB             OUTPUT BYTE                  *CAID*
         LB        R7,CHARCNT      LINE COUNT                   *CAID*
         BL        BFB             OUTPUT BYTE                  *CAID*
         LB        R7,BLNKCNT      LEADING BLANK COUNT          *CAID*
         BL        BFB             OUTPUT BYTE                  *CAID*
         ZR        R3              START AT SLINE               *CAID*
         LNB       R5,CHARCNT      GET CHARACTER COUNT          *CAID*
         BNN       STAB.72         BRANCH IF NO SOURCE          *CAID*
         LB        R7,SLINE,R3     GET A BYTE                   *CAID*
         BL        BFB             OUTPUT BYTE                  *CAID*
         ADI       R3,1B           NEXT BYTE                    *CAID*
         BIB       R5,$-3W         LOOP FOR ALL SRC             *CAID*
STAB.72  LI        R6,EXPFUNC      EXPANDED LOADER FUNCT CODE   *CAID*
         LW        R1,HABS         GET ADDRESS OF BO STACK      *CAID*
         ZR        R4              NO SUBCODE                   *CAID*
         BL        PB              PUBLISH BO STACK             *CAID*
         BU        NEXT            FINISHED THIS STATEMENT      *CAID*
SKIP     ANOP                                                   *CAID*
         TITLE     READ-ONLY       DATA
* PROCESS DATA,DATAB,DATAH,DATAW,DATAD
         SPACE
DATA     CEQU      $                                            ESCT-32
         ZMW       HWINDR          CLEAR INDIECT ADDRESSING INDICATOR
         LB        2,HWACT         0,0,1,2,3 FOR DATA,DATAB,H,W,D
         LB        6,TCTG,2        NUMBER OF BYTES REQD
         STB       6,TOT           STORE FOR DATA TRANSLATOR (1,2,4,8)
         ZMB       HBTTTF          INDICATE DATA STATEMENT
         ZMW       HWINAC          CLEAR ADDRESS ATTRIBUTE AREA
         BL        TDAT            TRANSLATE REST OF DATA STATEMENT
         LB        6,HBSTAC        LATEST TERMINATOR
         CI        6,G','          WAS IT A COMMA
         BEQ       DATA         YES- GET THE NEXT CONSTANT
         BU        NEXT
         TITLE     READ-ONLY       VFD
* GEN DATA PROCESSING
         SPACE
VFD      CEQU      $                                            ESCT-32
         ZMW       HWINDR          CLEAR INDIECT ADDRESSING INDICATOR
         ZMH       HHVFX           CLEAR BIT STACK
         ZMH       HHVFO           CLEAR BIT STACK POSITION POINTER
VFD1     ZMH       HHVFF           CLEAR BITS SCANNED COUNTER
         ZMH       HHVFGB          CLEAR GOOD BITS FROM THIS ELEMENT CT
         TBM       FORMGET,INPTSTAT   ARE WE EXPANDING A FORM
         BS        FORMEXP2     YES-THEN GET THE FIELD COUNT FROM MCL
         LW        1,=X'80010000'
         BL        UNST            UNSTRING LENGTH
         CI        7,G'/'          IS TERMINATOR A /
         BNE       VFDE         NO MARK ERROR
         LI        2,10            RADIX
         BL        CNUM            CONV TO NUMERIC IN R6,7
         CI        7,4096
         BLE       VFD2         WITHIN LIMIT
VFDE     BL        YEANAY          ARE WE ASSEMBLING?
         BNS       $+3W         NO.
         SBM       G'H'-X'40',HWERRF  MARK H ERROR.
         ABM       31,HWERCT       COUNT THE ERROR
         LI        7,32            ASSUME SMALL SIZE
VFD2     STH       7,HHVFS         FIELD SIZE
         LI        6,8             ALL GEN ARE IMPLICIT DOUBLE WORD
         STB       6,TOT
         LI        6,1W            IDENTIFY AS GEN STATEMENT
         STB       6,HBTTTF
         ZMW       HWINAC          DEFAULT TO A NULL ADR ATTRIBUTE
         LW        1,HWKSPA        WORD OF BLANKS.
         STW       1,HBSTAC        CLEAR TERMINATOR LIST.
         BL        TDAT            CONVERT THE CONSTANT
VFD3     LH        6,HHVFGB        NUMBER OF BITS PUT INTO OUTPUT STREAM
         CAMH      6,HHVFS         NUMBER WANTED IN OUTPUT STREAM
         BGE       VFD4         BRANCH IF DONE
         LW        6,HWKSPA        NOT DONE PAD WITH SPACES
         LI        7,8             IN EACH BYTE
         BL        VFDO            PUSH OUT ONE MORE BYTE
         BU        VFD3            SEE IF WE ARE DONE
VFD4     LB        6,HBSTAC        GET THE TERMINATOR
         CI        6,G','          IS IT A COMMA
         BEQ       VFD1         YES, GO DO ANOTHER ELEMENT
         ZR        6               NOT A COMMA
         LI        7,7             PUSH OUT 1 BIT LESS THAN BYTE TO
*                                  EMPTY HHVFX
         BL        VFDO
         BU        NEXT
         TITLE     READ-ONLY       REZ, RES
*  PROCESS REZ STATEMENT
         SPACE
REZ      CEQU      $                                            ESCT-32
         SBM       7,BACFLAG       SHOW REZ STATEMENT READ      S900542B
         BL        GRPS            EVALUATE EXPRESSION
         BL        YEANAY          ARE WE ASSEMBLING?
         BNS       NEXT         NO.
         LW        7,HWNM1         NON-NUMERIC TERMINATOR
         BEQ       $+2W         NO SPECIFIED BOUNDARY.
         BL        BOUC            GET PROG COUNTER TO CORRECT BOUNDARY.
         BL        TALL            ALLOCATE LABEL.
         LW        1,=X'007FFFFF'  LARGEST NUMBER OF BYTES TO REZ.
         ANMW      1,HWNL1         LIMIT NUMBER OF BYTES TO REZ.
         TRN       1,1             NEGATE NUMBER OF BYTES TO REZ.
         BEQ       NEXT            ZERO BYTES TO REZ - CONTINUE
         BLT       REZOK           NON-NEGATIVE NUM OF BYTES TO REZ - OK
         BL        YEANAY          ARE WE ASSEMBLING?
         BNS       NEXT         NO - DON'T MARK ERROR
         SBM       G'B'-X'40',HWERRF    MARK B ERROR
         ABM       31,HWERCT       COUNT THE ERROR
         BU        NEXT            GO GET NEXT LINE
REZOK    CEQU      $                                            ESCT-32
         ZMB       HBTTTF          INDICATE DATA TO BE GENERATED.
REZ1     ZR        6               DATA BYTE VALUE IS ZERO.
         ZR        7               INDICATE RIGHT JUSTIFICATION
         BL        TDG             GENERATE ONE BYTE OF ZERO.
         BIB       1,REZ1          DO ALL OF THE BYTES.
         BU        NEXT
         SPACE     2
* PROCESS RES STATEMENT
         SPACE
RES      CEQU      $                                            ESCT-32
         SBM       7,BACFLAG       SHOW RES STATEMENT READ      S900542B
         BL        GRPS            EVALUATE EXPRESSION
         BL        YEANAY          CHECK WHETHER PROCESSING ALLOWED
         BNS       NEXT         NO PROCESSING OF THIS DIRECTIVE
         LW        7,HWNM1         NON-NUMERIC TERMINATOR
         BEQ       $+2W
         BL        BOUC            GET PROG COUNTER TO CORRECT BOUNDARY
         LW        1,HWNL1         THE NUMBER OF BYTES TO BE SKIPPED
         SLL       1,9             DROP TYPE CODE
         LB        2,HBLABS        POINTER TO PROG COUNTER
         LW        5,HWLSTR,2      PICK UP PROG CTR
         SLLD      4,9             ISOLATE TYPE CODE
         ADR       1,5             MOD PROG CTR BY REQ AMOUNT
         SRLD      4,9             COMBINE TYPE CODE AND PROG CTR
         STW       5,HWLSTR,2      RESTORE NEW PROG CTR
         BL        PCCHK           CHECK FOR PROG CNT OVERFLOW  S920209
         BU        BOUQ
         TITLE     READ-ONLY       EQU, BOUND
* PROCESS EQU STATEMENT
         SPACE
EQU      CEQU      $                                            ESCT-32
         TBM       ASCT.OPT,OPTION     ARE WE IN AUTO-SECT MODE EASC-32
         BNS       EQU.0               SKIP IF NOT              EASC-32
         LW        R2,HWNAME           GET OPCODE               EASC-32
         IFT       ULC,SKIP                                     *JCB*
         LI        R0,-4           FOUR BYTES TO TEST           *JCB*
EQU.U    TBR       R2,1            THIS A LETTER                *JCB*
         BNS       EQU.U1          BR IF NOT                    *JCB*
         ZBR       R2,2            YES, CONVER TO UPPER CASE    *JCB*
EQU.U1   SRC       R2,8            NEXT BYTE                    *JCB*
         BIB       R0,EQU.U        DO 4 BYTES                   *JCB*
SKIP     ANOP                                                   *JCB*
         CAMW      R2,=C'EQU '         IS IT JUST EQU?          EASC-32
         BNE       EQU.0               SKIP IF NOT              EASC-32
         SBM       ASCT.NOD,ASCT.FLG   ELSE SET NO $ TO VAL     EASC-32
EQU.0    CEQU      $                   AND CONTINUE             ESCT-32
         LI        2,2             INDICATE  SKIP LEADING SPACES
         BL        VAL             EVALUATE EXPRESSION
         LW        1,HWINAC        THE TYPE AND VALUE FROM VAL
         STW       1,HWLSTS        PUT VALUE IN STATICIZED PROG CNTR
         LB        1,HWLSTS        GET THE TYPE OF THE RESULT
         ZBR       1,24            CLEAR DSECT/CSECT FLAG
         CI        1,TYPC          IS IT A COMMON TYPE SYMBOL?
*        BNE       BOUQ         THE EXPRESSION IS NOT TYPED COMMON
         BEQ       EQU.1        THE EXPRESSION IS TYPED COMMON
         TBM       DPFLG,DPFLAGS IS IT DATAPOOL
         BNS       BOUQ         NO
         SBM       G'V'-X'40',HWERRF  MARK 'V' ERROR
         ABM       31,HWERCT          COUNT ERROR
         BU        BOUQ
EQU.1    CEQU      $                                            ESCT-32
         LB        1,HWINACBN      GET THE BLOCK NUMBER IF IT IS
         STB       1,HWLSTS+1B     THE BLOCK NUMBER GOES WITH THIS THEN
         BU        BOUQ            ALLOCATE LABEL AND PRINT PROG COUNTER
         SPACE     2
* PROCESS BOUND PSEUDO-OP
         SPACE
BOUND    CEQU      $                                            ESCT-32
         LI        2,2             SIGNAL VAL TO SKIP LEADING SPACES
         BL        VAL             EVALUATE EXPRESSION
         BL        YEANAY          CHECK WHETHER PROCESSING ALLOWED
         BNS       NEXT         NO PROCESSING OF THIS DIRECTIVE
         ANMW      7,=X'007FFFFF'  MASK OFF TYPE
         BEQ       BOUNE        VALUE OF BOUND TO SMALLL
         TRR       7,6             VALUE TO R6 FOR NORMALIZATION
         SCZ       6,1             NORMALIZE THE THING
         TRR       6,6             CHECK THE CONTENTS AFTER THE SCZ
         BNE       BOUNE        PROPER IS COMPLETELY NORMALIZED
         CI        1,26            CHECK FOR OVER SCALING
         BGE       BOUR         WIHTIN THE LIMITS
BOUNE    SBM       G'Q'-X'40',HWERRF   MARK Q ERROR
         ABM       31,HWERCT       COUNT THE ERROR
*!!!!!!!!!!BU!!!!!!!!BOUQ!!!!!!!!!!!!PRINT!LOC!COUNTER!AND!ALL!!EASC-32
         BU        NEXT            DON'T PROCESS LABEL ON ERR   EASC-32
* ABOVE CHANGE MADE AT EASC-32 FOR CLARITY OF PROCESSING        EASC-32
BOUR     CEQU      $                                            ESCT-32
*!BOUR!!!!!BL!!!!!!!!BOUC!!!!!!!!!!!!BOUND!TO!REQUESTED!BOUNDA!!EASC-32
         TBM       ASCT.OPT,OPTION  ARE WE IN AUTO-SECT MODE    EASC-32
         BNS       BOUR.1           CONTINUE IF NOT!            EASC-32
         SBM       ASCT.BND,ASCT.FLG  INDICATE DEFERRED BND     EASC-32
         STW       R7,ASCT.BVL        TO SECTION CHOOSER        EASC-32
         LW        R7,HWLICT          GET LINE COUNTER          EASC-32
         STW       R7,ASCT.BLC       AND SAVE FOR SECTION CHSR  EASC-32
         LD        R6,HWLABL          AND ALLOCATE LABEL        EASC-32
         STD       R6,ASCT.BLB        AT THAT TIME              EASC-32
         BU        NEXT            AND FORGET THIS FOR NOW      EASC-32
BOUR.1   CEQU      $               CONTINUE                     ESCT-32
         BL        BOUC            GO BOUND IT                  EASC-32
*  NOTE THAT IF MULTIPLE BOUNDS ARE DEFERRED ONLY THE LAST      EASC-32
*  ONE WILL BE PROCESSED, ANY LABELS ON PREVIOUS ONES WILL      EASC-32
*  BE UNDEFINED!                                                EASC-32
BOUP     LB        1,HBLABS        GET ABS/REL MODE FLAG
         LW        6,HWLSTR,1
         STW       6,HWLSTS        STATICIZE PROGRAM COUNTER
BOUQ     BL        TALL            ALLLOCATE LABEL
         BL        YEANAY          CHECK WHETHER PROCESSING ALLOWED
         BNS       NEXT         NO PROCESSING OF THIS DIRECTIVE
         SBM       CVFL,HHBITS     SIGNAL TO PRINT PROGRAM COUNTER
         BU        NEXT
         TITLE     READ-ONLY       ORG
* PROCESS ORG STATEMENT
         SPACE
*
* (C) COPYRIGHT 1983 ENCORE COMPUTER CORPORATION
*     ALL RIGHTS RESERVED
*
ORG      CEQU      $                                            ESCT-32
         TBM       ASCT.OPT,OPTION     ARE WE IN AUTO-SECT MODE EASC-32
         BNS       ORG.0               SKIP IF NOT              EASC-32
         LW        R2,HWNAME           GET OPCODE               EASC-32
         IFT       ULC,SKIP                                     *JCB*
         LI        R0,-4           FOUR BYTES TO TEST           *JCB*
ORG.U    TBR       R2,1            THIS A LETTER                *JCB*
         BNS       ORG.U1          BR IF NOT                    *JCB*
         ZBR       R2,2            YES, CONVER TO UPPER CASE    *JCB*
ORG.U1   SRC       R2,8            NEXT BYTE                    *JCB*
         BIB       R0,ORG.U        DO 4 BYTES                   *JCB*
SKIP     ANOP                                                   *JCB*
         CAMW      R2,=C'ORG '         IS IT JUST ORG?          EASC-32
         BNE       ORG.0               SKIP IF NOT              EASC-32
         SBM       ASCT.NOD,ASCT.FLG   ELSE SET NO $ TO VAL     EASC-32
ORG.0    CEQU      $                   AND CONTINUE             ESCT-32
         LI        2,2             INDICATE SKIP LEADING SPACES
         BL        VAL             EVALUATE EXPRESSION
         BL        YEANAY
         BNS       NEXT         NO PROCESSING OF THIS DIRECTIVE
         LW        3,HWINAC        GET TYPE AND VALUE
         ZR        2
         SLLD      2,8
         ZBR       2,24            CLEAR DSECT/CSECT FLAG
         CI        2,TYPC          IS IT COMMON TYPE
         BEQ       ORG3         YES
         LB        1,HBLABS        CHECK THE CURRENT PROG CNTR MODE
         CI        1,2W            ARE WE IN COMMON MODE
         BEQ       ORG2         YES, ERROR CAN'T CHG FROM COM IN ORG
         LW        6,HWLSTR,1      FETCH PROG COUNTER
         CAR       R6,R3           BACKWARDS ORG ?              S8700512
         BGE       ORG.1           NO IF NON-NEGATIVE           S8700512
         CAMW      R6,MAX          IS P.C. GREATER THAN MAX ?   S8700512
         BLE       ORG.1           CONTINUE IF NOT              S8700512
         STW       R6,MAX          SAVE NEW MAX VALUE           S8700512
ORG.1    CEQU      $                                            ESCT-32
         LW        4,=X'FF800000'  MASK FOR TYPE
         CMMW      6,HWINAC        DO INPUT TYPE AND PC TYPE AGREE
         BEQ       ORG4         YES, OK
         TRR       1,1             SET CC BITS (0 = ABS MODE)
         BEQ       ORG2         ERROR, ABS NOW GOING TO REL
         TBM       9,HWINAC        TRYING TO GO TO ABS MODE?
         BS        ORG1            NO
         SPACE
*             FORGET IT CHARLIE, YOUR'E STAYING IN
*             RELOCATABLE MODE AT THE OFFSET IN HWINAC
         SPACE
         SBM       8,HWINAC        SET TO RELOCATABLE
         BU        ORG4
*
*   SWITCH FROM ONE REL SECTION TO ANOTHER
*
ORG1     LI        1,1W            DSECT INDICATOR
         TBM       0,HWINAC        TRYING TO ORG INTO DSECT
         BNS       ORG1.1          YEAH, YOUR'E COOL.
         LI        1,3W            CSECT INDICATOR
ORG1.1   STB       1,HBLABS        UPDATE PROG CTR PTR
         BU        ORG4
         SPACE
* ERROR
         SPACE
ORG2     SBM       G'Q'-X'40',HWERRF  MARK Q ERROR
         ABM       31,HWERCT       COUNT THE ERROR
         BU        BOUP
         SPACE
* COMMON TYPE
         SPACE
ORG3     CEQU      $                                            ESCT-32
         LB        1,HWLSTR+1B+2W  GET CURRENT COMMON BLOCK NUMBER
         SLL       1,2             TURN INTO AN INDEX
         TBM       0,HWCMSIZE,1    IS IT AN SSECT
         BNS       ORG3.1          NO, DON;T NEED TO SAVE SIZE
         LH        5,HWLSTR+1H+2W  GET CURRENT SIZE
         CAMH      5,HWCMSIZE+1H,1 CHECK IF CURRENT IS BIGGER
         BLT       ORG3.1
         STH       5,HWCMSIZE+1H,1 SAVE NEW LARGER SIZE
ORG3.1   CEQU      $                                            ESCT-32
         LW        5,HWINAC        THE TYPE AND VALUE FROM VAL
         TRR       R5,R7           MOVE INPUT VALUE TO R7       S8700508
         ANMW      R7,=X'7FFFFF'   CLEAR OUT TYPE FIELD         S8700508
         STW       R7,SIZE         SAVE INPUT ORG SIZE          S8700508
         LB        1,HWINACBN      GET THE COMMON BLOCK NUMBER
         SLL       1,2             TURN INTO AN ADDR.           C007-30
         TBM       7,HBPASS        IS THIS PASS 2?              S8701703
         BNS       $+4W            SKIP SIZE CHECK IF SO        S8701703
         LW        R7,HWCMSIZE,R1  GET COMMON AREA SIZE         S8700508
         CAMW      R7,SIZE         COMPARE ACTUAL TO INPUT      S8700508
         BLT       ORG2            INPUT GREATER, REPORT ERROR  S8700508
*!!!!!!!!SLL!!!!!!!1,2!!!!!!!!!!!!!TURN!INTO!AN!ADDR!!!!!!!!!!!!C007-30
         TBM       0,HWCMSIZE,1    WAS IT CREATED BY SSECT?
         BS        ORG2            YES, ORG INVALID, OUTPUT ERROR
ORG3.2   CEQU      $                                            ESCT-32
         STW       5,HWLSTR+2W     SAVE IT.
         LB        1,HWINACBN      PICK UP THE COMMON BLOCK NUMBER
         STB       1,HWLSTR+1B+2W  PUT IN THE COMMON PROG. CTR.
         LI        1,2W            COMMON MODE
         STB       1,HBLABS        SET THE PC POINTER TO COMMON
         BU        BOUP            FINISH IT
*ORG3    LI        1,2W            COMMON MODE
*        STB       1,HBLABS        SET PC POINTER TO COMMON
         SPACE
ORG4     LW        5,HWINAC        THE TYPE AND VALUE FROM VAL
         STW       5,HWLSTR,1      SET PROGRAM COUNTER
         LB        5,HWINACBN      GET THE COMMON BLOCK NUMBER
         STB       5,HWLSTR+1B+2W  PUT IT IN COMMON PROG CNTR
         BU        BOUP            FINISH IT
*
         TITLE     READ-ONLY       AREL
*   PROCESS ABS, REL, DSECT, AND CSECT PSEUDOS
         SPACE
AREL     CEQU      $                                            ESCT-32
         BL        YEANAY          CHECK WHETHER PROCESSING ALLOWED
         BNS       NEXT         NO PROCESSING OF THIS DIRECTIVE
         LB        6,HBLABS     WERE WE PROCESSING COMN
         CI        6,2W
         BNE       AREL1            NO
         LB        1,HWLSTR+1B+2W   GET COM NUMBER
         SLL       1,2              MAKE IT AN INDEX
         TBM       0,HWCMSIZE,1     WAS IT AN SSECT?
         BNS       AREL1
         LH        6,HWLSTR+1H+2W   GET SIZE FROM COM. PC
         CAMH      6,HWCMSIZE+1H,1  COMPARE WITH PREV. SIZE
         BLT       AREL1        NOT LARGER
         STH       6,HWCMSIZE+1H,1  SAVE NEW SIZE
AREL1    CEQU      $                                            ESCT-32
         LB        6,HWACT+1B      GET AUGMENT + 4 BITS OF GARBAGE
         SRL       6,4             DUMP GARBAGE
         STB       6,HBLABS        0W - ABS, 1W - REL/DSECT,
*                                    3W - CSECT
         CI        6,3W            WAS IT A CSECT DIRECTIVE?
         BNE       BOUP            NO - OK
         SBM       EXPLFC,HHBITS3  INDICATE 'USE EXPANDED
*                                    LOADER CODES'
         BU        BOUP            FINISH IN COMMON NODE
         TITLE     READ-ONLY       SDIR'S
*
SDIRS    CEQU      $                                            ESCT-32
         LB        1,HWACT+1B      GET AUGMENT + 4 BITS OF JUNK
         SRL       1,4
         SLL       1,2             MAKE IT AN INDEX
         BU        *SDIRTBL,1
         SPACE
SDIRTBL  CEQU      $-1W                                         ESCT-32
         ACW       SSECT
         ACW       SORG
         ACW       SEXT
         PAGE
SORG     CEQU      $                                            ESCT-32
         LB        2,HBIBYI        GET POINTER INTO BUFFER
         STB       2,HBIBYIS       SAVE IT
         LI        2,2             INDICATE SKIP LEADING SPACES
         BL        VAL             EVALUATE EXPRESSION
         BL        YEANAY
         BNS       NEXT         NO PROCESSING OF THIS DIRECTIVE
         LW        3,HWINAC        GET TYPE AND VALUE
         ZR        2
         SLLD      2,8
         ZBR       2,24            CLEAR DSECT/CSECT FLAG
         CI        2,TYPC          IS IT COMMON TYPE
         BNE       SORG1        OKAY, DO SOME MORE CHECKS
         LB        1,HWLSTR+1B+2W  CHECK IF IN SAME SECTION
         CAMB      1,HWINACBN      NEW SECTION NUMBER
         BNE       SORG2        NO MATCH, OUTPUT ERROR
SORG1    CEQU      $                                            ESCT-32
         LB        1,HBLABS        CHECK THE CURRENT PROG CNTR MODE
         CI        1,2W            ARE WE IN COMMON MODE
         BNE       SORG2        MUST NOT HAVE DONE AN SSECT
         LB        1,HWLSTR+1B+2W  GET CURRENT COMMON BLOCK NUMBER
         SLL       1,2             MAKE IT AN ADDRESS
         TBM       0,HWCMSIZE,1    IS IT AN SSECT
         BS        SORG3           OKAY, PROCESS IT
         SPACE
* ERROR
         SPACE
SORG2    SBM       G'Q'-X'40',HWERRF  MARK Q ERROR
         ABM       31,HWERCT       COUNT THE ERROR
         BU        BOUP
         SPACE
* COMMON TYPE
         SPACE
SORG3    CEQU      $                                            ESCT-32
         CI        2,TYPC          IS IT ALREADY COMMON
         BEQ       SORG3.1         OKAY, NO NEED TO CHECK FURTHER
         LW        2,=C'+   '      SET UP AS THOUGH + WAS TERM.
         STW       2,HBSTAC        SAVE IT
         LB        2,HBIBYIS       GET POSITION IN LINE
         STB       2,HBIBYI        RESTORE IT
         LH        3,HWLSTR+2W     GET COM. TYPE AND SECT. NUMBER
         SLL       3,16            POSITION IT
         STW       3,HWINAG        SAVE AS NUMERIC EQUIVALENT
         SBM       ALVAL,HHBITS2   INDICATE FIRST OPERAND EVAL.
         BL        VAL             RE-EVALUATE TO CHECK LEGALITY
SORG3.1  CEQU      $                                            ESCT-32
         LB        1,HWLSTR+1B+2W  GET CURRENT COMMON BLOCK NUMBER
         SLL       1,2             MAKE IT AN INDEX
         LH        5,HWLSTR+1H+2W  GET CURRENT SIZE
         CAMH      5,HWCMSIZE+1H,1 CHECK IF CURRENT IS BIGGER
         BLT       SORG3.2
         STH       5,HWCMSIZE+1H,1 SAVE NEW LARGER SIZE
SORG3.2  CEQU      $                                            ESCT-32
         LW        5,HWINAC       GET TYPE AND VALUE
         ANMW      5,=X'007FFFFF' ISOLATE VALUE
         SLL       5,8
         ADI       5,TYPC          MAKE IT COMMON
         SRC       5,8             IT NOW LOOKS LIKE COMMON
         STW       5,HWINAC        SAVE IT.
         LB        1,HWLSTR+1B+2W  GET COMMON BLOCK NUMBER
         STB       1,HWINACBN
         STW       5,HWLSTR+2W
         STB       1,HWLSTR+ 1B+2W
         BU        BOUP            FINISH IT
         PAGE
*
SSECT    CEQU      $                                            ESCT-32
         BL        YEANAY
         BNS       SSECT0.5         NO PROCESSING OF THIS DIRECTIVE
         LW        1,=X'80C80000'   TERM ON SP, ( )
         BL        UNST
         LB        6,HBSTAC
         CI        6,G' '
         BEQ       SSECT1.0         ONLY ONE SYMBOL ITS OKAY
         SBM       G'X'-X'40',HWERRF  MARK ERROR
         ABM       31,HWERCT        COUNT THE ERROR
SSECT0.5 LW        1,=X'80000000'   TERMINATE ON SPACE
         BL        UNST             FINISH UNSTRINGING LINE
         BU        NEXT
         SPACE
SSECT1.0 CEQU      $                                            ESCT-32
         LI        1,TYPU           UNDEFINED INDICATOR
         SRC       1,8              INTO TYPE POSITION
         LD        4,HWNAME
         ANMW      5,=X'FFFFFF00'   TRUNCATE SYMBOL TO 7 CHARACTERS
         ORMB      5,=G' '          SET LAST CHAR TO SP.
         BL        SS               SEARCH SYMBOL TABLE
         ZR        2
         SLLD      2,8
         ZBR       2,24             CLEAR DSECT/CSECT FLAG
         CI        2,TYPC           IS IT COMMON
         BNE       SSECT1.3         NO
*                                   SYMBOL IS COM., CHECK IF SSECT
         ZR        2
         SLLD      2,8              GET COMMON BLOCK NO.
         SLL       2,2              MAKE IT AN INDEX
         TBM       0,HWCMSIZE,2     IS IT AN SSECT?
         BS        SSECT1.2         OKAY
         SBM       G'M'-X'40',HWERRF  MUST BE A MULTIPLE DEFINITION
         ABM       31,HWERCT          COUNT IT
         BU        NEXT
         SPACE
SSECT1.2 LB        2,HWNAME+7B      CHECK NAME IS <= 7 CHARS
         CI        2,G' '
         BEQ       SSECT2.1
         SBM       G'X'-X'40',HWERRF  MARK ERROR
         ABM       31,HWERCT
         BU        SSECT2.1
         SPACE
SSECT1.3 CI        2,TYPU           IS IT UNDEFINED
         BEQ       SSECT1.5         YES, GO DEFINE IT
         ABM       31,HWERCT        COUNT THE ERROR
         CI        2,TYPM           IS IT MULTIPLE DEFINITION
         BNE       SSECT1.4         NO
         ZBM       G'M'-X'40',HWERRF  CHANGE FROM M TO J ERROR
SSECT1.4 SBM       G'J'-X'40',HWERRF  MARK ERROR
         BU        NEXT
         SPACE
SSECT1.5 CEQU      $                                            ESCT-32
*                                   DEFINE NEW SSECT
         LB        3,HBCCCT         GET NUMBER FOR NEW BLOCK
         CI        3,254            ARE THERE TOO MANY
         BLT       SSECT1.6         NO
         SBM       G'Z'-X'40',HWERRF  SET ERROR
         ABM       31,HWERCT        COUNT THE ERROR
         BU        NEXT
SSECT1.6 CEQU      $                                            ESCT-32
         SLL       3,2              MAKE IT AN INDEX
         SBM       0,HWCMSIZE,3     MARK IT AS AN SSECT
         SRC       3,10             POSITION IT FOR CONCATENATION
         LI        2,TYPC          TYPE FLAG FOR COMMON SYMBOL
         SRLD      2,8             COM TYPE, BLOCK NO., 0 DISPLACEMENT
         TRR       3,1
         LB        4,HWNAME+7B     CHECK TO SEE IF NAME<=7 CHARACTERS
         CI        4,G' '
         BEQ       SSECT2.0        YES, ITS OKAY
         SBM       G'X'-X'40',HWERRF  MARK ERROR
         ABM       31,HWERCT       COUNT ERROR
SSECT2.0 CEQU      $                                            ESCT-32
         LD        4,HWNAME
         ANMW      5,=X'FFFFFF00'  CLEAR LAST BYTE
         ORMB      5,=G' '         SET IT TO SP.
         BL        SS              ALLOCATE SYMBOL TO COMMON BLOCK
         LI        1,TYPD          COMMON BLOCK DEF. TYPE
         SLL       1,8
         ORMB      1,HBCCCT        COMMON BLOCK NUMBER
         SLL       1,16            COM. DEF TYPE, BLOCK NUMBER, 0 SIZE
         LD        4,HWNAME
         SRLD      4,8             CLEAR LAST CHARACTER
         ORMW      4,=X'29000000'  FORM SECTION NAME, ')XXXXXXX'
         BL        SS              DEFINE THE SECTION
         ABM       7,HBCCCT        INCREMENT NUMBER OF COMMON BLOCKS
SSECT2.1 LI        2,G' '          SET LAST BYTE OF SYMBOL TO SP.
         STB       2,HWNAME+7B
         LI        2,1             INDICATE ELEMENT ALREADY UNSTRUNG
         BL        VAL
         LB        1,HWLSTR+1B+2W  GET CURRENT COMMON BLOCK NUMBER
         CAMB      1,HWINACBN      SAME AS NEW BLOCK NUMBER
         BNE       SSECT2.9        NOT EQUAL CONTINUE
         LB        5,HBLABS        MAKE SURE ITS COMMON
         CI        5,2W
         BEQ       BOUP            THEIR THE SAME FINISH IT
SSECT2.9 SLL       1,2             MAKE IT AN ADDRESS
         TBM       0,HWCMSIZE,1    IS IT AN SSECT
         BNS       SSECT3          NO NEED TO SAVE CURRENT SIZE
         LH        5,HWLSTR+1H+2W  GET CURRENT SIZE
         CAMH      5,HWCMSIZE+1H,1 CHECK IF CURRENT IS LARGER
         BLT       SSECT3          NO, DON'T UPDATE
         STH       5,HWCMSIZE+1H,1 SAVE NEW SIZE
SSECT3   LB        1,HWINACBN      GET COM. BLOCK NUMBER
         SLL       1,2             MAKE IT AN INDEX
         LH        5,HWCMSIZE+1H,1 ADD IN PREV. SIZE
         ANMW      5,=X'0000FFFF'  ELIMINATE POSSIBLE SIGN EXTEND
         ADMW      5,HWINAC        TYPE AND VALUE FROM VAL
         STW       5,HWLSTR+2W     SAVE IN COM. PC
         LB        5,HWINACBN      GET COM. BLOCK NUMBER
         STB       5,HWLSTR+1B+2W  SAVE IN COM. PC
         LI        1,2W            COMMON MODE
         STB       1,HBLABS        SET PC POINTER TO COMMON
         BU        BOUP            FINISH IT
         PAGE
SEXT     CEQU      $                                            ESCT-32
         BL        YEANAY          DO WE ALLOW A SEXT DEFINITION
         BNS       SEXT1.0         NO, FINISH UNSTRING STATEMENT
         LI        5,255           VALUE FOR SEXT IN DATAPOOL DEF'S
         STB       5,HWDPNUM
         BU        CCP7.01         GO PROCESS AS A DATAPOOL
         SPACE     2
SEXT1.0  CEQU      $                                            ESCT-32
         LW        1,=X'80000000'  TERMINATE ON SPACE
         BL        UNST            UNSTRING THE REST OF THE LINE
         BU        NEXT
         TITLE     READ-ONLY       CCP1
* COMMON PSEUDO PROCESSOR
         SPACE
CCP1     CEQU      $                                            ESCT-32
         BL        YEANAY          DO WE ALLOW A COMMON DEFINITION
         BNS       CCP3         NO
         LD        4,HWLABL        GET LABEL
         CAMD      4,DATAPOOL      CHECK FOR DATAPOOL
         BEQ       CCP7.DP      DATAPOOL FOUND GO PROCES
         CAMW      4,DPOO       CHECK FOR MULTIPLE DATAPOOL
         BNE       CCP1.01
         SRL       5,24
         CAMW      5,LXX
         BEQ       CCP7.MDP     GO PROCESS MULTIPLE DATAPOOL
         LD        4,HWLABL
CCP1.01  CEQU      $                                            ESCT-32
         LI        1,TYPU          UNDEFINED INDICATOR
         SRC       1,8             INTO TYPE POSITION
         STW       1,CCTU          SAVE IT
         LD        4,HWLABL
         BL        SS              SEARCH FOR BLOCK NAME IN SYMBOL TBL
         TBM       INTSS,SPMAC     WAS SYMBOL INTERNALLY GENERATED?
         BNS       CCP1.3       NO--OK.
         SBM       G'I'-X'40',HWERRF   MARK I ERROR.
         ABM       31,HWERCT       COUNT THE ERROR.
CCP1.1   LW        1,=X'80C80000'   TERM ON SP , ( )
         BL        UNST            UNSTRING ONE SYMBOL NAME.
         LB        6,HBSTAC        GET TERMINATOR.
         CI        6,G' '          WAS IT A BLANK?
         BNE       CCP1.1       NO, FINISH UNSTRINGING LINE.
         BU        NEXT
CCP1.3   CEQU      $                                            ESCT-32
         ZR        2
         SLLD      2,8             TYPE TO R2
         ZBR       2,24            CLEAR DSECT/CSECT FLAG
         CI        2,TYPD          IS IT A COMMON BLOCK DEFINITION
         BEQ       CCP8         YES, WE MUST CHAIN THIS BLOCK    84-587
         CI        2,TYPU          WAS THE BLOCK NAME UNDEFINED
         BEQ       CCF          YES- IT WAS A NEW BLOCK
         SBM       G'J'-X'40',HWERRF  MARK J ERROR
         ABM       31,HWERCT       COUNT THE ERROR
         TBM       EXPAND,MACSTATE   ARE WE EXPANDING A MACRO?
         BS        CCP1.1       YES, GO UNSTRING REST OF LINE.
         BU        NEXT            GIVE UP
CCF      LB        3,HBCCCT        A NEW BLOCK, GET A NEW NUMBER FOR IT
*!!!!!!!!STB!!!!!!!R3,BLKNUM!!!!!!!SAVE!COMMON!AREA!BLOS8700508!S8701703
         STW       R3,BLKNUM       SAVE COMMON AREA BLOCK NUM.  S8701703
         CI        3,255           ARE THERE TOO MANY
         BLE       CCF1.0          NO
         SBM       G'R'-X'40',HWERRF  MARK ERROR
         ABM       31,HWERCT       COUNT ERROR
         BU        NEXT
CCF1.0   CEQU      $                                            ESCT-32
         ABM       7,HBCCCT        INCR NUMBER OF COMMON BLOCKS
         SRC       3,8             POSITION BLOCK NUMBER FOR CONCATENATE
         BU        CCP9            PROCESS BLOCK ENTRIES        84-587
CCP8     TBM       7,HBPASS        FIRST PASS?                  84-587
         BS        CCP9            IF NOT THEN GO               84-587
         SRL       3,24                                         84-587
         SLL       3,24                                         84-587
CCP9     LI        2,TYPC          TYPE FLAG FOR COMMON SYMBOL RESIDENT
         SRLD      2,8             COM TYPE, BLOCK NO., 0 DISPLACEMENT
         STW       3,CCTW          CURRENT COMMON BLOCK PROG. COUNTER
CCP3     LW        1,=X'80C80000'  TERM ON SP , ( )
         BL        UNST            UNSTRING ONE SYMBOL NAME FOR COMMON
         BL        YEANAY          DO WE ALLOW A COMMON DEFINITION
         BNS       CCP34        NO
         LD        4,HWNAME        NAME FOR COMMON
         LW        1,CCTW          ALLOCATE TO CURRENT COM PC IF PASS 1
         TBM       7,HBPASS        IS THIS PASS 2
         BNS       $+2W         YES, DONT ALLOCATE ANYTHING
         BL        SS              PASS 1,ALLOCATE SYMBOL TO COMMON AREA
CCP34    CEQU      $                                            ESCT-32
         LI        7,4
         LB        6,HBSTAC        LATEST TERMINATOR
         CI        6,G'('          WAS IT A (
         BNE       CCP4         NO, JUMP TO NEXT WORD
         LW        1,=X'80C80000'  TERM ON SP , ( )
         BL        UNST            UNSTRING DIMENSION SIZE
         LI        2,10            DIMENSION SIZE IN DECIMAL (NO. WORDS)
         BL        CNUM            CONV TO COMPUTATIONAL IN R6,7
         MPI       6,4             CONV WORDS TO BYTES
*!!!!!!!!ZBR!!!!!!!R7,0!!!!!!!!!!!!NOT!AN!SSECT!COMMON!S8700508!S8701703
*!!!!!!!!LW!!!!!!!!R3,BLKNUM!!!!!!!BLOCK!NUMBER!TO!R3!!S8700508!S8701703
*!!!!!!!!STW!!!!!!!R7,HWCMSIZE,X3!!STORE!COMMON!AREA!SIS8700508!S8701703
CCP4     CEQU      $                                            ESCT-32
         LW        6,CCTW          GET SIZE FIELD                 83-133
         SLL       6,16                                           83-133
         SRL       6,16            CLEAR ALL INFO BUT SIZE        83-133
         ADR       7,6             ADD NEW SIZE                   83-133
         SRL       6,16            SHIFT OFF HW OF SIZE           83-133
         TRR       6,6             ANYTHING LEFT ??               83-133
         BZ        CCP4.5          NO - SIZE IS O.K.              83-133
         SBM       G'R'-X'40',HWERRF  YES - OVERFLOWED. MARK R ERROR 133
         ABM       31,HWERCT       COUNT THE ERROR                83-133
         ZR        7               CLEAR R7 TO PREVENT DAMAGE     83-133
         SPACE     1
CCP4.5   CEQU      $               ADD SIZE                     ESCT-32
         ARMW      7,CCTW          INCRE COMMON BLOCK PROG. CNTR  83-133
CCP5     LB        6,HBSTAC        LATEST TERMINATOR
         CI        6,G','          WAS IT A COMMA
         BEQ       CCP3         YES, MORE SYMBOLS IN THIS BLOCK
         CI        6,G' '          WAS IT A SPACE
         BEQ       CCP6         YES, FINISH THIS BLOCK
         LW        1,=X'80C80000'  TERM ON SP , ( )
         BL        RUNST           UNSTRING-WOTHOUT SKIPPING LEFT SPACES
         BU        CCP5            SEE IF WE ARE FINISHED
CCP6     CEQU      $                                            ESCT-32
         LW        R3,BLKNUM       GET COMMON BLOCK NUMBER      S8701703
         SLL       R3,2            TURN INTO AN INDEX           S8701703
         LW        R6,CCTW         GET SIZE INFORMATION         S8701703
         ANMW      R6,=X'0000FFFF' JUST SIZE INFO.              S8701703
         STH       R6,HWCMSIZE+1H,X3   SAVE SIZE                S8701703
*!CCP6!!!LI!!!!!!!!6,TYPD!!!!!!!!!!BLOCK!DEFINITION!TYPE!CODE!!!S8701703
         LI        6,TYPD          BLOCK DEFINITION TYPE CODE   S8701703
         STB       6,CCTW          MODIFY TYPE IN CURRENT COUNTER
         LD        4,HWLABL        BLOCK NAME
         LW        1,CCTW
         TBM       7,HBPASS        IS THIS PASS 2
         BNS       NEXT         YES, DONT RESET THE DEF CODE
         BL        YEANAY          DO WE ALLOW A COMMON DEFINITION
         BNS       NEXT         NO
         BL        SS
         BU        NEXT            DEFINE COMMON BLOCK NO. AND MAX SIZE
         SPACE
CCP7.MDP CEQU      $               PROCESS MULTIPLE DATAPOOLS   ESCT-32
         LW        5,HWLABL+1W     GET 'LXX'
         SLL       5,8             ELIMINATE 'L'
         ORMW      5,=G' '         ADD IN SPACE AS A TERMINATOR
         STW       5,HWNAME
         LI        2,10            SET RADIX
         BL        CNUM            CONVERT TO DECIMAL
         STB       7,HWDPNUM       SAVE NUMBER FOR LATER USE
         CAMW      7,=99           ONLY DPOOL00 - DPOOL99 IS VALID
         BLE       CCP7.01
         BL        YEANAY         ARE WE ASSEMBLING?
         BNS       CCP7.01        NO, SKIP ERROR
         SBM       G'D'-X'40',HWERRF    SET ERROR
         ABM       31,HWERCT      COUNT THE ERROR
         BU        CCP7.01
         SPACE
CCP7.DP  CEQU      $               PROCESS DATAPOOL ITEMS       ESCT-32
         LI        5,100           VALUE FOR DATAPOOL
         STB       5,HWDPNUM
CCP7.01  CEQU      $                                            ESCT-32
         LW        1,=X'80C80000'  TERM ON SP , ( )
         BL        UNST            UNSTRING ONE SYMBOL
         LB        6,HBSTAC        LATEST TERMINATOR
         CI        6,G'('          WAS IT A LEFT PAREN?
         BEQ       CCP7.0       YES-ALLOCATE SYMBOL
         CI        6,G')'          WAS IT A RIGHT PAREN?
         BEQ       CCP7.1       YES-IGNOR TO (,) OR SP
CCP7.0   LD        4,HWNAME        MUST BE COMMA OR SP
         LI        1,TYPDP         GET TYPE CODE
         SRC       1,8
         ORMW      1,HWDP          ADD IN DATAPOOL NUMBER
         BL        SS              ALLOCATE SYMBOL
         CI        6,G' '          TERM ON SP
         BEQ       NEXT         YES-ALL DONE GET NEXT REC.
         CI        6,G'('          TERM ON A (
*        BNE       CCP7.DP      NO- DON'T IGNORE DATA TO   ,
         BNE       CCP7.01      NO- DON'T IGNORE DATA TO   ,
CCP7.1   LW        1,=X'80C80000'  TERM ON SP , ( )
         BL        UNST
         LB        6,HBSTAC        LAST TERMINATOR
         CI        6,G','          TERM ON COMMA?
*        BEQ       CCP7.DP      YES-GET NEXT ITEM
         BEQ       CCP7.01      YES-GET NEXT ITEM
         CI        6,G' '          NO-TERM ON SPACE?
         BEQ       NEXT         YES-ALL DONE GET NEXT REC
         BU        CCP7.1          NO-IGNORE DATE;LOOK FOR ,
         TITLE     READ-ONLY       REF
* PROCESS DEF AND EXT OPERATIONS
         SPACE
REF      CEQU      $                                            ESCT-32
         LI        1,TYPU          DEFAULT TO DEF (REQUEST FOR SS)
         TBM       3,HWACT+1B      IS IT A DEF
         BNS       $+2W         BU IF DEF
         LI        1,TYPX          EXT TYPE
         SRC       1,8             LEFT JUSTIFY TYPE CODE
         STW       1,REFS1         SAVE IT
         LW        1,=X'80080000'
         BL        UNST            UNSTRING IGNORING LEADING SPACES
REF1     CEQU      $                                            ESCT-32
         BL        YEANAY          DO WE PROCESS THIS EXT/DEF
         BNS       REF3         NO
         LD        4,HWNAME        NAME
         CAMW      4,=C'    '      ! IS NAME BLANK?
         BNE       REF1.1       ! BRANCH IF NOT BLANK
         SBM       G'F'-X'40',HWERRF  ! 'F' ERROR IF BLANK NAME IN LIST
         BU        REF1.2          ! BRANCH TO COUNT ERROR
         SPACE
REF1.1   LW        1,REFS1         TYPE CODE
         BL        SS              SEARCH AND INSERT IN SYM TBL
         TBM       INTSS,SPMAC     WAS SYMBOL INTERNALLY GENERATED?
         BNS       REF1.5       NO.
         SBM       G'I'-X'40',HWERRF   MARK I ERROR.
REF1.2   ABM       31,HWERCT       COUNT THE ERROR.
         BU        REF3
         SPACE
REF1.5   CEQU      $                                            ESCT-32
         TBM       3,HWACT+1B      IS IT A DEF
         BS        REF3         NO
         SPACE
*  PROCESS EXTERNAL DEFINITION. ADDED 01/30/78.
         SPACE
         TBM       7,HBPASS        WHICH PASS ARE WE IN? (ZERO=PASS 2)
         BS        REF3            PASS 1 - RETURN (NO OUTPUT)
         LB        6,HBBBFB        HAVE ANY DATA BYTES GONE OUT?
         IFF       UNIXF,SKIP      LEAVE OUT OF NBCAS           *JCB*
         BNZ       BB.DEF8         YES - ERROR. DEF MUST PRECEDE THEM.
SKIP     ANOP                                                   *JCB*
         STW       3,REFS2         SAVE OUTPUT DEFINITION FROM SS
         ZR        2
         SLLD      2,8             TYPE CODE TO R2
         ZBR       2,24            CLEAR SECTION FLAG BIT
         CI        2,TYPP          IS IT NORMAL PROG TYPE ALLOCATION
*        BNE       BB.DEF8      NO, MARK ERROR
         BEQ       DEF1         OKAY, PUBLISH IT
         CI        2,TYPC       IS IT COMMON
         BNE       BB.DEF8      NO, MARK ERROR
         LB        2,REFS2+1B   GET COMMON BLOCK NUMBER
         SLL       2,2          TURN INTO AN INDEX
         TBM       0,HWCMSIZE,2 IS IT AN SSECT
         BNS       BB.DEF8      NO,MARK ERROR
         TBM       2,HWACT+1B   IS IT A SEXT?
         BNS       BB.DEF8      NO, MARK ERROR
         ZMB       HBBS         RESET BO STACK POINTER
         BU        BB.DEF3      GENERATE EXPANDED LOADER CODE
DEF1     CEQU      $                                            ESCT-32
         ZMB       HBBS            RESET BO STACK POINTER
         TBM       EXPLFC,HHBITS3  CHECK FOR CSECT OR NON-ZERO DSECT
         BS        BB.DEF3         YES - GENERATE EXPANDED LOADER FUNC.
*                                  NO - GEN STANDARD LOADER FUNCTIONS
         BL        BFN             STACK NAME INTO BO STREAM STACK
         LW        7,REFS2
         BL        BFA             STACK ADR INTO BO STREAM
         LI        6,PTED          LOADER FUNC CODE ENTRY POINT DEF
         BU        BB.DEF7         GO TO PUBLISH OUTPUT
BB.DEF3  LI        7,LF.EXTDF      GET LDR.FUNC. SUB-CODE.
         BL        BFB             PUT 1 BYTE INTO BO STACK
         LI        7,0             LOAD DUMMY BYTE COUNT
         BL        BFB             PUT 1 BYTE INTO BO STACK
         LI        7,0             ZERO UNUSED BYTE
         BL        BFB             PUT 1 BYTE INTO BO STACK
         TBM       2,HWACT+1B      IS IT SEXT?
         BNS       BB.DEF4         NO
         LB        7,REFS2+1B      GET COMMON BLOCK NUMBER
         ADI       7,2             SKIP OVER SECTIONS 0 AND 1
         BL        BFB             PUT 1 BYTE INTO BO STACK
         LH        7,REFS2+1H      GET ADDRESS
         ANMW      7,=X'0000FFFF'  CLEAR SIGN EXTEND
         BU        BB.DEF5
BB.DEF4  CEQU      $                                            ESCT-32
         LW        7,REFS2         GET OUTPUT DEFINITION
         ZR        6               CLEAR R6
         SLLD      6,1             SHIFT DSECT/CSECT BIT INTO R6
         TRR       6,7             LOAD R7 WITH SECTION
         BL        BFB             PUT 1 BYTE INTO BO STACK
         LW        7,REFS2         GET OFFSET
BB.DEF5  CEQU      $                                            ESCT-32
         BL        BFA       AS13  PUT OFFSET (3 BYTES) INTO BO STACK
*             WAS BL BFA.0   AS13  FIX BO OUTPUT FOR DEF IN CSECT
         BL        BFN.0           PUT NAME INTO BO STACK
         LI        6,EXPFUNC       GET LOADER FUNCTION CODE
BB.DEF7  LW        1,HABS          BASE ADDR OF BIN BYTE STREAM STACK
         BL        PB             PUBLISH BINARY OUTPUT STACK
         BU        REF3            CONTINUE
BB.DEF8  CEQU      $               ERROR OCCURED                ESCT-32
         SBM       G'F'-X'40',HWERRF    MARK F ERROR
         ABM       31,HWERCT       COUNT THE ERROR
REF3     LB        6,HBSTAC        GET LATEST TERMINATOR
         CI        6,G'",'         CHECK FOR COMMA
         BNE       NEXT
         LW        1,=X'80080000'  SP AND ,
         BL        UNST            ! UNSTRING IGNORING LEADING SPACES
         BU        REF1
         TITLE     READ-ONLY
* END PROCESSOR
         SPACE
*
* (C) COPYRIGHT 1983 ENCORE COMPUTER CORPORATION
*     ALL RIGHTS RESERVED
*
* GET ADDRESS FOR LITERAL BASE
         SPACE
END      CEQU      $                                            ESCT-32
         SBM       0,ENDFLAG       SHOW THAT WE HAVE FOUND AN END CARD
         BL        YEANAY          CHECK WHETHER ASSEMBLY IS ALLOWED
         BS        END1A        WE ARE ASSEMBLING AT THIS TIME
         TBM       7,HBPASS        IS THIS PASS 2               |85.1166
         BNS       END.00          SKIP IF IT IS                |85.1166
         LW        1,END00TCW      GET MESSAGE ID               |85.1166
         LI        7,X'0F'         FORCE IT OUT                 |85.1166
         BU        ABORTM          LOG ERROR AND GET OUT        |85.1166
*                                                               |85.1166
END00MSG DATAB     C'1** UNEXPECTED  END  STATEMENT, PROBABLY'  |85.1166
         DATAB     C' MISSING ENDM, ENDR OR CONDITION LABEL **' |85.1166
END00END DEQU      $                                            ESCT-32
         BOUND     1W                                           |85.1166
END00TCW GEN       12/END00END-END00MSG,20/B(END00MSG)          |85.1166
*                                                               |85.1166
END.00   CEQU      $                                            ESCT-32
*                                                               |85.1166
         SBM       G'X'-X'40',HWERRF        X ERROR IF ASSEMBLY OFF
         ABM       31,HWERCT       WHEN END CARD IS FOUND
END1A    CEQU      $                                            ESCT-32
         ZMH       MACSTATE        CLEAR MAIN MACRO STATE FLAG
         ZMH       INPTSTAT        AND ITS LATERNATE
         BL        PRLIT           PROCESS ANY LITERALS
         TBM       7,HBPASS        IS THIS PASS ONE
         BNS       END2         NO,GO DO END PROCESS PASS TWO
         LI        2,2             INDICATE NOTHING UNSTRUNG YET
         BL        VAL             THIS WILL TAKE CARE OF ; AND XREF
         LB        2,HWLSTR+1B+2W  COM. BLK. NO. OF LAST COM. PROCES'D
         SLL       2,2             MAKE IT AN INDEX
         TBM       0,HWCMSIZE,2    WAS IT AN SSECT?
         BNS       END1B           NO
         LH        7,HWLSTR+1H+2W  GET LAST SIZE
         CAMH      7,HWCMSIZE+1H,2 CHECK WITH SAVED SIZE
         BLT       END1B           LAST SIZE WAS SMALLER DON'T SAVE
         STH       7,HWCMSIZE+1H,2 SAVE IT.
END1B    CEQU      $                                            ESCT-32
         TBM       EXPLFC,HHBITS3  CHECK FOR CSECT OR NON-ZERO DSECT
         BNS       ENDCONT1        NO - DON'T PUT IN XREF
         LD        4,DSNAME        DATA SECTION NAME
         LW        3,HWLSTR+1W     DATA SECTION SIZE
         ZR        1               CLEAR R1 FOR XREF
         ZMW       REPTYPE         INDICATE SYMBOL REPORT TO XREF
         BL        REPTR          CROSS REF THE DATA SECTION SIZE
         LD        4,CSNAME        CONTROL SECTION NAME
         LW        3,HWLSTR+3W     CONTROL SECTION SIZE
         BL        REPTR          CROSS REF THE CONTROL SECTION SIZE
ENDCONT1 ZR        1               SET UP FOR PASS 2
         BL        RSET            INITIALIZE ASSEMBLER FOR THIS PASS
         LI        1,0             INDICATE PASS 2
         BL        CPAS             CHANGE MODE OF ADAPTERS TO PASS 2
         ZBM       IMIN,HHBITS     INDICATE NO BUFFER IMAGE READY
         SPACE
* DUMP PROGRAM NAME AND ALL COMMON DEFINITIONS
         SPACE
         LB        6,HBBBFB        IS THIS THE FIRST BYTE GENERATION
         BNE       NEXT         NO, BYTES HAVE ALREADY GONE OUT
         ZMB       HBBS            RESET BO STACK POINTER
         LD        6,TCWPROG       LOAD PROGRAM NAME
         STD       6,HWNAME
         BL        BFN             STACK NAME IN BO STACK
         LW        7,HWCMPB        MAS BOUND
         TBM       2,FPFLAG        WAS $OPTION 55 SPECIFIED?    EIEE-33
         BS        PRG.000         TYPE OBJECT AS IEEE IF SO    EIEE-33
         TBM       1,FPFLAG        IEEE DATA IN PROGRAM?        EIEE-33
         BNS       PRG.00          NO...BRANCH                  EIEE-33
PRG.000  LW        R4,=X'00000300' GET IEEE OBJECT TYPE CODE    EIEE-33
         ORR       R4,R7           OR INTO OBJECT RECORD        EIEE-33
         IFT       CAID,SKIP                                    *CAID2*
         BU        PRG.0C          OUTPUT RECORD                *CAID2*
SKIP     ANOP                                                   *CAID2*
         IFF       CAID,SKIP                                    *CAID2*
         BU        PRG.0           OUTPUT RECORD                EIEE-33
SKIP     ANOP                                                   *CAID2*
PRG.00   TBM       ASCT.OPT,OPTION  AUTO-SECTION MODE ON?       ELST-32
         BNS       $+3W             SKIP IF NOT                 ELST-32
         LW        R4,=X'00000200'  GET AUTO-SECTION TYPE CODE  ELST-32
         ORR       R4,R7            OR INTO OBJECT RECORD       ELST-32
         IFT       CAID,SKIP                                    *CAID*
PRG.0C   TBM       DBG,OPTION       IS DEBUG OPTION SET         *CAID2*
         BNS       $+3W             SKIP IF NOT                 *CAID*
         LW        R4,=X'00000400'  GET C OBJECT TYPE CODE      *CAID*
         ORR       R4,R7            OR INTO OBJECT RECORD       *CAID*
SKIP     ANOP                                                   *CAID*
PRG.0    BL        BFA             PLACE IN BO STACK
         LI        6,PTPN          PROG NAME LOADER FUNC CODE
         LW        1,HABS          BASE ADR OF BO STACK
         BL        PB             PUBLISH PROG NAME ON BO
         IFF       UNIXF,SKIP                                   *JCB*
         TBM       15,OPTION       OPTION 17 SET?               ETCM-32C
         BNS       PRG.01          NO...OUTPUT DATE/TIME INFO   PR12063
         TBM       DT.OPT,OPTION   IS DATE/TIME OPTION SET      PR12063
         BNS       TCM.4           NO...BRANCH                  ETCM-32C
PRG.01   LI        R6,16           16 BYTES OF DATE/TIME INFO   ETCM-32
         TRN       R6,R2           NEGATE COUNT                 ETCM-32
         STB       R6,HBBS         SET UP SIZE FOR PB           ETCM-32
         LI        R7,LF.DTID      GET SUB FUNCTION CODE        ETCM-32
         STB       R7,HBBS+1B      SAVE FOR PB                  ETCM-32
         ZMH       HBBS+1H         CLEAR THE REST OF WORD 0     ETCM-32
         ZR        R3              CLEAR COUNTER                ETCM-32
PRG.1    LB        R5,FMTD.DT,X3   GET DATE/TIME DATA           ETCM-32
         STB       R5,HBBS+1W,X3   PUT IN BO STACK              ETCM-32
         ABR       R3,31           INCREMENT POINTER            ETCM-32
         BIB       R2,PRG.1        MOVE ALL THE DATA            ETCM-32
         LI        R6,EXPFUNC      LOAD EXPANDED LOADER CODE    ETCM-32
         LW        R1,HABS         GET ADDR OF BO STACK         ETCM-32
         ZR        R4              NO SUB-CODE FOR DATE/TIME    ETCM-32
         BL        PB              PUBLISH DATE/TIME RECORD     ETCM-32
SKIP     ANOP                                                   *JCB*
         IFF       UNIXF,SKIP                                   *JCB*
         TBM       15,OPTION       OPTION 17 SET                ETCM-32B
         BS        TCM.4           YES...SKIP TCM RECORDS       ETCM-32B
         ZMH       TCM.INCC        CLEAR PREVIOUS INCLUDE CNT.  S900289
         ZMH       TCM.RRSC        CLEAR PREVIOUS RRS COUNT     S900289
         BL        BLD_PRCT        BUILD TYPE 2 TCM RECORD      ETCM-32
         STW       R2,TCM.BUFA     SAVE START ADDRESS           ETCM-32
         STW       R2,TCM.PNTR     AND IN BUFFER POINTER        ETCM-32
         TRR       R7,R6           GET TYPE 2 RECORD LENGTH     ETCM-32
         ZR        R7                                           ETCM-32
         SRLD      R6,2            CONVERT TO WORD COUNT        ETCM-32
         TRR       R7,R5           SAVE REMAINDER               ETCM-32
         TRR       R6,R7                                        ETCM-32
         MPI       R6,4            CONVERT BACK TO BYTE COUNT   ETCM-32
         ARMW      R7,TCM.PNTR     ADD TO BUFFER POINTER        ETCM-32
         TRR       R5,R5           ANY REMAINDER?               ETCM-32
         BZ        $+3W            NO...BRANCH                  ETCM-32
         LI        R5,4            ADD ANOTHER WORD             ETCM-32
         ARMW      R5,TCM.PNTR     BUMP POINTER                 ETCM-32
         LA        R1,FCBBO        BO FCB ADDRESS               ETCM-32
         BL        BLD_PLFC        BUILD TYPE 3 TCM RECORD      ETCM-32
         LA        R1,FCBGO        GO FCB ADDRESS               ETCM-32
         BL        BLD_PLFC        BUILD TYPE 3 TCM RECORD      ETCM-32
         LA        R1,FCBLO        LO FCB ADDRESS               ETCM-32
         BL        BLD_PLFC        BUILD TYPE 3 TCM RECORD      ETCM-32
         LA        R1,FCBSI        SI FCB ADDRESS               ETCM-32
         BL        BLD_PLFC        BUILD TYPE 3 TCM RECORD      ETCM-32
         LA        R1,FCBPRE       PRE FCB ADDRESS              ETCM-32
         BL        BLD_PLFC        BUILD TYPE 3 TCM RECORD      ETCM-32
         LA        R1,FCBLIB       MAC LFC ADDRESS              ETCM-32
         BL        BLD_PLFC        BUILD TYPE 3 TCM RECORD      ETCM-32
         LA        R1,FCBLIB2      MA2 LFC ADDRESS              ETCM-32
         BL        BLD_PLFC        BUILD TYPE 3 TCM RECORD      ETCM-32
         LA        R1,FCBCS        CS FCB ADDRESS               ETCM-32
         BL        BLD_PLFC        BUILD TYPE 3 TCM RECORD      ETCM-32
         LA        R1,FCBXR        UT2 FCB ADDRESS              ETCM-32
         BL        BLD_PLFC        BUILD TYPE 3 TCM RECORD      ETCM-32
         LA        R1,FCBSK        UT1 FCB ADDRESS              ETCM-32
         BL        BLD_PLFC        BUILD TYPE 3 TCM RECORD      ETCM-32
         ZBM       1,INCFLAG       SHOW FIRST TIME THROUGH      ETCM-32
TCM.1    LW        R1,TCM.BUFA     GET START ADDR OF TCM BUFFER ETCM-32
         CAMW      R1,TCM.PNTR     AT END OF BUFFER?            ETCM-32
         BGE       TCM.4           YES...ALL DONE               ETCM-32
         LB        R5,2,X1         GET LENGTH OF THIS RECORD    ETCM-32
         SUI       R5,4                                         ETCM-32
         STB       R5,0,X1                                      ETCM-32
TCM.3    LI        R6,EXPFUNC      GET EXPANDED FUNCTION CODE   ETCM-32
         LW        R1,TCM.BUFA     BASE ADDR OF TCM STACK       ETCM-32
         TBM       1,INCFLAG       FIRST TIME THRU?             ETCM-32
         BS        TCM.31          NO...SUB-CODE TYPE 3         ETCM-32
         LI        R4,2            SUB-CODE TYPE 2 1ST TIME     ETCM-32
         SBM       1,INCFLAG       SHOW NOT 1ST TIME NOW        ETCM-32
         BU        TCM.32          CONTINUE                     ETCM-32
TCM.31   LI        R4,3            SUB-CODE TYPE 3 FOR THE REST ETCM-32
TCM.32   BL        PB              PUBLISH RECORD               ETCM-32
         LW        R2,TCM.BUFA     GET BUFFER ADDR              ETCM-32
         LB        R2,2,X2         GET LENGTH OF REC JUST PB'D  ETCM-32
         ZR        R3                                           ETCM-32
         SRLD      R2,2            CONVERT LENGTH TO WORD CNT   ETCM-32
         TRR       R3,R5           SAVE REMAINDER               ETCM-32
         TRR       R2,R3                                        ETCM-32
         MPI       R2,4            CONVERT BACK TO BYTE COUNT   ETCM-32
         TRR       R5,R5           ANY REMAINDER                ETCM-32
         BZ        $+2W            NO...BRANCH                  ETCM-32
         ADI       R3,4            ADD 1 MORE WORD              ETCM-32
         ARMW      R3,TCM.BUFA     ADJUST BUFFER ADDRESS        ETCM-32
         BU        TCM.1           NEXT TCM RECORD              ETCM-32
TCM.4    EQU       $                                            ETCM-32
SKIP     ANOP                                                   *JCB*
         SPACE
*  PROCESS SECTION DEFINITION (IF NEEDED). ADDED 02/02/78.
         SPACE
         TBM       EXPLFC,HHBITS3  CHECK FOR CSECT OR NON-ZERO DSECT
         BNS       BFCX            NO - NO SECTION DEFS TO BE OUTPUT
         ZMB       HBBS            RESET BINARY OUTPUT STREAM POINTER
         LI        7,LF.SDEF       GET LDR.FUNC. SUB-CODE.
         BL        BFB             PUT 1 BYTE INTO BO STACK
         LI        7,0             LOAD DUMMY BYTE COUNT
         BL        BFB             PUT 1 BYTE INTO BO STACK
         LW        7,HWCMPB        MIN BOUND REQ. FOR DSECT
         BL        BFB             PUT 1 BYTE INTO BO STACK
         LI        7,0             SET UP SECTION NUMBER 0
         STB       7,HBBN          SAVE FOR PUBLISH ROUTINE
         BL        BFB             PUT 1 BYTE INTO BO STACK
         LW        7,DSIZE         GET DSECT SECTION 0 SIZE
         BL        BFA.0           STORE IN STACK (3 BYTES LESS BIT 8)
         LD        6,DSNAME        GET NAME
         STD       6,HWNAME        STORE NAME
         BL        BFN.0           STORE IN STACK
         LI        6,EXPFUNC       GET LOADER FUNCTION CODE
         LW        1,HABS          BASE ADDR OF BIN BYTE STREAM STACK
         BL        PB             PUBLISH BINARY OUTPUT STACK
         ZMB       HBBS            RESET BINARY OUTPUT STREAM POINTER
         LI        7,LF.SDEF       GET LDR.FUNC. SUB-CODE.
         BL        BFB             PUT 1 BYTE INTO BO STACK
         LI        7,0             LOAD DUMMY BYTE COUNT
         BL        BFB             PUT 1 BYTE INTO BO STACK
         LW        7,HWCMPB+1W     MIN BOUND REQ. FOR CSECT
         BL        BFB             PUT 1 BYTE INTO BO STACK
         LI        7,1             SET UP SECTION NUMBER 1
         STB       7,HBBN          SAVE FOR PUBLISH ROUTINE
         BL        BFB             PUT 1 BYTE INTO BO STACK
         LW        7,CSIZE         GET CSECT SECTION 1 SIZE
         BL        BFA.0           STORE IN STACK (3 BYTES LESS BIT 8)
         LD        6,CSNAME        GET NAME
         STD       6,HWNAME        STORE NAME
         BL        BFN.0           STORE IN STACK
         LI        6,EXPFUNC       GET LOADER FUNCTION CODE
         LW        1,HABS          BASE ADDR OF BIN BYTE STREAM STACK
         BL        PB             PUBLISH BINARY OUTPUT STACK
         SPACE
* PROCESS COMMON DEFINITIONS
         SPACE
*!BFCX!!!LA!!!!!!!!R2,SYMTAB!!!!!!SYMBOL!TABLE!ADDRESS!!!!!!!!!!S880752
BFCX     LW        R2,SYMTAB       SYMBOL TABLE ADDRESS         S880752
         BZ        BFC6.0          SKIP IF NO SYMBOLS           S880752
BFC2     STW       R2,BFCS2        SAVE IT
         LB        R6,4W,R2        TYPE CODE FROM SYM TBL ITEM
         CI        6,TYPD          IS IT COMMON BLOCK DEFINITION
         IFF       CAID,SKIP                                    *CAID*
         BNE       BFC4            NO, GO TO NEXT ITEM
SKIP     ANOP                                                   *CAID*
         IFT       CAID,SKIP                                    *CAID*
         BNE       BFC6            TRY NEXT ENTRY IF NOT COMMON *CAID*
SKIP     ANOP                                                   *CAID*
         LW        R7,4W,R2        BLOCK NO. AND SIZE IN LAST 3 BYTES
         LB        R1,4W+1B,R2     GET BLOCK NO.
         SLL       R1,2            MAKE IT AN INDEX
         TBM       0,HWCMSIZE,R1   IS IT AN SSECT
         BNS       BFC2A           NO, ITS COMMON
         LH        R7,HWCMSIZE+1H,R1   GET SIZE OF SECTION
         ANMW      R7,=X'0000FFFF' CLEAR POSSIBLE SIGN EXTEND
         ORMW      R7,4W,R2        TYPE AND BLOCK NO.
BFC2A    CEQU      $                                            ESCT-32
         BL        BFO             STACK COMMON NAME IN BO STACK
         BL        BFA             STACK BLOCK NO. AND SIZE IN STACK
         LI        6,PTCD          LOADER FUNC CODE COMMON BLOCK DEF
         BU        BFC5            OUTPUT OBJECT RECORD
         IFF       CAID,SKIP       NOW IN PASS2 FOR CAID SUPPORT*CAID*
BFC4     ZBR       6,24            ! CLEAR CSECT FLAG, IF SET
         CI        6,TYPP          ! IS IT A LOCAL SYMBOL?
         BNE       BFC6            ! TRY NEXT ENTRY IF NOT LOCAL
         TBM       DBG,OPTION      ! IS DEBUG OPTION SET
         BNS       BFC6            ! BRANCH IF NO SYMBOLS WANTED
         LW        R3,4W,R2        ! SAVE SYMBOL ADDRESS
         LW        R4,2W,R2        ! SAVE FIRST 4 CHARS OF NAME
         LW        R5,3W,R2        ! SAVE NEXT 4 CHARS OF NAME
         TBR       3,8             ! IS SYMBOL ABSOLUTE (BIT 8)
         BNS       BFC6            ! DON'T OUTPUT SYMBOL IF ABSOLUTE
         ZMB       HBBS            ! START AT FRONT OF QUEUE
         LW        7,=X'0B1200'    ! FIRST 3 BYTES OF DEBUGGER OBJ. REC.
         TBR       3,0             ! IS THIS A CSECT SYMBOL (BIT 0)
         BNS       BFC4.0          ! BRANCH IF NOT
         SBR       7,31            ! SET FLAG IF CSECT
BFC4.0   BL        BFA             ! PLACE IN QUEUE
         LI        7,14            ! SYMBOL TYPE IS 'STATEMENT'
         BL        BFB             ! PUT 1 BYTE IN QUEUE
         TRR       3,7             ! GET SYMBOL'S ADDRESS
         SLL       7,3             ! SHIFT ADDRESS LEFT 3 BITS
         BL        BFA             ! PUT ADDRESS IN QUEUE
         LI        7,0             ! LEFT HAND BYTE OF LENGTH
         BL        BFB             ! PUT 1 BYTE IN QUEUE
         LI        7,4             ! RIGHT HAND BYTE OF LENGTH
         BL        BFB             ! PUT 1 BYTE IN QUEUE
         LB        1,HBBS          ! GET CURRENT RECORD LENGTH
         LI        2,-4            ! LOOP COUNT
         TRR       4,7             ! FIRST 4 CHARS OF NAME
BCF4.1   SLLD      6,8             ! SHIFT CHAR INTO R6
         ABR       1,31            ! INCREMENT COUNTER
         STB       6,HBBS,1        ! PUT BYTE IN QUEUE
         BIB       2,BCF4.1        ! OUTPUT 4 CHARS
         LI        2,-4            ! LOOP COUNT
         TRR       5,7             ! NEXT 4 CHARS OF NAME
BCF4.2   SLLD      6,8             ! SHIFT CHAR INTO R6
         ABR       1,31            ! INCREMENT COUNTER
         STB       6,HBBS,1        ! PUT BYTE IN QUEUE
         BIB       2,BCF4.2        ! OUTPUT SECOND 4 CHARS
         STB       1,HBBS          ! UPDATE RECORD COUNT
         LI        6,EXPFUNC       ! EXPANDED FUNCTION CODE
SKIP     ANOP                                                   *CAID*
BFC5     LW        1,HABS          BASE ADR OF BO STACK
         BL        PB             PUBLISH STACK
BFC6     LW        R2,BFCS2        GET BACK CURR SYMBOL TAB ADDR
*!!!!!!!!ADI!!!!!!!R2,6W!!!!!!!!!!!SYMBOL!TABLE!INCR!!!!!!!!!!!!S880752
         LW        R2,5W,X2        GET NEXT ENTRY ADDRESS       S880752
         BNZ       BFC2            CONTINUE IF NOT DONE         S880752
*!!!!!!!!CAMW!!!!!!R2,SYMCURRP!!!!!ARE!WE!AT!END!OF!SYMBOL!TABLES880752
*!!!!!!!!BLT!!!!!!!BFC2!!!!!!!!!NOT!DONE,!DO!NEXT!ITEM!!!!!!!!!!S880752
BFC6.0   CEQU      $                                            ESCT-32
         SPACE
*  INITIALIZE SSECT SAVE AREA
         LI        2,-256W
BFC6.1   ZMH       HWCMSIZE+256W+1H,2  CLEAR COMN PC SAVE AREA
         BIW       2,BFC6.1
         ZMW       HWLSTR+2W       CLEAR CURRENT COMMMON PC
         SPACE
         IFT       UNIXF,SKIP                                   *JCB*
         TBM       DT.OPT,OPTION   IS DATE/TIME OPTION SET??    *JCB*
         BNS       BFC8            NO - NO OBJECT OUTPUT        *JCB*
         LI        6,16            SET FOR 16 BYTES OF DATE/TIME*JCB*
         TRN       6,2             NEGATE FOR BIB LOOP          *JCB*
         STB       6,HBBS          SET UP SIZE FOR PB           *JCB*
         LI        7,LF.DTID       GET SUB FUNCT CODE           *JCB*
         STB       7,HBBS+1B       SAVE FOR PB                  *JCB*
         ZMH       HBBS+1H         CLEAR THE REST OF WORD 0     *JCB*
         ZR        3               CLEAR COUNTER                *JCB*
BFC7     LB        5,FMTD.DT,3     GET DATE/TIME DATA           *JCB*
         STB       5,HBBS+1W,3     PUT IN BO STACK              *JCB*
         ABR       3,31            INCREMENT POINTER            *JBC*
         BIB       2,BFC7          MOVE ALL THE DATA            *JCB*
         LI        6,EXPFUNC       GET EXPANDED LOADER FUNC CODE*JCB*
         LW        1,HABS          GET ADDR OF BO STACK         *JCB*
         ZR        R4              NO SUB-CODE FOR DATE/TIME    *JCB*
         BL        PB              PUBLISH STACK                *JCB*
*!!!!!!!!TBM!!!!!!!DT.OPT,OPTION!!!IS!DATE/TIME!OPTION!SET??!!!!ETCM-32
*!!!!!!!!BNS!!!!!!!BFC8!!!!!!!!!!!!NO!-!NO!OBJECT!OUTPUT!!!!!!!!ETCM-32
*!!!!!!!!LI!!!!!!!!6,16!!!!!!!!!!!!SET!UP!FOR!16!BYTES!OF!DATE/!ETCM-32
*!!!!!!!!TRN!!!!!!!6,2!!!!!!!!!!!!!NEGATE!FOR!BIB!LOOP!!!!!!!!!!ETCM-32
*!!!!!!!!STB!!!!!!!6,HBBS!!!!!!!!!!SET!UP!SIZE!FOR!PB!!!!!!!!!!!ETCM-32
*!!!!!!!!LI!!!!!!!!7,LF.DTID!!!!!!!GET!SUB!FUNCT!CODE!!!!!!!!!!!ETCM-32
*!!!!!!!!STB!!!!!!!7,HBBS+1B!!!!!!!SAVE!FOR!PB!!!!!!!!!!!!!!!!!!ETCM-32
*!!!!!!!!ZMH!!!!!!!HBBS+1H!!!!!!!!!CLEAR!THE!REST!OF!WORD!0!!!!!ETCM-32
*!!!!!!!!ZR!!!!!!!!3!!!!!!!!!!!!!!!CLEAR!COUNTER!!!!!!!!!!!!!!!!ETCM-32
*!BFC7!!!LB!!!!!!!!5,FMTD.DT,3!!!!!GET!DATE/TIME!DATA!!!!!!!!!!!ETCM-32
*!!!!!!!!STB!!!!!!!5,HBBS+1W,3!!!!!PUT!IN!BO!STACK!!!!!!!!!!!!!!ETCM-32
*!!!!!!!!ABR!!!!!!!3,31!!!!!!!!!!!!INCREMENT!POINTER!!!!!!!!!!!!ETCM-32
*!!!!!!!!BIB!!!!!!!2,BFC7!!!!!!!!!!MOVE!ALL!THE!DATA!!!!!!!!!!!!ETCM-32
*!!!!!!!!LI!!!!!!!!6,EXPFUNC!!!!!!!GET!EXPANDED!LOADER!FUNC!COD!ETCM-32
*!!!!!!!!LW!!!!!!!!1,HABS!!!!!!!!!!GET!ADDR!OF!BO!STACK!!!!!!!!!ETCM-32
*!!!!!!!!BL!!!!!!!!PB!!!!!!!!!!!!!!PUBLISH!STACK!!!!!!!!!!!!!!!!ETCM-32
SKIP     ANOP                                                   *JCB*
BFC8     LB        6,PROD.IDL      GET ID INFO LENGTH              11006
         BZ        BFC10           IF 0, NONE PROVIDED             11006
         TRN       6,2             NEGATE FOR BIB LOOP             11006
         STB       6,HBBS          SET UP SIZE FOR PB              11006
         LI        7,LF.DTID       GET SUB FUNCT CODE              11006
         STB       7,HBBS+1B       SAVE FOR PB                     11006
         ZMH       HBBS+1H         CLEAR THE REST OF WORD 0        11006
         SBM       7,HBBS+3B       SET ID INFO FLAG (PB HANDLES)   11006
         ZR        3               CLEAR COUNTER                   11006
BFC9     LB        5,PROD.ID,3     GET PRODUCT ID INFO             11006
         STB       5,HBBS+1W,3     PUT IN BO STACK                 11006
         ABR       3,31            INCREMENT POINTER               11006
         BIB       2,BFC9          MOVE ALL THE DATA               11006
         LI        6,EXPFUNC       GET EXPANDED LOADER FUNC CODE   11006
         LW        1,HABS          GET ADDR OF BO STACK            11006
         LI        R4,1            SUB-CODE OF 1 FOR PROG INFO  ETCM-32
         BL        PB              PUBLISH STACK                   11006
BFC10    CEQU      $                                            ESCT-32
         BU        NEXT            GO DO SECOND PASS
         TITLE     READ-ONLY       PRLIT
*PROCESS LITERALS
         SPACE
PRLIT    STW       0,PRLITT0       SAVE RETURN
         TBM       ASCT.OPT,OPTION   ARE WE AUTO-SECTIONING?    EASC-32
         BNS       PRLIT.0           SKIP IF NOT                EASC-32
         LB        R1,HBLABS         GET CURRENT LOCATION CNTR  EASC-32
         CI        R1,1W             IS IT DSECT                EASC-32
         BEQ       PRLIT.0           SKIP IF IT IS              EASC-32
         LW        R0,HWLSTS       ELSE GET THE CURRENT GUY     EASC-32
         STW       R0,HWLSTR,X1      AND SAVE IT                EASC-32
         LI        R1,1W             SET DSECT POINTER          EASC-32
         STB       R1,HBLABS         AS CURRENT                 EASC-32
         LW        R0,HWLSTR,X1      AND GET VALUE              EASC-32
         STW       R0,HWLSTS         INTO CURRENT GUY           EASC-32
PRLIT.0  CEQU      $               CONTINUE                     EASC-32
         BL        BNDW            FORCE PROG CNTR TO WORD BOUNDARY
         LB        1,HBLABS        POINTER TO CORRECT PC
         LW        6,HWLSTR,1      GET PROG CNTR FOR LITERALS BASE
         ADI       6,3             ADD 3 BYTE COUNTS
         ANMW      6,=X'FFFFFFFC'  AND FORCE TO NEXT WORD BOUNDARY
         LB        2,HWLTCT+1B     PICK UP LPOOL COUNTER
         STW       6,LITORGS,2     DEFINITION ADDR FOR LPOOL
         LH        7,HWLTCT+1H     THE FULL 16 BITS
         SLL       7,2             MAKE IT A DISP FROM LITERAL BASE
         ADR       6,7             BASE ADR + DISP FOR NO. OF LITERALS =
         STW       7,HWLSTS        NEXT LOC TO BE USED
         TBM       7,HBPASS        IS THIS PASS 1
         BNS       PRLIT2
         SPACE
* PASS ONE LIT PROCESSING
         SPACE
         STW       7,HWLTPE
         BL        TALL            ALLOCATE LABEL TO LPOOL OR END CARD
         LH        6,HWLTCT+1H     GET LITERAL COUNTER.
         SLL       6,2             NO, OF BYTES TO INCREMENT PROG CNTR
         LB        3,HBLABS        POINTER TO PROG COUNTER
         ARMW      6,HWLSTR,3      ADR OF NEXT WORD TO PROG CNTR.
         BL        PCCHK           CHECK FOR PROG CNT OVERFLOW  S920209
         BU        PRLIT3          GO INCREMENT LPOOL COUNT
PRLIT2   ZBM       IMIN,HHBITS     INDICATE NO BUFFER IMAGE READY
         SPACE
* LITERALS MUST BE OUTPUT AS CONSTANTS
* AT THE LOCATION THEY HAVE BEEN ASSIGNED TO
         SPACE
         LW        6,HWLTCT
         ANMW      6,=X'FFFF0000'
         STW       6,HWENDL        HTE CURRENT LPOOL COUNTER AND COUNT O
*!END4!!!LA!!!!!!!!R2,SYMTAB!!!!!!!ADDRESS!OF!SYMBOL!TABLE!!!!!!S880752
END4     LW        R2,SYMTAB       ADDRESS OF SYMBOL TABLE      S880752
         BZ        PRLIT3          SKIP IF NO SYMBOLS           S880752
         LW        R6,4W,R2        ONE ITEM FROM SYMBOL TABLE
         CAMW      6,HWENDL        IS THIS ITEM THE LITERAL WE WANT
         BEQ       END4A        YES, PROCESS IT.
*!!!!!!!!ADI!!!!!!!R2,6W!!!!!!!!!!!SYMBOL!TABLE!INCR!!!!!!!!!!!!S880752
         LW        R2,5W,X2        GET NEXT ENTRY ADDRESS       S880752
         BNZ       END4+1W         CONTINUE IF NOT DONE         S880752]
*!!!!!!!!CAMW!!!!!!R2,SYMCURRP!!!!!TEST!FOR!END!OF!TABLE!!!!!!!!S880752
*!!!!!!!!BLT!!!!!!!END4+1W!!!!!!!!!LOOP!TO!CHECK!ALL!ITEMS!OF!!!S880752
PRLIT3   ABM       13,HWLTCT       COUNT LPOOLS
         LB        2,HWLTCT+1B     GET LPOOL COUNT.
         CI        2,X'7C'         31 LPOOLS?
         BNE       END4.1       NO.
         SBM       LPOOL31,HHBITS  INDICATE 31 LPOOLS PROCESSED.
END4.1   ZMH       HWLTCT+1H       ZERO LITERAL COUNT.
         BU        *PRLITT0        RETURN
END4A    LB        1,HWENDL+1B     PICK UP THE LPOOL NUMBER
         ANMW      6,=X'FFFF'      ISOLATE LITERAL NUMBER
         SLL       6,2             CONV TO DISPLACEMENT FROM LIT BASE
         ADMW      6,LITORGS,1
         STW       6,HWLSTS        THIS IS THE CODE LOCATION
         ADI       6,4             ADDRESS OF NEXT WORD
         LB        3,HBLABS        POINTER TO PROG CNTR
         STW       6,HWLSTR,3      ADR OF NEXT WD TO PROG CNTR
         BL        PCCHK           CHECK FOR PROG CNT OVERFLOW  S920209
         LW        R6,3W,R2        VALUE OF LITERAL FROM SYM TBL
         STW       6,HWBYTE        INTO BYTE STACK
         LW        6,=X'01010101'
         STW       6,HWBYTF        FLAG BYTES AS BEING GENERATED
         LB        R7,2W,R2        THE BLOCK NUMBER OF COMMON, IF ANY
         STB       7,HBBN          FOR LATER OUTPUT HANDLER USE
         LW        R7,2W,R2        GET RELOCATION INFO
         SLL       7,15            LEFT JUSTIFY IT
         STW       7,HWEVAL        MODE EVALUATION OF WORD IN HWBYTE
         ZR        6               CLEAR FOR DOUBLE SHIFT
         ZR        5               DEFAULT TO PROG ABSOLUTE
         ANMW      7,=X'7F800000'  ISOLATE 9 BIT TYPE CODE
         BEQ       ENDR         ADDRESS TYPE WAS NULL
         SLLD      6,9             TYPE CODE TO R6
         CAMB      6,VDTO          IS TYPE PROG ABS?
         BEQ       END4A1A      YES.
         CAMB      6,VDTO+1B       IS TYPE PROG REL?
         BNE       END4A2       NO.
         ZMB       HBBN            INDICATE LIT IN DSECT (SECT. 0)
         TBM       0,HWEVAL        IS LIT IN DSECT?
         BNS       END4A1          YES - OK
         SBM       7,HBBN          INDICATE LIT IN CSECT (SEC. 1)
         BU        END4A1
END4A1A  ZMB       HBBN            CLEAR SECTION NUMBER
END4A1   LW        R7,3W,R2        GET THE ADDRESS.
         SLL       7,13            POSITION ADDR FOR CONCATENATION.
         SLL       6,4             POSITION TYPE CODE FOR CONCATENATION.
         SLLD      6,19            CONCATENATE TYPE CODE AND ADDR.
         STW       6,HWEVAL        STORE EXPRESSION VALUE.
         LB        6,HBBN          GET SECTION NUMBER
         SLL       6,7             SHIFT FOR USE AS CSECT/DSECT FLAG
         ARMB      6,HWEVAL        PUT IT IN EXPRESSION VALUE
         BU        ENDR+1W
END4A2   CAMB      6,VDTO+2B       IS TYPE COMMON?
         BNE       END4A3       NO.
         LB        7,HBBN          GET BLOCK #.
         SLL       7,28            POSITION BLOCK # FOR CONCATENATION.
         SLL       6,3             POSITION TYPE CODE FOR CONCATENATION.
         SLLD      6,4             CONCATENATE TYPE CODE AND BLOCK #.
         LW        R7,3W,R2        GET COMMON OFFSET.
         SLL       7,16            POSITION COMMON OFFSET FOR CONCAT.
         SLLD      6,16            CONCATENATE TYPE,BLOCK, AND OFFSET.
         STW       6,HWEVAL        STORE EXPRESSION VALUE.
         BU        ENDR+1W
         SPACE
* NOT LEGAL TYPE, MARK ERROR
         SPACE
END4A3   SBM       G'R'-X'40',HWERRF  MARK R ERROR
         ABM       31,HWERCT       COUNT THE ERROR
ENDR     STW       5,HWEVAL        STORE ASSESSED ADR TYPE
         ABM       7,HBBBCT        SHOW BYTE GENERATED
         SBM       CVFL,HHBITS     SIGNAL TO PRINT PROGRAM COUNTER
         BL        RELEAS          PRINT OUTPUT
         ABM       31,HWENDL       INCR NO. OF DESIRED LITERAL
         BU        END4            GO CHECK FOR MORE LITERALS
         SPACE
* DUMP ALL EXTERNAL STRING BACK DATA ONTO BINARY OBJECT
         SPACE
*!END2!!!LA!!!!!!!!R2,SYMTAB!!!!!!!GET!SYMBOL!TBL!ADDR!!!!!!!!!!S880752
END2     LW        R2,SYMTAB       GET SYMBOL TABLE ADDRESS     S880752
         BZ        END7.0          SKIP IF NO SYMBOLS           S880752
END6     STW       2,HWENDL        SAVE IT
         LB        R6,4W,R2        GET TYPE CODE FROM SYM TBL
         ZBR       6,24            CLEAR DSECT/CSECT FLAG
         IFT       CAID,SKIP       NOW IN PASS2 FOR CAID SUPPORT*CAID*
         CI        6,TYPP          IS IT A LOCAL SYMBOL?        *CAID*
         BNE       END5            TRY NEXT ENTRY IF NOT LOCAL  *CAID*
         TBM       DBG,OPTION      IS DEBUG OPTION SET          *CAID*
         BNS       END7            BRANCH IF NO SYMBOLS WANTED  *CAID*
         LW        R3,4W,R2        SAVE SYMBOL ADDRESS          *CAID*
         LW        R4,2W,R2        SAVE FIRST 4 CHARS OF NAME   *CAID*
         LW        R5,3W,R2        SAVE NEXT 4 CHARS OF NAME    *CAID*
         TBR       3,8             IS SYMBOL ABSOLUTE (BIT 8)   *CAID*
         BNS       END7            DON'T OUTPUT SYMBOL IF ABS   *CAID*
         ZMB       HBBS            START AT FRONT OF QUEUE      *CAID*
         LW        7,=X'0E1400'    1st 3 BYTES OF DBUG OBJ REC  *CAID*
         TBR       3,0             IS THIS A CSECT SYM (BIT 0)  *CAID*
         BNS       BFC4.0          BRANCH IF NOT                *CAID*
         SBR       7,31            SET FLAG IF CSECT            *CAID*
BFC4.0   BL        BFA             PLACE IN QUEUE               *CAID*
         LI        7,14            SYMBOL TYPE IS 'STATEMENT'   *CAID*
         BL        BFB             PUT 1 BYTE IN QUEUE          *CAID*
         LI        7,0             RESERVED BYTE OF ZERO        *CAID*
         BL        BFB             PUT 1 BYTE IN QUEUE          *CAID*
         LI        7,4             SIZE IS FOUR BYTES           *CAID*
         BL        BFH             PUT 2 BYTES IN QUEUE         *CAID*
         TRR       3,7             GET SYMBOL'S ADDRESS         *CAID*
         ANMW      R7,=X'7FFFFF'   JUST THE VALUE               *CAID*
         SLL       7,3             SHIFT ADDRESS LEFT 3 BITS    *CAID*
         BL        BFW             PUT 4 ADDRESS BYTES IN QUEUE *CAID*
         STD       4,HWNAME        PUT IN POSITION FOR BFN.0A   *CAID*
         BL        BFN.0A          PUT 8 SYMBOL BYTES IN QUEUE  *CAID*
         LI        6,EXPFUNC       EXPANDED FUNCTION CODE       *CAID*
         BU        END6.1          PUBLISH STACK                *CAID*
END5     CEQU      $               TRY NEXT TYPE                *CAID*
SKIP     ANOP                                                   *CAID*
         CI        6,TYPX          IS IT AN EXTERNAL DEFINITION SYMBOL
         BNE       END7            NO, CHECK NEXT ITEM
         SPACE
*  PROCESS EXTERNAL REFERENCE. ADDED 01/30/78.
         SPACE
         ZMB       HBBS            RESET BINARY OUTPUT STREAM POINTER
         TBM       EXPLFC,HHBITS3  CHECK FOR CSECT OR NON-ZERO DSECT
         BS        BB.EXT3         YES - GEN EXPANDED LOADER FUNCTIONS
*                                  NO - GEN STANDARD LOADER FUNCTIONS
         LW        6,HWNAME        GET 4 CHARS OF UNSTRUNG ADR NAME
         BL        BFO             STACK NAME OF EXTERNAL INTO STREAM
         LW        R2,4W,R2        GET PNTR TO STRINGBACK ADDRS ELST-32
         LW        R7,0,R2         GET DSECT STRINGBACK ADDRESS ELST-32
*!!!!!!!!LW!!!!!!!!R7,4W,R2!!!!!!!!TYPE!AND!TAIL!OF!STRING!BACK!ELST-32
         BL        BFA             STACK TAIL OF STRING BACK ADR IN HBBS
         LI        6,PTEX          LOADER FUNC CODE FOR EXT STGBCK DATA
         BU        END6.1          GO TO PUBLISH/RETURN LOGIC
BB.EXT3  LI        7,LF.EXTRF      GET LDR.FUNC. SUB-CODE.
         BL        BFB             PUT 1 BYTE INTO BO STACK
         LI        7,0             LOAD DUMMY BYTE COUNT
         BL        BFB             PUT 1 BYTE INTO BO STACK
         LI        7,0             ZERO UNUSED BYTE
         BL        BFB             PUT 1 BYTE INTO BO STACK
         LW        R2,4W,R2        GET PNTR TO STRINGBACK ADDRS ELST-32
         LW        R7,0,R2         GET DSECT STRINGBACK ADDRESS ELST-32
         ANMW      R7,=X'00FFFFFF' MASK OFF TYPE CODE           ELST-32
         BZ        BB.EXT4         NO DSECT REFS IF ABSOLUTE 0  ELST-32
         LW        R7,0,R2         GET DSECT STRINGBACK ADDRESS ELST-32
*!!!!!!!!LW!!!!!!!!R7,4W,R2!!!!!!!!TYPE!AND!TAIL!OF!STRING!BACK!ELST-32
         ZR        6               CLEAR R6 FOR SHIFT
         SLLD      6,1             SHIFT DSECT/CSECT BIT INTO R6
         TRR       6,7             LOAD R7 WITH SECTION
         BL        BFB             PUT 1 BYTE INTO BO STACK
*!!!!!!!!LW!!!!!!!!R7,4W,R2!!!!!!!!TYPE!AND!TAIL!OF!STRING!BACK!ELST-32
*!!!!!!!!TRR!!!!!!!2,5!!!!!!!!!!!!!SAVE!R2!BEFORE!GOING!TO!BFA.0ELST-32
         LW        R7,0,R2         GET DSECT STRINGBACK ADDRESS ELST-32
         BL        BFA             STACK TAIL OF STR.BACK ADDR IN HBBS
*!!!!!!!!TRR!!!!!!!5,2!!!!!!!!!!!!!RESTORE R2!!!!!!!!!!!!!!!!!!!ELST-32
         LW        R2,HWENDL       RESTORE R2                   ELST-32
         LW        R4,2W,R2        GET 1ST 4 CHAR OF SYMBOL NAME
         LW        R5,3W,R2        GET 2ND 4 CHAR OF SYMBOL NAME
         STD       4,HWNAME        PUT IN POSITION FOR BFN.0
         BL        BFN.0           PUT NAME ONTO BINARY OUTPUT STACK
         LI        6,EXPFUNC       GET LOADER FUNCTION CODE
         LW        R1,HABS         BASE ADDR OF BYTE STREAM     ELST-32
         BL        PB              PUBLISH DSECT EXT REF RECORD ELST-32
BB.EXT4  ZMB       HBBS            RESET OUTPUT STREAM POINTER  ELST-32
         LW        R2,HWENDL       RESTORE R2                   ELST-32
         LI        R7,LF.EXTRF     GET LOADER FUNCTION CODE     ELST-32
         BL        BFB             PUT IN BO STACK              ELST-32
         LI        R7,0            LOAD DUMMY BYTE COUNT        ELST-32
         BL        BFB             PUT IN BO STACK              ELST-32
         LI        R7,0            ZERO UNUSED BYTE             ELST-32
         BL        BFB             PUT IN BO STACK              ELST-32
         LW        R2,4W,R2        GET PNTR TO STRINGBACK ADDRS ELST-32
         LW        R7,1W,R2        GET CSECT STRINGBACK ADDRESS ELST-32
         ANMW      R7,=X'00FFFFFF' MASK OFF TYPE CODE           ELST-32
         BZ        END7            NO CSECT REFS IF ABSOLUTE 0  ELST-32
         LW        R7,1W,R2        GET CSECT STRINGBACK ADDRESS ELST-32
         ZR        R6              CLEAR R6                     ELST-32
         SLLD      R6,1            SHIFT OUT DSECT/CSECT BIT    ELST-32
         TRR       R6,R7           SECTION NUMBER TO R7         ELST-32
         BL        BFB             PUT ON BO STACK              ELST-32
         LW        R7,1W,R2        GET CSECT STRINGBACK ADDRESS ELST-32
         BL        BFA             PUT ADDRESS IN BO STACK      ELST-32
         LW        R2,HWENDL       RESTORE R2                   ELST-32
         LW        R4,2W,R2        GET 1ST 4 CHARS OF SYM NAME  ELST-32
         LW        R5,3W,R2        GET 2ND 4 CHARS OF SYM NAME  ELST-32
         STD       R4,HWNAME       PUT IN POSITION FOR BFN.0    ELST-32
         BL        BFN.0           PUT NAME IN BO STACK         ELST-32
         LI        6,EXPFUNC       GET LOADER FUNCTION CODE     ELST-32
END6.1   LW        1,HABS          BASE ADDR OF BIN BYTE STREAM STACK
         BL        PB             PUBLISH BINARY OUTPUT STACK
END7     LW        R2,HWENDL       GET BACK SYMBOL TAB ADDR
*!!!!!!!!ADI!!!!!!!R2,6W!!!!!!!!!!!SYMBOL!TAB!SIZE!!!!!!!!!!!!!!S880752
         LW        R2,5W,X2        GET NEXT ENTRY ADDRESS       S880752
         BNZ       END6            CONTINUE IF NOT DONE         S880752
*!!!!!!!!CAMW!!!!!!R2,SYMCURRP!!!!!ARE!WE!AT!END!OF!TABLE!!!!!!!S880752
*!!!!!!!!BLT!!!!!!!END6!!!!!!!!!MORE!TO!CHECK!!!!!!!!!!!!!!!!!!!S880752
END7.0   CEQU      $                                            ESCT-32
         SPACE
* COMPUTE ADR TO BU TO WHEN LOADING COMPLETE AND PUT IT OUT
         SPACE
         LW        1,=X'81FD0000'  LONG LIST OF TERMINATORS
         BL        UNST            UNSTRUING ADR RO BU TO
         LW        7,HWNAME        THE UNSTRUNG NAME
         CAMW      7,=C'    '      CHECK FOR NO NAME
         BEQ       END8         YES, NO TRANSFER ADDRESS
         LI        2,1             INDICATE UNSTRUNG ALREADY
         BL        VAL             EVALUATE ADDRESS
TESTP    STW       7,HWEVAL        ADR TO BU TO WHEN LOADING DONE
*                            TEST BOUNDING OF RETURNED VALUE    |86.0324
         TBR       7,31            IS IT EVEN                   |86.0324
         BNS       $+3W            SKIP IF IT IS                |86.0324
         SBM       G'B'-X'40',HWERRF    ELSE SET "B" ERROR      |86.0324
         ABM       31,HWERCT            AND BUMP ERROR COUNT    |86.0324
*                                                               |86.0324
         ZMB       HBBN            CLEAR SECTION NUMBER
         TBR       7,0             CHECK FOR DSECT/CSECT
         BNS       END7.1          NOT SET - LEAVE AS ZERO
         SBM       7,HBBN          SET - INITIALIZE TO 1
END7.1   ZMB       HBBS            RESET BINARY OUTPUT STREAM POINTER
         TRR       7,5             HOLD R7 IN R5 FOR EXP.LDR.FUNC.
         TBR       7,8             CHECK FOR ABS/REL
         BNS       BB.XFR2         NOT SET - ABS - STANDARD FUNC
         TBM       EXPLFC,HHBITS3  CHECK FOR CSECT OR NON-ZERO DSECT
         BS        BB.XFR3         YES - GEN EXPANDED LOADER FUNCTIONS
BB.XFR2  BL        BFA             PUT TRANSFER ADR IN BO STACK
         LI        6,PTTR          LOADER FUNC CODE (TERMINAL TRANS ADR)
         BU        BB.RETRN        GO TO PUBLISH/RETURN LOGIC
BB.XFR3  LI        7,LF.TRANS      GET LDR.FUNC. SUB-CODE.
         BL        BFB             PUT 1 BYTE INTO BO STACK
         LI        7,0             LOAD DUMMY BYTE COUNT
         BL        BFB             PUT 1 BYTE INTO BO STACK
         LI        7,0             ZERO UNUSED BYTE
         BL        BFB             PUT 1 BYTE INTO BO STACK
         LB        7,HBBN          GET SECTION NUMBER
         BL        BFB             PUT 1 BYTE INTO BO STACK
         TRR       5,7             GET ADDRESS THAT WAS HELD EARLIER
         BL        BFA.0           STACK ADDRESS
         LI        6,EXPFUNC       GET LOADER FUNCTION CODE
BB.RETRN LW        1,HABS          BASE ADDR OF BIN BYTE STREAM STACK
         BL        PB             PUBLISH BINARY OUTPUT STACK
         SPACE
* ALLOW END CARD OUT
         SPACE
END8     SBM       IMIN,HHBITS     INDICATE BUFFER IMAGE READY
*!!!!!!!!!!LW!!!!!!!!7,HWLTPE!!!!!!!!END!ADR!FOUND!IN!PASS!1!!!!!1.3#03!
         LW        7,DSIZE         USE END OF DSECT              1.3#03
         CAMW      R7,MAX          WHICH IS BIGGER ?            S8700512
         BGE       END8.A          R7, USE END OF DSECT         S8700512
         LW        R7,MAX          MAX, USE IT                  S8700512
END8.A   CEQU      $                                            ESCT-32
         STW       7,HWLSTS        TO STATICIZED PROG CNTR FOR LISTING
         ZMB       HBBS            RESET BINARY OUTPUT STREAM POINTER
         TBM       EXPLFC,HHBITS3  CHECK FOR CSECT OR NON-ZERO DSECT
         BS        END8.1          YES - RETURN
*                                  NO - GEN STANDARD LOADER FUNCTIONS
         BL        BFA             PUT END ADR IN BO STACK
         LI        6,PTO           LOADER FUNC CODE
         LW        1,HABS          BASE ADDR OF BIN BYTE STREAM STACK
         BL        PB             PUBLISH BINARY OUTPUT STACK
*                                  IF NO CSECT HAS BEEN REFERENCED
END8.1   SBM       CVFL,HHBITS     SIGNAL TO PRINT PROGRAM COUNTER
         BL        RELEAS          PRINT OUTPUT
         SPACE
* SEND OUT LAST BYTE
         SPACE
         ZMH       HBBS            CLEAR STACK POS CNTR AND NEXT BYTE
         ABM       7,HBBS          SHOW 1 BYTE OF ZERO IN STACK
         LI        6,X'F'          LOADER FUNC CODE FOR LAST BYTE
         LW        1,HABS          BASE ADR OF BO STACK
         BL        PB             PUBLISH IT
         SPACE
* OUTPUT NUMBER OF ERRORS FOUND DURING PASS 2
         SPACE
         LD        6,ERRORS        GET CONSTANT DATA
         STD       6,HDERCT        TO OUTPUT AREA
         LD        6,ERRORS+1D
         STD       6,HDERCT+1D     TO OUTPUT AREA
         LW        6,ERRORS2
         STW       6,HDERCT+4W
         LD        R6,TCWPROG      LOAD PROGRAM NAME
         STW       6,HDERCT+5W
         STW       7,HDERCT+6W
         LW        6,ERRORS3
         STW       6,HDERCT+7W
         LW        5,HWERCT        GET ERROR COUNT IN BINARY
         BL        CONBAD          CONVERT TO ASCII
         STW       7,HDERCT+1W
         LW        1,HAERCT              ERROR COUNT TCW
         CAMW      7,=C'0000'      ARE THERE ANY ERRORS?
         BNE       $+3W         YES, PRINT NUMBER OF ERRORS.
         TBM       LO,OPTION       IS PRINTOUT DESIRED?
         BS        UNDEFOUT     NO, DON'T PRINT NUMBER ERRORS.
         BL        PPP            OUTPUT ERROR COUNT
         SPACE
* OUTPUT UNDEFINED
* DUMP UNDEFINED SYMBOLS ON LISTING DEVICE
         SPACE
UNDEFOUT LD        6,UNDEFC        CONSTANT WORD 'UNDEFINED'
         STD       6,HDUN00        TO OUTPUT AREA
         LD        6,UNDEFC+1D
         STD       6,HDUN00+1D     TO OUTPUT AREA
*!!!!!!!!LA!!!!!!!!R2,SYMTAB!!!!!!!SYMBOL!TABLE!ADDRESS!!!!!!!!!S880752
         LW        R2,SYMTAB       SYMBOL TABLE ADDRESS         S880752
         BZ        UU0U.1          SKIP IF NO SYMBOLS           S880752
UOUT1    LB        R6,4W,R2        PICK UP TYPE FROM SYM TBL
         ZBR       R6,24           CLEAR DSECT/CSECT FLAG
         CI        R6,TYPU         IS IT UNDEFINED TYPE
         BNE       UOUU         NO-THEN BYPASS IT
         LW        R6,2W,R2        FIRST 4 CHAR OF LABEL
         LW        R7,3W,R2        2ND 4 CHAR OF LABEL
         STD       6,HDUNJF        STORE LABEL IN P/O AREA
         STW       R2,UOUTS2       SAVE R2
         LW       R1,HAUN00        ADR OF DATA
         BL        PPP            PRINTOUT ONE UNDEFINED
         LW       R2,UOUTS2        RESTORE R2
*!UOUU!!!ADI!!!!!!!R2,6W!!!!!!!!!!!BUMP!INDEX!BY!TABLE!ENTRY!SIZS880752
UOUU     CEQU      $                                            ESCT-32
         LW        R2,5W,X2        GET NEXT ENTRY ADDRESS       S880752
         BNZ       UOUT1           CONTINUE IF NOT DONE         S880752
*!!!!!!!!CAMW!!!!!!R2,SYMCURRP!!!!!TEST!FOR!END!OF!TABLE!!!!!!!!S880752
*!!!!!!!!BLT!!!!!!!UOUT1!!!!!!!!!!!LOOP!TO!CHECK!ALL!ENTRIES!!!!S880752
UU0U.1   CEQU      $                                            ESCT-32
         LW        6,HATCWD        LGTH AND ADR OF HEADING LINE.
         BL        EJCT2           FORCE TOP-OF-FORM.
         ABM       5,HHHHS0+3B     INCR RETURN ADR
         BU        *HHHHS0         RETURN TO ADAPTER USED
*
* (C) COPYRIGHT 1983 ENCORE COMPUTER CORPORATION
*     ALL RIGHTS RESERVED
*
         TITLE     READ-ONLY       BFO, BFN, BFA.0, BFB
* GET ITEM FROM SYMBOL TBL AND PUT IN BO STACK
* R2 SET AS POINTER TO ITEM IN SYMBOL TBL
* R7 MUST NOT BE ALTERED (CALL FROM BFC2)
         SPACE
BFO      ZMB       HBBS            RESET BO STACK POINTER
         LW        R4,2W,R2        FIRST 4 CHAR OF SYM NAME
         LW        R5,3W,R2        2ND 4 CHAR OF SYM NAME
         STD       4,HWNAME        INTO POSITION FOR BFN
         SPACE
* PUT NAME FROM HWNAME IN BO STACK
* R7 MUST NOT BE ALTERED
         SPACE
BFN      ZR        1               INITIALIZE POINTER
BFN.0    NOP                       FOR EXP.LDR.FUNC. DON'T INITIALIZE R1
         LI        3,-8            MAX 8 CHAR NAME
BFN1     LB        6,HWNAME+8B,3   GET BYTE
         CI        6,G' '          IS IT A SPACE
         BEQ       BFN2
         ABR       1,31            COUNT IT
         STB       6,HBBS,1        STORE IT IN STACK
         BIB       3,BFN1          LOOP TO DO MAX OF 8 CHAR
BFN2     STB       1,HBBS          STORE COUNT OF NUMBER OF BYTES
         TRSW      0               RETURN
         IFT       CAID,SKIP                                    *CAID*
* PUT ALL EIGHT CHARS OF NAME FROM HWNAME IN BO STACK           *CAID*
* R7 MUST NOT BE ALTERED                                        *CAID*
         SPACE                                                  *CAID*
BFN.0A   NOP                       FOR EXP.LDR.FUNC. DON'T INIT *CAID*
         LI        3,-8            DO 8 CHAR NAME               *CAID*
BFN1A    LB        6,HWNAME+8B,3   GET BYTE                     *CAID*
         ABR       1,31            COUNT IT                     *CAID*
         STB       6,HBBS,1        STORE IT IN STACK            *CAID*
         BIB       3,BFN1A         LOOP TO DO 8 CHAR            *CAID*
         STB       1,HBBS          STORE CNT OF NUMBER OF BYTES *CAID*
         TRSW      0               RETURN                       *CAID*
         SPACE                                                  *CAID*
* PUT 4 BYTES IN R7 INTO THE BINARY STACK HBBS                  *CAID*
* OUTPUT HBBS CONTAINS UPDATED BYTE COUNT AND BYTES ARE IN STACK*CAID*
         SPACE                                                  *CAID*
BFW      CEQU      $                                            *CAID*
         LI        2,-4            4 BYTES TO BE DONE           *CAID*
         ZR        6               CLEAR RECEIVING REGISTER     *CAID*
         LB        1,HBBS          GET CURRENT STACK POSITION   *CAID*
BFW1     SLLD      6,8             SHIFT BYTE IN                *CAID*
         ABR       1,31            INCREMENT STACK COUNT        *CAID*
         STB       6,HBBS,1        STORE BYTE IN STACK          *CAID*
         BIB       2,BFW1          LOOP TO PROCESS 4 BYTES      *CAID*
         STB       1,HBBS          SET NUMBER OF BYTES IN STACK *CAID*
         TRSW      0               RETURN                       *CAID*
         SPACE                                                  *CAID*
* PUT 2 BYTES RIGHT JUSTIFIED IN R7 INTO THE BINARY STACK HBBS  *CAID*
* OUTPUT HBBS CONTAINS UPDATED BYTE COUNT AND BYTES ARE IN STACK*CAID*
         SPACE                                                  *CAID*
BFH      CEQU      $                                            *CAID*
         LI        2,-2            2 BYTES TO BE DONE           *CAID*
         SLL       7,16            POSITION DATA                *CAID*
         ZR        6               CLEAR RECEIVING REGISTER     *CAID*
         LB        1,HBBS          GET CURRENT STACK POSITION   *CAID*
BFH1     SLLD      6,8             SHIFT BYTE IN                *CAID*
         ABR       1,31            INCREMENT STACK COUNT        *CAID*
         STB       6,HBBS,1        STORE BYTE IN STACK          *CAID*
         BIB       2,BFH1          LOOP TO PROCESS 2 BYTES      *CAID*
         STB       1,HBBS          SET NUMBER OF BYTES IN STACK *CAID*
         TRSW      0               RETURN                       *CAID*
SKIP     ANOP                                                   *CAID*
         SPACE
* PUT 3 BYTES WHICH ARE RT JUSTIFIED IN R7 INTO THE BINARY STACK HBBS
* OUTPUT HBBS CONTAINS UPDATED BYTE COUNT AND BYTES ARE IN STACK
         SPACE
BFA.0    CEQU      $               ENTRY FOR EXP.LDR.FUNC. (01  ESCT-32
         ZBR       7,8             CLEAR REL/ABS FLAG BIT (8) FROM ADDR.
BFA      CEQU      $                                            ESCT-32
         LI        2,-3            3 BYTES TO BE DONE
         SLL       7,8             LEFT JUSTIFY DATA
         ZR        6               CLEAR RECEIVING REGISTER
         LB        1,HBBS          GET CURRENT STACK POSITION
BFA1     SLLD      6,8             SHFIT BYTE IN
         ABR       1,31            INCREMENT STACK COUNT
         STB       6,HBBS,1        STORE BYTE IN STACK
         BIB       2,BFA1          LOOP TO PROCESS 3 BYTES
         STB       1,HBBS          RESET NUMBER OF BYTES IN STACK
         TRSW      0               RETURN
         SPACE
* PUT 1 BYTE WHICH IS RT.JUST. IN R7 INTO THE BINARY STACK HBBS
* OUTPUT HBBS CONTAINS UPDATED BYTE COUNT AND BYTES ARE IN STACK
         SPACE
BFB      CEQU      $               ADDED 01/30/78               ESCT-32
         ABM       7,HBBS          INCREMENT STACK COUNT
         LB        1,HBBS          STACK POSITION TO R1
         STB       7,HBBS,1        STORE BYTE IN STACK
         TRSW      0               RETURN
         TITLE     READ-ONLY       LPCP
*        LPOOL PROCESSOR
*        FC NOTE POOL PROCESSOR
         SPACE
LPOP     CEQU      $                                            ESCT-32
         TBM       EXPAND,MACSTATE  ARE WE EXPANDING A MACRO?
         BNS       $+3W         NO.
         ZMW       HWMSPBUF        CLEAR STORE POINTER FOR MACRO PRINT.
         SBM       LPOOLM,SPMAC    INDICATE WE ARE PROCESSING AN
*                                  LPOOL IN A MACRO EXPANSION.
         BL        YEANAY          CHECK WHETHER ASSEMBLY IS ALLOWED
         BNS       LPOP1        DON'T ASSEMBLE.
         TBM       LPOOL31,HHBITS  TOO MANY LPOOLS?
         BNS       LPOP2        NO.
         SBM       G'Z'-X'40',HWERRF
         ABM       31,HWERCT       ERROR IS Z FOR TOO MANY LPOOLS
         BU        $+2W            CONTINUE.
LPOP2    CEQU      $                                            ESCT-32
         BL        PRLIT           PROCESS ANY PENDING LITERALS
         SBM       IMIN,HHBITS
LPOP1    CEQU      $                                            ESCT-32
         ZBM       LPOOLM,SPMAC    FINISHED WITH LPOOL.
         BU        NEXT
         TITLE     READ-ONLY       MACEXP
MACEXP   BL        YEANAY          CHECK IF ASSEMBLY ALLOWED
         BNS       MACEXP3      NO
         LW        1,TALLS1        INDICATE A REQUEST WAS PERFORMED
         LW        3,HWLICT        FOR A MACRO FROM THIS LINE NUMBER
         ZMW       REPTYPE         INDICATE SYMBOL REPORT TO XREF
         BL        REPTR          SO IT WILL SHOW UP IN THE XREF
         BL        TALL            ALLOCATE THE LABEL ON THE MACRO CALL
         ABM       31,LEVEL        INDICATE A LEVEL OF EXPANSION
         SBM       CALLUS,MACSTATE SET CURRENT MACRO CALL INDICATOR
         LW        R4,STKP         EXPANSION STACK POINTER
         TBM       EXPAND,MACSTATE  SEE IF WE ARE EXPANDING A MACRO NOW
         BS        MACEXP2      YES
         LA        R4,STK          ADDR OF EXPANSION STACK
MACEXP2  STW       R4,STKP         INIT POINTER
         LW        R3,HWCMAC       ADDRESS OF PROTOTYPE
         LW        R1,STACKP       CURRENT LEVEL POINTER
         STW       R4,0W,R1        SAVE POINTER TO MACRO PROTO IN STK
*!!!!!!!!SEA!!!!!!!!!!!!!!!!!!!!!!!MACROS!IN!EXT!MEMORY!!!!!!!!!S880752
         LB        R2,4W,R3        GET # OF PARS DEFINED FOR MACRO
*!!!!!!!!CEA!!!!!!!!!!!!!!!!!!!!!!!CLEAR!EXT!MODE!!!!!!!!!!!!!!!S880752
         STB       R2,0W,R1        SAVE PAR COUNT
         ADI       R3,6W           MACRO HEADER SIZE
         STW       R3,1W,R1        SAVE MACRO PROTOTYPE POINTER
         TRR       R4,R3           PAR STORAGE STACK
         TRN       R2,R2           ANY PARAMETERS
         BZ        MACEXP3-1W      BR IF NOT
         LW        R4,=C'    '     ALL SPACES
         LW        R5,=C'    '     ALL SPACES
MACEXP25 STD       R4,0D,R3        INIT STACK
         STD       R4,1D,R3        INIT STACK
         STD       R4,2D,R3        INIT STACK
         ADI       R3,3D           BUMP TO NEXT PAR STORAGE
         BIB       R2,MACEXP25     LOOP TO INIT ALL DUMMY PARS
         STW       R3,MACT         SAVE END OF DUMMY VARIABLES
MACEXP3  LW        1,=X'80080000'  SP AND ,
         BL        UNST            UNSTRING ONE ELEMENT
         BL        YEANAY          CHECK WHETHER ASSEMBLY IS ALLOWED
         BNS    MACEXP5         DONT ASSEMBLE
MACEXP33 LD       R6,HWNAME        GET UNSTRUNG NAME
         ZBM       INTGEN,MACSTATE WAS ARGUMENT AN INT SYMBOL ?
         BS        MACEXP4-2W     YES, DON'T REPLACE IN STACK
         CAMW      6,=C'    '      CHECK FOR BEING PRESE T
         BNE       MACEXP4      DONT GO GENERATE AN INTERNAL TAG
MACEXP36 LW       R5,INTTAG        GET THE LATEST INTERNAL TAG
         ABM       31,INTTAG       INCR INT TAG COUNT.
         ANMW      5,=X'FFFF'      INT SYM NUM.
         BL        BTX             CONVERT TO ASCII.
         SLLD      6,24
         ORMW      7,=X'00202020'  PAD INT NUM WITH TRAILING BLANKS.
         ANMW      6,=X'00FFFFFF'  CLEAR BYTE 0.
         ORMW      6,=X'FF000000'  PLACE INT SYM XREF CHAR INTO INT SYM.
MACEXP4  LW        R1,STKP         POINTS TO CURRENT PLACE IN STACK
         CAMW      R1,MACT         TOO MANY PARS SPECIFIED
         BLE       $+4W            BR IF OK
         SBM       G'X'-X'40',HWERRF    SHOW ERROR
         ABM       31,HWERCT       COUNT THE ERROR
         BU        MACEXP5         SKIP STORAGE OF PARAMETER
         ABM       27,STKP         INCR CURR STACK POINTER BY 16
         ABM       28,STKP         INCR CURR STACK POINTER BY 8
         STD       R6,0D,R1        PLACE ITEM INTO STACK
         LD        R6,HWNAME+1D    GET NEXT 8 CHARS
         STD       R6,1D,R1        PLACE ITEM INTO STACK
         LD        R6,HWNAME+2D    GET NEXT 8 CHARS
         STD       R6,2D,R1        PLACE ITEM INTO STACK
MACEXP5  LB        4,HBSTAC        CHECK TERMINATOR
         CI        4,G','          FOR A COMMA
         BEQ       MACEXP3      GO GET MORE ITEMS
         BL        YEANAY          CHECK WHETHER ASSEMBLY IS ALLOWED
         BNS       MACEXP9      DON'T ASSEMBLE
         LW        R4,MACT         POINTER TO PROTOTYPE STOAGE LOCATION
         STW       R4,STKP         SET STACK POINTER
         LW        R1,STACKP       CURRENT LEVEL POINTER
         STW       R1,MPP          SAVE CURR LEV MACRO PAR POINTER
         ABM       28,STACKP       SET FOR NEXT LEVEL
         SBM       EXPAND,MACSTATE    SHOW WE ARE EXPANDING A MACRO NOW
         SBM       CVFL,HHBITS     INDICATE PRINT PROG CNTR
MACEXP9  ZBM       CALLUS,MACSTATE CLR CURRENT MACRO CALL INDICATOR
         BU        NEXT
         TITLE     READ-ONLY       FORMEXP
FORMEXP  CEQU      $               EXPAND A FORM                ESCT-32
         SBM       FORMGET,INPTSTAT      INDICATE STRIPPING DOWN A FORM
         LW        1,HWCMAC        THE PLACE WHERE THE FORM PROTOTYPE ST
         STW       1,HWCMACP       SAVE THIS FOR COUNTING
         BL        YEANAY          CHECK IF ASSEMBLY ALLOWED
         BNS       VFD          NO
         LW        1,TALLS1        INDICATE A REQUEST WAS PERFORMED
         LW        3,HWLICT        FOR A FORM  FROM THIS LINE NUMBER
         ZMW       REPTYPE         INDICATE SYMBOL REPORT TO XREF
         BL        REPTR          SO IT WILL SHOW UP IN THE XREF
         BL        TALL            ALLOCATE THE LABEL ON THE FORM  CALL
         BU        VFD             FINESSE THIS INTO THE VFD PROCESSOR
         SPACE
FORMEXP1 CEQU      $                                            ESCT-32
         LW        4,HWCMAC        THE PLACE WHERE THE FORM PROTOTYPE ST
         STW       4,HWCMACP       SAVE THIS FOR COUNTING
FORMEXP2 CEQU      $               COME HERE FOR A FORM EXPANS  ESCT-32
         LW        1,HWCMACP       POINTER TO A FORM FIELD COUNT ITEM
         ABM       31,HWCMACP      ADVANCE THE POINTER TO THE BIT LENGTH
*!!!!!!!!SEA!!!!!!!!!!!!!!!!!!!!!!!SET!EXT!MODE!!!!!!!!!!!!!!!!!S880752
         LB        R7,0B,R1        GET ONE BYTE OF FIELD COUNT
*!!!!!!!!CEA!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!S880752
         CI        7,X'FF'         CHECK FOR LIST TERMINATOR
         BNE       VFD2         WITH THE FIELD SIZE IN R7
         BU        FORMEXP1        BOTTOM OF LIST-THEN RESTART IT
         TITLE     READ-ONLY       IFPRO
IFPRO    CEQU      $                                            ESCT-32
         ZMW       PREVRELO        CLEAR OUT POINTER TO PREV RELATION
         LB        4,HWACT         GET TRUE/FALSE REQUIREMENT FLAG
*!!!!!!!!CI!!!!!!!!4,1!!!!!!!!!!!!!CHECK!FOR!IFP/IFA!!!!!!!!!!!!EIFD-32
         CI        R4,3            CHECK FOR IFP/IFA            EIFD-32
         BLE       IFPRO.1B     NOT AN IFP OR IFA               EIFD-32
         LW        1,=X'00080000'  TERM ON COMMA ONLY
         BL        UNST            UNSTRING ENTIRE EXPRESSION
         LB        1,HBPASS        ARE WE IN PASS 2 ?               AS19
         BNE       IFPRO.1         YES,CONTINUE  NO,SKIP            AS19
         ZBM       0,UNSTCK        RESET AND SET DELIM CHECK BIT    AS19
         BNS       IFPRO.1         SHOULD END IN PARAM, NOT DELIM   AS19
         SBM       G'E'-X'40',HWERRF FAULTY PARAMETER LIST-ERROR    AS19
         ABM       31,HWERCT       INCREMENT ERROR COUNT            AS19
IFPRO.1  ZBM       0,UNSTCK        RESET DELIM CHECK BIT            AS19
         LB        1,HBIBYI        BYTE READING POINTER
         CI        1,73            WAS A COMMA FOUND ?
         BGE       IFPRO99      NO - GO MARK ERROR
         BU        IFPROD          GO UNSTRING PLACE TO GO TO
         SPACE
IFPRO.1B CI        R4,2            CHECK FOR IFT/IFF            EIFD-32
         BGE       IFPRO.A         BRANCH IF IFTDEF/IFFDEF      EIFD-32
IFPRO2   CEQU      $                                            ESCT-32
         LW        1,=X'81FD0000'  LONG LIST OF TERMINATORS POSSIBLE
         BL        UNST
         LB        1,HBPASS        ARE WE IN PASS 2 ?               AS19
         BNE       IFPRO2.1        YES,CONTINUE  NO,SKIP            AS19
         ZBM       0,UNSTCK        RESET AND SET DELIM CHECK BIT    AS19
         BNS       IFPRO2.1        SHOULD END IN PARAM, NOT DELIM   AS19
         SBM       G'E'-X'40',HWERRF FAULTY PARAMETER LIST-ERROR    AS19
         ABM       31,HWERCT       INCREMENT ERROR COUNT            AS19
IFPRO2.1 ZBM       0,UNSTCK        RESET DELIM CHECK BIT            AS19
         LI        1,-SIZCOND      SIZE OF CONDITIONAL LIST
         LW        4,HWNAME        THE UNSTRING
         CAMW      4,=C'    '      ! IS TOKEN BLANK?
         BEQ       IFPRO9       ! SKIP BLANKS AND CONTINUE SCANNING
         CAMW      4,CONDLIST,1    CHECK FOR MATCH
         BEQ       FIND         A MATCH
         BIW       1,$-2W          CHECK WHOLE LIST
         LI        2,1             SIGNAL FIRST ELEMENT PART UNSTRUNG
         BL        VAL             EVALUATE THE UNSTRUNG ELEMENT
         LW        1,PREVRELO      POINTER TO PREVIOUS RELATION OPERATOR
         LI        4,1
         SLL       7,9             THROW AWAY TYPE CODE.
         SRA       7,9
         CAMW      7,IFET          COMPARE TO PREVIOUS VALUE
         EXM       IFCONDBR,1      EXECUTE THE PROPER JUMP FOR A .TRUE.
         ZR        4               FALL THRU FOR FALSE
IFPRO5   CEQU      $                                            ESCT-32
         STW       4,IFET          SAVE THE TRUE/FALSE INDICATOR
         BU        IFPRO9          GO GET NEXT ELEMENT
         SPACE
IFINIT   CEQU      $                                            ESCT-32
         STW       7,IFET          SAVE THE VALUE FOR THE TERM
         BU        IFPRO9          GO GET NEXT ELEMENT
         SPACE
IFPRAND  CEQU      $                                            ESCT-32
         ANMW      7,IFET         AND PREVIOUS LOG COND WITH LATEST ONE
         STW       7,IFET          UPDATE THE LOGICAL CONDITION
         BU        IFPRO9          GO GET NEXT ELEMENT
         SPACE
IFPROR   CEQU      $                                            ESCT-32
         ORMW      7,IFET          OR PREVIOUS LOG COND WITH LATEST ONE
         STW       7,IFET          UPDATE THE LOGICAL CONDITION
         BU        IFPRO9          GO GET NEXT ELEMENT
         SPACE
FIND     CEQU      $                                            ESCT-32
         STW       1,PREVRELO      SAVE THE POINTER TO THIS OPERATOR
IFPRO9   CEQU      $                                            ESCT-32
         LB        7,HBSTAC        GET THE LAST ERMINATOR
         CI        7,G','          FOR BEING A COMMA
         BEQ       IFPROD       FOUND A COMMA , NO MORE TERMS
*                                  TO CHECK
         LB        1,HBIBYI        BYTE READING POINTER
         CI        1,73            DID WE TRY TO GO BEYOND COLUMN 72?
         BLT       IFPRO2       NO, GO CHECK SOME MORE TERMS.
IFPRO99  CEQU      $                                            ESCT-32
         BL        YEANAY          ARE WE ASSEMBLING?
         BNS       NEXT         NO.
         SBM       G'E'-X'40',HWERRF   MARK 'E' ERROR
         ABM       31,HWERCT
         BU        NEXT
         SPACE     2
IFPROD   CEQU      $                                            ESCT-32
         ZBM       INTGEN2,MACSTATE  CLEAR IT OUT INTIALLLY
         TBM       INTGEN,MACSTATE CHECK IND OF INTERNAL LABEL IN EXP.
         BNS       $+2W         INTGEN WAS NOT ON-DONT COPY A 1
         SBM       INTGEN2,MACSTATE  INTGEN IS ON SO COPY IT
         LW        1,=X'80080000'  SP AND ,
         BL        UNST            UNSTRING THE PLACE TO GO TO
         LB        1,HBPASS        ARE WE IN PASS 2 ?               AS19
         BNE       IFPROD.1        YES,CONTINUE  NO,SKIP            AS19
         ZBM       0,UNSTCK        RESET AND SET DELIM CHECK BIT    AS19
         BNS       IFPROD.1        SHOULD END IN PARAM, NOT DELIM   AS19
         SBM       G'E'-X'40',HWERRF FAULTY PARAMETER LIST-ERROR    AS19
         ABM       31,HWERCT       INCREMENT ERROR COUNT            AS19
IFPROD.1 ZBM       0,UNSTCK        RESET DELIM CHECK BIT            AS19
         LB        4,HWACT         GET THE TRUE/FALSE REQUIREMENT FLAG
         CI        4,20            CHECK FOR IFP FLAG
         BEQ       IFPROD2      IT IS AN IFP.
         CI        4,21            CHECK FOR IFA FLAG.
         BNE       IFPRO7       NOT AN IFA--MUST BE IFF/IFT.
         TBM       INTGEN2,MACSTATE  ANY INT GEN SYMBOLS PRESENT?
         BS        NEXT         YES--SKIP COND SCAN.
         BU        IFPRO8          ALLOW COND SCAN IF ASSEMBLING
         SPACE
IFPROD2  TBM       INTGEN2,MACSTATE  ANY INT GEN SYMBOLS PRESENT?
         BNS       NEXT         NO--SKIP COND SCAN
         BU        IFPRO8          ALLOW COND SCAN IF ASSEMBLING
         SPACE
IFPRO7   CEQU      $                                            ESCT-32
         EOMB      4,IFET+3        COMPARE IT TO TRUE FALSE CASE OF EXPR
         BNE       NEXT         NO MATCH-GO GET NEXT WHOLE STATEMENT
IFPRO8   CEQU      $                                            ESCT-32
         LD        6,HWNAME        THE NAME WE CAN RESUME ASSEMBLY AT
         STD       6,HWSCNHP       FOR LATER SET-UP
         BU        GOTOPE    MAYBE START A NEW CONDITIONAL ASSEMBLY SCAN
*
IFPRO.A  CEQU      $                                            EIFD-32
         ZBM       1,IFFLG         CLEAR SYMBOL FOUND FLAG      EIFD-32
         LW        1,=X'00080000'  TERMINATE ON COMMA           EIFD-32
         BL        UNST            GET TEST SYMBOL              EIFD-32
         LW        R2,SYMTAB       GET SYMBOL TABLE ADDR        EIFD-32
         BZ        IFPRO.B         NO SYMBOLS IF ZERO           EIFD-32
IFPRO.A2 LW        R4,2W,X2        GET SYMBOL FROM TABLE        EIFD-32
         LW        R5,3W,X2        GET SECOND HALF              EIFD-32
         CAMD      R4,HWNAME       COMPARE WITH TEST SYMBOL     EIFD-32
         BNE       $+3W            NEXT SYMBOL IF NOT EQUAL     EIFD-32
         SBM       1,IFFLG         SHOW SYMBOL DEFINED          EIFD-32
         BU        IFPRO.B         CONTINUE                     EIFD-32
         LW        R2,5W,X2        GET NEXT SYMBOL ADDR         EIFD-32
         BZ        IFPRO.B         NO MORE IF ZERO              EIFD-32
         BU        IFPRO.A2        CONTINUE COMPARING           EIFD-32
IFPRO.B  CEQU      $                                            EIFD-32
         LW        1,=X'80080000'  GET TERMINATORS              EIFD-32
         BL        UNST            GET JUMP LABEL               EIFD-32
         LB        R4,HWACT        GET TRUE/FALSE CONDITION     EIFD-32
         CI        R4,2            IS IT IFTDEF?                EIFD-32
         BEQ       IFPRO.A3        BRANCH IF SO                 EIFD-32
         TBM       1,IFFLG         WAS SYMBOL DEFINED           EIFD-32
         BNS       NEXT            NEXT INSTR IF NOT DEFINED    EIFD-32
         LD        R4,HWNAME       ELSE GET JUMP NAME           EIFD-32
         STD       R4,HWSCNHP      AND SAVE                     EIFD-32
         BU        GOTOPE          SKIP TO THAT LABEL           EIFD-32
IFPRO.A3 TBM       1,IFFLG         WAS SYMBOL DEFINED?H         EIFD-32
         BS        NEXT            NEXT INSTR IF SO             EIFD-32
         LD        R4,HWNAME       ELSE GET JUMP NAME           EIFD-32
         STD       R4,HWSCNHP                                   EIFD-32
         BU        GOTOPE          SKIP TO SPECIFIED LABEL      EIFD-32
*                                                               EIFD-32
IFFLG    DATAB     0       SYMBOL DEFINED/UNDEFINED FLAG        EIFD-32
         BOUND     1W                                           EIFD-32
*
* (C) COPYRIGHT 1983 ENCORE COMPUTER CORPORATION
*     ALL RIGHTS RESERVED
*
         TITLE     READ-ONLY       SETPRO
SETPRO   CEQU      $                                            ESCT-32
         LB        7,HWACT         GET THE POINTER TO SET,SETT,SETF
         CI        7,2             CHECK FOR WHICH SET TYPE
         BLT       SETPRO4      NOT A VALUE SET-JUST TRUE OR FALSE
         LI        2,2             EVALUATE NEXT LINE ELEMENT
         BL        VAL             TO A NUMERIC VALUE
SETPRO4  STW       7,SETPROV       VALUE AMOUNT, OR TRU, OR FALSE
         BL        YEANAY          CHECK FOR ASSEMBLY ALLOWED
*        BNS       NEXT         NO ASSEMBLY ALLOWED
         BS        SETPR4.1     ASSEMBLY ALLOWED
         LW        1,=X'80000000'  TERMINATE ON SP
         BL        UNST         UNSTRING REMAINDER OF LINE
         BU        NEXT
SETPR4.1 CEQU      $                                            ESCT-32
         LB        6,HWACT         GET POINTER                  EBRM-33
         CI        6,3             CHECK IF OPTS,OPTR,OPTT      EBRM-33
         BLT       OPT.6           PROCESS SET TYPE DIRECTIVE   EBRM-33
         ANMW      7,=X'003FFFFF'  GET BIT NUMBER               EBRM-33
         CI        7,32            CHECK IF IN RANGE            EBRM-33
         BLE       OPT.1           OKAY, IT'S IN RANGE          EBRM-33
         CI        R7,55           OPTION 55 SPECIFIED?         EIEE-33
         BEQ       OPT.7           YES...BRANCH                 EIEE-33
         SBM       G'X'-X'40',HWERRF  MARK ERROR                EBRM-33
         ABM       31,HWERCT       COUNT IT                     EBRM-33
         BU        NEXT                                         EBRM-33
OPT.1    CEQU      $                                            ESCT-32
         TRR       7,2                                          EBRM-33
         SUI       2,1             MAKE OPTION # 0-REL          EBRM-33
         SLL       2,2             MAKE IT A WORD INDEX         EBRM-33
         LW        7,MSKTBL,2      GET APPROPRIATE BIT MASK     EBRM-33
         ANMW      7,OPTMSK        MAKE SURE IT'S A LEGAL OPT   EBRM-33
         BZ        OPT.2           OKAY, BRANCH                 EBRM-33
         SBM       G'X'-X'40',HWERRF OTHERWISE FLAG ERROR       EBRM-33
         ABM       31,HWERCT                                    EBRM-33
         BU        NEXT                                         EBRM-33
         SPACE                                                  EBRM-33
OPT.2    CEQU      $                                            ESCT-32
         LW        7,MSKTBL,2      GET BIT MASK AGAIN           EBRM-33
         CI        6,3             IS IT "OPTS"?                EBRM-33
         BNE       OPT.3           NO, BRANCH                   EBRM-33
         ORMW      7,OPTION        YES, SET THE OPTION          EBRM-33
         STW       7,OPTION                                     EBRM-33
         LI        7,1             INSURE SYMBOL VALUE IS 1     EBRM-33
         BU        OPT.5                                        EBRM-33
         SPACE                                                  EBRM-33
OPT.3    CEQU      $                                            ESCT-32
         CI        6,4             IS IT "OPTR"?                EBRM-33
         BNE       OPT.4           NO, BRANCH                   EBRM-33
         TRC       7,7             YES, COMPLEMENT MASK         EBRM-33
         ANMW      7,OPTION        AND RESET THE OPTION         EBRM-33
         STW       7,OPTION                                     EBRM-33
         ZR        7               INSURE SYMBOL VALUE IS 0     EBRM-33
         BU        OPT.5                                        EBRM-33
         SPACE                                                  EBRM-33
OPT.4    CEQU      $               MUST BE "OPTT"               ESCT-32
         ANMW      7,OPTION        GET THE OPTION               EBRM-33
         BZ        OPT.5           NOT SET, RETURN "FALSE"      EBRM-33
         LI        7,1             OTHERWISE, RETURN "TRUE"     EBRM-33
OPT.5    CEQU      $                                            ESCT-32
         STW       7,SETPROV       SET THE VALUE FOR THE LABEL  EBRM-33
         LB        4,HBSTAC        CHECK THAT WE TERMINATED ON A SPACE
         CI        4,G' '          YES, ONLY ONE OPTION SPECIFIED
         BEQ       OPT.6
         SBM       G'X'-X'40',HWERRF  MARK ERROR
         ABM       31,HWERCT       COUNT IT
         LW        1,=X'80000000'  TERMINATE ON SPACE
         BL        UNST            UNSTRING REST OF LINE
         LW        7,SETPROV
OPT.6    CEQU      $                                            ESCT-32
         LI        7,TYSETSYM
         STB       7,SETPROV       SET TYPE CODE FOR SYMBOL TABLE
         LW        1,HWINAC        FETCH TYPE CODE
         SRL       1,23            AND ALIGN FOR COMPARE
         CI        1,TYPP*2+X'101' IS IT PROG REL CSECT?
         BEQ       SETPRO5         YES
         CI        1,TYPX*2+X'101' IS IT EXT REL CSECT?
         BNE       SETPRO6         NO
SETPRO5  SBM       0,SETPROV       INDICATE CSECT IN SET TYPE
SETPRO6  CEQU      $                                            ESCT-32
         LW        1,SETPROV
         LD        4,HWLABL        THE NAME TO WHICH WE SET A COND OR VA
         BL        SS              SET IT TO THE CURRENT ARGUMENT
         TBM       DPFLG,DPFLAGS   IS IT DATAPOOL
         BNS       NEXT            NO, GET NEXT STATEMENT
         SBM       G'V'-X'40',HWERRF   MARK 'V' ERROR
         ABM       31,HWERCT           COUNT ERROR
         BU        NEXT            GO GET NEXT STATEMENT
OPT.7    CI        R6,3            IS THIS AN OPTS?             EIEE-33
         BNE       OPT.8           NO...BRANCH                  EIEE-33
         TBM       ASCT.OPT,OPTION    IS OPTION 18 SET?         EIEE-33
         BS        OPT.7B          YES...BRANCH                 EIEE-33
         IFF       UNIXF,SKIP                                   *JCB*
         LB        R5,MSG1.L       GET MESSAGE LENGTH           EIEE-33
         STW       R5,FCBLO+9W     SAVE IN FCB                  EIEE-33
         LA        R5,MSG1.A       GET MESSAGE ADDRESS          EIEE-33
         STW       R5,FCBLO+8W     SAVE IN FCB                  EIEE-33
         LA        R1,FCBLO        GET LO FCB ADDRESS           EIEE-33
         SVC       1,X'32'         WRITE OUT MESSAGE            EIEE-33
         LB        R5,MSG2.L       WRITE OUT SECOND PART        EIEE-33
         STW       R5,FCBLO+9W                                  EIEE-33
         LA        R5,MSG2.A                                    EIEE-33
         STW       R5,FCBLO+8W                                  EIEE-33
         SVC       1,X'32'                                      EIEE-33
         LW        R5,AS31         GET ABORT CODE               EIEE-33
         SVC       1,X'57'         AND ABORT                    EIEE-33
SKIP     ANOP                                                   *JCB*
         IFT       UNIXF,SKIP                                   *JCB*
         LB        R1,MSG1.L       GET MESSAGE LENGTH           *JCB*
         LA        R2,MSG1.A       GET MESSAGE ADDRESS          *JCB*
         BL        PSTDERR         PRINT MESSAGE ON STD ERROR   *JCB*
         LB        R1,MSG2.L       GET MESSAGE LENGTH           *JCB*
         LA        R2,MSG2.A       GET MESSAGE ADDRESS          *JCB*
         BL        PSTDERR         PRINT MESSAGE ON STD ERROR   *JCB*
         BU        ABRTM1-1W       GO ABORT WITH AS31           *JCB*
SKIP     ANOP                                                   *JCB*
OPT.7B   RDSTS     R2              READ CPU STATUS WORD         EIEE-33B
         LI        R5,X'F'         LOAD MASK                    EIEE-33B
         ANR       R5,R2           ISOLATE MACHINE TYPE         EIEE-33B
         BNZ       OPT.7D          BRANCH IF NOT A 32/2000      EIEE-33B
         ZR        R3                                           EIEE-33B
         SBR       R3,0            SET BIT TO READ CPU INFO     EIEE-33B
         RPSWT     R3              READ CPU INFO                EIEE-33B
         TBR       R3,0            IS THIS AN RSX MACHINE       EIEE-33B
         BS        OPT.7C          YES...BRANCH                 EIEE-33B
         IFF       UNIXF,SKIP                                   *JCB*
OPT.7D   LB        R5,MSG5.L       GET MESSAGE LENGTH           EIEE-33
         STW       R5,FCBLO+9W     SAVE IN FCB                  EIEE-33
         LA        R5,MSG5.A       GET MESSAGE ADDRESS          EIEE-33
         STW       R5,FCBLO+8W     SAVE IN FCB                  EIEE-33
         LA        R1,FCBLO        GET LO FCB ADDRESS           EIEE-33
         SVC       1,X'32'         WRITE OUT MESSAGE            EIEE-33
         LW        R5,AS31         GET ABORT CODE               EIEE-33
         SVC       1,X'57'         AND ABORT                    EIEE-33
SKIP     ANOP                                                   *JCB*
         IFT       UNIXF,SKIP                                   *JCB*
OPT.7D   LB        R1,MSG5.L       GET MESSAGE LENGTH           *JCB*
         LA        R2,MSG5.A       GET MESSAGE ADDRESS          *JCB*
         BL        PSTDERR         PRINT MESSAGE ON STD ERROR   *JCB*
         BU        ABRTM1-1W       GO ABORT WITH AS31           *JCB*
SKIP     ANOP                                                   *JCB*
OPT.7C   SBM       9,OPTION2       SET OPTION 55                EIEE-33
         BU        OPT.5           AND CONTINUE                 EIEE-33
OPT.8    CI        R6,4            IS THIS AN OPTR?             EIEE-33
         BNE       OPT.9           NO...BRANCH                  EIEE-33
         ZBM       9,OPTION2       CLEAR OPTION 55              EIEE-33
         BU        OPT.5           AND CONTINUE                 EIEE-33
OPT.9    TBM       9,OPTION2       ELSE OPTT, OPTION 55 SET?    EIEE-33
         BNS       OPT.5           NO...BRANCH                  EIEE-33
         LI        R7,1            SHOW OPTION 55 WAS SET       EIEE-33
         BU        OPT.5           AND CONTINUE                 EIEE-33
         TITLE     READ-ONLY       GOTOP
GOTOP    CEQU      $               GOTO PROCESSOR               ESCT-32
         LW        1,=X'80080000'  SP AND ,
         BL        UNST            UNSTRING IT
         LD        6,HWNAME        THE PLACE WE WILL LOOKK FOR
         STD       6,HWSCNHP       POSSIBLE NAME OF WHAT WE WEILL SCAN F
         LB        4,HBSTAC        GET TERMINATING CHARACTER
         CI        4,G' '          CHECK FRR COMPLETE END
         BEQ       GOTOPE       UNCONDITIONAL GOTO
         LI        2,1             SIGNAL FIRST UNSTRUNG ALREADY
         BL        VAL             EVALUATE THE FIRST LIST ITEM
         LW        4,=X'00FFFFFF'  CHECK ONLY THE VALUE PART
         TRRM      7,7             STRIP OFF TYPE
         TRN       7,7             NEGATE IT FOR USE AS A COUNTER
         STW       7,GOTOC         SAVE FOR COUNTING
         ZBM       7,GOTOCB        SIGNAL WE HAVE NOT FOUND GOTO PLACE Y
GOTOPC   CEQU      $                                            ESCT-32
         LB        7,HBSTAC        CHECK TERMINATOR
         CI        7,G','          ARE THERE MORE ELEMENTS IN STATEMENT
         BNE       GOTOPD       NO-THEN WE ARE DONE WITH THE LIST
         LW        1,=X'80080000'  SP AND ,
         BL        UNST            UNSTRING ONE LIST ITEM
         ABM       31,GOTOC        INCREMENT LIST COUNT
         LW        7,GOTOC         CHECK CURRENT COUNT
         BNE       GOTOPC       NOT AT EXACT POINT IN LIST
         LD        4,HWNAME        THE PLACE WE WILL SCAN TO
         STD       4,HWSCNHP       HOLD IT FOR LATER SET-UP
         SBM       7,GOTOCB        FLAG THAT WE HAVE FOUND THE ITEM
         BU        GOTOPC          SCAN REST OF LIST
         SPACE
GOTOPD   TBM       7,GOTOCB        HAVE WE FOUND THE PLACE IN THE LIST
         BNS       NEXT         NO-GOTO NOT TO BE DONE THEN
GOTOPE   BL        YEANAY          CHECK WHETHER ASSEMBLY IS ALLOWED
         BNS    NEXT            DONT ASSEMBLE
         LD        6,HWSCNHP                NAME OF WHAT WE  WILL SCAN F
         STD       6,LABLSCAN      SO FRONT END WILL LOOK FOR IT
         SBM       CONDSCAN,MACSTATE    SET SCAN FLAG ON-NO MORE ASSEMBL
         BU        NEXT            GO GET NEXT SOURCE ITEM
         TITLE     READ-ONLY       DEFMPRO
DEFMPRO  TBM       CONDSCAN,MACSTATE   ARE WE SKIPPING SOURCE?
         BS        DEFMPROE     YES.
         TBM       RSCAN,MACSTATE      ARE WE IN A REPT SCAN?
         BS        DEFMPROE     YES.
         TBM       EXPAND,MACSTATE     ARE WE EXPANDING?
         BS        DEFMPROB         YES.
         TBM       DEFMBODY,MACSTATE   ARE WE IN A PROTO BODY?
         BNS       DEFMPRO1         NO.
DEFMPROB SBM       G'A'-X'40',HWERRF    SET ERROR 'A'
         ABM       31,HWERCT       COUNT THIS ERROR
DEFMPROE LW        1,=X'80080000'  TERM ON A SPACE OR COMMA.
         BL        UNST            UNSTRING ONE PARAMETER.
         LB        6,HBSTAC        GET THE TERMINATOR.
         CI        6,G' '          WAS IT A SPACE?
         BNE       DEFMPROE     NO-CONTINUE UNSTRINGING PARAMETERS.
         BU        NEXT
         SPACE
DEFMPRO1 TBM       7,HBPASS        WHICH PASS ARE WE IN?
         BS        $+3W         PASS 1.
         SBM       DEFFRM2,SPMAC   SET PASS 2 DEFM-FORM BIT.
         BU        DEFMPRO3        DON'T RE-ENTER NAME IN SYM TAB.
*!!!!!!!!SBM!!!!!!!2,PGATE!!!!!!!!!FIRST!TIME!THRU!EVER?!!!!!!!!S880752
*!!!!!!!!BS!!!!!!!!MACPX!!!!!!!!!!!BR!IF!NOT!!!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!SVC!!!!!!!1,X'69'!!!!!!!!!M.GD!-!GET!EXT!DATA!SPACE!!!!S880752
*!!!!!!!!TRR!!!!!!!R3,R3!!!!!!!!!!!SET!CC'S!!!!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!BZ!!!!!!!!MNOK!!!!!!!!!!!!BR!IF!NO!SPACE!!!!!!!!!!!!!!!S880752
*!!!!!!!!STW!!!!!!!R3,LOW!!!!!!!!!!SAVE!START!ADDR!!!!!!!!!!!!!!S880752
*!!!!!!!!STW!!!!!!!R4,HIGH!!!!!!!!!SAVE!LAST!ADDR!!!!!!!!!!!!!!!S880752
*!!!!!!!!STW!!!!!!!R3,CURRP!!!!!!!!INIT!STACK!ADDR!!!!!!!!!!!!!!S880752
*!!!!!!!!ZMW!!!!!!!MACP!!!!!!!!!!!!INIT!MAC!POINTER!!!!!!!!!!!!!S880752
*!!!!!!!!ZMW!!!!!!!MA2P!!!!!!!!!!!!INIT!MA2!POINTER!!!!!!!!!!!!!S880752
*!MACPX!!!LW!!!!!!!R1,CURRP!!!!!!!!GET!STACK!POINTER!!!!!!!!!!!!S880752
         LA        R6,STACK        GET PARAMETER STACK ADDR
         STW       R6,STACKP       RESET POINTER
*!!!!!!!!STW!!!!!!!R2,HWMSP!!!!!!!!SAVE!POINTER!TO!MACRO!!!!!!!!S880752
*!!!!!!!!LI!!!!!!!!6,TYMACDEF!!!!!!MACRO!DEFINITION!TYPE!CODE!!!S880752
*!!!!!!!!STB!!!!!!!6,HWMSP!!!!!!!!!SET!IT!INTO!TABLE!!!!!!!!!!!!S880752
         LND       4,HWLABL        THE NEGATED UNSTRUNG FORM NAME
*!!!!!!!!LW!!!!!!!!1,HWMSP!!!!!!!!!TYPE!AND!BASE!LOCATION!OF!!!!S880752
         ZR        R1              CLEAR R1                     S880752
         LI        R1,TYMACDEF     GET MACRO DEF. TYPE CODE     S880752
         SLL       R1,24           POSITION IN REGISTER         S880752
         BL        SS              ENTER IT INTO SYMBOL TABLE
         LW        R1,CURRP        GET STACK POINTER            S880752
         ADI       R1,7B           ROUND TO NEXT DOUBLE WORD BOUND
         ANMW      R1,=X'00FFFFF8' FORCE DOUBLE WORD BOUND
         STW       R1,CURRP        DOUBLE WORD BOUND STACK POINTER
         STW       R1,HEAD         INITIALIZE THIS HEAD CELL
         ADI       R1,6W           HEADER SIZE
         STW       R1,CURRP        UPDATE CURR POINTER          S880752
         CAMW      R1,HIGH         SEE IF OUT OF ROOM IN MAP
         BLT       DEFX2           BR IF ROOM AVAILABLE
         SVC       1,X'69'         GET ANOTHER MAP BLOCK
         TRR       R3,R3           SET CC'S
         BZ        MNOK            BR IF MEM NOT AVAILABLE
         STW       R4,HIGH         UPDATE NEW HIGH ADDR
*!DEFX2!!!STW!!!!!!R1,CURRP!!!!!!!!UPDATE!CURR!POINTER!!!!!!!!!!S880752
DEFX2    CEQU      $                                            ESCT-32
         ZMW       DEFCNT          ZERO NUMBER OF NEW MACRO CHARS COUNT
         LW        R2,HEAD         GET CURRENT HEAD CELL ADDR
         STW       R2,HWMSP        SAVE IN PROTOTYPE POINTER    S880752
         LI        R6,TYMACDEF     GET MACRO TYPE CODE          S880752
         STB       R6,HWMSP        SAVE IN ENTRY                S880752
         LW        R1,SYMCURRP     GET CURRENT ENTRY POINTER    S880752
         LW        R6,HWMSP        GET PROTOTYPE POINTER        S880752
         STW       R6,4W,R1        PUT PROTOTYPE PNTR IN ENTRY  S880752
         LD        R6,HWLABL       GET MACRO NAME
*!!!!!!!!SEA!!!!!!!!!!!!!!!!!!!!!!!GO!EXTENDED!!!!!!!!!!!!!!!!!!S880752
         STD       R6,2W,R2        SAVE MACRO NAME
         ZMD       0W,R2           CLEAR HEAD CELL POINTERS
         ZMD       4W,R2                CLEAR COUNT AND STRING WORD
*!!!!!!!!CEA!!!!!!!!!!!!!!!!!!!!!!!CLEAR!EXT!ADDR!!!!!!!!!!!!!!!S880752
DEFMPRO3 LW        1,=X'80080000'  SP AND ,
         BL        UNST            UNSTRING ONE PROTOTYPE PARAMETER
         LW        4,HWNAME        GET THE WORD FROM INPUT
         CAMW      4,=C'    '      CHECK FOR NOTHING THERE
         BEQ       DEFMPRO5     NO MORE ARGUMENTS IN LIST
         TBM       DEFFRM2,SPMAC   IN PASS 2 DEFM-FORM SCAN?
         BS        DEFMPRO7     YES.
         LD        4,HWNAME        THE DUMMY ARGUMENT NAME
         LW        R1,STACKP       GET PARAMETER STACK ADDR
         STW       R4,0W,R1        PLACE ITEM INTO STACK
         STW       R5,1W,R1        AND SECOND WORD OF FORMAL NAME
         ABM       28,STACKP       INCREMENT THE STACK POINTER
         ABM       7,DEFCNT        INCR NUM PARAMETERS FOUND
DEFMPRO7 LB        4,HBSTAC        GET THE TERMINATOR
         CI        4,G','          THIS MEANS MORE PARAMETERS
         BEQ       DEFMPRO3     GO GET THE REMAINING PARAMETERS
DEFMPRO5 SBM       DEFMBODY,MACSTATE    SHOW WE ARE NOW GOING INTO BODY
         BU        NEXT            LET THE PROTYPE BODY COME IN
         TITLE     READ-ONLY       ENDMPRO
ENDMPRO  TBM       EXPAND,MACSTATE   CHECK FOR EXPANSION ON
         BS        ENDM6        WE ARE EXPANDING A MACRO
         TBM       DEFMBODY,MACSTATE    CHECK IF WE ARE IN A BODY
         BS        ENDM11       YES-NO ERROR
         TBM       CONDSCAN,MACSTATE   ARE WE SKIPPING SOURCE?
         BS        NEXT         YES.
         TBM       RSCAN,MACSTATE      ARE WE IN A REPT SCAN?
         BS        NEXT         YES.
ENDM5    SBM       G'A'-X'40',HWERRF
         ABM       31,HWERCT       INCREMENT ERROR COUNTER
         BU        ENDM10          EQU
         SPACE
ENDM6    LW        R1,STACKP       POINTER TO NAME STACK FOR PROTOTYPE
         SUI       R1,2W           CONTRACT THE POINTER IN THE STACK.
         STW       R1,STACKP       DUMP LAST MACRO DEFINATION
         SPACE
******ADD CODE FOR REPT HERE *******
         SPACE
         CAMW      R1,=A(STACK)     HAVE WE REACHED BOTTOM OF STACK?
         BEQ       ENDM6.3      YES.
         LW        4,LEVEL         IS MACRO DEPTH LEVEL IN REPT ZERO?
         BEQ       ENDM8        YES.
         LI        4,-1            DECREMENT FIELD.
         ARMW      4,LEVEL         DECREAS MACRO DEPTH LEVEL WITHIN REPT
         BU        ENDM8           KEEP LOOKING FOR PROTO PTR.
         SPACE
***** ADD CODE FOR REPT HERE*******
         SPACE
ENDM6.3  ZMW       LEVEL           ZERO MACRO DEPTH LEVEL WITHIN REPT
         LA        R1,STK          PAR STACK ADDR
         STW       R1,STKP         RESET POINTER
         LA        R1,STACK        MACRO LEVEL STACK
         STW       R1,STACKP       REINIT POINTER
         STW       R1,MPP          INIT STACKP FOR THIS LEV
         ZMB       MACSTATE        ZERO OUT ALL MACRO STATUS BITS
         BU        ENDM10          ALL DONE WITH MACRO EXPANSION
         SPACE
ENDM8    SUI       R1,2W           POINT TO PREVIOUS LEVEL
         LB        R5,0W,R1        GET PARAMETER COUNT FOR PREVIOUS LEV
         MPI       R4,3D           MAKE DOUBLE WORD OFFSET
         ADMW      R5,0W,R1        CALC NEW STKP
         STW       R5,STKP         NEW EXPANSION STORAGE
         STW       R1,MPP          THIS LEVEL STACKP
         LW        R4,1W,R1        ADDR OF MACRO STORAGE AREA
         STW       R4,HWCMAC       RESTORE MACRO POINTER
ENDM10   ZBM       DEFMBODY,MACSTATE   CLEAR MACRO BODY FLAG
         ZBM       DEFFRM2,SPMAC   CLEAR PASS 2 DEFM-FORM BIT.
         BU        NEXT            DONE WITH ENDM
         SPACE
ENDM11   LA        R1,STACK        MACRO LEVEL STACK
         STW       R1,STACKP       REINIT POINTER
         ZBM       DEFFRM2,SPMAC   TEST FOR PASS 2 DEF BODY
         BS        ENDM10          BR IF PASS 2
         LW        R2,MACP         CONT OF MAC POINTER
         BNZ       ENDMIT          BR IF INITIALIZED
         LW        R2,HEAD         GET STACK POINTER
         STW       R2,MACP         PUT IN MAC POINTER
ENDMIT   LW        R1,HEAD         GET NEW ENTRY ADDRESS
         LW        R7,DEFCNT       GET COUNT OF BYTES/PARMS IN MACRO
*!!!!!!!!SEA!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!S880752
         STW       R7,4W,R1        PUT IN STACK FOR LATER
         LD        R4,MACRO,R1    GET MACRO FROM NEW ENTRY
EN15     CAMD      R4,MACRO,R2    COMPARE AGAINST LAST NODE ENTRY
         BLT       EN50            NEW .LT. LAST
         BEQ       EN95            THEY ARE .EQ. (SHOULDN'T HAPPEN)
         LW        R3,RLINK,R2     NEW .GT. LAST, FOLLOW ASSENDING LINK
         BZ        EN90            ZERO MEANS END OF BRANCH
EN30     TRR       R3,R2           GENERATE PATH POINTER
         BU        EN15            GO TRY NEXT BRANCH NODE
         SPACE
EN50     LW        R3,LLINK,R2     GET DECENDING PATH
         BNZ       EN30            IF NOT END, GO UPDATE
         STW       R1,LLINK,R2     UPDATE LINK IN PREVIOUS NODE
         BU        EN95            GO CLEAR NEW ENTRY NODE POINTERS
EN90     STW       R1,RLINK,R2     UPDATE RLINK IN PREVIOUS NODE
EN95     ZMW       RLINK,R1        CLEAR NEW ENTRY NODE POINTERS
         ZMW       LLINK,R1        DITTO
*                                  NOW GO TRANSFER TO USER
*!!!!!!!!CEA!!!!!!!!!!!!!!!!!!!!!!!R1=ENTRY!ADDR,!R7=BYTE!COUNT!S880752
         BU        ENDM10
         SPACE
EXITMP   BL        YEANAY          CHECK FOR ASSEMBLY ALLOWED
         BNS       NEXT         DONT PROCESS THIS EXITM
         TBM       EXPAND,MACSTATE   ARE WE EXPANDING A MACRO NOW
         BS        ENDM6        YES-THEN TERMINATE IT EARLY
         BU        ENDM5           NO-THEN WE HAVE AN ERROEOUS EXITM
         TITLE     READ-ONLY       FORMP
FORMP    BL        YEANAY          CHECK WHETHER ASSEMBLY IS ALLOWED
         BNS       FORMP3       DONT ASSEMBLE
         TBM       EXPAND,MACSTATE  ARE WE EXPANDING?
         BS        $+3W         YES--ERROR.
         TBM       RPTGEN,MACSTATE  ARE WE GENERATING REPT CODE?
         BNS       FORMP2.5     NO.
         SBM       G'A'-X'40',HWERRF   MARK A ERROR.
         ABM       31,HWERCT       COUNT THE ERROR.
FORMP2   LW        1,=X'80080000'   TERM ON A SPACE OR COMMA
         BL        UNST            UNSTRING ONE BIT LENGTH DESCRIPTOR.
         CI        7,G','          ARE WE FINISHED?
         BEQ       FORMP2       NO--FINISH UNSTRINGING.
         BU        NEXT
         SPACE
FORMP2.5 CEQU      $    $                                       ESCT-32
         TBM       7,HBPASS        WHICH PASS ARE WE IN?
         BS        $+3W         PASS 1.
         SBM       DEFFRM2,SPMAC   SET PASS 2 DEFM-FORM BIT.
         BU        FORMP3          DON'T RE-ENTER NAME IN SYM TAB.
*!!!!!!!!SBM!!!!!!!2,PGATE!!!!!!!!!FIRST!TIME!THRU!EVER?!!!!!!!!S880752
*!!!!!!!!BS!!!!!!!!FORMPX!!!!!!!!!!BR!IF!NOT!!!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!SVC!!!!!!!1,X'69'!!!!!!!!!M.GD!-!GET!EXT!DATA!SPACE!!!!S880752
*!!!!!!!!TRR!!!!!!!R3,R3!!!!!!!!!!!SET!CC'S!!!!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!BZ!!!!!!!!MNOK!!!!!!!!!!!!BR IF NO SPACE!!!!!!!!!!!!!!!S880752
*!!!!!!!!STW!!!!!!!R3,LOW!!!!!!!!!!SAVE!START!ADDR!!!!!!!!!!!!!!S880752
*!!!!!!!!STW!!!!!!!R4,HIGH!!!!!!!!!SAVE!LAST!ADDR!!!!!!!!!!!!!!!S880752
*!!!!!!!!STW!!!!!!!R3,CURRP!!!!!!!!INIT!STACK!ADDR!!!!!!!!!!!!!!S880752
*!!!!!!!!ZMW!!!!!!!MACP!!!!!!!!!!!!INIT!MAC!POINTER!!!!!!!!!!!!!S880752
*!!!!!!!!ZMW!!!!!!!MA2P!!!!!!!!!!!!INIT!MA2!POINTER!!!!!!!!!!!!!S880752
*!FORMPX!!!LW!!!!!!R1,CURRP!!!!!!!!GET!STACK!POINTER!!!!!!!!!!!!S880752
         LND       R4,HWLABL       GET NEGATED FORM NAME        S880752
         ZR        R1                                           S880752
         LI        R1,TYFRM        GET FORM DEF. TYPE CODE      S880752
         SLL       R1,24           POSITION IN REGISTER         S880752
         BL        SS              ALLOCATE SYMTAB ENTRY        S880752
         LW        R1,CURRP        GET STACK POINTER            S880752
         ADI       R1,7B           ROUND TO NEXT DOUBLE WORD BOUND
         ANMW      R1,=X'00FFFFF8' FORCE DOUBLE WORD BOUND
         STW       R1,CURRP        DOUBLE WORD BOUND STACK POINTER
         STW       R1,HEAD         INITIALIZE THIS HEAD CELL
*!!!!!!!!ADI!!!!!!!R1,256B!!!!!!!!!MAXIMUM!FORM!SIZE!!!!!!!!!!!!S880752
FORMX1   CEQU      $                                            ESCT-32
         CAMW      R1,HIGH         SEE IF OUT OF ROOM IN MAP
         BLT       FORMX2          BR IF ROOM AVAILABLE
         SVC       1,X'69'         GET ANOTHER MAP BLOCK
         TRR       R3,R3           SET CC'S
         BZ        MNOK            BR IF MEM NOT AVAILABLE
         STW       R4,HIGH         UPDATE NEW HIGH ADDR
*!FORMX2!!!ZMW!!!!!DEFCNT!!!!!!!!!!ZERO!NUMBER!OF!NEW!MACRO!!!!!S880752
FORMX2   CEQU      $                                            ESCT-32
         ZMW       DEFCNT          ZERO NUM OF NEW MACRO CHARS  S880752
         LW        R2,HEAD         GET CURRENT HEAD CELL ADDR
         STW       R2,HWMSP        SAVE POINTER TO MACRO PROTOTYPE IN EX
         LI        4,TYFRM         TYPE CODE FOR A FORM STATEMENT
         STB       4,HWMSP         DEFINE THE MACRO STORAGE POINTER AS F
         LND       4,HWLABL        THE NEGATED UNSTRUNG PROTOTYPE NAME
         LW        1,HWMSP         WHERE IT IS WITHIN MACRO STORAGE
         LW        R2,SYMCURRP     GET CURRENT ENTRY POINTER    S880752
         STW       R1,4W,R2        PUT PROTOTYPE PNTR IN ENTRY  S880752
*!!!!!!!!BL!!!!!!!!SS!!!!!!!!!!!!!!ALLOCATE!IT!FOR!LATER!REFERENS880752
FORMP3   LI        2,2             INDICATE NOTHING UNSTRUNG YET
         BL        VAL             EVALUATE THE BIT  LENGTH
         ANMW      7,=X'000FFFFF'  LOOK ONLY AT THE VALUE
         CI        7,254           NO MORE THAN 254 BITS ALLOWED
         BGT       FORMPE       ERROR IF OUT OF THE RANGE
         SBM       FORMSCAN,INPTSTAT  SET THE FORM SCAN STATE
         BL        YEANAY          CHECK MODE
         BNS       $+2W         DONT ASSEMBLE
         BL        MBYT            COPY THE THING OUT
         ZBM       FORMSCAN,INPTSTAT   WIPE OUT FORM TRACES
         LB        7,HBSTAC        GET THE TERMINATOR
         CI        7,G'",'         CHECK FOR A CONTINUING MARK
         BEQ       FORMP3       WE HAVE ONE
         SBM       FORMSCAN,INPTSTAT  SET THE FORM SCAN STATE
         LI        7,X'FF'         TERMINATOR CHARACTER
         BL        YEANAY          CHECK MODE
         BNS       $+2W         DONT ASSEMBLE
         BL        MBYT            COPY OUT THE TERMINATOR
         ZBM       FORMSCAN,INPTSTAT   WIPE OUT FORM TRACES
         ZBM       DEFFRM2,SPMAC   CLEAR PASS 2 DEFM-FORM BIT.
         BU        NEXT            GO GET NEXT STATEMENT
*
* (C) COPYRIGHT 1983 ENCORE COMPUTER CORPORATION
*     ALL RIGHTS RESERVED
*
         SPACE
FORMPE   CEQU      $                                            ESCT-32
         BL        YEANAY          ARE WE ASSEMBLING?
         BNS       $+3W         NO
         SBM       G'H'-X'40',HWERRF     SET FLAG H
         ABM       7,HWERCT+3B     COUNT THE ERROR
         ZBM       DEFFRM2,SPMAC   CLEAR PASS 2 DEFM-FORM BIT.
         BU        NEXT            CANT DO ANYTHING WITH IT
         TITLE     READ-ONLY       REPTP
REPTP    CEQU      $                                            ESCT-32
         ZBM       RSCAN,MACSTATE  ARE WE ALREADY IN A REPT SCAN
         BS        REPTPE       ERROR
         BL        TALL            ALLOCATE THE LABEL
         LI        2,2             INDICATE TO SKIP SPACES AND UNSTRING
         ZBM       0,VALUNDF       INSURE VALID TEST
         BL        VAL             GET HOW MANY TIMES WE SHOULD REPEAT
         ZBM       0,VALUNDF       WAS VAL UNDEFINED
         BNS       $+2W            BR IF NOT
         ZR        R7              SET REPT COUNT TO ZERO FOR UNDEFINED
         STH       7,HHRCOUNT      SAVE THAT COUNT
         TBM       DEFMBODY,MACSTATE     CHECK FOR BEING IN MIDDLE OF DE
         BS        NEXT         WE ARE IN A DUMMY MACRO-IGNORE THIS S
         TBM       CONDSCAN,MACSTATE   CHECK FOR CONDITIONAL ASSEMBLY.
         BS        NEXT         CONDITIONAL ASSEMBLY--IGNORE THIS.
         ZMH       HHRDCOLC        ZERO TIMES THROUGH COUNTER
         SBM       RSCAN,MACSTATE    INDICATE WE ARE REPEAT SCANNING
*!!!!!!!!SBM!!!!!!!2,PGATE!!!!!!!!!FIRST!TIME!THRU!EVER?!!!!!!!!S880752
*!!!!!!!!BS!!!!!!!!REPTPX!!!!!!!!!!BR!IF!NOT!!!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!SVC!!!!!!!1,X'69'!!!!!!!!!M.GD!-!GET!EXT!DATA!SPACE!!!!S880752
*!!!!!!!!TRR!!!!!!!R3,R3!!!!!!!!!!!SET!CC'S!!!!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!BZ!!!!!!!!MNOK!!!!!!!!!!!!BR!IF!NO!SPACE!!!!!!!!!!!!!!!S880752
*!!!!!!!!STW!!!!!!!R3,LOW!!!!!!!!!!SAVE!START!ADDR!!!!!!!!!!!!!!S880752
*!!!!!!!!STW!!!!!!!R4,HIGH!!!!!!!!!SAVE!LAST!ADDR!!!!!!!!!!!!!!!S880752
*!!!!!!!!STW!!!!!!!R3,CURRP!!!!!!!!INIT!STACK!ADDR!!!!!!!!!!!!!!S880752
*!!!!!!!!ZMW!!!!!!!MACP!!!!!!!!!!!!INIT!MAC!POINTER!!!!!!!!!!!!!S880752
*!!!!!!!!ZMW!!!!!!!MA2P!!!!!!!!!!!!INIT!MA2!POINTER!!!!!!!!!!!!!S880752
*!REPTPX!!!LW!!!!!!R1,CURRP!!!!!!!!GET!STACK!POINTER!!!!!!!!!!!!S880752
         LW        R1,CURRP        GET STACK POINTER            S880752
         ADI       R1,7B           ROUND TO NEXT DOUBLE WORD BOUND
         ANMW      R1,=X'00FFFFF8' FORCE DOUBLE WORD BOUND
         STW       R1,CURRP        DOUBLE WORD BOUND STACK POINTER
         STW       R1,HEAD         INITIALIZE THIS HEAD CELL
         CAMW      R1,HIGH         SEE IF OUT OF ROOM IN MAP
         BLT       REPTX2          BR IF ROOM AVAILABLE
         SVC       1,X'69'         GET ANOTHER MAP BLOCK
         TRR       R3,R3           SET CC'S
         BZ        MNOK            BR IF MEM NOT AVAILABLE
         STW       R4,HIGH         UPDATE NEW HIGH ADDR
REPTX2   ZMW       DEFCNT          ZERO NUMBER OF NEW MACRO CHARS COUNT
         LW        R2,HEAD         GET CURRENT HEAD CELL ADDR
         STW       R2,HWMSP        SAVE POINTER TO REPT CODE STORAGE
         STW      R2,HWREPSS       HOLDS BASE POINT OF REPEATED CODE
         BU        NEXT            GO GET NEXT STATEMENT
         SPACE
REPTPE   CEQU      $                                            ESCT-32
         SBM       G'Y'-X'40',HWERRF   SET FLAG Y
         ABM       31,HWERCT       COUNT THIS ERROR
         BU        NEXT
         TITLE     READ-ONLY       ENDRP
ENDRP    CEQU      $                                            ESCT-32
         TBM       DEFMBODY,MACSTATE     CHECK FOR BEING IN MIDDLE OF DE
         BS        NEXT         WE ARE IN A DUMMY MACRO-IGNORE THIS S
         TBM       CONDSCAN,MACSTATE   CHECK FOR CONDITIONAL ASSEMBLY.
         BNS       ENDRP1       NO.
         ZBM       RPTGEN,MACSTATE ARE WE IN REPEATED GENERATION?
         BNS       NEXT         NO--IGNORE THIS.
         BU        ENDRF           GO TERMINATE REPEATED GENERATION.
ENDRP1   CEQU      $                                            ESCT-32
         ZBM       RPTGEN,MACSTATE CHECK FOR BEING IN REPEATED GENERATIO
         BS        ENDRPR       A NEW PASS-FIDDLE WITH COUNTS
         ZBM       RSCAN,MACSTATE  CHECK FOR A PREVIOUS REPT
         BNS       REPTPE       NOT SO-ERRORONEOUS ENDR
         TBM       EXPAND,MACSTATE  ARE WE EXPANDING A MACRO NOW
         BNS       ENDRPR       NO--NO LEVLEL MANIPULATION TO BE DONE
         SBM       MACREP,MACSTATE INDICATE A REPEAT WITHIN AN EXPANSION
         ZMW       LEVEL           SHOW NO EXPANSIONS WITHIN REPT YET
ENDRPR   CEQU      $                                            ESCT-32
         ABM       15,HHRDCOLC     COUNT THE NUMBER OF TIME  REPEATED
         LH        7,HHRCOUNT      NUMBER OF TIMES LEFT TO REPEAT
         SUI       7,1             TAKE   IT DOWN BY ONE
         BLT       ENDRF        FINISHED   IF NOW LESS THAN ZERO
         STH       7,HHRCOUNT      THE NEW COUNT
         SBM       RPTGEN,MACSTATE    FLAG A GENERATE SCAN TO FOLLOW
         LW        4,HWREPSS       HOLDS BASE POINT OF REPEATED CODE
         STW       4,HWREPSP       TEMPORARY POINTER FOR USE BY INPT
         BU        NEXT            GO GET NEXT STATEMENTFOR REPETITION
         SPACE
ENDRF    CEQU      $                                            ESCT-32
         ZBM       MACREP,MACSTATE   END    A REPEAT WITHIN AN EXPANSION
         LW        4,HWREPSS       THE BASE OF THE REPEATED CODE
         STW       4,HWMSP         GIVE THE REPEAT STORAGE BACK
         SPACE
*        STW       R4,CURRP        GIVE REPEAT STORAGE BACK
         SPACE
*        FOR LATER USE BY MACROS OR MORE REPEATS
         SPACE
         BU        NEXT            GO GET THE NEXT STATEMENT
         TITLE     READ-ONLY       MBYT
*        RECEIVE BYTE OF PROTOTYPE FOR STORAGE
         SPACE
MBYT     TBM       RSCAN,INPTSTAT      TEST FOR REPEAT SCAN
         BS        MBYT1           GO STORE IF YES
         TBM       DEFFRM2,SPMAC   IN PASS 2 DEFM-FORM SCAN?
         BS        MBYT3        YES.
         TBM       DEFMBODY,INPTSTAT    IN DEFM
         BS        MBYT1           BR IF YES
         TBM       FORMSCAN,INPTSTAT    IN FORM DEF
         BNS       MBYT3           BR IF NOT
MBYT1    ABM       31,DEFCNT        COUNT BYTES.
         STF       R0,LIBREG       SAVE THE REGS
         LW        1,CURRP         POINTER TO PROTOTYPE STORAGE
*!!!!!!!!SEA!!!!!!!!!!!!!!!!!!!!!!!GO!EXTENDED!IN!CASE!IN!EXT!MES880752
         STB       R7,0B,R1        SAVE THE PROTOTYPE BYTE
*!!!!!!!!CEA!!!!!!!!!!!!!!!!!!!!!!!RETURN!TO!NONEXTENDED!MODE!!!S880752
         ABM       31,CURRP        UPDATE STACK POINTER
         LW        R2,CURRP        GET CURR STACK POINTER
         CAMW      R2,HIGH         WILL WE GO OVER END WITH THIS REC?
         BLE       MBYT2           BR IF STILL ROOM
         SVC       1,X'69'         GET ANOTHER MAP BLOCK
         TRR       R3,R3           TEST FOR OK
         BZ        MNOK            BR IF NO MORE MEM AVAILABLE
         STW       R4,HIGH         SAVE NEW ENDING ADDR
MBYT2    LF        R0,LIBREG       UNSV CALLERS REGS
MBYT3    TRSW      0               RETURN
         TITLE     READ-ONLY       STACKCHK
*        CHECK TO SEE IF MACRO TABLE HAS OVERFLOWED AND RETURN TO
*        USER IF IT HAS NOT.
         SPACE     1
STACKCHK STW      R1,STCKCHK1      SAVE USER'S REG 1.
*!!!!!!!!LA!!!!!!!R1,SYMTAB!!!!!!!!END!OF!STACK!ADDR!!!!!!!!!!!!S880752
         LA        R1,STKEND       END OF STACK ADDRESS         S880752
         CAMW      R1,STACKP       CHECK FOR STACK OVERFLOW
         BGT       $+3W         STILL ENOUGH ROOM IN MACRO TABLE
         LW        1,OVFLCONT      GET OVERFLOW MESSAGE.
         BL        ABORTM         MACRO TABLE HAS OVERFLOWED.
         LW        1,STCKCHK1      RESTORE USER'S REG 1.
         TRSW      0               RETURN TO USER
         TITLE     READ-ONLY       PBYT, YEANAY
*        PLACE THE EXPANDED BYTE INTO THE PRINT BUFFER ALTERNATE
         SPACE
PBYT     CEQU      $                                            ESCT-32
         STW       1,PBYTS1        SAVE ORIGINAL X1
         LW        1,HWMSPBUF      POINTER TO WHERE TO STOEE MACRO
         CI        1,80            LIMIT TO SIZE OF THE BUFFER
         BCF       LT,$+2W         DONT OVERWRITE THE BUFFER
         STB       7,MPBUF,1       PLACE THE EXPANSION BYTE INTO BUFFER
         ABM       31,HWMSPBUF     POINT TO NEXT CHAR
         LW        1,PBYTS1        UNSV ORIGINAL X1
         TRSW      0               RETURN
         SPACE     2
*         CHECK WHETHER TO ASSEMBLE OR NOT, CC1=0 MEANS NOT,ELSE DO
         SPACE
YEANAY   CEQU      $               NO INPUT TO THIS ROUTINE     ESCT-32
         ZBR       0,1             MAKE SURE CC1 IS OFF FOR DEFAULT
         TBM       FALSE,MACSTATE  ALWAYS OFF
         TBM       RSCAN,MACSTATE     CHECK FOR BEING IN A REPEAT SCAN
         TBM       CONDSCAN,MACSTATE    CHECK FOR CONDITIONAL ASSEMBLY O
         TBM       DEFMBODY,MACSTATE     CHECK WHETHER WE IGNORE THIS
         BCT       ANY,$+1W+1H     THERE ARE FLAGS THAT SAY NOT TO ASSEM
         SPACE
*        BLE ANY CODE CURRENTLY.
         SPACE
         SBR       0,1             ALLOW ASSEMBLY TO OCCUR
         TRSW      0               RETURN WITH A FLAG SET
         TITLE     READ-ONLY       GRPS
*SCAN ALL OF THE VALUE EXPRESSIONS IN THE OPERAND FIELD. THE EVALUATED
* EXPRESSIONS AND THEIR TYPE ARE PUT IN NL1-NL5 AND THEIR NON-NUMERIC
* TERMINATORS ARE PUT IN NM1-NM5
         SPACE     1
GRPS     CEQU      $                                            ESCT-32
         STW       0,GRPSS0
         LI        1,-10W          NUMBER OF LOCATIONS TO BE CLEARED
         ZMW       HWNM5+1W,1      ZERO OUT RECEIVENG AREA
         BIW       1,$-1W          LOOP TO ZERO ALL OF AREA
         ZMW       HWINDR          CLEAR INDIRECT ADDRESSING FLAG
         LI        6,-5            NUMBER OF EXPRESSIONS POSSIBLE
         STW       6,GRPW
         LA        6,HWNL1         ADR OF VALUE LIST
         LA        7,HWNM1         ADR OF TERMINATOR FOUND LIS<
         STD       6,GRPV          SAVE ADDRESSES
GRPS1    LW        1,=X'81FD0004'  LONG LIST OF TERMINATORS
         BL        UNST            UNSTRING
         LW        6,HWNAME        4 CHAR OF UNSTRUNG NAME
         CAMW      6,=C'    '      IS IT SPACES
         BNE       GRPS2        NO, CAN'T BE LITERAL OR INDIRECT
         CI        7,G'*'          WAS THE TERMINATOR AN *
         BEQ       GRPS3        YES, GO PROCESS INDIRECT ADDRESS
         CI        7,G'='          WAS THER TERMINATOR AN =
         BEQ       GRPS3        YES, GO PROCESS LITERAL
         SPACE
* WE HAVE AN UNSTRUNG ELEMENT READY
         SPACE
GRPS2    LI        2,1             INDICATE TO VAL THAT ELEMENT UNSTRUNG
GRPS2A   BL        VAL             EVALUATE EXPRESSION
         TBM       ASCT.OPT,OPTION    IS AUTO SECTIONING ON?    EBAC-33C
         BNS       GRPS2B          BRANCH IF NOT                EBAC-33C
         CAMW      R7,=X'06000000'   IS THIS AN EXTERNAL REF?   EBAC-33C
         BNE       GRPS2B          BRANCH IF NOT                EBAC-33C
         SBM       3,BACFLAG       SET FLAG FOR EXTERNAL        EBAC-33C
GRPS2B   ZR        6
         SLLD      6,9             GET TYPE + A/R FROM 7 INTO 6
         ZBR       6,23            CLEAR DSECT/CSECT FLAG
         CAMB      6,VDTO          IS  IT PROG ABS TYPE?
         BEQ       GRPS2A5      YES - AOK
         CAMB      6,VDTO+2B       IS IT COMMON TYPE?
         BEQ       GRPS2A3         YES
         ZMB       HBBN            INDICATE DSECT (0)
         TBM       31,SECNUMAC     WAS IT A CSECT REF?
         BNS       GRPS2A4         NO - OK
         SBM       7,HBBN          INDICATE CSECT REF
         BU        GRPS2A4
GRPS2A3  LB        6,HWINACBN      COMMON BLOCK NUMBER
         STB       6,HBBN          ISOLATE IT
GRPS2A4  BL        FAC             DEF IT COMM, EXT, REL ALLOWED
GRPS2A5  LW        6,HWINAC        EXPRESSION FROM VAL
         BU        GRPS8
         SPACE
* PROCESS LITERAL OR INDIRECT
         SPACE
GRPS3    BL        FAC             DETERMINE IF ALLOWED
         BCT       1,GRPS8         NOT ALLOWED
         CI        7,G'='          IS IT A LITERAL
         BEQ       GRPS4        YES, GO TO LITERAL PROCESSOR
         SPACE
* PROCESS INDIRECT
         SPACE
         TBM       BM.OPT,OPTION   CHECK IF BASE MODE SET
         BNS       GRPS3A          NO, INDIRECT IS OKAY
         BL        YEANAY          CHECK WHETHER ASSEMBLY IS ALLOWED
         BNS       GRPS3B          NO
         SBM       G'S'-X'40',HWERRF   SET INDIRECT ERROR
         ABM       31,HWERCT       INCREMENT ERROR COUNT
         BU        GRPS3B
GRPS3A   SBM       11,HWINDR       SET INDIRECT FLAG
GRPS3B   ZR        2
         BU        GRPS2A
         SPACE
* LITERAL PROCESSOR
         SPACE
GRPS4    CEQU      $                                            ESCT-32
         LI        6,4             SIGNAL WORD
         STB       6,TOT           LENGTH CONSTANT FOR TDAT
         LI        6,2W
         STB       6,HBTTTF        SIGNAL DIRECT DATA TO LITERAL AREA
         LB        6,HBAVAR
         STB       6,GRPSS1        SAVE ADDRESSING TYPE
         LW        6,HWERRF        GET THE TEMPORARY ERROR FLAGS
         STW    6,HWERRFA   ALTERNATE ERROR FLAGS DURING LITERAL MAKE-UP
         ZMW       HWERRF          CLEAR THIS UP FOR A LATER TEST
         ZMW       HWINAC          INITIAL DEFAULT FOR ADR EVALUATION
         ZMB       HWINACBN
         LW        1,HWKSPA        SPACES.
         STW       1,HBSTAC        CLEAR TERMINATOR STACK.
         BL        TDAT
         BL        YEANAY          CHECK WHETHER ASSEMBLY IS ALLOWED
         BNS       GRPS8        DON'T ASSEMBLE
         LW        6,HWERRF        GET THE CURRENT ERROR FLAG
         ORMW   6,HWERRFA   ALTERNATE ERROR FLAGS DURING LITERAL MAKE-UP
         TBM       G'U'-X'40',HWERRF     SET FLAG U FOR UNDEFINED
         STW       6,HWERRF        RESTORE THE TOTAL ERROR FLAGS
         BS        GRPS6        THERE WAS ONE, FLAG IT
         LI        4,X'7F80'
         LMH       4,HWINAC        TYPE CODE
         SRL       4,7             RIGHT JUSTIFY TYPE CODE FOR ERR CHECK
         CI        4,0             IS LITERAL A CONSTANT?
         BEQ       GRPS4.5      YES.
         CAMB      4,VDTO          IS LITERAL PROG. ABS?
         BEQ       GRPS4.5      YES.
         CAMB      4,VDTO+1B       IS LITERAL PROG. REL?
         BEQ       GRPS4.5      YES.
         CAMB      4,VDTO+2B       IS LITERAL COMMON?
         BNE       GRPS6        NO--ERROR.
GRPS4.5  LW        5,HWINAC        WORD CONTAINING TYPE CODE
         ZR        4               ZERO RECEIVING REG
         SLLD      4,9             TYPE CODE TO R4
         SLL       4,8             POSITION TYPE CODE FOR
*                                  SYMBOL TABLE ENTRY
*                                  TABLE ENTRY.
         ORMB      4,HWINACBN      OR IN THE BLOCK NUMBER, IF ANY
         LW        5,HDTDS+1W      LITERAL EVALUATION
         LW        1,HWLTCT        TYPE,LPOOL NUMBER AND LIT COUNTER
         BL        SS              ENTER LITERAL IN SYM TBL
         TRR       3,6             SAVE OUTPUT DEFINITION FROM SS
         SLL       6,2             CONVERT LITERAL NUMBER TO DISPLACEMEN
         ANMW      6,=X'003FFFFC'  ISOLATE LITERAL DISPLACEMENT.
         EOMW      3,HWLTCT        WAS THIS A NEW LITERAL
         BNE       GRPS7        NO, SS OTMIZED IT WITH ANOTHER
         SPACE
* NEW LITERAL FOUND
         SPACE
         ABM       31,HWLTCT       INCR LITERAL COUNTER
GRPS7    LB        R3,4W+1B,R2     GET LPOOL # FROM SYMBOL TABLE
         ADMW      6,LITORGS,3     ADD IN THE BASE FOR THIS LPOOL
         LB        3,GRPSS1        ADDRESSING USER WANTED
         STB       3,HBAVAR        RESET IN CASE IT WAS CHGD IN LITERAL
         ADMB      6,GRPSS2,3      OFFSET ADR TO GET CORRECT PART OF WD
         ZMB       HBBN            CLEAR SECTION NUMBER
         TBR       6,0             IS LIT POOL IN CSECT?
*        BNS       GRPS8           NO - CONTINUE
         BNS       GRPS7.1         NO - CONTINUE
         SBM       7,HBBN          INDICATE LIT REF IN CSECT
         BU        GRPS8
GRPS7.1  CEQU      $               CHECK IF ITS COMMON          ESCT-32
         LB        3,4W+1B,2       GET LPOOL NUMBER
         LB        2,LITORGS,3     GET TYPE CODE
         CI        2,TYPC          IS IT COMMON?
         BNE       GRPS8           NO, LEAVE AS DSECT
         LB        2,LITORGS+1B,3  GET BLOCK NUMBER
         STB       2,HBBN          SAVE IT
         BU        GRPS8
GRPS6    BL        YEANAY          ARE WE ASSEMBLING?
         BNS       $+3W         NO.
         SBM       G'X'-X'40',HWERRF   MARK X ERROR.
         ABM       31,HWERCT       COUNT THE ERROR
GRPS8    STW       6,*GRPV         STORE IN VALUE LIST
         SPACE
* R5 SET BY CNUM WHEN CALLED BY VAL
         SPACE
         STW       5,*GRPV+1W      STORE NON-NUMERIC TERMINATOR EQUIV
         LB        6,HBSTAC        FETCH TERMINATOR
         CI        6,G' '          WAS IT A SPACE
         BEQ       GRPS9        YES, WE ARE FINISHED
         ABM       29,GRPV         NO, INCR VALVE LIST WORD ADDRESS
         ABM       29,GRPV+1W      INCR TERMINATOR LIST WORD ADDRESS
         ABM       31,GRPW         INCR COUNT
         BLT       GRPS1        NOT FINISHED - EVALUATE NEXT ONE
GRPS9    LI        1,X'0F'         LOOK ONLY AT 4 BITS
         ANMB      1,HWACT+2B      GET THE DESCRIPTOR FOR ARGUMENT CHECK
         ZBR       1,29            THIS TELLS WHETHER TO CHECK ARG 2 FOR
         ZBR       1,28            THIS TELLS WHETHER TO CHECK ARG 1 FOR
         BCT       1,GRPS9B        CHECK ARGUMENT NUMBER 1 FOR BEING EVE
         BCF       2,GRPS11        DONT CHECK ARG 2 FOR BEING EVEN
         TBM       31,HWNL2        IS ARGUMENT 2 EVEN
         BNS       GRPS11       YES-THEN THERE IS NO ERROR
GRPS10   CEQU      $                                            ESCT-32
         BL        YEANAY          CHECK WHETHER ASSEMBLY IS ALLOWED
         BNS    GRPS11          DONT ASSEMBLE
         SBM       G'B'-X'40',HWERRF   FLAG AN ERROR IN REGISTER BOUNDS
         ABM       31,HWERCT       COUN THIS ERROR
         BU        GRPS11
GRPS9B   TBM       31,HWNL1        CHECK ARG 1 FOR BEING EVEN
         BS        GRPS10       THE ARG IS NOT EVEN-THEREFORE IN ERRO
GRPS11   LW        6,GRPW          NUMBER OF OPERANDS COUNTER
         ADI       6,6             CONVERT TO A ZERO TO 5 RANGE OF VALUE
         CAMB      6,ARGMAX,1      COMPARE ACTUAL  NUMBER TO MAX NUMBER
         BGT       GRPS12       TOO MANY ARGUMENTS
         CAMB      6,ARGMIN,1      CHECK AGAINST MINIMUM NUMBER OF ARGUM
         BGE       GRPS19       NOT TOO FEW, NOT TOO MANY ARGUMENTS
GRPS12   CEQU      $
         BL        YEANAY          CHECK WHETHER ASSEMBLY IS ALLOWED
         BNS    GRPS19          DONT ASSEMBLE
         SBM       G'X'-X'40',HWERRF   FLAG WRONG NUMBER OF ARGUMENTS
         ABM       31,HWERCT       COUNT THIS ERROR
GRPS19   BU        *GRPSS0         RETURN-HAVING EVALUATED ALL OPERANDS
*
* (C) COPYRIGHT 1983 ENCORE COMPUTER CORPORATION
*     ALL RIGHTS RESERVED
*
         TITLE     READ-ONLY       FAC
* CHECK OP CODE DESCRIPTOR TO DETERMINE IF RELATIVE, COMMON, OR EXTERNAL
* EXPRESSION IS ALLOWED IN THIS FIELD OF THE STATEMENT. IF NOT PERMITTED
* AN ERROR IS FLAGGED AND CC BIT 1 IS SET
         SPACE     1
FAC      CEQU      $                                            ESCT-32
         LI        4,X'F0'         SET UP MASK
         LMB       6,HWACT+2B      GET NUMBER OF LEGAL FIELD
         LW        2,GRPW          NEG NUMBER OF EXPRESSIONS REMAINING
         ADI       2,6             NEG NO. REMAIN + 6 = NO. OF CURRENT
         SRL       6,4
         CAR       6,2             IS R,C OR EXT ALLOWED
         BEQ       FAC2
* COME HERE TO FLAG ERROR
         TRR       0,4             SAVE RETURN ADDRESS
         BL        YEANAY          ARE WE ASSEMBLING?
         BNS       $+3W         NO.
         SBM       G'R'-X'40',HWERRF   MARK R ERROR.
         ABM       31,HWERCT       COUNT THE ERROR
         TRR       4,0             RESTORE RETURN ADDRESS
         SBR       1,0             INDICATE ILLEGAL CONDITION
FAC2     TRSW      0               RETURN
         TITLE     READ-ONLY       VAL
* EVALUATE ONE EXPRESSION---INPUT- R2BIT 31=1 MEANS ELEMENT UNSTRUNG ALR
* OUTPUT- R7 AND HWINAC B0-7 CONTAIN TYPE CODE, B8=1 MEANS REL
*         BITS 9-31 CONTAN THE NUMERIC EQUIVALENT OF THE EXPRESSION
*        R5 CONTAINS THE NUMERIC EQUIV OF THE NON-NUMERIC TERMINATOR
         SPACE     1
VAL      CEQU      $                                            ESCT-32
         STW       0,VALS0         SAVE RETURN ADDRESS
         ZMW       HWINAC          CLEAR ACCUMULAND
         ZMW       ACCUM           CLEAR 2ND ACCUMULATOR        S900542
         ZMB       HWINAGBN        ZERO THE BLOCK NUMBER OF AUGNED
         ZMB       VALT            CLEAR NON NUMERIC TERMINATOR
         ZMW       SECNUMAG        ZERO SECT NUM OF AUGEND
         ZBM       ALVAL,HHBITS2   SHOULD WE EVAL FIRST OPERAND?
         BS        VALA         NO.
         TBR       2,31            IS ELEMENT UNSTRUNG
         BS        VAL2         YES, SKIP CALL TO UNSTRINGER
         LW        6,HWKSPA        SPACES
         STW       6,HBSTAC        CLEAR TERMINATOR LIST
VAL1     LW        1,=X'81FD0000'  LONG LIST OF TERMINATORS
         BL        UNST            UNSTRING NAME AFTER IGNORING LEADING
         BU        VAL3            CONTINUE
VAL2     LB        7,HBSTAC        LATEST TERMINATOR
VAL3     ZMW       HWINAG          CLEAR AUGEND STORAGE
         CI        7,G'"''         IS THE LATEST TERMINATOR A '
         BEQ       VALQ         YES
         CI        7,G'('          NOT ', IS IT (
         BEQ       VALQ         YES
         LW        6,HWNAME        GET FIRST 4 CHAR OF UNSTRUNG NAME
         CAMW      6,=C'"$   '     CHECK FOR LOCATION COUNTER REFERENCE
         BEQ       VALP         YES, LOCATION COUNTER REFERENCE
         CAMW      6,=C'    '      IS IT ALL SPACES
         BEQ       VALA         YES, SAME AS $$ OR 0
         CAMW      6,=C'"$"$  '    IS IT THE SPECIAL ZERO NAME
         BEQ       VALA         YES
         CAMW      6,=C'"$"$"$ '   CHK FOR SPECIAL NAME IN A REPT LOOP
         BEQ       VALK         GET THE ITERATION COUNT
         LB        4,HWNAME        FIRST CHAR
         LW        5,HWKSPA        SPACES
         SRLD      4,8             R5 CONTAINS FIRST CHAR AND SPACES
         CAMW      5,=C'0   '      CHECK FOR LESS THAN NUMERIC RANGE
         BLT       $+3W         NOT IN NUMERIC RANGE
         CAMW      5,=C'9   '      CHECK FOR GREATER THAN NUMERIC RANGE
         BCF       GT,VALN         IN NUMERIC RANGE
         ZR        7               WIPE OUT THE LATEST THING IN R7
         BL        YEANAY          CHECK WHETHER ASSEMBLY IS ALLOWED
         BNS    VALA            DONT ASSEMBLE
         LW        4,=X'80FFFFFF'  MASK TO REMOVE TYPE
         LMW       1,HWLSTS        ADDRESS FOR THE LABEL ON THIS CODE
         ORMW      1,TALLS1        UNDEFINED TYPE CODE
         LD        4,HWNAME        LABEL TO SEARCH FOR IN SYMBOL TABLE
         BL        SS              SEARCH SYM TBL TO FIND NUMERIC EQUIV
         IFT       UNIXF,SKIP                                   *JCB*
         SRL       R2,24           GET PC MODE FOR SYMBOL       *JCB*
         STB       R2,HWPCMODE     SAVE IT FOR TDATA            *JCB*
SKIP     ANOP                                                   *JCB*
         STW       3,HWINAG        SAVE NUMERIC EQUIVALENT
VALA     LI        1,-2W           LOOP COUNT AND POINTER
         LW        4,=X'00FFFFFF'  MASK TO CLEAR TYPE
VALA1    LW        3,HWINAG+2W,1   GET VALUE AND 9 BIT TYPE CODE
         STMW      3,HWINAGV+2W,1  STORE VALUE
         ZR        2
         SLLD      2,9             MOVE 9 BIT TYPE CODE TO R2
         ZMW       SECNUMAG+2W,1   CLEAR SECTION NUMBER
         ZBR       2,23            IS IT A CSECT REF?
         BNS       $+2W            NO - OK
         SBM       31,SECNUMAG+2W,1     INDICATE CSECT SECTION NUMBER
         CI        R2,3            IS IT UNDEFINED
         BNE       $+2W            BR IF NOT
         SBM       0,VALUNDF       SET FLAG SHOWING VAL IS UNDEFINED
         LB        2,VDT,2         CONVERT TYPE CODE TO 2 BIT TYPE CODE
         STB       2,HWINAGT+2W,1  STORE 2 BIT TYPE CODE
         CI        R2,TYPC2        IS THIS COMMON                   AS23
         BEQ       VALA1.1         BRANCH IF COMMON                 AS23
         ZBM       8,HWINAGV+2W,1  CLEAR ABS/REL FLAG (NON COMMON CASE)
VALA1.1  BIW       1,VALA1         DO AUGEND AND ACCUMULAND
         LB        2,HWINAGT       CHECK 2 BIT TYPE CODE
         CI        2,TYPC2         IS IT COMMON
         BNE       VALAB        NO
* PROCESSING FOR COMMON ONLY
         LH        2,HWINAGV
         STB       2,HWINAGBN
         LH        2,HWINAG+1H     GET THE DISPLACEMENT
         ANMW      2,=X'FFFF'      MASK OFF EXTRANEOUS BITS
         STW       2,HWINAGV       STORE VALUE
* CHECK PREVIOUS TERMINATOR AGAINST ACTION LIST
VALAB    CEQU      $                                            ESCT-32
         LNB       3,VALS          NUMBER OF TERMINATORS IN LIST
         LB        6,HBSTAC+1B     PREVIOUS TERMINATOR
         CAMB      6,VALS+10B,3    CHECK PREV TERM AGAINST ACTION LIST
         BEQ       VD1          HIT
         BIB       3,$-2W          CHECK ALL TYPES
         BL        YEANAY          ARE WE ASSEMBLING?
         BNS       $+3W         NO.
         SBM       G'E'-X'40',HWERRF  MARK E ERROR
         ABM       31,HWERCT       COUNT THIS ERROR
         BU        VALE            FINSIH THIS ELEMENT
VD1      LB        2,VDDC+9B,3     GET POINTER FOR OPERATION TO BE DOND
         SLL       2,2             MAKE ROOM FOR OTHER DESCRIPTORS
         STB       2,VDAP          POINTER TO OPERATION TO BE DONE
         ORMB      2,HWINAGT       2 BIT EQUIV OF AUGEND TYPE CODE
         SLL       2,2             MAKE ROOM FOR OTHER DESCRIPTOR
         ORMB      2,HWINACT       2 BIT EQUIV OF ACCUMULAND TYPE CODE
         LB        1,VDC,2         GET DECISION FOR DESCRIPTOR
         BU        *VDA,1          GO TO CORRECT HANDLER
VDA      ACW       VDE             ACTION 0
         ACW       VDE             ACTION 1
         ACW       VDAG            ACTION 2
         ACW       VDAC            ACTION 3
         ACW       VDAA            ACTION 4
         ACW       VDCC            ACTION 5
         ACW       VDCX            ACTION 6
         ACW       VDE             ACTION 7
         ACW       VDRR            ACTION 8
VDRR     LW        6,SECNUMAG      SECTION NUMBER
         EOMW      6,SECNUMAC      DO SECTION NUMBERS MATCH?
         BEQ       VDAA         YES, - MAKE ABSOLUTE
         BU        VDE             GO MARK ERROR
VDCC     LB        6,HWINACBN      COMMON BLOCK NUMBER
         EOMB      6,HWINAGBN      DO BLOCK NUMBERS MATCH
         BEQ       VDAA         SAME, SHOULD NOW BE PROG ABSOLUTE
VDE      CEQU      $                                            ESCT-32
         BL        YEANAY          ARE WE ASSEMBLING?
         BNS       VALE         NO.
         SBM       G'V'-X'40',HWERRF   MARK 'V' ERROR.
         ABM       31,HWERCT       COUNT THE ERROR
         BU        VALE
* EXTERNAL IN EXPRESSION
VDCX     LB        6,HBLABS        GET PROGRAM COUNTER MODE
         CI        6,8             IS IT IN COMMON MODE?
         BNE       VDCX2        NO, GO PROCESS EXTERNAL.
         BL        YEANAY          ARE WE ASSEMBLING?
         BNS       VALE         NO.
         SBM       G'A'-X'40',HWERRF   MARK A ERROR.
         ABM       31,HWERCT           COUNT THE ERROR.
         BU        VALE
VDCX2    LW        6,HWINAC        CHECK PREVIOUS ACCUMULAND FOR BEING 0
         BNE       VDE          NO, EXTERNAL IN EXPRESSION ISILLEGAL
         LW        7,HWINAG        THE EXTERNAL AUGEND
         STW       7,HWINAC        IS EXACTLY THE ACCUMULAND NOW
         LW        5,SECNUMAG      LOOKS LIKE THIS
         STW       5,SECNUMAC      SHOULD BE DONE
         BU        VALE
VDAA     ZMW       HWINAGT         PROGRAM ABSOLUTE TYPE CODE
         ZMW       SECNUMAG        ZERO SECTION NUMBER
         BU        VDAG
VDAC     LW        6,HWINACT       TYPE CODE OF ORIGINAL ACCUMULAND
*                                  AND BLOCK NUMBER IF COMMON
         STW       6,HWINAGT       FINAL TYPE CODE TO OUTSIDE WORLD
         LW        6,SECNUMAC      LOOKS LIKE THIS
         STW       6,SECNUMAG      SHOULD BE DONE
VDAG     LB        3,VDAP          POINTER TO CORRECT PROCESSOR FOR EXP
         BU        *VDDA,3         GO DO +,-,*,/
VDDA     ACW       VALC            + OPERATION
         ACW       VALB            - OPERATION
         ACW       VALM            * OPERATION
         ACW       VALD            / OPERATION
* DIVIDE OPERATION
VALD     ZR        6               SET UP FOR DIVIDE
         BL        YEANAY          IS ASSEMBLY GOING ON?
         BNS       VALH         NO, SKIP BOTH ERROR CHECK AND DIVIDE.
         LW        7,HWINAGV       GET DIVISOR
         BNE       VALD1        DIVISOR NOT EQUAL TO ZERO.
         SBM       G'\'-X'40',HWERRF  MARK \ ERROR.
         ABM       31,HWERCT       COUNT THE ERROR.
         ZR        7               ZERO OUT QUOTIENT.
         BU        VALH
VALD1    CEQU      $                                            ESCT-32
         TBM       7,BACFLAG       PROCESSING A RES OR REZ ?    S900542B
         BNS       $+5W            NO...BRANCH                  S900542B
         LW        R7,ACCUM        LOAD PREVIOUS VALUE          S900542
         DVMW      R6,HWINAGV      DIVIDE BY CURRENT VALUE      S900542
         STW       R7,ACCUM        SAVE NEW TOTAL               S900542
         ZR        R6                                           S900542
         LW        7,HWINACV       PREVIOUS ACCUMULATED VALUE
         DVMW      6,HWINAGV       DIVIDE BY LATEST NUMERIC VALUE ELEMNT
         BU        VALH            FINISH UP THIS ELEMENT
* MULTIPLY OPERATION
VALM     TBM       7,BACFLAG       PROCESSING A RES OR REZ ?    S900542B
         BNS       $+5W            NO...BRANCH                  S900542B
         LW        R7,ACCUM        LOAD PREVIOUS VALUE          S900542
         MPMW      R6,HWINAGV      MULTIPLY BY CURRENT VALUE    S900542
         STW       R7,ACCUM        SAVE NEW TOTAL               S900542
         ZR        R6                                           S900542
         LW        7,HWINACV       PREVIOUS ACCUMULATED VALUE
         MPMW      6,HWINAGV       MULTIPLY BY LATEST VALUE ELEMNT
         BU        VALH
* ADD OPERATION
VALC     LW        7,HWINAGV       THE VALUE PART TO ADD TO ACCUMULAND
         LB        1,HWINAGT       IS AUGEND COMMON
         CI        1,TYPREL        IS AUGEND RELOCATABLE?
         BNE       VALC1           NO
         LW        1,SECNUMAG      AUGEND SEC NUM
         STW       1,SECNUMAC      GOES TO ACCUM.SEC.NUM.
         BU        VALB+1W
VALC1    CEQU      $                                            ESCT-32
         CI        1,TYPC2         IN TWO BIT TYPE CODE
         BNE       VALB+1W      NOT COMMON
         LB        1,HWINAGBN      THE AUGEND BLOCK NUMBER
         STB       1,HWINACBN      NOW GOES TO THE ACCUMULAND
         BU        VALB+1W         GO DO ADD NOW
* SUBTRACT OPERATION
VALB     LNW       7,HWINAGV       NEG VALUE OF AUGEND,ADDED GETS SUBTRA
         TBM       7,BACFLAG       PROCESSING A RES OR REZ ?    S900542B
         BNS       $+2W            NO...BRANCH                  S900542B
         ARMW      R7,ACCUM        ADD CURRENT VALUE TO TOTAL   S900542
         ADMW      7,HWINACV       PREVIOUS ACCUMULATED VALUE
VALH     SLL       7,9             POSITION VALUE FOR CONCATENATION
         LB        1,HWINAGT
         LB        6,VDTO,1        CONVERT TO PROPER 8 BIT TYPE CODE
         SRLD      6,9             CONCATENATE VALUE AND TYPE CODE
         STW       7,HWINAC        THE NEW ACCUMULAND
         TBM       31,SECNUMAG     CSECT EXPRESSION?
         BNS       VALE            NO
         SBM       0,HWINAC        INDICATE CSECT EXPRESSION
VALE     LB        5,HBSTAC        GET LAST TERMINATOR
         CI        5,G' '          CHECK FOR A SPACE TERMINATOR
         BEQ       VALF         SPACE TERM FOUND
         CI        5,G','          CHECK FOR COMMA
         BEQ       VALF         COMMA TERMIANTOR FOUND
         CI        5,G'"''         IS THE LATEST TERMINATOR A '
         BEQ       VALF         ' TERMINATOR FOUND
         CI        5,G')'          CHECK FOR )
         BEQ       VALI         ) FOUND
         BU        VAL1
VALF     TBM       7,BACFLAG       PROCESSING A RES OR REZ ?    S900542B
         BNS       $+4W            NO...BRANCH                  S900542B
         ZBM       7,BACFLAG       CLEAR RES/REZ FLAG           S900542B
         LW        R7,ACCUM        LOAD FULL WORD ACCUMULATOR   S900542
         BLT       VALF.B          BRANCH IF NEGATIVE           S900542
         LB        5,VALT          NUMERIC EQUIV OF NON-NUMERIC TERMINAT
         LW        7,HWINAC        VALUE OF EXPRESSION AND TYPE
         BU        *VALS0          RETURN
VALF.B   BL        YEANAY          ARE WE ASSEMBLING?           S900542
         BNS       $+3W            NO...BRANCH                  S900542
         SBM       G'N'-X'40',HWERRF    MARK N TYPE ERROR       S900542
         ABM       31,HWERCT       AND COUNT IT                 S900542
         ZMW       HWINAG          CLEAR EXPRESSION VALUE       S900542
         BU        NEXT            PROCESS NEXT SOURCE LINE     S900542
* COME HERE TO SET UP LOCATION COUNTER REFERENCE
VALP     CEQU      $                                            ESCT-32
         ZBM       ASCT.NOD,ASCT.FLG   RESET NO '$' FLAG        EASC-32
         BNS       VALP.1              CONTINUE IF NOT SET      EASC-32
         SBM       G'O'-X'40',HWERRF   ELSE, SET 'O' ERROR      EASC-32
         ABM       31,HWERCT           AND COUNT IT             EASC-32
         ZMW       HWINAG              SET VALUE TO 0           EASC-32
         BU        NEXT                AND BAIL OUT OF INST.    EASC-32
VALP.1   CEQU      $                   ELSE CONTINUE NORMAL     ESCT-32
         LW        5,HWLSTS        INSTRUCTION COUNTER
         STW       5,HWINAG        USE FOR ARGUMENT ARITHMETIC
         BU        VALA            GO USE IT
* NUMERIC RANGE
VALN     LI        2,10            SET UP FOR CNUM TO CONV TO DECIMAL
         BL        CNUM            CONV NUMERIC STRING IN HWNAME
*                                  TO NUMERIC COUNT IN R6+7
         LW        4,=X'007FFFFF'  MASK TO CLEAR TYPE
         TRRM      7,6             R6=VALUE
         STW       6,HWINAG        PUT IT IN AUGEND
         STB       5,VALT          NUMERIC EQU OF NON NUMERIC TRMINATOR
         BU        VALA
* RIGHT PARENTHESIS FOUND
VALI     LW        2,HWINAC        THE ACCUMULAND
*        BL        AGEQ            ADD THE PROPER F AND CC BITS
         BL        AGEQ0           ADD THE PROPER F AND CC BITS
         LW        4,=X'007FFFFF'  MASK TO CLEAR TYPE
         TRRM      7,7             CLEAR TYPE
         TRC       4,4             MASK TO CLEAR ADDRESS
         LMW       6,HWINAC        GET OLD TYPE
         ORR       6,7             USE OLD TYPE AND NEW ADDRESS
         STW       7,HWINAC        IN ACCUMULAND
         LI        7,5
         STB       7,HBAVAR
         LW        1,=X'81FD0000'   TERMINATE ON ALMOST ANYTHING
         BL        RUNST           STOP ON THE FIRST SPACE FOUND
         LW        5,HWNAME        CHECK INPUT NAME FIELD
         CAMW      5,HWKSPA        IS IT ALL SPACES?
         BNE       VALI4        MARK ERROR
         LB        5,HBSTAC        GET THE TERMINATOR
         CI        5,G' '          IS IT A SPACE?
         BEQ       VALF         YES-THEN IT S OKAY
         CI        5,G','          IS IT A COMMA
         BEQ       VALF         YES-THEN IT S OKAY
VALI4    BL        YEANAY          ARE WE ASSEMBLING?
         BNS       VALF         NO.
         SBM       G'V'-X'40',HWERRF   MARK V ERROR.
         ABM       31,HWERCT       COUNT THIS ERROR
         BU        VALF            GO OUT
VALQ     LB        6,HWNAME+1B     SECOND BYTE OF HWNAME
         CI        6,G' '          IS IT A SPACE?
         BNE       VALU         NO, ILLEGAL CONSTANT TYPE
         LI        1,-13           13 POSSIBLE FIELD DESCRIPTORS
         LB        6,HWNAME        CHARACTER BEFORE ' OR (
         IFT       ULC,SKIP                                     *JCB*
         ZBR       R6,26           CONVERT TO UPPER CASE        *JCB*
SKIP     ANOP                                                   *JCB*
         CAMB      6,TCTE+1,1      SEARCH FOR IT IN VALID LIST
         BEQ       VALQ1        A HIT
         BIB       1,$-2W          INCR TO NEXT ITEM AND CONTINUE
*                                  OR FALL THRU TO MARK ERROR
VALU     BL        YEANAY          ARE WE ASSEMBLING?
         BNS       VALE         NO.
         SBM       G'W'-X'40',HWERRF   MARK W ERROR.
         ABM       31,HWERCT       COUNT THE ERROR
         BU        VALE            RETURN TO CYCLE
VALQ1    ADI       1,7
         BGE       VALG         R1=0-6 FOR C,G,X,N,F,E,R RESP
* COME HERE FOR ADDRESS ATTRIBUTE
         CI        7,G'('          WAS TERMIANTOR A (
         BNE       VALU         NO, ERROR CNA'T BE ADDRESS ATTRIBUTE
         ADI       1,5             R1=-1 IF BLANK DESC, 0-4 FOR B,H,W,D,
         BLT       VALU         ERROR DESCRIPTOR WAS A BLANK
         STB       1,HBAVAR        ADR VARIANT FOR EXPRESSION DETERMINAT
         BU        VAL1            GO DO ADDRESS ATTRIBUTE
* COME HERE TO PROCESS CONSTANT IN THE EXPRESSION
VALG     CI        7,G'"''         IS THE LATEST TERMINATOR A '
         BNE       VALU         NO, MARK AS ERROR
         LB        6,HBSTAC+1B     PREVIOUS TERMINATOR
         STB       6,VALS1         SAVE IT
         LH        6,HHODP         THE INITIAL OUTPUT POINTING STATUS
         STH       6,HHODPA        SAVED STATE TO PREVENT WIPEOUT
         LI        6,3W
         STB       6,HBTTTF        POINT DATA TO VALUE STACK
         LI        6,4             NUMBER OF BYTES TO GO OUT
         STB       6,TOT           FOR BOUNDING REQUIREMENTS
* R1=0-6 FOR C,G,X,N,F,E,R RESP
         BL        TMD             TRANSLATE THE CONSTANT
         LH        6,HHODPA        SAVED STATE TO PREVENT WIPEOUT
         STH       6,HHODP         THE INITIAL OUTPUT POINTING STATUS
         LW        4,=X'007FFFFF'  LEAVE ONLY THE ADDRESS VALUE PART
         LMW       6,HDTDS+1W      DATA COMPUTED BY TMD
         STW       6,HWINAG        THE VALUE FROM TMD
         LW        1,=X'81FD0000'  LONG LIST OF TERMINATORS
         BL        RUNST           UNSTRING-WITHOUT SKIPPING LEFT SPACES
         LB        6,VALS1         PREVIOUS TERMINATOR WE SAVED
         STB       6,HBSTAC+1B     RESTORE PREVIOUS TERMINATOR
         BU        VALA
VALK     CEQU      $                                            ESCT-32
         LH        5,HHRDCOLC      THE COUNT OF REPEAT ITERATIONS
         STW       5,HWINAG        THIS IS THE NEW AUGNEND
         BU        VALA            PROCESS THE VALUE FOR THE SPECIAL NAM
         TITLE     READ-ONLY       TDAT
* PROCESS DATA STRINGS
         SPACE     1
TDAT     CEQU      $                                            ESCT-32
         STW       0,TDATS0        SAVE RETURN ADDRESS
         ZMD       HDTDS           CLEAR INTEGER STACK
         ZMD       HDTDF           CLEAR FRACTION STACK
         ZBM       TGSIGN,HHBITS   ASSUME POSITIVE
         LW        1,=X'81FD0000'  MANY TERMINATORS
         BL        UNST            UNSTRING DESCRIPTOR OF CONSTANT
         CI        7,G'"''         IS THE LATEST TERMINATOR A '
         BEQ       TDAT1        YES
         CI        7,G'('          IS TERMINATOR A (
         BNE       TDAT3        NO, MAY BE IMPLICIT NUMERIC
* TERMINATOR IS ' OR (. EVALUATE CONSTANT TYPE IN VARIABLE NAME
TDAT1    LB        6,HWNAME+1B     SECOND BYTE OF HWNAME
         CI        6,G' '          IS IT A SPACE?
         BNE       TDATER       NO, ILLEGAL CONSTANT TYPE.
         LI        1,-12           NUMBER OF CONSTANT TYPES.
         LB        6,HWNAME
         IFT       ULC,SKIP                                     *JCB*
         ZBR       R6,26           CONVERT TO UPPER CASE        *JCB*
SKIP     ANOP                                                   *JCB*
         CAMB      6,TCTE+1,1      SEARCH CONSTANT TYPES
         BEQ       TDAT2        TYPE FOUND
         BIB       1,$-2W          SEARCH ENTIRE LIST
* ERROR - TYPE NOT FOUND
TDATER   BL        YEANAY          ARE WE ASSEMBLING?
         BNS       TDAT4A       NO.
         SBM       G'D'-X'40',HWERRF   MARK D ERROR.
         ABM       31,HWERCT       COUNT THE ERROR
         BU        TDAT4A
* TYPE FOUND
TDAT2    ADI       1,7             TYPE CGXNFER = 0-6 , ADWHB = -1 - -5
         BLT       TDAT2A       TRANSLATE AN ADDRESS CONSTANT STRING
         CI        7,G'"''         IS THE LATEST TERMINATOR A '
         BNE       TDATER       NO,GO MARK ERROR
         BL        TMD             CONSTANT SWITCHER AND DECODE CGXNFER
         LB        7,HBTTTF        GET DATA DESCRIPTOR
         CI        7,1W            PROCESSING A GEN OR DATA DIRECTIVE?
         BGT       TDAT4        NO.
         TBM       ALVAL,HHBITS2   DO WE HAVE AN ARITH. EXPRESSION?
         BNS       TDAT22       NO.
         BU        TDAT2B
TDAT22   LB        7,HBSTAC        GET CURRENT TERM.
         CI        7,G','          IS IT A COMMA?
         BEQ       TDAT4A1      YES-OK.
         CI        7,G' '          IS IT A SPACE?
         BEQ       TDAT4A1      YES-OK.
         BU        TDATER          MARK ERROR.
* TRANSLATE AN ADDRESS CONSTANT STRING
TDAT2A   ADI       1,5             TYPE RANGE 0-4 FOR B,H,W,D,A RESP
         STB       1,HBAVAR        FOR VAL
         CI        7,G'('          WAS TERMINATOR A COMMA
         BNE       TDATER       NO, MARK ERROR
         ZR        2               ELE NOT UNST, DON'T SKIP LEADING SP
TDAT2B   CEQU      $                                            ESCT-32
         ZBM       TGSIGN,HHBITS   CLEAR NEGATION FLAG
         IFT       UNIXF,SKIP                                   *JCB*
         ZMB       HWPCMODE        CLEAR PC MODE OF SYMBOL      *JCB*
SKIP     ANOP                                                   *JCB*
         BL        VAL             OBTAIN NUMERIC ADDRESS
         LB        6,HWINAC        TYPE CODE OF EXPRESSION
         ZBR       6,24            CLEAR DSECT/CSECT FLAG
         CI        6,TYPC          COMMON REF TYPE?
         BEQ       TDAT2B.1        YES
         CI        6,TYPD          COMMON DEF TYPE?
         BNE       TDAT2B.3        NO
TDAT2B.1 CEQU      $                                            ESCT-32
         LB        6,HWINACBN      THE BLOCK NUMBER OF COMMON, IF ANY
         STB       6,HBBN          FOR LATER OUTPUT HANDLER USE
         BU        TDAT2B.5
TDAT2B.3 LW        6,SECNUMAC      SECTION NUMBER, IF ANY
         STB       6,HBBN          STORE FOR OUTPUT HANDLER USE
TDAT2B.5 CEQU      $                                            ESCT-32
         IFF       UNIXF,SKIP                                   *JCB*
         ZR        6
SKIP     ANOP                                                   *JCB*
         ANMW      7,=X'007FFFFF'   LEAVE ONLY THE ADDRESS VALUE PART
         IFT       UNIXF,SKIP                                   *JCB*
         LB        R6,HWPCMODE     GET PC MODE OF STRINGBACK    *JCB*
         CI        R6,8            IS IT INTO COMMON            *JCB*
         BNE       $+2W            NO                           *JCB*
         ORMW      R7,=X'FF000000' ELSE, MARK AS COMMON FORMAT  *JCB*
         ZR        6                                            *JCB*
SKIP     ANOP                                                   *JCB*
         BU        TDAT3E          GO RELEASE THE DATA
*        MAY BE IMPLIED DECIMAL NUMERIC OR UNATTRIBUTED EXPRESSION
TDAT3    CEQU      $                                            ESCT-32
         LW        6,HWNAME        THE UNSTRUNG NAME
         CAMW      6,HWKSPA        IS IT ALL SPACES
         BNE       TDAT3C       NO-THEN WE HAVE SOMETHING NOW
         ZBM       DUMMY,SPMAC     WAS NAME A DUMMY ARGUMENT?
         BNS       TDAT3.1      NO.
         LI        2,1             THIS CAUSES VAL TO WORK ON UNSTRUNG
         LI        3,-4            NUMBER OF ARITH. OPERATORS.
         LB        7,VALS+10B,3    GET ONE OPERATOR.
         CAMB      7,HBSTAC        IS IT THE CURRENT TERMINATOR?
         BEQ       TDAT2B       YES.
         BIB       3,$-3W          CHECK ALL THE OPERATORS.
         BU        TDAT4           GO GET NEXT ELEMENT.
TDAT3.1  CEQU      $                                            ESCT-32
         LB        7,HBSTAC        FETCH CURRENT TERMINATOR
         CI        7,G' '          IS TERMINATOR A SPACE?
         BEQ       TDAT3C       YES, EVALUATE BLANK FIELD AS ZERO.
         CI        7,G','          IS TERMINATOR A COMMA?
         BEQ       TDAT3C       YES, EVALUATE BLANK FIELD AS ZERO.
         CI        7,G'+'          IS TERMINATOR A + ?
         BEQ       TDAT3B       YES, GO GET NEXT ELEMENT.
         CI        7,G'-'          IS TERMINATOR A - ?
         BNE       TDATER       NO, ILLEGAL TERMINATOR.
         SBM       TGSIGN,HHBITS   MAKE THE THING NEGATIVE
TDAT3B   LW        1,=X'81FD0000'
         BL        UNST            GET NEXT ELEMENT
TDAT3C   CEQU      $                                            ESCT-32
         LI        2,1             THIS CAUSES VAL TO WORK ON UNSTRUNG
         LB        7,HWNAME        CHECK FIRST CHAR OF UNSTRUNG
         CI        7,G'0'          IS IT BELOW NUMERIC RANGE
         BLT       TDAT2B       YES-THEN NOT NUMERIC
         CI        7,G'9'          IS IT ABOVE NUMERIC RANGE
         BGT       TDAT2B       YES-THEN NOT NUMERIC
* DECIMAL IMPLICIT TYPE NUMERIC STRING
         LI        3,-4            NUMBER OF ARITH. OPERATORS.
         LB        7,VALS+10B,3    GET ONE OPERATOR.
         CAMB      7,HBSTAC        IS IT THE CURRENT TERMINATOR?
         BEQ       TDAT2B       YES.
         BIB       3,$-3W          CHECK ALL THE OPERATORS.
         LI        2,10            RADIX 10 FOR DECIMAL CONVERSION
         BL        CNUM            CONV NO. STRING INTO R6,7
TDAT3E   CEQU      $                                            ESCT-32
         STD       6,HDTDS         STORE IT
         LND       6,HDTDS         THE NEGATED DATA-IF NEEDED
         TBM       TGSIGN,HHBITS   MAKE THE THING NEGATIVE?
         BNS       $+2W         NEGATION NOT NEEDED
         STD       6,HDTDS         STORE IT
         BL        TCY             ALLOW BYTES INTO DATA STREAM
* CHECK TERMINATOR
TDAT4    LB        7,HBSTAC        FETCH CURRENT TERMINATOR
         CI        7,G','          IS IT A ,
         BEQ       TDAT4B       YES, EXIT WE ARE READY FOR NEXT TERM
         CI        7,G' '          IS IT A SPACE
         BEQ       TDAT4B       YES, EXIT WE ARE FINISHED
TDAT4A   CEQU      $                                            ESCT-32
         LW        1,=X'80080000'  SP AND ,
         BL        RUNST           UNSTRING-WITHOUT SKIPPING LEFT SPACES
TDAT4A1  CEQU      $                                            ESCT-32
         LW        6,HWNAME        WAS THERE ANY DATA BET ' AND ,
         CAMW      6,=C'    '      MUST BE SPACES
         BNE       TDATER       MARK ERROR
TDAT4B   BU        *TDATS0                  RETURN
*
* (C) COPYRIGHT 1983 ENCORE COMPUTER CORPORATION
*     ALL RIGHTS RESERVED
*
         TITLE     READ-ONLY       TMD
* SWITCH TO DATA TRANSLATOR OTHER THAN A,B,D,W,H
* INPUT--R1=0-6 TO INDICATE C,G,X,N,F,E,R TYPE CONSTANT RESPECTIVELY
         SPACE     1
TMD      CEQU      $                                            ESCT-32
         STW       0,TMDS0         SAVE RETURN ADR
         CI        R1,5            WAS CONSTANT AN 'E' TYPE?    EIEE-33
         BNE       $+2W            BRANCH IF NOT                EIEE-33
         SBM       1,DBLORSGL      ELSE SET SINGLE PRECISION    EIEE-33
         ZMD       HDTDS           CLEAR INTEGER STACK
         ZMD       HDTDF           CLEAR FRACTION STACK
         SLL       1,2
         BU        *TCTS,1         SWITCH TO PROPER HANDLER
* C TYPE CONSTANT
TCD1     LW        1,=X'01000000'  TERM LIST FOR A CHARACTER STRING
         BL        GBYT            GO GET ONE ASCII CODED BYTE
         BCT       1,TCD2          APOSTROPHE OR ERROR FOUND
         LI        7,1             INDICATE LEFT JUSTIFIED ELEMENT
         BL        TDG             ALLOW OUT TO PROPER STREAM
         BU        TCD1            KEEP GETTING CHARACTERS
TCD2     BL        YEANAY          IS ASSEMBLY GOING ON?
         BNS       TGD30        NO, SKIP BOUNDARY CHECK.
TCD2.1   LB        7,TOT           1,2,4,8 FOR B,H,W,D BOUNDING REQD.
         BL        TBOU            TEST FOR CORRECT BOUNDARY
         TRR       4,4             SET CC BITS
         BEQ       TGD30        DONE IF CORRECT BOUNDARY
         LB        6,HBTTTF        CHECK WHERE THIS STATEMENT IS GOING
         BNE       TGD30        RETURN IF NOT DATA STATEMENT
         LI        6,G' '          SPACE CODE
         LI        7,1             INDICATE LEFT JUSTIFIED DATA
         BL        TDG             ALLOW OUT TO PROPER STREAM
         BU        TCD2.1          CONTINUE UNTIL PROPER BOUND REACHED
TGD30    CEQU      $                                            ESCT-32
         LB        7,HBIBYI        BYTE READING PTR
         STB       7,HBIBYIT       TEMP BYTE READING PTR
         LB        7,HBTTTF        DATA DESCRIPTOR
         CI        7,1W            PROCESSING GEN OR DATA DIRECTIVE?
         BGT       TGD3         NO.
         LW        1,=X'80080000'  TERM ON SPACE OR COMMA
         BL        RUNST           UNSTRING W/O SKIPPING LEADING SPACES
         BU        TGD3
* G TYPE CONSTANT
TGD1     LW        1,=X'01000000'  TERM LIST FOR A CHARACTER STRING
         BL        GBYT            GO GET ONE ASCII CODED BYTE
         BCT       1,TGD2          STRING TERMINATOR FOUND
         LD        4,HDTDS         GET BYTE STACK
         SLLD      4,8             MAKE ROOM FOR NEXT BYTE
         ORR       6,5             OR IN NEW BYTE
         STD       4,HDTDS         STORE UPDATED STACK
         BU        TGD1
TGD2     CEQU      $                                            ESCT-32
         LB        7,HBIBYI        BYTE READING PTR
         STB       7,HBIBYIT       TEMP HOLDS BYTE READING PTR
         LB        7,HBTTTF        GET DATA DESCRIPTOR.
         CI        7,1W            PROCESSING GEN OR DATA DIRECTIVE?
         BGT       TGD2.5       NO.
         LW        1,=X'81FD0000'  TERMINATE ON ALMOST ANYTHING.
         BL        RUNST           UNSTRING WITHOUT SKIPPING LEFT SPACES
         LI        1,-4            NUMBER OF ARITH. OPERATORS.
         LB        7,VALS+10B,1    GET ONE OPERATOR.
         CAMB      7,HBSTAC        IS IT THE CURRENT TERMINATOR?
         BEQ       TGD2.1       YES.
         BIB       1,$-3W          CHECK ALL THE OPERATORS.
         BU        TGD2.5          GO CYCLE DATA OUT.
TGD2.1   LW        4,=X'007FFFFF'  LEAVE ONLY ADDRESS VALUE PART.
         LMW       4,HDTDS+1W      DATA COMPUTED BY TMD
         STW       4,HWINAG        THE VALUE FROM TMD.
         LI        4,G' '          GET ONE SPACE.
         STB       4,HBSTAC+1B     STORE AS PREV. TERM. FOR VAL.
         SBM       ALVAL,HHBITS2   INDICATE TO VAL TO SKIP EVALUATION.
         BU        TGD2.6          SKIP CODE GENERATION.
TGD2.5   BL        TCY             CYCLE DATA OUT.
TGD2.6   CEQU      $                                            ESCT-32
TGD3     LB        7,HBIBYIT       TEMP BYTE READING PTR
         CI        7,73
         BLT       *TMDS0       WITHIN GOOD PART OF LINE
         BL        YEANAY          ARE WE ASSEMBLING?
         BNS       *TMDS0       NO.
         SBM       G'C'-X'40',HWERRF  SET NO TERMINATION ERROR FLAG
         ABM       31,HWERCT
         BU        *TMDS0
* HEXIDECIMAL TYPE X
TXD1     LW        1,=X'01000000'  TERMINATOR LIST FOR A HEX STRING
         BL        UNST            GO UNSTRING HEX NUMBER
         ZBM       DUMMY,SPMAC     IS THIS A DUMMY PARAMETER?
         BNS       TXD1.1.5     NO.
TXDA     CEQU      $                                            ESCT-32
         ZR        6               ZERO REG 6
         ZR        7               ZERO REG. 7
         BU        TXD1.7+2W
TXD1.1.5 CEQU      $                                            ESCT-32
         TBM       CONDSCAN,MACSTATE  IN CONDITIONAL SCAN?
         BS        TXDA         YES, SKIP ERROR CHECKS.
         CI        7,X'27'         WAS TERMINATOR A '?
         BEQ       TXD1.2       YES, GO PROCESS NUMBER.
         BU        TXD1.7          NOT A ' TERMINATOR, ERROR.
TXD1.2   CI        3,16            HOW MANY CHARACTERS WERE THERE?
         BGT       TXD1.6       MORE THAN 17, ERROR.
         BLT       TXD1.3       LESS THAN 17, OKAY.
         LB        1,HWNAME        GET FIRST CHARACTER OF 17
*                                  CHARACTER HEX NUMBER.
         CI        1,G'+'        IS IT A PLUS SIGN?
         BEQ       TXD1.3       YES, GO PROCESS NUMBER.
         CI        1,G'-'          IS IT A MINUS SIGN?
         BNE       TXD1.6       NO, ERROR.
TXD1.3   LNW       6,UNSTNP        NUMBER OF CHARACTERS IN HEX STRING
         ZR        3               ZERO CHARACTER COUNT
TXD1.5   ABR       3,31            INCREMENT CHARACTER COUNT
         LB        7,HWNAME-1B,3   PICK UP NEXT CHARACTER
         CI        7,G' '          IS IT A SPACE?
         BEQ       TXD1.6       YES, ERROR.
         CI        7,G'H'          IS IT AN 'H'?
         BEQ       TXD1.6       YES, ERROR
         CI        7,G'W'          IS IT AN 'W'?
         BEQ       TXD1.6       YES, ERROR.
         BIB       6,TXD1.5        CHECK ALL THE CHARACTERS
         BU        TXD1.7          GO COMPUTE THE HEX NUMBER
TXD1.6   BL        YEANAY          ARE WE ASSEMBLING?
         BNS       TGD2         NO.
         SBM       G'N'-X'40',HWERRF   MARK N ERROR.
         ABM       31,HWERCT
         BU        TGD2            CYCLE DATA OUT.
TXD1.7   LI        2,16            HEXADECIMAL RADIX.
         BL        CNUM            CONV TO NUMERIC STRING IN R6,7
         STD       6,HDTDS         STORE IT
         BU        TGD2
TNFER    LB        6,TCTS,1        BIT SCALING REQUIRED
* N TYPE CONSTANT
* F TYPE CONSTANT
* E TYPE CONSTANT
* R TYPE CONSTANT
         STH       6,HHTDB         DEFAULT FOR B NOT SPECIFIED
         STH       6,HHTDBN        INDICATE WHERE FINISHED DATA SCALED
         BL        TFN             TRANSLATE NUMERIC FIELD STNG TO BYTES
         BU        TGD2
         SPACE     3
************************************************************************
*                                                                      *
*        ATOF - ROUTINE TO CONVERT ASCII STRINGS TO IEEE-754 FORMATTED *
*               FLOATING POINT NUMBERS.                                *
*                                                                      *
************************************************************************
ATOF     CEQU      $                                            EIEE-33
         STF       R0,FILE1        SAVE REGISTERS               EIEE-33
         RDSTS     R2              READ CPU STATUS WORD         EIEE-33B
         LI        R5,X'F'         LOAD MASK                    EIEE-33B
         ANR       R5,R2           ISOLATE MACHINE TYPE         EIEE-33B
         BNZ       NORSX           BRANCH IF NOT A 32/2000      EIEE-33B
         ZR        R3                                           EIEE-33B
         SBR       R3,0            SET BIT TO READ CPU INFO     EIEE-33B
         RPSWT     R3              READ CPU INFO                EIEE-33B
         TBR       R3,0            IS THIS AN RSX MACHINE       EIEE-33B
         BS        ATOF.0          YES...BRANCH                 EIEE-33B
         IFF       UNIXF,SKIP                                   *JCB*
NORSX    LB        R1,MSG5.L       ELSE OUTPUT ERROR MESSAGE    EIEE-33B
         STW       R1,FCBLO+9W                                  EIEE-33B
         LA        R1,MSG5.A                                    EIEE-33B
         STW       R1,FCBLO+8W                                  EIEE-33B
         LA        R1,FCBLO                                     EIEE-33B
         SVC       1,X'32'                                      EIEE-33B
         LW        R5,AS31                                      EIEE-33B
         SVC       1,X'57'         ABORT ASSEMBLE               EIEE-33B
SKIP     ANOP                                                   *JCB*
         IFT       UNIXF,SKIP                                   *JCB*
NORSX    LB        R1,MSG5.L       GET MESSAGE LENGTH           *JCB*
         LA        R2,MSG5.A       GET MESSAGE ADDRESS          *JCB*
         BL        PSTDERR         PRINT MESSAGE ON STD ERROR   *JCB*
         BU        ABRTM1-1W       GO ABORT WITH AS31           *JCB*
SKIP     ANOP                                                   *JCB*
ATOF.0   GFPC      R2,R4           GET FLOATING POINT CONTEXT   EIEE-33
         SBR       R2,28           SET IEEE MODE                EIEE-33
         SBR       R2,29                                        EIEE-33
         SBR       R2,24                                        EIEE-34C
         SBR       R2,26                                        EIEE-34C
         ZBR       R2,30           CLEAR OUT EXCESS 64 MODE     EIEE-33
         ZBR       R2,31                                        EIEE-33
         ZBR       R2,27                                        EIEE-33
         RFPW      R2,R4           RESTORE FLOATING PT. CONTEXT EIEE-33
         LD        R6,POWERS       HAS POWERS ARRAY BEEN INITED?EIEE-33
         BNE       ATOF.2          YES...BRANCH                 EIEE-33
         LD        R6,ONEQTR       GET 1.25                     EIEE-33
         STD       R6,POWERS       SAVE IN ARRAY                EIEE-33
         LA        R3,POWERS       GET ADDRESS OF ARRAY         EIEE-33
ATOF.1   LA        R5,POWERS                                    EIEE-33
         ADI       R5,X'40'        BUMP ADDRESS BY 9 DW         EIEE-33
         CAR       R3,R5           AT END OF ARRAY?             EIEE-33
         BLE       ATOF.2          YES...BRANCH                 EIEE-33
         LD        R6,0,X3         GET CURRENT ENTRY            EIEE-33
         MPFD      R6,0,X3         MULTIPLY BY ITSELF           EIEE-33
         STD       R6,2W,X3        SAVE IN NEXT ENTRY           EIEE-33
         ABR       R3,28           GOTO NEXT DOUBLE WORD        EIEE-33
         BU        ATOF.1          CONTINUE                     EIEE-33
ATOF.2   ZMW       EXP             CLEAR EXPONENT               EIEE-33
         ZMB       NEGVAL          CLEAR NEGATIVE VALUE FLAG    EIEE-33
ATOF.3   BL        GBYTE           GET BYTE FROM STRING         EIEE-33
         CI        R7,G' '         IGNORE BLANKS                EIEE-33
         BNE       ATOF.4                                       EIEE-33
         BU        ATOF.3                                       EIEE-33
ATOF.4   CI        R7,G'-'         IS CHAR. A MINUS SIGN?       EIEE-33
         BNE       $+3W            CONTINUE IF NOT              EIEE-33
         SBM       0,NEGVAL        SHOW VALUE IS NEGATIVE       EIEE-33
         BU        $+3W            CONTINUE                     EIEE-33
         CI        R7,G'+'         IS CHAR. A PLUS SIGN?        EIEE-33
         BNE       $+2W            CONTINUE IF NOT              EIEE-33
         BL        GBYTE           GET NEXT BYTE FROM STRING    EIEE-33
         ZMW       BIG             CLEAR ACCUMULATOR            EIEE-33
         ZMW       LITTLE                 ''                    EIEE-33
         ZMW       SCALE           CLEAR SCALE                  EIEE-33
         ZMD       FLVAL                                        EIEE-33
         ZMD       FLEXP                                        EIEE-33
         ABM       31,SCALE        SCALE=1                      EIEE-33
         ZMB       DECPT           CLEAR DECIMAL POINT FLAG     EIEE-33
         ZMW       NZEROES         NO ZEROES TO SKIP            EIEE-33
ATOF.5   CI        R7,G'0'         CHECK FOR DIGIT              EIEE-33
         BLT       ATOF.6          NO...BRANCH                  EIEE-33
         CI        R7,G'9'         HIGH SIDE CHECK              EIEE-33
         BGT       ATOF.6          NO...BRANCH                  EIEE-33
         TBM       0,DECPT         DECIMAL POINT SEEN YET       EIEE-33
         BNS       ATOF.12         NO...BRANCH                  EIEE-33
         CI        R7,G'0'         IS CHAR. EQUAL TO ZERO?      EIEE-33
         BNE       ATOF.7          NO...BRANCH                  EIEE-33
         ABM       31,NZEROES      INCREMENT ZERO COUNT         EIEE-33
         BL        GBYTE           GET NEXT BYTE FROM STRING    EIEE-33
         BU        ATOF.5          PROCESS NEXT CHARACTER       EIEE-33
ATOF.6   CI        R7,G'.'         IS THIS A DECIMAL POINT?     EIEE-33
         BNE       ATOF.15         NO...CONTINUE                EIEE-33
         SBM       0,DECPT         SHOW DECIMAL POINT READ      EIEE-33
         BL        GBYTE           GET NEXT BYTE FROM STRING    EIEE-33
         BU        ATOF.5          PROCESS NEXT CHARACTER       EIEE-33
ATOF.7   LW        R3,NZEROES      ANY ZEROES TO SKIP?          EIEE-33
         BLE       ATOF.11         NO...BRANCH                  EIEE-33
         LI        R4,-1           SUBTRACT ONE FROM EXP        EIEE-33
         ARMW      R4,EXP                                       EIEE-33
         LW        R5,BIG          GET CURRENT VALUE            EIEE-33
         CAMW      R5,=X'CCCCCCC'  LESS THAN THE MAX?           EIEE-33
         BGE       ATOF.8          NO...CHECK SCALE             EIEE-33
         MPI       R4,X'A'         MULTIPLY CURRENT VALUE BY 10 EIEE-33
         STW       R5,BIG          AND SAVE                     EIEE-33
         BU        ATOF.10                                      EIEE-33
ATOF.8   LW        R5,SCALE        GET CURRENT SCALE VALUE      EIEE-33
         CAMW      R5,=X'CCCCCCC'  LESS THAN THE MAX?           EIEE-33
         BGE       ATOF.9          NO...BRANCH                  EIEE-33
         MPI       R4,X'A'         MULTIPLY SCALE BY 10         EIEE-33
         STW       R5,SCALE        AND SAVE                     EIEE-33
         LW        R5,LITTLE       GET CURRENT LOW VALUE        EIEE-33
         MPI       R4,X'A'         MULTIPLY BY 10               EIEE-33
         STW       R5,LITTLE       AND SAVE                     EIEE-33
         BU        ATOF.10                                      EIEE-33
ATOF.9   ABM       31,EXP          INCREMENT EXPONENT           EIEE-33
ATOF.10  LI        R3,-1           SUBTRACT ONE FROM NZEROES    EIEE-33
         ARMW      R3,NZEROES                                   EIEE-33
         BU        ATOF.7                                       EIEE-33
ATOF.11  LI        R3,-1           SUBTRACT ONE FROM EXP        EIEE-33
         ARMW      R3,EXP                                       EIEE-33
ATOF.12  LW        R5,BIG          GET CURRENT VALUE            EIEE-33
         CAMW      R5,=X'CCCCCCC'  LESS THAN THE MAX?           EIEE-33
         BGE       ATOF.13         NO...BRANCH                  EIEE-33
         MPI       R4,X'A'         MULTIPLY CURRENT VALUE BY 10 EIEE-33
         SUI       R7,X'30'        SUBTRACT OUT ASCII 0         EIEE-33
         ADR       R7,R5           ADD TO CURRENT VALUE         EIEE-33
         STW       R5,BIG          AND SAVE                     EIEE-33
         BL        GBYTE           GET NEXT BYTE FROM STRING    EIEE-33
         BU        ATOF.5          PROCESS NEXT CHARACTER       EIEE-33
ATOF.13  LW        R5,SCALE        GET CURRENT SCALE VALUE      EIEE-33
         CAMW      R5,=X'CCCCCCC'  LESS THAN THE MAX?           EIEE-33
         BGE       ATOF.14         NO...BRANCH                  EIEE-33
         MPI       R4,X'A'         MULTIPLY CURRENT VALUE BY 10 EIEE-33
         STW       R5,SCALE        AND SAVE                     EIEE-33
         LW        R5,LITTLE       GET CURRENT LOW VALUE        EIEE-33
         MPI       R4,X'A'         MULTIPLY BY 10               EIEE-33
         SUI       R7,X'30'        SUBTRACT OUT ASCII 0         EIEE-33
         ADR       R7,R5           ADD TO VALUE                 EIEE-33
         STW       R5,LITTLE       AND SAVE                     EIEE-33
         BL        GBYTE           GET NEXT BYTE FROM STRING    EIEE-33
         BU        ATOF.5          PROCESS NEXT CHARACTER       EIEE-33
ATOF.14  ABM       31,EXP          INCREMENT EXPONENT           EIEE-33
         BL        GBYTE           GET NEXT BYTE FROM STRING    EIEE-33
         BU        ATOF.5          PROCESS NEXT CHARACTER       EIEE-33
ATOF.15  LW        R5,BIG          GET CURRENT VALUE            EIEE-33
         IFF       UNIXF,SKIP                          *MYATOF* *JCB*
         BNE       $+3W            CONTINUE IF NOT ZERO         EIEE-33
SKIP     ANOP                                                   *JCB*
         IFT       UNIXF,SKIP                          *MYATOF* *JCB*
         CI        R7,G'E'         IS CHARACTER AN E            *JCB*
         BEQ       ATOF.J01        Yes, process                 *JCB*
         CI        R7,G'e'         Is char an e                 *JCB*
         BEQ       ATOF.J01        Yes, process                 *JCB*
SKIP     ANOP                                                   *JCB*
         ZR        R6              SHOW VALUE IS ZERO           EIEE-33
         ZR        R7                                           EIEE-33
         BU        ATOF.34         FINISH UP                    EIEE-33
         IFT       UNIXF,SKIP                          *MYATOF* *JCB*
ATOF.J01 CEQU      $                                            *JCB*
SKIP     ANOP                                                   *JCB*
         STW       R5,FLVAL+1W     SAVE CURRENT VALUE IN FLVAL  EIEE-33
         LD        R4,FLVAL        LOAD FLVAL                   EIEE-33
         FLTD      R4,R4           CONVERT TO FLOATING POINT    EIEE-33
         STD       R4,FLVAL        AND SAVE                     EIEE-33
         LW        R4,SCALE        GET SCALE FACTOR             EIEE-33
         CI        R4,1            GREATER THAN ONE             EIEE-33
         BLE       ATOF.16         NO...BRANCH                  EIEE-33
         STW       R4,TMP+1W       SAVE SCALE IN TEMP           EIEE-33
         LD        R4,TMP          LOAD TEMP                    EIEE-33
         FLTD      R4,R4           CONVERT TO FLOATING POINT    EIEE-33
         STD       R4,TMP          AND SAVE                     EIEE-33
         MPFD      R4,TMP          MULTIPLY FLVAL BY SCALE      EIEE-33
         ZMD       TMP             CLEAR TMP VALUE              EIEE-33B
         LW        R4,LITTLE       GET CURRENT LOW VALUE        EIEE-33
         STW       R4,TMP+1W       SAVE IN TEMP                 EIEE-33
         LD        R4,TMP          LOAD LOW                     EIEE-33
         FLTD      R4,R4           CONVERT TO FLOATING POINT    EIEE-33
         STD       R4,TMP          AND SAVE                     EIEE-33
         ADFD      R4,TMP          ADD LOW TO FLVAL             EIEE-33
         STD       R4,FLVAL        AND SAVE                     EIEE-33
ATOF.16  CI        R7,G'E'         IS CHARACTER AN E            EIEE-33
         IFT       UNIXF,SKIP                          *MYATOF* *JCB*
         BEQ       $+3W            Yes, process                 *JCB*
         CI        R7,G'e'         Is char an e                 *JCB*
SKIP     ANOP                                                   *JCB*
         BNE       ATOF.25         NO EXPONENT...BRANCH         EIEE-33
         ZMW       EXP2            CLEAR ASCII EXPONENT         EIEE-33
         ZBM       0,NEGEXP        CLEAR NEGATIVE EXPONENT FLAG EIEE-33
         BL        GBYTE           GET NEXT BYTE FROM STRING    EIEE-33
         CI        R7,G'-'         IS IT A MINUS SIGN           EIEE-33
         BNE       ATOF.17         NO...CONTINUE                EIEE-33
         SBM       0,NEGEXP        SHOW EXPONENT IS NEGATIVE    EIEE-33
         BU        ATOF.18         NEXT CHARACTER               EIEE-33
ATOF.17  CI        R7,G'+'         IS IT A PLUS SIGN            EIEE-33
         BNE       $+2W            NO...CONTINUE                EIEE-33
ATOF.18  BL        GBYTE           GET NEXT BYTE FROM STRING    EIEE-33
         CI        R7,X'30'        IS IT A DIGIT                EIEE-33
         BLT       ATOF.25         NO...BRANCH                  EIEE-33
         CI        R7,X'39'        HIGH SIDE CHECK              EIEE-33
         BGT       ATOF.25         NO...BRANCH                  EIEE-33
ATOF.19  LW        R5,EXP2         GET ASCII EXPONENT VALUE     EIEE-33
         MPI       R4,X'A'         MULTIPLY CURRENT VALUE BY 10 EIEE-33
         ADR       R7,R5           ADD TO CURRENT CHARACTER IN  EIEE-33
         SUI       R5,X'30'        SUBTRACT OUT ASCII 0         EIEE-33
         STW       R5,EXP2         AND SAVE                     EIEE-33
         BL        GBYTE           GET NEXT BYTE FROM STRING    EIEE-33
         CI        R7,X'30'        IS IT A DIGIT                EIEE-33
         BLT       ATOF.22         NO...BRANCH                  EIEE-33
         CI        R7,X'39'        HIGH SIDE CHECK              EIEE-33
         BGT       ATOF.22         NO...BRANCH                  EIEE-33
         BU        ATOF.19         PROCESS EXPONENT CHARACTER   EIEE-33
ATOF.20  BL        YEANAY          ARE WE ASSEMBLING?           EIEE-33
         BNS       ATOF.21         NO...BRANCH                  EIEE-33
         SBM       G'N'-X'40',HWERRF   SHOW TYPE N ERROR        EIEE-33
         ABM       31,HWERCT       ADD TO ERROR TOTAL           EIEE-33
ATOF.21  ZR        R6              VALUE IS ZERO                EIEE-33
         ZR        R7                                           EIEE-33
         BU        ATOF.34         FINISH UP                    EIEE-33
ATOF.22  TBM       0,NEGEXP        IS EXPONENT NEGATIVE?        EIEE-33
         BNS       ATOF.23         NO...BRANCH                  EIEE-33
         LW        R4,EXP          GET DECIMAL POINT EXPONENT   EIEE-33
         SUMW      R4,EXP2         SUBTRACT OUT ASCII EXPONENT  EIEE-33
         BU        ATOF.24         CONTINUE                     EIEE-33
ATOF.23  LW        R4,EXP          GET DECIMAL POINT EXPONENT   EIEE-33
         ADMW      R4,EXP2         ADD IN ASCII EXPONENT        EIEE-33
ATOF.24  STW       R4,EXP          SAVE FINAL EXPONENT VALUE    EIEE-33
ATOF.25  ZR        R3                                           EIEE-33
         LD        R6,FLVAL        GET CURRENT FLOATING PT.NVAL EIEE-33
         STD       R6,FLEXP        SAVE IN SECONDARY VALUE      EIEE-33
         LW        R4,EXP          GET EXPONENT                 EIEE-33
         BEQ       ATOF.31         BRANCH IF ZERO               EIEE-33
         IFT       UNIXF,SKIP                          *MYATOF* *JCB*
         BGE       ATOF.27         BRANCH IF POSITIVE  *MYATOF* *JCB*
SKIP     ANOP                                                   *JCB*
         IFF       UNIXF,SKIP                          *MYATOF* *JCB*
         BGE       ATOF.26         BRANCH IF POSITIVE           EIEE-33
SKIP     ANOP                                                   *JCB*
         TRN       R4,R4           CONVERT BACK TO POSITIVE     EIEE-33
         LD        R6,UNO          LOAD 1.0                     EIEE-33
         STD       R6,FLEXP        SAVE IN SECONDARY VALUE      EIEE-33
         IFF       UNIXF,SKIP                          *MYATOF* *JCB*
ATOF.26  CI        R4,308          EXPONENT GREATER THAN MAX    EIEE-33
         BLE       ATOF.27         NO...BRANCH                  EIEE-33
         BL        YEANAY          ARE WE ASSEMBLING            EIEE-33
         BNS       ATOF.27         NO...BRANCH                  EIEE-33
         SBM       G'N'-X'40',HWERRF    SHOW N TYPE ERROR       EIEE-33
         ABM       31,HWERCT       ADD TO ERROR TOTAL           EIEE-33
SKIP     ANOP                                                   *JCB*
ATOF.27  TBR       R4,31           IS BIT 31 SET IN EXPONENT    EIEE-33
         BNS       ATOF.28         NO...BRANCH                  EIEE-33
         LD        R6,FLEXP        GET CURRENT VALUE            EIEE-33
         MPFD      R6,POWERS,X3    MULTIPLY BY POWERS VALUE     EIEE-33
         NOP                                                    EIEE-33
         NOP                                                    EIEE-33
         GFPC      R2,R0           GET FLOATING PT CONTEXT      EIEE-33
         ANMW      R2,=X'03C00000'  CHECK FOR ERRORS            EIEE-33
         BEQ       ATOF.27B        BRANCH IF OK                 EIEE-33
         SBM       G'N'-X'40',HWERRF  SHOW N TYPE ERROR         EIEE-33
         ABM       31,HWERCT       ADD TO ERROR TOTAL           EIEE-33
         ZR        R6                                           EIEE-33
         ZR        R7                                           EIEE-33
         BU        ATOF.34         EXIT                         EIEE-33
ATOF.27B STD       R6,FLEXP        AND SAVE                     EIEE-33
ATOF.28  SRA       R4,1            SHIFT EXPONENT               EIEE-33
         TRR       R4,R4           IS IT ZERO?                  EIEE-33
         BEQ       ATOF.29         YES...BRANCH                 EIEE-33
         ADI       R3,1D           INCREMENT POWERS POINTER     EIEE-33
         BU        ATOF.27         NEXT BIT OF EXPONENT         EIEE-33
ATOF.29  LW        R7,EXP          GET EXPONENT VALUE           EIEE-33
         BLT       ATOF.30         BRANCH IF NEGATIVE           EIEE-33
         ZR        R6                                           EIEE-33
         MPI       R6,3            MULTIPLY EXPONENT BY 3       EIEE-33
         LW        R4,FLEXP        GET CURRENT VALUE            EIEE-33
         SRL       R4,20           SHIFT EXPONENT TO THE RIGHT  EIEE-33
         ADR       R7,R4           ADD 3*EXP TO CURRENT VALUE   EIEE-33
         CI        R4,X'7FF'       COMPARE TO MAX               EIEE-33
*!!!!!!!!BLE!!!!!!!ATOF.2A!!!!!!!!!BRANCH!IF!OK!!!!!!!!!!!!!!!!!EIEE-34D
         BLT       ATOF.2A         BRANCH IF OK                 EIEE-34D
         SBM       G'N'-X'40',HWERRF  SHOW N TYPE ERROR         EIEE-33
         ABM       31,HWERCT       ADD TO ERROR TOTAL           EIEE-33
ATOF.2A  SLL       R4,20           SHIFT BACK                   EIEE-33
         LD        R6,FLEXP        GET CURRENT VALUE            EIEE-33
         ANMW      R6,=X'000FFFFF' MASK OFF EXPONENT            EIEE-33
         ORR       R4,R6           ORR IN COMPUTED EXPONENT     EIEE-33
         STD       R6,FLVAL        SAVE FLOATING POINT VALUE    EIEE-33
         BU        ATOF.31         RETURN                       EIEE-33
ATOF.30  TRN       R7,R7           CONVERT EXP. BACK TO POS.    EIEE-33
         ZR        R6                                           EIEE-33
         MPI       R6,3            MULTIPLY EXPONENT BY 3       EIEE-33
         LD        R4,FLVAL        GET CURRENT VALUE            EIEE-33
         DVFD      R4,FLEXP        DIVIDE IT BY SECONDARY VALUE EIEE-33
         STD       R4,FLEXP        AND SAVE                     EIEE-33
         SRL       R4,20           SHIFT OUT MANTISSA           EIEE-33
         SUR       R7,R4           SUBTRACT OUT COMPUTED EXP.   EIEE-33
         SLL       R4,20           SHIFT BACK                   EIEE-33
         LD        R6,FLEXP        GET CURRENT VALUE            EIEE-33
         ANMW      R6,=X'000FFFFF' MASK OFF EXPONENT            EIEE-33
         ORR       R4,R6           OR COMPUTED EXP. INTO VALUE  EIEE-33
         STD       R6,FLVAL        SAVE FLOATING POINT VALUE    EIEE-33
ATOF.31  TBM       1,DBLORSGL      DOUBLE OR SINGLE PRECISION   EIEE-33
         BNS       ATOF.32         BRANCH IF DOUBLE             EIEE-33
         TRFD      R6              PUT VALUE IN FLOAT REGISTER  EIEE-33
         TSPR      R6              PULL OUT SINGLE PREC. VALUE  EIEE-33
         NOP                                                    EIEE-33
         NOP                                                    EIEE-33
         GFPC      R2,R4           GET FLOATING PT. STATUS      EIEE-33
         ANMW      R2,=X'00C00000'  OVERFLOW OR UNDERFLOW?      EIEE-33
         TRR       R2,R2                                        EIEE-33
         BEQ       ATOF.32         O.K. IF ZERO                 EIEE-33
         IFF       UNIXF,SKIP                          *MYATOF* *JCB*
* Allow overflow/underflow                                      *JCB*
         BL        YEANAY          ARE WE ASSEMBLING            EIEE-33
         BNS       ATOF.32         NO...BRANCH                  EIEE-33
         SBM       G'N'-X'40',HWERRF   SHOW TYPE N ERROR        EIEE-33
         ABM       31,HWERCT       ADD TO ERROR TOTAL           EIEE-33
SKIP     ANOP                                                   *JCB*
ATOF.32  TBM       0,NEGVAL        WAS NUMBER NEGATIVE          EIEE-33
         BS        $+2W            BRANCH IF SO                 EIEE-33
         BU        ATOF.33                                      EIEE-33
         SBR       R6,0            SHOW VALUE AS NEGATIVE       EIEE-33
ATOF.33  TBM       1,DBLORSGL      DOUBLE OR SINGLE?            EIEE-33
         BNS       ATOF.34         BRANCH IF DOUBLE             EIEE-33
         STW       R6,HDTDS+1W     SAVE SINGLE PRECISION VALUE  EIEE-33
         ZMW       HDTDS           CLEAR TOP HALF OF VALUE      EIEE-33
         ZBM       1,DBLORSGL      CLEAR PRECISION FLAG         EIEE-33
         BU        $+2W            CONTINUE                     EIEE-33
ATOF.34  STD       R6,HDTDS        SAVE DOUBLE PRECISION VALUE  EIEE-33
         SBM       1,FPFLAG        SHOW IEEE DATA OUTPUT        EIEE-33
         GFPC      R2,R4           GET FLOATING PT. CONTEXT     EIEE-33
         ZBR       R2,28           CLEAR IEEE MODE              EIEE-33
         ZBR       R2,29                                        EIEE-33
         ZBR       R2,24                                        EIEE-34C
         ZBR       R2,26                                        EIEE-34C
         SBR       R2,30           SET EXCESS 64 MODE           EIEE-33
         SBR       R2,31                                        EIEE-33
         SBR       R2,27           SET SATURATE ENABLE BIT      EIEE-33
         RFPW      R2,R4           RESTORE FLOATING PT. CONTEXT EIEE-33
         LF        R0,FILE1        RESTORE REGISTERS            EIEE-33
         TRSW      R0              RETURN                       EIEE-33
*                                                               EIEE-33
         BOUND     1D                                           EIEE-33
FLVAL    DATAD     0               FLOAT VALUE ACCUMULATORS     EIEE-33
FLEXP    DATAD     0                          ''                EIEE-33
TMP      DATAD     0                          ''                EIEE-33
POWERS   DATAD     0,0,0,0,0,0,0,0,0   FRACTIONAL POWERS OF 2   EIEE-33
BIG      DATAW     0               INTEGER VALUE ACCUMULATORS   EIEE-33
LITTLE   DATAW     0                          ''                EIEE-33
MANT     DATAW     0               X
SCALE    DATAW     0               SCALE FACTOR                 EIEE-33
EXP      DATAW     0               DECIMAL POINT EXPONENT VALUE EIEE-33
EXP2     DATAW     0               ASCII EXPONENT VALUE         EIEE-33
NZEROES  DATAW     0               ZERO REPEAT COUNT            EIEE-33
UNO      DATAD     X'3FF0000000000000'   IEEE 1.0               EIEE-33
ONEQTR   DATAD     X'3FF4000000000000'    IEEE 1.25             EIEE-33
FILE1    REZ       4D              REG SAVE AREA                EIEE-33
NEGVAL   DATAB     0               NEGATIVE VALUE FLAG          EIEE-33
NEGEXP   DATAB     0               NEGATIVE EXPONENT FLAG       EIEE-33
DECPT    DATAB     0               DECIMAL POINT FLAG           EIEE-33
DBLORSGL DATAB     0               DOUBLE/SINGLE PECISION FLAG  EIEE-33
FPFLAG   DATAB     0               IEEE FLOATING PT. DATA FLAG  EIEE-33
*
TFN      STW       0,TFNS0         SAVE RETURN ADDRESS
         ZMB       HBTFN2          LATEST TERMINATOR-ASSUME INTEGER
         ZMH       HHTDE           ZERO THE USER ENTERED EXPONENT
         ZBM       XPONENT,HHBITS  AND ITS FLAG.                |85.1302
         TBM       9,OPTION2       OPTION 55 SET?               EIEE-33
         BNS       TFM1            NO...BRANCH                  EIEE-33
         SRL       R1,2            POSITION STRING TYPE CODE    EIEE-33
         CI        R1,5            IS STRING TYPE E OR R        EIEE-33
         BLT       TFM1            BRANCH IF NOT E OR R STRING  EIEE-33B
         SLL       R1,2            PUT TYPE CODE BACK           EIEE-33B
         BL        ATOF            GENERATE IEEE NUMBER         EIEE-33
         BU        *TFNS0
TFM1     LB        1,HBTFN2
         STB       1,HBTFN1        PREVIOUS TERMINATOR
         ZMB       HBTFN3
         LW        7,=C'    '      ASCII SPACES
         TRR       7,6             COPY TO R6
         STD       6,HWNAME
         STD       6,HWNAME+1D     BLANK OUT RECEIVNG AREA
TFM2     LW        1,=X'01000000'  TERM ON A '
         BL        GBYTE           GET ONE BYTE                  AS22
         BS        TFM5
         CI        7,G' '
         BEQ       TFM2         IGNORE SPACES
         LI        1,-5W           5 VALID TERMINATORS
TFM4     CAMB      7,TFDE,1        SEARCH TERM LIST
         BEQ       TFM6         TERM FOUND
         BIW       1,TFM4
         LB        1,HBTFN3        STORE POINTER
         CI        1,16
         BLT       TFM42        NOT TOO MANY DIGITS YET
         IFF       UNIXF,SKIP                          *MYATOF* *JCB*
* Allow over 15 digits                                          *JCB*
         BL        YEANAY          ARE WE ASSEMBLING?
         BNS       TFM2         NO.
         SBM       G'N'-X'40',HWERRF   SET ERROR FLAG 'N'
         ABM       31,HWERCT       COUNT THIS ERROR
SKIP     ANOP                                                   *JCB*
         IFT       UNIXF,SKIP                          *MYATOF* *JCB*
* Need to add one to exponent here if not fraction              *JCB*
         LB        1,HBTFN2        LATEST TERMINATOR POINTER    *JCB*
         CI        1,1W            Was last terminator a .      *JCB*
         BEQ       TFM2            Just ignore fraction digit   *JCB*
         ABM       15,HHTDE        Add one to exponent          *JCB*
SKIP     ANOP                                                   *JCB*
         BU        TFM2            GO GET THE NEXT DIGIT
TFM42    CEQU      $                                            ESCT-32
         STB       7,HWNAME,1
         ABM       7,HBTFN3        STORE POINTER
         BU        TFM2            GO GET ANOTHER CHARACTER
TFM5     LI        1,-1W           SUPER TERMINATOR
TFM6     ADI       1,6W            CONVERT (-5W,-1W) TO (1W,5W)
         STB       1,HBTFN2        LATEST TERMINATOR POINTER
         LB        1,HBTFN1
         BU        *TFDD,1         GO DO PROCESSING FOR PREVIOUS TERM
TFM8     LB        1,HBTFN2        LATEST TERM
         CAMB      1,HBTFN1        IS THE NEW POINTER GREATER THAN OLD
         BLE       TFE          NO-ELEMENT SEQUNCE ERROR
         CI        1,4W            FINAL TERM IS 4W OR 5W (, or ')
         BLT       TFM1         NOT A FINAL TERM
         BU        TFO             FINISH UP
TFE      CEQU      $                                            ESCT-32
         BL        YEANAY          ARE WE ASSEMBLING?
         BNS       *TFNS0       NO.
         SBM       G'N'-X'40',HWERRF   FLAG THEBN ERROR
         ABM       31,HWERCT       COUNT THIS ERROR
         BU        *TFNS0          RETURN TO CALLER
TFI      LI        2,+10           DECIMAL RADIX
         BL        CNUM            CONVERT INTEGER FIELD
         STD       6,HDTDS         SAVE INTEGER PART OF CONSTANT
         ZBM       TFSIGN,HHBITS   0=+, 1=- FOR DECIMAL CONSTANT
         TBM       7,HBCNUL        IS THIS A NEGATIVE CONSTANT
         BNS       TFM8         SIGN WAS POSITIVE
         SBM       TFSIGN,HHBITS   0=+, 1=- FOR DECIMAL CONSTANT
         BU        TFM8
TFX      LI        2,+10           DECIMAL RADIX
         BL        CNUM            CONVERT EXPONENT FIELD
         ZR        R2              CLEAR R2                     PR12035
         IFF       UNIXF,SKIP                          *MYATOF* *JCB*
         ADMH      7,HHTDE         Add in previous exponent     *JCB*
SKIP     ANOP                                                   *JCB*
         STH       7,HHTDE         EXPONENT
         TRR       7,7             SET CC'S FOR EXPONENT IN R7  S8702087
         BZ        TFM8            SKIP SET BIT IF EXP. IS ZERO S8702087
         SBM       XPONENT,HHBITS  SHOW USER ENTERED AN EXPONENT 83-308
         BU        TFM8
TFB      LI        2,+10
         BL        CNUM
         STH       7,HHTDB
         BU        TFM8
* Got decimal point
TFF      CEQU      $                                            ESCT-32
         LI        4,X'F'
         ZR        6               CLEAR FRACTION STACK
         ZR        7
         LI        5,-16           16 FRACTIONAL HEX DIGIT WANTED
TFF2     LI        0,10            BASE 10
         ZR        3               NO CARRIES AT START
         LI        1,15            16 DIGITS LURK
TFF4     LB        2,HWNAME,1      FETCH ONE CHAR
         CI        5,-16           IS THIS THE FIRST TIME THRIUGH ?
         BNE       TBCHAR          NO - SKIP THE CHAR VALIDATION CHECK
         CI        2,X'20'         IS CHARACTER A BLANK ?
         BEQ       TBCHAR          YES - OK
         CI        2,X'30'         IS IT LESS THAN ASCII ZERO?
         BLT       TFE             YES - ERROR
         CI        2,X'39'         IS IT GREATER THEN ASCII NINE ?
         BGT       TFE             YES - ERROR
TBCHAR   CEQU      $                                            ESCT-32
         ANR       4,2             CONVERT FROM ASCII TO HEX
         SLL       2,2             BYTE DISP. TO WORD DISPLACEMENT
         ADMW      3,TDMP,2        GET DIGIT TIMES 16
         ZR        2
         SLLD      2,8             GET L. S. D. OF DIGIT PRODUCT
TFF6     CAR       0,2             CHECK FOR DECIMAL CARRY
         BLT       TFF8         NONE
         SUR       0,2             +10 TO +0
         ABR       3,7             THROW IN A CARRY
         BU        TFF6
TFF8     STB       2,HWNAME,1      ONE MULTIPLIED DIGIT
         SUI       1,1             GO FROM LS TO MS DIGITS
         BGE       TFF4         NOT ALL DIGITS DONE
         ZR        2               THROW AWAY DIGIT WE ARE DONE WITH
         SLLD      2,8             PROPAGATE NEXT DIGIT UP
         TBR       3,7             CHECK FOR OVER 10
         BNS       $+2W         NO
         ADI       2,10            YES-MAKE IT INTO ONE HEX DIGIT
         SLLD      6,4             MAKE ROOM IN FRACTION STACK
         ORR       2,7             NEW DIGIT
         BIB       5,TFF2          GET 16 HEX DIGITS
         STD       6,HDTDF         FINISHED FRACTION
         BU        TFM8            GO FINISH THIS ELEMENT
* Here when number done
TFO      CEQU      $                                            ESCT-32
         TBM       TFSIGN,HHBITS   0=+, 1=- FOR DECIMAL CONSTANT
         BNS       TFO4         NO-THEN EVERYTHING IS OK
         LND       6,HDTDF         NEGATE THE FRACTION
         BEQ       TFO4         ZERO FRACTION-NO NEED TO ADJUST INTGR
         STD       6,HDTDF
         LI        7,-1            INTEGER PART ADJUSTMENT
         ES        6               A DOUBLE LENGTH ADJUSTMENT
         ARMD      6,HDTDS         IS MADE TO THE INTEGER
TFO4     LH        6,HHTDE
         BNE       TFOAT1       E NOT ZERO
         LH        6,HHTDBN        NOMINAL BINARY SCALING
         SBR       6,26            MAKE 31 INTO 63 AND 63 INTO 63
         CI        6,63
         BEQ       TFO8         A FIXED POINT CONSTANT
TFOAT1   LI        4,X'F0'
         LB        7,HDTDS+0B      MOST SIG. BYTE
         TRRM      7,5
         TRR       5,6
         BEQ       TFOAT6       POSITIVE AND NOT NORMALIZED
         CI        5,X'F0'
         BNE       TFOAT8       NORMALIZED
         LI        6,X'FF'         NEGATIVE TYPE FLAG FOR R6
TFOAT6   LI        1,-16B
*        + OR - UNNORMALIZED, R6 HOLDS 00 OR FF FOR POS OR NEG
         LI        4,X'0F'
         LI        5,X'F0'
TFOAT7   LB        7,HDTDS+16B,1   GET ONE BYTE
         XCR       4,5             INVERT PATTERN
         CMR       6,7             CHECK DIGIT ONE OF BYTE
         BNE       TFOAT8       NORMALIZED
         XCR       4,5             INVERT PATTERN
         CMR       6,7             CHECK DIGIT TWO OF BYTE
         BNE       TFOAT8       NORMALIZED
         BIB       1,TFOAT7        CHECK 32 DIGITS
         ZMD       HDTDS           COMPLETE ZERO
         BU        TFO9            ALL DONE THEN
TFOAT8   ADI       1,15            GET TO POSITIVE RANGE
         SLL       1,1             CONVERT FROM BYTE COUNT TO DIGIT COUN
         TBR       4,24            WERE WE IN DIGIT ON E OR DIGIT TWO
         BS        TFOAT82      DIGIT ONE
         ABR       1,31            DIGIT TWO,ADD A COUNT
TFOAT82  TRR       6,6             WAS THIS POSITIVE OR NEGATIVE
         BEQ       TFOAT9       POSITIVE
         TRRM      7,7             NEGATIVE NUMBER
         BNE       TFOAT9       NEG AND DIGIT WAS NOT ZERO
         TRR       2,2          ANY PROPAGATED DIGITS ?         85-180
         BEQ       TFOAT83      IF ZERO THEN A FRACTION ENTERED 85-180
         LW        7,HDTDF      PICK UP 1ST 1/2 OF FRACTION     85-180
         BNE       TFOAT83      GO IF FRACTION ENTERED          85-180
         LW        7,HDTDF+1W   PICK UP 2ND 1/2 OF FRACTION     85-180
         BNE       TFOAT83      GO IF FRACTION ENTERED          85-180
         SUI       1,1          ADJ BIT SHIFT REG VALUE         85-180
TFOAT83  CEQU      $                                            ESCT-32
         TRR       2,2           ANY PROPAGATED DIGITS ?        85-180
         BNE       TFOAT9        IF SO DONE                     85-180
         CAMW      5,=X'000000F0'  CHK NORMALIZATION PATTERN    85-180
         BEQ       TFOAT9A                                      85-180
         SUI       1,1             ADJ BIT SHIFT REG VALUE      85-180
         BU        TFOAT9          ... AND CONTINUE             85-180
TFOAT9A  CEQU      $                                            ESCT-32
         TBR       1,31            ODD NUMERIC VALUE ?          85-180
         BNS       TFOAT9          EVEN IS OK                   85-180
         LB        7,HBTDFN+1      CHK EXPONENT SHIFT VALUE     85-180
         CI        7,X'15'
         BEQ       TFOAT9B                                      85-180
         SUI       1,1             ADJ BIT SHIFT REG VALUE      85-180
         BU        TFOAT9          ... AND CONTINUE             85-180
TFOAT9B  CEQU      $                                            ESCT-32
         LW        7,HDTDS+1W      GET PREV NORMAL. PATTERN     85-180
         ANMW      7,=X'00000FFF'  CHK FRACTION PORTION         85-180
         BNE       TFOAT9                                       85-180
         SUI       1,1             ADJ FOR INTEGER REAL VAL.    85-180
*                                                                 82-211
*
* REMOVED THE MODIFICATION FLAGGED AS 'AS20'. THIS 'FIX' WAS NOT A
* COMPLETE SOLUTION AND BROKE MORE THAN IT FIXED. THE PROBLEM WILL
* BE RE-ADDRESSED AND A 'COMPLETE' SOLUTION SEARCHED FOR.
*
TFOAT9   CEQU      $                                            ESCT-32
         LH        7,HHTDE         GET EXPONENT VALUE            83-308
         BNE       TFOAT9D         USER ENTERED AN EXPONENT      83-308
         TBM       XPONENT,HHBITS  IS THERE AN EXPONENT ?        83-308
         BNS       TFOAT9C         ZERO MEANS NO - JUST GO       83-308
TFOAT9D  TRR       6,6             IS NUMBER POSITIVE ?          83-308
         BEQ       TFOAT9C         IF ZERO ,YES DON'T ADJ        83-308
         ZBM       XPONENT,HHBITS  CLEAR EXPONENT DETECTOR       83-308
         SUI       1,1             ADJUST FOR EXPONENT           83-308
TFOAT9C  CEQU      $                                            ESCT-32
         STB       1,HBTDFN        SAVE FOR EXPONENT  REMOV LABEL83-308
         TRR       1,7             AMOUNT OF SHIFTING
         SLL       7,2             SHIFTS ARE 4 TIMES DIGITS PASSED
         BL        TSH             SHIFT NUMBER
         LNB       7,HBTDFN        GET NEGATIVE OF DIGITS PASSED
         ADI       7,14            STACK BIAS
         ADI       7,X'40'         SYSTEMS 86 FLOATING POINT BIAS
         ANMW      7,=X'7F'        LIMIT IT TO 7 BITS
         TBM       TFSIGN,HHBITS   0=+, 1=- FOR DECIMAL CONSTANT
         BNS       $+2W         POSITIVE
         TRC       7,7             NEGATIVE-COMPLEMENT BIASED EXPONENT
         STB       7,HDTDS+0B      MOST SIG BYTE IN FINISHED DOUBLEWORD
         LH        3,HHTDE         GET THE EXPONENT
         BEQ       TFO7         E=0
         IFF       UNIXF,SKIP                            *MYATOF*JCB*
         CI        3,+77           IS EXPONENT VALUE REASONABLE
         BGT       TFE          NO
         CI        3,-77           IS EXPONENT VALUE REASONABLE
         BLT       TFE          NO
SKIP     ANOP                                                   *JCB*
         IFT       UNIXF,SKIP                            *MYATOF*JCB*
* Ignore over/under value exponent                              *JCB*
         CI        3,+77           IS EXPONENT VALUE REASONABLE *JCB*
         BGT       TFEMAX          NO                           *JCB*
         CI        3,-77           IS EXPONENT VALUE REASONABLE *JCB*
         BGE       TFEJCB          YES                          *JCB*
         ZMW       HDTDS           Set 1st word                 *JCB*
         ZMW       HDTDS+1W        Set 2nd word                 *JCB*
         BU        TFO9            Done, so get out             *JCB*
TFEMAX   LW        R6,=X'7FFFFFFF' Get max word 1               *JCB*
         STW       6,HDTDS         Set 1st word                 *JCB*
         LW        R6,=X'FFFFFFFF' Get max word 2               *JCB*
         STW       6,HDTDS+1W      Set 2nd word                 *JCB*
         BU        TFO9            Done, so get out             *JCB*
TFEJCB   EQU       $               Here if O.K.                 *JCB*
* Exponent is -77 >= N <= +77                                   *JCB*
SKIP     ANOP                                                   *JCB*
* THIS PROGRAM COMPUTES 10.D0**I, I INTEGRAL (POSITIVE OR NEGATIVE)
         LD        6,ONE           SET ONE AS INITIAL PP
         TRR       3,2             SAVE AND TEST EXPONENT
         BGT       TFT1            IF EXP>0, CONTINUE
         BZ        TFTX            IF EXP=0, EXIT WITH 1.D0
         TRN       3,3             OTHERWISE, NEGATE EXPONENT
TFT1     ZR        1               SET BIT COUNTER
TFT2     TBR       3,31            TEST LOW BIT OF ABS(EXP)
         SRL       3,1             DIVIDE ABS(EXP) BY 2
         BNS       TFT3            IF LOW BIT WAS OFF, SKIP
         MPFD      6,BASE,1        PP=PP*10.D0**(2**(32-N))
*                                  WHERE N IS BIT POSITION OF ONE BIT
TFT3     TRR       3,3             TEST FOR COMPLETION
         BZ        TFTXP           IF ZERO, GO CLEAN UP
         BID       1,TFT2          GO BACK TO BEGINNING OF LOOP
TFTXP    TBR       2,0             TEST SIGN OF ORIGINAL EXPONENT
*85-180 BNS       TFTX            IF ORIGINAL EXP >0, DONE
         BS        TFTX1           IF ORIGINAL EXP <0, ADJUST   85-180
         LW        7,HDTDS+1W      GET 2ND 1/2 OF VALUE         85-180
         CAMW      7,=X'FFFFFFFF'  CAN IT BE ADJ?               85-180
         BEQ       TFTX2           NO                           85-180
         ADI       7,1             MAKE ADJ. FOR ACCURACY       85-180
         STW       7,HDTDS+1W      STORE CORRECTED VALUE        85-180
TFTX2    ZR        7               RESTORE R7                   85-180
         BU        TFTX            DONE                         85-180
TFTX1    CEQU      $               EXP IS <0                    ESCT-32
*
* OTHERWISE, ANSWER IS 1.D0/PP
*
         STD       6,TEMP          SAVE FOR DIVIDE
         LD        6,ONE           LOAD FOR DIVIDE
         DVFD      6,TEMP          SET TO 1.D0/PP
         TBM       0,HDTDS         IS ORIG NUM NEG?            83-308
         BS        TFTX            NO ADJUSTMENT                83-308
         TBR       2,31            IS EXPONENT ODD ?            83-308
         BNS       TFTXE           NOT SET, ITS EVEN            83-308
         ADI       7,17            INJECT FUDGE FACTOR (ODD)    83-308
         BU        TFTX                                         83-308
TFTXE    ADI       7,6             MUST BE EVEN ADJUSTMENT      83-308
TFTX     MPFD      6,HDTDS         MULTIPLY 10**E BY N.N PART OF CONST.
         STD       6,HDTDS         AND SAVE
TFO7     LH        6,HHTDBN        SCALING
         SBR       6,26
         CI        6,63
         BNE       TFO9         NOT FIXED POINT CONSTANT-NO UNFLOAT
         LB        6,HDTDS+0B      SIGN/EXPONENT BYTE
         SRLD      6,8
         ES        6               EXTEND SIGN THRU R6
         STB       6,HDTDS+0B
         BGE       $+1W+1H      CHECK SIGN
         TRC       7,7             NUMBER WAS NEGATIVE
         ZR        6
         SLLD      6,8             BACK INTO R6 WITH DIGIT COUNT
         TRR       6,7             NEED IT IN R7 FOR TSH
         SUI       7,X'40'+14      REMOVE EXPONENT AND STACK BIASES
         SLL       7,2             DIGIT TO BIT COUNT
         ADMH      7,HHTDBN        NUMBER WE ASSIGNED RIGHTMOST BIT
         SUMH      7,HHTDB         BINARY SCALING IN CONSTANT
         BL        TSH             SHIFT THE STACK TO UNFLOAT NUMBER
         BU        TFO9            NUMBER READY
TFO8     LH        7,HHTDBN        NUMBER WE ASSIGNED LEFTMOST BIT
         SUMH      7,HHTDB         THE SCALING THAT WAS INPUT
         BL        TSH             SHIFT STACK (- RT, + LEFT)
TFO9     LH        6,HHTDBN        CHECK WHETHER THIS WAS AN E TYPE
         CI        6,8
         BNE       *TFNS0       NOT E TYPE CONSTANT
         LW        6,HDTDS+0W      SIGN,EXPONENT, AND MANTISSA
         STW       6,HDTDS+1W      INTO PROPER PLACE FOR SINGLE PREC NO.
         ZR        R4                                           C011-33
         ADFW      R4,HDTDS+1W     NORMALIZE BY ADDING TO ZERO  C011-33
         STW       R4,HDTDS+1W     SAVE NORMALIZED RESULT       C011-33
         ZMW         HDTDS+0W      WIPE OUT WHERE IT WAS
         BU        *TFNS0          RETURN
         SPACE     3
* RELEASE PROPER NUMBER OF DATA BYTES
         SPACE     3
TCY      CEQU      $                                            ESCT-32
         STW       0,TCYS0
         LNB       1,TOT           NEG BOUNDARY REQ(-1,-2,-4,-8=B,H,W,D)
         LB        6,HDTDS+8B,1    GET ONE BYTE FROM STACK OF BYTES
         ZR        7               INDICATE RT JUSTIFIED DATA
         BL        TDG             ALLOW OUT TO PROPER STREAM
         BIB       1,$-3W          GENERATE REQD NUMBER OF BYTES
         BU        *TCYS0          RETURN
         SPACE     3
*        SHIFT THE DATA IN TDI AND TDF A VARIABLE AMOUNT
*        INPUT IS THE NUMBER OF SHIFTS TO BE DONE IN THE R7
*        A NEGATIVE NUMBER OF SHIFTS WILL CAUSE SIGN EXTENDED RIGHT SFT
*        A POSITIVE NUMBER OF SHIFTS WILL CAUSE ZERO FILLED LEFT SHIFTS
         SPACE     3
TSH      CEQU      $                                            ESCT-32
         ZR        2               DEFAULT BITS FOR THE RIGHTMOST FILL B
         TRR       7,7             INPUT REGISTER
         BLT       TSHR         RIGHT SHIFT WANTED
         BGT       TSHL         LEFT SHIFTS WANTED
         TRSW      0               RETURN FOR ZERO SHIFTS
TSHR     TRR       7,7             CHECK REMAINING SHIFS
         BGE       TSHF         ONLY FINE LEFT SHIFTING TO BE DONE
         LI        3,-16           NUMBER OF BYTES IN STACK
         ZR        4               OUR FAKE LEFT REGISTER
         TBM       0,HDTDS+0       CHECK SIGN BIT
         BNS       TSHR3        NO SIGN BIT ON
         TRC       4,4             SIGN BIT ON-SIGN EXTENDED
TSHR3    TRR       4,5             PUSH ONE BYTE
         LB        4,HDTDS+16,3    GET NEW BYTE
         STB       5,HDTDS+16,3    WHILE PUSHING OUT OLD
         BIB       3,TSHR3         DO ALL 16 BYTES
         TRR       4,2             SAVE RIGHTMOST BYTE
         ABR       7,28            SHOW WE HAVE SHIFTED 8 PLACES
         BU        TSHR            SEE IF DONE
TSHL     CI        7,7             HAVE WE FROM 0 THRU 7 SHIFTS TO DO
         BLE       TSHF         YES-THEN FINE SHIFT
         LI        3,-15
TSHL2    LB        4,HDTDS+16,3
         STB       4,HDTDS+15,3    EFFECT 8 BIT LEFT SHIFT
         BIB       3,TSHL2         DO ALL 15 USEFUL BYTES
         STB       2,HDTDS+16      RIGHTMOST BITS
         SUI       7,8             SHOW 8 PLACES SHIFTED
         BU        TSHL
TSHF     ORMH      7,TSHF9         DUMMY SLLD 4,0
         LI        3,-15           NUMBER OF BYTES IN FINE SHIFT
TSHF3    LB        4,HDTDS+16,3    RIGHTMOST BYTE OF THIS DOUBLET
         SRLD      4,8             STASH IT INTO R5
         LB        4,HDTDS+15,3    LEFTMOST BYTE OF THIS DOUBLET
         EXRR      7               PROPER NUMBER OF LEFT SHIFTS
         STB       4,HDTDS+15,3    PROPERLY SHIFTED 8 MSB OF DOUBLET
         BIB       3,TSHF3
         LB        4,HDTDS+15
         TRR       2,5             RIGHT BIT TO COME IN
         EXRR      7               SHIFT ENOUGH OF THEM IN
         STB       4,HDTDS+15      SHIFTED BITS
         TRSW      0               RETURN
TSHF9    SLLD      4,0             FOR EXECUTION IN PLACE
         SPACE     3
* TRANSFER INCOMING DATA BYTES TO PROPER SEQUENCING FOR THE VARIOUS USES
* OF THE DATA TRANSLATOR
* INPUT - R6 = BYTE OF DATA
*       -R7= 0 = RT JUSTIFY IN FIELD, R7 = 1 = LEFT JUSTIFY IN FIELD
*        R1 = NEGATIVE COUNT OF BYTES TO BE DONE
*        HBTTTF    HAS PNTR TO DESTINATION (0,1W,2W,3W=DATA,GEN,LIT,VAL)
TDG      CEQU      $                                            ESCT-32
         STW       0,TDGS0
         STW       1,TDGS1
         LB        2,HBTTTF        POINTER TO DESTINATION
         BU        *TDGJ,2         GO TO PROPER PROCESSOR
TDGJ     ACW       TDG1            DATA,DATAB,DATAH,DATAW,DATAD
         ACW       TDG2            VFD/GEN
         ACW       TDGV            LITERAL
         ACW       TDGV            VALUE EXPRESSION
* PROCES DATA,DATAB,DATAH,DATAW,DATAD
TDG1     LW        1,TDGS1         NEGATIVE BYTE COUNT
         BIB       1,TDG9          BRANCH IF NOT LAST BYTE
* LAST BYTE
         LW        5,HWINAC        GET THE ADDRESS TYPE CODE
         ZBR       5,0             CLEAR DSECT/CSECT FLAG
         ZR        4
         SLLD      4,9             TYPE CODE TO R4
         TRR       4,4             SET CC BITS
         BEQ       TDG9         NULL TYPE OK IN ALL DATA STATEMENTS
         SUMB      4,VDTO          CHECK FOR PROGRAM ABSOLUTE TYPE
         BEQ       TDG9         ABS TYPE OK IN ALL DATA STATEMENTS
         LW        4,HWINAC        GET THE FULL EVALUATION
         LB        5,TOT           NUMBER OF BYTES TO GO OUT
         CI        5,4             CHECK FOR A DATAW STATEMENT
         BEQ       TDG1B        THE ONLY GOOD SIZE FOR NON-ABS DATA
         BL        YEANAY          ARE WE ASSEMBLING?
         BNS       TDG1A        NO.
         SBM       G'R'-X'40',HWERRF  MARK R ERROR
         ABM       31,HWERCT       COUNT THE ERROR
TDG1A    CEQU      $                                            ESCT-32
         ZR        4               DEFAULT TO ABSOLUTE
TDG1B    STW       4,HWEVAL        THE ADDR ATTRIBUTE TYPE FOR OUTPUT
TDG9     BL        IGEN            R6 CONTAINS BYTE
TDGE     LW        1,TDGS1         RESTORE R1
         BU        *TDGS0          RETURN
* PROCESS GEN
TDG2     TRR       7,7             SET CC BITS (R7=0=RT JUSTIFY DATA)
         BEQ       TDG4
* ISSUE LEFT JUSTIFIED DATA (GENERALLY C TYPE)
         LI        7,8             DEFAULT BYTE SIZE OF 8
         LH        5,HHVFGB        HAVE ANY BITS BEEN ISSUED
         BNE       TDG3         YES
         LI        4,7             MASK FOR LAST 3 BITS
         LMH       5,HHVFS         NO, GET LAST 3 BITS OF FIELD SIZE
         BEQ       TDG3         IF 0, NO TRUNCATION REQD
         TRR       5,7             THE NUMBER OF BITS OF TRUNCATED CHAR
TDG3     LH        5,HHVFGB        THE NUMBER OF BITS ALLOWED OUT
         SUMH      5,HHVFS         CHECK AGAINST FIELD SIZE
         BGE       TDGE         ALREADY ENOUGH RELEASED, IGNORE THESE
* R6 CONTAINS BYTE OF DATA
         BL        VFDO            GENERATE FIELD
         BU        TDGE            RETURN
* ISSUE RIGHT JUSTIFIED DATA
TDG4     LH        5,HHVFF         HOW MANY BITS HAVE BEEN INPUT
         BNE       TDG5         NOT FIRST BYTE
         LI        7,64            MAX SIZE OF USABLE DATA
         SUMH      7,HHVFS         IS IT LARGER THAN DESIRED FIELD SIZE
         BGE       TDG5         YES, DONT NEED PADDING ON FRONT
         STW       6,TDGS6         SAVE R6 ORIGINAL CONTENTS
         TRR       7,1             INTO R1 FOR LOOP COUNT
         SRA       1,3             CONVERT FROM BIT COUNT TO BYTE COUNT
         ANMW      7,=X'7'         LIMIT COUNT TO 0-7 RANGE
         TRN       7,7             NEGATE NUMBER OF BITS FOR 1ST CYCLE
         ABR       7,28            ADD IN 8 TO GET NUMBER OF BITS (1-8)
TDG4A    ZR        6               PAD WITH ZEROS
         BL        VFDO            RELEASE DESIRED NUMBER OF BITS
         LI        7,8             ALL SUCCEEDING ARE FULL BYTES
         BIB       1,TDG4A
         LW        6,TDGS6         UNSV R6 ORIGINAL CONTENTS
TDG5     LI        7,8             DEFAULT NUMBER OF BITS PER BYTE
         LI        5,64
         SUMH      5,HHVFS         FIELD SIZE REQD
         SUMH      5,HHVFF         NUMBER OF BITS ALREADY IN
         BLT       TDG7         WE ARE WELL INTO FIELD ALREADY
         CAMW      5,=8
         BLT       TDG6         BEGINNING OF FIELD
* NOT AT FIELD YET
         LI        5,8             SKIP DATA SUPPLIED
         ARMH      5,HHVFF         MOVE TO NEXT DATA
         BU        TDGE            RETURN
* BEGINNING OF FIELD
TDG6     TRN       5,7
         ADI       7,8             RANGE 1-8 NUMBER OF BITS FOR 1ST BYTE
TDG7     BL        VFDO            R6 CONTAINS BYTE OF DATA TO RELEASE
         BU        TDGE            RETURN
* LITERAL OR VALUE EXPRESSION
TDGV     TRR       7,7             SET CC BITS FOR RT OR LT JUSTIFIED
         BEQ       TDGE         RT JUSTIFIED DATA IS OK WHERE IT IS
         LB        5,TOT           LT JUST.MUST BE LOADED INTO TDS
         SUI       5,4             IS THIS FIRST TIME THRU
         BNE       TDGW         NO, NO NEED TO PACK WITH SPACES
         LW        1,HWKSPA        PUT SPACES IN STACK
         STW       1,HDTDS+1W
TDGW     LB        1,TOT           USE THIS AS OVERRUN CO4N E-
         CI        1,8             MAX 4 CHAR PER CONSTANT
         BGE       TDGE         MAX REACHED, RETURN
         STB       6,HDTDS,1       BYTE TO TDS WITH TOT AS POINTER IN
         ADI       1,1             POINT TO NEXT STACK POSITION
         STB       1,TOT           SAVE STACK POSITION
         BU        TDGE            RETURN
*
* (C) COPYRIGHT 1983 ENCORE COMPUTER CORPORATION
*     ALL RIGHTS RESERVED
*
         TITLE     READ-ONLY       VFDO
* PACKER OF VARIABLE SIZE BIT FIELDS AND ISSUER OF FULL BYTES
* INPUT - R6 CONTAINS RIGHT JUSTIFIED DATA
*      - R7 CONTAINS NUMBER OF BITS TO BE PACKED (1-8)
         SPACE
VFDO     CEQU      $                                            ESCT-32
         STW       1,VFDOS1        SAVE X1
         STW       0,VFDOS0        SAVE RETURN ADDRESS
         LH        2,HHVFX         OLD BYTE STACK
         TRR       6,3             INPUT BITS FOR STACK
         TRR       7,5             NUMBER OF BITS
         ADMH      5,DSRC          DUMMY SHIFT INST + NUMBER OF SHIFTS
         EXRR      5               SHIFT TO POS BITS IN UPPER OF R3
         TRR       7,5             NUMBER OF BITS AGAIN
         ADMH      5,DSLLD         DUMMY SHIFT + NUMBER OF SHIFTS
         EXRR      5               SHIFT TO GET NEW BIT STACK IN R2
         STH       2,HHVFX         NEW BIT STACK
         ARMH      7,HHVFO         INCR NUMBER OF BITS IN STACK COUNT
         ARMH      7,HHVFGB        INCR NUMBER OF BITS RELEASED
         ABM       12,HHVFF        INCREASE NUMBER OF BITS IN
         LH        3,HHVFO         NUMBER OF BITS IN STACK
         CI        3,8             DO WE HAVE A FULL BYTE TO RELEASE
         BCF       GE,*VFDOS0      NO, RETURN
         ANMW      3,=7            GET NUMBER OF BITS LEFT AFTER ISSUE
         STH       3,HHVFO         POINTS TO THE BYTE TO BE ISSUED
         LH        5,HHVFS         NUMBER OF BITS REQD
         CAMH      5,HHVFGB        NUMBER OF GOOD BITS DONE
         BNE       VFDF         NOT AT END,IGNORE REL,EXT,COM CHECKS
         LH        6,HHVFO         NUMBER OF BITS LEFT IN STACK
         BNE       VFDC         SOME BITS LEFT
         LI        4,3
         LB        2,HBLABS        POINTER TO CORRECT PROG COUNTER
         LMW       6,HWLSTR,2      PROG COUNTER (LAST 2 BITS)
         SUI       6,3             MUST BE AT LAST BYTE FOR REL,EXT,COM
         BLT       VFDC         NOT THERE,ENSURE PROG ABS TYPE
         CI        5,19            MIN FIELD SIZE FOR REL,EXT,COM
*                                  COMPARED WITH NUMBER OF BITS REQUEST
         BLT       VFDC         TOO SMALL FORE RELOCATION
         CI        5,32            MAX FIELD SIZE FOR RELOCATION
         BGT       VFDC
         LW        6,HWINAC        FRESULT OF ANY ADR ATTRIBUTION
         STW       6,HWEVAL        ALLOW LOADER TO EXAMINE IN MAKING WRD
         ZBR       6,0             CLEAR DSECT/CSECT FLAG
         SRL       6,24            POSITION TYPE CODE FOR COMPARE
         CI        6,TYPC          COMMON REF TYPE.
         BNE       VFDL.1          NO
         LB        7,HWINACBN      THE BLOCK NUMBER FOR THE EXPRESSION
         STB       7,HBBN          IF ANY IS SAVED FOR OUTPUT
         BU        VFDF
VFDL.1   LW        7,SECNUMAC      SECTION NUMBER, IF ANY
         STB       7,HBBN          STORE LATER OUTPUT
VFDF     LH        2,HHVFX         GET BIT STACK
         ADMH      3,DSRL          NUMBER OF BITS TO REMAIN + DUMMY SHFT
         EXRR      3               SHIFT OFF BITS TO REMAIN
         TRR       2,6             BYTE TO R6 FOR IGEN
         BL        IGEN            RELEASE BYTE
         LW        1,VFDOS1        UNSV X1
         BU        *VFDOS0         RETURN
VFDC     LH        6,HWINAC        TYPE + GARBAGE
         SRL       6,7             DUMP GARBAGE
         TRR       6,6             SET CC BITS
         BEQ       VFDF         NULL TYPE OK FOR ALL CASES
         SUMB      6,VDTO          IS IT ABSOLUTE TYPE
         BEQ       VFDF         ABSOLUTE TYPE OK
         BL        YEANAY          IS ASSEMBLY GOING ON?
         BNS       VFDF         NO, DON'T MARK 'R' ERROR.
         SBM       G'R'-X'40',HWERRF  MARK R ERROR
         ABM       31,HWERCT       COUNT THE ERROR
         BU        VFDF
         TITLE     READ-ONLY       RSET
* INITIALIZE ASSEMBLER TO START ANY PASS. R1=0 MEANS PASS 2.
         SPACE     1
RSET     CEQU      $                                            ESCT-32
         STW       0,RSETS0        SAVE RETURN ADDRESS
         STB       1,HBPASS        ZERO MEANS PASS2,ELSE PASS1
         ZBM       1,EXTFLG        RESET STRINGBACK FLAG        ENSB-33
         LI        1,-80           COUNT OF MACROSTORAGE PRINT AREA
         LW        4,=C'    '      ASCII SPACES
         STW       4,MPBUF+80,1    BLANK OUT THE MACRO EXPANSION AREA
         BIW       1,$-1W          DO ALL 20 WORDS/80 BYTES
         ZMH       MACSTATE        CLEAR MACRO STATUS FLAG
         ZMH       INPTSTAT        CLEAR ALTERNATE MACRO STATUS FLAG
         ZMW       INTTAG          ZERO INTERNAL TAG COUNTER INITIALLY
         ZMW       HWMSPBUF        CLEAR STORE POINTER FOR MACRO PRINT
         LI        1,MACIU         ENTRY TYPE INT SYM UNASSEMBLED.
         SLL       1,5             SHIFT TO ENTRY TYPE POSITION.
         STB       1,INTTAG        STORE IN INT TAG COUNTER.
         TBM       7,HBPASS        WHICH PASS ARE WE IN?
         BNS       $+2W         PASS 2.
         ZMW       HWMSP           ZERO MACRO STORAGE POINTER
         ZBM       INSIG,HHBITS    FORCE OFF THE INSIGNIFIGANT BIT FLAG
         TBM       7,HBPASS        ARE WE IN PASS 2?
         BNS       RSET13       YES
*!!!!!!!!!!ZMB!!!!!!!HHBITS3!!!!!!!!!ZERO!FLAGS!FOR!PASS!1!ONL!!EASC-32
*!   ABOVE NOW DONE ELSEWHERE, ONLY BIT 0 IS USED.              EASC-32
         BU        RSET14
RSET13   LW        1,HWLSTR+1W     GET DSECT SIZE
         STW       1,DSIZE           AND SAVE IT
         LW        1,HWLSTR+3W     GET CSECT SIZE
         STW       1,CSIZE           AND SAVE IT
RSET14   ZMW       HWERCT          ZERO ERROR COUNT
         ZMW       HWERRF          ZERO ERROR FLAGS
         ZMW       HHBITS2         CLEAR HHBITS2 FLAGS.
         ZMH       HHBITS          CLEAR ALL THE FOLLOWING FLAG BITS
*                  ESCAPE2,        START IN AN UNESCAPED MODE
*                  APEX,           ALLOW EXTENSIONS
*                  APON,           ALLOW LISTING
*                  IMIN,           INDICATE NO BUFFER IMAGE READY
*                  CVFL,           DONT WANT PROGRAM COUNTER PRINTED
*                  PROGF,          PROGRAM STATEMENT ENTERED FLAG
* INITIALIZE TITLE CARD BUFFER
         LW        1,HWKSPA        A WORD OF SPACES
         LA        R2,TCWTITL      ADDRESS OF TITLE BUFFER
RSET14.1 STW       R1,0,R2         BLANK FILL "TCWTITL" BUFFER
         ADI       R2,4            INCREMENT POINTER TO NEXT WORD
         CAMW      R2,=TCWTTLE     COMPARE POINTER WITH BUF END   83-451
         BLT       RSET14.1        BRANCH IF NOT DONE
         LI        2,1W            REL DSECT MODE
*-------------------------------------------------------------- EASC-32
*  SELECT MODE AS A FUNCTION OF OPTION 18                       EASC-32
         TBM       ASCT.OPT,OPTION  IS OPTION 18 ON             EASC-32
         BNS       $+2W             SKIP IF NOT                 EASC-32
         LI        2,3W            ELSE SET CSECT MODE          EASC-32
*-------------------------------------------------------------- EASC-32
         STB       2,HBLABS
         LI        2,TYPP          PROGRAM DEFINITION TYPE CODE RT JUST
         ZR        3
         SRLD      2,8             LEFT JUSTIFIED IN R3
         STW       3,HWLSTR        INITIALIZE ABSOULTE PROG COUNTER
         SBR       3,8
         STW       3,HWLSTR+1W     INIT PROG REL DSECT CTR
         STW       3,HWBBLS        SET THE LOADER DRIVER PC TO REL 0
         SBR       3,0             SET CSECT FLAG
         STW       3,HWLSTR+3W     INIT PROG CSECT CTR
         ZMB       HBCCCT          CLEAR COMMON BLOCK COUNT
         ZMW       HWLTCT
         LI        2,TYPL
         STB       2,HWLTCT        SET LITERAL TYPE,LPOOL COUNT AND
         ZMB       HBBBFB          INDICATE NO DATA BYTES HAVE GONE OUT
         LW        6,HATCWD        LGTH AND ADR OF HEADING LINE.
         BL        EJCT2           FORCE TOP-OF-FORM.
         ZR        1               DONT CONFUSE THE REPORTER
         TBM       7,HBPASS        ARE WE IN PASS 1?
         BS        RSET18.1     YES--SKIP XREF.
*!!!!!!!!LA!!!!!!!!R2,SYMTAB!!!!!!!ADDRESS!OF!SYMBOL!TABLE!!!!!!S880752
         LW        R2,SYMTAB       ADDRESS OF SYMBOL TABLE      S880752
         BZ        RSET18.1        SKIP IF NO SYMBOLS           S880752
RSET15   LW        R4,2W,R2        4 CHARS OF NAME
         LW        R5,3W,R2        4 CHARS OF NAME
         LW        R3,4W,R2        THE SYMBOL ITEM KEY
         LB        R6,2W,R2        GET FIRST CHAR OF NAME
         CI        R6,X'21'          IS THIS AN INT SYM?
         BNE       RSET15.1     NO.
         TBM       XREFINT,OPTION  ARE WE XREFING INTERNALS
         BS        RSET15.1       YES
         BU        $+3W            SKIP OVER XREF CALL THEN
RSET15.1 ZMW       REPTYPE         INDICATE SYMBOL REPORT TO XREF
         BL        REPTR          REPORT RESIDENT SYMBOL
         LB        R6,4W,R2        GET THE TYPE OF THE SYMBOL TABLE ITEM
         ZBR      R6,24            CLEAR DSECT/CSECT FLAG
         LI       R4,0             IS THE EXTERNAL SYMBOL VALUE REPLACEM
         CI       R6,TYPX          IS THE TYPE EXTERNAL
         BNE       RSET18       NO.
         TRR       R2,R7           SAVE R2                      ELST-32
         LW        R2,4W,R2        GET PNTR TO STRINGBACK ADDRS ELST-32
         STW       R4,0,R2         RESET DSECT STRINGBACK ADDR  ELST-32
         STB       R6,0,R2         RESTORE TYPE CODE            ELST-32
         STW       R4,1W,R2        RESET CSECT STRINGBACK ADDR  ELST-32
         STB       R6,1W,R2        RESTORE TYPE CODE            ELST-32
         TRR       R7,R2           RESTORE R2                   ELST-32
*!!!!!!!!STW!!!!!!!R4,4W,R2!!!!!!!!PLACE!THE!NEW!VALUE!INTO!SYMBELST-32
*!!!!!!!!STB!!!!!!!R6,4W,R2!!!!!!!!PLACE!THE!TYPE!CODE!BACK!IN!!ELST-32
*!RSET18!!!ADI!!!!!R2,6W!!!!!!!!!!!SYMBOL!TABLE!INCREMENT!!!!!!!S880752
RSET18   CEQU      $                                            ESCT-32
         LW        R2,5W,X2        GET NEXT ENTRY ADDRESS       S880752
         BNZ       RSET15          CONTINUE IF NOT DONE         S880752
*!!!!!!!!CAMW!!!!!!R2,SYMCURRP!!!!!ARE!WE!AT!END!!!!!!!!!!!!!!!!S880752
*!!!!!!!!BLT!!!!!!!RSET15!!!!!!!!!!BR!IF!NOT!!!!!!!!!!!!!!!!!!!!S880752
RSET18.1 ZR        3               CLEAN UP WHAT WILL BECOME THE COMMAND
         TBM       7,HBPASS        WHICH PASS ARE WE IN
         BNS       $+1W+1H      PASS 2
         SBR       3,2             PASS 1
         SBR       3,0             COMMAND REPORTER
         SBM       0,REPTYPE       INDICATE COMMAND TO XREF.
         BL        REPTR          SEND PASS NUMBER TO REPORTER
         TBM       7,HBPASS        WHICH PASS ARE WE IN
         BNS       RSET2        PASS 2
*        CLEAR LITERAL POOL AREA
         LI        1,-32W
         ZMW       LITORGS+32W,1
         ZMW       SYMHEAD+32W,R1
         BIW       1,$-2W
*                                     LITERAL COUNTER
* RESET SYMBOL TABLE
*!!!!!!!!ZMD!!!!!!!SYMTAB!!!!!!!!!!CLEAR!1ST!ENTRY!IN!SYMTAB!!!!S880752
*!!!!!!!!ZMD!!!!!!!SYMTAB+2W!!!!!!!ENTRY!IS!6W!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!ZMD!!!!!!!SYMTAB+4W!!!!!!!LAST!WORD!OF!SYMTAB!ENTRY!!!!S880752
*!!!!!!!!LA!!!!!!!!R2,SYMTAB!!!!!!!GET!ADDRESS!OF!SYMBOL!TABLE!!S880752
*!!!!!!!!STW!!!!!!!R2,SYMCURRP!!!!!RESET!SYMBOL!TABLE!POINTER!!!S880752
*!!!!!!!!LW!!!!!!!!R2,LOW!!!!!!!!!!RESET!MACRO!STORAGE.!GET!LOW!S880752
*!!!!!!!!STW!!!!!!!R2,CURRP!!!!!!!!RESET!CURR!STORAGE!POINTER!!!S880752
         ZMW       MACP            CLEAR MACRO POINTER
         ZMW       MA2P            CLEAR MA2 STORAGE POINTER
*                                                               S880752
         LW        R5,LOW          GET START OF EXTENDED AREA   S880752
*!!!!!!!!STW!!!!!!!R5,SYMTAB!!!!!!!SET!AS!FIRST!SYMTAB!ENTRY!!!!S880752
*!!!!!!!!STW!!!!!!!R5,SYMCURRP!!!!!AND!AS!CURRENT!SYMTAB!ENTRY!!S880752
*!!!!!!!!ADI!!!!!!!R5,6W!!!!!!!!!!!MAKE!SURE!THERE'S!AN!ENTRY!!!S880752
         STW       R5,CURRP        BY UPDATING FREE POINTER     S880752
         ZMW       SYMCURRP        RESERT NEXT SYMBOL POINTER   S880752
         ZMW       SYMPREVP        RESET PREVIOUS SYMBOL PNTR.  S880752
         ZMW       SYMTAB          RESET ADDR OF 1ST SYMBOL     S880752
*                                                               S880752
         LI        5,8             DEFAULT CASE FOR MAX BOUNDING
         STW       5,HWCMPB+0W     FOR DSECT
         STW       5,HWCMPB+1W     FOR CSECT
         LW        5,=C'MAIN'      DEFAULT CASE PROGRAM NAME
         STW       R5,TCWPROG      TO TITLE HEADING AND STORAGE
         LW        R5,=G'    '     SECOND HALF OF DEFAULT       |85.0780
         STW       R5,TCWPROG+1W   TO HEADING AND STORAGE       |85.0780
         LI        6,TYMACREQ      MACRO REWUEST TYPE CODE
         STB       6,HWMRQ         GO GET IT
RSET2    CEQU      $                                            ESCT-32
         IFF       UNIXF,SKIP                                   *JCB*
         LW        R6,BUFFADD      GET XRBUF ADDR               S880752
         STW       R6,FCBXR+8W     PUT INTO FCB                 S880752
         LW        R6,BUFFADD+1W   GET BUFFER LENGTH            S880752
         STW       R6,FCBXR+9W     PUT INTO FCB                 S880752
SKIP     ANOP                                                   *JCB*
         IFT       UNIXF,SKIP                                   *JCB*
         TBM       XREF,OPTION     SET XREF REQUIRED            *JCB*
         BS        *RSETS0         NO, GET OUT                  *JCB*
         LW        1,XR.FCBA       FILLED THE BUFFER-WRITE IT   *JCB*
         LW        R6,BUFFADD      GET XRBUF ADDR               *JCB*
         STW       R6,8W,X1        PUT INTO FCB                 *JCB*
         LW        R6,BUFFADD+1W   GET BUFFER LENGTH            *JCB*
         STW       R6,9W,X1        PUT INTO FCB                 *JCB*
SKIP     ANOP                                                   *JCB*
         BU        *RSETS0
         TITLE     READ-ONLY       BOUC
*        MANIPULATE THE CURRENT PROGRAM COUNTER TO A MULTIPLE OF THE
*        INPUT IN R7. R7 EQ THE BOUND VALUE. SET HWCMPB TO LARGEST BOUND
         SPACE
BOUC     CEQU      $                                            ESCT-32
         STW       0,BOUCS0
         BL        YEANAY          CHECK WHETHER ASSEMBLY IS ALLOWED
         BNS    BOUC1           DONT ASSEMBLE
         BL        TBOU            CHECK FOR CORRECT BOUNDARY.
         TRR       4,4             DISTANCE FROM PREV BOUND IN R4. SET C
         BEQ       BOUD
         LW        6,HWLSTR,2      PROGRAM COUNTER
         ADR       7,6             BOUND VALUE + PROG COUNTER = R6
         SUR       4,6             LESS THE DIST FROM PREV BOUND EQ THE
*                                  NEW BOUNDARY IN R6
         STW       6,HWLSTR,2      RESET PROG COUNTER
         BL        PCCHK           CHECK FOR PROG CNT OVERFLOW  S920209
         STW       6,HWLSTS        STATICIZE PROG COUNTER
BOUD     LB        1,HBLABS        CHECK FOR RELATIVE MODE
         CI        1,1W            REL DSECT?
         BEQ       BOUD1           YES
         CI        1,3W            REL CSECT?
         BEQ       BOUD1           YES
         BU        *BOUCS0         NOT REL - RETURN
BOUD1    CEQU      $                                            ESCT-32
         TRR       7,1             PROG COUNTER
         SRL       1,31            ISOLATE DSECT/CSECT FLAG IN R1
         SLL       1,2             CONVERT DSECT/CSECT FLAG INTO A BYTE
*                                  OFFSET INTO HWCMPB
         ANMW      7,=X'FFFFF'     LIMIT BOUND TO REASONABLE VALUE
         CAMW      7,HWCMPB,1      COMPARE TO LARGEST PREV BOUND
         BCF       GT,BOUC1        SKIP NEXT INST IF OLD BOUND IS LARGER
         STW       7,HWCMPB,1      NEW BOUND IS LARGER , SAVE IT
BOUC1    BU        *BOUCS0         RETURN
         TITLE     READ-ONLY       TBOU, BNDW
*        CHECK WHETHER THE CURRENT PROGRAM COUNTER IS ON THE CORRECT
*        BOUNDARY (I.E. A MULTIPLE OF THE INPUT IN R7)
*        R4 WILL BE ZERO UPON RETURNING IF BOUNDARY IS CORRECT
         SPACE
*
* (C) COPYRIGHT 1983 ENCORE COMPUTER CORPORATION
*     ALL RIGHTS RESERVED
*
TBOU     CEQU      $                                            ESCT-32
         LW        4,=X'007FFFFF'  PROGRAM COUNTER VALUE MASK
         LB        2,HBLABS        POINTER TO PROGRAM COUNTER
         LMW       5,HWLSTR,2      PROGRAM CNTR VALUE TO R5 FOR DIVIDE
         TRRM      7,7             MASK INPUT WITH X'00FFFFFF'
         ZR        4
         DVR       7,4             PC/BOUND VAL=NO REMAINDER IF ON BOUND
         SPACE
* REMAINDER EQUALS DISTANCE FROM PREVIOUS CORRECT BOUNDARY
         SPACE
         TRSW      0               RETURN
         SPACE     3
* BOUND INSTRUCTION COUNTER AS NECESSARY FOR THE NEXT LINE
* ALGORITHM FOR BOUND - (PC)+8 MODULO 8= QTY TO ADD FOR DOUBLEWORD
*                     -(PC)+8MODULO 4=QTY TO ADD FOR WORD
*                     -(PC)+8MODULO 2= QTY TO ADD FOR HALFWORD
         SPACE
BNDW     CEQU      $                                            ESCT-32
         STW       R0,BNDW.R0      SAVE RETURN ADDRESS          S920209
         TBM       CONDSCAN,MACSTATE    CHECK FOR CONDITIONAL ASSEMBLY O
         BS        BNDW1        NO ASSEMBLY ALLOWED NOW
         TBM       DEFMBODY,MACSTATE     CHECK WHETHER WE IGNORE THIS
         BS        BNDW1           NO OPERATION DURING DEFM BODY
         TBM       RSCAN,MACSTATE     CHECK FOR BEING IN A REPEAT SCAN
         BS        BNDW1        NO GEN FOR A REPEAT SCAN
         LI        4,X'3'          SET MASK FOR LAST 2 BITS
         LMB       5,HWACT         BOUNDARY DEMAND
         LB        1,HBLABS        POINTER TO CORRECT PROG COUNTER
         LI        4,7             SET MASK FOR LAST 3 BITS
         LMW       2,HWLSTR,1      LAST 3 BITS OF PROG COUNTER
         LB        3,BNDWS1,2      SET R3 TO STATUS OF PROG COUNTER
         SPACE
* 0 EQ BYTE, 1 EQ HALFWORD, 2 EQ WORD, 3 EQ DOUBLE WORD
* WE MUST GEN NOP IF ON HALF BOUNDARY AND NEXT INST IS WORD
         SPACE
         TBR       3,31                  SHOULD
         BNS       BNDW1.5               A
         TBR       3,30                    NOP
         BS        BNDW1.5        INSTRUCTION
         TBR       5,31                     BE
         BS        BNDW1.5         GENERATED
         TBR       5,30                     ?
         BS        BNDWNOPG     YES.
BNDW1.5  CEQU      $                                            ESCT-32
         TRN       2,4             R4=(LAST 3 BITS OF PROG CNTR) NEG
         ABR       4,28            ADD 8
         TRR       5,2             BOUNDARY DEMAND IN R2
         LMB       4,BNDWS2-1,2    MODUL0 8,4 OR 2(BY BOUNDARY DEMAND)
         BEQ       BNDW1        BRU IF NO ADDITION REQD
         ADMW      4,HWLSTR,1      ADD TO PROG COUNTER
         STW       4,HWLSTR,1
         BL        PCCHK           CHECK FOR PROG CNT OVERFLOW  S920209
         STW       4,HWLSTS
BNDW1    LW        R0,BNDW.R0      RESTORE RETURN ADDRESS       S920209
         TRSW      0
         SPACE
* COME HERE TO GEN NOP
BNDWNOPG STW       0,BNDWS0        SAVE RET ADDRESS
         LI        6,0             GENERATE NOP
         BL        IGEN            GENERATE LEFT BYTE OF NOP (0000)
         ZBM       BNDWS3,HHBITS   CLEAR TEMP BITS STORE
         ZBM       IMIN,HHBITS     INDICATE NO BUFFER IMAGE READY
         BNS       $+2W         BIT WAS OFF-DONT TURN ON ITS PARTNER
         SBM       BNDWS3,HHBITS   SAVE A TURNED ON BIT
         ZBM       BNDWS4,HHBITS   BIT STORE
         ZBM       EXPAND,INPTSTAT     ZERO AND CHECK EXPAND MODE.
         BNS       $+2W         NOT ON BEFORE-DONT SAVE A BIT
         SBM       BNDWS4,HHBITS   BIT STORE
         SBM       NOPGEN,SPMAC    INDICATE  A NOP IS BEING GENERATED.
         LI        6,2             AUGMENT OF 2 IS RT BYTE OF NOP
         BL        IGEN            GENERATE RT BYTE
         TBM       BNDWS3,HHBITS   CHEK A TURNED ON BIT
         BNS       $+2W         BIT WAS OFF-DONT TURN ON ITS PARTNER
         SBM       IMIN,HHBITS     INDICATE BUFFER IMAGE READY
         ZBM       NOPGEN,SPMAC    CLEAR NOP GENERATION FLAG.
         TBM       BNDWS4,HHBITS   BIT STORE
         BNS       $+2W         NOT ON BEFORE-DONT SAVE A BIT
         SBM       EXPAND,INPTSTAT     IT WAS ON BEFORE-SAVE THE BIT.
         LB        2,HBLABS        POINTER TO CORRECT PROG COUNTER
         LW        6,HWLSTR,2      PROG COUNTER
         STW       6,HWLSTS        STATICIZE PROG COUNTER
         BU        *BNDWS0
*
BNDW.R0  REZ       1W              RETURN ADDRESS SAVE AREA     S920209
*
         TITLE     READ-ONLY       AGEQ
* PUT ADDRESS WORD TOGETHER WITH F,CC AND INDIRECT BIT
* INPUT--ADDRESS RIGHT JUSTIFIED IN R2
* OUTPUT-ADDRESS WITH F,CC AND I RIGHT JUSTIFIED IN R7
         SPACE     1
AGEQ     CEQU      $                                            ESCT-32
         LB        6,HWEVAL        GET TYPE OF ADDRESS FIELD
         CI        6,TYPC          IS IT COMMON?
         BNE       AGEQ0           NO
         LB        2,HWEVAL+1B     GET BLOCK NUMBER
         SLL       2,2             MAKE INTO A WORD INDEX
         TBM       0,HWCMSIZE,2    IS IT AN SSECT
         BNS       AGEQ.A          NO
         ZMB       HWEVAL+1B       CLEAR BLOCK NUMBER
AGEQ.A   LW        2,HWEVAL
AGEQ0    CEQU      $                                            ESCT-32
         LB        7,HBAVAR        ADDRESS VARIANT POINTER
         XCR       2,7             ADDRESS TO R7
         SLL       2,2             CONV ADR VAR PT TO WORD DISPLACEMENT
         LB        6,AGER,2        PEEK THRU AN ERROR MASK
         ANR       7,6             LOOK AT INPUT THRU ERROR MASK
         BEQ       AGEQ1        NO BOUNDARY ERROR.
         TRR       7,6             THE INPUT ADDRESS.
         SRL       6,24            TYPE OF ADDRESS.
         ZBR       6,24            CLEAR DSECT/CSECT FLAG
         CI        6,TYPX          IS IT EXTERNAL?
         BEQ       AGEQ1        YES--DON'T MARK ERROR.
         LB        6,HBSTAC          GET LAST TERMINATOR.
         CI        6,G')'          WAS IT A ')' ?
         BEQ       $+3W         YES, GO MARK ERROR.
         SBM       ADDRERR,HHBITS2   SET ADDRESSING BOUNDARY ERROR FLAG.
         BU        AGEQ1           CONTINUE PROCESSING.
         TBM       DEFMBODY,MACSTATE   ARE WE IN A PROTOTYPE BODY?
         BS        AGEQ1        YES, DON'T MARK ERROR.
         TBM       RSCAN,MACSTATE     IN REPEAT SCAN?
         BS        AGEQ1           YES-DON'T MARK ERROR.
         TBM       CONDSCAN,MACSTATE  SKIPPING SOURCE?
         BS        AGEQ1           YES-DON'T MARK ERROR.
         SBM       G'B'-X'40',HWERRF  MARK B ERROR
         ABM       31,HWERCT       COUNT THE ERROR
AGEQ1    TBM       3,BACFLAG       BAC TO AN EXTERNAL?          EBAC-33C
         BNS       $+3W            NO...BRANCH                  EBAC-33C
         ANMW      R7,=X'0008FFFF'  FILL WITH TERMINAL VALUE    EBAC-33C
         BU        $+2W            CONTINUE                     EBAC-33C
         ANMW      7,AGER,2        ELIMINATE UNUSED ADDRESS BITS.
         ORMW      7,AGES,2        PUT IN PROPER F AND CC BITS
         ORMW      7,HWINDR        AND INDIRECT ADR DESIGNATOR
         TRSW      0               RETURN
         TITLE     READ-ONLY       CNUM
*        RADIX NUMBER TO BE ENTERED IN R2.  IT MAY RANGE FROM N'2' TO
*        N'16' WHERE INPUT CHARACTERS WILL BE ASCII ALPHABET FROM
*        0-9 AND THEN A-F.
*        OUTPUT IS THE DOUBLE PRECISION INTEGER IN R6 AND R7
*        AND THE NON-NUMERIC EQUIVALENT TERMINATOR IN R5
         SPACE     1
CNUM     CEQU      $               ENTRY POINT                  ESCT-32
         ZR        3               ZERO INPUT BYTE POINTER, ASSUME + DAT
         ZMD       CNUA            ACCUMULATED CONVERTAND INITIALIZATION
         ZMD       CNUB            LATEST CHARACTER STORE INITIALIZATION
         ZBM       DUMMY,SPMAC     IS THIS A DUMMY PARAMETER?
         BS        CNUV         YES, MAKE WAY OUT.
         TBM       CONDSCAN,MACSTATE  IN CONDITIONAL SCAN?
         BS        CNUV         YES,MAKE WAY OUT.
         TBM       RSCAN,MACSTATE     IN REPT SCAN?
         BS        CNUV            YES-MAKE WAY OUT.
         TBM       DEFMBODY,MACSTATE  IN PROTOTYPE BODY?
         BS        CNUV            YES-MAKE WAY OUT.
         LB        1,HWNAME,3      GET FIRST BYTE
         CI        1,G'+'          DOES IT INDICATE POSITIVE CONVERSION
         BEQ       CNUN         YES-BIT 1 OF R3 IS OK THEN
         CI        1,G'-'          DOES IT INDICATE NEGATIVE CONVERSION
         BNE       CNUO         NOT A - , MUST BE NUMERIC
         SBR       3,1             SHOW RESULT TO BE NEGATED
CNUN     ABR       3,31            SKIP PAST + OR - OR LAST BYTE
         LB        1,HWNAME,3      GET ONE BYTE
CNUO     CI        1,G' '          HAVE WE FOUND A SPACE (TERMINATOR)
         BEQ       CNUS1        YES-NO MORE BY TES THEN
         CI        1,G'0'          IS CHARACTER LESS THAN NUMERIC
         BLT       CNUO1        YES, ILLEGAL CHARACTER
         CI        1,G'9'          IS CHARACTER GREATER THAN NUMERIC
         BCF       GT,CNUO2        NO, GO PROCESS THE DIGIT
         IFT       ULC,SKIP                                     *JCB*
         ZBR       R1,26           CONVERT TO UPPER CASE        *JCB*
SKIP     ANOP                                                   *JCB*
         CI        1,G'A'          IS CHARACTER LESS THAN 'A'
         BLT       CNUO1        YES, ILLEGAL CHARACTER
         CI        1,G'F'          IS CHARACTER GREATER THAN 'F'
         BCF       GT,CNUO2        NO, GO PROCESS THE DIGIT
         SUI       1,G'A'-X'A'     YES, MAKE G'A' EQUIVALENT TO X'A'
         BU        CNUQ            GO SEE IF CHARACTER IS AN 'H' OR 'W'
*                                  FOLLOWED BY A SPACE
CNUO1    CEQU      $               ILLEGAL CHARACTER USED AS D  ESCT-32
         SBM       G'N'-X'40',HWERRF    MARK N ERROR
         ABM       31,HWERCT       COUNT THE ERROR
         BU        CNUU            MAKE WAY OUT AFTER THIS ERROR
CNUO2    CEQU      $               CHARACTER IS LEGAL.  PROCES  ESCT-32
         SUI       1,G'0'          CONVERT ASCII 0 TO HEX 0
         CI        1,X'9'          WAS RESULT ABOVE 9 DIGIT
         BLE       $+2W         NO-THEN R1 IS GOOD NUMBER
         SUI       1,-G'0'+G'A'-X'A'  MAKE G'A' EQUIVALENT TO X'A'
         CAR       2,1             COMPARE INPUT NUMBER TO RADIX
         BGE       CNUQ         INPUT LARGER THAN RADIX
*        START CONVERSION TECHNIQUE-IT IS A MULTIPICATION BY SUCCESSIVE
*        ADDITION AND SHIFTING OF THE DOUBLE-LENGHT ACCUMULAND
         STW       1,CNUB+1W       INPUT DIGIT LOW IN DOUBLEWORD
         LI        1,-6            MAXIMUM OF 6 BIT MULTIPLIER
         ZR        6               CLEAR SCRATCH REGISTERS
         ZR        7               TO RECEIVE PRODUCT
CNUP     SLLD      6,1             INCREASE MULTIPLY-PRODUCT REGISTERS
         SLL       2,1             MULTIPLIER TO NEXT POSITION
         TBR       2,25            CHECK ONE BIT OF MULTIPLIER
         BNS       $+2W         NO BIT ON-DONT ADD MULTIPLICAND
         ADMD      6,CNUA          BIT IS ON-ADD MULTIPLICAND TO PRODUCT
         BIB       1,CNUP          DO CHECK AND ADDITION 6 TIMES
         ADMD      6,CNUB          ADD IN LATEST CONVERSION DIGIT
         STD       6,CNUA          NEW ACCUMULATED CONVERTAND
         SRL       2,6             RESTORE RADIX VALUE
         BU        CNUN            GO GET NEXT INPUT CHARACTER
CNUQ     LB        4,HWNAME+1,3    CHECK NEXT BYTE
         CI        4,G' '          IS IT A SPACE
         BEQ       CNUS         YES-THEN A LEGAL TERMINATION
CNUR     SBM       G'N'-X'40',HWERRF  MARK N ERROR
         ABM       31,HWERCT       COUNT THE ERROR
         BU        CNUU            MAKE WAY OUT AFTER THIS ERROR
CNUS     ADI       1,G'A'-X'A'     RESTORE ALPHA CHARACTER VALUE
CNUS1    LI        2,-6            NUMBER OF VALID TERMINATORS.
         CAMB      1,CNUC+6,2      CHECK AGAINST MULTIPLYING TERMINATORS
         BEQ       CNUT         WE FOUND ONE
         BIB       2,$-2W          NO FIND-SCAN REST OF LIST
         BU        CNUR            NO HIT IN ENTIRE LIST-ERROR
CNUT     LB        5,CNUD+6,2      GET NUMERIC MULTIPLIER VALUE.
         SLA       2,1             CHANGE POINTER FROM BYTE TO HALF-WORD
         LD        6,CNUA          ACCUMULATED CONVERT AND
         EXM       CNUE+6H,2       LEFT SHIFT FOR MULTIPLICATION EFFECT
         STD       6,CNUA          REPLACE MULTIPLIED CONVERTAND
CNUU     SLC       3,2             PUT MINUS SIGN FLAG INTO BIT 31
         TBR       3,31            TEST THE FLAG FOR THE NEXT BCF
         STB       3,HBCNUL        SAVE FOR OTHER PARTS OF CONSTANT
         BNS       CNUV         NOT MINUS-THEN DONT NEGATE
         LND       6,CNUA          LOAD NEGATED CONVERTAND
         STD       6,CNUA          AND RE-SAVE IT
CNUV     CEQU      $                                            ESCT-32
         LD        6,CNUA          FINAL CONVERSION RESULT
         TRSW      0               RETURN TO CALLING ROUTINE
         TITLE     READ-ONLY       RUNST, UNST
*        UNSTRING ONE WORD INTO WORK AREA HWNAME.  UNSTRINGING WILL
*        CONTINUE UNTIL A CHARACTER IS FOUND WHICH IS IN THE TERMINATOR
*        LIST# THE TERMINATOR LIST IS DESCRIBED AS ONE BYTE
*        OUTPUT IS THE UNSTRUNG NAME IN HWNAME, THE NUMBER OF
*        BYTES IN THE UNSTRUNG NAME IN R3
*        THE TERMINATOR IN R7
*        AND THE UPDATED TERMINATOR LIST IN HBSTAC
         SPACE     3
RUNST    SBR       R0,0            SET IGNORE LEADING BLANKS FLAG
         BU        $+2W            INTO THE ALTERNATE ENTRY POINT
UNST     ZBR       R0,0            CLEAR INGORE LEFT SPACES FLAG
         STW       0,UNSTS0
         STW       1,UNSTC         THE LIST OF TERMINATORS
         ZBM       INTGEN3,SPMAC   CLEAR INTERNAL3 BIT.
         SBM       UNS,SPMAC       SET UNSTRING BIT.
         ZMW       UNSTNP          ZERO NORMAL STORE POINTER
         LI        3,-MAXCHARS     NUMBER OF WORDS IN HWNAME
         LW        6,=C'    '      ASCII SPACES
         TRR       6,7             COPY SPACES TO R7
         STD      6,HWNAME+MAXCHARS,3   BLANK OUT RECEIVING AREA
         BID       3,$-1W          DO ALL WORDS OF RECIEVING ARE HWNAME
         ZR        3               COUNT OF  NUMBER OF SPACES SKIPPED
*        OR RECEIVING POINTER
         ZBR       0,0             CHECK INGORE LEFT SPACES FLAG
         BS        UNST2        BRACH IF LEFT SPACE NOT IGNORED
UNST1    ABR       3,31            INCREMENT COUNT OF NUMBER OF BLANKS
         CI        3,12            TO CHECK FOR  COMPLETELY BLANK FIELD
         BGE       UNST5        FIELD TO LONG
         LW        1,UNSTC         THE LIST OF TERMINATORS
         SBM       INSIG,HHBITS     FORCE ON THE INSIGNIFIGANT BIT FLAG
         IFF       ULC,SKIP                                     *JCB*
         BL        GBYTE           GET ONE BYTE                  AS22
SKIP     ANOP                                                   *JCB*
         IFT       ULC,SKIP                                     *JCB*
         BL        GBYT            GET ONE BYTE U/C CHAR        *JCB*
SKIP     ANOP                                                   *JCB*
         BCT       2,UNST6         FORCE TERMINATION FOR THIS CASE
         BS        UNST15       THE CHARACTER WAS A TERMINATOR
         CI        7,G' '          IS THE BYTE A SPACES
         BEQ       UNST1        IT IS STILL A SPACE
         BU        UNST3           NOT A SPACE ANDNOT A TERMINATOR
UNST15   ZBM       1,UNSTCK        NO PARAM CHECKS IF EXPANDING MAC AS19
         BS        UNST15.1                                         AS19
         CI        7,G','          A COMMA?                         AS19
         BNE       $+2W            IF NOT, SKIP                     AS19
         SBM       0,UNSTCK        ELSE SET VALID DELIM CHECK BIT   AS19
UNST15.1 CI        7,G' '          WAS THE CHARACTER A SPACE
         BNE       UNST6        NO.
         LW        2,UNSTNP        ANYTHING IN HWNAME?
         BNE       UNST6        YES--FORCE TERM.
         TBM       DUMMY,SPMAC     WAS A DUMMY UNSTRUNG?
         BNS       UNST1        NO--IT IS STILL A LEADING BLANK.
*        A DUMMY NAME FOLLOWED BY A COLON AND BLANK WERE UNSTRUNG.
         BU        UNST6           FORCE TERMINATION.
UNST2    LW        1,UNSTC         THE LIST OF TERMINATORS
         IFF       ULC,SKIP                                     *JCB*
         BL        GBYTE           GET ONE BYTE                  AS22
SKIP     ANOP                                                   *JCB*
         IFT       ULC,SKIP                                     *JCB*
         BL        GBYT            GET ONE BYTE U/C CHAR        *JCB*
SKIP     ANOP                                                   *JCB*
         BS        UNST6        A TERMINATOR WAS FOUND
*        FALL THRU WHEN ALL DEFINED TERMINATORS HAVE BEEN CHECKED
*        AND INPUT BYTE WAS NOT ONE OF THEM
UNST3    ZBM       0,UNSTCK        CLEAR-PARAM LAST(DELIM CORRECT)  AS19
         TBM       INTGEN3,SPMAC   HAS AN INT SYM BEEN PROCESSED.
         BNS       UNST3.5      NO.
         TBM       CALLUS,MACSTATE ARE WE IN A MACRO CALL?
         BS        UNST3.2      YES.
         TBM       RSCAN,MACSTATE   ARE WE IN A REPEAT SCAN?
         BS        UNST3.5      YES.
         LW        4,UNSTNP        MWNAME INDEX.
         SUI       4,2             BACK IT UP BY 2 BYTES.
         STW       4,UNSTNP        RESTORE HWNAME INDEX.
         LW        4,MUNSTS6       SAVE MUNSTS6
         LA        6,MGBD          ADDR OF ASCII INT SYM.
         STW       6,MUNSTS6       ADDR OF ASCII INT SYM
UNSTC3   LW        2,MUNSTS6       ADDR OF NEXT CHAR OF INT SYM.
         ABM       31,MUNSTS6      INCR INT SYM CHAR COUNT.
         LB        6,0,2           NEXT CHAR OF INT SYM.
         CI        6,G' '          IS IT A BLANK?
         BEQ       UNSTC2       YES--FINISHED.
         LW        2,UNSTNP        HWNAME INDEX.
         CI        2,MAXCHARS      TOO MANY CHARS?
         BGE       $+2W         YES.
         STB       6,HWNAME,2      STORE CHAR IN HWNAME.
         ABM       31,UNSTNP       INCR HWNAME INDEX.
         BU        UNSTC3          DO WHOLE NAME.
UNSTC2   STW       4,MUNSTS6       RESTORE MUNSTS6
         ZBM       INTGEN3,SPMAC   CLEAR INTGEN3 FLAG
         BU        UNST3.5         CONTINUE PROCESSING
UNST3.2  BL        YEANAY             ARE WE ASSEMBLING?
         BNS       UNST2           NO.
         SBM       G'I'-X'40',HWERRF  MARK I ERROR.
         BS        UNST2        ERROR HAS OCCURRED--DON'T COUNT AGAIN
         ABM       31,HWERCT          COUNT THE ERROR.
         BU        UNST2           CONTINUE SCANNING LINE.
UNST3.5  LW        3,UNSTNP        NOT IN MACRO-NORMAL NAME POINTER
         CI        3,MAXCHARS      CHECK FOR OVERFLOW OF HWNAME AREA
         BGE       $+2W         OVER RUN-IGNORE THEM
         STB       7,HWNAME,3      PUT INPUT BYTE IN RECEIVENG AREA
         ABM    31,UNSTNP          ADVANCE THE POINTER
         BU        UNST2           GO GET A NEW BYTE FROM INPUT STREAM
UNST5    ZR        3               SHOW THAT THERE ARE NO CHARACTERS FOU
UNST6    LI        2,X'FF00'       MASK FOR TERMINATOR STACKING
         ANMW      2,HBSTAC        THROW OUT OLD STACK ITEMS
         ORR       7,2             MERGE IN THE LATEST TERMINATOR
         SRC       2,8             PUT IT ON LEFT OF STACK
         STW       2,HBSTAC        UPDATED TERMINATOR STACK
         ZBM       UNS,SPMAC       CLEAR UNSTRING BIT.
         BU        *UNSTS0         RETURN
         TITLE     READ-ONLY       GBYTE
*
* (C) COPYRIGHT 1983 ENCORE COMPUTER CORPORATION
*     ALL RIGHTS RESERVED
*
GBYTE    SBR       R6,0            SET FLAG FOR UPPER CASE CONVERT  AS22
         BU        GBYT.1          SKIP INSTRUCTION                 AS22
GBYT     ZBR       R6,0            CLEAR CONVERT FLAG, NO CONVERSIONAS22
GBYT.1   ZBR       R0,1            ASSUME NO TERMINATOR FOUND
         ZBR       R0,2            CC2 OFF
         STW       R0,GBYX         SAVE R0
         STW       1,GBYC          TERMINATOR LIST
         ZBM       DUMMY,SPMAC     CLEAR DUMMY ARGUMENT FLAG.
GBYJ     TBM       REUNSTF,MACSTATE CHEK FLAG FOR MIDDLE OF CHARACTER EX
         BS        MGB9         CONTINUE WITH THE CHARACTER STREAM
         LB        1,HBIBYI        GET THE POINTER TO THE LINE IN USE
         CI        1,72            CHECK FOR LINE OVERSCAN
         BLT       GBYS         NOT AT THE END OF THE LIME
         LI        1,80            OVERRUN THE COUNT
         STB       1,HBIBYI
         LI        7,G'" '         FEED AN ASCII SPACE FOR OVER RUN
         ZBM       UNSTFLAG,MACSTATE  PROCESSING A DUMMY NAME?
         BS        MGB2         YES--GO FINISH DUMMY NAME PROCESSING.
         BU        GBYN            FORCE A TERMINATE AND THEN RETURN
GBYS     LB        R1,HBIBYI       THE READ IN POINTER AGAIN
         ABM       7,HBIBYI        ADVANCE THE READING POINTER
         LB        R7,IN,R1        GET BYTE FROM INPUT IMAGE
         TBR       R6,0            IS CONVERSION FLAG SET           AS22
         BNS       GBYS.1          BRANCH IF NOT CONVERTING         AS22
         CI        R7,X'60'        IS CHARACTER LOWER CASE?         AS22
         BLT       GBYS.1          BRANCH IF NOT LOWER CASE         AS22
         SUI       R7,X'20'        CONVERT TO UPPER CASE            AS22
GBYS.1   TBM       REUNSTF,MACSTATE CHEK FLAG FOR MIDDLE OF CHAR    AS22
         BS        MGB6         GIVE UP THE PARAMTER NUMBER CHARACTER
GBYL     TBM       UNSTFLAG,MACSTATE   CHECK FOR PERFORMING DUMMY NAME
         BS        MGB2         GO WORK ON THE DUMMY NAME
         TBM       ESCAPE2,HHBITS  IS THIS ESCAPED
         BS        GBYL2        YES-THEN DONT ALLOW CODE SENSITIVITY
         CI        7,X'25'         CHK FOR START MACRO DUMMY ARGUMENT
         BEQ       MGB1         IT IS ONE
GBYLL    TBM       CALLUS,MACSTATE ARE WE CURRENTLY IN A REAL MACRO CALL
         BNS       GBYL2        NO-PASS ANY CHARACTER OUT
         CI        7,G'";'         IS IT AN CONTINUATION CHARACTER
         BEQ       GBYL3        YES-DONT COPY TO THE MACRO STORE STAC
         CI        7,G' '
         BNE       GBYL1.4      NOT SPACE OR ;
         ZBM       INSIG,HHBITS    CHECK WHETHER THIS SPACE TO BE IGNORE
         BS        GBYM         THIS IS AN INSIGNIFIGANT SPACE
GBYL1.4  TBM       INTGEN3,SPMAC   WAS AN INT SYM UNSTRUNG?
         BS        GBYL3        YES--DON'T COPY INTO MACRO STORAGE.
GBYL2    BL        MBYT            COPY THE CHARACTER OUT FOR PROTOTYPE
GBYL3    BL        PBYT
         ZBM       ESCAPE2,HHBITS  ZERO ESCAPED CHARACTER COMING FLAG
         BS        GBYU         PREVIOUS CHAR WAS THE ESCAPE ONE (")
         IFT       CAID,SKIP                                    *CAID*
         TBM       INSTAB,HHBITS   IGNORE ; OR " IF STAB ENTRY  *CAID*
         BS        GBYM            SKIP CHECK                   *CAID*
SKIP     ANOP                                                   *CAID*
         CI        7,G'";'         ; IS THE CONTINUATION FLAG
         BEQ       GBYW         BRANCH IF A CONTINUATION CHARACTER FO
         CI        7,G'""'         CHECK FOR ESCAPE TRIGGER CHARACTER
         BEQ       GBYK         IT IS AN ESCAPE CHARACTER
GBYM     ZBM       INSIG,HHBITS    SHOW THAT WE HAVE FOUND A NON-SPACE
         LW        6,GBYC          USERS TERMINATION FLAG
         BL        TERMCHK         GO CHECK FOR A TERMINATOR CHARACTER
         BNS       $+2W
GBYN     SBM       1,GBYX          IT WAS A TERMINATOR-MARK IT TO CALLER
         BU        GBYZ            RETURN
GBYK     SBM       ESCAPE2,HHBITS   SET ESCAPED CHARACTER COMING FLAG
         TBM       CALLUS,MACSTATE ARE WE IN MACRO CALL
         BS        GBYM            YES, IGNORE ESCAPE CHAR ON CALL
         BU        GBYJ            GO GET THE NEXT CHARACTER TO ESCAPE
GBYW     BL        INPT            RELEASE IMAGE AND GET NWXT ONE
         SBM       COMMENT,MACSTATE  INDICATE THZT WE ARE NOT IN COMMENT
         ZR        1               THE READ-IN POINTER
GBYY     CI        1,72            MAXIMUM USABLE BYTES PER IMAGE
         BGE       GBYW         YOU HAVE SCANNED BEYOND END
         LB        7,IN,1          GET BYTE FROM CONTINUATION IMAGE
         ADI       1,1             ADD 1 TO THE READ-IN POINTER
         CI        7,G' '          CHECK FOR A SPACE
         BEQ       GBYY         STILL A SPACE KEEP SCANNING
         STB       1,HBIBYI        SAVE THE READIN POINTER FOR THE NEXT
         BU        GBYL            CHECK THE NON-SPACE CHARACTER
GBYU     ANMW      7,=X'3F'        MASK THE BYTE TO BE ESCAPED
GBYZ     TRR       7,6             COPY THE CHARACTER INTO R6 ALSO
         ZBM       INSIG,HHBITS    FORCE OFF THE INSIGNIFIGANT BIT FLAG
         BU         *GBYX          RETURN
         TITLE     READ-ONLY       MGB00
MGB00    LW        1,STERCONT      MESSAGE TO SAY ERROR FOUND
         BL        ABORTM         WRITE MESSAGE AND ABORT
MGB1     ZBM       1,UNSTCK       CLEAR 'EXPANDING MACRO' BIT     AS19
         TBM       EXPAND,MACSTATE   % FOUND, EXPANDING MACRO?
         BS        MGB5         YES
         TBM       DEFMBODY,MACSTATE   ARE WE IN A MACRO BODY
         BNS       GBYLL        NO-THEN IGNORE ANY CONTROL FROM %
         BL        MBYT            CPY OUT TO MACRO STORAGE
         LW        4,=C'    '      ASCII SPACES
         STW       4,MUNSTA
         STW       4,MUNSTA+1W     BLANK OUT NAME RECEIVING AREA
         ZMW       MUNSTAP         CLEAR THE POINTER TO THE NAME TABLE
         SBM       UNSTFLAG,MACSTATE    TURN ON DUMMY NAME UNSTRINGING G
         BU        GBYJ            GO GET ANOTHER CHARACTER.
MGB2     ZBM       ESCAPE2,HHBITS  WAS PRECEEDING CHAR A ?
         BNS       MGB21        NO-THEN CHARACTER IS NOT TO BE ALTERE
         ANMW      7,=X'0000003F'  ESCAPE MASK FOR THE CHARACTER
         BU        MGB3            GO PUT THE CHAR INTO THE NAME AREA
MGB21    CI        7,G'";'         ; IS THE CONTINUATION FLAG
         BEQ       GBYW         GO GET THE NEXT CARD
         CI        7,G'""'         CHECK FOR ESCAPE TRIGGER CHARACTER
         BEQ       GBYK         SET FLAG SO NEXT CHARACTER GETS HIT
         LW        6,GBYC          THE USERS TERMINATOR LIST
         BL        TERMCHK
         BS        MGB4         A TERMINATOR WAS FOUND
         CI        7,X'25'         CHK FOR START MACRO DUMMY ARGUMENT
         BEQ       MGB4         IMPLIED CONCATENATION-TERMINATE DUMMY
         CI        7,G'":'         CHK CONCATENATION SIGNAL CHARACTER
         BEQ       MGB4         TERMINATE THE DUMMY NAME
MGB3     LW        1,MUNSTAP       POINTER TO NAME STORAGE
         CI        1,8             LIMIT ON NUMBER OF CHARACTER IN A NAM
         BGE       $+2W         DONT STORE IF BEYOND THAT LIMIT
         STB       7,MUNSTA,1      SAVE THIS CHARACTER FOR THE NMAE
         ABM       31,MUNSTAP      ADVANCE THE STORE POINTER
         BU        GBYJ            GO GET ANOTHER CHARACTER.
MGB4     STB       7,MGBS7         THE SAVED TERMINATION CHARACTER
         LD        4,MUNSTA        THE NAME THAT WAS UNSTRUNG
*        CONVERT NAME IN R4+R5  TO POSITIONAL NOTATION IN STACK
         LA        R1,STACK        ADDRESS OF ARGUMENT STACK
         ZR        R7              USE AS POSITIONAL COUNTER
EMPH1    CAMW      R1,STACKP       IS ANYTHING IN THE STACK?
         BEQ       EPHEM5       NO.
EPHEM4   CAMW      R4,0W,R1        CHECK WORD 1 AGAINST NEW NAME
         BNE       $+3W         NO MATCH
         CAMW      R5,1W,R1        CHECK WORD 2 AGAINST NEW NAME
         BEQ       EPHEM8       WE HAVE FOUND THE NAME
         ABR       R7,31           NEXT ARG NUM
         BID       R1,EMPH1        INCR STACK PTR.
EPHEM5   ABM       28,STACKP       INCREMENT THE STACK POINTER
         STW       R4,0W,R1        1ST WORD OF NEW NAME
         STW       R5,1W,R1        2ND WORD OF NEW NAME
         STB       R7,DEFCNT       SAVE HIGHEST PAR #
         ABM       7,DEFCNT        MAKE PAR # INTO COUNT
EPHEM8   BL        MBYT            PUT THIS BYTE IN PROTOTYPE STORAGE
         SBM       DUMMY,SPMAC     INDICATE THAT A DUMMY ARGUMENT
*                                  HAS BEEN UNSTRUNG.
         LB        7,MGBS7         THE SAVED TERMINATION CHARACTER
         ZBM       UNSTFLAG,MACSTATE   TURN OFF DUMMY NAME UNSTRINGING F
         CI        7,G'":'         CHK CONCATENATION SIGNAL CHARACTER
         BEQ       GBYJ         CONCATENATION WANTED-GET NEXT CHAR.
         CI        7,X'25'         CHK FOR START MACRO DUMMY ARGUMENT
         BEQ       MGB1         IMPLIED CONCATENATION-GO GET NEW DUMM
         BL        MBYT            PLACE THE TERMINATOR INTO PROTOTYPE S
         SBM       2,GBYX          INDICATE THIS IS A TERMINAFGOR
         BU        GBYN            TO THE OUTSIDE AFTER FLAGGING TERMINA
MGB5     SBM       1,UNSTCK        SET EXPANDING MACRO BIT         AS19
         SBM       REUNSTF,MACSTATE  SET FLAG FOR MIDDLE OF CHARACTER EX
         BS        GBYLL        % WAS JUST A PASSED CHARACTER.
         BU        GBYS            GO GET THE ARGUMENT NUMBER
*                                  GET THE POINTER FOR THIS ARGUMENT NUM
MGB6     TBM       INTGEN3,SPMAC   HAS AN INT SYM ALREADY BEEN PROCESSED
         BNS       $+3W         NO--OK.
         TBM       CALLUS,MACSTATE ARE WE IN A MACRO CALL?
         BS        $+2W         YES--DON'T WIPE OUT INSYMARG.
         STB       7,INSYMARG      STORE % NUM IN INSYMARG.
         MPI       R6,3D           MAKE PAR # DOUBLE WD INDEX
         LW        R1,MPP          PAR STACK POINTER FOR THIS LEVEL
         LW        R1,0W,R1        PAR BASE ADDR FOR THIS LEVEL
         ADR       R7,R1           ADD IN PARAMETER ADJUSTMENT
         LB        R4,0B,R1        GET 1ST CHAR OF SYMBOL
         CI        R4,X'FF'        IS INTERNAL SYMBOL DEFINED
         BEQ       MGB10           BR IF YES
         LW        R4,0W,R1        GET 1ST 4 CHARS OF NAME
         CAMW      R4,=C'    '     IS IT STILL UNDEFINED
         BNE       MGB12           BR IF DEFINED
*        PROCESS A NEW INTERNAL TAG
*        NOW MOVE IN THE NEW INTERNAL TAG INTO THE VACATED SPACE
         LW        R5,INTTAG       THE CURRENT INTERNAL TAG NUMBER
         ABM       31,INTTAG       INCR INT TAG COUNT.
         ANMW      5,=X'0000FFFF'  LOOK AT INT SYM NUM
         BL        BTX             CONVERT TO ASCII
         SLLD     R6,24            MAKE ROOM FOR SPACES
         ORMW     R7,=X'00202020'  MERGE IN SPACES
         STD       6,MGBD          STORE IT AWAY.
         STW       R6,0W,R1        PLUG IN THE NEW ITEM
         STW       R7,1W,R1        PLUG IN NEW ITEM
         LW        R6,=C'    '     BLANKS
         TRR       R6,R7           WILL DO BOUBLE WORD STORE
         STD       R6,MGBD+1D
         STD       R6,MGBD+2D
         STD       R6,MGBD+3D
         STD       R6,1D,R1        PUT IN BLANKS
         STD       R6,2D,R1        PUT IN BLANKS
         LI        6,X'21'         INT SYM LEAD P/O CHAR.
         STB       6,MGBD          STORE IT AWAY.
         LI       R6,X'FF'         INT SYM TABLE LEAD CHAR
         STB      R6,0W,R1         PUT IN STACK FOR REPLACEMENT PARS
MGB10    SBM       INTGEN,MACSTATE    INDICATE INTERNAL LABEL
MGB12    TBM       INTGEN3,SPMAC   HAS AN INT SYM ALREADY BEEN PROCESSED
         BNS       MGB12.0       NO
         TBM       CALLUS,MACSTATE ARE WE IN A MACRO CALL?
         BS        MGB12.1+1W   YES--DON'T WIPE OUT INSYMVAL
         TBM       RSCAN,MACSTATE   ARE WE IN A REPEAT SCAN?
         BS        MGB12.1+1W   YES.
         LW         6,UNSTNP       HWNAME INDEX.
         SUI       6,2             BACK UP 2 CHARS.
         STW       6,UNSTNP        RESTORE HWNAME INDEX.
         LW        4,MUNSTS6       SAVE MUNSTS6
         LA        6,MGBD          ADDR OF ASCII INT SYM.
         STW       6,MUNSTS6       ADDR OF INT SYM.
MGB20    LW        2,MUNSTS6       ADDR OF NEXT INT SYM CHAR.
         ABM       31,MUNSTS6      INCR INT SYM CHAR COUNT.
         LB        6,0,2           NEXT INT SYM CHAR.
         CI        6,G' '          IS IT A BLANK?
         BEQ       MGB27        YES--WE ARE FINISHED.
         LW        2,UNSTNP        HWNAME INDEX.
         CI        2,MAXCHARS      TOO MANY CHARS?
         BGE       $+2W         YES.
         STB       6,HWNAME,2      STORE INT SYM CHAR IN HWNAME.
         ABM       31,UNSTNP       INCR HWNAME INDEX.
         BU        MGB20           DO ALL  OF INT SYM NAME.
MGB27    STW       4,MUNSTS6       RESTORE MUNSTS6.
         ZBM       UNS,SPMAC       TRICK GBYT INTO THINKING IT WAS NOT
*                                  CALLED BY UNST.
         BU        MGB12.1+1W
MGB9     ZBM       REUNSTF,MACSTATE  ZERO MORE BYTES IN THE STRING FLAG
         LW        2,MUNSTS6       MACRO ARGUMENT POINTER
         ABM       31,MUNSTS6      ADVANCE THE PICKUP POINTER
         LB        7,0,2           GET ON BYTE OF MACRO EXPANSION
         TBM       ESCAPE2,HHBITS  CHECK FOR BEING AN ESCAPED CHARACTER
         BS        MGB11        IT IS BEING ESCAPED
         CI        7,G' '          CHECK FOR A NON-SPACE CHARACTER
         BEQ       $+2W         IT IS STILL A SPACE OR IS AGAIN
         SBM       0,MUNSTS6       FINISH LEADING SPACES
         CI        7,G','          , ENDS A MACRO STRING
         BEQ       GBYJ         END OF THE MACRO SUBSTITUTION STRING
         TBM       0,MUNSTS6       CHECK IF WE ARE STILL IN LEADING SPAC
         BNS       MGB11        DONT CHECK ANY MORE MACRO STRING TERM
         CI        7,G' '          SPACE CAN END STRING ALSO
         BEQ       GBYJ         END OF THE MACRO SUBSTITUTION STRING
MGB11    SBM       REUNSTF,MACSTATE  SET  MORE BYTES IN THE STRING FLAG
         BU        GBYL            THE FOUND SUBSTITUTION CHARACTER
MGB12.0  TBM       CALLUS,MACSTATE ARE WE IN A MACRO CALL?
*        BS        MGB12.05     YES.
         TBM       RSCAN,MACSTATE  ARE WE IN A REPEAT SCAN?
         BS        MGB12.1      YES.
*        LW        6,UNSTNP        HWNAME INDEX.
*        BEQ       MGB12.1      NOTHING IN HWNAME--OK.
         ZBM       UNS,SPMAC       TRICK GBYT INTO THINKING IT WAS NOT
*                                  CALLED BY UNST.
         BU        MGB12.1+1W
MGB12.05 LW        6,UNSTNP        ANYTHING IN AWNAME ?
         BEQ       MGB12.1      NO.
         BL        YEANAY             ARE WE ASSEMBLING?
         BNS       $+4W            NO.
         SBM       G'I'-X'40',HWERRF MARK  I  ERROR.
         BS        $+2W         ERROR HAS OCCURRED--DON'T COUNT AGAIN
         ABM       31,HWERCT         COUNT THE ERROR.
         ZMW       UNSTNP            ZERO HWNAME INDEX.
MGB12.1  SBM       INTGEN3,SPMAC   SET INTERNAL3 BIT.
         LW        R6,0W,R1        GET 1ST 4 CHARS OF NAME
         LW        R7,1W,R1        GET 2ND 4 CHARS OF NAME
         STD       6,MGBD          STORE IT AWAY.
         SRL       R6,24           ISOLATE 1ST CHAR
         CI        R6,X'FF'        SEE IF INTERNAL SYMBOL
         BNE       $+3W            BR IF NOT
         LI        6,X'21'         INT SYM LEAD P/O CHAR.
         STB       6,MGBD          STORE IT AWAY.
         LD        R6,1D,R1        GET 2ND 8 CHARS OF PARM
         STD       R6,MGBD+1D
         LD        R6,2D,R1        GET 3RD 8 CHARS OF PARM
         STD       R6,MGBD+2D
         LW        R6,=C'    '     BLANKS
         TRR       R6,R7           WILL DO BOUBLE WORD STORE
         STD       R6,MGBD+3D
         LA        4,MGBD          BASE ADDRESS OF INTERNAL LABEL
         STW       4,MUNSTS6       ADDRESS FOR RETRIEVAL
         TBM       UNS,SPMAC       DID WE COME FROM UNST.
         BNS       MGB14        NO
         TBM       RSCAN,MACSTATE  ARE WE IN A REPT SCAN
         BNS       MGB13        NO.
         LI        7,G'%'          DUMMY LEAD CHARACTER.
         BL        MBYT            COPY TO STORAGE.
         LB        7,INSYMARG      INT SYM % NUMBER.
         BL        MBYT            COPY TO STORAGE.
         LI        7,G'%'          DUMMY LEAD CHARACTER.
MGB12.5  LW        2,UNSTNP        HWNAME INDEX.
         CI        2,MAXCHARS      TOO MANY CHARACTERS?
         BGE       $+2W         YES.
         STB       7,HWNAME,2      STORE CHAR IN NAME WORD
         ABM       31,UNSTNP       INCR HWNAME INDEX
         ABR       2,31            INCR HWNAME INDEX IN REG 2.
         CI        2,MAXCHARS      TOO MANY CHARACTERS?
         BGE       $+3W         YES.
         LB        7,INSYMARG      INT SYM % NUMBER.
         STB       7,HWNAME,2      STORE IN HWNAME
         ABM       31,UNSTNP       INCR HWNAME INDEX.
MGB12.7  LW        2,MUNSTS6       ADDR OF NEXT CHAR OF ASCII INT NUM
         ABM       31,MUNSTS6      INCR ADDRESS
         LB        7,0,2           PICK UP NEXT CHAR
         CI        7,G' '          IS IT A BLANK ?
         BEQ       MGB12.9      YES--FINISHED.
         BL        PBYT            COPY CHAR TO PRINT BUFFER.
         BU        MGB12.7         GO GET NEXT CHAR.
MGB12.9  ZBM       REUNSTF,MACSTATE  CLEAR INT SYM UNSTRING FLAG.
         BU        GBYJ            CONTINUE SCANNING LINE.
MGB13    TBM       CALLUS,MACSTATE ARE WE IN A MACRO CALL?
         BNS       MGB13.5       NO.
         LW        7,UNSTNP         ANYTHING IN HWNAME?
         BEQ       MGB13.5       NO--OK.
         BL        YEANAY          ARE WE ASSEMBLING?
         BNS       MGB12.7      NO.
         SBM       G'I'-X'40',HWERRF  MARK  I ERROR.
         BS        MGB12.7      ERROR HAS OCCURRED--DON'T COUNT AGAIN
         ABM       31,HWERCT          COUNT THE ERROR.
         BU        MGB12.7          GO PRINT OUT INT NUM.
MGB13.5  LI        7,X'FF'          INT SYM LEAD CHAR.
         BU        MGB12.5          STORE WITH % NUM INTO HWNAME & P/O.
MGB14    ZBM       INTGEN3,SPMAC    CLEAR INTERNAL3 BIT
         BU        MGB9             GO PASS OUT INT SYM NUM
TERMCHK  ZBR       0,1             CLR THE TERMINATE FLAG BIT
         TBM       ESCAPE2,HHBITS  TEST ESCAPED CHARACTER COMING FLAG
         BS        TERMCHKF     IT IS ESCAPDD-CAN NOT BE TERMINATOR
         CI        7,G'@'          CHECK FOR BEING ABOVE @
         BGE       TERMCHKF     IF SO CAN NOT BE A TERMINATOR
         CI        7,G'" '         CHECK FOR BEING BELOW SPACE
         BLT       TERMCHKF     IF SO CAN NOT BE A TERMINATOR
         TRR       7,5             GET THE DATA BYTE IN OUR RANGE OF TER
         ZBR       5,26            KNOCK OFF AN EXTRANEOUS BIT
         ORMH      5,TERMCHKS      MAKE UP A VARIABLE SHIFT INSTRUCTION
         EXRR      5               EXECUTE THE VARIABLE SHIFT TO GET A B
*        OF THE TERMINATOR MASK WORD INTO BIT POSITIONN 0
TERMCHKS SLL       6,0             THIS INSTRUCTION IS FILLED WITH A COU
         TBR       6,0             CHECK MOST SIGNIFIGANT BIT
         BNS       TERMCHKF     NO TERMINATE IF IT IS NOT A 1
         SBR       0,1             SET THE TERMINATE FLAG BIT
TERMCHKF TRSW      0               RETURN
         TITLE     READ-ONLY       INPT
* RELEASE IMAGE AND GET NEXT ONE
         SPACE     3
*
* (C) COPYRIGHT 1983 ENCORE COMPUTER CORPORATION
*     ALL RIGHTS RESERVED
*
INPT     STW       0,INPTS0
         LI        7,X'FF'         FLAG TO INDICATE END OF SI RECORD
         ZBM     COMMENT,MACSTATE  0= * IN COL 1, 1=ELSE
         BNS       INPTM2       IT WAS JUST A COMMENT LINE,DONT COPY
         TBM       DEFMBODY,INPTSTAT   CHECK FOR SCANNING PROTOTYPE
         BS        INPTM1       SEND EOSI BYTE
         TBM       RSCAN,INPTSTAT  ARE WE LOOKING FOR END OF REPT GROUP
         BNS       INPTM2       DONT SEND EOSI BYTE
INPTM1   BL        MBYT            STORE TERM CODE
INPTM2   BL        RELEAS          PRINT OUTPUT
         LW        4,HWERRF        ARE THERE ANY UNPRINTED ERRORS?
         BEQ       INPT0        NO.
         ZBM       IMIN,HHBITS     INDICATE NO IMAGE READY.
         BU        INPTM2          GO PRINT ERRORS.
INPT0    LH        4,MACSTATE      THE LATEST MACRO STATE
         STH       4,INPTSTAT      THE LATE MACRO STATE(SLOW RISE AND FA
         TBM       MACREP,MACSTATE  CHECK   A REPEAT WITHIN AN EXPANSION
         BNS       INPTM3       WE DO NOT HAVE A REPT WITHIN AN EXPAN
         LW        4,LEVEL         IS THIS STILL AT THE REPEAT LEVEL
         BEQ       INPTM4       YES-NO EXPANSIONS HAVE OCCURRED SINCE
INPTM3   TBM       EXPAND,MACSTATE   CHECK IF EXPANSION WANTED
         BS        INPT3        YES-THEN GET LINE FROM PROTOTYPE
INPTM4   TBM       RPTGEN,MACSTATE CHECK FOR A PASS FROM STORED CODE
         BS        INPTR1       MUST SEND REPEATED CODE TO ASSEMBLER
         LW        3,HAIN          BASE ADDRESS OF RECEIVING AREA
         BL        READ            INPUT 20 WORDS (4CH/W) TO AREA IN
         STW       7,HWLICT
INPT1    ZMB       HBIBYI          INITIALIZE CARD UNSTRING COUNTER
         SBM       IMIN,HHBITS     INDICATE BUFFER IMAGE READY
         LB        1,HBLABS        GET ABSOLUTE/RELATIVE MODE FLAG
         LW        2,HWLSTR,1      FETCH THE PROPER PROGRAM COUNTER
         STW       2,HWLSTS        STATICIZED PROGRAM COUNTER
         BU        *INPTS0
INPT3    LW        R3,MPP          BASE ADDRESS  FOR STACK MANIPULATION
         ADI       R3,1W           POINTER TO CURRENT PROTOTYPE POINTER
INPT4    LI        2,-72           NUMBER OF CHARACTERS PER LINE
INPT6    LW        R1,0W,R3        POINTER TO PROTOTYPE PART IN USE
         ABM       31,0W,R3       ADVANCE THE POINTER PAST JUST GOTTEN B
*!!!!!!!!SEA!!!!!!!!!!!!!!!!!!!!!!!MACRO!IN!EXT!ADDR!!!!!!!!!!!!S880752
         LB        R4,0B,R1       GET THE PROTOTYPE BYTE
*!!!!!!!!CEA!!!!!!!!!!!!!!!!!!!!!!!CLEAR!EXT!MODE!!!!!!!!!!!!!!!S880752
         CI        4,X'FF'         CHECK FOR EOSI FLAG
         BEQ       INPTM9       END OF SI IMAGE
         STB       4,IN+72,2       STORE PROTO BYTE FOR INPUT LINE HANDL
         BIB       2,INPT6         ADVANCE STORAGE POINTER AND GET NEW B
         ABR       1,31            ADVANCE STORAGE POINTER
*!!!!!!!!SEA!!!!!!!!!!!!!!!!!!!!!!!MACRO!IN!EXT!MEMORY!!!!!!!!!!S880752
         LB        R4,0B,R1       GET THE PROTOTYPE BYTE
*!!!!!!!!CEA!!!!!!!!!!!!!!!!!!!!!!!CLEAR!EXT!MODE!!!!!!!!!!!!!!!S880752
         CI        4,X'FF'         CHECK FOR EOSI FLAG
         BNE       INPTM10      DONT ADVANCE COUNT IF NOT EOSI
         ABM       31,0,3          ADVANCE POINTER PAST LONG RECORD
         BU        INPTM10         ALMOST DONE
INPTM9   LI        4,G' '          ASCII SPACE
         STB       4,IN+72,2       BLANK OUT IMAGE AREA
         BIB       2,$-1W          DO ALL 72 COLUMNS LEFT
INPTM10  LI        1,-80
         LW        4,=C'    '      ASCII SPACES
         STW       4,MPBUF+80,1    BLANK THE AUXILIARY PRINT BUFFER
         BIW       1,$-1W          ALL OF IT
         LW        7,HWLICT        GET THE LINE NUMBER OF THE OUTER CALL
         BU        INPT1           ALL DONE WITH IT
INPTR1   LA        3,HWREPSP       REPEATED SPACE
         BU        INPT4           FINISH LIKE A MACRO GET
         TITLE     READ-ONLY       IGEN, CEXT
* BYTE GENERATION ROUTINE. PUT BYTE RIGHT JUSTIFIED IN R6 AND IT WILL
* BE PLACED AT THE NEXT AVAILABLE LOCATION AS SHOWN BY THE INSTRUCTION
* COUNTER HWLSTR WHICH WILL BE INCREMENTED BY ONE UPON RETURN.
         SPACE
IGEN     TBM       CONDSCAN,MACSTATE   CHECK FOR NOASSEMBLY FLAG
         BS        IGEP         IF ON DONT BOTHER WITHOUTPUT
         TBM       DEFMBODY,MACSTATE     CHECK WHETHER WE IGNORE THIS
         BS        IGEP         NO ASSEMBLY DURING PROTTOTYPE BODY
         TBM       RSCAN,MACSTATE     CHECK FOR BEING IN A REPEAT SCAN
         BS        IGEP         NO GEN FOR A REPEAT SCAN
         SBM       CVFL,HHBITS     SIGNAL TO PRINT PROGRAM COUNTER
         LI        1,1
         ARMB      1,HBBBCT        INCREMENT GEN BYTE COUNT
         LB        1,HBLABS        POINTER TO PROG COUNTER
         LI        4,3             MASK FOR LAST 2 BITS
         LMW       2,HWLSTR,1      POINTER TO BYTE POSITION
         STB       6,HWBYTE,2      STORE INPUT BYTE IN PROPER LOC
         SBM       7,HWBYTF,2      FLAG BYTE AS BEING GENERATED
         ABM       31,HWLSTR,1     INCREMENT PROGRAM COUNTER
         STW       R0,IGENS0       SAVE RETURN ADDRESS          S920209
         BL        PCCHK           CHECK FOR PROG CNT OVERFLOW  S920209
         LW        R0,IGENS0       RESTORE RETURN ADDRESS       S920209
         LMW       2,HWLSTR,1      FETCH LAST 2 BITS
         BNE       IGEP         NOT A WORD BOUNDARY NOW
*!!!!!!!!STW!!!!!!!0,IGENS0!!!!!!!!SAVE!RETURN!ADDRESS!!!!!!!!!!S920209
         BL        RELEAS          ON A WORD BOUNDARY, PRINT IT OUT
         LW        2,HWLSTR,1      PROG COUNTER
         STW       2,HWLSTS        STATICIZE PROG COUNTER
         LW        0,IGENS0        RESTORE RETURN ADDRESS
IGEP     TRSW      0               RETURN
         SPACE     3
*        THIS ROUTINE CLEARS THE FLAGS THAT MAY HAVE BEEN SET DURING
*        THE GENERATION OF ONE LINE OF CODE.
         SPACE     3
CEXT     LI        3,-10W          NUMBER OF WORDS PER PRINT LINE (SHORT
         LW        4,=C'    '      WORD OF SPACES
         STW       4,IN,3          BLANK OUT LEFT SIDE OF PRINT LINE
         BIW       3,$-1W          BLANK WHOLE LEFT SIDE
         ZMB       DPFLAGS         CLEAR DATAPOOL FLAGS
         ZMW       HWBYTF          CLEAR INDICATORS OF BYTES GENERATED
         ZMW       HWEVAL          CLEAR ADDRESS EVALUATION AREA
         ZBM       CVFL,HHBITS     DONT WANT PROGRAM COUNTER PRINTED
         ZMB       HBBBCT          CLEAR NUMBER OF BYTES GENERATED/LINE
         TRSW      0               RETURN TO CALLER
         TITLE     READ-ONLY       RELEAS
*        MAJOR IMAGE AND OBJECT OUTPUT CONTROL ROUTINE
         SPACE     3
RELEAS   STF       0,RELEASF       PROTECT CALLERS REGISTERS
*                  BO OUTPUT FIRST
         TBM       7,HBPASS        IS THIS PASS 2
         BS        BBS0         NO, RETURN
         LB        6,HBBBCT        NUMBER OF BYTES GENERATED
         BEQ       BBS0         NO BYTES GENERATED, RETURN
         SBM       7,HBBBFB        SHOW THAT A BYTE AHS BEEN GENERATED
         ZMB       HBBS            STACK POINTER
         LW        5,HWLSTS        ADR OF LEFT MOST BYTE TO GO OUT
         EOMW      5,HWBBLS        COMPARE IT TO ONE MORE THAN LAST BYTE
*                                  TO GO OUT
         BNE       BB1.0        NOT EQUAL - WE NEED A NEW ORIGIN
         TBM       EXPLFC,HHBITS3  CHECK FOR CSECT OR NON-ZERO DSECT
         BNS       BB2             RESET - NO NEED FOR A NEW ORIGIN
         LW        5,HWLSTS        ADDR OF LEFTMOST BYTE TO GO OUT
         CAMW      5,=X'04800000'  IS IT LOCATION ZERO IN THE DSECT ??
         BNE       BB2             NO - WE DON'T NEED A NEW ORIGIN
BB1.0    CEQU      $                                            ESCT-32
         LB        6,HWLSTS        GET TYPE CODE FROM STATICIZED PROG CT
         ZBR       6,24            CLEAR DSECT/CSECT FLAG
         CI        6,TYPC          IS PROG CNTR IN COMMON MODE
         BEQ       BB6          YES, PRODUCE COMMON ORIGIN
         TBM       EXPLFC,HHBITS3  CHECK FOR CSECT OR NON-ZERO DSECT
         BS        BB1.1           SET - GEN. EXP.LDR.FUNC. CODE
         LW        7,HWLSTS        NO, GET PROG CNTR
         BL        BFA             STACK  THE 3 BYTES INTO OUT STREAM ST
         LI        6,PTO           PROGRAM ORIGIN FUNCTION CODE
         LW        1,HABS          BASE ADR OF BIN BYTE STREAM STACK
         BL        PB             PUBLISH THE BINARY STACK
         BU        BB2             CONTINUE WITH STANDARD CODES
BB1.1    CEQU      $               EXP LDR.FUNC. CODES. ADDED   ESCT-32
         LI        7,LF.SORIG      GET LDR.FUNC. SUB-CODE.
         BL        BFB             PUT 1 BYTE INTO BO STACK
         LI        7,0             LOAD DUMMY BYTE COUNT
         BL        BFB             PUT 1 BYTE INTO BO STACK
         LI        7,0             ZERO UNUSED BYTE
         BL        BFB             PUT 1 BYTE INTO BO STACK
         LB        7,HWLSTS        GET BIT FOR SECTION NUMBER
         SRL       7,7               FROM PROGRAM COUNTER
         BL        BFB             PUT 1 BYTE INTO BO STACK
         LW        7,HWLSTS        GET ADDRESS
         BL        BFA.0           STACK ADDRESS
         LI        6,EXPFUNC       GET LOADER FUNCTION CODE
         LW        1,HABS          BASE ADDR OF BIN BYTE STREAM STACK
         BL        PB             PUBLISH BINARY OUTPUT STACK
BB2      ZMB       HBBS            CLEAR STACK POSITION AND COUNTER
         LI        2,-4            MAX NO. OF BYTES TO DO AT ONE TIME
         ZR        1               SYNCRONIZE AT ZERO
         LB        6,HWEVAL        TYPE OF SYMBOL EVALUATION, IF ANY
         ZBR       6,24            CLEAR DSECT/CSECT FLAG
         CI        6,TYPC          WAS THERE A REF TO A COMMON SYMBOL
         BNE       BB2.4           NO - MUST BE NORMAL TYPE
* REFERENCE TO COMMON TYPE
         LB        6,HBBN          COMMON BLOCK NUMBER
         ABR       1,31            ICNR BIN OUTPUT STREAM STACK POINTER
         STB       6,HBBS,1        PUT BLK NO. IN STACK PRECEEDING DATA
* NORMAL TYPE
BB2.4    CEQU      $                                            ESCT-32
         TBM       EXPLFC,HHBITS3  CHECK FOR CSECT OR NON-ZERO DSECT
         BNS       BB3             NOT SET - GENERATE STANDARD CODES
         LI        3,SECTYPES-NSECTYPS  NEG NUM OF SECTION TYPES
BB2.3    CAMB      6,NSECTYPS,3    DOES TYPE MATCH THIS SEC TYPE?
         BEQ       BB2.5           YES
         BIB       3,BB2.3         LOOK AT ALL SECTION TYPES
         BU        BB3             NOT A SECTION TYPE
BB2.5    CEQU      $                                            ESCT-32
         TBM       8,HWEVAL        IS IT RELOCATABLE?
         BNS       BB3             NO - GEN OLD CODE
         TBM       DPFLG,DPFLAGS   IS THIS A DATAPOOL REFERENCE?
         BS        BB3             YES - GEN OLD CODE
*        OUTPUT EXPANDED LOADER FUNCTION CODE FOR REL.
         TBM       1,BACFLAG       IS THIS A BACW OR BACH?      EBAC-33
         BNS       BB2.5A          BRANCH IF NOT                EBAC-33
         LI        R7,X'0F'        GET LOADER FUNCTION SUB-CODE EBAC-33
         BL        BFB             PUT IN BO STACK              EBAC-33
         LB        R7,HBBBCT       GET DATA BYTE COUNT          EBAC-33
         BL        BFB             PUT BYTE IN BO STACK         EBAC-33
         LI        R7,0            LAST BYTE OF 1ST WORD UNUSED EBAC-33
         BL        BFB             PUT IN BO STACK              EBAC-33
         LI        R7,0            1ST BYTE OF ADDR IS ZERO     EBAC-33
         TBM       2,BACFLAG       ADDRESS IN CSECT?            EBAC-33B
         BNS       $+2W            NO...BRANCH                  EBAC-33B
         LI        R7,1            ELSE SHOW AS CSECT ADDRESS   EBAC-33B
         BL        BFB             PUT IN BO STACK              EBAC-33
         ABR       R1,31           INCREMENT BO STACK POINTER   EBAC-33
         LB        R6,HWBYTE+1B    GET FIRST BYTE OF ADDRESS    EBAC-33
         STB       R6,HBBS,X1      PUT IT IN BO STACK           EBAC-33
         ABR       R1,31           INCREMENT BO POINTER         EBAC-33
         LB        R6,HWBYTE+2B    GET SECOND ADDRESS BYTE      EBAC-33
         STB       R6,HBBS,X1      STORE IN BO STACK            EBAC-33
         ABR       R1,31           INCREMENT BO POINTER         EBAC-33
         LB        R6,HWBYTE+3B    GET LAST ADDRESS BYTE        EBAC-33
         STB       R6,HBBS,X1      STORE IN BO STACK            EBAC-33
         STB       R1,HBBS         STORE BYTE COUNT IN STACK    EBAC-33
         LI        R6,EXPFUNC      LOAD EXPANDED FUNCTION CODE  EBAC-33
         BU        BB5             PUBLISH OBJECT RECORD        EBAC-33
BB2.5A   LI        7,LF.SREL       GET LDR.FUNC. SUB-CODE.      EBAC-33
         BL        BFB             PUT 1 BYTE INTO BO STACK
         LB        7,HBBBCT        GET BYTE COUNT (OF DATA)
         BL        BFB             PUT 1 BYTE INTO BO STACK
         LI        7,0             ZERO UNUSED BYTE
         BL        BFB             PUT 1 BYTE INTO BO STACK
         LB        7,HBBN          LOAD SECTION NUMBER
         BL        BFB             PUT 1 BYTE INTO BO STACK
         LI        7,0             LOAD REPEAT COUNT
         BL        BFB             PUT 1 BYTE INTO BO STACK
BB2.6    TBM       7,HWBYTF+4,2    WAS A BYTE GENERATED IN THIS LOC?
         BNS       BB2.7           NOT SET - NO DATA - SKIP.
         ABR       1,31            INCREMENT BO STACK POINTER
         LB        6,HWBYTE+4,2    GET BYTE OF DATA
         STB       6,HBBS,1        STACK IT INTO BO STREAM STACK.
BB2.7    BIB       2,BB2.6         LOOP TO DO ALL 4 BYTE POSITIONS
         STB       1,HBBS          SAVE INDEX (BYTE COUNT)
         LI        6,EXPFUNC       LOAD EXPANDED FUNCTION CODE
         BU        BB5             CONTINUE (PUBLISH BINARY STACK)
BB3      TBM       7,HWBYTF+4,2    WAS A BYTE GENERATED IN THIS LOC
         BNS       BB4          NOTHING GENERATED THESE
         ABR       1,31            INCR BYTE STACK POINTER
         LB        6,HWBYTE+4,2    GET BYTE OF DATA
         STB       6,HBBS,1        STACK IT INTO OUTPUT STREAM STACK
BB4      BIB       2,BB3           LOOP TO DO ALL 4 BYTE POSITIONS
         STB       1,HBBS          NUMBER OF BYTES IN THES STACK
         LI        6,PTCR          DEFAULT TO COMMON FUNCTION CODE
         LB        7,HWEVAL        TYPE CODE
         CI        7,TYPC          IS IT COMMON TYPE
         BEQ       BB5          YES
         LI        6,PTA           SET DEFAULT TO ABSOLUTE PUNC CODE
         TBM       8,HWEVAL        NOT COMMON IS IT ABSOLUTE (BIT 8=0)
         BNS       BB5          YES
         TBM       DPFLG,DPFLAGS   CHECK FOR DATAPOOL ITEM
         BS        BB8          DATAPOOL REFERENCE- PROCESS IT
         LI        6,PTR           RELOCATABLE FUNC CODE
BB5      LW        1,HABS          ADR OF BINARY STREAM STACK
         BL        PB             PUBLISH THE BINARY OUTPUT
         LB        2,HBLABS        POINTER TO PROG COUNTER
         LW        6,HWLSTR,2      GET PROG COUNTER
         STW       6,HWBBLS        SAVE PROG CTR FOR NEXT RELEASE
         BU        BBS0            RETURN
*
*        A DATAPOOL REFERENCE IS NEEDED
*BB8     LI        1,-13B
BB8      LI        1,-16B
*        ZMB       DPBUF+13B,1     ZERO DATAPOOL BUFFER
         ZMB       DPBUF+16B,1     ZERO DATAPOOL BUFFER
         BIB       1,$-1W
         LB        1,HBBS          GET NO. OF BYTGES GENERATED
         CI        1,4             ONLY ALLOW 4 BYTES
         BEQ       BB8.1        4 BYTE GENED PROCESS
         SBM       G'A'-X'40',HWERRF SET "A" TYPE ERROR
         ABM       31,HWERCT       COUNT THE ERROR
         BU        BB5
BB8.1    ZR        1
         ZR        2
         LB        5,DPNUM
         CI        5,100           IS THIS "DATAPOOL"
         BEQ       BB8.1.0         YES
         LI        1,3             SET BUFFER FOR EXTENDED OUTPUT
BB8.1.0  CEQU      $                                            ESCT-32
         LI        7,-8
*BB8.1.1  LB        6,DPITEM,1      GET CHARACTER
BB8.1.1  LB        6,DPITEM,2      GET CHARACTER
         CI        6,G' '          SP?
         BEQ       BB8.2        YES-EXIT LOOP
         ABM       7,HBBS          NO-COUNT CHARACTER
         STB       6,DPBUF+1B,1    BYTE IN BUFFER
         ABR       2,31
         ABR       1,31            BUMP INDEX
         BIB       7,BB8.1.1
BB8.2    LI        2,-4B
BB8.2.1  LB        6,HBBS+1B+4B,2  MOVE GENED. DATA TO DPBUF
         STB       6,DPBUF+1B,1
         ABR       1,31
         BIB       2,BB8.2.1
         CI        5,100           IS THIS "DATAPOOL"
         BEQ       BB8.2.2         YES
         STB       5,DPBUF+1B,1    SAVE DATAPOOL NUMBER
         LI        5,LF.MULDP      PUT SUBTYPE IN DPBUF
         STB       5,DPBUF+1B
         LB        5,HBBS
         ADI       5,4
         STB       5,DPBUF
         ZMB       DPBUF+3B
         LA        1,DPBUF         DP BUF ADR
         ANMW      1,=X'000FFFFF'   ADR ONLY
         LI        6,EXPFUNC
         BU        BB5+1W
BB8.2.2  CEQU      $                                            ESCT-32
         LA        1,DPBUF         DP BUF ADR
         ANMW      1,=X'000FFFFF'   ADR ONLY
         LI        6,PTDP          DP LOADER FUNCTION CODE
         LB        2,HBBS          BYTE COUNT
         STB       2,DPBUF         1ST. CHARACTER OF BUFFER
         BU        BB5+1W          PUBLISH DATA
* A COMMON ORIGIN IS NEEDED
BB6      LW        7,HWLSTS        STATICIZED PROG CNTR
*                                  LEFT 3 BYTES ARE BLK NO. AND DISP
         BL        BFA             BREAK INTO 3 BYTES IN OUT STREAM STK
         LI        6,PTCO          COMMON ORIGIN FUNCTION CODE
         LW        1,HABS          BASE ADR OF BIN OUTPUT STREAM STACK
         BL        PB             PUBLISH BINARY OUTPUT STEAM
         BU        BB2             GO OUTPUT NECESSARY BYTES
BBS0     TBM       7,HBPASS        WHICH PASS IS THIS           ENSB-33
         BS        BBS01           PASS 1...BRANCH              ENSB-33
         TBM       1,EXTFLG        NON-STRUNGBACK ENTRY?        ENSB-33
         BNS       BBS01           NO...BRANCH                  ENSB-33
         TBM       ASCT.OPT,OPTION  AUTO SECTIONING ON?         ENSB-33
         BNS       BBS01           NO...BRANCH                  ENSB-33
         TBM       OPT11,OPTION    OPTION 11 SET?               ENSB-33
         BNS       BBS01           NO...BRANCH                  ENSB-33
         ZBM       1,EXTFLG        CLEAR FLAG                   ENSB-33
         ZMB       HBBS            CLEAR STACK POINTER/COUNT    ENSB-33
         LI        R7,LF.EXTRF     GET LDR. FUNC. SUB-CODE      ENSB-33
         BL        BFB             PUT 1 BYTE IN BO STACK       ENSB-33
         LI        R7,0            LOAD DUMMY BYTE COUNT        ENSB-33
         BL        BFB             PUT IN BO STACK              ENSB-33
         LI        R7,0            ZERO UNUSED BYTE             ENSB-33
         BL        BFB             PUT IN BO STACK              ENSB-33
         LW        R7,EXTWRD       GET INSTRUCTION ADDRESS      ENSB-33
         ZR        R6                                           ENSB-33
         SLLD      R6,1            SHIFT IN DSECT/CSECT BIT     ENSB-33
         TRR       R6,R7                                        ENSB-33
         BL        BFB             PUT IN BO STACK              ENSB-33
         LW        R7,EXTWRD       GET INSTRUCTION ADDRESS      ENSB-33
         BL        BFA             PUT ADDRESS IN BO STACK      ENSB-33
         LD        R4,EXTNAM       GET REFERENCED SYMBOL NAME   ENSB-33
         STD       R4,HWNAME       PUT IN POSITION FOR OUTPUT   ENSB-33
         BL        BFN.0           PUT NAME IN BO STACK         ENSB-33
         LI        R6,EXPFUNC      GET LOADER FUNC. CODE        ENSB-33
         LW        R1,HABS         BASE ADDR OF BO STACK        ENSB-33
         BL        PB              PUBLISH EXTERNAL REF RECORD  ENSB-33
BBS01    BL        POUT            MAKE UP LO OUTPUT
         BL        CEXT            CLEAR OUTPUTS SENT OUT ABOVE
         ZBM       1,BACFLAG       CLEAR BACW,BACH FLAG         EBAC-33
         ZBM       2,BACFLAG       CLEAR CSECT ADDRESS FLAG     EBAC-33B
         LF        0,RELEASF       RESTORE CALLERS REGISTERS
         TRSW      0               RETURN
         TITLE     READ-ONLY       POUT
*--------SYSTEM FLAGS CONTROLLING FORMAT AND OUTPUT DETERMINATION IN
*--------THIS ROUTINE ARE AS FOLLOWS
*                  HBAPON=0=ALLOW LISTING,1=NO LISTING
*                  HBAPEX=0'ALLOW LISTING OF EXTENSION,1=NO EXT LISTING
*                  HBPASS=0=PASS 2,ELSE PASS1
*                  HWERRF=IND ERROR TYPES SINCE LAST PRINTED
*                  HBCVFL=0=DONT PRINT PROG COUNTER, 1 MEANS PRINT IT
*                  HBIMIN=0=IMAGE ALREADY PRINTED,1 MEANS NOT PRINTED
         SPACE     3
POUT     STW       0,POUTS0        SAVE RETURN ADDRESS
         ZBM       MBUFSW,SPMAC    CLEAR PRNT BUF SWITCH BIT.
         LB        6,HBPASS        IS THIS PASS 2
         BNE       POUZ         NO, GO TO SPECIAL ERROR HANDLING
         LW        6,HWERRF        CHECK FOR ERRORS
         BNE       POUY         ERRORS ON PASS 2
         TBM       NGPRINT,HHBITS
         BNS       POUD         WE WILL LIST NON-GEN SOURCE
         BL        YEANAY          CHECK MODE
         BNS       POUT1        NOT ASSEMBLING-SUPPRESS PRINT
         TBM       NONGITEM,HHBITS2  LIST NONG SUPPRESSABLE OPERATION?
         BNS       POUD         NO
POUT1    ZBM       IMIN,HHBITS
POUD     TBM       APON,HHBITS     IS 'LIST ON'?
         BS        POUW         NO--SKIP P/O.
         TBM       NOPGEN,SPMAC    GENERATING A NOP?
         BNS       POUD0        NO.
         TBM       BNDWS4,HHBITS   EXPANDING WHILE GENERATING A NOP?
         BNS       POUD3        NO.
         BU        POUD2
POUD0    TBM       EXPAND,INPTSTAT  EXPANDING?
         BNS       POUD3        NO.
POUD2    TBM       MACPRINT,HHBITS2  EXPANSION LIST ALLOWED?
         BS        POUW         NO--SKIP P/O
POUD3    TBM       RPTGEN,INPTSTAT  GENERATING REPEATED CODE?
         BNS       POUD1        NO.
         TBM       REPPRINT,HHBITS2   REPEAT EXPANSION LIST ALLOWED?
         BS        POUW         NO-SKIP P/O
POUD1    TBM       IMIN,HHBITS     IS LISTING SUPPRESSED?
         BS        POUY         NO--GO PRINT LINE.
         TBM       CVFL,HHBITS     IS 'PRINT PROG CTR' FLAG SET?
         BNS       POUW         NO--SKIP P/O.
         TBM       APEX,HHBITS     DO WE ALLOW EXTENSION LISTING?
         BS        POUW         NO--SKIP P/O.
         SPACE     3
* AN IMAGE IS READY FOR PRINTING OR WE HAVE BYTES GENERATED AND READY
* FOR PRINTING IN THE EXTENSION IMAGE CASE OR WE HAVE ERRORS ON PASS 2
POUY     TBM       CVFL,HHBITS     SIGNAL TO PRINT PROGRAM COUNTER
         BNS       POUS         NO BYTES GENERATED
         LA        2,HWLSTS        ADR OF THE STATICIZED PROGRAM COUNTER
         LA        3,PRNT+2W+1B    CONVERTED PROG CTR GOES HERE
         ZBR       R2,0            INDICATE LOCATION CNTR. PROC.EINS-31
         BL        LOCH            ENCODE LOCATION COUNTER
         LW        2,HWEVAL        WAS THERE AN EVALUATED EXPRESSION
         BEQ       POUT.DP      NO,DON'T PRINT IT THEN
         TRR       2,3
         SRL       3,24            LOOK AT TYPE OF EXPRESSION.
         ZBR       3,24            CLEAR DSECT/CSECT FLAG
         CI        3,TYPC          IS TYPE COMMON?
         BNE       POUY.1       NO.
         LB        3,HBBN          COMMON BLOSK NUMBER.
         SLL       3,28            POSITION LEAST SIG. 4 BITS OF BLOCK
         SRL       3,12            NUMBER FOR 'OR'ING.
         ORR       3,2             OR BLOCK NUMBER INTO EVAL EXP.
         STW       2,HWEVAL        STORE INTO EVAL EXP WORD.
POUY.1   CEQU      $                                            ESCT-32
         LA        2,HWEVAL        ADR OF THE EVALUATED EXPRESSION
         LA        3,PRNT+7W       WHERE THE EVALUATED EXPRESSION GOES
         SBR       R2,0            INDICATE OPERAND PROC.       EINS-31
         BL        LOCH            ENCODE EVALUATED EXPRESSION
         TBM       DPFLG,DPFLAGS
         BNS       POUT.DP
         LI        6,G'A'
         STB       6,PRNT+7W+2B
         LB        6,DPNUM         GET DATAPOOL NUMBER
         CI        6,X'FF'         IS IT SEXT
         BNE       POUT.DP
         LI        6,G'X'
         STB       6,PRNT+7W+2B
POUT.DP  CEQU      $                                            ESCT-32
         BL        PTH1            FORMAT FINISHED CODING
POUS     LW        6,HWKSPA        SPACES
         STW       6,PRNT+1W       IN LINE NUMBER LOCATION
         LI        1,0             DEFAULT TO A SHORT LINE IF NO IMAGE
         ZBM       IMIN,HHBITS     INDICATE NO BUFFER IMAGE READY
         BS        POUU         THE IMAGE IS PRESENT AND UNPRINTED
         TBM       EXPAND,INPTSTAT  CHECK FOR BEING IN EXPANSION
         BNS       POUX         NOT IN EXPANSION
         LW        6,HWMSPBUF      SEE IF THERE ARE ANY MACRO BYTES READ
         BEQ       POUX         THERE ARE NONE
* PRINT A SHORT NUMBER OF ERRORS AND A LONG IMAGE LINE
POUU     CEQU      $                                            ESCT-32
         TBM       EXPAND,INPTSTAT  CHECK IF WE ARE EXPANDING A MACRO
         BNS       POUM         NO-THEN ALLOW USE OF TEGULAR IMAGE
         SBM       MBUFSW,SPMAC    INDICATE THAT PRNT BUFS WERE SWITCHED
         LI        1,-80           READY COUNT FOR TRANSFER OF MACRO IMA
         LW        5,MPBUF+80,1    ONE WORD OF EXPANDED MACRO IMAGE
         LW        4,IN+80,1       GET THE CURRENT IMAGE FOR TRANSLATION
         STW       5,IN+80,1       INTO THE NORMAL PRINT IMAGE AREA
         STW       4,MPBUF+80,1    BLANK OUT THE MACRO EXPANSION AREA
         BIW       1,$-4W          DO ALL 20 WORDS/80 BYTES
POUM     CEQU      $                                            ESCT-32
         ZMW       HWMSPBUF        CLEAR STORE POINTER FOR MACRO PRINT
         LW        5,HWLICT        THE BINARY LINE COUNT
         BL        CONBAD          CONVERT TO ASCII PRINTABLE DECIMAL
         TBM       EXPAND,INPTSTAT  CHECK IF WE ARE EXPANDING A MACRO
         BS        POUK         DONT LET OUT LINE NUMBER FROM MACRO
         TBM       RPTGEN,INPTSTAT   CHECK FOR BEING INSODE REPEAT GENER
         BS        POUK         DONT LET OUT LINE NUMBER FROM MACRO
         LI        1,-5            5 DIGITS IN LINE NUMBER.
         STB       6,PRNT+8B,1     STORE ASCII LINE NUMBER DIGIT.
         SLLD      6,8             POSITION NEXT DIGIT FOR PRINTING.
         BIB       1,$-2W          DO ALL OF LINE NUMBER.
POUK     CEQU      $                                            ESCT-32
         LI        1,4             INDICATE A FULL LINE OF PRINT
         LI        6,2             INDICATE MAX. OF 2 ERRORS.
* FINISH UP THE LINE AND PRINT IT. R1=LENGTH,R6=NUMBER OF ERRORS THAT
* CAN BE PRINTED ON THE LINE
POUV     LW        5,HWERRF        ALL POSSIBLE ERROR FLAGS
         BZ        ERRW1           THERE ARE NO ERRORS
         LI        4,X'FFFF'       THE FLAG TURNING OFF MASK
         LI        7,X'40'         CHAR CODE FOR ERROR BIT 0
         LI        3,+1            FIRST ERROR FLAG TO COLUMN 2
ERRW2    SRL       4,1             SO THAT WE MAY TURN OFF CHECKED FLAGS
         SLC       5,1             PLACE FLAG TO BE CHECKED IN BIT 31
         ZBR       5,31            CHECK FOR ERROR FLAG ON
         BNS       ERRW3        ERROR FLAG NOT ON
         STB       7,PRNT,3        PLACE ERROR FLAG IN PLACE
         ABR       3,31            POINT TO NEXT COLUMN
         CAR       6,3             CHECK FOR NO MORE COLUMNS TO FILL
         BGT       ERRW4        NO MORE SPACE-GIVE UP
ERRW3    ABR       7,31            GENERATE NEXT ERROR FLAG CODE
         TRR       5,5             SO WE CAN CHECK REMAINING FLAGS
         BNE       ERRW2        MORE FLAGS TO BE CHECKED
ERRW4    LMW       5,HWERRF        NO MORE FLGS ON-TRUN OFF THOSE WHICH
         STW       5,HWERRF        HAVE BEEN PRINTED-KEEP THOSE NOT
ERRW1    LW        1,QAFCBLO,1     BASE ADR AND QTY
         LB        7,PRNT+1B       LOAD FIRST ERROR FLAG BYTE OF PRINT-
*                                  LINE IMAGE
         SUI       7,X'20'         SUBTRACT A SPACE
         BL        PPP
POUW     LW        4,=C'    '      ASCII SPACES
         LI        1,-80           COUNT FOR RESTORATION OF IMAGE
POUH     TBM       LPOOLM,SPMAC    ARE WE PROCESSING AN LPOOL IN A
*                                  MACRO EXPANSION?
         BS        POUJ+1W      YES, DON'T TOUCH MPBUF.
         TBM       NOPGEN,SPMAC        IS A NOP BEING GENERATED?
         BS        POUJ+1W      YES, DON'T TOUCH MPBUF.
         TBM       MBUFSW,SPMAC    WERE THE PRNT BUFS SWITCHED?
         BNS       $+3W         NO--THEN DON'T SWITCH THEM BACK.
         LW        5,MPBUF+80,1    GET ORIGINAL IMAGE DATA
         STW       5,IN+80,1       RESTORE IT
         STW       4,MPBUF+80,1    SAVE THE IMAGE FOR FURTHER PROCESSING
         BIW       1,POUH          DO ALL 20 WORDS/80 BYTES
POUJ     ZMW       HWMSPBUF        CLEAR STORE POINTER FOR MACRO PRINT
         ZBM       MBUFSW,SPMAC    CLEAR PRNT BUF SWITCH BIT.
         BU        *POUTS0         RETURN
*  IGNORE B,R,U,V, AND \ ERRORS ON PASS 1
POUZ     ZBM       G'B'-X'40',HWERRF  IGNORE B ERROR
         ZBM       G'R'-X'40',HWERRF  IGNORE R ERROR
         ZBM       G'U'-X'40',HWERRF  IGNORE U ERROR
         ZBM       G'V'-X'40',HWERRF   IGNORE V ERROR.
         ZBM       G'\'-X'40',HWERRF   IGNORE \ ERROR.
         LW        6,HWERRF
         BEQ       POUW         NO ERRORS--DON'T PRINT LINE.
         BU        POUU            PRINT SHORT ERRORS AND LONG IMAGE
POUX     LI        6,20            NUMBER OF ERRORS WE CAN PRINT IF THEY
*                                  ARE ALONE
         TBM       CVFL,HHBITS     SIGNAL TO PRINT PROGRAM COUNTER
         BNS       POUV
         LI        6,8             YES, WE CAN ONLY OUTPUT 8 FLAGS THEN
         BU        POUV            FINISH UP SHORT LINE
         SPACE     3
*        FORMAT THOSE FLAGGED BYTES OF GENERATED CODE FOR PRINT-OUT
         SPACE     3
PTH1     STW       0,PTH1R         SAVE RETURN ADDRESS
         LW        5,HWBYTE        4 POSSIBLE BYTES TO GEN
         BL        BTX             CONV. HEX TO ASCII
         LI        3,-8            8 BYTES TO STORE
         LI        2,7B            INIT STORE INDEX
PTH2     STB       7,PRNT+4W+3B,2  STORE AWAY ONE BYTE
         SRLD      6,8             POSITION NEXT BYTE FOR STORE
         SUI       2,1             DECREMENT STORAGE INDEX
         BIB       3,PTH2          LOOP TO STORE ALL BYTES
*
         LI        6,G' '          BLANK CHAR
         LI        3,-4            4 BITS TO CHECK
         LI        2,0
PTH3     TBM       7,HWBYTF+4B,3   WAS CODE GEN'D FOR THIS BYTE?
         BS        PTH4            YES - OK
         STB       6,PRNT+4W+3B,2  BLANK OUT 1ST HEX DIG. BYTE
         STB       6,PRNT+4W+4B,2  BLANK OUT 2ND HEX DIG. BYTE
PTH4     ADI       2,2             INCREMENT STORE INDEX
         BIB       3,PTH3          LOOP TO CHECK ALL 4 BYTES
         BU        *PTH1R          RETURN TO CALLER
*
* (C) COPYRIGHT 1983 ENCORE COMPUTER CORPORATION
*     ALL RIGHTS RESERVED
*
         TITLE     READ-ONLY
*        FORMAT LOCATION COUNTER TYPE EXPRESSION FOR PRINTOUT
*        INPUTS ARE
*        R2 = ADDRESS WHERE DATA TO BE CONVERTED IS STORED
*        R3 = ADDRESS WHERE FORMATTED DATA TO BE PLACED
         SPACE     3
LOCH     CEQU      $                                            ESCT-32
         STW       0,LOCHS0        RETURN PSWR
         STW       1,LOCHS1        SAVE R1
         LI        1,SECTYPES-NSECTYPS  NEG NUM OF SECTION TYPES
         LB        5,0,2           FETCH     TYPE OF EXP/SYMBOL
         ZBR       5,24            CLEAR DSECT/CSECT FLAG
LOCH1    CAMB      5,NSECTYPS,1    DOES TYPE MATCH THIS SEC TYPE?
         BEQ       LOCH1.1         YES
         BIB       1,LOCH1         LOOK AT ALL SECTION TYPES
         BU        LOCH1.3         NOT A SECTION TYPE - DON'T PRINT SEC
*                                     NUMBER
LOCH1.1  TBM       0,0,2           IS CSECT FLAG SET IN TYPE?
         BNS       LOCH1.3         NO
         LI        5,G'*'          CSECT INDICATOR
         STB       5,1B,3          STORE IN PRINT BUFFER
LOCH1.3  CEQU      $                                            ESCT-32
         LH        1,0,2           DATA WORD LEFT 16 BITS
         SLL       1,17            GET TYPE CODE AND
         SRL       1,24               ABS/REL FLAG ONLY
         LB        1,SSTL,1        GET THE TYPE SUMMARY CHARACTER
         STB       1,2B,3          TYPE CHAR TO PRINT LINE
         LW        5,0,2           ALL 32 DATA BITS
         CI        1,G'L'          IS TYPE LITERAL?
         BNE       LOCH2        NO.
         SLLD      4,16            TYPE CODE AND LPOOL # TO REG. 4.
         SRL       4,2             DIVIDE LPOOL # BY 4.
         SRLD      4,4             CONCATENATE LPOOL # TO LITERAL #.
         SLL       4,6             POSITION TYPE CODE FOR CONCATENATION.
         SRLD      4,12            CONCATENATE TYPE CODE.
LOCH2    CEQU      $                                            ESCT-32
         CI        1,G'C'          IS TYPE COMMON
         BNE       LOCH2.1         NO
         LB        1,1,2           GET COMMON BLOCK NUMBER
         SLL       1,2             MAKE AN INDEX
         TBM       0,HWCMSIZE,1    IS IT SSECT
         BNS       LOCH2.1         NO
         LI        1,G'S'
         STB       1,2B,3
LOCH2.1  CEQU      $                                            ESCT-32
         ZBR       R2,0            ARE WE PROCESSING OPRND DATA EINS-31
         BNS       LOCH2.2         SKIP IF NOT                  EINS-31
         ZBM       EIS.OPC,EISFLG  IS THIS A CONTEXT TYPE INSTR EINS-31
         BNS       LOCH2.2         SKIP IF NOT                  EINS-31
         LI        R1,G'#'         SET MODIFIER TO "#"          EINS-31
         STB       R1,2B,X3        AND STORE IN LINE IMAGE      EINS-31
LOCH2.2  CEQU      $               CONTINUE                     ESCT-32
         BL        BTX             CONVERT ADDRESS VALUE TO ASCII HEX
         TRR       3,1             STORAGE ADDRESS
         LI        4,-4            4 BYTES TO STORE FROM R7
LOCH3    SLC       7,8             POSITION A BYTE TO STORE
         STB       7,1W,1          STORE IT
         ADI       1,1             INCREMENT STORAGE INDEX
         BIB       4,LOCH3         LOOP TO DO ALL FOUR BYTES
         STB       6,3B,3          MOST SIG VALUE DIGIT
         LW        1,LOCHS1        RESTORE R1
         BU        *LOCHS0         RETURN TO CALLER
         PAGE
*        THIS ROUTINE CONVERTS A FULL 32 BIT QUANTITY IN R5 TO ITS
*        ASCII REPRESENTATION OF EIGHT HEXADECIMAL DIGITS IN R6 AND R7
         SPACE     3
BTX      CEQU      $               ENTRY POINT                  ESCT-32
         STW       1,BTXA          SAVE SCRATCH REGISTERS
         STW       2,BTXB
         LI        1,-8            NUMBER OF DIGITS TO CONVERT
         ZR        7               CLEAR LEAST SIG DIGIT OUTPUT REGISTER
BTX1     ZR        4               CLEAR HEX-BINARY DIGIT RECEIVER
         SLLD      4,4             BRING ONE DIGIT FROM R5 INTO R4
         SLLD      6,8             REG 6,7 READY TO RECEIVE ONE BYTE
         TRR       4,2             SAVE THE HEX DIGIT
         ORMB      7,BTX4,2        CONVERT HEX SIGIT TO ASCII BYTE
         BIB       1,BTX1          DO ALL EIGHT DIGITS OF R3
         LW        1,BTXA          RESTORE SCRATCH REGISTERS
         LW        2,BTXB
         TRSW      0               RETURN TO CALLER
         PAGE
*        CONVERT BINARY TO ASCII-CODED DECIMAL.
*
*        R5        SOURCE.         * IF SOURCE EXCEEDS 99,999,999 THE
*        R6,R7     RESULT.         *MOST SIGNIFICANT DIGITS WILL BE
*        R1,2,3,4  DESTROYED.      *TRUNCATED.
*
         SPACE     3
CONBAD   LI        1,10            DIVISOR.
         LI        2,X'30'         ASCII CHARACTER GENERATOR.
         LI        3,-9            ITERATION COUNTER.
CONBAD1  ZR        4               CLEAR GARGAGE
         BIB       3,$+3H          NEXT ITERATION, OF GET OUT
         TRSW      0               FINISHED, RETURN
         DVR       1,4             RESULT TO R5, REMAINDER TO R4.
         ORR       2,4             GENERATE ASCII CHARACTER.
         SRC       4,8             CHARACTER TO FIRST BYTE OF R4.
         SRLD      6,8             MAKE ROOM FOR NEW CHARACTER.
         ORR       4,6             CHAR TO FIRST BYTE OF RESULT.
         BU        CONBAD1         GO TO NEXT ITERATION.
         PAGE
* ALLOCATE CURRENT LABEL TO STATICIZED PROGRAM COUNTER
         SPACE     3
TALL     CEQU      $                                            ESCT-32
         LD        4,HWLABL        LABEL TO BE ALLOCATED IS IN 4+5
         CAMW      4,=C'    '      IS THERE A LABEL
         BEQ       TALL2        NO, RETURN
         STW       0,TALLS0        SAVE RETURN ADDRESS
         BL        YEANAY          CHECK WHETHER ASSEMBLY PERMITTED
         BNS       TALL1        DONT ALLOCATE THIS LABEL
         LW        1,HWLSTS        PROG COUNTER
         TBM       7,HBPASS        WHICH PASS ARE WE IN
         BS        $+2W         PASS 1
         LW        1,TALLS1        PASS 2 CHECK LABL AGAINST SYM TBL
         BL        SS              SYMBOL TABLE WORKER
         TBM       7,HBPASS        WHICH PASS ARE WE IN
         BS        TALL1        PASS 1, RETURN NO CHECK REQD
         EOMW      3,HWLSTS        PASS 2. CHECK SYM TBL AGAINST KEY
         BEQ       TALL1        RETURN IF THEY AGREE
         SBM       G'T'-X'40',HWERRF   MARK T ERROR
         ABM       31,HWERCT       COUNT THE ERROR
TALL1    LW        0,TALLS0        GET RETURN ADR
TALL2    TRSW      0               RETURN
         TITLE     SYMBOL TABLE ITEM DESCRIPTION
**********************************************************************
*        WORD 1 OF EACH SYMBOL TABLE ITEM CONTAINS THE FIRST 4 BYTES *
*                  OF THE SYMBOL NAME (MACRO AND FORM NAMES STORED   *
*                  NEGATED)     FOR LITERALS (BITS0-14=0,            *
* BIT 15 SET INDICATES LITERAL ADDRESS IN WORD 2 IS IN CSECT         *
*                               IF BIT 23 IS SET IN WORD 1           *
* BIT 15 RESET INDICATES LITERAL ADDRESS IN WORD 2 IS IN DSECT       *
*                               IF BIT 23 IS SET IN WORD 1           *
*                  BIT15-22=LITERAL TYPE,BIT23=ABS/REL FLAG OF VALUE,*
*                  BITS24-31=COMMON BLOCK NUMBER IF COMMON TYPE      *
*                  LITERAL OTHERWISE BITS24-31=0)                    *
*        WORD 2 OF EACH SYMBOL TABLE ITEM CONTAINS THE SECOND 4 BYTES*
*                  OF THE SYMBOL NAME (MACRO AND FORM NAMES STORED   *
*                  NEGATED)    FOR LITERALS, WORD 2 = LITERAL VALUE  *
*        WORD 3 OF EACH SYMBOL TABLE ITEM CONTAINS DEFINITION        *
*                  INFORMATION AS DESCRIBED BELOW:                   *
**********************************************************************
*               ( ABS/REL FLAG = 0 IF ABSOLUTE , 1 IF RELOCATABLE)   *
**********************************************************************
**********************************************************************
*  BYTE 0 - SYMBOL TYPE         *  BYTES 1 TO 3 - VALUE              *
**********************************************************************
**********************************************************************
*  UNDEFINED (1)                *  BIT8=ABS/REL FLAG , BITS 9-31=LAST*
*                               *  ADDRESS  IN UNDEFINED STRINGBACK  *
*                               *  CHAIN.                            *
* BIT 0 = DSECT/CSECT FLAG      *                                    *
*   SET - SYMBOL IN CSECT       *                                    *
*   NOT SET - SYMBOL IN DSECT   *                                    *
**********************************************************************
*  LITERAL (2)                  * BITS 8-15 CONTAIN LITERAL          *
*                               * POOL NUMBER (A NUMBER              *
*                               * IN THE RANGE 0 - 124 REPRESENTING  *
*                               * LPOOLS 0 - 31),                    *
*                               * BITS 16-31 CONTAIN THE NUMBER      *
*                               * OF THE LITERAL (0 - 65535)         *
*                               * WITHIN THE LPOOL                   *
* BIT 0 = DSECT/CSECT FLAG      *                                    *
*   SET - SYMBOL IN CSECT       *                                    *
*   NOT SET - SYMBOL IN DSECT   *                                    *
**********************************************************************
*  COMMON SYMBOL NAME (3)       *  BYTE1=BLOCK NUMBER,BYTES2-3=      *
*                               *  DISPLACEMENT FROM BASE OF COMMON  *
*                               *  BLOCK.                            *
**********************************************************************
*  PROGRAM (4)                  *  BIT8=ABS/REL FLAG,BITS9-31=PROGRAM*
*                               *  ADDRESS.                          *
* BIT 0 = DSECT/CSECT FLAG      *                                    *
*   SET - SYMBOL IN CSECT       *                                    *
*   NOT SET - SYMBOL IN DSECT   *                                    *
**********************************************************************
*  MULTIPLY DEFINED (5)         *  BIT8=ABS/REL FLAG,BITS9-31=LAST   *
*                               *  VALUE ASSIGNED TO SYMBOL.         *
* BIT 0 = DSECT/CSECT FLAG      *                                    *
*   SET - SYMBOL IN CSECT       *                                    *
*   NOT SET - SYMBOL IN DSECT   *                                    *
**********************************************************************
*  EXTERNAL (6)                 *  BIT8=ABS/REL FLAG,BITS9-31=ADDR   *
*                               *  OF 2 WORD ENTRY CONTAINING LAST   *
*                               *  EXTERNAL STRINGBACK ADDRESSES     *
* BIT 0 = DSECT/CSECT FLAG      *  FOR DSECT AND CSECT REFERENCES    *
*   SET - SYMBOL IN CSECT       *  DSECT - 1ST WORD  CSECT - 2ND WRD *
*   NOT SET - SYMBOL IN DSECT   *                                    *
**********************************************************************
*  COMMON BLOCK DEFINITION (7)  *  BYTE1=BLOCK NUMBER,BYTES2-3=SIZE  *
*                               *  (IN BYTES) OF COMMON BLOCK.       *
**********************************************************************
*  SET (8)                      *  BIT8=ABS/REL FLAG,BITS9-31=VALUE  *
*                               *  TO WHICH SYMBOL WAS LAST SET.     *
* BIT 0 = DSECT/CSECT FLAG      *                                    *
*   SET - SYMBOL IN CSECT       *                                    *
*   NOT SET - SYMBOL IN DSECT   *                                    *
**********************************************************************
*  MACRO DEFINITION (9)         *  BYTES1-3=DISPLACEMENT FROM BASE OF*
*                               *  MACRO STORAGE TABLE.              *
**********************************************************************
*  FORM DEFINITION (A)          *  BYTES1-3=DISPLACEMENT FROM BASE OF*
*                               *  MACRO STORAGE TABLE.              *
**********************************************************************
*  DATAPOOL (C)                 *  BYTES1-3=ZERO.                    *
**********************************************************************
         SPACE     3
*                   SYMBOL TABLE WORKER. INPUT WITH KEY NAME IN R4,R5
*        AND DEFINITION/REQUEST IN R1. OUTPUT DEFINITION IS IN  R3 AND
*        POINTER TO ITEM IN R2.
         SPACE     3
SS       TRR       R0,R2            SAVE CALLERS ADDRESS
         STD       R6,SSUFB         SAVE INPUT REGS R6,R7
         LW        R3,HWLICT        CURRENT LINE COUNT
         TRR       R4,6             LEFT NAME WORD TO R6
         SRL       R6,24            MASK OFF POSSIBLE ARG NUM.
         CI        R6,X'21'          IS THIS AN INT SYM?
         BNE       SSU1.8       NO.
         STF       R0,REGSAV        SAVE ALL REGS.
         TBM       XREFINT,OPTION  ARE WE XREFING INTERNALS
         BNS       SSUNI        NO
         ZMW       REPTYPE         INDICATE SYMBOL REPORT TO XREF
         BL        REPTR          REPORT INT SYM TO XREF.
SSUNI    LF        R0,REGSAV        RESTORE ALL REGS.
         SBM       INTSS,SPMAC     SET SS INT FLAG.
         BU        SSUCH           CONTINUE GOING THROUGH THE LEVELS.
SSU1.8   ZBM       INTSS,SPMAC     CLEAR SS INTERNAL FLAG.
         ZMW       REPTYPE         INDICATE SYMBOL REPORT TO XREF
         BL        REPTR          REPORT THIS REFERENCE FOR LATER CONCO
         TRR       R2,0             REST CALLERS ADDRESS
*                 SUBROUTINE TO LOOKUP SYMBOL FROM TABLE
*
*        IN        R4, R5 = SYMBOL NAME LEFT JUSTIFIED BLANK FILLED
*                  R2 = STACK POINTER TO SYMBOL HEADER
*
*        OUT       R2 = ADDRESS OF SYMBOL  TABLE ENTRY IF FOUND
*
*!SSUCH!!!LA!!!!!!!R2,SYMTAB!!!!!!!GET!ADDR!OF!1ST!SYMBOL!TABLE!S880752
SSUCH    CEQU      $                                            ESCT-32
         TRR       R4,R2           GET 1ST PART OF NAME
         TBM       INTSS,SPMAC     IS THIS INT SYMBOL
         BNS       SS01            BR IF NOT
         TRR       R5,R2           USE LEAST DIGIT OF INT SYMBOL
SS01     SRL       R2,21           SHIFT 1ST BYTE OVER
         ANMW      R2,=X'7C'       32 ONLY
         LA        R2,SYMHEAD,R2   GET HEAD CELL ADDR
         STW       R2,SYMDEX       SAVE HEAD CELL ADDR
         LW        R2,0W,R2        ANY ENTRIES IN THIS CELL YET
         BZ        SSU5            BR IF NOT
SS51     CAMD      R4,SYMBOL,R2    COMPARE AGAINST LAST NODE ENTRY
         BLT       SS50            NEW .LT. LAST, FOLLOW DESENDING LINK
         BEQ       SSU7            THEY ARE .EQ. WE FOUND THE SYMBOL
         LW        R2,RLINK,R2     NEW .GT. LAST, FOLLOW ASSENDING LINK
         BNZ       SS51            GO TRY NEXT LARGER BRANCH
         BU        SSU5            NOT FOUND, RETURN ERROR
SS50     LW        R2,LLINK,R2     GET DECENDING PATH
         BNZ       SS51            IF NOT END, GO UPDATE
         SPACE     3
SSU5     TRR       R1,7             COPY INPUT ARGUMENT TO R7
         ZR        R6              ZERO R6 TO RECEIVE TYPE CODE
         ZR        R3              INDICATE NOT FOUND
         SLLD      R6,8             GET TYPE CODE INTO R6
         CI        R6,TYMACREQ      WAS THIS A REQUEST FOR MACRO INFO
         BEQ       SSU88        YES-THEN FORGET IF NAME NOT PRESENT
         TBM       7,HBPASS         CHECK WHICH PASS THIS IS
         BS        SSU10        PASS 1 -NEW TAGS ARE ALLOWED
         SBM       G'T'-X'40',HWERRF  MARK T ERROR
         ABM       31,HWERCT       COUNT OF ERRORS DURING THIS PASS
         BU        SSU10           AND OUT
         SPACE     3               SYMBOL ENTRY FOUND
SSU7     LB        R7,4W,R2         THE TYPE CODE IN THE SYMBOL TABLE
         ZBR       R7,24            CLEAR DSECT/CSECT FLAG
         CI        R7,TYPM          CHECK FOR MULTIPLY DEFINED ALREADY
         BEQ       SSU0         IT IS A M TYPE
         TRR       R1,6             THE INPUT DESCRIPTION
         ZBR       R6,0             CLEAR DSECT/CSECT FLAG
         SRL       R6,24            GET TYPE CODE TO R6(24-31)
         CI        R6,TYPC          IS IT BELOW COMMON
         BLT       SSU9         UNDEFINED OR LITERAL
         CI        R6,TYPX          IS IT BELOW EXTERNAL
         BLT       SSU14        YES- THEN PROGRAM, COMMON, OR MULTIPL
         CI        R6,TYMACREQ      IS IT JUST A MACRO REQUEST
         BGE       SSU9         YES
         CI        R6,TYPD          IS IT A BLOCK DEFINITION?
         BEQ       SSUBLK       YES
         CI        R6,TYSETSYM      IS IT A SET SYMBOL?
         BEQ       SSUSET       YES
         CI        R6,TYPDP         IS IT A DATAPOOL ITEM?
         BEQ       SSU11        YES.
         CI        R6,TYMACDEF      IS IT A MACRO DEFINITION?
         BEQ       $+3W         YES.
         CI        R6,TYFRM         IS IT A FORM DEFINITION?
         BNE       SSUAB        NO.
         SBM       G'M'-X'40',HWERRF    MARK M ERROR.
         ABM       31,HWERCT            COUNT THE ERROR.
         BU        SSU8            AND LEAVE.
SSUBLK   CI        R7,TYPD          IS TYPE IN TABLE 'COMMON' BLOCK ?
         BEQ       SSU11        YES - OK
         BU        SSU14           GO CHECK FOR 'UNDEFINED' IN TABLE
SSUSET   CI        R7,TYSETSYM      IS TYPE IN TABLE 'SET' ?
         BEQ       SSU11        YES - OK
         BU        SSU14           GO CHECK FOR 'UNDEFINRD' IN TABLE
SSUAB    CEQU      $                                            ESCT-32
         CI        R7,TYPU          IS TYPE CODE IN TABLE UNDEFINED?
*!!!!!!!!BEQ!!!!!!!SSU13!!!!!!!!YES,!GO!PROCESS!EXTERNAL!DEFINI!S920183
         BEQ       SSU16        YES, GO PROCESS EXTERNAL DEF    S920183
         CI        R7,TYPX          IS TYPE CODE IN TABLE ALREADY
*                                  EXTERNAL?
         BEQ       SSU88        YES, MAKE WAY OUT.
         BU        SSU0            MULT. DEFINED SYMBOL--GO MARK M ERROR
SSU14    CEQU      $                                            ESCT-32
         CI        R7,TYPU          WAS NAME UNDEFINED BEFORE DEFINITION
         BEQ       SSU11        YES-NORMAL PASS 1 OCCURENCE
SSU0     CEQU      $                                            ESCT-32
*        FALL THRU HERE WHEN NAME IS BEING MULTIPLY DEFINED.
         SBM       G'M'-X'40',HWERRF  MARK M ERROR
         ABM       31,HWERCT       COUNT THE ERROR
         LI        R7,TYPM          MULTIPLE TYPE CODE
         LB        R3,4W,R2         TYPE CODE FROM TABLE
         ANMW      R3,=X'80'        CLEAR ALL BUT DSECT/CSECT FLAG
         ORR       R3,R7            COMBINE FLAG AND 'M' TYPE CODE
         STB       R7,4W,R2         MODIFY DIRECTORY FOR THAT NAME
         BU        SSU8            AND THEN LEAVE.
*
* (C) COPYRIGHT 1983 ENCORE COMPUTER CORPORATION
*                ROW+1   *     LLINK         *
*                        *********************
*                ROW+2   *      ABCD         *
*                        *********************
*                ROW+3   *      EFGH         *
*                        *********************
*                ROW+4   *     DESCR         *
*                        *********************
*                ROW+5   *     RESERVED      *
*                        *********************
*
*
*       ABCD IS THE FIRST FOUR ASCII CHARACTERS OF THE
*               SYMBOL, BLANK FILLED, LEFT JUSTIFIED
*       EFGH IS THE SECOND FOUR ASCII CHARACTERS OF THE
*               SYMBOL, BLANK FILLED, LEFT JUSTIFIED
*
*       DESCR IS THE VALUE OR DESCRIPTION ASSIGNED TO THE SYMBOL
*
*                  R1 HAS NEW ENTRY DESCRIPTOR
*                  R4 + R5 HAS ENTRY NAME
*                  SYMCURRP - POINTS TO NEXT STACK FRAME AVAILABLE
*                  SYMHEAD  - POINTS TO START OF SYMBOL TABLE
***********************************************************************
SSU10    TRR       R1,R7           GET NEW ENTRY DESCRIPTOR
         TRR       R4,R6           SAVE FOR POSSIBLE SYSTEM CALL
*!!!!!!!!LA!!!!!!!!R1,SYMTAB!!!!!!!GET!POINTER!TO!START!OF!SYMBOS880752
         LW        R3,CURRP        GET FREE POINTER             S880752
         ADI       R3,7B           ROUND UP                     S880752
         ANMW      R3,=X'00FFFFF8' AND DOUBLEWORD BOUND         S880752
         STW       R3,SYMCURRP     SET AS NEXT SYMTAB ENTRY     S880752
         ADI       R3,6W           GET THE SPACE                S880752
         STW       R3,CURRP        AND UPDATE FREE POINTER      S880752
         CAMW      R3,HIGH         DO WE HAVE THE SPACE         S880752
         BLT       ST05.1          SKIP IF WE DO                S880752
         SVC       1,X'69'         ELSE GET A MAPBLOCK          S880752
         TRR       R3,R3           COULD WE?                    S880752
         BZ        MNOK            BR IF NOT                    S880752
         STW       R4,HIGH         ELSE SAVE NEW HIGH           S880752
         TRR       R6,R4           RECOVER SYMBOL               S880752
ST05.1   CEQU      $                                            ESCT-32
         LW        R2,SYMCURRP     GET CURRENT SYMBOL TABLE STACK POINTE
         LW        R3,SYMPREVP     GET PREVIOUS ENTRY ADDR      S880752
         BZ        ST05.2          SKIP FIRST SYMBOL            S880752
         STW       R2,5W,X3        ELSE INSERT NEXT ENTRY PTR   S880752
         BU        ST05.3          MERGE UP                     S880752
ST05.2   CEQU      $                                            ESCT-32
         STW       R2,SYMTAB       INITIALIZE 1ST SYMBOL ADDR   S880752
ST05.3   CEQU      $                                            ESCT-32
         STW       R2,SYMPREVP     UPDATE PREVIOUS SYMBOL PTR   S880752
         TRR       R7,R3           TYPE CODE TO R3              ELST-32
         SRL       R3,24                                        ELST-32
         CI        R3,TYPX         IS TYPE EXTERNAL?            ELST-32
         BNE       ST05.4          NO SPECIAL PROCESSING IF NOT ELST-32
         LW        R3,CURRP        GET NEXT FREE ENTRY PNTR     ELST-32
         ADI       R3,7B           ROUND UP                     ELST-32
         ANMW      R3,=X'00FFFFF8' AND DOUBLEWORD BOUND         ELST-32
         STW       R3,SYMCURRP     SET AS NEXT SYMTAB ENTRY     ELST-32
         ADI       R3,2W           GET SPACE FOR STNGBACK ADDRS ELST-32
         STW       R3,CURRP        UPDATE FREE POINTER          ELST-32
         CAMW      R3,HIGH         DO WE HAVE THE SPACE?        ELST-32
         BLT       ST05.5          YES, CONTINUE                ELST-32
         TRR       R4,R6           SAVE R4                      ELST-32
         SVC       1,X'69'         GET A MAPBLOCK               ELST-32
         TRR       R3,R3           SERVICE O.K.?                ELST-32
         BZ        MNOK            ERROR IF NOT                 ELST-32
         STW       R4,HIGH         UPDATE NEW HIGH              ELST-32
         TRR       R6,R4           RESTORE R4                   ELST-32
ST05.5   LW        R2,SYMPREVP     GET PREVIOUS SYMBOL POINTER  ELST-32
         LW        R6,SYMCURRP     GET CURRENT POINTER          ELST-32
         ORR       R7,R6           OR IN TYPE CODE              ELST-32
         STW       R6,4W,R2        SAVE ADDR PNTR IN ENTRY      ELST-32
ST05.4   LW        R3,SYMDEX       GET HEAD CELL ADDR
         LW        R1,0W,R3        IS HEAD CELL ACTIVE
         BNZ       ST05            BR IF YES
         STW       R2,0W,R3        ESTABLISH NEW HEAD CELL POINTER
         TRR       R2,R1           USE CURRENT ENTRY AS IST ONE
*!ST05!!!LI!!!!!!!!R3,6W!!!!!!!!!!!SYMBOL!TABLE!ENTRY!INCREMENT!S880752
*!!!!!!!!ARMW!!!!!!R3,SYMCURRP!!!!!UPDATE!SYMBOL!TABLE!POINTER!!S880752
ST05     CEQU      $                                            ESCT-32
*!!!!!!!!LW!!!!!!!!R3,SYMCURRP!!!!!GET!STACK!POINTER!!!!!!!!!!!!S880752
*!!!!!!!!CAMW!!!!!!R3,SYMEND!!!!!!!ARE!WE!AT!END!YET!!!!!!!!!!!!S880752
*!!!!!!!!BLT!!!!!!!ST14!!!!!!!!!!!!BR!IF!NOT!END!!!!!!!!!!!!!!!!S880752
*!!!!!!!!SVC!!!!!!!1,X'67'!!!!!!!!!GET!MORE!EXECUTION!SPACE!!!!!S880752
*!!!!!!!!TRR!!!!!!!R3,R3!!!!!!!!!!!ALL!OK?!!!!!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!BZ!!!!!!!!MNOK!!!!!!!!!!!!NO!MEM!TO!GET,!ABORT!!!!!!!!!S880752
*!!!!!!!!STW!!!!!!!R4,SYMEND!!!!!!!UPDATE!NEW!END!ADDR!!!!!!!!!!S880752
*!ST14!!!TRR!!!!!!!R6,R4!!!!!!!!!!!RESTORE!REG!!!!!!!!!!!!!!!!!!S880752
         ZMW       5W,X2           INSURE CURRENT POINTS NOWHERES880752
         STD       R4,SYMBOL,R2    SAVE NAME OF SYMBOL IN CELL
*!!!!!!!!LW!!!!!!!!R3,SYMCURRP!!!!!GET!UPDATED!CURRENT-I.E.!NEXTS880752
*!!!!!!!!STW!!!!!!!R3,5W,X2!!!!!!!!AND!SET!INTO!TABLE!!!!!!!!!!!S880752
ST15     CAMD      R4,SYMBOL,R1    COMPARE AGAINST LAST NODE ENTRY
         BLT       ST50            NEW .LT. LAST
         BEQ       ST95            THEY ARE .EQ. (SHOULDN'T HAPPEN)
         LW         R3,RLINK,R1     NEW .GT. LAST, FOLLOW ASSENDING LINK
         BZ        ST90            ZERO MEANS END OF BRANCH
ST30     TRR        R3,R1           GENERATE PATH POINTER
         BU        ST15            GO TRY NEXT BRANCH NODE
ST50     LW         R3,LLINK,R1     GET DECENDING PATH
         BNZ       ST30            IF NOT END, GO UPDATE
         STW       R2,LLINK,R1     UPDATE LINK IN PREVIOUS NODE
         BU        ST95            GO CLEAR NEW ENTRY NODE POINTERS
ST90     STW       R2,RLINK,R1     UPDATE RLINK IN PREVIOUS NODE
ST95     ZMW       RLINK,R2        CLEAR NEW ENTRY NODE POINTERS
         ZMW       LLINK,R2        DITTO
*                                  R2=ENTRY ADDR, R7=DESCRIPTOR
         TRR       R7,R1           RESTORE R1
         SRL       R7,24           SHIFT TYPE CODE OVER         ELST-32
         CI        R7,TYPX         IS IT EXTERNAL               ELST-32
         BNE       SSU11           SKIP IF NOT                  ELST-32
         LW        R3,4W,R2        GET PNTR TO STRINGBACK ADDRS ELST-32
         STW       R1,0,R3         INIT DSECT STRINGBACK ADDR   ELST-32
         STW       R1,1W,R3        INIT CSECT STRINGBACK ADDR   ELST-32
         BU        SSU8            CONTINUE                     ELST-32
SSU11    STW       R1,4W,R2         PUT INPUT DEFINITION INTO SYM TAB.
SSU8     LW        R3,4W,R2         THE CONTENTS OF SYMBOL TABLE.
SSU88    LD        R6,SSUFB         RESTORE ORIGINAL REGISTERS
         TRSW      0               RETURN TO CALLER
SSU9     LB        R7,4W,R2         WHAT IS TYPE CODE FOR NAME IN TABLE?
         ZBR       R7,24            CLEAR DSECT/CSECT FLAG
         CI        R7,TYPDP         IS THIS A DATAPOOL ITEM
         BEQ       SSU15        YES-DO SPECIAL PROCESSING
         CI        R7,TYPU          WAS IT UNDEFINED PREVIOUSLY
         BNE       SSU12        BRANCH IF NOT
         SBM       G'U'-X'40',HWERRF  MARK U ERROR
         ABM       31,HWERCT       COUNT THE ERROR
         LW        R3,4W,R2         GET PREVIOUS DESCRIPTION OF NAME
*                                  GET INPUT ARGUMENT FROM CALLER
         STW       R1,4W,R2         AND PLACE IT INTO SYMBOL TABLE NOW
         BU        SSU88           EXIT-HAVING CHAINED UNDEFINED
SSU12    CI        R7,TYPX          IT IS CURRENTLY EXTERNAL NAME
         BNE       SSU8         NO-THEN JUST FETCH INFO FOR NAME
         LB        R3,HWACT+3       ELEMENT 7, OPERATION PROCESSOR NO.
         SLL       R3,2             CONVERT TO BYTE DISPLACEMENT.
         CI        R3,KINTL3        IS EXTERNAL ALLOWED?
         BLT       SSU12.1      YES.
         SBM       G'A'-X'40',HWERRF   MARK A ERROR.
         ABM       31,HWERCT       COUNT THE ERROR.
         BU        SSU8            AND LEAVE.
SSU12.1  LB        R3,HBLABS       GET SECTION INDICATOR        ELST-32
         CI        R3,X'C'         IN CSECT?                    ELST-32
         BEQ       SSU12.2         PROCESS CSECT REF IF SO      ELST-32
         LW        R2,4W,R2        GET PNTR TO STRINGBACK ADDRS ELST-32
         LW        R3,0,R2         GET PREVIOUS LINK IN CHAIN   ELST-32
         STW       R1,0,R2         STORE INTO SYMBOL TABLE ITEM ELST-32
         LI        R7,TYPX         EXTERNAL TYPE CODE           ELST-32
         LB        R6,0,R2         TYPE CODE FROM SYMTAB ENTRY  ELST-32
         ANMW      R6,=X'80'       CLEAR ALL BUT DSECT/CSECT    ELST-32
         ORR       R6,R7           COMBINE                      ELST-32
         STB       R7,0,R2         PUT IT IN ENTRY              ELST-32
         BU        SSU88           EXIT                         ELST-32
SSU12.2  LW        R2,4W,R2        GET PNTR TO STRINGBACK ADDRS ELST-32
         TBM       2,EXTFLG        NON-BRANCH INSTRUCTION REF?  ENSB-33
         BNS       SSU12.3         NO...BRANCH                  ENSB-33
         TBM       OPT11,OPTION    OPTION 11 SET?               ENSB-33
         BNS       SSU12.3         NO...BRANCH                  ENSB-33
         TBM       ASCT.OPT,OPTION   AUTO SECTIONING SET?       ENSB-33
         BNS       SSU12.3         NO...BRANCH                  ENSB-33
         ZBM       2,EXTFLG        CLEAR FLAG                   ENSB-33
         SBM       1,EXTFLG        SHOW EXT. REF. RECORD NEEDED ENSB-33
         ZR        R3              R3 CONTAINS ADDRESS OF ZERO  ENSB-33
         SBR       R3,5            PLUS EXTERNAL ENTRY CODE 6   ENSB-33
         SBR       R3,6                                         ENSB-33
         STW       R1,EXTWRD       SAVE ADDRESS FOR LATER       ENSB-33
         STD       R4,EXTNAM       SAVE SYMBOL NAME ALSO        ENSB-33
         BU        SSU13           CONTINUE                     ENSB-33
SSU12.3  LW        R3,1W,R2        GET PREVIOUS CSECT ADDR      ELST-32
         STW       R1,1W,R2        STORE IN SYMBOL TABLE ITEM   ELST-32
*!!!!!!!!LW!!!!!!!!R3,4W,R2!!!!!!!!!GET!PREVIOUS!LINK!IN!CHAIN!!ELST-32
*                                  INPUT ARGUMENT WILL BE NEXT LINK
*!!!!!!!!STW!!!!!!!R1,4W,R2!!!!!!!!!STORED!INTO!SYMBOL!TABLE!ITEELST-32
SSU13    LI        R7,TYPX          EXTERNAL TYPE CODE
*!!!!!!!!LB!!!!!!!!R6,4W,R2!!!!!!!!!TYPE!CODE!FROM!SYMTAB!ENTRY!ELST-32
         LB        R6,1W,R2        TYPE CODE FROM SYMTAB ENTRY  ELST-32
         ANMW      R6,=X'80'        CLEAR ALL BUT DSECT/CSECT FLAG
         ORR       R6,7             COMBINE DSECT/CSECT FLAG
*                                     AND EXTERNAL TYPE CODE
*!!!!!!!!STB!!!!!!!R7,4W,R2!!!!!!!!!KEEP!IT!IN!THE!CHAIN!!!!!!!!ELST-32
         STB       R7,1W,R2        KEEP IT IN THE CHAIN         ELST-32
         BU        SSU88           EXIT-WITH CHAINED EXTERNAL IN  R3
SSU16    LW        R3,CURRP        GET FREE POINTER             S920183
         ADI       R3,7B           ROUND UP                     S920183
         ANMW      R3,=X'00FFFFF8' AND DOUBLEWORD BOUND         S920183
         STW       R3,SYMCURRP     SET AS NEXT SYMTAB ENTRY     S920183
         ADI       R3,2W           GET TWO WORDS                S920183
         STW       R3,CURRP        AND UPDATE THE FREE POINTER  S920183
         CAMW      R3,HIGH         DO WE HAVE THE SPACE?        S920183
         BLT       SSU16.2         YES...BRANCH                 S920183
         SVC       1,X'69'         ELSE GET A MAPBLOCK          S920183
         TRR       R3,R3           DID WE?                      S920183
         BZ        MNOK            BRANCH IF NOT                S920183
         STW       R4,HIGH         SAVE NEW HIGH POINTER        S920183
SSU16.2  LI        R7,TYPX         GET EXTERNAL TYPE CODE       S920183
         LB        R6,4W,X2        GET TYPE CODE FROM ENTRY     S920183
         ANMW      R6,=X'80'       SAVE CSECT/DSECT FLAG        S920183
         ORR       R6,R7           OR IN NEW TYPE CODE          S920183
         STW       R3,4W,X2   SAVE ADDR OF CSECT/DSECT ADDRS    S920183
         ZMW       0,X3            CLEAR DSECT STRINGBACK ADDR  S920183
         ZMW       1W,X3           CLEAR CSECT STRINGBACK ADDR  S920183
         STB       R7,0,X3         SAVE TYPE CODE IN ENTRY      S920183
         STB       R7,1W,X3        BOTH CSECT AND DSECT         S920183
         STB       R7,4W,X2        AND IN SYMTAB                S920183
         BU        SSU88           RETURN                       S920183
SSU15    LW        R3,4W,R2         GET DATAPOOL ITEM DESCRIPTOR WORD.
         LH        R3,4W,R2         GET DATAPOOL NUMBER
         STB       R3,DPNUM         SAVE DATAPOOL NUMBER
         LH        R3,4W+1H,R2      GET DATAPOOL ITEM DESCRIPTOR WORD.
         ANMW      R3,=X'0000FFFF'  CLEAR POSSIBLE SIGN EXTD
*        ANMW      R3,=X'00FFFFFF'  MASK OFF TYPE CODE
         SBR       R3,5             SET REL PROGRAM TYPE
         SBR       R3,8             SET BIT 8 FOR REL DATA
         SBM       DPFLG,DPFLAGS   SET DP FLAG
         BS        SSU15.1      IS THIS A MULTIPLE REF?
         STD       R4,DPITEM        NO-SAVE LABEL
         BU        SSU88           RET
SSU15.1  SBM       G'V'-X'40',HWERRF  MARK "V" TYPE ERROR
         ABM       31,HWERCT       COUNT ERROR
         ZMB       DPNUM           THERE HAS BEEN AN ERROR CLEAR IT
         BU        SSU88           RETURN
SYMBOL   EQU       2W              POSITION OF SYMBOL IN TABLE ENTRY
SYMDEX   DATAW     0               CURR SYMHEAD ADDR
SYMHEAD  REZ       32W             32 HEAD POINTERS FOR SYMTAB
*!SYMCURRP!!DATAW!!!!SYMTAB!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!S880752
SYMCURRP DATAW     0                                            S880752
SYMPREVP DATAW     0               POINTS TO LAST USED ENTRY    S880752
SYMEND   DATAW     0               ENDING ADDRESS OF SYMBOL TABLE
*
*         DATAPOOL DATA AREA
*
PTDP     EQU       X'C'            DATAPOOL LOADER FUNCTION CODE
DATAPOOL DATAD     C'DATAPOOL'     DEDICATED NAME
DPOO     DATAW     C'DPOO'
LXX      DATAW     G'L'
DPITEM   DATAD     C'        '     REFERENCED DATAPOOL ITEM
DPNUM    DATAB     0               DATAPOOL NUMBER
DPFLAGS  DATAB     0               FLAGS FOR DATAPOOL USAGE
*DPBUF   RES       13B             DATAPOOL OBJ BJFFER
DPBUF    RES       17B             DATAPOOL OBJ BJFFER
*        BIT VARIABLES FOR DPFLAGS
DPFLG    EQU       1               PROCESSING A DATAPOOL REF
EXTFLG   REZ       1B              STRINGBACK CONTROL FLAG      ENSB-33
EXTWRD   REZ       1W              STRINGBACK CONTROL ADDRESS   ENSB-33
EXTNAM   DATAD     0               STRINGBACK CONTROL SYMBOL    ENSB-33
         TITLE     OPERATOR DIRECTORY
*MPX MACRO ASSEMBLER OPERATOR TABLE   OPSTAB            HEADER  OPSTAB
************************************************************************
*         THE OP CODE TRANSLATOR TABLE CONSIST OF SEVERAL ELEMENTS
*         FOR EACH OP CODE TO BE ACCOMODATED.
************************************************************************
*         ELEMENT ONE OF EACH ITEM IS THE OPERATION NAME IN FULL 8 BIT
*         ASCII CODE. THIS FIELD IS EITHER 32 OR 64 BITS LONG DEPENDING
*         UPON WHETHER THE ITEM IS IN TABLE SOPS OR LOPS,
************************************************************************
*         ELEMENT 2 OF EACH ITEM IS THE ACTUAL OPCODE AND A DESCRIPTION
*         OF THE BOUNDING REQUIREMENTS.  THE OPCODE IS THE LEFT MOST 6 B
*         ITS OF THE FIELD, WHILE THE RIGHTMOST 2 BITS ARE THE BOUNDING
*         CODED 0 FOR BYTE (OR NONE), 1 FOR HALFWORD, 2 FOR WORD, 3 FOR
*         DOUBLEWORD. THE LAYOUT OF THE OPCODE IN THE LEFT MAKES IT
*         APPEAR IN THE ASSEMBLER LISTING WITH THE SAME BASIC CODE AS ON
*         AN H ASSEMBLY LISTING. THIS SHOULD EASE MAINTENANCE.
************************************************************************
*         ELEMENT 3 CONTAINS THE NUMBER OF THE OPERATION AUGMENT CODE
*         AND IS 4 BITS LONG
************************************************************************
*         ELEMENT 4 CONTAINS A 4 BIT ADDRESS VARIANT CODE, THIS NUMBER
*         IS USED FOR SETTING THE PROPER F AND CC BITS IN ADDRESS FIELDS
************************************************************************
*         ELEMENT 5 IS 4 BITS LONG AND IS THE FIELD NUMBER IN WHICH RELA
*         TIVE, COMMON, OR EXTERNAL ADDRESSING IS ALLOWED.
************************************************************************
*         ELEMENT 6 IS BROKEN INTO THREE SUB-ELEMENTS
*                  LEFTMOST BIT IS ON MEANS CHECK ARGUMENT 1 FOR EVEN
*                      NEXT BIT IS ON MEANS CHECK ARGUMENT 2 FOR EVEN
*                  NEXT 2 BITS ARE POINTER TO ARGUMENT COUNT MIN/MAX LIS
************************************************************************
*         ELEMENT 7 IS THE 8 BIT NUMBER OF THE PARTICULAR OPERATION PRO-
*         CESSOR  FOR THIS OPERATION MNEMONIC.
***********************************************************************
         PAGE
***********************************************************************
*
*       RLINK = OPCODE ENTRY ADDRESS OF NEXT ALPHABETICALLY GREATER
*               IN VALUE THAN CURRENT NODE
*       LLINK = OPCODE ENTRY ADDRESS OF ALPHABETICALLY LESSER IN
*               VALUE THAN CURRENT NODE.
*
*               SO TO FIND THE NEXT OPCODE LOWER IN THE
*               ALPHABET (CLOSER TO Z) TAKE RLINK ADDRESS;
*               (CLOSER TO A) TAKE LLINK ADDRESS.
*
*
*                        *********************
*       OPSTAB   ROW     *     RLINK         *
*                        *********************
*                ROW+1   *     LLINK         *
*                        *********************
*                ROW+2   *      ABCD         *
*                        *********************
*                ROW+3   *      EFGH         *
*                        *********************
*                ROW+4   *    RESERVED       *
*                        *********************
*                ROW+5   *     DESCR         *
*                        *********************
*
*
*       ABCD IS THE FIRST FOUR ASCII CHARACTERS OF THE
*               OPCODE, BLANK FILLED, LEFT JUSTIFIED
*       EFGH IS THE SECOND FOUR ASCII CHARACTERS OF THE
*               OPCODE, BLANK FILLED, LEFT JUSTIFIED
*
*       DESCR IS THE VALUE OR DESCRIPTION ASSIGNED TO THE OPCODE
*
*                  OPSTAB   - POINTS TO START OF OPCODE TABLE
         PAGE
*        OPSCAN - SUBROUTINE TO LOOKUP OPCODE FROM TABLE
*
*        IN        R4, R5 = OPCODE LEFT JUSTIFIED BLANK FILLED
*
*        OUT       R1 = ADDRESS OF OPCODE TABLE ENTRY IF FOUND
*                  R1 = 0 IF OPCODE NOT FOUND
*                  R2 = DESCRIPTOR ELEMENTS
*                  R3,R4,R5,R6,R7  UNCHANGED
         SPACE     1
*OPSCAN   LA        R1,OPSTAB       GET BASE ADDR OF OPSTAB
         IFF       ULC,SKIP                                     *JCB*
OPSCAN   LA        R1,OPSTAB
SKIP     ANOP                                                   *JCB*
         IFT       ULC,SKIP                                     *JCB*
OPSCAN   LI        R1,-8           SET UP FOR 8 BYTES           *JCB*
OPS.0    CI        R1,-4           ARE WE HALF WAY YET?         *JCB*
         BNE       OPS.1           NO, KEEP CONVERTING          *JCB*
         XCR       R4,R5           SWITCH REGS                  *JCB*
OPS.1    TBR       R4,1            IS IT A LETTER               *JCB*
         BNS       OPS.2           NO, LEAVE IT ALONE           *JCB*
         ZBR       R4,2            FORCE TO UPPER CASE          *JCB*
OPS.2    SRC       R4,8            POSITION NEXT BYTE           *JCB*
         BIB       R1,OPS.0        GO TEST FOR END OF WORD      *JCB*
         XCR       R4,R5           PUT BACK REGS                *JCB*
         LA        R1,OPSTAB       GET BASE ADDRESS OF OPCODES  *JCB*
SKIP     ANOP                                                   *JCB*
         TBM       BM.OPT,OPTION   IS BASE MODE OPTION SET
         BNS       $+2W            NO
         LA        R1,OPSTABBA     USE BASE MODE TABLE
SC15     CAMD      R4,OPCODE,R1    COMPARE AGAINST LAST NODE ENTRY
         BLT       SC50            NEW .LT. LAST, FOLLOW DESENDING LINK
         BEQ       SC95            THEY ARE .EQ. WE FOUND THE OPCODE
         LW        R1,RLINK,R1     NEW .GT. LAST, FOLLOW ASSENDING LINK
         BNZ       SC15            GO TRY NEXT LARGER BRANCH
         TRSW      R0              NOT FOUND, RETURN ERROR
SC50     LW        R1,LLINK,R1     GET DECENDING PATH
         BNZ       SC15            IF NOT END, GO UPDATE
         TRSW      R0              NOT FOUND, ERROR
SC95     LW        R2,5W,R1        ENTRY FOUND, GET DESCRIPTOR ELEMENT
         TRSW      R0              RETURN
OPCODE   EQU       2W              POSITION OF OPCODE IN TABLE ENTRY
OPSIZE   EQU       6W              SIX WORD ENTRIES
OPSNUM   DATAW     OPSEND-OPSTAB/OPSIZE
OPSNUMBA DATAW     OPSENDBA-OPSTABBA/OPSIZE
OPSTBLAD DATAW     0
         SPACE     1
* SUBROUTINE TO INITIALIZE OPCODE TABLE IN BINARY SEARCH FORM
         SPACE     1
* OPINIT   LNW       R7,OPSNUM       GET NUMBER OF ENTRIES IN OPSTAB
OPINITNB LNW       R7,OPSNUM       GET NUMBER OF ENTRIES IN OPSTAB
         LA        R2,OPSTAB       R2 WILL WALK DOWN TABLE AS NEW NODE P
         STW       R2,OPSTBLAD     SAVE WHICH NON-BASE TABLE ADDRESS
         BU        OP05
OPINITBA LNW       R7,OPSNUMBA     GET NUMBER OF ENTRIES IN OPSTAB BASE
         LA        R2,OPSTABBA     R2 WILL WALK DOWN TABLE AS NEW NODE P
         STW       R2,OPSTBLAD
* OP05     LA        R1,OPSTAB       GET BASE ADDR OF OPSTAB
OP05     LW        R1,OPSTBLAD     GET BASE ADDR OF OPSTAB
         LD        R4,OPCODE,R2    GET OPCODE FROM NEW ENTRY
OP15     CAMD      R4,OPCODE,R1    COMPARE AGAINST LAST NODE ENTRY
         BLT       OP50            NEW .LT. LAST
         BEQ       OP95            THEY ARE .EQ. (SHOULDN'T HAPPEN)
         LW        R3,RLINK,R1     NEW .GT. LAST, FOLLOW ASSENDING LINK
         BZ        OP90            ZERO MEANS END OF BRANCH
OP30     TRR       R3,R1           GENERATE PATH POINTER
         BU        OP15            GO TRY NEXT BRANCH NODE
OP50     LW        R3,LLINK,R1     GET DECENDING PATH
         BNZ       OP30            IF NOT END, GO UPDATE
         STW       R2,LLINK,R1     UPDATE LINK IN PREVIOUS NODE
         BU        OP95            GO CLEAR NEW ENTRY NODE POINTERS
OP90     STW       R2,RLINK,R1     UPDATE RLINK IN PREVIOUS NODE
OP95     ZMW       RLINK,R2        CLEAR NEW ENTRY NODE POINTERS
         ZMW       LLINK,R2        DITTO
         ADI       R2,OPSIZE       BUMP TO NEXT OPCODE ENTRY
         BIB       R7,OP05         LOOP FOR ALLENTRIES
         TRSW      R0              RETURN
         PAGE
         BOUND     1D
         TITLE     OPSTAB - DIRECT ADDRESS MODE INSTRUCTIONS
*
*   OPSTAB CHANGE HISTORY
*
* THE FOLLOWING AC DIRECTIVES WERE CHANGED FROM PROCESSING      EASC-32
* VECTOR 14 TO PROCESSING VECTOR 11 TO SUPPORT THE AUTO         EASC-32
* SECTIONING OPTION. THIS SEPARATES AC? DIRECTIVES WHICH MUST   EASC-32
* GENERATE DSECT CODE FROM OTHER VECTOR 14 OPERATIONS WHICH     EASC-32
* MUST GENERATE CSECT CODE.  VECTOR 11 WAS PREVIOUSLY UNUSED.   EASC-32
* A CHANGE IN THE PROCESSING VECTOR JUMP TABLE IS ALSO MADE     EASC-32
*                                                               EASC-32
*---------------------------------------------------------------EASC-32
OPSTAB   DEQU      $               BEGINNING ADDRESS OF OPCODE  ESCT-32
EIS.LDI  DEQU      $               TAG START OF LOAD TABLE ARE  ESCT-32
 GEN 64/0,64/C'LCB     ',32/0,8/X'00',4/X'8',4/X'0',4/X'2',4/X'3',8/15
 GEN 64/0,64/C'LCH     ',32/0,8/X'00',4/X'0',4/X'1',4/X'2',4/X'3',8/15
 GEN 64/0,64/C'LCW     ',32/0,8/X'00',4/X'0',4/X'2',4/X'2',4/X'3',8/15
 GEN 64/0,64/C'LCD     ',32/0,8/X'00',4/X'0',4/X'3',4/X'2',4/X'B',8/15
EIS.STI  DEQU      $               TAG START OF STORE TAB AREA  ESCT-32
 GEN 64/0,64/C'STCB    ',32/0,8/X'00',4/X'8',4/X'0',4/X'2',4/X'3',8/15
 GEN 64/0,64/C'STCH    ',32/0,8/X'00',4/X'0',4/X'1',4/X'2',4/X'3',8/15
 GEN 64/0,64/C'STCW    ',32/0,8/X'00',4/X'0',4/X'2',4/X'2',4/X'3',8/15
 GEN 64/0,64/C'STCD    ',32/0,8/X'00',4/X'0',4/X'3',4/X'2',4/X'B',8/15
EIS.LRI  DEQU      $               TAG LOAD REAL ADDR TAB ENTR  ESCT-32
 GEN 64/0,64/C'LCRA    ',32/0,8/X'00',4/X'0',4/X'4',4/X'2',4/X'3',8/15
 GEN 64/0,64/C'LPSD    ',32/0,8/X'FA',4/X'3',4/X'2',4/X'1',4/X'1',8/16
 GEN 64/0,64/C'LB      ',32/0,8/X'AE',4/X'8',4/X'0',4/X'2',4/X'3',8/15
 GEN 64/0,64/C'LH      ',32/0,8/X'AE',4/X'0',4/X'1',4/X'2',4/X'3',8/15
 GEN 64/0,64/C'LW      ',32/0,8/X'AE',4/X'0',4/X'2',4/X'2',4/X'3',8/15
 GEN 64/0,64/C'LD      ',32/0,8/X'AE',4/X'0',4/X'3',4/X'2',4/X'B',8/15
 GEN 64/0,64/C'STB     ',32/0,8/X'D6',4/X'8',4/X'0',4/X'2',4/X'3',8/15
 GEN 64/0,64/C'STH     ',32/0,8/X'D6',4/X'0',4/X'1',4/X'2',4/X'3',8/15
 GEN 64/0,64/C'STW     ',32/0,8/X'D6',4/X'0',4/X'2',4/X'2',4/X'3',8/15
 GEN 64/0,64/C'STD     ',32/0,8/X'D6',4/X'0',4/X'3',4/X'2',4/X'B',8/15
 GEN 64/0,64/C'LNB     ',32/0,8/X'B6',4/X'8',4/X'0',4/X'2',4/X'3',8/15
 GEN 64/0,64/C'LNH     ',32/0,8/X'B6',4/X'0',4/X'1',4/X'2',4/X'3',8/15
 GEN 64/0,64/C'LNW     ',32/0,8/X'B6',4/X'0',4/X'2',4/X'2',4/X'3',8/15
 GEN 64/0,64/C'LND     ',32/0,8/X'B6',4/X'0',4/X'3',4/X'2',4/X'B',8/15
 GEN 64/0,64/C'LMB     ',32/0,8/X'B2',4/X'8',4/X'0',4/X'2',4/X'3',8/15
 GEN 64/0,64/C'LMH     ',32/0,8/X'B2',4/X'0',4/X'1',4/X'2',4/X'3',8/15
 GEN 64/0,64/C'LMW     ',32/0,8/X'B2',4/X'0',4/X'2',4/X'2',4/X'3',8/15
 GEN 64/0,64/C'LMD     ',32/0,8/X'B2',4/X'0',4/X'3',4/X'2',4/X'B',8/15
 GEN 64/0,64/C'STMB    ',32/0,8/X'DA',4/X'8',4/X'0',4/X'2',4/X'3',8/15
 GEN 64/0,64/C'STMH    ',32/0,8/X'DA',4/X'0',4/X'1',4/X'2',4/X'3',8/15
 GEN 64/0,64/C'STMW    ',32/0,8/X'DA',4/X'0',4/X'2',4/X'2',4/X'3',8/15
 GEN 64/0,64/C'STMD    ',32/0,8/X'DA',4/X'0',4/X'3',4/X'2',4/X'B',8/15
 GEN 64/0,64/C'ADMB    ',32/0,8/X'BA',4/X'8',4/X'0',4/X'2',4/X'3',8/15
 GEN 64/0,64/C'ADMH    ',32/0,8/X'BA',4/X'0',4/X'1',4/X'2',4/X'3',8/15
 GEN 64/0,64/C'ADMW    ',32/0,8/X'BA',4/X'0',4/X'2',4/X'2',4/X'3',8/15
 GEN 64/0,64/C'ADMD    ',32/0,8/X'BA',4/X'0',4/X'3',4/X'2',4/X'B',8/15
 GEN 64/0,64/C'SUMB    ',32/0,8/X'BE',4/X'8',4/X'0',4/X'2',4/X'3',8/15
 GEN 64/0,64/C'SUMH    ',32/0,8/X'BE',4/X'0',4/X'1',4/X'2',4/X'3',8/15
 GEN 64/0,64/C'SUMW    ',32/0,8/X'BE',4/X'0',4/X'2',4/X'2',4/X'3',8/15
 GEN 64/0,64/C'SUMD    ',32/0,8/X'BE',4/X'0',4/X'3',4/X'2',4/X'B',8/15
 GEN 64/0,64/C'CAMB    ',32/0,8/X'92',4/X'8',4/X'0',4/X'2',4/X'3',8/15
 GEN 64/0,64/C'CAMH    ',32/0,8/X'92',4/X'0',4/X'1',4/X'2',4/X'3',8/15
 GEN 64/0,64/C'CAMW    ',32/0,8/X'92',4/X'0',4/X'2',4/X'2',4/X'3',8/15
 GEN 64/0,64/C'CAMD    ',32/0,8/X'92',4/X'0',4/X'3',4/X'2',4/X'B',8/15
 GEN 64/0,64/C'CMMB    ',32/0,8/X'96',4/X'8',4/X'0',4/X'2',4/X'3',8/15
 GEN 64/0,64/C'CMMH    ',32/0,8/X'96',4/X'0',4/X'1',4/X'2',4/X'3',8/15
 GEN 64/0,64/C'CMMW    ',32/0,8/X'96',4/X'0',4/X'2',4/X'2',4/X'3',8/15
 GEN 64/0,64/C'CMMD    ',32/0,8/X'96',4/X'0',4/X'3',4/X'2',4/X'B',8/15
 GEN 64/0,64/C'ANMB    ',32/0,8/X'86',4/X'8',4/X'0',4/X'2',4/X'3',8/15
 GEN 64/0,64/C'ANMH    ',32/0,8/X'86',4/X'0',4/X'1',4/X'2',4/X'3',8/15
 GEN 64/0,64/C'ANMW    ',32/0,8/X'86',4/X'0',4/X'2',4/X'2',4/X'3',8/15
 GEN 64/0,64/C'ANMD    ',32/0,8/X'86',4/X'0',4/X'3',4/X'2',4/X'B',8/15
 GEN 64/0,64/C'ORMB    ',32/0,8/X'8A',4/X'8',4/X'0',4/X'2',4/X'3',8/15
 GEN 64/0,64/C'ORMH    ',32/0,8/X'8A',4/X'0',4/X'1',4/X'2',4/X'3',8/15
 GEN 64/0,64/C'ORMW    ',32/0,8/X'8A',4/X'0',4/X'2',4/X'2',4/X'3',8/15
 GEN 64/0,64/C'ORMD    ',32/0,8/X'8A',4/X'0',4/X'3',4/X'2',4/X'B',8/15
 GEN 64/0,64/C'EOMB    ',32/0,8/X'8E',4/X'8',4/X'0',4/X'2',4/X'3',8/15
 GEN 64/0,64/C'EOMH    ',32/0,8/X'8E',4/X'0',4/X'1',4/X'2',4/X'3',8/15
 GEN 64/0,64/C'EOMW    ',32/0,8/X'8E',4/X'0',4/X'2',4/X'2',4/X'3',8/15
 GEN 64/0,64/C'EOMD    ',32/0,8/X'8E',4/X'0',4/X'3',4/X'2',4/X'B',8/15
 GEN 64/0,64/C'ARMB    ',32/0,8/X'EA',4/X'8',4/X'0',4/X'2',4/X'3',8/15
 GEN 64/0,64/C'ARMH    ',32/0,8/X'EA',4/X'0',4/X'1',4/X'2',4/X'3',8/15
 GEN 64/0,64/C'ARMW    ',32/0,8/X'EA',4/X'0',4/X'2',4/X'2',4/X'3',8/15
 GEN 64/0,64/C'ARMD    ',32/0,8/X'EA',4/X'0',4/X'3',4/X'2',4/X'B',8/15
 GEN 64/0,64/C'BGT     ',32/0,8/X'EE',4/X'2',4/X'1',4/X'1',4/X'1',8/16
 GEN 64/0,64/C'BLT     ',32/0,8/X'EE',4/X'3',4/X'1',4/X'1',4/X'1',8/16
 GEN 64/0,64/C'BEQ     ',32/0,8/X'EE',4/X'4',4/X'1',4/X'1',4/X'1',8/16
 GEN 64/0,64/C'BGE     ',32/0,8/X'EE',4/X'5',4/X'1',4/X'1',4/X'1',8/16
 GEN 64/0,64/C'BLE     ',32/0,8/X'EE',4/X'6',4/X'1',4/X'1',4/X'1',8/16
 GEN 64/0,64/C'BNE     ',32/0,8/X'F2',4/X'4',4/X'1',4/X'1',4/X'1',8/16
 GEN 64/0,64/C'BOV     ',32/0,8/X'EE',4/X'1',4/X'1',4/X'1',4/X'1',8/16
 GEN 64/0,64/C'BP      ',32/0,8/X'EE',4/X'2',4/X'1',4/X'1',4/X'1',8/16
 GEN 64/0,64/C'BN      ',32/0,8/X'EE',4/X'3',4/X'1',4/X'1',4/X'1',8/16
 GEN 64/0,64/C'BZ      ',32/0,8/X'EE',4/X'4',4/X'1',4/X'1',4/X'1',8/16
 GEN 64/0,64/C'BNOV    ',32/0,8/X'F2',4/X'1',4/X'1',4/X'1',4/X'1',8/16
 GEN 64/0,64/C'BNP     ',32/0,8/X'F2',4/X'2',4/X'1',4/X'1',4/X'1',8/16
 GEN 64/0,64/C'BNN     ',32/0,8/X'F2',4/X'3',4/X'1',4/X'1',4/X'1',8/16
 GEN 64/0,64/C'BNZ     ',32/0,8/X'F2',4/X'4',4/X'1',4/X'1',4/X'1',8/16
 GEN 64/0,64/C'BS      ',32/0,8/X'EE',4/X'1',4/X'1',4/X'1',4/X'1',8/16
 GEN 64/0,64/C'BNS     ',32/0,8/X'F2',4/X'1',4/X'1',4/X'1',4/X'1',8/16
 GEN 64/0,64/C'BANY    ',32/0,8/X'EE',4/X'7',4/X'1',4/X'1',4/X'1',8/16
 GEN 64/0,64/C'BAZ     ',32/0,8/X'F2',4/X'7',4/X'1',4/X'1',4/X'1',8/16
 GEN 64/0,64/C'DATAB   ',32/0,8/X'00',4/X'0',4/X'0',4/X'0',4/X'0',8/29
 GEN 64/0,64/C'DATAH   ',32/0,8/X'01',4/X'0',4/X'0',4/X'0',4/X'0',8/29
 GEN 64/0,64/C'DATAW   ',32/0,8/X'02',4/X'0',4/X'0',4/X'0',4/X'0',8/29
 GEN 64/0,64/C'DATAD   ',32/0,8/X'03',4/X'0',4/X'0',4/X'0',4/X'0',8/29
 GEN 64/0,64/C'BEI     ',32/0,8/X'01',4/X'6',4/X'0',4/X'0',4/X'0',8/01
 GEN 64/0,64/C'UEI     ',32/0,8/X'01',4/X'7',4/X'0',4/X'0',4/X'0',8/01
 GEN 64/0,64/C'EWCS    ',32/0,8/X'02',4/X'A',4/X'0',4/X'0',4/X'0',8/01
 GEN 64/0,64/C'RWCS    ',32/0,8/X'01',4/X'B',4/X'0',4/X'0',4/X'2',8/06
 GEN 64/0,64/C'WWCS    ',32/0,8/X'01',4/X'C',4/X'0',4/X'0',4/X'2',8/06
 GEN 64/0,64/C'JWCS    ',32/0,8/X'FA',4/X'4',4/X'0',4/X'1',4/X'1',8/16
 GEN 64/0,64/C'SVC     ',32/0,8/X'CA',4/X'6',4/X'0',4/X'0',4/X'1',8/72
 GEN 64/0,64/C'LEAR    ',32/0,8/X'82',4/X'0',4/X'4',4/X'2',4/X'3',8/15
 GEN 64/0,64/C'SIO     ',32/0,8/X'FE',4/X'7',4/X'2',4/X'0',4/X'3',8/74
 GEN 64/0,64/C'TIO     ',32/0,8/X'FE',4/X'7',4/X'3',4/X'0',4/X'3',8/74
 GEN 64/0,64/C'HIO     ',32/0,8/X'FE',4/X'7',4/X'6',4/X'0',4/X'3',8/74
 GEN 64/0,64/C'GRIO    ',32/0,8/X'FE',4/X'7',4/X'7',4/X'0',4/X'3',8/74
 GEN 64/0,64/C'ECI     ',32/0,8/X'FE',4/X'7',4/X'C',4/X'0',4/X'3',8/74
 GEN 64/0,64/C'DCI     ',32/0,8/X'FE',4/X'7',4/X'D',4/X'0',4/X'3',8/74
 GEN 64/0,64/C'ACI     ',32/0,8/X'FE',4/X'7',4/X'E',4/X'0',4/X'3',8/74
 GEN 64/0,64/C'DACI    ',32/0,8/X'FE',4/X'7',4/X'F',4/X'0',4/X'3',8/74
 GEN 64/0,64/C'LA      ',32/0,8/X'36',4/X'0',4/X'4',4/X'2',4/X'3',8/15
 GEN 64/0,64/C'LMAP    ',32/0,8/X'2E',4/X'7',4/X'2',4/X'0',4/X'0',8/20
 GEN 64/0,64/C'EAE     ',32/0,8/X'01',4/X'8',4/X'0',4/X'0',4/X'0',8/01
 GEN 64/0,64/C'DAE     ',32/0,8/X'01',4/X'E',4/X'0',4/X'0',4/X'0',8/01
 GEN 64/0,64/C'LCS     ',32/0,8/X'01',4/X'3',4/X'0',4/X'0',4/X'0',8/07
 GEN 64/0,64/C'ES      ',32/0,8/X'01',4/X'4',4/X'0',4/X'0',4/X'8',8/07
 GEN 64/0,64/C'RND     ',32/0,8/X'01',4/X'5',4/X'0',4/X'0',4/X'8',8/07
 GEN 64/0,64/C'HALT    ',32/0,8/X'01',4/X'0',4/X'0',4/X'0',4/X'0',8/01
 GEN 64/0,64/C'WAIT    ',32/0,8/X'01',4/X'1',4/X'0',4/X'0',4/X'0',8/01
 GEN 64/0,64/C'NOP     ',32/0,8/X'01',4/X'2',4/X'0',4/X'0',4/X'0',8/01
 GEN 64/0,64/C'SIPU    ',32/0,8/X'01',4/X'A',4/X'0',4/X'0',4/X'0',8/01
 GEN 64/0,64/C'SEA     ',32/0,8/X'01',4/X'D',4/X'0',4/X'0',4/X'0',8/01
 GEN 64/0,64/C'CEA     ',32/0,8/X'01',4/X'F',4/X'0',4/X'0',4/X'0',8/01
 GEN 64/0,64/C'ANR     ',32/0,8/X'05',4/X'0',4/X'0',4/X'0',4/X'2',8/06
 GEN 64/0,64/C'ORR     ',32/0,8/X'09',4/X'0',4/X'0',4/X'0',4/X'2',8/06
 GEN 64/0,64/C'ORRM    ',32/0,8/X'09',4/X'8',4/X'0',4/X'0',4/X'2',8/06
 GEN 64/0,64/C'EOR     ',32/0,8/X'0D',4/X'0',4/X'0',4/X'0',4/X'2',8/06
 GEN 64/0,64/C'EORM    ',32/0,8/X'0D',4/X'8',4/X'0',4/X'0',4/X'2',8/06
 GEN 64/0,64/C'ZR      ',32/0,8/X'0D',4/X'0',4/X'0',4/X'0',4/X'0',8/12
 GEN 64/0,64/C'CAR     ',32/0,8/X'11',4/X'0',4/X'0',4/X'0',4/X'2',8/06
 GEN 64/0,64/C'CMR     ',32/0,8/X'15',4/X'0',4/X'0',4/X'0',4/X'2',8/06
 GEN 64/0,64/C'SBR     ',32/0,8/X'19',4/X'0',4/X'0',4/X'0',4/X'2',8/09
 GEN 64/0,64/C'ZBR     ',32/0,8/X'1D',4/X'0',4/X'0',4/X'0',4/X'2',8/09
 GEN 64/0,64/C'ABR     ',32/0,8/X'21',4/X'0',4/X'0',4/X'0',4/X'2',8/09
 GEN 64/0,64/C'TBR     ',32/0,8/X'25',4/X'0',4/X'0',4/X'0',4/X'2',8/09
 GEN 64/0,64/C'TRSW    ',32/0,8/X'29',4/X'0',4/X'0',4/X'0',4/X'0',8/08
 GEN 64/0,64/C'TRCC    ',32/0,8/X'29',4/X'5',4/X'0',4/X'0',4/X'0',8/07
 GEN 64/0,64/C'TCCR    ',32/0,8/X'29',4/X'4',4/X'0',4/X'0',4/X'0',8/07
 GEN 64/0,64/C'TRR     ',32/0,8/X'2D',4/X'0',4/X'0',4/X'0',4/X'2',8/06
 GEN 64/0,64/C'TRBR    ',32/0,8/X'2D',4/X'1',4/X'0',4/X'0',4/X'2',8/06
 GEN 64/0,64/C'TBRR    ',32/0,8/X'2D',4/X'2',4/X'0',4/X'0',4/X'2',8/06
 GEN 64/0,64/C'TRC     ',32/0,8/X'2D',4/X'3',4/X'0',4/X'0',4/X'2',8/06
 GEN 64/0,64/C'TRN     ',32/0,8/X'2D',4/X'4',4/X'0',4/X'0',4/X'2',8/06
 GEN 64/0,64/C'XCR     ',32/0,8/X'2D',4/X'5',4/X'0',4/X'0',4/X'2',8/06
 GEN 64/0,64/C'XCBR    ',32/0,8/X'29',4/X'2',4/X'0',4/X'0',4/X'2',8/06
 GEN 64/0,64/C'TRRM    ',32/0,8/X'2D',4/X'8',4/X'0',4/X'0',4/X'2',8/06
 GEN 64/0,64/C'TRCM    ',32/0,8/X'2D',4/X'B',4/X'0',4/X'0',4/X'2',8/06
 GEN 64/0,64/C'TRNM    ',32/0,8/X'2D',4/X'C',4/X'0',4/X'0',4/X'2',8/06
 GEN 64/0,64/C'XCRM    ',32/0,8/X'2D',4/X'D',4/X'0',4/X'0',4/X'2',8/06
 GEN 64/0,64/C'TRSC    ',32/0,8/X'2D',4/X'E',4/X'0',4/X'0',4/X'2',8/06
 GEN 64/0,64/C'TSCR    ',32/0,8/X'2D',4/X'F',4/X'0',4/X'0',4/X'2',8/06
FWCALM   DEQU      $+2W                                         ESCT-32
 GEN 64/0,64/C'CALM    ',32/0,8/X'32',4/X'0',4/X'0',4/X'0',4/X'0',8/04
HWCALM   DEQU      $+2W                                         ESCT-32
 GEN 64/0,64/C'CALM    ',32/0,8/X'31',4/X'0',4/X'0',4/X'0',4/X'0',8/04
 GEN 64/0,64/C'ADR     ',32/0,8/X'39',4/X'0',4/X'0',4/X'0',4/X'2',8/06
 GEN 64/0,64/C'ADRM    ',32/0,8/X'39',4/X'8',4/X'0',4/X'0',4/X'2',8/06
 GEN 64/0,64/C'SUR     ',32/0,8/X'3D',4/X'0',4/X'0',4/X'0',4/X'2',8/06
 GEN 64/0,64/C'SURM    ',32/0,8/X'3D',4/X'8',4/X'0',4/X'0',4/X'2',8/06
 GEN 64/0,64/C'MPR     ',32/0,8/X'41',4/X'0',4/X'0',4/X'0',4/X'6',8/06
 GEN 64/0,64/C'DVR     ',32/0,8/X'45',4/X'0',4/X'0',4/X'0',4/X'6',8/06
 GEN 64/0,64/C'NOR     ',32/0,8/X'61',4/X'0',4/X'0',4/X'0',4/X'2',8/11
 GEN 64/0,64/C'NORD    ',32/0,8/X'65',4/X'0',4/X'0',4/X'0',4/X'A',8/11
 GEN 64/0,64/C'SCZ     ',32/0,8/X'69',4/X'0',4/X'0',4/X'0',4/X'2',8/11
 GEN 64/0,64/C'SLA     ',32/0,8/X'6D',4/X'1',4/X'0',4/X'0',4/X'2',8/10
 GEN 64/0,64/C'SRA     ',32/0,8/X'6D',4/X'0',4/X'0',4/X'0',4/X'2',8/10
 GEN 64/0,64/C'SLL     ',32/0,8/X'71',4/X'1',4/X'0',4/X'0',4/X'2',8/10
 GEN 64/0,64/C'SRL     ',32/0,8/X'71',4/X'0',4/X'0',4/X'0',4/X'2',8/10
 GEN 64/0,64/C'SLC     ',32/0,8/X'75',4/X'1',4/X'0',4/X'0',4/X'2',8/10
 GEN 64/0,64/C'SRC     ',32/0,8/X'75',4/X'0',4/X'0',4/X'0',4/X'2',8/10
 GEN 64/0,64/C'SLAD    ',32/0,8/X'79',4/X'1',4/X'0',4/X'0',4/X'A',8/10
 GEN 64/0,64/C'SRAD    ',32/0,8/X'79',4/X'0',4/X'0',4/X'0',4/X'A',8/10
 GEN 64/0,64/C'SLLD    ',32/0,8/X'7D',4/X'1',4/X'0',4/X'0',4/X'A',8/10
 GEN 64/0,64/C'SRLD    ',32/0,8/X'7D',4/X'0',4/X'0',4/X'0',4/X'A',8/10
 GEN 64/0,64/C'SBM     ',32/0,8/X'9A',4/X'0',4/X'0',4/X'2',4/X'3',8/05
 GEN 64/0,64/C'ZBM     ',32/0,8/X'9E',4/X'0',4/X'0',4/X'2',4/X'3',8/05
 GEN 64/0,64/C'ABM     ',32/0,8/X'A2',4/X'0',4/X'0',4/X'2',4/X'3',8/05
 GEN 64/0,64/C'TBM     ',32/0,8/X'A6',4/X'0',4/X'0',4/X'2',4/X'3',8/05
 GEN 64/0,64/C'EXM     ',32/0,8/X'AA',4/X'0',4/X'1',4/X'1',4/X'1',8/16
 GEN 64/0,64/C'MPMB    ',32/0,8/X'C2',4/X'0',4/X'0',4/X'2',4/X'B',8/15
 GEN 64/0,64/C'MPMH    ',32/0,8/X'C2',4/X'0',4/X'1',4/X'2',4/X'B',8/15
 GEN 64/0,64/C'MPMW    ',32/0,8/X'C2',4/X'0',4/X'2',4/X'2',4/X'B',8/15
 GEN 64/0,64/C'DVMB    ',32/0,8/X'C6',4/X'0',4/X'0',4/X'2',4/X'B',8/15
 GEN 64/0,64/C'DVMH    ',32/0,8/X'C6',4/X'0',4/X'1',4/X'2',4/X'B',8/15
 GEN 64/0,64/C'DVMW    ',32/0,8/X'C6',4/X'0',4/X'2',4/X'2',4/X'B',8/15
 GEN 64/0,64/C'LI      ',32/0,8/X'CA',4/X'0',4/X'0',4/X'0',4/X'2',8/19
 GEN 64/0,64/C'ADI     ',32/0,8/X'CA',4/X'1',4/X'0',4/X'0',4/X'2',8/19
 GEN 64/0,64/C'SUI     ',32/0,8/X'CA',4/X'2',4/X'0',4/X'0',4/X'2',8/19
 GEN 64/0,64/C'MPI     ',32/0,8/X'CA',4/X'3',4/X'0',4/X'0',4/X'A',8/19
 GEN 64/0,64/C'DVI     ',32/0,8/X'CA',4/X'4',4/X'0',4/X'0',4/X'A',8/19
 GEN 64/0,64/C'CI      ',32/0,8/X'CA',4/X'5',4/X'0',4/X'0',4/X'2',8/19
 GEN 64/0,64/C'EXR     ',32/0,8/X'CA',4/X'7',4/X'0',4/X'0',4/X'0',8/20
 GEN 64/0,64/C'EXRR    ',32/0,8/X'CA',4/X'7',4/X'2',4/X'0',4/X'0',8/20
 GEN 64/0,64/C'LF      ',32/0,8/X'CE',4/X'0',4/X'2',4/X'2',4/X'3',8/15
 GEN 64/0,64/C'LFBR    ',32/0,8/X'CE',4/X'0',4/X'6',4/X'2',4/X'3',8/15
 GEN 64/0,64/C'LEA     ',32/0,8/X'D2',4/X'0',4/X'4',4/X'2',4/X'3',8/15
 GEN 64/0,64/C'STF     ',32/0,8/X'DE',4/X'0',4/X'2',4/X'2',4/X'3',8/15
 GEN 64/0,64/C'STFBR   ',32/0,8/X'DE',4/X'0',4/X'6',4/X'2',4/X'3',8/15
 GEN 64/0,64/C'ADFW    ',32/0,8/X'E2',4/X'1',4/X'2',4/X'2',4/X'3',8/18
 GEN 64/0,64/C'ADFD    ',32/0,8/X'E2',4/X'1',4/X'3',4/X'2',4/X'3',8/18
 GEN 64/0,64/C'SUFW    ',32/0,8/X'E2',4/X'0',4/X'2',4/X'2',4/X'3',8/18
 GEN 64/0,64/C'SUFD    ',32/0,8/X'E2',4/X'0',4/X'3',4/X'2',4/X'3',8/18
 GEN 64/0,64/C'MPFW    ',32/0,8/X'E6',4/X'1',4/X'2',4/X'2',4/X'3',8/18
 GEN 64/0,64/C'MPFD    ',32/0,8/X'E6',4/X'1',4/X'3',4/X'2',4/X'3',8/18
 GEN 64/0,64/C'DVFW    ',32/0,8/X'E6',4/X'0',4/X'2',4/X'2',4/X'3',8/18
 GEN 64/0,64/C'DVFD    ',32/0,8/X'E6',4/X'0',4/X'3',4/X'2',4/X'3',8/18
 GEN 64/0,64/C'BCT     ',32/0,8/X'EE',4/X'0',4/X'1',4/X'2',4/X'3',8/15
 GEN 64/0,64/C'BU      ',32/0,8/X'EE',4/X'0',4/X'1',4/X'1',4/X'1',8/16
 GEN 64/0,64/C'BFT     ',32/0,8/X'F2',4/X'0',4/X'1',4/X'1',4/X'1',8/16
 GEN 64/0,64/C'BCF     ',32/0,8/X'F2',4/X'0',4/X'1',4/X'2',4/X'3',8/15
 GEN 64/0,64/C'BIB     ',32/0,8/X'F6',4/X'0',4/X'1',4/X'2',4/X'2',8/17
 GEN 64/0,64/C'BIH     ',32/0,8/X'F6',4/X'1',4/X'1',4/X'2',4/X'2',8/17
 GEN 64/0,64/C'BIW     ',32/0,8/X'F6',4/X'2',4/X'1',4/X'2',4/X'2',8/17
 GEN 64/0,64/C'BID     ',32/0,8/X'F6',4/X'3',4/X'1',4/X'2',4/X'2',8/17
 GEN 64/0,64/C'ZMB     ',32/0,8/X'FA',4/X'0',4/X'0',4/X'1',4/X'1',8/24
 GEN 64/0,64/C'ZMH     ',32/0,8/X'FA',4/X'0',4/X'1',4/X'1',4/X'1',8/24
 GEN 64/0,64/C'ZMW     ',32/0,8/X'FA',4/X'0',4/X'2',4/X'1',4/X'1',8/24
 GEN 64/0,64/C'ZMD     ',32/0,8/X'FA',4/X'0',4/X'3',4/X'1',4/X'1',8/24
 GEN 64/0,64/C'BL      ',32/0,8/X'FA',4/X'1',4/X'1',4/X'1',4/X'1',8/16
 GEN 64/0,64/C'BRI     ',32/0,8/X'FA',4/X'2',4/X'1',4/X'1',4/X'1',8/16
 GEN 64/0,64/C'TRP     ',32/0,8/X'FA',4/X'6',4/X'0',4/X'0',4/X'2',8/14
 GEN 64/0,64/C'TPR     ',32/0,8/X'FA',4/X'7',4/X'0',4/X'0',4/X'2',8/14
 GEN 64/0,64/C'EI      ',32/0,8/X'FE',4/X'0',4/X'0',4/X'0',4/X'1',8/22
 GEN 64/0,64/C'DI      ',32/0,8/X'FE',4/X'1',4/X'0',4/X'0',4/X'1',8/22
 GEN 64/0,64/C'RI      ',32/0,8/X'FE',4/X'2',4/X'0',4/X'0',4/X'1',8/22
 GEN 64/0,64/C'AI      ',32/0,8/X'FE',4/X'3',4/X'0',4/X'0',4/X'1',8/22
 GEN 64/0,64/C'DAI     ',32/0,8/X'FE',4/X'4',4/X'0',4/X'0',4/X'1',8/22
 GEN 64/0,64/C'TD      ',32/0,8/X'FE',4/X'5',4/X'0',4/X'0',4/X'2',8/22
 GEN 64/0,64/C'CD      ',32/0,8/X'FE',4/X'6',4/X'0',4/X'0',4/X'2',8/22
 GEN 64/0,64/C'CDL     ',32/0,8/X'FE',4/X'6',4/X'0',4/X'0',4/X'0',8/21
 GEN 64/0,64/C'DATA    ',32/0,8/X'00',4/X'0',4/X'0',4/X'0',4/X'0',8/29
 GEN 64/0,64/C'RES     ',32/0,8/X'00',4/X'0',4/X'0',4/X'0',4/X'0',8/41
 GEN 64/0,64/C'GEN     ',32/0,8/X'00',4/X'0',4/X'0',4/X'0',4/X'0',8/30
 GEN 64/0,64/C'EQU     ',32/0,8/X'00',4/X'0',4/X'0',4/X'1',4/X'0',8/40
 GEN 64/0,64/C'CEQU    ',32/0,8/X'00',4/X'0',4/X'0',4/X'1',4/X'0',8/68
 GEN 64/0,64/C'DEQU    ',32/0,8/X'00',4/X'0',4/X'0',4/X'1',4/X'0',8/66
 GEN 64/0,64/C'AC      ',32/0,8/X'02',4/X'0',4/X'0',4/X'1',4/X'1',8/13
 GEN 64/0,64/C'ACB     ',32/0,8/X'02',4/X'0',4/X'0',4/X'1',4/X'1',8/13
 GEN 64/0,64/C'ACH     ',32/0,8/X'02',4/X'0',4/X'1',4/X'1',4/X'1',8/13
 GEN 64/0,64/C'ACW     ',32/0,8/X'02',4/X'0',4/X'2',4/X'1',4/X'1',8/13
 GEN 64/0,64/C'ACD     ',32/0,8/X'02',4/X'0',4/X'3',4/X'1',4/X'1',8/13
 GEN 64/0,64/C'BACH    ',32/0,8/X'02',4/X'0',4/X'1',4/X'1',4/X'1',8/23
 GEN 64/0,64/C'BACW    ',32/0,8/X'02',4/X'0',4/X'2',4/X'1',4/X'1',8/23
 GEN 64/0,64/C'ORG     ',32/0,8/X'00',4/X'0',4/X'0',4/X'0',4/X'0',8/37
 GEN 64/0,64/C'CORG    ',32/0,8/X'00',4/X'0',4/X'0',4/X'0',4/X'0',8/69
 GEN 64/0,64/C'DORG    ',32/0,8/X'00',4/X'0',4/X'0',4/X'0',4/X'0',8/67
 GEN 64/0,64/C'SSECT   ',32/0,8/X'00',4/X'1',4/X'0',4/X'0',4/X'0',8/47
 GEN 64/0,64/C'SORG    ',32/0,8/X'00',4/X'2',4/X'0',4/X'0',4/X'0',8/47
 GEN 64/0,64/C'SEXT    ',32/0,8/X'00',4/X'3',4/X'0',4/X'0',4/X'0',8/47
 GEN 64/0,64/C'REL     ',32/0,8/X'00',4/X'4',4/X'0',4/X'0',4/X'0',8/38
 GEN 64/0,64/C'ABS     ',32/0,8/X'00',4/X'0',4/X'0',4/X'0',4/X'0',8/38
 GEN 64/0,64/C'DEF     ',32/0,8/X'00',4/X'0',4/X'0',4/X'0',4/X'0',8/36
 GEN 64/0,64/C'SDEF    ',32/0,8/X'00',4/X'2',4/X'0',4/X'0',4/X'0',8/36
 GEN 64/0,64/C'PAGE    ',32/0,8/X'00',4/X'0',4/X'0',4/X'0',4/X'0',8/44
 GEN 64/0,64/C'LIST    ',32/0,8/X'00',4/X'0',4/X'0',4/X'0',4/X'0',8/45
 GEN 64/0,64/C'REIS    ',32/0,8/X'00',4/X'0',4/X'0',4/X'0',4/X'0',8/33
 GEN 64/0,64/C'SEIS    ',32/0,8/X'00',4/X'0',4/X'0',4/X'0',4/X'0',8/33
 GEN 64/0,64/C'EXT     ',32/0,8/X'00',4/X'1',4/X'0',4/X'0',4/X'0',8/36
 GEN 64/0,64/C'REZ     ',32/0,8/X'00',4/X'0',4/X'0',4/X'0',4/X'0',8/65
 GEN 64/0,64/C'END     ',32/0,8/X'02',4/X'0',4/X'0',4/X'1',4/X'0',8/34
 GEN 64/0,64/C'ANOP    ',32/0,8/X'00',4/X'0',4/X'0',4/X'0',4/X'0',8/48
 GEN 64/0,64/C'IFF     ',32/0,8/X'01',4/X'0',4/X'0',4/X'0',4/X'0',8/49
 GEN 64/0,64/C'IFT     ',32/0,8/X'00',4/X'0',4/X'0',4/X'0',4/X'0',8/49
 GEN 64/0,64/C'IFTDEF  ',32/0,8/X'02',4/X'0',4/X'0',4/X'0',4/X'0',8/49
 GEN 64/0,64/C'IFFDEF  ',32/0,8/X'03',4/X'0',4/X'0',4/X'0',4/X'0',8/49
 GEN 64/0,64/C'IFP     ',32/0,8/X'14',4/X'0',4/X'0',4/X'0',4/X'0',8/49
 GEN 64/0,64/C'IFA     ',32/0,8/X'15',4/X'0',4/X'0',4/X'0',4/X'0',8/49
 GEN 64/0,64/C'SETF    ',32/0,8/X'00',4/X'0',4/X'0',4/X'0',4/X'0',8/52
 GEN 64/0,64/C'SETT    ',32/0,8/X'01',4/X'0',4/X'0',4/X'0',4/X'0',8/52
 GEN 64/0,64/C'SET     ',32/0,8/X'02',4/X'0',4/X'0',4/X'0',4/X'0',8/52
 GEN 64/0,64/C'OPTS    ',32/0,8/X'03',4/X'0',4/X'0',4/X'0',4/X'0',8/52
 GEN 64/0,64/C'OPTR    ',32/0,8/X'04',4/X'0',4/X'0',4/X'0',4/X'0',8/52
 GEN 64/0,64/C'OPTT    ',32/0,8/X'05',4/X'0',4/X'0',4/X'0',4/X'0',8/52
 GEN 64/0,64/C'DEFM    ',32/0,8/X'00',4/X'0',4/X'0',4/X'0',4/X'0',8/50
 GEN 64/0,64/C'ENDM    ',32/0,8/X'00',4/X'0',4/X'0',4/X'0',4/X'0',8/51
 GEN 64/0,64/C'GOTO    ',32/0,8/X'00',4/X'0',4/X'0',4/X'0',4/X'0',8/53
 GEN 64/0,64/C'ENDR    ',32/0,8/X'00',4/X'0',4/X'0',4/X'0',4/X'0',8/54
 GEN 64/0,64/C'REPT    ',32/0,8/X'00',4/X'0',4/X'0',4/X'0',4/X'0',8/55
 GEN 64/0,64/C'FORM    ',32/0,8/X'00',4/X'0',4/X'0',4/X'0',4/X'0',8/57
         IFT       CAID,SKIP                                    *CAID*
* NEW DEBUGGER OPCODES                                          *CAID*
 GEN 64/0,64/C'.SRC    ',32/0,8/X'00',4/X'0',4/X'0',4/X'0',4/X'0',8/61
 GEN 64/0,64/C'.COM    ',32/0,8/X'00',4/X'1',4/X'0',4/X'0',4/X'0',8/61
 GEN 64/0,64/C'.STAB   ',32/0,8/X'00',4/X'2',4/X'0',4/X'0',4/X'0',8/61
 GEN 64/0,64/C'.STABC  ',32/0,8/X'00',4/X'3',4/X'0',4/X'0',4/X'0',8/61
 GEN 64/0,64/C'.SYM    ',32/0,8/X'00',4/X'4',4/X'0',4/X'0',4/X'0',8/61
 GEN 64/0,64/C'.END    ',32/0,8/X'00',4/X'5',4/X'0',4/X'0',4/X'0',8/61
 GEN 64/0,64/C'.XEQ    ',32/0,8/X'00',4/X'6',4/X'0',4/X'0',4/X'0',8/61
 GEN 64/0,64/C'.ARG    ',32/0,8/X'00',4/X'7',4/X'0',4/X'0',4/X'0',8/61
SKIP     ANOP                                                   *CAID*
 GEN 64/0,64/C'LPSDCM  ',32/0,8/X'FA',4/X'5',4/X'2',4/X'1',4/X'1',8/16
 GEN 64/0,64/C'TMAPR   ',32/0,8/X'2D',4/X'A',4/X'0',4/X'0',4/X'2',8/06
 GEN 64/0,64/C'SETCPU  ',32/0,8/X'2D',4/X'9',4/X'0',4/X'0',4/X'0',8/71
 GEN 64/0,64/C'RDSTS   ',32/0,8/X'01',4/X'9',4/X'0',4/X'0',4/X'0',8/71
 GEN 64/0,64/C'RPSWT   ',32/0,8/X'05',4/X'B',4/X'0',4/X'0',4/X'0',8/71
 GEN 64/0,64/C'CMC     ',32/0,8/X'05',4/X'A',4/X'0',4/X'0',4/X'0',8/71
 GEN 64/0,64/C'SMC     ',32/0,8/X'05',4/X'7',4/X'0',4/X'0',4/X'0',8/71
 GEN 64/0,64/C'UNDEF   ',32/0,8/X'05',4/X'9',4/X'0',4/X'0',4/X'0',8/01
 GEN 64/0,64/C'ADRFW   ',32/0,8/X'39',4/X'1',4/X'0',4/X'0',4/X'2',8/06
 GEN 64/0,64/C'SURFW   ',32/0,8/X'39',4/X'3',4/X'0',4/X'0',4/X'2',8/06
 GEN 64/0,64/C'MPRFW   ',32/0,8/X'39',4/X'6',4/X'0',4/X'0',4/X'2',8/06
 GEN 64/0,64/C'DVRFW   ',32/0,8/X'39',4/X'4',4/X'0',4/X'0',4/X'2',8/06
 GEN 64/0,64/C'FLTW    ',32/0,8/X'39',4/X'7',4/X'0',4/X'0',4/X'2',8/06
 GEN 64/0,64/C'FIXW    ',32/0,8/X'39',4/X'5',4/X'0',4/X'0',4/X'2',8/06
 GEN 64/0,64/C'ADRFD   ',32/0,8/X'39',4/X'9',4/X'0',4/X'0',4/X'E',8/06
 GEN 64/0,64/C'SURFD   ',32/0,8/X'39',4/X'B',4/X'0',4/X'0',4/X'E',8/06
 GEN 64/0,64/C'MPRFD   ',32/0,8/X'39',4/X'E',4/X'0',4/X'0',4/X'E',8/06
 GEN 64/0,64/C'DVRFD   ',32/0,8/X'39',4/X'C',4/X'0',4/X'0',4/X'E',8/06
 GEN 64/0,64/C'FLTD    ',32/0,8/X'39',4/X'F',4/X'0',4/X'0',4/X'E',8/06
 GEN 64/0,64/C'FIXD    ',32/0,8/X'39',4/X'D',4/X'0',4/X'0',4/X'E',8/06
 GEN 64/0,64/C'STPIO   ',32/0,8/X'FE',4/X'7',4/X'4',4/X'0',4/X'3',8/74
 GEN 64/0,64/C'RSCHNL  ',32/0,8/X'FE',4/X'7',4/X'5',4/X'0',4/X'3',8/74
 GEN 64/0,64/C'RSCTL   ',32/0,8/X'FE',4/X'7',4/X'8',4/X'0',4/X'3',8/74
 GEN 64/0,64/C'ECWCS   ',32/0,8/X'FE',4/X'7',4/X'9',4/X'0',4/X'3',8/74
 GEN 64/0,64/C'WCWCS   ',32/0,8/X'FE',4/X'7',4/X'B',4/X'0',4/X'3',8/74
 GEN 64/0,64/C'PROGRAM ',32/0,8/X'00',4/X'0',4/X'0',4/X'0',4/X'0',8/35
 GEN 64/0,64/C'BOUND   ',32/0,8/X'00',4/X'0',4/X'0',4/X'0',4/X'0',8/39
 GEN 64/0,64/C'COMMON  ',32/0,8/X'00',4/X'0',4/X'0',4/X'0',4/X'0',8/42
 GEN 64/0,64/C'TITLE   ',32/0,8/X'00',4/X'0',4/X'0',4/X'0',4/X'0',8/43
 GEN 64/0,64/C'SPACE   ',32/0,8/X'00',4/X'0',4/X'0',4/X'0',4/X'0',8/46
 GEN 64/0,64/C'LPOOL   ',32/0,8/X'02',4/X'0',4/X'0',4/X'0',4/X'0',8/64
 GEN 64/0,64/C'DSECT   ',32/0,8/X'00',4/X'4',4/X'0',4/X'0',4/X'0',8/38
         IFF       UNIXF,SKIP                                   *JCB*
 GEN 64/0,64/C'CSECT   ',32/0,8/X'00',4/X'C',4/X'0',4/X'0',4/X'0',8/38
SKIP     ANOP                                                   *JCB*
         IFT       UNIXF,SKIP                                   *JCB*
 GEN 64/0,64/C'CSECT   ',32/0                                   *JCB*
SECT.FLG GEN       8/X'00',4/X'C',4/X'0',4/X'0',4/X'0',8/38     *JCB*
SKIP     ANOP                                                   *JCB*
 GEN 64/0,64/C'EXITM   ',32/0,8/X'00',4/X'0',4/X'0',4/X'0',4/X'0',8/56
 GEN 64/0,64/C'DATAONLY',32/0,8/X'00',4/X'0',4/X'0',4/X'0',4/X'0',8/62
 GEN 64/0,64/C'ENDDATA ',32/0,8/X'00',4/X'0',4/X'0',4/X'0',4/X'0',8/63
 GEN 64/0,64/C'SCSR    ',32/0,8/X'05',4/X'1',4/X'0',4/X'0',4/X'0',8/07
 GEN 64/0,64/C'SDSR    ',32/0,8/X'05',4/X'2',4/X'0',4/X'0',4/X'0',8/07
 GEN 64/0,64/C'PIT     ',32/0,8/X'05',4/X'4',4/X'0',4/X'0',4/X'0',8/01
 GEN 64/0,64/C'DCSR    ',32/0,8/X'05',4/X'5',4/X'0',4/X'0',4/X'0',8/07
 GEN 64/0,64/C'DDSR    ',32/0,8/X'05',4/X'6',4/X'0',4/X'0',4/X'0',8/07
 GEN 64/0,64/C'SEAR    ',32/0,8/X'05',4/X'E',4/X'0',4/X'0',4/X'0',8/01
 GEN 64/0,64/C'CEAR    ',32/0,8/X'05',4/X'F',4/X'0',4/X'0',4/X'0',8/01
 GEN 64/0,64/C'DMSINT  ',32/0,8/X'0D',4/X'1',4/X'0',4/X'0',4/X'2',8/06
 GEN 64/0,64/C'RMSINT  ',32/0,8/X'0D',4/X'1',4/X'0',4/X'0',4/X'2',8/06
 GEN 64/0,64/C'MDMSW   ',32/0,8/X'0D',4/X'2',4/X'0',4/X'0',4/X'6',8/06
 GEN 64/0,64/C'MRMSW   ',32/0,8/X'0D',4/X'2',4/X'0',4/X'0',4/X'6',8/06
 GEN 64/0,64/C'ZBDMS   ',32/0,8/X'0D',4/X'1',4/X'0',4/X'0',4/X'2',8/09
 GEN 64/0,64/C'ZBRMS   ',32/0,8/X'0D',4/X'1',4/X'0',4/X'0',4/X'2',8/09
 GEN 64/0,64/C'RDMSW   ',32/0,8/X'0D',4/X'3',4/X'0',4/X'0',4/X'2',8/06
 GEN 64/0,64/C'RRMSW   ',32/0,8/X'0D',4/X'3',4/X'0',4/X'0',4/X'2',8/06
 GEN 64/0,64/C'SBDMS   ',32/0,8/X'0D',4/X'3',4/X'0',4/X'0',4/X'2',8/09
 GEN 64/0,64/C'SBRMS   ',32/0,8/X'0D',4/X'3',4/X'0',4/X'0',4/X'2',8/09
 GEN 64/0,64/C'WDMSCS  ',32/0,8/X'0D',4/X'9',4/X'0',4/X'0',4/X'0',8/07
 GEN 64/0,64/C'WRMSCS  ',32/0,8/X'0D',4/X'9',4/X'0',4/X'0',4/X'0',8/07
 GEN 64/0,64/C'RDMSCS  ',32/0,8/X'0D',4/X'A',4/X'0',4/X'0',4/X'0',8/07
 GEN 64/0,64/C'RRMSCS  ',32/0,8/X'0D',4/X'A',4/X'0',4/X'0',4/X'0',8/07
 GEN 64/0,64/C'CGEW    ',32/0,8/X'29',4/X'6',4/X'0',4/X'0',4/X'2',8/06
 GEN 64/0,64/C'CGED    ',32/0,8/X'29',4/X'7',4/X'0',4/X'0',4/X'2',8/06
 GEN 64/0,64/C'CEGW    ',32/0,8/X'29',4/X'A',4/X'0',4/X'0',4/X'2',8/06
 GEN 64/0,64/C'CEGD    ',32/0,8/X'29',4/X'B',4/X'0',4/X'0',4/X'2',8/06
 GEN 64/0,64/C'CXIW    ',32/0,8/X'29',4/X'6',4/X'0',4/X'0',4/X'2',8/06
 GEN 64/0,64/C'CXID    ',32/0,8/X'29',4/X'7',4/X'0',4/X'0',4/X'2',8/06
 GEN 64/0,64/C'CIXW    ',32/0,8/X'29',4/X'A',4/X'0',4/X'0',4/X'2',8/06
 GEN 64/0,64/C'CIXD    ',32/0,8/X'29',4/X'B',4/X'0',4/X'0',4/X'2',8/06
 GEN 64/0,64/C'TC      ',32/0,8/X'CA',4/X'8',4/X'0',4/X'0',4/X'1',8/73
 GEN 64/0,64/C'PINTV   ',32/0,8/X'CA',4/X'9',4/X'0',4/X'0',4/X'2',8/19
 GEN 64/0,64/C'RINTV   ',32/0,8/X'CA',4/X'A',4/X'0',4/X'0',4/X'2',8/19
*
*        RISC STYLE FLOATING POINT INSTRUCTIONS
*
 GEN 64/0,64/C'MAFW    ',32/0,8/X'09',4/X'1',4/X'0',4/X'0',4/X'2',8/06
 GEN 64/0,64/C'MAFD    ',32/0,8/X'09',4/X'2',4/X'0',4/X'0',4/X'E',8/06
 GEN 64/0,64/C'ATFW    ',32/0,8/X'09',4/X'5',4/X'0',4/X'0',4/X'2',8/77
 GEN 64/0,64/C'ATFD    ',32/0,8/X'09',4/X'6',4/X'0',4/X'0',4/X'E',8/77
 GEN 64/0,64/C'MTFW    ',32/0,8/X'09',4/X'3',4/X'0',4/X'0',4/X'2',8/77
 GEN 64/0,64/C'MTFD    ',32/0,8/X'09',4/X'4',4/X'0',4/X'0',4/X'E',8/77
 GEN 64/0,64/C'DFWD    ',32/0,8/X'09',4/X'7',4/X'0',4/X'0',4/X'2',8/06
 GEN 64/0,64/C'DFDD    ',32/0,8/X'09',4/X'9',4/X'0',4/X'0',4/X'E',8/06
 GEN 64/0,64/C'DFWN    ',32/0,8/X'09',4/X'A',4/X'0',4/X'0',4/X'2',8/06
 GEN 64/0,64/C'DFDN    ',32/0,8/X'09',4/X'B',4/X'0',4/X'0',4/X'E',8/06
 GEN 64/0,64/C'ABSW    ',32/0,8/X'05',4/X'C',4/X'0',4/X'0',4/X'2',8/06
 GEN 64/0,64/C'ABSD    ',32/0,8/X'05',4/X'D',4/X'0',4/X'0',4/X'E',8/06
* NEW IEEE Conversion opcodes                                   IEEE-MOD
 GEN 64/0,64/C'.CF2D   ',32/0,8/X'01',4/X'0',4/X'0',4/X'0',4/X'0',8/79
 GEN 64/0,64/C'.CD2F   ',32/0,8/X'01',4/X'0',4/X'0',4/X'0',4/X'0',8/80
*-----------------------------------------------------------------------
 GEN 64/0,64/C'TFWR    ',32/0,8/X'29',4/X'D',4/X'0',4/X'0',4/X'1',8/75
 GEN 64/0,64/C'TFDR    ',32/0,8/X'29',4/X'F',4/X'0',4/X'0',4/X'9',8/75
 GEN 64/0,64/C'TRFW    ',32/0,8/X'09',4/X'E',4/X'0',4/X'0',4/X'1',8/75
 GEN 64/0,64/C'TRFD    ',32/0,8/X'09',4/X'F',4/X'0',4/X'0',4/X'9',8/75
 GEN 64/0,64/C'AFFW    ',32/0,8/X'09',4/X'C',4/X'0',4/X'0',4/X'1',8/75
 GEN 64/0,64/C'AFFD    ',32/0,8/X'09',4/X'D',4/X'0',4/X'0',4/X'9',8/75
 GEN 64/0,64/C'SFFW    ',32/0,8/X'09',4/X'C',4/X'2',4/X'0',4/X'1',8/75
 GEN 64/0,64/C'SFFD    ',32/0,8/X'09',4/X'D',4/X'2',4/X'0',4/X'9',8/75
 GEN 64/0,64/C'MFFW    ',32/0,8/X'09',4/X'C',4/X'4',4/X'0',4/X'1',8/75
 GEN 64/0,64/C'MFFD    ',32/0,8/X'09',4/X'D',4/X'4',4/X'0',4/X'9',8/75
 GEN 64/0,64/C'HLD1    ',32/0,8/X'0D',4/X'B',4/X'2',4/X'0',4/X'0',8/76
 GEN 64/0,64/C'HLD2    ',32/0,8/X'0D',4/X'B',4/X'4',4/X'0',4/X'0',8/76
 GEN 64/0,64/C'HLD3    ',32/0,8/X'0D',4/X'B',4/X'6',4/X'0',4/X'0',8/76
 GEN 64/0,64/C'TSPR    ',32/0,8/X'29',4/X'D',4/X'2',4/X'0',4/X'1',8/75
 GEN 64/0,64/C'TDPR    ',32/0,8/X'29',4/X'F',4/X'2',4/X'0',4/X'9',8/75
 GEN 64/0,64/C'FLFW    ',32/0,8/X'09',4/X'E',4/X'2',4/X'0',4/X'1',8/75
 GEN 64/0,64/C'FLFD    ',32/0,8/X'09',4/X'F',4/X'2',4/X'0',4/X'9',8/75
 GEN 64/0,64/C'TSFR    ',32/0,8/X'29',4/X'D',4/X'4',4/X'0',4/X'1',8/75
 GEN 64/0,64/C'TDFR    ',32/0,8/X'29',4/X'F',4/X'4',4/X'0',4/X'9',8/75
 GEN 64/0,64/C'CAFW    ',32/0,8/X'29',4/X'9',4/X'0',4/X'0',4/X'2',8/06
 GEN 64/0,64/C'CAFD    ',32/0,8/X'2D',4/X'6',4/X'0',4/X'0',4/X'E',8/06
 GEN 64/0,64/C'LPSDR   ',32/0,8/X'05',4/X'3',4/X'2',4/X'0',4/X'1',8/75
 GEN 64/0,64/C'LPSDCMR ',32/0,8/X'05',4/X'3',4/X'4',4/X'0',4/X'1',8/75
 GEN 64/0,64/C'ERF     ',32/0,8/X'05',4/X'4',4/X'2',4/X'0',4/X'0',8/75
 GEN 64/0,64/C'DRF     ',32/0,8/X'05',4/X'4',4/X'4',4/X'0',4/X'0',8/75
 GEN 64/0,64/C'RST     ',32/0,8/X'05',4/X'3',4/X'0',4/X'0',4/X'0',8/01
 GEN 64/0,64/C'GFPC    ',32/0,8/X'CA',4/X'D',4/X'0',4/X'0',4/X'6',8/78
 GEN 64/0,64/C'RFPW    ',32/0,8/X'CA',4/X'E',4/X'0',4/X'0',4/X'2',8/78
 GEN 64/0,64/C'RFPD    ',32/0,8/X'CA',4/X'F',4/X'0',4/X'0',4/X'6',8/78
 GEN 64/0,64/C'MMBR    ',32/0,8/X'0D',4/X'1',4/X'0',4/X'0',4/X'1',8/75
OPSEND   DEQU      $               END OF OPCODE TABLE          ESCT-32
*
* (C) COPYRIGHT 1983 ENCORE COMPUTER CORPORATION
*     ALL RIGHTS RESERVED
*
         TITLE     OPSTABBA - BASE ADRRESS MODE INSTRUCTIONS
*
*-----------------------------------------------------------------------
*
*   OPSTABBA CHANGE HISTORY:
*
* THE FOLLOWING AC DIRECTIVES WERE CHANGED FROM PROCESSING      EASC-32
* VECTOR 14 TO PROCESSING VECTOR 11 TO SUPPORT THE AUTO         EASC-32
* SECTIONING OPTION. THIS SEPARATES AC? DIRECTIVES WHICH MUST   EASC-32
* GENERATE DSECT CODE FROM OTHER VECTOR 14 OPERATIONS WHICH     EASC-32
* MUST GENERATE CSECT CODE.  VECTOR 11 WAS PREVIOUSLY UNUSED.   EASC-32
* A CHANGE IN THE PROCESSING VECTOR JUMP TABLE IS ALSO MADE     EASC-32
*                                                               EASC-32
*---------------------------------------------------------------EASC-32
         BOUND     1D
OPSTABBA DEQU      $               BEGINNING ADDR OF BASE OPCO  ESCT-32
 GEN 64/0,64/C'LPSD    ',32/0,8/X'FA',4/X'3',4/X'2',4/X'1',4/X'1',8/16
 GEN 64/0,64/C'LB      ',32/0,8/X'AE',4/X'8',4/X'0',4/X'2',4/X'3',8/15
 GEN 64/0,64/C'LH      ',32/0,8/X'AE',4/X'0',4/X'1',4/X'2',4/X'3',8/15
 GEN 64/0,64/C'LW      ',32/0,8/X'AE',4/X'0',4/X'2',4/X'2',4/X'3',8/15
 GEN 64/0,64/C'LD      ',32/0,8/X'AE',4/X'0',4/X'3',4/X'2',4/X'B',8/15
 GEN 64/0,64/C'LWBR    ',32/0,8/X'5E',4/X'0',4/X'2',4/X'2',4/X'3',8/15
 GEN 64/0,64/C'STB     ',32/0,8/X'D6',4/X'8',4/X'0',4/X'2',4/X'3',8/15
 GEN 64/0,64/C'STH     ',32/0,8/X'D6',4/X'0',4/X'1',4/X'2',4/X'3',8/15
 GEN 64/0,64/C'STW     ',32/0,8/X'D6',4/X'0',4/X'2',4/X'2',4/X'3',8/15
 GEN 64/0,64/C'STD     ',32/0,8/X'D6',4/X'0',4/X'3',4/X'2',4/X'B',8/15
 GEN 64/0,64/C'STWBR   ',32/0,8/X'56',4/X'0',4/X'2',4/X'2',4/X'3',8/15
 GEN 64/0,64/C'LCB     ',32/0,8/X'AE',4/X'8',4/X'0',4/X'2',4/X'3',8/15
 GEN 64/0,64/C'LCH     ',32/0,8/X'AE',4/X'0',4/X'1',4/X'2',4/X'3',8/15
 GEN 64/0,64/C'LCW     ',32/0,8/X'AE',4/X'0',4/X'2',4/X'2',4/X'3',8/15
 GEN 64/0,64/C'LCD     ',32/0,8/X'AE',4/X'0',4/X'3',4/X'2',4/X'B',8/15
 GEN 64/0,64/C'STCB    ',32/0,8/X'D6',4/X'8',4/X'0',4/X'2',4/X'3',8/15
 GEN 64/0,64/C'STCH    ',32/0,8/X'D6',4/X'0',4/X'1',4/X'2',4/X'3',8/15
 GEN 64/0,64/C'STCW    ',32/0,8/X'D6',4/X'0',4/X'2',4/X'2',4/X'3',8/15
 GEN 64/0,64/C'STCD    ',32/0,8/X'D6',4/X'0',4/X'3',4/X'2',4/X'B',8/15
 GEN 64/0,64/C'REIS    ',32/0,8/X'00',4/X'0',4/X'0',4/X'0',4/X'0',8/48
 GEN 64/0,64/C'SEIS    ',32/0,8/X'00',4/X'0',4/X'0',4/X'0',4/X'0',8/48
 GEN 64/0,64/C'LNB     ',32/0,8/X'B6',4/X'8',4/X'0',4/X'2',4/X'3',8/15
 GEN 64/0,64/C'LNH     ',32/0,8/X'B6',4/X'0',4/X'1',4/X'2',4/X'3',8/15
 GEN 64/0,64/C'LNW     ',32/0,8/X'B6',4/X'0',4/X'2',4/X'2',4/X'3',8/15
 GEN 64/0,64/C'LND     ',32/0,8/X'B6',4/X'0',4/X'3',4/X'2',4/X'B',8/15
 GEN 64/0,64/C'LMB     ',32/0,8/X'B2',4/X'8',4/X'0',4/X'2',4/X'3',8/15
 GEN 64/0,64/C'LMH     ',32/0,8/X'B2',4/X'0',4/X'1',4/X'2',4/X'3',8/15
 GEN 64/0,64/C'LMW     ',32/0,8/X'B2',4/X'0',4/X'2',4/X'2',4/X'3',8/15
 GEN 64/0,64/C'LMD     ',32/0,8/X'B2',4/X'0',4/X'3',4/X'2',4/X'B',8/15
 GEN 64/0,64/C'STMB    ',32/0,8/X'DA',4/X'8',4/X'0',4/X'2',4/X'3',8/15
 GEN 64/0,64/C'STMH    ',32/0,8/X'DA',4/X'0',4/X'1',4/X'2',4/X'3',8/15
 GEN 64/0,64/C'STMW    ',32/0,8/X'DA',4/X'0',4/X'2',4/X'2',4/X'3',8/15
 GEN 64/0,64/C'STMD    ',32/0,8/X'DA',4/X'0',4/X'3',4/X'2',4/X'B',8/15
 GEN 64/0,64/C'ADMB    ',32/0,8/X'BA',4/X'8',4/X'0',4/X'2',4/X'3',8/15
 GEN 64/0,64/C'ADMH    ',32/0,8/X'BA',4/X'0',4/X'1',4/X'2',4/X'3',8/15
 GEN 64/0,64/C'ADMW    ',32/0,8/X'BA',4/X'0',4/X'2',4/X'2',4/X'3',8/15
 GEN 64/0,64/C'ADMD    ',32/0,8/X'BA',4/X'0',4/X'3',4/X'2',4/X'B',8/15
 GEN 64/0,64/C'SUMB    ',32/0,8/X'BE',4/X'8',4/X'0',4/X'2',4/X'3',8/15
 GEN 64/0,64/C'SUMH    ',32/0,8/X'BE',4/X'0',4/X'1',4/X'2',4/X'3',8/15
 GEN 64/0,64/C'SUMW    ',32/0,8/X'BE',4/X'0',4/X'2',4/X'2',4/X'3',8/15
 GEN 64/0,64/C'SUMD    ',32/0,8/X'BE',4/X'0',4/X'3',4/X'2',4/X'B',8/15
 GEN 64/0,64/C'CAMB    ',32/0,8/X'92',4/X'8',4/X'0',4/X'2',4/X'3',8/15
 GEN 64/0,64/C'CAMH    ',32/0,8/X'92',4/X'0',4/X'1',4/X'2',4/X'3',8/15
 GEN 64/0,64/C'CAMW    ',32/0,8/X'92',4/X'0',4/X'2',4/X'2',4/X'3',8/15
 GEN 64/0,64/C'CAMD    ',32/0,8/X'92',4/X'0',4/X'3',4/X'2',4/X'B',8/15
 GEN 64/0,64/C'CMMB    ',32/0,8/X'96',4/X'8',4/X'0',4/X'2',4/X'3',8/15
 GEN 64/0,64/C'CMMH    ',32/0,8/X'96',4/X'0',4/X'1',4/X'2',4/X'3',8/15
 GEN 64/0,64/C'CMMW    ',32/0,8/X'96',4/X'0',4/X'2',4/X'2',4/X'3',8/15
 GEN 64/0,64/C'CMMD    ',32/0,8/X'96',4/X'0',4/X'3',4/X'2',4/X'B',8/15
 GEN 64/0,64/C'ANMB    ',32/0,8/X'86',4/X'8',4/X'0',4/X'2',4/X'3',8/15
 GEN 64/0,64/C'ANMH    ',32/0,8/X'86',4/X'0',4/X'1',4/X'2',4/X'3',8/15
 GEN 64/0,64/C'ANMW    ',32/0,8/X'86',4/X'0',4/X'2',4/X'2',4/X'3',8/15
 GEN 64/0,64/C'ANMD    ',32/0,8/X'86',4/X'0',4/X'3',4/X'2',4/X'B',8/15
 GEN 64/0,64/C'ORMB    ',32/0,8/X'8A',4/X'8',4/X'0',4/X'2',4/X'3',8/15
 GEN 64/0,64/C'ORMH    ',32/0,8/X'8A',4/X'0',4/X'1',4/X'2',4/X'3',8/15
 GEN 64/0,64/C'ORMW    ',32/0,8/X'8A',4/X'0',4/X'2',4/X'2',4/X'3',8/15
 GEN 64/0,64/C'ORMD    ',32/0,8/X'8A',4/X'0',4/X'3',4/X'2',4/X'B',8/15
 GEN 64/0,64/C'EOMB    ',32/0,8/X'8E',4/X'8',4/X'0',4/X'2',4/X'3',8/15
 GEN 64/0,64/C'EOMH    ',32/0,8/X'8E',4/X'0',4/X'1',4/X'2',4/X'3',8/15
 GEN 64/0,64/C'EOMW    ',32/0,8/X'8E',4/X'0',4/X'2',4/X'2',4/X'3',8/15
 GEN 64/0,64/C'EOMD    ',32/0,8/X'8E',4/X'0',4/X'3',4/X'2',4/X'B',8/15
 GEN 64/0,64/C'ARMB    ',32/0,8/X'EA',4/X'8',4/X'0',4/X'2',4/X'3',8/15
 GEN 64/0,64/C'ARMH    ',32/0,8/X'EA',4/X'0',4/X'1',4/X'2',4/X'3',8/15
 GEN 64/0,64/C'ARMW    ',32/0,8/X'EA',4/X'0',4/X'2',4/X'2',4/X'3',8/15
 GEN 64/0,64/C'ARMD    ',32/0,8/X'EA',4/X'0',4/X'3',4/X'2',4/X'B',8/15
 GEN 64/0,64/C'BGT     ',32/0,8/X'EE',4/X'2',4/X'1',4/X'1',4/X'1',8/16
 GEN 64/0,64/C'BLT     ',32/0,8/X'EE',4/X'3',4/X'1',4/X'1',4/X'1',8/16
 GEN 64/0,64/C'BEQ     ',32/0,8/X'EE',4/X'4',4/X'1',4/X'1',4/X'1',8/16
 GEN 64/0,64/C'BGE     ',32/0,8/X'EE',4/X'5',4/X'1',4/X'1',4/X'1',8/16
 GEN 64/0,64/C'BLE     ',32/0,8/X'EE',4/X'6',4/X'1',4/X'1',4/X'1',8/16
 GEN 64/0,64/C'BNE     ',32/0,8/X'F2',4/X'4',4/X'1',4/X'1',4/X'1',8/16
 GEN 64/0,64/C'BOV     ',32/0,8/X'EE',4/X'1',4/X'1',4/X'1',4/X'1',8/16
 GEN 64/0,64/C'BP      ',32/0,8/X'EE',4/X'2',4/X'1',4/X'1',4/X'1',8/16
 GEN 64/0,64/C'BN      ',32/0,8/X'EE',4/X'3',4/X'1',4/X'1',4/X'1',8/16
 GEN 64/0,64/C'BZ      ',32/0,8/X'EE',4/X'4',4/X'1',4/X'1',4/X'1',8/16
 GEN 64/0,64/C'BNOV    ',32/0,8/X'F2',4/X'1',4/X'1',4/X'1',4/X'1',8/16
 GEN 64/0,64/C'BNP     ',32/0,8/X'F2',4/X'2',4/X'1',4/X'1',4/X'1',8/16
 GEN 64/0,64/C'BNN     ',32/0,8/X'F2',4/X'3',4/X'1',4/X'1',4/X'1',8/16
 GEN 64/0,64/C'BNZ     ',32/0,8/X'F2',4/X'4',4/X'1',4/X'1',4/X'1',8/16
 GEN 64/0,64/C'BS      ',32/0,8/X'EE',4/X'1',4/X'1',4/X'1',4/X'1',8/16
 GEN 64/0,64/C'BNS     ',32/0,8/X'F2',4/X'1',4/X'1',4/X'1',4/X'1',8/16
 GEN 64/0,64/C'BANY    ',32/0,8/X'EE',4/X'7',4/X'1',4/X'1',4/X'1',8/16
 GEN 64/0,64/C'BAZ     ',32/0,8/X'F2',4/X'7',4/X'1',4/X'1',4/X'1',8/16
 GEN 64/0,64/C'DATAB   ',32/0,8/X'00',4/X'0',4/X'0',4/X'0',4/X'0',8/29
 GEN 64/0,64/C'DATAH   ',32/0,8/X'01',4/X'0',4/X'0',4/X'0',4/X'0',8/29
 GEN 64/0,64/C'DATAW   ',32/0,8/X'02',4/X'0',4/X'0',4/X'0',4/X'0',8/29
 GEN 64/0,64/C'DATAD   ',32/0,8/X'03',4/X'0',4/X'0',4/X'0',4/X'0',8/29
 GEN 64/0,64/C'BEI     ',32/0,8/X'01',4/X'6',4/X'0',4/X'0',4/X'0',8/01
 GEN 64/0,64/C'UEI     ',32/0,8/X'01',4/X'7',4/X'0',4/X'0',4/X'0',8/01
 GEN 64/0,64/C'RWCS    ',32/0,8/X'01',4/X'B',4/X'0',4/X'0',4/X'2',8/06
 GEN 64/0,64/C'WWCS    ',32/0,8/X'01',4/X'C',4/X'0',4/X'0',4/X'2',8/06
 GEN 64/0,64/C'JWCS    ',32/0,8/X'FA',4/X'4',4/X'0',4/X'1',4/X'1',8/16
 GEN 64/0,64/C'SVC     ',32/0,8/X'CA',4/X'6',4/X'0',4/X'0',4/X'1',8/72
 GEN 64/0,64/C'LEAR    ',32/0,8/X'82',4/X'0',4/X'4',4/X'2',4/X'3',8/15
 GEN 64/0,64/C'LCRA    ',32/0,8/X'82',4/X'0',4/X'4',4/X'2',4/X'3',8/15
 GEN 64/0,64/C'SIO     ',32/0,8/X'FE',4/X'7',4/X'2',4/X'0',4/X'3',8/74
 GEN 64/0,64/C'TIO     ',32/0,8/X'FE',4/X'7',4/X'3',4/X'0',4/X'3',8/74
 GEN 64/0,64/C'HIO     ',32/0,8/X'FE',4/X'7',4/X'6',4/X'0',4/X'3',8/74
 GEN 64/0,64/C'GRIO    ',32/0,8/X'FE',4/X'7',4/X'7',4/X'0',4/X'3',8/74
 GEN 64/0,64/C'ECI     ',32/0,8/X'FE',4/X'7',4/X'C',4/X'0',4/X'3',8/74
 GEN 64/0,64/C'DCI     ',32/0,8/X'FE',4/X'7',4/X'D',4/X'0',4/X'3',8/74
 GEN 64/0,64/C'ACI     ',32/0,8/X'FE',4/X'7',4/X'E',4/X'0',4/X'3',8/74
 GEN 64/0,64/C'DACI    ',32/0,8/X'FE',4/X'7',4/X'F',4/X'0',4/X'3',8/74
 GEN 64/0,64/C'LA      ',32/0,8/X'52',4/X'0',4/X'4',4/X'2',4/X'3',8/15
 GEN 64/0,64/C'LABR    ',32/0,8/X'5A',4/X'8',4/X'6',4/X'2',4/X'3',8/15
 GEN 64/0,64/C'SUABR   ',32/0,8/X'5A',4/X'0',4/X'7',4/X'2',4/X'3',8/15
 GEN 64/0,64/C'LMAP    ',32/0,8/X'2E',4/X'7',4/X'2',4/X'0',4/X'0',8/20
 GEN 64/0,64/C'EAE     ',32/0,8/X'01',4/X'8',4/X'0',4/X'0',4/X'0',8/01
 GEN 64/0,64/C'DAE     ',32/0,8/X'01',4/X'E',4/X'0',4/X'0',4/X'0',8/01
 GEN 64/0,64/C'LCS     ',32/0,8/X'01',4/X'3',4/X'0',4/X'0',4/X'0',8/07
 GEN 64/0,64/C'ES      ',32/0,8/X'01',4/X'4',4/X'0',4/X'0',4/X'8',8/07
 GEN 64/0,64/C'RND     ',32/0,8/X'01',4/X'5',4/X'0',4/X'0',4/X'8',8/07
 GEN 64/0,64/C'HALT    ',32/0,8/X'01',4/X'0',4/X'0',4/X'0',4/X'0',8/01
 GEN 64/0,64/C'WAIT    ',32/0,8/X'01',4/X'1',4/X'0',4/X'0',4/X'0',8/01
 GEN 64/0,64/C'NOP     ',32/0,8/X'01',4/X'2',4/X'0',4/X'0',4/X'0',8/01
 GEN 64/0,64/C'SIPU    ',32/0,8/X'01',4/X'A',4/X'0',4/X'0',4/X'0',8/01
 GEN 64/0,64/C'ANR     ',32/0,8/X'05',4/X'0',4/X'0',4/X'0',4/X'2',8/06
 GEN 64/0,64/C'ORR     ',32/0,8/X'09',4/X'0',4/X'0',4/X'0',4/X'2',8/06
 GEN 64/0,64/C'ORRM    ',32/0,8/X'09',4/X'8',4/X'0',4/X'0',4/X'2',8/06
 GEN 64/0,64/C'EOR     ',32/0,8/X'0D',4/X'0',4/X'0',4/X'0',4/X'2',8/06
 GEN 64/0,64/C'EORM    ',32/0,8/X'0D',4/X'8',4/X'0',4/X'0',4/X'2',8/06
 GEN 64/0,64/C'ZR      ',32/0,8/X'0D',4/X'0',4/X'0',4/X'0',4/X'0',8/12
 GEN 64/0,64/C'CAR     ',32/0,8/X'11',4/X'0',4/X'0',4/X'0',4/X'2',8/06
 GEN 64/0,64/C'CMR     ',32/0,8/X'15',4/X'0',4/X'0',4/X'0',4/X'2',8/06
 GEN 64/0,64/C'SBR     ',32/0,8/X'19',4/X'0',4/X'0',4/X'0',4/X'2',8/09
 GEN 64/0,64/C'ZBR     ',32/0,8/X'19',4/X'1',4/X'0',4/X'0',4/X'2',8/09
 GEN 64/0,64/C'ABR     ',32/0,8/X'19',4/X'2',4/X'0',4/X'0',4/X'2',8/09
 GEN 64/0,64/C'TBR     ',32/0,8/X'19',4/X'3',4/X'0',4/X'0',4/X'2',8/09
 GEN 64/0,64/C'TRSW    ',32/0,8/X'29',4/X'0',4/X'0',4/X'0',4/X'0',8/08
 GEN 64/0,64/C'CALL    ',32/0,8/X'29',4/X'8',4/X'0',4/X'0',4/X'2',8/06
 GEN 64/0,64/C'CALLM   ',32/0,8/X'5E',4/X'0',4/X'6',4/X'2',4/X'3',8/15
 GEN 64/0,64/C'BSUB    ',32/0,8/X'29',4/X'8',4/X'0',4/X'0',4/X'0',8/75
 GEN 64/0,64/C'BSUBM   ',32/0,8/X'5E',4/X'0',4/X'6',4/X'1',4/X'1',8/15
 GEN 64/0,64/C'RETURN  ',32/0,8/X'29',4/X'E',4/X'0',4/X'0',4/X'0',8/01
 GEN 64/0,64/C'TRCC    ',32/0,8/X'29',4/X'5',4/X'0',4/X'0',4/X'0',8/07
 GEN 64/0,64/C'TCCR    ',32/0,8/X'29',4/X'4',4/X'0',4/X'0',4/X'0',8/07
 GEN 64/0,64/C'TPCBR   ',32/0,8/X'29',4/X'C',4/X'0',4/X'0',4/X'0',8/07
 GEN 64/0,64/C'TRR     ',32/0,8/X'2D',4/X'0',4/X'0',4/X'0',4/X'2',8/06
 GEN 64/0,64/C'TRBR    ',32/0,8/X'2D',4/X'1',4/X'0',4/X'0',4/X'2',8/06
 GEN 64/0,64/C'TBRR    ',32/0,8/X'2D',4/X'2',4/X'0',4/X'0',4/X'2',8/06
 GEN 64/0,64/C'TRC     ',32/0,8/X'2D',4/X'3',4/X'0',4/X'0',4/X'2',8/06
 GEN 64/0,64/C'TRN     ',32/0,8/X'2D',4/X'4',4/X'0',4/X'0',4/X'2',8/06
 GEN 64/0,64/C'XCR     ',32/0,8/X'2D',4/X'5',4/X'0',4/X'0',4/X'2',8/06
 GEN 64/0,64/C'XCBR    ',32/0,8/X'29',4/X'2',4/X'0',4/X'0',4/X'2',8/06
 GEN 64/0,64/C'TRRM    ',32/0,8/X'2D',4/X'8',4/X'0',4/X'0',4/X'2',8/06
 GEN 64/0,64/C'TRCM    ',32/0,8/X'2D',4/X'B',4/X'0',4/X'0',4/X'2',8/06
 GEN 64/0,64/C'TRNM    ',32/0,8/X'2D',4/X'C',4/X'0',4/X'0',4/X'2',8/06
 GEN 64/0,64/C'XCRM    ',32/0,8/X'2D',4/X'D',4/X'0',4/X'0',4/X'2',8/06
 GEN 64/0,64/C'TRSC    ',32/0,8/X'2D',4/X'E',4/X'0',4/X'0',4/X'2',8/06
 GEN 64/0,64/C'TSCR    ',32/0,8/X'2D',4/X'F',4/X'0',4/X'0',4/X'2',8/06
 GEN 64/0,64/C'ADR     ',32/0,8/X'39',4/X'0',4/X'0',4/X'0',4/X'2',8/06
 GEN 64/0,64/C'ADRM    ',32/0,8/X'39',4/X'8',4/X'0',4/X'0',4/X'2',8/06
 GEN 64/0,64/C'SUR     ',32/0,8/X'3D',4/X'0',4/X'0',4/X'0',4/X'2',8/06
 GEN 64/0,64/C'SURM    ',32/0,8/X'3D',4/X'8',4/X'0',4/X'0',4/X'2',8/06
 GEN 64/0,64/C'MPR     ',32/0,8/X'39',4/X'2',4/X'0',4/X'0',4/X'6',8/06
 GEN 64/0,64/C'DVR     ',32/0,8/X'39',4/X'A',4/X'0',4/X'0',4/X'6',8/06
 GEN 64/0,64/C'SCZ     ',32/0,8/X'11',4/X'8',4/X'0',4/X'0',4/X'2',8/11
 GEN 64/0,64/C'SLA     ',32/0,8/X'1D',4/X'1',4/X'0',4/X'0',4/X'2',8/10
 GEN 64/0,64/C'SRA     ',32/0,8/X'1D',4/X'0',4/X'0',4/X'0',4/X'2',8/10
 GEN 64/0,64/C'SLL     ',32/0,8/X'1D',4/X'3',4/X'C',4/X'0',4/X'2',8/10
 GEN 64/0,64/C'SRL     ',32/0,8/X'1D',4/X'2',4/X'0',4/X'0',4/X'2',8/10
 GEN 64/0,64/C'SLC     ',32/0,8/X'25',4/X'1',4/X'0',4/X'0',4/X'2',8/10
 GEN 64/0,64/C'SRC     ',32/0,8/X'25',4/X'0',4/X'0',4/X'0',4/X'2',8/10
 GEN 64/0,64/C'SLAD    ',32/0,8/X'21',4/X'1',4/X'0',4/X'0',4/X'A',8/10
 GEN 64/0,64/C'SRAD    ',32/0,8/X'21',4/X'0',4/X'0',4/X'0',4/X'A',8/10
 GEN 64/0,64/C'SLLD    ',32/0,8/X'21',4/X'3',4/X'C',4/X'0',4/X'A',8/10
 GEN 64/0,64/C'SRLD    ',32/0,8/X'21',4/X'2',4/X'0',4/X'0',4/X'A',8/10
 GEN 64/0,64/C'SBM     ',32/0,8/X'9A',4/X'0',4/X'0',4/X'2',4/X'3',8/05
 GEN 64/0,64/C'ZBM     ',32/0,8/X'9E',4/X'0',4/X'0',4/X'2',4/X'3',8/05
 GEN 64/0,64/C'ABM     ',32/0,8/X'A2',4/X'0',4/X'0',4/X'2',4/X'3',8/05
 GEN 64/0,64/C'TBM     ',32/0,8/X'A6',4/X'0',4/X'0',4/X'2',4/X'3',8/05
 GEN 64/0,64/C'EXM     ',32/0,8/X'AA',4/X'0',4/X'1',4/X'1',4/X'1',8/16
 GEN 64/0,64/C'MPMB    ',32/0,8/X'C2',4/X'0',4/X'0',4/X'2',4/X'B',8/15
 GEN 64/0,64/C'MPMH    ',32/0,8/X'C2',4/X'0',4/X'1',4/X'2',4/X'B',8/15
 GEN 64/0,64/C'MPMW    ',32/0,8/X'C2',4/X'0',4/X'2',4/X'2',4/X'B',8/15
 GEN 64/0,64/C'DVMB    ',32/0,8/X'C6',4/X'0',4/X'0',4/X'2',4/X'B',8/15
 GEN 64/0,64/C'DVMH    ',32/0,8/X'C6',4/X'0',4/X'1',4/X'2',4/X'B',8/15
 GEN 64/0,64/C'DVMW    ',32/0,8/X'C6',4/X'0',4/X'2',4/X'2',4/X'B',8/15
 GEN 64/0,64/C'LI      ',32/0,8/X'CA',4/X'0',4/X'0',4/X'0',4/X'2',8/19
 GEN 64/0,64/C'ADI     ',32/0,8/X'CA',4/X'1',4/X'0',4/X'0',4/X'2',8/19
 GEN 64/0,64/C'SUI     ',32/0,8/X'CA',4/X'2',4/X'0',4/X'0',4/X'2',8/19
 GEN 64/0,64/C'MPI     ',32/0,8/X'CA',4/X'3',4/X'0',4/X'0',4/X'A',8/19
 GEN 64/0,64/C'DVI     ',32/0,8/X'CA',4/X'4',4/X'0',4/X'0',4/X'A',8/19
 GEN 64/0,64/C'CI      ',32/0,8/X'CA',4/X'5',4/X'0',4/X'0',4/X'2',8/19
 GEN 64/0,64/C'EXR     ',32/0,8/X'CA',4/X'7',4/X'0',4/X'0',4/X'0',8/20
 GEN 64/0,64/C'EXRR    ',32/0,8/X'CA',4/X'7',4/X'2',4/X'0',4/X'0',8/20
 GEN 64/0,64/C'LF      ',32/0,8/X'CE',4/X'0',4/X'2',4/X'2',4/X'3',8/15
 GEN 64/0,64/C'LFBR    ',32/0,8/X'CE',4/X'0',4/X'6',4/X'2',4/X'3',8/15
 GEN 64/0,64/C'STF     ',32/0,8/X'DE',4/X'0',4/X'2',4/X'2',4/X'3',8/15
 GEN 64/0,64/C'STFBR   ',32/0,8/X'DE',4/X'0',4/X'6',4/X'2',4/X'3',8/15
 GEN 64/0,64/C'ADFW    ',32/0,8/X'E2',4/X'1',4/X'2',4/X'2',4/X'3',8/18
 GEN 64/0,64/C'ADFD    ',32/0,8/X'E2',4/X'1',4/X'3',4/X'2',4/X'3',8/18
 GEN 64/0,64/C'SUFW    ',32/0,8/X'E2',4/X'0',4/X'2',4/X'2',4/X'3',8/18
 GEN 64/0,64/C'SUFD    ',32/0,8/X'E2',4/X'0',4/X'3',4/X'2',4/X'3',8/18
 GEN 64/0,64/C'MPFW    ',32/0,8/X'E6',4/X'1',4/X'2',4/X'2',4/X'3',8/18
 GEN 64/0,64/C'MPFD    ',32/0,8/X'E6',4/X'1',4/X'3',4/X'2',4/X'3',8/18
 GEN 64/0,64/C'DVFW    ',32/0,8/X'E6',4/X'0',4/X'2',4/X'2',4/X'3',8/18
 GEN 64/0,64/C'DVFD    ',32/0,8/X'E6',4/X'0',4/X'3',4/X'2',4/X'3',8/18
 GEN 64/0,64/C'BCT     ',32/0,8/X'EE',4/X'0',4/X'1',4/X'2',4/X'3',8/15
 GEN 64/0,64/C'BU      ',32/0,8/X'EE',4/X'0',4/X'1',4/X'1',4/X'1',8/16
 GEN 64/0,64/C'BFT     ',32/0,8/X'F2',4/X'0',4/X'1',4/X'1',4/X'1',8/16
 GEN 64/0,64/C'BCF     ',32/0,8/X'F2',4/X'0',4/X'1',4/X'2',4/X'3',8/15
 GEN 64/0,64/C'BIB     ',32/0,8/X'F6',4/X'0',4/X'1',4/X'2',4/X'2',8/17
 GEN 64/0,64/C'BIH     ',32/0,8/X'F6',4/X'1',4/X'1',4/X'2',4/X'2',8/17
 GEN 64/0,64/C'BIW     ',32/0,8/X'F6',4/X'2',4/X'1',4/X'2',4/X'2',8/17
 GEN 64/0,64/C'BID     ',32/0,8/X'F6',4/X'3',4/X'1',4/X'2',4/X'2',8/17
 GEN 64/0,64/C'ZMB     ',32/0,8/X'FA',4/X'0',4/X'0',4/X'1',4/X'1',8/24
 GEN 64/0,64/C'ZMH     ',32/0,8/X'FA',4/X'0',4/X'1',4/X'1',4/X'1',8/24
 GEN 64/0,64/C'ZMW     ',32/0,8/X'FA',4/X'0',4/X'2',4/X'1',4/X'1',8/24
 GEN 64/0,64/C'ZMD     ',32/0,8/X'FA',4/X'0',4/X'3',4/X'1',4/X'1',8/24
 GEN 64/0,64/C'BL      ',32/0,8/X'FA',4/X'1',4/X'1',4/X'1',4/X'1',8/16
 GEN 64/0,64/C'EI      ',32/0,8/X'FE',4/X'0',4/X'0',4/X'0',4/X'1',8/22
 GEN 64/0,64/C'DI      ',32/0,8/X'FE',4/X'1',4/X'0',4/X'0',4/X'1',8/22
 GEN 64/0,64/C'RI      ',32/0,8/X'FE',4/X'2',4/X'0',4/X'0',4/X'1',8/22
 GEN 64/0,64/C'AI      ',32/0,8/X'FE',4/X'3',4/X'0',4/X'0',4/X'1',8/22
 GEN 64/0,64/C'DAI     ',32/0,8/X'FE',4/X'4',4/X'0',4/X'0',4/X'1',8/22
 GEN 64/0,64/C'TD      ',32/0,8/X'FE',4/X'5',4/X'0',4/X'0',4/X'2',8/22
 GEN 64/0,64/C'CD      ',32/0,8/X'FE',4/X'6',4/X'0',4/X'0',4/X'2',8/22
 GEN 64/0,64/C'CDL     ',32/0,8/X'FE',4/X'6',4/X'0',4/X'0',4/X'0',8/21
 GEN 64/0,64/C'DATA    ',32/0,8/X'00',4/X'0',4/X'0',4/X'0',4/X'0',8/29
 GEN 64/0,64/C'RES     ',32/0,8/X'00',4/X'0',4/X'0',4/X'0',4/X'0',8/41
 GEN 64/0,64/C'GEN     ',32/0,8/X'00',4/X'0',4/X'0',4/X'0',4/X'0',8/30
 GEN 64/0,64/C'EQU     ',32/0,8/X'00',4/X'0',4/X'0',4/X'1',4/X'0',8/40
 GEN 64/0,64/C'CEQU    ',32/0,8/X'00',4/X'0',4/X'0',4/X'1',4/X'0',8/68
 GEN 64/0,64/C'DEQU    ',32/0,8/X'00',4/X'0',4/X'0',4/X'1',4/X'0',8/66
  GEN 64/0,64/C'AC      ',32/0,8/X'02',4/X'0',4/X'0',4/X'1',4/X'1',8/13
  GEN 64/0,64/C'ACB     ',32/0,8/X'02',4/X'0',4/X'0',4/X'1',4/X'1',8/13
  GEN 64/0,64/C'ACH     ',32/0,8/X'02',4/X'0',4/X'1',4/X'1',4/X'1',8/13
  GEN 64/0,64/C'ACW     ',32/0,8/X'02',4/X'0',4/X'2',4/X'1',4/X'1',8/13
  GEN 64/0,64/C'ACD     ',32/0,8/X'02',4/X'0',4/X'3',4/X'1',4/X'1',8/13
 GEN 64/0,64/C'ORG     ',32/0,8/X'00',4/X'0',4/X'0',4/X'0',4/X'0',8/37
 GEN 64/0,64/C'CORG    ',32/0,8/X'00',4/X'0',4/X'0',4/X'0',4/X'0',8/69
 GEN 64/0,64/C'DORG    ',32/0,8/X'00',4/X'0',4/X'0',4/X'0',4/X'0',8/67
 GEN 64/0,64/C'SSECT   ',32/0,8/X'00',4/X'1',4/X'0',4/X'0',4/X'0',8/47
 GEN 64/0,64/C'SORG    ',32/0,8/X'00',4/X'2',4/X'0',4/X'0',4/X'0',8/47
 GEN 64/0,64/C'SEXT    ',32/0,8/X'00',4/X'3',4/X'0',4/X'0',4/X'0',8/47
 GEN 64/0,64/C'REL     ',32/0,8/X'00',4/X'4',4/X'0',4/X'0',4/X'0',8/38
 GEN 64/0,64/C'ABS     ',32/0,8/X'00',4/X'0',4/X'0',4/X'0',4/X'0',8/38
 GEN 64/0,64/C'DEF     ',32/0,8/X'00',4/X'0',4/X'0',4/X'0',4/X'0',8/36
 GEN 64/0,64/C'SDEF    ',32/0,8/X'00',4/X'2',4/X'0',4/X'0',4/X'0',8/36
 GEN 64/0,64/C'PAGE    ',32/0,8/X'00',4/X'0',4/X'0',4/X'0',4/X'0',8/44
 GEN 64/0,64/C'LIST    ',32/0,8/X'00',4/X'0',4/X'0',4/X'0',4/X'0',8/45
 GEN 64/0,64/C'EXT     ',32/0,8/X'00',4/X'1',4/X'0',4/X'0',4/X'0',8/36
 GEN 64/0,64/C'REZ     ',32/0,8/X'00',4/X'0',4/X'0',4/X'0',4/X'0',8/65
 GEN 64/0,64/C'END     ',32/0,8/X'02',4/X'0',4/X'0',4/X'1',4/X'0',8/34
 GEN 64/0,64/C'ANOP    ',32/0,8/X'00',4/X'0',4/X'0',4/X'0',4/X'0',8/48
 GEN 64/0,64/C'IFF     ',32/0,8/X'01',4/X'0',4/X'0',4/X'0',4/X'0',8/49
 GEN 64/0,64/C'IFT     ',32/0,8/X'00',4/X'0',4/X'0',4/X'0',4/X'0',8/49
 GEN 64/0,64/C'IFTDEF  ',32/0,8/X'02',4/X'0',4/X'0',4/X'0',4/X'0',8/49
 GEN 64/0,64/C'IFFDEF  ',32/0,8/X'03',4/X'0',4/X'0',4/X'0',4/X'0',8/49
 GEN 64/0,64/C'IFP     ',32/0,8/X'14',4/X'0',4/X'0',4/X'0',4/X'0',8/49
 GEN 64/0,64/C'IFA     ',32/0,8/X'15',4/X'0',4/X'0',4/X'0',4/X'0',8/49
 GEN 64/0,64/C'SETF    ',32/0,8/X'00',4/X'0',4/X'0',4/X'0',4/X'0',8/52
 GEN 64/0,64/C'SETT    ',32/0,8/X'01',4/X'0',4/X'0',4/X'0',4/X'0',8/52
 GEN 64/0,64/C'SET     ',32/0,8/X'02',4/X'0',4/X'0',4/X'0',4/X'0',8/52
 GEN 64/0,64/C'OPTS    ',32/0,8/X'03',4/X'0',4/X'0',4/X'0',4/X'0',8/52
 GEN 64/0,64/C'OPTR    ',32/0,8/X'04',4/X'0',4/X'0',4/X'0',4/X'0',8/52
 GEN 64/0,64/C'OPTT    ',32/0,8/X'05',4/X'0',4/X'0',4/X'0',4/X'0',8/52
 GEN 64/0,64/C'DEFM    ',32/0,8/X'00',4/X'0',4/X'0',4/X'0',4/X'0',8/50
 GEN 64/0,64/C'ENDM    ',32/0,8/X'00',4/X'0',4/X'0',4/X'0',4/X'0',8/51
 GEN 64/0,64/C'GOTO    ',32/0,8/X'00',4/X'0',4/X'0',4/X'0',4/X'0',8/53
 GEN 64/0,64/C'ENDR    ',32/0,8/X'00',4/X'0',4/X'0',4/X'0',4/X'0',8/54
 GEN 64/0,64/C'REPT    ',32/0,8/X'00',4/X'0',4/X'0',4/X'0',4/X'0',8/55
 GEN 64/0,64/C'FORM    ',32/0,8/X'00',4/X'0',4/X'0',4/X'0',4/X'0',8/57
         IFT       CAID,SKIP                                    *CAID*
* NEW DEBUGGER OPCODES                                          *CAID*
 GEN 64/0,64/C'.SRC    ',32/0,8/X'00',4/X'0',4/X'0',4/X'0',4/X'0',8/61
 GEN 64/0,64/C'.COM    ',32/0,8/X'00',4/X'1',4/X'0',4/X'0',4/X'0',8/61
 GEN 64/0,64/C'.STAB   ',32/0,8/X'00',4/X'2',4/X'0',4/X'0',4/X'0',8/61
 GEN 64/0,64/C'.STABC  ',32/0,8/X'00',4/X'3',4/X'0',4/X'0',4/X'0',8/61
 GEN 64/0,64/C'.SYM    ',32/0,8/X'00',4/X'4',4/X'0',4/X'0',4/X'0',8/61
 GEN 64/0,64/C'.END    ',32/0,8/X'00',4/X'5',4/X'0',4/X'0',4/X'0',8/61
 GEN 64/0,64/C'.XEQ    ',32/0,8/X'00',4/X'6',4/X'0',4/X'0',4/X'0',8/61
 GEN 64/0,64/C'.ARG    ',32/0,8/X'00',4/X'7',4/X'0',4/X'0',4/X'0',8/61
SKIP     ANOP                                                   *CAID*
 GEN 64/0,64/C'LPSDCM  ',32/0,8/X'FA',4/X'5',4/X'2',4/X'1',4/X'1',8/16
 GEN 64/0,64/C'TMAPR   ',32/0,8/X'2D',4/X'A',4/X'0',4/X'0',4/X'2',8/06
 GEN 64/0,64/C'SETCPU  ',32/0,8/X'2D',4/X'9',4/X'0',4/X'0',4/X'0',8/71
 GEN 64/0,64/C'RDSTS   ',32/0,8/X'01',4/X'9',4/X'0',4/X'0',4/X'0',8/71
 GEN 64/0,64/C'RPSWT   ',32/0,8/X'05',4/X'B',4/X'0',4/X'0',4/X'0',8/71
 GEN 64/0,64/C'CMC     ',32/0,8/X'05',4/X'A',4/X'0',4/X'0',4/X'0',8/71
 GEN 64/0,64/C'UNDEF   ',32/0,8/X'05',4/X'9',4/X'0',4/X'0',4/X'0',8/01
 GEN 64/0,64/C'ADRFW   ',32/0,8/X'39',4/X'1',4/X'0',4/X'0',4/X'2',8/06
 GEN 64/0,64/C'SURFW   ',32/0,8/X'39',4/X'3',4/X'0',4/X'0',4/X'2',8/06
 GEN 64/0,64/C'MPRFW   ',32/0,8/X'39',4/X'6',4/X'0',4/X'0',4/X'2',8/06
 GEN 64/0,64/C'DVRFW   ',32/0,8/X'39',4/X'4',4/X'0',4/X'0',4/X'2',8/06
 GEN 64/0,64/C'FLTW    ',32/0,8/X'39',4/X'7',4/X'0',4/X'0',4/X'2',8/06
 GEN 64/0,64/C'FIXW    ',32/0,8/X'39',4/X'5',4/X'0',4/X'0',4/X'2',8/06
 GEN 64/0,64/C'ADRFD   ',32/0,8/X'39',4/X'9',4/X'0',4/X'0',4/X'E',8/06
 GEN 64/0,64/C'SURFD   ',32/0,8/X'39',4/X'B',4/X'0',4/X'0',4/X'E',8/06
 GEN 64/0,64/C'MPRFD   ',32/0,8/X'39',4/X'E',4/X'0',4/X'0',4/X'E',8/06
 GEN 64/0,64/C'DVRFD   ',32/0,8/X'39',4/X'C',4/X'0',4/X'0',4/X'E',8/06
 GEN 64/0,64/C'FLTD    ',32/0,8/X'39',4/X'F',4/X'0',4/X'0',4/X'E',8/06
 GEN 64/0,64/C'FIXD    ',32/0,8/X'39',4/X'D',4/X'0',4/X'0',4/X'E',8/06
 GEN 64/0,64/C'STPIO   ',32/0,8/X'FE',4/X'7',4/X'4',4/X'0',4/X'3',8/74
 GEN 64/0,64/C'RSCHNL  ',32/0,8/X'FE',4/X'7',4/X'5',4/X'0',4/X'3',8/74
 GEN 64/0,64/C'RSCTL   ',32/0,8/X'FE',4/X'7',4/X'8',4/X'0',4/X'3',8/74
 GEN 64/0,64/C'ECWCS   ',32/0,8/X'FE',4/X'7',4/X'9',4/X'0',4/X'3',8/74
 GEN 64/0,64/C'WCWCS   ',32/0,8/X'FE',4/X'7',4/X'B',4/X'0',4/X'3',8/74
 GEN 64/0,64/C'PROGRAM ',32/0,8/X'00',4/X'0',4/X'0',4/X'0',4/X'0',8/35
 GEN 64/0,64/C'BOUND   ',32/0,8/X'00',4/X'0',4/X'0',4/X'0',4/X'0',8/39
 GEN 64/0,64/C'COMMON  ',32/0,8/X'00',4/X'0',4/X'0',4/X'0',4/X'0',8/42
 GEN 64/0,64/C'TITLE   ',32/0,8/X'00',4/X'0',4/X'0',4/X'0',4/X'0',8/43
 GEN 64/0,64/C'SPACE   ',32/0,8/X'00',4/X'0',4/X'0',4/X'0',4/X'0',8/46
 GEN 64/0,64/C'LPOOL   ',32/0,8/X'02',4/X'0',4/X'0',4/X'0',4/X'0',8/64
 GEN 64/0,64/C'DSECT   ',32/0,8/X'00',4/X'4',4/X'0',4/X'0',4/X'0',8/38
         IFF       UNIXF,SKIP                                   *JCB*
 GEN 64/0,64/C'CSECT   ',32/0,8/X'00',4/X'C',4/X'0',4/X'0',4/X'0',8/38
SKIP     ANOP                                                   *JCB*
         IFT       UNIXF,SKIP                                   *JCB*
 GEN 64/0,64/C'CSECT   ',32/0                                   *JCB*
SECT.FLH GEN       8/X'00',4/X'C',4/X'0',4/X'0',4/X'0',8/38     *JCB*
SKIP     ANOP                                                   *JCB*
 GEN 64/0,64/C'EXITM   ',32/0,8/X'00',4/X'0',4/X'0',4/X'0',4/X'0',8/56
 GEN 64/0,64/C'DATAONLY',32/0,8/X'00',4/X'0',4/X'0',4/X'0',4/X'0',8/62
 GEN 64/0,64/C'ENDDATA ',32/0,8/X'00',4/X'0',4/X'0',4/X'0',4/X'0',8/63
 GEN 64/0,64/C'SCSR    ',32/0,8/X'05',4/X'1',4/X'0',4/X'0',4/X'0',8/07
 GEN 64/0,64/C'SDSR    ',32/0,8/X'05',4/X'2',4/X'0',4/X'0',4/X'0',8/07
 GEN 64/0,64/C'PIT     ',32/0,8/X'05',4/X'4',4/X'0',4/X'0',4/X'0',8/01
 GEN 64/0,64/C'DCSR    ',32/0,8/X'05',4/X'5',4/X'0',4/X'0',4/X'0',8/07
 GEN 64/0,64/C'DDSR    ',32/0,8/X'05',4/X'6',4/X'0',4/X'0',4/X'0',8/07
 GEN 64/0,64/C'DMSINT  ',32/0,8/X'0D',4/X'1',4/X'0',4/X'0',4/X'2',8/06
 GEN 64/0,64/C'RMSINT  ',32/0,8/X'0D',4/X'1',4/X'0',4/X'0',4/X'2',8/06
 GEN 64/0,64/C'MDMSW   ',32/0,8/X'0D',4/X'2',4/X'0',4/X'0',4/X'6',8/06
 GEN 64/0,64/C'MRMSW   ',32/0,8/X'0D',4/X'2',4/X'0',4/X'0',4/X'6',8/06
 GEN 64/0,64/C'ZBDMS   ',32/0,8/X'0D',4/X'1',4/X'0',4/X'0',4/X'2',8/09
 GEN 64/0,64/C'ZBRMS   ',32/0,8/X'0D',4/X'1',4/X'0',4/X'0',4/X'2',8/09
 GEN 64/0,64/C'RDMSW   ',32/0,8/X'0D',4/X'3',4/X'0',4/X'0',4/X'2',8/06
 GEN 64/0,64/C'RRMSW   ',32/0,8/X'0D',4/X'3',4/X'0',4/X'0',4/X'2',8/06
 GEN 64/0,64/C'SBDMS   ',32/0,8/X'0D',4/X'3',4/X'0',4/X'0',4/X'2',8/09
 GEN 64/0,64/C'SBRMS   ',32/0,8/X'0D',4/X'3',4/X'0',4/X'0',4/X'2',8/09
 GEN 64/0,64/C'WDMSCS  ',32/0,8/X'0D',4/X'9',4/X'0',4/X'0',4/X'0',8/07
 GEN 64/0,64/C'WRMSCS  ',32/0,8/X'0D',4/X'9',4/X'0',4/X'0',4/X'0',8/07
 GEN 64/0,64/C'RDMSCS  ',32/0,8/X'0D',4/X'A',4/X'0',4/X'0',4/X'0',8/07
 GEN 64/0,64/C'RRMSCS  ',32/0,8/X'0D',4/X'A',4/X'0',4/X'0',4/X'0',8/07
 GEN 64/0,64/C'CGEW    ',32/0,8/X'29',4/X'6',4/X'0',4/X'0',4/X'2',8/06
 GEN 64/0,64/C'CGED    ',32/0,8/X'29',4/X'7',4/X'0',4/X'0',4/X'2',8/06
 GEN 64/0,64/C'CEGW    ',32/0,8/X'29',4/X'A',4/X'0',4/X'0',4/X'2',8/06
 GEN 64/0,64/C'CEGD    ',32/0,8/X'29',4/X'B',4/X'0',4/X'0',4/X'2',8/06
 GEN 64/0,64/C'CXIW    ',32/0,8/X'29',4/X'6',4/X'0',4/X'0',4/X'2',8/06
 GEN 64/0,64/C'CXID    ',32/0,8/X'29',4/X'7',4/X'0',4/X'0',4/X'2',8/06
 GEN 64/0,64/C'CIXW    ',32/0,8/X'29',4/X'A',4/X'0',4/X'0',4/X'2',8/06
 GEN 64/0,64/C'CIXD    ',32/0,8/X'29',4/X'B',4/X'0',4/X'0',4/X'2',8/06
 GEN 64/0,64/C'TC      ',32/0,8/X'CA',4/X'8',4/X'0',4/X'0',4/X'1',8/73
 GEN 64/0,64/C'PINTV   ',32/0,8/X'CA',4/X'9',4/X'0',4/X'0',4/X'2',8/19
 GEN 64/0,64/C'RINTV   ',32/0,8/X'CA',4/X'A',4/X'0',4/X'0',4/X'2',8/19
OPSENDBA DEQU      $               END OF OPCODE TABLE          ESCT-32
*
*-----------------------------------------------------------------------
         TITLE     OPERATOR PROCESSOR DIRECTORY
         BOUND     1W
KINT     CEQU      $               BASE OF PROCESSOR DIRECTORY  ESCT-32
         BU        AERR      00    ENTRY  0 - ERROR             EASC-32
         BU        NSS       01    ENTRY  1 - NOP,HALT,WAIT     EASC-32
         BU        AERR      02    ENTRY    - SPARE             EASC-32
         BU        AERR      03    ENTRY    - SPARE             EASC-32
*                                                               EASC-32
KINTL1   CEQU      $-KINT  NO AUTOMATIC OPERAND STRIPPING ABOVE ESCT-32
*                                                               EASC-32
         BU        CALM      04    ENTRY  2 - CALL MONITOR      EASC-32
         BU        BM        05    ENTRY  3 - SBM,ZBM,ABM,TBM,  EASC-32
         BU        RRO       06    ENTRY  4 - REG-TO-REG OPS    EASC-32
         BU        LER       07    ENTRY  5 - LCS,ES,RND        EASC-32
         BU        TRSW      08    ENTRY  6 - TRSW              EASC-32
         BU        RTB       09    ENTRY  7 - SBR,TBR,ABR,ZBR   EASC-32
*                                             ZBDMS,SBDMS       EASC-32
         BU        SHF       10    ENTRY  8 - SHIFTS            EASC-32
         BU        NORDS     11    ENTRY  9 - NOR,NORD,SCZ      EASC-32
         BU        ZRX       12    ENTRY 10 - ZR                EASC-32
         BU        BU        13    ENTRY 11 - AC? (TREAT AS BU) EASC-32
         BU        TRIP      14    ENTRY 12 - TRP,TPR           EASC-32
         BU        AGEN      15    ENTRY 13 - MOST MEMORY REFS. EASC-32
         BU        BU        16    ENTRY 14 - BU,BFT,ZM ,EXM,   EASC-32
         BU        BI        17    ENTRY 15 - BIB,BIW,BIH,BID   EASC-32
         BU        FPP       18    ENTRY 16 - FLOATING PNT. OPS EASC-32
         BU        IMOP      19    ENTRY 17 - IMMEDIATE OPS     EASC-32
         BU        EXR       20    ENTRY 18 - EXR,EXRR,LMAP     EASC-32
         BU        CDL       21    ENTRY 19 - CDL SEMI-PSEUDO   EASC-32
         BU        IO        22    ENTRY 20 - CD,TD,EI,DI,R1,AI EASC-32
*                                             DAI               EASC-32
         BU        BACX      23    ENTRY 21 - BACH,BACW         EBAC-33
         BU        ZMX       24    ENTRY 22 - ZMB,ZMH,ZMW,ZMD   ENSB-33
         BU        AERR      25    ENTRY    - SPARE             EASC-32
         BU        AERR      26    ENTRY    - SPARE             EASC-32
         BU        AERR      27    ENTRY    - SPARE             EASC-32
         BU        AERR      28    ENTRY    - SPARE             EASC-32
*                                                               EASC-32
KINTL2   CEQU      $-KINT    NO AUTOMATIC OPERAND STRIPPING BE  ESCT-32
*                                                               EASC-32
         BU        DATA      29    ENTRY 22 - DATA,DATA{B,H,W,D}EASC-32
         BU        VFD       30    ENTRY 23 - GEN PSEUDO        EASC-32
         BU        AERR      31    ENTRY    - SPARE             EASC-32
         BU        AERR      32    ENTRY    - SPARE             EASC-32
*                                                               EASC-32
KINTL3   CEQU      $-KINT    NO BOUNDING CHECKS MADE BELOW HERE ESCT-32
*                                                               EASC-32
         BU        RS.EIS    33    ENTRY 24 - REIS/SEIS IN NON- EINS-31
*                                             BASE MODE         EINS-31
         BU        END       34    ENTRY 25 - END               EASC-32
         BU        PROG      35    ENTRY 26 - PROGRAM           EASC-32
         BU        REF       36    ENTRY 27 - EXT, DEF, SDEF    EASC-32
         BU        ORG       37    ENTRY 28 - ORG               EASC-32
         BU        AREL      38    ENTRY 29 - ABS, REL, DSECT,  EASC-32
*                                             CSECT             EASC-32
         BU        BOUND     39    ENTRY 30 - BOUND             EASC-32
         BU        EQU       40    ENTRY 31 - EQU               EASC-32
         BU        RES       41    ENTRY 32 - RES               EASC-32
         BU        CCP1      42    ENTRY 33 - COMMON            EASC-32
         BU        TITL      43    ENTRY 34 - TITLE             EASC-32
         BU        PAGP      44    ENTRY 35 - PAGE              EASC-32
         BU        LIST      45    ENTRY 36 - LIST              EASC-32
         BU        SPACE     46    ENTRY 37 - SPACE             EASC-32
         BU        SDIRS     47    ENTRY 38 - S DIRECTIVES      EASC-32
*                                                               EASC-32
KINTLN1  CEQU      $-KINT    BEGIN "NONG" SUPRESSED ENTRIES     ESCT-32
*                                                               EASC-32
         BU        NEXT      48    ENTRY 39 - ANOP, SEIS/REIS   EINS-31
*                                             IN BASE MODE      EINS-31
         BU        IFPRO     49    ENTRY 40 - IFT,IFF,IFP,IFA   EASC-32
         BU        DEFMPRO   50    ENTRY 41 - DEFM              EASC-32
         BU        ENDMPRO   51    ENTRY 42 - ENDM              EASC-32
         BU        SETPRO    52    ENTRY 43 - SET,SETF,SETT,    EASC-32
*                                             OPTS,OPTR,OPTT    EASC-32
         BU        GOTOP     53    ENTRY 44 - GOTO              EASC-32
         BU        ENDRP     54    ENTRY 45 - ENDR              EASC-32
         BU        REPTP     55    ENTRY 46 - REPT              EASC-32
         BU        EXITMP    56    ENTRY 47 - EXITM             EASC-32
         BU        FORMP     57    ENTRY 48 - FORM              EASC-32
         BU        AERR      58    ENTRY    - SPARE             EASC-32
         BU        AERR      59    ENTRY    - SPARE             EASC-32
*                                                               EASC-32
KINTLN2  CEQU      $-KINT     END OF NONG ENTRIES               ESCT-32
*                                                               EASC-32
         BU        AERR      60    ENTRY    - SPARE             EASC-32
         IFT       CAID,SKIP                                    *CAID*
         BU        STAB      61    ENTRY    - STAB ENTRIES      *CAID*
SKIP     ANOP                                                   *CAID*
         IFF       CAID,SKIP                                    *CAID*
         BU        AERR      61    ENTRY    - SPARE             EASC-32
SKIP     ANOP                                                   *CAID*
         BU        DTONLY    62    ENTRY    - DATAONLY          EASC-32
         BU        ENDDT     63    ENTRY    - ENDDATA           EASC-32
         BU        LPOP      64    ENTRY 49 - LPOOL             EASC-32
         BU        REZ       65    ENTRY 50 - REZ               EASC-32
         BU        EQU       66    ENTRY    - DEQU              EASC-32
         BU        ORG       67    ENTRY    - DORG              EASC-32
         BU        EQU       68    ENTRY    - CEQU              EASC-32
         BU        ORG       69    ENTRY    - CORG              EASC-32
         BU        AERR      70    ENTRY    - SPARE             EASC-32
*                                                               EASC-32
KINTL4   CEQU      $-KINT    MARK END OF THE OPERATION PROCESS  ESCT-32
*                                                               EASC-32
         BU        SETCPU    71    ENTRY 51 - SETCPU,RDSTS,     EASC-32
*                                             RPSWT,SMC,CMC     EASC-32
         BU        SVC       72    ENTRY 52 - SVC               EASC-32
         BU        TRAP      73    ENTRY 53 - TC                ENIS-32
         BU        EXTIO     74    ENTRY 54 - EXTIO             ENIS-32
         BU        RSC1      75    ENTRY 55 - RISC STYLE F.P.   ERSC-32
         BU        RSC2      76    ENTRY 56 - RISC WAITS        ERSC-32
         BU        REVRRO    77    ENTRY 57 - RISC REG-TO-REG   ERSC-32
         BU        FPCTX     78    ENTRY 58 - RISC F.P. CONTEXT ERSC-32
         BU        CF2D      79    ENTRY 79 - FLT to DBL Conv   IEEE-MOD
         BU        CD2F      80    ENTRY 80 - DBL to FLT Conv   IEEE-MOD
*
*-----------------------------------------------------------------------
         TITLE     REPORT CAPTURE PART OF DISC BASED XREF
*    MPX-32 MACRO ASSEMBLER DISC-BASED CROSS-REFERENCE  XREF 12NOV80
************************************************************************
*                                                                      *
*        REPORT CAPTURE PART OF DISC BASED XREF                        *
*                                                                      *
************************************************************************
         SPACE     3
*        REFERENCE REPORTER FOR LATER SYMBOL CONCORDANCE
REPTR    CEQU      $                                            ESCT-32
*        COMMAND INPUT IN R3: C0=Y,E0=N,80=2,A0=1 IN BITS 0-7 OF R3
*!!!!!!!!ZBM!!!!!!!4,FCBXR+2W!!!!!!SET!SEQUENTIAL!DISC!ACCESS.!!S880752
*!!!!!!!!SBM!!!!!!!0,FCBXR+2W!!!!!!SET!NO-WAIT!MODE!FOR!WRITES!!S880752
         TBM       0,REPTYPE       COMMAND OR SYMBOL REPORT ???
         BS        REPTRC          IT IS A COMMAND.
         CAMW      1,REPTMCK       IS THIS A MACRO NAME CHECK
         BGE       REPTRRET     IT IS JUST A MACRO DATA REQUEST
         TBM       02,REPTRCBP
         BNS       REPTRRET     DONT REPORT DURING PASS 2
         STW       1,REPTRS1       SAVE THE USERS X1
         TBR       3,0             DSECT/CSECT FLAG SET ???
         BS        REPTM1          YES - MUST BE FINAL DATA VALUE
         CAMW      3,=X'0001869F'      IS THIS THE FINAL DATA VALUE?
         BGT       REPTM1       YES--WE DONT SEGREGATE IT FURTHER
         ZBR       1,0             CLEAR DSECT/CSECT FLAG
         CAMW      1,REPTDCK       CHECK WHETHER DATA REQUEST OR DEF.
         BGE       $+1W+1H      IT IS A DEFINITION
         SBR       3,3             INDICATE A USAGE REFERENCE (REQUEST)
         SBR       3,2             INDICATE EITHER USAGE OR DEFINITION
REPTM1   CEQU      $                                            ESCT-32
         LW        1,XRBUFP        GET THE POINTER TO THE RECORD
         BNZ       REPTM2          NOT START OF THE RECORD
*!!!!!!!!LA!!!!!!!!R1,FCBXR!!!!!!!!FCB!ADDR!!!!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!SVC!!!!!!!1,X'3C'!!!!!!!!!WAIT!FOR!I/O!COMPLETE!!!!!!!!S880752
*!!!!!!!!LI!!!!!!!!1,-192W!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!ZMD!!!!!!!XRBUF+192W,1!!!!!SHOW!NOTHING!IN!THE!BUFFER!NS880752
*!!!!!!!!BID!!!!!!!1,$-1W!!!!!!!!!!GO!UP!BY!TWO!WORD!!!!!!!!!!!!S880752
         LW        1,XRBUFP        POINTER IN THE BUFFER
REPTM2   CEQU      $                                            ESCT-32
*        REPORT ONE REFERENCE
*        WORDS ARE PLACED INTO UT2 RECORDS IN FOLLWING ORDER:
*        I0 WD3,I0 WD2,I0 WD1,I1 WD3,I1 WD2,I1 WD1,I2 WD3,I2 WD2,I2 WD1,
*        ETC
         STW       4,XRBUF+0W,1    1ST 4 CHARS
         STW       5,XRBUF+1W,1    2ND 4 CHARS
         SLC       3,1             ROTATE SIGN BIT TO BIT 31 (FOR SORT)
         STW       3,XRBUF+2W,1    KEY DATA AND FLAG
         SRC       3,1             RESTORE ORIGINAL R3
*!!!!!!!!ABM!!!!!!!29,XRBUFP!!!!!!!ADVANCE!BY!1W!!!!!!!!!!!!!!!!S880752
*!!!!!!!!ABM!!!!!!!28,XRBUFP!!!!!!!ADVANCE!BY!2W!!!!!!!!!!!!!!!!S880752
         ABM       31,RECCOUN      COUNT NUMBER OF ELEMENTS     S880752
         LW        1,XRBUFP         CHECK IF BUFFER OVER THE END
         ADI       1,3W            BUMP POINTER                 S880752
         STW       1,XRBUFP        AND RESTORE                  S880752
         CI        R1,XRSECSIZ     CHECK END OF BUFFER          S880752
*!!!!!!!!CAMW!!!!!!1,XRSECSIZ!!!!!!!NUMBER!OF!WORDS!IN!ONE!BUFFES880752
         BLT       REPTM4          NOT DONE WITH THIS RECORD
         IFF       UNIXF,SKIP                                   *JCB*
         LA        1,FCBXR         FILLED THE BUFFER-NWO WRITE IT
         SVC       1,X'32'         ON UT2 IN THE NO WAIT MODE
         TBM       6,FCBXR+3W      TEST FOR EOM   AS17
         BS        XRER            ERROR IF EOF ON WRITE.
SKIP     ANOP                                                   *JCB*
         IFT       UNIXF,SKIP                                   *JCB*
         LW        1,XR.FCBA       FILLED THE BUFFER-WRITE IT   *JCB*
         SVC       1,X'32'         ON UT2 IN THE NO WAIT MODE   *JCB*
         TBM       6,3W,X1         TEST FOR EOM   AS17          *JCB*
         BS        XRER            ERROR IF EOF ON WRITE.       *JCB*
SKIP     ANOP                                                   *JCB*
         ZMW       XRBUFP          NEW RECORDS START AT THE FRONT
*!!!!!!!!ABM!!!!!!!31,RECCOUN!!!!!!COUNT!THE!NUMBER!OF!RECORDS!!S880752
REPTM4   LW        1,REPTRS1       UNSV THE USERS X1
REPTRRET CEQU      $               LOTS OF PEOPLE RETURN THRU   ESCT-32
         TRSW      0               RETURN
REPTRC   CEQU      $                                            ESCT-32
         TBR       3,1             WHAT TYPE OF COMMAND
         BNS       REPTRCP      PASS REPORT
         STW       3,REPTRCBO      SAVE XREF OPTION INDICATOR
         ZMW       REPTRCBP        AND HOLD OFF REPORTING
         BU        REPTRRET        RETURN TO CALLER
REPTRCP  CEQU      $                                            ESCT-32
         TBM       02,REPTRCBO     IS THE XREF OPTION ON
         BS        REPTRRET     NO--DONT OPEN THE FILES
         LW        4,REPTRCBO      GET THE OPTION DESCRIPTION WORD
         TRC       4,4             NOW  0011 MEANS YES, 0001 MEANS NO
         ANR       3,4             WE WILL REPORT DURING PASS 1 ONLY
         STW       4,REPTRCBP      SO BIT 2 ON MEANS ALLOW REPORTING
         TBR       3,2             THIS BIT TELLS US WHICH PASS
         BNS       REPTRCP2     PASS 2--ENTER QUIESCENT PERIOD
         IFF       UNIXF,SKIP                                   *JCB*
*        INITIALIZE REPORT FILE
         LI        R1,4            UPDATE MODE INDICATOR
         STB       R1,MCNP+2W      SET IN CNP
         STW       R7,REPTRS7      SAVE R7 FOR OPEN CALL
SKIP     ANOP                                                   *JCB*
         IFF       UNIXF,SKIP                                   *JCB*
         LA        1,FCBXR         UT2 FCB ADDR
         LA        R7,MCNP         CNP ADDRWRITE.
         SVC       2,X'42'         OPEN UT2 UPDATE MODE UNBLOCKED
         LW        R7,REPTRS7      RESTORE R7
         LI        R1,1            READ ONLY MODE
         STB       R1,MCNP+2W      RESTORE CNP TO RE AD ONLY
*!!!!!!!!LI!!!!!!!!1,192W!!!!!!!!!!SET!SECTOR!SIZE!TO!192W.!!!!!S880752
*!!!!!!!!STW!!!!!!!1,XRSECSIZ!!!!!!!NUMBER!OF!WORDS!IN!ONE!BUFFES880752
*!!!!!!!!LW!!!!!!!!1,=X'0C000000'!!DISC!TRANSFER!COUNT!!!!!!!!!!S880752
*!!!!!!!!STW!!!!!!!1,XRSECTCW!!!!!!SAVE!FOR!LATER!!!!!!!!!!!!!!!S880752
*!!!!!!!!LW!!!!!!!!1,FCBXRI!!!!!!!!!!!!!INITIAL!SET!UP!FOR!TCW!!S880752
*!!!!!!!!STW!!!!!!!1,FCBXR+1W!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!S880752
         ZBM       4,FCBXR+2W      SET SEQUENTIAL DISC ACCESS   S880752
         LI        R1,XRSECSIZ     SET BUFFER SIZE              S880752
         STW       R1,FCBXR+FCB.EQTY   INTO FCB                 S880752
SKIP     ANOP                                                   *JCB*
         IFT       UNIXF,SKIP                                   *JCB*
         STF       R0,XRP.RSV      SAVE REGS                    *JCB*
         CCALL     _open,XRFILPTR,=X'902',=X'1B6' OPEN R/W UBLK *JCB*
         TRR       R0,R0           ERROR                        *JCB*
         BLT       XRER            ABORT IF YES                 *JCB*
         STW       R0,XR.FD        SAVE FILE DESCRIPTOR         *JCB*
         CCALL     _fcbadr,XR.FD   GET UT2 FCB ADDRESS          *JCB*
         STW       R0,XR.FCBA      SAVE FCB ADDRESS             *JCB*
         LW        1,XR.FCBA       GET XREF FCB ADDR            *JCB*
         ZBM       4,2W,X1         SET SEQUENTIAL DISC ACCESS   *JCB*
         LI        R7,XRSECSIZ     SET BUFFER SIZE              *JCB*
         STW       R7,FCB.EQTY,X1  INTO FCB                     *JCB*
         LF        R0,XRP.RSV      RESTORE REGS                 *JCB*
SKIP     ANOP                                                   *JCB*
         ZMW       RECCOUN         THIS WILL HOLDS THE NUMBER OF RECORDS
         ZMW       XRBUFP          NEW RECORDS START AT THE FRONT
         IFF       UNIXF,SKIP                                   *JCB*
         LA        1,FCBXR         BASE ADDRESS OF THE FCB FOR UT2
SKIP     ANOP                                                   *JCB*
         IFT       UNIXF,SKIP                                   *JCB*
         LW        1,XR.FCBA       GET XREF FCB ADDR            *JCB*
SKIP     ANOP                                                   *JCB*
         SVC       1,X'37'         REWIND UT2
         BU        REPTRRET        RETURN TO CALLER
         SPACE     2
REPTRCP2 CEQU      $               PASS 2                       ESCT-32
*        END THE REPORT
         LW        1,XRBUFP        ANYTHING LEFT IN THE BUFFER?
         BEQ       REPTRCP4     NO-SKIP LAST WRITE
         TRR       R1,R5           COPY COUNT                   S880752
         DVI       R4,768          MOD 768                      S880752
         LI        R5,768                                       S880752
         SUR       R4,R5                                        S880752
         TRN       R5,R4           NEGATE REMAINDER             S880752
         ZMW       XRBUF,X1        ZAP BALANCE OF BUFFER        S880752
         ADI       R1,1W           BUMP POINTER                 S880752
         BIW       R4,$-2W         AND LOOP                     S880752
         IFF       UNIXF,SKIP                                   *JCB*
         STW       R1,FCBXR+FCB.EQTY    AND SAY HOW MUCH        S880752
         LA        1,FCBXR
*!!!!!!!!SVC!!!!!!!1,X'3C'!!!!!!!!!WAIT!FOR!I/O!COMPLETE!!!!!!!!S880752
         SVC       1,X'32'         WRITE LAST RECORD
         TBM       6,FCBXR+3W      TEST FOR EOM   AS17
SKIP     ANOP                                                   *JCB*
         IFT       UNIXF,SKIP                                   *JCB*
         TRR       R1,R4           SAVE COUNT                   *JCB*
         LW        R1,XR.FCBA      GET XREF FCB ADDR            *JCB*
         STW       R4,FCB.EQTY,X1  AND SAY HOW MUCH             *JCB*
         SVC       1,X'32'         WRITE LAST RECORD            *JCB*
         TBM       6,3W,X1         TEST FOR EOM   AS17          *JCB*
SKIP     ANOP                                                   *JCB*
         BS        XRER         ERROR IF EOF ON WRITE.
*!!!!!!!!ABM!!!!!!!31,RECCOUN!!!!!!COUNT!THE!LAST!RECORD!WRITTENS880752
REPTRCP4 CEQU      $                                            ESCT-32
*!REPTRCP4!!!LA!!!!1,FCBXR!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!AS18!!!S880752
*!!!!!!!!SVC!!!!!!!1,X'3C'!!!!!!!!!WAIT!FOR!I/O!COMPLETE!AS18!!!S880752
*!!!!!!!!LI!!!!!!!!1,-192W!!!!!!!!!SECTOR!SIZE!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!ZMD!!!!!!!XRBUF+192W,1!!!!CLEAR!XRBUF.!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!BID!!!!!!!1,$-1W!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!LI!!!!!!!!1,X'0F00'!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!STH!!!!!!!1,XRBUF!!!!!!!!!STOR!LAST!REC.!INDICATOR!FOR!S880752
*!!!!!!!!LA!!!!!!!!1,FCBXR!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!SVC!!!!!!!1,X'32'!!!!!!!!!WRITE!LAST!RECORD!INDICATOR.!S880752
*!!!!!!!!SVC!!!!!!!1,X'3C'!!!!!!!!!WAIT!FOR!I/O!COMPLETE!!!!!!!!S880752
*!!!!!!!!TBM!!!!!!!7,FCBXR+3W!!!!!!TEST!FOR!EOM!!!AS17!!!!!!!!!!S880752
*!!!!!!!!BS!!!!!!!!XRER!!!!!!!!!ERROR!IF!EOF!ON!WRITE.!!!!!!!!!!S880752
         BU        REPTRRET        RETURN TO CALLER
*
REPTYPE  RES       1W
REPTRCBP RES       1W              PASS INDICATOR 00=N, 80=28 A0=1
REPTRCBO RES       1W              XREF INDICATOR C0=Y, E0=N
REPTRS1  RES       1W
REPTRS7  RES       1W              R7 SAVE AREA
REPTMCK  GEN       8/A(TYMACREQ),24/0     BOUNDARY FOR MACRO TABLE SEARC
REPTDCK  GEN       8/A(TYPL),24/0  BOUNDARY BETWEEN USAGE AND DEFINITION
RECCOUN  RES       1W              THIS WILL HOLDS THE NUMBER OF RECO-D
*
* (C) COPYRIGHT 1983 ENCORE COMPUTER CORPORATION
*     ALL RIGHTS RESERVED
*
         TITLE     WRITERPT - XREF REPORT WRITER                S880752
*                                                               S880752
*  THE ALGORITHM USED TO PRODUCE THE CROSS REFERENCE LISTING IS S880752
* TO PARTITION THE DATA FILE INTO ONE OR MORE SUB-FILES. EACH   S880752
* SUB-FILE IS SORTED IN MEMORY AND INDEXED BY A 8 WORD HEADER   S880752
* BLOCK. THE RUNS THAT ARE PRODUCED ARE THEN MERGED INTO THE    S880752
* FINAL REPORT. THE SIZE OF EACH SUB-FILE IS CONTROLLED BY THE  S880752
* AMOUNT OF MEMORY AVAILABLE TO HOLD THE SORT STRINGS           S880752
* (3W/ELEMENT) AND THE SUB-FILE INDEX BLOCK (8W/SUB-FILE).      S880752
*  THE SUB-FILE INDEX BLOCKS AND THE SORT BUFFER OVERLAY THE    S880752
* MEMORY USED TO HOLD THE MACRO PROTOTYPES AND THE SYMBOL TABLE.S880752
* THIS MEMORY IS ITERATIVELY DIVIDED INTO THE SUB-FILE INDEX    S880752
* TABLE AQT THE BEGINNING, FOLLOWED BY A SINGLE INTEGRAL SECTOR S880752
* SIZE SORT TABLE. THE LATTER ESTABLISHING THE SIZE, AND HENCE  S880752
* THE NUMBER OF SUB-FILES.                                      S880752
*                                                               S880752
****************************************************************S880752
IT.SIZE  EQU       8W                                           S880752
IT.BGSCT EQU       0W              BEGINNING SECT. NUM. OF RUN  S880752
IT.RNSCT EQU       1W              NUMBER OF SECTORS IN RUN     S880752
IT.BFSCT EQU       2W              NUMBER OF SECTORS IN BUFFER  S880752
IT.INSCT EQU       3W              1ST SECTOR IN BUFFER         S880752
IT.BFBGN EQU       4W              START ADDR OF BUFFER         S880752
IT.BFEND EQU       5W              END ADDR OF BUFFER           S880752
IT.BFPOS EQU       6W              CURRENT BUFFER POSITION      S880752
IT.NMELS EQU       7W              NUMBER OF ELEMENTS IN RUN    S880752
*                                                               S880752
WRTR.RET DATAW     0               RETURN ADDRESS               S880752
NUMRECS  DATAW     0               HOLDS NUMBER OF ELEMENTS     S880752
MEMSTRT  DATAW     0               HOLDS START OF MEM AREA-LOW  S880752
MEMENDR  DATAW     0               HOLDS END OF MEM AREA - HIGH S880752
MEMSIZ.B DATAW     0               HOLDS MEM AREA SIZE IN BYTES S880752
DSCSIZ.S DATAW     0               HOLDS DISC FILE SIZE-SECTORS S880752
DSCSIZ.B DATAW     0               HOLDS DISC FILE SIZE-BYTES   S880752
NUMRUNS  DATAW     0               HOLDS NUM. OF RUNS TO MERGE  S880752
SRTSIZ.S DATAW     0               SIZE OF SORT RUNS IN SECTORS S880752
BUFSTRT  DATAW     0               ADDR OF SORT BUFFER          S880752
HEDSIZ.B DATAW     0               SIZE OF INDEX BLOCK AREA     S880752
BUFSIZ.B DATAW     0          BALANCE OF MEM AREA (-HEDSIZE.B)  S880752
BUFSIZ.S DATAW     0          BUFSIZ.B DIVIDED BY SECTOR SIZE   S880752
ELESLFT  DATAW     0               NUM OF UNPROCESSED ELEMENTS  S880752
*                                                               S880752
INQBUF   RES       8W                                           S880752
*                                                               S880752
WRITEREP CEQU      $                                            ESCT-32
         STW       R0,WRTR.RET     SAVE RETURN                  S880752
         LW        R5,RECCOUN                                   S880752
         BZ        XRM.XIT         SKIP IF NO SYMBOLS           S880752
         STW       R5,NUMRECS      INIT RECORD COUNT            S880752
WREP.1   CEQU      $               LOOP TOP                     C010-32
         LW        R5,LOW                                       S880752
         STW       R5,MEMSTRT      INIT MEMORY BUFFER START     S880752
         LW        R5,HIGH                                      S880752
         STW       R5,MEMENDR      INIT MEMORY BUFFER END       S880752
         SUMW      R5,LOW          COMPUTE SIZE OF BUFFER       C010-32
         CAMW      R5,=X'8000'     IS IT AT LEAST 4 MAP BLOCKS  C010-32
         BGE       WREP.2          CONTINUE IF IT IS            C010-32
         SVC       1,X'69'         ELSE GET ANOTHER             C010-32
         TRR       R3,R3           SET CC'S                     C010-32
         BZ        XRM.XIT         FORGET XREF IF WE CAN'T      C010-32
         STW       R4,HIGH         SAVE TOP                     C010-32
         BU        WREP.1          AND TRY AGAIN                C010-32
WREP.2   CEQU      $               CONTINUE                     C010-32
*                                                               S880752
*        COMPUTE THE DISC FILE STATISTICS FROM THE RECORD COUNT S880752
*                                                               S880752
         LW        R5,NUMRECS                                   S880752
         ES        R4                                           S880752
         DVI       R4,64           64 RECORDS PER SECTOR        S880752
         TRR       R4,R4           SET CC'S                     S880752
         BZ        $+2W            SKIP IF NO REMAINDER         S880752
         ADI       R5,1            ELSE BUMP SECTOR COUNT       S880752
         STW       R5,DSCSIZ.S     AND SAVE                     S880752
         ES        R4                                           S880752
         MPI       R4,768          COMPUTE SECT BOUNDED BYTE CT S880752
         STW       R5,DSCSIZ.B     AND SAVE                     S880752
*                                                               S880752
*        COMPUTE SUB-FILE LENGTH                                S880752
*                                                               S880752
         LW        R5,MEMENDR                                   S880752
         SUMW      R5,MEMSTRT                                   S880752
         STW       R5,MEMSIZ.B                                  S880752
*                                                               S880752
         LW        R5,DSCSIZ.B     GET DISC SIZE IN BYTES       S880752
         ES        R4              PREPARE FOR DIVIDE           S880752
         DVMW      R4,MEMSIZ.B     COMPUTE NUMBER OF RUNS       S880752
         TRR       R4,R4           SET CC'S                     S880752
         BZ        $+2W            SKIP                         S880752
XRS.1    CEQU      $               FROM RUN SIZE EVALUATOR      ESCT-32
         ADI       R5,1            ELSE ROUND (OR BUMP)         S880752
         STW       R5,NUMRUNS      AND SAVE                     S880752
         ES        R4                                           S880752
         MPI       R4,IT.SIZE      COMPUTE MEM FOR INDEX TABLE  S880752
         STW       R5,HEDSIZ.B     AND SAVE                     S880752
         ADMW      R5,MEMSTRT      ADD START ADDRESS OF MEMORY  S880752
         STW       R5,BUFSTRT      AND SAVE                     S880752
         LW        R6,MEMENDR      GET END OF MEMORY VALUE      S880752
         SUR       R5,R6           COMPUTE SORT BUFFER SIZE     S880752
         STW       R6,BUFSIZ.B     AND SAVE SIZE                S880752
         TRR       R6,R5                                        S880752
         ES        R4              SET UP                       S880752
         DVI       R4,768          DIVIDE BY SECTOR SIZE        S880752
         STW       R5,BUFSIZ.S     SAVE SIZE (IN SECTORS)       S880752
         TRR       R5,R6           SAVE BUF SIZE FOR LATER      S880752
         LW        R5,DSCSIZ.S     GET SIZE OF DATA SET         S880752
         ES        R4                                           S880752
         DVMW      R4,NUMRUNS      COMPUTE RUN SIZE             S880752
         TRR       R4,R4           ANY REMAINDER                S880752
         BZ        $+1W            SKIP IF NOT                  S880752
         ADI       R5,1            ELSE ROUND UP                S880752
         STW       R5,SRTSIZ.S     SAVE FOR LATER               S880752
         CAR       R5,R6           DOES RUN SIZE FIT IN MEM     S880752
         BGE       XRS.2           CONTINUE IF ALL COVERED      S880752
         LW        R5,NUMRUNS      ELSE RECOVER NUMBER OF RUNS  S880752
         BU        XRS.1           AND LOOP TO CONVERGE         S880752
XRS.2    CEQU      $                                            ESCT-32
*                                                               S880752
*        PRODUCE THE RUNS                                       S880752
*                                                               S880752
         LW        R5,NUMRECS                                   S880752
         STW       R5,ELESLFT                                   S880752
         LW        R5,BUFSTRT      GET ADDR OF SORT BUFFER      S880752
         IFF       UNIXF,SKIP                                   *JCB*
         STW       R5,FCBXR+FCB.ERWA                            S880752
*                                                               S880752
         LW        R5,SRTSIZ.S     GET SUB-FILE SIZE            S880752
         ES        R4                                           S880752
         MPI       R4,768          CONVERT TO BYTES             S880752
         STW       R5,FCBXR+FCB.EQTY                            S880752
         ZMW       FCBXR+FCB.ERAA                               S880752
         SBM       4,FCBXR+FCB.GCFG     SET RANDOM MODE         S880752
SKIP     ANOP                                                   *JCB*
         IFT       UNIXF,SKIP                                   *JCB*
         LW        R1,XR.FCBA      GET XREF FCB ADDR            *JCB*
         STW       R5,FCB.ERWA,X1                               *JCB*
*                                                               *JCB*
         LW        R5,SRTSIZ.S     GET SUB-FILE SIZE            *JCB*
         ES        R4                                           *JCB*
         MPI       R4,768          CONVERT TO BYTES             *JCB*
         STW       R5,FCB.EQTY,X1                               *JCB*
         ZMW       FCB.ERAA,X1                                  *JCB*
         SBM       4,FCB.GCFG,X1   SET RANDOM MODE              *JCB*
SKIP     ANOP                                                   *JCB*
         LNW       R7,NUMRUNS      SET UP LOOP COUNT            S880752
         LW        R3,MEMSTRT      INIT INDEX TABLE POINTER     S880752
*                                                               S880752
XRS.3    CEQU      $               TOP OF SUB-FILE PROC. LOOP   ESCT-32
         IFF       UNIXF,SKIP                                   *JCB*
         M.READ    FCBXR                                        S880752
         LB        R4,FCBXR+FCB.SFLG                            S880752
         BNZ       IOERUT2         REPORT I/O ERROR             S880752
         LW        R5,FCBXR+FCB.RECL    GET AMOUNT READ         S880752
SKIP     ANOP                                                   *JCB*
         IFT       UNIXF,SKIP                                   *JCB*
         LW        R1,XR.FCBA      GET XREF FCB ADDR            *JCB*
         SVC       1,X'31'         READ A RECORD                *JCB*
         LB        R4,FCB.SFLG,X1                               *JCB*
         BNZ       IOERUT2         REPORT I/O ERROR             *JCB*
         LW        R5,FCB.RECL,X1  GET AMOUNT READ              *JCB*
SKIP     ANOP                                                   *JCB*
         ES        R4                                           S880752
         DVI       R4,12           COMPUTE NUMBER OF ELEMENTS   S880752
         CAMW      R5,ELESLFT      COMPARE TO OUTSTANDING COUNT S880752
         BLE       XRS.4                                        S880752
         LW        R5,ELESLFT                                   S880752
         ZMW       ELESLFT                                      S880752
         BU        XRS.5                                        S880752
XRS.4    CEQU      $                                            ESCT-32
         LW        R4,ELESLFT                                   S880752
         SUR       R5,R4                                        S880752
         STW       R4,ELESLFT                                   S880752
XRS.5    CEQU      $                                            ESCT-32
         STW       R5,IT.NMELS,X3  SAVE ELEMENT CNT FOR SUB-FIL S880752
         ES        R4                                           S880752
         MPI       R4,12           CONVERT ELEMENT CNT TO BYTES S880752
         DVI       R4,768          COMPUTE # SECTORS IN SUB-FIL S880752
         TRR       R4,R4           SET CC'S                     S880752
         BZ        $+2W            SKIP IF NO REMAINDER         S880752
         ADI       R5,1            ELSE BUMP SUBFILE LENGTH     S880752
         STW       R5,IT.RNSCT,X3  AND SET INTO INDEX TABLE     S880752
         LW        R1,BUFSTRT      GET ADDR OF BUFFER           S880752
         LW        R5,IT.NMELS,X3  RECOVER NUMBER OF ELEMENTS   S880752
         BL        ISORT                                        S880752
XRS.TSTP CEQU      $                                            ESCT-32
         IFF       UNIXF,SKIP                                   *JCB*
         M.WRIT    FCBXR                                        S880752
         LW        R5,FCBXR+FCB.ERAA   GET FILE POINTER         S880752
         STW       R5,IT.BGSCT,X3  SAVE INDEX IN TABLE          S880752
         LW        R5,SRTSIZ.S     GET SIZE OF SUB-FILE         S880752
         ARMW      R5,FCBXR+FCB.ERAA    ADD TO FILE POINTER     S880752
SKIP     ANOP                                                   *JCB*
         IFT       UNIXF,SKIP                                   *JCB*
         LW        R1,XR.FCBA      GET XREF FCB ADDR            *JCB*
         SVC       1,X'32'         WRITE A RECORD               *JCB*
         LW        R5,FCB.ERAA,X1  GET FILE POINTER             *JCB*
         STW       R5,IT.BGSCT,X3  SAVE INDEX IN TABLE          *JCB*
         LW        R5,SRTSIZ.S     GET SIZE OF SUB-FILE         *JCB*
         ARMW      R5,FCB.ERAA,X1  ADD TO FILE POINTER          *JCB*
SKIP     ANOP                                                   *JCB*
         ADI       R3,IT.SIZE      BUMP INDEX TABLE POINTER     S880752
         BIB       R7,XRS.3        LOOP FOR ALL SUBFILES        S880752
*                                                               S880752
*        NOW MERGE THE RUNS                                     S880752
*                                                               S880752
*        COMPUTE SIZE OF EACH RUN BUFFER                        S880752
*                                                               S880752
XMERGE   CEQU      $                                            ESCT-32
         LW        R7,BUFSIZ.S     GET SIZE OF SORT BUFF - SECT S880752
         ES        R6                                           S880752
         DVMW      R6,NUMRUNS      COMPUTE SIZE OF EACH RUN BUF S880752
         TRR       R7,R4           HOLD SIZE IN SECTORS         S880752
         ES        R6                                           S880752
         MPI       R6,768          CONVERT TO BYTES             S880752
         TRR       R4,R6           SIZE IN SECTORS TO R6        S880752
         LNW       R0,NUMRUNS      SET LOOP COUNT               S880752
         LW        R3,MEMSTRT      AND INDEX TABLE POINTER      S880752
         LW        R2,BUFSTRT      SET UP BEGINNING OF 1ST BUFF S880752
*                                                               S880752
* R0=-LOOPCOUNT, R2=BUFFPNTR, R3=IT. PNTR, R6=BUFSCT, R7=BUFBYT S880752
*                                                               S880752
XRM.1    CEQU      $                                            ESCT-32
         LI        R4,-1                                        S880752
         STW       R4,IT.INSCT,X3  SHOW RUN BUFFER NOT INITED   S880752
         CAMW      R2,MEMENDR      IS BUFF IN BOUNDS            S880752
         BGT       XMRG.ER         REPORT ERR IF NOT            S880752
         STW       R2,IT.BFBGN,X3  SET START ADDR THIS BUFFER   S880752
* SELECT MAXIMUM BUFFER SIZE OR RUN SIZE INTO R4,R5             S880752
         LW        R5,IT.NMELS,X3  GET NUMBER OF ELEMENTS       S880752
         ES        R4                                           S880752
         MPI       R4,12           CONVERT TO BYTES             S880752
         CAR       R7,R5           COMPARE TO MAX BUFF SIZE     S880752
         BLT       XRM.2                                        S880752
         TRR       R7,R5           USE MAX SIZE                 S880752
         TRR       R6,R4           USE MAX SCT ALSO             S880752
         BU        XRM.3           AND CONTINUE                 S880752
XRM.2    CEQU      $               ELSE USE COMPUTED REQUIREME  ESCT-32
         STW       R5,XRM.T1       SAVE                         S880752
         ES        R4                                           S880752
         DVI       R4,768          CONVERT TO SECTORS           S880752
         TRR       R4,R4           SET CC'S                     S880752
         BZ        $+2W            SKIP IF ZERO                 S880752
         ADI       R5,1            ELSE ROUND UP                S880752
         TRR       R5,R4           COPY SECTOR REQUIREMENT      S880752
         LW        R5,XRM.T1       AND RESTORE BYTE REQUIREMENT S880752
* R0=-LOOP, R2=BUFADDR, R3=I.T.PNTR, R4,R5=SELECTED,R6,R7=BUFF  S880752
XRM.3    CEQU      $                                            ESCT-32
         TRR       R5,R1           COPY SIZE IN BYTES           S880752
         ADR       R2,R1           ADD BUFFER START             S880752
         SUI       R1,1            COMPUTE TRIAL END ADDR       S880752
         CAMW      R1,MEMENDR      AND SEE IF IT FITS           S880752
         BLE       XRM.4           CONTINUE IF IT DOES          S880752
         SUI       R5,768          ELSE DECREMENT SIZE(BYTES)   S880752
         SUI       R4,1            AND SIZE(SECTORS)            S880752
         BZ        XMRG.ER                                      S880752
         BU        XRM.3           AND LOOP TILL IT DOES.       S880752
XRM.4    CEQU      $                                            ESCT-32
         STW       R1,IT.BFEND,X3  SAVE BUFFER END VALUE        S880752
         STW       R1,IT.BFPOS,X3       AND SHOW BUFFER EMPTY   S880752
         STW       R4,IT.BFSCT,X3  SAVE BUFF LENGTH IN SECTORS  S880752
         ADR       R5,R2           ADVANCE BUFF START LOCATION  S880752
         ADI       R3,IT.SIZE      BUMP TABLE POINTER           S880752
         BIB       R0,XRM.1                                     S880752
*                                                               S880752
         ZMW       XRBUFP          INIT LINE ASSEMBLY POINTER   S880752
         LI        R2,-30W         LINE LENGTH                  S880752
         LW        R6,=C'    '     GET SOME BLANKS              S880752
         STW       R6,PRMT+30W,X2  AND BLANK THE LINE           S880752
         BIW       R2,$-1W         TO ITS END                   S880752
         LI        R6,-1           SET INIT VALUE               S880752
         STW       R6,XRCNAME      INTO XRCNAME                 S880752
         STW       R6,XRCNAME+1W                                S880752
         LW        R2,MEMSTRT                                   S880752
XRM.5    CEQU      $      LOOP TO PERFORM THE MERGE             ESCT-32
         BL        XR.NWAY                                      S880752
         BS        XRM.XIT         FINISHED WHEN CC1 SET        S880752
         LW        R6,0W,X3        GET ELEMENT                  S880752
         LW        R7,1W,X3                                     S880752
         LW        R5,2W,X3                                     S880752
         SRC       R5,1            REPPOSITION DATA             S880752
         STD       R6,XRBUF                                     S880752
         STW       R5,XRBUF+2W                                  S880752
         BL        XRPRNT                                       S880752
         BU        XRM.5                                        S880752
XRM.XIT  LW        R1,QAFCBLO1     LENGTH AND ADDR OF PRINT BUF S880752
         IFT       UNIXF,SKIP                                   *JCB*
         ZR        R7              SIGNALS PPP NO ERRORS EXITS  *JCB*
*                                  FOR THIS LINE.               *JCB*
SKIP     ANOP                                                   *JCB*
         BL        PPP             PRINT THE LAST XREF LINE     S880752
         BU        *WRTR.RET       RETURN TO CALLER             S880752
XMRG.ER  CEQU      $                                            ESCT-32
         M.BORT    XR01                                         S880752
XR01     DATAW     C'XR01'                                      S880752
XRM.T1   DATAW     0               TEMP FOR R5                  S880752
*---------------------------------------------------------------S880752
         TITLE     XR.NWAY - PERFORM N-WAY MERGE OF RUNS        S880752
*                                                               S880752
*     IN   R2= ADDR OF INDEX TABLE                              S880752
*          NUMRUNS = NUMBER OF RUNS PRODUCED BY SORT            S880752
*                                                               S880752
*    OUT   R3 = ADDR OF SELECTED (LOWEST) ENTRY                 S880752
*          CC1 SET IF ALL DONE WITH MERGE                       S880752
*---------------------------------------------------------------S880752
*                                                               S880752
XR.NWAY  CEQU      $                                            ESCT-32
         ZBR       R0,1            RESET ALL DONE FLAG          S880752
         STF       R0,XRNW.RSV     SAVE CALLER REGS             S880752
XRNW.1   CEQU      $               LOOP TOP                     ESCT-32
         LW        R4,IT.NMELS,X2  ANY DATA LEFT THIS RUN       S880752
         BNZ       XRNW.11         CONTINUE IF THERE IS         S880752
         ADI       R2,IT.SIZE      ELSE BUMP TO NEXT I.TABLE IF S880752
         CAMW      R2,BUFSTRT      ARE ALL RUNS EMPTY?          S880752
         BLT       XRNW.1          CONTINUE IF NOT              S880752
         SBM       1,XRNW.RSV      ELSE INDICATE ALL DONE       S880752
         BU        XRNW.XIT        AND RETURN                   S880752
XRNW.11  CEQU      $                                            ESCT-32
         LW        R4,IT.BFPOS,X2  GET CURR POSITION IN 1ST BYT S880752
         CAMW      R4,IT.BFEND,X2  IS THERE UNPROCESSED DATA    S880752
         BLT       XRNW.2          CONTINUE IF THERE IS         S880752
         BL        XRNW.RD1        ELSE REFILL THE BUFFER       S880752
         BNS       XRNW.11         RETRY IF READ OK             S880752
         BU        XRNW.1          ELSE KEEP LOOKING            S880752
XRNW.2   CEQU      $               CONTINUE                     ESCT-32
         TRR       R2,R3           COPY INDEX TABLE ADDR OF 1ST S880752
XRNW.3   CEQU      $                                            ESCT-32
         ADI       R3,IT.SIZE      AND BUMP R2 TO SECOND ENTRY  S880752
         CAMW      R3,BUFSTRT      IS THIS A VALID I.TABLE ENTRYS880752
         BLT       XRNW.31         CONTINUE IF IT IS            S880752
         STW       R4,XRNW.RSV+3W  ELSE ONLY ONE RUN REMAINS    S880752
         LI        R7,3W           BUMP BY ONE ENTRY            S880752
         ARMW      R7,IT.BFPOS,X2  AND UPDATE ELEMENT POINTER   S880752
         LI        R7,-1                                        S880752
         ARMW      R7,IT.NMELS,X2  DECREMENT REMAINING COUNT    S880752
         BU        XRNW.XIT        SO USE IT AND RETURN         S880752
XRNW.31  CEQU      $                                            ESCT-32
         LW        R5,IT.NMELS,X3  ANY DATA IN THIS RUN         S880752
         BZ        XRNW.3          TRY NEXT IF NOT              S880752
         LW        R5,IT.BFPOS,X3  GET CURRENT POSITION IN NEXT S880752
         CAMW      R5,IT.BFEND,X3  IS THERE UNPROCESSED DATA    S880752
         BLT       XRNW.4          CONTINUE IF THERE IS         S880752
         BL        XRNW.RD2        FILL SECOND BUFFER           S880752
         BNS       XRNW.31         RETRY IF READ IS OK          S880752
         BU        XRNW.3          AND RETRY                    S880752
XRNW.4   CEQU      $                                            ESCT-32
         XCR       R2,R4           SET UP X2 TO POINT TO BUF 1  S880752
         XCR       R3,R5           SET UP X3 TO POINT TO BUF 2  S880752
*>>>>                                                           S880752
         LW        R7,0W,X2                                     S880752
         EOMW      R7,0W,X3        CHECK SIGN OF 1ST WORD       S880752
         BGE       XRNW.41         BR, IF THE SAME              S880752
         TBM       0,0,X2          TEST SIGN OF 1ST BUFFER WORD S880752
         BS        XRNW.6          TREAT AS GREATER             S880752
         BU        XRNW.5          ELSE ITS LESS                S880752
XRNW.41  CEQU      $                                            ESCT-32
         LW        R7,0W,X2        GET 1ST WORD OF BUF 1 ENTRY  S880752
         CAMW      R7,0W,X3        COMPARE TO 1ST WORD OF BUF 2 S880752
         BLT       XRNW.5          PROCESS BUF1 < BUF2          S880752
         BGT       XRNW.6          PROCESS BUF2 < BUF1          S880752
*>>>>                                                           S880752
         LW        R7,1W,X2                                     S880752
         EOMW      R7,1W,X3        CHECK SIGN OF 2ND WORD       S880752
         BGE       XRNW.42         BR, IF THE SAME              S880752
         TBM       0,1W,X2         TEST SIGN OF 2ND BUFFER WORD S880752
         BS        XRNW.6          TREAT AS GREATER             S880752
         BU        XRNW.5          ELSE ITS LESS                S880752
XRNW.42  CEQU      $                                            ESCT-32
         LW        R7,1W,X2        ELSE CONTINUE TEST           S880752
         CAMW      R7,1W,X3        WITH SECOND WORD OF ENTRY    S880752
         BLT       XRNW.5          PROCESS BUF1 < BUF2          S880752
         BGT       XRNW.6          PROCESS BUF2 < BUF1          S880752
*>>>>                                                           S880752
         LW        R7,2W,X2                                     S880752
         EOMW      R7,2W,X3        CHECK SIGN OF 3RD WORD       S880752
         BGE       XRNW.43         BR, IF THE SAME              S880752
         TBM       0,2W,X2         TEST SIGN OF 3RD BUFFER WORD S880752
         BS        XRNW.6          TREAT AS GREATER             S880752
         BU        XRNW.5          ELSE ITS LESS                S880752
XRNW.43  CEQU      $                                            ESCT-32
         LW        R7,2W,X2        ESLE CONTINUE TEST           S880752
         CAMW      R7,2W,X3                                     S880752
         BGT       XRNW.6          PROCESS BUF2 < BUF1          S880752
*>>>>                                                           S880752
XRNW.5   CEQU      $               (R2,R4) IS </=               ESCT-32
         XCR       R2,R4                                        S880752
         XCR       R3,R5                                        S880752
         BU        XRNW.3                                       S880752
XRNW.6   CEQU      $               (R3,R5) IS </=               ESCT-32
         XCR       R2,R4                                        S880752
         XCR       R3,R5                                        S880752
         TRR       R3,R2                                        S880752
         TRR       R5,R4           SELECT (R3,R5)               S880752
         BU        XRNW.3                                       S880752
XRNW.XIT CEQU      $               RETURN TO CALLER             ESCT-32
         LF        R0,XRNW.RSV                                  S880752
         TRSW      R0                                           S880752
         NOP                                                    S880752
*                                                               S880752
XRNW.RSV RES       8W                                           S880752
*                                                               S880752
*---------------------------------------------------------------S880752
         TITLE     XRNW.RD2- READ SUB-FILE INTO RUN BUFFER      S880752
*                                                               S880752
*  IN   R3= ADDR OF IT. ENTRY DESCRIBING BUFFER TO FILL         S880752
*                                                               S880752
*  OUT  CC1 SET IF REQUESTED RUN HAS BEEN COMPLETELY READ       S880752
*                                                               S880752
*---------------------------------------------------------------S880752
XRNW.RD2 ZBR       R0,1            RESET END INDICATOR          S880752
         STW       R0,XRD2.RSV                                  S880752
         XCR       R2,R3           INVERT POINTERS              S880752
         BL        XRNW.RD1        AND DO READ                  S880752
         BNS       $+2W            SKIP IF OK                   S880752
         SBM       1,XRD2.RSV     ELSE INDICATE END TO CALLER   S880752
         XCR       R2,R3           PUT POINTERS BACK            S880752
         LW        R0,XRD2.RSV                                  S880752
         TRSW      R0              RETURN                       S880752
*                                                               S880752
XRD2.RSV DATAW     0                                            S880752
*                                                               S880752
*---------------------------------------------------------------S880752
         TITLE     XRNW.RD1- READ SUB-FILE INTO RUN BUFFER      S880752
*                                                               S880752
*  IN   R2= ADDR OF IT. ENTRY DESCRIBING BUFFER TO FILL         S880752
*                                                               S880752
*  OUT  CC1 SET IF REQUESTED RUN HAS BEEN COMPLETELY READ       S880752
*                                                               S880752
*---------------------------------------------------------------S880752
*                                                               S880752
XRNW.RD1 CEQU      $                                            ESCT-32
         ZBR       R0,1              RESET RUN COMPLETE FLAG    S880752
         STD       R0,XRRD.RSV                                  S880752
         LW        R1,IT.INSCT,X2  GET CURRENT BUFFER STATE     S880752
         BN        XRRD.1          PROCESS 1ST TIME LOAD        S880752
         ADMW      R1,IT.BFSCT,X2  ELSE COMPUTE SECTOR TO READ  S880752
         STW       R1,IT.INSCT,X2  UPDATE SECTOR POINTER IN IT. S880752
         IFF       UNIXF,SKIP                                   *JCB*
         STW       R1,FCBXR+FCB.ERAA AND IN FCB                 S880752
SKIP     ANOP                                                   *JCB*
         IFT       UNIXF,SKIP                                   *JCB*
         TRR       R1,R0           VALUE TO XR                  *JCB*
         LW        R1,XR.FCBA      GET XREF FCB ADDR            *JCB*
         STW       R0,FCB.ERAA,X1  AND IN FCB                   *JCB*
SKIP     ANOP                                                   *JCB*
         BU        XRRD.2          MERGE WITH COMMON CODE       S880752
XRRD.1   CEQU      $               FIRST TIME                   ESCT-32
         LW        R1,IT.BGSCT,X2  GET ADDR OF FIRST SECT IN R1 S880752
         STW       R1,IT.INSCT,X2  INTO IT. ENTRY               S880752
         IFF       UNIXF,SKIP                                   *JCB*
         STW       R1,FCBXR+FCB.ERAA AND INTO FCB               S880752
SKIP     ANOP                                                   *JCB*
         IFT       UNIXF,SKIP                                   *JCB*
         TRR       R1,R0           VALUE TO XR                  *JCB*
         LW        R1,XR.FCBA      GET XREF FCB ADDR            *JCB*
         STW       R0,FCB.ERAA,X1  AND INTO FCB                 *JCB*
SKIP     ANOP                                                   *JCB*
XRRD.2   CEQU      $               MERGE POINT                  ESCT-32
         LW        R1,IT.RNSCT,X2  GET SIZE OF THIS RUN         S880752
         BZ        XRRD.EXT        RETURN CC1 IF RUN ALL READ   S880752
         SUMW      R1,IT.BFSCT,X2  DECREMENT BY BUFF SIZE       S880752
         BGE       XRRD.3          CONTINUE IF REMAINING RUN >= S880752
         LW        R0,IT.RNSCT,X2  ELSE GET REMAINING LENGTH    S880752
         ZMW       IT.RNSCT,X2     AND SHOW RUN COMPLETE        S880752
         BU        XRRD.4          NOW MERGE UP                 S880752
XRRD.3   CEQU      $                                            ESCT-32
         STW       R1,IT.RNSCT,X2  AND RESTORE IN IT. ENTRY     S880752
         LW        R0,IT.BFSCT,X2  GET BUFFER SIZE IN SECTORS   S880752
XRRD.4   CEQU      $                                            ESCT-32
         TRR       R0,R1           MOVE XFER LENGTH             S880752
         ES        R0                                           S880752
         MPI       R0,768          COPMUTE SIZE IN BYTES        S880752
         IFF       UNIXF,SKIP                                   *JCB*
         STW       R1,FCBXR+FCB.EQTY AND SAVE IN FCB            S880752
         LW        R1,IT.BFBGN,X2  GET BUFFER ADDR              S880752
         STW       R1,IT.BFPOS,X2  RESET BUFFER POSITION        S880752
         STW       R1,FCBXR+FCB.ERWA AND SET INTO FCB           S880752
         M.READ    FCBXR                                        S880752
         LB        R1,FCBXR+FCB.SFLG GET STATUS BYTE            S880752
SKIP     ANOP                                                   *JCB*
         IFT       UNIXF,SKIP                                   *JCB*
         TRR       R1,R0           VALUE TO XR                  *JCB*
         LW        R1,XR.FCBA      GET XREF FCB ADDR            *JCB*
         STW       R0,FCB.EQTY,X1  AND SAVE IN FCB              *JCB*
         LW        R0,IT.BFBGN,X2  GET BUFFER ADDR              *JCB*
         STW       R0,IT.BFPOS,X2  RESET BUFFER POSITION        *JCB*
         STW       R0,FCB.ERWA,X1  AND SET INTO FCB             *JCB*
         SVC       1,X'31'         DO THE READ                  *JCB*
         LB        R1,FCB.SFLG,X1  GET STATUS BYTE              *JCB*
SKIP     ANOP                                                   *JCB*
         BNZ       XRRD.ERR        DO ERR EXIT                  S880752
XRRD.XIT CEQU      $                                            ESCT-32
         LD        R0,XRRD.RSV                                  S880752
         TRSW      R0                                           S880752
         NOP                                                    S880752
XRRD.EXT CEQU      $                                            ESCT-32
         SBM       1,XRRD.RSV                                   S880752
         BU        XRRD.XIT                                     S880752
*                                                               S880752
XRRD.ERR CEQU      $                                            ESCT-32
         TRR       R1,R5                                        S880752
         M.CONBAD                                               S880752
         STB       R7,XRRD.MST+1B                               S880752
         SRL       R7,8                                         S880752
         STB       R7,XRRD.MST                                  S880752
         LD        R2,XRRD.MSG                                  S880752
         LW        R5,XRRD.ABC                                  S880752
         ZR        R6                                           S880752
         ZR        R7                                           S880752
         SVC       1,X'62'                                      S880752
         BOUND     1D                                           S880752
XRRD.MSG DATAB     C'T2 ST='                                    S880752
XRRD.MST DATAB     0,0                                          S880752
XRRD.ABC DATAW     C'RD U'                                      S880752
XRRD.RSV DATAD     0                                            S880752
*                                                               S880752
*---------------------------------------------------------------S880752
         TITLE     ISORT - INTERNAL SORT OF SUB-FILE            S880752
*                                                               S880752
****************************************************************S880752
*                                                               S880752
*        D.L. SHELL'S SORT                                      S880752
*                                                               S880752
****************************************************************S880752
*                                                               S880752
*        R1        BASE ADDRESS OF THE TABLE TO BE SORTED       S880752
*        R5        NUMBER OF ITEMS TO BE SORTED                 S880752
*                                                               S880752
****************************************************************S880752
         BOUND     1W                                           S880752
ISORT    CEQU      $                                            ESCT-32
         STF       R0,ISRT.RSV                                  S880752
*                                                               S880752
         LI        R2,-ISRT.INL    GET LENGTH OF INCREMENT TABLES880752
ISRT.01  CEQU      $                                            ESCT-32
         CAMW      R5,ISRT.INC+ISRT.INL,X2                      S880752
         BLT       ISRT.02                                      S880752
         BIW       R2,ISRT.01                                   S880752
ISRT.02  CEQU      $                                            ESCT-32
         LI        R0,ISRT.INL                                  S880752
         ADR       R2,R0           INCREMENT                    S880752
         SUI       R0,2W                                        S880752
         CI        R0,4                                         S880752
         BGE       $+2W                                         S880752
         LI        R0,4                                         S880752
*                                                               S880752
         MPI       R4,3W           COMPUTE ARRAY SIZE IN BYTES  S880752
         STW       5,SORTN         AND SAVE                     S880752
         ADR       R1,R5           ADD IN BASE                  S880752
         STW       R5,SORT.LIM                                  S880752
*                                                               S880752
* OUTER LOOP                                                    S880752
SORT20   CEQU      $                                            ESCT-32
         TRR       R0,R2                                        S880752
         LW        R5,ISRT.INC,X2  GET INCREMENT                S880752
         BZ        SORT40          FINISHED                     S880752
         SUI       R0,1W           DECREMENT POINTER            S880752
*                                                               S880752
         MPI       R4,3W           COMPUTE INCREMENT IN BYTES   S880752
*!!!!!!!!!!SUI!!!!!!!R5,3W!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!S880752
         TRN       R5,R6                                        S880752
         STW       5,SORTM         M=M/2                        S880752
         ADMW      6,SORTN         N-M                          S880752
         STW       6,SORTK         K=N-M                        S880752
*                                                               S880752
         LI        5,0W                                         S880752
         STW       5,SORTJ         J=0                          S880752
SORT41   STW       5,SORTI         I=J                          S880752
*                                                               S880752
SORT49   CEQU      $                                            ESCT-32
         LW        R1,SORTB        GET ARRAY BASE               S880752
         ADMW      R1,SORTI        ADD IN "I" INDEX             S880752
         TRR       R1,R2           COPY FOR "L" INDEX           S880752
         ADMW      R2,SORTM        ADD IN INCREMENT             S880752
         CAMW      R2,SORT.LIM     STILL IN RANGE               S880752
         BGE       SORT20          STEP OUTER LOOP IF NOT       S880752
         LI        3,-3W           NUMBER OF WORDS TO BE COMPARES880752
COMPP    CEQU      $                                            ESCT-32
         CAMW      R1,SORT.LIM                                  S880752
         BGE       WHOOPS                                       S880752
         CAMW      R2,SORT.LIM                                  S880752
         BGE       WHOOPS                                       S880752
         LW        7,0,1           A(I)                         S880752
         EOMW      7,0,2           A(L)                         S880752
         BGE       COMPQ           SIGNS ARE THE SAME           S880752
         TBM       0,0,1           CHECK SIGN OF A(I)           S880752
         BS        SORT50          A(I).GT.A(L)                 S880752
         BU        SORT60          A(I).LT.A(L)                 S880752
COMPQ    LW        7,0,1           A(I)                         S880752
         CAMW      7,0,2           A(L)                         S880752
         BLT       SORT60          A(I) .LT. A(L)               S880752
         BGT       SORT50          A(I) .GT. A(L)               S880752
         ABR       1,29            ADVANCE ADDRESS BY DISTANCE BS880752
         ABR       2,29            WORDS OF THE SAME ITEM       S880752
         BIW       3,COMPP         COMPARE EACH WORD            S880752
         BU        SORT60          A(I) .EQ. A(I+M)             S880752
WHOOPS   BU        WHOOPS                                       S880752
*                                                               S880752
SORT50   LW        4,0,1                                        S880752
         LW        7,0,2                                        S880752
         STW       4,0,2                                        S880752
         STW       7,0,1           INTERCHANGE OF ONE WORD COMPLS880752
         ABR       1,29            GET ADDRESS FOR NEXT WORD OF S880752
         ABR       2,29            GET ADDRESS FOR NEXT WORD OF S880752
         BIW       3,SORT50        MORE WORDS TO EXCHANGE       S880752
*                                                               S880752
         LW        7,SORTI                                      S880752
         SUMW      7,SORTM                                      S880752
         STW       7,SORTI         I=I-M                        S880752
         BGE       SORT49          BUBBLE BACK THROUGH EARLY INCS880752
*                                                               S880752
SORT60   CEQU      $                                            ESCT-32
         LW        5,SORTJ                                      S880752
         ADI       R5,3W           BUMP J                       S880752
         STW       R5,SORTJ        AND SAVE                     S880752
         CAMW      5,SORTK                                      S880752
         BLE       SORT41          IF(J-K)41,41,20              S880752
         BU        SORT20                                       S880752
SORTME   DATAW     0               SAVE INCREMENT IN ELEMENTS   S880752
SORTN    RES       1W              NUMBER OF ITEMS IN BYTES     S880752
SORTI    RES       1W                                           S880752
SORTM    RES       1W                                           S880752
SORTJ    RES       1W                                           S880752
SORTK    RES       1W                                           S880752
SORT.LIM DATAW     0                                            S880752
SORT40   CEQU      $                                            ESCT-32
         LF        R0,ISRT.RSV                                  S880752
         TRSW      R0              RETURN                       S880752
*                                                               S880752
ISRT.RSV DATAW     0                                            S880752
SORTB    DATAW     0               HOLDS BASE ADDR OF ARRAY     S880752
         DATAW     0                                            S880752
         DATAW     0                                            S880752
         DATAW     0                                            S880752
         DATAW     0               HOLDS NUMBER OF ELEMENTS     S880752
         DATAW     0                                            S880752
         DATAW     0                                            S880752
ISRT.INC DATAW     0,1,4,13,40,121,364,1093,3280,9841,29524     S880752
         DATAW     88573,265720,797161,2391484,7174453          S880752
ISRT.INL DEQU      $-ISRT.INC                                   ESCT-32
*                                                               S880752
*---------------------------------------------------------------S880752
         TITLE     XRPRNT - FORMAT ENTRY INTO LINE              S880752
*                                                               S880752
*  INPUT:  XRBUF,XRBUF+1W,XRBUF+2W = SYMBOL+CONTROL WORD        S880752
*                                                               S880752
*---------------------------------------------------------------S880752
*                                                               S880752
XRPRNT   CEQU      $                                            ESCT-32
         STF       R0,XRP.RSV                                   S880752
         LW        6,XRBUF+0W      CHARS 1-4 OF THE SYMBOL
         LW        7,XRBUF+1W      CHARS 5-8 OF THE SYMBOL
         CAMD      6,XRCNAME       IS THIS SAME AS PRECEEDING SYMBOL?
         BEQ       XRPS7        YES
         STD       6,XRCNAME       THE NEW SYMBOL
         LW        1,QAFCBLO1      LENGTH AND ADR OF PRINT BUFFER
         LB        2,PRMT+3W       FIRST CHAR OF NAME.
         CAMB      2,=X'FF'        IS IT AN INTERNAL SYMBOL?
         BCF       EQ,$+3W         NO.
         LI        2,X'21'         INT SYM LEAD CHAR.
         STB       2,PRMT+3W       REPLACE X'FF' IN BUFFER WITH X'21'
         CI        2,G')'          IT MAY BE A COMMON BLOCK
         BNE       XRGETI9         NO
         LB        2,PRMT+2B       GET TYPE CODE
         CI        2,G'D'          CHECK IF A COMMON BLOCK
         BNE       XRGETI9
         LI        2,G'S'          ITS AN SSECT CHANGE SYMBOL
         STB       2,PRMT+2B       SAVE IT
XRGETI9  CEQU      $                                            ESCT-32
         TBM       22,OPTION       DOES USER WANT ALL SYMBOLS  AS17
         BS        XRPS1           BR IF HE DOES  AS17
         LB        R2,PRMT+2B      GET TYPE CHAR AS17
         CI        R2,G'L'         IS IT LITERAL AS17
         BEQ       XRPS1           PRINT IT ANYWAY AS17
         LW        R2,XRBUFP       GET BUFFER POINTER AS17
         CI        R2,8            TEST IF MORE THAN DEF IN LINE AS17
         BGT       XRPS1           PRINT IF SYMBOL USED AS17
         LW        R2,PRMT+3W      GET SYMBOL AS17
         CAMW      R2,=C'    '     IS IT BLANK    AS17
         BEQ       XRPS1           MUST BE 2ND LINE, PRINT IT AS17
         BU        XRPS8           IGNOR THIS LINE  AS17
         IFF       UNIXF,SKIP                                   *JCB*
XRPS1    BL        PPP            PRINT THE PRESENTLY FORMED LINE AS17
SKIP     ANOP                                                   *JCB*
         IFT       UNIXF,SKIP                                   *JCB*
XRPS1    ZR        R7              SIGNALS PPP NO ERRORS EXITS  *JCB*
*                                  FOR THIS LINE.               *JCB*
         BL        PPP            PRINT THE PRESENTLY FORMED LN *JCB*
SKIP     ANOP                                                   *JCB*
XRPS8    LI        2,-30W         SET UP TO CLEAR 120 BYTES     AS17
         LW        6,=C'    '      ASCII SPACES
         STW       6,PRMT+30W,2    SPACES TO BUFFER
         BIW       2,$-1W
         ZMW       XRBUFP
         LA        3,PRMT          WHERE TO PLACE THE SYMBOL'S VALUE
         LA        2,XRCDATA       WHERE CODED VALUE IS
         ZBR       R2,0            INDICATE PROGRAM CNTR PROC.  EINS-31
         BL        LOCH
         LD        6,XRCNAME
         LB        5,XRCDATA       THE TYPE OF THE SYMBOL
         ZBR       5,24            CLEAR DSECT/CSECT FLAG
         CI        5,TYPL          WAS TYPE LITERAL
         BEQ       XRPS4        YES
         CI        5,TYMACDEF      IS IT A MACRO OR A FORM
         BLT       XRPS5        NO
         CI        5,12            WAS TYPE A DATAPOOL?
         BCF       EQ,XRPS3.1      NO
         LI        5,G'A'          YES, USE DATAPOOL DESCRIPTOR
         LB        2,XRCDATA+1B    GET DATAPOOL NUMBER
         CI        2,X'FF'         IS IT SSECT
         BNE       XRPS3.0         NO
         LI        5,G'0'
         STB       5,PRMT+3B
         LI        5,G'S'
XRPS3.0  CEQU      $                                            ESCT-32
         STB       5,PRMT+2B       PUT IN PRINT BUFFER
         BU        XRPS5           GO PUT IN PRBUF
XRPS3.1  CEQU      $               NOT A DATAPOOL ITEM          ESCT-32
         CI        5,20            IS IT OTHER THAN VALUE?
         BGT       XRPS6        YES THEN TAKE RESTORATIVE MEASURES.
         LND       6,XRCNAME       MACRO/FORM NAMES ARE CODED
         BU        XRPS5           GO PLACE INTO BUFFER
XRPS4    CEQU      $                                            ESCT-32
         TRR       7,5             THE LITERAL VALUE
         BL        BTX             CONVERT TO ASCII CODED HEX
XRPS5    CEQU      $                                            ESCT-32
         STW       6,PRMT+3W       PLACE INTO PRINT BUFFER
         STW       7,PRMT+4W
*!!!!!!!!BU!!!!!!!!XRPS2!!!!!!!!!!!GO!GET!NEXT!ITEM!!!!!!!!!!!!!S880752
         BU        XRP.XIT         RETURN                       S880752
XRPS6    CEQU      $                                            ESCT-32
         STW       6,PRMT+3W
         STW       7,PRMT+4W
         LW        6,=C'    '
         STW       6,PRMT+0W
         STW       6,PRMT+1W
XRPS7    CEQU      $                                            ESCT-32
         LW        1,XRBUFP
         ADI       1,9W            ALLOW FOR MARGINS ON THE PRINTER
         CAMW      1,XRLINELIM     CHECK AGAINST MAX LINE SIZE
         BCT       LE,XRPS9        MORE SPACE ON THE LINE
         LW        1,QAFCBLO1      LENGTH AND ADR OF PRINT BUFFER
         LB        2,PRMT+3W       FIRST CHAR OF NAME.
         CAMB      2,=X'FF'        IS IT AN INTERNAL SYMBOL?
         BCF       EQ,$+3W         NO.
         LI        2,X'21'         INT SYM LEAD CHAR.
         STB       2,PRMT+3W       REPLACE X'FF' IN BUFFER WITH X'21'
         IFF       UNIXF,SKIP                                   *JCB*
         BL        PPP            PRINT THE FORMED LINE
SKIP     ANOP                                                   *JCB*
         IFT       UNIXF,SKIP                                   *JCB*
         ZR        R7              SIGNALS PPP NO ERRORS EXITS  *JCB*
*                                  FOR THIS LINE.               *JCB*
         BL        PPP            PRINT THE FORMED LINE         *JCB*
SKIP     ANOP                                                   *JCB*
         LI        2,-30W
         LW        6,=C'    '      ASCII SPACES
         STW       6,PRMT+30W,2    SPACES TO BUFFER
         BIW       2,$-1W
         ZMW       XRBUFP
XRPS9    CEQU      $                                            ESCT-32
         LW        5,XRCDATA       THE SYMBOL ITEM KEY
         LW        1,XRBUFP
         LI        7,G'*'          REFERENCE FLAG
         ZBR       5,2
         ZBR       5,3             CHECK DEFINITION/REFERENCE FLAG
         BS        $+2W         JUST A USAGE OR REFERENCE
         STB       7,PRMT+5W+2B,1   IT WAS A DEFINITION--PLANT A *.
         BL        CONBAD         CONVERT TO PRINTABLE ASCII CODING
         LW        1,XRBUFP
         STB       6,PRMT+5W+3B,1    PLACE ASCII LINE
         STW       7,PRMT+6W,1       NUMBER INTO PRINT BUFFER.
         ABM       28,XRBUFP       INCREMENT PRINT BUFFER POINTER
*!!!!!!!!BU!!!!!!!!XRPS2!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!S880752
XRP.XIT  CEQU      $                                            ESCT-32
         LF        R0,XRP.RSV                                   S880752
         TRSW      R0                                           S880752
*                                                               S880752
XRP.RSV  RES       8W                                           S880752
XRCNAME  RES       1D              HOLDS NAME OF THE NEW ITEM FOR OUTPUT
QAFCBLO1 GEN       12/120,20/B(PRMT)   PRMT QTY AND ADR OF PRINT BUFFER
XRLINELI DATAW     120B    HOLDS NUMBER OF CHARS ON ONE PRINTER S880752
XRCDATA  EQU       XRBUF+2W        THE SYMBOL ITEM KEY
PRMT     EQU       XRBUF+10W       OVERLAY PRINT BUFFER OVER OLD DISC BU
*
* (C) COPYRIGHT 1983 ENCORE COMPUTER CORPORATION
*     ALL RIGHTS RESERVED
*
XRER     CEQU      $                                            ESCT-32
         LW        5,AS05          ABORT CODE TO R5 .
         BU        ABORT
IOERUT2  CEQU      $                                            ESCT-32
         LW        5,AS16          ABORT CODE TO R5
         TBM       2,3W,1          BLOCKING ERROR FLAG
         BNS       $+2W         BRANCH IF NOT SET-I/O ERROR
         LW        5,AS24          ABORT CODE
         BU        ABORT
         SPACE     3
         BOUND     1W
AS05     DATAW     C'AS05'         EOF ON UT2 DURING WRITE.
AS16     DATAW     C'AS16'         UNRECOVERABLE I/O ERROR UT2
AS24     DATAW     C'AS24'         INVALID BLOCKING BUFF CTRL PTR  UT2.
ABORT    CEQU      $                                            ESCT-32
         ZR        1
         BL        ABORTM
*!XRPZ!!!EQU!!!!!!!$!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!LW!!!!!!!!1,QAFCBLO1!!!!!!LENGTH!AND!ADR!OF!PRINT!BUFF!S880752
*!XRPZ1!!!EQU!!!!!!$!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!TITLE!!!!!THE!SORT!AND!OUTPUT!PART!OF!DISC!BASED!XREF!!S880752
*!**************************************************************S880752*
*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!S880752*
*!!!!!!!!THE!SORT!AND!OUTPUT!PART!OF!DISC!BASED!XREF!!!!!!!!!!!!S880752*
*!!!!!!!!!!!!!!!!!!RANDOM!DISC!ACCESS!USED!!!!!!!!!!!!!!!!!!!!!!S880752*
*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!S880752*
*!**************************************************************S880752*
*!!!!!!!!SPACE!!!!!3!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!S880752
*!WRITEREP!!!EQU!!!!!!$!!!!!!!!!!!!WRITE!THE!CONCORDANCE!REPORT!S880752
*!!!!!!!!SBM!!!!!!!4,FCBXR+2W!!!!!!SET!RANDOM!ACCESS.!!!!!!!!!!!S880752
*!!!!!!!!ZBM!!!!!!!0,FCBXR+2W!!!!!!SET!WAIT!MODE!FOR!READS!!!!!!S880752
*!!!!!!!!STW!!!!!!!0,SDX0!!!!!!!!!!SAVE!RETURN!ADDRESS!!!!!!!!!!S880752
*!!!!!!!!STW!!!!!!!7,XRLINELIM!!!!!SAVE!FOR!PRINTER!DESCRIPTION!S880752
*!!!!!!!!LNW!!!!!!!1,RECCOUN!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!CI!!!!!!!!1,0!!!!!!!!!!!!!DID!ANY!SYMBOLS!OCCUR!?!!!!!!S880752
*!!!!!!!!BEQ!!!!!!!*SDX0!!!!!!!!NO!SYMBOLS!OCCURRED!-!EXIT!!!!!!S880752
*!!!!!!!!STW!!!!!!!1,XRMXRECS!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!SVC!!!!!!!1,X'44'!!!!!!!!!!CORE!ADR.!INQ.!!!!!!!!!!!!!!S880752
*!!!!!!!!TRR!!!!!!!7,1!!!!!!!!!!!!!!END!ADR.!TO!R1.!!!!!!!!!!!!!S880752
*!!!!!!!!ANMW!!!!!!1,=X'0007FFFC'!!ADDRESS!PART!ONLY!PLEASE!!!!!S880752
*!!!!!!!!LA!!!!!!!!2,STK!!!!!!!!!!!START!ADDRESS!!!!!!!!!!!!!!!!S880752
*!!!!!!!!ANMW!!!!!!2,=X'0007FFFC'!!ADDRESS!PART!ONLY!PLEASE!!!!!S880752
*!!!!!!!!SUR!!!!!!!2,1!!!!!!!!!!!!!COMPUTE!!SPACE!FOR!SYMBOLS!!!S880752
*!!!!!!!!ES!!!!!!!!0!!!!!!!!!!!!!!!PREP!R0,1!FOR!THE!DIVDE!!!!!!S880752
*!!!!!!!!LW!!!!!!!!7,XRSECSIZ!!!!!!!FIND!SIZE!OF!A!SECTOR!!!!!!!S880752
*!!!!!!!!ADI!!!!!!!7,2W!!!!!!!!!!!!!PLUS!SIZE!OF!THE!POINTER!FORS880752
*!!!!!!!!DVR!!!!!!!7,0!!!!!!!!!!!!!!FIND!NUMBER!OF!RECORDS!WITH!S880752
*!!!!!!!!STW!!!!!!!1,XRRCT!!!!!!!!!THAT!WE!CAN!STORE!AT!ONE!TIM!S880752
*!!!!!!!!STW!!!!!!!1,XRSCT!!!!!!!!!MAX!NUMBER!OF!SORTED!STRINGS!S880752
*!!!!!!!!MPI!!!!!!!0,2W!!!!!!!!!!!!FIND!AMOUNT!OF!HEAD!SPACE!FORS880752
*!!!!!!!!STW!!!!!!!1,XRHDSPAC!!!!!!AMOUNT!OF!SPACE!NEEDED!FOR!!!S880752
*!!!!!!!!LW!!!!!!!!1,XRRCT!!!!!!!!!NUMBER!OF!RECORDS!PERMITTED!!S880752
*!!!!!!!!MPMW!!!!!!0,XRRCT!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!CAMW!!!!!!1,RECCOUN!!!!!!!MUST!HAVE!SPACE!FOR!A!RECORD!S880752
*!!!!!!!!BGT!!!!!!!OK!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!LW!!!!!!!!1,NOXTCW!!!!!!!!!CANNOT!DO!XREF.!!!!!!!!!!!!!S880752
*!!!!!!!!BU!!!!!!!!XRPZ1!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!S880752
*!OK!!!!!ZR!!!!!!!!2!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!LA!!!!!!!!R4,STK!!!!!!!!!!STARTING!ADDRESS!!!!!!!!!!!!!S880752
*!!!!!!!!ANMW!!!!!!4,=X'0007FFFC'!!ADDRESS!ONLY!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!TRR!!!!!!!4,5!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!ORMW!!!!!!5,XRRA!!!!!!!!!!MAKE!INTO!AN!INDEXED!INDIREC!S880752
*!!!!!!!!STW!!!!!!!5,XRHDADD!!!!!!!ADDRESS!OF!THE!POINTERS!!!!!!S880752
*!!!!!!!!ADMW!!!!!!4,XRHDSPAC!!!!!!ADJUST!FOR!THE!HEADER!SPACE!!S880752
*!!!!!!!!ORMW!!!!!!4,XRSECTCW!!!!!!!TRANSFER!COUNT!FOR!THE!DISC!S880752
*!!!!!!!!STW!!!!!!!4,XRFCBS!!!!!!!!COUNT!AND!ADDRESS!OF!SORT!BUFS880752
*!!!!!!!!LNW!!!!!!!4,XRSCT!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!LI!!!!!!!!1,1W!!!!!!!!!!!!WORK!ON!2ND!WORD!!!!!!!!!!!!!S880752
*!!!!!!!!ZMW!!!!!!!*XRHDADD!!!!!!!!CLEAR!SECTOR!COUNTS!AND!ITEM!S880752
*!!!!!!!!ADI!!!!!!!1,2W!!!!!!!!!!!!FOR!EACH!STRING!!!!!!!!!!!!!!S880752
*!!!!!!!!BIB!!!!!!!4,$-2W!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!ZMW!!!!!!!XRSPOINT!!!!!!!!START!AT!THE!FIRST!OF!THE!STRS880752
*!!!!!!!!ZMH!!!!!!!FCBXR+2W+1H!!!!!SET!REL.!BLOCK!#!TO!ZERO!FOR!S880752
*!XRPA1!!!EQU!!!!!!!$!!!!!!!!!!!!!!START!PRE-SORT!WORK!!!!!!!!!!S880752
*!!!!!!!!LW!!!!!!!!1,XRSPOINT!!!!!!POINTS!TO!THE!STRING!POINTER!S880752
*!!!!!!!!LH!!!!!!!!4,FCBXR+2W+1H!!!DISC!ADDRESS!FOR!START!OF!THIS880752
*!!!!!!!!STW!!!!!!!4,*XRHDADD!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!LW!!!!!!!!4,XRFCBS!!!!!!!!COUNT!AND!ADDRESS!OF!SORT!BUFS880752
*!!!!!!!!STW!!!!!!!4,FCBXR+1W!!!!!!TCW!TO!FCB!FOR!UT2!READING!!!S880752
*!!!!!!!!LNW!!!!!!!5,XRRCT!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!LW!!!!!!!!4,XRSECSIZ!!!!!!SECOTR!SIZE!FOR!THIS!RUN!!!!!S880752
*!XRPA3!!!LA!!!!!!!1,FCBXR!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!SVC!!!!!!!1,X'31'!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!TBM!!!!!!!6,FCBXR+3W!!!!!!EOF!DISCOVERED!AS17!!!!!!!!!!S880752
*!!!!!!!!BS!!!!!!!!XRPA4!!!!!!!!YES!!!!!!!!!!!!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!LW!!!!!!!!1,FCBXR+1W!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!LH!!!!!!!!1,0,1!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!CI!!!!!!!!1,X'0F00'!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!BCF!!!!!!!EQ,XRPA3.1!!!!!!BRANCH!IF!NOT!EOF!INDICATOR!!S880752
*!!!!!!!!LW!!!!!!!!1,FCBXR+1W!!!!!!RESTORE!BUFFER!ADDRESS.!!!!!!S880752
*!!!!!!!!ZMW!!!!!!!0,1!!!!!!!!!!!!!CLEAN!UP!RECORD.!!!!!!!!!!!!!S880-752
*!!!!!!!!BU!!!!!!!!XRPA4!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!S880752
*!XRPA3.1!!!EQU!!!!!!$!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!ABM!!!!!!!15,FCBXR+2W+1H!!UPDATE!REL.!BLOCK!#!.!!!!!!!!S880752
*!!!!!!!!LW!!!!!!!!1,XRSPOINT!!!!!!STRING!POINTER!!!!!!!!!!!!!!!S880752
*!!!!!!!!ADI!!!!!!!1,1W!!!!!!!!!!!!WANT!THE!SECOND!WORD!OF!THE!!S880752
*!!!!!!!!ABM!!!!!!!31,*XRHDADD!!!!!COUNT!THIS!SECTOR!IN!THE!STRIS880752
*!!!!!!!!ARMW!!!!!!4,FCBXR+1W!!!!!!ADVANCE!TCW!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!BIB!!!!!!!5,XRPA3!!!!!!!!!FILL!THE!SORT!AREA!!!!!!!!!!!S880752
*!XRPA4!!ADMW!!!!!!5,XRRCT!!!!!!!!!FIND!HOW!MANU!RECORDS!ARE!IN!S880752
*!!!!!!!!BZ!!!!!!!!XRPD1!!!!!!!!!!!NOTHING!IN!THIS!SUBFILE!!!!!!S880752
*!!!!!!!!MPMW!!!!!!4,XRSECSIZ!!!!!!SECTOR!SIZE!FOR!THIS!RUN!!!!!S880752
*!!!!!!!!DVI!!!!!!!4,3!!!!!!!!!!!!!GET!THE!R5!INPUT!FOR!THE!SORTS880752
*!!!!!!!!LW!!!!!!!!1,XRFCBS!!!!!!!!COUNT!AND!ADDRESS!OF!SORT!BUFS880752
*!**************************************************************S880752
*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!D.L.!SHELL'S!SORT!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!S880752
*!**************************************************************S880752
*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!R1!!!!!!!!BASE!ADDRESS!OF!THE!TABLE!TO!BE!SORTED!!!!!!!S880752
*!!!!!!!!R5!!!!!!!!NUMBER!OF!ITEMS!TO!BE!SORTED!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!S880752
*!**************************************************************S880752
*!!!!!!!!SPACE!!!!!2!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!STW!!!!!!!5,SORTM!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!STW!!!!!!!1,SORTB!!!!!!!!!SAVE!SORT!BUFFER!ADDR!!!!!!!!S880752
*!!!!!!!!STW!!!!!!!5,SORTN!!!!!!!!!SAVE!NUM!OF!SORT!ITEMS!!!!!!!S880752
*!SORT20!!!LW!!!!!!5,SORTM!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!SRL!!!!!!!5,1!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!ZBR!!!!!!!5,31!!!!!!!!!!!!KNOCK!OUT!ANY!EXTRANEOUS!BIT!S880752
*!!!!!!!!ZBR!!!!!!!5,30!!!!!!!!!!!!KNOCK!OUT!ANY!EXTRANEOUS!BIT!S880752
*!!!!!!!!TRN!!!!!!!5,6!!!!!!!!!!!!!-M!FOR!LATER!USE!AND!ALSO!SETS880752
*!!!!!!!!STW!!!!!!!5,SORTM!!!!!!!!!M=M/2!!!!!!!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!BZ!!!!!!!!SORT40!!!!!!!!!!IF(M=0)GOTO40!!!!!!!!!!!!!!!!S880752
*!!!!!!!!ADMW!!!!!!6,SORTN!!!!!!!!!N-M!!!!!!!!!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!STW!!!!!!!6,SORTK!!!!!!!!!K=N-M!!!!!!!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!LI!!!!!!!!5,1W!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!STW!!!!!!!5,SORTJ!!!!!!!!!J=1!!(WORD)!!!!!!!!!!!!!!!!!!S880752
*!SORT41!!!STW!!!!!5,SORTI!!!!!!!!!I=J!!!!!!!!!!!!!!!!!!!!!!!!!!S880752
*!SORT49!!!LW!!!!!!5,SORTM!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!ADMW!!!!!!5,SORTI!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!SUI!!!!!!!5,1W!!!!!!!!!!!!FORTRAN!INDICES!!!!!!!!!!!!!!S880752
*!!!!!!!!MPI!!!!!!!4,3W!!!!!!!!!!!!1!FOR!HOR.,!SIZE!FOR!VERTICALS880752
*!!!!!!!!SRL!!!!!!!5,2!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!TRR!!!!!!!5,2!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!ADMW!!!!!!2,SORTB!!!!!!!!!ADD!IN!THE!BASE!ADDRESS!!!!!!S880752
*!!!!!!!!LW!!!!!!!!5,SORTI!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!SUI!!!!!!!5,1W!!!!!!!!!!!!FORTRAN!INDICES!!!!!!!!!!!!!!S880752
*!!!!!!!!MPI!!!!!!!4,3W!!!!!!!!!!!!1!FOR!HOR.,!SIZE!FOR!VERTICALS880752
*!!!!!!!!SRL!!!!!!!5,2!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!TRR!!!!!!!5,1!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!ADMW!!!!!!1,SORTB!!!!!!!!!ADD!IN!THE!BASE!ADDRESS!!!!!!S880752
*!!!!!!!!LI!!!!!!!!3,-3W!!!!!!!!!!!NUMBER!OF!WORDS!TO!BE!COMPARES880752
*!COMPP!!!LW!!!!!!!7,0,1!!!!!!!!!!!A(I)!!!!!!!!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!EOMW!!!!!!7,0,2!!!!!!!!!!!A(L)!!!!!!!!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!BGE!!!!!!!COMPQ!!!!!!!!!!!SIGNS!ARE!THE!SAME!!!!!!!!!!!S880752
*!!!!!!!!TBM!!!!!!!0,0,1!!!!!!!!!!!CHECK!SIGN!OF!A(I)!!!!!!!!!!!S880752
*!!!!!!!!BS!!!!!!!!SORT50!!!!!!!!!!A(I).GT.A(L)!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!BU!!!!!!!!SORT60!!!!!!!!!!A(I).LT.A(L)!!!!!!!!!!!!!!!!!S880752
*!COMPQ!!!LW!!!!!!!7,0,1!!!!!!!!!!!A(I)!!!!!!!!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!CAMW!!!!!!7,0,2!!!!!!!!!!!A(L)!!!!!!!!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!BLT!!!!!!!SORT60!!!!!!!!!!A(I)!.LT.!A(L)!!!!!!!!!!!!!!!S880752
*!!!!!!!!BGT!!!!!!!SORT50!!!!!!!!!!A(I)!.GT.!A(L)!!!!!!!!!!!!!!!S880752
*!!!!!!!!ABR!!!!!!!1,29!!!!!!!!!!!!ADVANCE!ADDRESS!BY!DISTANCE!!S880752
*!!!!!!!!ABR!!!!!!!2,29!!!!!!!!!!!!WORDS!OF!THE!SAME!ITEM!!!!!!!S880752
*!!!!!!!!BIW!!!!!!!3,COMPP!!!!!!!!!COMPARE!EACH!WORD!!!!!!!!!!!!S880752
*!!!!!!!!BU!!!!!!!!SORT60!!!!!!!!!!A(I)!.EQ.!A(I+M)!!!!!!!!!!!!!S880752
*!SORT50!!!LW!!!!!!4,0,1!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!LW!!!!!!!!7,0,2!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!STW!!!!!!!4,0,2!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!STW!!!!!!!7,0,1!!!!!!!!!!!INTERCHANGE!OF!ONE!WORD!COMPLS880752
*!!!!!!!!ABR!!!!!!!1,29!!!!!!!!!!!!GET!ADDRESS!FOR!NEXT!WORD!OF!S880752
*!!!!!!!!ABR!!!!!!!2,29!!!!!!!!!!!!GET!ADDRESS!FOR!NEXT!WORD!OF!S880752
*!!!!!!!!BIW!!!!!!!3,SORT50!!!!!!!!MORE!WORDS!TO!EXCHANGE!!!!!!!S880752
*!!!!!!!!LW!!!!!!!!7,SORTI!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!SUMW!!!!!!7,SORTM!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!STW!!!!!!!7,SORTI!!!!!!!!!I=I-M!!!!!!!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!SUI!!!!!!!7,1W!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!BGE!!!!!!!SORT49!!!!!!!!!!IF(I-1)60,49,49!!!!!!!!!!!!!!S880752
*!SORT60!!!ABM!!!!!29,SORTJ!!!!!!!!J=J+1!!!!!!!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!LW!!!!!!!!5,SORTJ!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!CAMW!!!!!!5,SORTK!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!BLE!!!!!!!SORT41!!!!!!!!!!IF(J-K)41,41,20!!!!!!!!!!!!!!S880752
*!!!!!!!!BU!!!!!!!!SORT20!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!S880752
*!SORTB!!!RES!!!!!!1W!!!!!!!!!!!!!!BASE!ADDRESS!OF!TABLE!!!!!!!!S880752
*!SORTN!!!RES!!!!!!1W!!!!!!!!!!!!!!NUMBER!OF!ITEMS!TO!BE!SORTED!S880752
*!SORTI!!!RES!!!!!!1W!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!S880752
*!SORTM!!!RES!!!!!!1W!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!S880752
*!SORTJ!!!RES!!!!!!1W!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!S880752
*!SORTK!!!RES!!!!!!1W!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!S880752
*!SORT40!!!LW!!!!!!1,XRSPOINT!!!!!!POINTS!TO!DISC!ADDRESS!FOR!!!S880752
*!!!!!!!!LW!!!!!!!!4,*XRHDADD!!!!!!WHICH!IS!WHERE!WE!WRITE!SORTES880752
*!!!!!!!!STH!!!!!!!4,FCBXR+2W+1H!!!STRING!BACK!TO!!!!!!!!!!!!!!!S880752
*!!!!!!!!LW!!!!!!!!1,XRFCBS!!!!!!!!COUNT!AND!ADDRESS!OF!SORT!BUFS880752
*!!!!!!!!STW!!!!!!!1,FCBXR+1W!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!LW!!!!!!!!1,XRSPOINT!!!!!!STRING!POINTER!!!!!!!!!!!!!!!S880752
*!!!!!!!!ADI!!!!!!!1,H(1W+1H)!!!!!!!WANT!THE!SECTORS!IN!HALFWORDS880752
*!!!!!!!!LNH!!!!!!!5,*XRHDADD!!!!!!GET!NUMBER!OF!SECTORS!IN!THISS880752
*!!!!!!!!BGE!!!!!!!XRPD1!!!!!!!!!ERROR-NO!SECTORS!IN!A!STRING!!!S880752
*!!!!!!!!LW!!!!!!!!4,XRSECSIZ!!!!!!SEXTOR!SIZE!FOR!THIS!RUN!!!!!S880752
*!XRPC3!!!LA!!!!!!!1,FCBXR!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!SVC!!!!!!!1,X'32'!!!!!!!!!WRITE!BACK!ONTO!UT2!!!!!!!!!!S880752
*!!!!!!!!TBM!!!!!!!7,FCBXR+3W!!!!!!TEST!FOR!EOM!!!AS17!!!!!!!!!!S880752
*!!!!!!!!BS!!!!!!!!XRER!!!!!!!!!ERROR!IF!EOF!ON!WRITE.!!!!!!!!!!S880752
*!!!!!!!!ABM!!!!!!!15,FCBXR+2W+1H!!UPDATE!REL.!BLOCK!#!.!!!!!!!!S880752
*!!!!!!!!ARMW!!!!!!4,FCBXR+1W!!!!!!ADVANCE!TCW!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!ABM!!!!!!!31,XRMXRECS!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!BIB!!!!!!!5,XRPC3!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!ABM!!!!!!!28,XRSPOINT!!!!!!ADVANCE!THE!STRING!POINTER!!S880752
*!!!!!!!!LW!!!!!!!!1,XRSCT!!!!!!!!!!COMPARE!TO!MAX!NUMBER!OF!!!!S880752
*!!!!!!!!SLL!!!!!!!1,3!!!!!!!!!!!!!ADJUST!R1!FOR!COMPARE.!!!!!!!S880752
*!!!!!!!!CAMW!!!!!!1,XRSPOINT!!!!!!!WHERE!THE!STRING!POINTER!IS!S880752
*!!!!!!!!BLT!!!!!!!XRPD1!!!!!!!!!HAVE!EXCEEDED!SORT!CAPACITY!!!!S880752
*!!!!!!!!LW!!!!!!!!1,XRMXRECS!!!!!!!HAVE!ALL!SECTORS!BEEN!PROCESS880752
*!!!!!!!!BLT!!!!!!!XRPA1!!!!!!!!MORE!STRINGS!TO!DO!!!!!!!!!!!!!!S880752
*!XRPD1!!!EQU!!!!!!$!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!GET!TO!FRONT!OF!EACH!SORTED!STRING!PREPARATORY!TO!MERGES880752
*!!!!!!!!ZMW!!!!!!!XRPICKP!!!!!!!!!!START!AT!THE!FIRST!STRING!!!S880752
*!XRPF2!!!EQU!!!!!!$!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!LW!!!!!!!!1,XRPICKP!!!!!!!!CHECK!HWO!FAR!WE!ARE!INTO!!!S880752
*!!!!!!!!BL!!!!!!!!RDDESSCT!!!!!!!!!READ!THE!DESIGNATED!SECTOR!!S880752
*!!!!!!!!ABM!!!!!!!28,XRPICKP!!!!!!!ADVANCE!TO!THE!NEXT!STRING!!S880752
*!!!!!!!!LW!!!!!!!!1,XRPICKP!!!!!!!CHECK!HOWO!FAR!WE!ARE!INTO!!!S880752
*!!!!!!!!CAMW!!!!!!1,XRSPOINT!!!!!!!COMPARE!TO!THE!LIMIT!!!!!!!!S880752
*!!!!!!!!BLT!!!!!!!XRPF2!!!!!!!!!MORE!STRINGS!TO!BE!STARTED!!!!!S880752
*!!!!!!!!LI!!!!!!!!2,-30W!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!LW!!!!!!!!6,=C'!!!!'!!!!!!ASCII!SPACES!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!STW!!!!!!!6,PRMT+30W,2!!!!SPACES!TO!BUFFER!!!!!!!!!!!!!S880752
*!!!!!!!!BIW!!!!!!!2,$-1W!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!ZMW!!!!!!!XRBUFP!!!!!!!!!!PRINT!BUFFER!POINTER!!!!!!!!!S880752
*!!!!!!!!LI!!!!!!!!7,-1!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!STW!!!!!!!7,XRCNAME!!!!!!!LOAD!THE!HIGHEST!VALUE!TO!!!!S880752
*!!!!!!!!STW!!!!!!!7,XRCNAME+1W!!!!PRESET!MATCH!PLACE!!!!!!!!!!!S880752
*!!!!!!!!START!MERGING!THE!SORTED!STRINGS!FOR!PRINTED!OUTPUT!!!!S880752
*!XRPS2!!!EQU!!!!!!$!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!ZMW!!!!!!!XRPICKP!!!!!!!!!PICKUP!POINTER!FOR!SINGLE!!!!S880752
*!!!!!!!!LI!!!!!!!!7,-1!!!!!!!!!!!!!HIGH!VALUE!DATA!FOR!COMPARISS880752
*!!!!!!!!STW!!!!!!!7,XRBUF+2W!!!!!!!ITEM!KEY!!!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!STW!!!!!!!7,XRBUF+1W!!!!!!!CHARS!5-8!OF!KEY!!!!!!!!!!!!S880752
*!!!!!!!!STW!!!!!!!7,XRBUF+0W!!!!!!!CHARS!1-4!OF!THE!KEY!!!!!!!!S880752
*!!!!!!!!STW!!!!!!!7,XRBUF+3W!!!!!!!POS!!!!!!!!!!!!!!!!!!!!!!!!!S880752
*!XRGETI3!!!EQU!!!!!$!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!LW!!!!!!!!1,XRPICKP!!!!!!!!CURRENT!STRING!POINTER!!!!!!S880752
*!!!!!!!!ADI!!!!!!!1,1W!!!!!!!!!!!!!WE!WANT!TO!USE!THE!SECOND!!!S880752
*!!!!!!!!LH!!!!!!!!4,*XRHDADD!!!!!!!CHECK!FOR!BUFFER!EXHAUSTED!!S880752
*!!!!!!!!CAMW!!!!!!4,XRSECSIZ!!!!!!!CHECK!FOR!DONE!WITH!THE!BUFFS880752
*!!!!!!!!BLT!!!!!!!XRGETI4!!!!!!!SECTOR!HAS!ITEMS!LEFT!IN!IT!!!!S880752
*!!!!!!!!ADI!!!!!!!1,H(1H)!!!!!!!!!!WANT!THE!SECTORS!REMAINING!!S880752
*!!!!!!!!LH!!!!!!!!5,*XRHDADD!!!!!!HOW!MANY!SECTORS!LEFT!IN!THISS880752
*!!!!!!!!BEQ!!!!!!!XRGETI8!!!!!!!NONE--FORGET!THIS!STRING!!!!!!!S880752
*!!!!!!!!LW!!!!!!!!1,XRPICKP!!!!!!!!TELL!WHICH!STRING!TO!READ!!!S880752
*!!!!!!!!BL!!!!!!!!RDDESSCT!!!!!!!!!SOME!LEFT--READ!ONE!OF!THEM!S880752
*!XRGETI4!!!EQU!!!!!$!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!LW!!!!!!!!1,XRPICKP!!!!!!!!THIS!WILL!TELL!US!WHERE!SECTS880752
*!!!!!!!!MPMW!!!!!!0,XRSECSIZ!!!!!!!HOW!MUCH!SPACE!FOR!EACH!SECTS880752
*!!!!!!!!SRL!!!!!!!1,3!!!!!!!!!!!!!!CONVERT!TO!THE!PLACE!NUMBER!S880752
*!!!!!!!!TRR!!!!!!!1,2!!!!!!!!!!!!!!GIVES!US!BASE!ADDRESS!OF!THIS880752
*!!!!!!!!ADMW!!!!!!2,XRFCBS!!!!!!!!!PLUS!BASE!ADDRESS!OF!MAIN!!!S880752
*!!!!!!!!LW!!!!!!!!1,XRPICKP!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!ADI!!!!!!!1,1W!!!!!!!!!!!!!WANT!SECOND!WORD!!!!!!!!!!!!S880752
*!!!!!!!!ADMH!!!!!!2,*XRHDADD!!!!!!!WHICH!CONTAINS!POINTER!TO!!!S880752
*!!!!!!!!LW!!!!!!!!7,+2W,2!!!!!!!!!!GET!THE!VALUE!KEY!WORD!OF!!!S880752
*!!!!!!!!BCF!!!!!!!EQ,XRGETI6!!!!!!!NOT!A!NULL!ITEM-PROCESS!IT!!S880752
*!!!!!!!!ABM!!!!!!!12,*XRHDADD!!!!!WE!WANT!TO!MODIFY!2ND!WD!OF!!S880752
*!!!!!!!!ABM!!!!!!!13,*XRHDADD!!!!!POINTER!TO!ACCOUNT!FOR!ITEM!!S880752
*!!!!!!!!BU!!!!!!!!XRGETI3!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!S880752
*!XRGETI6!!!EQU!!!!!$!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!LA!!!!!!!!1,XRBUF!!!!!!!!!!THE!LOWEST!UNPROCESSED!ITEM!S880752
*!!!!!!!!LI!!!!!!!!3,-3W!!!!!!!!!!!!NUMBER!OF!WORDS!TO!CMPARE!!!S880752
*!COMPT!!!LW!!!!!!!7,0,1!!!!!!!!!!!A(I)!!!!!!!!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!EOMW!!!!!!7,0,2!!!!!!!!!!!A(L)!!!!!!!!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!BGE!!!!!!!COMPR!!!!!!!!!!!SIGNS!ARE!THE!SAME!!!!!!!!!!!S880752
*!!!!!!!!TBM!!!!!!!0,0,1!!!!!!!!!!!CHECK!SIGN!OF!A(I)!!!!!!!!!!!S880752
*!!!!!!!!BS!!!!!!!!XRGETI7!!!!!!!!!A(I).GT.A(L)!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!BU!!!!!!!!XRGETI8!!!!!!!!!A(I).LT.A(L)!!!!!!!!!!!!!!!!!S880752
*!COMPR!!!LW!!!!!!!7,0,1!!!!!!!!!!!A(I)!!!!!!!!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!CAMW!!!!!!7,0,2!!!!!!!!!!!A(L)!!!!!!!!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!BLT!!!!!!!XRGETI8!!!!!!!!!A(I)!.LT.!A(L)!!!!!!!!!!!!!!!S880752
*!!!!!!!!BGT!!!!!!!XRGETI7!!!!!!!!!A(I)!.GT.!A(L)!!!!!!!!!!!!!!!S880752
*!!!!!!!!ABR!!!!!!!1,29!!!!!!!!!!!!!ADVANCE!THE!A(I)!ADDRESS!!!!S880752
*!!!!!!!!ABR!!!!!!!2,29!!!!!!!!!!!!!ADVANCE!THE!A(L)!ADDRESS!!!!S880752
*!!!!!!!!BIW!!!!!!!3,COMPT!!!!!!!!!COMPARE!EACH!WORD!!!!!!!!!!!!S880752
*!!!!!!!!BU!!!!!!!!XRGETI8!!!!!!!!!A(I)!.EQ.!A(L)!!!!!!!!!!!!!!!S880752
*!XRGETI7!!!EQU!!!!!!$!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!LW!!!!!!!!7,0,2!!!!!!!!!!!!MOVE!THE!NEW!LOWEST!VALUE!!!S880752
*!!!!!!!!STW!!!!!!!7,0,1!!!!!!!!!!!!INTO!THE!HOLDING!AREA!!!!!!!S880752
*!!!!!!!!ABR!!!!!!!1,29!!!!!!!!!!!!!ADVANCE!THE!A(I)!ADDRESS!!!!S880752
*!!!!!!!!ABR!!!!!!!2,29!!!!!!!!!!!!!ADVANCE!THE!A(L)!ADDRESS!!!!S880752
*!!!!!!!!BIW!!!!!!!3,XRGETI7!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!LW!!!!!!!!7,XRPICKP!!!!!!!!REMEMBER!WHICH!STRING!WE!GOTS880752
*!!!!!!!!STW!!!!!!!7,XRBUF+3W!!!!!!!WILL!HOLD!THE!STRING!IDENTIFS880752
*!XRGETI8!!!EQU!!!!!!$!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!ABM!!!!!!!28,XRPICKP!!!!!!GO!TO!THE!NEXT!STRING!!!!!!!!S880752
*!!!!!!!!LW!!!!!!!!1,XRPICKP!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!CAMW!!!!!!1,XRSPOINT!!!!!!!HAVE!WE!CHECKED!ALL!CURRENT!S880752
*!!!!!!!!BLT!!!!!!!XRGETI3!!!!!!!HAVE!NOT!CHECKED!ALL!OF!THE!!!!S880752
*!!!!!!!!LW!!!!!!!!1,XRBUF+3W!!!!!!!HAVE!WE!FOUND!A!VALID!ITEM!!S880752
*!!!!!!!!BLT!!!!!!!XRPZ!!!!!!!!!NO--ALL!DONE!WITH!ALL!STRINGS!!!S880752
*!!!!!!!!ADI!!!!!!!1,1W!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!ABM!!!!!!!12,*XRHDADD!!!!!WE!WANT!TO!MODIFY!2ND!WD!OF!!S880752
*!!!!!!!!ABM!!!!!!!13,*XRHDADD!!!!!POINTER!TO!ACCOUNT!FOR!ITEM!!S880752
*!!!!!!!!LW!!!!!!!!6,XRCDATA!!!!!!!GET!SYMBOL!ITEM!KEY!(SHIFTED)S880752
*!!!!!!!!SRC!!!!!!!6,1!!!!!!!!!!!!!REALIGN!SYMBOL!ITEM!KEY!!!!!!S880752
*!!!!!!!!STW!!!!!!!6,XRCDATA!!!!!!!RESTORE!SYMBOL!ITEM!KEY!!!!!!S880752
*!!!!!!!!LB!!!!!!!!2,PRMT+3W!!!!!!!FIRST!CHAR!OF!NAME.!!!!!!!!!!S880752
*!!!!!!!!CAMB!!!!!!2,=X'FF'!!!!!!!!IS!IT!AN!INTERNAL!SYMBOL?!!!!S880752
*!!!!!!!!BCF!!!!!!!EQ,$+3W!!!!!!!!!NO.!!!!!!!!!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!LI!!!!!!!!2,X'21'!!!!!!!!!INT!SYM!LEAD!CHAR.!!!!!!!!!!!S880752
*!!!!!!!!STB!!!!!!!2,PRMT+3W!!!!!!!REPLACE!X'FF'!IN!BUFFER!WITH!S880752
*!!!!!!!!LI!!!!!!!!7,X'0F'!!!!!!!!!PRINT!LINE!UNCONDITIONALLY.!!S880752
*!!!!!!!!BL!!!!!!!!PPP!!!!!!!!!!!!PRINT!FINAL!LINE!!!!!!!!!!!!!!S880752
*!!!!!!!!BU!!!!!!!!*SDX0!!!!!!!!!!!RETURN!!!!!!!!!!!!!!!!!!!!!!!S880752
*!RDDESSCT!!!EQU!!!!!!!$!!!!!!!!!!!READ!THE!NEXT!SECTOR!FROM!DESS880752
*!!!!!!!!TRR!!!!!!!0,7!!!!!!!!!!!!!!SAVE!THE!RETURN!ADDRESS!!!!!S880752
*!!!!!!!!TRR!!!!!!!1,2!!!!!!!!!!!!!SAVE!POINTER!TO!DESIGNATED!!!S880752
*!!!!!!!!LW!!!!!!!!4,*XRHDADD!!!!!!GET!DISC!ADDRESS!FOR!NEXT!!!!S880752
*!!!!!!!!STH!!!!!!!4,FCBXR+2W+1H!!!SO!WE!CAN!READ!FROM!THERE!!!!S880752
*!!!!!!!!SRL!!!!!!!1,3!!!!!!!!!!!!!DOUBLEWORD!POINTER!TO!INTEGERS880752
*!!!!!!!!MPMW!!!!!!0,XRSECSIZ!!!!!!TIMES!THE!CURRENT!SECTOR!SIZES880752
*!!!!!!!!ADMW!!!!!!1,XRFCBS!!!!!!!!TO!GET!THE!SECTOR!AREA!FOR!!!S880752
*!!!!!!!!ORMW!!!!!!1,XRSECTCW!!!!!!!TRANSFER!COUNT!FOR!THE!DISC!S880752
*!!!!!!!!STW!!!!!!!1,FCBXR+1W!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!LA!!!!!!!!1,FCBXR!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!SVC!!!!!!!1,X'31'!!!!!!!!!READ!THAT!SECTOR!!!!!!!!!!!!!S880752
*!!!!!!!!ABM!!!!!!!15,FCBXR+2W+1H!!UPDATE!REL!BLOCK!#!.!!!!!!!!!S880752
*!!!!!!!!TRR!!!!!!!2,1!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!LH!!!!!!!!4,FCBXR+2W+1H!!!DISC!ADDRESS!OF!THE!NEXT!SECTS880752
*!!!!!!!!STW!!!!!!!4,*XRHDADD!!!!!!WHICH!WE!MAY!GO!TO!!!!!!!!!!!S880752
*!!!!!!!!ADI!!!!!!!1,1W!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!LW!!!!!!!!4,*XRHDADD!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!SUI!!!!!!!4,1!!!!!!!!!!!!!SHOW!NO!MORE!SECTORS!IN!THIS!S880752
*!!!!!!!!ANMW!!!!!!4,=X'0000FFFF'!!!USE!ONLY!THE!SECTOR !OUNT!!!S880752
*!!!!!!!!STW!!!!!!!4,*XRHDADD!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!S880752
*!!!!!!!!TRSW!!!!!!7!!!!!!!!!!!!!!!!RETURN!!!!!!!!!!!!!!!!!!!!!!S880752
*!**************************************************************S880752*
*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!S880752*
*!!!!!!!!!!!!!!!!!!D!A!T!A!!!!A!R!E!A!!!!!!!!!!!!!!!!!!!!!!!!!!!S880752*
*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!S880752*
*!**************************************************************S880752*
*!!!!!!!!SPACE!!!!!3!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!S880752
*!SDX0!!!!RES!!!!!!1W!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!S880752
*!XRHDADD!!!RES!!!!1W!!!!!!!!!!!!!!INDIRECT!POINTER!TO!THE!POINTS880752
*!XRSCT!!!RES!!!!!!1W!!!!!!!!!!!!!!MAX!NUMBER!OF!SORTED!STRINGS!S880752
*!XRSPOINT!!!RES!!!1W!!!!!!!!!!!!!!POINTS!TO!THE!STRING!POINTER!S880752
*!XRHDSPAC!!!RES!!!1W!!!!!!!!!!!!!!AMOUNT!OF!SPACE!NEEDED!FOR!!!S880752
*!XRRCT!!!RES!!!!!!1W!!!!!!!!!!!!!!HOLDS!NUMBER!OF!RECORDS!ALLWES880752
*!XRFCBS!!!RES!!!!!1W!!!!!!!!!!!!!!COUNT!AND!ADDRESS!OF!SORT!BUFS880752
*!XRMXRECS!!!RES!!!1W!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!S880752
*!XRSECTCW!!!RES!!!1W!!!!!!!!!!!!!!!TRANSFER!COUNT!FOR!THE!DISC!S880752
*!XRPICKP!!!RES!!!!1W!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!S880752
*!XRRA!!!ACW!!!!!!!$$,1!!!!!!!!!!!!MADE!INTO!AN!INDEXED!INDIRECTS880752
*!FCBXRI!!!GEN!!!!!12/768,20/B(XRBUF)!!!INITIAL!SET!UP!FOR!TCW!!S880752
*!NOXTCW!!!GEN!!!!!12/34,20/B(NOXMSG)!!!!!!!!!!!!!!!!!!!!!!!!!!!S880752
*!NOXMSG!!!DATAB!!!C'1**!XREF!COULD!NOT!BE!PERFORMED!**'!!!!!!!!S880752
         TITLE                     MACRO LIBRARY SEARCH
*    MPX-32 MACRO ASSEMBLER MACRO LIBRARY SEARCH  LIBSRCH
         BOUND     8W
LIBREG   RES       8W              SAVES CALLERS REGISTERS
LIBCNT   EQU       LIBREG+6W       THIS GOES OUT IN R6
         IFT       UNIXF,SKIP                                   *JCB*
JCBREG   RES       8W              TEMP REG SAVE AREA           *JCB*
SKIP     ANOP                                                   *JCB*
RLINK    EQU       0W              POINTER TO NEXT GREATER VALUE THAN CU
LLINK    EQU       1W              POINTER TO NEXT LOWER VAL THAN CURR N
MACRO   EQU       2W              POSITION OF MACRO IN TABLE ENTRY
***********************************************************************
*
*       RLINK = MACRO ENTRY ADDRESS OF NEXT ALPHABETICALLY GREATER
*               IN VALUE THAN CURRENT NODE
*       LLINK = MACRO ENTRY ADDRESS OF ALPHABETICALLY LESSER IN
*               VALUE THAN CURRENT NODE.
*
*               SO TO FIND THE NEXT MACRO LOWER IN THE
*               ALPHABET (CLOSER TO Z) TAKE RLINK ADDRESS;
*               (CLOSER TO A) TAKE LLINK ADDRESS.
*
*
*                        *********************
*       LOW      ROW     *     RLINK         *
*                        *********************
*                ROW+1   *     LLINK         *
*                        *********************
*                ROW+2   *      ABCD         *
*                        *********************
*                ROW+3   *      EFGH         *
*                        *********************
*                ROW+4   * #PARS *   SIZE    *
*                        *********************
*                ROW+5   *     RESERVED      *
*                        *********************
*
*
*       ABCD IS THE FIRST FOUR ASCII CHARACTERS OF THE
*               MACRO, BLANK FILLED, LEFT JUSTIFIED
*       EFGH IS THE SECOND FOUR ASCII CHARACTERS OF THE
*               MACRO, BLANK FILLED, LEFT JUSTIFIED
*       #PARS IS THE NUMBER OF PARAMETERS REQUIRED FOR MACRO
*       SIZE IS THE NUMBER OF BYTES CONTAINED IN THE MACRO
*
FCBLIB   DATAW     G'MAC'
         GEN       12/192,20/B(LIBBUF)
         DATAW     0,0,0,0
         ACW       ERMAC
         DATAW     0
FCBLIB2  DATAW     G'MA2'
         GEN       12/192,20/B(LIBBUF)
         DATAW     0,0,0,0
         ACW       ERMAC2
         DATAW     0
PGATE    DATAB     X'0'            PASS GATE-CLOSE AFTER FIRST PASS.
MACSWIT  DATAB     0               BIT 7 SET - SEARCH MA2 FILE
*                                  BIT 7 RESET - SEARCH MAC FILE
LOW      DATAW     0               START EXT ADDR
HIGH     DATAW     0               LAST WORD AVAIL IN BLOCK
MACP     DATAW     0               MAC STRING START
MA2P     DATAW     0               MA2 STRING START
CURRP    DATAW     0               CURRENT STACK POINTER
HEAD     DATAW     0               ADDR OF CURR DEFINED HEADER
         BOUND     1D
MCNP     DATAW     0,0,X'01200000',0,0,0   READ ONLY, OPEN UNBLOCKED
LIBBUF   RES       48W             SPACE FOR ONE DISC SECOTR
         IFF       UNIXF,SKIP                                   *JCB*
LIBSCH1  STF       0,LIBREG        SAVE ALL REGS
         SBM       7,MACSWIT       INDICATE SEARCH MA2 FILE
         SBM       0,PGATE         IS PASS GATE SET ?
         BS        LIBSC0          YES - SKIP INITIALIZATION
         BU        LIBSCH2         CONTINUE AT COMMON NODE
SKIP     ANOP                                                   *JCB*
LIBSCH   CEQU      $                                            ESCT-32
         STF       0,LIBREG        SAVE THE CALLERS REGISTERS
         ZBM       7,MACSWIT       INDICATE SEARCH MAC FILE
         SBM       1,PGATE         CLOSE FIRST PASS GATE.
         BS        LIBSC0          BRANCH IF GATE CLOSED.
LIBSCH2  CEQU      $                                            ESCT-32
         IFF       UNIXF,SKIP                                   *JCB*
         LA        R1,INQ.INFO     ADDRESS FOR INQUIRY INFO    11003
         LW        R4,FCBLIB       GET LFC                     11003
         TBM       7,MACSWIT       SEARCHING MA2 FILE ?
         BNS       $+2W            NO
         LW        R4,FCBLIB2      GET MA2 LFC                 11003
         ANMW      R4,=X'00FFFFFF' MASK ALL BUT LFC            11003
         ZR        R5              CLEAR R5                      11003
         ZR        R7              NO CNP                        11003
         SVC       2,X'48'         M.INQUIRY                   11003
         LW        R2,INQ.INFO+3W  GET INDEX TO DTT            11003
         LB        R7,0,R2         GET DEV TYPE FROM DTT       11003
         CI        7,6             IS IT DISC OR TAPE ?
         BGT       BADDVMAC        NO - ERROR !!
SKIP     ANOP                                                   *JCB*
         SBM       2,PGATE         FIRST TIME THRU EVER?
         BS        LIB1            BR IF NOT
         SVC       1,X'69'         M.GD - GET EXT DATA SPACE
         TRR       R3,R3           SET CC'S
         BZ        MNOK            BR IF NO SPACE
         STW       R3,LOW          SAVE START ADDR
         STW       R4,HIGH         SAVE LAST ADDR
         STW       R3,CURRP        INIT STACK ADDR
         ZMW       MACP            INIT MAC POINTER
         ZMW       MA2P            INIT MA2 POINTER
LIB1     LA        1,FCBLIB
         IFF       UNIXF,SKIP                                   *JCB*
         TBM       7,MACSWIT       SEARCHING MA2 FILE ?
         BNS       $+2W            NO
         LA        1,FCBLIB2       FCB ADDR OF MA2 FCB
         LA        R7,MCNP         CNP ADDR FOR OPEN UNBLK, READ ONLY
         SVC       2,X'42'         OPEN 'MAC' FILE  UNBLOCKED
SKIP     ANOP                                                   *JCB*
         IFT       UNIXF,SKIP                                   *JCB*
*FIX     CCALL     _open,MCFILPTR,=0  OPEN MAC READ ONLY        *JCB*
         CCALL     _open,MCFILPTR,=X'800'  OPEN MAC READ/UNBLK  *JCB*
         TRR       R0,R0           ERROR                        *JCB*
         BLT       BADDVMAC        ABORT IF YES                 *JCB*
         STW       R0,MC.FD        SAVE FILE DESCRIPTOR         *JCB*
SKIP     ANOP                                                   *JCB*
         LF        0,LIBREG        RESTOR REGS.
         IFT       ULC,SKIP                                     *JCB*
LIBSC0   LI        R1,-8           SET UP FOR 8 BYTES           *JCB*
LIB.0    CI        R1,-4           ARE WE HALF WAY YET?         *JCB*
         BNE       LIB.1           NO, KEEP CONVERTING          *JCB*
         XCR       R6,R7           SWITCH REGS                  *JCB*
LIB.1    TBR       R6,1            IS IT A LETTER               *JCB*
         BNS       LIB.2           NO, LEAVE IT ALONE           *JCB*
         ZBR       R6,2            FORCE TO UPPER CASE          *JCB*
LIB.2    SRC       R6,8            POSITION NEXT BYTE           *JCB*
         BIB       R1,LIB.0        GO TEST FOR END OF WORD      *JCB*
         XCR       R6,R7           PUT BACK REGS                *JCB*
         LW        R1,MACP         GET MAC POINTER              *JCB*
SKIP     ANOP                                                   *JCB*
         IFF       ULC,SKIP                                     *JCB*
LIBSC0   LW        R1,MACP         GET MAC POINTER
         TBM       7,MACSWIT       SEARCHING MA2
         BNS       $+2W            BR IF NO
         LW        R1,MA2P         GET MA2 POINTER
SKIP     ANOP                                                   *JCB*
         TRR       R1,R1           SET CC'S
         BZ        LB2             ANY ENTRIES IN STACK YET, BR IF NOT
*                 SUBROUTINE TO LOOKUP MACRO  FROM TABLE
*
*        IN        R6, R7 = MACRO NAME LEFT JUSTIFIED BLANK FILLED
*                  R1 = STACK POINTER TO MAC OR MA2 HEADER
*
*        OUT       R1 = ADDRESS OF MACRO  TABLE ENTRY IF FOUND
*!!!!!!!!SEA!!!!!!!!!!!!!!!!!!!!!!!SET!EXT!ADDR!MODE!!!!!!!!!!!!S880752
SM15     CAMD      R6,MACRO,R1    COMPARE AGAINST LAST NODE ENTRY
         BLT       SM50            NEW .LT. LAST, FOLLOW DESENDING LINK
         BEQ       SM60            THEY ARE .EQ. WE FOUND THE MACRO
         LW        R1,RLINK,R1     NEW .GT. LAST, FOLLOW ASSENDING LINK
         BNZ       SM15            GO TRY NEXT LARGER BRANCH
         BU        LB2             NOT FOUND, RETURN ERROR
SM50     LW        R1,LLINK,R1     GET DECENDING PATH
         BNZ       SM15            IF NOT END, GO UPDATE
         BU        LB2             NOT FOUND, ERROR
SM60     LW        R7,4W,R1        MACRO FOUND, GET NUM OF BYTES
         STW       R7,LIBCNT       SAVE NUMBER OF NEW MACRO CHARS COUNT
*!!!!!!!!CEA!!!!!!!!!!!!!!!!!!!!!!!CLEAR!EXT!MODE!!!!!!!!!!!!!!!S880752
*                  R1 HAS NEW ENTRY HEADER ADDR, R6=#PARS/#CHARS
         STW       R1,LIBREG+1W    SAVE REG 1 FOR RETURN
LIBNO    LF        0,LIBREG        RESTORE THE REGISTERS
         TRSW      0               RETURN TO THE CALLER
MNOK     LW        1,OVFLWTCW
MNOK1    LI        7,X'0F'         PRINT LINE UNCONDITIONALLY.
         BU        ABORTM           RETURN.
ABORTMAC LW        R1,HEAD         BAD MACRO LIB ENTRY
         STW       R1,CURRP        RESTORE POINTER
         LW        R1,BADMACM      ADDRESS OF ABORT MESSG
         BU        MNOK1           GO PRINT MSG
         SPACE     3
*!LB2!!!!CEA!!!!!!!!!!!!!!!!!!!!!!!CLEAR!EXT!ADDR!MODE!!!!!!!!!!S880752
LB2      CEQU      $                                            ESCT-32
         IFF       UNIXF,SKIP                                   *JCB*
         LA        1,FCBLIB
         TBM       7,MACSWIT       SEARCHING MA2 FILE ?
         BNS       $+2W            NO
         LA        1,FCBLIB2       FCB ADDR OF MA2 FCB
         SVC       1,X'37'         REWIND 'MAC'.
SKIP     ANOP                                                   *JCB*
         IFT       UNIXF,SKIP                                   *JCB*
         STF       R0,JCBREG       SAVE REGS                    *JCB*
         CCALL     _fcbadr,MC.FD   GET MAC FCB ADDR             *JCB*
         TRR       R0,R1           FCB ADDR TO R1               *JCB*
         SVC       1,X'37'         REWIND                       *JCB*
         LF        R0,JCBREG       RESTORE REGS                 *JCB*
         LA        1,FCBLIB                                     *JCB*
         ZBM       6,FCBLIB+3W     CLEAR EOF ON LIB             *JCB*
SKIP     ANOP                                                   *JCB*
         BL        PRIM            PRIM INPUT BUFFER.
         ZBR       1,0             INDICATE NOT IN A PROTO
LIBSC2   BL        READREC         GET INPUT RECORD.
         IFF       UNIXF,SKIP                                   *JCB*
         TBM       7,MACSWIT       SEARCHING MA2 FILE ?
         BNS       LIBSC2.0        NO
         TBM       6,FCBLIB2+3W    CHECK FOR EOF ON MA2 FILE
         BU        LIBSC2.1        CONTINUE AT COMMON NODE
SKIP     ANOP                                                   *JCB*
LIBSC2.0 TBM       6,FCBLIB+3W     CHECK FOR EOF ON LIB
LIBSC2.1 BS        LIBNO           EOF FOUND-DONE WITH LIB THEN
         LB        5,LIBBUF        CHECK THE FIRST BYTE OF THE RECORD
         CI        5,X'EF'         ONE OF A LIBRARY RECORD
         BEQ       LIBSC3       EITHER FIRST OR MIDDLE RECORD
         CI        5,X'CF'         LAST OF A LIBRARY PROTO
         BNE       LIBSC2        NOT LIB. REC. IGNORE
         ZBR       1,0             FIRST OR LAST CARD
         BS        LIBSC2          IT WAS THE LAST RECORD OF A PROTO
         BU        LIBSC4          SAME RECORD IS FIRST AND LAST OF PROT
LIBSC3   SBR       1,0             INDICATE THAT WE HAVE STARTED PROTO
         BS        LIBSC2          THIS IS A MIDDLE RECORD
*        FALL THROUGH HERE ONLY ON FIRST RECORD OF A GIVEN PROTOTYPE
LIBSC4   CAMD      6,LIBBUF+2W     CHECK AGAINST NAME
         BNE       LIBSC2       NOT THE CORRECT PROTOTYPE
*        FALL THRU HERE WHEN WE HAVE FOUND THE FIRST RECORD OF THE
*        MACRO PROTOTYPE IN THE LIBRARY.
         LW        R1,CURRP        GET STACK POINTER
         ADI       R1,7B           ROUND TO NEXT DOUBLE WORD BOUND
         ANMW      R1,=X'00FFFFF8' FORCE DOUBLE WORD BOUND
         STW       R1,CURRP        DOUBLE WORD BOUND STACK POINTER
         STW       R1,HEAD         INITIALIZE THIS HEAD CELL
         ADI       R1,6W           HEADER SIZE
         CAMW      R1,HIGH         SEE IF OUT OF ROOM IN MAP
         BLT       LIBX2           BR IF ROOM AVAILABLE
         SVC       1,X'69'         GET ANOTHER MAP BLOCK
         TRR       R3,R3           SET CC'S
         BZ        MNOK            BR IF MEM NOT AVAILABLE
         STW       R4,HIGH         UPDATE NEW HIGH ADDR
LIBX2    STW       R1,CURRP        UPDATE CURR POINTER
         ZMW       LIBCNT          ZERO NUMBER OF NEW MACRO CHARS COUNT
         ZBM       0,PARFLAG       CLEAR FLAG SHOWING NEXT CHAR PAR #
         STD       R6,MACNAME      SAVE MACRO NAME
         LB        7,LIBBUF+1B     NUMBER OF BYTES IN A RECORD
         BZ        ABORTMAC        ABORT IF MACRO LIB BAD
         SUI       R7,10B          LESS THE ID PORTION + M.
         LA        R1,LIBBUF+16B
LIBMV2   LW        R2,CURRP        GET CURR STACK POINTER
         TRR       2,3             GET POINTER TO END OF MACRO TABLE
         ARMW      R7,LIBCNT        COUNT BYTES.
         ARMW      R7,CURRP        UPDATE STACK POINTER
         ADR       R7,R3           PLUS THE NUMBR  OF BYTES TO BE MOVED
         CAMW      R3,HIGH         WILL WE GO OVER END WITH THIS REC?
         BLE       LIBX1           BR IF STILL ROOM
         SVC       1,X'69'         GET ANOTHER MAP BLOCK
         TRR       R3,R3           TEST FOR OK
         BZ        MNOK            BR IF NO MORE MEM AVAILABLE
         STW       R4,HIGH         SAVE NEW ENDING ADDR
LIBX1    TRN       7,7
*        MOVE THE NEW PROTOTYPE DATA BYTES INTO THE TABLE
*!!!!!!!!SEA!!!!!!!!!!!!!!!!!!!!!!!SET!EXT!ADDR!!!!!!!!!!!!!!!!!S880752
LIBMV4   LB        R4,0B,R1        GET ONE BYTE OF NEW PROTOTYPE
         ZBM       0,PARFLAG       IS NEXT CHAR A PAR #
         BS        LIBX4           BR IF IT IS
         CI        R4,X'25'        IS THIS CHAR A %
         BNE       $+2W            BR IF NOT
         SBM       0,PARFLAG       SET PAR # COMING FLAG
LIBX3    STB       R4,0B,R2        PLACE NEW PROTOTYPE BYTE INTO TABLE
         ABR       R1,31           BUMP ADDR
         ABR       R2,31           BUMP ADDR
         BIB       7,LIBMV4        DO ALL OF THE RECORD
*!!!!!!!!CEA!!!!!!!!!!!!!!!!!!!!!!!CLEAR!EXT!ADDR!!!!!!!!!!!!!!!S880752
         LB        6,LIBBUF        THE ID BYTE FROM THE RECORD
         CI        6,X'CF'         WAS THE RECORD A FINAL RECORD
         BEQ       LIBLINK      YES-ALL DONE
         LA        1,FCBLIB        BASE ADDRESS OF THE LIBRARY FCB
         IFF       UNIXF,SKIP                                   *JCB*
         TBM       7,MACSWIT       SEARCHING MA2 FILE ?
         BNS       $+2W            NO
         LA        1,FCBLIB2       FCB ADDR OF MA2 FCB
SKIP     ANOP                                                   *JCB*
         BL        READREC         GET INPUT RECORD.
         IFF       UNIXF,SKIP                                   *JCB*
         TBM       7,MACSWIT       SEARCHING MA2 FILE ?
         BNS       LIBMV5.0        NO
         TBM       6,FCBLIB2+3W    EOF ON MA2 FILE ??
         BS        ERLIB2          YES
         BU        LIBMV5.1
SKIP     ANOP                                                   *JCB*
LIBMV5.0 TBM       6,FCBLIB+3W
         BS        ERLIB            ERROR IF EOF HERE.
LIBMV5.1 LB        7,LIBBUF+1B     GET THE BYTE COUNT FROM THE NEXT REC
         BZ        ABORTMAC        ABORT IF MACRO LIB BAD
         LA        R1,LIBBUF+6B    THE PLACE WHERE WE START COPYING
         BU        LIBMV2          GO PROCESS THE NEW MACRO PROTYPE REC
LIBX4    CAMB      R4,LIBCNT       TEST FOR MAX PAR #
         BLT       LIBX3           BR IF NOT NEW HIGH
         STB       R4,LIBCNT       SAVE NEW HIGH
         ABM       7,LIBCNT        MAKE IT A COUNT
         BU        LIBX3           GO ON
         SPACE     3
LIBLINK  LA        R2,MACP         ADDR OF MAC POINTER
         IFF       UNIXF,SKIP                                   *JCB*
         TBM       7,MACSWIT       SEARCHING MA2?
         BNS       $+2W            BR IF NOT
         LA        R2,MA2P         ADDR OF MA2 POINTER
SKIP     ANOP                                                   *JCB*
         LW        R1,0W,R2        GET POINTER
         BNZ       LINKIT          BR IF INITIALIZED
         LW        R1,HEAD         GET STACK POINTER
         STW       R1,0W,R2        PUT IN MA2/MAC POINTER
LINKIT   LW        R1,HEAD         GET NEW ENTRY ADDRESS
         LW        R7,LIBCNT       GET COUNT OF BYTES IN MACRO
         LD        R4,MACNAME      GET MACRO NAME FOR NEW ENTRY
*!!!!!!!!SEA!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!S880752
         STW       R7,4W,R1        PUT IN STACK FOR LATER
         STD       R4,2W,R1        SAVE MACRO NAME
         ZMD       0W,R1           CLEAR HEAD CELL POINTERS
         ZMW       5W,R1                CLEAR COUNT AND STRING WORD
         LW        R2,0W,R2        GET BASE ADDR OF MAC/MA2 START
MS15     CAMD      R4,MACRO,R2    COMPARE AGAINST LAST NODE ENTRY
         BLT       MS50            NEW .LT. LAST
         BEQ       MS95            THEY ARE .EQ. (SHOULDN'T HAPPEN)
         LW        R3,RLINK,R2     NEW .GT. LAST, FOLLOW ASSENDING LINK
         BZ        MS90            ZERO MEANS END OF BRANCH
MS30     TRR       R3,R2           GENERATE PATH POINTER
         BU        MS15            GO TRY NEXT BRANCH NODE
MS50     LW        R3,LLINK,R2     GET DECENDING PATH
         BNZ       MS30            IF NOT END, GO UPDATE
         STW       R1,LLINK,R2     UPDATE LINK IN PREVIOUS NODE
         BU        MS95            GO CLEAR NEW ENTRY NODE POINTERS
MS90     STW       R1,RLINK,R2     UPDATE RLINK IN PREVIOUS NODE
MS95     ZMW       RLINK,R1        CLEAR NEW ENTRY NODE POINTERS
         ZMW       LLINK,R1        DITTO
*                                  NOW GO TRANSFER TO USER
         BU        SM60            R1=ENTRY ADDR, R7=BYTE COUNT
         PAGE
************************************************************************
*                                                                      *
*        R E A D R E C                                                 *
*                                                                      *
*                  DEBLOCK FIXED LENGTH RECORDS OF 48W                 *
*                                                                      *
************************************************************************
         SPACE     3
READREC  CEQU      $                                            ESCT-32
         STF       0,RRREGS
RR0      LW        R1,CURREC       GET CURRENT REC POINTER
         MPI       R0,48W          COMPUTE ADDRESS
         LH        R1,SYSBUF,R1    TEST FOR EOF
         CI        1,X'0F00'
         BNE       RR1           WAS THIS EOF RECORDZ
         IFF       UNIXF,SKIP                                   *JCB*
         TBM       7,MACSWIT       SEARCHING MA2 FILE ?
         BNS       RR0.0           NO
         SBM       6,FCBLIB2+3W    SET EOF IN MA2 FCB
         BU        RRR             RETURN
SKIP     ANOP                                                   *JCB*
RR0.0    CEQU      $                                            ESCT-32
         SBM       6,FCBLIB+3W     YES-SET EOF BIT IN FCB.
         BU        RRR             RETURN.
RR1      LW        1,RECNUM        GET CONTROL BYTE .
         BNE       RR2          IS RECORD COUNT EXHAUSTED?
         BL        PRIM            YES-PRIM BUFFER.
         BU        RR0             RESTART READ.
RR2      LW        1,CURREC        GET CURRENT REC POINTER     [JB]
         MPI       0,48W
         LI        5,-48
         LW        2,FCBLIB+1W     GET TCW.
         IFF       UNIXF,SKIP                                   *JCB*
         TBM       7,MACSWIT       SEARCHING MA2 FILE?
         BNS       $+2W            NO
         LW        2,FCBLIB2+1W    GET TCW FOR MA2
SKIP     ANOP                                                   *JCB*
         ANMW      R2,=X'0007FFFF' KEEP ONLY THE ADDR PART      S880752
RR3      CEQU      $                                            ESCT-32
         LW        6,SYSBUF,1      MOVE 48W TO CALLERS BUFFER.
         STW       6,0,2
         ADI       1,1W
         ADI       2,1W
         BIB       5,RR3
         ABM       31,CURREC       BUMP REC POINTER   [JB]
         LW        1,RECNUM        GET CONTROL BYTE.
         SUI       1,1             DECREMENT RECORD COUNT.
         STW       1,RECNUM
RRR      CEQU      $                                            ESCT-32
         LF        0,RRREGS
         TRSW      0               RETURN.
         SPACE     2
         BOUND     8W
RRREGS   RES       8W
         PAGE
************************************************************************
*                                                                      *
*        P R I M                                                       *
*                                                                      *
************************************************************************
*
* (C) COPYRIGHT 1983 ENCORE COMPUTER CORPORATION
*     ALL RIGHTS RESERVED
*
         SPACE     3
PRIM     CEQU      $                                            ESCT-32
         STF       0,PRIMREGS      SAVE REGS.
         LA        1,FCBLIB
         IFF       UNIXF,SKIP                                   *JCB*
         TBM       7,MACSWIT       SEARCHING MA2 FILE ??
         BNS       $+2W            NO
         LA        1,FCBLIB2       MA2 FCB ADDRESS
         LW        2,1W,1          SAVE CALLER'S TCW
         LW        3,PRIMTCW
         STW       3,1W,1
         SVC       1,X'31'         READ BLOCK
         STW       2,1W,1          RESTORE CALLER'S TCW
         TBM       7,3W,1          TEST FOR EOM
         BS        LIBNO           IF EOF, SEARCH COMPLETE
SKIP     ANOP                                                   *JCB*
         IFT       UNIXF,SKIP                                   *JCB*
         LA        R6,SYSBUF       READ BUFFER ADDRESS          *JCB*
         CCALL     _readraw,MC.FD,R6.,=7680                     *JCB*
         TRR       R0,R0           ERROR                        *JCB*
         BLT       LIBNO           ASSUME EOF                   *JCB*
SKIP     ANOP                                                   *JCB*
         LI        5,40            CALC NUM OF REC IN MEMORY
         ZMW       CURREC          CLEAR REC COUNTER
         STW       5,RECNUM        SET RECORD CONTROL BYTE.
         LF        0,PRIMREGS      RESTORE REGS.
         TRSW      0
         SPACE     2
         BOUND     1W
PRIMTCW  GEN       12/1920,20/W(SYSBUF)
         SPACE     2
         BOUND     8W
PRIMREGS RES       8W
MACNAME  DATAD     0               CURRENT MACRO NAME
         SPACE     3
BADDVMAC LW        5,AS29          ABORT CODE
         IFF       UNIXF,SKIP                                   *JCB*
         TBM       7,MACSWIT       SEARCHING MA2 FILE ?
         BNS       ABORT           NO
         LW        5,AS30          ABORT CODE
SKIP     ANOP                                                   *JCB*
         BU        ABORT
         SPACE     3
ERLIB    CEQU      $                                            ESCT-32
         LW        5,AS14          ABORT CODE.
         BU        ABORT
         SPACE     2
ERLIB2   LW        5,AS26          ABORT CODE
         BU        ABORT
         SPACE     2
         BOUND     1W
ERMAC    CEQU      $                                            ESCT-32
         LW        5,AS15          ABORT CODE.
         TBM       2,3W,1          BLOCKING ERROR FLAG
         BNS       $+2W            BRANCH IF NOT SET-I/O ERROR
         LW        5,AS25          ABORT CODE
         BU        ABORT
         SPACE     2
ERMAC2   CEQU      $                                            ESCT-32
         LW        5,AS27          ABORT CODE
         TBM       2,3W,1          BLOCKING BUFFER ERROR FLAG SET ?
         BNS       ABORT           NO
         LW        5,AS28          ABORT CODE
         BU        ABORT
         SPACE     2
         BOUND     1W
AS14     DATAW     C'AS14'         EOF ENCOUNTERED ON MACRO FILE.
AS15     DATAW     C'AS15'         UNRECOVERABLE I/O ERROR 'MAC'.
AS25     DATAW     C'AS25'         INVALID BLOCKING BUFF CTRL PTR  MAC.
AS26     DATAW     C'AS26'         EOF ON "MA2" FILE
AS27     DATAW     C'AS27'         UNREC I/O ERROR ON "MA2" FILE
AS28     DATAW     C'AS28'         INVALID BLK. BUFF. CTRL PTR ON "MA2"
AS29     DATAW     C'AS29'         "MAC" ASSIGNED TO ILLEGAL DEVICE
AS30     DATAW     C'AS30'         "MA2" ASSIGNED TO ILLEGAL DEVICE
         SPACE     2
CURREC   DATAW     0
RECNUM   RES       1W
SYSBUF   RES       1920W
         BOUND     1W
BADMACM  GEN       12/BMBC,20/B(BMACMSG)
BMACMSG  DATAB     C'1** BAD MACRO ENCOUNTERED DURING MACRO SEARCH **'
BMBC     DEQU      $-BMACMSG                                    ESCT-32
         BOUND     1W
OVFLWTCW GEN       12/OVBC,20/B(OVFLWMSG)
OVFLWMSG DATAB     C'1** UNABLE TO ALLOCATE MEMORY FOR MACRO STORAGE **'
OVBC     DEQU      $-OVFLWMSG                                   ESCT-32
         LPOOL                     DROP LITERALS HERE
PARFLAG  DATAB     0               FLAGS FOR MACRO SCAN
STKP     DATAW     STK             MACRO EXPANSION STACK POINTER
         BOUND     1D
STK      RES       4000W           START WITH 2K STACK SIZE   84-175
STKEND   DEQU      $               MARKS END OF STACK           ESCT-32
*!SYMTAB!!!DATAD!!!0,0,0!!!!!!!!!!!START!SYMBOL!TABLE!HERE!2WD!!S880752
SYMTAB   DATAW     SYMBOLS                                      S880752
SYMBOLS  DATAD     0,0,0           FIRST ENTRY IN SYMBOL TABLE  S880752
*
* (C) COPYRIGHT 1983 ENCORE COMPUTER CORPORATION
*     ALL RIGHTS RESERVED
*****************************************************************JCB*
* THE FOLLOWING END STATEMENT MUST BE MODIFIED FOR UNIXF SET ****JCB*
*****************************************************************JCB*
*JCB* THEEND   END       A0        THE ASSM ADAPT CONTROLS START*JCB*
THEEND   END                       THE ASSEMBLER IS A SUBROUTINE*JCB*
