#include "buzzer.h"

void buzzer_init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOB_CLK_ENABLE();
	/*Configure GPIO pin Output Level */
	  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, GPIO_PIN_SET);

	  /*Configure GPIO pin : PC9 */
	  GPIO_InitStruct.Pin = GPIO_PIN_9;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
}
