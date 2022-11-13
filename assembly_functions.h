#ifndef ASSEMBLY_FUNCTIONS_H
#define ASSEMBLY_FUNCTIONS_H
#endif

#include <stdint.h>

// funciones que luego seran definidas en assembler.

extern void register_display_c(uint32_t *registerArray);
extern void command_register_modify(int32_t registro, uint64_t data);
extern void ensamblador_run_address(uint32_t address);

// funciones 
void clock_config(void);

void RD(void);