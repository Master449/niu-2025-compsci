*****************************************************************
*                                                               *
* CSCI 360-0001           ASSIGNMENT 9              SPRING 2024 *
*                                                               *
* DEVELOPER NAME: David Flowers II                              *
*       DUE DATE: 04/19/24                                      *
*                                                               *
*****************************************************************
*
PAYROLL2 CSECT
*
* STANDARD ENTRY LINKAGE WITH R12 AS BASE REGISTER
*
         STM   14,12,12(13)      SAVE REGS IN CALLER'S SAVE AREA
         LR    12,15 COPY        CSECT ADDR INTO R12
         USING PAYROLL2,12       ESTABLISH R12 AS THE BASE REG
         LA    14,REGSAVE        R14 POINTS TO THIS CSECT'S SAVE AREA
         ST    14,8(,13)         STORE ADDR OF THIS CSECT'S SAVE AREA
         ST    13,4(,14)         STORE ADDR OF CALLER'S SAVE AREA
         LR    13,14             POINT R13 AT THIS CSECT'S SAVE AREA
*
         LA    11,4095(,12)      POINT R11 4095 BYTES BEYOND R12
         LA    11,1(,11)         POINT R11 4096 BYTES BEYOND R12
         USING PAYROLL2+4096,11  ESTABLISH R11 AS SECOND BASE REG
*
         LA    1,BTPARMS         R1  -> BTPARMS
         L     15,=V(BUILDTBL)   R15 -> SUBPROGRAM BUILDTBL
         BALR  14,15             BRANCH TO BUILDTBL
*
         LA    1,PTPARMS         R1 -> PTPARMS
         L     15,=V(PROCTBL)    15 -> SUBPROGRAM PROCTBL
         BALR  14,15             BRANCH TO PROCTBL
*
* STANDARD EXIT LINKAGE WITH RC OF 0
*
         SR    15,15             R15 = RETURN CODE OF 0
         L     13,4(,13)         POINT R13 TO CALLER'S SAVE AREA
         L     14,12(,13)        RESTORE REGISTER 14
         LM    0,12,20(13)       RESTORE R0 THRU R12
*
         BR    14                RETURN TO CALLER
*
         LTORG
*
REGSAVE  DS 18F                  PROGRAM'S REGISTER SAVE AREA
*
EMPTBL   DS    120CL42           120 TABLE ENTRIES 42 BYTES LONG
*
PEMPCTR  DC    PL3'0'            PACKED EMPLOYEE COUNTER (MAX 999)
*
BTPARMS  DC    A(PFWHPCT,PSWHPCT,EMPTBL,PEMPCTR)  BUILD TABLE PARMS
PTPARMS  DC    A(PFWHPCT,PSWHPCT,EMPTBL,PEMPCTR)  PROCE TABLE PARMS
*
*****************************************************************
*                                                               *
* CSCI 360-0001           ASSIGNMENT 9              SPRING 2024 *
*                                                               *
* DEVELOPER NAME: David Flowers II                              *
*       DUE DATE: 04/19/24                                      *
*       FUNCTION: BUILDTBL                                      *
*                 Read the input and build the table            *
*                                                               *
*****************************************************************
*
$TBLENT  DSECT                  DSECT FOR TABLE ENTRY
$EMPID   DS    PL5              TABLE EMP ID
$HRPAY   DS    PL3              TABLE HOURLY PAY
$HOURS   DS    PL3              TABLE HOURS WORKED
$DEDUCT  DS    PL3              TABLE DEDUCTIONS
$BONUS   DS    PL3              TABLE BONUS AMMOUNT
$EMPNME  DS    CL25             TABLE NAME
*
$RECORD  DSECT                  DSECT FOR INPUT RECORD
$IEMPID  DS    ZL8              INPUT EMPLOYEE ID
$IHRPAY  DS    ZL5              INPUT EMPLOYEE HOURLY PAY RATE
$IHOURS  DS    ZL5              INPUT EMPLOYEE HOURS WORKED
$IDEDUCT DS    ZL5              INPUT EMPLOYEE DEDUCTION
$IBONUS  DS    ZL5              INPUT EMPLOYEE BONUS
$IEMPNME DS    CL25             EMP NAME
         DS    CL27
*
BUILDTBL CSECT
*
         STM   14,12,12(13)     SAVE REGS IN CALLER'S SAVE AREA
         LR    12,15            COPY CSECT ADDRESS INTO R12
         USING BUILDTBL,12      ESTABLISH R12 AS THE BASE REG
         LA    14,BTSAVE        R14 POINTS TO THIS CSECT'S SAVE AREA
         ST    14,8(,13)        STORE ADDRESS OF THIS CSECT'S SAVE AREA
         ST    13,4(,14)        STORE ADDRESS OF CALLER'S SAVE AREA
         LR    13,14            POINT R13 AT THIS CSECT'S SAVE AREA
*
         LM    2,5,0(1)         R2 -> PFWPCT(3)
*                               R3 -> PSWHPCT(3)
*                               R4 -> EMPTBL
*                               R5 -> PEMPCTR(3)
*
         XREAD RECORD,80               READ FIRST RECORD
         PACK  PFWHPCT(4),RECORD(6)    PACK FEDERAL WH
         PACK  PSWHPCT(4),RECORD+6(6)  PACK STATE WH
*
         USING $TBLENT,4           ESTABLISH ADDRESSABILITY FOR TBLENT
*
         LA    6,RECORD            R6 -> BEGINING INPUT RECORD
         USING $RECORD,6           ESTABLISH ADDRESSABILITY FOR RECORD
*
         XREAD RECORD,80           READ FIRST RECORD
*
LOOP1    BC    B'0100',ENDLOOP1    BRANCH IF NO RECORDS
*
         AP    0(3,5),=PL1'1'      ADD 1 TO EMPCTR
*
         PACK  $EMPID(5),$IEMPID(9)       PACK EMPLOYEE ID
         PACK  $HRPAY(3),$IHRPAY(5)       PACK HOURLY PAY
         PACK  $HOURS(3),$IHOURS(5)       PACK HOURS WORKED
         PACK  $DEDUCT(3),$IDEDUCT(5)     PACK DEDUCTION
         PACK  $BONUS(3),$IBONUS(5)       PACK BONUS
         MVC   $EMPNME(25),$IEMPNME       MOVE EMPLOYEE NAME
*
         LA    4,42(,4)             MOVE REG 4 TO NEXT ENTRY
         XREAD RECORD,80            READ NEXT RECORD
*
         BC    B'1111',LOOP1        BRANCH BACK TO TOP
*
         DROP  4,6
*
ENDLOOP1 DS    0H                END OF LOOP
*
         SR    15,15             R15 = RETURN CODE OF 0
         L     13,4(,13)         POINT R13 TO CALLER'S SAVE AREA
         L     14,12(,13)        RESTORE REGISTER 14
         LM    0,12,20(13)       RESTORE R0 THRU R12
*
         BR    14                RETURN TO CALLER
*
         LTORG
*
BTSAVE   DS    18F              REGISTER SAVE AREA
*
RECORD   DS    CL80
*
PFWHPCT  DC    PL4'0'           PACK F WH PCT
PSWHPCT  DC    PL4'0'           PACK S WH PCT
*
*        END   BUILDTBL
*
*****************************************************************
*                                                               *
* CSCI 360-0001           ASSIGNMENT 9              SPRING 2024 *
*                                                               *
* DEVELOPER NAME: David Flowers II                              *
*       DUE DATE: 04/19/24                                      *
*       FUNCTION: PROCTBL                                       *
*                 Subroutine to process the employee records.   *
*                                                               *
*****************************************************************
*
$TBLENT2 DSECT                  DSECT FOR TABLE ENTRY
$EMPID2  DS    PL5              TABLE EMP ID
$HRPAY2  DS    PL3              TABLE HOURLY PAY
$HOURS2  DS    PL3              TABLE HOURS WORKED
$DEDUCT2 DS    PL3              TABLE DEDUCTIONS
$BONUS2  DS    PL3              TABLE BONUS AMMOUNT
$EMPNME2 DS    CL25             TABLE NAME
*
PROCTBL  CSECT
         STM   14,12,12(13)     SAVE REGS IN CALLER'S SAVE AREA
         LR    12,15            COPY CSECT ADDRESS INTO R12
         USING PROCTBL,12       ESTABLISH R12 AS THE BASE REG
         LA    14,PROCSAVE      R14 POINTS TO THIS CSECT'S SAVE AREA
         ST    14,8(,13)        STORE ADDRESS OF THIS CSECT'S SAVE AREA
         ST    13,4(,14)        STORE ADDRESS OF CALLER'S SAVE AREA
         LR    13,14            POINT R13 AT THIS CSECT'S SAVE AREA
*
         LM    2,5,0(1)         R2 -> PFWPCT(3)
*                               R3 -> PSWHPCT(3)
*                               R4 -> EMPTBL
*                               R5 -> PEMPCTR(3)
*
         USING $TBLENT2,4       ESTABLISH ADDRESSABILITY FOR $TBLENT2
*
         ST    5,CAPARMS+4      STORE PEMPCTR IN PARMS LIST
         ST    2,CNPPARMS+8     STORE PFWPCT IN PARMS
         ST    3,CNPPARMS+16    STORE PSWHPCT IN PARMS
*
         LA    2,99                       LOAD 99 INTO HEADER COUNTER
         ZAP   TEMPCTR(3),0(3,5)          LOAD EMP CTR INTO TEMP CTR
*
LOOPPROC DS    0H                         BEGIN PROCESSING LOOP
*
*    EMPLOYEE NAME
*
         MVC   OEMPNME(25),$EMPNME2       MOVE EMPLOYEE NAME
*
*    EMPLOYEE ID
*
         MVC   OEMPID(9),=X'212020602020202020'
         LA    1,OEMPID+1                 PREP R1 FOR 0
         EDMK  OEMPID(9),$EMPID2          MOVE ID TO PRINT
         BCTR  1,0                        DECREMENT R1 BY 1
         MVI   0(1),C'0'                  PLACE 0
*
*    HOURLY PAY
*
         MVC   OPAYRATE(7),=X'402021204B2020'
         LA    1,OPAYRATE                 PREP R1
         EDMK  OPAYRATE(7),$HRPAY2        MOVE PAY TO PRINT LINE
         BCTR  1,0                        DECREMENT R1 BY 1
         MVI   0(1),C'$'                  PLACE $ IN FRONT
*
*    HOURS WORKED
*
         MVC   OHOURS(7),=X'402021204B2020'
         ED    OHOURS(7),$HOURS2          MOVE PAY TO PRINT LINE
*
*    GROSS PAY
*
         ZAP   PCALC(6),$HRPAY2(3)        COPY PHR INTO CALC
*
         MP    PCALC(6),$HOURS2(3)        HOURS * PAYRATE
         SRP   PCALC(6),64-2,9            ROUND TO TWO DECIMAL
         SP    PCALC(6),$DEDUCT2(3)       SUBTRACT DEDUCTIONS
         AP    PCALC(6),$BONUS2(3)        ADD BONUSES
*
         ZAP   PEMPGPAY(6),PCALC(6)       PACK GROSS PAY
         LA    1,OGROSS                   PREPARE R1 FOR $ ADDRESS
         MVC   OGROSS(16),=X'402020206B2020206B2021204B2020'
         EDMK  OGROSS(16),PEMPGPAY        MOVE PCALC TO PRINT LINE
*
*
         BCTR  1,0                        SUBTRACT 1 FROM R1
         MVI   0(1),C'$'                  ADD $ SIGN
         AP    PTGRPAY(7),PEMPGPAY(6)     ADD GROSS TO RUNNING TOTAL
*
*    CALL NET PAY SUBROUTINE
*
         LA    1,CNPPARMS                 R1  -> CNPPARMS
         L     15,=V(CALCNPAY)            R15 -> SUBPROGRAM CALCNPAY
         BALR  14,15                      BRANCH TO CALCNPAY
*
*    ADD TOTALS
*
         AP    PTNETPAY(7),PEMPNPAY(6)    ADD NET TO RUNNING TOTAL
         AP    PTFWITH(7),PFEDWITH(6)     ADD FEDWH TO RUNNING TOTAL
         AP    PTSWITH(7),PSTWITH(6)      ADD STWH TO RUNNING TOTAL
*
* PRINT FED
         MVC   OFEDWH(15),=X'402020206B2020206B2021204B2020'
         EDMK  OFEDWH(15),PFEDWITH        MOVE PCALC TO PRINT LINE
         BCTR  1,0                        SUBTRACT 1 FROM R1
         MVI   0(1),C'$'                  ADD $ SIGN
*
* PRINT STATE
         MVC   OSTAWH(15),=X'402020206B2020206B2021204B2020'
         EDMK  OSTAWH(15),PSTWITH         MOVE PCALC TO PRINT LINE
         BCTR  1,0                        SUBTRACT 1 FROM R1
         MVI   0(1),C'$'                  ADD $ SIGN
*
* PRINT NET
         MVC   ONETPAY(15),=X'402020206B2020206B2021204B2020'
         EDMK  ONETPAY(15),PEMPNPAY       MOVE PCALC TO PRINT LINE
         BCTR  1,0                        SUBTRACT 1 FROM R1
         MVI   0(1),C'$'                  ADD $ SIGN
*
*    PAGE DELIMITER CHECKING
*    AND HEADER PRINTING
*
         C     2,=F'17'                   COMPARE WITH FULLWORD LITERAL
         BL    NOHDRS                     BRANCH LOW TO NO HEADERS
         AP    PPAGECTR(2),=PL1'1'        INCREMENT PAGE CTR BY 1
         MVC   OPAGECTR(4),=X'4020212020' SUPRESSES LEADING 0
         ED    OPAGECTR(6),PPAGECTR       MOVE TO PRINTLINE
*
         XPRNT HEADER1,133                PRINT BANK HEADER
         XPRNT HEADER2,133                PRINT BANK SUBSCRIPT
         XPRNT COLHEAD1,133               PRINT COLUMN HEADER 1
         XPRNT COLHEAD2,133               PRINT COLUMN HEADER 2
         XPRNT COLHEAD3,133               PRINT DASHED LINE BREAK
*
         SR    2,2                        RESET LINE COUNTER
NOHDRS   XPRNT DETAIL,133                 PRINT THE EMPLOYEE RECORD
         LA    2,1(,2)                    ADD 1 TO LINE COUNTER
*
         CP    TEMPCTR(3),=PL1'1'         COMPARE TEMP COUNTER TO 0
         BC    B'1100',ENDPROCL           IF 0 THEN EXIT LOOP
*
         SP    TEMPCTR(3),=PL1'1'         DECREMENT TEMP COUNTER
         LA    4,42(4)                    MOVE REG 4 TO NEXT ENTRY
         B     LOOPPROC                   IF WE DIDNT EXIT, BRANCH TOP
*
ENDPROCL DS    0H                         LOOP BREAK
*
         AP    PPAGECTR(2),=PL1'1'        INCREMENT PAGE CTR BY 1
         MVC   OPAGECTR(4),=X'4020212020' SUPRESSES LEADING 0
         ED    OPAGECTR(6),PPAGECTR       MOVE TO PRINTLINE
*
*    PRINT TOTALS
*
* EMP COUNTER
         MVC   OEMPCTR(6),=X'402020202120'
         ED    OEMPCTR(6),PEMPCTR         MOVE TOTAL EMP TO PRNT
*
* TOTAL GROSS PAY
         MVC   OTGRPAY(16),=X'4020202020202020206B2021204B2020'
         LA    1,OTGRPAY                  PREP R1
         EDMK  OTGRPAY(16),PTGRPAY        MOVE TOTAL GROSS TO PRNT
         BCTR  1,0                        SUBTRACT 1 FROM R1
         MVI   0(1),C'$'                  ADD $ SIGN
*
* TOTAL FEDERAL WH
         MVC   OTFWITH(16),=X'4020202020202020206B2021204B2020'
         LA    1,OTFWITH                  PREP R1
         EDMK  OTFWITH(16),PTFWITH        MOVE TOTAL FW TO PRNT
         BCTR  1,0                        SUBTRACT 1 FROM R1
         MVI   0(1),C'$'                  ADD $ SIGN
*
* TOTAL STATE WH
         MVC   OTSWITH(16),=X'4020202020202020206B2021204B2020'
         LA    1,OTSWITH                  PREP R1
         EDMK  OTSWITH(16),PTSWITH        MOVE TOTAL STW TO PRNT
         BCTR  1,0                        SUBTRACT 1 FROM R1
         MVI   0(1),C'$'                  ADD $ SIGN
*
* TOTAL NET PAY
         MVC   OTNETPAY(16),=X'4020202020202020206B2021204B2020'
         LA    1,OTNETPAY                 PREP R1
         EDMK  OTNETPAY(16),PTNETPAY      MOVE TOTAL NET TO PRNT
         BCTR  1,0                        SUBTRACT 1 FROM R1
         MVI   0(1),C'$'                  ADD $ SIGN
*
*
*    CALCULATE AND PRINT AVERAGES
*
* GROSS AVERAGE
         ZAP   PTOTAL(7),PTGRPAY(7)
         LA    1,CAPARMS                  R1  -> CAPARMS
         L     15,=V(CALCAVG)             R15 -> CALCAVG
         BALR  14,15                      BRANCH TO CALCAVG
*
         MVC   AGROSPAY(18),=X'4020202020202020206B2021204B2020'
         LA    1,AGROSPAY                 PREP R1
         EDMK  AGROSPAY(18),PAVG          MOVE TO AVG GROSS
         BCTR  1,0                        SUBTRACT 1 FROM R1
         MVI   0(1),C'$'                  ADD $ SIGN
*
* FEDERAL WIHHOLDING AVERAGE
         ZAP   PTOTAL(7),PTFWITH(7)
         LA    1,CAPARMS                  R1  -> CAPARMS
         L     15,=V(CALCAVG)             R15 -> CALCAVG
         BALR  14,15                      BRANCH TO CALCAVG
*
         MVC   ATFWITH(18),=X'4020202020202020206B2021204B2020'
         LA    1,ATFWITH                  PREP R1
         EDMK  ATFWITH(18),PAVG           MOVE TO AVG FED WH
         BCTR  1,0                        SUBTRACT 1 FROM R1
         MVI   0(1),C'$'                  ADD $ SIGN
*
* STATE WITHHOLDING AVERAGE
         ZAP   PTOTAL(7),PTSWITH(7)
         LA    1,CAPARMS                  R1  -> CAPARMS
         L     15,=V(CALCAVG)             R15 -> CALCAVG
         BALR  14,15                      BRANCH TO CALCAVG
*
         MVC   ATSWITH(18),=X'4020202020202020206B2021204B2020'
         LA    1,ATSWITH                  PREP R1
         EDMK  ATSWITH(18),PAVG           MOVE TO AVG STATE WH
         BCTR  1,0                        SUBTRACT 1 FROM R1
         MVI   0(1),C'$'                  ADD $ SIGN
*
* NET PAY AVERAGE
         ZAP   PTOTAL(7),PTNETPAY(7)
         LA    1,CAPARMS                  R1  -> CAPARMS
         L     15,=V(CALCAVG)             R15 -> CALCAVG
         BALR  14,15                      BRANCH TO CALCAVG
*
         MVC   ATNETPAY(18),=X'4020202020202020206B2021204B2020'
         LA    1,ATNETPAY                 PREP R1
         EDMK  ATNETPAY(18),PAVG          MOVE TO AVG NET PAY
         BCTR  1,0                        SUBTRACT 1 FROM R1
         MVI   0(1),C'$'                  ADD $ SIGN
*
*    PRINT SUMMARY
*
         XPRNT HEADER1,133                PRINT BANK HEADER
         XPRNT HEADER2,133                PRINT BANK SUBSCRIPT
         XPRNT TOTLHEAD,133               PRINT TOTALS
*
         XPRNT SUMHEAD1,133               PRINT SUMMARY LINE 1
         XPRNT SUMHEAD2,133               PRINT SUMMARY LINE 2
         XPRNT SUMHEAD3,133               PRINT SUMMARY LINE 3
         XPRNT SUMHEAD4,133               PRINT SUMMARY LINE 4
         XPRNT SUMHEAD5,133               PRINT SUMMARY LINE 5
*
         SR    15,15             R15 = RETURN CODE OF 0
         L     13,4(,13)         POINT R13 TO CALLER'S SAVE AREA
         L     14,12(,13)        RESTORE REGISTER 14
         LM    0,12,20(13)       RESTORE R0 THRU R12
*
         BR    14                RETURN TO CALLER
*
         LTORG
*
PROCSAVE DS    18F                        REGISTER SAVE AREA
*
* PARAMETER VARIABLES
*
CNPPARMS DC    A(PEMPGPAY,PEMPNPAY,0,PFEDWITH,0,PSTWITH) CALC NET PARM
CAPARMS  DC    A(PTOTAL,0,PAVG)    CALCULATE AVERAGE PARAMETERS
*
TEMPCTR  DC    PL3'0'              TEMP FIELD FOR EMP CTR BRANCHING
*
* PACKED DECIMAL VARIABLES
*
PTOTAL   DC    PL7'0'      TOTAL FIELD TO PASS
PAVG     DC    PL7'0'      AVG FIELD FOR RETURNED CALC
*
PPAGECTR DC    PL2'0'      PACKED PAGE COUNTER (MAX 999)
*
PEMPID   DC    PL5'0'      PACKED EMPLOYEE ID
PHRPAY   DC    PL3'0'      PACKED EMPLOYEE HOURLY PAY RATE
PHOURS   DC    PL3'0'      PACKED EMPLOYEE HOURS WORKED
PDEDUCT  DC    PL3'0'      PACKED EMPLOYEE DEDUCTION
PBONUS   DC    PL3'0'      PACKED EMPLOYEE BONUS
PEMPGPAY DC    PL6'0'      PACKED CALCULATED EMPLOYEE GROSS PAY
PFEDWITH DC    PL6'0'      PACKED CALCULATED FEDERAL WITHHOLDING
PSTWITH  DC    PL6'0'      PACKED CALCULATED STATE WITHHOLDING
PEMPNPAY DC    PL6'0'      PACKED CALCULATED EMPLOYEE NET PAY
*
PCALC    DC    PL10'0'     USED TO CALCULATE WITHHOLDING AND AVGS
*
PTGRPAY  DC    PL7'0'      PACKED TOTAL GROSS EMPLOYEE PAY
PTFWITH  DC    PL7'0'      PACKED TOTAL FEDERAL WITHHOLDING
PTSWITH  DC    PL7'0'      PACKED TOTAL STATE WITHHOLDING
PTNETPAY DC    PL7'0'      PACKED TOTAL NET EMPLOYEE PAY
*
* OUTPUT FIELDS
*
DETAIL   DC    C'0'                 CARRIAGE CONTROL
OEMPID   DS    CL9                  OUTPUT FIELD FOR EMPLOYEE ID
         DC    2C' '                02 SPACES
OEMPNME  DS    CL25                 OUTPUT FIELD FOR EMPLOYEE NAME
         DC    3C' '                03 SPACES
OPAYRATE DS    CL7                  OUTPUT FIELD FOR PAY RATE
         DC    3C' '                03 SPACES
OHOURS   DS    CL7                  OUTPUT FIELD FOR HOURS WORKED
         DC    5C' '                05 SPACES
OGROSS   DS    CL16                 OUTPUT FIELD FOR GROSS PAY
         DC    4C' '                04 SPACES
OFEDWH   DS    CL15                 OUTPUT FOR FEDERAL WITHHOLD
         DC    3C' '                03 SPACES
OSTAWH   DS    CL14                 OUTPUT FOR STATE WITHHOLD
         DC    4C' '                04 SPACES
ONETPAY  DS    CL15                 OUTPUT FOR NET PAY
         DC    1C' '                01 SPACE
*
* PAGE HEADERS
*
HEADER1  DC    C'0'                 CARRIAGE CONTROL
         DC    50C' '               50 SPACES
         DC    C'STATE OF ILLINOIS NATIONAL BANK'   BANK HEADER
         DC    42C' '               42 SPACES
         DC    C'PAGE:'             PAGE INDICATOR
OPAGECTR DS    CL4                  OUTPUT FIELD FOR PAGE COUNTER
*
HEADER2  DC    C'0'                 CARRIAGE CONTROL
         DC    48C' '               48 SPACES
         DC    C'SEMI-MONTHLY EMPLOYEE PAYROLL REPORT'
         DC    48C' '               48 SPACES
*
* COLUMN HEADERS
*
COLHEAD1 DC    C'0'                 CARRIAGE CONTROL
         DC    C'EMPLOYEE'          EMPLOYEE LABEL
         DC    3C' '                03 SPACES
         DC    C'EMPLOYEE'          EMPLOYEE LABEL
         DC    21C' '               21 SPACES
         DC    C'HOURLY'            HOURLY LABEL
         DC    5C' '                05 SPACES
         DC    C'HOURS'             HOURS LABEL
         DC    12C' '               12 SPACES
         DC    C'EMPLOYEE'          EMPLOYEE LABEL
         DC    4C' '                04 SPACES
         DC    C'EMPLOYEE FEDERAL'  EMPLOYEE FEDERAL LABEL
         DC    4C' '                04 SPACES
         DC    C'EMPLOYEE STATE'    EMPLOYEE STATE LABEL
         DC    10C' '               10 SPACES
         DC    C'EMPLOYEE'          EMPLOYEE LABEL
*
COLHEAD2 DC    C' '                 CARRIAGE CONTROL
         DC    C'ID'                ID LABEL
         DC    9C' '                09 SPACES
         DC    C'NAME'              NAME LABEL
         DC    28C' '               28 SPACES
         DC    C'PAY'               PAY LABEL
         DC    4C' '                04 SPACES
         DC    C'WORKED'            WORKED LABEL
         DC    11C' '               11 SPACES
         DC    C'GROSS PAY'         GROSS PAY LABEL
         DC    9C' '                09 SPACES
         DC    C'WITHHOLDING'       WITHHOLDING LABEL
         DC    7C' '                07 SPACES
         DC    C'WITHHOLDING'       WITHHOLDING LABEL
         DC    11C' '               11 SPACES
         DC    C'NET PAY'           NET PAY LABEL
*
*                                   DASHED LINE SEPERATOR
COLHEAD3 DC    C' '
         DC    C'---------  -------------------------   -------   '
         DC    C'-------     ---------------    ----------------'
         DC    C'    --------------   ---------------'
*
* SUMMARY HEADERS
*
TOTLHEAD DC    C'0'                 CARRIAGE CONTROL
         DC    62C' '               62 SPACES
         DC    C'TOTALS'            TOTALS LABEL
         DC    65C' '               65 SPACES
*
SUMHEAD1 DC    C'0'                 CARRIAGE CONTROL
         DC    6C' '                6 SPACES
         DC    C'NUMBER OF EMPLOYEES: ' LABEL
         DC    9C' '                9 SPACES
OEMPCTR  DS    CL6                  EMPLOYEE COUNTER OUTPUT
         DC    87C' '               90 SPACES
*
SUMHEAD2 DC    C'0'                 CARRIAGE CONTROL
         DC    10C' '               10 SPACES
         DC    C'TOTAL GROSS PAY:   ' LABEL
OTGRPAY  DS    CL16                 TOTAL GROSS PAY OUTPUT
         DC    19C' '               19 SPACES
         DC    C'AVERAGE GROSS PAY: ' LABEL
AGROSPAY DS    CL18                 AVERAGE GROSS PAY OUTPUT
         DC    32C' '               32 SPACES
*
SUMHEAD3 DC    C'0'                 CARRIAGE CONTROL
         DC    C'TOTAL FEDERAL WITHHOLDING:   ' LABEL
OTFWITH  DS    CL16                 TOTAL FED WH OUTPUT
         DC    9C' '                09 SPACES
         DC    C'AVERAGE FEDERAL WITHHOLDING: '
ATFWITH  DS    CL18                 AVERAGE FED WH OUTPUT
         DC    32C' '               32 SPACES
*
SUMHEAD4 DC    C'0'                 CARRIAGE CONTROL
         DC    2C' '                02 SPACES
         DC    C'TOTAL STATE WITHHOLDING:   ' LABEL
OTSWITH  DS    CL16                 TOTAL STATE WH OUTPUT
         DC    11C' '               11 SPACES
         DC    C'AVERAGE STATE WITHHOLDING: ' LABEL
ATSWITH  DS    CL18                 AVERAGE STATE WH OUTPUT
         DC    32C' '               32 SPACES
*
SUMHEAD5 DC    C'0'                 CARRIAGE CONTROL
         DC    12C' '               12 SPACES
         DC    C'TOTAL NET PAY:   ' TOTAL NET PAY LABEL
OTNETPAY DS    CL16                 TOTAL NET PAY OUTPUT
         DC    21C' '               21 SPACES
         DC    C'AVERAGE NET PAY: ' AVERAGE NET PAY OUTPUT
ATNETPAY DS    CL18                 AVERAGE NET PAY OUTPUT
         DC    32C' '               32 SPACES
*
*        END   PROCTBL
*
*****************************************************************
*                                                               *
* CSCI 360-0001           ASSIGNMENT 9              SPRING 2024 *
*                                                               *
* DEVELOPER NAME: David Flowers II                              *
*       DUE DATE: 04/19/24                                      *
*       FUNCTION: CALCNPAY                                      *
*                 Calculate employees withholding and pay       *
*                                                               *
*****************************************************************
*
*
CALCNPAY CSECT
         STM   14,12,12(13)     SAVE REGS IN CALLER'S SAVE AREA
         LR    12,15            COPY CSECT ADDRESS INTO R12
         USING CALCNPAY,12      ESTABLISH R12 AS THE BASE REG
         LA    14,CALCNSVE      R14 POINTS TO THIS CSECT'S SAVE AREA
         ST    14,8(,13)        STORE ADDRESS OF THIS CSECT'S SAVE AREA
         ST    13,4(,14)        STORE ADDRESS OF CALLER'S SAVE AREA
         LR    13,14            POINT R13 AT THIS CSECT'S SAVE AREA
*
         LM    2,7,0(1)         R2 -> PEMPGPAY(6)
*                               R3 -> PEMPNPAY(6)
*                               R4 -> PFWHPCT(3)
*                               R5 -> PFEDWITH(6)
*                               R6 -> PSWHPCT(3)
*                               R7 -> PSTWITH(6)
*
*    FEDERAL WITHHOLDING
*
         ZAP   PTEMP1(10),0(6,2)      COPY GROSS INTO CALC
*
         MP    PTEMP1(10),0(4,4)      GROSS * FED PERCENT
         SRP   PTEMP1(10),64-5,5      ROUND TO PROPER NUMBER
*
         ZAP   0(6,5),PTEMP1(10)      PACK FEDERAL WH
*
*    STATE WITHHOLDING
*
         ZAP   PTEMP1(10),0(6,2)      COPY GROSS INTO CALC FIELD
*
         MP    PTEMP1(10),0(4,6)      GROSS * STATE PERCECENT
         SRP   PTEMP1(10),64-5,5      ROUND TO TWO DECIMAL
*
         ZAP   0(6,7),PTEMP1(10)      PACK STATE WITHHOLDING
*
*    NET EMPLOYEE PAY
*
         ZAP   0(6,3),0(6,2)          COPY GROSS INTO CALC FIELD
         SP    0(6,3),0(6,5)          MINUS FED WH
         SP    0(6,3),0(6,7)          MINUS STATE WH
*
         SR    15,15            R15 = RETURN CODE OF 0
         L     13,4(,13)        POINT R13 TO CALLER'S SAVE AREA
         L     14,12(,13)       RESTORE REGISTER 14
         LM    0,12,20(13)      RESTORE R0 THROUGH R12
         BR    14               RETURN TO CALLER
*
         LTORG
*
CALCNSVE DS    18F              REGISTER SAVE AREA
*
* PACKED FIELDS
*
PTEMP1   DC    PL10'0'
*
*****************************************************************
*                                                               *
* CSCI 360-0001           ASSIGNMENT 9              SPRING 2024 *
*                                                               *
* DEVELOPER NAME: David Flowers II                              *
*       DUE DATE: 04/19/24                                      *
*       FUNCTION: CALCAVG                                       *
*                 Calculate a single average                    *
*                                                               *
*****************************************************************
CALCAVG  CSECT
         STM   14,12,12(13)     SAVE REGS IN CALLER'S SAVE AREA
         LR    12,15            COPY CSECT ADDRESS INTO R12
         USING CALCAVG,12       ESTABLISH R12 AS THE BASE REG
         LA    14,CAVGSAVE      R14 POINTS TO THIS CSECT'S SAVE AREA
         ST    14,8(,13)        STORE ADDRESS OF THIS CSECT'S SAVE AREA
         ST    13,4(,14)        STORE ADDRESS OF CALLER'S SAVE AREA
         LR    13,14            POINT R13 AT THIS CSECT'S SAVE AREA
*
         LM    2,4,0(1)         R2 -> PTOTAL(7)
*                               R3 -> PEMPCTR(3)
*                               R4 -> PAVG(7)
*
         ZAP   PTEMP2(10),0(7,2)      COPY TOTAL INTO PTEMP2
*
         DP    PTEMP2(10),0(3,3)      DIVIDE BY EMPLOYEE COUNT
*
         ZAP   0(7,4),PTEMP2(7)       MOVE TO AVG
*
         SR    15,15             R15 = RETURN CODE OF 0
         L     13,4(,13)         POINT R13 TO CALLER'S SAVE AREA
         L     14,12(,13)        RESTORE REGISTER 14
         LM    0,12,20(13)       RESTORE R0 THRU R12
*
         BR    14                RETURN TO CALLER
*
         LTORG
*
CAVGSAVE DS    18F
*
* PACKED FIELDS
*
PTEMP2   DC    PL10'0'
*
         END   PAYROLL2