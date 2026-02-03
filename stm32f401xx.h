/*
 * stm32f401xx.h
 *
 *  Created on: Jan 29, 2026
 *      Author: ACER
 */

#ifndef STM32F401XX_H_
#define STM32F401XX_H_

#include <stdint.h>
#include <stdbool.h>
#include "gpio.h"
#include "cortex_m4.h"

/*Flash registers definition structure */
typedef struct
{
	volatile uint32_t ACR;
	volatile uint32_t KEYR;
	volatile uint32_t OPTKEYR;
	volatile uint32_t SR;
	volatile uint32_t CR;
	volatile uint32_t OPTCR;
} FLASH_RegDef_t;


/* RCC register definition structure*/
typedef struct
{
	volatile uint32_t CR;
	volatile uint32_t PLLCFGR;
	volatile uint32_t CFGR;
	volatile uint32_t CIR;
	volatile uint32_t AHB1RSTR;
	volatile uint32_t AHB2RSTR;
	uint32_t RESERVED1[2];
	volatile uint32_t APB1RSTR;
	volatile uint32_t APB2RSTR;
	uint32_t RESERVED2[2];
	volatile uint32_t AHB1ENR;
	volatile uint32_t AHB2ENR;
	uint32_t RESERVED3[2];
	volatile uint32_t APB1ENR;
	volatile uint32_t APB2ENR;
	uint32_t RESERVED4[2];
	volatile uint32_t AHB1LPENR;
	volatile uint32_t AHB2LPENR;
	uint32_t RESERVED5[2];
	volatile uint32_t APB1LPENR;
	volatile uint32_t APB2LPENR;
	uint32_t RESERVED6[2];
	volatile uint32_t BDCR;
	volatile uint32_t CSR;
	uint32_t RESERVED7[2];
	volatile uint32_t SSCGR;
	volatile uint32_t PLLI2SCFGR;
} RCC_RegDef_t;


/* SYSCFG register definition structure */
typedef struct
{
	volatile uint32_t MEMRMP;
	volatile uint32_t PMC;
	volatile uint32_t EXTICR[4];
	volatile uint32_t CMPCR;
} SYSCFG_RegDef_t;


/* GPIOx register definition structure  */
typedef struct
{
	volatile uint32_t MODER;
	volatile uint32_t OTYPER;
	volatile uint32_t OSPEEDR;
	volatile uint32_t PUPDR;
	volatile uint32_t IDR;
	volatile uint32_t ODR;
	volatile uint32_t BSRR;
	volatile uint32_t LCKR;
	volatile uint32_t AFRL;
	volatile uint32_t AFRH;
} GPIO_RegDef_t;


/* EXTI registers definition structure */
typedef struct
{
	volatile uint32_t IMR;
	volatile uint32_t EMR;
	volatile uint32_t RTSR;
	volatile uint32_t FTSR;
	volatile uint32_t SWIER;
	volatile uint32_t PR;
} EXTI_RegDef_t;


/* Common TIMERx registers definition structure */
typedef struct
{
	volatile uint32_t CR1;
	volatile uint32_t CR2;
	volatile uint32_t SMCR;
	volatile uint32_t DIER;
	volatile uint32_t SR ;
	volatile uint32_t EGR;
	volatile uint32_t CCMR1;
	volatile uint32_t CCMR2;
	volatile uint32_t CCER;
	volatile uint32_t CNT;
	volatile uint32_t PSC;
	volatile uint32_t ARR;
	uint32_t RESERVED1;
	volatile uint32_t CCR1;
	volatile uint32_t CCR2;
	volatile uint32_t CCR3;
	volatile uint32_t CCR4;
	uint32_t RESERVED2;
	volatile uint32_t DCR;
	volatile uint32_t DMAR;
	volatile uint32_t OR;
} TIMER_RegDef_t;


/* Define peripheral buses base address */
#define AHB2_BASE_ADDR					(0x50000000UL)
#define AHB1_BASE_ADDR					(0x40020000UL)
#define APB2_BASE_ADDR					(0x40010000UL)
#define APB1_BASE_ADDR					(0x40000000UL)

/* Define Flash base address */
#define FLASH_BASE_ADDR					((AHB1_BASE_ADDR) + 0x3C00UL)
/* Define macro for Flash address */
#define FLASH							((FLASH_RegDef_t *)FLASH_BASE_ADDR)
/* Define RCC base address */
#define RCC_BASE_ADDR					((AHB1_BASE_ADDR) + 0x3800UL)
/* Define macro for RCC address */
#define RCC								((RCC_RegDef_t *)RCC_BASE_ADDR)

/* Define SYSCFG base address */
#define SYSCFG_BASE_ADDR				((APB2_BASE_ADDR) + 0x3800UL)
/* Define macro for SYSCFG address */
#define SYSCFG							((SYSCFG_RegDef_t *)SYSCFG_BASE_ADDR)

/* Define EXTI base adddress */
#define EXTI_BASE_ADDRESS				((APB2_BASE_ADDR) + 0x3C00UL)
/* Define macro for EXTI address*/
#define EXTI							((EXTI_RegDef_t *)EXTI_BASE_ADDRESS)


/* Define advanced TIMERx base address */
#define TIMER1_BASE_ADDR 				((APB2_BASE_ADDR) + 0x2C00UL)

/* Define general TIMERx base address */
#define TIMER2_BASE_ADDR				((APB1_BASE_ADDR) + 0x0000UL)
#define TIMER3_BASE_ADDR				((APB1_BASE_ADDR) + 0x0400UL)
#define TIMER4_BASE_ADDR				((APB1_BASE_ADDR) + 0x0800UL)
#define TIMER5_BASE_ADDR				((APB1_BASE_ADDR) + 0x0C00UL)

/* Define basic TIMERx base address */
#define TIMER9_BASE_ADDR				((APB2_BASE_ADDR) + 0x4000UL)
#define TIMER10_BASE_ADDR				((APB2_BASE_ADDR) + 0x4400UL)
#define TIMER11_BASE_ADDR				((APB2_BASE_ADDR) + 0x4800UL)

/* Define macro for advanced TIMERx address */
#define TIMER1							((TIMER_RegDef_t *) TIMER1_BASE_ADDR)

/* Define macro for genaral TIMERx address */
#define TIMER2							((TIMER_RegDef_t *) TIMER2_BASE_ADDR)
#define TIMER3							((TIMER_RegDef_t *) TIMER3_BASE_ADDR)
#define TIMER4							((TIMER_RegDef_t *) TIMER4_BASE_ADDR)
#define TIMER5							((TIMER_RegDef_t *) TIMER5_BASE_ADDR)

/* Define macro for basci TIMERx address */
#define TIMER9							((TIMER_RegDef_t *) TIMER9_BASE_ADDR)
#define TIMER10							((TIMER_RegDef_t *) TIMER10_BASE_ADDR)
#define TIMER11							((TIMER_RegDef_t *) TIMER11_BASE_ADDR)

/* Define GPIOx base address */
#define GPIOA_BASE_ADDR					((AHB1_BASE_ADDR) + 0x0000UL)
#define GPIOB_BASE_ADDR					((AHB1_BASE_ADDR) + 0x0400UL)
#define GPIOC_BASE_ADDR					((AHB1_BASE_ADDR) + 0x0800UL)
#define GPIOD_BASE_ADDR					((AHB1_BASE_ADDR) + 0x0C00UL)
#define GPIOE_BASE_ADDR					((AHB1_BASE_ADDR) + 0x1000UL)
#define GPIOH_BASE_ADDR					((AHB1_BASE_ADDR) + 0x1C00UL)


/* Define macro for GPIOx addresses */
#define GPIOA							((GPIO_RegDef_t *)GPIOA_BASE_ADDR)
#define GPIOB							((GPIO_RegDef_t *)GPIOB_BASE_ADDR)
#define GPIOC							((GPIO_RegDef_t *)GPIOC_BASE_ADDR)
#define GPIOD							((GPIO_RegDef_t *)GPIOD_BASE_ADDR)
#define GPIOE							((GPIO_RegDef_t *)GPIOE_BASE_ADDR)
#define GPIOH							((GPIO_RegDef_t *)GPIOH_BASE_ADDR)

/* Enable RCC clock for given GPIO port */
#define GPIO_ENABLE_CLOCK(GPIOx) \
	((GPIOx == GPIOA) ? (RCC->AHB1ENR |= (1U << 0)) :\
	 (GPIOx == GPIOB) ? (RCC->AHB1ENR |= (1U << 1)) :\
	 (GPIOx == GPIOC) ? (RCC->AHB1ENR |= (1U << 2)) :\
	 (GPIOx == GPIOD) ? (RCC->AHB1ENR |= (1U << 3)) :\
	 (GPIOx == GPIOE) ? (RCC->AHB1ENR |= (1U << 4)) :\
	 (GPIOx == GPIOH) ? (RCC->AHB1ENR |= (1U << 7)) : 0)

/* Disable RCC clock for given GPIO port */
#define GPIO_DISABLE_CLOCK(GPIOx) \
	((GPIOx == GPIOA) ? (RCC->AHB1ENR &= ~(1U << 0)) :\
	 (GPIOx == GPIOB) ? (RCC->AHB1ENR &= ~(1U << 1)) :\
	 (GPIOx == GPIOC) ? (RCC->AHB1ENR &= ~(1U << 2)) :\
	 (GPIOx == GPIOD) ? (RCC->AHB1ENR &= ~(1U << 3)) :\
	 (GPIOx == GPIOE) ? (RCC->AHB1ENR &= ~(1U << 4)) :\
	 (GPIOx == GPIOH) ? (RCC->AHB1ENR &= ~(1U << 7)) : 0)

/* Enable SYSCFG for EXTI */
#define SYSCFG_ENABLE_CLOCK					(RCC->APB2ENR |= (1U << 14U))

/* Define SYSCFG portcode */
#define SYSCFG_EXTICR_PORTCODE(GPIOx) \
	((GPIOx == GPIOA) ? 0U :\
	 (GPIOx == GPIOB) ? 1U :\
	 (GPIOx == GPIOC) ? 2U :\
	 (GPIOx == GPIOD) ? 3U :\
	 (GPIOx == GPIOE) ? 4U:\
	 (GPIOx == GPIOH) ? 7U : 0)

/* Enable TIMERx clock */
#define TIMER_ENABLE_CLOCK(TIMERx) \
	((TIMERx == TIMER1) ? (RCC->APB2ENR |= (1U << 0U)) :\
	 (TIMERx == TIMER2) ? (RCC->APB1ENR |= (1U << 0U)) :\
	 (TIMERx == TIMER3) ? (RCC->APB1ENR |= (1U << 1U)) :\
	 (TIMERx == TIMER4) ? (RCC->APB1ENR |= (1U << 2U)) :\
	 (TIMERx == TIMER5) ? (RCC->APB1ENR |= (1U << 3U)) :\
	 (TIMERx == TIMER9) ? (RCC->APB2ENR |= (1U << 16U)) :\
	 (TIMERx == TIMER10) ? (RCC->APB2ENR |= (1U << 17U)) :\
	 (TIMERx == TIMER11) ? (RCC->APB2ENR |= (1U << 18U)) : 0)


#endif /* STM32F401XX_H_ */
