#pragma once

#include "Drink.h"

#include <string>

constexpr unsigned TABLES_COUNT = 20;

class CoffeeShop
{
public:
	CoffeeShop(const std::string& shopName);
	~CoffeeShop();

	int takePlace();
	void order(int tableNumber);
	bool prepare(int tableNumber);
	bool getReceipt(int tableNumber);

private:
	std::string name;
	bool m_Tables[TABLES_COUNT];
	Drink* m_Orders[TABLES_COUNT];
};