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
	
	while(1) {

		//Brihten LED RED
		for (i=0; i<PWM_PERIOD; i++) {
			TPM2->CONTROLS[0].CnV = i;
			for (delay=0; delay<100; delay++)
									;
		}
		//Dim LED RED
		for (i=PWM_PERIOD-1; i>0; i--) {
			TPM2->CONTROLS[0].CnV = i;
			for(delay=0; delay<100; delay++)
									;
		}
			//Brihten LED BLUE
		for (i=0; i<PWM_PERIOD; i++) {
			TPM0->CONTROLS[1].CnV = i;
			for (delay=0; delay<100; delay++)
									;
		}
		//Dim LED BLUE
		for (i=PWM_PERIOD-1; i>0; i--) {
			TPM0->CONTROLS[1].CnV = i;
			for(delay=0; delay<100; delay++)
									;
		}
			//Brihten LED GREEN
		for (i=0; i<PWM_PERIOD; i++) {
			TPM2->CONTROLS[1].CnV = i;
			for (delay=0; delay<100; delay++)
									;
		}
		//Dim LED GREEN
		for (i=PWM_PERIOD-1; i>0; i--) {
			TPM2->CONTROLS[1].CnV = i;
			for(delay=0; delay<100; delay++)
									;
		}
	}
}
