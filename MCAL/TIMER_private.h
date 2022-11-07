

#ifndef TIMER_PRIVATE_H_
#define TIMER_PRIVATE_H_

#define TCNT0 *( (volatile u8 *)0x52)
#define TCCR0 *( (volatile u8 *)0x53)
#define TIMSK *( (volatile u8 *)0x59)
#define SREG  *( (volatile u8 *)0x5F)
#define OCR0  *( (volatile u8 *)0x5C)

#endif /* TIMER_PRIVATE_H_ */
