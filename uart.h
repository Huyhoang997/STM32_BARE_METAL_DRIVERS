#ifndef UART_H_
#define UART_H_

#include "stm32f401xx.h"

/* USART data type enum */
typedef enum 
{
    DATA_8_BIT = 0U,
    DATA_9_BIT
} USART_WordLength_t;

/* USART stop-bit type enum */
typedef enum 
{
    STOP_BIT_1 = 0U,
    STOP_BIT_0_HALF = 1U,
    STOP_BIT_2 = 10U,
    STOP_BIT_1_HALF = 11U
} USART_StopBit_t;

/* USARTx configure structute */
typedef struct 
{
    uint8_t OverSamplingMode;
    USART_WordLength_t WordLength;
    uint8_t ParityType;
    USART_StopBit_t type;
    uint32_t Baudrate;
    uint8_t HWFlowControl;
    uint8_t TransferMode;
} USART_Config_t;

/* Transmit data register */
#define USART_TXE_DATA_NOT_TRANSFERRED  0U
#define USART_TXE_DATA_TRANFERRED  		1U
/* USART transfer mode */
#define USART_TX                        (1U << 3)
#define USART_RX                        (1U << 2)
#define USART_TX_RX                     (USART_TX | USART_RX)

/* Define USART parity type selection */
#define USART_NONE_PARITY               (0U << 10)
#define USART_EVEN_PARITY               (1U << 10) | (0U << 9)
#define USART_ODD_PARITY                (1U << 10) | (1U << 9)

/* Define USART oversampling value */
#define USART_OVERSAMPLING_BY_8         1U
#define USART_OVERSAMPLING_BY_16        0U

/* Define macro for UE(USART start bit) */
#define USART_UE_DISABLE                0U
#define USART_UE_ENABLE                 1U

/* Define USART flow control mode */
#define USART_FLOWCTRL_CTS_EN           (1U << 9)
#define USART_FLOWCTRL_RTS_EN           (1U << 8)
#define USART_FLOWCTRL_RTS_CTS_EN       (USART_FLOWCTRL_CTS_EN | USART_FLOWCTRL_RTS_EN)



 /* ====================================================
 * User API
 * configuration functions for application code.
 * ==================================================== */

 /* USART Init function */
USART_Status_Typedef USART_Init(USART_RegDef_t *USARTx, USART_Config_t *USART_Config);
USART_Status_Typedef USART_Transmit(USART_RegDef_t *USARTx, uint8_t *transmit_data, uint16_t size);
USART_Status_Typedef USART_Receive(USART_RegDef_t *USARTx, uint8_t *receive_data, uint16_t size, uint32_t timeout);

#endif
