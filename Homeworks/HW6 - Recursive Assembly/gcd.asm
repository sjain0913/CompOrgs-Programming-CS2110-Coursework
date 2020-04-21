;;=======================================
;; CS 2110 - Spring 2019
;; HW6 - Recursive Greatest Common Denominator
;;=======================================
;; Name: Saumya Jain
;;=======================================

;; In this file, you must implement the 'gcd' subroutine.

;; Little reminder from your friendly neighborhood 2110 TA staff:
;; don't run this directly by pressing 'RUN' in complx, since there is nothing
;; put at address x3000. Instead, load it and use 'Debug' -> 'Simulate Subroutine
;; Call' and choose the 'gcd' label.


.orig x3000
HALT

gcd
;; See the PDF for more information on what this subroutine should do.
;;
;; Arguments of GCD: integer a, integer b
;;
;; Psuedocode:
;; gcd(int a, int b) {
;;     if (a == b) {
;;         return a;
;;     } else if (a < b) {
;;         return gcd(b, a);
;;     } else {
;;         return gcd(a - b, b);
;;     }
;; }


;; YOUR CODE HERE
; Setting up the STACK
ADD R6, R6, #-4 ; space for RV, RA, old FP, and 1st local
STR R7, R6, #2 ; Store RA
STR R5, R6, #1 ; Store old FP
ADD R5, R6, #0 ; Set new FP
ADD R6, R6, #-5 ; Space for registers
STR R0, R6, #4
STR R1, R6, #3
STR R2, R6, #2
STR R3, R6, #1
STR R4, R6, #0 ; Store registers

; GCD
LDR R0, R5, #4
LDR R1, R5, #5 ;Extract args
NOT R2, R1
ADD R2, R2, #1
ADD R2, R0, R2 ; A-B
BRZ IFBRANCH1
BRN IFBRANCH2

ADD R6, R6, #-2
STR R2, R6, #0 ; Store A - B
STR R1, R6, #1 ; Store B (below A-B)
JSR gcd ; gcd(A-B, B)
LDR R2, R6, #0 ; Get the return value
ADD R6, R6, #3
STR R2, R5, #3 ; Store return value
BR ENDBRANCH

IFBRANCH1
STR R0, R5, #3
BR ENDBRANCH

IFBRANCH2
ADD R6, R6, #-2 ;  Room for args
STR R1, R6, #0 ; Store B
STR R0, R6, #1 ; Store A (below B)
JSR gcd ; gcd(B, A)
LDR R2, R6, #0 ; Get the return value
ADD R6, R6, #3
STR R2, R5, #3 ;; Store return value
BR ENDBRANCH


;Tearing down stack
ENDBRANCH
LDR R0, R6, 4
LDR R1, R6, 3
LDR R2, R6, 2
LDR R3, R6, 1
LDR R4, R6, 0 ; Restoring registers
ADD R6, R5, 0
LDR R5, R6, 1
LDR R7, R6, 2 ; Store return address
ADD R6, R6, 3

RET

; Needed by Simulate Subroutine Call in complx
STACK .fill xF000
.end
