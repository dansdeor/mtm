#include "Character.h"

using mtm::Team;
using mtm::units_t;


Character::Character(Team team, units_t health, units_t ammo, units_t range, units_t power) :
		team(team), health(health), ammo(ammo), range(range), power(power)
{}


mtm::units_t Character::getHealth() const
{
	return health;
}


void Character::addToHealth(mtm::units_t amount)
{
	health += amount;
}


mtm::Team Character::getTeam() const
{
	return team;
}
