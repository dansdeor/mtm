#ifndef TOURNAMENT_H_
#define TOURNAMENT_H_

#include <stdbool.h>
#include "mtm_map/map.h"
#include "game.h"


typedef struct tournament_t* Tournament;


typedef enum {
	STARTED, ENDED
} TournamentStatus;


void* copyTournament(void* tournament);

void* copyTournamentId(void* tournament_id);

void freeTournament(void* tournament);

void freeTournamentId(void* tournament_id);

int compareTournamentId(void* first_tournament_id, void* second_tournament_id);

Tournament createTournament(int max_games_per_player, const char* tournament_location,
							TournamentStatus status, int max_play_time, int winner_id);

const char* getTournamentLocation(Tournament tournament);

int getMaxGamesPerPlayer(Tournament tournament);

int getPlayerParticipationNumber(Tournament tournament, int player_id);

Map getTournamentGames(Tournament tournament);

int getTournamentNumberOfGames(Tournament tournament);

TournamentStatus getTournamentStatus(Tournament tournament);

int getTournamentWinner(Tournament tournament);

int getTournamentMaxPlayTime(Tournament tournament);

double getTournamentAveragePlayTime(Tournament tournament);

int getTournamentNumberOfPlayers(Tournament tournament);

void setTournamentStatus(Tournament tournament, TournamentStatus status);

void setTournamentWinner(Tournament tournament, int winner_id);

bool isGameExist(Tournament tournament, int first_player_id, int second_player_id);

MapResult addGame(Tournament tournament, int first_player, int second_player, Winner winner, int play_time);

#endif /* TOURNAMENT_H_ */
