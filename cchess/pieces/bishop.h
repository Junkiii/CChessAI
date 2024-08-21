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
 * Function: bishop_get_movemaps
 * -----------------------------
 * Generate a basic movement array for the bishop across all 
 * 64 positions on the chessboard.
 */
Bitboard64 *bishop_get_movemaps();

/**
 * Function: bishop_get_masks
 * --------------------------
 * Retrieve masks for blocking bishop movement in the context of magic bitboards. 
 * The computation of these masks relies on previously calculated move maps. 
 * It's important to note that pieces on the A and H file or the 1st and 
 * 8th ranks are never considered blockers.
 */
Bitboard64 *bishop_get_masks();

/**
 * Function: bishop_get_blocked_movemaps
 * -------------------------------------
 * Generate a move hash array with a size of 4096 for each square. 
 * This array is utilized to calculate the appropriate index using 
 * magic numbers and to query the move map.
 */
Bitboard64 **bishop_get_blocked_movemaps(const Bitboard64 *bishop_masks);

/**
 * Function: bishop_all_moves
 * --------------------------
 * Calculates all potential bishop moves within the current state of the chess game.
 */
Node *bishop_all_moves(const Board *board, const Magic *bishop_magics, Node *node);