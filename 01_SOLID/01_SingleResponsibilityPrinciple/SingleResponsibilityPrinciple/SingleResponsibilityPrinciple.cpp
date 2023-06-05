// SingleResponsibilityPrinciple.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <fstream>
#include <boost/lexical_cast.hpp>

struct Journal
{
    std::string title;
    std::vector<std::string> entries;

    explicit Journal(const std::string& title)
        : title{ title }
    {
    }

    void add(const std::string& entry);
    
    // persistence is a speparate concern
    void save(const std::string& filename);
};

void Journal::add(const std::string& entry)
{
    static int count{ 1 };
    entries.push_back(boost::lexical_cast<std::string> (count++)
        + ": " + entry);
}

void Journal::save(const std::string& filename)
{
    std::ofstream ofs(filename);
    for (auto& s : entries)
    {
        ofs << s << std::endl;
    }
}

struct PersistenceManager
{
    static void save(const Journal& j, const std::string& filename)
    {
        std::ofstream ofs(filename);
        for (auto& s : j.entries)
            ofs << s << std::endl;
    }
};


int main()
{
    Journal journal{ "Dear Diary" };
    journal.add("I ate a bug");
    journal.add("I cried today");
    
    //journal.save("diary.txt");
    PersistenceManager pm;
    pm.save(journal, "diary.txt");
}


