#pragma once
#include <iostream>
#include "clsMyDblLinkedList.h"
using namespace std;

template <class T>
class clsMyQueue
{
protected:
	clsMyDblLinkedList <T> _MyList;
public:
	
	void push(T value) {
		_MyList.InsertAtEnd(value);
}

	void pop() {
		_MyList.DeleteFirstNode();
	}

	void print() {
		_MyList.PrintList();
	}

	int size() {
		return _MyList.size();
	}

	bool IsEmpty() {
		return _MyList.IsEmpty();
	}

	T Front() {
		return _MyList.GetItem(0);
	}

	T Back() {
		return _MyList.GetItem(size() - 1);
	}

	T GetItem(int Index)
	{
		return _MyList.GetItem(Index);

	}

	void Reverse()
	{

		_MyList.Reverse();

	}

	void UpdateItem(int Index, T NewValue)
	{
		_MyList.UpdateItem(Index, NewValue);

	}

	void InsertAfter(int Index, T NewValue)
	{
		_MyList.InsertAfter(Index, NewValue);
	}


	void InsertAtFront(T Value)
	{
		_MyList.InsertAtBeginning(Value);

	}

	void InsertAtBack(T Value)
	{
		_MyList.InsertAtEnd(Value);
	}


	void Clear()
	{
		_MyList.Clear();
	}

};

