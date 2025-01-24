;;=============================================================
;;  CS 2110 - Spring 2024
;;  Homework 6 - GCD
;;=============================================================
;;  Name: 
;;============================================================

;;  In this file, you must implement the 'MOD' and 'GCD' subroutines.

.orig x3000
    ;; You do not need to write anything here
    LD R6, STACK_PTR

    ;; Pushes arguments A and B
    ADD R6, R6, -2
    LD R1, A
    STR R1, R6, 0
    LD R1, B
    STR R1, R6, 1 
    JSR GCD
    LDR R0, R6, 0
    ADD R6, R6, 3
    HALT

    STACK_PTR   .fill xF000
    ;; You can change these numbers for debugging!
    A           .fill 10
    B           .fill 4


;;  MOD Pseudocode (see PDF for explanation and examples)   
;;  
;;  MOD(int a, int b) {
;;      while (a >= b) {
;;          a -= b;
;;      }
;;      return a;
;;  }

MOD ;; Do not change this label! Treat this as like the name of the function in a function header
    ;; Code your implementation for the MOD subroutine here!
    
    ADD R6, R6, #-4 ; Push 4 spaces on stack for return value, old R7, old R5, and one local var
    STR R7, R6, #2  ; Save the return address --> old R7
    STR R5, R6, #1  ; Save the old frame pointer --> old R5
    ADD R5, R6, #0  ; FP = SP
    ADD R6, R6, #-5 ; Push 5 spaces (going to back up regs now)
    STR R0, R5, #-1 ; Save register 0
    STR R1, R5, #-2 ; Save register 1
    STR R2, R5, #-3 ; Save register 2
    STR R3, R5, #-4 ; Save register 3
    STR R4, R5, #-5 ; Save register 4

    LDR R0, R5, 5 ; R0 = b
    LDR R1, R5, 4 ; R1 = a
    
    
    NOT R0, R0
    ADD R0, R0, #1 ; -b
    
    WHILE ADD R2, R1, R0
    BRn END
    ADD R1, R1, R0
    BR WHILE
    
    END
    STR R1, R5, 3
    
    LDR R0, R5, #-1 ;Restore reg 0
    LDR R1, R5, #-2 ;Restore reg 1
    LDR R2, R5, #-3 ;Restore reg 2
    LDR R3, R5, #-4 ;Restore reg 3
    LDR R4, R5, #-5 ;Restore reg 4
    ADD R6, R5, 0   ;Restore SP         sets SP to FP effectively popping registers
    LDR R5, R6, 1   ;Restore FP
    LDR R7, R6, 2   ;Restore RA
    ADD R6, R6, 3   ;Pop RA, FP, LV1


    RET


;;  GCD Pseudocode (see PDF for explanation and examples)
;;
;;  GCD(int a, int b) {
;;      if (b == 0) {
;;          return a;
;;      }
;;        
;;      while (b != 0) {
;;          int temp = b;
;;          b = MOD(a, b);
;;          a = temp;
;;      }
;;      return a;
;;  }

GCD ;; Do not change this label! Treat this as like the name of the function in a function header
    ;; Code your implementation for the GCD subroutine here!
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
    
    LDR R1, R5, 4 ; R1 = a
    LDR R0, R5, 5 ; R0 = b
    
    ;if (b == 0) { 
    ADD R0, R0, #0
    BRz STACKTEARDOWN
    
    ;while (b != 0) {
    GCDWHILE ADD R0, R0, 0
    BRz STACKTEARDOWN
    
    ADD R3, R0, 0 ; int temp = b
    ADD R6, R6, #-1 
    STR R0, R6, 0 ; push b
    
    ADD R6, R6, #-1
    STR R1, R6, 0 ; push a
    
    JSR MOD
    
    LDR R0, R6, 0 ; B = MOD(A, B)
    ADD R6, R6, 3 ; pop return value
    
    ADD R1, R3, 0 ; a = temp
    BR GCDWHILE
    
    STACKTEARDOWN
    STR R1, R5, 3
    
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