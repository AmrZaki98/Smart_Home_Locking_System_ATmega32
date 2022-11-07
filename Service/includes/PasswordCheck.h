/*
 * PasswordCheck.h
 *
 *  Created on: Nov 3, 2022
 *      Author: TOP
 */

#ifndef PASSWORDCHECK_H_
#define PASSWORDCHECK_H_

typedef enum {WRONG,CORRECT} PassStatus;

PassStatus CheckPassword(char *Password);
PassStatus UpdatePassword(char* NewPassword, char* VerNewPassword);


#endif /* PASSWORDCHECK_H_ */
