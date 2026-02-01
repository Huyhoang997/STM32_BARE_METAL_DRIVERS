/*
 * cortex_M4.h
 *
 *  Created on: Jan 30, 2026
 *      Author: ACER
 */

#ifndef CORTEX_M4_H_
#define CORTEX_M4_H_

#include "stm32f401xx.h"
/* NVIC definition structure */
typedef struct {
	volatile uint32_t ISER[8];
	uint32_t RESERVED1[24];
	volatile uint32_t ICER[8];
	uint32_t RESERVED2[24];
	volatile uint32_t ISPR[8];
	uint32_t RESERVED3[24];
	volatile uint32_t ICPR[8];
	uint32_t RESERVED4[24];
	volatile uint32_t IABR[8];
	uint32_t RESERVED5[24];
	volatile uint32_t IPR[60];
	uint32_t RESERVED6[644];
	volatile uint32_t STIR;
} NVIC_RegDef_t;

/* Define the NVIC base address */
#define NVIC_BASE_ADDR			0xE000E100
/* Define macro for the NVIC */
#define NVIC 					((NVIC_RegDef_t *)NVIC_BASE_ADDR)

void NVIC_EnableIRQ(uint8_t IRQNumber);
void NVIC_DisableIRQ(uint8_t IRQNumber);
void NVIC_SetPriority(uint8_t IRQNumber, uint8_t Priority);
#endif /* CORTEX_M4_H_ */
