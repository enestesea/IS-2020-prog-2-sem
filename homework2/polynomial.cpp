#include <iostream>
#include "polynomial.h"
#include <sstream>
#include <string>
#include <cmath>
using namespace std;

Polynomial::Polynomial() {
	max = 0;
	min = 0;
	arr = new int[1]{ 0 };
};
Polynomial::Polynomial(int min_, int max_, int* coefficents) {
	min = min_;
	max = max_;
	arr = new int[max_ - min_ + 1];
	for (int i = 0; i < max - min + 1; i++) {
		arr[i] = coefficents[i];
	}
};
Polynomial::Polynomial(const Polynomial& copy) {
	min = copy.min;
	max = copy.max;
	arr = new int[max - min + 1];
	for (int i = 0; i < max - min + 1; i++) {
		arr[i] = copy.arr[i];
	}
};
Polynomial::~Polynomial() {
	delete[]arr;
};
Polynomial& Polynomial::operator =(const Polynomial& copy) {
	max = copy.max;
	min = copy.min;
	arr = new int[max - min + 1];
	for (int i = 0; i < max - min + 1; i++) {
		arr[i] = copy.arr[i];
	}
	return *this;
};

float Polynomial::get(int n) {
	int temp = arr[0] * pow(n, min);
	int s = temp;
	for (int i = 1; i < max - min + 1; i++) {
		temp *= n;
		s += arr[i] * temp;
	}
	return s;
};
int Polynomial:: operator [](int i) const {
	if (i <= max && i >= min)
		return arr[i - min];
	else
		return 0;
};
int& Polynomial:: operator [](int i) {
	if (i <= max && i >= min)
		return arr[i - min];
	else {
		int min_ = std::min(min, i);
		int max_ = std::max(max, i);
		resize(min_, max_);
		return arr[i - min];
	}
};
void Polynomial::resize(int min_, int max_) {
	int temp[max_ - min_ + 1];
	for (int j = min_; j <= max_; j++) {
		if (j >= min && j <= max) {
			temp[j - min_] = arr[j - min];
		}
		else {
			temp[j - min_] = 0;
		}
	}
	arr = new int[max_ - min_ + 1];
	for (int j = 0; j < max_ - min_ + 1; j++) {
		arr[j] = temp[j];
	}
	max = max_;
	min = min_;
};
