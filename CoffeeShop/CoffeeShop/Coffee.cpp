#include "Coffee.h"

#include <iostream>
#include <string>

Coffee::Coffee(CoffeeType t) : type(t)
{
	setCost();
}

void Coffee::setCost()
{
	switch (type)
	{
		case CoffeeType::Espresso:
			cost = 60;
			break;
		case CoffeeType::Latte:
			cost = 65;
			break;
		case CoffeeType::Cappuccino:
			cost = 50;
			break;
		case CoffeeType::Americano:
			cost = 45;
			break;
		default:
			cost = -1;
			break;

	}
}

int Coffee::getCost()
{
	return cost;
}

void Coffee::prepare()
{
	switch (type) 
	{
		case CoffeeType::Espresso:
			std::cout << "Ingredients: Water, Coffee\nTime: 2 minutes\n";
			break;
		case CoffeeType::Latte:
			std::cout << "Ingredients: Water, Coffee, Milk\nTime: 3 minutes\n";
			break;
		case CoffeeType::Cappuccino:
			std::cout << "Ingredients: Water, Coffee, Milk, Foam\nTime: 4 minutes\n";
			break;
		case CoffeeType::Americano:
			std::cout << "Ingredients: Water, Coffee\nTime: 3 minutes\n";
			break;
	}
}
