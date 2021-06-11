#ifndef SNIPER_H
#define SNIPER_H

#include "Character.h"

class Sniper : public Character {
private:
	static const mtm::units_t MOVING_RANGE = 4;
public:
	Sniper(mtm::Team team, mtm::units_t health, mtm::units_t ammo, mtm::units_t range, mtm::units_t power);

	~Sniper() override = default;

	mtm::CharacterType getType() const override;

	mtm::units_t getMovingRange() const override;

	Character* clone() const override;

	void attack(const mtm::GridPoint& src, const mtm::GridPoint& dst,
				const std::vector<std::vector<std::shared_ptr<Character>>>& board) override;

	void reload() override;
};


#endif //SNIPER_H
