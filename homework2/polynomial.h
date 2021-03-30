#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H
#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <sstream>
using namespace std;
class Polynomial {
public:
int min, max;
int* arr;
Polynomial(); 
Polynomial(int min_, int max_, int*coefficents); 
Polynomial(const Polynomial& copy);
~Polynomial();	
Polynomial& operator=(const Polynomial &copy);
int operator [](int i) const; 
int& operator [](int i);  
void resize(int min_, int max_); 
int get(int n); 	
};
#endif
