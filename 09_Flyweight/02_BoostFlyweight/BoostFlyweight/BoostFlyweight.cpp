#include <iostream>
#include <boost/flyweight.hpp>
#include <string>

struct User2
{
    boost::flyweight<std::string> first_name, last_name;
    User2(const std::string& first_name,
        const std::string& last_name) :
        first_name(first_name), last_name(last_name)
    {
    }

};

int main()
{
    User2 first("John", "Smith");
    User2 second("Jane", "Smith");

    std::cout << first.first_name << std::endl;
    std::cout << std::boolalpha << (&first.first_name.get() == &second.first_name.get()) <<std::endl; // expect false
    std::cout << std::boolalpha << (&first.last_name.get() == &second.last_name.get()) << std::boolalpha  << std::endl; // expect true
}
