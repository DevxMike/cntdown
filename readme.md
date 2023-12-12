Overview

This embedded system project, written in C++, implements a timer application with additional functionalities. The system is designed to manage time, allowing users to set and display minutes and seconds, start and stop the timer, and configure various settings.
Table of Contents

    Introduction
    Components
    File Structure
    Dependencies
    How to Build
    How to Run
    Functionality

Introduction

The timer application is intended for embedded systems and uses a combination of buttons, displays, and timers to provide a user-friendly interface. It includes features such as setting and displaying minutes and seconds, counting down, and supporting user interactions through physical buttons.
Components

    Animation Manager (animation.h, animation.cpp):
        Manages the display of animations during system initialization.

    Button Module (button.h):
        Implements classes for handling push buttons and hold push buttons.
        Manages button states, debouncing, and callback functions.

    Digital Output Module (digital_output.h):
        Provides a class for controlling digital outputs.

    Display Manager (display.h, display.cpp):
        Manages the display using SPI communication and updates content.
        Defines hex codes for display segments.

    System Manager (system.h, system.cpp):
        Manages the overall system state, including reset, counting, halting, and setting states.
        Handles callback functions for system events.

    Timer Manager (timer.h, timer.cpp):
        Manages time-related functionalities, including time counting, alarm events, and settings.

File Structure

    APP/
        animation.h, animation.cpp
        button.h
        digital_output.h
        display.h, display.cpp
        system.h, system.cpp
        timer.h, timer.cpp

Dependencies

    STM32 HAL Library: This project relies on the STM32 HAL (Hardware Abstraction Layer) library for interfacing with the microcontroller's hardware.

How to Build

To build the project, follow these steps:

    Install the STM32CubeIDE or your preferred STM32 development environment. 

How to Run

    Connect the STM32 microcontroller to your development environment.

    Upload the compiled code to the microcontroller.

    Power on the embedded system.

    Interact with the physical buttons to set the timer and control its operation.

Functionality

The main functionalities of the embedded system include:

    Timer Counting:
        The system can count down minutes and seconds.

    Setting Timer:
        Users can set the desired minutes and seconds using dedicated buttons.

    User Interaction:
        Physical buttons allow users to start/stop the timer, reset it, and navigate through settings.
