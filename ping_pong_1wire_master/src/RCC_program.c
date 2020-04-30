#include "STD_TYPES.H"
#include "BIT_MATH.h"
#include "RCC_interface.h"
//#include "RCC_register.h"
#include "RCC_register.h"
#include "RCC_private.h"
#include "RCC_config.h"

extern void RCC_Init(void)
{
	/*HSI >> off*
	PLL_>OFF*
	HSE>>ON
	CSS>off*/
	RCC_CR=0x00010000;
	
	/*
	sysclk >>HSE
	AHB,APB!,APb2> no division
	MCO > NOt connected 
	*/
	RCC_CFGR=0x00000001;
	
}
//enable leh clck elly da5la leh
extern void RCC_EnablePreiphiralClock(u8 Bus , u8 Preiphiral)
{
	switch(Bus)
	{
		case 0:SET_BIT(RCC_AHBENR,Preiphiral);break;
		case 1:SET_BIT(RCC_APB1ENR,Preiphiral);break;
		case 2:SET_BIT(RCC_APB2ENR,Preiphiral);break;

	}
}

extern void RCC_DisablePreiphiralClock(u8 Bus ,u8 Preiphiral)
{
	switch(Bus)
	{
		case 0:CLEAR_BIT(RCC_AHBENR,Preiphiral);break;
		case 1:CLEAR_BIT(RCC_APB1ENR,Preiphiral);break;
		case 2:CLEAR_BIT(RCC_APB2ENR,Preiphiral);break;

	}
}

