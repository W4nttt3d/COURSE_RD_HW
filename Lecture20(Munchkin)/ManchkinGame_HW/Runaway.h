#pragma once
#include <string>

class Munchkin;

class Runaway
{
public:
	virtual void apply(Munchkin* munchkin) = 0;

	virtual std::string getFullInfo() const { return ""; }
	static Runaway* parseRunawayPolicy(const std::string& type, std::stringstream& ss);
};

class RunawayPolicy
{
public:
	virtual void apply(Munchkin* munchkin) = 0;
	virtual std::string getFullInfo() const = 0;
};

class Runaway_LevelDowngrade : public Runaway
{
public:
	Runaway_LevelDowngrade(int level = 1) : m_levelToDowngrade(level) {}
	void apply(Munchkin* munchkin) override;
	std::string getFullInfo() const override;

protected:
	int m_levelToDowngrade;
};

class Runaway_LevelDowngradeIf : public Runaway_LevelDowngrade
{
public:
	Runaway_LevelDowngradeIf(int level, int minimalMunchkinLevel) 
		: Runaway_LevelDowngrade(level), m_minimalMunchkinLevelToApply(minimalMunchkinLevel) {}

	void apply(Munchkin* munchkin) override;
	std::string getFullInfo() const override;

private:
	int m_minimalMunchkinLevelToApply;
};

//Remove a card from hand(modifier) at random
class Runaway_ModifierFromHandRemoval : public Runaway
{
public:
	void apply(Munchkin* munchkin) override;
	std::string getFullInfo() const override;
};

//Random item removal
class Runaway_ItemEquipedRemoval : public Runaway
{
public:
	void apply(Munchkin* munchkin) override;
	std::string getFullInfo() const override;
};

//Remove equiped item from Outfit with biggest base power
class Runaway_BiggestBonusCardRemoval : public Runaway
{
public:
	void apply(Munchkin* munchkin) override;
	std::string getFullInfo() const override;
};

