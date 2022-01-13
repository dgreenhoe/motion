//=============================================================================
// Daniel J. Greenhoe
//=============================================================================
#include <stdio.h>
#include "io.h"
#include "main.h"
#include "LEDs.h"
extern UART_HandleTypeDef huart3;

//-----------------------------------------------------------------------------
// \Drivers\STM32H7xx_HAL_Driver\Src\stm32h7xx_hal_uart.c
// https://youtu.be/WnCpPf7u4Xo?t=139
//-----------------------------------------------------------------------------
int _write(int file, char *ptr, int len)
{
  //HAL_StatusTypeDef HAL_UART_Transmit(UART_HandleTypeDef *huart, const uint8_t *pData, uint16_t Size, uint32_t Timeout)
  HAL_UART_Transmit( &huart3, (const uint8_t *)ptr, (uint16_t )len, HAL_MAX_DELAY );
  return len;
}

//-----------------------------------------------------------------------------
// \brief Non-blocking get one character
// \ref https://www.openstm32.org/forumthread5015
//-----------------------------------------------------------------------------
int getcharnb(uint8_t * oneChar)
{
  if (__HAL_UART_GET_FLAG(&huart3, UART_FLAG_ORE))
    __HAL_UART_CLEAR_FLAG(&huart3, UART_FLAG_ORE);

  if (__HAL_UART_GET_FLAG(&huart3, UART_FLAG_RXNE))
  {
    *oneChar = huart3.Instance->RDR & 0x1FF;
    return 1;
  }

  return 0;
}

//-----------------------------------------------------------------------------
// \brief Display menu options
//-----------------------------------------------------------------------------
int Menu_Options(void)
{
  printf("Menu Options:\r\n");
  printf("  r: Toggle Red LED\r\n");
  printf("  y: Toggle Yellow LED\r\n");
  printf("  g: Toggle Green LED\r\n");
  printf("  0: Toggle LED 0\r\n");
  printf("  1: Toggle LED 1\r\n");
  printf("  2: Toggle LED 2\r\n");
  printf("  3: Toggle LED 3\r\n");
  printf("  4: Toggle LED 4\r\n");
  printf("  5: Toggle LED 5\r\n");
  printf("  6: Toggle LED 6\r\n");
  printf("  7: Toggle LED 7\r\n");
  return 0;
}

//-----------------------------------------------------------------------------
// \brief Display menu options
//-----------------------------------------------------------------------------
int Menu_Processing( uint8_t oneChar )
{
  switch( oneChar )
  {
    case 'r':
      LED_Red_Toggle();
      break;
    case 'g':
      LED_Grn_Toggle();
      break;
    case 'y':
      LED_Ylw_Toggle();
      break;
    case '0':
      LED_0_Toggle();
      break;
    case '1':
      LED_1_Toggle();
      break;
    case '2':
      LED_2_Toggle();
      break;
    case '3':
      LED_3_Toggle();
      break;
    case '4':
      LED_4_Toggle();
      break;
    case '5':
      LED_5_Toggle();
      break;
    case '6':
      LED_6_Toggle();
      break;
    case '7':
      LED_7_Toggle();
      break;
  }
  return 0;
}

