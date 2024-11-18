//Ethan's Stack.h

#pragma once
#include <iostream>

template<class T>
class Stack {
	int size;
	T* stackArray;
	int topPointer;

public:
	Stack(int stackSize) {
		topPointer = -1;
		size = stackSize;
		stackArray = new int[size];
	}

	int getTopPointer() {
		return topPointer;
	}

	bool isEmpty() {
		return (topPointer == -1);
	}

	bool isFull() {
		return (topPointer == size - 1);
	}

	void push(T x) {
		if (isFull()) {
			std::cout << "Error 101: the stack is full, cannot push.\n";
		}
		else {
			stackArray[++topPointer] = x;
		}
	}

	T pop() {
		if (isEmpty()) {
			return stackArray[0];
		}

		return stackArray[topPointer--];

	}

	T peek() {
		if (isEmpty()) {
			std::cout << "Error 103: the stack is empty, cannot peek.\n";
			return stackArray[0];
		}
		return stackArray[topPointer];
	}
};