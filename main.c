#include "stm32f3xx.h"                  // Device header
#include "usart_utils.h"
#include "command_utils.h"
#include "buzzer_utils.h"
#include <stdio.h>

// funcion para direccion 
void call(void);

//comando que ejecuta la funcion en especifico
void execute_registerMod(void);
void IOMAP();
void RunAddress();

//Arreglo de registros
static uint32_t registros[15];
char datos_registros[32];

// Para la lectura de los comandos.
volatile static char input;
static char tokens[64];
// 5 posiciones porque el comando m�s largo ocupa 5 posiciones.
static char *parameters_commands[5] = {" ", " ", " ", " ", " "};
static uint32_t command_counter;
static uint32_t isCarriageReturn = 0;

// variables para el buzzer
static char *freq_buz;
int32_t numerical_value_freq;

void RD(void);

char *ptr;
char *buzzerPtr;

void clock_config(void);
void quitarX(char *dato);
int32_t get_size(char*);

// referencia https://stackoverflow.com/questions/6001661/how-to-find-the-length-of-an-char-array-in-c
// 

int32_t get_size(char* s) {
	char *t;
	for (t = s; *t != '\0'; t++);
	return t - s;
}

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
	USART2->CR1 |= USART_CR1_RXNEIE;										// Interrupci�n recepcion
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
	if ((strcmp(command, RD_COMMAND)) == 0) {
		RD();
	} else if ((strcmp(command, RM_COMMAND)) == 0) {
		put_string_USART("Estas en el comando RM \n\r");
		execute_registerMod();
	} else if ((strcmp(command, MD_COMMAND)) == 0) {
		put_string_USART("Estas en el comando MD \n\r");
	} else if ((strcmp(command, MM_COMMAND)) == 0) {
		put_string_USART("Estas en el comando MM \n\r");
	} else if ((strcmp(command, BF_COMMAND)) == 0) {
		put_string_USART("Estas en el comando BF \n\r");
	} else if ((strcmp(command, RUN_COMMAND)) == 0) {
		put_string_USART("Estas en el comando RUN \n\r");
		RunAddress();
	} else if ((strcmp(command, CALL_COMMAND)) == 0) {
		put_string_USART("Estas en el comando CALL \n\r");
		call();
	} else if ((strcmp(command, IOMAP_COMMAND)) == 0) {
		put_string_USART("Estas en el comando IOMAP \n\r");
		IOMAP();
	} else if ((strcmp(command, IOUNMAP_COMMAND)) == 0) {
		put_string_USART("Estas en el comando IOUNMAP \n\r");
	} else if ((strcmp(command, SOUND_COMMAND)) == 0) {
		put_string_USART("Estas en el comando SOUND \n\r");
		run_buzzer();
	} else if ((strcmp(command, MUTE_COMMAND)) == 0) {
		put_string_USART("Estas en el comando MUTE \n\r");
		run_buzzer();
	} else if ((strcmp(command, RGBOUT_COMMAND)) == 0) {
		put_string_USART("Estas en el comando RGBOUT \n\r");
	} else if ((strcmp(command, ARCADE_COMMAND)) == 0) {
		put_string_USART("Estas en el comando ARCADE \n\r");
	} else if ((strcmp(command, CLEAR_COMMAND)) == 0) {
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

char* direccionCall;
unsigned long nuevaCall;

void call(void){
	
	direccionCall = parameters_commands[1];
	quitarX(direccionCall);
	nuevaCall = strtoul(direccionCall,&ptr,16);
	calladdr(nuevaCall);
	put_string_USART("Call terminado");
}

void quitarX(char *dato){
	char *in, *out;
	in = dato;
	out = dato;
	for (in; *in != '\0'; in++){
		*out = *in;
		if (*out != "x"){
			out++;
		}
	}
	*out = '\0';
}

void RD(void){
	put_string_USART("Register Display\n\r");
	register_display(registros);
	int x=0;
	for(x = 0;x<15;x++){
		sprintf(datos_registros, "0x%08x", registros[x]);
		put_string_USART(datos_registros);
		put_string_USART("\n\r");
	}
}

//se definio en ensamblador
extern void registerModEnsamblador(int posicion_deseada, unsigned long dato); //-- funcion y variables



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

	pointer_registry = parameters_commands[1];
	dato = parameters_commands[2];

    registro_display_indice = 0;
    while(registro_display_indice < get_size(pointer_registry)){
        if (pointer_registry[registro_display_indice] != 'R')
		{
			rm_temporal1 = pointer_registry[registro_display_indice];
			// https://stackoverflow.com/questions/21022644/how-to-get-the-real-and-total-length-of-char-char-array
			strncat(posiciones, &rm_temporal1, 1);
		}
        registro_display_indice = registro_display_indice + 1;
    }

	sscanf(posiciones, "%d", &rm_temporal2);

	if (rm_temporal2 >= 0 & rm_temporal2 <= 15)
	{

		unsigned long ul;
		char *sinPrefijox;
		sinPrefijox = strtok(dato, "0x");
		ul = strtoul(sinPrefijox, &pointer, 16);

		registerModEnsamblador(rm_temporal2, ul);
	}
	else
	{
		put_string_USART("El registro deseado no es aceptado! \n");
	}
}

unsigned long run_addr_dir;
void RunAddress(void){
    char *RUN_ADDR= parameters_commands[1];
    long run_addr_dir;
		put_string_USART("Run Address\n\r");
		//Removemos Character
		quitarX(RUN_ADDR);
		run_addr_dir = strtoul(RUN_ADDR, &ptr, 16);
		//Mandamos run_addr_dir a funcion en ensamblador
		ensamblador_run_address(run_addr_dir);
}


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


void run_buzzer() {
	freq_buz = parameters_commands[1];

	numerical_value_freq = strtoul(freq_buz, &buzzerPtr, 10);
	config_buzzer(numerical_value_freq);
}

void config_buzzer(uint32_t freq_hz) {
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN; // Reloj puerto A
  RCC->APB2ENR |= RCC_APB2ENR_TIM1EN; // clock habilita tim1
	GPIOA->MODER |= (1<<21); // PA10 funcion alternativa
	GPIOA->AFR[1] |= (6<<8); // AF6 (TIM1CH3)
	TIM1->ARR = (SystemCoreClock/4)/(freq_hz);
	TIM1->CCR3 = (SystemCoreClock / 4) / (freq_hz * 2);
	TIM1->CCMR2 |= TIM_CCMR2_OC3M_2 | TIM_CCMR2_OC3M_1 | TIM_CCMR2_OC3PE; // Autoreload, Counter enable, Edge aligned, Upcounter
	TIM1->CR1 |= TIM_CR1_ARPE | TIM_CR1_CEN; // Autoreload register + Counter Enable
	TIM1->EGR |= TIM_EGR_UG; // reiniciar conteo
	
	TIM1->CCER |= TIM_CCER_CC3E;
	TIM1->BDTR |= TIM_BDTR_MOE; // MOE: Main output enable
}



int counter_negation = 0;
int pin = 0;

char *param_1;
char *param_2;
char *param_3;
char *param_4;

//IOMAP
//-----------------------------------------------------------------------------------------
void IOMAP(void){
    //IN
    param_1 = parameters_commands[1];
    //out
    param_2 = parameters_commands[2];
    //not
    param_3 = parameters_commands[3];
    //all
    param_4 = parameters_commands[4];

    //Habilitamos puertos b del reloj
    RCC->AHBENR |= RCC_AHBENR_GPIOBEN;    
    // Se habilita el reloj de SYSC
    RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
//---------------------------------------------------------------------------------------------
    //DECLARAMOS LAS SALIDAS (OUT) E INPUT IN
    //de 0 a 7 pines de GPIO
    if ( ((param_3 == 'not') && (param_4 == 'all')) || ((param_3 == 'all') )){
        if(param_1 == '7'){
            //PINES DE ENTRADA
            //PB_0
            GPIOB->MODER &= ~(3 << 0);
            GPIOB->PUPDR |= (1 << 0);
            //PB 0 EXTI ENABLE
            SYSCFG->EXTICR[0] |= (1 << 0);
             // UTILIZA EL VALOR DEL PIN DEL BOTON
            EXTI->IMR |= (1 << 0);
            EXTI->FTSR |= (1 << 0);
            EXTI->RTSR |= (1 << 0);
        }else if(param_1 == '6'){
            //PINES DE ENTRADA
            //PB_9
            GPIOB->MODER &= ~(3 << 18);
            GPIOB->PUPDR |= (1 << 18);
            //PB 9 EXTI ENABLE
            SYSCFG->EXTICR[2] |= (1 << 4);
            // UTILIZA EL VALOR DEL PIN DEL BOTON
            EXTI->IMR |= (1 << 9);
            EXTI->FTSR |= (1 << 9);
            EXTI->RTSR |= (1 << 9);
        }else if(param_1 == '5'){
            //PB_10
            GPIOB->MODER &= ~(3 << 20);
            GPIOB->PUPDR |= (1 << 20);
            //PB 10 EXTI ENABLE
            SYSCFG->EXTICR[2] |= (1 << 8);
             // UTILIZA EL VALOR DEL PIN DEL BOTON
            EXTI->IMR |= (1 << 10);
            EXTI->FTSR |= (1 << 10);
            EXTI->RTSR |= (1 << 10);
            //PINES DE ENTRADA
        }else if(param_1 == '4'){
            //PB11
            GPIOB->MODER &= ~(3 << 22);
            GPIOB->PUPDR |= (1 << 22);
            //PB 11 EXTI ENABLE
            SYSCFG->EXTICR[2] |= (1 << 12);
             // UTILIZA EL VALOR DEL PIN DEL BOTON
            EXTI->IMR |= (1 << 11);
            EXTI->FTSR |= (1 << 11);
            EXTI->RTSR |= (1 << 11);
            //PINES DE ENTRADA
        }else if(param_1 == '3'){
            //PB12
            GPIOB->MODER &= ~(3 << 24);
            GPIOB->PUPDR |= (1 << 24);
            //PB 12 EXTI ENABLE
            SYSCFG->EXTICR[3] |= (1 << 0);
             // UTILIZA EL VALOR DEL PIN DEL BOTON
            EXTI->IMR |= (1 << 12);
            EXTI->FTSR |= (1 << 12);
            EXTI->RTSR |= (1 << 12);
            //PINES DE ENTRADA
        }else if(param_1 == '2'){
            //PB13
            GPIOB->MODER &= ~(3 << 26);
            GPIOB->PUPDR |= (1 << 26);
            //PB 13 EXTI ENABLE
            SYSCFG->EXTICR[3] |= (1 << 4);
             // UTILIZA EL VALOR DEL PIN DEL BOTON
            EXTI->IMR |= (1 << 13);
            EXTI->FTSR |= (1 << 13);
            EXTI->RTSR |= (1 << 13);
            //PINES DE ENTRADA
        }else if(param_1 == '1'){
            //PB_14
            GPIOB->MODER &= ~(3 << 28);
            GPIOB->PUPDR |= (1 << (28));
            //PB 14 EXTI ENABLE
            SYSCFG->EXTICR[3] |= (1 << 8);
             // UTILIZA EL VALOR DEL PIN DEL BOTON
            EXTI->IMR |= (1 << 14);
            EXTI->FTSR |= (1 << 14);
            EXTI->RTSR |= (1 << 14);
            //PINES DE ENTRADA
        }else if(param_1 == '0'){
            //PB15
            GPIOB->MODER &= ~(3 << 30);
            GPIOB->PUPDR |= (1 << 30);
            //PB 15 EXTI ENABLE
            SYSCFG->EXTICR[3] |= (1 << 12);
             // UTILIZA EL VALOR DEL PIN DEL BOTON
            EXTI->IMR |= (1 << 15);
            EXTI->FTSR |= (1 << 15);
            EXTI->RTSR |= (1 << 15);
            //PINES DE ENTRADA
        }
//PINES OUTPUT
        if(param_2 == '7'){
            //PB_1 Output
            GPIOB->MODER |= (1 << 2);  
            pin=1;
        }else if(param_2 == '6'){
            //PB_2 Output
            GPIOB->MODER |= (1 << 4); 
            pin=2;
        }else if(param_2 == '5'){
            //PB_3 Output
            GPIOB->MODER |= (1 << 6); 
            pin=3;
        }else if(param_2 == '4'){
            //PB_4 Output
            GPIOB->MODER |= (1 << 8); 
            pin=4;
        }else if(param_2 == '3'){
            //PB_5 Output
            GPIOB->MODER |= (1 << 10); 
            pin=5;
        }else if(param_2 == '2'){
            //PB_6 Output
            GPIOB->MODER |= (1 << 12); 
            pin=6;
        }else if(param_2 == '1'){
            //PB_7 Output
            GPIOB->MODER |= (1 << 14); 
            pin=7;
        }else if(param_2 == '0'){
            //PB_8 Output
            GPIOB->MODER |= (1 << 16); 
            pin=8;
        }
    }
    
//-----------------------------------------------------------------------------------------
    if (param_3 == 'not'){
        if (counter_negation != 0){
            counter_negation = 0;
        }else{
            counter_negation = 1;
        }
    }
//-----------------------------------------------------------------------------------------
    if (param_4 == 'all'){
        //PB_0 PB_9 PV_10 PB_11 PB_12 PB_13 PB_14 PB_15  EXTI ENABLE
        SYSCFG->EXTICR[0] |= (1 << 0);
        SYSCFG->EXTICR[2] |= (1 << 4) | (1 << 8) | (1 << 12);
        SYSCFG->EXTICR[3] |= (1 << 0) | (1 << 4) | (1 << 8) | (1 << 12);
        // MAP EXTI
        EXTI->IMR |= (1 << 0) | (1 << 9) | (1 << 10) | (1 << 11) | (1 << 12) | (1 << 13) | (1 << 14) | (1 << 15);                          
        EXTI->FTSR |= (1 << 0) | (1 << 9) | (1 << 10) | (1 << 11) | (1 << 12) | (1 << 13) | (1 << 14) | (1 << 15);                        
        EXTI->RTSR |= (1 << 0) | (1 << 9) | (1 << 10) | (1 << 11) | (1 << 12) | (1 << 13) | (1 << 14) | (1 << 15); 
        //INPUTS PB_0 PB_9 PV_10 PB_11 PB_12 PB_13 PB_14 PB_15 
        GPIOB->MODER &= ~(3 << 0) | ~(3 << 18) | ~(3 << 20) | ~(3 << 22) | ~(3 << 24) | ~(3 << 26) | ~(3 << 28) | ~(3 << 30);
        GPIOB->PUPDR |= (1 << 0) | (1 << 18) | (1 << 20) | (1 << 22) | (1 << 24) | (1 << 26) | (1 << 28) | (1 << 30);
        //Outputs Leds PB_1 PB_2 PB_3 PB_4 PB_5 PB_6 PB_7 PB_8
        GPIOB->MODER |= (1 << 2) | (1 << 4) | (1 << 6) | (1 << 8) | (1 << 10) | (1 << 12) | (1 << 14) | (1 << 16);
        GPIOB->ODR |= (1 << 1) | (1 << 2) | (1 << 3) | (1 << 4) | (1 << 5) | (1 << 6) | (1 << 7) | (1 << 8);
    }
    NVIC_EnableIRQ(EXTI0_IRQn); 
    NVIC_EnableIRQ(EXTI9_5_IRQn);
    NVIC_EnableIRQ(EXTI15_10_IRQn);
}


//-----------------------------------------------------------------------------------------
//IRQHANDLER

void EXTI15_10_IRQHandler(void){
    //EXTI_PR_PR10
    if (EXTI->PR & EXTI_PR_PR10){
        if(counter_negation == 0){
            if(GPIOB -> IDR & (1<< 10)){
                GPIOB -> ODR |= (1 << pin);
            }else{
                GPIOB -> ODR |= ~(1 << pin);
            }
        }else{
            if(GPIOB -> IDR & (1<< 10)){
                GPIOB -> ODR |= ~(1 << pin);
            }else{
                GPIOB -> ODR |= (1 << pin);
            }
        }
        EXTI->PR |= EXTI_PR_PR10; 
    }
    //EXTI_PR_PR11
    if (EXTI->PR & EXTI_PR_PR11){
        if(counter_negation == 0){
            if(GPIOB -> IDR & (1<< 11)){
                GPIOB -> ODR |= (1 << pin);
            }else{
                GPIOB -> ODR |= ~(1 << pin);
            }
        }else{
            if(GPIOB -> IDR & (1<< 11)){
                GPIOB -> ODR |= ~(1 << pin);
            }else{
                GPIOB -> ODR |= (1 << pin);
            }
        }
        EXTI->PR |= EXTI_PR_PR11; 
    }
    //EXTI_PR_PR12
    if (EXTI->PR & EXTI_PR_PR12){
        if(counter_negation == 0){
            if(GPIOB -> IDR & (1<< 12)){
                GPIOB -> ODR |= (1 << pin);
            }else{
                GPIOB -> ODR |= ~(1 << pin);
            }
        }else{
            if(GPIOB -> IDR & (1<< 12)){
                GPIOB -> ODR |= ~(1 << pin);
            }else{
                GPIOB -> ODR |= (1 << pin);
            }
        }
        EXTI->PR |= EXTI_PR_PR12; 
    }
    //EXTI_PR_PR13
    if (EXTI->PR & EXTI_PR_PR13){
        if(counter_negation == 0){
            if(GPIOB -> IDR & (1<< 13)){
                GPIOB -> ODR |= (1 << pin);
            }else{
                GPIOB -> ODR |= ~(1 << pin);
            }
        }else{
            if(GPIOB -> IDR & (1<< 13)){
                GPIOB -> ODR |= ~(1 << pin);
            }else{
                GPIOB -> ODR |= (1 << pin);
            }
        }
        EXTI->PR |= EXTI_PR_PR13; 
    }
    //EXTI_PR_PR14
    if (EXTI->PR & EXTI_PR_PR14){
        if(counter_negation == 0){
            if(GPIOB -> IDR & (1<< 14)){
                GPIOB -> ODR |= (1 << pin);
            }else{
                GPIOB -> ODR |= ~(1 << pin);
            }
        }else{
            if(GPIOB -> IDR & (1<< 14)){
                GPIOB -> ODR |= ~(1 << pin);
            }else{
                GPIOB -> ODR |= (1 << pin);
            }
        }
        EXTI->PR |= EXTI_PR_PR14; 
    }
    //EXTI_PR_PR15
    if (EXTI->PR & EXTI_PR_PR15){
        if(counter_negation == 0){
            if(GPIOB -> IDR & (1<< 15)){
                GPIOB -> ODR |= (1 << pin);
            }else{
                GPIOB -> ODR |= ~(1 << pin);
            }
        }else{
            if(GPIOB -> IDR & (1<< 15)){
                GPIOB -> ODR |= ~(1 << pin);
            }else{
                GPIOB -> ODR |= (1 << pin);
            }
        }
        EXTI->PR |= EXTI_PR_PR15; 
    }
}

void EXTI9_5_IRQHandler(void){
    if (EXTI->PR & EXTI_PR_PR9){
        if(counter_negation == 0){
            if(GPIOB -> IDR & (1<< 9)){
                GPIOB -> ODR |= (1 << pin);
            }else{
                GPIOB -> ODR |= ~(1 << pin);
            }
        }else{
            if(GPIOB -> IDR & (1<< 9)){
                GPIOB -> ODR |= ~(1 << pin);
            }else{
                GPIOB -> ODR |= (1 << pin);
            }
        }
        EXTI->PR |= EXTI_PR_PR5; 
    }
}


void EXTI0_IRQHandler(void){
    if(counter_negation == 0){
        if(GPIOB -> IDR & (1<< 0)){
            GPIOB -> ODR |= (1 << pin);
        }else{
            GPIOB -> ODR |= ~(1 << pin);
        }
    }else{
        if(GPIOB -> IDR & (1<< 0)){
            GPIOB -> ODR |= ~(1 << pin);
        }else{
            GPIOB -> ODR |= (1 << pin);
        }
    }
    EXTI->PR |= EXTI_PR_PR0; 
}

