#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H
#include <iostream>
#include <limits.h>
#include <cmath>
#include <string>
#include <sstream>
using namespace std;
class Polynomial {
public:
    int minp, maxp;
    int* arr;
    Polynomial();
    Polynomial(int min_, int max_, int* coefficents);
    Polynomial(const Polynomial& copy);
    ~Polynomial();
    Polynomial& operator=(const Polynomial& copy);
    int operator [](int i) const;
    int& operator [](int i);
    void resize(int min_, int max_);
    float get(int n);
    friend ostream& operator <<(ostream& stream, const Polynomial& poly);
//==
    friend bool operator==(const Polynomial& poly1, const Polynomial& poly2);
//!=
    friend operator !=(const Polynomial& poly1, const Polynomial& poly2);
//+
    friend Polynomial operator+(const Polynomial& poly);
//-
    friend Polynomial operator-(const Polynomial& poly);
// +=
    Polynomial operator += (const Polynomial poly2);
// -=
    Polynomial operator -= (const Polynomial poly2);
//+
    friend Polynomial operator+(const Polynomial poly1, const Polynomial poly2);
//-
    friend Polynomial operator-(const Polynomial poly1, const Polynomial poly2);
//* int*poly
    friend Polynomial operator *(const Polynomial poly1, const int a);
//fixed copy-paste
//* poly* int
//todo const&???
    friend Polynomial operator *(const int a, const Polynomial poly1);
//poly*poly
    friend Polynomial operator *(const Polynomial poly1, const Polynomial poly2);
//fixed you dont need it
//*=
    Polynomial operator*=(const int a);
// /
    friend Polynomial operator/(Polynomial poly, const int a);
//fixed / from /=
// /=
    Polynomial operator /=(const int a);
// >>
    friend istream& operator >>(istream& stream, Polynomial& poly);
};
#endif


