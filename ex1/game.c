#include "game.h"
#include "stdlib.h"


struct game_t {
	int first_player;
	int second_player;
	Winner winner;
	int play_time;
};


void* copyGame(void* game)
{
	if (!game) {
		return NULL;
	}
	return createGame(((Game) game)->first_player,
					  ((Game) game)->second_player,
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


Game createGame(int first_player, int second_player, Winner winner, int play_time)
{
	Game game = malloc(sizeof(*game));
	if (!game) {
		return NULL;
	}
	game->first_player = first_player;
	game->second_player = second_player;
	game->winner = winner;
	game->play_time = play_time;
	return game;
}
