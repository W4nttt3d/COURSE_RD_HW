#include "Tea.h"

#include <iostream>
#include <string>

Tea::Tea(TeaType t, Size s) : type(t), size(s)
{
    setCost();
}

void Tea::setCost()
{
    switch (type)
    {
    case TeaType::Black:
        switch (size)
        {
            case Size::M:
                cost = 20;
                break;
            case Size::L:
                cost = 30;
                break;
        }
        break;
    case TeaType::Green:
        switch (size)
        {
            case Size::M:
                cost = 25;
                break;
            case Size::L:
                cost = 30;
                break;
        }
        break;
    case TeaType::Fruit:
        switch (size)
        {
            case Size::M:
                cost = 30;
                break;
            case Size::L:
                cost = 35;
                break;
        }
        break;
    }
}


int Tea::getCost()
{
    return cost;
}

void Tea::prepare()
{
    switch (type)
    {
    case TeaType::Black:
        std::cout << "Ingredients: Water, Tea leaves\nTime: 2 minutes\n";
        break;
    case TeaType::Green:
        std::cout << "Ingredients: Water, Green tea leaves\nTime: 2 minutes\n";
        break;
    case TeaType::Fruit:
        std::cout << "Ingredients: Water, Tea leaves, Fruit flavor\nTime: 3 minutes\n";
        break;
    }
}