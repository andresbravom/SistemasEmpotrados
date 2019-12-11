#include "MKL25Z4.h"
#define mask(x) (1UL << (x))
#define led_azul (1)

//Delay function (Software)

void delay(volatile unsigned int time){
	while(time--);
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
		PORTD -> PCR[led_azul] |= PORT_PCR_MUX(1); 		//MUX Set
		PTD->PDDR |= mask(led_azul);

	//Set the value of the ports to 0
	while(1){
		PTD->PSOR = mask(led_azul);
		delay(1000000);
		PTD->PCOR = mask(led_azul);
		delay(1000000);
	}		
}