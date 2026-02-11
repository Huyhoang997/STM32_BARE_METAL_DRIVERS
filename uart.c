#include "stm32f401xx.h"

USART_Status_Typedef USART_Init(USART_RegDef_t *USARTx, USART_Config_t *USART_Config)
{
    /* Check if NULL pointer */
    if(USARTx == NULL || USART_Config == NULL)
    {
        return USART_ERR;
    }
    /* Check if invalid oversampling mode */
    if(USART_Config->OverSamplingMode > USART_OVERSAMPLING_BY_8)
    {
        return USART_INVALID_OVERSAMPLING;
    }

    uint32_t pclk, usartdiv;
    uint8_t mantissa, reminder, fraction;
    /* Enable USARTx peripheral clock */
    UART_ENABLE_CLOCK(USARTx);
    /* Configure the oversampling */
    USARTx->CR1 &= ~(1U << 15);
    USARTx->CR1 |= (USART_Config->OverSamplingMode << 15);
    /* Set the USARTx word length */
    USARTx->CR1 &= ~(1U << 12);
    USARTx->CR1 |= (USART_Config->WordLength << 12);
    /* 1. Configure parity mode */
    /* 1.1 Set default parity control */
    USARTx->CR1 &= ~((1U << 10) | (1U << 9));
    USARTx->CR1 |= USART_Config->ParityType;
    /* 2. Configure stop bit */
    USARTx->CR2 &= ~(3U << 12);
    USARTx->CR2 |= (USART_Config->type << 12);
    /* Configure USARTx transfer mode */
    USARTx->CR1 |= USART_Config->TransferMode;
   
    /* Configure flow control */
    USARTx->CR3 |= (USART_Config->HWFlowControl);
    
    /* Configure baudrate */
    /* OVER8 = 0 (oversampling 16) - OVER8 = 1 (oversampling 8)*/
    /* Baudrate = PCLK / (8 x (2 -OVER8) x USARTDIV) */
    /* USARTDIV = DIV_Mantissa + (DIV_Fraction / 8 × (2 – OVER8)) */
    /* 1.0 Read APBx clock frequency */
    if(USARTx == USART1 || USARTx == USART6)
    {
        pclk = RCC_APB2_GetFreq();
    }
    else 
    {
        pclk = RCC_APB1_GetFreq();
    }
    /* 1.1 Calculate USARTDIV */
    usartdiv = pclk / (8 * (2 - USART_Config->OverSamplingMode) * USART_Config->Baudrate);
    mantissa = usartdiv;
    reminder = pclk % (8 * (2 - USART_Config->OverSamplingMode) * USART_Config->Baudrate);
    fraction = ((reminder) + (USART_Config->Baudrate / 2)) / USART_Config->Baudrate;    /* Round fraction */
    USARTx->BRR &= ~(15U << 0);
    if(USART_Config->OverSamplingMode == USART_OVERSAMPLING_BY_16)
    {
        USARTx->BRR |= (mantissa << 4);
        USARTx->BRR |= (fraction << 0);
    }
    else
    {
        USARTx->BRR |= (mantissa << 4);
        USARTx->BRR |= (fraction << 0);
        USARTx->BRR &= ~(1U << 3);
    }
    /* Enable the USARTx */
    USARTx->CR1 |= (USART_UE_ENABLE << 13);

    return USART_OK;
}

/* USARTx transmits */
USART_Status_Typedef USART_Transmit(USART_RegDef_t *USARTx, uint8_t *transmit_data, uint16_t size)
{
    /* Check if NULL pointer */
    if(USARTx == NULL || transmit_data == NULL)
    {
        return USART_ERR;
    }
    /* Check if invalid data */
    if(size == 0U)
    {
        return USART_INVALID_DATA;
    }

    uint8_t *pdata8bit;
    uint16_t *pdata16bit;
    uint8_t TxBufCounter = size;
    /* Check the wordlength: if 9bit wordlength then use 16 bit data pointer 
    else if 8 bit then use 8bit data pointer */
    if((((USARTx->CR1 >> 12) & 1U) == DATA_8_BIT)  && !((USARTx->CR1 >> 10) & 1U))
    {
        pdata8bit = transmit_data;
        pdata16bit = NULL;
    }
    else 
    {
        pdata16bit = (uint16_t*)transmit_data;
        pdata8bit = NULL;
    }

    /* Loop through all data in the message */
    while(TxBufCounter > 0)     
    {
        if(((USARTx->SR >> 7) & 1U) == USART_TXE_DATA_TRANFERRED)
        {
            if(pdata8bit == NULL)
            {
                USARTx->DR = (uint16_t) (*pdata16bit & 0x01FF);
                /* Move data pointer to the next character */
                pdata16bit++;
            }
            else 
            {
                USARTx->DR = (uint8_t) (*pdata8bit & 0x00FF);
                pdata8bit++;
            }
            TxBufCounter--;
        }

    }

    return USART_OK;
}


USART_Status_Typedef USART_Receive(USART_RegDef_t *USARTx, uint8_t *receive_data, uint16_t size, uint16_t timeout)
{
    /* Check if NULL pointer */
    if(USARTx == NULL || receive_data == NULL)
    {
        return USART_ERR;
    }
    /* Check if invalid data */
    if(size == 0U)
    {
        return USART_INVALID_DATA;
    }

    uint8_t *pdata8bit;
    uint16_t *pdata16bit;
    uint16_t RxBufCount = size;
    uint32_t timecheck = uwTick;
    /* Check the wordlength: if 9bit wordlength then use 16 bit data pointer 
    else if 8 bit then use 8bit data pointer */
    if(((USARTx->CR1 >> 12) & 1U) == DATA_8_BIT && !((USARTx->CR1 >> 10) & 1U)) 
    {
        pdata8bit = receive_data;
        pdata16bit = NULL;
    }
    else 
    {
        pdata16bit =  (uint16_t*)receive_data;
        pdata8bit = NULL;
    }


    
    while (RxBufCount > 0)
    {
        if(((USARTx->SR >> 5) & 1U) == USART_RXNE_DATA_READY)
        {
            /* Configure 9 bit data -> use uint16_t variable to store the data */
            if(pdata8bit == NULL)
            {
                *pdata16bit = (uint16_t )(USARTx->DR & 0x01FF);
                pdata16bit++;
            }
            else 
            {
                /* Configure 8 bit data & parity mode */
                /* 1. Enable 8 bit data & disable parity */
                if((((USARTx->CR1 >> 10U) & 1U) == USART_NONE_PARITY))
                {
                    *pdata8bit = (uint8_t)(USARTx->DR & 0x00FF);
                }
                else /* 2. Enable 8 bit data & enable parity */
                {
                    *pdata8bit = (uint8_t)(USARTx->DR & 0x007F);
                }
                pdata8bit++;
            }
            RxBufCount--;
            timecheck = uwTick;
        }
        if(((uwTick - timecheck) > timeout) || (timeout == 0U))
        {
            return USART_TIMEOUT;
        }
    }

    return USART_OK;
}
