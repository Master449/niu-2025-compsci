*****************************************************************
*                                                               *
* CSCI 360-0001           ASSIGNMENT 7              SPRING 2024 *
*                                                               *
* DEVELOPER NAME: David Flowers II                              *
*       DUE DATE: 03/29/24                                      *
*                                                               *
*****************************************************************
*
PAYROLL CSECT
*
* STANDARD ENTRY LINKAGE WITH R12 AS BASE REGISTER
*
         STM   14,12,12(13)     SAVE REGS IN CALLER'S SAVE AREA
         LR    12,15 COPY       CSECT ADDR INTO R12
         USING PAYROLL,12       ESTABLISH R12 AS THE BASE REG
         LA    14,REGSAVE       R14 POINTS TO THIS CSECT'S SAVE AREA
         ST    14,8(,13)        STORE ADDR OF THIS CSECT'S SAVE AREA
         ST    13,4(,14)        STORE ADDR OF CALLER'S SAVE AREA
         LR    13,14            POINT R13 AT THIS CSECT'S SAVE AREA
*
         XREAD RECORD,80     READ FIRST RECORD
*
LOOP1    BC    B'0100',ENDLOOP1  BRANCH TO ENDLOOP1 IF EOF
*
         MVC   OEMPNME(25),IEMPNME  MOVE EMP NAME INTO PRINT LINE
         MVC   OEMPID(5),IEMPID     MOVE EMP ID INTO PRINT LINE
*
         PACK  PHRPAY(3),IHRPAY(5)             PACK HOURLY PAY
         MVC   OPAYRATE(7),=X'402021204B2020'  EDIT PATTERN XX.XX
         ED    OPAYRATE(7),PHRPAY              MOVE PAY TO PRINT LINE
*
         PACK  PHOURS(3),IHOURS(5)             PACK HOURS WORKED
         MVC   OHOURS(7),=X'402021204B2020'    EDIT PATTERN XX.XX
         ED    OHOURS(7),PHOURS                MOVE HOURS TO PRINT LINE
*
         ZAP   PCALC(6),PHRPAY(3)   COPY HOUR PLAY INTO CALC FIELD
         MP    PCALC(6),PHOURS(3)   MULTIPLY HOURLY PAY BY HOURS WORKED
         SRP   PCALC(6),64-2,5      ROUND TO TWO DECIMAL PLACES
*
         MVC   OGROSS(15),=X'402020202020202021204B2020'  EDIT PATTERN
         ED    OGROSS(15),PCALC     MOVE GROSS TO PRINT LINE
*
         XPRNT DETAIL,133     PRINT THE EMPLOYEE RECORD
*
         XREAD RECORD,80      READ NEXT EMPLOYEE RECORD
*
         BC    B'1111',LOOP1  BRANCH TO TOP OF LOOP1 TO CHECK EOF
*
ENDLOOP1 DS    0H
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
PHRPAY   DC    PL3'0'
PHOURS   DC    PL3'0'
PCALC    DC    PL6'0'       CALCULATION FIELD
*
DETAIL   DC    C'0'    CARRIAGE CONTROL
OEMPNME  DS    CL25    OUTPUT FIELD FOR EMPLOYEE NAME
         DC    5C' '   SPACES
OEMPID   DS    CL5     OUTPUT FIELD FOR EMPLOYEE ID
         DC    5C' '   SPACES
OPAYRATE DS    CL7    OUTPUT FIELD FOR PAY RATE
         DC    5C' '   SPACES
OHOURS   DS    CL7    OUTPUT FIELD FOR HOURS WORKED
         DC    5C' '   SPACES
OGROSS   DS    CL15    OUTPUT FIELD FOR GROSS PAY
         DC    118C' ' SPACES
*
RECORD   DS    0H
IEMPNME  DS    CL25               INPUT EMPLOYEE NAME
         DS    CL1
IEMPID   DS    CL5                INPUT EMPLOYEE ID
IHRPAY   DS    ZL5                INPUT EMPLOYEE HOURLY PAY RATE
IHOURS   DS    ZL5                INPUT EMPLOYEE HOURS WORKED
         DS    CL39
         END   PAYROLL