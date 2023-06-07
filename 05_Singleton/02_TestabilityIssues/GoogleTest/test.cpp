#include "pch.h"
#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <boost/lexical_cast.hpp>
#include <vector>
#include <gtest/gtest.h>


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

struct SingletonRecordFinder
{
    int total_population(std::vector<std::string> names)
    {
        int result{ 0 };
        for (auto& name : names)
        {
            result += SingletonDatabase::get().get_population(name);
        }
        return result;
    }
};

TEST(RecordFinderTests, SingletonTotalPopulationTest)
{
    SingletonRecordFinder rf;
    std::vector<std::string> names{ "Seoul", "Mexico City" };
    int tp = rf.total_population(names);
    EXPECT_EQ(17500000 + 17400000, tp);
}

int main(int ac, char* av[])
{
    ::testing::InitGoogleTest(&ac, av);

}
