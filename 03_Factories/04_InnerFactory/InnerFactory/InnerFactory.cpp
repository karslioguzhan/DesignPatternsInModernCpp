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
private:
    float x, y;
    Point(float x, float y) :
        x(x), y(y) {}
public:
    friend std::ostream& operator << (std::ostream& os, const Point& point)
    {
        os << "x: " << point.x << " y: " << point.y;
        return os;
    }
    
private:
    // InnerFactory
    class PointFactory
    {
    private:
        PointFactory() {}
    public:
        static Point NewCartesian(float x, float y)
        {
            return { x, y };
        }

        static Point NewPolar(float r, float theta)
        {
            return { r * cos(theta), r * sin(theta) };
        }
    };
public:
    static PointFactory Factory;
};



int main()
{
    auto p = Point::Factory.NewCartesian(2,3);
    
    std::cout << p << std::endl;

}
