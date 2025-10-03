# Simple Embedded Systems Simulator

This is a **simple embedded systems project** written in C that simulates a small microcontroller with input pins and output LEDs using your terminal. The project demonstrates basic embedded concepts such as pins, ports, input/output mapping, and a main loop with timing.

---

## Features

- 8-pin port simulation with input and output pins.
- Map input pins (buttons) to output pins (LEDs).
- Toggle LED state by pressing keys `1`-`4`.
- Real-time input handling using non-blocking `poll()`.
- Main loop runs at a fixed 50ms interval to simulate embedded timing.
- Terminal display of LED states updated in place.
- Raw mode terminal input for immediate key detection.
- Exit program by pressing `q`.

---

## Pin Mapping

| Key | Input Pin | Output LED |
|-----|-----------|------------|
| 1   | 0         | 4          |
| 2   | 1         | 5          |
| 3   | 2         | 6          |
| 4   | 3         | 7          |

- Pressing a key toggles the state of the corresponding input pin.
- The mapped output pin (LED) mirrors the input pin state.

---

## How It Works

1. **Port and Pin Structs**
   - Each `Pin` has a `mode` (INPUT or OUTPUT) and a `state` (LOW or HIGH).
   - The `Port` contains an array of 8 pins and a mapping of input pins to output pins.

2. **Terminal Setup**
   - Terminal is switched to **raw mode** so key presses are detected immediately.
   - Uses ANSI escape codes to attempt alternate screen mode and cursor hiding (may not work in all terminals).

3. **Non-blocking Input**
   - Uses `poll()` to check for key presses without stopping the program loop.
   - Reads one key at a time and maps it to the corresponding input pin.

4. **Main Loop**
   - Continuously checks for key input.
   - Updates input pins and propagates state changes to mapped output pins.
   - Prints LED states in a single line using `%-3s` formatting for alignment.
   - Sleeps 50ms per iteration to simulate a timed loop.

---

## How to Compile and Run

### Compile and Run:

```bash
gcc -o simulated_microcontroller mc.c
./simulated_microcontroller
```
OR use makefile
```bash
make
./vmc
```

---

## Press buttons
  - Press 1 - 4 on keyboard to toggle LEDs
  - Press q to quit

---

## Platform Compatibility

- This project is designed to run on **Linux/Unix terminals**.
- It has been tested on Ubuntu and works in native terminal or VS Code’s integrated terminal.
- Windows is not supported without modifying input handling and terminal control code.

---

## Notes
  - Cursor hiding may not work in all terminals (tested in VS Code terminal and Ubuntu Terminal).
  - The program uses a fixed 8-pin port, which can be extended if desired.
  - LED toggling is immediate on key press (toggle mode); holding a key repeatedly toggles in the loop.
