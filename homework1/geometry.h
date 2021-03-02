#ifndef GEOMETRY_H
#define GEOMETRY_H
#include <vector>
#include<iostream>
#include "math.h"

using namespace std;
class Point {
public:
    int x;
    int y;
    Point() {
        x = 0;
        y = 0;
    }
    Point(int x_, int y_) {
        x = x_;
        y = y_;
    }
    Point operator = (const Point& point) {
        x = point.x;
        y = point.y;
    }
    Point(const Point& point) {
        x = point.x;
        y = point.y;
    }
    int getX() const {
        return x;
    }
    int getY() const {
        return y;
    }
};

class PolygonalChain : public Point {
public:
    int n;
    int t;
    vector <Point> arr;
    PolygonalChain() {
        n = 0;
    }
    PolygonalChain(const int kol, const Point* other) {
        n = kol;
        for (int i = 0; i < n; i++) {
            arr.push_back(other[i]);
        }
    }
    PolygonalChain(const PolygonalChain& other) {
        n = other.n;
        arr = other.arr;
    }
    PolygonalChain& operator = (const PolygonalChain& other) {
        n = other.n;
        arr = other.arr;
        return *this;
    }
    Point getPoint(int i) const {
        return arr[i];
    }

    float perimeter() const {
    	if (t==1) {
    		float length = 0;
	        for (int i = 0; i < n - 1; i++)
	            length += sqrt((arr[i + 1].x - arr[i].x) * (arr[i + 1].x - arr[i].x) + (arr[i + 1].y - arr[i].y) * (arr[i + 1].y - arr[i].y));
	        length += sqrt((arr[n - 1].x - arr[0].x) * (arr[n - 1].x - arr[0].x) + (arr[n - 1].y - arr[0].y) * (arr[n - 1].y - arr[0].y));
	        return length;
		}
        float length = 0;
        for (int i = 0; i < n - 1; i++)
            length += sqrt((arr[i + 1].x - arr[i].x) * (arr[i + 1].x - arr[i].x) + (arr[i + 1].y - arr[i].y) * (arr[i + 1].y - arr[i].y));
        return length;
    }
    int getN() const {
        return n;
    }
};

class ClosedPolygonalChain : public PolygonalChain {
public:
    ClosedPolygonalChain() {
        n = 0;
    }
    ClosedPolygonalChain(const int kol, const Point* other) {
    	t = 1;
        n = kol;
        for (int i = 0; i < n; i++) {
            arr.push_back(other[i]);
        }
    }
};

class Polygon : public ClosedPolygonalChain {
public:
    Polygon() {
        n = 0;
    }
    Polygon(const int kol, const Point* other) {
    	t = 1;
        n = kol;
        for (int i = 0; i < n; i++) {
            arr.push_back(other[i]);
        }
    }
    float area() const { // gauss formula
        float area = 0;
        for (int i = 0; i < n - 1; i++) {
            area += arr[i].x * arr[i + 1].y;
        }
        area += arr[n - 1].x * arr[0].y;
        for (int i = 0; i < n - 1; i++) {
            area -= arr[i + 1].x * arr[i].y;
        }
        area -= arr[0].x * arr[n - 1].y;
        area = 0.5 * abs(area);
        return area;
    }

};

class Triangle : public Polygon {

public:
    Triangle(const int kol, const Point* other) {
    	t = 1;
        n = kol;
        for (int i = 0; i < n; i++) {
            arr.push_back(other[i]);
        }
    }
    float hasRightAngle() const {
        int check = 0;
        float a, b, c;
        a = sqrt(pow((arr[0].x - arr[1].x), 2) + pow((arr[0].y - arr[1].y), 2));
        b = sqrt(pow((arr[1].x - arr[2].x), 2) + pow((arr[1].y - arr[2].y), 2));
        c = sqrt(pow((arr[2].x - arr[0].x), 2) + pow((arr[2].y - arr[0].y), 2));
        float p = (a + b + c) / 2;
        float S = sqrt(p * (p - a) * (p - b) * (p - c));
        if ((S == 0.5 * a * b) || (S == 0.5 * a * c) || (S == 0.5 * b * c)) {
            check = 1;
        }

        if (check == 1) {
            return true;
        }
        else return false;

    };


};

class Trapezoid : public Polygon {

public:
    Trapezoid(const int kol, const Point* other) {
    	t = 1;
        n = kol;
        for (int i = 0; i < n; i++) {
            arr.push_back(other[i]);
        }
    }
    float height() const {
        float height;
        float S = area();
        height = 2 * S / (sqrt((pow((arr[2].x - arr[1].x), 2)) + pow((arr[2].y - arr[1].y), 2)) + sqrt(pow((arr[3].x - arr[0].x), 2)) + pow((arr[2].y - arr[1].y), 2));
        return height;
    }
};
class RegularPolygon : public Polygon {
public:
    RegularPolygon() {
        n = 0;
    }
    RegularPolygon(const int kol, const Point* other) {
    	t = 1;
        n = kol;
        for (int i = 0; i < n; i++) {
            arr.push_back(other[i]);
        }
    }

};
#endif // GEOMETRY_H
