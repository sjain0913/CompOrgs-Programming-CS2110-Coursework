;; Name: Saumya Jain
;; Timed Lab 3 Makeup
;; April 17, 2020
;; DO NOT WORRY ABOUT THE CODE BELOW (except for the checkpoint labels)
.orig x3000

HALT ; DO NOT REMOVE

STACK .fill xF000 ; NEEDED BY COMPLx, DO NOT REMOVE

HEAD  .fill x4000
EXP   .fill 2    ;exp

; Labels for checkpoints
; DO NOT MODIFY
FIRSTNODE .blkw 1 ; Checkpoint 1
FINISHEDSUM .blkw 1 ; Checkpoint 3

;; DO NOT WORRY ABOUT THE CODE ABOVE (except for the checkpoint labels)
; START OF SUM POWERS
; pseudo code down below
; int sumPowers(Node head, int exp, function func) {
;     int sum = 0;
;     while(head != Null) {
;         sum += pow(head.data, exp);
;         head = head.next;
;     }
;     return func(sum);
; }
sumPowers
; !!!!! WRITE YOUR CODE FOR THE TIMED LAB HERE !!!!!

;;initializing registers
;; messes it up plz remove
; AND R0, R0, 0
; AND R1, R1, 0
; AND R2, R2, 0
; AND R3, R3, 0
; AND R4, R4, 0
; AND R5, R5, 0
; AND R6, R6, 0
; AND R7, R7, 0

;;Stack Buildup
ADD R6, R6, #-4
STR R7, R6, #2
STR R5, R6, #1
ADD R5, R6, #0
ADD R6, R6, #-5 ; register space
STR R0, R6, #4
STR R1, R6, #3
STR R2, R6, #2
STR R3, R6, #1
STR R4, R6, #0

;;sumPowers(Node head, int exp, function func) 
;; initializing registers with values
AND R4, R4, 0    ;;R4 is sum (int sum = 0)
AND R3, R3, 0    ;;R3 is temp
LDR R2, R5, 4    ;;R2 is head address
LDR R1, R5, 5    ;;R1 is exp
LDR R0, R5, 6    ;;R0 is func)

ST R2, FIRSTNODE ;; putting the head inside R2

LOOP
    ADD R2, R2, 0
    BRz FINISH   ; checking if head is null (if it is we end)


    ADD R3, R2, 1 
    LDR R3, R3, 0 
    ADD R6, R6, -1
    ADD R6, R6, -1
    STR R3, R6, 0
    STR R1, R6, 1 

    JSR pow

    LDR R3, R6, 0
    ADD R6, R6, 1
    ADD R6, R6, 1
    ADD R6, R6, 1
    
    ; add to sum
    ADD R4, R3, R4
    LDR R3, R2, 0
    AND R2, R2, 0
    ADD R2, R3, 0
    BR LOOP
    
FINISH
    ST R4, FINISHEDSUM
    BR FUNC

; func function
FUNC
    ADD R6, R6, -1
    STR R4, R6, 0

    JSRR R0

    LDR R3, R6, 0
    ADD R6, R6, 1
    ADD R6, R6, 1
    STR R3, R5, 3
    BR TEAR

TEAR
    LDR R0, R6, #4
    LDR R1, R6, #3
    LDR R2, R6, #2
    LDR R3, R6, #1
    LDR R4, R6, #0
    ADD R6, R5, #0
    LDR R5, R6, #1
    LDR R7, R6, #2
    ADD R6, R6, #3

RET
; END SUM POWERS

; ====== HELPER SUBROUTINES ======
; pow
; multBy10
; isEven
; DO NOT MODIFY

; START POW SUBROUTINE
pow
.fill x1DBC
.fill x7F82
.fill x7B81
.fill x1BA0
.fill x1DBB
.fill x7980
.fill x7781
.fill x7582
.fill x7383
.fill x7184
.fill x6144
.fill x6345
.fill x1420

POWLOOP
.fill x18A0
.fill x127F
.fill x0406
.fill x1620

MULTLOOP
.fill x16FF
.fill x0402
.fill x1484
.fill x0FFC

DONEMULT
.fill x0FF7

DONEPOW
.fill x7543
.fill x6184
.fill x6383
.fill x6582
.fill x6781
.fill x6980
.fill x1D60
.fill x6B81
.fill x6F82
.fill x1DA3
.fill xC1C0
; END POW SUBROUTINE

; START MULT BY 10
multBy10
.fill x1DBC
.fill x7F82
.fill x7B81
.fill x1BA0
.fill x1DBB
.fill x7980
.fill x7781
.fill x7582
.fill x7383
.fill x7184
.fill x6144
.fill x1220
.fill x1000
.fill x1000
.fill x1000
.fill x1001
.fill x1001
.fill x7143
.fill x6184
.fill x6383
.fill x6582
.fill x6781
.fill x6980
.fill x1D60
.fill x6B81
.fill x6F82
.fill x1DA3
.fill xC1C0

isEven
.fill x1DBC
.fill x7F82
.fill x7B81
.fill x1BA0
.fill x1DBB
.fill x7980
.fill x7781
.fill x7582
.fill x7383
.fill x7184
.fill x6144
.fill x5021
.fill x0402
.fill x103F
.fill x0E01

EVEN
.fill x1021

END
.fill x7143
.fill x6184
.fill x6383
.fill x6582
.fill x6781
.fill x6980
.fill x1D60
.fill x6B81
.fill x6F82
.fill x1DA3
.fill xC1C0
.end

; NODES FOR TESTING
.orig x4000
.fill x4008
.fill 5
.end

.orig x4008
.fill x0
.fill 12
.end
