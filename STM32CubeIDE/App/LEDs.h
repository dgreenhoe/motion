//=============================================================================
// Application
// Daniel J. Greenhoe
// 
//=============================================================================

//extern "C" void LED_test(void);

void LED_Ylw_Toggle(void);
void LED_Red_Toggle(void);
void LED_Grn_Toggle(void);

HAL_StatusTypeDef LED_Toggle( int n );
HAL_StatusTypeDef LED_SetHigh( int n );
HAL_StatusTypeDef LED_SetLow( int n );
void LED_Sequence(uint32_t delay);
