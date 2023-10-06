#include "MPU6050_TIMER.h"


//#define TIMER_PERIOD    2000
TIM_HandleTypeDef    TimHandle;

void Error_Handler(void)
{
  /* 无限循环 */
  while (1)
  {
  }
}

void Timer_init(void)
{
	
	/* 使能TIM3时钟 */
  __HAL_RCC_TIM3_CLK_ENABLE();
  
 
	TimHandle.Instance = TIM3;                                           /* 选择TIM3 */
  TimHandle.Init.Period            = 3200 - 1;                         /* 自动重装载值 */
  TimHandle.Init.Prescaler         = 10 - 1;                         /* 预分频为1000-1 */
  TimHandle.Init.ClockDivision     = TIM_CLOCKDIVISION_DIV1;           /* 时钟不分频 */
  TimHandle.Init.CounterMode       = TIM_COUNTERMODE_UP;               /* 向上计数 */
  TimHandle.Init.RepetitionCounter = 1 - 1;                            /* 不重复计数 */
  TimHandle.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;   /* 自动重装载寄存器没有缓冲 */
  
	 /* 设置中断优先级 */
  HAL_NVIC_SetPriority(TIM3_IRQn, 0, 0);
  /* 使能TIM3中断 */
  HAL_NVIC_EnableIRQ(TIM3_IRQn);
	/* TIM3初始化 */
  if (HAL_TIM_Base_Init(&TimHandle) != HAL_OK)
  {
    Error_Handler();
  }

  /* TIM3使能启动，并使能中断 */
  if (HAL_TIM_Base_Start_IT(&TimHandle) != HAL_OK)
  {
    Error_Handler();
  }
}



