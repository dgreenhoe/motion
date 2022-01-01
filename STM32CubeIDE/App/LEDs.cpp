//=============================================================================
// Application
// Daniel J. Greenhoe
// 
//=============================================================================

#include "main.h"
#include "LEDs.h"

void LED_test(void)
{
  LED_RED_TOGGLE ; HAL_Delay(  5);
  LED_0_TOGGLE   ; HAL_Delay(  5);
  LED_1_TOGGLE   ; HAL_Delay(  5);
  LED_2_TOGGLE   ; HAL_Delay(  5);
  LED_3_TOGGLE   ; HAL_Delay(  5);
  LED_4_TOGGLE   ; HAL_Delay(  5);
  LED_5_TOGGLE   ; HAL_Delay(  5);
  LED_6_TOGGLE   ; HAL_Delay(  5);
  LED_7_TOGGLE   ; HAL_Delay(  5);
  LED_RED_TOGGLE ; HAL_Delay(355);
  LED_YLW_TOGGLE ; HAL_Delay(350);
  LED_GRN_TOGGLE ; HAL_Delay(250);
}
