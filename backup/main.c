#include <stdio.h>
#include <time.h>
#include "elev.h"

int order_matrix[4][3] = 
{
    { 0, 0, 0 }, // first   up, elevator, down 
    { 0, 0, 0 }, // second  up, elevator, down 
    { 0, 0, 0 }, // third   up, elevator, down 
    { 0, 0, 0 }  // fourth  up, elevator, down 
};

elev_button_type_t buttons[3] = { BUTTON_CALL_UP, BUTTON_COMMAND, BUTTON_CALL_DOWN };

void ov_initialize();
void ov_floor_buttons();
void ov_delay(int s);
void ov_doors();
int ov_check_if_any_orders();
int ov_get_order(int currentFloor);
int ov_check_if_pickups(int currentDir, int currentFloor);
int ov_check_if_order_above(int currentFloor);
int ov_check_if_order_below(int currentFloor);
void ov_turn_off_lights(int currentFloor);

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

    ov_initialize();
    elev_set_door_open_lamp(0);
    currentFloor = elev_get_floor_sensor_signal();
    elev_set_floor_indicator(currentFloor);
    currentOrder = currentFloor;

    while (1) {
        ov_floor_buttons();
        //ov_finish_order(currentFloor, currentDir);
        printf("currentOrder: %d \t currenDir: %d \t currentFloor: %d \n", currentOrder, currentDir, currentFloor);
        ov_print_matrix();
        if (elev_get_stop_signal() == 1) {
            elev_set_motor_direction(DIRN_STOP);
            if (elev_get_floor_sensor_signal() != -1)
                elev_set_door_open_lamp(1);

            elev_set_stop_lamp(1);
            stopped = 1;

            for (int i = 0; i < 4; ++i) {
                ov_turn_off_lights(i);
                for (int j = 0; j < 3; ++j)
                    order_matrix[i][j] = 0;
            }

            while (stopped) {
                printf("STOPPED!!!!!\n");
                ov_floor_buttons();
                if (ov_check_if_any_orders()) stopped = 0;
            }

            elev_set_stop_lamp(0);
            elev_set_door_open_lamp(0);
            currentOrder = ov_get_order(-1);

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

            // if (currentFloor == currentOrder) currentFloor+=currentDir;
        }

        if (ov_check_if_any_orders() && (currentDir == 0)) {
            currentOrder = ov_get_order(currentFloor);
            if (currentFloor - currentOrder < 0) {
                elev_set_motor_direction(DIRN_UP);
                if (!ov_check_if_order_below(currentFloor))
                    currentDir = 1;
            }
            else if (currentFloor - currentOrder > 0) {
                elev_set_motor_direction(DIRN_DOWN);
                if (!ov_check_if_order_above(currentFloor))
                    currentDir = -1;
            }
        }

        if (currentDir != 0) {
            ov_floor_buttons();
            
            if (elev_get_floor_sensor_signal() != -1) {
                currentFloor = elev_get_floor_sensor_signal();
                elev_set_floor_indicator(currentFloor);
                printf("CHECKING FOR PICKUPS!\n");
                if (ov_check_if_pickups(currentDir, currentFloor)) {
                    elev_set_motor_direction(DIRN_STOP);
                    ov_finish_order(currentFloor, currentDir);
                    ov_doors();
                }
            }

            if (currentDir == 1) {
                elev_set_motor_direction(DIRN_UP);
                if (elev_get_floor_sensor_signal() == -1);
                else if (!ov_check_if_order_above(currentFloor))
                    currentDir = 0;
            }
            else if (currentDir == -1) {
                elev_set_motor_direction(DIRN_DOWN);
                if (elev_get_floor_sensor_signal() == -1);
                else if (!ov_check_if_order_below(currentFloor))
                    currentDir = 0;
            }
            //currentFloor = elev_get_floor_sensor_signal();
            
            
            printf("currentOrder: %d \t currenDir: %d \t currentFloor: %d \n", currentOrder, currentDir, currentFloor);
            ov_print_matrix();
            if (currentDir == 0) { //currentOrder == currentFloor) {
                elev_set_motor_direction(DIRN_STOP);
                ov_finish_order(currentFloor, currentDir);
                ov_doors();
            }
        }

        if ((currentFloor == currentOrder) && (elev_get_floor_sensor_signal() != -1)){ //&& !ov_check_if_any_orders()) {
            for (int i = 0; i < 3; ++i) {
                order_matrix[currentFloor][i] = 0;
            }
            ov_turn_off_lights(currentFloor);
            printf("LST FNC!!!!!\n");
            printf("currentOrder: %d \t currenDir: %d \t currentFloor: %d \n", currentOrder, currentDir, currentFloor);
            ov_print_matrix();
        }
    }
    return 0;
}

void ov_initialize()
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

void ov_floor_buttons()
{
    for (int i = 0; i < 4; ++i) {
        switch (i) {
            case 0: {
                for (int j = 0; j < 2; ++j) {
                    if (elev_get_button_signal(buttons[j], i)) {
                        elev_set_button_lamp(buttons[j], i, 1);
                        
                    order_matrix[i][j] = 1;
                    }

                }
            } break;
            case 1: {
                for (int j = 0; j < 3; ++j) {
                    if (elev_get_button_signal(buttons[j], i)) {
                        elev_set_button_lamp(buttons[j], i, 1);
                        
                    order_matrix[i][j] = 1;
                    }
                }
            } break;
            case 2: {
                for (int j = 0; j < 3; ++j) {
                    if (elev_get_button_signal(buttons[j], i)) {
                        elev_set_button_lamp(buttons[j], i, 1);
                        
                    order_matrix[i][j] = 1;
                    }
                }
            } break;
            case 3: {
                for (int j = 1; j < 3; ++j) {
                    if (elev_get_button_signal(buttons[j], i)) {
                        elev_set_button_lamp(buttons[j], i, 1);
                        
                    order_matrix[i][j] = 1;
                    }
                }
            } break;
        }
    }

}

void ov_delay(int s)
{
    time_t t = time(NULL);
    while((t + s) > (time(NULL))){}
}

void ov_doors()
{
    elev_set_door_open_lamp(1);
    clock_t start = clock()/CLOCKS_PER_SEC;
    while ((int)start+3 > (int)(clock()/CLOCKS_PER_SEC))
        check_buttons_for_input();
    //ov_delay(2);
    elev_set_door_open_lamp(0);
}

int ov_check_if_any_orders()
{
    for (int i = 0; i < 4; ++i) 
        for (int j = 0; j < 3; ++j)
            if (order_matrix[i][j] != 0) return 1;
    return 0;
}

int ov_check_if_order_above(int currentFloor)
{
    for (int i = currentFloor + 1; i < 4; ++i)
        for (int j = 0; j < 3; ++j)
            if (order_matrix[i][j] != 0) return 1;
    return 0;
}

int ov_check_if_order_below(int currentFloor)
{
    for (int i = currentFloor - 1; i > -1; --i)
        for (int j = 0; j < 3; ++j)
            if (order_matrix[i][j] != 0) return 1;
    return 0;
}

int ov_get_order(int currentFloor)
{
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 3; ++j)
            if(order_matrix[i][j] && i != currentFloor) return i;
}

int ov_check_if_pickups(int currentDir, int currentFloor)
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

/*
    if (currentDir == 1) {
        for (int i = currentFloor; i < 4; ++i) {
            if (order_matrix[i][0]) return i;
            if (order_matrix[i][1]) return i;
        }
    }
    else {
        for (int i = currentFloor; i >= 0; --i) {
            if (order_matrix[i][1]) return i;
            if (order_matrix[i][2]) return i;
        }
    }
    return 0;
*/
}

void ov_finish_order(int currentFloor, int currentDir)
{
    switch (currentFloor) {
    case 0: {
            order_matrix[0][0] = 0;
            order_matrix[0][1] = 0;
            elev_set_button_lamp(buttons[0], 0, 0);
            elev_set_button_lamp(buttons[1], 0, 0);
        } break;
    case 1:{
            if (currentDir == 1) {
                order_matrix[1][0] = 0;
                order_matrix[1][1] = 0;
                elev_set_button_lamp(buttons[0], 1, 0);
                elev_set_button_lamp(buttons[1], 1, 0);
            }
            else if ( currentDir == -1) {
                order_matrix[1][1] = 0;
                order_matrix[1][2] = 0;
                elev_set_button_lamp(buttons[1], 1, 0);
                elev_set_button_lamp(buttons[2], 1, 0);
            }

            else {
                order_matrix[1][0] = 0;
                order_matrix[1][1] = 0;
                order_matrix[1][2] = 0;
                elev_set_button_lamp(buttons[0], 1, 0);
                elev_set_button_lamp(buttons[1], 1, 0);
                elev_set_button_lamp(buttons[2], 1, 0);
            }
        } break;

    case 2:{
            if (currentDir == 1) {
                order_matrix[2][0] = 0;
                order_matrix[2][1] = 0;
                elev_set_button_lamp(buttons[0], 2, 0);
                elev_set_button_lamp(buttons[1], 2, 0);
            }
            else if ( currentDir == -1) {
                order_matrix[2][1] = 0;
                order_matrix[2][2] = 0;
                elev_set_button_lamp(buttons[1], 2, 0);
                elev_set_button_lamp(buttons[2], 2, 0);
            }

            else {
                order_matrix[2][0] = 0;
                order_matrix[2][1] = 0;
                order_matrix[2][2] = 0;
                elev_set_button_lamp(buttons[0], 2, 0);
                elev_set_button_lamp(buttons[1], 2, 0);
                elev_set_button_lamp(buttons[2], 2, 0);
            }
        } break;

    case 3:{
            order_matrix[3][1] = 0;
            order_matrix[3][2] = 0;
            elev_set_button_lamp(buttons[1], 3, 0);
            elev_set_button_lamp(buttons[2], 3, 0);
        } break;

    }
}

void ov_print_matrix()
{
    for (int i = 0; i < 4; ++i) {
        printf("{%d} {%d} {%d}\n", order_matrix[3 - i][0], order_matrix[3 - i][1], order_matrix[3 - i][2] );
    }
}

void ov_turn_off_lights(int currentFloor) {
    elev_set_button_lamp(buttons[1], currentFloor, 0);
    if (currentFloor == 0)
        elev_set_button_lamp(buttons[0], currentFloor, 0);
    else if (currentFloor == 3)
        elev_set_button_lamp(buttons[2], currentFloor, 0);
    else {
        elev_set_button_lamp(buttons[0], currentFloor, 0);
        elev_set_button_lamp(buttons[2], currentFloor, 0);
    }
}

// up, elevator, down