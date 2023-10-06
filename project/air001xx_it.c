#include "air001xx_it.h"
#include "air001xx_hal.h"
#include "usart.h"
#include "MPU6050_TIMER.h"


void NMI_Handler(void)
{
}

void HardFault_Handler(void)
{
  while (1)
  {
  }
}

void SVC_Handler(void)
{
}

void PendSV_Handler(void)
{
}

void SysTick_Handler(void)
{
  HAL_IncTick();
}



void USART2_IRQHandler(void)
{
  HAL_UART_IRQHandler(&UartHandle);
}

void TIM3_IRQHandler(void)
{
  HAL_TIM_IRQHandler(&TimHandle);
}

