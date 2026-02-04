/*
 * gpio.h
 *
 *  Created on: Jan 29, 2026
 *      Author: ACER
 */
#ifndef GPIO_H_
#define GPIO_H_

#include "stm32f401xx.h"

/* GPIO configure structute */
typedef struct
{
	uint8_t GPIO_MODE;
	uint8_t GPIO_PIN;
	uint8_t GPIO_OUT_TYPE;
	uint8_t GPIO_OUT_SPEED;
	uint8_t GPIO_PUPD;
	uint8_t GPIO_ALT_MODE;
	uint8_t GPIO_IT_TRIGGER_MODE;
} GPIO_Config_t;

/* GPIO pin state */
typedef enum
{
	GPIO_PIN_LOW = 0U,
	GPIO_PIN_HIGH
} GPIO_PinState_Typedef;

/* GPIO Pin Number */
#define GPIO_PIN_0						0U
#define GPIO_PIN_1						1U
#define GPIO_PIN_2						2U
#define GPIO_PIN_3						3U
#define GPIO_PIN_4						4U
#define GPIO_PIN_5						5U
#define GPIO_PIN_6						6U
#define GPIO_PIN_7						7U
#define GPIO_PIN_8						8U
#define GPIO_PIN_9						9U
#define GPIO_PIN_10						10U
#define GPIO_PIN_11						11U
#define GPIO_PIN_12						12U
#define GPIO_PIN_13						13U
#define GPIO_PIN_14						14U
#define GPIO_PIN_15						15U

/* Define GPIO mode for MODER register */
#define GPIO_MODE_INPUT					0U
#define GPIO_MODE_OUTPUT				1U
#define GPIO_MODE_ALT					10U
#define GPIO_MODE_ANALOG				11U

/* Define GPIO output type for OTYPER register */
#define GPIO_OUTPUT_PUSH_PULL			0U
#define GPIO_OUTPUT_OPEN_DRAIN			1U

/* Define GPIO output speed for OSPEEDR register */
#define GPIO_LOW_SPEED					0U
#define GPIO_MEDIUM_SPEED				1U
#define GPIO_HIGH_SPEED					10U
#define GPIO_VERY_HIGH_SPEED			11U

/* Define GPIO pull-up/pull-down for PUPDR register */
#define GPIO_NO_PUPD					0U
#define GPIO_PULL_UP					1U
#define GPIO_PULL_DOWN					10U

/* Define GPIO alternate function */
#define GPIO_ALT_0						0U
#define GPIO_ALT_1						1U
#define GPIO_ALT_2						2U
#define GPIO_ALT_3						3U
#define GPIO_ALT_4						4U
#define GPIO_ALT_5						5U
#define GPIO_ALT_6						6U
#define GPIO_ALT_7						7U
#define GPIO_ALT_8						8U
#define GPIO_ALT_9						9U
#define GPIO_ALT_10						10U
#define GPIO_ALT_11						11U
#define GPIO_ALT_12						12U
#define GPIO_ALT_13						13U
#define GPIO_ALT_14						14U
#define GPIO_ALT_15						15U

/* Define EXTIO numbers */
#define EXTI_IRQ_0						6U
#define EXTI_IRQ_1						7U
#define EXTI_IRQ_2						8U
#define EXTI_IRQ_3						9U
#define EXTI_IRQ_4						10U
#define EXTI_IRQ_5_9					23U
#define EXTI_IRQ_10_15					40U

/* Define EXTI falling raising mode */
#define GPIO_IT_FALLING					0U
#define GPIO_IT_RAISING					1U
#define GPIO_IT_FALLING_RAISING			2U

/* Mapping EXTI number to IRQ number */
#define EXTI_TO_IRQ(GPIO_Pin) \
    ((GPIO_Pin == GPIO_PIN_0)  ? EXTI_IRQ_0 : \
     (GPIO_Pin == GPIO_PIN_1)  ? EXTI_IRQ_1 : \
     (GPIO_Pin == GPIO_PIN_2)  ? EXTI_IRQ_2 : \
     (GPIO_Pin == GPIO_PIN_3)  ? EXTI_IRQ_3 : \
     (GPIO_Pin == GPIO_PIN_4)  ? EXTI_IRQ_4 : \
     ((GPIO_Pin >= GPIO_PIN_5)  && (GPIO_Pin <= GPIO_PIN_9))  ? EXTI_IRQ_5_9 : \
     ((GPIO_Pin >= GPIO_PIN_10) && (GPIO_Pin <= GPIO_PIN_15)) ? EXTI_IRQ_10_15 : 0)


 /* ====================================================
 * User API
 * configuration functions for application code.
 * ==================================================== */

/* Init GPIO port */	 
void GPIO_Init_Mode(GPIO_RegDef_t *GPIOx, GPIO_Config_t *GPIO_Config);

/* De-Init the GPIO port */
void GPIO_DeInit(GPIO_RegDef_t *GPIOx);

/* Set the GPIO pin to High */
void GPIO_PinOutSet(GPIO_RegDef_t *GPIOx, uint8_t GPIO_PIN);

/* Set the GPIO pin to Low */
void GPIO_PinOutClear(GPIO_RegDef_t *GPIOx, uint8_t GPIO_PIN);

/* Toogle value of the GPIO pin */
GPIO_PinState_Typedef GPIO_PinInRead(GPIO_RegDef_t *GPIOx, uint8_t GPIO_PIN );

/* Read the value of the GPIO */
void GPIO_PinOutToggle(GPIO_RegDef_t *GPIOx, uint8_t GPIO_PIN);

/* Init GPIO intterupt */
void GPIO_Init_IT(GPIO_RegDef_t *GPIOx, GPIO_Config_t *GPIO_Config, uint8_t Priority);


#endif /* GPIO_H_ */
