#include "Medic.h"

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


void Medic::attack(const mtm::GridPoint& src, const mtm::GridPoint& dst,
				   const std::vector<std::vector<std::shared_ptr<Character>>>& board)
{

}


void Medic::reload()
{

}
