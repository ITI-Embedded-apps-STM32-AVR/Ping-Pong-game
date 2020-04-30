/*Author: sara youssif*
version:V01
Date:14/1/2019*/

/*Description : This API shall inizalize LCD*/
#include "STD_TYPES.h"
#include "BIT_MAN.h"
#include "CLCD_config.h"
#include "CLCD_interface.h"
#include "DIO_interface.h"
#include <util/delay.h>

#define Display_control 0x0F



#define CLCD_LINE_1_CMCD 0x80
#define CLCD_LINE_2_CMCD 0xc0

void CLCD_VoidIntialize(void)
{
	DIO_setPinVal(CLCD_u8_RS_PORT,CLCD_u8_RS_PIN,0);
	DIO_setPinVal(CLCD_u8_RW_PORT,CLCD_u8_RW_PIN,0);
	DIO_setPinVal(CLCD_u8_E_PORT,CLCD_u8_E_PIN,0);
	/*set rs=1*/
	_delay_ms(40);
	CLCD_voidWriteCmd(0b00111111);
	CLCD_voidWriteCmd(0b00001100);
	CLCD_voidWriteCmd(0b00000001);

	/*set RW=0*/
	_delay_ms(2);

}

/*Description : This API shall display data on LCD*/
void CLCD_voidWriteDate(u8 Copy_u8Data)
{
	/*set rs=1*/
	DIO_setPinVal(CLCD_u8_RS_PORT,CLCD_u8_RS_PIN,1);
	/*set RW=0*/
	DIO_setPinVal(CLCD_u8_RW_PORT,CLCD_u8_RW_PIN,0);
	/*Set Data on Data Port*/
	CLCD_voidSetDataPort(Copy_u8Data);
	
	/*Enable pulse*/
	DIO_setPinVal(CLCD_u8_E_PORT,CLCD_u8_E_PIN,1);
	_delay_ms(1);
	DIO_setPinVal(CLCD_u8_E_PORT,CLCD_u8_E_PIN,0);
		_delay_ms(1);
}

/*Description : This API shall execute command on  LCD*/
void CLCD_voidWriteCmd(u8 copy_u8cmd)
{
	/*set rs=0*/
	DIO_setPinVal(CLCD_u8_RS_PORT,CLCD_u8_RS_PIN,0);
	/*set RW=0*/
	DIO_setPinVal(CLCD_u8_RW_PORT,CLCD_u8_RW_PIN,0);
	/*Set Data on Data Port*/
	CLCD_voidSetDataPort(copy_u8cmd);
	
	/*Enable pulse*/
	DIO_setPinVal(CLCD_u8_E_PORT,CLCD_u8_E_PIN,1);
	_delay_ms(1);
	DIO_setPinVal(CLCD_u8_E_PORT,CLCD_u8_E_PIN,0);
		_delay_ms(1);
}


void CLCD_voidSetDataPort(u8 Copy_u8Data)
{
	u8 Local_u8BitVal;
	Local_u8BitVal=BIT_GET(Copy_u8Data,0);
	DIO_setPinVal(CLCD_u8_DATA_PORT,CLCD_u8_D0,Local_u8BitVal);
	
	Local_u8BitVal=BIT_GET(Copy_u8Data,1);
	DIO_setPinVal(CLCD_u8_DATA_PORT,ClCD_u8_D1,Local_u8BitVal);
	
	Local_u8BitVal=BIT_GET(Copy_u8Data,2);
	DIO_setPinVal(CLCD_u8_DATA_PORT,CLCD_u8_D2,Local_u8BitVal);
	Local_u8BitVal=BIT_GET(Copy_u8Data,3);
	DIO_setPinVal(CLCD_u8_DATA_PORT,CLCD_u8_D3,Local_u8BitVal);
	Local_u8BitVal=BIT_GET(Copy_u8Data,4);
	DIO_setPinVal(CLCD_u8_DATA_PORT,CLCD_u8_D4,Local_u8BitVal);
	Local_u8BitVal=BIT_GET(Copy_u8Data,5);
	DIO_setPinVal(CLCD_u8_DATA_PORT,CLCD_u8_D5,Local_u8BitVal);
	Local_u8BitVal=BIT_GET(Copy_u8Data,6);
	DIO_setPinVal(CLCD_u8_DATA_PORT,CLCD_u8_D6,Local_u8BitVal);
	Local_u8BitVal=BIT_GET(Copy_u8Data,7);
	DIO_setPinVal(CLCD_u8_DATA_PORT,CLCD_u8_D7,Local_u8BitVal);
	
}
void CLCD_voidGOToLocation(u8 copy_LineNb,u8 copy_Postion)
{
	if(copy_LineNb == CLCD_LINE_1)
	{
		CLCD_voidWriteCmd(CLCD_LINE_1_CMCD + copy_Postion);
	}
	else if (copy_LineNb == CLCD_LINE_2)
	{
		CLCD_voidWriteCmd(CLCD_LINE_2_CMCD + copy_Postion);
	}
	else
	{

	}

}

void CLCD_voidWriteString(u8 * copy_pu8String)
{
	u8 Local_u8Counter=0;
	while(copy_pu8String[Local_u8Counter]!='\0' )
	{
		CLCD_voidWriteDate(copy_pu8String[Local_u8Counter]);
		Local_u8Counter++;
	}
}
