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
	Square(float side) :
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
	ColoredShape(Shape& shape, const std::string& color) :
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

	TransparentShape(Shape& shape, uint8_t transparency) :
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


// mixin inheritance
// perfect forward

// Define concept
template<typename T>
concept IsAShape = std::is_base_of<Shape, T>::value;

template <IsAShape T> struct ColoredShape2 : T
{
	std::string color;

	ColoredShape2()
	{
	}

	template <typename ...Args>
	ColoredShape2(const std::string& color, Args ...args):
		T(std::forward<Args>(args)...), color{color}
	{}

	std::string str() const override
	{
		std::ostringstream oss;
		oss << T::str() << " has the color " << color;
		return oss.str();
	}
};

template <IsAShape T> struct TransparentShape2: T
{
	uint8_t transparency;

	template <typename ...Args>
	TransparentShape2(const uint8_t transparency, Args ...args) :
		T(std::forward<Args>(args)...), transparency{transparency}
	{}

	std::string str() const override
	{
		std::ostringstream oss;
		oss << T::str() << " has "
			<< static_cast<float>(transparency) /255.f * 100.f
			<< " % transparency";
		return oss.str();
	}
};
int main()
{
	ColoredShape2<Circle> grennCircle{ "green", 5 };
	std::cout << grennCircle.str() << std::endl;

	TransparentShape2<ColoredShape2<Square>> bis{ 0, "blue", 10 };
	bis.color = "light blue";
	bis.side = 21;
	std::cout << bis.str() << std::endl;
}
