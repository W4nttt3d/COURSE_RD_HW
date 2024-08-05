#pragma once
#include <vector>
#include "DeckSelectionHelper.h"

class Modifier;

class ModifierDeck
{
public:
    ModifierDeck();
    ~ModifierDeck();

    std::vector<Modifier*> generateModifiers(int number);
    Modifier* generateModifier();

private:
    std::vector<Modifier*> m_modifiersDatabase;
    DeckSelectionHelper<Modifier> m_deck;
};