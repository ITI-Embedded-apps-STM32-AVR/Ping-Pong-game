#define PORTA_BASEADD 0x40010800
#define PORTB_BASEADD 0x40010C00
#define PORTC_BASEADD 0x40011000
#define PORTA_CRL	    *((u32*)(PORTA_BASEADD+0x00))
#define PORTA_CRH 		*((u32*)(PORTA_BASEADD+0x04))
#define PORTA_IDR 		*((u32*)(PORTA_BASEADD+0x08))
#define PORTA_ODR       *((u32*)(PORTA_BASEADD+0x0c))
#define PORTA_BSRR      *((u32*)(PORTA_BASEADD+0x10))
#define PORTA_BRR 	    *((u32*)(PORTA_BASEADD+0x14))
#define PORTA_LCKR      *((u32*)(PORTA_BASEADD+0x18))


#define PORTB_CRL	     *((u32*)(PORTB_BASEADD+0x00))
#define PORTB_CRH 		 *((u32*)(PORTB_BASEADD+0x04))
#define PORTB_IDR 		 *((u32*)(PORTB_BASEADD+0x08))
#define PORTB_ODR  		 *((u32*)(PORTB_BASEADD+0x0c))
#define PORTB_BSRR       *((u32*)(PORTB_BASEADD+0x10))
#define PORTB_BRR 	     *((u32*)(PORTB_BASEADD+0x14))
#define PORTB_LCKR       *((u32*)(PORTB_BASEADD+0x18))


#define PORTC_CRL		  *((u32*)(PORTC_BASEADD+0x00))
#define PORTC_CRH 		  *((u32*)(PORTC_BASEADD+0x04))
#define PORTC_IDR 		  *((u32*)(PORTC_BASEADD+0x08))
#define PORTC_ODR  		  *((u32*)(PORTC_BASEADD+0x0c))
#define PORTC_BSRR 		  *((u32*)(PORTC_BASEADD+0x10))
#define PORTC_BRR 		  *((u32*)(PORTC_BASEADD+0x14))
#define PORTC_LCKR 		  *((u32*)(PORTC_BASEADD+0x18))


//cr and cfgr el clock elly da5la el processor
//AHBENR,apb2str ,apb1str  enable leh kol clock  feh  kol preiphral
