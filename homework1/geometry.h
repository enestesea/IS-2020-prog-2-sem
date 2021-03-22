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
    Point();
    Point(int, int);
    Point& operator= (const Point &point); 
    Point(const Point& point); 
    int getX() const;
    int getY() const;
};

//fixed u dont need inheritance here
class PolygonalChain {
public:
    //fixed make destructor
    vector <Point> arr;
    PolygonalChain(); 
    PolygonalChain(const int amount, const Point* other);     
    PolygonalChain(const PolygonalChain& other); 
    PolygonalChain& operator = (const PolygonalChain& other);
    ~PolygonalChain();
    Point getPoint(int i) const; 
    float dist(Point p1, Point p2) const;
    virtual int perimeter() const;
    int getN() const;
};

class ClosedPolygonalChain : public PolygonalChain {
public:
    ClosedPolygonalChain(); 
    int perimeter() const;
    ClosedPolygonalChain(const int amount, const Point* other); 
};

class Polygon : public ClosedPolygonalChain {
public:
    Polygon(); 
    Polygon(const int amount, const Point* other); 
    virtual float area() const;
};

class Triangle : public Polygon {
public:
    Triangle(const int amount, const Point* other); 
    //fixed without sqrt
    bool hasRightAngle() const;
};

class Trapezoid : public Polygon {
public:
    Trapezoid(const int amount, const Point* other); 
    int height() const;
};

//fixed area and perimeter
class RegularPolygon : public Polygon {
public:
    RegularPolygon(); 
    RegularPolygon(const int amount, const Point* other); 
    int perimeter() const;
    float area() const;
};
#endif // GEOMETRY_H
