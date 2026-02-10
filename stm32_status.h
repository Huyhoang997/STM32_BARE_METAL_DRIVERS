#ifndef STM32_STATUS_H_
#define STM32_STATUS_H_

#include "stm32f401xx.h"

/* Define status enum for the RCC */
typedef enum
{
    RCC_OK,
    RCC_OUT_RANGE_CLOCK
} RCC_Status_Typedef;


/* Define staus enum for the TIMERx*/
typedef enum
{
    TIMER_OK,
    TIMER_ERR,
    TIMER_INVALID_MODE,
    TIMER_INVALID_OC_MODE
} TIMER_Status_Typedef;


/* Define status enum for the GPIOx*/
typedef enum
{
    GPIO_OK,
    GPIO_ERR,
    GPIO_INVALID_PIN,
    GPIO_INVALID_PORT,
    GPIO_INVALID_MODE
} GPIO_Status_Typedef;

/* Define status enum for the ADC */
typedef enum
{
    ADC_OK,
    ADC_ERR,
    ADC_DATA_LOST
} ADC_Status_Typedef;

/* Define status enum for the USARTx */
typedef enum
{
    USART_OK,
    USART_ERR,
    USART_INVALID_DATA,
    USART_INVALID_OVERSAMPLING
} USART_Status_Typedef;

#endif
