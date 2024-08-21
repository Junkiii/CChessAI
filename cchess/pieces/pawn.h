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
 * Function: pawn_get_quiet_movemaps
 * ---------------------------------
 * Calculate a move map for pawn quiet moves for each of the 64 positions 
 * on the chessboard. Note that this computation is specifically for 
 * quiet moves and does not encompass capture moves.
 * 
 * color: 0 -> white; 1 -> black
 * 
 * TODO: Promotion moves missing !
 */
Bitboard64 *pawn_get_quiet_movemaps(U8 color);

/**
 * Function: pawn_get_attack_maps
 * ------------------------------
 * Calculate an attack map for the pawns for all 64 positions on the chessboard. 
 * Please note that this computation specifically generates attack maps, 
 * excluding simple pushes or double pushes.
 * 
 * color: 0 -> white; 1 -> black
 * 
 * TODO: En passant missing !
 */
Bitboard64 *pawn_get_attack_maps(U8 color);

/**
 * Function: pawn_all_moves
 * ------------------------
 * Calculates all potential pawn moves in the current state of the 
 * chess game and adds each generated move to the provided node.
 */
Node *pawn_all_moves(const Board *board, const Bitboard64 *const *pawn_maps, Node *node);