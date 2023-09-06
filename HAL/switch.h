/*******************************************************************************
 *                                                                             *
 * [FILE NAME]:   switch.h                                                     *
 *                                                                             *
 * [AUTHORS]:     Ahmed Saeed, Amr Gafar, Kareem Abd-elrasheed,                *
 *                Mohamed Abosreea, Ahmed Maher, and Mohamed Ramadan           *
 *                                                                             *
 * [Version]:     1.0.0                                                        *
 *                                                                             *
 * [DATE]:        03/09/2023                                                   *
 *                                                                             *
 * [DESCRIPTION]: header file for switch driver                                *
 *                                                                             *
 *******************************************************************************/

#ifndef BUTTON_H
#define BUTTON_H

/*******************************************************************************
 *                                 Includes                                    *
 *******************************************************************************/
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/timer.h"
#include "driverlib/systick.h"
#include "HAL/UART_API.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define HIGH 1U
#define LOW  0U

/*******************************************************************************
 *                                  Externs                                    *
 *******************************************************************************/
extern int8_t flag_state;
extern uint8_t flag_interrupt;

/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/
/*
 * Description: Enumeration representing button connection types.
 *              - PULL_DOWN : Indicates a pull-down resistor connection.
 *              - PULL_UP   : Indicates a pull-up resistor connection.
 */
typedef enum
{
    PULL_DOWN = 0U,
    PULL_UP = 1U
} buttonConnection_t;

/*
 * Description: Enumeration representing button states.
 *              - RELEASED : Indicates that the button is in the released state.
 *              - PRESSED  : Indicates that the button is in the pressed state.
 */
typedef enum
{
    RELEASED = 0U,
    PRESSED  = 1U
} buttonState_t;

/*
 * Description: Structure representing a button with its properties.
 *              - btnPort   : The GPIO port to which the button is connected.
 *              - btnPin    : The specific GPIO pin used for the button.
 *              - btn_conn  : The type of button connection (PULL_DOWN or PULL_UP).
 *              - btn_state : The current state of the button (RELEASED or PRESSED).
 */
typedef struct
{
    uint32_t btnPort;
    uint8_t  btnPin;
    buttonConnection_t btn_conn;
    buttonState_t btn_state;
} button_t;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
/*
 * Description :
 * Interrupt Service Routine for the SysTick timer.
 * This handler is responsible for monitoring the state of
 * a button (SW1) and handling state transitions. When the
 * button is pressed, it increments a flag_state variable, which
 * is used to select a specific function from a states_map array.
 * The handler also sets a flag_interrupt to indicate a state change.
 * Parameters: None.
 * Returns: None.
 */
void SysticISR(void);

/*
 * Description :
 * This function initializes the SysTick timer for periodic interrupts,
 * and configures the SysTick timer, sets the interrupt handler to SysticISR,
 * and enables the timer to generate interrupts at a specified interval.
 * Parameters: None.
 * Returns: None.
 */
void SysticInit(void);

/*
 * Description :
 * This function initializes the switch, and enables the GPIO
 * peripheral for Port F, initializes the SysTick timer for
 * button state monitoring, and initializes the button (SW1)
 * using the buttonInit function.
 * Parameters: None.
 * Returns: None.
 */
void SwitchInit(void);

/*
 * Description :
 * This function initializes a button's GPIO pin and configuration,
 * takes a pointer to a button_t structure and configures the associated
 * GPIO pin as an input with a pull-up resistor. It ensures that
 * the button is ready for use.
 * Parameters: btn -> A pointer to the button_t structure representing
 * the button to be initialized..
 * Returns: None.
 */
void buttonInit(button_t *btn);

/*
 * Description :
 * This function Retrieves the state of a button and updates
 * the provided btn_state pointer, checks if either the button pointer
 * (btn) or the state pointer (btn_state) is NULL. If either is NULL,
 * the function returns without performing any further actions.
 * If both pointers are valid, it reads the state of the button's
 * GPIO pin and applies logic according to the button connection
 * type (PULL_UP or PULL_DOWN) to determine the button state (PRESSED or RELEASED).
 * Parameters: btn -> A pointer to the button_t structure representing the button to be queried.
 *             btn_state -> A pointer to the variable where the button state will be stored.
 * Returns: None.
 */

void buttonGetState(button_t *btn , buttonState_t *btn_state1);

#endif  /* BUTTON_H */
