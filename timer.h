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
	uint32_t CounterValue;		// Cnt value
} TIMER_Config_t;

/* TIMERx Output Compare definition structure */
typedef struct 
{
	uint8_t OutputCompareMode;
	bool is_fast_mode;
	bool is_enable_preload;
} TIMER_OC_Config_t;


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

/* Define macro for TIMERx Channel */
#define TIMER_CHANNEL_1						0U
#define TIMER_CHANNEL_2						1U
#define TIMER_CHANNEL_3						2U
#define TIEMR_CHANNEL_4						3U

/* Define Output Compare active mode */
#define OC1M_FROZEN							0U
#define OC1M_SET_CH1_ACTIVE					1U
#define OC1M_SET_CH1_INACTIVE				2U
#define OC1M_TOGGLE							3U
#define OC1M_FORCE_INACTIVE					4U	
#define OC1M_FORCE_ACTIVE					5U
#define OC1M_PWM_MODE_1						6U			/*  Active as long as TIMx_CNT < TIMx_CCRx */
#define OC1M_PWM_MODE_2						7U			/*  Inactive as long as TIMx_CNT < TIMx_CCR*/

/* Define Output Compare fast mode */
#define OC1FE_DISABLE_FAST_MODE				0U
#define OC1FE_ENABLE_FAST_MODE				1U

/* Mapping TIMERx to IRQ number */
#define TIMER_TO_IRQ(TIMERx) \
	 ((TIMERx == TIMER1 || TIMERx == TIMER11) ? 26U :\
	  (TIMERx == TIMER2) ? 28U :\
	  (TIMERx == TIMER3) ? 29U :\
	  (TIMERx == TIMER4) ? 30U :\
	  (TIMERx == TIMER5) ? 50U :\
	  (TIMERx == TIMER9) ? 24U :\
	  (TIMERx == TIMER10) ? 25U : 0)

 /* ====================================================
 * User API
 * configuration functions for application code.
 * ==================================================== */

/* TIMERx Init */
void TIMER_Base_Init(TIMER_RegDef_t *TIMERx, TIMER_Config_t *Timer_Config);

/* TIMERx start */
void TIMER_Start(TIMER_RegDef_t *TIMERx);

/* TIMERx stop */
void TIMER_Stop(TIMER_RegDef_t *TIMERx);

/* Configure value for PSC register */
void TIMER_TopCount(TIMER_RegDef_t *TIMERx, uint32_t value);

/* Configure value for CNT register */
void TIMER_CountFlag(TIMER_RegDef_t *TIMERx, uint32_t value);

/* Configure interrupt for TIMERx */
void TIMER_BASE_Init_IT(TIMER_RegDef_t *TIMERx, TIMER_Config_t *Timer_Config, uint32_t Priority);

/* TIMERx Output Compare Init */
void TIMER_OC_Init(TIMER_RegDef_t *TIMERx, uint8_t Timer_CHx, TIMER_OC_Config_t *Timer_OC_Config);

/* TIMERx PWM configure duty cycle */ 
void TIMER_PWM_SetDutyRaw(TIMER_RegDef_t *TIMERx, uint8_t Timer_CHx, uint32_t duty_raw);

/* TIMERx PWM configure duty cycle percent */
void TIMER_PWM_SetDutyCycle(TIMER_RegDef_t *TIMERx, uint8_t Timer_CHx, uint32_t duty_cycle);

#endif /* TIMER_H_*/

