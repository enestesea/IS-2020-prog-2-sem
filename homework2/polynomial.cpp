#include <iostream>
#include "polynomial.h"
#include <sstream>
#include <string>
#include <cmath>
using namespace std;

Polynomial::Polynomial() {
    maxp = 0;
    minp = 0;
    arr = new int[1]{ 0 };
};
Polynomial::Polynomial(int min_, int max_, int* coefficents) {
    minp = min_;
    maxp = max_;
    arr = new int[max_ - min_ + 1];
    for (int i = 0; i < maxp - minp + 1; i++) {
        arr[i] = coefficents[i];
    }
};
Polynomial::Polynomial(const Polynomial& copy) {
    minp = copy.minp;
    maxp = copy.maxp;
    arr = new int[maxp - minp + 1];
    for (int i = 0; i < maxp - minp + 1; i++) {
        arr[i] = copy.arr[i];
    }
};
Polynomial::~Polynomial() {
    delete[]arr;
};
//todo check if copy==this
Polynomial& Polynomial::operator =(const Polynomial& copy) {
    delete[] arr;
    maxp = copy.maxp;
    minp = copy.minp;
    arr = new int[maxp - minp + 1];
    for (int i = 0; i < maxp - minp + 1; i++) {
        arr[i] = copy.arr[i];
    }
    return *this;
};
float Polynomial::get(int n) {
    float temp = arr[0] * powf(n, minp);
    float s = temp;
    for (int i = 1; i < maxp - minp + 1; i++) {
        temp *= n;
        s += arr[i] * temp;
    }
    return s;

};
int Polynomial:: operator [](int i) const {
    if (i <= maxp && i >= minp)
        return arr[i - minp];
    else
        return 0;
};
int& Polynomial:: operator [](int i) {
    if (i <= maxp && i >= minp)
        return arr[i - minp];
    else {
        int min_ = min(minp, i);
        int max_ = max(maxp, i);
        resize(min_, max_);
        return arr[i - minp];
    }
};
void Polynomial::resize(int min_, int max_) {
    int temp[max_ - min_ + 1];
    for (int j = min_; j <= max_; j++) {
        if (j >= minp && j <= maxp) {
            temp[j - min_] = arr[j - minp];
        }
        else {
            temp[j - min_] = 0;
        }
    }
    arr = new int[max_ - min_ + 1];
    for (int j = 0; j < max_ - min_ + 1; j++) {
        arr[j] = temp[j];
    }
    maxp = max_;
    minp = min_;
};
ostream& operator <<(ostream& stream, const Polynomial& poly) {
        int max_ = poly.maxp;
        if (poly.maxp == 0 && poly.minp == 0) {
        stream << 0;
    }
        else {
        for (int i = poly.maxp; i >= poly.minp; i--) {
            int coef = i - poly.minp;
            if (poly.arr[coef] != 0) {
                if (i != max_) {
                    if (poly.arr[coef] > 0) {
                        stream << "+";
                    }
                }
                if (i == 1) {
                    if (poly.arr[coef] == -1) {
                        stream << "-x";
                    }
                    else if (poly.arr[coef] == 1) {
                        stream << "x";
                    }
                    else
                        stream << poly.arr[coef] << "x";
                }
                else if (i == 0) {
                    stream << poly.arr[coef];
                }
                else {
                    if (poly.arr[coef] == -1) {
                        stream << "-x^" << i;
                    }
                    else if (poly.arr[coef] == 1) {
                        stream << "x^" << i;
                    }
                    else
                        stream << poly.arr[coef] << "x^" << i;
                }
            }
            else {
                max_--;
            }
        }
    }
        stream << "";
        return stream;
}
bool operator==(const Polynomial& poly1, const Polynomial& poly2) {
    stringstream p1, p2;
    p1 << poly1;
    p2 << poly2;
    return p1.str() == p2.str();
};
operator !=(const Polynomial& poly1, const Polynomial& poly2) {
    return !(poly1 == poly2);
};
Polynomial operator+(const Polynomial& poly) {
    return poly;
};
Polynomial operator-(const Polynomial& poly) {
    int temp[poly.maxp - poly.minp + 1];
    for (int i = 0; i < (poly.maxp - poly.minp) + 1; i++)
        temp[i] = poly.arr[i] * (-1);
    return Polynomial(poly.minp, poly.maxp, temp);
};
Polynomial Polynomial::operator += (const Polynomial poly2){
    int _min = min(minp, poly2.minp);
    int _max = max(maxp, poly2.maxp);
    int* _coef = new int[_max - _min + 1];
    for(int i = 0; i < _max - _min + 1; i++){
        int temp = 0;
    if(i+_min >= minp && i+_min <= maxp){
        temp += arr[i + _min - minp];
    }
    if(i+_min >= poly2.minp && i+_min <= poly2.maxp){
    temp += poly2.arr[i + _min - poly2.minp];
    }
    _coef[i] = temp;
    }
    delete[] arr;
    arr = _coef;
    minp = _min;
    maxp = _max;
    return *this;
};
//todo -1 * poly2 cerating new object
Polynomial Polynomial::operator -= (const Polynomial poly2){
    *this += -1 * poly2;
    return *this;
};
Polynomial operator+(const Polynomial poly1, const Polynomial poly2) {
   Polynomial poly = poly1;
   poly += poly2;
   return poly;
};
Polynomial operator-(const Polynomial poly1, const Polynomial poly2) {
    Polynomial poly = poly1;
    poly -= poly2;
    return poly;
};
//todo const int-> int
Polynomial operator *(const Polynomial poly1, const int a) {
    Polynomial poly = poly1;
    return poly *= a;
};
Polynomial operator *(const int a, const Polynomial poly1) {
    Polynomial poly = poly1;
    return poly *= a;
};
//todo * from *=
Polynomial operator *(const Polynomial poly1, const Polynomial poly2) {
    if ((poly1.maxp == 0 && poly1.minp == 0) || (poly2.maxp == 0 && poly2.minp == 0)) {
        if (poly1.maxp == 0 && poly1.minp == 0)
            return poly1;
        else return poly2;
    }
    else {
        int min_ = INT_MAX;
        int max_ = -INT_MAX;
        for (int i = poly1.minp; i <= poly1.maxp; i++) {
            for (int j = poly2.minp; j <= poly2.maxp; j++) {
                if (i + j > max_)
                    max_ = i + j;
                if (i + j < min_)
                    min_ = i + j;
            }
        }
        int temp[max_ - min_ + 1];
        for (int i = 0; i < max_ - min_ + 1; i++)
            temp[i] = 0;
        for (int i = poly1.minp; i <= poly1.maxp; i++) {
            for (int j = poly2.minp; j <= poly2.maxp; j++) {
                temp[i + j - min_] += (poly1.arr[i - poly1.minp] * poly2.arr[j - poly2.minp]);
            }
        }
        return Polynomial(min_, max_, temp);
    }
};
Polynomial Polynomial::operator*=(const int a) {
    for(int i = 0; i < maxp - minp + 1; i++){
            arr[i] *= a;
    }
    return *this;
};
//todo / from /=
Polynomial operator/(Polynomial poly, const int a) {
    poly /= a;
    int* temp;
    int min_ = poly.minp;
    int max_ = poly.maxp;
    while (poly.arr[min_ - poly.minp] == 0) {
        min_++;
    }
    while (poly.arr[max_ - poly.minp] == 0 && max_ != poly.minp) {
        max_--;
    }
    temp = new int[max_ - min_ + 1];
    for (int i = min_; i <= max_; i++) {
        temp[i - min_] = poly.arr[i - poly.minp];
    }
    Polynomial new_poly(min_, max_, temp);
    return new_poly;
};
Polynomial Polynomial::operator /=(const int a){
    for(int i = 0; i < maxp - minp + 1; i++){
        arr[i]/=a;
    }
    return *this;
};
istream& operator >>(istream& stream, Polynomial& poly) {
    string poly_;
    int* arr_;
    int max_, min_;
    stream >> poly_;
    arr_ = new int[poly_.size()];
    for (size_t i = 0; i < poly_.size() - 1; i++) {
        if (poly_[i + 1] == 'x') {
            unsigned char coef = poly_[i];
            arr_[i] = (int)coef;
        }
    }
    if (poly_[poly_.size() - 1] == '^') {
        min_ = (int)poly_[poly_.size()];
    }
    else if (poly_[poly_.size()] == 'x') {
        min_ = 1;
    }
    max_ = min_ + poly_.size();
    poly.maxp = max_ - 1;
    poly.minp = min_;
    poly.arr = arr_;
};
