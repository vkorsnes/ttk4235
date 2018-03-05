#include "buttons.h"

void check_buttons_for_input()
{
    for (int i = 0; i < 4; ++i) {
        switch (i) {
            case 0: {
                for (int j = 0; j < 2; ++j) {
                    if (elev_get_button_signal(button_type[j], i)) {
                        elev_set_button_lamp(button_type[j], i, 1);
                        
                    order_matrix[i][j] = 1;
                    }

                }
            } break;
            case 1: {
                for (int j = 0; j < 3; ++j) {
                    if (elev_get_button_signal(button_type[j], i)) {
                        elev_set_button_lamp(button_type[j], i, 1);
                        
                    order_matrix[i][j] = 1;
                    }
                }
            } break;
            case 2: {
                for (int j = 0; j < 3; ++j) {
                    if (elev_get_button_signal(button_type[j], i)) {
                        elev_set_button_lamp(button_type[j], i, 1);
                        
                    order_matrix[i][j] = 1;
                    }
                }
            } break;
            case 3: {
                for (int j = 1; j < 3; ++j) {
                    if (elev_get_button_signal(button_type[j], i)) {
                        elev_set_button_lamp(button_type[j], i, 1);
                        
                    order_matrix[i][j] = 1;
                    }
                }
            } break;
        }
    }
}

void turn_off_lights(int currentFloor) {
    elev_set_button_lamp(button_type[1], currentFloor, 0);
    if (currentFloor == 0)
        elev_set_button_lamp(button_type[0], currentFloor, 0);
    else if (currentFloor == 3)
        elev_set_button_lamp(button_type[2], currentFloor, 0);
    else {
        elev_set_button_lamp(button_type[0], currentFloor, 0);
        elev_set_button_lamp(button_type[2], currentFloor, 0);
    }
}