#include "Runaway.h"
#include "Munchkin.h"
#include <cstdlib>
#include "Item.h"
#include "fstream"
#include "sstream"

void Runaway_LevelDowngrade::apply(Munchkin* munchkin)
{
	munchkin->updateLevelBy(-m_levelToDowngrade);
}

std::string Runaway_LevelDowngrade::getFullInfo() const
{
    return "Level Downgrade by " + std::to_string(m_levelToDowngrade);
}


void Runaway_LevelDowngradeIf::apply(Munchkin* munchkin)
{
	if (munchkin->getLevel() >= m_minimalMunchkinLevelToApply)
	{
		Runaway_LevelDowngrade::apply(munchkin);
	}
}

std::string Runaway_LevelDowngradeIf::getFullInfo() const
{
	return "Level Downgrade by " + std::to_string(m_levelToDowngrade) + " if Munchkin level >= " + std::to_string(m_minimalMunchkinLevelToApply);
}

void Runaway_ModifierFromHandRemoval::apply(Munchkin* munchkin)
{
	if (!munchkin->getModifiers().empty())
	{
		int randomIndex = std::rand() % munchkin->getItems().size();
		munchkin->removeModifierFromHand(randomIndex);
	}
}

std::string Runaway_ModifierFromHandRemoval::getFullInfo() const
{
    return "Will lose 1 card from the hand";
}

void Runaway_ItemEquipedRemoval::apply(Munchkin* munchkin)
{
	if (!munchkin->getItems().empty())
	{
		int randomIndex = std::rand() % munchkin->getItems().size();
		munchkin->removeItemEquipped(randomIndex);
	}
}

std::string Runaway_ItemEquipedRemoval::getFullInfo() const
{
    return "Random item removal";
}

void Runaway_BiggestBonusCardRemoval::apply(Munchkin* munchkin)
{
	const std::vector<Item*>& items = munchkin->getItems();
	
	if (items.empty())
	{
		return; 
	}

	int maxIndex = 0;
	int maxPower = items[0]->getBasePower();

	for (int i = 1; i < items.size(); ++i)
	{
		int currentPower = items[i]->getBasePower();
		if (currentPower > maxPower)
		{
			maxPower = currentPower;
			maxIndex = i;
		}
	}

	munchkin->removeItemEquipped(maxIndex);
}

std::string Runaway_BiggestBonusCardRemoval::getFullInfo() const
{
    return "Will lose the equipped item with the biggest base power";
}