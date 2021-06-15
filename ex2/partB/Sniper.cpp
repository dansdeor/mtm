#include "Sniper.h"
#include "Exceptions.h"

using mtm::Team;
using mtm::units_t;


Sniper::Sniper(Team team, units_t health, units_t ammo, units_t range, units_t power)
		: Character(team, health, ammo, range, power), attack_sequence(0)
{}


mtm::CharacterType Sniper::getType() const
{
	return mtm::SNIPER;
}


mtm::units_t Sniper::getMovingRange() const
{
	return Sniper::MOVING_RANGE;
}


Character* Sniper::clone() const
{
	return new Sniper(team, health, ammo, range, power);
}


void Sniper::attackTarget(std::shared_ptr<Character> target, const mtm::GridPoint& attacker_coordinates,
						  const mtm::GridPoint& target_coordinates)
{
	mtm::units_t range_from_attacker = mtm::GridPoint::distance(attacker_coordinates, target_coordinates);
	if (range_from_attacker < static_cast<mtm::units_t>(std::ceil(range / 2.0)) || range < range_from_attacker) {
		throw mtm::OutOfRange();
	}
	if (target == nullptr) {
		throw mtm::IllegalTarget();
	}
	if (this->team == target->getTeam()) {
		throw mtm::IllegalTarget();
	}
	if (ammo < ATTACK_COST) {
		throw mtm::OutOfAmmo();
	}
	if (attack_sequence == ATTACK_MODULE - 1) {
		target->addToHealth(-2 * power);
	}
	else {
		target->addToHealth(-power);
	}
	attack_sequence = (attack_sequence + 1) % ATTACK_MODULE;
	ammo -= ATTACK_COST;
}


void Sniper::attackNeighbor(std::shared_ptr<Character> target, mtm::units_t range_from_dst)
{
}


void Sniper::reload()
{
	ammo += RELOAD_AMOUNT;
}
