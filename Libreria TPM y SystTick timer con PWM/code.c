#include <MKL25Z4.h>
#define led_azul 1
#define led_rojo 18
#define led_verde 19
#define mask(x)	(1UL << (x))

void init_led_azul(uint16_t period){
	//Enable clock to PORTB, TPM0
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

void init_led_rojo(uint16_t period){
	//Enable clock to PORTB, TPM2
	SIM->SCGC5|= SIM_SCGC5_PORTB_MASK;
	SIM->SCGC6|= SIM_SCGC6_TPM2_MASK;
	
	
	PORTB->PCR[led_rojo]&= ~PORT_PCR_MUX_MASK;
	PORTB->PCR[led_rojo]|= PORT_PCR_MUX(7);
	
	SIM->SOPT2 &= ~SIM_SOPT2_PLLFLLSEL_MASK;
	SIM->SOPT2 |= SIM_SOPT2_TPMSRC(1);


	TPM2->MOD = period-1;
	
	TPM2->SC = TPM_SC_PS(1);
	
	TPM2->CONF |= TPM_CONF_DBGMODE(3);
	
	TPM2->CONTROLS[0].CnSC = TPM_CnSC_MSB_MASK | TPM_CnSC_ELSA_MASK;
	
	TPM2->CONTROLS[0].CnV = 0;
	
	TPM2->SC |= TPM_SC_CMOD(1);
		
	}

	void init_led_verde(uint16_t period){
	//Enable clock to PORTB, TPM2
	SIM->SCGC5|= SIM_SCGC5_PORTB_MASK;
	SIM->SCGC6|= SIM_SCGC6_TPM2_MASK;
	
	PORTB->PCR[led_verde]&= ~PORT_PCR_MUX_MASK;
	PORTB->PCR[led_verde]|= PORT_PCR_MUX(3);
	
	SIM->SOPT2 &= ~SIM_SOPT2_PLLFLLSEL_MASK;
	SIM->SOPT2 |= SIM_SOPT2_TPMSRC(1);


	TPM2->MOD = period-1;
	
	TPM2->SC = TPM_SC_PS(1);
	
	TPM2->CONF |= TPM_CONF_DBGMODE(3);
	
	TPM2->CONTROLS[1].CnSC = TPM_CnSC_MSB_MASK | TPM_CnSC_ELSA_MASK;
	
	TPM2->CONTROLS[1].CnV = 0;
	
	TPM2->SC |= TPM_SC_CMOD(1);
		
}
	void init_sysTick(void){
		SysTick->LOAD = (48999999L/16);
		NVIC_SetPriority (SysTick_IRQn, 3);
		NVIC_EnableIRQ(SysTick_IRQn);
		SysTick->VAL = 0;
		SysTick->CTRL = SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk;
	}