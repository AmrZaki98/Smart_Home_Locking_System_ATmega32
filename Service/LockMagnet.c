

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_INTERFACE.h"
#include "LockMagnetConfig.h"
#include "LockMagnet.h"



void LockMgnt_VidInit()
{
	DIO_VidSetPinDirection(LOCK_MAGNET_PORT,LOCK_MAGNET_PIN,PIN_OUTPUT);
}
void LockMgnt_VidOn()
{
	/*Note that the magnet is normally closed*/
	DIO_VidSetPinValue(LOCK_MAGNET_PORT,LOCK_MAGNET_PIN,PIN_LOW);
}
void LockMgnt_VidOff()
{
	DIO_VidSetPinValue(LOCK_MAGNET_PORT,LOCK_MAGNET_PIN,PIN_HIGH);
}
