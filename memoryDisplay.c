extern void ensamblador_memory_display(uint32_t *memoria_data, uint32_t start_display, uint32_t end_display);

// Memory display
char md_character[32];
uint32_t *save_MD;
uint32_t *save_MD;
int contador = 0;

void memoryDisplay(void){
	char *start_display = parameters_commands[1];
	char *end_display = parameters_commands[2];
    char *memory_display_indicador;
    long memory_display_function;
    long memory_display_function_fin;
	USART2_putSTring("Memory Display\n\r");
    //Removemos character 'x'
	quitarX(start_display);
	quitarX(end_display);
	memory_display_function = strtoul(start_display, &ptr, 16);
	memory_display_function_fin = strtoul(end_display, &ptr, 16);
	memory_display_function = memory_display_function;
	memory_display_function_fin = memory_display_function_fin;
	array_memory_display = ((memory_display_function_fin - memory_display_function) / 4) + 1;
	save_MD = (uint32_t *)malloc(sizeof(uint32_t) * array_memory_display);
    //Guardamos memoria
	memory_MD = save_MD;
    // mandamos los valores al ensamblador
	ensamblador_memory_display(save_MD, start_display, end_display);
    for(i=start_display; i<= end_display; i+=0x4){
        sprintf(md_character, "0x%08x", save_MD[contador]);
		USART2_putSTring(md_character + "\n\r");
		contador++;
    }
	// Liberaramos la memoria
	free(memory_MD);
}