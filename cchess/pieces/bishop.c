// Hendrik Junkawitsch

#include "bishop.h"

/**
 * Static Function: bishop_get_single_blocked_movemap
 * --------------------------------------------------
 * Provides the movemap of a bishop at a particular position 
 * considering the specified blockers.
 */
static Bitboard64 bishop_get_single_blocked_movemap(Square square, Bitboard64 block);

Bitboard64 *bishop_get_movemaps() {
    Bitboard64 *movemaps = (Bitboard64 *) malloc(64 * sizeof(Bitboard64));
    assert(movemaps != NULL);
    for (U8 board_idx = 0; board_idx < 64; ++board_idx) {
        Bitboard64 bishop_pos = POS_1 << board_idx;
        movemaps[board_idx] = EMPTY_BOARD;
        Bitboard64 new_pos;
        // right
        for (U8 i = 1; i < 8; ++i) {
            new_pos = (bishop_pos << 9 * i) | (bishop_pos >> 7 * i);
            if ((new_pos & NOT_FILE_A) == 0) break;
            movemaps[board_idx] |= new_pos;
        }
        // left
        for (U8 i = 1; i < 8; ++i) {
            new_pos = (bishop_pos << 7 * i) | (bishop_pos >> 9 * i);
            if ((new_pos & NOT_FILE_H) == 0) break;
            movemaps[board_idx] |= new_pos;
        }
    }
    return movemaps;
}

Bitboard64 *bishop_get_masks() {
    Bitboard64 *masks = bishop_get_movemaps();
    for (U8 board_idx = 0; board_idx < 64; ++board_idx) {
        masks[board_idx] &= NOT_FILE_A;
        masks[board_idx] &= NOT_FILE_H;
        masks[board_idx] &= NOT_RANK_1;
        masks[board_idx] &= NOT_RANK_8;
    }
    return masks;
}

Bitboard64 **bishop_get_blocked_movemaps(const Bitboard64 *bishop_masks) {
    Bitboard64 **movemaps = (Bitboard64 **) malloc(64 * sizeof(Bitboard64 *));
    assert(movemaps != NULL);
    for (U8 board_idx = 0; board_idx < 64; ++board_idx) {
        movemaps[board_idx] = (Bitboard64 *) malloc(4096 * sizeof(Bitboard64));
        assert(movemaps[board_idx] != NULL);

        U8 n = bitboard_popcount(&bishop_masks[board_idx]);

        for (U16 i = 0; i < (1 << n); ++i) {
            Bitboard64 block = magic_index_to_bitboard(i, n, bishop_masks[board_idx]);
            movemaps[board_idx][i] = bishop_get_single_blocked_movemap(board_idx, block);
        }
    }
    return movemaps;
}

Node *bishop_all_moves(const Board *board, const Magic *bishop_magics, Node *node) {
    U8 turn = (board->flags & TURN_MASK) >> 7;
    Bitboard64 bishops = board->piece_bb[BISHOP_BB] & board->piece_bb[turn];
    U8 amount_bishops = bitboard_popcount(&bishops);

    for (U8 b = 0; b < amount_bishops; ++b) {
        Square bishop_orgn = bitboard_pop_LSB(&bishops);
        Bitboard64 blockers = (board->piece_bb[WHITE_BB] | board->piece_bb[BLACK_BB]) & bishop_magics[bishop_orgn].mask;
        U16 index = magic_transform(bishop_orgn, blockers, bishop_magics[bishop_orgn].magic, 1);
        Bitboard64 bishop_moves = bishop_magics[bishop_orgn].movemaps[index] & ~board->piece_bb[turn];
        U8 amount = bitboard_popcount(&bishop_moves);
        for (U8 m = 0; m < amount; ++m) {
            Square bishop_dest = bitboard_pop_LSB(&bishop_moves);
            Move *move = move_init();
            move->orgn = bishop_orgn;
            move->dest = bishop_dest;
            move->piece = BISHOP_BB - 2;
            move->special = 0;
            node = movelist_add(node, move);
        }
    }
    return node;
}

static Bitboard64 bishop_get_single_blocked_movemap(Square square, Bitboard64 block) {
    Bitboard64 result = EMPTY_BOARD;
    int rk = square / 8, fl = square % 8, r, f;
    for(r = rk+1, f = fl+1; r <= 7 && f <= 7; r++, f++) {
        result |= (POS_1 << (f + r*8));
        if(block & (POS_1 << (f + r * 8))) break;
    }
    for(r = rk+1, f = fl-1; r <= 7 && f >= 0; r++, f--) {
        result |= (POS_1 << (f + r*8));
        if(block & (POS_1 << (f + r * 8))) break;
    }
    for(r = rk-1, f = fl+1; r >= 0 && f <= 7; r--, f++) {
        result |= (POS_1 << (f + r*8));
        if(block & (POS_1 << (f + r * 8))) break;
    }
    for(r = rk-1, f = fl-1; r >= 0 && f >= 0; r--, f--) {
        result |= (POS_1 << (f + r*8));
        if(block & (POS_1 << (f + r * 8))) break;
    }
    return result;
}