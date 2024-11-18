// Polynomials.cpp

#include <iostream>
#include "Polynomials.h"
using namespace std;

int main()
{
    //First we will work with real polynomials

    Polynomial p1, p2, p3, p4, p5, p6;
    double xValue;

    cout << "Input the first polynomial:\n";
    p1.inputRealPolynomial();
    cout << "First polynomial (rp1): ";
    p1.displayRealPolynomial();
    cout << "Input a value for x: ";
    cin >> xValue;
    cout << p1.inputXForRealPolynomial(xValue);
    cout << "\n";
    cout << "\n";

    cout << "Input second polynomial:\n";
    p2.inputRealPolynomial();
    cout << "Second polynomial (rp2): ";
    p2.displayRealPolynomial();
    cout << "Input a value for x: ";
    cin >> xValue;
    cout << p2.inputXForRealPolynomial(xValue);
    cout << "\n";
    cout << "\n";

    p3 = p1.addRealPolynomials(p2);
    cout << "Sum of p1 and p2 (rp3): ";
    p3.displayRealPolynomial();
    cout << "\n";
    cout << "\n";

    p4 = p1.multiplyRealPolynomials(p2);
    cout << "Product of p1 and p2 (rp4): ";
    p4.displayRealPolynomial();
    cout << "\n";
    cout << "\n";

    p5 = p3.addRealPolynomials(p4);
    cout << "Sum of rp3 and rp4: ";
    p5.displayRealPolynomial();
    cout << "\n";
    cout << "\n";

    p6 = p4.multiplyRealPolynomials(p3);
    cout << "Product of rp3 and rp4: ";
    p6.displayRealPolynomial();
    cout << "\n";

    //Now we will work with complex polynomials
    Polynomial complexPol1, complexPol2, complexPol3, complexPol4;

    complexPol1.inputComplexPolynomial();
    cout << "First complex polynomial (cp1):\n";
    complexPol1.displayComplexPolynomial();
    cout << "\n";
    cout << "\n";

    complexPol2.inputComplexPolynomial();
    cout << "Second complex polynomial (cp2):\n";
    complexPol2.displayComplexPolynomial();
    cout << "\n";
    cout << "\n";

    complexPol3 = complexPol1.addComplexPolynomials(complexPol2);
    cout << "Sum of cp1 and cp2 (cp3):\n";
    complexPol3.displayComplexPolynomial();
    cout << "\n";
    cout << "\n";

    complexPol4 = complexPol3.addComplexPolynomials(complexPol1);
    cout << "Sum of cp1 and cp3:\n";
    complexPol4.displayComplexPolynomial();
}

