#include "tournament.h"
#include "player.h"
#include "string.h"
#include "stdlib.h"


struct tournament_t {
	char* location;
	int max_games_per_player;
	TournamentStatus status;
	int max_play_time;
	int winner_id;
	Map games;
};


void* copyTournament(void* tournament)
{
	if (!tournament) {
		return NULL;
	}
	Tournament new_tournament = createTournament(((Tournament) tournament)->max_games_per_player,
												 ((Tournament) tournament)->location,
												 ((Tournament) tournament)->status,
												 ((Tournament) tournament)->max_play_time,
												 ((Tournament) tournament)->winner_id);

	MAP_FOREACH(int*, i, ((Tournament) tournament)->games) {
		if (mapPut(new_tournament->games, i, mapGet(((Tournament) tournament)->games, i)) != MAP_SUCCESS) {
			freeTournament(new_tournament);
			freeGameIndex(i);
			return NULL;
		}
		freeGameIndex(i);
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
	*new_tournament_id = *(int*) tournament_id;
	return new_tournament_id;
}


void freeTournament(void* tournament)
{
	if (!tournament) {
		return;
	}
	mapDestroy(((Tournament) tournament)->games);
	free(((Tournament) tournament)->location);
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
	return *(int*) first_tournament_id - *(int*) second_tournament_id;
}


Tournament createTournament(int max_games_per_player, const char* tournament_location,
							TournamentStatus status, int max_play_time, int winner_id)
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
	tournament->max_play_time = max_play_time;
	tournament->winner_id = winner_id;
	tournament->games = games;

	return tournament;
}


const char* getTournamentLocation(Tournament tournament)
{
	if (!tournament) {
		return NULL;
	}
	return tournament->location;
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
		freeGameIndex(i);
	}
	return counter;
}


Map getTournamentGames(Tournament tournament)
{
	if (!tournament) {
		return NULL;
	}
	return tournament->games;
}


int getTournamentNumberOfGames(Tournament tournament)
{
	if (!tournament) {
		return 0;
	}
	return mapGetSize(tournament->games);
}


TournamentStatus getTournamentStatus(Tournament tournament)
{
	if (!tournament) {
		return ENDED;
	}
	return tournament->status;
}


int getTournamentWinner(Tournament tournament)
{
	if (!tournament) {
		return 0;
	}
	return tournament->winner_id;
}


int getTournamentMaxPlayTime(Tournament tournament)
{
	if (!tournament) {
		return 0;
	}
	return tournament->max_play_time;
}


double getTournamentAveragePlayTime(Tournament tournament)
{
	if (!tournament) {
		return 0;
	}
	double average_play_time = 0;
	MAP_FOREACH(int*, game_index, tournament->games) {
		Game game = mapGet(tournament->games, game_index);
		average_play_time += getPlayTime(game);
		freeGameIndex(game_index);
	}
	if (getTournamentNumberOfGames(tournament) > 0) {
		average_play_time /= getTournamentNumberOfGames(tournament);
	}
	return average_play_time;
}


int getTournamentNumberOfPlayers(Tournament tournament)
{
	if (!tournament) {
		return 0;
	}
	Player player_data = createPlayer();
	if (!player_data) {
		return 0;
	}
	Map players = mapCreate(copyPlayer,
							copyPlayerId,
							freePlayer,
							freePlayerId,
							comparePlayerId);
	if (!players) {
		freePlayer(player_data);
		return 0;
	}
	MAP_FOREACH(int*, game_index, tournament->games) {
		Game game = mapGet(tournament->games, game_index);
		int first_player_id = getFirstPlayerId(game);

		if (first_player_id != INVALID_PLAYER_ID && mapPut(players, &first_player_id, player_data) != MAP_SUCCESS) {
			freePlayer(player_data);
			mapDestroy(players);
			freeGameIndex(game_index);
			return 0;
		}
		int second_player_id = getFirstPlayerId(game);
		if (second_player_id != INVALID_PLAYER_ID && mapPut(players, &second_player_id, player_data) != MAP_SUCCESS) {
			freePlayer(player_data);
			mapDestroy(players);
			freeGameIndex(game_index);
			return 0;
		}
		freeGameIndex(game_index);
	}
	int number_of_players = mapGetSize(players);
	freePlayer(player_data);
	mapDestroy(players);
	return number_of_players;
}


void setTournamentStatus(Tournament tournament, TournamentStatus status)
{
	if (!tournament) {
		return;
	}
	tournament->status = status;
}


void setTournamentWinner(Tournament tournament, int winner_id)
{
	if (!tournament) {
		return;
	}
	tournament->winner_id = winner_id;
}


bool isGameExist(Tournament tournament, int first_player_id, int second_player_id)
{
	if (!tournament || first_player_id <= 0 || second_player_id <= 0) {
		return false;
	}
	MAP_FOREACH(int*, i, tournament->games) {
		Game game = mapGet(tournament->games, i);
		if (getFirstPlayerId(game) == first_player_id && getSecondPlayerId(game) == second_player_id) {
			freeGameIndex(i);
			return true;
		}
		freeGameIndex(i);
	}
	return false;
}


MapResult addGame(Tournament tournament, int first_player, int second_player, Winner winner, int play_time)
{
	if (!tournament) {
		return MAP_NULL_ARGUMENT;
	}
	Game game = createGame(first_player, second_player, winner, play_time);
	if (!game) {
		return MAP_OUT_OF_MEMORY;
	}
	int index = mapGetSize(tournament->games);
	MapResult result = mapPut(tournament->games, &index, game);
	if (result != MAP_SUCCESS) {
		freeGame(game);
		return result;
	}
	freeGame(game);
	if (tournament->max_play_time < play_time) {
		tournament->max_play_time = play_time;
	}
	return MAP_SUCCESS;
}
