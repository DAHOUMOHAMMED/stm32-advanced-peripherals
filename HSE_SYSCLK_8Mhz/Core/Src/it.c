/*
 * it.c
 *
 *  Created on: Nov 23, 2026
 *      Author: Med Dahou
 */

#include "main.h"



void SysTick_Handler(void)
{
	HAL_IncTick();
	HAL_SYSTICK_IRQHandler();
}





