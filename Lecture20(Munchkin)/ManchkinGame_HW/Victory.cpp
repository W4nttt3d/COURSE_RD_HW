#include "Victory.h"
#include "Munchkin.h"
#include "Item.h"
#include <vector>
#include "fstream"
#include "sstream"

void Victory_LevelBonus::apply(Munchkin* munchkin) const
{
    munchkin->updateLevelBy(m_bonusLevels);
}

std::string Victory_LevelBonus::getFullInfo() const
{
    return "Level Up by " + std::to_string(m_bonusLevels);
}

void Victory_ItemFromHandAdd::apply(Munchkin* munchkin) const
{
    Item* newItem = m_itemDeck->generateItem();
    munchkin->addItem(newItem);
}

std::string Victory_ItemFromHandAdd::getFullInfo() const
{
    return "Add one random item to hand";
}

void Victory_ModifierFromHandAdd::apply(Munchkin* munchkin) const
{
    Modifier* newModifier = m_modifierDeck->generateModifier();
    munchkin->addModifier(newModifier);
}

std::string Victory_ModifierFromHandAdd::getFullInfo() const
{
    return "Add one random modifier to hand";
}