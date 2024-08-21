// Hendrik Junkawitsch

#pragma once

#include <stdlib.h>
#include <assert.h>
#include "../typedefs.h"

#include "../movelist.h"
#include "../bitboard.h"
#include "../board.h"
#include "../move.h"
#include "../magic.h"

/**
 * Function: queen_get_movemaps
 * ----------------------------
 * Calculate a move map for the queen for every position on the chessboard. 
 * The queen's move map is a fusion of the bishop and rook move maps.
 */
Bitboard64 *queen_get_movemaps();

/**
 * Function: queen_all_moves
 * -------------------------
 * Calculates all potential queen moves in the current state of the chess game.
 */
Node *queen_all_moves(const Board *board, const Magic *rook_magics, const Magic *bishop_magics, Node *node);