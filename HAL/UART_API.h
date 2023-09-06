/*******************************************************************************
 *                                                                             *
 * [FILE NAME]:   UART_API.h                                                   *
 *                                                                             *
 * [AUTHORS]:     Ahmed Saeed, Amr Gafar, Kareem Abd-elrasheed,                *
 *                Mohamed Abosreea, Ahmed Maher, and Mohamed Ramadan           *
 *                                                                             *
 * [Version]:     1.0.0                                                        *
 *                                                                             *
 * [DATE]:        03/09/2023                                                   *
 *                                                                             *
 * [DESCRIPTION]: header file for UART APIs                                    *
 *                                                                             *
 *******************************************************************************/

#ifndef UART_API_H_
#define UART_API_H_

/*******************************************************************************
 *                                 Includes                                    *
 *******************************************************************************/
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/uart.h"
#include "inc/hw_ints.h"
#include "driverlib/interrupt.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
/* UART0 configuration */
#define UART0_MODULE UART0_BASE
#define UART0_PERIPH SYSCTL_PERIPH_UART0
#define UART0_GPIO_PERIPH SYSCTL_PERIPH_GPIOA
#define UART0_GPIO_BASE GPIO_PORTA_BASE
#define UART0_TX_PIN GPIO_PIN_1
#define UART0_RX_PIN GPIO_PIN_0

/* UART1 configuration */
#define UART1_MODULE UART1_BASE
#define UART1_PERIPH SYSCTL_PERIPH_UART1
#define UART1_GPIO_PERIPH SYSCTL_PERIPH_GPIOB
#define UART1_GPIO_BASE GPIO_PORTB_BASE
#define UART1_TX_PIN GPIO_PIN_1
#define UART1_RX_PIN GPIO_PIN_0

#define MAX_UART_SEND_CHARS 200

/*******************************************************************************
 *                      Functions Prototypes                                   *
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
void UARTInit(void);

/*
 * Description :
 * This function turns off the UART module.
 * Parameters: None.
 * Returns: None.
 */
void UARTOff(void);

/*
 * Description :
 * This function puts the UART module in a listening
 * mode, it prepares the UART to listen for incoming
 * data on the dedicated UART pins.
 * Parameters: None.
 * Returns: None.
 */
void UARTListen(void);

/*
 * Description :
 * This function applies bidirectional UART
 * communication, enables the UART module to send a
 * message over UART or listen for incoming UART data.
 * Parameters: None.
 * Returns: None.
 */
void UARTSendandReceive(void);

/*
 * Description :
 * This function sends a text message over UART
 * communication by taking a null-terminated
 * string as input then iterating through each
 * character in the string.
 * Parameters: text-> The null-terminated string to be transmitted over UART.
 * Returns: None.
 */
void UARTprint(const char* text);

#endif /* UART_API_H_ */
