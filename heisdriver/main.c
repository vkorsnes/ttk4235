#include <stdio.h>
#include <time.h>
#include "elev.h"



void omvk_initialize()
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
                if (elev_get_stop_signal() == 1) {
            elev_set_motor_direction(DIRN_STOP);
            break;
        }
    }
}
void omvk_delay(int s)
{
    time_t t = time(NULL);
    while((t + s) > (time(NULL))){}
}

void omvk_doors()
{
    elev_set_door_open_lamp(1);
    omvk_delay(3);
    elev_set_door_open_lamp(0);
}

int main() {
    // Initialize hardware
    if (!elev_init()) {
        printf("Unable to initialize elevator hardware!\n");
        return 1;
    }
    int currentFloor = -1;
    omvk_initialize();
    elev_set_door_open_lamp(0);
    omvk_doors();
    currentFloor = elev_get_floor_sensor_signal();

    while (1) {
        // Stop elevator and exit program if the stop button is pressed
        if (elev_get_stop_signal() == 1) {
            elev_set_motor_direction(DIRN_STOP);
            break;
        }
    }

    return 0;
}
