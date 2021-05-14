#include "player.h"
#include <stdlib.h>


struct player_t {
	int score;
	int num_wins;
	int num_loses;
	int num_draws;
};


void* copyPlayer(void* player)
{
	if (!player) {
		return NULL;
	}
	Player new_player = malloc(sizeof(*new_player));
	if (!new_player) {
		return NULL;
	}
	new_player->score = ((Player) player)->score;
	new_player->num_wins = ((Player) player)->num_wins;
	new_player->num_loses = ((Player) player)->num_loses;
	new_player->num_draws = ((Player) player)->num_draws;
	return new_player;
}


void* copyPlayerId(void* player_id)
{
	if (!player_id) {
		return NULL;
	}
	int* new_player_id = malloc(sizeof(*new_player_id));
	if (!new_player_id) {
		return NULL;
	}
	*new_player_id = *(int*) player_id;
	return new_player_id;
}


void freePlayer(void* player)
{
	free(player);
}


void freePlayerId(void* player_id)
{
	free(player_id);
}


int comparePlayerId(void* first_player_id, void* second_player_id)
{
	return *(int*) first_player_id - *(int*) second_player_id;
}


Player createPlayer()
{
	Player player = malloc(sizeof(*player));
	if (!player) {
		return NULL;
	}
	player->score = 0;
	player->num_wins = 0;
	player->num_loses = 0;
	player->num_draws = 0;
	return player;
}


int getPlayerScore(Player player)
{
	if (!player) {
		return 0;
	}
	return player->score;
}


int getPlayerWins(Player player)
{
	if (!player) {
		return 0;
	}
	return player->num_wins;
}


int getPlayerLoses(Player player)
{
	if (!player) {
		return 0;
	}
	return player->num_loses;
}


int getPlayerDraws(Player player)
{
	if (!player) {
		return 0;
	}
	return player->num_draws;
}


void setPlayerScore(Player player, int score)
{
	if (!player) {
		return;
	}
	player->score = score;
}


void setPlayerWins(Player player, int num_wins)
{
	if (!player) {
		return;
	}
	player->num_wins = num_wins;
}


void setPlayerLoses(Player player, int num_loses)
{
	if (!player) {
		return;
	}
	player->num_loses = num_loses;
}


void setPlayerDraws(Player player, int num_draws)
{
	if (!player) {
		return;
	}
	player->num_draws = num_draws;
}
