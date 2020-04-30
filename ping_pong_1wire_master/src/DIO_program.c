#include "STD_TYPES.H"
#include "BIT_MATH.h"
#include "DIO_interface.h"
#include "DIO_register.h"
#include "DIO_private.h"
#include "DIO_config.h"

void DIO_SetPinMode(u8 Port , u8 Pin, u8 Mode)
{
	switch (Port)
	{
	case 'A':
		if(Pin<=7)
		{
			/*clear 4 bits */
			PORTA_CRL &= ~(0b1111<<(Pin *4));
			/*set mod in 4 bits*/
			PORTA_CRL |= (Mode   <<(Pin *4));
		}
		else if(Pin<=15)
		{
			/*dah 3shan el crh  fa tar7na 8 */
			Pin=Pin-8;
			PORTA_CRH &= ~(0b1111<<(Pin *4));
			PORTA_CRH |= (Mode   <<(Pin *4));
		}
		break;
	case 'B':
		if(Pin<=7)
		{
			/*clear 4 bits */
			PORTB_CRL &= ~(0b1111<<(Pin *4));
			/*set mod in 4 bits*/
			PORTB_CRL |= (Mode   <<(Pin *4));
		}
		else if(Pin<=15)
		{
			/*dah 3shan el crh  fa tar7na 8 */
			Pin=Pin-8;
			PORTB_CRH &= ~(0b1111<<(Pin *4));
			PORTB_CRH |= (Mode   <<(Pin *4));
		}
		break;
	case 'C':

		if((Pin>=13) &&(Pin<=15))
		{
			/*dah 3shan el crh  fa tar7na 8 */
			Pin=Pin-8;
			PORTC_CRH &= ~(0b1111<<(Pin *4));
			PORTC_CRH |= (Mode   <<(Pin *4));
		}
		break;

	}
}
void DIO_SetPinValue(u8 Port , u8 Pin, u8 Val)
{
	switch (Port)
	{
	case 'A':
		if(Val==1)
		{
			SET_BIT(PORTA_ODR,Pin);
		}
		else
		{
			CLEAR_BIT(PORTA_ODR,Pin);
		}
		break;
	case 'B':
		if(Val==1)
		{
			SET_BIT(PORTB_ODR,Pin);
		}
		else
		{
			CLEAR_BIT(PORTB_ODR,Pin);
		}
		break;
	case 'C':
		if(Val==1)
		{
			SET_BIT(PORTC_ODR,Pin);
		}
		else
		{
			CLEAR_BIT(PORTC_ODR,Pin);
		}
		break;
	}
}
u8 DIO_GetPinVal(u8 Port, u8 Pin)
{
	u8 Result = 0;
	switch(Port)
	{
	case 'A':

		Result= GET_BIT(PORTA_IDR,Pin);
		break;
	case 'B':
		Result= GET_BIT(PORTB_IDR,Pin);
		break;
	case 'C':
		Result= GET_BIT(PORTC_IDR,Pin);
		break;
	}
	return Result;
}
