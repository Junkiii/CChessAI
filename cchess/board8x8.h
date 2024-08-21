// Hendrik Junkawitsch

/**
 * Board8x8:
 * ---------
 * This file establishes the straightforward 8x8 2D representation of the chessboard. 
 * This representation is not employed for internal computations. In the 2D 
 * representation, additional state parameters such as castling rights, en passant, 
 * etc., are not considered; the primary focus is solely on the actual board.
 */

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <wchar.h>
#include "typedefs.h"

#include "board.h"

#define EMPTY    0x0020
#define W_KING   0x2654
#define W_QUEEN  0x2655  
#define W_ROOK   0x2656
#define W_BISHOP 0x2657
#define W_KNIGHT 0x2658
#define W_PAWN   0x2659
#define B_KING   0x265A
#define B_QUEEN  0x265B
#define B_ROOK   0x265C
#define B_BISHOP 0x265D
#define B_KNIGHT 0x265E
#define B_PAWN   0x265F

/**
 * Function: board8x8_init
 * -----------------------
 * Allocates memory for the 2D 8x8 board representation using malloc.
 */
Board8x8 board8x8_init();

/**
 * Function: board8x8_destroy
 * --------------------------
 * Deallocates the memory of a 2D 8x8 board, rendering it unusable in the future.
 */
void board8x8_destroy(Board8x8 board8x8);

/**
 * Function: board8x8_from_board
 * ---------------------
 * Transforms the provided bitmap board representation into a 2D array.
 */
void board8x8_from_board(Board8x8 board8x8, const Board *board);

/**
 * Function: board8x8_print
 * ------------------------
 * Displays the 2D 8x8 board in a readable format on the console.
 */
void board8x8_print(const Board8x8 board8x8);