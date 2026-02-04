/*
 * cortex_M4.h
 *
 *  Created on: Jan 30, 2026
 *      Author: ACER
 */

#ifndef CORTEX_M4_H_
#define CORTEX_M4_H_

#include "stm32f401xx.h"

/* Extern gobal variable to get RCC clock */
extern uint32_t SystemCoreClock;

/* NVIC definition structure */
typedef struct 
{
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

/* Systick timer registers difinition structure */
typedef struct 
{
	volatile uint32_t CTRL;
	volatile uint32_t LOAD;
	volatile uint32_t VAL;
	volatile uint32_t CALIB;
} STK_RegDef_t;


/* Define the NVIC base address */
#define NVIC_BASE_ADDR			0xE000E100
/* Define macro for the NVIC */
#define NVIC 					((NVIC_RegDef_t *)NVIC_BASE_ADDR)

/* Define IRQ's priority bit group  */
#define SCB_BASE_ADDR			0xE000ED00
#define SCB_AIRCR  				(*(volatile uint32_t *)(SCB_BASE_ADDR + 0x0CU))

/* Define the Systick timer base address */
#define STK_BASE_ADDR			(0xE000E010UL)
/* Define macro for the Systick timer address */
#define STK						((STK_RegDef_t *)STK_BASE_ADDR)

/* Configure the Systick source clock */
#define STK_AHB_CLKSRC			0U
#define STK_PROCESSOR_CLKSRC	1U

/* Configure Systick counter interrupt */
#define STK_TICKINT_DISABLE		0U
#define STK_TICKINT_ENABLE		1U

/* Configure Systick counter state */
#define STK_DISABLE_COUNTER			0U
#define STK_ENABLE_COUNTER			1U


 /* ====================================================
 * User API
 * configuration functions for application code.
 * ==================================================== */

/* Enable the IRQ number */
void NVIC_EnableIRQ(uint8_t IRQNumber);

/* Disable the IRQ number */
void NVIC_DisableIRQ(uint8_t IRQNumber);

/* Set priority for the IRQ number */
void NVIC_SetPriority(uint8_t IRQNumber, uint8_t Priority);

/* Systick Init function */
void SYS_InitTick(void);

/* System level(SL) delay millisecond(ms) */
void SL_Delay_ms(uint32_t ms);

#endif /* CORTEX_M4_H_ */
