#include "player_levels.h"
#include "player.h"

#include <stdlib.h>

#define WINS_FACTOR (6)
#define LOSES_FACTOR (-10)
#define DRAW_FACTOR (2)

struct player_level_t {
	int player_id;
	double level;
};


void* copyPlayerLevel(void* key_or_data)
{
	if (!key_or_data) {
		return NULL;
	}
	PlayerLevel player_level = malloc(sizeof(*player_level));
	if (!player_level) {
		return NULL;
	}
	player_level->player_id = ((PlayerLevel) key_or_data)->player_id;
	player_level->level = ((PlayerLevel) key_or_data)->level;
	return player_level;
}


void freePlayerLevel(void* key_or_data)
{
	free(key_or_data);
}


int comparePlayerLevels(void* first_player_level, void* second_player_level)
{
	double comparing_factor = ((PlayerLevel) first_player_level)->level - ((PlayerLevel) second_player_level)->level;
	if (comparing_factor < 0) {
		return 1;
	}
	else if (comparing_factor > 0) {
		return -1;
	}
	else {
		return ((PlayerLevel) first_player_level)->player_id - ((PlayerLevel) second_player_level)->player_id;
	}
}


Map getPlayerLevelMap(Map players, int number_of_games)
{
	Map player_levels = mapCreate(copyPlayerLevel,
								  copyPlayerLevel,
								  freePlayerLevel,
								  freePlayerLevel,
								  comparePlayerLevels);
	if (!player_levels) {
		return NULL;
	}
	MAP_FOREACH(int*, player_id, players) {
		struct player_level_t player_level;
		player_level.player_id = *player_id;
		Player player = mapGet(players, player_id);
		player_level.level = (WINS_FACTOR * getPlayerWins(player) +
							  LOSES_FACTOR * getPlayerLoses(player) +
							  DRAW_FACTOR * getPlayerDraws(player)) / ((double) number_of_games);
		if (mapPut(player_levels, &player_level, &player_level) != MAP_SUCCESS) {
			freePlayerId(player_id);
			mapDestroy(player_levels);
			return NULL;
		}
		freePlayerId(player_id);
	}
	return player_levels;
}


int getPlayerLevelId(PlayerLevel player_level)
{
	if (!player_level) {
		return 0;
	}
	return player_level->player_id;
}


double getPlayerLevel(PlayerLevel player_level)
{
	if (!player_level) {
		return 0;
	}
	return player_level->level;
}
