#include "MPU6050_TIMER.h"


//#define TIMER_PERIOD    2000
TIM_HandleTypeDef    TimHandle;

void Error_Handler(void)
{
  /* ����ѭ�� */
  while (1)
  {
  }
}

void Timer_init(void)
{
	
	/* ʹ��TIM3ʱ�� */
  __HAL_RCC_TIM3_CLK_ENABLE();
  
 
	TimHandle.Instance = TIM3;                                           /* ѡ��TIM3 */
  TimHandle.Init.Period            = 3200 - 1;                         /* �Զ���װ��ֵ */
  TimHandle.Init.Prescaler         = 10 - 1;                         /* Ԥ��ƵΪ1000-1 */
  TimHandle.Init.ClockDivision     = TIM_CLOCKDIVISION_DIV1;           /* ʱ�Ӳ���Ƶ */
  TimHandle.Init.CounterMode       = TIM_COUNTERMODE_UP;               /* ���ϼ��� */
  TimHandle.Init.RepetitionCounter = 1 - 1;                            /* ���ظ����� */
  TimHandle.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;   /* �Զ���װ�ؼĴ���û�л��� */
  
	 /* �����ж����ȼ� */
  HAL_NVIC_SetPriority(TIM3_IRQn, 0, 0);
  /* ʹ��TIM3�ж� */
  HAL_NVIC_EnableIRQ(TIM3_IRQn);
	/* TIM3��ʼ�� */
  if (HAL_TIM_Base_Init(&TimHandle) != HAL_OK)
  {
    Error_Handler();
  }

  /* TIM3ʹ����������ʹ���ж� */
  if (HAL_TIM_Base_Start_IT(&TimHandle) != HAL_OK)
  {
    Error_Handler();
  }
}



