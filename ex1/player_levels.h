#ifndef PLAYER_LEVELS_H_
#define PLAYER_LEVELS_H_

#include "mtm_map/map.h"

typedef struct player_level_t* PlayerLevel;

void freePlayerLevel(void* key_or_data);

Map getPlayerLevelMap(Map players);

int getPlayerLevelId(PlayerLevel player_level);

double getPlayerLevel(PlayerLevel player_level);

#endif /* PLAYER_LEVELS_H_ */
