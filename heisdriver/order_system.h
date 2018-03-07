#ifndef _ORDER_SYSTEM_H
#define _ORDER_SYSTEM_H

// If any orders, returns true (1)
int check_if_any_orders();

// Returns floor number for order
int get_order(int current_floor);

// When moving, checks if it should stop and pick up passanger.
int check_if_pickups(int current_dir, int current_floor);

// Resets orders which are serviced
void finish_order(int current_floor, int current_dir);

void set_order(int m, int n);
void rset_order(int m, int n);

// Functions for making sure the elevator reaches the first and fourth floor.
int check_if_order_above(int current_floor);
int check_if_order_below(int current_floor);

#endif // !_ORDER_SYSTEM_H