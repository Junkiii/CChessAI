// Hendrik Junkawitsch

/**
 * Magic:
 * This file outlines functions for calculating and utilizing magic 
 * numbers and bitboards. It employs a brute force trial-and-error 
 * approach to generate all the magic numbers. The methods used to 
 * find these magic numbers closely follow Tord Romstad's proposal, 
 * as described in the following link: 
 * https://www.chessprogramming.org/Looking_for_Magics.
 */

#pragma once

#include <assert.h>
#include "typedefs.h"

#include "bitboard.h"
#include "pieces/rook.h"
#include "pieces/bishop.h"

/**
 * Magic Container
 * ---------------
 * Includes the mask, magic number, relevant bits, and the hash array. 
 * A Magic struct is required for each square.
 */
typedef struct magic {
    Bitboard64 mask;
    Bitboard64 magic;
    Bitboard64 *movemaps;
    U8 rellevant_bits;
} Magic;

/**
 * Function: magic_compute
 * -----------------------
 * Calculates all magic numbers for rooks and bishops using the 
 * corresponding move maps and masks. Returns a pointer to the 
 * array of magic structs.
 *
 * NOTE: Perform this computation ONLY ONCE.
 */
Magic *magic_compute(U8 bishop);

/**
 * Function: magic_transform
 * -------------------------
 * Given a blockers bitboard, a magic number, the square, and the flag
 * for bishop or rook, determine and return the index.
 */
U16 magic_transform(Square square, Bitboard64 blockers, Bitboard64 magic, U8 bishop);

/**
 * Function: magic_index_to_bitboard
 * ---------------------------------
 * Helper function to compute all blocker combinations for a given mask.
 */
Bitboard64 magic_index_to_bitboard(U16 index, U8 bits, Bitboard64 m);