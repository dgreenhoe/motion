//=============================================================================
// Daniel J. Greenhoe
//=============================================================================
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
