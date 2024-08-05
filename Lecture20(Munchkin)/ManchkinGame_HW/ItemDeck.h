#pragma once
#include <vector>
#include "DeckSelectionHelper.h"

class Item;

class ItemDeck
{
public:
    ItemDeck();
    ~ItemDeck();

    std::vector<Item*> generateItems(int number);
    Item* generateItem();

private:
    std::vector<Item*> m_itemsDataBase;
    DeckSelectionHelper<Item> m_deck;
};