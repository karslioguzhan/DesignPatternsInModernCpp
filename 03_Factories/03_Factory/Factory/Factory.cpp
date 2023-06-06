#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <ostream>


enum class PointType
{
    cartesian,
    polar
};

class Point
{
public:
    float x, y;
    Point(float x, float y) :
        x(x), y(y) {}
public:
    friend std::ostream& operator << (std::ostream& os, const Point& point)
    {
        os << "x: " << point.x << " y: " << point.y;
        return os;
    }
    // friend class PointFactory; // Violates the Open Closed Principle
};

// Speration of concers 
struct PointFactory
{
    static Point NewCartesian(float x, float y)
    {
        return { x, y };
    }

    // Factory method
    static Point NewPolar(float r, float theta)
    {
        return { r * cos(theta), r * sin(theta) };
    }
};

int main()
{
    auto p = PointFactory::NewPolar(5, M_PI_4);
    std::cout << p << std::endl;

    Point p2{ 2, 3 };
}
