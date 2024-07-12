#include "Coffee.h"

#include <iostream>
#include <string>

Coffee::Coffee(CoffeeType t, Size s) : type(t), size(s)
{
    setCost();
}

void Coffee::setCost()
{
    switch (type)
    {
        case CoffeeType::Espresso:
            cost = 35;
            break;
        case CoffeeType::Latte:
            switch (size)
            {
                case Size::M:
                    cost = 75;
                    break;
                case Size::L:
                    cost = 80;
                    break;
                case Size::X:
                    cost = 84;
                    break;
                case Size::XL:
                    cost = 88;
                    break;
            }
            break;
        case CoffeeType::Cappuccino:
            switch (size)
            {
                case Size::S:
                    cost = 50;
                    break;
                case Size::M:
                    cost = 55;
                    break;
                case Size::L:
                    cost = 60;
                    break;
                case Size::X:
                case Size::XL:
                    cost = -1; 
                    break;
            }
            break;
        case CoffeeType::Americano:
            switch (size)
            {
                case Size::S:
                    cost = 40;
                    break;
                case Size::M:
                    cost = 45;
                    break;
                case Size::L:
                    cost = 48;
                    break;
                case Size::X:
                case Size::XL:
                    cost = -1;
                    break;
                }
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