#include "Game.h"

#include <iostream>
#include <chrono> //for sleep delays
#include <thread> //for sleep delays
#include <time.h> //for rand generator init

#include "Fight.h"
#include "Item.h"
#include "ItemDeck.h"
#include "Modifier.h"
#include "Monster.h"

namespace UI
{
	void printDelayWithText(int count, std::string text)
	{
		std::cout << text;

		for (int i = 0; i < count; i++)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(700));
			std::cout << ".";
		}
		std::cout << std::endl;
	}

void printTossing()
{
	UI::printDelayWithText(5, "\nTossing the deck");
}

void printMonsterSelection()
{
	UI::printDelayWithText(5, "\nSelecting monster card");
}

void printMunchkinWon()
{
	std::cout << "CONGRATS: MunchkinG WON!\n\n";
}

void pressAnyKeyToContinue()
{
	char anyKey;
	std::cout << "\n\nPress any key to start a round...";
	std::cin >> anyKey;
}

void printMunchkinLost(Monster* monster)
{
	std::cout << "-------YOU'VE LOST to \"" << monster->getName() << "\"Monster!---------\n";
}

std::string getTribeString(Tribe tribe)
{
	switch (tribe)
	{
	case Tribe::Human: return "HUMAN";
	case Tribe::Undead: return "UNDEAD";
	case Tribe::Zombie: return "ZOMBIE";
	case Tribe::God: return "GOD";
	default:
		return "";
	}
}

void printIntro(Munchkin* munchkin)
{
	std::cout << "WELCOME TO TEXT-BASED MANCKIN GAME!!!\n";
	std::cout << "Enter your Munchkin name: ";
	std::string name;
	std::cin >> name;
	munchkin->setName(name);

	std::cout << "Enter your Munchkin tribe: ";
	for (int i = 0; i <= static_cast<int>(Tribe::God); ++i)
	{
		Tribe tribe = static_cast<Tribe>(i);
		std::cout << std::endl << i + 1 << ". " << getTribeString(tribe);
	}

	std::cout << std::endl;

	int tribeNumber;
	std::cin >> tribeNumber;
	switch (tribeNumber)
	{
	case 1: 
		munchkin->setTribe(Tribe::Human);
		break;
	case 2:
		munchkin->setTribe(Tribe::Undead);
		break;
	case 3:
		munchkin->setTribe(Tribe::Zombie);
		break;
	case 4:
		munchkin->setTribe(Tribe::God);
		break;
	default:
		munchkin->setTribe(Tribe::Human);
		break;
	}

	UI::printTossing();
}

void printItems(Munchkin* munchkin)
{
	const std::vector<Item*>& items = munchkin->getItems();
	std::cout << "--------OUTFIT-----------\n";
	for (Item* item : items)
	{
		std::cout << item->getFullInfo();
	}
}

void printModifiers(Munchkin* munchkin)
{
	const std::vector<Modifier*> modifiers = munchkin->getModifiers();
	std::cout << "\n---------HAND CARDS----------\n";
	int idx = 1;
	for (Modifier* modifier : munchkin->getModifiers())
	{
		std::cout << idx++ << ". " << modifier->getFullInfo() << std::endl;
	}
}

void printPlayerDeck(Munchkin* munchkin)
{
	std::cout << std::endl << "\nMunchkin " << "\"" << munchkin->getName() << "\", level " << munchkin->getLevel() << "\", tribe " << getTribeString(munchkin->getTribe()) << std::endl;
	printItems(munchkin);
	printModifiers(munchkin);
}

void printMunchkinPower(Munchkin* munchkin, Fight* fight)
{
	std::cout << "-----\"" << munchkin->getName() << "\" power: " << fight->getMunchkinPower() << "-------\n";
}

void printMonsterPower(Monster* monster, Fight* fight)
{
	std::cout << "-----\"" << monster->getName() << "\" power: " << fight->getMonsterPower() << "-------\n";
}

enum class UserInput
{
	None,
	Runaway,
	ApplyModifier
};

UserInput readUserBehavior()
{
	std::cout << "Use card from Hand or Runaway?(M/R)";
	char choice;
	std::cin >> choice;
	choice = std::toupper(choice);

	switch (choice)
	{
	case 'R':
		return UserInput::Runaway;
	case 'M':
		return UserInput::ApplyModifier;
	default:
		return UserInput::None;
	}
}

int selectModifierFromHand(unsigned short handSize)
{
	std::cout << "Select card from HAND: ";
	int choice = -1;
	std::cin >> choice;

	if (choice > handSize || choice <= 0)
	{
		choice = -1;
	}

	return choice;
}

void printCurrentFightResult(int powerDifference)
{
	std::cout << "You are missing " << std::abs(powerDifference) << " power!\n\n";
}

void printMonsterInfo(Monster* monster)
{
	std::cout << "\n--------Monster \"" << monster->getName() << "\"" << ", of " <<
		UI::getTribeString(monster->getTribe()) << ", level " << monster->getLevel() << " --------" << std::endl << std::endl;
	std::cout << monster->getRunawayPolicy()->getFullInfo() << std::endl; 
}
} //namespace UI

void Game::run()
{
	constexpr uint WinningLevel = 10;

	std::srand(static_cast<int>(std::time(0)));
	UI::printIntro(&m_munchkin);
	
	generateMunchkinInitialCards();

	while (m_munchkin.getLevel() < WinningLevel)
	{
		UI::printPlayerDeck(&m_munchkin);
		
		UI::pressAnyKeyToContinue();
		UI::printMonsterSelection();

		Monster* monster = generateMonster();
		UI::printMonsterInfo(monster);

		Fight fight;
		fight.setMonster(monster);
		fight.setMunchkin(&m_munchkin);

		fight.start();
		
		//Fight loop
		while (!fight.getFinish())
		{
			const int munchkinMonsterDifference = fight.getMunchkinMonsterPowerDifference();
			UI::printMunchkinPower(&m_munchkin, &fight);
			UI::printMonsterPower(monster, &fight);

			if (munchkinMonsterDifference > 0)	//WINNING CASE
			{
				fight.victoryFlow();
				UI::printMunchkinWon();
				UI::pressAnyKeyToContinue();
			}
			else  //LOSING CASE
			{
				UI::printCurrentFightResult(munchkinMonsterDifference);
				UI::UserInput input = UI::readUserBehavior();
				if (input == UI::UserInput::Runaway)
				{
					fight.runawayFlow();

					UI::printMunchkinLost(monster);
					UI::pressAnyKeyToContinue();
				}
				else if (input == UI::UserInput::ApplyModifier)
				{
					UI::printModifiers(&m_munchkin);
					const int choice = UI::selectModifierFromHand(static_cast<short>(m_munchkin.getModifiers().size()));
					
					if (choice != -1)
						fight.applyModifier(choice - 1);
				}
			}
		}
	}
}

void Game::generateMunchkinInitialCards()
{
	m_munchkin.addItems(m_itemsDeck.generateItems(1));
	m_munchkin.addModifiers(m_modifiersDeck.generateModifiers(2));
}

Monster* Game::generateMonster()
{
	return m_monstersDeck.generateMonster();
}
