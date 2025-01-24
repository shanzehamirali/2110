.ORIG x0000
    LD R0, NUM1
    LD R5, NUM2
    SETPC R0, R5

    NUM1 .fill x3002
    NUM2 .fill -1
.END

.ORIG x3001
    HALT
.END