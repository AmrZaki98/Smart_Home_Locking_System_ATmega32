/*
 * LCD_program.c

 *
 *  Created on: Oct 16, 2021
 *      Author: TOP
 */
#include <string.h>
#include <util/delay.h>
#include "STD_TYPES.h"
#include "LCD_config.h"
#include "DIO_Interface.h"
#include "LCD_private.h"
#include "LCD_interface.h"




void LCD_vidSendCommand(u8 LCD_Instruction)
{
	//set the RS pin to 0--> I am about to send a command
	 DIO_VidSetPinValue(LCD_RS_PORT,LCD_RS_BIT,PIN_LOW);
	//set the RW pin to 0--> I am about to write
	 DIO_VidSetPinValue(LCD_RW_PORT,LCD_RW_BIT,PIN_LOW);
	 DIO_VidSet_4MSBValue(LCD_PORT,LCD_Instruction);
	 DIO_VidSetPinValue(LCD_E_PORT,LCD_E_BIT,PIN_HIGH);
	 _delay_ms(5);
	 DIO_VidSetPinValue(LCD_E_PORT,LCD_E_BIT,PIN_LOW);
	 _delay_ms(2);
}



void LCD_vidInit_4bits()
{
	_delay_ms(35);
	LCD_vidSendCommand(Function_set_4_bit_mode_default>>4);
	LCD_vidSendCommand(Function_set_4_bit_mode_default>>4);
	LCD_vidSendCommand(Function_set_4_bit_mode_default);
	_delay_ms(1);
	LCD_vidSendCommand(DISPLAY_DEFAULT>>4);
	LCD_vidSendCommand(DISPLAY_DEFAULT);
	_delay_ms(1);
	LCD_vidSendCommand(DISPLAY_CLR>>4);
	LCD_vidSendCommand(DISPLAY_CLR);
	_delay_ms(2);
	LCD_vidSendCommand(ENTRY_MODE_SET_DEFAULT>4);
	LCD_vidSendCommand(ENTRY_MODE_SET_DEFAULT);
}


void LCD_vidSendData(u8 LCD_data)
{
	//set the RS pin to 0--> I am about to send a data
	 DIO_VidSetPinValue(LCD_RS_PORT,LCD_RS_BIT,PIN_HIGH);
	//set the RW pin to 0--> I am about to write
	 DIO_VidSetPinValue(LCD_RW_PORT,LCD_RW_BIT,PIN_LOW);

	 DIO_VidSet_4MSBValue(LCD_PORT,LCD_data);
	 DIO_VidSetPinValue(LCD_E_PORT,LCD_E_BIT,PIN_HIGH);
	 _delay_ms(5);
	 DIO_VidSetPinValue(LCD_E_PORT,LCD_E_BIT,PIN_LOW);
	 _delay_ms(2);

}

void LCD_vidSendData_4bits(u8 LCD_data)
{
	LCD_vidSendData((LCD_data>>4));
	LCD_vidSendData(LCD_data);
}

void LCD_VidSendString(u8*PtrToString)
{
	char C= *PtrToString;
	int i=0;
	while(C!=0)
	{
		LCD_vidSendData_4bits(C);

		i=i+1;

		C=*(PtrToString+i);

	}
}

void LCD_VidSendNumber(s16 Number)
{
	if(Number==0)
	{
		u8 x=48;
		LCD_vidSendData_4bits(x);
		return;
	}
	u8 N [10];
	s16 N2=Number;
	int i=0;
	if(Number>0)
	{
		/*
		while(N2!=0)
		{
			*(N+i)=(Number%10)+48;
			N2=(N2-N2%10)/10;
			*(N+i+1)=0;
		}
		*/
		while(N2!=0)
		{
			u8 x=(N2%10)+48;
			//LCD_vidSendData_4bits(x);
			*(N+i)=(u8)x;

			*(N+i+1)=0;
			N2=(N2-N2%10)/10;
			i=i+1;
		}
		swap(N,i);
		LCD_VidSendString(&N);
	}

	else
	{
		LCD_vidSendData_4bits('-');
		LCD_VidSendNumber(-Number);

	}


}



void swap(u8 * N,int size)
{
	u8 temp=0;
	for(int i=0;i<(size/2);i++)
	{
		temp=*(N+i);
		*(N+i)=*(N+size-i-1);
		*(N+size-i-1)=temp;
	}
}


void LCD_VidSelectPosition(u8 Column,u8 Row)
{
	u8 command =0b10100111;
	command=0b11000000;
	LCD_vidSendCommand(command>>4);
	LCD_vidSendCommand(command);
}


void LCD_VidClear()
{
	LCD_vidSendCommand(0x01>>4);
	LCD_vidSendCommand(0x01);
}

void LCD_VidNewLine()
{
	LCD_VidSelectPosition(12,5);
}
