#include <MKL25Z4.h>
#include <core_cm0plus.h>

#define Mask(x) (1UL<<(x))
#define led_azul (1) //Port D
#define led_rojo (18) //Port B
#define led_verde (19) //Port B

//Encender 3 LEDs
void delay(volatile unsigned int time){
while(time--);
}

int main(){
	//Paso 1: Conectar CLK a los puertos
	SIM -> SCGC5 |= SIM_SCGC5_PORTD_MASK |SIM_SCGC5_PORTB_MASK;

	//Paso 2: Conectar GPIO

	//Limpiamos los campos del multiplexor
	PORTD -> PCR[led_azul] &= ~PORT_PCR_MUX_MASK;
	PORTB -> PCR[led_rojo] &= ~PORT_PCR_MUX_MASK;
	PORTB -> PCR[led_verde] &= ~PORT_PCR_MUX_MASK;

	PORTD -> PCR[led_azul] |= PORT_PCR_MUX(1);
	PORTB -> PCR[led_rojo] |= PORT_PCR_MUX(1);
	PORTB -> PCR[led_verde] |= PORT_PCR_MUX(1);

	//Paso 3: Configuramos pines como I/O

	PTD -> PDDR |= Mask(led_azul);
	PTD-> PSOR= Mask(led_azul);
	PTB -> PDDR |= Mask(led_rojo);
	PTB-> PSOR= Mask(led_rojo);
	PTB -> PDDR |= Mask(led_verde);
	PTB-> PSOR= Mask(led_verde);

	//Paso 4: R/W
	while (1){
		PTD-> PCOR= Mask(led_azul);
		delay(2000000);
		PTD-> PSOR= Mask(led_azul);
		delay(2000000);
		PTB-> PCOR= Mask(led_rojo);
		delay(2000000);
		PTB-> PSOR= Mask(led_rojo);
		delay(2000000);
		PTB-> PCOR= Mask(led_verde);
		delay(2000000);
		PTB-> PSOR= Mask(led_verde);
		delay(2000000);
	}
}