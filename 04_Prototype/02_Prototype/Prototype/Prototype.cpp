#include <string>
#include <iostream>
#include <memory>
#include <functional>
#include <sstream>
using namespace std;
#include <boost/serialization/serialization.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>

struct Address
{
    string street;
    string city;
    int suite;


    Address(const string& street, const string& city, const int suite)
        : street{ street }, city{ city }, suite{ suite }
    {
    }

    Address (const Address& adress)
        :street{adress.street}, city{adress.city}, suite{adress.suite}
    {}

    friend ostream& operator<<(ostream& os, const Address& obj)
    {
        return os
            << "street: " << obj.street
            << " city: " << obj.city
            << " suite: " << obj.suite;
    }
};


struct Contact
{
    string name;
    Address* address;

    Contact& operator=(const Contact& other)
    {
        if (this == &other)
            return *this;
        name = other.name;
        address = other.address;
        return *this;
    }

    Contact() : name(nullptr), address(nullptr)
    {} // required for serialization

    Contact(string name, Address* address)
        : name{ name }, address{ address }
    {
        //this->address = new Address{ *address };
    }

    Contact(const Contact& other)
        : name{ other.name }
        , address{ new Address{*other.address} }
    {
        address = new Address(
            other.address->street,
            other.address->city,
            other.address->suite
        );
    }


private:
    friend class boost::serialization::access;

    template <class archive>
    void save(archive& ar, const unsigned version) const
    {
        ar << name;
        ar << address;
    }

    template <class archive>
    void load(archive& ar, const unsigned version)
    {
        ar >> name;
        ar >> address;
    }

    BOOST_SERIALIZATION_SPLIT_MEMBER()

public:
    ~Contact()
    {
        delete address;
    }


    friend ostream& operator<<(ostream& os, const Contact& obj)
    {
        return os
            << "name: " << obj.name
            << " works at " << *obj.address; // note the star here
    }
};

struct EmployeeFactory
{
    static Contact main;
    static Contact aux;

    static unique_ptr<Contact> NewMainOfficeEmployee(string name, int suite)
    {
        //static Contact p{ "", new Address{ "123 East Dr", "London", 0 } };
        return NewEmployee(name, suite, main);
    }

    static unique_ptr<Contact> NewAuxOfficeEmployee(string name, int suite)
    {
        return NewEmployee(name, suite, aux);
    }

private:
    static unique_ptr<Contact> NewEmployee(string name, int suite, Contact& proto)
    {
        auto result = make_unique<Contact>(proto);
        result->name = name;
        result->address->suite = suite;
        return result;
    }
};


int main()
{

    Contact john{ "John Doe", new Address{"123 East Dr", "London", 123} };
    Contact jane{ john };
    jane.name = "Jane Smith";
    jane.address->suite = 103;

    cout << john << endl << jane << endl;
}