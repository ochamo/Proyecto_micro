AREA |.text|, CODE, READONLY, ALIGN=2
	THUMB
	REQUIRE8
	PRESERVE8
	EXTERN addressNueva
	EXTERN dataNueva
	EXPORT memory_size1
	EXPORT memory_size2
	EXPORT memory_size4
		
memory_size1
	push{lr}
	ldr r0, [r0]
	ldr r1, [r1]
	strb r1, [r0]
	bx lr
	
		
memory_size2
	push{lr}
	ldr r0, [r0]
	ldr r1, [r1]
	strh r1, [r0]
	bx lr
	

memory_size4
	push{lr}
	ldr r0, [r0]
	ldr r1, [r1]
	str r1, [r0]
	bx lr
	
	end
		