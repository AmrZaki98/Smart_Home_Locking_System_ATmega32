/*
 * I2C_program.c
 *
 *  Created on: Mar 25, 2022
 *      Author: TOP
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_Interface.h"
#include "DIO_config.h"
#include "I2C_private.h"
#include "I2C_interface.h"
#include "I2C_config.h"

void CLR_Ack()
{
	CLR_BIT(TWCR,6);
}

void I2C_VidMasterInit()
{
	SET_BIT(TWCR,6);
	//The frequency required is (100/16) kHz
	TWBR=160;
	CLR_BIT(TWSR,1);
	CLR_BIT(TWSR,0);
	SET_BIT(TWCR,2);


}
//void I2C_VidSlaveInit(u8 Copy_u8Address);
LocErr I2C_LocErrSendStartCondition()
{
	SET_BIT(TWCR,5);
	SET_BIT(TWCR,7);
	while(!GET_BIT(TWCR,7));

	if((TWSR&0b11111000)==0x08)
	{
		return NoError;
	}
	else
	{
		return StartConditionError;
	}

}
LocErr I2C_LocErrSendRepeatedStartCondition()
{
	SET_BIT(TWCR,5);
	SET_BIT(TWCR,7);
	while(!GET_BIT(TWCR,7));
	if((TWSR&0b11111000)==0x10)
	{

		return NoError;
	}
	else
	{
		return RepeatedStartConditionError;
	}
}
void I2C_VidErrSendStopCondition()
{
	SET_BIT(TWCR,4);
	SET_BIT(TWCR,7);
	while(GET_BIT(TWCR,4));

}
LocErr I2C_LocErrSlaveWrite(u8 Copy_u8Address)
{
	TWDR=Copy_u8Address<<1;
	CLR_BIT(TWDR,0);
	CLR_BIT(TWCR,5);  //The start condition bit must be cleared after putting the data in the TWDR
	SET_BIT(TWCR,7);
	while(!GET_BIT(TWCR,7));
	if((TWSR&0b11111000)==0x18 )
	{
		return NoError;
	}

	else
	{

		return SlaveAddressWithWriteError;
	}

}
LocErr I2C_LocErrSlaveRead(u8 Copy_u8Address)
{
	TWDR=Copy_u8Address<<1;
	SET_BIT(TWDR,0);
	CLR_BIT(TWCR,5);
	SET_BIT(TWCR,7);


	while(!GET_BIT(TWCR,7));
	if((TWSR&0b11111000)==0x40)
	{
		return NoError;
	}
	else
	{
		return SlaveAddressWithReadError;
	}
}
void I2C_VidSendData(u8 Copy_u8Data)
{

	TWDR=Copy_u8Data;
	SET_BIT(TWCR,7);
	while(!GET_BIT(TWCR,7));
}
u8 I2C_u8GetData()
{
	SET_BIT(TWCR,7);
	while(!GET_BIT(TWCR,7));


	return TWDR;
}
