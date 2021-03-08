#include <iostream>
#include "geometry.h"
#include <cmath>
using namespace std;
int Point::getX() const {
    return x;
}
int Point::getY() const {
    return y;
}
int PolygonalChain::getN() const {
    return n;
}
int PolygonalChain::perimeter() const {
    float length = 0;
    for (int i = 0; i < n - 1; i++)
        length += sqrt((arr[i + 1].x - arr[i].x) * (arr[i + 1].x - arr[i].x) + (arr[i + 1].y - arr[i].y) * (arr[i + 1].y - arr[i].y));
    return length;
}
int ClosedPolygonalChain::perimeter() const {
    int length = 0;
    for (int i = 0; i < getN() - 1; i++)
        length += sqrt((arr[i + 1].x - arr[i].x) * (arr[i + 1].x - arr[i].x) + (arr[i + 1].y - arr[i].y) * (arr[i + 1].y - arr[i].y));
    length += sqrt((arr[getN() - 1].x - arr[0].x) * (arr[getN() - 1].x - arr[0].x) + (arr[getN() - 1].y - arr[0].y) * (arr[getN() - 1].y - arr[0].y));
    return length;
}
int Polygon::area() const { // gauss formula
        //todo remove double-fixed
    int area = 0;
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
//todo without sqrt-fixed
float Triangle::hasRightAngle() const {
    float a, b, c;
    a = sqrt(pow((arr[0].x - arr[1].x), 2) + pow((arr[0].y - arr[1].y), 2));
    b = sqrt(pow((arr[1].x - arr[2].x), 2) + pow((arr[1].y - arr[2].y), 2));
    c = sqrt(pow((arr[2].x - arr[0].x), 2) + pow((arr[2].y - arr[0].y), 2));
    if ((c * c == a * a + b * b) || (a * a == b * b + c * c) || (b * b == a * a + c * c)) {
        return true;
    }
    else {
        return false;
    }
    //todo return check-fixed
};
int Trapezoid::height() const {
    int height;
    int S = area();
    height = 2 * S / (sqrt((pow((arr[2].x - arr[1].x), 2)) + pow((arr[2].y - arr[1].y), 2)) + sqrt(pow((arr[3].x - arr[0].x), 2)) + pow((arr[2].y - arr[1].y), 2));
    return height;
}
int RegularPolygon::perimeter() const {
    return sqrt(pow((arr[0].x - arr[1].x), 2) + pow((arr[0].y - arr[1].y), 2)) * n;
}
int RegularPolygon::area() const {
    int a = sqrt(pow((arr[0].x - arr[1].x), 2) + pow((arr[0].y - arr[1].y), 2));
    return (a * a * n) / (4 * tan(3.14 / n));
}