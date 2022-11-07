

#ifndef TIMER__INTERFACE_H_
#define TIMER__INTERFACE_H_

#define EIGHTH		     		0
#define SIXTYFOURTH      		1
#define TWOFIFTYSIXTH    		2
#define THOUSANDANDTWENYFOUR	3

#define NORMAL					0
#define PHASE_CORRECT_PWM		1
#define CTCMODE					2
#define FASTPWM					3


#define CTCTNORMAL				0
#define CTCTOGGLE				1
#define CTCCLR					2
#define CTCSET					3

#define INVERTINGMODE			0
#define NONINVERTINGMODE		1


void Timer0_init();
void Start_timer(u8 PRELOAD);
void set_prescaler(u8 Prescaler_value);
void set_OCR0(u8 Value);
void ClrOCR0Interrupt();
void SetOCR0Interrupt();
void vidTimer0SetCallBackFunc(void (*CopyTimer0CallBackFun)(void));



#endif /* TIMER__INTERFACE_H_ */
