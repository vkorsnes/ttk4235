#include "order_system.h"

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
    if (currentDir == 1) {
        for (int i = 0; i < 2; ++i) {
            if (order_matrix[currentFloor][i]) return 1;
        }
    }
    else if (currentDir == -1) {
        for (int i = 1; i < 3; ++i) {
            if (order_matrix[currentFloor][i]) return 1;
        }
    }
    else return 0;
}

void finish_order(int currentFloor, int currentDir)
{
    if (currentFloor == -1) return;

    order_matrix[currentFloor][1] = 0
    elev_set_button_lamp(button_type[1], currentFloor);
    
    // When in first or fourth floor, all orders must have been serviced
    if (currentFloor == 0) {
        order_matrix[currentFloor][0] = 0;
        elev_set_button_lamp(button_type[0], currentFloor);
    }
    else if (currentFloor == 3) {
        order_matrix[currentFloor][2] = 0;
        elev_set_button_lamp(button_type[2], currentFloor);   
    }
    
    // Only remove order in the direction the elevator is moving
    else if (currentDir == 1) {
        order_matrix[currentFloor][0] = 0;
        elev_set_button_lamp(button_type[0], 0);
    }
    else if (currentDir == -1) {
        order_matrix[currentFloor][2] = 0;
        elev_set_button_lamp(button_type[2], 0);
    }
    
    // In this case the elevator has landed on this floor, and thus all orders are removed
    else {
        order_matrix[currentFloor][0] = 0;
        order_matrix[currentFloor][2] = 0;
        elev_set_button_lamp(button_type[0], 0);
        elev_set_button_lamp(button_type[2], 0);
    }
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