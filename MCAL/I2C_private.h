
#ifndef I2C_PRIVATE_H_
#define I2C_PRIVATE_H_

#define TWCR		*((volatile u8*)0x56)
#define TWDR		*((volatile u8*)0x23)
#define TWAR		*((volatile u8*)0x22)
#define TWSR		*((volatile u8*)0x21)
#define TWBR		*((volatile u8*)0x20)




#define NoError							0
#define StartConditionError				1
#define RepeatedStartConditionError		2
#define SlaveAddressWithWriteError		3
#define SlaveAddressWithReadError		4

#endif /* I2C_PRIVATE_H_ */
