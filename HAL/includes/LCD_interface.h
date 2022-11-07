


#ifndef LCD_INTERFACE_H_
#define LCD_INTERFACE_H_

//#define LCD_vidSendData_4bits(LCD_data)     LCD_vidSendData((LCD_data>>4)); LCD_vidSendData(LCD_data)

void LCD_vidInit_4bits();
void LCD_vidSendCommand(u8 LCD_Instruction);
void LCD_vidSendData(u8 LCD_data);
void LCD_vidSendData_4bits(u8 LCD_data);
void LCD_VidSendString(u8*PtrToString);
void LCD_VidSelectPosition(u8 Column,u8 Row);
void LCD_VidClear();
void LCD_VidNewLine();


#endif /* LCD_INTERFACE_H_ */


