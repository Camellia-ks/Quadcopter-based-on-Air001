#ifndef __USART_H
#define __USART_H

#include "air001xx_hal.h"
#include "Delay.h"

extern UART_HandleTypeDef UartHandle;

void HAL_MspInit(void);
void HAL_UART_MspInit(UART_HandleTypeDef *huart);
void USART2_Init(void);
void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart);
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *UartHandle);
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *UartHandle);
void Error_Handler(void);
#endif

