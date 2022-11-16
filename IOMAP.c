
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
            EXTI->RTSR |= (1 << 10)
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
            pin=5
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
    //DECLARAMOS ENTRADAS (IN)
    //valores a,b,c,d referencia 4 push buttons
    if( param_1 == 'D'){
        var_io = 'd';
    }else if( param_1 == 'C'){
        var_io = 'c';
    }else if( param_1 == 'B'){
        var_io = 'b';
    }else if( param_1 == 'A'){
        var_io = 'a';
    }else{
        var_io= param_1;
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
        SYSCFG->EXTICR[0] |= (1 << 0)
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
    NVIC_EnableIRQ(EXTI15_10_IRQn)
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


