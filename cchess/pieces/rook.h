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
 * Function: rook_get_movemaps
 * ----------------------------
 * Generate a basic movement array for the rook across all 
 * 64 positions on the chessboard.
 */
Bitboard64 *rook_get_movemaps();

/**
 * Function: rook_get_masks
 * ------------------------
 * Retrieve masks for blocking rook movement in the context of magic bitboards. 
 * It's important to note that pieces on the A and H file or the 1st and 
 * 8th ranks are never considered blockers.
 */
Bitboard64 *rook_get_masks();

/**
 * Function: rook_get_blocked_movemaps
 * -----------------------------------
 * Generate a move hash array with a size of 4096 for each square. 
 * This array is utilized to calculate the appropriate index using 
 * magic numbers and to query the move map.
 */
Bitboard64 **rook_get_blocked_movemaps(const Bitboard64 *rook_masks);

/**
 * Function: rook_all_moves
 * ------------------------
 * Calculates all potential rook moves in the current state of the chess game.
 */
Node *rook_all_moves(const Board *board, const Magic *rook_magics, Node *node);