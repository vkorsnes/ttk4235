#include <stdio.h>
#include <time.h>
#include "elev.h"

int order_array[4][3] = {
    {0,0,0},
    {0,0,0},
    {0,0,0},
    {0,0,0}
};

elev_button_type_t buttonz[3] = {BUTTON_CALL_UP, BUTTON_COMMAND, BUTTON_CALL_DOWN};


void omvk_initialize();

void omvk_floor_buttons();

void omvk_delay(int s);


void omvk_doors();

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
        omvk_floor_buttons();
        //elev_set_button_lamp(elev_get_button_signal());

        // Stop elevator and exit program if the stop button is pressed
        if (elev_get_stop_signal() == 1) {
            elev_set_motor_direction(DIRN_STOP);
            break;
        }
    }

    return 0;
}

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

void omvk_floor_buttons()
{
    for (int i = 0; i < 4; ++i) {
        switch (i) {
            case 0: {
                for (int j = 0; j < 2; ++j) {
                    if (elev_get_button_signal(buttonz[j], i)){
                        elev_set_button_lamp(buttonz[j], i, 1);
                        order_array[i][j] = 1;
                    }

                }
            } break;
            case 1: {
                for (int j = 0; j < 3; ++j) {
                    if (elev_get_button_signal(buttonz[j], i)) {
                        elev_set_button_lamp(buttonz[j], i, 1);
                        order_array[i][j] = 1;
                    }
                }
            } break;
            case 2: {
                for (int j = 0; j < 3; ++j) {
                    if (elev_get_button_signal(buttonz[j], i)) {
                        elev_set_button_lamp(buttonz[j], i, 1);
                        order_array[i][j] = 1;
                    }
                }
            } break;
            case 3: {
                for (int j = 1; j < 3; ++j) {
                    if (elev_get_button_signal(buttonz[j], i)) {
                        elev_set_button_lamp(buttonz[j], i, 1);
                        order_array[i][j] = 1;
                    }
                }
            } break;
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