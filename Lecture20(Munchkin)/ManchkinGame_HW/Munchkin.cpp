#include "Munchkin.h"
#include "Item.h"
#include "Modifier.h"

void Munchkin::updateLevelBy(int levels)
{
    if (m_level + levels <= 0)
    {
        m_level = 1;
    }
    else
    {
	    m_level += levels; 
    }

}

void Munchkin::addItem(Item* item)
{
    m_items.push_back(item);
}

void Munchkin::addItems(const std::vector<Item*>& items)
{
    for (Item* item : items)
    {
        void addItem(Item* item);
        m_items.push_back(item);
    }
}

const std::vector<Item*>& Munchkin::getItems() const
{
    return m_items;
}

void Munchkin::addModifier(Modifier* modifier)
{
    m_modifiers.push_back(modifier);
}

void Munchkin::addModifiers(const std::vector<Modifier*>& modifiers)
{
    for (Modifier* modifier : modifiers)
    {
        void addModifier(Modifier* modifier);
        m_modifiers.push_back(modifier);
    }
}

Modifier* Munchkin::popModifier(int idx)
{
    if (idx >= m_modifiers.size() || idx < 0)
    {
        return nullptr;
    }

    Modifier* modifier = m_modifiers[idx];
    m_modifiers.erase(m_modifiers.begin() + idx);
    return modifier;
}

void Munchkin::removeModifierFromHand(int idx)
{
    m_modifiers.erase(m_modifiers.begin() + idx);
}

void Munchkin::removeItemEquipped(int idx)
{ 
    m_items.erase(m_items.begin() + idx);
}