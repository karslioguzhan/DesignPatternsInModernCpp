#include <iostream>
#include <map>
#include <boost/bimap.hpp>

typedef uint32_t key;

struct User
{
	User(const std::string& first_name, const std::string& last_name):
		first_name{add(first_name)}, last_name{add(last_name)} {}

	const std::string& get_first_name() const
	{
		return names.left.find(first_name)->second;
	}	
	
	const std::string& get_last_name() const
	{
		return names.left.find(last_name)->second;
	}

	friend std::ostream& operator<< (std::ostream& os, const User& user);
protected:
	key first_name, last_name;
	static boost::bimap<key, std::string> names;
	static key seed;

	static key add(const std::string& s)
	{
		auto it = names.right.find(s);
		if (it == names.right.end())
		{
			key id = ++seed;
			names.insert({ seed, s });
			return id;
		}
		return it->second;
	}
};
key User::seed{0};
boost::bimap<key, std::string> User::names{};

std::ostream& operator<< (std::ostream& os, const User& user)
{
	os << "first_name: " << user.get_first_name() << " last_name: "
		<< user.get_last_name() << "(" << user.last_name << ")";
	return os;
}

int main(int ac, char* av[])
{
	User user1{ "John", "Smith" };
	User user2{ "Jane", "Smith" };

	std::cout << user1 << std::endl << user2 << std::endl;

}
