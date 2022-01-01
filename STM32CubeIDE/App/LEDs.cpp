//=============================================================================
// Application
// Daniel J. Greenhoe
// 
//=============================================================================

#include "main.h"
#include "LEDs.h"

void LED_test(void)
{
  HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_14); // Red LED
  HAL_Delay(5);
  HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_2 ); // PE2_Out_LED0 (CN9-14)
  HAL_Delay(5);
  HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_4 ); // PE4_Out_LED1 (CN9-16)
  HAL_Delay(5);
  HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_5 ); // PE5_Out_LED2 (CN9-18)
  HAL_Delay(5);
  HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_6 ); // PE5_Out_LED3 (CN9-20)
  HAL_Delay(5);
  HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_3 ); // PE3_Out_LED4 (CN9-22)
  HAL_Delay(5);
  HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_1 ); // PD1_Out_LED5 (CN9-27)
  HAL_Delay(5);
  HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_0 ); // PD0_Out_LED6 (CN9-25)
  HAL_Delay(5);
  HAL_GPIO_TogglePin(GPIOF, GPIO_PIN_1 ); // PF1_Out_LED7 (CN9-19)
  HAL_Delay(365);
  HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_1 ); // Yellow LED
  HAL_Delay(350);
  HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_0 ); // Green LED
  HAL_Delay(250);
}


