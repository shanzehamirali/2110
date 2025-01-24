.orig x0000
	LD R0, HLT_START
	LD R1, GOOD_DATA
	JMP R0

	HLT_START .fill xee24
	GOOD_DATA .fill 1
.end

.orig xee24
	STPCO R0, 512 ; next instruction = mem[PC*] = PC* + PCOffset11 = xee24 + 512 = xf025 = HALT
	LD R1, BAD_DATA ; !!! THIS INSTRUCTION SHOULD BECOME HALT
	HALT

	BAD_DATA .fill -1
.end
