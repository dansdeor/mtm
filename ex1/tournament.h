#ifndef TOURNAMENT_H_
#define TOURNAMENT_H_

#include <stdbool.h>
#include "mtm_map/map.h"


typedef struct tournament_t* Tournament;


typedef enum {
	STARTED, ENDED
} TournamentStatus;


Tournament copyTournament(Tournament tournament);

int* copyTournamentId(int* tournament_id);

void freeTournament(Tournament tournament);

void freeTournamentId(int* tournament_id);

Tournament createTournament(int max_games_per_player,
							const char* tournament_location);

int getMaxGamesPerPlayer(Tournament tournament);

const char* getTournamentLocation(Tournament tournament);

//Map const getTournamentGames(Tournament tournament);

bool isTournamentLocationLegal(const char* location);


#endif /* TOURNAMENT_H_ */