// libs
#include "STD_TYPES.h"
#include "BIT_MAN.h"
#include "Delay_interface.h"
// MCAL
#include "PORT_interface.h"
#include "DIO_interface.h"
#include "CLCD_interface.h"
// srv
#include "OneWireProtocol_interface.h"

#define UC_ID 0

#define MSG_RACKET       0
#define MSG_DISPLAY_TEXT 1
#define MSG_BALL         2
#define MSG_CLEAR_BALL   3

#define RACKET_UP   0
#define RACKET_DOWN 1

#define TEXT_WIN  0
#define TEXT_LOSE 1

#define BALL_YAXIS_UP   0
#define BALL_YAXIS_DOWN 1


#define POS_0   0
#define POS_1   1
#define POS_2   2
#define POS_3   3
#define POS_4   4
#define POS_5   5
#define POS_6   6
#define POS_7   7
#define POS_8   8
#define POS_9   9
#define POS_10  10
#define POS_11  11
#define POS_12  12
#define POS_13  13
#define POS_14  14
#define POS_15  15


OneWire_t proto1 = {
		.port = 'D',
		.pin = 0
};

void main(void)
{
	/* protocol = D0 */
	/* LCD = port A */

	/* init pins */
	initPort();

	/* init 1-wire protocol */
	OneWireProtocol_init(ONE_WIRE_AS_RECEIVER, &proto1);

	/*init lcd*/
	CLCD_VoidIntialize();


	/* holds value of frame, msg ID, and decoded data */
	u8 frame = 0;
	u8 msgID = 0;
	u8 data = 0;

	/* values of ball position, current and new */
	u8 ballX_current = 0;
	u8 ballY_current = 0;
	u8 ballX_new = 0;
	u8 ballY_new = 0;


	/* value of racket, current and new */
	u8 racketY_current = 0;
	//u8 racketY_new = 0;
	/*string  for win and lose*/
	char *win = "Win ^_^";
	char *lose = "Lose x_x";
	while (1)
	{
		/* if a valid frame is received */
		if (OneWireProtocol_read(&frame, &proto1) == OneWireErr_Rx_Success)
		{
			/* if uC ID == 0 */
			if (BIT_GET(frame, 7) == UC_ID)
			{
				/* decode msg ID */
				msgID = (frame >> 5) & 0b00000011;
				data  = frame        & 0b00011111;

				switch (msgID)
				{
				case MSG_RACKET:
					if (data == RACKET_UP)
					{
						// TODO:
						CLCD_voidGOToLocation(CLCD_LINE_2,POS_15);
						CLCD_voidWriteDate(' ');
						CLCD_voidGOToLocation(CLCD_LINE_1,POS_15);
						CLCD_voidWriteDate('I');
						racketY_current=data;
					}
					else if (data == RACKET_DOWN)
					{
						// TODO:
						CLCD_voidGOToLocation(CLCD_LINE_1,POS_15);
						CLCD_voidWriteDate(' ');
						CLCD_voidGOToLocation(CLCD_LINE_2,POS_15);
						CLCD_voidWriteDate('I');
						racketY_current=data;
					}
				break;

				case MSG_DISPLAY_TEXT:
					if (data == TEXT_WIN)
					{
						CLCD_voidWriteCmd(Clear_Display);
						CLCD_voidGOToLocation(CLCD_LINE_1,POS_4);
						CLCD_voidWriteString(win);
						// TODO:
					}
					else if (data == TEXT_LOSE)
					{
						// TODO:
						CLCD_voidWriteCmd(Clear_Display);
						CLCD_voidGOToLocation(CLCD_LINE_1,POS_4);
						CLCD_voidWriteString(lose);
					}

					delay_ms(4000);
					CLCD_voidWriteCmd(Clear_Display);
				break;

				case MSG_BALL:
					ballX_new = data & 0b00001111;
					ballY_new = BIT_GET(data, 4) + 1;
					//CLCD_voidWriteDate(ballX_new  + '0');
					//break;
					// TODO: remove current ball from ballX_current and ballY_current
					// TODO: update (ballX_current and ballY_current) from (ballX_new and ballY_new)
					// TODO:
					CLCD_voidGOToLocation(ballY_current,ballX_current);
					CLCD_voidWriteDate(' ');
					ballX_current=ballX_new;
					ballY_current=ballY_new;
					CLCD_voidGOToLocation(ballY_new,ballX_new);
					CLCD_voidWriteDate('O');
				break;

				case MSG_CLEAR_BALL:
					// TODO change between the screens:
					CLCD_voidGOToLocation(ballY_current,ballX_current);
					CLCD_voidWriteDate(' ');

				break;
				}
			}
			else /* if not our uC ID */
			{
				//CLCD_voidWriteDate('N');
			}
		}
		else /* invalid frame */
		{

		}
	}
}
