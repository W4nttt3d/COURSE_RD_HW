#include "Fight.h"

#include "Item.h"
#include "Modifier.h"
#include "Munchkin.h"
#include "Monster.h"
#include "Runaway.h"
#include "Victory.h"

#include <iostream>


void Fight::start()
{
	m_result = FightResult::InProgress;

	calculateMunchkinPower();
	calculateMonsterPower();
}

void Fight::applyModifier(int choice)
{
	Modifier* modifier = m_munchkin->popModifier(choice);
	if (modifier == nullptr)
	{
		std::cerr << "Error: Modifier is null. Check if the choice is valid or if the modifier was removed." << std::endl;
		return;
	}

	modifier->apply(m_munchkin, m_monster);

	m_MunchkinPower += modifier->getMunchkinModifier();
	m_monsterPower += modifier->getMonsterModifier();
}

void Fight::runawayFlow()
{
	Runaway* policy = m_monster->getRunawayPolicy();
	policy->apply(m_munchkin);

	m_result = FightResult::MonsterWon;
}

void Fight::victoryFlow()
{
	m_munchkin->updateLevelBy(1);

	VictoryPolicy* policy = m_monster->getVictoryPolicy();
	policy->apply(m_munchkin);

	m_result = FightResult::MunchkinWon;
}

template <typename T, typename Y>
void calculateTribePower(T* fighter1, Y* fighter2, int& power)
{
	if (fighter1->getTribe() == Tribe::Human && fighter2->getTribe() == Tribe::Zombie)
	{
		power += 2;
	}
	else if (fighter1->getTribe() == Tribe::God && fighter2->getTribe() == Tribe::Undead)
	{
		power += 3;
	}
}

void Fight::calculateMunchkinPower()
{
	m_MunchkinPower += m_munchkin->getLevel();
	
	for (Item* item : m_munchkin->getItems())
	{
		m_MunchkinPower += item->getPower(m_monster->getTribe());
	}

	calculateTribePower(m_munchkin, m_monster, m_MunchkinPower);
}

void Fight::calculateMonsterPower()
{
	m_monsterPower = m_monster->getLevel();

	calculateTribePower(m_monster, m_munchkin, m_monsterPower);
}
