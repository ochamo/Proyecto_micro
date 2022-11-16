#include "stm32f3xx.h"                  // Device header
#include "usart_utils.h"
#include "command_utils.h"
#include "buzzer_utils.h"
#include <stdio.h>

uint32_t direccionEnviada;
uint32_t direccionRetorno;
unsigned long dataNueva;
unsigned long addressNueva;

static char *mmAddress,*mmData,*mmSize;

void MemoryModify(void){
	mmAddress = parameters_commands[1];
	mmData = parameters_commands[2];
	mmSize = parameters_commands[3];
	int size;
	sscanf(mmSize,"%d",&size);
	quitarX(mmAddress);
	quitarX(mmData);
	dataNueva = strtoul(mmData,&ptr,16);
	addressNueva = strtoul(mmAddress,&ptr,16);
	if(size==1){
		memory_size1(addressNueva,dataNueva);
	}else if(size==2){
		memory_size2(addressNueva,dataNueva);
	}else{
		memory_size4(addressNueva,dataNueva);
	}
	
}