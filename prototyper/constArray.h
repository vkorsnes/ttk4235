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

int ov_get_order(int arr[])
{
	if (!ov_check_if_any_order(arr)) return 0;
	if else (arr[0] == 0){
		while (arr[0] == 0)
			ov_shift_array_left(arr);
		int tmp = arr[0];
		ov_shift_array_left(arr);
		return tmp;
	else {
		int tmp = arr[0];
		ov_shift_array_left(arr);
		return tmp;
	}
}

void ov_remove_order(int arr[], int floor)
{
	
}

#endif // !_EVENT_LIST_H