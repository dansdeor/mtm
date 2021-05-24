#ifndef PLAYER_LEVELS_H_
#define PLAYER_LEVELS_H_

#include "mtm_map/map.h"

typedef struct player_level_t* PlayerLevel;

/*
 * createPlayerLevelMap: returns new map containing as a key and as the value the id and the level of the player
 * returns NULL if players is pointing to NULL or allocation fails
 */
Map createPlayerLevelMap(Map players);

/*
 * freePlayerKeyOrLevel: free the key or the data
 */
void freePlayerKeyOrLevel(void* key_or_data);

/*
 * getPlayerLevelId: returns the id of the player or INVALID_PLAYER_ID if player_level is pointing to NULL
 */
int getPlayerLevelId(PlayerLevel player_level);

/*
 * getPlayerLevel: returns the level of the player or 0 if player_level is pointing to NULL
 */
double getPlayerLevel(PlayerLevel player_level);

#endif /* PLAYER_LEVELS_H_ */
