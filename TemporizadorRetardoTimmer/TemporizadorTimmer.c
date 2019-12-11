#include "MKL25Z4.h"
#define mask(x) (1UL << (x))
#define led_azul (1)

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
		PORTD -> PCR[led_azul] &= ~PORT_PCR_MUX_MASK; 	//MUX Clear
		PORTD -> PCR[led_azul] |= PORT_PCR_MUX(led_azul); 		//MUX Set

	//Set the value of the ports to 0
		PTD->PSOR = mask(led_azul);

	//Configure pin as input/output ("|=" equals to output and "&= ~" equals to input)
		PTD->PDDR |= mask(led_azul);		//Blue led port output

	//Initialize the clock timer
		Init_SysTick();

	//Enable IRQ interrupts
		__enable_irq();

	//Loop forever
		while(1){
			;
		}
}