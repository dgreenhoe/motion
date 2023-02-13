//=============================================================================
// Application
// Daniel J. Greenhoe
// 
//=============================================================================

//extern "C" void LED_test(void);

void LED_Ylw_Toggle(void);
void LED_Red_Toggle(void);
void LED_Grn_Toggle(void);

void LED_Ylw_On(void);
void LED_Red_On(void);
void LED_Grn_On(void);

void LED_Ylw_Off(void);
void LED_Red_Off(void);
void LED_Grn_Off(void);

void LED_Toggle( int n );
void LED_On( int n );
void LED_Off( int n );
void LED_AllOff( void );
void LED_Sequence(uint32_t delay);
void LED_Pulsate( int n );
