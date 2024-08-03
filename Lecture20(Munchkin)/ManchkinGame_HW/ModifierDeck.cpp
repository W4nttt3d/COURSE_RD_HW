#include "ModifierDeck.h"
#include "DeckSelectionHelper.h"
#include "Modifier.h"
#include <fstream>
#include <sstream>

ModifierDeck::ModifierDeck() : m_modifiersDatabase(), m_deck(m_modifiersDatabase)
{
	std::ifstream file("modifiers_database.txt");
	if (!file.is_open())
	{
		throw std::runtime_error("Failed to open items database file.");
	}

	std::string line;
	while (std::getline(file, line))
	{
		std::stringstream ss(line);
		std::string type, paramStr;
		std::getline(ss, type, ';');
		std::getline(ss, paramStr);
		if (!paramStr.empty())
		{
			if (type == "SimpleModifier")
			{
				int param = std::stoi(paramStr);
				m_modifiersDatabase.push_back(new SimpleModifier{ param });
			}
			else if (type == "HalvesMonsterLevel")
			{
				if (paramStr == "Undead")
				{
					m_modifiersDatabase.push_back(new HalvesMonsterLevel{ Tribe::Undead });
				}
				else if (paramStr == "God")
				{
					m_modifiersDatabase.push_back(new HalvesMonsterLevel{ Tribe::God });
				}
				else
				{
					throw std::runtime_error("Unknown tribe: " + paramStr);
				}
			}
			else
			{
				throw std::runtime_error("Unknown modifier type with parameters: " + type);
			}
		}
		else
		{
			if (type == "DoubleMunchkinLevel")
			{
				m_modifiersDatabase.push_back(new DoubleMunchkinLevel{});
			}
			else
			{
				throw std::runtime_error("Unknown modifier type without parameters: " + type);
			}
		}
	}

	file.close();

	m_deck = DeckSelectionHelper<Modifier>(m_modifiersDatabase);
}

ModifierDeck::~ModifierDeck()
{
	for (Modifier* modifier : m_modifiersDatabase)
	{
		delete modifier;
	}
}

Modifier* ModifierDeck::generateModifier()
{
	return m_deck.generate();
}

std::vector<Modifier*> ModifierDeck::generateModifiers(int number)
{
	std::vector<Modifier*> generatedModifiers;  

	for (int i = 0; i < number; i++) 
	{
		Modifier* modifier = m_deck.generate(); 
		generatedModifiers.push_back(modifier); 
	}

	return generatedModifiers; 
}
