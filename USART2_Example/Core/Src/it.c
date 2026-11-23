/*
 * it.c
 *
 *  Created on: Nov 23, 2026
 *      Author: fuji
 */

#include "stm32f4xx_hal.h"

void SysTick_Handler(void)
{
	HAL_IncTick();
	HAL_SYSTICK_IRQHandler();
}

