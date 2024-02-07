*****************************************************************
* CSCI 360-0001           ASSIGNMENT 3C             SPRING 2024 *
*                                                               *
* DEVELOPER NAME: David Flowers II                              *
*       DUE DATE:  02/16/24                                     *
*                                                               *
*****************************************************************
ASSIGN3C CSECT
         USING ASSIGN3C,15     ESTABLISH ADDRESSABILITY ON REG 15
*
         L     2,24(,15)      LOAD STORAGE ADDR 24 INTO R2
         L     3,28(,15)      LOAD STORAGE ADDR 28 INTO R3
*
         SR    2,3            SUBTRACT R3 FROM R2
*
         ST    2,32(,15)      STORE R2 INTO ADDR 32
*
         XDUMP 32(,15),4      XDUMP ADDR 32 STORAGE
*
         BCR   B'1111',14     RETURN
         LTORG                
*
         DC    F'15'          DEFINE CONTSANT 23
         DC    F'7'           DEFINE CONSTANT 5
         DS    F              STORAGE TO HOLD ANSWER
*
         END   ASSIGN3C       END MAIN PROGRAM