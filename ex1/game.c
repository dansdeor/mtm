#include "game.h"
#include "stdlib.h"


struct game_t {
	int first_player_id;
	int second_player_id;
	Winner winner;
	int play_time;
};


void* copyGame(void* game)
{
	if (!game) {
		return NULL;
	}
	return createGame(((Game) game)->first_player_id,
					  ((Game) game)->second_player_id,
					  ((Game) game)->winner,
					  ((Game) game)->play_time);
}


void* copyGameIndex(void* game_index)
{
	if (!game_index) {
		return NULL;
	}
	int* new_game_index = malloc(sizeof(*new_game_index));
	if (!new_game_index) {
		return NULL;
	}
	*new_game_index = *(int*) game_index;
	return new_game_index;
}


void freeGame(void* game)
{
	free(game);
}


void freeGameIndex(void* game_index)
{
	free(game_index);
}


int compareGameIndex(void* first_game_index, void* second_game_index)
{
	if (!first_game_index || !second_game_index) {
		return 0;
	}
	return *(int*) first_game_index - *(int*) second_game_index;
}


Game createGame(int first_player_id, int second_player_id, Winner winner, int play_time)
{
	Game game = malloc(sizeof(*game));
	if (!game) {
		return NULL;
	}
	game->first_player_id = first_player_id;
	game->second_player_id = second_player_id;
	game->winner = winner;
	game->play_time = play_time;
	return game;
}

int getFirstPlayerId(Game game)
{
	if (!game) {
		return 0;
	}
	return game->first_player_id;
}


int getSecondPlayerId(Game game)
{
	if (!game) {
		return 0;
	}
	return game->second_player_id;
}
