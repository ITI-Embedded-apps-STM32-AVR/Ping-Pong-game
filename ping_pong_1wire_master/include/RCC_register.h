#define RCC_BASE_ADDRESS 0x40021000
#define RCC_CR 			 *((u32*)(RCC_BASE_ADDRESS+0x00))
#define RCC_CFGR 		 *((u32*)(RCC_BASE_ADDRESS+0x04))
#define RCC_CIR 		 *((u32*)(RCC_BASE_ADDRESS+0x08))
#define RCC_APB2RSTR  	 *((u32*)(RCC_BASE_ADDRESS+0x0c))
#define RCC_APB1RSTR      *((u32*)(RCC_BASE_ADDRESS+0x10))
#define RCC_AHBENR 	     *((u32*)(RCC_BASE_ADDRESS+0x14))
#define RCC_APB2ENR       *((u32*)(RCC_BASE_ADDRESS+0x18))
#define RCC_APB1ENR      *((u32*)(RCC_BASE_ADDRESS+0x1c))
#define RCC_BDCR 		 *((u32*)(RCC_BASE_ADDRESS+0x20))
#define RCC_CSR 		 *((u32*)(RCC_BASE_ADDRESS+0x24))
//cr and cfgr el clock elly da5la el processor
//AHBENR,apb2str ,apb1str  enable leh kol clock  feh  kol preiphral
