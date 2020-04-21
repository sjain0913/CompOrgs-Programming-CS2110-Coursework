;;=============================================================
;;CS 2110 - Spring 2020
;;Homework 5 - Print the Vowels in a String
;;=============================================================
;;Name: Saumya Jain
;;=============================================================
;;Pseudocode (see PDF for explanation)
;;string = "TWENTY ONE TEN";
;;i = 0;
;;while(string[i] != ’\0’){
;;  if(string[i] == ’A’ || string[i] == ’E’ ||
;;  string[i] == ’I’ || string[i] == ’O’ ||
;;  string[i] == ’U’){
;;      print(string[i]);
;;  }
;;i++;
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

;INSERT CODE AT THIS LOCATION
LD R5, STRING      ; loading string adress
LDR R0, R5, 0      ; loading string's 1st char

WHILE              ; while loop (runs when char != null)
BRz END


ADD R2 , R0, -16   
ADD R2 , R2, -16
ADD R2 , R2, -16
ADD R2 , R2, -16 
ADD R2 , R2, -16    ; subtracting 60 from ASCII char, making checking its value easier

AND R3, R3, 0       ;to see if char is A
ADD R3, R2, 15

BRnp SKIPA
OUT
SKIPA

AND R3, R3, 0       ;to see if char is E
ADD R3, R2, 11    

BRnp SKIPE          
OUT
SKIPE

AND R3, R3, 0       ;to see if char is I
ADD R3, R2, 7

BRnp SKIPI
OUT
SKIPI

AND R3, R3, 0        ;to see if char is O
ADD R3, R2, 1

BRnp SKIPO
OUT
SKIPO

AND R3, R3, 0        ;testing if character is U
ADD R3, R2, -5       

BRnp SKIPU
OUT
SKIPU

    
ADD R5, R5, 1         ;incrementing i
LDR R0, R5, 0         ;loads next character in string

BR WHILE 
END

HALT

A .fill x41    ;; A in ASCII
STRING .fill x4000
.end

.orig x4000
.stringz "TWENTY ONE TEN"
.end
