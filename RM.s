	AREA |.text|, CODE, READONLY, ALIGN=2
	THUMB
	REQUIRE8
	PRESERVE8

	EXPORT registerModEnsamblador ; se exporta funcion realizada

registerModEnsamblador ; definicion de la funcion
	push { lr }
	cmp r0, #0 ; se compara si el valor obtenido es el indicado para saltar
	beq modifyR0
	cmp r0, #1
	beq modifyR1
	cmp r0, #2
	beq modifyR2
	cmp r0, #3
	beq modifyR3
	cmp r0, #4
	beq modifyR4
	cmp r0, #5
	beq modifyR5
	cmp r0, #6
	beq modifyR6
	cmp r0, #7
	beq modifyR7
	cmp r0, #8
	beq modifyR8
	cmp r0, #9
	beq modifyR9
	cmp r0, #10
	beq modifyR10
	cmp r0, #11
	beq modifyR11
	cmp r0, #12
	beq modifyR12
	pop {pc}
	bx lr

modifyR0 ; lugares en donde salta si se cumple la condicion
	movs r0, r1
	bx lr
	
modifyR1
	movs r1, r1
	bx lr
	
setR2
	movs r2, r1
	bx lr
	
modifyR3
	movs r3, r1
	bx lr

modifyR4
	movs r4, r1
	bx lr
	
modifyR5
	movs r5, r1
	bx lr
	
modifyR6
	movs r6, r1
	bx lr

modifyR7
	movs r7, r1
	bx lr

modifyR8
	movs r8, r1
	bx lr

modifyR9
	movs r9, r1
	bx lr

modifyR10
	movs r10, r1
	bx lr

modifyR11
	movs r11, r1
	bx lr

modifyR12
	movs r12, r1
	bx lr