#include "CoffeeShop.h"

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
	std::cout << "Choose your coffee:\n";
	std::cout << "1. Espresso\n";
	std::cout << "2. Latte\n";
	std::cout << "3. Cappuccino\n";
	std::cout << "4. Americano\n";

	int choice;
	std::cin >> choice;

	CoffeeType type;
	switch (choice) {
	case 1:
		type = CoffeeType::Espresso;
		break;
	case 2:
		type = CoffeeType::Latte;
		break;
	case 3:
		type = CoffeeType::Cappuccino;
		break;
	case 4:
		type = CoffeeType::Americano;
		break;
	default:
		std::cout << "Invalid choice.\n";
		return;
	}

	delete m_Orders[tableNumber];
	m_Orders[tableNumber] = new Coffee(type);
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