#include "MonsterDeck.h"
#include "DeckSelectionHelper.h"
#include "Monster.h"
#include "Runaway.h"
#include "Victory.h"
#include "fstream"
#include "sstream"

Tribe parseTribe(const std::string& tribeStr) {
	if (tribeStr == "Human") 
	{
		return Tribe::Human;
	}
	else if (tribeStr == "Zombie") 
	{
		return Tribe::Zombie;
	}
	else if (tribeStr == "Undead") 
	{
		return Tribe::Undead;
	}
	else if (tribeStr == "God") 
	{
		return Tribe::God;
	}
	else 
	{
		throw std::runtime_error("Unknown tribe: " + tribeStr);
	}
}

Runaway* parseRunawayPolicy(const std::string& type, std::stringstream& ss, int& step)
{
	if (type == "Runaway_LevelDowngrade")
	{
		int level;
		ss >> level;
		step = 1;
		return new Runaway_LevelDowngrade{ level };
	}
	else if (type == "Runaway_LevelDowngradeIf")
	{
		int level1, level2;
		ss >> level1;
		ss.ignore(1, ';');
		ss >> level2;
		step = 2;
		return new Runaway_LevelDowngradeIf{ level1, level2 };
	}
	else if (type == "Runaway_ItemEquipedRemoval")
	{
		return new Runaway_ItemEquipedRemoval{};
	}
	else if (type == "Runaway_ModifierFromHandRemoval")
	{
		return new Runaway_ModifierFromHandRemoval{};
	}
	else if (type == "Runaway_BiggestBonusCardRemoval")
	{
		return new Runaway_BiggestBonusCardRemoval{};
	}
	throw std::runtime_error("Unknown runaway effect type: " + type);
}

VictoryPolicy* parseVictoryPolicy(const std::string& victoryType, std::stringstream& ss, ItemDeck* itemDeck, ModifierDeck* modifierDeck) {
	if (victoryType == "Victory_LevelBonus")
	{
		int bonus;
		ss >> bonus;
		return new Victory_LevelBonus{ bonus };
	}
	else if (victoryType == "Victory_ItemFromHandAdd")
	{
		return new Victory_ItemFromHandAdd{ itemDeck };
	}
	else if (victoryType == "Victory_ModifierFromHandAdd")
	{
		return new Victory_ModifierFromHandAdd{ modifierDeck };
	}
	throw std::runtime_error("Unknown victory effect type: " + victoryType);
}

MonsterDeck::MonsterDeck() : m_monstersDatabase(), m_deck(m_monstersDatabase)
{
	std::ifstream file("monsters_database.txt");
	if (!file.is_open())
	{
		throw std::runtime_error("Failed to open items database file.");
	}

	std::string line;
	while (std::getline(file, line))
	{
		std::stringstream ss(line);
		std::string name, levelStr, tribeStr, runawayType, victoryType;
		std::getline(ss, name, ';');
		std::getline(ss, levelStr, ';');
		int level = std::stoi(levelStr);

		std::getline(ss, tribeStr, ';');
		Tribe tribe = parseTribe(tribeStr);

		int step;
		std::getline(ss, runawayType, ';');
		Runaway* runawayPolicy = parseRunawayPolicy(runawayType, ss, step);

		ss.ignore(step, ';');
		std::getline(ss, victoryType, ';');
		VictoryPolicy* victoryPolicy = parseVictoryPolicy(victoryType, ss, m_itemDeck, m_modifierDeck);
		step = 0;

		Monster* monster = new Monster(name, level, tribe, runawayPolicy, victoryPolicy);
		m_monstersDatabase.push_back(monster);
	}

	file.close();
	m_deck = DeckSelectionHelper<Monster>(m_monstersDatabase);
}

MonsterDeck::~MonsterDeck()
{
	for (Monster* monster : m_monstersDatabase)
	{
		delete monster;
	}
}

Monster* MonsterDeck::generateMonster() 
{
	return m_deck.generate();
}