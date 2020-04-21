;;=============================================================
;;CS 2110 - Spring 2020
;;Homework 5 - Selection Sort
;;=============================================================
;;Name: Saumya Jain
;;=============================================================
;;Pseudocode (see PDF for explanation)
;;x = 0;                         // current swapping index in the array
;;len = length of array;
;;while(x < len - 1) {
;;  z = x;                     // index of minimum value in unsorted portion of array
;;  y = x + 1;                 // current index in array
;;  while (y < len) {
;;      if (arr[y] < arr[z]) {
;;          z = y;             // update the index of the minimum value
;;      }
;;      y++;
;;  }
;;  if (z != x) {
;;      temp = arr[x];         // perform a swap
;;      arr[x] = arr[z];
;;      arr[z] = temp;
;;  }
;;      x++;
;;}
.orig x3000

AND R0, R0, 0    ;clearing all registers
AND R1, R1, 0
AND R2, R2, 0
AND R3, R3, 0
AND R4, R4, 0
AND R5, R5, 0
AND R6, R6, 0
AND R7, R7, 0

;;PUT YOUR CODE HERE
LD R1, ARRAY ; initializing x as Array[0]
LD R4, LENGTH ; pointer to length
LOOP1
    ADD R3, R1, 0 ; z = x, start of outer loop
    ADD R2, R1, #1 ; y = x + 1

LOOP2
    ;
    LDR R6, R2, 0 ; value of Array[y]
    LDR R7, R3, 0 ; value of Array[z]
    NOT R7, R7 ; flipping bits of Array[z]
    ADD R7, R7, #1 ; adding 1 to get 2's complement
    ADD R7, R6, R7 ; subtracting arr[y] - arr[z]
    BRzp ZEROPOS ; Branching
    AND R3, R2, R2 ; put [y] into z if values unequal
ZEROPOS
    LD R6, ARRAY
    ADD R5, R6, R4
    NOT R5, R5 ; flipping bits of length
    ADD R5, R5, #1 ; adding 1 to get 2's complement
    ADD R2, R2, #1 ; iterating y
    ADD R5, R2, R5 ; y - length
    BRn LOOP2

    NOT R5, R1 ; flipping bits of x
    ADD R5, R5, #1 ; adding one to make complement
    ADD R5, R3, R5 ; z - x
    BRz EQ  ; branching
    LDR R6, R1, 0 ; x
    LDR R7, R3, 0 ; z
    STR R7, R1, 0 ; storing z into address of x
    STR R6, R3, 0 ; storing x into address of z
EQ
    LD R5, ARRAY
    ADD R5, R5, #-1 ; length - 1
    ADD R5, R5, R4
    NOT R5, R5 ; flippingbits
    ADD R5, R5, #1 ; adding one
    ADD R1, R1, #1 ; x++
    ADD R5, R1, R5 ; x + - (length - 1)
    BRn LOOP1

HALT

ARRAY .fill x4000
LENGTH .fill 7
.end

.orig x4000
.fill 4
.fill 9
.fill 0
.fill 2
.fill 9
.fill 3
.fill 10
.end
