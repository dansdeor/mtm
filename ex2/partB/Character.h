#ifndef CHARACTER_H
#define CHARACTER_H

#include <vector>
#include <memory>

#include "Auxiliaries.h"

class Character {
protected:
	mtm::Team team;
	mtm::units_t health;
	mtm::units_t ammo;
	mtm::units_t range;
	mtm::units_t power;

public:
	Character(mtm::Team team, mtm::units_t health, mtm::units_t ammo, mtm::units_t range, mtm::units_t power);

	virtual ~Character() = default;

	mtm::units_t getHealth() const;

	void addToHealth(mtm::units_t amount);

	mtm::Team getTeam() const;

	virtual mtm::CharacterType getType() const = 0;

	virtual mtm::units_t getMovingRange() const = 0;

	//Creates a clone of the same class object, even for inherited ones because of the virtual keyword
	virtual Character* clone() const = 0;

	//Used to attack the chosen target coordinates specifically
	virtual void attackTarget(std::shared_ptr<Character> target, const mtm::GridPoint& attacker_coordinates,
							  const mtm::GridPoint& target_coordinates) = 0;

	//Used to attack all the characters in the board which answer rhe attack demands
	virtual void attackNeighbor(std::shared_ptr<Character> target, mtm::units_t range_from_dst) = 0;

	virtual void reload() = 0;
};


#endif //CHARACTER_H
