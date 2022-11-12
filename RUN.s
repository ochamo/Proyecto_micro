	AREA |.text|, CODE, READONLY, ALIGN=2
	THUMB
	REQUIRE8
	PRESERVE8

    EXTERN run_address;

run_address
	push { lr }
	add r0, r0, #1
	bx r0
	pop { pc }