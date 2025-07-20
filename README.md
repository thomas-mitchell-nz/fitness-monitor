## Fitness Monitor

A personal activity tracker implemented on a TIVA-Orbit board. Tracks steps, estimates distance, and displays goals.

**Features:**
- Custom interrupt-driven kernel for multitasking
- Concurrent task handling for background and user-facing features
- Onboard OLED display for real-time goal tracking

**Project Demo:**  
[Watch the demo video](https://drive.google.com/file/d/1ADSg9c9PQlCyL9jafoBX7RClkiDyDpmP/view?usp=sharing)

---

### Development Environment

Created using Code Composer Studio (CCS). Refer to the included **CCS Tutorial** document for workspace setup instructions.

---

### Functional Specification

1. Estimates the number of steps based on accelerometer data from the Orbit board.
2. Calculates the distance traveled.
3. Allows users to set a step goal and displays progress.
4. Notifies users upon goal completion.
5. RESET button restarts the program and clears stored step, distance, and goal values.
6. User interface includes display, buttons, switches, and potentiometer functionality per UI Specification.
7. On startup or reset, step and distance values reset to zero; goal defaults to 1,000 steps.
8. **Test Mode** (activated by setting switch SW1 UP) modifies functionality:
    - UP button increments steps by 100 and distance by 0.09 km.
    - DOWN button decrements steps by 500 and distance by 0.45 km (no underflow below zero).
    - UP and DOWN buttons' normal functions are disabled in test mode.
    - LEFT and RIGHT buttons behave normally.
9. Interrupt-driven kernel ensures robust multitasking.

---

### User Interface Specification

1. At startup, the OLED displays total steps since last reset.
2. LEFT button cycles display through:
   - Steps counted
   - Distance traveled
   - Set Goal state (to adjust step goal)
3. RIGHT button cycles the display in reverse order of LEFT.
4. UP button toggles units:
   - Steps: raw count or percentage of goal
   - Distance: kilometers or miles
5. DOWN button behavior:
   - Short press in Set Goal state saves the new goal and returns to steps display.
   - Long press (outside Set Goal) resets steps and distance to zero.
6. Feedback differentiates short and long presses of DOWN button.
7. Potentiometer (in Set Goal state) increments/decrements goal in 100-step units.
8. Test Mode (SW1 UP) modifies button functions:
   - UP/DOWN buttons adjust step and distance counts (increments/decrements).
   - Other UP/DOWN functions disabled.
   - LEFT/RIGHT buttons unaffected.
   - SW1 DOWN restores normal button behavior.

---
