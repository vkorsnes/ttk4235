#include <stdio.h>
#include <time.h>
#include "elev.h"

int order_matrix[4][3] = 
{
    { 0, 0, 0 }, // fourth  up, elevator, down 
    { 0, 0, 0 }, // third   up, elevator, down 
    { 0, 0, 0 }, // second  up, elevator, down 
    { 0, 0, 0 }  // first   up, elevator, down 
};

elev_button_type_t buttons[3] = { BUTTON_CALL_UP, BUTTON_COMMAND, BUTTON_CALL_DOWN };

void ov_initialize();
void ov_floor_buttons();
void ov_delay(int s);
void ov_doors();
int ov_check_if_any_orders();
int ov_get_order(int currentFloor);
void ov_check_if_pickups(int currentDir, int currentFloor, int *currentOrder);

int main() {
    // Initialize hardware
    if (!elev_init()) {
        printf("Unable to initialize elevator hardware!\n");
        return 1;
    }

    int currentFloor = -1;
    int currentOrder = 0;
    int currentDir = 0;

    ov_initialize();
    elev_set_door_open_lamp(0);
    ov_doors();
    currentFloor = elev_get_floor_sensor_signal();
    currentOrder = currentFloor;
    while (1) {
        ov_floor_buttons();

        if (elev_get_stop_signal() == 1) {
            elev_set_motor_direction(DIRN_STOP);
            currentDir = 0;
            break;
        }
        if (ov_check_if_any_orders(order_matrix)) {
            currentOrder = ov_get_order(currentFloor);
            if (currentFloor - currentOrder < 0) {
                elev_set_motor_direction(DIRN_UP);
                currentDir = 1;
            }
            else if (currentFloor - currentOrder > 0) {
                elev_set_motor_direction(DIRN_DOWN);
                currentDir = -1;
            }
        }
        while(currentFloor != currentOrder) {
            currentFloor = elev_get_floor_sensor_signal();
            ov_check_if_pickups(currentDir, currentFloor, &currentOrder);
            printf("currentOrder: %d \t currenDir: %d \t currentFloor: %d \n", currentOrder, currentDir, currentFloor);
            if (currentOrder == currentFloor) {
                elev_set_motor_direction(DIRN_STOP);
                ov_finish_order(currentFloor, currentDir);
                ov_doors();
            }
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
                if (elev_get_stop_signal() == 1) {
            elev_set_motor_direction(DIRN_STOP);
            break;
        }
    }
}

void ov_floor_buttons()
{
    for (int i = 1; i < 5; ++i) {
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
    ov_delay(3);
    elev_set_door_open_lamp(0);
}

int ov_check_if_any_orders()
{
    for (int i = 0; i < 4; ++i) 
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

void ov_check_if_pickups(int currentDir, int currentFloor, int *currentOrder)
{
    if (currentDir == 1) {
        for (int i = currentFloor; i < 4; ++i) {
            if (order_matrix[i][0]) *currentOrder = i;
            if (order_matrix[i][1]) *currentOrder = i;
        }
    }
    else {
        for (int i = currentFloor; i >= 0; --i) {
            if (order_matrix[i][1]) *currentOrder = i;
            if (order_matrix[i][2]) *currentOrder = i;
        }
    }
    return 0;
}

void ov_finish_order(int currentFloor, int currentDir)
{
    if (currentDir == 1) {
        order_matrix[currentFloor][0] = 0;
        order_matrix[currentFloor][1] = 0;
    }
    else if (currentDir == -1) {
        order_matrix[currentFloor][1] = 0;
        order_matrix[currentFloor][2] = 0;
    }
}

void ov_print_matrix()
{
    for (int i = 0; i < 4) {
        printf("{%d} {&d} {&d}\n", order_matrix[i][0], order_matrix[i][1], order_matrix[i][2] );
    }
}

// up, elevator, down