*****************************************************************
*                                                               *
* CSCI 360-0001           ASSIGNMENT 6              SPRING 2024 *
*                                                               *
* DEVELOPER NAME: David Flowers II                              *
*       DUE DATE: 01/26/24                                      *
*                                                               *
*****************************************************************
*
ASSIGN6  CSECT
         USING ASSIGN6,15     ESTABLISH ADDRESSABILITY ON REG 15
*
         LA    10,16          GET FED WITHHOLDING PERCENT INTO R10
         LA    11,4           GET STATE WITHHOLDING PERCENT INTO R11
*
         XREAD RECORD,80      GET FIRST EMPLOYEE RECORD
*
LOOP1    BC    B'0100',ENDLOOP1  BRANCH TO ENDLOOP1 IF EOF
*
         MVC   OEMPNME(25),RECORD    SEND EMP NAME TO PRINT
         MVC   OEMPID(5),RECORD+25   SEND EMP ID TO PRINT
*
         XDECI 2,RECORD+31           GET PAY RATE INTO R2
         XDECO 2,OPAYRATE            DISPLAY PAY RATE
*
         XDECI 3,0(1)                GET HOURS
         XDECO 3,OHOURS              DISPLAY HOURS WORKED
*
GROSSPAY MR    2,2                   PAY RATE * HOURS (PRODUCT IN R3)
*
         XDECI 2,0(1)                GET DEDUCTIONS
         SR    3,2                   SUBTRACT FROM PAY
*
         XDECI 2,0(1)                GET BONUS
         AR    3,2                   ADD TO PAY
*
         XDECO 3,OGROSS              DISPLAY GROSS PAY AMT
*
WITHHOLD XDECI 2,RECORD+33           GET FED WITHHOLDING
         XDECI 6,RECORD+35           GET STATE WITHHOLDING
*
         LR    4,3                   LOAD GROSS INTO R4 FOR FEDERAL
         LR    6,3                   LOAD GROSS INTO R6 FOR STATE
*
         LR    5,10                  LOAD FED PERCENT INTO 5
         LR    7,11                  LOAD STA PERCENT INTO 7
*
         MR    4,4                   GROSS * FED WH PERCENT
         MR    6,6                   GROSS * STA WH PERCENT
*
         LR    4,5                   LOAD FED RESULT BACK INTO R4
         LR    6,7                   LOAD STA RESULT BACK INTO R6
*
         M     4,=F'1'               CLEAR OUT REGISTER
         D     4,=F'100'             DIVIDE FED BY 100
*
         M     6,=F'1'               CLEAR OUT REGISTER
         D     6,=F'100'             DIVIDE STA BY 100
*
         XDECO 5,OFEDWH              PRINT FEDERAL WITHHOLDING
         XDECO 7,OSTWH               PRINT STATE WITHHOLDING
*
         SR    3,5                   SUBTRACT FED WH FROM GROSS
         SR    3,7                   SBUTRACT STA WH FROM GROSS
*
         XDECO 3,ONETPAY
*
         XPRNT DETAIL,133     PRINT THE EMPLOYEE DETAIL RECORD
*
         XREAD RECORD,80      READ NEXT EMPLOYEE RECORD
*
         BC    B'1111',LOOP1  BRANCH TO TOP OF LOOP1 TO CHECK EOF
*
ENDLOOP1 DS    0H
*
         BCR   B'1111',14     UNCONDITIONAL RETURN TO CALLER
*
         LTORG                LITERAL ORGANIZATION
*
* THE FOLLOWING 16 LINES ARE THE DEFINITION FOR THE OUTPUT DETAIL
*   LINE FOR EACH EMPLOYEE FOR THE REPORT YOU ARE CREATING.  IT
*   IS EXACTLY 133 BYTES LONG.  EACH OUTPUT FIELD IS SEPARATED
*   BY 4 OR 5 BYTES OF EBCDIC SPACES, i.e., X'40'.
*
DETAIL   DC    C'0'   CARRIAGE CONTROL CHARACTER
OEMPNME  DS    CL25   OUTPUT FIELD FOR EMPLOYEE NAME
         DC    4C' '  SPACES
OEMPID   DS    CL5    OUTPUT FIELD FOR EMPLOYEE ID
         DC    4C' '  SPACES
OPAYRATE DS    CL12   OUTPUT FIELD FOR XDECO OF PAY RATE
         DC    4C' '  SPACES
OHOURS   DS    CL12   OUTPUT FIELD FOR XDECO OF HOURS WORKED
         DC    4C' '  SPACES
OGROSS   DS    CL12   OUTPUT FIELD FOR XDECO OF GROSS PAY AMT
         DC    4C' '  SPACES
OFEDWH   DS    CL12   OUTPUT FIELD FOR XDECO OF FEDERAL WH AMT
         DC    5C' '  SPACES
OSTWH    DS    CL12   OUTPUT FIELD FOR XDECO OF STATE WH AMT
         DC    5C' '  SPACES
ONETPAY  DS    CL12   OUTPUT FIELD FOR XDECO OF NET PAY AMT
*
*  THE FOLLOWING IS THE BUFFER FOR THE INPUT RECORD
*
RECORD   DS    CL80   BUFFER FOR EMPLOYEE RECORD READ FROM INPUT FILE
*
         END   ASSIGN6