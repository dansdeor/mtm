#ifndef PLAYER_H_
#define PLAYER_H_

#define INVALID_PLAYER_ID (0)

typedef struct player_t* Player;

/*
 * copyPlayer: function copies the player ADT to new ADT and returns the ADT
 * returns NULL if an allocation error occurred or player is pointing to NULL
 */
void* copyPlayer(void* player);

/*
 * copyPlayerId: function copies the player id to new allocated integer and returns the id
 * returns NULL if an allocation error occurred or player is pointing to NULL
 */
void* copyPlayerId(void* player_id);

/*
 * freePlayer: free player ADT
 */
void freePlayer(void* player);

/*
 * freePlayerId: free player id
 */
void freePlayerId(void* player_id);

/*
 * comparePlayerId: comparing two pointers to int by returning the subtraction
 * or returning 0 if one of the pointers are NULL
 */
int comparePlayerId(void* first_player_id, void* second_player_id);

/*
 * createPlayer: allocates new player ADT without any statistics and returns it
 * returns NULL if allocation failed
 */
Player createPlayer();

/*
 * getPlayerScore: returns player's score or 0 if player is pointing to NULL
 */
int getPlayerScore(Player player);

/*
 * getPlayerWins: returns player's total wins or 0 if player is pointing to NULL
 */
int getPlayerWins(Player player);

/*
 * getPlayerLoses: returns player's total loses or 0 if player is pointing to NULL
 */
int getPlayerLoses(Player player);

/*
 * getPlayerDraws: returns player's total draws or 0 if player is pointing to NULL
 */
int getPlayerDraws(Player player);

/*
 * getPlayerPlayTime: returns player's total play time or 0 if player is pointing to NULL
 */
int getPlayerPlayTime(Player player);

/*
 * getPlayerNumberOfPlays: returns player's total number of plays or 0 if player is pointing to NULL
 */
int getPlayerNumberOfPlays(Player player);

/*
 * setPlayerScore: set player's score if player is not pointing to NULL
 */
void setPlayerScore(Player player, int score);

/*
 * setPlayerWins: set player's total wins if player is not pointing to NULL
 */
void setPlayerWins(Player player, int num_wins);

/*
 * setPlayerLoses: set player's total loses if player is not pointing to NULL
 */
void setPlayerLoses(Player player, int num_loses);

/*
 * setPlayerDraws: set player's total draws if player is not pointing to NULL
 */
void setPlayerDraws(Player player, int num_draws);

/*
 * setPlayerPlayTime: set player's total play time if player is not pointing to NULL
 */
void setPlayerPlayTime(Player player, int play_time);

/*
 * setPlayerNumberOfPlays: set player's total number of plays if player is not pointing to NULL
 */
void setPlayerNumberOfPlays(Player player, int number_of_plays);

#endif /* PLAYER_H_ */
