#include "CoffeeShop.h"

#include <iostream>

int main()
{
	CoffeeShop myCoffeeShop("Hypernova");

	int tableNumber = myCoffeeShop.takePlace();

	if (tableNumber != -1)
	{
		std::cout << "Table " << tableNumber + 1 << " is taken.\n";

		myCoffeeShop.order(tableNumber);

		if (myCoffeeShop.prepare(tableNumber))
		{
			std::cout << "Your coffee is ready.\n";
		}

		if (myCoffeeShop.getReceipt(tableNumber))
		{
			std::cout << "Thank you for visiting!\n";
		}
	}
	else
	{
		std::cout << "No tables available.\n";
	}
}