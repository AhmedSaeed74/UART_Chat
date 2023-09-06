/*******************************************************************************
 *                                                                             *
 * [FILE NAME]:   UART_API.c                                                   *
 *                                                                             *
 * [AUTHORS]:     Ahmed Saeed, Amr Gafar, Kareem Abd-elrasheed,                *
 *                Mohamed Abosreea, Ahmed Maher, and Mohamed Ramadan           *
 *                                                                             *
 * [Version]:     1.0.0                                                        *
 *                                                                             *
 * [DATE]:        03/09/2023                                                   *
 *                                                                             *
 * [DESCRIPTION]: source file for UART APIs                                    *
 *                                                                             *
 *******************************************************************************/

/*******************************************************************************
 *                                 Includes                                    *
 *******************************************************************************/
#include "HAL/UART_API.h"
#include "HAL/switch.h"
#include "string.h"

/*******************************************************************************
 *                      Functions definitions                                  *
 *******************************************************************************/
/*
 * Description :
 * This function initializes the UART module, sets up
 * the necessary GPIO pins for UART communication, and
 * establishes communication parameters including the baud rate,
 * data frame format, and parity settings.
 * Parameters: None.
 * Returns: None.
 */
void UARTInit(void)
{
    /* Enable UART0 peripheral */
    SysCtlPeripheralEnable((uint32_t)UART0_PERIPH);

    /* Enable GPIOA peripheral (UART0 pins) */
    SysCtlPeripheralEnable((uint32_t)UART0_GPIO_PERIPH);

    /* Configure UART0 pins (PA0 as UART0 Rx, PA1 as UART0 Tx) */
    GPIOPinConfigure((uint32_t)GPIO_PA0_U0RX);
    GPIOPinConfigure((uint32_t)GPIO_PA1_U0TX);
    GPIOPinTypeUART((uint32_t)UART0_GPIO_BASE, (uint8_t)UART0_RX_PIN | (uint8_t)UART0_TX_PIN);

    /* Initialize UART0 module */
    UARTConfigSetExpClk((uint32_t)UART0_MODULE, (uint32_t)SysCtlClockGet(), (uint32_t)115200, ((uint32_t)UART_CONFIG_WLEN_8 | (uint32_t)UART_CONFIG_STOP_ONE | (uint32_t)UART_CONFIG_PAR_NONE));

    /* Enable UART0 module */
    UARTEnable((uint32_t)UART0_MODULE);

    /* Disable UART0 FIFO */
    UARTFIFODisable((uint32_t)UART0_MODULE);

    /* Enable UART1 peripheral */
    SysCtlPeripheralEnable((uint32_t)UART1_PERIPH);

    /* Enable GPIOB peripheral (UART1 pins) */
    SysCtlPeripheralEnable((uint32_t)SYSCTL_PERIPH_GPIOB);

    /* Configure UART1 pins (PB0 as UART0 Rx, PB1 as UART0 Tx) */
    GPIOPinConfigure((uint32_t)GPIO_PB0_U1RX);
    GPIOPinConfigure((uint32_t)GPIO_PB1_U1TX);
    GPIOPinTypeUART((uint32_t)UART1_GPIO_BASE, (uint8_t)UART1_RX_PIN | (uint8_t)UART1_TX_PIN);

    /* Initialize UART1 module */
    UARTConfigSetExpClk((uint32_t)UART1_MODULE, (uint32_t)SysCtlClockGet(), (uint32_t)115200, ((uint32_t)UART_CONFIG_WLEN_8 | (uint32_t)UART_CONFIG_STOP_ONE | (uint32_t)UART_CONFIG_PAR_NONE));

    /* Enable UART1 module */
    UARTEnable((uint32_t)UART1_MODULE);

    /* Disable UART1 FIFO */
    UARTFIFODisable((uint32_t)UART1_MODULE);
}


/*
 * Description :
 * This function turns off the UART module.
 * Parameters: None.
 * Returns: None.
 */
void UARTOff(void)
{
    /* Disable UART1 module */
    UARTDisable((uint32_t)UART1_MODULE);

    flag_interrupt = 0U;
}

/*
 * Description :
 * This function puts the UART module in a listening
 * mode, it prepares the UART to listen for incoming
 * data on the dedicated UART pins.
 * Parameters: None.
 * Returns: None.
 */
void UARTListen(void)
{
    /* enable UART1 module */
    UARTEnable((uint32_t)UART1_MODULE);

    flag_interrupt = 0U;
    uint8_t i = 0U;

    while(flag_interrupt == 0U)
    {
        /* Check if data is available to read */
        if (UARTCharsAvail((uint32_t)UART1_MODULE))
        {
            /* Read and process incoming data */
            int32_t receivedChar = UARTCharGet((uint32_t)UART1_MODULE);

            /* Check if the received character is either '#' or Enter (ASCII 13).
             * If either condition is met, it breaks out of the loop then
             * prints the received data */
            if((receivedChar == '#') || (receivedChar == 13U))
            {
                break;
            }

            /* This condition is used to print the below message only once */
            if(i == 0U)
            {
                UARTprint("Message Received : ");
                i = 1U;
            }

            /* Send the received message on UART1 to UART0 to be displayed over the terminal */
            UARTCharPut((uint32_t)UART0_MODULE, (uint8_t)receivedChar);
        }
    }

    /* New line */
    UARTprint("\n\r");

    flag_interrupt = 1U;
}

/*
 * Description :
 * This function applies bidirectional UART
 * communication, enables the UART module to send a
 * message over UART or listen for incoming UART data.
 * Parameters: None.
 * Returns: None.
 */
void UARTSendandReceive(void)
{
    uint8_t m = 0U;
    uint8_t j;
    uint8_t data[300];
    flag_interrupt = 0U;
    uint8_t receive_flag = 1U;

    while(flag_interrupt == 0U)
    {
        /* Check if data is available to read */
        if (UARTCharsAvail((uint32_t)UART0_MODULE))
        {
            /* Read and process incoming data */
            int32_t receivedChar = UARTCharGet((uint32_t)UART0_MODULE);

            /* Store the data to be sent in its array */
            data[m] = receivedChar;

            /* Increment the counter */
            m++;

            /* Check if the received character is either '#' or Enter (ASCII 13).
             * If either condition is met, it breaks out of the loop then
             * prints the received data */
            if((receivedChar == '#') || (receivedChar == 13U))
            {
                break;
            }
        }

        /* Check if data is available to read */
        else if (UARTCharsAvail((uint32_t)UART1_MODULE))
        {
            /* Read and process incoming data */
            uint8_t receivedChar = UARTCharGet((uint32_t)UART1_MODULE);

            /* Check if the received character is either '#' or Enter (ASCII 13).
             * If either condition is met, it breaks out of the loop then
             * prints the received data */
            if((receivedChar == '#') || (receivedChar == 13U))
            {
                break;
            }

            /* This condition is used to print the below message only once */
            if(receive_flag)
            {
                UARTprint("Messege Received : ");
                receive_flag = 0U;
            }

            /* Send the received message on UART1 to UART0 to be displayed over the terminal */
            UARTCharPut((uint32_t)UART0_MODULE, receivedChar);
        }

        else
        {

        }
    }

    /* Verify whether the message size exceeds the permitted limit */
    if ((m < (uint32_t)MAX_UART_SEND_CHARS) && (m != 0U))
    {
        UARTprint("Message Sent : ");

        for(j = 0U; j < m; j++)
        {
            /* Send the message character by charcater to UART0
             * to be displayed over the terminal and to UART1 to be sent
             * to the other board */
            UARTCharPut((uint32_t)UART0_MODULE, data[j]);
            UARTCharPut((uint32_t)UART1_MODULE, data[j]);
        }
    }

    else
    {

    }

    flag_interrupt = 1U;
    receive_flag = 1U;

    /* New line */
    UARTprint("\n\r");

}

/*
 * Description :
 * This function sends a text message over UART
 * communication by taking a null-terminated
 * string as input then iterating through each
 * character in the string.
 * Parameters: text-> The null-terminated string to be transmitted over UART.
 * Returns: None.
 */
void UARTprint(const char* text)
{
    uint16_t k;

    for(k = 0U ; k < strlen(text) ; k++)
    {
        /* Send the message character by character till
         * reaching the null terminator */
        UARTCharPut((uint32_t)UART0_MODULE, (uint8_t)(text[k]));
    }

}
