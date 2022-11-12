static char *RUN_ADDR;

unsigned long run_addr_dir;

extern void ensamblador_run_address(uint32_t address);


void RunAddress(void){
	USART2_putSTring("Run Address\n\r");
	RUN_ADDR = parameters_commands[1];
	//Removemos Character
	character_remove(RUN_ADDR, 'x');
	run_addr_dir = strtoul(RUN_ADDR, &pointer, 16);
	//Mandamos run_addr_dir a funcion en ensamblador
	ensamblador_run_address(run_addr_dir);
}