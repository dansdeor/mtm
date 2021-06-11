#include "Soldier.h"

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


void Soldier::attack(const mtm::GridPoint& src, const mtm::GridPoint& dst,
					 const std::vector<std::vector<std::shared_ptr<Character>>>& board)
{

}


void Soldier::reload()
{

}
