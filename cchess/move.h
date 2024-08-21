// Hendrik Junkawitsch

/**
 * Move:
 * -----
 * This file introduces the move data structure. In general,
 * a move is specified by both the origin and destination.
 */

#pragma once

#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include "typedefs.h"

#include "board.h"
#include "bitboard.h"

/**
 * 19-bit move representation
 * --------------------------
 * actual size: 4 bytes
 * - piece:      3 bits [0,5] -> {KING, QUEEN, ROOK, BISHOP, KNIGHT, PAWN}
 * - orgn:       6 bits [0,63]
 * - dest:       6 bits [0,63]
 * - promotion:  2 bits [0,3] -> {QUEEN, ROOK, BISHOP, KNIGHT}
 * - special:    2 bits [0,3] -> {NOTHING, PROMOTION, EN PASSANT, CASTLE}
 */
typedef struct move {
    U8 piece     : 3;
    Square orgn  : 6;
    Square dest  : 6;
    U8 promotion : 2;
    U8 special   : 2;
} Move;

/**
 * Function: move_init
 * -------------------
 * Initializes the move structure and returns a pointer to the initialized struct.
 */
Move *move_init();

/**
 * Deallocates the memory used by the move structure.
 */
void move_destroy(Move *move);

/**
 * Executes a move on the existing chess board, updating all corresponding 
 * board values accordingly.
 */
void move_make(Board *board, const Move *move);

/**
 * Function: get_move
 * ------------------
 * Generates the move structure from file and rank. 
 * Note that you have to use upper case letters.
 */
Move get_move(char *from, char *to);

/**
 * Function: move_to_string
 * ------------------------
 * Converts a move into a human-readable string that describes the move. 
 * This function returns a 64-bit value internally representing the character 
 * array. You can treat the 64-bit value as a char* and output it using printf.
 */
U64 move_to_string(const Move *move);

/**
 * Function: move_print
 * --------------------
 * Prints a move to the console.
 */
void move_print(const Move *move);