#include <iostream>
#include <memory>
#include "HotDrinkFactory.h"
#include "DrinkFactory.h"


std::unique_ptr<HotDrink> make_drink(std::string type)
{
	std::unique_ptr<HotDrink> drink;
	if (type == "tea")
	{
		drink = std::make_unique<Tea>();
		drink->prepare(200);
	}
	else
	{
		drink = std::make_unique<Coffee>();
		drink->prepare(50);
	}
	return drink;
}

int main()
{
	DrinkFactory df;
	auto c = df.make_drink("coffee");

}

