#pragma once

#include <string>

enum class DrinkType
{
	Tea,
	Coffee
};

enum class Size
{
    S,
    M,
    L,
    X,
    XL
};

class Drink
{
public:
    virtual void prepare() = 0;
    virtual int getCost() = 0;
    virtual ~Drink() {};
};

Drink* createDrink(DrinkType drinkType);
