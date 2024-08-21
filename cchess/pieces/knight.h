// Hendrik Junkawitsch

#pragma once

#include <stdlib.h>
#include <assert.h>
#include "../typedefs.h"

#include "../movelist.h"
#include "../bitboard.h"
#include "../board.h"
#include "../move.h"

/**
 * Function: knight_get_movemaps
 * ------------------------------
 * Calculate move maps for the knight for all 64 positions on the chessboard. 
 * The knight move maps include both quiet moves and capture moves.
 */
Bitboard64* knight_get_movemaps();

/**
 * Function: knight_all_moves
 * --------------------------
 * Calculates all potential knight moves in the current state of the chess 
 * game and adds each generated move to the provided node.
 */
Node* knight_all_moves(const Board *board, const Bitboard64 *knight_movemaps, Node *node);