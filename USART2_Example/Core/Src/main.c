/*
 * main.c
 *
 *  Created on: Nov 23, 2026
 *      Author: Med Dahou
 */

#include "stm32f4xx_hal.h"
#include "main.h"
#include "string.h"

void SystemClockConfig(void);
void UART2_Init(void);
void Error_handler(void);

UART_HandleTypeDef huart2;

char *user_data = "Hi, I'm Mohammed\r\n";
char recieved_data[20];

int main()
{
	HAL_Init();
	SystemClockConfig();
	UART2_Init();

	uint16_t Length = strlen(user_data);

	if( HAL_UART_Transmit(&huart2, (uint8_t*)user_data, Length, HAL_MAX_DELAY) != HAL_OK)
	{
		Error_handler();
	}

	Length = strlen(recieved_data);
	if( HAL_UART_Receive(&huart2, (uint8_t*)recieved_data, Length, HAL_MAX_DELAY) != HAL_OK)
	{
		Error_handler();
	}

	while(1);

	return 0;
}


void SystemClockConfig(void)
{

}

void UART2_Init()
{
	huart2.Instance = USART2;
	huart2.Init.BaudRate = 115200;
	huart2.Init.WordLength = UART_WORDLENGTH_8B;
	huart2.Init.StopBits = UART_STOPBITS_1;
	huart2.Init.Parity = UART_PARITY_NONE;
	huart2.Init.Mode = UART_MODE_TX_RX;
	huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;

	if(HAL_UART_Init(&huart2) != HAL_OK)
	{
		//There is a problem
		Error_handler();
	}

}

void Error_handler(void)
{
	while(1);
}
