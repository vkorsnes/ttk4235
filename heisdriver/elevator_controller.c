#include "elevator_controller.h"

void initialize()
{
    if (elev_get_floor_sensor_signal() == -1)
        elev_set_motor_direction(DIRN_DOWN);
    else
        elev_set_motor_direction(DIRN_STOP); 
    while (1) {
        // Change direction when we reach top/bottom floor
        if (elev_get_floor_sensor_signal() !=  -1) {
            elev_set_motor_direction(DIRN_STOP);
            elev_set_floor_indicator(elev_get_floor_sensor_signal());
            break;
        }
    }
}

void stop(int stopped, int currentOrder, int currentDir) 
{
    elev_set_motor_direction(DIRN_STOP);
    if (elev_get_floor_sensor_signal() != -1)
        elev_set_door_open_lamp(1);

    elev_set_stop_lamp(1);
    stopped = 1;

    for (int i = 0; i < 4; ++i) {
        turn_off_lights(i);
        for (int j = 0; j < 3; ++j)
            order_matrix[i][j] = 0;
    }

    while (stopped) {
        printf("STOPPED!!!!!\n");
        floor_buttons();
        if (check_if_any_orders()) stopped = 0;
    }

    elev_set_stop_lamp(0);
    elev_set_door_open_lamp(0);
    currentOrder = get_order(-1);

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