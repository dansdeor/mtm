#ifndef PLAYER_H_
#define PLAYER_H_


typedef struct player_t* Player;

void* copyPlayer(void* player);

void* copyPlayerId(void* player_id);

void freePlayer(void* player);

void freePlayerId(void* player_id);

int comparePlayerId(void* first_player_id, void* second_player_id);

Player createPlayer();

int getPlayerScore(Player player);

int getPlayerWins(Player player);

int getPlayerLoses(Player player);

int getPlayerDraws(Player player);

void setPlayerScore(Player player, int score);

void setPlayerWins(Player player, int num_wins);

void setPlayerLoses(Player player, int num_loses);

void setPlayerDraws(Player player, int num_draws);

#endif /* PLAYER_H_ */
