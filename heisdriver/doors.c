#include <unistd.h>
#include "doors.h"
#include "buttons.h"
#include <time.h>

void doors()
{
    elev_set_door_open_lamp(1);

    //Start gets a timespamp from CPU clock, dividing by the constant "CLOCKS_PER_SEC" turns the value into seconds
    //Program then checks for new orders while door is open
    clock_t start = clock()/CLOCKS_PER_SEC;
    while ((int)start+3 > (int)(clock()/CLOCKS_PER_SEC))
    	check_buttons_for_input();
    elev_set_door_open_lamp(0);
}