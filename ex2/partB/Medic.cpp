#include "Medic.h"
#include "Exceptions.h"

using mtm::Team;
using mtm::units_t;


Medic::Medic(Team team, units_t health, units_t ammo, units_t range, units_t power)
		: Character(team, health, ammo, range, power)
{}


mtm::CharacterType Medic::getType() const
{
	return mtm::MEDIC;
}


mtm::units_t Medic::getMovingRange() const
{
	return Medic::MOVING_RANGE;
}


Character* Medic::clone() const
{
	return new Medic(team, health, ammo, range, power);
}


void Medic::attackTarget(std::shared_ptr<Character> target, const mtm::GridPoint& attacker_coordinates,
						 const mtm::GridPoint& target_coordinates)
{
	if (range < mtm::GridPoint::distance(attacker_coordinates, target_coordinates)) {
		throw mtm::OutOfRange();
	}
	if (target == nullptr) {
		throw mtm::IllegalTarget();
	}
	if (this == target.get()) {
		throw mtm::IllegalTarget();
	}
	if (this->team == target->getTeam()) {
		target->addToHealth(power);
	}
	else {
		if (ammo < ATTACK_COST) {
			throw mtm::OutOfAmmo();
		}
		target->addToHealth(-power);
		ammo -= ATTACK_COST;
	}
}


void Medic::attackNeighbor(std::shared_ptr<Character> target, mtm::units_t range_from_dst)
{
}


void Medic::reload()
{
	ammo += RELOAD_AMOUNT;
}


