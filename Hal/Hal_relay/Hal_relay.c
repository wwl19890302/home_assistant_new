/**
********************************************************
*
* @file      Hal_rgb_led.c
* @author    Gizwtis
* @version   V03010100
* @date      2016-07-05
*
* @brief     机智云.只为智能硬件而生
*            Gizwits Smart Cloud  for Smart Products
*            链接|增值ֵ|开放|中立|安全|自有|自由|生态
*            www.gizwits.com
*
*********************************************************/
#include "Hal_relay/Hal_relay.h"

void relayGpioInit(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
	__HAL_RCC_GPIOB_CLK_ENABLE();

    GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStructure.Pin = relay0_pin;
    HAL_GPIO_Init(relay0_gpio, &GPIO_InitStructure);
	
	HAL_GPIO_WritePin(relay0_gpio, relay0_pin, GPIO_PIN_RESET);
}

void relay_on(uint8_t index)
{
	if(index == 0)
	{
		HAL_GPIO_WritePin(relay0_gpio, relay0_pin, GPIO_PIN_SET);
	}
//	else {led1 = 0;}
}
void relay_off(uint8_t index)
{
	if(index == 0)
	{
		HAL_GPIO_WritePin(relay0_gpio, relay0_pin, GPIO_PIN_RESET);
	}
//	else {led1 = 1;}
}


