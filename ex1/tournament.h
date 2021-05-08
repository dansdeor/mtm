#ifndef TOURNAMENT_H_
#define TOURNAMENT_H_

#include <stdbool.h>
#include "mtm_map/map.h"


typedef struct tournament_t* Tournament;


typedef enum {
	STARTED, ENDED
} TournamentStatus;


void* copyTournament(void* tournament);

void* copyTournamentId(void* tournament_id);

void freeTournament(void* tournament);

void freeTournamentId(void* tournament_id);

int compareTournamentId(void* first_tournament_id, void* second_tournament_id);

Tournament createTournament(int max_games_per_player, const char* tournament_location, TournamentStatus status);

int getMaxGamesPerPlayer(Tournament tournament);

int getPlayerParticipationNumber(Tournament tournament, int player_id);

//Map const getTournamentGames(Tournament tournament);



#endif /* TOURNAMENT_H_ */