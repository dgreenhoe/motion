//=============================================================================
// Application
// Daniel J. Greenhoe
// 
//=============================================================================

//extern "C" void LED_test(void);

void LED_Ylw_Toggle(void){ HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_1 ); }
void LED_Red_Toggle(void){ HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_14); }
void LED_Grn_Toggle(void){ HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_0 ); } 

void LED_0_Toggle(void){ HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_2 ); }
void LED_1_Toggle(void){ HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_4 ); }
void LED_2_Toggle(void){ HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_5 ); }
void LED_3_Toggle(void){ HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_6 ); }
void LED_4_Toggle(void){ HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_3 ); }
void LED_5_Toggle(void){ HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_1 ); }
void LED_6_Toggle(void){ HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_0 ); }
void LED_7_Toggle(void){ HAL_GPIO_TogglePin(GPIOF, GPIO_PIN_1 ); }

void Tx_0_Toggle(void){ HAL_GPIO_TogglePin(GPIOF, GPIO_PIN_3 ); }
void Tx_1_Toggle(void){ HAL_GPIO_TogglePin(GPIOF, GPIO_PIN_6 ); }
void Tx_2_Toggle(void){ HAL_GPIO_TogglePin(GPIOF, GPIO_PIN_9 ); }
void Tx_3_Toggle(void){ HAL_GPIO_TogglePin(GPIOF, GPIO_PIN_7 ); }
void Tx_4_Toggle(void){ HAL_GPIO_TogglePin(GPIOF, GPIO_PIN_8 ); }
void Tx_5_Toggle(void){ HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_12); }
void Tx_6_Toggle(void){ HAL_GPIO_TogglePin(GPIOF, GPIO_PIN_10); }
void Tx_7_Toggle(void){ HAL_GPIO_TogglePin(GPIOF, GPIO_PIN_0 ); }

