#include <iostream>
#include <string>
#include <sstream>
#include <ostream>
#include <memory>
#include "HotDrinkFactory.h"
#include "DrinkFactory.h"
using namespace std;



int main()
{
	DrinkFactory df;
	auto coffee = df.make_drink("coffee",50);
	
}