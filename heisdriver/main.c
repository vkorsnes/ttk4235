#include <stdio.h>

#include "elev.h"
#include "order_system.h"
#include "elevator_controller.h"
#include "buttons.h"


int main() {
    // Initialize hardware
    if (!elev_init()) {
        printf("Unable to initialize elevator hardware!\n");
        return 1;
    }

    int currentFloor = -1;
    int currentOrder = 0;
    int currentDir = 0;
    int stopped = 0;

    initialize();
    
    currentFloor = elev_get_floor_sensor_signal();
    elev_set_floor_indicator(currentFloor);
    currentOrder = currentFloor;

    while (1) {
        check_buttons_for_input();
        printf("currentOrder: %d \t currenDir: %d \t currentFloor: %d \n", currentOrder, currentDir, currentFloor);
        print_matrix();
        if (elev_get_stop_signal() == 1) 
            stop(stopped, currentOrder, currentDir);


        // The case when elevator is not moving
        if (check_if_any_orders() && (currentDir == 0)) {
            currentOrder = get_order(currentFloor);
            if (currentFloor - currentOrder < 0) {
                elev_set_motor_direction(DIRN_UP);
                if (!check_if_order_below(currentFloor))
                    currentDir = 1;
            }
            else if (currentFloor - currentOrder > 0) {
                elev_set_motor_direction(DIRN_DOWN);
                if (!check_if_order_above(currentFloor))
                    currentDir = -1;
            }
        }

        // The case when elevator is moving
        if (currentDir != 0) {
            check_buttons_for_input();
            if (elev_get_floor_sensor_signal() != -1) {
                currentFloor = elev_get_floor_sensor_signal();
                elev_set_floor_indicator(currentFloor);
                printf("CHECKING FOR PICKUPS!\n");
                if (check_if_pickups(currentDir, currentFloor)) {
                    elev_set_motor_direction(DIRN_STOP);
                    finish_order(currentFloor, currentDir);
                    doors();
                }
            }

            if (currentDir == 1) {
                elev_set_motor_direction(DIRN_UP);
                if (elev_get_floor_sensor_signal() == -1);
                else if (!check_if_order_above(currentFloor))
                    currentDir = 0;
            }
            else if (currentDir == -1) {
                elev_set_motor_direction(DIRN_DOWN);
                if (elev_get_floor_sensor_signal() == -1);
                else if (!check_if_order_below(currentFloor))
                    currentDir = 0;
            }            
            
            printf("currentOrder: %d \t currenDir: %d \t currentFloor: %d \n", currentOrder, currentDir, currentFloor);
            print_matrix();
            if (currentDir == 0) { //currentOrder == currentFloor) {
                elev_set_motor_direction(DIRN_STOP);
                finish_order(currentFloor, currentDir);
                doors();
            }
        }

        if ((currentFloor == currentOrder) && (elev_get_floor_sensor_signal() != -1)) {
            for (int i = 0; i < 3; ++i) {
                order_matrix[currentFloor][i] = 0;
            }
            turn_off_lights(currentFloor);
            printf("LST FNC!!!!!\n");
            printf("currentOrder: %d \t currenDir: %d \t currentFloor: %d \n", currentOrder, currentDir, currentFloor);
            print_matrix();
        }
    }
    return 0;
}

void print_matrix()
{
    for (int i = 0; i < 4; ++i) {
        printf("{%d} {%d} {%d}\n", order_matrix[3 - i][0], order_matrix[3 - i][1], order_matrix[3 - i][2] );
    }
}