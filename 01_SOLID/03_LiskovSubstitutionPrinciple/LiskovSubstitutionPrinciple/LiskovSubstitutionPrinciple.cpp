// Objects in a program should be replaceable with instances of their subtypes
// w/o altering the correctness of the program

#include <iostream>

class Rectangle
{
protected:
    int width, height;
public:
    Rectangle(int width, int height) : width(width), height(height) {}
    int getWidth() const
    {
        return width;
    }
    virtual void setWidth(int width)
    {
        Rectangle::width=width;
    }

    int getHeight() const
    {
        return height;
    }

    virtual void setHeight(int height)
    {
        Rectangle::height = height;
    }

    int area() const
    {
        return width * height;
    }

};

void process(Rectangle& r)
{
    int w = r.getWidth();
    r.setHeight(10);

    std::cout << "expected area = " << (w * 10)
        << ", got " << r.area() << std::endl;
}

class Square : public Rectangle
{
public:
    Square(int size) : Rectangle(size, size) {};
    virtual void setWidth(int width) override
    {
        this->width = this->height = width;
    }
    virtual void setHeight(int height) override
    {
        this->width = this->height = height;
    }
};

/*
struct RectangleFactory
{
    static Rectangle create_rectangle(int w, int h);
    static Rectangle create_square(int size);
};
*/

int main()
{
    Rectangle r{ 3,4 };
    process(r);

    Square sq{ 5 }; 
    process(sq); // Liskov Substition is not respected, because functions for base classes 
    // should work with derived classes 
     
}
