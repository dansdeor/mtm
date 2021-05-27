#include "chessSystem.h"
#include "mtm_map/map.h"
#include "tournament.h"
#include "player.h"
#include "player_levels.h"

#include <stdlib.h>
#include <string.h>

#define WIN_SCORE (2)
#define DRAW_SCORE (1)


struct chess_system_t {
	Map tournaments;
	Map players;
};


ChessSystem chessCreate()
{
	ChessSystem chess_system = malloc(sizeof(*chess_system));
	if (chess_system == NULL) {
		return NULL;
	}
	chess_system->tournaments = mapCreate(copyTournament,
										  copyTournamentId,
										  freeTournament,
										  freeTournamentId,
										  compareTournamentId);
	if (chess_system->tournaments == NULL) {
		free(chess_system);
		return NULL;
	}
	chess_system->players = mapCreate(copyPlayer,
									  copyPlayerId,
									  freePlayer,
									  freePlayerId,
									  comparePlayerId);
	if (chess_system->players == NULL) {
		mapDestroy(chess_system->tournaments);
		free(chess_system);
		return NULL;
	}
	return chess_system;
}


void chessDestroy(ChessSystem chess)
{
	if (chess == NULL) {
		return;
	}
	mapDestroy(chess->tournaments);
	mapDestroy(chess->players);
	free(chess);
}


static bool isTournamentLocationLegal(const char* location)
{
	if (location == NULL) {
		return false;
	}
	size_t string_size = strlen(location);
	if (string_size <= 0) {
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
	if (chess == NULL || tournament_location == NULL) {
		return CHESS_NULL_ARGUMENT;
	}
	if (tournament_id <= INVALID_TOURNAMENT_ID) {
		return CHESS_INVALID_ID;
	}
	if (mapContains(chess->tournaments, &tournament_id)) {
		return CHESS_TOURNAMENT_ALREADY_EXISTS;
	}
	if (!isTournamentLocationLegal(tournament_location)) {
		return CHESS_INVALID_LOCATION;
	}
	if (max_games_per_player <= 0) {
		return CHESS_INVALID_MAX_GAMES;
	}
	Tournament tournament = createTournament(max_games_per_player, tournament_location,
											 STARTED, 0, 0, INVALID_PLAYER_ID);
	if (!tournament) {
		return CHESS_OUT_OF_MEMORY;
	}
	if (mapPut(chess->tournaments, &tournament_id, tournament) == MAP_OUT_OF_MEMORY) {
		freeTournament(tournament);
		return CHESS_OUT_OF_MEMORY;
	}
	freeTournament(tournament);
	return CHESS_SUCCESS;
}


static Player getOrCreatePlayer(ChessSystem chess, int player_id)
{
	if (chess == NULL || player_id <= INVALID_PLAYER_ID) {
		return NULL;
	}
	if (!mapContains(chess->players, &player_id)) {
		Player player = createPlayer();
		mapPut(chess->players, &player_id, player);
		freePlayer(player);
	}
	return mapGet(chess->players, &player_id);
}


/*
 * updatePlayers: reset players scores and updates their other statistics based on all participated games.
 * if a player has been removed, he will no longer be in the map
 */
static void updatePlayers(ChessSystem chess)
{
	if (chess == NULL) {
		return;
	}
	mapClear(chess->players);
	MAP_FOREACH(int*, tournament_id, chess->tournaments) {
		Tournament tournament = mapGet(chess->tournaments, tournament_id);
		Map games = getTournamentGames(tournament);
		MAP_FOREACH(int*, game_index, games) {
			Game game = mapGet(games, game_index);
			Player first_player = getOrCreatePlayer(chess, getFirstPlayerId(game));
			Player second_player = getOrCreatePlayer(chess, getSecondPlayerId(game));
			switch (getWinner(game)) {
				case FIRST_PLAYER:
					setPlayerWins(first_player, getPlayerWins(first_player) + 1);
					setPlayerLoses(second_player, getPlayerLoses(second_player) + 1);
					break;
				case SECOND_PLAYER:
					setPlayerWins(second_player, getPlayerWins(second_player) + 1);
					setPlayerLoses(first_player, getPlayerLoses(first_player) + 1);
					break;
				case DRAW:
					setPlayerDraws(first_player, getPlayerDraws(first_player) + 1);
					setPlayerDraws(second_player, getPlayerDraws(second_player) + 1);
					break;
				default:
					break;

			}
			setPlayerNumberOfPlays(first_player, getPlayerNumberOfPlays(first_player) + 1);
			setPlayerNumberOfPlays(second_player, getPlayerNumberOfPlays(second_player) + 1);
			setPlayerPlayTime(first_player, getPlayerPlayTime(first_player) + getPlayTime(game));
			setPlayerPlayTime(second_player, getPlayerPlayTime(second_player) + getPlayTime(game));
			freeGameIndex(game_index);
		}
		freeTournamentId(tournament_id);
	}
}


ChessResult chessAddGame(ChessSystem chess, int tournament_id, int first_player,
						 int second_player, Winner winner, int play_time)
{
	if (chess == NULL) {
		return CHESS_NULL_ARGUMENT;
	}
	if (tournament_id <= INVALID_TOURNAMENT_ID || first_player <= INVALID_PLAYER_ID ||
		second_player <= INVALID_PLAYER_ID || first_player == second_player) {
		return CHESS_INVALID_ID;
	}
	if (winner < FIRST_PLAYER || winner > DRAW) {
		return CHESS_INVALID_ID;
	}
	if (!mapContains(chess->tournaments, &tournament_id)) {
		return CHESS_TOURNAMENT_NOT_EXIST;
	}
	Tournament tournament = mapGet(chess->tournaments, &tournament_id);
	if (getTournamentStatus(tournament) == ENDED) {
		return CHESS_TOURNAMENT_ENDED;
	}
	if (isGameExist(tournament, first_player, second_player)) {
		return CHESS_GAME_ALREADY_EXISTS;
	}
	if (play_time < 0) {
		return CHESS_INVALID_PLAY_TIME;
	}
	int max_plays_per_player = getMaxGamesPerPlayer(tournament);
	if (max_plays_per_player <= getPlayerParticipationNumber(tournament, first_player)) {
		return CHESS_EXCEEDED_GAMES;
	}
	if (max_plays_per_player <= getPlayerParticipationNumber(tournament, second_player)) {
		return CHESS_EXCEEDED_GAMES;
	}
	//because the arguments are not set to null, the only option is memory allocation problem
	if (addTournamentGame(tournament, first_player, second_player, winner, play_time) != MAP_SUCCESS) {
		return CHESS_OUT_OF_MEMORY;
	}
	updatePlayers(chess);
	return CHESS_SUCCESS;
}


ChessResult chessRemoveTournament(ChessSystem chess, int tournament_id)
{
	if (chess == NULL) {
		return CHESS_NULL_ARGUMENT;
	}
	if (tournament_id <= INVALID_TOURNAMENT_ID) {
		return CHESS_INVALID_ID;
	}
	if (!mapContains(chess->tournaments, &tournament_id)) {
		return CHESS_TOURNAMENT_NOT_EXIST;
	}
	mapRemove(chess->tournaments, &tournament_id);
	updatePlayers(chess);
	return CHESS_SUCCESS;
}


ChessResult chessRemovePlayer(ChessSystem chess, int player_id)
{
	if (chess == NULL) {
		return CHESS_NULL_ARGUMENT;
	}
	if (player_id <= INVALID_PLAYER_ID) {
		return CHESS_INVALID_ID;
	}
	if (!mapContains(chess->players, &player_id)) {
		return CHESS_PLAYER_NOT_EXIST;
	}
	MAP_FOREACH(int*, tournament_id, chess->tournaments) {
		Tournament tournament = mapGet(chess->tournaments, tournament_id);
		if (getTournamentStatus(tournament) != ENDED) {
			Map games = getTournamentGames(tournament);
			MAP_FOREACH(int*, game_index, games) {
				Game game = mapGet(games, game_index);
				if (getFirstPlayerId(game) == player_id) {
					setFirstPlayerId(game, INVALID_PLAYER_ID);
					setWinner(game, SECOND_PLAYER);
				}
				else if (getSecondPlayerId(game) == player_id) {
					setSecondPlayerId(game, INVALID_PLAYER_ID);
					setWinner(game, FIRST_PLAYER);
				}
				freeGameIndex(game_index);
			}
		}
		freeTournamentId(tournament_id);
	}
	updatePlayers(chess);
	return CHESS_SUCCESS;
}


static int pickWinner(ChessSystem chess, int first_player_id, int second_player_id)
{
	if (chess == NULL || (!mapContains(chess->players, &first_player_id)
						  && !mapContains(chess->players, &second_player_id))) {
		return INVALID_PLAYER_ID;
	}
	Player first_player = mapGet(chess->players, &first_player_id);
	if (first_player == NULL) {
		return second_player_id;
	}
	Player second_player = mapGet(chess->players, &second_player_id);
	if (second_player == NULL) {
		return first_player_id;
	}
	if (getPlayerScore(first_player) > getPlayerScore(second_player)) {
		return first_player_id;
	}
	else if (getPlayerScore(first_player) < getPlayerScore(second_player)) {
		return second_player_id;
	}
	else {
		if (getPlayerLoses(first_player) < getPlayerLoses(second_player)) {
			return first_player_id;
		}
		else if (getPlayerLoses(first_player) > getPlayerLoses(second_player)) {
			return second_player_id;
		}
		else {
			if (getPlayerWins(first_player) > getPlayerWins(second_player)) {
				return first_player_id;
			}
			else if (getPlayerWins(first_player) < getPlayerWins(second_player)) {
				return second_player_id;
			}
		}
	}
	if (first_player_id <= second_player_id) {
		return first_player_id;
	}
	return second_player_id;
}


ChessResult chessEndTournament(ChessSystem chess, int tournament_id)
{
	if (chess == NULL) {
		return CHESS_NULL_ARGUMENT;
	}
	if (tournament_id <= INVALID_TOURNAMENT_ID) {
		return CHESS_INVALID_ID;
	}
	if (!mapContains(chess->tournaments, &tournament_id)) {
		return CHESS_TOURNAMENT_NOT_EXIST;
	}
	Tournament tournament = mapGet(chess->tournaments, &tournament_id);
	if (getTournamentStatus(tournament) == ENDED) {
		return CHESS_TOURNAMENT_ENDED;
	}
	if (getTournamentNumberOfGames(tournament) == 0) {
		return CHESS_NO_GAMES;
	}
	Map games = getTournamentGames(tournament);
	int winner_id = INVALID_PLAYER_ID;
	MAP_FOREACH(int*, game_index, games) {
		Game game = mapGet(games, game_index);
		Player first_player = getOrCreatePlayer(chess, getFirstPlayerId(game));
		Player second_player = getOrCreatePlayer(chess, getSecondPlayerId(game));
		switch (getWinner(game)) {
			case FIRST_PLAYER:
				setPlayerScore(first_player, getPlayerScore(first_player) + WIN_SCORE);
				break;
			case SECOND_PLAYER:
				setPlayerScore(second_player, getPlayerScore(second_player) + WIN_SCORE);
				break;
			case DRAW:
				setPlayerScore(first_player, getPlayerScore(first_player) + DRAW_SCORE);
				setPlayerScore(second_player, getPlayerScore(second_player) + DRAW_SCORE);
				break;
			default:
				break;
		}
		winner_id = pickWinner(chess, winner_id, getFirstPlayerId(game));
		winner_id = pickWinner(chess, winner_id, getSecondPlayerId(game));
		freeGameIndex(game_index);
	}
	setTournamentWinner(tournament, winner_id);
	setTournamentStatus(tournament, ENDED);
	updatePlayers(chess);
	return CHESS_SUCCESS;
}


double chessCalculateAveragePlayTime(ChessSystem chess, int player_id, ChessResult* chess_result)
{
	if (chess == NULL || chess_result == NULL) {
		if (chess_result != NULL) {
			*chess_result = CHESS_NULL_ARGUMENT;
		}
		return 0;
	}
	if (player_id <= INVALID_PLAYER_ID) {
		*chess_result = CHESS_INVALID_ID;
		return 0;
	}
	if (!mapContains(chess->players, &player_id)) {
		*chess_result = CHESS_PLAYER_NOT_EXIST;
		return 0;
	}
	Player player = mapGet(chess->players, &player_id);
	if (!getPlayerNumberOfPlays(player)) {
		return 0;
	}
	*chess_result = CHESS_SUCCESS;
	return ((double) getPlayerPlayTime(player)) / getPlayerNumberOfPlays(player);
}


ChessResult chessSavePlayersLevels(ChessSystem chess, FILE* file)
{
	if (chess == NULL || file == NULL) {
		return CHESS_NULL_ARGUMENT;
	}
	Map players_map = createPlayerLevelMap(chess->players);
	if (!players_map) {
		return CHESS_SAVE_FAILURE;
	}
	MAP_FOREACH(PlayerLevel, player_level, players_map) {
		if (fprintf(file, "%d %.2lf\n", getPlayerLevelId(player_level), getPlayerLevel(player_level)) <= 0) {
			freePlayerKeyOrLevel(player_level);
			return CHESS_SAVE_FAILURE;
		}
		freePlayerKeyOrLevel(player_level);
	}
	mapDestroy(players_map);
	return CHESS_SUCCESS;
}


ChessResult chessSaveTournamentStatistics(ChessSystem chess, char* path_file)
{
	if (chess == NULL || path_file == NULL) {
		return CHESS_NULL_ARGUMENT;
	}
	FILE* file = NULL;
	bool ended_tournament_exist = false;
	MAP_FOREACH(int*, tournament_id, chess->tournaments) {
		Tournament tournament = mapGet(chess->tournaments, tournament_id);
		if (getTournamentStatus(tournament) == ENDED) {
			if (!ended_tournament_exist) {
				file = fopen(path_file, "w");
				if (file == NULL) {
					freeTournamentId(tournament_id);
					return CHESS_SAVE_FAILURE;
				}
				ended_tournament_exist = true;
			}
			int chars_written = fprintf(file, "%d\n%d\n%.2lf\n%s\n%d\n%d\n", getTournamentWinner(tournament),
										getTournamentMaxPlayTime(tournament), getTournamentAveragePlayTime(tournament),
										getTournamentLocation(tournament), getTournamentNumberOfGames(tournament),
										getTournamentNumberOfPlayers(tournament));
			if (chars_written <= 0) {
				if (file != NULL) {
					fclose(file);
				}
				freeTournamentId(tournament_id);
				return CHESS_SAVE_FAILURE;
			}

		}
		freeTournamentId(tournament_id);
	}
	if (file != NULL && fclose(file) != 0) {
		return CHESS_SAVE_FAILURE;
	}
	if (!ended_tournament_exist) {
		return CHESS_NO_TOURNAMENTS_ENDED;
	}
	return CHESS_SUCCESS;
}
