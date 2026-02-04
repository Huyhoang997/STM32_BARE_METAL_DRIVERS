/*
 * gpio.c
 *
 *  Created on: Feb 4, 2026
 *      Author: ACER
 */

#include "stm32f401xx.h"

/* RCC Init (HSI only) */
void RCC_InitSystemClock(RCC_Clock_Speed_Typedef Clk_Speed) 
{
    uint8_t pllp, pllm;
    uint16_t plln;

    /* Disable PLL */
    RCC->CR &= ~(1U << 24);

   /* Configure clock source for the RCC */
   /* 1.1 VCO input frequency = PLL input clock frequency / PLLM with (2 ≤ PLLM ≤ 63) (1 ≤ VCO input ≤ 2) */ 
   /* 1.2 VCO output frequency = VCO input frequency × PLLN with 192 ≤ PLLN ≤ 432*/
   /* 1.3 PLL output clock frequency = VCO frequency / PLLP with PLLP = 2, 4, 6, or 8*/
    switch(Clk_Speed) 
    {
        case RCC_CLOCK_16MHZ:
            /* Enable HSI */
            RCC->CR |= HSI_ON;
            while(!(RCC->CR & (1U << 1)));    // Wait for the HSI ready flag
            /* Select HSI as SYS entry clock */
            RCC->CFGR &= ~(3U << 2);
            RCC->CFGR |= (SYS_ENTRY_HSI_CLKSRC << 2);
        break;

        case RCC_CLOCK_48MHZ:
            pllm = PLLM_DIVIDE_BY_16; plln = 192U; pllp = PLLP_DIVIDE_BY_4; 

            /* Enable HSI */
            RCC->CR |= HSI_ON;
            while(!(RCC->CR & (1U << 1)));    // Wait for the HSI ready flag
            /* Configure wait states for the flash */
            FLASH->ACR &= ~(7U << 0);
            FLASH->ACR |= (FLASH_LATENCY_1_WS);     // 1 Wait state
            /* Select HSI as PLL entry clock */
            RCC->PLLCFGR &= ~(1U << 22);
            RCC->PLLCFGR |= (PLL_ENTRY_HSI_CLKSRC << 22);
            /* Configure the correct PLL output speed */
            RCC->PLLCFGR &= ~(3U << 16 | 0x1FF << 6 | 0x3F << 0);
            RCC->PLLCFGR |= (pllm << 0) | (plln << 6) | (pllp << 16);
            /* Enable PLL */
            RCC->CR |= PLL_ON;
            while(!(RCC->CR & (1U << 25)));    // Wait for the PLL ready flag
            /* Select PLL output as SYS entry clock */
            RCC->CFGR &= ~(3U << 0);
            RCC->CFGR |= (SYS_ENTRY_PLL_CLKSRC << 0);
        break;

        case RCC_CLOCK_64MHZ:
            pllm = PLLM_DIVIDE_BY_8; plln = 192U; pllp = PLLP_DIVIDE_BY_6; 

            /* Enable HSI */
            RCC->CR |= HSI_ON;
            while(!(RCC->CR & (1U << 1)));    // Wait for the HSI ready flag
            /* Configure wait states for the flash */
            FLASH->ACR &= ~(7U << 0);
            FLASH->ACR |= (FLASH_LATENCY_2_WS);     // 2 Wait states
            /* Select HSI as PLL entry clock */
            RCC->PLLCFGR &= ~(1U << 22);
            RCC->PLLCFGR |= (PLL_ENTRY_HSI_CLKSRC << 22);
            /* Configure the correct PLL output speed */
            RCC->PLLCFGR &= ~(3U << 16 | 0x1FF << 6 | 0x3F << 0);
            RCC->PLLCFGR |= (pllm << 0) | (plln << 6) | (pllp << 16);
            /* Enable PLL */
            RCC->CR |= PLL_ON;
            while(!(RCC->CR & (1U << 25)));    // Wait for the PLL ready flag
            /* Select PLL output as SYS entry clock */
            RCC->CFGR &= ~(3U << 0);
            RCC->CFGR |= (SYS_ENTRY_PLL_CLKSRC << 0);

        break; 

        case RCC_CLOCK_84MHZ:
            pllm = PLLM_DIVIDE_BY_16; plln = 336U; pllp = PLLP_DIVIDE_BY_4;

            /* Enable HSI */
            RCC->CR |= HSI_ON;
            while(!(RCC->CR & (1U << 1)));    // Wait for the HSI ready flag
            /* Configure wait states for the flash */
            FLASH->ACR &= ~(7U << 0);
            FLASH->ACR |= (FLASH_LATENCY_2_WS);     // 2 Wait states 
            /* Select HSI as PLL entry clock */
            RCC->PLLCFGR &= ~(1U << 22);
            RCC->PLLCFGR |= (PLL_ENTRY_HSI_CLKSRC << 22);
            /* Configure the correct PLL output speed */
            RCC->PLLCFGR &= ~(3U << 16 | 0x1FF << 6 | 0x3F << 0);
            RCC->PLLCFGR |= (pllm << 0) | (plln << 6) | (pllp << 16);
            /* Enable PLL */
            RCC->CR |= PLL_ON;
            while(!(RCC->CR & (1U << 25)));    // Wait for the PLL ready flag
            /* Select PLL output as SYS entry clock */
            RCC->CFGR &= ~(3U << 0);
            RCC->CFGR |= (SYS_ENTRY_PLL_CLKSRC << 0);
        break;

    }
}