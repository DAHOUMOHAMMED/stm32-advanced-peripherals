/*
 * msp.c
 *
 *  Created on: Nov 23, 2026
 *      Author: Med Dahou
 */

#include "stm32f4xx_hal.h"

void HAL_MspInit(void)
{
  // here we will do low level processor specific inits.
	//1. Set up the priority grouping of the arm cortex mx processor
	HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);

	//2. Enable the required system exception of the arm cortex mx processor
	SCB->SHCSR |= 0x07 << 16;

	//3. Configure the priority for the systems exceptions
	HAL_NVIC_SetPriority(MemoryManagement_IRQn, 0, 0);
	HAL_NVIC_SetPriority(BusFault_IRQn, 0, 0);
	HAL_NVIC_SetPriority(UsageFault_IRQn, 0, 0);
}


void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
	GPIO_InitTypeDef  gpio_uart;
	// low level inits , of the uart peripheral

	//1. enabe the clock for the uart2 peripheral
	__HAL_RCC_USART2_CLK_ENABLE();
	//2. do the pin maxing configuration
	__HAL_RCC_GPIOA_CLK_ENABLE();

	gpio_uart.Pin = GPIO_PIN_2;
	gpio_uart.Mode = GPIO_MODE_AF_PP;
	gpio_uart.Pull = GPIO_PULLUP;
	gpio_uart.Speed = GPIO_SPEED_FREQ_LOW;
	gpio_uart.Alternate = GPIO_AF7_USART2;
	HAL_GPIO_Init(GPIOA, &gpio_uart);//UART2_TX

	gpio_uart.Pin = GPIO_PIN_3;//UART2 RX
	HAL_GPIO_Init(GPIOA, &gpio_uart);

	//3. Enable the IRQ and set up the priority (NVIC setting)
	HAL_NVIC_EnableIRQ(USART2_IRQn);
	HAL_NVIC_SetPriority(USART2_IRQn , 15 , 0);

}
