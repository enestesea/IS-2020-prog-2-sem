#ifndef GEOMETRY_H
#define GEOMETRY_H
#include <vector>
#include<iostream>
#define _USE_MATH_DEFINES
#include <math.h>
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
        return *this;
    }
    Point(const Point& point) {
        x = point.x;
        y = point.y;
    }
    int getX() const;
    int getY() const;
};

//todo u dont need inheritance here
class PolygonalChain : public Point {
public:
	//todo make destructor
    vector <Point> arr;
    PolygonalChain() {
        arr.resize(0);
    }
    PolygonalChain(const int amount, const Point* other) {
        for (int i = 0; i < amount; i++) {
            arr.push_back(other[i]);
        }
    }
    PolygonalChain(const PolygonalChain& other) {
        arr = other.arr;
    }
    PolygonalChain& operator = (const PolygonalChain& other) {
        arr = other.arr;
        return *this;
    }
    Point getPoint(int i) const {
        return arr[i];
    } 
    virtual int perimeter() const;
    int getN() const;
};

class ClosedPolygonalChain : public PolygonalChain {
public:
    ClosedPolygonalChain() {
        arr.resize(0);
    }
    int perimeter() const;
    ClosedPolygonalChain(const int amount, const Point* other) {
        for (int i = 0; i < amount; i++) {
            arr.push_back(other[i]);
        }
    }
};

class Polygon : public ClosedPolygonalChain {
public:
    Polygon() {
        arr.resize(0);
    }
    Polygon(const int amount, const Point* other) {
        for (int i = 0; i < amount; i++) {
            arr.push_back(other[i]);
        }
    }
    virtual float area() const;

};

class Triangle : public Polygon {

public:
    Triangle(const int amount, const Point* other) {
        for (int i = 0; i < amount; i++) {
            arr.push_back(other[i]);
        }
    }
    //fixed without sqrt
    bool hasRightAngle() const;
};

class Trapezoid : public Polygon {
public:
    Trapezoid(const int amount, const Point* other) {
        for (int i = 0; i < amount; i++) {
            arr.push_back(other[i]);
        }
    }
    int height() const;
};

//fixed area and perimeter
class RegularPolygon : public Polygon {
public:
    RegularPolygon() {
        arr.resize(0);
    }
    RegularPolygon(const int amount, const Point* other) {
        for (int i = 0; i < amount; i++) {
            arr.push_back(other[i]);
        }
    }
    int perimeter() const;
    float area() const;
};
#endif // GEOMETRY_H


