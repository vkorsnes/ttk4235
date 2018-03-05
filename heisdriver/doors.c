#include <unistd.h>
#include "doors.h"

void doors()
{
    elev_set_door_open_lamp(1);
    usleep(3000);
    elev_set_door_open_lamp(0);
}