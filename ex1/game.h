#ifndef GAME_H_
#define GAME_H_

typedef struct game_t* Game;


typedef enum {
	FIRST_PLAYER,
	SECOND_PLAYER,
	DRAW
} Winner;


void* copyGame(void* game);

void* copyGameIndex(void* game_index);

void freeGame(void* game);

void freeGameIndex(void* game_index);

int compareGameIndex(void* first_game_index, void* second_game_index);

Game createGame(int first_player, int second_player, Winner winner, int play_time);

#endif /* GAME_H_ */
