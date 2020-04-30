/* when a function-like and an object-like macros are present in the same sentence,
   the function is expanded 1st then the macros */
#define cocat_helper(b7, b6, b5, b4, b3, b2, b1, b0) 0b##b7##b6##b5##b4##b3##b2##b1##b0
#define concat(b7, b6, b5, b4, b3, b2, b1, b0) cocat_helper(b7, b6, b5, b4, b3, b2, b1, b0)

#define PORTA_DIR concat(PORTA_PIN7_DIR, PORTA_PIN6_DIR, PORTA_PIN5_DIR, PORTA_PIN4_DIR, PORTA_PIN3_DIR, PORTA_PIN2_DIR, PORTA_PIN1_DIR, PORTA_PIN0_DIR)
#define PORTB_DIR concat(PORTB_PIN7_DIR, PORTB_PIN6_DIR, PORTB_PIN5_DIR, PORTB_PIN4_DIR, PORTB_PIN3_DIR, PORTB_PIN2_DIR, PORTB_PIN1_DIR, PORTB_PIN0_DIR)
#define PORTC_DIR concat(PORTC_PIN7_DIR, PORTC_PIN6_DIR, PORTC_PIN5_DIR, PORTC_PIN4_DIR, PORTC_PIN3_DIR, PORTC_PIN2_DIR, PORTC_PIN1_DIR, PORTC_PIN0_DIR)
#define PORTD_DIR concat(PORTD_PIN7_DIR, PORTD_PIN6_DIR, PORTD_PIN5_DIR, PORTD_PIN4_DIR, PORTD_PIN3_DIR, PORTD_PIN2_DIR, PORTD_PIN1_DIR, PORTD_PIN0_DIR)
