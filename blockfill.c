#include "stm32f3xx.h"

#include <stdio.h>
#include <string.h> // Device header

#include <stdlib.h>

#define MASK(x) (1 << x)

//comando que ejecuta la funcion en especifico
void execute_blockFill(void);

// variables necesarias de execute_blockFill
static char *bf_start;
static char *bf_end;
static char *bf_data;
static char *bf_size;
int size_bf2 = 4;
unsigned long start_bfLong;
unsigned long end_bfLong;
unsigned long data_bfLong;


void execute_blockFill()
{

	USART2_putSTring("Block Fill \n\r");

    //obtencion de la linea de comandos
    bf_data = parameters_command[3];
	bf_size = parameters_command[4];
	bf_start = parameters_command[1];
	bf_end = parameters_command[2];
	
    //hace uso de metodo implementado "helpers"
	removeChar(bf_start);
	start_bfLong = strtoul(bf_start, &pointer, 16);

	removeChar(bf_end);
	end_bfLong = strtoul(bf_end, &pointer, 16);

	removeChar(bf_data);
	data_bfLong = strtoul(bf_data, &pointer, 16);
    //hace uso de metodo implementado "helpers"

	sscanf(bf_size, "%d", &size_bf2);

    if(start_bfLong > end_bfLong ){
        return;
    }else if(start_bfLong < 0x20000000){
        return;
    }else if(start_bfLong > 0x20009FFF){
        return;
    }else if(end_bfLong > 0x20009FFF){
        return;
    }


    for(i=start_bfLong; i <= end_bfLong; i = i + 4){
        startAddress = i;
		returnAddress = data_bfLong;
		if (size_bf2 == 1)
		{
			memory_size1(i, data_bfLong);
		}
		else if (size_bf2 == 2)
		{
			memory_size2(i, data_bfLong);
		}
		else if (size_bf2 == 4)
		{
			memory_size4(i, data_bfLong);
		}
    }
}