#include "gamedata.h"
#include "geometry.h"

#include <cmath>


double Geometry::cross_product(Point a, Point b, Point c)
{
    return (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y);
}

Point Geometry::rotatePoint(Point p, Point pivot, double angle)
{
    angle = angle / 180.0 * PI;
    double x = pivot.x + (p.x - pivot.x) * cos(angle) - (p.y - pivot.y) * sin(angle);
    double y = pivot.y + (p.y - pivot.y) * cos(angle) + (p.x - pivot.x) * sin(angle);
    return Point(x, y);
}

bool Geometry::intersect(const std::vector<Point> poly1, const std::vector<Point> poly2)
{
    for (auto i = 0; i < poly1.size(); ++i)
    {
        auto j = (i + 1 < poly1.size() ? i + 1 : 0);
        auto k = (j + 1 < poly1.size() ? j + 1 : 0);

        bool ok = true;
        for (const auto p : poly2)
        {
            if (cross_product(poly1[i], poly1[j], poly1[k]) * cross_product(poly1[i], poly1[j], p) >= 0)
            {
                ok = false;
                break;
            }
        }

        if (ok) return false;
    }

    for (auto i = 0; i < poly2.size(); ++i)
    {
        auto j = (i + 1 < poly2.size() ? i + 1 : 0);
        auto k = (j + 1 < poly2.size() ? j + 1 : 0);

        bool ok = true;
        for (const auto p : poly1)
        {
            if (cross_product(poly2[i], poly2[j], poly2[k]) * cross_product(poly2[i], poly2[j], p) >= 0)
            {
                ok = false;
                break;
            }
        }

        if (ok) return false;
    }

    return true;
}
