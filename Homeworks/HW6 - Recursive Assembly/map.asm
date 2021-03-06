;;=======================================
;; CS 2110 - Spring 2019
;; HW6 - Map Function to Array
;;=======================================
;; Name: Saumya Jain
;;=======================================

;; In this file, you must implement the 'map' subroutine.

;; Little reminder from your friendly neighborhood 2110 TA staff:
;; don't run this directly by pressing 'RUN' in complx, since there is nothing
;; put at address x3000. Instead, load it and use 'Debug' -> 'Simulate Subroutine
;; Call' and choose the 'map' label.


.orig x3000
HALT

map
;; See the PDF for more information on what this subroutine should do.
;;
;; Arguments of map: Array A, int len, function func
;; Array A is a number representing the address of the first element in the array. If the array starts at x4000, then A will be the number x4000.
;; int len is the length of the array. Recall that arrays are not null-terminated like strings, so you must use the length to know when to stop modifying the array.
;; function func is the address of the function you should call. What function can you use to jump to a subroutine at this address?
;;
;; Psuedocode:
;; map(Array A, int len, function func) {
;;     for(i = 0; i < len; i++) {
;;         A[i] = func(A[i]);
;;     }
;;     return A;
;; }


;; YOUR CODE HERE
; Setting up stack
ADD R6, R6, #-4
STR R7, R6, #2 ; Storing RA
STR R5, R6, #1 ; Store old FP
ADD R5, R6, #0 ; Set new FP
ADD R6, R6, #-5 ; register space
STR R0, R6, #4
STR R1, R6, #3
STR R2, R6, #2
STR R3, R6, #1
STR R4, R6, #0 ; Store registers

; the actual map
LDR R0, R5, #4 ; Array address
LDR R1, R5, #5 ; Lengty
LDR R2, R5, #6
LOOP
ADD R1, R1, #-1
BRN LOOP_END_BRANCH
ADD R3, R0, R1
LDR R4, R3, #0 ; A[i]
ADD R6, R6, #-1
STR R4, R6, #0 ; Store A[i]
JSRR R2

LDR R4, R6, #0 ; return value
ADD R6, R6, #2
STR R4, R3, #0
BR LOOP

LOOP_END_BRANCH
STR R0, R5, #3
BR ENDBRANCH

; Tearing down stack
ENDBRANCH
LDR R0, R6, 4
LDR R1, R6, 3
LDR R2, R6, 2
LDR R3, R6, 1
LDR R4, R6, 0
ADD R6, R5, 0
LDR R5, R6, 1
LDR R7, R6, 2
ADD R6, R6, 3


RET

; Needed by Simulate Subroutine Call in complx
STACK .fill xF000
.end

;; The following block gives an example of what the passed-in array may look like.
;; Note that this will not necessarily be the location of the array in every test case.
;; The 'A' parameter will be the address of the first element in the array (for example, x4000).
.orig x4000
    .fill 6
	.fill 2
	.fill 5
	.fill 8
	.fill 3
.end

;; The following functions are possible functions that may be called by the map function.
;; Note that these functions do not do the full calling convention on the callee's side.
;; However, they will work perfectly fine as long as you follow the convention on the caller's side.
;; Do not edit these functions; they will be used by the autograder.
.orig x5000	;; double
	ADD R6, R6, -2
	STR R0, R6, 0
	LDR R0, R6, 2
	ADD R0, R0, R0
	STR R0, R6, 1
	LDR R0, R6, 0
	ADD R6, R6, 1
	RET
.end
.orig x5100 ;; negate
	ADD R6, R6, -2
	STR R0, R6, 0
	LDR R0, R6, 2
	NOT R0, R0
	ADD R0, R0, 1
	STR R0, R6, 1
	LDR R0, R6, 0
	ADD R6, R6, 1
	RET
.end
.orig x5200 ;; increment
	ADD R6, R6, -2
	STR R0, R6, 0
	LDR R0, R6, 2
	ADD R0, R0, 1
	STR R0, R6, 1
	LDR R0, R6, 0
	ADD R6, R6, 1
	RET
.end
.orig x5300 ;; isOdd
	ADD R6, R6, -2
	STR R0, R6, 0
	LDR R0, R6, 2
	AND R0, R0, 1
	STR R0, R6, 1
    LDR R0, R6, 0
	ADD R6, R6, 1
	RET
.end
.orig x5400 ;; decrement
	ADD R6, R6, -2
	STR R0, R6, 0
	LDR R0, R6, 2
	ADD R0, R0, -1
	STR R0, R6, 1
	LDR R0, R6, 0
	ADD R6, R6, 1
	RET
.end
