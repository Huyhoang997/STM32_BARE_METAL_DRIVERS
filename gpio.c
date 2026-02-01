/*
 * gpio.c
 *
 *  Created on: Jan 29, 2026
 *      Author: ACER
 */
#include "stm32f401xx.h"


/* Init GPIO port */
void GPIO_Init_Mode(GPIO_RegDef_t *GPIOx, GPIO_Config_t *GPIO_Config) {
	/* 1. Enable clock for the GPIO port*/
	GPIO_ENABLE_CLOCK(GPIOx);
	/* 2. Configure GPIO mode */
	GPIOx->MODER &= ~(3U << (GPIO_Config->GPIO_PIN * 2));
	GPIOx->MODER |= (GPIO_Config->GPIO_MODE << (GPIO_Config->GPIO_PIN * 2));

	/* 2.1 GPIO output mode */
	if(GPIO_Config->GPIO_MODE == GPIO_MODE_OUTPUT || GPIO_Config->GPIO_MODE == GPIO_MODE_ALT)
	{
		/* 2.1 Configure the GPIO output type*/
		GPIOx->OTYPER &= ~(1U << GPIO_Config->GPIO_PIN);
		GPIOx->OTYPER |= (GPIO_Config->GPIO_OUT_TYPE << GPIO_Config->GPIO_PIN);

		/* 2.2 Configure the GPIO output speed */
		GPIOx->OSPEEDR &= ~(3U << (GPIO_Config->GPIO_PIN *2));
		GPIOx->OSPEEDR |= (GPIO_Config->GPIO_OUT_SPEED << (GPIO_Config->GPIO_PIN *2));
	}

	/* 3. Configure the GPIO to pull-up / pull-down */
	GPIOx->PUPDR &= ~(3U << (GPIO_Config->GPIO_PIN *2));
	GPIOx->PUPDR |= (GPIO_Config->GPIO_PUPD << (GPIO_Config->GPIO_PIN *2));

	/* Select Alt mode for the GPIO pin */
	if(GPIO_Config->GPIO_MODE == GPIO_MODE_ALT)
	{
		if(GPIO_Config->GPIO_PIN < 8)
		{
			GPIOx->AFRL &= ~(15U << (GPIO_Config->GPIO_PIN * 4));
			GPIOx->AFRL |= (GPIO_Config->GPIO_ALT_MODE << (GPIO_Config->GPIO_PIN * 4));
		}
		else
		{
			GPIOx->AFRH &= ~(15U << (GPIO_Config->GPIO_PIN * 4));
			GPIOx->AFRH |= (GPIO_Config->GPIO_ALT_MODE << (GPIO_Config->GPIO_PIN * 4));
		}
	}
}


/* De-Init the GPIO port */
void GPIO_DeInit(GPIO_RegDef_t *GPIOx)
{
	/* Disable the GPIO clock*/
	GPIO_DISABLE_CLOCK(GPIOx);
}


/* Set the GPIO pin to High */
void GPIO_PinOutSet(GPIO_RegDef_t *GPIOx, uint8_t GPIO_PIN)
{
	GPIOx->BSRR |= (1U << GPIO_PIN);
}


/* Set the GPIO pin to Low */
void GPIO_PinOutClear(GPIO_RegDef_t *GPIOx, uint8_t GPIO_PIN)
{
	GPIOx->BSRR |= (1U << (GPIO_PIN + 16U));
}


/* Toogle value of the GPIO pin */
void GPIO_PinOutToggle(GPIO_RegDef_t *GPIOx, uint8_t GPIO_PIN)
{
	GPIOx->ODR ^= (1U << GPIO_PIN);
}


/* Read the value of the GPIO */
GPIO_PinState_Typedef GPIO_PinInRead(GPIO_RegDef_t *GPIOx, uint8_t GPIO_PIN)
{
	return (GPIOx->IDR & (1U << GPIO_PIN)) ? GPIO_PIN_HIGH : GPIO_PIN_LOW;
}


/* Init GPIO intterupt */
void GPIO_Init_IT(GPIO_RegDef_t *GPIOx, GPIO_Config_t *GPIO_Config, uint8_t Priority)
{
	uint8_t index, bitpos, portcode;
	index = (GPIO_Config->GPIO_PIN) /4;
	bitpos = (GPIO_Config->GPIO_PIN % 4) *4;
	portcode = SYSCFG_EXTICR_PORTCODE(GPIOx);
	/* Enable GPIO clock */
	GPIO_ENABLE_CLOCK(GPIOx);
	/* Enable SYSCFG clock */
	SYSCFG_ENABLE_CLOCK;

	/* Select the correct EXTICR register */
	SYSCFG->EXTICR[index] &= ~(15U << bitpos);
	SYSCFG->EXTICR[index] |= (portcode << bitpos);

	/* Configure mode for the GPIO pin */
	GPIOx->MODER &= ~(3U << (GPIO_Config->GPIO_PIN * 2));
	GPIOx->MODER |= (GPIO_Config->GPIO_MODE << (GPIO_Config->GPIO_PIN * 2));

	/* Configure the GPIO to pull-up / pull-down */
	GPIOx->PUPDR &= ~(3U << (GPIO_Config->GPIO_PIN *2));
	GPIOx->PUPDR |= (GPIO_Config->GPIO_PUPD << (GPIO_Config->GPIO_PIN *2));

	if(GPIO_Config->GPIO_MODE == GPIO_MODE_INPUT)
	{
		switch(GPIO_Config->GPIO_IT_TRIGGER_MODE)
		{
		case GPIO_IT_FALLING :
			EXTI->FTSR	|= (1U << GPIO_Config->GPIO_PIN);
			EXTI->RTSR &= ~(1U << GPIO_Config->GPIO_PIN);
			break;
		case GPIO_IT_RAISING:
			EXTI->RTSR |= (1U << GPIO_Config->GPIO_PIN);
			EXTI->FTSR	&= ~(1U << GPIO_Config->GPIO_PIN);
			break;
		case GPIO_IT_FALLING_RAISING:
			EXTI->FTSR	|= (1U << GPIO_Config->GPIO_PIN);
			EXTI->RTSR |= (1U << GPIO_Config->GPIO_PIN);
			break;
		}
	}
	/* Clear pending interrupt flag of the EXTI*/
	EXTI->PR = (1U << GPIO_Config->GPIO_PIN);
	/* Enable interrupt masking register */
	EXTI->IMR |= (1U << GPIO_Config->GPIO_PIN);

	/* Set the priority for the EXTI */
	NVIC_SetPriority(EXTI_TO_IRQ(GPIO_Config->GPIO_PIN), Priority);
	/* Enable NVIC */
	NVIC_EnableIRQ(EXTI_TO_IRQ(GPIO_Config->GPIO_PIN));
}
