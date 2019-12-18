#include <MKL25Z4.h>
#define UART_OVERSAMPLE_RATE	(16)//16
#define SYS_CLOCK (48e6)//24

void init_uart(uint32_t baud_rate){
	
	uint16_t sbr;
	//Hsbilita el reloj del módulo UART 0
	SIM->SCGC4 |= SIM_SCGC4_UART0_MASK;
	
	//Habilita el reloij del puerto A
	SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;
	
	//Limpia el campo TE y RE del UART 0
	UART0->C2 &= ~UART0_C2_TE_MASK & ~UART0_C2_RE_MASK;
	
	//Hay que configurar el reloj de la UART	
	MCG->C1|= MCG_C1_CLKS(2);
	MCG->C6&=~MCG_C6_PLLS_MASK;
	MCG->C2|= ~MCG_C2_LP_MASK;
	MCG->C5|=MCG_C5_PRDIV0(1);
	MCG->C5|=MCG_C5_PLLCLKEN0_MASK;
	
	//Configura la fuente del reloj
	SIM->SOPT2 |= SIM_SOPT2_UART0SRC(1);
	
	//
	SIM->SOPT2 |= SIM_SOPT2_PLLFLLSEL_MASK;
	
	//SIM->SOPT2 &= ~SIM_SOPT2_PLLFLLSEL_MASK;
	PORTA->PCR[1]=PORT_PCR_ISF_MASK | PORT_PCR_MUX(2); //COnecta el UART al MUX
	PORTA->PCR[2]=PORT_PCR_ISF_MASK | PORT_PCR_MUX(2);
	
	//hay que programas UART0_C1, C2 y C3
	// vamos a configurar los baudios
	//sbr = 625;//(uint16_t)((SYS_CLOCK)/(baud_rate * UART_OVERSAMPLE_RATE));
	sbr = (uint16_t)((SYS_CLOCK)/(baud_rate * UART_OVERSAMPLE_RATE));

	UART0->BDH &= ~UART0_BDH_SBR_MASK;
	UART0->BDH = UART0_BDH_SBR(sbr>>8);
	UART0->BDL = UART0_BDL_SBR(sbr);
	UART0->C4 |= UART0_C4_OSR(UART_OVERSAMPLE_RATE-1);//-1
	//UART0->BDH = 0x02;
	//UART0->BDL = 0x71;
	//UART0->C4 |= UART0_C4_OSR(UART_OVERSAMPLE_RATE-1);//-1	
	// hay que deshabilitar interrupciones
	
	UART0->BDH |= UART0_BDH_RXEDGIE(0) | UART0_BDH_SBNS(0) | UART0_BDH_LBKDIE(0);
	
	//Configuración del UART
	
	UART0->C1 |= UART0_C1_M(0);	
	UART0->C1 |= UART0_C1_PE(0);
	UART0->C1 |= UART0_C1_LOOPS(0);
	
	UART0->C3 |= UART0_C3_TXINV(0);
	UART0->C3 |= UART0_C3_ORIE(1);
	UART0->C3 |= UART0_C3_NEIE(1);
	UART0->C3 |= UART0_C3_FEIE(1);
	UART0->C3 |= UART0_C3_PEIE(1);
	
//Limpiar flags
	
	UART0->S1 = UART0_S1_OR(1) | UART0_S1_NF(1) | UART0_S1_FE(1) | UART0_S1_PF(1);
	UART0->S2 = UART0_S2_MSBF(0) | UART0_S2_RXINV(0);
	UART0->C2 |= UART0_C2_TE(1) | UART0_C2_RE(1);
}

void UART0_Transmit_Poll(uint8_t data){
	while(!(UART0->S1 & UART0_S1_TDRE_MASK)){
		;
	}
	UART0->D = data;
}

uint8_t UART0_Receive_Poll(void){
	while(!(UART0->S1 & UART0_S1_RDRF_MASK)){
		;
	}
	 return UART0->D;
}

int main(void){
	uint8_t c, i;

	c=0x00;
	init_uart(9600);//19200 115200
	for (i=0; i<128; i++){
	
		UART0_Transmit_Poll(c++);
		//c = UART0_Receive_Poll();
	}
}