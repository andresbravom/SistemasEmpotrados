#include <MKL25Z4.h>
#include <cmath>
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
		x=2047*sin(2*3.14*i)+2047;
		DAC0->DAT[0].DATL = DAC_DATL_DATA0(x);
		DAC0->DAT[0].DATH = DAC_DATH_DATA1(x >> 8);
	 
		i += change;
	}
}

int main(void){
	Init_DAC();
	Triangle_Output();
}