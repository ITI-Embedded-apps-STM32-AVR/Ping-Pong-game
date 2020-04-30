
#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "DIO_interface.h"
#include "RCC_interface.h"
#include "Keypad_interface.h"
#include "OneWireProtocol_interface.h"
#include "Delay_interface.h"
#include <stdlib.h>

#define FRAME_PROCESSING_TIME_MS 11

#define KEY_LEFT_UP       1
#define KEY_LEFT_DOWN     13
#define KEY_RIGHT_UP      4
#define KEY_RIGHT_DOWN    16
#define BALL_DIR_RIGHT    0
#define BALL_DIR_LEFT     1

#define UC_LEFT_ID        128
#define UC_RIGHT_ID       0

#define MSG_RACKET       (0<<5)
#define MSG_DISPLAY_TEXT (1<<5)
#define MSG_BALL         (2<<5)
#define MSG_CLEAR_BALL   (3<<5)

#define RACKET_UP   0
#define RACKET_DOWN 1

#define TEXT_WIN  0
#define TEXT_LOSE 1

#define BALL_YAXIS_UP   0
#define BALL_YAXIS_DOWN 1

OneWire_t proto1 = {
	.port = 'A',
	.pin = 11
};

void main ()
{

	RCC_Init();
	RCC_EnablePreiphiralClock(2 , 2);
	DIO_SetPinMode('A', 0, 0b0010);
	DIO_SetPinMode('A', 1, 0b0010);
	DIO_SetPinMode('A', 2, 0b0010);
	DIO_SetPinMode('A', 3, 0b0010);

	//keypad out
	DIO_SetPinMode('A', 4, 0b1000);
	DIO_SetPinMode('A', 5, 0b1000);
	DIO_SetPinMode('A', 6, 0b1000);
	DIO_SetPinMode('A', 7, 0b1000);
	DIO_SetPinValue('A', 4, 1);
	DIO_SetPinValue('A', 5, 1);
	DIO_SetPinValue('A', 6, 1);
	DIO_SetPinValue('A', 7, 1);

	//onewire out
	DIO_SetPinMode('A' , 11, 0b0010);

	/* init 1-wire protocol */
	OneWireProtocol_init(ONE_WIRE_AS_SENDER, &proto1);

	delay_setCPUclockFactor(8000000);

	u8 frame = 0;
	u8 racketLeftY = RACKET_UP;
	u8 racketRightY = RACKET_UP;
	u8 getKey = 0;
	u8 mCID = UC_LEFT_ID;
	u8 ballDir = BALL_DIR_RIGHT;
	u8 ballX = 1;
	u8 ballY = BALL_YAXIS_UP;
	u8 loadVal = 3;
	u8 blockCtr = loadVal;

	frame = UC_RIGHT_ID | MSG_RACKET | RACKET_UP;
	OneWireProtocol_send(frame, &proto1);
	delay_ms(FRAME_PROCESSING_TIME_MS);

	//racket frame
	frame = UC_LEFT_ID | MSG_RACKET | RACKET_UP;
	OneWireProtocol_send(frame, &proto1);
	delay_ms(FRAME_PROCESSING_TIME_MS);

	//ball frame
	frame = UC_LEFT_ID | MSG_BALL | (BALL_YAXIS_UP << 4) | (1);
	OneWireProtocol_send(frame, &proto1);
	delay_ms(FRAME_PROCESSING_TIME_MS);

	while (1)
	{
		//APP LAYER 1: Getting input from keypad
		getKey = KEYPAD_GetPressedKey();
		if(getKey == KEY_LEFT_UP)
		{
			racketLeftY = 0;
		}
		else if(getKey == KEY_LEFT_DOWN)
		{
			racketLeftY = 1;
		}

		frame = UC_LEFT_ID | MSG_RACKET | racketLeftY;
		OneWireProtocol_send(frame, &proto1);
		delay_ms(FRAME_PROCESSING_TIME_MS);

		if(getKey == KEY_RIGHT_UP)
		{
			racketRightY = 0;
		}
		else if(getKey == KEY_RIGHT_DOWN)
		{
			racketRightY = 1;
		}

		frame = UC_RIGHT_ID | MSG_RACKET | racketRightY;
		OneWireProtocol_send(frame, &proto1);
		delay_ms(FRAME_PROCESSING_TIME_MS);

		//APP LAYER 2: manipulating variables & defining logic

		if(ballX == 15)
		{
			if ((mCID == UC_LEFT_ID) && (ballDir == BALL_DIR_RIGHT))
			{
				mCID = UC_RIGHT_ID;
				ballX = 0;
				frame = UC_LEFT_ID | MSG_CLEAR_BALL | 0;
				OneWireProtocol_send(frame, &proto1);
				delay_ms(FRAME_PROCESSING_TIME_MS);
			}
			else if (mCID == UC_RIGHT_ID)
			{
				if(racketRightY == ballY)
				{
					ballDir = BALL_DIR_LEFT;
					ballX = 14;
				}
				else
				{
					frame = UC_LEFT_ID | MSG_DISPLAY_TEXT | TEXT_WIN ;
					OneWireProtocol_send(frame, &proto1);
					delay_ms(FRAME_PROCESSING_TIME_MS);

					frame = UC_RIGHT_ID | MSG_DISPLAY_TEXT | TEXT_LOSE ;
					OneWireProtocol_send(frame, &proto1);
					delay_ms(FRAME_PROCESSING_TIME_MS);

					delay_ms(4050);

					//racket frame
					frame = UC_RIGHT_ID | MSG_RACKET | RACKET_UP;
					OneWireProtocol_send(frame, &proto1);
					delay_ms(FRAME_PROCESSING_TIME_MS);

					//racket frame
					frame = UC_LEFT_ID | MSG_RACKET | RACKET_UP;
					OneWireProtocol_send(frame, &proto1);
					delay_ms(FRAME_PROCESSING_TIME_MS);

					racketLeftY = RACKET_UP;
					racketRightY = RACKET_UP;
					mCID = UC_LEFT_ID;
					ballDir = BALL_DIR_RIGHT;
					ballX = 1;
					ballY = BALL_YAXIS_UP;
				}
			}
		}
		else if(ballX == 0)
		{
			if ((mCID == UC_RIGHT_ID) && (ballDir == BALL_DIR_LEFT))
			{
				mCID = UC_LEFT_ID;
				ballX = 15;
				frame = UC_RIGHT_ID | MSG_CLEAR_BALL | 0;
				OneWireProtocol_send(frame, &proto1);
				delay_ms(FRAME_PROCESSING_TIME_MS);
			}
			else if (mCID == UC_LEFT_ID)
			{
				if(racketLeftY == ballY)
				{
					ballDir = BALL_DIR_RIGHT;
					ballX = 1;
				}
				else
				{
					frame = UC_RIGHT_ID | MSG_DISPLAY_TEXT | TEXT_WIN ;
					OneWireProtocol_send(frame, &proto1);
					delay_ms(FRAME_PROCESSING_TIME_MS);

					frame = UC_LEFT_ID | MSG_DISPLAY_TEXT | TEXT_LOSE ;
					OneWireProtocol_send(frame, &proto1);
					delay_ms(FRAME_PROCESSING_TIME_MS);

					delay_ms(4050);

					//racket frame
					frame = UC_RIGHT_ID | MSG_RACKET | RACKET_UP;
					OneWireProtocol_send(frame, &proto1);
					delay_ms(FRAME_PROCESSING_TIME_MS);

					//racket frame
					frame = UC_LEFT_ID | MSG_RACKET | RACKET_UP;
					OneWireProtocol_send(frame, &proto1);
					delay_ms(FRAME_PROCESSING_TIME_MS);

					racketLeftY = RACKET_UP;
					racketRightY = RACKET_UP;
					mCID = UC_LEFT_ID;
					ballDir = BALL_DIR_RIGHT;
					ballX = 1;
					ballY = BALL_YAXIS_UP;
				}
			}
		}

		if (blockCtr == 0)
		{
			if ((mCID == UC_LEFT_ID) && (ballX == 1) && (ballDir == BALL_DIR_LEFT))
			{
				if (loadVal)
				{
					loadVal--;
				}
			}

			blockCtr = loadVal;

			//randomize ballY pos :D
			ballY = rand() % 2;

			//ball frame
			frame = mCID | MSG_BALL | (ballY << 4) | ballX;
			OneWireProtocol_send(frame, &proto1);
			delay_ms(FRAME_PROCESSING_TIME_MS);

			if (ballDir == BALL_DIR_LEFT)
			{
				ballX--;
			}
			if (ballDir == BALL_DIR_RIGHT)
			{
				ballX++;
			}
		}
		else
		{
			blockCtr--;
		}
	}
}
