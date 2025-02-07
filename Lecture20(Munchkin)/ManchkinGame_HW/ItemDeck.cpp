#include "ItemDeck.h"
#include "DeckSelectionHelper.h"
#include "Item.h"
#include <fstream>
#include <sstream>

ItemDeck::ItemDeck() : m_itemsDataBase(), m_deck(m_itemsDataBase) 
{
    std::ifstream file("items_database.txt");
    if (!file.is_open())
    {
        throw std::runtime_error("Failed to open items database file.");
    }

    std::string line;
    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        std::string type, name, paramStr;
        std::getline(ss, type, ';');
        std::getline(ss, name, ';');
        std::getline(ss, paramStr);

        int param = std::stoi(paramStr);

        if (type == "Weapon")
        {
            m_itemsDataBase.push_back(new Weapon{ name, param });
        }
        else if (type == "UndeadWeapon")
        {
            m_itemsDataBase.push_back(new UndeadWeapon{ name, param });
        }
        else if (type == "ZombieWeapon")
        {
            m_itemsDataBase.push_back(new ZombieWeapon{ name, param });
        }
        else
        {
            throw std::runtime_error("Unknown item type: " + type);
        }
    }

    file.close();

    m_deck = DeckSelectionHelper<Item>(m_itemsDataBase);
}

ItemDeck::~ItemDeck()
{
    for (Item* item : m_itemsDataBase)
    {
        delete item;
    }
}

Item* ItemDeck::generateItem()
{
    return m_deck.generate();
}

std::vector<Item*> ItemDeck::generateItems(int number)
{
    std::vector<Item*> generatedItems;

    for (int i = 0; i < number; i++)
    {
        Item* item = m_deck.generate();
        generatedItems.push_back(item);
    }

    return generatedItems;
}
