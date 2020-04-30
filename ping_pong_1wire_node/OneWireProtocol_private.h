#ifndef OneWireProtocol_PRIVATE_H_
#define OneWireProtocol_PRIVATE_H_

/* amount of time to waste by sender as a new frame indicator */
#define FRAME_START_PAUSE_TIME_US 100

/* amount of time data is held by sender without any change */
/* minimum time > EDGE_TIMEOUT * 1.5 (for proper frame start condition) */
#define DATA_HOLD_TIME_US         2200

/* amount of time to purposefully skip by receiver
 * to reach the beginning of the new level.
 * the sender may create transitional edge during this time */
#define EDGE_TIMEOUT_US           1100

/* amount of time to purposefully skip by receiver to make sure
 * we're at the level of next data bit */
#define DATA_WASTE_TIME_US        (DATA_HOLD_TIME_US / 2)

/**** private sender functions ****/
static void OneWireProtocol_createHighLevel(OneWire_t* protocol);
static void OneWireProtocol_createLowLevel(OneWire_t* protocol);

static void OneWireProtocol_createRisingEdge(OneWire_t* protocol);
static void OneWireProtocol_createFallingEdge(OneWire_t* protocol);

static void OneWireProtocol_startFrame(OneWire_t* protocol);
/**********************************/

/**** private receiver functions ****/
static u8 OneWireProtocol_waitForHighLevel(OneWire_t* protocol);
static u8 OneWireProtocol_waitForLowLevel(OneWire_t* protocol);

static u8 OneWireProtocol_waitForEdge(u8 currentLevel, OneWire_t* protocol);

static OneWireErr_t OneWireProtocol_detectFrame(OneWire_t* protocol);
/************************************/

#endif /* OneWireProtocol_PRIVATE_H_ */
