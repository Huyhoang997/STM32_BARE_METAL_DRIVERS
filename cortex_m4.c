/*
 * cortex_M4.c
 *
 *  Created on: Jan 30, 2026
 *      Author: ACER
 */
#include "stm32f401xx.h"

uint32_t SystemCoreClock = 16000000;
uint32_t uwTick;

void NVIC_EnableIRQ(uint8_t IRQNumber)
{
	uint8_t index, bitpos;
	/* Get the IRQ register */
	index = IRQNumber / 32U;
	/* Get the IRQ number in the register */
	bitpos = IRQNumber % 32U;
	/* Enable the IRQ*/
	NVIC->ISER[index] |= (1U << bitpos);
}

void NVIC_DisableIRQ(uint8_t IRQNumber)
{
	uint8_t index, bitpos;
	/* Get the IRQ register */
	index = IRQNumber / 32U;
	/* Get the IRQ number in the register */
	bitpos = IRQNumber % 32U;
	/* Disable the IRQ*/
	NVIC->ICER[index] |= (1U << bitpos);
}

void NVIC_SetPriority(uint8_t IRQNumber, uint8_t Priority)
{
	uint8_t index, bitpos;
	/* Acccess the correct IPR register */
	index = IRQNumber / 4U;
	/* Access the correct bit fields of the IPR register */
	bitpos = IRQNumber % 4U;
	/* Configure IRQ priority bitgroup */
	SCB_AIRCR = (0x5FA << 16) | (0U << 8);
	/* Set priority for the IRQ number */
	NVIC->IPR[index] &= ~(0xFF << (bitpos * 8U));
	NVIC->IPR[index] |= ((Priority << 4) << (bitpos * 8U));
}

void SYS_InitTick(void)
{
	uint32_t reload;
	/* Get the system xx(ms) overflow from the RCC clock */
	reload = SystemCoreClock / 1000;
	STK->LOAD = reload - 1;
	STK->VAL = 0;
	/* Configure source clock & interrupt & counter mode for the Systick  */
	STK->CTRL = (STK_PROCESSOR_CLKSRC << 2) | (STK_TICKINT_ENABLE << 1) | (STK_ENABLE_COUNTER << 0);
}

/* SysTick interrupt handling */
void SysTick_Handler(void)
{
	uwTick++;
}

/* System level (SL) delay millisecond */
void SL_Delay_ms(uint32_t ms)
{
	uint32_t start = uwTick;
	while((uwTick - start) < ms);
}
