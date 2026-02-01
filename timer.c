/*
 * timer.c
 *
 *  Created on: Jan 31, 2026
 *      Author: ACER
 */
#include "timer.h"

/* TIMERx Init */
void TIMER_Base_Init(TIMER_RegDef_t *TIMERx, TIMER_Config_t *Timer_Config)
{
	/* Enable TIMERx clock */
	TIMER_ENABLE_CLOCK(TIMERx);
	/* Select clock division */
	TIMERx->CR1	&= ~(3U << 8U);
	TIMERx->CR1 |= (Timer_Config->ClockDivision << 8U);

	/* Enable/Disable preload */
	(Timer_Config->is_enable_Preload) ? (TIMERx->CR1 |= (1U << 7U)) :
										(TIMERx->CR1 &= ~(1U << 7U));
	/* Enable/Disable one pulse mode */
	(Timer_Config->is_enable_OnePulse) ? (TIMERx->CR1 |= (1U << 3U)) :
										 (TIMERx->CR1 &= ~(1U << 3U));



	/* Configure TIMERx counter mode */
	TIMERx->CR1 &= ~(1U << 4U);
	TIMERx->CR1 |= (Timer_Config->CounterMode << 4U);

	/* Configure TIMERx update source */
	TIMERx->CR1 &= ~(1U << 2U);
	TIMERx->CR1 |= (Timer_Config->UpdateSource << 2U);

	/* Set auto reload value */
	TIMERx->ARR = Timer_Config->AutoReload;
	/* Set prescale for the TIMERx */
	TIMERx->PSC = Timer_Config->Prescaler;
	/* Enable bit genarate event flag */
	TIMERx->EGR |= (1U << 0U);
	/* Clear bit event flag */
	TIMERx->SR &= ~(1U << 0U);
	/* Set counter value */
	TIMERx->CNT = Timer_Config->CounterValue;

}


/* TIMERx start */
void TIMER_Start(TIMER_RegDef_t *TIMERx)
{
	TIMERx->CR1 |= (1U << 0U);
}


/* TIMERx stop */
void TIMER_Stop(TIMER_RegDef_t *TIMERx)
{
	TIMERx->CR1 &= ~(1U << 0U);
}


/* Configure value for PSC register */
void TIMER_TopCount(TIMER_RegDef_t *TIMERx, uint32_t value)
{
	TIMERx->ARR = value;
}

void TIMER_CountFlag(TIMER_RegDef_t *TIMERx, uint32_t value)
{
	TIMERx->CNT = value;
}
