//=============================================================================
// Application
// Daniel J. Greenhoe
// 
//=============================================================================

extern void LED_test(void);

#define LED_YLW_TOGGLE HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_1 )
#define LED_RED_TOGGLE HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_14)
#define LED_GRN_TOGGLE HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_0 )
#define LED_0_TOGGLE   HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_2 )
#define LED_1_TOGGLE   HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_4 )
#define LED_2_TOGGLE   HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_5 )
#define LED_3_TOGGLE   HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_6 )
#define LED_4_TOGGLE   HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_3 )
#define LED_5_TOGGLE   HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_1 )
#define LED_6_TOGGLE   HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_0 )
#define LED_7_TOGGLE   HAL_GPIO_TogglePin(GPIOF, GPIO_PIN_1 )

