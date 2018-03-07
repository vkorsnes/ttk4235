#include "elevator_controller.h"
#include "order_system.h"
#include "elev.h"
#include "buttons.h"

void initialize()
{
    if (elev_get_floor_sensor_signal() == -1)
        elev_set_motor_direction(DIRN_DOWN);
    else
        elev_set_motor_direction(DIRN_STOP); 
    while (1) {
        if (elev_get_floor_sensor_signal() !=  -1) {
            elev_set_motor_direction(DIRN_STOP);
            elev_set_floor_indicator(elev_get_floor_sensor_signal());
            break;
        }
    }
}

void emergency_stop(int currentFloor, int currentOrder, int currentDir) 
{
    elev_set_motor_direction(DIRN_STOP);

    // If it stops on a floor, open doors.
    if (elev_get_floor_sensor_signal() != -1)
        elev_set_door_open_lamp(1);

    elev_set_stop_lamp(1);

    // Clear all orders.
    for (int i = 0; i < 4; ++i) {
        turn_off_lights(i);
        for (int j = 0; j < 3; ++j)
            rset_order(i,j);
    }

    // Stay stopped untill a new order has been issued
    while (1) {
        // Make sure you cant do anything while the stop-button is pressed in
        if (!elev_get_stop_signal())
            check_buttons_for_input();
        if (check_if_any_orders()) 
            break;
    }

    elev_set_stop_lamp(0);
    elev_set_door_open_lamp(0);
    currentOrder = get_order(-1);

    // When stopping between two floors, in order to return we must
    // change current floor to make it move back to a floor.
    if (currentOrder == currentFloor) {
        if (currentDir == 1) {
            currentDir = -1;
            currentFloor += 1;
        }
        else if (currentDir == -1) {
            currentDir = 1;
            currentFloor -= 1;
        }
    }
    else currentDir = 0;
}