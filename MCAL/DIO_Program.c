
#include"STD_TYPES.h"
#include"BIT_MATH.h"
#include"DIO_Private.h"
#include"DIO_Interface.h"
/*Set Pin Direction */
void DIO_VidSetPinDirection(u8 Copy_u8PortID,u8 Copy_u8PinNumber,u8 Copy_u8PinDirection)
{
	/*Check on Port ID*/
	switch(Copy_u8PortID)
	{
	case DIO_PORTA:
		if(Copy_u8PinDirection==PIN_OUTPUT)
		{
			SET_BIT(DDRA,Copy_u8PinNumber);
		}
		else if(Copy_u8PinDirection==PIN_INPUT)
		{
			CLR_BIT(DDRA,Copy_u8PinNumber);
		}
		break;
	case DIO_PORTB:
		if(Copy_u8PinDirection==PIN_OUTPUT)
		{
			SET_BIT(DDRB,Copy_u8PinNumber);
		}
		else if(Copy_u8PinDirection==PIN_INPUT)
		{
			CLR_BIT(DDRB,Copy_u8PinNumber);
		}
		break;
	case DIO_PORTC:
		if(Copy_u8PinDirection==PIN_OUTPUT)
		{
			SET_BIT(DDRC,Copy_u8PinNumber);
		}
		else if(Copy_u8PinDirection==PIN_INPUT)
		{
			CLR_BIT(DDRC,Copy_u8PinNumber);
		}
		break;
	case DIO_PORTD:
		if(Copy_u8PinDirection==PIN_OUTPUT)
		{
			SET_BIT(DDRD,Copy_u8PinNumber);
		}
		else if(Copy_u8PinDirection==PIN_INPUT)
		{
			CLR_BIT(DDRD,Copy_u8PinNumber);
		}
		break;
	}
}
/*Set Pin Value*/
void DIO_VidSetPinValue(u8 Copy_u8PortID,u8 Copy_u8PinNumber,u8 Copy_u8PinValue)
{
	switch(Copy_u8PortID)
	{
	case DIO_PORTA:
		if(Copy_u8PinValue==PIN_HIGH)
		{
			SET_BIT(PORTA,Copy_u8PinNumber);
		}
		else if(Copy_u8PinValue==PIN_LOW)
		{
			CLR_BIT(PORTA,Copy_u8PinNumber);
		}
		break;
	case DIO_PORTB:
		if(Copy_u8PinValue==PIN_HIGH)
		{
			SET_BIT(PORTB,Copy_u8PinNumber);
		}
		else if(Copy_u8PinValue==PIN_LOW)
		{
			CLR_BIT(PORTB,Copy_u8PinNumber);
		}
		break;
	case DIO_PORTC:
		if(Copy_u8PinValue==PIN_HIGH)
		{
			SET_BIT(PORTC,Copy_u8PinNumber);
		}
		else if(Copy_u8PinValue==PIN_LOW)
		{
			CLR_BIT(PORTC,Copy_u8PinNumber);
		}
		break;
	case DIO_PORTD:
		if(Copy_u8PinValue==PIN_HIGH)
		{
			SET_BIT(PORTD,Copy_u8PinNumber);
		}
		else if(Copy_u8PinValue==PIN_LOW)
		{
			CLR_BIT(PORTD,Copy_u8PinNumber);
		}
		break;
	}
}
/*Read Pin Value*/
u8 DIO_u8GetPinValue(u8 Copy_u8PortID,u8 Copy_u8PinNumber)
{
	u8 LOC_u8PinState=0;
	switch(Copy_u8PortID)
	{
	case DIO_PORTA:
		LOC_u8PinState=GET_BIT(PINA,Copy_u8PinNumber);
		break;
	case DIO_PORTB:
		LOC_u8PinState=GET_BIT(PINB,Copy_u8PinNumber);
		break;
	case DIO_PORTC:
		LOC_u8PinState=GET_BIT(PINC,Copy_u8PinNumber);
		break;
	case DIO_PORTD:
		LOC_u8PinState=GET_BIT(PIND,Copy_u8PinNumber);
		break;
	}
	return LOC_u8PinState;
}


void DIO_VidSet_4MSBDirection(u8 Copy_u8PortID,u8 Copy_u8PinsDirection)
{
	switch(Copy_u8PortID)
	{
	case DIO_PORTA:
		DDRA&=0x0F;
		DDRA|=Copy_u8PinsDirection<<4;
		break;
	case DIO_PORTB:
		DDRB&=0x0F;
		DDRB|=Copy_u8PinsDirection<<4;
		break;
	case DIO_PORTC:
		DDRC&=0x0F;
		DDRC|=Copy_u8PinsDirection<<4;
		break;
	case DIO_PORTD:
		DDRD&=0x0F;
		DDRD|=Copy_u8PinsDirection<<4;
		break;
	}
}

void DIO_VidSet_4MSBValue(u8 Copy_u8PortID,u8 Copy_u8PinsValue)
{
	switch(Copy_u8PortID)
	{
	case DIO_PORTA:
		PORTA&=0x0F;
		PORTA|=Copy_u8PinsValue<<4;
		break;
	case DIO_PORTB:
		PORTB&=0x0F;
		PORTB|=Copy_u8PinsValue<<4;
		break;
	case DIO_PORTC:
		PORTC&=0x0F;
		PORTC|=Copy_u8PinsValue<<4;
		break;
	case DIO_PORTD:
		PORTD&=0x0F;
		PORTD|=Copy_u8PinsValue<<4;
		break;
	}
}

