#include <iostream>

struct Renderer
{
    virtual void render_circle(float x, float y, float radius) = 0;
};

struct  RasterRenderer : Renderer
{
    void render_circle(float x, float y, float radius) override
    {
        std::cout << "Rasterizing a circle of radio " << radius << std::endl;
    }
};

struct VectorRenderer: Renderer
{
    void render_circle(float x, float y, float radius) override
    {
        std::cout << "Drawing a vector circle of radius " << radius << std::endl;
    }
};

struct Shape
{
protected:
    Renderer& renderer;
    Shape(Renderer &renderer):
        renderer(renderer)
    {
    }
public:
    virtual void draw() = 0;
    virtual void resize(float factor) = 0;
};

struct Circle : Shape
{
    Circle(Renderer& renderer, float x, float y, float radius):
        Shape(renderer), x{x}, y{y}, radius{radius}
    {
    }
    float x, y, radius;

    void draw() override
    {
        renderer.render_circle(x, y, radius);
    }

    void resize(float factor) override
    {
        radius *= factor;
    }
};

int main()
{
    RasterRenderer rr;
    Circle rasterCircle{ rr , 5, 5, 5};
    rasterCircle.draw();
    rasterCircle.resize(2);
    rasterCircle.draw();
}
