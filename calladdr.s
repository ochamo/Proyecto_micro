AREA |.text|, CODE, READONLY, ALIGN=2
	THUMB
	REQUIRE8
	PRESERVE8
		
	EXPORT calladdr
		
calladdr
	push { lr }
	add r0, r0, #1
	blx r0
	pop { pc }
	
	end