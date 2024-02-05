*****************************************************************
* CSCI 360-0001           ASSIGNMENT 3B             SPRING 2024 *
*                                                               *
* DEVELOPER NAME: David Flowers II                              *
*       DUE DATE:  02/16/24                                     *
*                                                               *
*****************************************************************
ASSIGN3B CSECT
         USING ASSIGN3B,15     ESTABLISH ADDRESSABILITY ON REG 15
*
         LR    2,NUM1         LOAD NUM1 INTO R2
         LR    3,NUM2         LOAD NUM2 INTO R3
*
         SR    2,3            SUBTRACT R3 FROM R2
*
         ST    2,ANSWER       STORE R2 INTO ANSWER
*
         XDUMP ANSWER,4       XDUMP ANSWER STORAGE
*
         BCR   B'1111',14     RETURN
         LTORG                
*
NUM1     DC    F'15'          DEFINE CONTSANT 23
NUM2     DC    F'7'           DEFINE CONSTANT 5
ANSWER   DS    CL12           STORAGE TO HOLD ANSWER
*
         END   ASSIGN3B       END MAIN PROGRAM