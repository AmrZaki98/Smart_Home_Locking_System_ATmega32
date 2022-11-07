/*
 * DisplayMngr.h
 *
 *  Created on: Nov 5, 2022
 *      Author: TOP
 */

#ifndef DISPLAYMNGR_H_
#define DISPLAYMNGR_H_

typedef struct
{
	char * msgString;
	u8 MsgTimeOut;
}Msg_t;

typedef enum  {EnterPassword,Passed, WrongPassword, Confidential ,EnterNewPassword,VerifyPassword,
Clear}MessageType_t;

void DispMngr_DisplayMsg(Msg_t * Loc_msg);
void DipMngr_init();
void DispMngr_DisplayStandardMsg(MessageType_t MsgId);
#endif /* DISPLAYMNGR_H_ */
