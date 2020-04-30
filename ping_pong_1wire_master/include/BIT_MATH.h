
#define SET_BIT(VAR,BIT_NO) (VAR|=(1<<BIT_NO))
#define CLEAR_BIT(VAR,BIT_NO) (VAR&=~(1<<BIT_NO))
#define TOGGLE_BIT(VAR,BIT_NO)	(VAR^=(1<<BIT_NO))
#define GET_BIT(VAR,BIT_NO)	((VAR>>BIT_NO)&(1))
#define CIRC_RSHIFT(VAR,N_SHIFTS) (VAR>>N_SHIFTS)|(VAR<<(sizeof(char)*8-N_SHIFTS))
#define CIRC_LSHIFT(VAR,N_SHIFTS) (VAR<<N_SHIFTS)|(VAR>>(sizeof(char)*8-N_SHIFTS))






