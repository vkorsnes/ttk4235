#ifndef _ORDER_SYSTEM_H
#define _ORDER_SYSTEM_H

int order_matrix[4][3] = 
{
    { 0, 0, 0 }, // first   up, elevator, down 
    { 0, 0, 0 }, // second  up, elevator, down 
    { 0, 0, 0 }, // third   up, elevator, down 
    { 0, 0, 0 }  // fourth  up, elevator, down 
};

elev_button_type_t button_type[3] = { BUTTON_CALL_UP, BUTTON_COMMAND, BUTTON_CALL_DOWN };

// If any orders, returns true (1)
int check_if_any_orders();

// Returns order
int get_order(int currentFloor);

// When moving, checks if it should stop and pick up passanger.
int check_if_pickups(int currentDir, int currentFloor);

// Functions for making sure the elevator reaches the first and fourth floor.
int check_if_order_above(int currentFloor);
int check_if_order_below(int currentFloor);

#endif // !_ORDER_SYSTEM_H