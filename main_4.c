#include "led.h"
#include "keyboard.h"
#include "servo.h"
#include "uart.h"

#define NULL '\0'


int main (){
	
	extern char cOdebranyZnak;
	unsigned char ucServoPosition = 1;
	ServoInit(50);
	UART_InitWithInt(9600);
	
while(1){
	
		switch(cOdebranyZnak){
			case '1':
				ServoGoTo(12*ucServoPosition);
				ucServoPosition++;
				cOdebranyZnak = NULL;
				break;			
			case '2':
				break;
			case '3':
				break;
			case '4':
				break;
			case 'c':
				ServoCallib();
				ucServoPosition = 1;
				cOdebranyZnak = NULL;
				break;
			default:{}
		}
		switch(eKeyBoardRead()){
			case BUTTON_0:
				ServoCallib();
				ucServoPosition = 1;
				break;			
			case BUTTON_1:
				ServoGoTo(12);
				ucServoPosition = 2;
				break;
			case BUTTON_2:
				ServoGoTo(24);
				ucServoPosition = 3;
				break;
			case BUTTON_3:
				ServoGoTo(36);
				ucServoPosition = 4;
				break;
			case RELASED:
				break;
			default:
				break;
		}
	}
}


