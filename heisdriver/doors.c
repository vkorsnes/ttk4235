#include <unistd.h>
#include "doors.h"

void doors()
{
    elev_set_door_open_lamp(1);
    sleep(3);
    elev_set_door_open_lamp(0);
}