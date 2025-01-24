.ORIG x0000
OFFSET1 LDRPC R3, OFFSET2
        LDRPC R0, OFFSET1
        HALT

        FILLER1 .fill 0
        FILLER2 .fill 0
        FILLER3 .fill 0
        OFFSET2 .fill 0
.END