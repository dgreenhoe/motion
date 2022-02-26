/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32h7xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define PE2_GPiO_LED0_Pin GPIO_PIN_2
#define PE2_GPiO_LED0_GPIO_Port GPIOE
#define PE3_GPiO_LED4_Pin GPIO_PIN_3
#define PE3_GPiO_LED4_GPIO_Port GPIOE
#define PE4_GPiO_LED1_Pin GPIO_PIN_4
#define PE4_GPiO_LED1_GPIO_Port GPIOE
#define PE5_GPiO_LED2_Pin GPIO_PIN_5
#define PE5_GPiO_LED2_GPIO_Port GPIOE
#define PE6_TIM15_CH2_RX2_Pin GPIO_PIN_6
#define PE6_TIM15_CH2_RX2_GPIO_Port GPIOE
#define B1_Pin GPIO_PIN_13
#define B1_GPIO_Port GPIOC
#define PF0_Out_TX7_Pin GPIO_PIN_0
#define PF0_Out_TX7_GPIO_Port GPIOF
#define PF1_GPiO_LED7_Pin GPIO_PIN_1
#define PF1_GPiO_LED7_GPIO_Port GPIOF
#define PF2_GPIO_RST_MM_Pin GPIO_PIN_2
#define PF2_GPIO_RST_MM_GPIO_Port GPIOF
#define PF3_Out_TX0_Pin GPIO_PIN_3
#define PF3_Out_TX0_GPIO_Port GPIOF
#define PF6_Out_TX1_Pin GPIO_PIN_6
#define PF6_Out_TX1_GPIO_Port GPIOF
#define PF7_Out_TX3_Pin GPIO_PIN_7
#define PF7_Out_TX3_GPIO_Port GPIOF
#define PF8_Out_TX4_Pin GPIO_PIN_8
#define PF8_Out_TX4_GPIO_Port GPIOF
#define PF9_Out_TX2_Pin GPIO_PIN_9
#define PF9_Out_TX2_GPIO_Port GPIOF
#define MCO_Pin GPIO_PIN_0
#define MCO_GPIO_Port GPIOH
#define RMII_MDC_Pin GPIO_PIN_1
#define RMII_MDC_GPIO_Port GPIOC
#define PC2_C_SPI2_MISO_MEM_Pin GPIO_PIN_2
#define PC2_C_SPI2_MISO_MEM_GPIO_Port GPIOC
#define PC3_C_SPI2_MOSI_MEM_Pin GPIO_PIN_3
#define PC3_C_SPI2_MOSI_MEM_GPIO_Port GPIOC
#define PA0_TIM5_CH1_RX5_Pin GPIO_PIN_0
#define PA0_TIM5_CH1_RX5_GPIO_Port GPIOA
#define RMII_REF_CLK_Pin GPIO_PIN_1
#define RMII_REF_CLK_GPIO_Port GPIOA
#define RMII_MDIO_Pin GPIO_PIN_2
#define RMII_MDIO_GPIO_Port GPIOA
#define PA4_DAC_Left_Pin GPIO_PIN_4
#define PA4_DAC_Left_GPIO_Port GPIOA
#define PA5_DAC_Right_Pin GPIO_PIN_5
#define PA5_DAC_Right_GPIO_Port GPIOA
#define PA6_TIM3_CH1_RX0_Pin GPIO_PIN_6
#define PA6_TIM3_CH1_RX0_GPIO_Port GPIOA
#define RMII_CRS_DV_Pin GPIO_PIN_7
#define RMII_CRS_DV_GPIO_Port GPIOA
#define RMII_RXD0_Pin GPIO_PIN_4
#define RMII_RXD0_GPIO_Port GPIOC
#define RMII_RXD1_Pin GPIO_PIN_5
#define RMII_RXD1_GPIO_Port GPIOC
#define LED_GREEN_Pin GPIO_PIN_0
#define LED_GREEN_GPIO_Port GPIOB
#define PB2_GPIO_XDCSN_MM_Pin GPIO_PIN_2
#define PB2_GPIO_XDCSN_MM_GPIO_Port GPIOB
#define PF11_Out_TX6_Pin GPIO_PIN_11
#define PF11_Out_TX6_GPIO_Port GPIOF
#define PG0_BUF_OE__Pin GPIO_PIN_0
#define PG0_BUF_OE__GPIO_Port GPIOG
#define PG1_Out_LED3_Pin GPIO_PIN_1
#define PG1_Out_LED3_GPIO_Port GPIOG
#define PE9_TIM1_CH1_RX1_Pin GPIO_PIN_9
#define PE9_TIM1_CH1_RX1_GPIO_Port GPIOE
#define PB10_TIM2_CH3_RX3_Pin GPIO_PIN_10
#define PB10_TIM2_CH3_RX3_GPIO_Port GPIOB
#define PB11_TIM2_CH4_RX4_Pin GPIO_PIN_11
#define PB11_TIM2_CH4_RX4_GPIO_Port GPIOB
#define PB12_PROTO6_Pin GPIO_PIN_12
#define PB12_PROTO6_GPIO_Port GPIOB
#define RMII_TXD1_Pin GPIO_PIN_13
#define RMII_TXD1_GPIO_Port GPIOB
#define LED_RED_Pin GPIO_PIN_14
#define LED_RED_GPIO_Port GPIOB
#define PB15_PROTO7_Pin GPIO_PIN_15
#define PB15_PROTO7_GPIO_Port GPIOB
#define STLK_VCP_RX_Pin GPIO_PIN_8
#define STLK_VCP_RX_GPIO_Port GPIOD
#define STLK_VCP_TX_Pin GPIO_PIN_9
#define STLK_VCP_TX_GPIO_Port GPIOD
#define PD11_GPIO_MP3CSN_MM_Pin GPIO_PIN_11
#define PD11_GPIO_MP3CSN_MM_GPIO_Port GPIOD
#define PD12_TIM4_CH1_RX6_Pin GPIO_PIN_12
#define PD12_TIM4_CH1_RX6_GPIO_Port GPIOD
#define PD13_TIM4_CH2_DREQ_MM_Pin GPIO_PIN_13
#define PD13_TIM4_CH2_DREQ_MM_GPIO_Port GPIOD
#define USB_FS_OVCR_Pin GPIO_PIN_7
#define USB_FS_OVCR_GPIO_Port GPIOG
#define PC6_PROTO8_Pin GPIO_PIN_6
#define PC6_PROTO8_GPIO_Port GPIOC
#define PC7_PROTO4_Pin GPIO_PIN_7
#define PC7_PROTO4_GPIO_Port GPIOC
#define PC6_TIM8_CH3_RX7_Pin GPIO_PIN_8
#define PC6_TIM8_CH3_RX7_GPIO_Port GPIOC
#define USB_FS_VBUS_Pin GPIO_PIN_9
#define USB_FS_VBUS_GPIO_Port GPIOA
#define USB_FS_ID_Pin GPIO_PIN_10
#define USB_FS_ID_GPIO_Port GPIOA
#define USB_FS_DM_Pin GPIO_PIN_11
#define USB_FS_DM_GPIO_Port GPIOA
#define USB_FS_DP_Pin GPIO_PIN_12
#define USB_FS_DP_GPIO_Port GPIOA
#define SWDIO_Pin GPIO_PIN_13
#define SWDIO_GPIO_Port GPIOA
#define SWCLK_Pin GPIO_PIN_14
#define SWCLK_GPIO_Port GPIOA
#define PA15_PROTO5_Pin GPIO_PIN_15
#define PA15_PROTO5_GPIO_Port GPIOA
#define PC10_SPI3_SCK_MM_Pin GPIO_PIN_10
#define PC10_SPI3_SCK_MM_GPIO_Port GPIOC
#define PC11_SPI3_MISO_MM_Pin GPIO_PIN_11
#define PC11_SPI3_MISO_MM_GPIO_Port GPIOC
#define PC12_Out_TX5_Pin GPIO_PIN_12
#define PC12_Out_TX5_GPIO_Port GPIOC
#define PD0_GPiO_LED6_Pin GPIO_PIN_0
#define PD0_GPiO_LED6_GPIO_Port GPIOD
#define PD1_GPiO_LED5_Pin GPIO_PIN_1
#define PD1_GPiO_LED5_GPIO_Port GPIOD
#define PD3_SPI2_SCK_MEM_Pin GPIO_PIN_3
#define PD3_SPI2_SCK_MEM_GPIO_Port GPIOD
#define PD5_USART2_TX_MIDI_MM_Pin GPIO_PIN_5
#define PD5_USART2_TX_MIDI_MM_GPIO_Port GPIOD
#define PB2_SPI3_MOSI_MM_Pin GPIO_PIN_6
#define PB2_SPI3_MOSI_MM_GPIO_Port GPIOD
#define RMII_TX_EN_Pin GPIO_PIN_11
#define RMII_TX_EN_GPIO_Port GPIOG
#define RMII_TXD0_Pin GPIO_PIN_13
#define RMII_TXD0_GPIO_Port GPIOG
#define SWO_Pin GPIO_PIN_3
#define SWO_GPIO_Port GPIOB
#define PB5_PROTO3_Pin GPIO_PIN_5
#define PB5_PROTO3_GPIO_Port GPIOB
#define PB8_PROTO9_Pin GPIO_PIN_8
#define PB8_PROTO9_GPIO_Port GPIOB
#define PB9_PROTO10_Pin GPIO_PIN_9
#define PB9_PROTO10_GPIO_Port GPIOB
#define LED_YELLOW_Pin GPIO_PIN_1
#define LED_YELLOW_GPIO_Port GPIOE
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
