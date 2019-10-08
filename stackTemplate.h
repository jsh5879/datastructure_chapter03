#pragma once
#include <iostream>


template <class T>
class Stack {

public:
	Stack(int MaxStackSize = DefaultSize);
	Boolean IsFull();
	void Add(const T& item);
	Boolean IsEmpty();
	T* Delete(T&);

	void StackEmpty() { cout << "empty" << endl; };
	void StackFull() { cout << "full" << endl; };

	template <class T>
	friend ostream& operator<<(ostream& os, const Stack<T>& s);

	template <class T>
	friend ostream& operator<<(ostream& os, items& item);

private:
	int top; //current element index, begin with 0
	T* stack;
	int MaxSize;//capacity of the stack
};