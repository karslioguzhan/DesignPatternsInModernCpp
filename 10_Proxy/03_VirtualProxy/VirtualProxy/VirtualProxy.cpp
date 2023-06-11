#include <iostream>
#include <string>

struct Image
{
    virtual void draw() = 0;
};

struct  Bitmap : Image
{
    Bitmap(const std::string filename)
    {
        std::cout << "Loading bitmap from " << filename << std::endl;
    }

    void draw() override
    {
        std::cout << "Drawing bitmap" << std::endl;
    }
};

struct LazyBitmap : Image
{
private:
    std::string filename;

public:

    LazyBitmap(const std::string& filename)
        : filename(filename)
    {
    }
    Bitmap* bmp{ nullptr };

    void draw() override
    {
        bmp = new Bitmap(filename);
        bmp->draw();
    }
};

int main()
{
    LazyBitmap bmp{ "pokemon.png" };
    bmp.draw();
}
