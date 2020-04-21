; int[] array = new int[]{1, 2, 4, 5, 6};
; int twoCounts = 0;
; int fourCounts = 0;
; for (int i = 0; i < 5; i++) { 
;    if (array[I] % 2 == 0) {
;         twoCounts++;
;    }
;    if (array[I] % 4 == 0) {
;         fourCounts++;
;    }
;  }

.ORIG	x3000

AND R0, R0, 0
AND R1, R1, 0
AND R2, R2, 0
AND R3, R3, 0
AND R4, R4, 0
AND R5, R5, 0
AND R6, R6, 0
AND R7, R7, 0


    LD R0, LENGTH
    LD R1, ARRAY
    LD R2, TWOS
    LD R3, FOURS
    LD R5, COUNTER
    
    LDR R4, R1, 0
    NOT	R0,	R0
    ADD R0, R0, 1   ;Length is now negative
LOOP

    ADD R6, R0, R5
    BRz END
    
    AND R4, R4, 0b1
    BRz TWOSUCCESSFULL
    BR AFTERTWO

    TWOSUCCESSFULL ADD R2, R2, 1
    AFTERTWO AND R4, R4, 0b11
    BRz FOURSUCCESSFULL
    BR AFTERFOUR

    FOURSUCCESSFULL R3, R3, 1
    AFTERFOUR
        ADD R1, R1, 1
        LDR R4, R1, 0
        ADD R5, R5, 1
        BR LOOP

END
ST R2, TWOS
ST R3, FOURS

HALT

LENGTH .fill 5
ARRAY .fill x5000
TWOS .fill 0
FOURS .fill 0
COUNTER .fill 0

.END

.ORIG x5000
.fill 1
.fill 2
.fill 4
.fill 5
.fill 6
.END