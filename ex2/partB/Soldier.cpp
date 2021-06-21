#include "Soldier.h"
#include "Exceptions.h"

using mtm::Team;
using mtm::units_t;


Soldier::Soldier(Team team, units_t health, units_t ammo, units_t range, units_t power)
		: Character(team, health, ammo, range, power)
{}


mtm::CharacterType Soldier::getType() const
{
	return mtm::SOLDIER;
}


mtm::units_t Soldier::getMovingRange() const
{
	return Soldier::MOVING_RANGE;
}


Character* Soldier::clone() const
{
	return new Soldier(team, health, ammo, range, power);
}


void Soldier::attackTarget(std::shared_ptr<Character> target, const mtm::GridPoint& attacker_coordinates,
						   const mtm::GridPoint& target_coordinates)
{
	if (range < mtm::GridPoint::distance(attacker_coordinates, target_coordinates)) {
		throw mtm::OutOfRange();
	}
	if (ammo < ATTACK_COST) {
		throw mtm::OutOfAmmo();
	}
	if (attacker_coordinates.row != target_coordinates.row && attacker_coordinates.col != target_coordinates.col) {
		throw mtm::IllegalTarget();
	}
	if (target != nullptr && this->team != target->getTeam()) {
		target->addToHealth(-power);
	}
	ammo -= ATTACK_COST;
}


void Soldier::attackNeighbor(std::shared_ptr<Character> target, mtm::units_t range_from_dst)
{
	if (0 < range_from_dst && range_from_dst <= static_cast<mtm::units_t>(std::ceil(range / 3.0))) {
		if (target != nullptr && this->team != target->getTeam()) {
			target->addToHealth(-static_cast<mtm::units_t>(std::ceil(power / 2.0)));
		}
	}
}


void Soldier::reload()
{
	ammo += RELOAD_AMOUNT;
}


