#include <iostream>
#include <cmath>

enum class PointType
{
    cartesian, 
    polar
};

struct Point
{
    float x, y;
    /*
    Point(float x, float y):
        x(x), y(y) {}
    This is not possible because constructor must have the same name as the class
    And the declaration with two floats is in both Constructors the same 
    --> Solution Factory
    Point(float rho, float theta)
    {
    }
    */
    // Unsufficient because is it not clear what a and b is
    Point(float a, float b, PointType type = PointType::cartesian)
    {
        if (type == PointType::cartesian)
        {
            x = a;
            y = b;
        }
        else
        {
            x = a * cos(b);
            y = a * sin(b);
        }
    }
};

int main()
{
    std::cout << "A example why factories are important!\n";
}
