#pragma once
#include <map>
#include <functional>
#include "HotDrink.h"
#include "HotDrinkFactory.h"

class DrinkFactory
{
	std::map < std::string,
		std::unique_ptr<HotDrinkFactory>> hot_factories;
public:
	DrinkFactory()
	{
		hot_factories["coffee"] = std::make_unique<CoffeeFactory>();
		hot_factories["tea"] = std::make_unique<TeaFactory>();
	}

	std::unique_ptr<HotDrink> make_drink(const std::string& name)
	{
		auto drink = hot_factories[name]->make();
		drink->prepare(200);
		return drink;
	}
};

class DrinkWithVolumeFactory
{
	std::map<std::string, std::function<std::unique_ptr<HotDrink>()>> factories;
public:
	DrinkWithVolumeFactory()
	{
		// Here is the factory method
		factories["tea"] = []
		{
			auto tea = std::make_unique<Tea>();
			tea->prepare(200);
			return tea;
		};
	}
	std::unique_ptr<HotDrink> make_drink(const std::string& name)
	{
		return factories[name]();
	}
};