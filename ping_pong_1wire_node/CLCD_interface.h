/*Author: sara youssif*
version:V01
Date:14/1/2019*/

/*Description : This API shall inizalize LCD*/

void CLCD_VoidIntialize(void);

/*Description : This API shall display data on LCD*/
void CLCD_voidWriteDate(u8 Copy_u8Data);


/*Description : This API shall execute command on  LCD*/
void CLCD_voidWriteCmd(u8 copy_u8cmd);

void CLCD_voidSetDataPort(u8 Copy_u8Data);

void CLCD_voidGOToLocation(u8 copy_LineNb,u8 copy_Postion);
void CLCD_voidWriteString(u8 * copy_pu8String);
#define Display_control 0x0F
#define return_home 0x02
#define Entry_shiftleft_Mode 0x03
#define Entry_shiftright_Mode 0x01
#define Clear_Display 0x01
#define CLCD_LINE_1 1
#define CLCD_LINE_2 2
