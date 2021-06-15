#ifndef MEDIC_H
#define MEDIC_H

#include "Character.h"

class Medic : public Character {
private:
	static const mtm::units_t MOVING_RANGE = 5;
	static const mtm::units_t ATTACK_COST = 1;
	static const mtm::units_t RELOAD_AMOUNT = 5;
public:
	Medic(mtm::Team team, mtm::units_t health, mtm::units_t ammo, mtm::units_t range, mtm::units_t power);

	~Medic() override = default;

	mtm::CharacterType getType() const override;

	mtm::units_t getMovingRange() const override;

	Character* clone() const override;

	void attackTarget(std::shared_ptr<Character> target, const mtm::GridPoint& attacker_coordinates,
					  const mtm::GridPoint& target_coordinates) override;

	void attackNeighbor(std::shared_ptr<Character> target, mtm::units_t range_from_dst) override;

	void reload() override;
};


#endif //MEDIC_H
