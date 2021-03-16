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
    return arr.size();
}
int PolygonalChain::perimeter() const {
    int length = 0;
    for (int i = 0; i < arr.size() - 1; i++)
        length += sqrt((arr[i + 1].x - arr[i].x) * (arr[i + 1].x - arr[i].x) + (arr[i + 1].y - arr[i].y) * (arr[i + 1].y - arr[i].y));
    return length;
}
int ClosedPolygonalChain::perimeter() const {
    int length = 0;
    for (int i = 0; i < arr.size() - 1; i++)
        length += sqrt((arr[i + 1].x - arr[i].x) * (arr[i + 1].x - arr[i].x) + (arr[i + 1].y - arr[i].y) * (arr[i + 1].y - arr[i].y));
    length += sqrt((arr[arr.size() - 1].x - arr[0].x) * (arr[arr.size() - 1].x - arr[0].x) + (arr[arr.size() - 1].y - arr[0].y) * (arr[arr.size() - 1].y - arr[0].y));
    return length;
}
float Polygon::area() const { // gauss formula
        //fixed  remove double
    float area = 0;
    for (int i = 0; i < arr.size() - 1; i++) {
        area += arr[i].x * arr[i + 1].y;
    }
    area += arr[arr.size() - 1].x * arr[0].y;
    for (int i = 0; i < arr.size() - 1; i++) {
        area -= arr[i + 1].x * arr[i].y;
    }
    area -= arr[0].x * arr[arr.size() - 1].y;
    area = 0.5 * abs(area);
    return area;
}
// fixed todo without sqrt
bool Triangle::hasRightAngle() const {
    int a, b, c;//Í‚‡‰‡Ú˚ ÒÚÓÓÌ
    a = (pow((arr[0].x - arr[1].x), 2) + pow((arr[0].y - arr[1].y), 2));
    b = (pow((arr[1].x - arr[2].x), 2) + pow((arr[1].y - arr[2].y), 2));
    c = (pow((arr[2].x - arr[0].x), 2) + pow((arr[2].y - arr[0].y), 2));
    if ((c == a + b) || (a == b + c) || (b == a + c)) {
        return true;
    }
    else {
        return false;
    }
    //fixed return check
};
int Trapezoid::height() const {
    int height;
    int S = area();
    height = 2 * S / (sqrt((pow((arr[2].x - arr[1].x), 2)) + pow((arr[2].y - arr[1].y), 2)) + sqrt(pow((arr[3].x - arr[0].x), 2)) + pow((arr[2].y - arr[1].y), 2));
    return height;
}
int RegularPolygon::perimeter() const {
    return sqrt(pow((arr[0].x - arr[1].x), 2) + pow((arr[0].y - arr[1].y), 2)) * arr.size();
}
float RegularPolygon::area() const {
    float x;
    x = sqrt(pow(arr[0].x - arr[1].x, 2) + pow(arr[0].y - arr[1].y, 2));
    float area;
    area = (pow(x, 2) * arr.size()) / (4 * tan((M_PI) / arr.size()));
    return area;
}
