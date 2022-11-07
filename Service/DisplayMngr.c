/*
 * DisplayMngr.c
 *
 *  Created on: Nov 5, 2022
 *      Author: TOP
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "TIMER__interface.h"
#include "LCD_interface.h"
#include "LCD_config.h"
#include "DIO_interface.h"
#include "DisplayMngr.h"
#include "DIO_interface.h"
#define F_CPU		16000000UL


u16 GlobalInterruptCount=0;
u16 GlobalInterruptCountRequired=0;
Msg_t MsgToSend;
char MsgString[20];
static void CopyString(char * String_ptr, char * Content);
static void StaticLCDTimeOut();
void DipMngr_init()
{
	set_OCR0(250);
	Timer0_init();
	set_prescaler(SIXTYFOURTH);
	ClrOCR0Interrupt();
	DIO_VidSet_4MSBDirection(LCD_PORT,15);
	DIO_VidSetPinDirection(LCD_RS_PORT,LCD_RS_BIT,PIN_OUTPUT);
	DIO_VidSetPinDirection(LCD_RW_PORT,LCD_RW_BIT,PIN_OUTPUT);
	DIO_VidSetPinDirection(LCD_E_PORT,LCD_E_BIT,PIN_OUTPUT);
	LCD_vidInit_4bits();
	vidTimer0SetCallBackFunc(&StaticLCDTimeOut);
}

void DispMngr_DisplayMsg(Msg_t * Loc_msg)
{
	GlobalInterruptCount=0;
	GlobalInterruptCountRequired=0;
	char * String_msg=Loc_msg->msgString;
	u8 i=0;
	u8 NewLineFlag=0;
	while(*(String_msg+i)!=0)
	{
		if(*(String_msg+i)=='$')
		{
			LCD_VidClear();
		}
		else if(*(String_msg+i)=='\n')
		{
			LCD_VidNewLine();
			NewLineFlag=1;
		}
		else
			LCD_vidSendData_4bits(*(String_msg+i));

		i++;
		if(i>=16 && !NewLineFlag)
		{
			LCD_VidNewLine();
			NewLineFlag=1;
		}
	}

	GlobalInterruptCountRequired=1000*(Loc_msg->MsgTimeOut);

	if(GlobalInterruptCountRequired>0)
	{
		SetOCR0Interrupt();
	}
	else
	{
		ClrOCR0Interrupt();
	}
}


static void StaticLCDTimeOut()
{

	if(GlobalInterruptCountRequired==0)
	{

		return;
	}
	else
		{
		if(GlobalInterruptCountRequired<=GlobalInterruptCount)
		{

			LCD_VidClear();
			GlobalInterruptCount=0;
			GlobalInterruptCountRequired=0;
		}
		else
		{
			GlobalInterruptCount++;

		}
		}
}

void DispMngr_DisplayStandardMsg(MessageType_t MsgId)
{

	switch(MsgId)
	{
	case EnterPassword:
		CopyString(MsgString,"$Enter Password:\n");
		MsgToSend.msgString=MsgString;
		MsgToSend.MsgTimeOut=0;
		DispMngr_DisplayMsg(&MsgToSend);
		break;
	case Passed:
		CopyString(MsgString,"$Passed\n");
		MsgToSend.msgString=MsgString;
		MsgToSend.MsgTimeOut=1;
		DispMngr_DisplayMsg(&MsgToSend);
		break;
	case WrongPassword:
		CopyString(MsgString,"$Wrong Password\n");
		MsgToSend.msgString=MsgString;
		MsgToSend.MsgTimeOut=1;
		DispMngr_DisplayMsg(&MsgToSend);
		break;
	case Confidential:
		CopyString(MsgString,"*");
		MsgToSend.msgString=MsgString;
		MsgToSend.MsgTimeOut=1;
		DispMngr_DisplayMsg(&MsgToSend);
		break;
	case EnterNewPassword:
		CopyString(MsgString,"$New Password:\n");
		MsgToSend.msgString=MsgString;
		MsgToSend.MsgTimeOut=0;
		DispMngr_DisplayMsg(&MsgToSend);
		break;

	case VerifyPassword:
		CopyString(MsgString,"$Verify password\n");
		MsgToSend.msgString=MsgString;
		MsgToSend.MsgTimeOut=0;
		DispMngr_DisplayMsg(&MsgToSend);
		break;
	case Clear:
		LCD_VidClear();
		break;
	}
}

static void CopyString(char * String_ptr, char * Content)
{
	u8 i=0;
	while(*(Content+i) !=0)
	{
		*(String_ptr+i)=*(Content+i);
		i++;
	}
	*(String_ptr+i)=0;
}

