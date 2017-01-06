#include <cmath>
#include "geometry.h"

double Geometry::cross_product(Point a, Point b, Point c)
{
    return (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y);
}

Point Geometry::rotatePoint(Point p, Point pivot, double angle)
{
    angle = angle / 180.0 * acos(-1);
    double x = pivot.x + (p.x - pivot.x) * cos(angle) - (p.y - pivot.y) * sin(angle);
    double y = pivot.y + (p.y - pivot.y) * cos(angle) + (p.x - pivot.x) * sin(angle);
    return Point(x, y);
}
