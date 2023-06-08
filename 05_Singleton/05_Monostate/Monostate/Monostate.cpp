#include <iostream>

class Printer
{
    // Static members are not inheritable --> very unflexible
    static int id;
public:
    int get_id() const
    {
        return id;
    }
    void set_id(int value)
    {
        id = value;
    }

};

int main()
{
    Printer p;
    int id = p.get_id();

   // Printer p2;
}

