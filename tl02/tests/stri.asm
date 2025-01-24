.orig x0000
	LD R0, DATA
	LD R1, PTR
	STRI R0, R1, 2
	HALT

	DATA .fill x5000
	PTR .fill x4000
.end

.orig x4000
	.fill x0010
	.fill x0020
	.fill x0030
.end
