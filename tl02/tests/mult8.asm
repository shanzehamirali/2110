.orig x0000
    LD R0, AA
    LD R1, BB
    LD R2, CC
    MULT8 R0, R0, R0
    MULT8 R2, R2, R2
    MULT8 R1, R1, R1
    HALT
.end
AA .fill x0000
BB .fill x0005
CC .fill xFFFF