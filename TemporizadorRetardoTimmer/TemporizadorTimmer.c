/*#include <mkl25z4.h>
#include <core_cm0plus.h>
#define MASK(x) (1UL << (x))

void SysTick_Handler() {
	PTD->PTOR |= MASK(1);
}

int main(void) {
	//Se configura el led azul
	
	SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK;
	
	//Habilitamos las interrupciones
	
	PORTD->PCR[1] = ~ PORT_PCR_MUX_MASK;
	PORTD->PCR[1] = PORT_PCR_MUX(1);
	PTD->PDOR |= MASK(1);
	PTD->PDDR |= MASK(1);
	
	//Configuramos el SystickTimer
	SysTick->LOAD = (48000000/16);
	NVIC_SetPriority(SysTick_IRQn, 3);
	NVIC_EnableIRQ(SysTick_IRQn);
	
	SysTick->VAL = 0;
	SysTick->CTRL = SysTick_CTRL_TICKINT_Msk;
	SysTick->CTRL = SysTick_CTRL_ENABLE_Msk;
	
	while(1) {
		;
	}
}






#include <MKL25z4.h>
#define Mask(x) (1UL<<(x))
#define led_azul (1) //Port D

void SysTick_Handler() {
	PTD->PCOR |= Mask(led_azul);
}

int main(void){
	//Enciende el led
	SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK; 
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;
	PORTD->PCR[led_azul] &= ~ PORT_PCR_MUX_MASK; 
	PORTD->PCR[led_azul] |= PORT_PCR_MUX(1);
	PTD->PDDR |= Mask(led_azul);
	
	//Configuramos el SystickTimer
	SysTick->LOAD = (48000000/16);
	NVIC_SetPriority(SysTick_IRQn, 3);
	NVIC_EnableIRQ(SysTick_IRQn);
	
	SysTick->VAL = 0;
	SysTick->CTRL = SysTick_CTRL_TICKINT_Msk;
	SysTick->CTRL = SysTick_CTRL_ENABLE_Msk;
	
	while(1) {
		;
	}
}*/


#include "MKL25Z4.h"
#define mask(x) (1UL << (x))

//Delay function (Software)

void delay(volatile unsigned int time){
	while(time--);
}

//Handler for the Systick

void SysTick_Handler() {
	PTD->PTOR = mask(1);
	delay(1000000);
}

//Initialize clock timer

void Init_SysTick(void){
	//Load the value of how long to wait between each interrupts
	SysTick->LOAD = (48999999L/16); //This is the clock speed/16

	//Set the interrupt priority of the timer interrupt
	NVIC_SetPriority(SysTick_IRQn,3);

	//Enable the NVIC flags for the IRQ interrupt
	NVIC_EnableIRQ(SysTick_IRQn);

	//Set the value of the Systick to 0
	SysTick->VAL = 0;

	//Configure the control values of the Systick to acept the TICKINT and enable it
	SysTick->CTRL = SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk;
}

int main(void){
	//Clock to each port
		//Clear
		SIM->SCGC5 &= ~SIM_SCGC5_PORTD_MASK;

	//Set
		SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK;

	//Setting the MUX to the GPIO
		//Port for Blue led
		PORTD -> PCR[1] &= ~PORT_PCR_MUX_MASK; 	//MUX Clear
		PORTD -> PCR[1] |= PORT_PCR_MUX(1); 		//MUX Set

	//Set the value of the ports to 0
		PTD->PSOR = mask(1);

	//Configure pin as input/output ("|=" equals to output and "&= ~" equals to input)
		PTD->PDDR |= mask(1);		//Blue led port output

	//Initialize the clock timer
		Init_SysTick();

	//Enable IRQ interrupts
		__enable_irq();

	//Loop forever
		while(1){
			;
		}
}