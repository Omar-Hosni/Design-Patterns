#pragma once
#include <memory>
#include "HotDrink.h"
#include "HotDrinkFactory.h"
#include <string>
#include <map>

using namespace std;

class DrinkFactory
{
	map<string, unique_ptr<HotDrinkFactory>> hot_factories;

public:
	DrinkFactory() {
		hot_factories["coffee"] = make_unique<CoffeeFactory>();
		hot_factories["tea"] = make_unique<TeaFactory>();
	}

	unique_ptr<HotDrink> make_drink(const string& name, const int volume)
	{
		auto drink = hot_factories[name]->make();
		drink->prepare(volume);
		return drink;
	}
};

