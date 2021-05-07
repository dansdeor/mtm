#include "chessSystem.h"
#include "mtm_map/map.h"
#include <stdlib.h>


struct chess_system_t {
	Map tournaments;
};


ChessSystem chessCreate()
{
	ChessSystem chess_system = malloc(sizeof(*chess_system));
	if (!chess_system) {
		return NULL;
	}
	chess_system->tournaments = mapCreate();
}