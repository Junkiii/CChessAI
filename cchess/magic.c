// Hendrik Junkawitsch

#include "magic.h"

/**
 * Static Function: magic_find
 * ---------------------------
 * Finds the magic number for a specific square.
 */
static void magic_find(Square square, Magic *magic, const Bitboard64 *movemaps, U8 bishop);

/**
 * Static function: magic_transform
 * --------------------------------
 * Helper function that, given a blockers bitboard, a magic number, and the 
 * corresponding relevant bits, determines and returns the index.
 */
static U16 magic_transform_helper(Bitboard64 blockers, Bitboard64 magic, U8 bits);

/**
 * rook rellevant occupancy bits
 */
static U8 rook_bits[64] = {
    12, 11, 11, 11, 11, 11, 11, 12,
    11, 10, 10, 10, 10, 10, 10, 11,
    11, 10, 10, 10, 10, 10, 10, 11,
    11, 10, 10, 10, 10, 10, 10, 11,
    11, 10, 10, 10, 10, 10, 10, 11,
    11, 10, 10, 10, 10, 10, 10, 11,
    11, 10, 10, 10, 10, 10, 10, 11,
    12, 11, 11, 11, 11, 11, 11, 12
};

/**
 * bishop rellevant occupancy bits
 */
static U8 bishop_bits[64] = {
    6, 5, 5, 5, 5, 5, 5, 6,
    5, 5, 5, 5, 5, 5, 5, 5,
    5, 5, 7, 7, 7, 7, 5, 5,
    5, 5, 7, 9, 9, 7, 5, 5,
    5, 5, 7, 9, 9, 7, 5, 5,
    5, 5, 7, 7, 7, 7, 5, 5,
    5, 5, 5, 5, 5, 5, 5, 5,
    6, 5, 5, 5, 5, 5, 5, 6
};

Magic *magic_compute(U8 bishop) { 
    // calculate masks and move maps
    Bitboard64 *masks = bishop ? bishop_get_masks() : rook_get_masks();
    Bitboard64 **movemaps = bishop ? bishop_get_blocked_movemaps(masks) : rook_get_blocked_movemaps(masks);

    Magic *magics = (Magic *) malloc(64 * sizeof(Magic));
    assert(magics != NULL);

    U8 *bits = bishop ? bishop_bits : rook_bits;

    for (U8 i = 0; i < 64; ++i) {
        magics[i].rellevant_bits = bits[i];
        magics[i].mask = masks[i];

        magic_find(i, &magics[i] , movemaps[i], bishop);
    }

    // free masks and movemaps again
    assert(masks != NULL);
    free(masks);
    for (U8 i = 0; i < 64; ++i) {
        assert(movemaps[i] != NULL);
        free(movemaps[i]);
    }
    assert(movemaps != NULL);
    free(movemaps);

    return magics;
}

Bitboard64 magic_index_to_bitboard(U16 index, U8 bits, Bitboard64 m) {
    Bitboard64 result = EMPTY_BOARD;
    for (U8 i = 0; i < bits; ++i) {
        U8 j = bitboard_pop_LSB(&m);
        if (index & (1 << i)) result |= (POS_1 << j);
    }
    return result;
}

U16 magic_transform(Square square, Bitboard64 blockers, Bitboard64 magic, U8 bishop) {
    U8 bits = bishop ? bishop_bits[square] : rook_bits[square];
    return magic_transform_helper(blockers, magic, bits);
}

static void magic_find(Square square, Magic *magic, const Bitboard64 *movemaps, U8 bishop) {
    U8 amount_blockers = bitboard_popcount(&magic->mask);
    Bitboard64 blocker_combinations[1 << amount_blockers];

    // allocate memory for hash array containing move maps
    Bitboard64 *hash_array = (Bitboard64 *) malloc((1 << amount_blockers) * sizeof(Bitboard64));
    assert(hash_array != NULL);

    // compute every combination of blockers
    for (U16 i = 0; i < (1 << amount_blockers); ++i) {
        blocker_combinations[i] = magic_index_to_bitboard(i, amount_blockers, magic->mask);
    }

    // brute force magic numbers
    for (U32 try = 0; try < 0xffffffff; ++try) {
        Bitboard64 magic_number = bitboard_random_sparse();
        
        Bitboard64 bb = (magic->mask * magic_number) & 0xff00000000000000ULL;
        if (bitboard_popcount(&bb) < 6) continue;

        for (U16 i = 0; i < (1 << amount_blockers); ++i) {
            hash_array[i] = EMPTY_BOARD;
        }

        U8 fail = 0;
        for (U16 i = 0; i < (1 << amount_blockers) && !fail; ++i) {
            U16 index = magic_transform_helper(blocker_combinations[i], magic_number, magic->rellevant_bits);
            if (hash_array[index] == EMPTY_BOARD) hash_array[index] = movemaps[i];
            else if (hash_array[index] != movemaps[i]) fail = 1;
        }
        if (!fail) {
            magic->magic = magic_number;
            magic->movemaps = hash_array;
            return;
        }
    }
    assert(0);
}

static U16 magic_transform_helper(Bitboard64 blockers, Bitboard64 magic, U8 bits) {
    return (U16)((blockers * magic) >> (64 - bits));
}