
unsigned long run_addr_dir;

extern void ensamblador_run_address(uint32_t address);


void RunAddress(void){
    char *RUN_ADDR= parameters_commands[1];
    char *run_address_indicador;
    long run_addr_dir
	USART2_putSTring("Run Address\n\r");
	//Removemos Character
	character_remove(RUN_ADDR, 'x');
	run_addr_dir = strtoul(RUN_ADDR, &run_address_indicador, 16);
	//Mandamos run_addr_dir a funcion en ensamblador
	ensamblador_run_address(run_addr_dir);
}