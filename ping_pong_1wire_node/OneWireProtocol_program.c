/* libs */
#include "STD_TYPES.h"
#include "BIT_MAN.h"
#include "Delay_interface.h"
/* MCAL */
#include "DIO_interface.h"
/* own */
#include "OneWireProtocol_interface.h"
#include "OneWireProtocol_private.h"

/**** private sender functions ****/
static void OneWireProtocol_createHighLevel(OneWire_t* protocol)
{
	DIO_setPinVal(protocol->port, protocol->pin, 1);
}

static void OneWireProtocol_createLowLevel(OneWire_t* protocol)
{
	DIO_setPinVal(protocol->port, protocol->pin, 0);
}

static void OneWireProtocol_createRisingEdge(OneWire_t* protocol)
{
	OneWireProtocol_createLowLevel(protocol);
	delay_us((u16)DATA_HOLD_TIME_US);
	
   OneWireProtocol_createHighLevel(protocol);
	delay_us((u16)EDGE_TIMEOUT_US);
}

static void OneWireProtocol_createFallingEdge(OneWire_t* protocol)
{
	OneWireProtocol_createHighLevel(protocol);
	delay_us((u16)DATA_HOLD_TIME_US);
   
	OneWireProtocol_createLowLevel(protocol);
	delay_us((u16)EDGE_TIMEOUT_US);
}

static void OneWireProtocol_startFrame(OneWire_t* protocol)
{
	/* send a low level to pause the receiver */
	OneWireProtocol_createLowLevel(protocol);
	delay_us((u16)FRAME_START_PAUSE_TIME_US);

	/* create 1st level */
	OneWireProtocol_createHighLevel(protocol);
	delay_us((u16)EDGE_TIMEOUT_US);

	/* create 2nd level */
	OneWireProtocol_createLowLevel(protocol);
	delay_us((u16)EDGE_TIMEOUT_US);

	/* create 3rd level */
	OneWireProtocol_createHighLevel(protocol);
	delay_us((u16)EDGE_TIMEOUT_US);

	/* send a falling edge to the receiver indicating that
	 * frame start is finished and data should be received now */
	OneWireProtocol_createLowLevel(protocol);
	/* this delay is needed in case the 1s data bit = 0
	 * in that case (without the delay) the rising edge
	 * would be transient and could possibly be not detected
	 * by the receiver */
	delay_us((u16)EDGE_TIMEOUT_US);
}
/**********************************/

/**** private receiver functions ****/
static u8 OneWireProtocol_waitForHighLevel(OneWire_t* protocol)
{
	/* timeout counter, when it reaches 0 a bad state
	 * should be returned */
	register u16 timeoutCtr = 0xFFFF;

	while ((DIO_getPinVal(protocol->port, protocol->pin) == 0) && (timeoutCtr != 0))
	{
		timeoutCtr--;
	}

	/* if it timed out before detecting an edge */
	if (timeoutCtr == 0)
	{
		return 0;
	}
	else if (timeoutCtr == 0xFFFF) /* if the level was already opposite */
	{
		return 0;
	}
	else /* if an edge was detected before a timeout */
	{
		return 1;
	}
}

static u8 OneWireProtocol_waitForLowLevel(OneWire_t* protocol)
{
	/* timeout counter, when it reaches 0 a bad state
	 * should be returned */
	register u16 timeoutCtr = 0xFFFF;

	while ((DIO_getPinVal(protocol->port, protocol->pin) == 1) && (timeoutCtr != 0))
	{
		timeoutCtr--;
	}

	/* if it timed out before detecting an edge */
	if (timeoutCtr == 0)
	{
		return 0;
	}
	else if (timeoutCtr == 0xFFFF) /* if the level was already opposite */
	{
		return 0;
	}
	else /* if an edge was detected before a timeout */
	{
		return 1;
	}
}

static u8 OneWireProtocol_waitForEdge(u8 currentLevel, OneWire_t* protocol)
{
	/* if current level is high, then wait for low and vice versa */
	if (currentLevel == 1)
	{
		/* if function timed out */
		if (OneWireProtocol_waitForLowLevel(protocol) == 0)
		{
			return 0;
		}
	}
	else
	{
		/* if function timed out */
		if (OneWireProtocol_waitForHighLevel(protocol) == 0)
		{
			return 0;
		}
	}

	/* wait until sender prepares next bit */
	delay_us((u16)EDGE_TIMEOUT_US + (u16)DATA_WASTE_TIME_US);

	return 1;
}

static OneWireErr_t OneWireProtocol_detectFrame(OneWire_t* protocol)
{
	/* wait for rising edge, this indicates that
	 * sender is about to send either data or frame overhead */
	if (OneWireProtocol_waitForHighLevel(protocol) == 0) /* if function timed out*/
	{
		return OneWireErr_Rx_FrameStart_timeout + 0;
	}

	/* we reach here if current level is high */

	/* wait by an amount of EDGE_TIMEOUT * 1.5 to reach the next level
	 * exactly at the middle */
	delay_us((u16)EDGE_TIMEOUT_US + (u16)EDGE_TIMEOUT_US / 2);

	/* read second level (should be low) */
	if (DIO_getPinVal(protocol->port, protocol->pin) != 0)
	{
		return OneWireErr_Rx_FrameStart_timeout + 1;
	}

	/* skip by an amount of EDGE_TIMEOUT to reach the next level
	 * exactly at the middle */
	delay_us((u16)EDGE_TIMEOUT_US);
	/* read third level (should be high) */
	if (DIO_getPinVal(protocol->port, protocol->pin) != 1)
	{
		return OneWireErr_Rx_FrameStart_timeout + 2;
	}

	/* wait until an edge is sent */
	if (OneWireProtocol_waitForEdge(1, protocol) == 0) /* if function timed out*/
	{
		return OneWireErr_Rx_FrameStart_timeout + 3;
	}

	return OneWireErr_Rx_Success;
}
/************************************/

void OneWireProtocol_init(u8 mode, OneWire_t* protocol)
{
	if (mode == ONE_WIRE_AS_SENDER) /* as a sender */
	{
		/* initially pause the receiver */
		OneWireProtocol_createLowLevel(protocol);
	}
	else if (mode == ONE_WIRE_AS_RECEIVER) /* as a receiver */
	{

	}
}

/**** sender functions ****/
void OneWireProtocol_send(u8 value, OneWire_t* protocol)
{
	/* start the frame */
	OneWireProtocol_startFrame(protocol);

	/* send frame data (8-bits) (MSB first) */
	for (u8 i = 8; i > 0; i--)
	{
		/* if data bit is high create a falling edge because the first level (high) represents the bit */
		if (BIT_GET(value, i - 1) == 1)
		{
			OneWireProtocol_createFallingEdge(protocol);
		}
		else /* if data bit is low create a rising edge because the first level (low) represents the bit */
		{
			OneWireProtocol_createRisingEdge(protocol);
		}
	}

	/* create a low level to pause the receiver */
	OneWireProtocol_createLowLevel(protocol);
}
/**************************/

/**** receiver functions ****/
OneWireErr_t OneWireProtocol_read(u8* out, OneWire_t* protocol)
{
	/* holds value of current level */
	register u8 level;

	/* holds final value */
	register u8 result = 0;

	/* holds last error level */
	register OneWireErr_t err = OneWireProtocol_detectFrame(protocol);

	/* if we couldn't detect a frame */
	if (err != OneWireErr_Rx_Success)
	{
	  return err;
	}

	/* read frame data (8-bits) MSB is sent first */
	for (u8 i = 8; i > 0; i--)
	{
		/* get pin value */
		level = DIO_getPinVal(protocol->port, protocol->pin);

		/* put pin value in 1st bit */
		result |= level;

		/* if not last iteration, then shift bit to the left */
		/* by the end of the loop the 1st received bit will
		 * at the far left (MSB) */
		if (i != 1)
		{
			result <<= 1;
		}

		/* if function timed out */
		if (OneWireProtocol_waitForEdge(level, protocol) == 0)
		{
			return OneWireErr_Rx_BitN_timeout + i - 1;
		}
	}

	/* assign final/result value to out variable */
	*out = result;

	return OneWireErr_Rx_Success;
}
/****************************/
