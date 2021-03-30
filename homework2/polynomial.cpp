#include <iostream>
#include "polynomial.h"
#include <sstream>
#include <string>
#include <assert.h>
#include <cmath>
using namespace std;

Polynomial::Polynomial() {
			max = 0;
			min = 0;
			arr = new int[1]{0};
		};
Polynomial::Polynomial(int min_, int max_, int*coefficents) {
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
Polynomial& Polynomial::operator =( const Polynomial &copy) {
			max = copy.max;
			min = copy.min;
			arr = new int[max - min + 1];
			for (int i = 0; i < max - min + 1; i++) {
				arr[i] = copy.arr[i];
			}
			return *this;
		};
int Polynomial::get(int n) {
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
int& Polynomial:: operator [](int i)  {
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
					if (j >= min && j <= max ) {
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
ostream& operator <<(ostream& stream, const Polynomial& poly) {
	int max_ = poly.max;
	if (poly.max == 0 && poly.min == 0)  {
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
}
//==
bool operator==(const Polynomial &poly1, const Polynomial &poly2) {
	stringstream p1, p2;
	p1 << poly1;
	p2 << poly2;
	return p1.str() == p2.str();
}
//!=
bool operator !=(const Polynomial& poly1, const Polynomial& poly2) {
	return !(poly1 == poly2);
}
//+ 
Polynomial operator+(const Polynomial& poly) {
	return poly;
}
//-
Polynomial operator-(const Polynomial &poly) {
	int temp[poly.max - poly.min + 1];
	for (int i = 0; i < (poly.max - poly.min) + 1; i++)
		temp[i] = poly.arr[i] * (-1);
	return Polynomial(poly.min, poly.max, temp);
}
// +=
Polynomial operator+=(const Polynomial& poly1, const Polynomial poly2) {
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
Polynomial operator-=(Polynomial& poly1, Polynomial &poly2) {
		poly2 = -poly2;
        return poly1 += poly2;
}
//+
Polynomial operator+(const Polynomial &poly1, const Polynomial &poly2) {
	return poly1 += poly2;
}
//-
Polynomial operator-(Polynomial poly1, Polynomial poly2) {
	return poly1 -= poly2;
}
//* int*poly
Polynomial operator *(Polynomial poly, int a) {
	for (int i = 0; i < poly.max - poly.min + 1; i++)
		poly.arr[i] *= a;
	return poly;
}
//* poly* int
Polynomial operator *(int a, Polynomial poly) {
	for (int i = 0; i < poly.max - poly.min + 1; i++)
		poly.arr[i] *= a;
	return poly;
}
//poly*poly
Polynomial& operator * (const Polynomial poly1, const Polynomial poly2){
        int min_ = poly1.min + poly2.min;
        int max_ = poly1.max + poly2.max;
        int* temp = new int[max_ - min_ + 1];
        for(int i = 0; i < poly1.max - poly1.min + 1; i++){
            for(int j = 0; j < poly2.max - poly2.min + 1; j++){
                temp[i + j] += poly1[i] * poly2[j];
            }
        }
        Polynomial new_poly(min_, max_, temp);
        return new_poly;
    }

//*=
Polynomial operator*=(Polynomial& poly, int a) {
	poly = poly * a;
	return poly;
}

// /
Polynomial operator/(Polynomial poly, int a) {
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
	for (int i = min_; i<=max_; i++) {
		temp[i - min_] = poly.arr[i - poly.min];
	}
	Polynomial new_poly(min_, max_, temp);
	return new_poly;
}
// /=
void operator/=(Polynomial& poly, double a) {
	poly = poly / a;
}

// >>
istream& operator >>(istream& stream,  Polynomial& poly) {
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

void checkOut() {
    stringstream ss;
    ss << Polynomial(0, 2, new int[3]{1, 2, 3}) << " ";
    ss << Polynomial(1, 2, new int[2]{-3, 4}) << " ";
    ss << Polynomial(-1, 2, new int[4]{1, -3, 0, -1}) << " ";
    ss << Polynomial() << " ";
    ss << Polynomial(0, 2, new int[3]{0, 3, -3}) << " ";
    ss << Polynomial(-2, 2, new int[5]{1, 0, 0, 0, 1}) << " ";
    assert(ss.str() == "3x^2+2x+1 4x^2-3x -x^2-3+x^-1 0 -3x^2+3x x^2+x^-2 ");
}

void PolynomialOperators() {
    stringstream ss;
    const auto a =  Polynomial(0, 2, new int[3]{1, 2, 3}) ;
    const auto b = Polynomial(1, 2, new int[2]{-3, 4});
    auto c = Polynomial(-1, 2, new int[4]{1, -3, 0, -1});
    const auto d = Polynomial();
    const auto e =  Polynomial(0, 2, new int[3]{0, 3, -3});
    const auto f = Polynomial(-2, 2, new int[5]{1, 0, 0, 0, 1});
    assert(a * b == b * a);
    assert(d * e == d);
    assert(a * b * c == a * (b * c));
    assert(a * b == Polynomial(1, 4, new int[4]{-3, -2, -1, 12}));
    assert(a + b == b + a);
    assert(d + e == e);
    assert(a + b + c == a + (b + c));
    assert(5 * a == a * 5);
    assert(a + b + c == Polynomial(-1, 2, new int[4]{1, -2, -1, 6}));
    assert(c / 2 == Polynomial(0, 0, new int[1]{-1}));
    assert(c.get(4) == -18.75);
    assert(a[1] == 2);
    assert(a[10] == 0);
    c[5] = 3;
    assert(c.get(4) == 3053.25);
    assert((-c) == (-(-(-c))));
    auto h = -c;
    (-c)[5];
    assert(c[5] == 3 && h[5] == -3);
    assert((-c)[5] == -3);
	auto g = b;
	g[3] = 0;
	assert(g == b);
}


int main() {
    checkOut();
    PolynomialOperators();
    return 0;
}
