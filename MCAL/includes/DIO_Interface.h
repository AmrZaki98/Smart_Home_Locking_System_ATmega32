/*
 * DIO_Interface.h
 *
 *  Created on: Oct 15, 2021
 *      Author: gerges
 */

#ifndef DIO_INTERFACE_H_
#define DIO_INTERFACE_H_

#define DIO_PORTA     0
#define DIO_PORTB     1
#define DIO_PORTC     2
#define DIO_PORTD     3

#define PIN_OUTPUT    1
#define PIN_INPUT     0

#define PIN_HIGH      1
#define PIN_LOW       0

#define PORT_OUTPUT    255
#define PORT_INPUT     0

typedef enum
{
	PIN0=0,
	PIN1,
	PIN2,
	PIN3,
	PIN4,
	PIN5,
	PIN6,
	PIN7
}Pin_t;

/*Set Pin Direction */
void DIO_VidSetPinDirection(u8 Copy_u8PortID,u8 Copy_u8PinNumber,u8 Copy_u8PinDirection);
/*Set Pin Value*/
void DIO_VidSetPinValue(u8 Copy_u8PortID,u8 Copy_u8PinNumber,u8 Copy_u8PinValue);
/*Read Pin Value*/
u8 DIO_u8GetPinValue(u8 Copy_u8PortID,u8 Copy_u8PinNumber);


void DIO_VidSet_4MSBDirection(u8 Copy_u8PortID,u8 Copy_u8PinsDirection);
void DIO_VidSet_4MSBValue(u8 Copy_u8PortID,u8 Copy_u8PinsValue);


#endif /* DIO_INTERFACE_H_ */
