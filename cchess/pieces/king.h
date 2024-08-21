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
 * Function: king_get_movemaps
 * ----------------------------
 * Calculate a move map for the king for every of the 64 positions on the chessboard. 
 * The king move maps encompass both quiet moves and capture moves.
 */
Bitboard64 *king_get_movemaps();

/**
 * Function: king_all_moves
 * ------------------------
 * Calculates all potential king moves in the current state of the chess game 
 * and adds each generated move to the provided node.
 * 
 * TODO: Castling moves are missing !
 */
Node *king_all_moves(const Board *board, const Bitboard64 *king_movemaps, Node *node);