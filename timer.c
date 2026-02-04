/*
 * timer.c
 *
 *  Created on: Jan 31, 2026
 *      Author: ACER
 */
#include "stm32f401xx.h"

/* TIMERx Init */
void TIMER_Base_Init(TIMER_RegDef_t *TIMERx, TIMER_Config_t *Timer_Config)
{
	/* Enable TIMERx clock */
	TIMER_ENABLE_CLOCK(TIMERx);
	/* Select clock division */
	TIMERx->CR1	&= ~(3U << 8);
	TIMERx->CR1 |= (Timer_Config->ClockDivision << 8);

	/* Enable/Disable preload */
	(Timer_Config->is_enable_Preload) ? (TIMERx->CR1 |= (1U << 7)) :
										(TIMERx->CR1 &= ~(1U << 7));
	/* Enable/Disable one pulse mode */
	(Timer_Config->is_enable_OnePulse) ? (TIMERx->CR1 |= (1U << 3)) :
										 (TIMERx->CR1 &= ~(1U << 3));

	/* Configure TIMERx counter mode */
	TIMERx->CR1 &= ~(1U << 4);
	TIMERx->CR1 |= (Timer_Config->CounterMode << 4);

	/* Configure TIMERx update source */
	TIMERx->CR1 &= ~(1U << 2);
	TIMERx->CR1 |= (Timer_Config->UpdateSource << 2);

	/* Set auto reload value */
	TIMERx->ARR = Timer_Config->AutoReload;
	/* Set prescale for the TIMERx */
	TIMERx->PSC = Timer_Config->Prescaler;
	/* Enable bit genarate event flag */
	TIMERx->EGR |= (1U << 0);
	/* Clear bit event flag */
	TIMERx->SR &= ~(1U << 0);
	/* Set counter value */
	TIMERx->CNT = Timer_Config->CounterValue;

}


/* TIMERx start */
void TIMER_Start(TIMER_RegDef_t *TIMERx)
{
	TIMERx->CR1 |= (1U << 0);
}


/* TIMERx stop */
void TIMER_Stop(TIMER_RegDef_t *TIMERx)
{
	TIMERx->CR1 &= ~(1U << 0);
}


/* Configure value for PSC register */
void TIMER_TopCount(TIMER_RegDef_t *TIMERx, uint32_t value)
{
	TIMERx->ARR = value;
}


/* Configure value for CNT register */
void TIMER_CountFlag(TIMER_RegDef_t *TIMERx, uint32_t value)
{
	TIMERx->CNT = value;
}


/* Configure interrupt for TIMERx */
void TIMER_BASE_Init_IT(TIMER_RegDef_t *TIMERx, TIMER_Config_t *Timer_Config, uint32_t Priority)
{
	/* Enable TIMERx clock */
	TIMER_ENABLE_CLOCK(TIMERx);
	/* Select clock division */
	TIMERx->CR1	&= ~(3U << 8);
	TIMERx->CR1 |= (Timer_Config->ClockDivision << 8);

	/* Enable/Disable preload */
	(Timer_Config->is_enable_Preload) ? (TIMERx->CR1 |= (1U << 7)) :
										(TIMERx->CR1 &= ~(1U << 7));
	/* Enable/Disable one pulse mode */
	(Timer_Config->is_enable_OnePulse) ? (TIMERx->CR1 |= (1U << 3)) :
										 (TIMERx->CR1 &= ~(1U << 3));

	/* Configure TIMERx counter mode */
	TIMERx->CR1 &= ~(1U << 4);
	TIMERx->CR1 |= (Timer_Config->CounterMode << 4);

	/* Configure TIMERx update source */
	TIMERx->CR1 &= ~(1U << 2);
	TIMERx->CR1 |= (Timer_Config->UpdateSource << 2);

	/* Set auto reload value */
	TIMERx->ARR = Timer_Config->AutoReload;
	/* Set prescale for the TIMERx */
	TIMERx->PSC = Timer_Config->Prescaler;
	/* Enable bit genarate event flag */
	TIMERx->EGR |= (1U << 0);
	/* Clear bit event flag */
	TIMERx->SR &= ~(1U << 0);
	/* Set counter value */
	TIMERx->CNT = Timer_Config->CounterValue;
	/* Enable interrupt bit */
	TIMERx->DIER |= (1U << 0);

	/* Set the priority for the TIMERx */
	NVIC_SetPriority(TIMER_TO_IRQ(TIMERx), Priority);
	/* Enable NVIC */
	NVIC_EnableIRQ(TIMER_TO_IRQ(TIMERx));
}
