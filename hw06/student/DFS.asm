;;=============================================================
;;  CS 2110 - Spring 2024
;;  Homework 6 - DFS
;;=============================================================
;;  Name: Shanzeh Amirali
;;============================================================

;;  In this file, you must implement the 'SET_VISITED', 'IS_VISITED', and 'DFS' subroutines.


.orig x3000
    ;; You do not need to write anything here
    LD R6, STACK_PTR

    ;; Pushes arguments (address of node 1, target node 5)
    ADD R6, R6, -1
    AND R1, R1, 0
    ADD R1, R1, 5
    STR R1, R6, 0
    ADD R6, R6, -1
    LD R1, STARTING_NODE_ADDRESS
    STR R1, R6, 0
    JSR DFS
    LDR R0, R6, 0
    ADD R6, R6, 3
    HALT

    STACK_PTR .fill xF000
    STARTING_NODE_ADDRESS .fill x6110
    VISITED_VECTOR_ADDR .fill x4199 ;; stores the address of the visited vector.

;;  SET_VISITED Pseudocode

;; Parameter: The address of the node
;; Updates the visited vector to mark the given node as visited

;;  SET_VISITED(addr node) {
;;      visited = mem[mem[VISITED_VECTOR_ADDR]]; LDI
;;      data = mem[node];
;;      mask = 1;
;;      while (data > 0) {
;;          mask = mask + mask;
;;          data--;
;;      }
;;      mem[mem[VISITED_VECTOR_ADDR]] = (visited | mask); //Hint: Use DeMorgan's Law! -(-visited && -mask)
;;  }

SET_VISITED ;; Do not change this label! Treat this as like the name of the function in a function header
;; Code your implementation for the SET_VISITED subroutine here!
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
    
    LDR R0, R5, #4   ; R0 = start_node_addr
    LDI R1, VISITED_VECTOR_ADDR ; visted = MEM[MEM[VISITED_ADDR]
    LDR R2, R0, #0   ; R2 = mem[node]
    
    AND R3, R3, #0
    ADD R3, R3, 1   ; R3 = mask = 1
    
    WHILE
    ADD R2, R2, #0   ; while data > 0
    BRnz SET_END
    ADD R3, R3, R3  ; mask = mask + mask;
    ADD R2, R2, -1    ; data--
    BR WHILE
    
    SET_END
    AND R2, R2, #0
    NOT R2, R1 ; ~visited
    NOT R3, R3 ; ~mask
    
    AND R4, R4, 0
    AND R4, R3, R2 ; ~visited & ~mask
    NOT R4, R4 ; ~(visited & ~mask)
    STI R4, VISITED_VECTOR_ADDR
    
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


;;  IS_VISITED Pseudocode

;; Parameter: The address of the node
;; Returns: 1 if the node has been visited, 0 if it has not been visited

;;  IS_VISITED(addr node) {
;;       visited = mem[mem[VISITED_VECTOR_ADDR]];
;;       data = mem[node];
;;       mask = 1;
;;       while (data > 0) {
;;           mask = mask + mask;
;;           data--;
;;       }
;;       return (visited & mask) != 0;
;;   }

IS_VISITED ;; Do not change this label! Treat this as like the name of the function in a function header
;; Code your implementation for the IS_VISITED subroutine here!
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
    
    LDR R0, R5, 4   ; R0 = start_node_addr
    LDI R1, VISITED_VECTOR_ADDR
    LDR R2, R0, 0   ; R2 = data
    
    AND R3, R3, 0
    ADD R3, R3, 1   ; R3 = mask = 1
    
    VISITED_WHILE
    ADD R2, R2, 0   ; while data > 0
    BRnz VISITED_END
    ADD R3, R3, R3  ; mask = mask + mask;
    ADD R2, R2, -1    ; data--
    BR VISITED_WHILE  
    
    VISITED_END
    AND R4, R4, 0
    AND R4, R3, R1
    BRz ZERO
    AND R4, R4, 0
    ADD R4, R4, #1
    BR RETURN
    
    ZERO
    AND R4, R4, 0
    
    RETURN
    STR R4, R5, 3
    
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



;;  DFS Pseudocode (see PDF for explanation and examples)

;; Parameters: The address of the starting (or current) node, the data of the target node
;; Returns: the address of the node (if the node is found), 0 if the node is not found

;;  DFS(addr node, int target) {
;;        SET_VISITED(node);
;;        if (mem[node] == target) {
;;           return node;
;;        }
;;        result = 0;
;;        for (i = node + 1; mem[i] != 0 && result == 0; i++) {
;;            if (! IS_VISITED(mem[i])) {
;;                result = DFS(mem[i], target);
;;            }
;;        }       
;;        return result;
;;  }

DFS ;; Do not change this label! Treat this as like the name of the function in a function header
    ;; Code your implementation for the DFS subroutine here!

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
    
    LDR R0, R5, #4 ; R0 = start
    LDR R1, R5, #5 ; R1 = target
    

    ADD R6, R6, #-1
    STR R0, R6, #0  ; push start
    JSR SET_VISITED 
    ADD R6, R6, #2 
    
    ; if (mem[node] == target) {
    LDR R2, R0, #0 ; mem[node]
    NOT R3, R1
    ADD R3, R3, #1 ; -target
    ADD R3, R2, R3
    BRnp ELSE
    
    ; return node;
    STR R0, R5, #3  ; store node 
    BR TEARDOWN
        
    ELSE
    ;result = 0;
    AND R3, R3, #0
    STR R3, R5, #-1
    
    ;for (i = node + 1; mem[i] != 0 && result == 0; i++) {
    ADD R4, R0, #1 ; i = node + 1
    WHILE1 
    LDR R2, R4, #0 ; mem[i]
    BRz FINISH
    ADD R3, R3, #0
    BRnp FINISH 
            
    ;if (! IS_VISITED(mem[i])) { 
    ADD R6, R6, #-1 
    STR R2, R6, #0  ; push mem[i]
    JSR IS_VISITED
    LDR R1, R6, #0
    ADD R6, R6, #2  ; caller breakdown
    ADD R1, R1, #-1
    NOT R1, R1
    ADD R1, R1, #1
    ;If true -> false end
    BRz ENDIF 
            
    ; result = DFS(mem[i], target);
    ADD R6, R6, #-2 
    STR R2, R6, #0      ; push mem[i]
    LDR R1, R5, #5      
    STR R1, R6, #1      ; PUSH TARGET
    JSR DFS
    LDR R3, R6, #0
    ADD R6, R6, #3
    ENDIF
    ADD R4, R4, #1      ; i++
    BR WHILE1
    FINISH  
    
    
    STR R3, R5, #3 
    
    TEARDOWN
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
;; Assuming the graphs starting node (1) is at address x6100, here's how the graph (see below and in the PDF) is represented in memory
;;
;;         0      3
;;          \   / | \
;;            4   1 - 2 
;;             \ /    |
;;              5  -  6
;;

.orig x4199
    .fill 0 ;; visited set will be at address x4199, initialized to 0
.end

.orig x6110         ;; node 1 itself lives here at x6110
    .fill 1         ;; node.data (1)
    .fill x6120     ;; node 2 lives at this address
    .fill x6130     ;; node 3 lives at this address
    .fill x6150     ;; node 5 lives at this address   
    .fill 0
.end

.orig x6120	        ;; node 2 itself lives here at x6120
    .fill 2         ;; node.data (2)
    .fill x6110     ;; node 1 lives at this address
    .fill x6130     ;; node 3 lives at this address
    .fill x6160     ;; node 6 lives at this address
    .fill 0
.end

.orig x6130	        ;; node 3 itself lives here at x6130
    .fill 3         ;; node.data (3)
    .fill x6110     ;; node 1 lives at this address
    .fill x6120     ;; node 2 lives at this address
    .fill x6140     ;; node 4 lives at this address
    .fill 0
.end

.orig x6140	        ;; node 4 itself lives here at x6140
    .fill 4         ;; node.data (4)
    .fill x6100     ;; node 0 lives at this address
    .fill x6130     ;; node 3 lives at this address
    .fill x6150     ;; node 5 lives at this address
    .fill 0
.end

.orig x6100         ;; node 0 itself lives here at x6000
    .fill 0         ;; node.data (0)
    .fill x6140     ;; node 4 lives at this address
    .fill 0
.end

.orig x6150	        ;; node 5 itself lives here at x6150
    .fill 5         ;; node.data (5)
    .fill x6110     ;; node 1 lives at this address
    .fill x6140     ;; node 4 lives at this address
    .fill x6160     ;; node 6 lives at this address
    .fill 0
.end

.orig x6160	        ;; node 6 itself lives here at x6160
    .fill 6         ;; node.data (6)
    .fill x6120     ;; node 2 lives at this address
    .fill x6150     ;; node 5 lives at this address
    .fill 0
.end
 


