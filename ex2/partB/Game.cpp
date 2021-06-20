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
	if (board[coordinates.row][coordinates.col] != nullptr) {
		throw mtm::CellOccupied();
	}
	board[coordinates.row][coordinates.col] = character;
}


std::shared_ptr<Character> Game::makeCharacter(mtm::CharacterType type, mtm::Team team,
											   mtm::units_t health, mtm::units_t ammo,
											   mtm::units_t range, mtm::units_t power)
{
	if (health <= 0 || ammo < 0 || range < 0 || power < 0) {
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
	shared_ptr<Character> attacker = board[src_coordinates.row][src_coordinates.col];
	attacker->attackTarget(board[dst_coordinates.row][dst_coordinates.col], src_coordinates, dst_coordinates);
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			mtm::GridPoint target_coordinates(i, j);
			attacker->attackNeighbor(board[i][j], mtm::GridPoint::distance(target_coordinates, dst_coordinates));
			if (board[i][j] != nullptr && board[i][j]->getHealth() <= 0) {
				board[i][j] = nullptr;
			}
		}
	}

}


void Game::reload(const mtm::GridPoint& coordinates)
{
	if (!isCellLegal(coordinates)) {
		throw mtm::IllegalCell();
	}
	if (board[coordinates.row][coordinates.col] == nullptr) {
		throw mtm::CellEmpty();
	}
	board[coordinates.row][coordinates.col]->reload();
}


std::ostream& operator<<(std::ostream& os, const Game& game)
{
	char* textual_board = new char[game.height * game.width];
	for (int i = 0; i < game.height; i++) {
		for (int j = 0; j < game.width; j++) {
			if (game.board[i][j] == nullptr) {
				textual_board[i * game.width + j] = Game::EMPTY_CELL;
			}
			else {
				switch (game.board[i][j]->getType()) {
					case mtm::CharacterType::SOLDIER:
						textual_board[i * game.width + j] = Game::SOLDIER_CELL;
						break;
					case mtm::CharacterType::MEDIC:
						textual_board[i * game.width + j] = Game::MEDIC_CELL;
						break;
					case mtm::CharacterType::SNIPER:
						textual_board[i * game.width + j] = Game::SNIPER_CELL;
						break;
				}
				if (game.board[i][j]->getTeam() == mtm::Team::CROSSFITTERS) {
					textual_board[i * game.width + j] = (char) std::tolower(textual_board[i * game.width + j]);
				}
			}
		}
	}
	mtm::printGameBoard(os, textual_board, textual_board + game.height * game.width, game.width);
	delete[] textual_board;
	return os;
}


bool Game::isOver(mtm::Team* winningTeam) const
{
	bool powerlifters_left = false;
	bool crossfitters_left = false;
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (board[i][j] != nullptr) {
				if (board[i][j]->getTeam() == mtm::Team::POWERLIFTERS) {
					powerlifters_left = true;
				}
				else {
					crossfitters_left = true;
				}
			}
		}
	}
	if (winningTeam != nullptr && powerlifters_left && !crossfitters_left) {
		*winningTeam = mtm::Team::POWERLIFTERS;
	}
	else if (winningTeam != nullptr && !powerlifters_left && crossfitters_left) {
		*winningTeam = mtm::Team::CROSSFITTERS;
	}
	if (powerlifters_left == crossfitters_left) {
		return false;
	}
	return true;
}


bool Game::isCellLegal(const mtm::GridPoint& coordinates) const
{
	return (0 <= coordinates.row && coordinates.row < height) && (0 <= coordinates.col && coordinates.col < width);
}
