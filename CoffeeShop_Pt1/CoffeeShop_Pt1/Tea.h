#pragma once

#include "Drink.h"

#include <string>

enum class TeaType
{
    Black,
    Green,
    Fruit,
};

class Tea : public Drink
{
public:
    Tea(TeaType t, Size s);
    void prepare();
    int getCost();

private:
    TeaType type;
    Size size;
    int cost;
    void setCost();
};