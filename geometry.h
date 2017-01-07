#pragma once

struct Point
{
    double x, y;
    Point(double _x = 0, double _y = 0) : x(_x), y(_y) {}
};

namespace Geometry
{
    double cross_product(Point a, Point b, Point c);
    Point rotatePoint(Point p, Point pivot, double angle);
};