***************************************************************
*                                                             *
* CSCI 360-1              ASSIGNMENT 5            SPRING 2024 *
*                                                             *
*   PROGRAMMER NAME: DAVID FLOWERS II                         *
*                                                             *
*          DATE DUE: 03/01/2024                               *
*                                                             *
* MAIN PROGRAM NAME: ASSIGN5                                  *
*                                                             *
*          FUNCTION: DECODING EXERCISE FROM A RAN PROGRAM     *
*                                                             *
***************************************************************
ASSIGN5  CSECT
         USING ASSIGN5,15    ESTABLISH ADDRESSABILITY ON REG 15
*
         LA    4,23
         L     5,60(0,15)
         LR    2,4
         AR    2,5
         ST    2,64(0,15)
         LR    7,5
         LR    6,4
         MR    6,6
         ST    7,68(0,15)
         LR    9,4
         M     4,80(0,15)
         DR    4,9
         ST    4,72(0,15)
         ST    5,76(0,15)
         XDUMP ASSIGN5,84
*
         LTORG               LITERAL ORGANIZATION
*
         DC    H'2046'
         DS    2F
         DC    F'101'
         DS    2F
         DC    F'64'
         DC    F'9'
         DC    F'1'
*
         END ASSIGN5