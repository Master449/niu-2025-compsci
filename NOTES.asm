*****************************************************************
*                                                               *
* CSCI 360-0001               NOTES                 SPRING 2024 *
*                                                               *
* DEVELOPER NAME: David Flowers II                              *
*                                                               *
*****************************************************************
*
**************************************************************
************************ BASICS ******************************
**************************************************************
*
* - Comment every line as you write it
* - Comments are either:
*        1. Asterisk in Column 1
*        2. 1 Space after Operand
*
* - Some instructions set a condition code
*     Add and Subtract Registers:
*        The condition code relfects the results of the execution
*          0 Result is equal to 0       (0)
*          1 Result is less than 0      (Negative)
*          2 Result is greater than 0   (Positive)
*          3 Overflow                   (Overflow)
*     
* - RX Instructions involve D(X,B)
*        4 bytes long
*        Encoding is 4th from the bottom on p.2 on the Yellow Card
*
* - Only allowed to use registers 2 - 11
*        The rest have specific uses
*
* - Reference Summary Quick Guide
*        MACHINE INST FORMAT p. 2. - 3
*        MACHINE INSTRUCT by Mneomic  p. 4 - 11
*        MACHINE INSTRUCTIONS By Operation Code p. 12 - 13
*        PSW (BC MODE) p. 22
*        PROGRAM INTERUPT CODES p. 23
*        CODE ASSIGNMENTS Code Tables p. 34 - 37
*
**************************************************************
****************** INSTRUCTION BASICS ************************
**************************************************************
*
* Loads mean copy value into register
* Load Address calculates D(X,B) address and stored it into a register
*        Similar to a pointer
*
* Load Address of Storage
         LA    2,NUM
*        R2 -> NUM      DC   F'33
         L     2,0(,2)
*        or
         L     2,NUM
*
* To increment in Deckers class just do
         LA    5,4(,5)       Takes the contents of R5    ,5 
*                            adds 4                      ,4
*                            and puts it in 5             5
*
* If you need to add a value between 0 and 4095
* You should use Load Address      
*
* Fastest way to zero out a register
         SR    7,7       R7 - R7 store into R7
*
* Decrement a register by 1
         BCTR  X,Y
* We are not this far though
* This is the Branch on Count To Register
*        RX gets decremented by 1
*        if the value is still > 0
*        Branch to address in Y
* If Y is 0, it doesn't branch, and only decrements
*
*
         LA    12,3
*
*
* Compare
         C     2,NUM1      
         BC    b'0010',GTHAN   
* This is equivalent to
*    if (R2 >= NUM2)
*        goto GTHAN
*
* Compare Register
         CR    2,7     
         BC    b'0010',GTHAN
*
* (the bitmask is in binary for the op code its looking for (2 in this))
*
* CC
*  0    Equal
*  1    1st < 2nd
*  2    2st > 2nd
* (the bitmask is in binary for the op code its looking for (2 in this))
*
**************************************************************
******************** ABENDS AND CRASHES **********************
**************************************************************
*
* - We should memorize S0C:
*        S0C1  Operation  Exception (Non valid instruction)
*        S0C4  Protection Exception (Valid Storage doesn't belong to you)
*        S0C5  Addressing Exception (Trying to use invalid address)
*        S0C6  Specification Exception (Load storage not on Fullword)
*        S0C7  Data Exception (Dealing invalid packed decimals in storage)
*        S0C9  Fixed Point Divide Exception
*        S0CB  Decimal Divide Exception
*
* - Good way to remember:
*        1   4      5   6
*        Old People And Snakes
*
* Appendix D of the Textbook has a good explanation of them
*
* Besides syntax errors we will run into ABENDS (like core dumps)
* Last 4 bytes of an ABEND will be the S0C code up there
* 
* After the type of ABEND:
*   First two bits are the length of instruction
*        Binary * 2 = Length
*
* Next two bits are the Condition Code
*        After an instruction sets the CC
*            NEVER set by the abending instruction
*            Check Line 14 for CC
*   
* The rest is the address of next instruction
* Figure out the length, and subtract the address of the last 3 bytes of the PSW
* 
* so lets say
*        A_ 00 10 AB
*
* A in Binary = 10 10
*        First two are the length / 2 so its length is 4
*        Second two are the Condition Code, CC is 2 (Positive)
*
* 00 10 AB are the Address of the next instruction 
*
* EXAMPLE ABEND
* 
* ADD THIS TO YELLOW CARD
*   op code begins with a 0 - 3 it is a 2 byte instruction
*   op code begins with a 4 - B it is a 4 byte instruction
*   op code begins with a C - F is a 6 byte instruction
*
*   CSECTS and LTORGS always begin on a double-word boundary (8 bytes)
*
PSW AT ABEND FFC50006 A0000030         SYSTEM = 0C6 SPECIFICATION 
* S0C6 Specification Error
* A in Binary is 1010 
* 10  - 4 byte instruction (2 in binary * 2)
* 10  - Condition code (result greater than 0, positive)
* 00030 - Instruction that would've executed
*
*       
         SR    3,5
*        SR op code from the reference summary is 1B
*        so encoded its 1B35
* You can then do
         DC    X'1B35'
* This will do exactly what you think it will do
* X meaning Hexidecimal encoded
*
**************************************************************
************************ LITERALS ****************************
**************************************************************
*
* Literals allow us to put a hardcoded value within the program
* without the need for a DC
*
               =F'32'       fullword
               =C'Hello'    for character
               =P'2.5'      for packed
               =X'01AF33'   for hexadecimal
*
* Literals get declared where the LTORG is, before any DS or DCs
* We will use F and C before spring break, and learn the others after
* Using any literals, we need BCR   B'1111',14 (We are already doing this)
* 
* Literals can be substitued for a D(X,B) address in struction
*
         A     5,=F'14'      Adds 4 to the contents of R5
         C     3,=F'4        Compare R3 with fullword of 4
*
* Stay away from literals unless specifically given directions to use them
* Compare is okay to use literal
* DO NOT use the A literal
*
*        
**************************************************************
******************** RX INSTRUCTIONS *************************
**************************************************************
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
label    LA    R,D         Loads D into R12 Like saying 3(0,0)
*
* Adds the fullword value at the absolute address, 
* represnete dby D(X,B) to the value stored in R
label    A     R,D(X,B)
*
* Takes the 4 bytes from the absolute address 
* represented by D(X,B) and subtracts it from the content of R
label    S     R,D(X,B)
*
**************************************************************
******************** RR INSTRUCTIONS *************************
**************************************************************
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
* * * * * * EVEN - ODD PAIR * * * * * * * * * * 
* Multiplies the contents of R2 from R1
label    MR    R1,R2
*
* Divides the contents of R2 from R1 (R2 is the divisor)
label    DR    R1,R2
* * * * * * * * * * * * * * * * * * * * * * * *  
*
**************************************************************
******************** SS INSTRUCTIONS *************************
**************************************************************
*
* This copies 6 bytes from Storage 1 and puts it into Storage 2
label    MVC   S1(6),S2     
*
* 
*
**************************************************************
******************** ASSIST INSTRUCTIONS *********************
**************************************************************
*
* Used to dump the contents of GPRs or program storage
        XDUMP  ,              General Purpose Registers
        XDUMP  D(X,B),length  Program storage from D(X,B) to length
*       This will dump at (or exactly) the preceding 32bit boundary
*
* Used to read an input. Reads length of bytes starting at D(X,B)
* the length is usually 80 in this class
label    XREAD D(X,B),length
*        CC = 0 Sucessful Read
*        CC = 1 End-of-file reached
*
* Used to print a line of output. Length is usually 133
label    XPRNT D(X,B),length
*        First char of print defined is used to indicate carriage control
*        space    single spacing    C' '
*        zero     double spacing    C'0'
*        hyphen   triple spacing    C'-'
*        1        new page          C'1'
*
* Used to conver a number from itws char to its binary representation
label    XDECI   R,D(X,B)
*        Stops scanning for digits when a space is reached
*        First cahracter might be a digit, + or -
*
* 
*        XDECO
*
**************************************************************
******************** EXAMPLE PROGRAM *************************
**************************************************************
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
OUTSUM   DS    F              RAW STORAGE
*
PRNTLNE  DC    C'1'
         DC    C'THE SUM OF '
*
         END   MAIN           END MAIN PROGRAM
*
*
*
*
* Heres a basic while loop
         XREAD RECORD,80
LOOP1    BC    B'0111',ENDLOOP1
*
         XREAD RECORD,80
         BC    B'1111',LOOP1
ENDLOOP1 DS    0H             A GOOD WAY TO HAVE A LABEL WITHOUT INSTRU
*
*
*
*
* Somewhere in storage RECORD is stored
RECORD   DS    CL80           CHAR BLANK 80
        
         SR    3,5
*        SR op code from the reference summary is 1B
*        so encoded its 1B35
* You can then do
         DC    X'1B35'
* This will do exactly what you think it will do
* X meaning Hexidecimal encoded
*
*
*
*
* XPRNT EXAMPLE
         XPRNT PRNTLINE,133
* MORE CODE 
PRNTLINE DC    C' '      SINGLE SPACED CARRIAGE CONTROL
         DC    CL17'NUM1 IS EQUAL TO '
ONUM1    DS    CL12      12 BYTE OUTPUT FOR NUM1
         DC    5C' '     FIVE SPACES
         DC    CL17'NUM2 IS EQUAL TO'
ONUM2    DS    CL12      12 BYTE OUTPUT FOR NUM2
         DC    69C' '    69 SPACES FOR REMAINDER OF LINE


* CSECT MAIN LTORG END <- does not execute
* Storage from the top to bottom, All in Hex 
*  EXAMPLE DECODING
* LOCAT  INSTRUCTION  REG INDEX REG  DISPLACEMENT
* 00000A 5A           70  80         00      
* IGNORE A            7   8          0
*        A    7,0(,8)

**************************************************************
******************** MULTIPLICATION **************************
**************************************************************
* This is on the midterm
* When doing binary multiplication and division we need the
*    even-odd pair of registers
*  0 & 1   or   2 & 3  etc
*
* First Operand is ALWAYS an even number
* Second Operand is ALWAYS an odd number
*
* For the R instructions of M, MR, D, DR the second operand is the divisor
*
************ RX MULTIPLY ************
         LA    3,15        PUT THE VALUE YOU WANT INTO ODD (15)
         M     2,MULT      15 TIMES 3
*                          R3 NOW CONTAINS 0000002D (45)
*
*                    00000000 0000002D
*                       R2       R3
MULT     DC    F'3'
*
************ RR MULTIPLY ************
         LA    2,3         3 INTO R2
         LA    3,15        PUT THE VALUE YOU WANT INTO ODD (15)
         MR    2,2         15 TIMES 3 INTO R3
*
*                    00000000 0000002D
*                       R2       R3
*
         

