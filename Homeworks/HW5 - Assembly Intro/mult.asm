;;=============================================================
;;CS 2110 - Spring 2020
;;Homework 5 - Iterative Multiplication
;;=============================================================
;;Name: Saumya Jain
;;=============================================================
;;Pseudocode (see PDF for explanation)
;;a = (argument 1);
;;b = (argument 2);
;;ANSWER = 0;
;;while (b > 0) {
;;  ANSWER = ANSWER + a;
;;  b--;
;; }
;; note: when the while-loop ends, the value stored at ANSWER is a times b.

.orig x3000

AND R0, R0, 0    ;clearing registers
AND R1, R1, 0
AND R2, R2, 0
AND R3, R3, 0
AND R4, R4, 0
AND R5, R5, 0
AND R6, R6, 0
AND R7, R7, 0

;;YOUR CODE GOES HERE
        LD R1, A    ;Loading A
        LD R2, B    ;Loading B
        AND R3, R3, #0
        
        

AGAIN   ADD R3, R3, R1      ;changing value of answer to answer + A
        ADD R2, R2, #-1     ;decrment B by 1 as loop condition
        BRP AGAIN           ;causes the loop
        ST R3, ANSWER       ;storing value of answer

HALT

A   .fill 5
B   .fill 15

ANSWER .blkw 1

.end
