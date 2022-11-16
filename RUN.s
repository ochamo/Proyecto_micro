	AREA |.text|, CODE, READONLY, ALIGN=2
	THUMB
	REQUIRE8
	PRESERVE8

    EXPORT ensamblador_run_address

ensamblador_run_address
	add r0, r0, #1
	bx r0
	
	end