/*
 * main.c
 *
 *  Created on: Nov 23, 2026
 *      Author: Med Dahou
 */

#include "stm32f4xx_hal.h"
#include "main.h"
#include "string.h"

#define FALSE  0
#define TRUE   1

void SystemClockConfig(void);
void UART2_Init(void);
void Error_handler(void);
uint8_t convert_to_upper(uint8_t data);

UART_HandleTypeDef huart2;
uint32_t count = 0;
uint8_t data_buffer[100];
uint8_t recieved_data = 0;

uint8_t reception_complete = FALSE;

char *user_data = "The application is running\r\n";


int main()
{
	HAL_Init();
	SystemClockConfig();
	UART2_Init();

	uint16_t Length = strlen(user_data);
	HAL_UART_Transmit(&huart2, (uint8_t*)user_data, Length, HAL_MAX_DELAY) ;


	HAL_UART_Receive_IT(&huart2, &recieved_data, 1);



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

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(recieved_data == '\r')
	{

		data_buffer[count++] = '\r';
		HAL_UART_Transmit(&huart2, data_buffer, count, HAL_MAX_DELAY) ;
		count = 0;
	}

	else
	{
		data_buffer[count++] = recieved_data;
	}

	HAL_UART_Receive_IT(&huart2, &recieved_data, 1);
}

void Error_handler(void)
{
	while(1);
}

uint8_t convert_to_upper(uint8_t data)
{
	if( data >= 'a' && data <= 'z')
	{
		data -= 32;
	}

	return data;
}
