
#ifndef I2C_INTERFACE_H_
#define I2C_INTERFACE_H_

typedef u8 LocErr;

void I2C_VidMasterInit();
//void I2C_VidSlaveInit(u8 Copy_u8Address);
LocErr I2C_LocErrSendStartCondition();
LocErr I2C_LocErrSendRepeatedStartCondition();
void I2C_VidErrSendStopCondition();
LocErr I2C_LocErrSlaveWrite(u8 Copy_u8Address);
LocErr I2C_LocErrSlaveRead(u8 Copy_u8Address);
void I2C_VidSendData(u8 Copy_u8Data);
u8 I2C_u8GetData();
void CLR_Ack();

#endif /* I2C_INTERFACE_H_ */
