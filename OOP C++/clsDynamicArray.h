#pragma once
using namespace std;
#include <iostream>

template <class T>
class clsDynamicArray
{

protected:
	int _Size = 0;
	T* _TempArray;

public:
	T* OriginalArray;

	clsDynamicArray(int size = 0) {
		if (size < 0)
		{
			size = 0;
		}

		_Size = size;

		OriginalArray = new T[_Size];
	}

	~clsDynamicArray() {
		delete[] OriginalArray;
	}

	bool SetItem(int index, T value) {
		if (index >= _Size || index < 0)
		{
			return false;
		}
		else
		{
			OriginalArray[index] = value;
			return true;
		}
	}

	int Size() {
		return _Size;
	}

	bool IsEmpty() {
		return _Size == 0;
	}

	void PrintList() {
		for (int i = 0; i < _Size; i++)
		{
			cout << OriginalArray[i] << " ";
		}
		cout << "\n";
	}

	void Resize(int NewSize) {
		if (NewSize < 0) NewSize = 0;

		_TempArray = new T[NewSize];

		int elementsToCopy = (NewSize < _Size) ? NewSize : _Size;

		for (int i = 0; i < elementsToCopy; i++) {
			_TempArray[i] = OriginalArray[i];
		}

		delete[] OriginalArray;
		OriginalArray = _TempArray;
		_Size = NewSize; 
	}

	T GetItem(int Index) {
		return OriginalArray[Index];
	}

	void Reverse() {
		_TempArray = new T[_Size];

		for (int i = 0; i < _Size; i++)
		{
			_TempArray[i] = OriginalArray[_Size - (i + 1)];
		}

		delete [] OriginalArray;

		OriginalArray = _TempArray;
	}

	void Clear() {
		_Size = 0;

		_TempArray = new T[0];

		delete [] OriginalArray;

		OriginalArray = _TempArray;
	}

	bool DeleteItemAtIndex(int Index) {

		if (Index >= _Size || Index < 0)
		{
			return false;
		}

		_TempArray = new T[(--_Size)];

		for (int i = 0; i < Index; i++)
		{
			_TempArray[i] = OriginalArray[i];
		}

		for (int i = Index + 1; i < _Size + 1; i++)
		{
			_TempArray[i - 1] = OriginalArray[i];
		}

		delete[] OriginalArray;

		OriginalArray = _TempArray;
		return true;
	}

	void DeleteFrontItem() {

		DeleteItemAtIndex(0);

	}

	void DeleteBackItem() {

		DeleteItemAtIndex(_Size - 1);

	}

	int Find(T Value) {

		for (int i = 0; i < _Size; i++)
		{
			if (OriginalArray[i] == Value)
			{
				return i;
			}
		}

		return -1;
	}

	bool DeleteItemWithValue(T Value) {
		int index = Find(Value);

		if (index == -1)
		{
			return false;
		}
		else
		{
			DeleteItemAtIndex(index);
			return true;
		}
	}

	bool InsertAt(int Index, T Value) {

		if (Index < 0 || Index > _Size) 
			return false;

		_TempArray = new T[_Size + 1];

		for (int i = 0; i < Index; i++) {
			_TempArray[i] = OriginalArray[i];
		}

		_TempArray[Index] = Value;

		for (int i = Index; i < _Size; i++) {
			_TempArray[i + 1] = OriginalArray[i];
		}

		delete[] OriginalArray;
		OriginalArray = _TempArray;
		_Size++;

		return true;
	}


	void InsertAtBeginning(T value)
	{

		InsertAt(0, value);

	}


	bool InsertBefore(int index, T value)
	{
		if (index < 1)
			return InsertAt(0, value);
		else
			return InsertAt(index - 1, value);

	}

	bool InsertAfter(int index, T value)
	{
		if (index >= _Size)
			return InsertAt(_Size - 1, value);
		else
			return InsertAt(index + 1, value);

	}

	bool InsertAtEnd(T value)
	{

		return InsertAt(_Size , value);

	}


};

