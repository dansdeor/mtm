#include "chessSystem.h"
#include "mtm_map/map.h"
#include "tournament.h"
#include <stdlib.h>
#include <string.h>


struct chess_system_t {
	Map tournaments;
	Map players;
};


ChessSystem chessCreate()
{
	ChessSystem chess_system = malloc(sizeof(*chess_system));
	if (!chess_system) {
		return NULL;
	}
	chess_system->tournaments = mapCreate(copyTournament,
										  copyTournamentId,
										  freeTournament,
										  freeTournamentId,
										  compareTournamentId);
	if (!chess_system->tournaments) {
		free(chess_system);
		return NULL;
	}
	chess_system->players = mapCreate(copyPlayer,
									  copyPlayerId,
									  freePlayer,
									  freePlayerId,
									  comparePlayerId);
	if (!chess_system->players) {
		mapDestroy(chess_system->tournaments);
		free(chess_system);
		return NULL;
	}
}

void chessDestroy(ChessSystem chess)
{
	if (!chess) {
		return;
	}
	mapDestroy(chess->tournaments);
	mapDestroy(chess->players);
}

static bool isTournamentLocationLegal(const char* location)
{
	if (!location) {
		return false;
	}
	size_t string_size = strlen(location);
	if (!string_size) {
		return false;
	}
	if (location[0] < 'A' || 'Z' < location[0]) {
		return false;
	}
	for (int i = 1; i < string_size; i++) {
		if (location[i] != ' ' && (location[i] < 'a' || 'z' < location[i])) {
			return false;
		}
	}
	return true;
}

ChessResult chessAddTournament(ChessSystem chess, int tournament_id,
							   int max_games_per_player, const char* tournament_location)
{
	if (!chess) {
		return CHESS_NULL_ARGUMENT;
	}
	if (tournament_id <= 0) {
		return CHESS_INVALID_ID;
	}
	if (!isTournamentLocationLegal(tournament_location)) {
		return CHESS_INVALID_LOCATION;
	}
	if (!mapContains(chess->tournaments, &tournament_id)) {
		return CHESS_TOURNAMENT_ALREADY_EXISTS;
	}
	Tournament tournament = createTournament(max_games_per_player, tournament_location, STARTED);
	mapPut(chess->tournaments, &tournament_id, tournament);
	freeTournament(tournament);
	return CHESS_SUCCESS;
}
