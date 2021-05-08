#include "tournament.h"
#include "mtm_map/map.h"
#include "game.h"
#include "string.h"
#include "stdlib.h"


struct tournament_t {
	char* location;
	int max_games_per_player;
	TournamentStatus status;
	Map games;
};


void* copyTournament(void* tournament)
{
	if(!tournament){
		return NULL;
	}
	Tournament new_tournament = createTournament(((Tournament)tournament)->max_games_per_player,
												 ((Tournament)tournament)->location,
												 ((Tournament)tournament)->status);

	MAP_FOREACH(int*, i, ((Tournament)tournament)->games) {
		if (mapPut(new_tournament->games, i, mapGet(((Tournament)tournament)->games, i)) != MAP_SUCCESS) {
			freeTournament(new_tournament);
			return NULL;
		}
	}
	return new_tournament;
}

void* copyTournamentId(void* tournament_id)
{
	if (!tournament_id) {
		return NULL;
	}
	int* new_tournament_id = malloc(sizeof(*new_tournament_id));
	if (!new_tournament_id) {
		return NULL;
	}
	*new_tournament_id = *(int*)tournament_id;
	return new_tournament_id;
}

void freeTournament(void* tournament)
{
	if (!tournament) {
		return;
	}
	mapDestroy(((Tournament)tournament)->games);
	free(((Tournament)tournament)->location);
	free(tournament);
}

void freeTournamentId(void* tournament_id)
{
	free(tournament_id);
}


int compareTournamentId(void* first_tournament_id, void* second_tournament_id)
{
	if (!first_tournament_id || !second_tournament_id) {
		return 0;
	}
	return *(int*)first_tournament_id - *(int*)second_tournament_id;
}


Tournament createTournament(int max_games_per_player, const char* tournament_location, TournamentStatus status)
{
	Tournament tournament = malloc(sizeof(*tournament));
	if (!tournament) {
		return NULL;
	}
	char* location = malloc(strlen(tournament_location) + 1);
	if (!location) {
		free(tournament);
		return NULL;
	}
	strcpy(location, tournament_location);
	Map games = mapCreate(copyGame, copyGameIndex, freeGame, freeGameIndex, compareGameIndex);
	if (!games) {
		free(location);
		free(tournament);
		return NULL;
	}

	tournament->location = location;
	tournament->max_games_per_player = max_games_per_player;
	tournament->status = status;
	tournament->games = games;

	return tournament;
}


int getMaxGamesPerPlayer(Tournament tournament)
{
	return tournament->max_games_per_player;
}

int getPlayerParticipationNumber(Tournament tournament, int player_id)
{
	int counter = 0;
	MAP_FOREACH(int*, i, tournament->games) {
		Game game = mapGet(tournament->games, i);
		if (player_id == getFirstPlayerId(game) || player_id == getSecondPlayerId(game)) {
			counter++;
		}
	}
	return counter;
}


/*
const char* getTournamentLocation(Tournament tournament)
{

}
*/

//Map const getTournamentGames(Tournament tournament);
