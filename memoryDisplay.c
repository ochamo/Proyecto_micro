extern void ensamblador_memory_display(uint32_t *data, uint32_t start_display, uint32_t end_display);

// Memory display
char md_character[32];
uint32_t *save_MD;
uint32_t *memory_MD;
int contador = 0;

static uint32_t res_start_end;

char *start_display;
char *end_display;
char *memory_display_indicador;
unsigned long memory_display_function;
unsigned long memory_display_function_fin;

void memoryDisplay(void){
	start_display = parameters_commands[1];
	end_display = parameters_commands[2];
    
	put_string_USART("Memory Display \n\r");
    //Removemos character 'x'
	quitarX(start_display);
	quitarX(end_display);
	memory_display_function = strtoul(start_display, &ptr, 16);
	memory_display_function_fin = strtoul(end_display, &ptr, 16);
	memory_display_function_fin = memory_display_function_fin;
	memory_display_function = memory_display_function;
	res_start_end = ((memory_display_function_fin - memory_display_function) / 4) + 1;
	save_MD = (uint32_t *)malloc(sizeof(uint32_t) * res_start_end);
    //Guardamos memoria
	memory_MD = save_MD;
    // mandamos los valores al ensamblador
	ensamblador_memory_display(save_MD, start_display, end_display);
	char i;
    for(i=start_display; i<= end_display; i+=0x4){
        sprintf(md_character, "0x%08x", save_MD[contador]);
		put_string_USART(md_character);
		put_string_USART("\n\r");
		contador++;
    }

	/* SI NO SIRVE EL FOR
		while (start_display <= end_display){
		sprintf(md_character, "0x%08x", save_MD[contador]);
		contador++;
		put_string_USART(md_character);
		put_string_USART("\n\r");
		start_display += 0x4;
	}
	
	*/
	free(memory_MD);
}