#include "buttons.h"
#include "order_system.h"


void check_buttons_for_input()
{
    for (int i = 0; i < 4; ++i) {
        switch (i) {
            case 0: {
                for (int j = 0; j < 2; ++j) {
                    if (elev_get_button_signal(button_type[j], i)) {
                        set_order(i,j);
                    }

                }
            } break;
            case 1: {
                for (int j = 0; j < 3; ++j) {
                    if (elev_get_button_signal(button_type[j], i)) {
                        set_order(i,j);
                    }
                }
            } break;
            case 2: {
                for (int j = 0; j < 3; ++j) {
                    if (elev_get_button_signal(button_type[j], i)) {
                        set_order(i,j);
                    }
                }
            } break;
            case 3: {
                for (int j = 1; j < 3; ++j) {
                    if (elev_get_button_signal(button_type[j], i)) {
                        set_order(i,j);
                    }
                }
            } break;
        }
    }
}
