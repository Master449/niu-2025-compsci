*****************************************************************
*                                                               *
* CSCI 360-0001           ASSIGNMENT 1              SPRING 2024 *
*                                                               *
* DEVELOPER NAME: David Flowers II                              *
*       DUE DATE:  01/26/24                                     *
*                                                               *
*****************************************************************
MAIN     CSECT
         USING MAIN,15        ESTABLISH ADDRESSABILITY ON REG 15
*
         L     2,NUM1         LOAD R2 WITH NUM1
         L     3,NUM2         LOAD R3 WITH NUM2
*
         AR    2,3            R2 = R2 + R3
*
         XDECO 2,OUTSUM       CONVERT TO OUTPUT
*        XDECI                INPUT VERSION
         XPRNT PRNTLNE,133    SEND TO PRINT BUFFER
*
         BCR   B'1111',14     RETURN
         LTORG                
*
NUM1     DC    F'23'          DEFINE CONTSANT 23
NUM2     DC    F'5'           DEFINE CONSTANT 5
OUTSUM   DS    CL12           RAW STORAGE
*
PRNTLNE  DC    C'1'
         DC    C'THE SUM OF '
*
         END   MAIN           END MAIN PROGRAM
/*
//
