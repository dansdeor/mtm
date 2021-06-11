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

	virtual mtm::CharacterType getType() const = 0;

	virtual mtm::units_t getMovingRange() const = 0;

	virtual Character* clone() const = 0;

	virtual void attack(const mtm::GridPoint& src, const mtm::GridPoint& dst,
						const std::vector<std::vector<std::shared_ptr<Character>>>& board) = 0;

	virtual void reload() = 0;
};


#endif //CHARACTER_H
