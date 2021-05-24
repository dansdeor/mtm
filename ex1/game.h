#ifndef GAME_H_
#define GAME_H_

#include "chessSystem.h"

typedef struct game_t* Game;

/*
 * copyGame: function copies the game ADT to new ADT and returns the ADT
 * returns NULL if an allocation error occurred or game is pointing to NULL
 */
void* copyGame(void* game);

/*
 * copyGameIndex: function copies the game index which is being use just as a different key in the map
 * returns NULL if an allocation error occurred or game_index is pointing to NULL
 */
void* copyGameIndex(void* game_index);

/*
 * freeGame: free the game ADT
 */
void freeGame(void* game);

/*
 * freeGameIndex: free the game index
 */
void freeGameIndex(void* game_index);

/*
 * compareGameIndex: comparing two pointers to int by returning the subtraction
 * or returning 0 if one of the pointers are NULL
 */
int compareGameIndex(void* first_game_index, void* second_game_index);

/*
 * createGame: creating new Game ADT based on the parameters given below
 * or returns NULL if an allocation error occurred
 */
Game createGame(int first_player, int second_player, Winner winner, int play_time);

/*
 * getFirstPlayerId: returning game's first player id or 0 if game is pointing to NULL
 */
int getFirstPlayerId(Game game);

/*
 * getFirstPlayerId: returning game's second player id or 0 if game is pointing to NULL
 */
int getSecondPlayerId(Game game);

/*
 * getWinner: returning game's winner or DRAW if game is pointing to NULL
 */
Winner getWinner(Game game);

/*
 * getWinner: returning game's play time or 0 if game is pointing to NULL
 */
int getPlayTime(Game game);

/*
 * setFirstPlayerId: setting first player id in the game if game is not pointing to NULL
 */
void setFirstPlayerId(Game game, int player_id);

/*
 * setSecondPlayerId: setting second player id in the game if game is not pointing to NULL
 */
void setSecondPlayerId(Game game, int player_id);

/*
 * setWinner: setting the winner in the game if game is not pointing to NULL
 */
void setWinner(Game game, Winner winner);

#endif /* GAME_H_ */
