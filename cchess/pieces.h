// Hendrik Junkawitsch

#pragma once

#include <assert.h>
#include "typedefs.h"

#include "bitboard.h"
#include "magic.h"

#include "pieces/king.h"
#include "pieces/queen.h"
#include "pieces/rook.h"
#include "pieces/bishop.h"
#include "pieces/knight.h"
#include "pieces/pawn.h"

/**
 * Precalculated data for move generation
 * --------------------------------------
 * pawn: size 4 array
 * - 0 white quiet moves
 * - 1 white attacks
 * - 2 black quiet moves
 * - 3 black attacks
 * 
 * knight: size 64 array of move maps
 * king: size 64 array of move maps
 * rook: size 64 array of magics
 * bishop: size 64 array of magics
 * 
 */
typedef struct precalc {
    Bitboard64 **pawn;
    Bitboard64 *knight;
    Bitboard64 *king;
    Magic *rook;
    Magic *bishop;
} Precalc;

/**
 * Function: pieces_precalculation
 * -------------------------------
 * Compute move maps, magic numbers, and other precalculated 
 * values for all pieces and provide a Precalc struct as the result.
 */
Precalc *pieces_precalculation();

/**
 * Function: pieces_all_moves
 * --------------------------
 * Calculate all potential moves for each chess piece and merge 
 * them into a consolidated list of final moves.
 */
Node *pieces_all_moves(const Board *board, const Precalc *precalc);

/**
 * Function: pieces_name
 * ---------------------
 * Given the piece ID, return the piece name.
 */
char *pieces_name(U8 id);