#include "PWM.h"

/*
	PA5   TIM3   TIM_CHANNEL_2
	PA4   TIM3   TIM_CHANNEL_3
	PA6   TIM3   TIM_CHANNEL_1
	PB1   TIM3   TIM_CHANNEL_4
*/
void PWM_Init(void)
{	
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_TIM3_CLK_ENABLE();
	//PA5
	GPIO_InitTypeDef PWM_GPIO_Init;
	PWM_GPIO_Init.Pin = GPIO_PIN_5;
	PWM_GPIO_Init.Speed = GPIO_SPEED_FREQ_HIGH;
	PWM_GPIO_Init.Mode = GPIO_MODE_AF_PP;
	PWM_GPIO_Init.Alternate = GPIO_AF13_TIM3;
	HAL_GPIO_Init(GPIOA,&PWM_GPIO_Init);
	
	TIM_HandleTypeDef    TIM_Handle;
	
	TIM_Handle.Instance = TIM3;
	
	TIM_Handle.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;//时钟分频因子
	TIM_Handle.Init.CounterMode = TIM_COUNTERMODE_UP;//向上计数
	TIM_Handle.Init.Period =100-1;//自动重装载值 ARR
	TIM_Handle.Init.Prescaler = 0;//时钟预分频值 PSC
	TIM_Handle.Init.RepetitionCounter = 0;
	HAL_TIM_Base_Init(&TIM_Handle);
	 
	TIM_OC_InitTypeDef TIM_OC_InitStruct;
	HAL_TIM_OC_DeInit(&TIM_Handle);

	TIM_OC_InitStruct.OCMode       = TIM_OCMODE_PWM1;                                     /* 输出配置为PWM1 */
  TIM_OC_InitStruct.OCPolarity   = TIM_OCPOLARITY_HIGH;                                 /* OC通道输出高电平有效 */
  TIM_OC_InitStruct.OCNPolarity  = TIM_OCNPOLARITY_HIGH;                                /* OCN通道输出高电平有效 */
  TIM_OC_InitStruct.Pulse = 50;//CCR
	HAL_TIM_OC_Init(&TIM_Handle);
	HAL_TIM_OC_Start(&TIM_Handle, TIM_CHANNEL_2);
	HAL_TIM_PWM_Init(&TIM_Handle);
	HAL_TIM_PWM_ConfigChannel(&TIM_Handle, &TIM_OC_InitStruct, TIM_CHANNEL_2);  // 替换为你要配置的具体通道，如 TIM_CHANNEL_1、TIM_CHANNEL_2 等

	HAL_TIM_PWM_Start(&TIM_Handle, TIM_CHANNEL_2);  // Start PWM for channel 2
	
	//PA4
	GPIO_InitTypeDef PWM_GPIO2_Init;
	PWM_GPIO2_Init.Pin = GPIO_PIN_4;
	PWM_GPIO2_Init.Speed = GPIO_SPEED_FREQ_HIGH;
	PWM_GPIO2_Init.Mode = GPIO_MODE_AF_PP;
	PWM_GPIO2_Init.Alternate = GPIO_AF13_TIM3;
	HAL_GPIO_Init(GPIOA,&PWM_GPIO2_Init);
	
	TIM_HandleTypeDef    TIM_2_Handle;
	
	TIM_2_Handle.Instance = TIM3;
	
	TIM_2_Handle.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;//时钟分频因子
	TIM_2_Handle.Init.CounterMode = TIM_COUNTERMODE_UP;//向上计数
	TIM_2_Handle.Init.Period =100-1;//自动重装载值 ARR
	TIM_2_Handle.Init.Prescaler = 0;//时钟预分频值 PSC
	TIM_2_Handle.Init.RepetitionCounter = 0;
	HAL_TIM_Base_Init(&TIM_2_Handle);
	 
	TIM_OC_InitTypeDef TIM_OC_2_InitStruct;
	HAL_TIM_OC_DeInit(&TIM_2_Handle);

	TIM_OC_2_InitStruct.OCMode       = TIM_OCMODE_PWM1;                                     /* 输出配置为PWM1 */
  TIM_OC_2_InitStruct.OCPolarity   = TIM_OCPOLARITY_HIGH;                                 /* OC通道输出高电平有效 */
  TIM_OC_2_InitStruct.OCNPolarity  = TIM_OCNPOLARITY_HIGH;                                /* OCN通道输出高电平有效 */
  TIM_OC_2_InitStruct.Pulse = 50;//CCR
	HAL_TIM_OC_Init(&TIM_2_Handle);
	HAL_TIM_OC_Start(&TIM_2_Handle, TIM_CHANNEL_3);
	HAL_TIM_PWM_Init(&TIM_2_Handle);
	HAL_TIM_PWM_ConfigChannel(&TIM_2_Handle, &TIM_OC_2_InitStruct, TIM_CHANNEL_3);  // 替换为你要配置的具体通道，如 TIM_CHANNEL_1、TIM_CHANNEL_2 等

	HAL_TIM_PWM_Start(&TIM_2_Handle, TIM_CHANNEL_3);  // Start PWM for channel 2
  
	//PA6
	GPIO_InitTypeDef PWM_GPIO3_Init;
	PWM_GPIO3_Init.Pin = GPIO_PIN_6;
	PWM_GPIO3_Init.Speed = GPIO_SPEED_FREQ_HIGH;
	PWM_GPIO3_Init.Mode = GPIO_MODE_AF_PP;
	PWM_GPIO3_Init.Alternate = GPIO_AF1_TIM3;
	HAL_GPIO_Init(GPIOA,&PWM_GPIO3_Init);
	
	TIM_HandleTypeDef    TIM_3_Handle;
	
	TIM_3_Handle.Instance = TIM3;
	
	TIM_3_Handle.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;//时钟分频因子
	TIM_3_Handle.Init.CounterMode = TIM_COUNTERMODE_UP;//向上计数
	TIM_3_Handle.Init.Period =100-1;//自动重装载值 ARR
	TIM_3_Handle.Init.Prescaler = 0;//时钟预分频值 PSC
	TIM_3_Handle.Init.RepetitionCounter = 0;
	HAL_TIM_Base_Init(&TIM_3_Handle);
	 
	TIM_OC_InitTypeDef TIM_OC_3_InitStruct;
	HAL_TIM_OC_DeInit(&TIM_3_Handle);

	TIM_OC_3_InitStruct.OCMode       = TIM_OCMODE_PWM1;                                     /* 输出配置为PWM1 */
  TIM_OC_3_InitStruct.OCPolarity   = TIM_OCPOLARITY_HIGH;                                 /* OC通道输出高电平有效 */
  TIM_OC_3_InitStruct.OCNPolarity  = TIM_OCNPOLARITY_HIGH;                                /* OCN通道输出高电平有效 */
  TIM_OC_3_InitStruct.Pulse = 50;//CCR
	HAL_TIM_OC_Init(&TIM_3_Handle);
	HAL_TIM_OC_Start(&TIM_3_Handle, TIM_CHANNEL_1);
	HAL_TIM_PWM_Init(&TIM_3_Handle);
	HAL_TIM_PWM_ConfigChannel(&TIM_3_Handle, &TIM_OC_3_InitStruct, TIM_CHANNEL_1);  // 替换为你要配置的具体通道，如 TIM_CHANNEL_1、TIM_CHANNEL_2 等

	HAL_TIM_PWM_Start(&TIM_3_Handle, TIM_CHANNEL_1);  // Start PWM for channel 2
	
	//PB1
	GPIO_InitTypeDef PWM_GPIO4_Init;
	PWM_GPIO4_Init.Pin = GPIO_PIN_1;
	PWM_GPIO4_Init.Speed = GPIO_SPEED_FREQ_HIGH;
	PWM_GPIO4_Init.Mode = GPIO_MODE_AF_PP;
	PWM_GPIO4_Init.Alternate = GPIO_AF1_TIM3;
	HAL_GPIO_Init(GPIOB,&PWM_GPIO4_Init);
	
	TIM_HandleTypeDef    TIM_4_Handle;
	
	TIM_4_Handle.Instance = TIM3;
	
	TIM_4_Handle.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;//时钟分频因子
	TIM_4_Handle.Init.CounterMode = TIM_COUNTERMODE_UP;//向上计数
	TIM_4_Handle.Init.Period =100-1;//自动重装载值 ARR
	TIM_4_Handle.Init.Prescaler = 0;//时钟预分频值 PSC
	TIM_4_Handle.Init.RepetitionCounter = 0;
	HAL_TIM_Base_Init(&TIM_4_Handle);
	 
	TIM_OC_InitTypeDef TIM_OC_4_InitStruct;
	HAL_TIM_OC_DeInit(&TIM_4_Handle);

	TIM_OC_4_InitStruct.OCMode       = TIM_OCMODE_PWM1;                                     /* 输出配置为PWM1 */
  TIM_OC_4_InitStruct.OCPolarity   = TIM_OCPOLARITY_HIGH;                                 /* OC通道输出高电平有效 */
  TIM_OC_4_InitStruct.OCNPolarity  = TIM_OCNPOLARITY_HIGH;                                /* OCN通道输出高电平有效 */
  TIM_OC_4_InitStruct.Pulse = 50;//CCR
	HAL_TIM_OC_Init(&TIM_4_Handle);
	HAL_TIM_OC_Start(&TIM_4_Handle, TIM_CHANNEL_4);
	HAL_TIM_PWM_Init(&TIM_4_Handle);
	HAL_TIM_PWM_ConfigChannel(&TIM_4_Handle, &TIM_OC_4_InitStruct, TIM_CHANNEL_4);  // 替换为你要配置的具体通道，如 TIM_CHANNEL_1、TIM_CHANNEL_2 等

	HAL_TIM_PWM_Start(&TIM_4_Handle, TIM_CHANNEL_4);  // Start PWM for channel 2
}

