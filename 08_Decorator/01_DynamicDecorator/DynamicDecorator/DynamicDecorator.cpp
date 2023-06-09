#include <iostream>
#include <string>
#include <sstream>
struct Shape
{
    virtual std::string str() const = 0;
};

struct Circle : Shape
{
	float radius{ 0 };
	Circle()
	{
	}
	Circle(float radius) :
		radius(radius)
	{
	}

	void resize(float factor)
	{
		radius *= factor;
	}

	std::string str() const override
	{
		std::ostringstream oss;
		oss << "A circle of radius " << radius;
		return oss.str();
	}

};

struct Square :Shape
{
	float side{ 0 };
	Square()
	{
	}
	Square(float side):
		side(side)
	{

	}

	std::string str() const override
	{
		std::ostringstream oss;
		oss << "A square with side " << side;
		return oss.str();
	}

};

struct ColoredShape : Shape
{
	Shape& shape;
	std::string color;
	ColoredShape(Shape &shape, const std::string &color):
		shape(shape), color(color)
	{
	}

	std::string str() const override
	{
		std::ostringstream oss;
		// This is a dynamic decorator
		oss << shape.str() << " has the color " << color;
		return oss.str();
	}
};

struct TransparentShape :Shape
{
	Shape& shape;
	uint8_t transparency;

	TransparentShape(Shape &shape, uint8_t transparency):
		shape(shape), transparency(transparency)
	{
	}

	std::string str() const override
	{
		std::ostringstream oss;
		oss << shape.str() << " has "
			<< static_cast<float>(transparency) / (255.f) * 100.f
			<< " % transparency";
		return oss.str();
	}
};

int main()
{
	Square square{ 5 };
	ColoredShape redSquare{ square, "red" };
	std::cout << square.str() << std::endl;
	std::cout << redSquare.str() << std::endl;

	TransparentShape mySquare{ redSquare, 51 };
	std::cout << mySquare.str() << std::endl;

}
