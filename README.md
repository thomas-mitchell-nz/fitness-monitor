# fitness-monitor
A TIVA-Orbit board was used to implement a rudimentary personal fitness monitor. The purpose of the fitness monitor was to record a user’s steps, estimate the distance travelled and display the user’s progress towards their set goals. To implement this functionality, many concurrent foreground and background tasks were required. A robust, interrupt driven kernel was used to achieve this behaviour. 

Link to project demo: https://drive.google.com/file/d/1ADSg9c9PQlCyL9jafoBX7RClkiDyDpmP/view?usp=sharing

This project was created using Code-Composer Studio (CCS). Refer to the 'CCS Tutorial' document for instructions on setting up a workspace.

Functional Specification:

    1. The program estimates the number of steps taken by a user based on data
    from the accelerometer on the Orbit board.

    2. The program estimates the distance travelled by the user.

    3. The program allows the user to set a step goal and displays
    progress towards this goal.

    4. The program notifies the user when a goal is completed.

    5. The RESET button on the TIVA board restarts the program and clear any
    stored step, distance and goal values.

    6. In addition to the requirements above, the user interface – made up of the
    display, buttons, switches and potentiometer on the TIVA and Orbit boards –
    functions according to the requirements given in the UI Specification.

    7. When the program starts, which may happen after a ‘reset’ operation or after
    reprogramming, the step and distance values are set to zero and the goal
    is returned to its default value, namely 1,000 steps.

    8. The program includes a ‘test mode’, activated by moving switch 1 (SW1)
    to the up position. This test mode has the following requirements:

        8.1) When in test mode, pressing the UP button increments the step
        count by 100 steps, and the distance travelled by 0.09 km.

        8.2) When in test mode, pressing the DOWN button decrements the
        step count by 500, and the distance travelled by 0.45 km. Neither of
        these values fall below zero or underflow.

        8.3) When in test mode, the other functions of the UP and DOWN buttons are
        disabled.

        8.4) The behaviour of the LEFT and RIGHT buttons are unaffected
        by being in the test mode.

    9. The program uses an interrupt-driven kernel and maintains robust behaviour 
    at all times.

User Interface Specification:

    1. At startup the OLED board displays the number of steps counted since the
    last reset or power cycle. Pushing the LEFT button on the Orbit board changes 
    the display to the total distance travelled since last reset. Pushing the
    LEFT button again takes the user to a Set Goal state, where the target
    number of steps can be set. Pushing the LEFT button again displays the
    number of steps counted since the last reset or power cycle.

    2. Pushing the RIGHT button achieves the same change in state as pushing
    the LEFT button, but in the opposite direction: that is, pushing the RIGHT button
    when the number of steps is displayed takes the user to a Set Goal state;
    pushing the RIGHT button again shows the total distance travelled; and
    pushing the RIGHT button a third time shows the total number of steps
    since last reset.

    3. Pushing the UP button on the TIVA board toggles the units used by the
    fitness monitor.

        3.1. For the total number of steps, the units are either the raw number of steps
        or the number of steps as a percentage of the step goal.

        3.2. For the total distance travelled, the units are either the total
        distance in kilometres or the total distance in miles.
        In all cases, numbers shown on the OLED display are accompanied by units.

    4. Briefly pushing the DOWN button on the TIVA board when in the Set Goal state
    sets the number displayed as the new goal and change the state to show
    steps counted. When not in the Set Goal state a long press on the DOWN
    button resets the number of steps counted and distance travelled to zero.

    5. The UI provides feedback to the user that acknowledges and
    differentiates between long and short pushes on the DOWN button.

    6. Rotating the potentiometer on the Orbit board clockwise when in the Set Goal
    state increases the number displayed. Similarly, rotating anti-clockwise
    decreases the displayed value. The Goal value increments in units
    of 100 steps. Note that the goal value is only overwritten with the
    displayed value when the DOWN button is briefly pushed.

    7. Setting SW1 to the UP position puts the fitness monitor in a test mode,
    where the functionality of the GUI can be verified. In this test mode each push of
    the UP button increments the step count by 100 and the distance by 0.09
    km. Likewise, pushing the DOWN button decrements the step count by 500 and the 
    distance by 0.45 km. Note that the other functions of the UP and
    DOWN buttons, namely toggling units, setting goals and resetting counts, are 
    disabled while SW1 is UP. The functionality of the LEFT and RIGHT
    buttons are not be affected by SW1. Setting SW1 to DOWN restores the normal 
    functionality of the UP and DOWN buttons.
