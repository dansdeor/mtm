CC = gcc
OBJS = chess.o chessSystem.o tournament.o game.o player.o player_levels.o
EXEC_PATH = tests/chessSystemTestsExample.c
EXEC_NAME = chess
DEBUG = # now empty, assign -g for debug
CFLAGS = -std=c99 -Wall -pedantic-errors -Werror $(DEBUG)

chess: $(OBJS)
	$(CC) $(CFLAGS) $(DEBUG) $(OBJS) -L. -lmap -o $(EXEC_NAME)

chess.o: $(EXEC_PATH)
	$(CC) $(CFLAGS) $(DEBUG) -c -o $@ $<
chessSystem.o: chessSystem.c chessSystem.h mtm_map/map.h tournament.h game.h player.h player_levels.h
tournament.o: tournament.c tournament.h mtm_map/map.h game.h chessSystem.h player.h
game.o: game.c game.h chessSystem.h
player.o: player.c player.h
player_levels.o: player_levels.c player_levels.h mtm_map/map.h player.h

clean:
	rm -f $(OBJS) $(EXEC_NAME)
