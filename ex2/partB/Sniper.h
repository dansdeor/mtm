#ifndef SNIPER_H
#define SNIPER_H

#include "Character.h"

class Sniper : public Character {
private:
	static const int ATTACK_MODULE = 3;
	static const mtm::units_t MOVING_RANGE = 4;
	static const mtm::units_t ATTACK_COST = 1;
	static const mtm::units_t RELOAD_AMOUNT = 2;
	int attack_sequence;
public:
	Sniper(mtm::Team team, mtm::units_t health, mtm::units_t ammo, mtm::units_t range, mtm::units_t power);

	~Sniper() override = default;

	mtm::CharacterType getType() const override;

	mtm::units_t getMovingRange() const override;

	Character* clone() const override;

	void attackTarget(std::shared_ptr<Character> target, const mtm::GridPoint& attacker_coordinates,
					  const mtm::GridPoint& target_coordinates) override;

	void attackNeighbor(std::shared_ptr<Character> target, mtm::units_t range_from_dst) override;

	void reload() override;
};


#endif //SNIPER_H
