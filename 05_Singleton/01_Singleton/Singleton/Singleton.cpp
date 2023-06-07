#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <boost/lexical_cast.hpp>

class SingletonDatabase
{
private:
    SingletonDatabase()
    {
        std::cout << "Initializing database\n";
        std::fstream ifs("capitals.txt");
        std::string s, s2;

        while (std::getline(ifs, s))
        {
            std::getline(ifs, s2);
            int pop = boost::lexical_cast<int>(s2);
            capitals[s] = pop;
        }
    }
    std::map<std::string, int> capitals;
public:
    SingletonDatabase(SingletonDatabase const&) = delete;
    void operator=(SingletonDatabase const&) = delete;

    static SingletonDatabase& get()
    {
        static SingletonDatabase db;
        return db;
    }

    int get_population(const std::string& name)
    {
        return capitals[name];
    }
};

int main()
{
    std::string city{ "Tokyo" };
    std::cout << city << " has population " <<
        SingletonDatabase::get().get_population(city) << std::endl;
}
