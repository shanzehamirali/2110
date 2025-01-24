.orig x0000
	LD R0, AA
	LD R1, BB
	LD R2, CC
	NAND R3, R0, R2
	NAND R4, R1, R2
	NAND R5, R0, R1
	HALT
	AA .fill x7E31
	BB .fill xF0A0
	CC .fill xFFFF
.end

