#include <MKL25Z4.h>
#define RESOLUTION 4096
#define DAC_POS 30

void Init_DAC(void){
	SIM->SCGC6 |= SIM_SCGC6_DAC0_MASK;
	SIM-> SCGC5 |= SIM_SCGC5_PORTE_MASK;
	
	PORTE->PCR[DAC_POS] &= ~PORT_PCR_MUX_MASK;
	PORTE->PCR[DAC_POS] |= PORT_PCR_MUX(0);
	
	DAC0->C1 = 0;
	DAC0->C2 = 0;
	
	DAC0->C0 = DAC_C0_DACEN_MASK | DAC_C0_DACRFS_MASK;
}

void Triangle_Output(void){
	int i = 0, change =1;
	int x;
	while(1){
		DAC0->DAT[0].DATL = DAC_DATL_DATA0(i);
		DAC0->DAT[0].DATH = DAC_DATH_DATA1(i >> 8);
		
		i += change;
		
		if(i == 0){
			change = 1;
		}else if(i == RESOLUTION - 1){
			change = -1;
		}
	}
}

int main(void){
	Init_DAC();
	Triangle_Output();
}
