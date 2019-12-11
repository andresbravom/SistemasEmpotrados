#include <MKL25Z4.h>
#include <core_cm0plus.h>
#define led_red 18
#define led_azul 1
#define mask(x)	(1UL << (x))
#define PWM_PERIOD (48000)

void Init_Red_LED_PWM(uint16_t period){
	//Enable clock to PORTB, TPM0
	SIM->SCGC5|= SIM_SCGC5_PORTB_MASK;
	SIM->SCGC6|= SIM_SCGC6_TPM2_MASK;
	
	PORTB->PCR[led_red]&= ~PORT_PCR_MUX_MASK;
	PORTB->PCR[led_red]|= PORT_PCR_MUX(7);
	
	SIM->SOPT2 &= ~SIM_SOPT2_PLLFLLSEL_MASK;
	SIM->SOPT2 |= SIM_SOPT2_TPMSRC(1);

	TPM2->MOD = period-1;
	
	TPM2->SC = TPM_SC_PS(1);
	
	TPM2->CONF |= TPM_CONF_DBGMODE(3);
	
	TPM2->CONTROLS[0].CnSC = TPM_CnSC_MSB_MASK | TPM_CnSC_ELSA_MASK;
	
	TPM2->CONTROLS[0].CnV = 0;
	
	TPM2->SC |= TPM_SC_CMOD(1);		
}

void Init_Azul_LED_PWM(uint16_t period){
//Enable clock to PORTD, TPM0
SIM->SCGC5|= SIM_SCGC5_PORTD_MASK;
SIM->SCGC6|= SIM_SCGC6_TPM0_MASK;


PORTD->PCR[led_azul]&= ~PORT_PCR_MUX_MASK;
PORTD->PCR[led_azul]|= PORT_PCR_MUX(4);

SIM->SOPT2 &= ~SIM_SOPT2_PLLFLLSEL_MASK;
SIM->SOPT2 |= SIM_SOPT2_TPMSRC(1);


TPM0->MOD = period-1;

TPM0->SC = TPM_SC_PS(1);

TPM0->CONF |= TPM_CONF_DBGMODE(3);

TPM0->CONTROLS[1].CnSC = TPM_CnSC_MSB_MASK | TPM_CnSC_ELSA_MASK;

TPM0->CONTROLS[1].CnV = 0;

TPM0->SC |= TPM_SC_CMOD(1);
	
}
	
int main (void) {
	uint16_t i=0;
	volatile int32_t delay;
	Init_Red_LED_PWM(PWM_PERIOD);
	Init_Azul_LED_PWM(PWM_PERIOD);
	
	//TPM0->CONTROLS[1].CnV = 1;
	//flash forever
	while(1) {
		
		//Brihten LED
		for (i=0; i<PWM_PERIOD; i++) {
			TPM2->CONTROLS[0].CnV = i;
			TPM0->CONTROLS[1].CnV = i;
			for (delay=0; delay<100; delay++)
									;
		}
		//Dim LED
		for (i=PWM_PERIOD-1; i>0; i--) {
			TPM2->CONTROLS[0].CnV = i;
			TPM0->CONTROLS[1].CnV = i;
			for(delay=0; delay<100; delay++);
		}
	}
}