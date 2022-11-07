

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_Interface.h"
#include "TIMER_private.h"
#include "TIMER_config.h"
#include "TIMER__interface.h"

void (*Timer0CallBackFun) (void)=0;

void Timer0_init()
{

	SET_BIT(SREG,7);//Set global interrupt flag

	//according to the mode, manipulate the bits
#if TIMER_SET_MODE==NORMAL
	CLR_BIT(TCCR0,3);
	CLR_BIT(TCCR0,6);
	SET_BIT(TIMSK,0); //set overflow interrupt flag for timer0

#elif TIMER_SET_MODE==PHASE_CORRECT_PWM
	CLR_BIT(TCCR0,3);
	SET_BIT(TCCR0,6);
#if OC0_SET_MODE==INVERTINGMODE
	CLR_BIT(TCCR0,4);
	SET_BIT(TCCR0,5);
#elif INVERTINGMODE==NONINVERTINGMODE
	SET_BIT(TCCR0,4);
	SET_BIT(TCCR0,5);
#endif
#elif TIMER_SET_MODE==CTCMODE
	SET_BIT(TCCR0,3);
	CLR_BIT(TCCR0,6);
	SET_BIT(TIMSK,1); //set interrupt on compare match
#if CTC_SET_MODE==CTCTNORMAL
	CLR_BIT(TCCR0,5);
	CLR_BIT(TCCR0,4);
#elif CTC_SET_MODE==CTCTTOGGLE
	CLR_BIT(TCCR0,5);
	SET_BIT(TCCR0,4);
#elif CTC_SET_MODE==CTCCLR
	SET_BIT(TCCR0,5);
	CLR_BIT(TCCR0,4);
#elif CTC_SET_MODE==CTCSET
	SET_BIT(TCCR0,5);
	SET_BIT(TCCR0,4);

#endif
#elif TIMER_SET_MODE==FASTPWM
	SET_BIT(TCCR0,3);
	SET_BIT(TCCR0,6);
#if OC0_SET_MODE==INVERTINGMODE
	SET_BIT(TCCR0,4);
	SET_BIT(TCCR0,5);
#elif OC0_SET_MODE==NONINVERTINGMODE
	CLR_BIT(TCCR0,4);
	SET_BIT(TCCR0,5);
#endif

#endif



}

void Start_timer(u8 PRELOAD)
{
	TCNT0=PRELOAD;
}

void set_prescaler(u8 Prescaler_value)
{
	switch(Prescaler_value)
	{
	case EIGHTH:
		SET_BIT(TCCR0,0);
		CLR_BIT(TCCR0,1);
		CLR_BIT(TCCR0,2);
		break;

	case SIXTYFOURTH:
		SET_BIT(TCCR0,0);
		SET_BIT(TCCR0,1);
		CLR_BIT(TCCR0,2);
		break;

	case TWOFIFTYSIXTH:
		SET_BIT(TCCR0,0);
		SET_BIT(TCCR0,1);
		CLR_BIT(TCCR0,2);
		break;

	case THOUSANDANDTWENYFOUR:
		SET_BIT(TCCR0,0);
		CLR_BIT(TCCR0,1);
		SET_BIT(TCCR0,2);
		break;
	}


}

void ClrOCR0Interrupt()
{
	CLR_BIT(TIMSK,1); //clr interrupt on compare match
}

void SetOCR0Interrupt()
{
	SET_BIT(TIMSK,1); //set interrupt on compare match
}



void set_OCR0(u8 Value)
{
	OCR0=Value;
}

void vidTimer0SetCallBackFunc(void (*CopyTimer0CallBackFun)(void))
{
	Timer0CallBackFun=CopyTimer0CallBackFun;
}

void __vector_10(void)  __attribute__((signal));

void __vector_10(void)
{
	if(Timer0CallBackFun!=0)
		Timer0CallBackFun();
}
void __vector_11(void)  __attribute__((signal));

void __vector_11(void)
{
	if(Timer0CallBackFun!=0)
		Timer0CallBackFun();
}
