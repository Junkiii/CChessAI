// Hendrik Junkawitsch

/**
 * Bitboard64:
 * -----------
 * This file outlines the fundamental functionality of 64-bit bitboards, 
 * encompassing basic operations on this data structure.
 * See https://www.chessprogramming.org/Bitboards for more information. 
 */

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include "typedefs.h"

#define EMPTY_BOARD 0x0ULL
#define POS_1 0x1ULL

#define NOT_RANK_1 0xffffffffffffff00ULL
#define NOT_RANK_2 0xffffffffffff00ffULL
#define NOT_RANK_3 0xffffffffff00ffffULL
#define NOT_RANK_4 0xffffffff00ffffffULL
#define NOT_RANK_5 0xffffff00ffffffffULL
#define NOT_RANK_6 0xffff00ffffffffffULL
#define NOT_RANK_7 0xff00ffffffffffffULL
#define NOT_RANK_8 0x00ffffffffffffffULL

#define RANK_1 ~NOT_RANK_1
#define RANK_2 ~NOT_RANK_2
#define RANK_3 ~NOT_RANK_3
#define RANK_4 ~NOT_RANK_4
#define RANK_5 ~NOT_RANK_5
#define RANK_6 ~NOT_RANK_6
#define RANK_7 ~NOT_RANK_7
#define RANK_8 ~NOT_RANK_8

#define NOT_FILE_A 0xfefefefefefefefeULL
#define NOT_FILE_B 0xfdfdfdfdfdfdfdfdULL
#define NOT_FILE_C 0xfbfbfbfbfbfbfbfbULL
#define NOT_FILE_D 0xf7f7f7f7f7f7f7f7ULL
#define NOT_FILE_E 0xefefefefefefefefULL
#define NOT_FILE_F 0xdfdfdfdfdfdfdfdfULL
#define NOT_FILE_G 0xbfbfbfbfbfbfbfbfULL
#define NOT_FILE_H 0x7f7f7f7f7f7f7f7fULL

#define FILE_A ~NOT_FILE_A
#define FILE_B ~NOT_FILE_B
#define FILE_C ~NOT_FILE_C
#define FILE_D ~NOT_FILE_D
#define FILE_E ~NOT_FILE_E
#define FILE_F ~NOT_FILE_F
#define FILE_G ~NOT_FILE_G
#define FILE_H ~NOT_FILE_H

#define NOT_FILE_AB 0xfcfcfcfcfcfcfcfcULL
#define NOT_FILE_GH 0x3f3f3f3f3f3f3f3fULL

/**
 * Function: bitboard_random
 * -------------------------
 * Generates a Bitboard by randomly combining four 16-bit integers.
 * It is advisable to initialize the random number generator with a seed beforehand.
 */
Bitboard64 bitboard_random();

/**
 * Function: bitboard_random_sparse
 * --------------------------------
 * Randomly creates a Bitboard that contains a low amount of set bits.
 * It is advisable to initialize the random number generator with a seed beforehand.
 */
Bitboard64 bitboard_random_sparse();

/**
 * Function: bitboard_pop_LSB
 * --------------------------
 * Clears the least significant non-zero bit and returns its position.
 */
U8 bitboard_pop_LSB(Bitboard64 *bitboard);

/**
 * Function: bitboard_popcount
 * ---------------------------
 * Operation to determine the cardinality of the bitboard.
 */
U8 bitboard_popcount(const Bitboard64 *bitboard);

/**
 * Function: bitboard_rotate_left
 * ------------------------------
 * Performs a 90-degree left rotation on a provided 64-bit bitboard.
 */
void bitboard_rotate_left(Bitboard64 *bitboard);

/**
 * Function: bitboard_rotate_right
 * -------------------------------
 * Performs a 90-degree right rotation on a provided 64-bit bitboard.
 */
void bitboard_rotate_right(Bitboard64 *bitboard);

/**
 * Function: bitboard_rotatate_180
 * -------------------------------
 * Performs a 180-degree rotation on a provided 64-bit bitboard.
 */
void bitboard_rotate_180(Bitboard64 *bitboard);

/**
 * Function: bitboard_flip_diag_a1h8
 * ---------------------------------
 * Flips a provided 64-bit bitboard along the diagonal a1h8.
 */
void bitboard_flip_diag_a1h8(Bitboard64 *bitboard);

/**
 * Function: bitboard_flip_diag_a8h1
 * ---------------------------------
 * Flips a provided 64-bit bitboard along the antidiagonal a8h1.
 */
void bitboard_flip_diag_a8h1(Bitboard64 *bitboard);

/**
 * Function: bitboard_flip_vertical
 * --------------------------------
 * Performs a vertical flip on a provided 64-bit bitboard.
 */
void bitboard_flip_vertical(Bitboard64 *bitboard);

/**
 * Function: bitboard_flip_horizontal
 * ----------------------------------
 * Performs a horizontal flip on a provided 64-bit bitboard.
 */
void bitboard_flip_horizontal(Bitboard64 *bitboard);

/**
 * Function: bitboard_reverse_array
 * --------------------------------
 * Reverses an array of 64-bit bitboards.
 * Please be aware that the length parameter is an 8-bit unsigned value, 
 * limiting its capacity to represent lengths up to 255.
 */
void bitboard_reverse_array(Bitboard64 *bitboards, U8 length);

/**
 * Function: bitboard_print
 * ------------------------
 * Prints a 64-bit bitboard to the console.
 */
void bitboard_print(Bitboard64 bitboard);

/**
 * Function: bitboard_write_multiple_to_file
 * -----------------------------------------
 * Stores an array of bitboards into a file specified by the provided path.
 */
void bitboard_write_multiple_to_file(const Bitboard64 *bitboards, U16 amount, char *path);