#ifndef	_ELEVATOR_CONTROLLER_H
#define _ELEVATOR_CONTROLLER_H

// Moves elevator to defined floor
void initialize();

// Stops elevator in place when stop-button is pressed.
// Opens doors if in floor, and starts moving (in the right direction) when new order is recieved.
void emergency_stop(int stopped, int current_order, int current_dir);


#endif // !_ELEVATOR_CONTROLLER_H