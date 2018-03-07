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
int get_order(int currentFloor)
{
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 3; ++j)
            if(order_matrix[i][j] && i != currentFloor) return i;
}

int check_if_pickups(int currentDir, int currentFloor)
{
    // When moving up, ignore orders down
    if (currentDir == 1) {
        for (int i = 0; i < 2; ++i) {
            if (order_matrix[currentFloor][i]) {
                return 1;
            }

        }
    }
    // When moving down, ignore orders up
    else if (currentDir == -1) {
        for (int i = 1; i < 3; ++i) {
            if (order_matrix[currentFloor][i]) {
                return 1;
            }
        }
    }
    else {
      return 0;
    } 
}

void finish_order(int currentFloor, int currentDir)
{
    if (currentFloor == -1) return;

    rset_order(currentFloor, 1);
    
    // When in first or fourth floor, all orders must have been serviced
    if (currentFloor == 0) 
        rset_order(currentFloor, 0);

    else if (currentFloor == 3)
        rset_order(currentFloor, 2);
    
    // Only remove order in the direction the elevator is moving
    else if (currentDir == 1) 
        rset_order(currentFloor, 0);

    else if (currentDir == -1) 
        rset_order(currentFloor, 2);
    
    // In this case the elevator has landed on this floor, and thus all orders are removed
    else {
        rset_order(currentFloor, 0);
        rset_order(currentFloor, 2);
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


int check_if_order_above(int currentFloor)
{
    for (int i = currentFloor + 1; i < 4; ++i)
        for (int j = 0; j < 3; ++j)
            if (order_matrix[i][j] != 0) return 1;
    return 0;
}

int check_if_order_below(int currentFloor)
{
    for (int i = currentFloor - 1; i > -1; --i)
        for (int j = 0; j < 3; ++j)
            if (order_matrix[i][j] != 0) return 1;
    return 0;
}