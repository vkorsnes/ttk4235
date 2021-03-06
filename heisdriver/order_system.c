#include "order_system.h"

int order_matrix[4][3] = 
{
    { 0, 0, 0 }, // first   up, elevator, down 
    { 0, 0, 0 }, // second  up, elevator, down 
    { 0, 0, 0 }, // third   up, elevator, down 
    { 0, 0, 0 }  // fourth  up, elevator, down 
};

elev_button_type_t button_type[3] = { BUTTON_CALL_UP, BUTTON_COMMAND, BUTTON_CALL_DOWN };

// If there is any orders, returns true (1)
int check_if_any_orders()
{
    for (int i = 0; i < 4; ++i) 
        for (int j = 0; j < 3; ++j)
            if (order_matrix[i][j] != 0) return 1;
    return 0;
}

// Checks for order outside the current floor and returns order
int get_order(int current_floor)
{
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 3; ++j)
            if(order_matrix[i][j] && i != current_floor) return i;
}

int check_if_pickups(int current_dir, int current_floor)
{
    // When moving up, ignore orders down
    if (current_dir == 1) {
        for (int i = 0; i < 2; ++i) {
            if (order_matrix[current_floor][i]) {
                return 1;
            }

        }
    }
    // When moving down, ignore orders up
    else if (current_dir == -1) {
        for (int i = 1; i < 3; ++i) {
            if (order_matrix[current_floor][i]) {
                return 1;
            }
        }
    }
    else {
      return 0;
    } 
}

void finish_order(int current_floor, int current_dir)
{
    if (current_floor == -1) return;

    rset_order(current_floor, 1);
    
    // When in first or fourth floor, all orders must have been serviced
    if (current_floor == 0) 
        rset_order(current_floor, 0);

    else if (current_floor == 3)
        rset_order(current_floor, 2);
    
    // Only remove order in the direction the elevator is moving
    else if (current_dir == 1) 
        rset_order(current_floor, 0);

    else if (current_dir == -1) 
        rset_order(current_floor, 2);
    
    // curentDir == 0 elevator has landed on this floor, and thus all orders are removed
    else {
        rset_order(current_floor, 0);
        rset_order(current_floor, 2);
    }
}


void set_order(int m, int n)  
{ 
    order_matrix[m][n] = 1;

    // Setting a light that doesnt exist should never happen, but redundancy is good.
    if(!(m == 3 && n == 0) || !(m == 0 && n == 2))
        elev_set_button_lamp(button_type[n], m 1);
}

void rset_order(int m, int n) 
{ 
    order_matrix[m][n] = 0;

    // Resetting a light that doesnt exist happens a lot, so must check.
    if(!(m == 3 && n == 0) || !(m == 0 && n == 2))
        elev_set_button_lamp(button_type[n], m = 0);

}


int check_if_order_above(int current_floor)
{
    for (int i = current_floor + 1; i < 4; ++i)
        for (int j = 0; j < 3; ++j)
            if (order_matrix[i][j] != 0) return 1;
    return 0;
}

int check_if_order_below(int current_floor)
{
    for (int i = current_floor - 1; i > -1; --i)
        for (int j = 0; j < 3; ++j)
            if (order_matrix[i][j] != 0) return 1;
    return 0;
}