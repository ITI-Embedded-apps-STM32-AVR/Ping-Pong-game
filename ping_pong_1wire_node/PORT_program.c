// libs
#include "STD_TYPES.h"
//#include "BIT_MAN.h"
// own
#include "PORT_interface.h"
#include "PORT_register.h"
#include "PORT_config.h"
#include "PORT_private.h"

void initPort()
{
   DDRA = PORTA_DIR;
   DDRB = PORTB_DIR;
   DDRC = PORTC_DIR;
   DDRD = PORTD_DIR;
}
