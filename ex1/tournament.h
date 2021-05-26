#ifndef TOURNAMENT_H_
#define TOURNAMENT_H_

#include "game.h"
#include "mtm_map/map.h"

#include <stdbool.h>

#define INVALID_TOURNAMENT_ID (0)

typedef struct tournament_t* Tournament;

typedef enum {
	STARTED, ENDED
} TournamentStatus;

/*
 * copyGame: function copies the tournament ADT to new ADT and returns the ADT
 * returns NULL if an allocation error occurred or tournament is pointing to NULL
 */
void* copyTournament(void* tournament);

/*
 * copyTournamentId: function copies the tournament id to new allocated integer and returns the id
 * returns NULL if an allocation error occurred or game_index is pointing to NULL
 */
void* copyTournamentId(void* tournament_id);

/*
 * freeTournament: free tournament ADT
 */
void freeTournament(void* tournament);

/*
 * freeTournamentId: free tournament id
 */
void freeTournamentId(void* tournament_id);

/*
 * compareTournamentId: comparing two pointers to int by returning the subtraction
 * or returning 0 if one of the pointers are NULL
 */
int compareTournamentId(void* first_tournament_id, void* second_tournament_id);

/*
 * createTournament: allocates new tournament with all the fields as parameters
 * and returns it or NULL if allocation failed or tournament_location is pointing to NULL
 */
Tournament createTournament(int max_games_per_player, const char* tournament_location,
							TournamentStatus status, int max_play_time, int number_of_players, int winner_id);

/*
 * getTournamentLocation: returns pointer to tournament location or NULL if tournament is pointing to NULL
 */
const char* getTournamentLocation(Tournament tournament);

/*
 * getMaxGamesPerPlayer: returns tournament's max games per player or 0 if tournament is pointing to NULL
 */
int getMaxGamesPerPlayer(Tournament tournament);

/*
 * getPlayerParticipationNumber: returns player's participation number in tournament or 0 if tournament is pointing
 * to NULL or player didn't play in that tournament
 */
int getPlayerParticipationNumber(Tournament tournament, int player_id);

/*
 * getTournamentGames: returns tournament's games map or NULL if tournament is pointing to NULL
 */
Map getTournamentGames(Tournament tournament);

/*
 * getTournamentNumberOfGames: returns tournament's number of games or 0 if tournament is pointing to NULL
 */
int getTournamentNumberOfGames(Tournament tournament);

/*
 * getTournamentStatus: returns tournament's status or ENDED if tournament is pointing to NULL
 */
TournamentStatus getTournamentStatus(Tournament tournament);

/*
 * getTournamentWinner: returns tournament's winner id or INVALID_PLAYER_ID if tournament is pointing to NULL
 */
int getTournamentWinner(Tournament tournament);

/*
 * getTournamentMaxPlayTime: returns tournament's max play time or 0 if tournament is pointing to NULL
 */
int getTournamentMaxPlayTime(Tournament tournament);

/*
 * getTournamentAveragePlayTime: returns tournament's average play time or 0 if tournament is pointing to NULL
 */
double getTournamentAveragePlayTime(Tournament tournament);

/*
 * getTournamentNumberOfPlayers: returns tournament's number of players or 0 if tournament is pointing to NULL
 */
int getTournamentNumberOfPlayers(Tournament tournament);

/*
 * setTournamentStatus: set tournament's status if tournament is not pointing to NULL
 */
void setTournamentStatus(Tournament tournament, TournamentStatus status);

/*
 * setTournamentWinner: set tournament's winner id if tournament is not pointing to NULL
 */
void setTournamentWinner(Tournament tournament, int winner_id);

/*
 * isGameExist: returns true if a game with first_player_id, second_player_id as players id exist in tournament
 * or false if it doesn't exit or tournament is pointing to NULL or the ids are illegal
 */
bool isGameExist(Tournament tournament, int first_player_id, int second_player_id);

/*
 * addTournamentGame: creates a game based on the parameters and adds it to tournament if it's not pointing to NULL
 */
MapResult addTournamentGame(Tournament tournament, int first_player, int second_player, Winner winner, int play_time);

#endif /* TOURNAMENT_H_ */
