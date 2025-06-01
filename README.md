# StateMachineController

A Finite State Machine (FSM) system built with Arduino, designed to simulate an electronic lock using a 4x4 keypad, LCD display, buzzer, and modular components.

---

## University Project

This project was developed as part of the **Computer Architecture** course at university. It demonstrates embedded systems concepts such as:

- Finite State Machines
- Sensor and actuator integration
- Modular code organization
- User interfaces in embedded applications

---

## Features

- **Keypad Input**: Accepts user input via a 4x4 matrix keypad.
- **LCD Display**: Provides visual feedback for input and state changes.
- **Buzzer Feedback**: Audio confirmation for access granted or denied.
- **FSM Logic**: Implements a simple finite state machine for user authentication.
- **Modular Design**: Clean separation of logic across multiple `.ino` files.

---

## Project Structure

```bash
StateMachineController/
│
├── logic.ino        # Entry point: contains setup() and loop()
├── LCD.ino            # LCD initialization and message functions
├── Keypad.ino         # Keypad configuration
├── Buzzer.ino         # Buzzer setup and control
├── Logic.ino          # FSM logic: password handling and state transitions
```
## How to Run
The project is designed to be simulated in Wokwi:

Visit [https://wokwi.com](https://wokwi.com)

Click "New Project"

Replace the default code with the contents of this repository.

Ensure all .ino files are present.

Click the green "Start Simulation" button to test the system.

## Dependencies
LiquidCrystal.h

Keypad.h

These libraries are pre-installed in Wokwi. No additional installation is required.

