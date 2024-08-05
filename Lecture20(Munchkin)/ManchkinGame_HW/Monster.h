#pragma once
#include <string>
#include "Tribe.h"
#include "Runaway.h"
#include "Victory.h"

class Runaway;
class VictoryPolicy;

class Monster
{
public:
    Monster(const std::string& name, int level = 1, Tribe tribe = Tribe::Human, Runaway* runawayPolicy = nullptr, VictoryPolicy* victoryPolicy = nullptr)
        : m_name(name), m_level(level), m_tribe(tribe), m_RunawayPolicy(runawayPolicy), m_VictoryPolicy(victoryPolicy) {}

    Tribe getTribe() const { return m_tribe; }
    unsigned int getLevel() const { return m_level; }
    const std::string& getName() const { return m_name; }

    Runaway* getRunawayPolicy() const { return m_RunawayPolicy; }
    VictoryPolicy* getVictoryPolicy() const { return m_VictoryPolicy; }

    std::string getFullInfo() const
    {
        std::string info = "Monster " + getName() + ", level " + std::to_string(getLevel()) + ".";
        if (m_RunawayPolicy)
        {
            info += " Runaway: " + m_RunawayPolicy->getFullInfo();
        }
        if (m_VictoryPolicy)
        {
            info += " Victory: " + m_VictoryPolicy->getFullInfo();
        }
        return info;
    }

private:
    unsigned int m_level = 1;
    Tribe m_tribe = Tribe::Human;
    std::string m_name;

	Runaway* m_RunawayPolicy = nullptr;
    VictoryPolicy* m_VictoryPolicy = nullptr;
};