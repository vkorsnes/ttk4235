#ifndef _BUTTONS_H
#define _BUTTONS_H

// Checks if any button is pressed and sets them in the order_matrix
// also sets the light.
void check_buttons_for_input();

// Use when you want to turn off all lights in one floor.
void turn_off_lights(int currentFloor);

#endif // !_BUTTONS_H