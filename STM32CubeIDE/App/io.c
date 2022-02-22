//=============================================================================
// Daniel J. Greenhoe
//=============================================================================
#include <stdio.h>
#include "io.h"
#include "main.h"
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


