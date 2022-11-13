#include "stm32f3xx.h"                  // Device header
#include "usart_utils.h"
#include "command_utils.h"
#include <stdio.h>

//Arreglo de registros
static uint32_t registros[15];
char datos_registros[32];

// Para la lectura de los comandos.
volatile static char input;
static char tokens[64];
// 5 posiciones porque el comando más largo ocupa 5 posiciones.
static char *parameters_commands[5] = {" ", " ", " ", " ", " "};
static uint32_t command_counter;
static uint32_t isCarriageReturn = 0;

void clock_config(void);

// Configuracion a 64Mhz
void clock_config() {
	RCC->CFGR |= 0xE<<18;
	FLASH->ACR |= 0x2;
	RCC->CR |= RCC_CR_PLLON;
	while (!(RCC->CR & RCC_CR_PLLRDY));	
	RCC->CFGR |= 0x402;
	while (!(RCC->CFGR & RCC_CFGR_SWS_PLL));
	SystemCoreClockUpdate();
}

void setup_USART(uint32_t baudrate) {
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
	RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
	
	GPIOA->MODER |= (0x2 << 4) | (0x2 << 6); // Configurando PA2 y PA3
	GPIOA->AFR[0] |= (0x7 << 8); // PA2 TX
	GPIOA->AFR[0] |= (0x7 << 12);	// PA3 RX
	
	// Baud rate register
	//uint32_t round_result =  (uint32_t) ((SystemCoreClock/2)/baudrate); // (64Mhz/2)/baudrate
	USART2->BRR = 277;
	USART2->CR1 |= USART_CR1_TE + USART_CR1_RE;					// Habiliar recepcion y transmision
	USART2->CR1 |= USART_CR1_RXNEIE;										// Interrupción recepcion
	USART2->CR1 |= USART_CR1_UE;
	
	NVIC_EnableIRQ(USART2_IRQn);
}

void USART2_IRQHandler(void){
	if (USART2->ISR & USART_ISR_RXNE) {
		input = USART2->RDR;
		if (input != '\r') {
			tokens[command_counter] = input;
			command_counter++;
			isCarriageReturn = 0;
		} else {
			tokens[command_counter] = '\0';
			isCarriageReturn = 1;
			command_counter = 0;
			read_command();
			put_string_USART(">> ");
		}
	}
}

void read_command() {
	// strtok reference
	// https://wiki.sei.cmu.edu/confluence/display/c/STR06-C.+Do+not+assume+that+strtok%28%29+leaves+the+parse+string+unchanged#:~:text=The%20C%20function%20strtok(),if%20there%20is%20no%20token.
	parameters_commands[0] = strtok(tokens, " ");
	parameters_commands[1] = strtok(NULL, " ");
	parameters_commands[2] = strtok(NULL, " ");
	parameters_commands[3] = strtok(NULL, " ");
	parameters_commands[4] = strtok(NULL, " ");
	
	char *command = parameters_commands[0];
	
	//stcmp retora 0 si son iguales los string
	if (strcmp(command, RD_COMMAND) == 0) {
		put_string_USART("Estas en el comando RD \n\r");
	} else if (strcmp(command, RM_COMMAND) == 0) {
		put_string_USART("Estas en el comando RM \n\r");
	} else if (strcmp(command, MD_COMMAND) == 0) {
		put_string_USART("Estas en el comando MD \n\r");
	} else if (strcmp(command, MM_COMMAND) == 0) {
		put_string_USART("Estas en el comando MM \n\r");
	} else if (strcmp(command, BF_COMMAND) == 0) {
		put_string_USART("Estas en el comando BF \n\r");
	} else if (strcmp(command, RUN_COMMAND) == 0) {
		put_string_USART("Estas en el comando RUN \n\r");
	} else if (strcmp(command, CALL_COMMAND) == 0) {
		put_string_USART("Estas en el comando CALL \n\r");
	} else if (strcmp(command, IOMAP_COMMAND) == 0) {
		put_string_USART("Estas en el comando IOMAP \n\r");
	} else if (strcmp(command, IOUNMAP_COMMAND) == 0) {
		put_string_USART("Estas en el comando IOUNMAP \n\r");
	} else if (strcmp(command, SOUND_COMMAND) == 0) {
		put_string_USART("Estas en el comando SOUND \n\r");
	} else if (strcmp(command, MUTE_COMMAND) == 0) {
		put_string_USART("Estas en el comando MUTE \n\r");
	} else if (strcmp(command, RGBOUT_COMMAND) == 0) {
		put_string_USART("Estas en el comando RGBOUT \n\r");
	} else if (strcmp(command, ARCADE_COMMAND) == 0) {
		put_string_USART("Estas en el comando ARCADE \n\r");
	} else if (strcmp(command, CLEAR_COMMAND) == 0) {
		put_string_USART("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\r");
		welcome_message();
	} else {
		put_string_USART("Comando no disponible \n\r");
	}
}


void send_USART(uint8_t c) {
	while(!(USART2->ISR & USART_ISR_TC));
	USART2->TDR = c;
}

void put_string_USART(char *string){
	while(*string){
		send_USART(*string);
		string++;
	}
}

void welcome_message() {
put_string_USART("Proyecto Unidad basica microprocesadores 2022 \n\r");
	/*put_string_USART("Integrantes: \n\r");
	put_string_USART("Abel Alvarez - 20002301 \n\r");
	put_string_USART("Jairo Garcia - 20002864 \n\r");
	put_string_USART("David Barrera - 20002878 \n\r");
	put_string_USART("Otto Chamo - 19001395 \n\r");*/
}


int main(void) {
	clock_config();
	setup_USART(115200);
	welcome_message();
	put_string_USART(">> ");

	while (1) {
	}
	
}

void RD(void){
	register_display(*registros);
	int x=0;
	for(x = 0;x<15;x++){
		sprintf(datos_registros, "0x%08x", registros[x]);
		USART2_putSTring(datos_registros);
		USART2_putSTring("\n\r");
	}
}