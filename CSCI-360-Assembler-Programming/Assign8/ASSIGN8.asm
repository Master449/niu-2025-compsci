*****************************************************************
*                                                               *
* CSCI 360-0001           ASSIGNMENT 8              SPRING 2024 *
*                                                               *
* DEVELOPER NAME: David Flowers II                              *
*       DUE DATE: 03/29/24                                      *
*                                                               *
*****************************************************************
*
PAYROLL1 CSECT
*
* STANDARD ENTRY LINKAGE WITH R12 AS BASE REGISTER
*
         STM   14,12,12(13)     SAVE REGS IN CALLER'S SAVE AREA
         LR    12,15 COPY       CSECT ADDR INTO R12
         USING PAYROLL1,12      ESTABLISH R12 AS THE BASE REG
         LA    14,REGSAVE       R14 POINTS TO THIS CSECT'S SAVE AREA
         ST    14,8(,13)        STORE ADDR OF THIS CSECT'S SAVE AREA
         ST    13,4(,14)        STORE ADDR OF CALLER'S SAVE AREA
         LR    13,14            POINT R13 AT THIS CSECT'S SAVE AREA
*
         ZAP   PPAGECTR(2),=PL1'0'       PREPARE PAGE COUNTER
         ZAP   PEMPCTR(3),=PL1'0'        PREPARE EMPLOYEE COUNTER
         LA    2,99                      LOAD 99 INTO HEADER COUNTER
*
         XREAD RECORD,80                 READ FIRST RECORD
*
         PACK  PFWHPCT(4),RECORD(6)      PACK FEDERAL WH PERCENT
         PACK  PSWHPCT(4),RECORD+6(6)    PACK STATE WH PERCENT
*
         XREAD RECORD,80                 READ FIRST RECORD
*
LOOP1    BC    B'0100',ENDLOOP1          BRANCH TO ENDLOOP1 IF EOF
*
*    PACKING AND MOVING INPUT DATA
*
         PACK  PEMPID(5),IEMPID(9)       PACK EMPLOYEE ID
         PACK  PHRPAY(3),IHRPAY(5)       PACK HOURLY PAY
         PACK  PHOURS(3),IHOURS(5)       PACK HOURS WORKED
         PACK  PDEDUCT(3),IDEDUCT(5)     PACK DEDUCTION
         PACK  PBONUS(3),IBONUS(5)       PACK BONUS
         MVC   OEMPNME(25),IEMPNME       MOVE EMPLOYEE ID
*
*    EMPLOYEE ID
*
         MVC   OEMPID(9),=X'21202020602020202020'
         LA    1,OEMPID+1                    PREP R1 FOR 0
         EDMK  OEMPID(9),PEMPID              MOVE ID TO PRINT
         BCTR  1,0                           DECREMENT R1 BY 1
         MVI   0(1),C'0'                     PLACE 0
*
*    HOURLY PAY
*
         MVC   OPAYRATE(7),=X'402021204B2020'
         LA    1,OPAYRATE                    PREP R1
         EDMK  OPAYRATE(7),PHRPAY            MOVE PAY TO PRINT LINE
         BCTR  1,0                           DECREMENT R1 BY 1
         MVI   0(1),C'$'                     PLACE $ IN FRONT
*
*    HOURS WORKED
*
         MVC   OHOURS(7),=X'402021204B2020'  EDIT PATTERN XX.XX
         ED    OHOURS(7),PHOURS              MOVE PAY TO PRINT LINE
*
*    GROSS PAY
*
         ZAP   PCALC(6),PHRPAY(3)            COPY PHR INTO CALC
*
         MP    PCALC(6),PHOURS(3)            HOURS * PAYRATE
         SRP   PCALC(6),64-2,9               ROUND TO TWO DECIMAL
         SP    PCALC(6),PDEDUCT(3)           SUBTRACT DEDUCTIONS
         AP    PCALC(6),PBONUS(3)            ADD BONUSES
*
         ZAP   PEMPGPAY(6),PCALC(6)          PACK GROSS PAY
         LA    1,OGROSS                      PREPARE R1 FOR $ ADDRESS
         MVC   OGROSS(15),=X'402020206B2020206B2021204B2020'
         EDMK  OGROSS(15),PEMPGPAY           MOVE PCALC TO PRINT LINE
         BCTR  1,0                           SUBTRACT 1 FROM R1
         MVI   0(1),C'$'                     ADD $ SIGN
         AP    PTGRPAY(7),PEMPGPAY(6)        ADD GROSS TO RUNNING TOTAL
*
*    FEDERAL WITHHOLDING
*
         ZAP   PCALC(10),PEMPGPAY(6)         COPY GROSS INTO CALC
*
         MP    PCALC(10),PFWHPCT(4)          GROSS * FED PERCENT
         SRP   PCALC(10),64-5,5              ROUND TO PROPER NUMBER
*
         ZAP   PFEDWITH(6),PCALC(10)         PACK FEDERAL WH
*
         MVC   OFEDWH(15),=X'402020206B2020206B2021204B2020'
         EDMK  OFEDWH(15),PFEDWITH           MOVE PCALC TO PRINT LINE
         BCTR  1,0                           SUBTRACT 1 FROM R1
         MVI   0(1),C'$'                     ADD $ SIGN
         AP    PTFWITH(7),PFEDWITH(6)        ADD FEDWH TO RUNNING TOTAL
*
*    STATE WITHHOLDING
*
         ZAP   PCALC(10),PEMPGPAY(6)         COPY GROSS INTO CALC FIELD
*
         MP    PCALC(10),PSWHPCT(4)          GROSS * STATE PERCECENT
         SRP   PCALC(10),64-5,5              ROUND TO TWO DECIMAL
*
         ZAP   PSTWITH(6),PCALC(10)          PACK STATE WITHHOLDING
*
         MVC   OSTAWH(15),=X'402020206B2020206B2021204B2020'
         EDMK  OSTAWH(15),PSTWITH            MOVE PCALC TO PRINT LINE
         BCTR  1,0                           SUBTRACT 1 FROM R1
         MVI   0(1),C'$'                     ADD $ SIGN
         AP    PTSWITH(7),PSTWITH(6)         ADD STWH TO RUNNING TOTAL
*
*    NET EMPLOYEE PAY
*
         ZAP   PCALC(10),PEMPGPAY(6)         COPY GROSS INTO CALC FIELD
         SP    PCALC(10),PFEDWITH(6)         MINUS FED WH
         SP    PCALC(10),PSTWITH(6)          MINUS STATE WH
         ZAP   PEMPNPAY(6),PCALC(10)         PACK STATE WH
         MVC   ONETPAY(15),=X'402020206B2020206B2021204B2020'
         EDMK  ONETPAY(15),PEMPNPAY          MOVE PCALC TO PRINT LINE
         BCTR  1,0                           SUBTRACT 1 FROM R1
         MVI   0(1),C'$'                     ADD $ SIGN
         AP    PTNETPAY(7),PEMPNPAY(6)       ADD NET TO RUNNING TOTAL
*
         AP    PEMPCTR(3),=PL1'1'            INCREMENT EMP COUNT BY 1
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
         XREAD RECORD,80           READ NEXT EMPLOYEE RECORD
*
         BC    B'1111',LOOP1       BRANCH TO TOP OF LOOP1 TO CHECK EOF
*
ENDLOOP1 DS    0H
*
*    PRINT TOTALS
*
         MVC   OEMPCTR(6),=X'402020202120'
         ED    OEMPCTR(6),PEMPCTR         MOVE TOTAL EMP TO PRNT
*
         MVC   OTGRPAY(16),=X'4020202020202020206B2021204B2020'
         LA    1,OTGRPAY                  PREP R1
         EDMK  OTGRPAY(16),PTGRPAY        MOVE TOTAL GROSS TO PRNT
         BCTR  1,0                        SUBTRACT 1 FROM R1
         MVI   0(1),C'$'                  ADD $ SIGN
*
         MVC   OTFWITH(16),=X'4020202020202020206B2021204B2020'
         LA    1,OTFWITH                  PREP R1
         EDMK  OTFWITH(16),PTFWITH        MOVE TOTAL FW TO PRNT
         BCTR  1,0                        SUBTRACT 1 FROM R1
         MVI   0(1),C'$'                  ADD $ SIGN
*
         MVC   OTSWITH(16),=X'4020202020202020206B2021204B2020'
         LA    1,OTSWITH                  PREP R1
         EDMK  OTSWITH(16),PTSWITH        MOVE TOTAL STW TO PRNT
         BCTR  1,0                        SUBTRACT 1 FROM R1
         MVI   0(1),C'$'                  ADD $ SIGN
*
         MVC   OTNETPAY(16),=X'4020202020202020206B2021204B2020'
         LA    1,OTNETPAY                 PREP R1
         EDMK  OTNETPAY(16),PTNETPAY      MOVE TOTAL NET TO PRNT
         BCTR  1,0                        SUBTRACT 1 FROM R1
         MVI   0(1),C'$'                  ADD $ SIGN
*
*    CALCULATE AND PRINT AVERAGES
*
* GROSS AVERAGE
         ZAP   PCALC(10),PTGRPAY(7)       COPY TOTAL GROSS INTO PCALC
*
         DP    PCALC(10),PEMPCTR(3)       DIVIDE BY EMPLOYEE COUNT
*
         MVC   AGROSPAY(18),=X'4020202020202020206B2021204B2020'
         LA    1,AGROSPAY                 PREP R1
         EDMK  AGROSPAY(18),PCALC         MOVE TO AVG GROSS
         BCTR  1,0                        SUBTRACT 1 FROM R1
         MVI   0(1),C'$'                  ADD $ SIGN
*
* FEDERAL WIHHOLDING AVERAGE
         ZAP   PCALC(10),PTFWITH(7)       COPY TOTAL FED WH INTO PCALC
*
         DP    PCALC(10),PEMPCTR(3)       DIVIDE BY EMPLOYEE COUNT
*
         MVC   ATFWITH(18),=X'4020202020202020206B2021204B2020'
         LA    1,ATFWITH                  PREP R1
         EDMK  ATFWITH(18),PCALC          MOVE TO AVG FED WH
         BCTR  1,0                        SUBTRACT 1 FROM R1
         MVI   0(1),C'$'                  ADD $ SIGN
*
* STATE WITHHOLDING AVERAGE
         ZAP   PCALC(10),PTSWITH(7)       COPY TOTAL STA WH INTO PCALC
*
         DP    PCALC(10),PEMPCTR(3)       DIVIDE BY EMPLOYEE COUNT
*
         MVC   ATSWITH(18),=X'4020202020202020206B2021204B2020'
         LA    1,ATSWITH                  PREP R1
         EDMK  ATSWITH(18),PCALC          MOVE TO AVG STATE WH
         BCTR  1,0                        SUBTRACT 1 FROM R1
         MVI   0(1),C'$'                  ADD $ SIGN
*
* NET PAY AVERAGE
         ZAP   PCALC(10),PTNETPAY(7)      COPY TOTAL NET INTO PCALC
*
         DP    PCALC(10),PEMPCTR(3)       DIVIDE BY EMPLOYEE COUNT
*
         MVC   ATNETPAY(18),=X'4020202020202020206B2021204B2020'
         LA    1,ATNETPAY                 PREP R1
         EDMK  ATNETPAY(18),PCALC         MOVE TO AVG NET PAY
         BCTR  1,0                        SUBTRACT 1 FROM R1
         MVI   0(1),C'$'                  ADD $ SIGN
*
         AP    PPAGECTR(2),=PL1'1'        INCREMENT PAGE CTR BY 1
         MVC   OPAGECTR(4),=X'4020212020' SUPRESSES LEADING 0
         ED    OPAGECTR(6),PPAGECTR       MOVE TO PRINTLINE
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
* STANDARD EXIT LINKAGE WITH RC OF 0
*
         SR    15,15            R15 = RETURN CODE OF 0
         L     13,4(,13)        POINT R13 TO CALLER'S SAVE AREA
         L     14,12(,13)       RESTORE REGISTER 14
         LM    0,12,20(13)      RESTORE R0 THRU R12
*
         BR    14               RETURN TO CALLER
*
         LTORG
*
REGSAVE  DS 18F                 PROGRAM'S REGISTER SAVE AREA
*
* PACKED DECIMAL VARIABLES
*
PFWHPCT  DC    PL4'0'      PACKED FEDERAL WITHHOLDING PERCENTAGE
PSWHPCT  DC    PL4'0'      PACKED STATE WITHHOLDING PERCENTAGE
*
PEMPCTR  DC    PL3'0'      PACKED EMPLOYEE COUNTER (MAX 999)
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
PCALC    DC    PL10'0'      USED TO CALCULATE WITHHOLDING AND AVGS
*
PTGRPAY  DC    PL7'0'      PACKED TOTAL GROSS EMPLOYEE PAY
PTFWITH  DC    PL7'0'      PACKED TOTAL FEDERAL WITHHOLDING
PTSWITH  DC    PL7'0'      PACKED TOTAL STATE WITHHOLDING
PTNETPAY DC    PL7'0'      PACKED TOTAL NET EMPLOYEE PAY
*
* OUTPUT FIELDS
*
DETAIL   DC    C'0'        CARRIAGE CONTROL
OEMPID   DS    CL9         OUTPUT FIELD FOR EMPLOYEE ID
         DC    2C' '       SPACES
OEMPNME  DS    CL25        OUTPUT FIELD FOR EMPLOYEE NAME
         DC    3C' '       SPACES
OPAYRATE DS    CL7         OUTPUT FIELD FOR PAY RATE
         DC    3C' '       SPACES
OHOURS   DS    CL7         OUTPUT FIELD FOR HOURS WORKED
         DC    4C' '       SPACES
OGROSS   DS    CL16        OUTPUT FIELD FOR GROSS PAY
         DC    5C' '       SPACES
OFEDWH   DS    CL15        OUTPUT FOR FEDERAL WITHHOLD
         DC    3C' '       SPACES
OSTAWH   DS    CL14        OUTPUT FOR STATE WITHHOLD
         DC    4C' '       SPACES
ONETPAY  DS    CL15        OUTPUT FOR NET PAY
         DC    1C' '       SPACE
*
* PAGE HEADERS
*
HEADER1  DC    C'0'
         DC    50C' '
         DC    C'STATE OF ILLINOIS NATIONAL BANK'
         DC    42C' '
         DC    C'PAGE:'
OPAGECTR DS    CL4
*
HEADER2  DC    C'0'
         DC    48C' '
         DC    C'SEMI-MONTHLY EMPLOYEE PAYROLL REPORT'
         DC    48C' '
*
* COLUMN HEADERS
*
COLHEAD1 DC    C'0'
         DC    C'EMPLOYEE   EMPLOYEE                     '
         DC    C'HOURLY     HOURS            EMPLOYEE    '
         DC    C'EMPLOYEE FEDERAL    EMPLOYEE STATE          EMPLOYEE'
*
COLHEAD2 DC    C'0'
         DC    C'ID         NAME                            PAY    '
         DC    C'WORKED           GROSS PAY         WITHHOLDING'
         DC    C'       WITHHOLDING           NET PAY'
*
COLHEAD3 DC    C'0'
         DC    C'---------  -------------------------   -------   '
         DC    C'-------     ---------------    ----------------'
         DC    C'    --------------   ---------------'
*
* SUMMARY HEADERS
*
TOTLHEAD DC    C'0'
         DC    62C' '
         DC    C'TOTALS'
         DC    65C' '
*
SUMHEAD1 DC    C'0'
         DC    6C' '
         DC    C'NUMBER OF EMPLOYEES: '
         DC    12C' '
OEMPCTR  DS    CL6
         DC    87C' '
*
SUMHEAD2 DC    C'0'
         DC    10C' '
         DC    C'TOTAL GROSS PAY:   '
OTGRPAY  DS    CL16
         DC    19C' '
         DC    C'AVERAGE GROSS PAY: '
AGROSPAY DS    CL18
         DC    32C' '
*
SUMHEAD3 DC    C'0'
         DC    C'TOTAL FEDERAL WITHHOLDING:   '
OTFWITH  DS    CL16
         DC    9C' '
         DC    C'AVERAGE FEDERAL WITHHOLDING: '
ATFWITH  DS    CL18
         DC    32C' '
*
SUMHEAD4 DC    C'0'
         DC    2C' '
         DC    C'TOTAL STATE WITHHOLDING:   '
OTSWITH  DS    CL16
         DC    11C' '
         DC    C'AVERAGE STATE WITHHOLDING: '
ATSWITH  DS    CL18
         DC    32C' '
*
SUMHEAD5 DC    C'0'
         DC    12C' '
         DC    C'TOTAL NET PAY:   '
OTNETPAY DS    CL16
         DC    21C' '
         DC    C'AVERAGE NET PAY: '
ATNETPAY DS    CL18
         DC    32C' '
*
* INPUT
*
RECORD   DS    0H
IEMPID   DS    ZL8         INPUT EMPLOYEE ID
IHRPAY   DS    ZL5         INPUT EMPLOYEE HOURLY PAY RATE
IHOURS   DS    ZL5         INPUT EMPLOYEE HOURS WORKED
IDEDUCT  DS    ZL5         INPUT EMPLOYEE DEDUCTION
IBONUS   DS    ZL5         INPUT EMPLOYEE BONUS
IEMPNME  DS    CL25        INPUT EMPLOYEE NAME
         DS    CL27
         END   PAYROLL1