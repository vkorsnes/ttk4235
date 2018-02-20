#pragma once
#ifndef _EVENT_LIST_H
#define _EVENT_LIST_H

#include <cstdint>
#include <assert.h>

int arr[16] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

bool ov_check_if_any_order(int arr[])
{
	int64_t *intPtr = (int64_t*) arr;
	for (int i = 0; i < 8; ++i)
		if (*intPtr != 0)
			return true
		++intPtr;
	return false;
}

void ov_shift_array_left(int arr[])
{
	int64_t *intPtr = (int64_t*) arr;
	for (int i = 0; i < 15; ++i)
		(*intPtr) >>= 16;
}

bool ov_check_duplicate(int arr[], int order)
{
	for (int i = 0; i < 16; ++i)
		if (arr[i] == order)
			return true;
	return false;
}

void ov_add_order(int arr[], int order) 
{
	assert(arr[15] == 0);
	if (ov_checkDuplicate(arr, order));
	else {
		for (int i = 0; i < 16; ++i) 
			if (arr[15 - i] == 0) {
				arr[16 - i] = order;
				break;
			}
	}
}





bool checkDuplicate(listStruct list[], int order) {
	for(int i = 0; i < 16; ++i)
		if (list[i] == order) return true;
	return false;
}

void removeOrder(listStruct *list, int floor) {
	int button_up = 1 + 3 * (floor - 1);
	int button_down = 2 + 3 * (floor - 1);
	int button_elev = 3 + 3 * (floor - 1);
	int counter = 0;
	int tmp = 0;
	for (int i = 0; i < list->len; ++i) {
		tmp = list->arr[i];
		if ((tmp == button_up) || (tmp == button_down) || (tmp == button_elev))
			++counter;
	}

	// TODO: tungvindt, prøver med matrisen først
}

void addOrder(listStruct *list, int order) {
	if (list->len < 1) {
		list->arr = new int[1];
		list->arr[0] = order;
		++list->len;
	}
	else if (checkDuplicate(list, order));
	else {
		int *temp = new int[list->len + 1];
		for (int i = 0; i < list->len; ++i)
			temp[i] = list->arr[i];
		temp[list->len] = order;
		list->arr = temp;
		++list->len;
	}
}

int getOrder(listStruct *list) {
	if (list->len == 0) return 0;
	else {
		int order = list->arr[0];
		int *temp = new int[list->len - 1];
		for (int i = 0; i < list->len - 1; ++i)
			temp[i] = list->arr[i+1];
		list->arr = temp;
		--list->len;
		return order;
	}
}
#endif // !_EVENT_LIST_H
