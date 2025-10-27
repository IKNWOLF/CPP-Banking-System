#pragma once
#include<iostream>
using namespace std;
#include "clsMyQueue.h"

template <class T>

class clsMyStack : protected clsMyQueue<T>
{
public:

	void push(T value){
		this->_MyList.InsertAtBeginning(value);	
	}

	T Top() {
		return this->Front();
	}

	T Bottom() {
		return this->Back();;
	}

	using clsMyQueue<T>::print;
};

