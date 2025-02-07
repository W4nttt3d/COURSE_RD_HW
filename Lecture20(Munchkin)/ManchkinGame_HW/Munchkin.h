#pragma once
#include <vector>
#include <string>
#include "Tribe.h"

class Item;
class Modifier;

using uint = unsigned int;

class Munchkin
{
public:
	Munchkin() = default;
	Munchkin(const std::string& name, Tribe tribe) : m_name(name), m_tribe(tribe) {}

	void setName(const std::string& name) { m_name = name; }
	const std::string& getName() const { return m_name; }

	void setTribe(const Tribe tribe) { m_tribe = tribe; }
	Tribe getTribe() const { return m_tribe; }

	int getLevel() const { return m_level; }
	void updateLevelBy(int levels);

	void addItem(Item* item);
	void addItems(const std::vector<Item*>& items);
	const std::vector<Item*>& getItems() const;

	Modifier* popModifier(int idx);
	const std::vector<Modifier*>& getModifiers() const { return m_modifiers; }
	void addModifiers(const std::vector<Modifier*>& modifiers);

	void addModifier(Modifier* modifier);

	void removeModifierFromHand(int idx);
	void removeItemEquipped(int idx);

private:
	uint m_level = 1;
	std::string m_name;

	std::vector<Item*> m_items;
	std::vector<Modifier*> m_modifiers;

	Tribe m_tribe;
};