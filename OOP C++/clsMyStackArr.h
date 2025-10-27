#pragma once
#include <iostream>
#include "clsMyQueueArray.h"
using namespace std;

template <class T>
class clsMyStackArr : public clsMyQueueArray<T>
{
public:

	void push(T value) {
		clsMyQueueArray <T> ::_MyList.InsertAtBeginning(value);
	}

	
	T Top() {
		return clsMyQueueArray <T> ::front();
	}

	T Bottom() {
		return clsMyQueueArray <T> ::back();
	}
};

