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
    int min, max;
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
};
inline ostream& operator <<(ostream& stream, const Polynomial& poly) {
    int max_ = poly.max;
    if (poly.max == 0 && poly.min == 0) {
        stream << 0;
    }
    else {
        for (int i = poly.max; i >= poly.min; i--) {
            int coef = i - poly.min;
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
//==
inline bool operator==(const Polynomial& poly1, const Polynomial& poly2) {
    stringstream p1, p2;
    p1 << poly1;
    p2 << poly2;
    return p1.str() == p2.str();
}
//!=
inline bool operator !=(const Polynomial& poly1, const Polynomial& poly2) {
    return !(poly1 == poly2);
}
//+
inline Polynomial operator+(const Polynomial& poly) {
    return poly;
}
//-
inline Polynomial operator-(const Polynomial& poly) {
    int temp[poly.max - poly.min + 1];
    for (int i = 0; i < (poly.max - poly.min) + 1; i++)
        temp[i] = poly.arr[i] * (-1);
    return Polynomial(poly.min, poly.max, temp);
}
// +=
inline Polynomial operator+=(const Polynomial& poly1, const Polynomial poly2) {
    if ((poly1.max == 0 && poly1.min == 0) || (poly2.max == 0 && poly2.min == 0))
        return poly1.max == 0 && poly1.min == 0 ? poly2 : poly1;
    else {
        int min_ = min(poly1.min, poly2.min);
        int max_ = max(poly1.max, poly2.max);
        int* arr_ = new int[max_ - min_ + 1];
        for (int i = 0; i < max_ - min_ + 1; i++) {
            arr_[i] = 0;
        }
        for (int i = min_; i <= max_; i++) {
            if (i >= poly1.min && i <= poly1.max) {
                arr_[i - min_] += poly1.arr[i - poly1.min];
            }
            if (i >= poly2.min && i <= poly2.max) {
                arr_[i - min_] += poly2.arr[i - poly2.min];
            }
        }
        Polynomial p(min_, max_, arr_);
        return p;
    }
}
// -=
inline Polynomial operator-=(Polynomial& poly1, Polynomial& poly2) {
    poly2 = -poly2;
    return poly1 += poly2;
}
//+
inline Polynomial operator+(const Polynomial& poly1, const Polynomial& poly2) {
    return poly1 += poly2;
}
//-
inline Polynomial operator-(Polynomial poly1, Polynomial poly2) {
    return poly1 -= poly2;
}
//* int*poly
inline Polynomial operator *(Polynomial poly, int a) {
    for (int i = 0; i < poly.max - poly.min + 1; i++)
        poly.arr[i] *= a;
    return poly;
}
//* poly* int
inline Polynomial operator *(int a, Polynomial poly) {
    for (int i = 0; i < poly.max - poly.min + 1; i++)
        poly.arr[i] *= a;
    return poly;
}
//poly*poly
inline Polynomial operator *(const Polynomial poly1, const Polynomial poly2) {
    if ((poly1.max == 0 && poly1.min == 0) || (poly2.max == 0 && poly2.min == 0)) {
        if (poly1.max == 0 && poly1.min == 0)
            return poly1;
        else return poly2;
    }
    else {
        int min_ = INT_MAX;
        int max_ = -INT_MAX;
        for (int i = poly1.min; i <= poly1.max; i++) {
            for (int j = poly2.min; j <= poly2.max; j++) {
                if (i + j > max_)
                    max_ = i + j;
                if (i + j < min_)
                    min_ = i + j;
            }
        }
        int temp[max_ - min_ + 1];
        for (int i = 0; i < max_ - min_ + 1; i++)
            temp[i] = 0;
        for (int i = poly1.min; i <= poly1.max; i++) {
            for (int j = poly2.min; j <= poly2.max; j++) {
                temp[i + j - min_] += (poly1.arr[i - poly1.min] * poly2.arr[j - poly2.min]);
            }
        }
        return Polynomial(min_, max_, temp);
    }
}

//*=
inline Polynomial operator*=(Polynomial& poly, int a) {
    poly = poly * a;
    return poly;
}

// /
inline Polynomial operator/(Polynomial poly, int a) {
    for (int i = 0; i < poly.max - poly.min + 1; i++)
        poly.arr[i] /= a;
    int* temp;
    int min_ = poly.min;
    int max_ = poly.max;
    while (poly.arr[min_ - poly.min] == 0) {
        min_++;
    }
    while (poly.arr[max_ - poly.min] == 0 && max_ != poly.min) {
        max_--;
    }
    temp = new int[max_ - min_ + 1];
    for (int i = min_; i <= max_; i++) {
        temp[i - min_] = poly.arr[i - poly.min];
    }
    Polynomial new_poly(min_, max_, temp);
    return new_poly;
}
// /=
inline void operator/=(Polynomial& poly, double a) {
    poly = poly / a;
}

// >>
inline istream& operator >>(istream& stream, Polynomial& poly) {
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
    poly.max = max_ - 1;
    poly.min = min_;
    poly.arr = arr_;
}

#endif



