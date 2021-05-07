#include "tournament.h"
#include "mtm_map/map.h"
#include "game.h"
#include "string.h"
#include "stdlib.h"


struct tournament_t {
	const char* location;
	int max_games_per_player;
	Map games;
};


Tournament copyTournament(Tournament tournament)
{
	Tournament new_tournament = malloc(sizeof(*new_tournament));
	if (!new_tournament) {
		return NULL;
	}
	char* location = malloc(strlen(tournament->location) + 1);
	if (!location) {
		free(new_tournament);
		return NULL;
	}
	strcpy(location, tournament->location);
	Map games = mapCreate();
	if (!games) {
		free(new_tournament);
		free(location);
		return NULL;
	}

	new_tournament->location = location;
	new_tournament->max_games_per_player = tournament->max_games_per_player;
	MAP_FOREACH()

}

int* copyTournamentId(int* tournament_id)
{

}

void freeTournament(Tournament tournament)
{

}

void freeTournamentId(int* tournament)
{

}

int getMaxGamesPerPlayer(Tournament tournament)
{

}

const char* getTournamentLocation(Tournament tournament)
{

}

//Map const getTournamentGames(Tournament tournament);

bool isTournamentLocationLegal(const char* location)
{

}