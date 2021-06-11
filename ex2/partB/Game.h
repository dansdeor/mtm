#ifndef GAME_H
#define GAME_H

#include <memory>
#include <vector>
#include <iostream>

#include "Character.h"
#include "Auxiliaries.h"

class Game {
private:
	int height;
	int width;
	std::vector<std::vector<std::shared_ptr<Character>>> board;

	bool isCellLegal(const mtm::GridPoint& coordinates) const;

public:
	Game(int height, int width);

	~Game() = default;

	Game(const Game& other);

	Game& operator=(const Game& other);

	void addCharacter(const mtm::GridPoint& coordinates, std::shared_ptr<Character> character);

	static std::shared_ptr<Character> makeCharacter(mtm::CharacterType type, mtm::Team team,
													mtm::units_t health, mtm::units_t ammo,
													mtm::units_t range, mtm::units_t power);

	void move(const mtm::GridPoint& src_coordinates, const mtm::GridPoint& dst_coordinates);

	void attack(const mtm::GridPoint& src_coordinates, const mtm::GridPoint& dst_coordinates);

	void reload(const mtm::GridPoint& coordinates);

	friend std::ostream& operator<<(std::ostream& os, const Game& game);
};


#endif //GAME_H
