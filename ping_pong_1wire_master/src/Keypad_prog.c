#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_interface.h"

#include "Keypad_config.h"
#include "Keypad_interface.h"
#include "Keypad_private.h"
/*R0 R1 R2 R3 C0 C1 C2 C3*/
u8 KEYPAD_GetPressedKey(void)
{
	u8 ROWSCounter;
	u8 COLSCounter;
	u8 flag=0;
	u8 pressedKey=KEYPAD_NOKEYPRESSED;
	static u8 KEYPAD_ROWSPortArray[KEYPAD_ROWSMAXNUM]=KEYPAD_ROWS_PORTS;
	static u8 KEYPAD_ROWSPinArray[KEYPAD_ROWSMAXNUM]=KEYPAD_ROWS_PINS;
	
	static u8 KEYPAD_COLSPortArray[KEYPAD_COLMAXNUM]=KEYPAD_COLS_PORTS;
	static u8 KEYPAD_COLSPinArray[KEYPAD_COLMAXNUM]=KEYPAD_COLS_PINS;
	
	static u8 KEYPAD_KEYSArray[KEYPAD_ROWSMAXNUM][KEYPAD_COLMAXNUM]=KEYPAD_KEYS;
	//static u8 KEYPAD_COlSPortArray[KEYPAD_COLSMAXNUM]=[KEYPAD_C0_PORT,KEYPAD_C1_PORT,KEYPAD_C2_PORT,KEYPAD_C3_PORT];
	
	
	for (ROWSCounter=0;(ROWSCounter<KEYPAD_ROWSMAXNUM) && (flag==0);ROWSCounter++)
	{
		/*put on each rows 0*/
		DIO_SetPinValue(KEYPAD_ROWSPortArray[ROWSCounter], KEYPAD_ROWSPinArray[ROWSCounter],0);

		/*check every col*/
		for(COLSCounter=0; (COLSCounter<KEYPAD_COLMAXNUM)&&( flag==0); COLSCounter++)
		{
			if(DIO_GetPinVal(KEYPAD_COLSPortArray[COLSCounter],KEYPAD_COLSPinArray[COLSCounter])==0)
			{
				//while(GetPinValue(KEYPAD_COLSPortArray[COLSCounter],KEYPAD_COLSPinArray[COLSCounter])==0);

				pressedKey=KEYPAD_KEYSArray[ROWSCounter][COLSCounter];
				//pressedKey=3;
				flag=1;
				//break;
			}
		}

		DIO_SetPinValue(KEYPAD_ROWSPortArray[ROWSCounter], KEYPAD_ROWSPinArray[ROWSCounter],1);
		
	}
	return pressedKey;
}
