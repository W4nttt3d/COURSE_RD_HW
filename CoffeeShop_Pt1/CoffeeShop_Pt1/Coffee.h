#pragma once

#include "Drink.h"

#include <string>

enum class CoffeeType
{
    Espresso,
    Latte,
    Cappuccino,
    Americano
};

class Coffee : public Drink
{
public:
    Coffee(CoffeeType t, Size s);
    void prepare();
    int getCost();

private:
    CoffeeType type;
    Size size;
    int cost;
    void setCost();
};