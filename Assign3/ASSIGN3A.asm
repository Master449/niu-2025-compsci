*****************************************************************
* CSCI 360-0001           ASSIGNMENT 3A             SPRING 2024 *
*                                                               *
* DEVELOPER NAME: David Flowers II                              *
*       DUE DATE:  02/16/24                                     *
*                                                               *
*****************************************************************
ASSIGN3A CSECT
         USING ASSIGN3A,15     ESTABLISH ADDRESSABILITY ON REG 15
*
         LR    2,NUM1         LOAD NUM1 INTO R2
         LR    3,NUM2         LOAD NUM2 INTO R3
*
         SR    2,3            SUBTRACT R3 FROM R2
*
         XDUMP ,              DUMP REGISTERS
*
         BCR   B'1111',14     RETURN
         LTORG                
*
NUM1     DC    F'15'          DEFINE CONTSANT 23
NUM2     DC    F'7'           DEFINE CONSTANT 5
*
         END   ASSIGN3A       END MAIN PROGRAM