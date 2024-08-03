#pragma once
#include <vector>
#include "DeckSelectionHelper.h"
#include "ModifierDeck.h"
#include "ItemDeck.h"

class Monster;

class MonsterDeck
{
public:
    MonsterDeck();
    ~MonsterDeck();

    Monster* generateMonster();

private:
    std::vector<Monster*> m_monstersDatabase;
    DeckSelectionHelper<Monster> m_deck;
    ItemDeck* m_itemDeck;  
    ModifierDeck* m_modifierDeck;
};