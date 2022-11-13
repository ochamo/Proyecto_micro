//se cambio nombres de metodos y variables en donde esta un comentario con "----"

#include "stm32f3xx.h"

#include <stdio.h>
#include <string.h> // Device header

#include <stdlib.h>

#define MASK(x) (1 << x)

//se definio en ensamblador
extern void registerModEnsamblador(int posicion_deseada, unsigned long dato); //-- funcion y variables

//comando que ejecuta la funcion en especifico
void execute_registerMod(void);

// variables necesarias de execute_registerMod
char posiciones[] = "";
int registro_display_indice = 0;
char rm_temporal1;
int rm_temporal2;
char *pointer_registry;
char *dato;
static char *pointer;


void execute_registerMod(void)
{
	USART2_putSTring("Comando Register Modify");
	USART2_putSTring("\n\r");

	pointer_registry = command_line[1];
	dato = command_line[2];

    registro_display_indice = 0;
    while(registro_display_indice < getSize(pointer_registry)){
        if (pointer_registry[registro_display_indice] != 'R')
		{
			rm_temporal1 = pointer_registry[registro_display_indice];
			strncat(posiciones, &rm_temporal1, 1);
		}
        registro_display_indice = registro_display_indice + 1;
    }

	/*for (registro_display_indice = 0; registro_display_indice < getSize(pointer_registry); registro_display_indice++)
	{
		if (pointer_registry[registro_display_indice] != 'R')
		{
			rm_temporal1 = pointer_registry[registro_display_indice];
			strncat(posiciones, &rm_temporal1, 1);
		}
	}*/

	sscanf(posiciones, "%d", &rm_temporal2);

	if (rm_temporal2 >= 0 & rm_temporal2 <= 15)
	{

		unsigned long ul;
		char *sinPrefijox;
		sinPrefijox = strtok(dato, "0x");
		ul = strtoul(sinPrefijox, &pointer, 16);

		registerModifyAssembler(rm_temporal2, ul);
	}
	else
	{
		printf("El registro deseado no es aceptado! \n");
	}
}


