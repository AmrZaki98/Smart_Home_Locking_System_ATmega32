

#include"STD_TYPES.h"
#include"DIO_Interface.h"
#include"Keypad_Config.h"
#include<util/delay.h>

u8 KeypadValues[4][4]={{'7','8','9','O'},{'4','5','6','C'},
					   {'1','2','3','L'},{'U','0','A','E'}};

void Keypad_VidInit(void)
{
	DIO_VidSetPinDirection(COL_PORT,COL_PIN0,PIN_OUTPUT);
	DIO_VidSetPinDirection(COL_PORT,COL_PIN1,PIN_OUTPUT);
	DIO_VidSetPinDirection(COL_PORT,COL_PIN2,PIN_OUTPUT);
	DIO_VidSetPinDirection(COL_PORT,COL_PIN3,PIN_OUTPUT);

	DIO_VidSetPinDirection(ROW_PORT,ROW_PIN0,PIN_INPUT);
	DIO_VidSetPinDirection(ROW_PORT,ROW_PIN1,PIN_INPUT);
	DIO_VidSetPinDirection(ROW_PORT,ROW_PIN2,PIN_INPUT);
	DIO_VidSetPinDirection(ROW_PORT,ROW_PIN3,PIN_INPUT);

	/*Active Pull Up Resistor To Row Pins */
	DIO_VidSetPinValue(ROW_PORT,ROW_PIN0,PIN_HIGH);
	DIO_VidSetPinValue(ROW_PORT,ROW_PIN1,PIN_HIGH);
	DIO_VidSetPinValue(ROW_PORT,ROW_PIN2,PIN_HIGH);
	DIO_VidSetPinValue(ROW_PORT,ROW_PIN3,PIN_HIGH);

	/*Set (1)Initial Value to Col Pins */
	DIO_VidSetPinValue(COL_PORT,COL_PIN0,PIN_HIGH);
	DIO_VidSetPinValue(COL_PORT,COL_PIN1,PIN_HIGH);
	DIO_VidSetPinValue(COL_PORT,COL_PIN2,PIN_HIGH);
	DIO_VidSetPinValue(COL_PORT,COL_PIN3,PIN_HIGH);


}
u8 Keypad_u8GetKeyPressed(void)
{
	u8 ColumnCount;
	u8 RowCount;
	u8 ReturnValue=255;

	for(ColumnCount=COL_INIT;ColumnCount<COL_END;ColumnCount++)
	{
		/*Select Column by using set zero*/
		DIO_VidSetPinValue(COL_PORT,ColumnCount,PIN_LOW);
		for(RowCount=ROW_INIT;RowCount<ROW_END;RowCount++)
		{
			if(DIO_u8GetPinValue(ROW_PORT,RowCount)==0)
			{
				ReturnValue=KeypadValues[RowCount-ROW_INIT][ColumnCount-COL_INIT];

				/*check on one pressed*/
				while(DIO_u8GetPinValue(ROW_PORT,RowCount)==0);

				/*De-bouncing*/
				_delay_ms(20);
				return ReturnValue;
			}
			else
			{
				/*Do Nothing*/
			}
		}
		/*Return the Column to idle state*/
		DIO_VidSetPinValue(COL_PORT,ColumnCount,PIN_HIGH);
	}
	return ReturnValue;
}
