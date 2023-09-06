/*******************************************************************************
 *                                                                             *
 * [FILE NAME]:   switch.c                                                     *
 *                                                                             *
 * [AUTHORS]:     Ahmed Saeed, Amr Gafar, Kareem Abd-elrasheed,                *
 *                Mohamed Abosreea, Ahmed Maher, and Mohamed Ramadan           *
 *                                                                             *
 * [Version]:     1.0.0                                                        *
 *                                                                             *
 * [DATE]:        03/09/2023                                                   *
 *                                                                             *
 * [DESCRIPTION]: source file for switch driver                                *
 *                                                                             *
 *******************************************************************************/

/*******************************************************************************
 *                                 Includes                                    *
 *******************************************************************************/
#include "HAL/switch.h"

buttonState_t Button_lastState = RELEASED;

/*
 * Description: An instance of the button_t structure representing a specific button.
 *              - btnPin: Configured with GPIO_PIN_0, indicating the button's GPIO pin.
 *              - btnPort: Configured with GPIO_PORTF_BASE, indicating the button's GPIO port.
 *              - btn_conn: Configured with PULL_UP, indicating a pull-up resistor connection for the button.
 *              - btn_state: Configured with RELEASED, indicating that the button is in the released state initially.
 */
button_t sw1 = {
                .btnPin  = (uint8_t)GPIO_PIN_0 ,
                .btnPort = (uint32_t)GPIO_PORTF_BASE ,
                .btn_conn = PULL_UP ,
                .btn_state = RELEASED
};

/*******************************************************************************
 *                      Functions Definitions                                  *
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
void SysticISR(void)
{
    SysTickPeriodSet(3U*160000U - 1U);
    buttonState_t Button_currentState = RELEASED;
    buttonGetState(&sw1, &Button_currentState);

   /* when both current and last are equal do nothing */
   if((Button_currentState == PRESSED) && (Button_lastState == RELEASED))
    {
        /* we are in pre-pressed state */
        /* make the last stated = pressed */
        flag_state++;
        flag_state %=3;
        Button_lastState = Button_currentState;
        flag_interrupt = 1U;

    }

    /* Button_currentState == RELEASED && Button_lastState == PRESSED */
    else
    {
        /*then we are in the pre-release state,
          make the last stated = pressed */
        Button_lastState = Button_currentState;
    }
}

/*
 * Description :
 * This function initializes the SysTick timer for periodic interrupts,
 * and configures the SysTick timer, sets the interrupt handler to SysticISR,
 * and enables the timer to generate interrupts at a specified interval.
 * Parameters: None.
 * Returns: None.
 */
void SysticInit(void)
{
    SysTickDisable();
    SysTickIntDisable();
    SysTickIntRegister(&SysticISR);
    SysTickPeriodSet(5U*160000U - 1U);
    SysTickIntEnable();
    SysTickEnable();
}

/*
 * Description :
 * This function initializes the switch, and enables the GPIO
 * peripheral for Port F, initializes the SysTick timer for
 * button state monitoring, and initializes the button (SW1)
 * using the buttonInit function.
 * Parameters: None.
 * Returns: None.
 */
void SwitchInit(void)
{
    /* Enable the GPIO peripheral for Port F */
    SysCtlPeripheralEnable((uint32_t)SYSCTL_PERIPH_GPIOF);

    /* Initialize the SysTick timer for button state monitoring */
    SysticInit();

    /* Initialize the button (SW1) using the buttonInit function */
    buttonInit(&sw1);
}

/*
 * Description :
 * This function initializes a button's GPIO pin and configuration,
 * takes a pointer to a button_t structure and configures the associated
 * GPIO pin as an input with a pull-up resistor. It ensures that
 * the button is ready for use.
 * Parameters: btn -> A pointer to the button_t structure representing
 * the button to be initialized.
 * Returns: None.
 */
void buttonInit(button_t *btn)
{
    /* Check if the button pointer is NULL */
    if(NULL == btn)
    {
        /* Exit the function if NULL */
        return;
    }

    /* Unlock the GPIO pin, set it as an input, and configure with pull-up resistor */
    else
    {
        GPIOUnlockPin(btn->btnPort,  btn->btnPin);
        GPIOPinTypeGPIOInput(btn->btnPort , btn->btnPin);
        GPIOPadConfigSet(btn->btnPort , btn->btnPin , (uint32_t)GPIO_STRENGTH_2MA, (uint32_t)GPIO_PIN_TYPE_STD_WPU);
    }
}

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
void buttonGetState(button_t *btn, buttonState_t *btn_state1)
{
    /* Check if either the button pointer or the state pointer is NULL */
    if((NULL == btn) || (NULL == btn_state1))
    {
        /* Exit the function if either pointer is NULL */
        return;
    }

    else
    {
        uint32_t state ;
        state = GPIOPinRead(btn->btnPort, btn->btnPin);

        /* Determine the button state based on the connection type (PULL_UP or PULL_DOWN) */
        switch(btn-> btn_conn)
        {
        case PULL_UP :
            switch(state & btn->btnPin)
            {
            case LOW :
                *btn_state1 = PRESSED ;
                break;
            case HIGH :
                *btn_state1 = RELEASED ;
                break;
            default :
                break;
            }
            break;
            case PULL_DOWN :
                switch(state & btn->btnPin)
                {
                case LOW :
                    *btn_state1 = RELEASED ;
                    break;
                case HIGH :
                    *btn_state1 = PRESSED ;
                    break;
                default :
                    break;
                }
                break;
                default:
                    break;
        }
    }
}



