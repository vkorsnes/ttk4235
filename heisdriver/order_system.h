#ifndef _ORDER_SYSTEM_H
#define _ORDER_SYSTEM_H

#include "elev.h"

extern int order_matrix[4][3];
extern elev_button_type_t button_type[3];

// If any orders, returns true (1)
int check_if_any_orders();

// Returns order
int get_order(int currentFloor);

// When moving, checks if it should stop and pick up passanger.
int check_if_pickups(int currentDir, int currentFloor);

// 
void finish_order(int currentFloor, int currentDir);

void set_order(int m, int n);
void rset_order(int m, int n);

// Functions for making sure the elevator reaches the first and fourth floor.
int check_if_order_above(int currentFloor);
int check_if_order_below(int currentFloor);

#endif // !_ORDER_SYSTEM_H