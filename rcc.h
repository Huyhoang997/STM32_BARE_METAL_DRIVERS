/*
 * rcc.h
 *
 *  Created on: Feb 4, 2026
 *      Author: ACER
 */

#ifndef RCC_H_
#define RCC_H_

#include "stm32f401xx.h"


/* Define RCC clock source configure enum */
typedef enum {
    RCC_HSI_SOURCE_CLOCK,
    RCC_HSE_SOURCE_CLOCK,
    RCC_PLL_SOURCE_CLOCK
} RCC_Source_Clock_Typedef;

/* Define RCC clock speed configure enum */
typedef enum 
{
    RCC_CLOCK_16MHZ,
    RCC_CLOCK_48MHZ ,            
    RCC_CLOCK_64MHZ,             
    RCC_CLOCK_84MHZ             
} RCC_Clock_Speed_Typedef;


/* Define main PLL mode */
#define PLL_OFF                     (0U << 24)
#define PLL_ON                      (1U << 24)

/* Define Clock security system */
#define CSS_OFF                     (0U << 19)
#define CSS_ON                      (1U << 19)

/* Define HSE clock mode */
#define HSE_OFF                     (0U << 16)
#define HSE_ON                      (1U << 16)

/* Define HSI clock mode */
#define HSI_OFF                     0U
#define HSI_ON                      1U

/* Configure main PLL entry clock source */
#define PLL_ENTRY_HSI_CLKSRC        0U
#define PLL_ENTRY_HSE_CLKSRC        1U

/* Configure main SYS entry clock source */
#define SYS_ENTRY_HSI_CLKSRC        0U
#define SYS_ENTRY_HSE_CLKSRC        1U
#define SYS_ENTRY_PLL_CLKSRC        10U

/* Configure division factor for the PLLP */
#define PLLP_DIVIDE_BY_2                    0U
#define PLLP_DIVIDE_BY_4                    1U
#define PLLP_DIVIDE_BY_6                    2U
#define PLLP_DIVIDE_BY_8                    3U

/* Configure division factor for the PLLM */
#define PLLM_DIVIDE_BY_2                    2U
#define PLLM_DIVIDE_BY_4                    4U
#define PLLM_DIVIDE_BY_8                    8U
#define PLLM_DIVIDE_BY_16                   16U


/* Configure clock source for the RCC */
void RCC_InitSystemClock(RCC_Clock_Speed_Typedef Clk_Speed);

#endif /* RCC_H_ */