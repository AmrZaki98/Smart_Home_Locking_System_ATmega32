

#include"STD_TYPES.h"
#include"DIO_Interface.h"

#include"DisplayMngr.h"
#include"Keypad_Interface.h"
#include<util/delay.h>

#include "LCD_interface.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"



#include"STD_TYPES.h"
#include"DIO_Interface.h"
#include<util/delay.h>
#include "EEPROM_interface.h"
#include "PasswordCheck.h"
#include "DisplayMngr.h"
#include "LockMagnet.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

/*The main states of the locking system*/
#define LOCKED			0  /*The magnet is on, the door can't be opened*/
#define REQUESTED		1  /*A request has been made to open the door,
 	 	 	 	 	 	 	 the system is waiting for the password*/
#define UNLOCKED		2  /*Magnet off, the door could be opened*/
#define UPDATEPASSWORD	3  /*The user wants to change the password*/


/*The status of the password when it is changed*/
#define FIRSTPASSWORD	0
#define SECONDPASSWORD	1

/*********************************************************************************************************/

/*Global variables*/


/*Initial states of the system*/
u8 SecurityState=LOCKED;
u8 PasswordState=FIRSTPASSWORD;

/*The password variables, to store the user's password*/
char Password[15]="789456123";
u8 PasswordLength=9;
char EnteredPassWord[15];

/*The queue for the messages displayed on the LCD*/
xQueueHandle MsgQueue;

/*The message to be sent*/
MessageType_t MsgToSendId;

/********************************************************************************************************/

/*Helper functions*/


/*Clear a certain string data */
void ClrPassword(char * LocPasswordAddress)
{
	for(u8 i=0;i<15;i++)
	{
		 LocPasswordAddress[i]=0;
	}
}

/*Insert a character to a specific location in a string*/
void InsertPasswordChar(char * PasswordString, u8 LocCharLocation,u8 LocCharData)
{
	PasswordString[LocCharLocation]=LocCharData;
	MsgToSendId=Confidential;
	xQueueSend(MsgQueue,&MsgToSendId,20);

}

/***************************************************************************************************/

/*The tasks*/




/*This is the state machine implementation */

void SecurityStateChartTask(void * pvParameter)
{

	u8 Result; /*Data from the keypad*/

	u8 LocPassWordCounter=0;

	while(1)
	{

		Result=Keypad_u8GetKeyPressed();

		switch(SecurityState)
		{

		/*Locked state*/
		case LOCKED:
			ClrPassword(EnteredPassWord);
			ClrPassword(Password);
			LocPassWordCounter=0;
			if(Result=='O') /*The user request to open the door*/
			{
				SecurityState=REQUESTED;  /*Update the state to requested*/

				MsgToSendId=EnterPassword;  /*Enter password message required to appear on the LCD*/
				xQueueSend(MsgQueue,&MsgToSendId,20); /*Send the message to the LCD display task*/

			}
			LockMgnt_VidOn();
			break;



		case REQUESTED:

			LockMgnt_VidOn();
			/*If the keypad input is a number, add it to the password string*/
			if(Result>47 && Result<58)
			{
				InsertPasswordChar(EnteredPassWord,LocPassWordCounter,Result);
				LocPassWordCounter++;
			}
			/*If the user presses enter, compare the password to the one stored in the EEPROM*/
			else if(Result=='E')
			{
				LocPassWordCounter=0;

				if(CheckPassword(EnteredPassWord)==CORRECT)
				{

					MsgToSendId=Passed; /*Sent success message to the user*/
					xQueueSend(MsgQueue,&MsgToSendId,20);

					ClrPassword(EnteredPassWord);
					SecurityState=UNLOCKED;

				}
				else
				{

					MsgToSendId=WrongPassword; /*Send password message to the user*/
					xQueueSend(MsgQueue,&MsgToSendId,20);

					ClrPassword(EnteredPassWord);
					SecurityState=LOCKED;
				}
			}
			/*The clear key, for the user to start typing the password again*/
			else if(Result=='C')
			{
				LocPassWordCounter=0;
				ClrPassword(EnteredPassWord);
				MsgToSendId=EnterPassword;
				xQueueSend(MsgQueue,&MsgToSendId,20);
			}

			/*If the user wants to abort  password typing and return to the locked state*/
			if(Result=='L')
			{
				SecurityState=LOCKED;
				MsgToSendId=Clear;
				xQueueSend(MsgQueue,&MsgToSendId,20);
			}



			break;


		/*The door unlocked state*/
		case UNLOCKED:

			LockMgnt_VidOff(); /*Unlock the door*/
			/*If the user wants to lock the door*/
			if(Result=='L')
			{
				SecurityState=LOCKED;
				MsgToSendId=Clear;
				xQueueSend(MsgQueue,&MsgToSendId,20);
			}

			/*If the user requests to change the password*/
			else if(Result=='A')
			{
				LocPassWordCounter=0;
				ClrPassword(EnteredPassWord);
				ClrPassword(Password);
				SecurityState=UPDATEPASSWORD;
				MsgToSendId=EnterNewPassword;  /*Enter new password message will appear*/
				xQueueSend(MsgQueue,&MsgToSendId,20);
			}

			break;

			/*The update password state*/
		case UPDATEPASSWORD:
			/*If the user wants to abort typing the new password and enter the locked state*/
			if(Result=='L')
			{
				SecurityState=LOCKED;
				MsgToSendId=Clear;
				xQueueSend(MsgQueue,&MsgToSendId,20);
				PasswordState=FIRSTPASSWORD;
			}
			/*If the user wants to abort typing the new password and return to the unlocked state*/
			if(Result=='O')
			{
				LocPassWordCounter=0;
				ClrPassword(EnteredPassWord);
				ClrPassword(Password);
				SecurityState=UNLOCKED;
				MsgToSendId=Clear;
				xQueueSend(MsgQueue,&MsgToSendId,20);
				PasswordState=FIRSTPASSWORD;
			}

			/*Since the user must verify the new password, there are two states dedicated to changing the password*/
			switch(PasswordState)
			{
			/*If the user didn't write the new password yet, the system is in the FIRSTPASSWORD state*/
			case FIRSTPASSWORD:
				/*If it is a number, add it to the new password variable*/
				if(Result>47 && Result<58)
				{
					InsertPasswordChar(EnteredPassWord,LocPassWordCounter,Result);
					LocPassWordCounter++;
				}
				/*If the user press enter, change the state from FIRSTPASSWORD to SECONDPASSWORD*/
				else if(Result=='E')
				{
					LocPassWordCounter=0;
					PasswordState=SECONDPASSWORD;
					MsgToSendId=VerifyPassword; /*Ask the user to verify his password*/
					xQueueSend(MsgQueue,&MsgToSendId,20);

				}
				/*The user could clear the password he wrote and starts over again*/
				else if(Result=='C')
				{
					LocPassWordCounter=0;
					ClrPassword(EnteredPassWord);
					MsgToSendId=EnterNewPassword;
					xQueueSend(MsgQueue,&MsgToSendId,20);
				}
				break;

				/*In case the user wrote the password, this state is dedicated to verifying the new password*/
			case SECONDPASSWORD:

				/*If it is a number, add it to the verefication password*/
				if(Result>47 && Result<58)
				{
					InsertPasswordChar(Password,LocPassWordCounter,Result);
					LocPassWordCounter++;
				}
				/*Pressing enter checks if the two newly added password are identical
				 * If they are identical, the password will be updated in the eeprom
				 */
				else if(Result=='E')
				{
					LocPassWordCounter=0;
					PasswordState=FIRSTPASSWORD;
					if(UpdatePassword(EnteredPassWord,Password)==CORRECT)
					{

						ClrPassword(Password);
						ClrPassword(EnteredPassWord);
						MsgToSendId=Passed; /*Inform the user that the password was updated successfully*/
						xQueueSend(MsgQueue,&MsgToSendId,20);
					}
					else
					{

						ClrPassword(EnteredPassWord);
						ClrPassword(Password);
						MsgToSendId=WrongPassword; /*Inform the user that the two passwords entered are different*/
						xQueueSend(MsgQueue,&MsgToSendId,20);
					}
					SecurityState=UNLOCKED;
				}
				/*The user could clear the verfication password and starts writing it again*/
				else if(Result=='C')
				{
					LocPassWordCounter=0;
					ClrPassword(Password);
					MsgToSendId=VerifyPassword;
					xQueueSend(MsgQueue,&MsgToSendId,20);
				}
				break;
			}

		}

		vTaskDelay(20);
	}
}


/*Task responsible to display the messages*/
void LCD_DISP2(void * pvParameter)
{
	portBASE_TYPE  b;
	MessageType_t Msg_received;

	while(1)
	{

		b=xQueueReceive(MsgQueue,&Msg_received, 40);


		if(b==pdPASS )
		{


			DispMngr_DisplayStandardMsg(Msg_received);
		}


	}
}

int main(void)
{
	DIO_VidSetPinDirection(DIO_PORTC,2,PIN_OUTPUT);
	DIO_VidSetPinDirection(DIO_PORTC,7,PIN_OUTPUT);
	DIO_VidSetPinDirection(DIO_PORTD,7,PIN_OUTPUT);


	LockMgnt_VidInit();
	u8 Result;

	DipMngr_init();



	/*Put the initial password*/
	EEPROM_VidSendData(0,0,9);
	EEPROM_VidWriteString(0,1,Password);

	_delay_ms(100);

	LCD_VidClear();


	Keypad_VidInit();


	MsgQueue=  xQueueCreate( 48,sizeof(MessageType_t) );


	xTaskCreate(    &SecurityStateChartTask,"Security State Chart",200,NULL,1,NULL);
	xTaskCreate(    &LCD_DISP2,"LCD",200, NULL,0,NULL);

	vTaskStartScheduler();

	while(1);

	return 0;
}
