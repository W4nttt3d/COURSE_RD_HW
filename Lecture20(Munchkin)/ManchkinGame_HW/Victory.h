#pragma once
#include <vector>
#include <string>
#include "ItemDeck.h"
#include "ModifierDeck.h"
class Munchkin;
class Item;
class Modifier;

class VictoryPolicy
{
public:
    virtual void apply(Munchkin* munchkin) const = 0;
    virtual std::string getFullInfo() const = 0;
    static VictoryPolicy* parseVictoryPolicy(const std::string& victoryType, std::stringstream& ss, ItemDeck* itemDeck, ModifierDeck* modifierDeck);
};


class Victory_LevelBonus : public VictoryPolicy
{
public:
    Victory_LevelBonus(int bonusLevels) : m_bonusLevels(bonusLevels) {}

    void apply(Munchkin* munchkin) const override;
    std::string getFullInfo() const override;

private:
    int m_bonusLevels;
};

class Victory_ModifierFromHandAdd : public VictoryPolicy
{
public:
    Victory_ModifierFromHandAdd(ModifierDeck* modifierDeck) : m_modifierDeck(modifierDeck) {}

    void apply(Munchkin* munchkin) const override;
    std::string getFullInfo() const override;

private:
    ModifierDeck* m_modifierDeck;
};

class Victory_ItemFromHandAdd : public VictoryPolicy
{
public:
    Victory_ItemFromHandAdd(ItemDeck* itemDeck) : m_itemDeck(itemDeck) {}

    void apply(Munchkin* munchkin) const override;
    std::string getFullInfo() const override;

private:
    ItemDeck* m_itemDeck;
};
