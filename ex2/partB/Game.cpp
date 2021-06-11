#include "Game.h"

#include "Soldier.h"
#include "Medic.h"
#include "Sniper.h"
#include "Exceptions.h"

using std::vector;
using std::shared_ptr;


Game::Game(int height, int width) : height(height),
									width(width),
									board(height, vector<shared_ptr<Character>>(width))
{}


Game::Game(const Game& other) : height(other.height),
								width(other.width),
								board(height, vector<shared_ptr<Character>>(width))
{
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (other.board[i][j] != nullptr) {
				board[i][j] = shared_ptr<Character>(other.board[i][j]->clone());
			}
		}
	}
}


Game& Game::operator=(const Game& other)
{
	if (this == &other) {
		return *this;
	}
	vector<vector<shared_ptr<Character>>> copied_board(other.height, vector<shared_ptr<Character>>(other.width));
	for (int i = 0; i < other.height; i++) {
		for (int j = 0; j < other.width; j++) {
			if (other.board[i][j] != nullptr) {
				copied_board[i][j] = shared_ptr<Character>(other.board[i][j]->clone());
			}
		}
	}
	board = copied_board;
	height = other.height;
	width = other.width;
	return *this;
}


void Game::addCharacter(const mtm::GridPoint& coordinates, std::shared_ptr<Character> character)
{
	if (!isCellLegal(coordinates)) {
		throw mtm::IllegalCell();
	}
	if (board[coordinates.row][coordinates.col] == nullptr) {
		throw mtm::CellOccupied();
	}
	board[coordinates.row][coordinates.col] = character;
}


std::shared_ptr<Character> Game::makeCharacter(mtm::CharacterType type, mtm::Team team,
											   mtm::units_t health, mtm::units_t ammo,
											   mtm::units_t range, mtm::units_t power)
{
	if (health <= 0 || ammo < 0 || range <= 0 || power < 0) {//TODO: need to check this values again
		throw mtm::IllegalArgument();
	}
	switch (type) {
		case mtm::SOLDIER:
			return std::shared_ptr<Character>(new Soldier(team, health, ammo, range, power));
			break;
		case mtm::MEDIC:
			return std::shared_ptr<Character>(new Medic(team, health, ammo, range, power));
			break;
		case mtm::SNIPER:
			return std::shared_ptr<Character>(new Sniper(team, health, ammo, range, power));
			break;
		default:
			break;

	}
	return std::shared_ptr<Character>(nullptr);
}


void Game::move(const mtm::GridPoint& src_coordinates, const mtm::GridPoint& dst_coordinates)
{
	if (!isCellLegal(src_coordinates) || !isCellLegal(dst_coordinates)) {
		throw mtm::IllegalCell();
	}
	if (board[src_coordinates.row][src_coordinates.col] == nullptr) {
		throw mtm::CellEmpty();
	}
	if (board[src_coordinates.row][src_coordinates.col]->getMovingRange() <
		mtm::GridPoint::distance(src_coordinates, dst_coordinates)) {
		throw mtm::MoveTooFar();
	}
	if (board[dst_coordinates.row][dst_coordinates.col] != nullptr) {
		throw mtm::CellOccupied();
	}
	board[dst_coordinates.row][dst_coordinates.col] = board[src_coordinates.row][src_coordinates.col];
	board[src_coordinates.row][src_coordinates.col] = nullptr;
}


void Game::attack(const mtm::GridPoint& src_coordinates, const mtm::GridPoint& dst_coordinates)
{
	if (!isCellLegal(src_coordinates) || !isCellLegal(dst_coordinates)) {
		throw mtm::IllegalCell();
	}
	if (board[src_coordinates.row][src_coordinates.col] == nullptr) {
		throw mtm::CellEmpty();
	}
}


void Game::reload(const mtm::GridPoint& coordinates)
{

}


std::ostream& operator<<(std::ostream& os, const Game& game)
{

}


bool Game::isCellLegal(const mtm::GridPoint& coordinates) const
{
	return (0 <= coordinates.row && coordinates.row < height) && (0 <= coordinates.col && coordinates.col < width);
}
