;;=============================================================
;;  CS 2110 - Spring 2024
;;  Homework 6 - isPalindrome
;;=============================================================
;;  Name: Shanzeh Amirali
;;============================================================

;;  In this file, you must implement the 'isPalindrome' subroutine.
 

.orig x3000
    ;; You do not need to write anything here
    LD R6, STACK_PTR

    ;; Pushes arguments (word addr and len)
    ADD R6, R6, -2
    LEA R0, STRING
    LD R1, LENGTH
    STR R0, R6, 0
    STR R1, R6, 1
    JSR IS_PALINDROME
    LDR R0, R6, 0
    ADD R6, R6, 3
    HALT
    STACK_PTR .fill xF000
    LENGTH .fill 3                 ;; Change this to be length of STRING
    STRING .stringz "aba"	       ;; You can change this string for debugging!


;;  IS_PALINDROME **RECURSIVE** Pseudocode
;;
;;  isPalindrome(word (addr), len) { 
;;      if (len == 0 || len == 1) {
;;          return 1;
;;      } else {
;;          if (word[0] == word[len - 1]) {
;;              return IS_PALINDROME(word + 1, len - 2);
;;          } else { 
;;              return 0;
;;          }
;;      }
;;  }
;;
IS_PALINDROME ;; Do not change this label! Treat this as like the name of the function in a function header
    ;; Code your implementation for the isPalindrome subroutine here!
    ;; NOTE: Your implementation MUST be done recursively
    
    Add R6, R6, #-4     ; make space on stack
    STR R7, R6, #2      ; save return addr to stack
    STR R5, R6, #1      ; save old fp to stack
    ADD R5, R6, #0      ; make curr fp point to 1st local variable
    ADD R6, R6, #-5     ; push gen purpose regs to stack
    STR R0, R5, #-1     ; push old R0 to stack
    STR R1, R5, #-2     ; push old R1 to stack
    STR R2, R5, #-3     ; push old R2 to stack
    STR R3, R5, #-4     ; push old R3 to stack
    STR R4, R5, #-5     ; push old R4 to stack
    
    LDR R0, R5, 4 ; R0 = str addr
    LDR R1, R5, 5 ; R1 = len
    
    ADD R1, R1, 0
    BRz RETURNONE
    ADD R2, R1, #-1     ; length - 1
    BRz RETURNONE

    LDR R3, R0, #0      ; word[0]
    ADD R2, R0, R2      ; addr word[addr + length - 1]
    LDR R2, R2, #0      ; word[addr + length - 1]
    NOT R2, R2          
    ADD R2, R2, #1      ; -word[length - 1]
    
    
    
    ;if (word[0] == word[len - 1]) {
    ADD R4, R3, R2       
    BRnp RETURNZERO
    
    ADD R1, R1, #-2     ; len - 2
    ADD R0, R0, #1      ; word + 1
    ADD R6, R6, -1      ; caller buildup
    STR R1, R6, 0       ; push len
    ADD R6, R6, -1
    STR R0, R6, 0       ; push word
    JSR IS_PALINDROME
    LDR R4, R6, 0       ; caller breakdown
    STR R4, R5, 3       ; R4 = ret
    ADD R6, R6, 3
    BR STACKTEARDOWN
    
    RETURNONE
    AND R4, R4, 0
    ADD R4, R4, 1
    BR STACKTEARDOWN
    
    RETURNZERO
    AND R4, R4, 0

    
    STACKTEARDOWN STR R4, R5, 3
    LDR R4, R5, -5
    LDR R3, R5, -4
    LDR R2, R5, -3
    LDR R1, R5, -2
    LDR R0, R5, -1
    
    ADD R6, R5, 0
    LDR R5, R6, 1
    LDR R7, R6, 2
    ADD R6, R6, 3
    
    RET
.end
