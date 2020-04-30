// libs
#include "STD_TYPES.h"
#include "BIT_MAN.h"
// own
#include "DIO_interface.h"
#include "DIO_private.h"
#include "DIO_register.h"
#include "DIO_config.h"

void DIO_setPinVal(u8 port, u8 pin, u8 value)
{
   switch (port)
   {
      case 'A':
         if (value == 0)
         {
            PORTA = BIT_CLEAR(PORTA, pin);
         }
         else if (value == 1)
         {
            PORTA = BIT_SET(PORTA, pin);
         }
      break;
      
      case 'B':
         if (value == 0)
         {
            PORTB = BIT_CLEAR(PORTB, pin);
         }
         else if (value == 1)
         {
            PORTB = BIT_SET(PORTB, pin);
         }
      break;
      
      case 'C':
         if (value == 0)
         {
            PORTC = BIT_CLEAR(PORTC, pin);
         }
         else if (value == 1)
         {
            PORTC = BIT_SET(PORTC, pin);
         }
      break;
      
      case 'D':
         if (value == 0)
         {
            PORTD = BIT_CLEAR(PORTD, pin);
         }
         else if (value == 1)
         {
            PORTD = BIT_SET(PORTD, pin);
         }
      break;
   }
}

void DIO_togglePinVal(u8 port, u8 pin)
{
   switch (port)
   {
      case 'A':
         PORTA = BIT_TOGGLE(PORTA, pin);
      break;
      
      case 'B':
         PORTB = BIT_TOGGLE(PORTB, pin);
      break;
      
      case 'C':
         PORTC = BIT_TOGGLE(PORTC, pin);
      break;
      
      case 'D':
         PORTD = BIT_TOGGLE(PORTD, pin);
      break;
   }
}

void DIO_setPinPullup(u8 port, u8 pin, u8 value)
{
   switch (port)
   {
      case 'A':
         if (value == 0)
         {
            PORTA = BIT_CLEAR(PORTA, pin);
         }
         else if (value == 1)
         {
            PORTA = BIT_SET(PORTA, pin);
         }
      break;
      
      case 'B':
         if (value == 0)
         {
            PORTB = BIT_CLEAR(PORTB, pin);
         }
         else if (value == 1)
         {
            PORTB = BIT_SET(PORTB, pin);
         }
      break;
      
      case 'C':
         if (value == 0)
         {
            PORTC = BIT_CLEAR(PORTC, pin);
         }
         else if (value == 1)
         {
            PORTC = BIT_SET(PORTC, pin);
         }
      break;
      
      case 'D':
         if (value == 0)
         {
            PORTD = BIT_CLEAR(PORTD, pin);
         }
         else if (value == 1)
         {
            PORTD = BIT_SET(PORTD, pin);
         }
      break;
   }
}

u8 DIO_getPinVal(u8 port, u8 pin)
{
   switch (port)
   {
      case 'A':
         return BIT_GET(PINA, pin);
      break;
      
      case 'B':
         return BIT_GET(PINB, pin);
      break;
      
      case 'C':
         return BIT_GET(PINC, pin);
      break;
      
      case 'D':
         return BIT_GET(PIND, pin);
      break;

      default:
    	  return 0;
	  break;
   }
}

