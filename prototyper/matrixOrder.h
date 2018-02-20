#pragma once
#ifndef	_MATRIX_ORDER_H
#define	_MATRIX_ORDER_H

void decrement_matrix(int& order[])
{
	// TODO
}

void ov_get_button_signal(int& order[])
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

void ov_remove_orders(int& order[], int floor)
{
	for (int i = 0; i < 3; ++i) {
		order[floor][i] = 0;
		elev_set_button_lamp(buttonz[i], floor, 0);
	}
}

int ov_get_order(int& order[])
{
	int = 10;
}

#endif // !_MATRIX_ORDER_H