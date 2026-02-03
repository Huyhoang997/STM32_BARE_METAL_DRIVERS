/*
 * timer.h
 *
 *  Created on: Jan 31, 2026
 *      Author: ACER
 */
#ifndef TIMER_H_
#define TIMER_H_

#include "stm32f401xx.h"

/* TIMERx definition structure */
typedef struct
{
	uint8_t ClockDivision;
	uint32_t AutoReload;
	uint16_t Prescaler;
	bool is_enable_Preload;
	uint8_t CounterMode;
	bool is_enable_OnePulse;
	uint8_t UpdateSource;
	uint32_t CounterValue;
} TIMER_Config_t;


/* Define TIMERx clock division */
#define CLOCK_DIVINE_BY_1					0U
#define CLOCK_DIVINE_BY_2					1U
#define CLOCK_DIVINE_BY_4					2U

/* Define TIMERx counter mode */
#define COUNTER_MODE_UP						0U
#define COUNTER_MODE_DOWN					1U

/* Define TIMERx update event */
#define TIMER_UPDATE_ALL_EVENT				0U
#define TIMER_UPDATE_COUNTER_ONLY			1U

/* Mapping TIMERx to IRQ number */
#define TIMER_TO_IRQ(TIMERx) \
	 ((TIMERx == TIMER1 || TIMERx == TIMER11) ? 26U :\
	  (TIMERx == TIMER2) ? 28U :\
	  (TIMERx == TIMER3) ? 29U :\
	  (TIMERx == TIMER4) ? 30U :\
	  (TIMERx == TIMER5) ? 50U :\
	  (TIMERx == TIMER9) ? 24U :\
	  (TIMERx == TIMER10) ? 25U : 0)


void TIMER_Base_Init(TIMER_RegDef_t *TIMERx, TIMER_Config_t *Timer_Config);
void TIMER_Start(TIMER_RegDef_t *TIMERx);
void TIMER_Stop(TIMER_RegDef_t *TIMERx);
void TIMER_TopCount(TIMER_RegDef_t *TIMERx, uint32_t value);
void TIMER_CountFlag(TIMER_RegDef_t *TIMERx, uint32_t value);
void TIMER_BASE_Init_IT(TIMER_RegDef_t *TIMERx, TIMER_Config_t *Timer_Config, uint32_t Priority);

#endif /* TIMER_H_*/

