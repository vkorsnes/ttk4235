#include <stdio.h>
#include "elev.h"
#include "order_system.h"
#include "elevator_controller.h"
#include "buttons.h"
#include "doors.h"

int main() 
{
    // Initialize hardware
    if (!elev_init()) {
        printf("Unable to initialize elevator hardware!\n");
        return 1;
    }

    int currentFloor = -1;
    int currentOrder = 0;

    // currentDir is used for making sure the end floors are serviced,
    // only changes when there is no more orders above/below.
    int currentDir = 0;

    initialize();
    
    currentFloor = elev_get_floor_sensor_signal();
    currentOrder = currentFloor;
    
    while (1) {
        check_buttons_for_input();

        if (elev_get_stop_signal() == 1) 
            // Stays inside stop untill new order
            emergency_stop(currentFloor, currentOrder, currentDir);


        // The case when elevator is not moving
        if (check_if_any_orders() && (currentDir == 0)) {
            currentOrder = get_order(currentFloor);

            // checks which direction it should move
            if (currentFloor - currentOrder < 0) { 
                elev_set_motor_direction(DIRN_UP);
                currentDir = 1;
            }
            else if (currentFloor - currentOrder > 0) {
                elev_set_motor_direction(DIRN_DOWN);
                currentDir = -1;
            }
        }

        // The case when elevator is moving
        if (currentDir != 0) {

            // Checks if it should stop when moving past a floor,
            // but only when on on floor
            if (elev_get_floor_sensor_signal() != -1) {
                currentFloor = elev_get_floor_sensor_signal();

                // Sets indicator light
                elev_set_floor_indicator(currentFloor);

                // Checks if there are any orders in the floor its moving past
                if (check_if_pickups(currentDir, currentFloor)) {
                    elev_set_motor_direction(DIRN_STOP);
                    finish_order(currentFloor, currentDir);
                    doors();
                }
            }

            // Check if it should continue the same direction it was moving
            // or which way to continue if it had to pick up someone. 
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
            
            // Here we're at the last stop.
            if (currentDir == 0) { 
                elev_set_motor_direction(DIRN_STOP);
                finish_order(currentFloor, currentDir);
                doors();
            }
        }

        // When ordered in the same floor it's in.
        if ((currentFloor == currentOrder) && (elev_get_floor_sensor_signal() != -1)) {
            for (int i = 0; i < 3; ++i) {
                rset_order(currentFloor, i);
            }
            doors();
        }
    }
    return 0;
}
