/*
 * EEPROM_program.c
 *
 *  Created on: Mar 25, 2022
 *      Author: TOP
 */

#include "STD_TYPES.h"
#include "I2C_interface.h"
#include "I2C_config.h"
#include "DIO_interface.h"
#include <util/delay.h>
#include"LCD_Interface.h"


void EEPROM_VidSendData(u8 LocU8Address,u8 LocU8Word,u8 u8Word)
{
	I2C_VidMasterInit();
	I2C_LocErrSendStartCondition();
	I2C_LocErrSlaveWrite(0b01010000|LocU8Address);

	I2C_VidSendData(LocU8Word);


	I2C_VidSendData(u8Word);

	I2C_VidErrSendStopCondition();

	_delay_ms(10);
}
u8 EEPROM_U8GetData(u8 LocU8Address,u8 LocU8Word)
{
	I2C_VidMasterInit();
	I2C_LocErrSendStartCondition();
	I2C_LocErrSlaveWrite(0b01010000|LocU8Address);
	I2C_VidSendData(LocU8Word);
	I2C_LocErrSendRepeatedStartCondition();
	I2C_LocErrSlaveRead(0b01010000|LocU8Address);
	CLR_Ack();
	u8 u8Word=I2C_u8GetData();

	I2C_VidErrSendStopCondition();

	_delay_ms(10);

	return u8Word;
}

void EEPROM_VidWriteString(u8 LocU8Address,u8 StartWord,char * Locstr)
{
	u8 i=0;
	while(*(Locstr+i)!=0)
	{
		EEPROM_VidSendData(LocU8Address,StartWord+i,*(Locstr+i));

		i++;
		_delay_ms(20);
	}

}


