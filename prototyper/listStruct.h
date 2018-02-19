#pragma once
#ifndef _EVENT_LIST_H
#define _EVENT_LIST_H

struct listStruct{
	int *arr;
	int len = 0;
};

void addOrder(listStruct *list, int order) {
	if (list->len < 1) {
		list->arr = new int[1];
		list->arr[0] = order;
		++list->len;
	}
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
