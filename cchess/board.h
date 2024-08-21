// Hendrik Junkawitsch

/**
 * Board:
 * ------
 * This file outlines the efficient dense representation of a chessboard, 
 * utilized for internal computations. It follows the conventional 
 * bitboard approach.
 */

#pragma once

#include "typedefs.h"

#include "bitboard.h"
#include "board8x8.h"
#include "move.h"

#define TURN_MASK 0b10000000

#define WHITE_BB  0
#define BLACK_BB  1
#define KING_BB   2
#define QUEEN_BB  3
#define ROOK_BB   4
#define BISHOP_BB 5
#define KNIGHT_BB 6
#define PAWN_BB   7

/* 
 * Dense Board Representation
 * --------------------------
 * flags: 8bit {t, w_c_ks, w_c_qs, b_c_ks, b_c_qs, ep, -, -}
 *  - t: turn
 *  - w_c_ks: white castle kingside
 *  - w_c_qs: white castle queenside
 *  - b_c_ks: black castle kingside
 *  - b_c_qs: black castle queenside
 *  - ep: en passant
 * halfmove_clock: 16bit [0, 65535]
 * fullmove_clock: 16bit [0, 65535]
 * piece_bb: 8*64bit for 6 pieces and color maps
 *  - using little-endian rank-file mapping (LERF)
 */
typedef struct board {
    U8 flags;
    U16 halfmove_clock;
    U16 fullmove_clock;
    Bitboard64 piece_bb[8];
} Board;

/**
 * Function: board_starting_position
 * ---------------------------------
 * Initializes the board with the starting position.
 */
void board_starting_position(Board *board);

/**
 * Function board_print
 * --------------------
 * Displays the dense board in a readable format on the console. 
 * This function acts as a wrapper, converting the dense board representation 
 * to 8x8 internally before invoking the board8x8_print function.
 */
void board_print(const Board* board);