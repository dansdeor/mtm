#ifndef GAME_H_
#define GAME_H_

#include "chessSystem.h"

typedef struct game_t* Game;

void* copyGame(void* game);

void* copyGameIndex(void* game_index);

void freeGame(void* game);

void freeGameIndex(void* game_index);

int compareGameIndex(void* first_game_index, void* second_game_index);

Game createGame(int first_player, int second_player, Winner winner, int play_time);

int getFirstPlayerId(Game game);

int getSecondPlayerId(Game game);

Winner getWinner(Game game);

int getPlayTime(Game game);

void setFirstPlayerId(Game game, int player_id);

void setSecondPlayerId(Game game, int player_id);

void setWinner(Game game, Winner winner);

#endif /* GAME_H_ */
