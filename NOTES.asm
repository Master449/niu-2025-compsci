*****************************************************************
*                                                               *
* CSCI 360-0001           ASSIGNMENT 1              SPRING 2024 *
*                                                               *
* DEVELOPER NAME: David Flowers II                              *
*       DUE DATE:  01/26/24                                     *
*                                                               *
*****************************************************************
*
* - Comment every line as you write it
* - Comments are either:
*        1. Asterisk in Column 1
*        2. 1 Space after Operand
*
* - Some instructions set a condition code
*        The condition code relfects the results of the execution
*          0 Result is equal to 0
*          1 Result is less than 0
*          2 Result is greater than 0
*          3 Overflow
*     
* - RX Instructions involve D(X,B)
*        4 bytes long
*        Encoding is 4th from the bottom on p.2 on the Yellow Card
*
* - Only allowed to use registers 2 - 11
*        The rest have specific uses
*
******************** RX INSTRUCTIONS *************************
*
* copies or loads in the 4 bytes at the absolute 
* address represented by D(X,B) into R register
label    L     R,D(X,B)
*
* Stores the contents of R at the absolute address
* represented by D(X,B)
label    ST    R,D(X,B)
*
* Loads the 24-bit absolute ADDRESS represented 
* by D(X,B) into the last 3 bytes of R, also
* 0s out the first byte
label    LA    R,D(X,B)
*
* Adds the fullword value at the absolute address, 
* represnete dby D(X,B) to the value stored in R
label    A     R,D(X,B)
*
* Takes the 4 bytes from the absolute address 
* represented by D(X,B) and subtracts it from the content of R
label    S     R,D(X,B)
*
*
******************** RR INSTRUCTIONS *************************
*
* Copies the contents of R2 into R1
label    LR    R1,R2
*
* Add the contents of R2 to R1, Result is placed in R1
label    AR    R1,R2
*
* Subtracts the contents of R2 from R1
label    SR    R1,R2
*
******************** ASSIST INSTRUCTIONS *********************
*
* Used to dump the contents of GPRs or program storage
        XDUMP  ,              General Purpose Registers
        XDUMP  D(X,B),length  Program storage from D(X,B) to length
*
*
*
*label   instr op             line doc up to 71
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
