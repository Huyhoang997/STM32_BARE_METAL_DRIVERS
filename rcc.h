/*
 * rcc.h
 *
 *  Created on: Feb 10, 2026
 *      Author: ACER
 */
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
typedef enum
{
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

/* Define AHB clock prescale */
typedef enum {
    RCC_AHB_DIV_1 = 0,
    RCC_AHB_DIV_2 = 8U,
    RCC_AHB_DIV_4,
    RCC_AHB_DIV_8,
    RCC_AHB_DIV_16,
    RCC_AHB_DIV_64,
    RCC_AHB_DIV_128,
    RCC_AHB_DIV_256,
    RCC_AHB_DIV_512
} RCC_AHB_Prescaler_t;

/* Define APBx clock prescale*/
typedef enum {
    RCC_APB_DIV_1 = 0,
    RCC_APB_DIV_2 = 4U,
    RCC_APB_DIV_4 ,
    RCC_APB_DIV_8 ,
    RCC_APB_DIV_16
} RCC_APB_Prescaler_t;

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


 /* ====================================================
 * User API
 * configuration functions for application code.
 * ==================================================== */

/* Configure clock source for the RCC */
RCC_Status_Typedef RCC_InitSystemClock(RCC_Clock_Speed_Typedef Clk_Speed);

/* Configure AHB clock prescale */
void RCC_AHB_SetPrescale(RCC_AHB_Prescaler_t AHB_Prescale);

/* Configure APB1 clock prescale */
void RCC_APB1_SetPrescale(RCC_APB_Prescaler_t APB1_Prescale);

/* Configure APB2 clock prescale */
void RCC_APB2_SetPrescale(RCC_APB_Prescaler_t APB2_Prescale);

/* Read clock frequency from APB1 peripheral bus */
uint32_t RCC_APB1_GetFreq(void);

/* Read clock frequency from APB2 peripheral bus */
uint32_t RCC_APB2_GetFreq(void);

#endif /* RCC_H_ */

