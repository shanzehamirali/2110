.orig x0000
	LD R0, AA
	LD R1, BB
	STRNEXT R0, R1; mem[100] = mem[107 + -7] = 4 = PC*
	HALT

	AA .fill 107
	BB .fill -7
.end

