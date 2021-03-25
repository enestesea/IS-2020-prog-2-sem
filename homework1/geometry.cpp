#include <iostream>
#include "geometry.h"
#include <cmath>
using namespace std;
//fixed transfer all from h to cpp
Point::Point() {
    x = 0;
    y = 0;
}
Point::Point(int x_, int y_) {
    x = x_;
    y = y_;
}
Point::Point(const Point& point) {
    x = point.x;
    y = point.y;
}
Point& Point::operator=(const Point &point){
    x = point.x;
    y = point.y;
    return *this;
}
int Point::getX() const {
    return x;
}
int Point::getY() const {
    return y;
}
PolygonalChain::PolygonalChain() {
    arr.resize(0);
}
PolygonalChain::PolygonalChain(const int amount, const Point* other){
for (int i = 0; i < amount; i++) {
    arr.push_back(other[i]);
}
};
PolygonalChain::PolygonalChain(const PolygonalChain& other) {
    arr = other.arr;
}
PolygonalChain& PolygonalChain::operator = (const PolygonalChain& other) {
    arr = other.arr;;
    return*this;
}
int PolygonalChain::getN() const {
    return arr.size();
}
Point PolygonalChain::getPoint(int i) const {
    return arr[i];
}
PolygonalChain::~PolygonalChain() {
}
float PolygonalChain::dist(Point p1, Point p2) const {
    return sqrt(pow((p1.getX() - p2.getX()),2) + pow((p1.getY() - p2.getY()),2));
}
int PolygonalChain::perimeter() const {
    int length = 0;
    //fixed int comparing unsinged int
    for (size_t i = 0; i < arr.size() - 1; i++)
        length += dist(arr[i], arr[i + 1]);
    return length;
}
ClosedPolygonalChain::ClosedPolygonalChain() {
    arr.resize(0);
}
ClosedPolygonalChain::ClosedPolygonalChain(const int amount, const Point* other) {
    for (int i = 0; i < amount; i++) {
        arr.push_back(other[i]);
    }
}
int ClosedPolygonalChain::perimeter() const {
    //fixed use perimeter from polygonalChain
    int length = PolygonalChain::perimeter();
    return length + dist(arr[arr.size() - 1], arr[0]);
} 
Polygon::Polygon() {
    arr.resize(0);
}
Polygon::Polygon(const int amount, const Point* other) {
    for (int i = 0; i < amount; i++) {
        arr.push_back(other[i]);
    }
}
float Polygon::area() const { // gauss formula
    //fixed remove double
    int area = 0;
    for (size_t i = 0; i < arr.size() - 1; i++) {
        area += arr[i].x * arr[i + 1].y;
    }
    area += arr[arr.size() - 1].x * arr[0].y;
    for (size_t i = 0; i < arr.size() - 1; i++) {
        area -= arr[i + 1].x * arr[i].y;
    }
    area -= arr[0].x * arr[arr.size() - 1].y;
    return 0.5 * abs(area);
}
// fixed todo without sqrt
Triangle::Triangle(const int amount, const Point* other) {
    for (int i = 0; i < amount; i++) {
        arr.push_back(other[i]);
    }
}
bool Triangle::hasRightAngle() const {
    int a, b, c;//sides^2
    a = (pow((arr[0].x - arr[1].x), 2) + pow((arr[0].y - arr[1].y), 2));
    b = (pow((arr[1].x - arr[2].x), 2) + pow((arr[1].y - arr[2].y), 2));
    c = (pow((arr[2].x - arr[0].x), 2) + pow((arr[2].y - arr[0].y), 2));
    //fixed return expression
    return(c == a + b) || (b == a + c) || (a == b + c);
 };
//fixed function dist between points
Trapezoid::Trapezoid(const int amount, const Point* other) {
    for (int i = 0; i < amount; i++) {
        arr.push_back(other[i]);
    }
}
int Trapezoid::height() const {
    int S = area();
    return 2 * S/(dist(arr[2], arr[1]) + dist(arr[3], arr[0]));
}
RegularPolygon::RegularPolygon() {
    arr.resize(0);
}
RegularPolygon::RegularPolygon(const int amount, const Point* other) {
    for (int i = 0; i < amount; i++) {
        arr.push_back(other[i]);
    }
}
int RegularPolygon::perimeter() const {
    return sqrt(pow((arr[0].x - arr[1].x), 2) + pow((arr[0].y - arr[1].y), 2)) * arr.size();
}
float RegularPolygon::area() const {
    float x;
    x = dist(arr[0], arr[1]);
    float area;
    area = (pow(x, 2) * arr.size()) / (4 * tan((M_PI) / arr.size()));
    return area;
}
