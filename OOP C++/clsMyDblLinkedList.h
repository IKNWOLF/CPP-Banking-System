#pragma once
#include<iostream>
using namespace std;

template <class T>
class clsMyDblLinkedList
{
	
protected:

	int _size = 0;

public:
	

	class Node {

	public:

		T value;
		Node* next;
		Node* prev;

	};

	Node* Head = NULL;

	void InsertAtBeginning(T value) {
		Node* newNode = new Node();
		newNode->value = value;
		newNode->next = Head;
		newNode->prev = NULL;

		if (Head!= NULL)
		{
			Head->prev = newNode;
		}

		Head = newNode;
		_size++;
	}

	void PrintList() {
		Node* current = Head;

		while (current != NULL)
		{
			cout << current->value << " ";
			current = current->next;
		}
		cout << "\n";
	}

	Node* Find(T value) {
		Node* current = Head;

		while (current != NULL)
		{
			if (current->value == value)
			{
				return current;
			}
			current = current->next;
		}
		return NULL;
	}

	void InsertAfter(Node* current, T value) {
		Node* newNode = new Node();

		newNode->value = value;

		newNode->next = current->next;

		newNode->prev = current;

		if (current->next != NULL)
		{
			current->next->prev = newNode;

		}

		current->next = newNode;
		_size++;
	}

	bool InsertAfter(int index, T value) {
		Node* current = GetNode(index);

		if (current != NULL)
		{
			InsertAfter(current, value);
			return true;
		}

		else
		{
			return false;
		}
	}

	void InsertAtEnd(T value) {

		Node* newNode = new Node();

		newNode->value = value;

		newNode->next = NULL;

		if (Head==NULL)
		{
			newNode->prev = NULL;

			Head = newNode;
			_size++;
			
		}

		else
		{
			Node* current = Head;

			while (current->next!=NULL)
			{
				current = current->next;
			}

			current->next = newNode;

			newNode->prev = current;

			_size++;
		}
		
	}
	 
	void DeleteNode(Node*& NodeToDelete) {
		if (Head==NULL || NodeToDelete == NULL)
		{
			return;
		}

		if (Head == NodeToDelete)
		{
			Head = Head->next;
		}

		if (NodeToDelete->next != NULL)
		{
			NodeToDelete->next->prev = NodeToDelete->prev;
		}

		if (NodeToDelete->prev!= NULL)
		{
			NodeToDelete->prev->next = NodeToDelete->next;
		}

		delete NodeToDelete;
		_size--;
	}


	void DeleteFirstNode() {
		
		if (Head == NULL)
		{
			return;
		}
		Node* temp = Head;

		Head = Head->next;

		if (Head != NULL)
		{
			Head->prev = NULL;
		}

		delete temp;
		_size--;
	}

	void DeleteLastNode() {
		if (Head == NULL)
		{
			return;
		}
		
		if (Head->next == NULL)
		{
			delete Head;
			Head = NULL;
			_size--;
			return;
		}

		Node* current = Head;

		while (current->next != NULL)
		{
			current = current->next;
		}

		current->prev->next = NULL;

		delete current;
		_size--;
	}

	int size() {
		return _size;
	}

	bool IsEmpty() {
		return (_size == 0);
	}
	
	void Clear() {
		while (_size != 0)
		{
			DeleteFirstNode();
		}
	}

	void Reverse() {
		Node* current = Head;
		Node* temp = nullptr;
		while (current != nullptr)
		{
			temp = current->prev;
			current->prev = current->next;
			current->next = temp;
			current = current->prev;
		}

		if (temp != nullptr) {
			Head = temp->prev;
		}
	}

	Node* GetNode(int index) {
		int count = 0;

		if (index > _size - 1 || index < 0)
		{
			return NULL;
		}

		Node* current = Head;

		while (current!=NULL)
		{
			if (count == index)
			{
				return current;
			}
			current = current->next;
			count++;
		}
		return NULL;
	}

	T GetItem(int index) {
		Node* Item = GetNode(index);

		if (Item == NULL)
		{
			return NULL;
		}
		else
		{
			return Item->value;
		}
	}

	bool UpdateItem(int index, T value) {
		Node* NodeItem = GetNode(index);

		if (NodeItem != NULL)
		{
			NodeItem->value = value;
			return true;
		}
		else
		{
			return false;
		}
	}
};


