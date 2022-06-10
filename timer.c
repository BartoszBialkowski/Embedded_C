#include <LPC21xx.H>
#include "timer.h"

#define COUNTER_ENABLE (1<<0)
#define COUNTER_RESET (1<<1)
#define RESET_ON_MR0 (1<<1)
#define INTERRUPT_ON_MR0 (1<<0)
#define MR0_INTERRUPT_FLAG (1<<0)

void InitTimer0(void){

	T0TCR = COUNTER_ENABLE;
}

void WaitOnTimer0(unsigned int uiTime){

	T0TCR = T0TCR | COUNTER_RESET;
	T0TCR = T0TCR & ~COUNTER_RESET;
	while (T0TC <= (uiTime*15)){}
}

void InitTimer0Match0(unsigned int iDelayTime){

	T0TCR = COUNTER_ENABLE | COUNTER_RESET;
	T0TCR = T0TCR & ~COUNTER_RESET;
	T0MR0 = iDelayTime * 15;
	T0MCR = RESET_ON_MR0 | INTERRUPT_ON_MR0;
}

void WaitOnTimer0Match0(){

	while ((T0IR & MR0_INTERRUPT_FLAG) == 0){}
	T0IR = MR0_INTERRUPT_FLAG;
}


