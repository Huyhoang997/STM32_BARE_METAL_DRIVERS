/*
 * cortex_M4.c
 *
 *  Created on: Jan 30, 2026
 *      Author: ACER
 */
#include "stm32f401xx.h"

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

	/* Set priority for the IRQ number */
	NVIC->IPR[index] &= ~(0xFF << (bitpos * 8U));
	NVIC->IPR[index] |= ((Priority << 4U) << (bitpos * 8U));
}

