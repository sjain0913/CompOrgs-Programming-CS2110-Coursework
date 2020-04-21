;;=============================================================
;;CS 2110 - Spring 2020
;;Homework 5 - Make elements of a Linked List into a string
;;=============================================================
;;Name: Saumya Jain
;;=============================================================
;;Pseudocode (see PDF for explanation)
;;length = LL.length;
;;curr = LL.head; //HINT: What can an LDI instruction be used for?
;;ANSWER = char[length]; //This character array will already be setup for you
;;i = 0;
;;while (curr != null) {
;;  ANSWER[i] = curr.value;
;;  curr = curr.next;
;;  i++;
;;}


.orig x3000

AND R0, R0, 0    ;clearing registers
AND R1, R1, 0
AND R2, R2, 0
AND R3, R3, 0
AND R4, R4, 0
AND R5, R5, 0
AND R6, R6, 0
AND R7, R7, 0

;; YOUR CODE GOES HERE
LD R0,LL 			;; R0 has mem at linked list
LDR R1,R0,#0		;; address of next node
ADD R0,R0,#1		;; Get mem address of length of 
LDR R0,R0,#0		;; gets value of length
AND R4,R4,#0		;; clear R4 to be a memory address iterator when putting string in


LOOP ADD R0,R0,#0 	;; this represents the looping condition
BRNZ END1			;; exits loop if conditions met
ADD R0,R0,#-1		;; decrement length when entering loop
ADD R2,R1,#1		;; gets address of value node
LDR R2,R2,#0		;; R2 hold head node value
LD R5, ANSWER		;; R5 address of answer
ADD R5,R5,R4		;; gets to the correct memory location
STR R2,R5,#0		;; mem[R5] = R2, loads R2
LDR R1,R1,#0		;; iterating R1
ADD R4,R4,#1		;; increment R4
BR LOOP

END1
ADD R5,R5,#1
LD R3, ZERO
STR R3,R5,#0

HALT

LL .fill x6000
ANSWER .fill x5000
ZERO .fill 0	; have make a label ZERO with 0 as its val
.end

.orig x4000
.fill x4008
.fill 98
.fill x400A
.fill 73
.fill x4002
.fill 103
.fill x0000 
.fill 114
.fill x4004
.fill 97
.fill x4006
.fill 116
.end

.orig x5000
.blkw 7
.end

.orig x6000
.fill x4000
.fill 6
.end
