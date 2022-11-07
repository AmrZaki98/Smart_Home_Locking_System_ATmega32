

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "PasswordCheck.h"
#include "EEPROM_interface.h"
#include "PsswordCheckPrivate.h"

PassStatus CheckPassword(char *Password)
{
	u8 PassSize=EEPROM_U8GetData(EEPROM_BLOCK,EEPROM_WORD);
	u8 i=1;
	for(;i<PassSize;i++)
	{

		if(EEPROM_U8GetData(EEPROM_BLOCK,i)!=Password[i-1])
		{
			return WRONG;
		}
	}

	if(Password[i]!=0)
	{
		return WRONG;
	}

	return CORRECT;
}
PassStatus UpdatePassword(char* NewPassword, char* VerNewPassword)
{
	u8 LocPassSize=0;
	while(*(NewPassword+LocPassSize) !=0)
	{
		if(*(NewPassword+LocPassSize)!=*(VerNewPassword+LocPassSize))
		{
			return WRONG;
		}
		LocPassSize++;
	}
	if(*(VerNewPassword+LocPassSize)!=0)
		return WRONG;


	EEPROM_VidSendData(EEPROM_BLOCK,EEPROM_WORD,LocPassSize);
	EEPROM_VidWriteString(EEPROM_BLOCK,EEPROM_WORD+1,NewPassword);
	return CORRECT;
}
