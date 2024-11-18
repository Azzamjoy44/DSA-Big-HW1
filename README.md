# DSA-Big-HW1
Data Structures and Algorithms Big Assignment 1, Year 1 Semester 2


# Homer Simpson Finding Program

This program consists of two parts: a template-based stack implementation named "Ethan's Stack" and a main program that uses the stack to find a person of interest, "Homer Simpson," in a series of dinner events. The file `Ethan’s Stack.h` contains the stack class declaration and definition and the file `Ethan Hunt.cpp` contains the main function and a function which prints a matrix.

## Part 1: Ethan's Stack

Ethan's Stack is a templated stack implementation, allowing you to create a stack of any data type. However, only an integer stack will be used.

### Features:
1. Dynamically sized stack
2. Methods for basic stack operations: push, pop, and peek
3. Checking if the stack is empty or full

## Part 2: Homer Finding Program

This main program uses the stack implementation to find Homer Simpson in a series of dinner events.

### Features:
1. Reads the size of an N x N matrix representing the interactions of people at dinner events
2. Inputs the matrix data for each person, indicating if they talked (1) or didn't talk (0) to another person
3. Utilizes Ethan's Stack to process the matrix and find the person of interest

### Instructions for the user:
DO NOT under any circumstances, input anything other than an integer when prompted for input by the program. If you input another data type, the program may not work correctly.

#1.# Firstly, you are asked for the size N. Input an integer greater than 1. Then an N x N matrix will begin to generate.
2. Afterwards, you will need to fill the matrix with 1s and 0s. You must do as the program says and input a 1 or 0. Keep inputting 1s and 0s until the program stops asking you to do so. The position in which you are inputting a 1 or 0 will be on the left side of the screen.
   - Please note that positions (i, j) where i = j will be automatically filled with a 0 by the program. When i ≠ j, the program will ask you to input a 1 or 0.
   - In order to make a matrix with Homer in it, before inputting any 0s and 1s, decide which row index you would like Homer to be. Once you decide the row index, you must do the following:
     - When asked to input a 1 or 0 at position (i, j) where i = row index of Homer, and j = any index, input 0.
     - When asked to input a 1 or 0 at position (i, j) where i ≠ row index of Homer, and j = row index of Homer, input 1.
     - At any other positions (i, j) which were not previously specified, you are free to input either 0 or 1, it is up to you.
3. Once you have filled the matrix, the rest is left to the program. The program will print the matrix and determine whether or not Homer Simpson is present at the dinner.
4. If Homer is not present at the dinner, you will be prompted again to input the size of a new matrix and you will need to restart from step 1.
5. If Homer is present at the dinner, the program will tell you the index of Homer, and program execution will cease.

---

# Restaurant Order Management System

This program simulates a restaurant order management system. It reads order information from a file, calculates the completion time for each order, and checks if all orders are completed within the specified maximum allowed duration. The program also determines when the chef can take breaks between orders. The program uses the standard C++ queue data structure to complete the tasks.

## Features:
1. Reads order data from a text file
2. Processes order information, including arrival time and duration
3. Calculates expected and actual completion times for each order
4. Determines when the chef can take breaks between orders
5. Checks if all orders are completed within the specified maximum allowed duration
6. Prints order and chef break information, maximum order duration, and overall completion status

## Structure:
- **Order**: Represents an individual order with arrival time and duration.
- **res**: Represents a restaurant with a queue of orders, number of orders, and the maximum allowed order duration.

### Functions:

- **input(const string& filename)**:
  Reads the input data from the provided file and stores the order information in the orders queue. It opens the specified file, reads the number of orders and maximum allowed order duration, and then reads the arrival time and duration for each order.

- **prorder()**:
  Processes each order in the queue, calculates the completion time for each order, and checks if the chef can take a break between orders. It iterates through all orders, updating the current time based on the order's arrival time and duration. The function also calculates the expected and actual completion times for each order, prints the order information, and checks if the order is completed within the maximum allowed duration.

### How to Run:
1. Create a text file named `abd.txt` in the same directory as `restaurant.cpp`.
2. Add the input data in the correct format (number of orders, time when the restaurant closes, followed by order arrival time and duration for each order) and save the file.
3. The program will read the input data from the `abd.txt` file, process the data, and display output on the screen. The output will contain:
   - Order completion times
   - Chef's break times
   - Maximum order duration
   - Completion status of all orders

### Example:

Input: `abd.txt`

5 21

1 3

3 4

10 2

11 5

18 7


Output:

Chef has a break: 0 to 1

Order 1: expected completion time = 4, actual completion time = 4;

Order 2: expected completion time = 7, actual completion time = 8;

Chef has a break: 8 to 10

Order 3: expected completion time = 12, actual completion time = 12;

Order 4: expected completion time = 16, actual completion time = 17;

Chef has a break: 17 to 18

Order 5: expected completion time = 25, actual completion time = 25;

the max duration:7 there are orders which are not completed or the chef finished them after time 21

---

# Polynomial Operations

This program demonstrates the use of various polynomial operation functions. It handles operations on both real and complex polynomials, including input, display, addition, and multiplication. The program also allows users to evaluate a real polynomial at a given value of x. The file `Polynomials.h` contains the declaration and definition of the classes and functions used. The file `Polynomials.cpp` includes the main program which uses the classes and functions declared and defined in `Polynomials.h` to show the polynomial operation functions in action. The program uses a template-based linked list to represent polynomials.

## Part 1: Polynomial and Linked List Classes

### Linked List Class Functions:
The provided functions offer the following functionality:
- **LinkedList()**: Constructor which initializes `firstPointer` and `lastPointer` to `NULL`.
- **addLast(T term)**: Adds (pushes) a node to the end of the list.
- **findFirstOccurrence(T data)**: Finds the first occurrence of given data in the linked list.

### Polynomial Class Functions:
The provided functions offer the following functionality:
- **void inputRealPolynomial()**: Input the terms for a real polynomial.
- **void inputComplexPolynomial()**: Input the terms for a complex polynomial.
- **void displayRealPolynomial()**: Display a real polynomial in human-readable format.
- **void displayComplexPolynomial()**: Display a complex polynomial in human-readable format.
- **double inputXForRealPolynomial(double x)**: Input the value of `x` to evaluate a real polynomial.
- **Polynomial addRealPolynomials(Polynomial p)**: Add two real polynomials.
- **Polynomial addComplexPolynomials(Polynomial p)**: Add two complex polynomials.
- **Polynomial multiplyRealPolynomials(Polynomial p)**: Multiply two real polynomials.

## Part 2: Main Program

### Instructions for the User:
DO NOT under any circumstances, input a letter or special character like `*`, `#`, `$`, etc.

1. **Input a Real Polynomial**:
   - The program will first ask you to input the degree of the polynomial. Input a degree greater than or equal to 0.
   - Then, you will be prompted to input the exponent and coefficient respectively for the terms of the polynomial:
     - For the exponent, input an integer greater than or equal to zero and less than or equal to the degree (`0 <= exponent <= degree`).
     - For the coefficient, input a real number (positive or negative).
     - You do not need to input every exponent.
     - You can input the terms’ exponents in any order you like.
     - You can input exponents you have already inputted previously.
   - The program will give you the option to stop inputting terms once you input a non-zero coefficient for the degree of the polynomial. You may continue to input as many terms as you want.
     - **Important**: DO NOT input the coefficients for the degree in such a way that the sum of the coefficients of the degree will equal zero. This may cause the program to function improperly. The coefficient of the degree must NOT be zero.
   - Once you finish inputting terms, the program will:
     - Add the terms with the same exponent together.
     - Sort the terms in ascending order of exponents.
     - Print the polynomial onto the screen for you to see.

2. **Input a Second Real Polynomial**:
   - Input a degree greater than or equal to zero like you did in step 1 and input the terms as in steps 2-3.

3. **Calculate Results**:
   - The program will calculate the sum and product of the two real polynomials and print the results to the screen.
   - It will then calculate the sum and product of the sum and product of the two real polynomials and print the results.

4. **Input a Complex Polynomial**:
   - Input the degree of the polynomial (integer greater than or equal to zero).
   - Then input the exponent and complex coefficient (real and imaginary parts) for each term:
     - For the exponent, input an integer greater than or equal to zero and less than or equal to the degree (`0 <= exponent <= degree`).
     - For the complex coefficient:
       - Input a real number for the real part (positive or negative).
       - Input a real number for the imaginary part (positive or negative).
     - You do not need to input every exponent.
     - You can input the terms’ exponents in any order you like.
     - You can input exponents you have already inputted previously.
   - The program will give you the option to stop inputting terms once you input a non-zero coefficient for the degree of the polynomial. You may continue to input as many terms as you want.
     - **Important**: DO NOT input the coefficients for the degree in such a way that the sum of the coefficients of the degree will equal zero. This may cause the program to function improperly. The coefficient of the degree must NOT be zero.
   - Once you finish inputting terms, the program will:
     - Add the terms with the same exponent together.
     - Sort the terms in ascending order of exponents.
     - Print the polynomial onto the screen for you to see.

5. **Input a Second Complex Polynomial**:
   - Input a degree greater than or equal to zero like you did in step 4 and input the terms as in steps 7-8.

6. **Calculate Results for Complex Polynomials**:
   - The program will calculate the sum of the two complex polynomials you inputted and print the result to the screen.
   - It will then calculate the sum of the first complex polynomial and the previous sum polynomial and print the result to the screen.

---

**Note**: After completing the above steps for both real and complex polynomials, program execution will stop.
