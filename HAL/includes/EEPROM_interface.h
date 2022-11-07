/*
 * EEPROM_interface.h
 *
 *  Created on: Mar 25, 2022
 *      Author: TOP
 */

#ifndef EEPROM_INTERFACE_H_
#define EEPROM_INTERFACE_H_

void EEPROM_VidSendData(u8 LocU8Address,u8 LocU8Word,u8 U8Word);
u8 EEPROM_U8GetData(u8 LocU8Address,u8 LocU8Word);
void EEPROM_VidWriteString(u8 LocU8Address,u8 StartWord,char * Locstr);
#endif /* EEPROM_INTERFACE_H_ */
