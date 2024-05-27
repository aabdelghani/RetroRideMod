# RetroRideMod

## Overview

Welcome to RetroRideMod! This repository is dedicated to transforming classic vehicles by integrating modern control systems for electric windows and lights. By retrofitting old cars with new technology, RetroRideMod bridges the gap between vintage charm and contemporary functionality.

## Milestone 1: Vehicle Electric Windows Controller

### Objective

Develop and implement a control system for vehicle electric windows that allows each window to be operated independently via momentary push buttons, incorporating essential safety features.

### System Description

- **Inputs:** Uses Normally Open (NO) momentary push buttons.
- **Operations:** Each window is controlled independently by its specific inputs.
- **Safety Features:** Includes automatic shutoff and controls to prevent simultaneous contradictory commands.

### Detailed Behavior for Window 1

- **IN1 = ON, IN2 = OFF:** Activates Relay #1, causing the window motor to turn clockwise. This is subject to an 8-second automatic cutoff as a safety feature.
- **IN1 = OFF, IN2 = ON:** Activates Relay #2, causing the window motor to turn counterclockwise, also with an 8-second cutoff.
- **IN1 = ON, IN2 = ON:** Safety feature—both relays are OFF to prevent damage.
- **IN1 = OFF, IN2 = OFF:** Window remains stationary as both relays are OFF.

### Implementation Steps

1. **Hardware Setup:**
   - Connect push buttons to the Pro mini PLC's input terminals.
   - Connect relay modules to the output terminals according to the schematic provided.

2. **Programming:**
   - Implement control logic within the PLC to handle input signals and activate relays accordingly.
   - Ensure the system respects the safety timeout and input delay rules.

3. **Testing:**
   - Independently test each window's functionality to ensure compliance with the design specifications.
   - Verify the safety cutoff and delay features function as intended.

### Safety Mechanisms

- **Motor Timeout:** Each motor is limited to an 8-second run time to prevent overheating or accidental damage.
- **Input Delay:** Requires a minimum of 1 second delay between releasing and pressing the button again to change the direction or restart the motor.

### Documentation and Review

- **Documentation:** Update schematics and system documentation based on the implementation and testing results.
- **Review:** Schedule a review session with the project team to evaluate the system’s functionality and safety features. Adjust based on feedback and conduct additional testing as necessary.


## Features

### Electric Windows Controller

- **Independent Operation:** Each window functions independently for enhanced control.
- **Safety First:** Automatic shutoff after 8 seconds and conditions to ensure safety and prevent accidental damage.
- **Momentary Switch Control:** Utilizes push buttons to manage window operations effectively.

### Vehicle Lights Controller

- **Adaptive Control:** Tailored light control based on the vehicle’s operational state.
- **Modern Signals:** Incorporates modern vehicle signal functionalities including hazard and turn signals that adapt based on ignition status.
- **Dynamic Headlights:** Features high beam flashing and low/high beam switching to enhance driving safety and visibility.

## Hardware Requirements

- **Momentary Switches:** For user inputs.
- **Relays:** To control the motors and lights powerfully and safely.
- **Microcontrollers:** To implement the logic and control sequences.
- **LED Display:** To provide real-time status and feedback.

## Setup

1. Connect all hardware as per the diagrams in the `schematics` folder.
2. Install necessary libraries from `requirements.txt`.
3. Upload the provided code to your microcontroller to bring the modern functionalities to your classic car.

## Usage

Operate your upgraded vehicle systems via intuitive controls designed for safety and reliability. The system ensures all modern safety protocols are met, keeping the vintage aesthetics intact.

## Contributing

We encourage contributions to make RetroRideMod even better. If you have improvements or new features, please fork this repository, make your changes, and submit a pull request.

## Safety

Built with robust safety features to prevent overuse and misuse:
- Timed shutoffs for all window controls.
- Delayed switching to protect system integrity and ensure operational safety.

## License

This project is available under the MIT License. For more details, see the [LICENSE.md](LICENSE.md) file.

