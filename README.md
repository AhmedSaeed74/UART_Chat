# UART Chat Project

Overview

The UART Chat Project is a communication system between two Tiva C TM4C123 microcontroller boards using UART communication. 
This project demonstrates bidirectional communication between the boards and includes features such as switching between off, listen, send, and receive modes.

Features

Off State: The system is initially in an "Off" state, where UART communication is disabled.

Listen State: In this state, one board listens for incoming UART data and displays it on a virtual terminal.

Send and Receive State: In this state, one board sends data to another board, which can then be displayed on a virtual terminal.

Button Control: The project uses button presses to switch between states and initiate actions.

Usage

Power on both Tiva C TM4C123 boards.

Use buttons on the boards to switch between different states:

    Off State: Initial state with no UART communication.
    Listen State: Listen for incoming UART data on one board.
    Send and Receive State: Send and receive data between the boards.
    
Observe the virtual terminal to view incoming and outgoing UART data.

Layered Architecture Overview

The UART Chat Project utilizes a layered architecture to structure and organize its components. 
This architecture is divided into three main layers: MCAL (Microcontroller Abstraction Layer), HAL (Hardware Abstraction Layer), and the Application Layer. 
Each layer serves a distinct purpose and encapsulates related functionalities.

MCAL (Microcontroller Abstraction Layer)

The MCAL represents the lowest layer in the architecture and abstracts the microcontroller-specific hardware details. It encompasses drivers for various hardware modules of the Tiva C TM4C123 microcontroller. In this project, the MCAL includes:

SysTick Driver: This driver manages the SysTick timer, responsible for system timing and precise timing intervals. It provides functions to configure and utilize the SysTick timer for tasks such as button debouncing and state transitions.

System Clock Driver: The System Clock Driver handles the microcontroller's clock settings. It allows for the configuration and management of clock sources and frequencies, ensuring that the system operates at the desired clock rate.

GPIO Driver: The GPIO Driver manages the GPIO (General-Purpose Input/Output) pins on the microcontroller. It provides functions for configuring and controlling pins, allowing for various uses such as button input and UART communication.

HAL (Hardware Abstraction Layer)
The HAL layer resides above the MCAL and offers higher-level abstractions of specific hardware components. It simplifies hardware interactions for the application layer. In this project, the HAL comprises:

Switch Driver: The Switch Driver abstracts the functionality of buttons or switches. It offers functions to initialize buttons and read their states. The switch driver simplifies button handling for the application layer, including debouncing.

UART Driver: The UART Driver abstracts UART communication. It provides functions for initializing and managing UART communication, including sending and receiving data. This driver streamlines UART communication for the application layer.

Application Layer
The Application Layer represents the top layer of the architecture and contains the core logic of the UART Chat Project. It is responsible for managing the project's functionality and state transitions. In this project:

The Application Layer controls the switching between different states (Off State, Listen State, Send and Receive State) based on button presses, specifically when Switch 1 is pressed.

It manages interactions between the HAL and MCAL layers to perform actions like UART communication, state transitions, and button handling.

The Application Layer implements the main loop, where the project's behavior is defined, including handling button presses, UART data transmission, and state transitions.

Please click the link to make sure everything works perfectly and passes all tests without any problems.

https://drive.google.com/file/d/1MW8c-YN99jgOPbYTLcjXkI6rU1Mx2trk/view?usp=sharing

Misra C report :

https://drive.google.com/file/d/14ScFYmaIb8LwFzd877thr9-OgtA2faOx/view?usp=sharing

Contributing

Contributions to this project are welcome. Feel free to submit bug reports, feature requests, or pull requests.
