#include <LPC21xx.H>
#include "led.h"
#include "timer_interrupts.h"
#include "servo.h"
#include "keyboard.h"

#define SET_DETECTOR (1<<10)
#define ROTATE (1<<16)
#define SECOND 1000000

enum DetectorState {ACTIVE,INACTIVE};

enum ServoState {CALLIB, IDLE, IN_PROGRESS};

enum ServoState eState = IDLE;

struct Servo
{
	enum ServoState eState;
	unsigned int uiCurrentPosition;
	unsigned int uiDesiredPosition;
};

struct Servo sServo;

void DetectorInit(){

	IO0DIR = IO0DIR & (~SET_DETECTOR);
}


enum DetectorState eReadDetector(){

	if((IO0PIN & SET_DETECTOR) == 0){
	return ACTIVE ;
	}
	return INACTIVE ;
}


void Automat(){
		
	switch(eState){
		case IDLE:
			if(sServo.uiCurrentPosition != sServo.uiDesiredPosition){	
				eState = IN_PROGRESS;
			}
			else{
				eState = eState;
			}
			break;
				
		case IN_PROGRESS:
			if(sServo.uiCurrentPosition > sServo.uiDesiredPosition){
				eState = eState;
				sServo.uiCurrentPosition = sServo.uiCurrentPosition - 1;
				LedStepLeft();
			}
			else if(sServo.uiCurrentPosition < sServo.uiDesiredPosition){
				eState = eState;
				sServo.uiCurrentPosition = sServo.uiCurrentPosition + 1;
				LedStepRight();
			}
			else{
				eState = IDLE;
			}
			break;
				
		case CALLIB:
			if(eReadDetector() == ACTIVE){
				eState = IDLE;
				sServo.uiCurrentPosition = 0;
				sServo.uiDesiredPosition = 0;
			}
			else{
				LedStepLeft();
				eState = eState;		
			}
			break;
			
		default:
			break;
	 }
}


void ServoInit(unsigned int uiServoFrequency){

	unsigned int uiCycle = SECOND / uiServoFrequency;
	Timer0Interrupts_Init(uiCycle, &Automat);
	KeyboardInit();
	LedInit();
	DetectorInit();
	eState = CALLIB;
}

void ServoCallib(void){
	
	eState = CALLIB;
}
	
void ServoGoTo(unsigned int uiPosition){

	sServo.uiDesiredPosition = uiPosition ;
}


