#include "Sniper.h"

using mtm::Team;
using mtm::units_t;


Sniper::Sniper(Team team, units_t health, units_t ammo, units_t range, units_t power)
		: Character(team, health, ammo, range, power)
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


void Sniper::attack(const mtm::GridPoint& src, const mtm::GridPoint& dst,
					const std::vector<std::vector<std::shared_ptr<Character>>>& board)
{

}


void Sniper::reload()
{

}
