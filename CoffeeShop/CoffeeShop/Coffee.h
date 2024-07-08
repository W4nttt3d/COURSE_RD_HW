#pragma once

#include <string>

enum class CoffeeType 
{
    Espresso,
    Latte,
    Cappuccino,
    Americano
};

class Coffee
{
public:
    Coffee(CoffeeType t);
    void prepare();
    int getCost();

private:
    CoffeeType type;
    int cost;
    void setCost();
};

