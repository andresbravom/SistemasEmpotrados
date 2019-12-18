#include <MKL25z4.h>
#define Mask(x) (1UL<<(x))
#define led_azul (1) //Port D
#define led_rojo (18) //Port B
#define led_verde (19) //Port B

int main(){
	//Paso 1: Conectar CLK a los puertos
	
	SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK; //Activamos el CLK en los puertos que vamos a utilizar
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;
	
	//Paso 2: Conectar GPIO al pin del micro
	//Limpiamos los camps del multiplexor
	
	PORTD->PCR[led_azul] &= ~ PORT_PCR_MUX_MASK; //Registro para el pin 1(led_azul) del puerto D
	PORTB->PCR[led_rojo] &= ~ PORT_PCR_MUX_MASK;
	PORTB->PCR[led_verde] &= ~ PORT_PCR_MUX_MASK;
	
	//Ponemos a '1' los campos del multiplexor correspondiente a los puertos B y D
	
	PORTD->PCR[led_azul] |= PORT_PCR_MUX(1); //Registro para el pin 1(led_azul) del puerto D
	PORTB->PCR[led_rojo] |= PORT_PCR_MUX(1);
	PORTB->PCR[led_verde] |= PORT_PCR_MUX(1);
	
	//Paso 3: Configurar los pines como I/O
	PTD->PSOR = Mask(led_azul); //Pone a '1' el pin del puerto D (Enciende el led)
	PTB->PSOR = Mask(led_rojo);
	PTB->PSOR = Mask(led_verde);
	
	PTD->PDDR |= Mask(led_azul);
	PTB->PDDR |= Mask(led_rojo);
	PTB->PDDR |= Mask(led_verde);
	
	//Paso 4: R/W
	
	PTD->PCOR = Mask(led_azul); //Pone a '1' el pin del puerto D (Enciende el led)
	PTB->PCOR = Mask(led_rojo);
	PTB->PCOR = Mask(led_verde);
	
	PTD->PSOR = Mask(led_azul); //Pone a '1' el pin del puerto D (Enciende el led)
	PTB->PSOR = Mask(led_rojo);
	PTB->PSOR = Mask(led_verde);
}