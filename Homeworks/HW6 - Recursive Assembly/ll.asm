;; =============================================================
;; CS 2110 - Spring 2020
;; HW6 - Replace Values in Linked List
;; =============================================================
;; Name: Saumya Jain
;; ============================================================

;; In this file, you must implement the 'mult' subroutine.

;; Little reminder from your friendly neighborhood 2110 TA staff:
;; don't run this directly by pressing 'RUN' in complx, since there is nothing
;; put at address x3000. Instead, load it and use 'Debug' -> 'Simulate Subroutine
;; Call' and choose the 'replaceValueLL' label.

.orig x3000
HALT

replaceValueLL
;; See the PDF for more information on what this subroutine should do.
;;
;; Arguments of replaceValueLL: Node head, int r 
;;
;; Psuedocode:
;; replaceValueLL(Node head, int r) {
;;     if (head == null) {
;;         return head;
;;     }
;;     if (head.data == r) {
;;         head.data = 0;
;;     } else {
;;         head.data = head.data * r;
;;     }
;;     replaceValueLL(head.next, r);
;;     return head;
;; }

;; NOTE: if you need to calculate head.data * r using the mult subroutine, please make head.data be the first parameter and r be the second parameter.
;; The autograder will check if you are calling mult at appropriate times.
;; If the autograder fails you for not calling mult even though you did, try switching the arguments around.


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

; the actual linked list
LDR R0, R5, #4 ; the head
LDR R1, R5, #5
ADD R0, R0, #0
BRZ IFBRANCH1
LDR R3, R0, #1 ; head data
NOT R2, R3
ADD R2, R2, #1
ADD R2, R2, R1 ; r - head.data
BRZ IFBRANCH2
ADD R6, R6, #-2
STR R3, R6, #0 ; storing head.data
STR R1, R6, #1 ; Storing r (below head.data)
JSR mult
LDR R2, R6, #0 ; getting return value
ADD R6, R6, #3
STR R2, R0, #1 ; head.data = head.data * r

CONDITION_END_BRANCH
LDR R2, R0, #0
ADD R6, R6, #-2
STR R2, R6, #0 ; Storing head.next
STR R1, R6, #1 ; Storing r (below head.next)
JSR replaceValueLL
LDR R2, R6, #0
ADD R6, R6, #3
STR R0, R5, #3 ; Storing return
BR ENDBRANCH

IFBRANCH1
STR R0, R5, #3
BR ENDBRANCH

IFBRANCH2
AND R2, R2, #0
STR R2, R0, #1 
BR CONDITION_END_BRANCH

; Tearing stack down
ENDBRANCH
LDR R0, R6, 4
LDR R1, R6, 3
LDR R2, R6, 2
LDR R3, R6, 1
LDR R4, R6, 0 ; Restoring
ADD R6, R5, 0
LDR R5, R6, 1 
LDR R7, R6, 2
ADD R6, R6, 3
RET

;; This is a mult subroutine that you can call to multiply numbers.
;; Note that this is not the same as the one you need to implement for Part 1 of this homework;
;; the one you implement there needs to be recursive, and must support negative numbers.
;; However, you can use this subroutine for this homework question.
;; Note that this subroutine does not follow the full calling convention; however, it will work fine if you properly follow the convention on the caller's side.
mult
;; Arguments: int a, int b
ADD R6, R6, -4
STR R0, R6, 0
STR R1, R6, 1
STR R2, R6, 2
AND R0, R0, 0
LDR R1, R6, 4
LDR R2, R6, 5
BRz 3
ADD R0, R0, R1
ADD R2, R2, -1
BRp -3
STR R0, R6, 3
LDR R0, R6, 0
LDR R1, R6, 1
LDR R2, R6, 2
ADD R6, R6, 3

RET
.end


;; The following is an example of a small linked list that starts at x4000.
;; The first number (offset 0) contains the address of the next node in the linked list, or zero if this is the final node.
;; The second number (offset 1) contains the data of this node.
.orig x4000
.fill x4008
.fill 5
.end

.orig x4008
.fill 0
.fill 12
.end
