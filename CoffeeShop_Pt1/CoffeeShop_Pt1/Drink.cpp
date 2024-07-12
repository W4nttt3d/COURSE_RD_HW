#include "Drink.h"
#include "Coffee.h"
#include "Tea.h"

#include <iostream>
#include <vector>

Size chooseSize(const std::vector<int>& availableSizes)
{
    int choiceSize;

    while (true)
    {
        std::cout << "Choose your drink:\n";
        std::cout << "1. S\n";
        std::cout << "2. M\n";
        std::cout << "3. L\n";
        std::cout << "4. X\n";
        std::cout << "5. XL\n";
        std::cout << "Choose your size: ";
        std::cin >> choiceSize;

        for (const int sizeDrink : availableSizes)
        {
            if (sizeDrink == choiceSize)
            {
                switch (choiceSize)
                {
                case 1:
                    return Size::S;
                case 2:
                    return Size::M;
                case 3:
                    return Size::L;
                case 4:
                    return Size::X;
                case 5:
                    return Size::XL;
                default:
                    break;
                }
            }
        }
        std::cout << "Incorrect size selection. Try again.\n";
    }
}

CoffeeType chooseCoffeeType() 
{
    int choiceType;
    while (true)
    {
        std::cout << "Choose your coffee:\n";
        std::cout << "1. Espresso (S)\n";
        std::cout << "2. Latte (M, L, X, XL)\n";
        std::cout << "3. Cappuccino (M, L, X)\n";
        std::cout << "4. Americano (M, L, X)\n";

        std::cin >> choiceType;

        switch (choiceType) 
        {
            case 1:
                return CoffeeType::Espresso;
            case 2:
                return CoffeeType::Latte;
            case 3:
                return CoffeeType::Cappuccino;
            case 4:
                return CoffeeType::Americano;
            default:
                std::cout << "Incorrect size selection. Try again.\n";
        }
    }
}

TeaType chooseTeaType() 
{
    int choiceType;

    while (true)
    {
        std::cout << "Choose your tea:\n";
        std::cout << "1. Black (M, L)\n";
        std::cout << "2. Green (M, L)\n";
        std::cout << "3. Fruit (M, L)\n";

        std::cin >> choiceType;

        switch (choiceType) 
        {
            case 1:
                return TeaType::Black;
            case 2:
                return TeaType::Green;
            case 3:
                return TeaType::Fruit;
            default:
                std::cout << "Incorrect size selection. Try again.\n";
        }
    }
}

Drink* createDrink(DrinkType drinkType)
{
    switch (drinkType)
    {
    case DrinkType::Coffee:
    {
        CoffeeType type = chooseCoffeeType();

        std::vector<int> availableSizes;
        switch (type)
        {
        case CoffeeType::Espresso:
            availableSizes = { 1 };
            break;
        case CoffeeType::Latte:
            availableSizes = { 2, 3, 4, 5 };
            break;
        case CoffeeType::Cappuccino:
            availableSizes = { 2, 3, 4 };
            break;
        case CoffeeType::Americano:
            availableSizes = { 2, 3, 4 };
            break;
        default:
            return nullptr;
        }

        Size size = chooseSize(availableSizes);

        return new Coffee(type, size);
    }
    case DrinkType::Tea:
    {
        TeaType type = chooseTeaType();

        std::vector<int> availableSizes = { 2, 3 };
        Size size = chooseSize(availableSizes);

        return new Tea(type, size);
    }
    default:
        return nullptr;
    }
}