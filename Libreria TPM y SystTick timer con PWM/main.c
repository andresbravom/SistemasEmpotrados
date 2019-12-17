#include <MKL25Z4.h>
#include "functions.h"
#define led_azul 1
#define mask(x)	(1UL << (x))

#define PWM_PERIOD (48000)

void SysTick_Handler(){
	
}

int main (void) {
	uint16_t i=0;
	volatile int32_t delay;
	init_led_rojo(PWM_PERIOD);
	init_led_azul(PWM_PERIOD);
	init_led_verde(PWM_PERIOD);
	init_sysTick();
	__enable_irq();
	

	//TPM0->CONTROLS[1].CnV = 1;
	//flash forever
	while(1) {
		
		//Brihten LED
		for (i=0; i<PWM_PERIOD; i++) {
			TPM2->CONTROLS[0].CnV = i;
			TPM0->CONTROLS[1].CnV = i;
			TPM2->CONTROLS[1].CnV = i;
			for (delay=0; delay<100; delay++)
									;
		}
		//Dim LED
		for (i=PWM_PERIOD-1; i>0; i--) {
			TPM2->CONTROLS[0].CnV = i;
			TPM0->CONTROLS[1].CnV = i;
			TPM2->CONTROLS[1].CnV = i;
			for(delay=0; delay<100; delay++)
									;
		}
	}
}
