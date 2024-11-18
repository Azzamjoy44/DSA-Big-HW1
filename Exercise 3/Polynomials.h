//Polynomials.h

#pragma once
#include <iostream>
#include <cmath>
using namespace std;

//Struct for a complex number
struct complex {
	double re; //Real part of the complex number
	double im; //Imaginary part of the complex number
};

//Struct for a term in a polynomial
struct term {
	double coeff; //The (real) coefficient (this field is used when dealing with real polynomials)
	int exp; //The exponent
	complex complexCoeff; //The complex coefficient (this field is used when dealing with complex polynomials)
};

//Struct for a generic node of a linked list
template<typename T>
struct node {
	T info;
	node<T>* nextPointer, * previousPointer;
};

//Linked List
template<typename T>
class LinkedList {

public:

	node<T>* firstPointer, * lastPointer;

	LinkedList() {
		firstPointer = lastPointer = NULL;
	}

	void addLast(T term) {
		node<T>* auxiliaryPointer = new node<T>;

		auxiliaryPointer->info = term;
		auxiliaryPointer->nextPointer = NULL;
		auxiliaryPointer->previousPointer = lastPointer;

		if (lastPointer != NULL) {
			lastPointer->nextPointer = auxiliaryPointer;
		}
		lastPointer = auxiliaryPointer;

		if (firstPointer == NULL) {
			firstPointer = lastPointer;
		}
	}

	bool findFirstOccurence(T data) {
		node<T>* auxiliaryPointer = firstPointer;

		while (auxiliaryPointer != NULL) {
			if (auxiliaryPointer->info == data) {
				return true;
			}
			auxiliaryPointer = auxiliaryPointer->nextPointer;
		}

		return false;
	}

};

//Class for a Polynomial
class Polynomial {
private:

	//Polynomial is represented using a linked list
	LinkedList<term> terms;

	//Used to find the next non-zero term in a polynomial
	//There is no need for this function to be publicly accessible, so it is private
	double findNextNonZeroCoeff(node<term>* pointer) { //The pointer to a term is passed
		node<term>* auxPointer = pointer->nextPointer; //auxPointer will point to the next term
		double nextTermCoeff = auxPointer->info.coeff;//nextTermCoeff will store the next term's coefficient
		while (true) {
			if (nextTermCoeff != 0) {
				return nextTermCoeff; //if the next term coefficient in not zero, return it
			}

			//Otherwise we move onto the next term
			auxPointer = auxPointer->nextPointer;
			nextTermCoeff = auxPointer->info.coeff;
		}
	}

public:

	//This function is used to input a real polynomial
	void inputRealPolynomial() {

		//Inputting terms into the polynomial

		cout << "Real Polynomial :\n";
		int degree; //Degree of the polynomial
		double coeff; 
		int exp; 
		char cont = 'y'; //Will be used to check if the user wants to keep adding more terms to the polynomial
		bool degreeReached = false; //Will be used to check if the degree of the polynomial has been reached whilst the user is inputting terms
		term newTerm;
		Polynomial poly; //We will intially store the terms in this auxiliary real polynomial

		cout << "Input the degree of the polynomial : ";
		cin >> degree;
		cout << "\n";

		//Ensure that the degree is greater than or equal to zero
		while (degree < 0) {
			cout << "Input a degree which meets the following criteria ; deg >= 0 : ";
			cin >> degree;
		}

		//We loop while the user still wants to input terms (However, the user cannot REALLY stop WHENEVER they want)
		while (cont != 'n') {
			cout << "Input the exponent of the term : ";
			cin >> exp;

			//Ensure that the exponent is greater than or equal to zero and less than or equal to the degree
			while (exp > degree || exp < 0) {
				cout << "Please input an exponent which meets the following criteria ; 0 <= exp <= deg : ";
				cin >> exp;
			}

			cout << "Input the coefficient of the term : ";
			cin >> coeff;

			//Ensure that coefficient is not zero for the degree
			while ((exp == degree && coeff == 0) && (!degreeReached)) {
				cout << "For degree " << degree << ", the coefficient cannot be zero!\n";
				cout << "Input the coefficient of the term : ";
				cin >> coeff;
			}

			//If the user has inputted a non-zero term for the degree, the degree has been reached
			if (exp == degree) {
				degreeReached = true;
			}

			//We add the term to the end of the auxiliary polynomial 'poly'
			newTerm.coeff = coeff;
			newTerm.exp = exp;
			poly.terms.addLast(newTerm);
			cout << "\n";

			/*If the degree has been reached, the user is given the
			option of whether or not they want to add more terms to the polynomial*/
			if (degreeReached) {
				do
				{
					cout << "Do you want to input more terms? ('y' or 'n'): ";
					cin >> cont;
				} while (cont != 'y' && cont != 'n');
			}

		}

		// Now we will add together terms which have the same exponent as each other

		node<term>* pointer1 = poly.terms.firstPointer; //We start by adding terms which have the same exponent as the first term
		node<term>* pointer2 = pointer1; //We initialize this pointer to point to the first term
		LinkedList<int> expList; //We will use this list to check if we have already added together the terms with the exponent we are looking at right now
		bool foundExp = false;

		//We will loop until we reach the end of the auxiliary polynomial 'poly'
		while (pointer1 != NULL) {
			term newTerm2;
			newTerm2.exp = pointer1->info.exp;
			newTerm2.coeff = pointer1->info.coeff;
			pointer1->info.coeff = 0; //Terms we consider will have their coefficient replaced with zero so that we do not consider them again
			//We will compare all the terms in 'poly' with the term pointed to by pointer1 and add the terms if necessary
			while (pointer2 != NULL) {
				/*If the two pointers are not pointing to the same term and the exponents of the two terms are equal,
				and the coefficient of the term pointed to by pointer2 is not zero, we add the two terms*/ 
				if ((pointer1->info.exp == pointer2->info.exp && pointer1 != pointer2) && (pointer2->info.coeff != 0)) {
					newTerm2.coeff += pointer2->info.coeff;
					pointer2->info.coeff = 0; //Terms we consider will have their coefficient replaced with zero so that we do not consider them again
				}
				//After comparing and/or adding pointer1's and pointer2's terms, we move onto comparing other terms with pointer1's term 
				pointer2 = pointer2->nextPointer;
			}

			
			//We do not want multiple terms with the same exponent in our main polynomial
			//So we check if we already added a term with the same exponent as the term we have right now, to the main polynomial
			foundExp = expList.findFirstOccurence(newTerm2.exp);

			//If we didn't add a term with this exponent to our main polynomial, we add this term to the main polynomial
			if (!foundExp) {
				expList.addLast(newTerm2.exp); //We mark this exponent as 'added'
				terms.addLast(newTerm2); //We add the term to the main polynomial
			}

			pointer1 = pointer1->nextPointer; //We will now add together terms which have the same exponent as the next term
			pointer2 = poly.terms.firstPointer; //We make it point to the first term again
		}

		/*We augment the polynomial by introducing terms with previously unconsidered
		exponents and assigning a coefficient value of zero to them*/
		node<int>* expListPointer = expList.firstPointer;
		for (int i = 0; i < degree; i++) {
			foundExp = expList.findFirstOccurence(i);
			if (!foundExp) {
				int exp = i;
				term zeroTerm;
				zeroTerm.coeff = 0;
				zeroTerm.exp = i;
				terms.addLast(zeroTerm);
				expList.addLast(i);
			}
		}
		

		//Sorting terms in ascending order of exponents using bubble sort
		bool swap = true;
		node<term>* upperBound = terms.lastPointer;
		node<term>* pointer3;

		while (swap) {
			swap = false;
			pointer3 = terms.firstPointer;
			while (pointer3 != upperBound) {
				if (pointer3->info.exp > pointer3->nextPointer->info.exp) {
					term temp = pointer3->info;
					pointer3->info = pointer3->nextPointer->info;
					pointer3->nextPointer->info = temp;
					swap = true;
				}
				pointer3 = pointer3->nextPointer;
			}
			upperBound = upperBound->previousPointer;
		}
	}


	//This function is used to input complex polynomials
	void inputComplexPolynomial() {

		//Inputting terms into the polynomial
		cout << "Complex Polynomial :\n";
		int degree;
		complex complexCoeff;
		int exp;
		char cont = 'y';
		bool degreeReached = false;
		term newComplexTerm;
		Polynomial complexPoly; //Auxiliary Complex Polynomial
		cout << "Input the degree of the polynomial : ";
		cin >> degree;
		cout << "\n";

		//Ensure that the degree is greater than or equal to zero
		while (degree < 0) {
			cout << "Input a degree which meets the following criteria ;  deg >= 0 : ";
			cin >> degree;
		}

		while (cont != 'n') {
			cout << "Input the exponenent of the term : ";
			cin >> exp;

			while (exp > degree || exp < 0) {
				cout << "Please input an exponent which meets the following criteria ; 0 <= exp <= deg : ";
				cin >> exp;
			}

			cout << "Input the real part of the coefficient: ";
			cin >> complexCoeff.re;
			cout << "Input the imaginary part of the coefficient: ";
			cin >> complexCoeff.im;

			//Ensure that the coefficient of the degree is not zero
			while ((exp == degree) && (complexCoeff.re == 0 && complexCoeff.im == 0) && (!degreeReached)) {
				cout << "For degree " << degree << "the coefficient cannot be zero!\n";
				cout << "Input the real part of the coefficient : ";
				cin >> complexCoeff.re;
				cout << "Input the imaginary part of the complex number : ";
				cin >> complexCoeff.im;
			}

			//We check if degree has been reached
			if (exp == degree) {
				degreeReached = true;
			}

			//The terms are added to the back of the auxiliary complex polynomial
			newComplexTerm.complexCoeff = complexCoeff;
			newComplexTerm.exp = exp;
			complexPoly.terms.addLast(newComplexTerm);
			cout << "\n";

			//If degree has been reached the user can stop adding terms
			if (degreeReached) {
				do
				{
					cout << "Do you want to input more terms? ('y' or 'n'): ";
					cin >> cont;
				} while (cont != 'y' && cont != 'n');
			}

		}

		//Now we add together terms which have the same exponent as each other

		node<term>* pointer1 = complexPoly.terms.firstPointer; //We start by adding terms which have the same exponent as the first term
		node<term>* pointer2 = pointer1; //We initialize pointer2 to point to the first term
		LinkedList<int> expList; //We use this list to keep track of the terms with exponents which we already considered
		bool foundExp = false;
		while (pointer1 != NULL) {
			term newTerm2;
			newTerm2.exp = pointer1->info.exp;
			newTerm2.complexCoeff = pointer1->info.complexCoeff;
			pointer1->info.complexCoeff.re = 0; //We make the coefficient of considered terms equal to zero
			pointer1->info.complexCoeff.im = 0; //We make the coefficient of considered terms equal to zero
			while (pointer2 != NULL) {
				/*If the two pointers are not pointing to the same term and the exponents of the two terms are equal,
				and the coefficient of the term pointed to by pointer2 is not zero, we add the two terms*/
				if ((pointer1->info.exp == pointer2->info.exp && pointer1 != pointer2) && (pointer2->info.complexCoeff.re != 0 || pointer2->info.complexCoeff.im != 0)) {
					newTerm2.complexCoeff.re += pointer2->info.complexCoeff.re;
					newTerm2.complexCoeff.im += pointer2->info.complexCoeff.im;
					pointer2->info.complexCoeff.re = 0; //We make the coefficient of considered terms equal to zero
					pointer2->info.complexCoeff.im = 0; //We make the coefficient of considered terms equal to zero
				}
				//We compare the term at pointer1 with all the other terms in the polynomial and add if necessary
				pointer2 = pointer2->nextPointer;
			}

			//We do not want multiple terms with the same exponent in our main polynomial
			//So we check if we already added a term with the same exponent as the term we have right now, to the main polynomial
			foundExp = expList.findFirstOccurence(newTerm2.exp);

			//If we have not considered this exponent, we add the exponent to the main polynomial
			if (!foundExp) {
				expList.addLast(newTerm2.exp); //We mark the exponent as visited
				terms.addLast(newTerm2);
			}

			pointer1 = pointer1->nextPointer; //We now consider terms with the same exponent as the next term
			pointer2 = complexPoly.terms.firstPointer; //We make pointer2 equal to the first term to restart the adding process, but this time, with the new term pointed to by pointer1
		}

		/*We augment the polynomial by introducing terms with previously unconsidered
		exponents and assigning a coefficient value of zero to them*/
		node<int>* expListPointer = expList.firstPointer;
		for (int i = 0; i < degree; i++) {
			foundExp = expList.findFirstOccurence(i);
			if (!foundExp) {
				int exp = i;
				term zeroTerm;
				zeroTerm.complexCoeff.re = 0;
				zeroTerm.complexCoeff.im = 0;
				zeroTerm.exp = i;
				terms.addLast(zeroTerm);
				expList.addLast(i);
			}
		}

		//Sorting terms in ascending order of exponents using bubble sort
		bool swap = true;
		node<term>* upperBound = terms.lastPointer;
		node<term>* pointer3;

		while (swap) {
			swap = false;
			pointer3 = terms.firstPointer;
			while (pointer3 != upperBound) {
				if (pointer3->info.exp > pointer3->nextPointer->info.exp) {
					term temp = pointer3->info;
					pointer3->info = pointer3->nextPointer->info;
					pointer3->nextPointer->info = temp;
					swap = true;
				}
				pointer3 = pointer3->nextPointer;
			}
			upperBound = upperBound->previousPointer;
		}

	}

	//This function is used to print real polynomials
	void displayRealPolynomial() {
		node<term>* pointer = terms.firstPointer; //This pointer is used to access all the terms of the polynomial

		while (pointer != NULL) {
			if (pointer != terms.lastPointer) {
				if (pointer->info.exp != 0) {
					if (pointer->info.exp == 1) {
						/*If current term is not the last term and 
						the exponent of the current term is not 0 and is equal to 1, this part of the code is run*/

						/*We check if the coefficent is zero to ensure we do not print terms
						which have zero as their coefficient*/
						if (pointer->info.coeff != 0) {

							/*After printing the current term, we will determine whether or not to print '+' afterwards
							by checking the sign of the next non-zero coefficient*/
							/*If the next non-zero coefficient is negative, we will not print '+' and 
							the '-' sign will print on its own when the next term's coefficient is printed*/
							//Otherwise we will print '+' after printing the current term
							double nextNonZeroCoeff = findNextNonZeroCoeff(pointer);

							//We will also determine whether or not to print the coefficient of the term
							//If the coefficient is 1 or -1, we will not print '1'

							if (nextNonZeroCoeff < 0) {
								if (pointer->info.coeff == 1) {
									cout << "x";
								}
								else if (pointer->info.coeff == -1) {
									cout << "-x";
								}
								else {
									cout << pointer->info.coeff << "x";
								}
							}
							else {
								if (pointer->info.coeff == 1) {
									cout << "x" << "+";
									cout << pointer->info.coeff << "x" << "+";
								}
								else if (pointer->info.coeff == -1) {
									cout << "-x" << "+";
								}
								else {
									cout << pointer->info.coeff << "x" << "+";
								}
							}
						}
					}
					else {
						/*If the current term is not the last term of the polynomial and
						the exponent of the current term is not 0 and not 1, this part of the code is run*/

						/*We check if the coefficent is zero to ensure we do not print terms
						which have zero as their coefficient*/
						if (pointer->info.coeff != 0) {

							/*After printing the current term, we will determine whether or not to print '+' afterwards
							by checking the sign of the next non-zero coefficient*/
							/*If the next non-zero coefficient is negative, we will not print '+' and
							the '-' sign will print on its own when the next term's coefficient is printed*/
							//Otherwise we will print '+' after printing the current term
							double nextNonZeroCoeff = findNextNonZeroCoeff(pointer);

							//We will also determine whether or not to print the coefficient of the term
							//If the coefficient is 1 or -1, we will not print '1'

							if (nextNonZeroCoeff < 0) {
								if (pointer->info.coeff == 1) {
									cout << "x^" << pointer->info.exp;
								}
								else if (pointer->info.coeff == -1) {
									cout << "-x^" << pointer->info.exp;
								}
								else {
									cout << pointer->info.coeff << "x^" << pointer->info.exp;
								}
							}
							else {
								if (pointer->info.coeff == 1) {
									cout << "x^" << pointer->info.exp << "+";
								}
								else if (pointer->info.coeff == -1) {
									cout << "-x^" << pointer->info.exp << "+";
								}
								else {
									cout << pointer->info.coeff << "x^" << pointer->info.exp << "+";
								}
							}
						}
					}
				}
				else {
					/*If the current term is not the last term of the polynomial and
					the exponent of the current term is 0, this part of the code is run*/

					/*We check if the coefficent is zero to ensure we do not print terms
					which have zero as their coefficient*/
					if (pointer->info.coeff != 0) {

						/*After printing the current term, we will determine whether or not to print '+' afterwards
						by checking the sign of the next non-zero coefficient*/
						/*If the next non-zero coefficient is negative, we will not print '+' and
						the '-' sign will print on its own when the next term's coefficient is printed*/
						//Otherwise we will print '+' after printing the current term
						double nextNonZeroCoeff = findNextNonZeroCoeff(pointer);

						//We always print the coefficient

						if (nextNonZeroCoeff < 0) {
							cout << pointer->info.coeff;
						}
						else {
							cout << pointer->info.coeff << "+";
						}
					}
				}
			}
			else {
				//If the current term is the last term, this part of the code is run


				if (pointer->info.exp == 0) {
					cout << pointer->info.coeff;
				}
				else if (pointer->info.exp == 1){
					if (pointer->info.coeff == 1) {
						cout << "x";
					}
					else if (pointer->info.coeff == -1) {
						cout << "-x";
					}
					else {
						cout << pointer->info.coeff << "x";
					}
				}
				else {
					if (pointer->info.coeff == 1) {
						cout << "x^" << pointer->info.exp;
					}
					else if (pointer->info.coeff == -1) {
						cout << "-x^" << pointer->info.exp;
					}
					else {
						cout << pointer->info.coeff << "x^" << pointer->info.exp;
					}
				}
			}

			//We move onto printing the next term
			pointer = pointer->nextPointer;
		}
		cout << "\n";
	}


	void displayComplexPolynomial() {
		node<term>* pointer = terms.firstPointer;

		while (pointer != NULL) {
			if (pointer != terms.lastPointer) {
				if (pointer->info.exp != 0) {
					if (pointer->info.exp == 1) {
						/*If current term is not the last term and
						the exponent of the current term is not 0 and is equal to 1, this part of the code is run*/

						/*We check if the coefficent is zero to ensure we do not print terms
						which have zero as their coefficient*/
						if (pointer->info.complexCoeff.re != 0 || pointer->info.complexCoeff.im != 0) {

							//We check if the imaginary part of the coefficient is -1 or 1
							//because we do not want to print '1' next to 'i'
							if (pointer->info.complexCoeff.im < 0) {
								if (pointer->info.complexCoeff.im == -1) {
									cout << "(" << pointer->info.complexCoeff.re << "-i)x" << " + ";
								}
								else {
									cout << "(" << pointer->info.complexCoeff.re << pointer->info.complexCoeff.im << "i)x" << " + ";
								}
							}
							else {
								if (pointer->info.complexCoeff.im == 1) {
									cout << "(" << pointer->info.complexCoeff.re << "+i)x" << " + ";
								}
								else {
									cout << "(" << pointer->info.complexCoeff.re << "+" << pointer->info.complexCoeff.im << "i)x" << " + ";
								}
							}
						}
					}
					else {
						/*If the current term is not the last term of the polynomial and
						the exponent of the current term is not 0 and not 1, this part of the code is run*/

						/*We check if the coefficent is zero to ensure we do not print terms
						which have zero as their coefficient*/
						if (pointer->info.complexCoeff.re != 0 || pointer->info.complexCoeff.im != 0) {

							//We check if the imaginary part of the coefficient is -1 or 1
							//because we do not want to print '1' next to 'i'
							if (pointer->info.complexCoeff.im < 0) {
								if (pointer->info.complexCoeff.im == -1) {
									cout << "(" << pointer->info.complexCoeff.re << "-i)x^" << pointer->info.exp << " + ";
								}
								else {
									cout << "(" << pointer->info.complexCoeff.re << pointer->info.complexCoeff.im << "i)x^" << pointer->info.exp << " + ";
								}
							}
							else {
								if (pointer->info.complexCoeff.im == 1) {
									cout << "(" << pointer->info.complexCoeff.re << "+i)x^" << pointer->info.exp << " + ";
								}
								else {
									cout << "(" << pointer->info.complexCoeff.re << "+" << pointer->info.complexCoeff.im << "i)x^" << pointer->info.exp << " + ";
								}
							}
						}
					}
				}
				else {
					/*If the current term is not the last term of the polynomial and
					the exponent of the current term is 0, this part of the code is run*/

					/*We check if the coefficent is zero to ensure we do not print terms
					which have zero as their coefficient*/
					if (pointer->info.complexCoeff.re != 0 || pointer->info.complexCoeff.im != 0) {

						//We check if the imaginary part of the coefficient is -1 or 1
						//because we do not want to print '1' next to 'i'
						if (pointer->info.complexCoeff.im < 0) {
							if (pointer->info.complexCoeff.im == -1) {
								cout << "(" << pointer->info.complexCoeff.re << "-i)" << " + ";
							}
							else {
								cout << "(" << pointer->info.complexCoeff.re << pointer->info.complexCoeff.im << "i)" << " + ";
							}
						}
						else {
							if (pointer->info.complexCoeff.im == 1) {
								cout << "(" << pointer->info.complexCoeff.re << "+i)" << " + ";
							}
							else {
								cout << "(" << pointer->info.complexCoeff.re << "+" << pointer->info.complexCoeff.im << "i)" << " + ";
							}
						}
					}
				}
			}
			else {
				//If the current term is the last term, this part of the code is run

				if (pointer->info.exp == 0) {

					//We check if the imaginary part of the coefficient is -1 or 1
					//because we do not want to print '1' next to 'i'
					if (pointer->info.complexCoeff.im < 0) {
						if (pointer->info.complexCoeff.im == -1) {
							cout << "(" << pointer->info.complexCoeff.re << "-i)";
						}
						else {
							cout << "(" << pointer->info.complexCoeff.re << pointer->info.complexCoeff.im << "i)";
						}
					}
					else {
						if (pointer->info.complexCoeff.im == 1) {
							cout << "(" << pointer->info.complexCoeff.re << "+i)";
						}
						else {
							cout << "(" << pointer->info.complexCoeff.re << "+" << pointer->info.complexCoeff.im << "i)";
						}
					}
				}
				else if (pointer->info.exp == 1) {

					//We check if the imaginary part of the coefficient is -1 or 1
					//because we do not want to print '1' next to 'i'
					if (pointer->info.complexCoeff.im < 0) {
						if (pointer->info.complexCoeff.im == -1) {
							cout << "(" << pointer->info.complexCoeff.re << "-i)x";
						}
						else {
							cout << "(" << pointer->info.complexCoeff.re << pointer->info.complexCoeff.im << "i)x";
						}
					}
					else {
						if (pointer->info.complexCoeff.im == 1) {
							cout << "(" << pointer->info.complexCoeff.re << "+i)x";
						}
						else {
							cout << "(" << pointer->info.complexCoeff.re << "+" << pointer->info.complexCoeff.im << "i)x";
						}
					}
				}
				else {

					//We check if the imaginary part of the coefficient is -1 or 1
					//because we do not want to print '1' next to 'i'
					if (pointer->info.complexCoeff.im < 0) {
						if (pointer->info.complexCoeff.im == -1) {
							cout << "(" << pointer->info.complexCoeff.re << "-i)x^" << pointer->info.exp;
						}
						else {
							cout << "(" << pointer->info.complexCoeff.re << pointer->info.complexCoeff.im << "i)x^" << pointer->info.exp;
						}
					}
					else {
						if (pointer->info.complexCoeff.im == 1) {
							cout << "(" << pointer->info.complexCoeff.re << "+i)x^" << pointer->info.exp;
						}
						else {
							cout << "(" << pointer->info.complexCoeff.re << "+" << pointer->info.complexCoeff.im << "i)x^" << pointer->info.exp;
						}
					}
				}
			}

			//We move onto printing the next term
			pointer = pointer->nextPointer;
		}
		cout << "\n";
	}


	//This function is used to calculate the value of a real polynomial for a given value X 
	double inputXForRealPolynomial(double x) {
		node<term>* pointer = terms.firstPointer; //This pointer is used to access all the terms in the polynomial
		double sum = 0; //The polynomial is a sum of terms. The sum is initially 0

		//We loop until we reach the end of the polynomial
		while (pointer != NULL) {
			sum += pointer->info.coeff * pow(x, pointer->info.exp); //First we multiply the coefficient with X raised to the exponent and then add the product to the sum
			pointer = pointer->nextPointer; //We move onto the next term
		}
		return sum; //We return the value of the polynomial for the given value X
	}

	//This function is used to add two real polynomials
	Polynomial addRealPolynomials(Polynomial p) {

		Polynomial result; //real polynomial which will be returned as the answer
		node<term>* pointer1 = terms.firstPointer; //This pointer is used to access the main polynomial's terms
		node<term>* pointer2 = p.terms.firstPointer; //This pointer is used to access the terms of the polynomial 'p' which is being added to the main polynomial

		//We loop until we reach the end of either the main polynomial or polynomial 'p'
		while (pointer1 != NULL && pointer2 != NULL) {

			//No need to check if the exponents of the two terms are equal
			/*The polynomials are ordered in ascending order of exponenents and terms with every exponent up till 
			the degree of the respective polynomial exist in that polynomial (including terms with coefficient 0)*/

			//We make a new term
			//The new term is assigned the sum of the two terms being looked at
			//Then the new term is added to the back of the result polynomial
			term newTerm;
			newTerm.coeff = pointer1->info.coeff + pointer2->info.coeff;
			newTerm.exp = pointer1->info.exp;
			result.terms.addLast(newTerm);

			pointer1 = pointer1->nextPointer;
			pointer2 = pointer2->nextPointer;
		}

		//If we reached the end of polynomial 'p' we simply add the terms of the main polynomial to the result polynomial
		while (pointer1 != NULL) {
			result.terms.addLast(pointer1->info);
			pointer1 = pointer1->nextPointer;
		}

		//If we reached the end of the main polynomial we simply add the terms of polynomial 'p' to the result polynomial
		while (pointer2 != NULL) {
			result.terms.addLast(pointer2->info);
			pointer2 = pointer2->nextPointer;

		}
		return result; //We return the result polynomial
	}

	//This function is used to add two complex polynomials
	Polynomial addComplexPolynomials(Polynomial p) {

		Polynomial complexResult; //Complex polynomial which will be returned as the answer
		node<term>* pointer1 = terms.firstPointer; //This pointer is used to access the main polynomial's terms
		node<term>* pointer2 = p.terms.firstPointer; //This pointer is used to access the terms of the polynomial 'p' which is being added to the main polynomial
		while (pointer1 != NULL && pointer2 != NULL) {

			//No need to check if the exponents of the two terms are equal
			/*The polynomials are ordered in ascending order of exponenents and terms with every exponent up till
			the degree of the respective polynomial exist in that polynomial (including terms with coefficient 0)*/

			//We make a new complex term
			//The new complex term is assigned the sum of the two terms being looked at
			//Then the new term is added to the back of the complex result polynomial
			term newComplexTerm;
			newComplexTerm.complexCoeff.re = pointer1->info.complexCoeff.re + pointer2->info.complexCoeff.re;
			newComplexTerm.complexCoeff.im = pointer1->info.complexCoeff.im + pointer2->info.complexCoeff.im;
			newComplexTerm.exp = pointer1->info.exp;
			complexResult.terms.addLast(newComplexTerm);

			pointer1 = pointer1->nextPointer;
			pointer2 = pointer2->nextPointer;
		}

		//If we reached the end of polynomial 'p' we simply add the terms of the main polynomial to the result polynomial
		while (pointer1 != NULL) {
			complexResult.terms.addLast(pointer1->info);
			pointer1 = pointer1->nextPointer;
		}

		//If we reached the end of the main polynomial we simply add the terms of polynomial 'p' to the result polynomial
		while (pointer2 != NULL) {
			complexResult.terms.addLast(pointer2->info);
			pointer2 = pointer2->nextPointer;

		}
		return complexResult; //We return the complex result polynomial
	}

	//This polynomial is used to multiply two real polynomials
	Polynomial multiplyRealPolynomials(Polynomial p) {

		//Multiplying the polynomials

		Polynomial result; //Auxiliary real polynomial
		node<term>* pointer1 = terms.firstPointer; //Used to traverse the main polynomial

		/*We multiply every term in the main polynomial with every term in polynomial 'p' and
		the product is added to the back of the auxiliary result polynomial*/
		while (pointer1 != NULL) {
			node<term>* pointer2 = p.terms.firstPointer; //Used to traverse polynomial 'p'
			while (pointer2 != NULL) {

				//We make a new term
				//The product of the two terms is stored in this new term
				//The new term is added to the back of the auxiliary result polynomial
				term newTerm;
				newTerm.coeff = pointer1->info.coeff * pointer2->info.coeff; 
				newTerm.exp = pointer1->info.exp + pointer2->info.exp;
				result.terms.addLast(newTerm);

				pointer2 = pointer2->nextPointer; //We multiply the next term in polynomial 'p' with the same term in the main polynomial
			}
			pointer1 = pointer1->nextPointer; //We move onto multiplying the next term in the main polynomial with every term in polynomial 'p'
		}

		//Adding together terms which have the same exponent as each other

		pointer1 = result.terms.firstPointer; //Now pointer1 is used to traverse through the auxiliary result polynomial
		node<term>* pointer2 = pointer1; //We initialize pointer2 to point to the first term of the auxiliary result polynomial
		Polynomial finalResult; //We make a final result polynomial which is the polynomial which will be returned as the answer
		int expCount = 0; //We keep track of exponents we have considered
		
		//We loop through the auxiliary polynomial
		while (pointer1 != NULL) {
			term newTerm2;
			newTerm2.exp = pointer1->info.exp;
			newTerm2.coeff = pointer1->info.coeff;
			pointer1->info.coeff = 0; //Term we have considered have their coefficient replaced with zero
			while (pointer2 != NULL) {
				if ((pointer1->info.exp == pointer2->info.exp && pointer1 != pointer2) && (pointer2->info.coeff != 0)) {
					newTerm2.coeff += pointer2->info.coeff;
					pointer2->info.coeff = 0;
				}
				pointer2 = pointer2->nextPointer;
			}

			//We do not want multiple terms with the same exponent in our main polynomial
			//So we check if we already added a term with the same exponent as the term we have right now, to the main polynomial
			/*The auxiliary polynomial is ordered in ascending order of exponents and terms with every exponent up till
			the degree of the respective polynomial exist in that polynomial (including terms with coefficient 0)*/
			if (newTerm2.exp >= expCount) {
				finalResult.terms.addLast(newTerm2);
				expCount++; //We mark the exponent as visited
			}
			pointer1 = pointer1->nextPointer;
			pointer2 = result.terms.firstPointer;
		}
		return finalResult; //We return the final result
	}

};