/*
 * LCD_private.h
 *
 *  Created on: Oct 16, 2021
 *      Author: TOP
 */

#ifndef LCD_PRIVATE_H_
#define LCD_PRIVATE_H_



//Some Commands for the data to the LCD

#define Function_set_4_bit_mode_default     	0b00101000
#define DISPLAY_ON_CURSOR_ON_BLINKING_ON		0b00001111
#define DISPLAY_ON_CURSOR_ON_BLINKING_OFF		0b00001110
#define DISPLAY_ON_CURSOR_OFF_BLINKING_OFF		0b00001100
#define DISPLAY_OFF_CURSOR_OFF_BLINKING_OFF		0b00001000

#define DISPLAY_DEFAULT  DISPLAY_ON_CURSOR_ON_BLINKING_ON

#define DISPLAY_CLR       						0b00000001
#define ENTRY_MODE_SET_DEFAULT					0b00000010

#endif /* LCD_PRIVATE_H_ */
