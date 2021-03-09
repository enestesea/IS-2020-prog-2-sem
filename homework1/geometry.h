#ifndef GEOMETRY_H
#define GEOMETRY_H
#include <vector>
#include<iostream>
#include <cmath>
//todo cpp
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

class PolygonalChain : public Point {
public:
    int n;
    vector <Point> arr;
    PolygonalChain() {
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
        int n = other.n;
        arr = other.arr;
        return *this;
    }
    Point getPoint(int i) const {
        return arr[i];
    }
    //todo remove t -fixed
    virtual int perimeter() const; 
    int getN() const; 
};

class ClosedPolygonalChain : public PolygonalChain {
public:
    ClosedPolygonalChain() {
        n = 0;
    }
    int perimeter() const; 
    ClosedPolygonalChain(const int kol, const Point* other) {
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
        n = kol;
        for (int i = 0; i < n; i++) {
            arr.push_back(other[i]);
        }
    }
    virtual int area() const; 

};

class Triangle : public Polygon {

public:
    Triangle(const int kol, const Point* other) {
        n = kol;
        for (int i = 0; i < n; i++) {
            arr.push_back(other[i]);
        }
    }
    //todo without sqrt-fixed
    float hasRightAngle() const; 
};

class Trapezoid : public Polygon {
public:
    Trapezoid(const int kol, const Point* other) {
        n = kol;
        for (int i = 0; i < n; i++) {
            arr.push_back(other[i]);
        }
    }
    int height() const; 
};

//todo area and perimeter-fixed
class RegularPolygon : public Polygon {
public:
    RegularPolygon() {
        n = 0;
    }
    //todo constructor fro base class
    RegularPolygon operator = (const RegularPolygon& reg) {
        x = reg.x;
        y = reg.y;
        return *this;
    }
    RegularPolygon(const RegularPolygon& reg) {
        x = reg.x;
        y = reg.y;
    }
    RegularPolygon(const int kol, const Point* other) {
        n = kol;
        for (int i = 0; i < n; i++) {
            arr.push_back(other[i]);
        }
    }
    int perimeter() const;
    int area() const; 
};
#endif // GEOMETRY_H

