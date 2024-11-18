// Ethan Hunt.cpp

#include <iostream>
#include "Ethan's Stack.h"

using namespace std;

//Function to print the matrix
void printMatrix(int** matrix, int size) {
	for (int index1 = 0; index1 < size; index1++) {
		std::cout << "Index " << index1 << ": ";
		for (int index2 = 0; index2 < size; index2++) {
			std::cout << matrix[index1][index2] << " ";
		}
		cout << "\n";
	}
}

int main()
{

	bool foundHomer = false;
	//We keep creating events until Homer is found
	while (!foundHomer) {

		int size;
		cout << "What is the size of the N*N matrix?: ";
		cin >> size;

		//We ensure the size of the matrix is greater than 1
		while (size <= 1) {
			cout << "Please input a number greater than 1 for the size of the N*N matrix?: ";
			cin >> size;
		}
		int** matrix = new int* [size]; //We create an array of int pointers

		//We then make each of the pointers in the pointer array, point to a seperate integer array
		//Effectively making a matrix
		for (int i = 0; i < size; i++) {
			matrix[i] = new int[size];
		}

		//We fill the matrix with data (0s and 1s)
		int talked;
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				//We ensure that a person does not talk to themselves
				if (i != j) {
					cout << "[" << i << ", " << j << "];  " << "Input a 1 or 0 (no other integer or data type): ";
					cin >> talked;

					//We ensure that only 0s and 1s are inputted into the matrix
					while (talked != 0 && talked != 1) {
						cout << "[" << i << ", " << j << "];  " << "Please input a 1 or 0 (no other integer or data type): ";
						cin >> talked;
					}
					matrix[i][j] = talked;
				}
				//We ensure that a person does not talk to themselves
				else {
					matrix[i][j] = 0;
					cout << "[" << i << ", " << j << "] = 0\n";
				}
			}
			cout << "\n";
		}
		cout << "--------------------------------\n\n";

		printMatrix(matrix, size);
		cout << "\n";

		//We initialize Ethan's Stack and push everyone at the dinner onto the stack
		Stack<int> ethansStack(size);
		for (int i = 0; i < size; i++) {
			ethansStack.push(i);
		}

		int person1; //Index of person 1
		int person2; //Index of person 2

		//We loop until the stack is empty or until Homer has been found
		while (!ethansStack.isEmpty() && !foundHomer) {
			person1 = ethansStack.pop();
			person2 = ethansStack.pop();

			//We do not want to compare a person with themselves
			if (person1 != person2) {

				if (matrix[person1][person2] == 1 && matrix[person2][person1] == 0) {
					ethansStack.push(person2);
				}
				else if (matrix[person1][person2] == 0 && matrix[person2][person1] == 1) {
					ethansStack.push(person1);
				}
				//else {both people remain popped out}
				//Because if both talked, then both cannot be the target
				/*If no-one talked, then none of the people can be the target because
				the target must be talked to by someone*/

				//If there is one person left in the stack
				if (ethansStack.getTopPointer() == 0) {

					/*We will check if everyone has talked with the one person left in the stack
					who is POTENTIALLY Homer Simpson and we will check if this person has not talked
					with anyone else*/
					bool rowEmpty = true, columnFull = true;
					int potentialTarget = ethansStack.peek();

					//We first check if the potential target has talked with no-one
					for (int index = 0; index < size; index++) {
						if (matrix[potentialTarget][index] == 1) {
							rowEmpty = false;
						}
					}

					/*If the potential target has talked with no-one,
					we check if everyone has talked to the potential target*/
					if (rowEmpty) {
						for (int index = 0; index < size; index++) {
							if (index != potentialTarget) { //We do not compare the potential target with themselves
								if (matrix[index][potentialTarget] == 0) {
									columnFull = false;
								}
							}
						}
					}

					//If everyone talked to the potential target and
					//the potential target talked to no-one,
					//The person of interest is Homer Simpson
					if (rowEmpty && columnFull) {
						foundHomer = true;
						cout << "Homer Simpson is the person with index " << potentialTarget << "\n";
					}
					//Otherwise the person is not Homer Simpson
					else {
						cout << "Homer Simpson is not at this dinner, you must arrange a new dinner :\n\n";
					}
				}

				// If the stack is empty, Homer is not at the dinner
				else if (ethansStack.isEmpty()) {
					cout << "Homer Simpson is not at this dinner, you must arrange a new dinner :\n\n";
				}
			}
		}
	}
}
