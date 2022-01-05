//=============================================================================
// Application
// Daniel J. Greenhoe
//
//=============================================================================
extern "C" void LED_test(void); // mixing C/C++: https://isocpp.org/wiki/faq/mixing-c-and-cpp
#include "main.h"
#include "LEDs.h"

void LED_test(void)
{
  LED_Red_Toggle() ; HAL_Delay(  5);
  Tx_0_Toggle()    ; HAL_Delay(  5);
  Tx_1_Toggle()    ; HAL_Delay(  5);
  Tx_2_Toggle()    ; HAL_Delay(  5);
  Tx_3_Toggle()    ; HAL_Delay(  5);
  Tx_4_Toggle()    ; HAL_Delay(  5);
  Tx_5_Toggle()    ; HAL_Delay(  5);
  Tx_6_Toggle()    ; HAL_Delay(  5);
  Tx_7_Toggle()    ; HAL_Delay(  5);
  LED_0_Toggle()   ; HAL_Delay(  5);
  LED_1_Toggle()   ; HAL_Delay(  5);
  LED_2_Toggle()   ; HAL_Delay(  5);
  LED_3_Toggle()   ; HAL_Delay(  5);
  LED_4_Toggle()   ; HAL_Delay(  5);
  LED_5_Toggle()   ; HAL_Delay(  5);
  LED_6_Toggle()   ; HAL_Delay(  5);
  LED_7_Toggle()   ; HAL_Delay(  5);
  LED_Red_Toggle() ; HAL_Delay(355);
  LED_Ylw_Toggle() ; HAL_Delay(350);
  LED_Grn_Toggle() ; HAL_Delay(250);
}
