/*******************************************************************************
 *                                                                             *
 * [FILE NAME]:   main.c                                                       *
 *                                                                             *
 * [AUTHORS]:     Ahmed Saeed, Amr Gafar, Kareem Abd-elrasheed,                *
 *                Mohamed Abosreea, Ahmed Maher, and Mohamed Ramadan           *
 *                                                                             *
 * [Version]:     1.0.0                                                        *
 *                                                                             *
 * [DATE]:        03/09/2023                                                   *
 *                                                                             *
 * [DESCRIPTION]: UART Chat application between two boards and two PCs         *
 *                                                                             *
 *******************************************************************************/

/*******************************************************************************
 *                                 Includes                                    *
 *******************************************************************************/
#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "driverlib/systick.h"
#include "HAL/switch.h"
#include "HAL/UART_API.h"

/*******************************************************************************
 *                            Global Variables                                 *
 *******************************************************************************/
int8_t flag_state = 0;
uint8_t flag_interrupt = 1U;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
/* This line wrote to solve that MISRA C warning:
 * (MISRA-C:2004 8.1/R) Functions shall have prototype declarations
 * and the prototype shall be visible at both the function definition and call.
 */
void main(void);

/*******************************************************************************
 *                              Main Function                                  *
 *******************************************************************************/
void main(void)
{
    /* Initialize the UART driver */
    UARTInit();

    /* Initialize the Switch driver */
    SwitchInit();

    /*
     * An array of function pointers representing different states.
     *   - Element 0: Points to the UARTOff function.
     *   - Element 1: Points to the UARTListen function.
     *   - Element 2: Points to the UARTSendAndReceive function.
     */
    void (*states_map[3])(void) = {&UARTOff , &UARTListen , &UARTSendandReceive};

    while(1)
    {
        /* Checks the flag_interrupt condition, and if it is true,
         * calls the function pointed to by the states_map at the index
         * specified by flag_state */
        if (flag_interrupt)
        {
            states_map[flag_state]();
        }
    }
}


