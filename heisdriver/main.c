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

    int current_floor = -1;
    int current_order = 0;

    // current_dir is used for making sure the end floors are serviced,
    // only changes when there is no more orders above/below.
    int current_dir = 0;

    initialize();
    
    current_floor = elev_get_floor_sensor_signal();
    current_order = current_floor;
    
    while (1) {
        check_buttons_for_input();

        if (elev_get_stop_signal() == 1) 
            // Stays inside emergency_stop untill new order
            emergency_stop(current_floor, current_order, current_dir);


        // The case when elevator is not moving
        if (check_if_any_orders() && (current_dir == 0)) {
            current_order = get_order(current_floor);

            // checks which direction it should move
            if (current_floor - current_order < 0) { 
                elev_set_motor_direction(DIRN_UP);
                current_dir = 1;
            }
            else if (current_floor - current_order > 0) {
                elev_set_motor_direction(DIRN_DOWN);
                current_dir = -1;
            }
        }

        // The case when elevator is moving
        if (current_dir != 0) {

            // Checks if it should stop when moving past a floor,
            // but only when on on floor
            if (elev_get_floor_sensor_signal() != -1) {
                current_floor = elev_get_floor_sensor_signal();

                // Sets indicator light
                elev_set_floor_indicator(current_floor);

                // Checks if there are any orders in the floor its moving past
                if (check_if_pickups(current_dir, current_floor)) {
                    elev_set_motor_direction(DIRN_STOP);
                    finish_order(current_floor, current_dir);
                    doors();
                }
            }

            // Check if it should continue the same direction it was moving
            // or which way to continue if it had to pick up someone. 
            if (current_dir == 1) {
                elev_set_motor_direction(DIRN_UP);
                if (!check_if_order_above(current_floor))
                    current_dir = 0;
            }
            else if (current_dir == -1) {
                elev_set_motor_direction(DIRN_DOWN);
                if (!check_if_order_below(current_floor))
                    current_dir = 0;
            }            
            
            // Here we're at the last stop.
            if (current_dir == 0) { 
                elev_set_motor_direction(DIRN_STOP);
                finish_order(current_floor, current_dir);
                doors();
            }
        }

        // When ordered in the same floor it's in.
        if ((current_floor == current_order) && (elev_get_floor_sensor_signal() != -1)) {
            for (int i = 0; i < 3; ++i) {
                rset_order(current_floor, i);
            }
            finish_order(current_floor, 0);
            doors();
        }
    }
    return 0;
}
