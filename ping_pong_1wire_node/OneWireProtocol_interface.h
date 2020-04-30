#ifndef OneWireProtocol_INTERFACE_H_
#define OneWireProtocol_INTERFACE_H_

/* initialization state */
#define ONE_WIRE_AS_RECEIVER 0
#define ONE_WIRE_AS_SENDER   1

/* an object of this protocol */
typedef struct
{
   u8 port;
   u8 pin;
} OneWire_t;

typedef enum
{
	OneWireErr_Rx_Success            = 0,
	OneWireErr_Rx_FrameStart_timeout = 10,
	OneWireErr_Rx_BitN_timeout       = 20,
} OneWireErr_t;

void OneWireProtocol_init(u8 mode, OneWire_t* protocol);

/**** sender functions ****/
void OneWireProtocol_send(u8 value, OneWire_t* protocol);
/**************************/

/**** receiver functions ****/
OneWireErr_t OneWireProtocol_read(u8* out, OneWire_t* protocol);
/****************************/

#endif /* OneWireProtocol_INTERFACE_H_ */
