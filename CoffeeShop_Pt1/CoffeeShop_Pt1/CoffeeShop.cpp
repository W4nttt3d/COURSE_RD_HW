#include "CoffeeShop.h"
#include "Drink.h"
#include "Coffee.h"
#include "Tea.h"

#include <iostream>

CoffeeShop::CoffeeShop(const std::string& shopName) : name(shopName)
{
	for (int i = 0; i < TABLES_COUNT; i++)
	{
		m_Tables[i] = false;
		m_Orders[i] = nullptr;
	}
}

CoffeeShop::~CoffeeShop()
{
	for (int i = 0; i < TABLES_COUNT; i++)
	{
		delete m_Orders[i];
	}
}

int CoffeeShop::takePlace()
{
	for (int i = 0; i < TABLES_COUNT; i++)
	{
		if (!m_Tables[i])
		{
			m_Tables[i] = true;
			return i;
		}
	}
	return -1;
}

void CoffeeShop::order(int tableNumber)
{
	if (tableNumber < 0 || tableNumber >= TABLES_COUNT || !m_Tables[tableNumber])
	{
		std::cout << "Invalid table number.\n";
		return;
	}

	std::cout << "Welcome to " << name << " cafe\n";
	std::cout << "Choose your drink:\n";
	std::cout << "1. Coffee\n";
	std::cout << "2. Tea\n";

	int choice;
	std::cin >> choice;

	DrinkType type;
	switch (choice) {
	case 1:
		type = DrinkType::Coffee;
		break;
	case 2:
		type = DrinkType::Tea;
		break;
	default:
		std::cout << "Invalid choice.\n";
		return;
	}

	delete m_Orders[tableNumber];
	m_Orders[tableNumber] = createDrink(type); // Use the createDrink function
	std::cout << "Order placed successfully.\n";
}

bool CoffeeShop::prepare(int tableNumber)
{
	if (tableNumber < 0 || tableNumber >= TABLES_COUNT || m_Orders[tableNumber] == nullptr)
	{
		std::cout << "No order to prepare.\n";
		return false;
	}

	m_Orders[tableNumber]->prepare();
	return true;
}

bool CoffeeShop::getReceipt(int tableNumber) {
	if (tableNumber < 0 || tableNumber >= TABLES_COUNT || m_Orders[tableNumber] == nullptr)
	{
		std::cout << "No order exists for this table.\n";
		return false;
	}

	std::cout << "Total cost: " << m_Orders[tableNumber]->getCost() << std::endl;
	delete m_Orders[tableNumber];
	m_Orders[tableNumber] = nullptr;
	m_Tables[tableNumber] = false;
	return true;
}