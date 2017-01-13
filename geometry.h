#pragma once

#include <vector>
#include <cmath>

struct Point
{
    double x, y;
    Point(double _x = 0, double _y = 0) : x(_x), y(_y) {}
    bool operator ==(const Point &p);
};

namespace Geometry
{
    double cross_product(Point a, Point b, Point c);
    Point rotatePoint(Point p, Point pivot, double angle);
    bool intersect(const std::vector<Point> poly1, const std::vector<Point> poly2);
    std::vector<Point> getPolygon(Point pos, int width, int height);
};