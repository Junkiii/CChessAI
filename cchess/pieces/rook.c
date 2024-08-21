// Hendrik Junkawitsch

#include "rook.h"

/**
 * Static Function: rook_get_single_blocked_movemap
 * ------------------------------------------------
 * Returns the movemap of a rook on a specific position based on 
 * the given blocker.
 */
static Bitboard64 rook_get_single_blocked_movemap(Square square, Bitboard64 block);

Bitboard64 *rook_get_movemaps() {
    Bitboard64 *movemaps = (Bitboard64 *) malloc(64 * sizeof(Bitboard64));
    assert(movemaps != NULL);
    for (U8 board_idx = 0; board_idx < 64; ++board_idx) {
        Bitboard64 rook_pos = POS_1 << board_idx;
        movemaps[board_idx] = EMPTY_BOARD;
        // vertical movement
        for (U8 i = 1; i < 8; ++i) {
            movemaps[board_idx] |= (rook_pos << 8 * i);
            movemaps[board_idx] |= (rook_pos >> 8 * i);
        }
        // rotate left
        bitboard_rotate_left(&movemaps[board_idx]);
        bitboard_rotate_left(&rook_pos);
        // horizontal movement
        for (U8 i = 1; i < 8; ++i) {
            movemaps[board_idx] |= (rook_pos << 8 * i);
            movemaps[board_idx] |= (rook_pos >> 8 * i);
        }
        // rotate right again
        bitboard_rotate_right(&movemaps[board_idx]);
    }
    return movemaps;
}

Bitboard64 *rook_get_masks() {
    Bitboard64 *masks = (Bitboard64 *) malloc(64 * sizeof(Bitboard64));
    assert(masks != NULL);
    for (U8 board_idx = 0; board_idx < 64; ++board_idx) {
        Bitboard64 rook_pos = POS_1 << board_idx;
        masks[board_idx] = EMPTY_BOARD;
        // vertical movement
        for (U8 i = 1; i < 8; ++i) {
            masks[board_idx] |= (rook_pos << 8 * i);
            masks[board_idx] |= (rook_pos >> 8 * i);
        }
        masks[board_idx] &= NOT_RANK_1 & NOT_RANK_8;

        // rotate left
        Bitboard64 rotated = EMPTY_BOARD;
        bitboard_rotate_left(&rotated);
        bitboard_rotate_left(&rook_pos);
        // horizontal movement
        for (U8 i = 1; i < 8; ++i) {
            rotated |= (rook_pos << 8 * i);
            rotated |= (rook_pos >> 8 * i);
        }
        rotated &= NOT_RANK_1 & NOT_RANK_8;
        // rotate right again
        bitboard_rotate_right(&rotated);

        // put both directions together
        masks[board_idx] |= rotated;
    }
    return masks;
}

Bitboard64 **rook_get_blocked_movemaps(const Bitboard64 *rook_masks) {
    Bitboard64 **movemaps = (Bitboard64 **) malloc(64 * sizeof(Bitboard64 *));
    assert(movemaps != NULL);
    for (U8 board_idx = 0; board_idx < 64; ++board_idx) {
        movemaps[board_idx] = (Bitboard64 *) malloc(4096 * sizeof(Bitboard64));
        assert(movemaps[board_idx] != NULL);
        
        U8 n = bitboard_popcount(&rook_masks[board_idx]);

        for (U16 i = 0; i < (1 << n); ++i) {
            Bitboard64 block = magic_index_to_bitboard(i, n, rook_masks[board_idx]);
            movemaps[board_idx][i] = rook_get_single_blocked_movemap(board_idx, block);
        }
    }
    return movemaps;
}

Node *rook_all_moves(const Board *board, const Magic *rook_magics, Node *node) {
    U8 turn = (board->flags & TURN_MASK) >> 7;
    Bitboard64 rooks = board->piece_bb[ROOK_BB] & board->piece_bb[turn];
    U8 amount_rooks = bitboard_popcount(&rooks);

    for (U8 r = 0; r < amount_rooks; ++r) {
        Square rook_orgn = bitboard_pop_LSB(&rooks);
        Bitboard64 blockers = (board->piece_bb[WHITE_BB] | board->piece_bb[BLACK_BB]) & rook_magics[rook_orgn].mask;
        U16 index = magic_transform(rook_orgn, blockers, rook_magics[rook_orgn].magic, 0);
        Bitboard64 rook_moves = rook_magics[rook_orgn].movemaps[index] & ~board->piece_bb[turn];
        U8 amount = bitboard_popcount(&rook_moves);
        for (U8 m = 0; m < amount; ++m) {
            Square rook_dest = bitboard_pop_LSB(&rook_moves);
            Move *move = move_init();
            move->orgn = rook_orgn;
            move->dest = rook_dest;
            move->piece = ROOK_BB - 2;
            move->special = 0;
            node = movelist_add(node, move);
        }
    }
    return node;
}

static Bitboard64 rook_get_single_blocked_movemap(Square square, Bitboard64 block) {
    Bitboard64 result = EMPTY_BOARD;
    int rk = square / 8, fl = square % 8, r, f;
    for(r = rk+1; r <= 7; r++) {
        result |= (POS_1 << (fl + r*8));
        if(block & (POS_1 << (fl + r*8))) break;
    }
    for(r = rk-1; r >= 0; r--) {
        result |= (POS_1 << (fl + r*8));
        if(block & (POS_1 << (fl + r*8))) break;
    }
    for(f = fl+1; f <= 7; f++) {
        result |= (POS_1 << (f + rk*8));
        if(block & (POS_1 << (f + rk*8))) break;
    }
    for(f = fl-1; f >= 0; f--) {
        result |= (POS_1 << (f + rk*8));
        if(block & (POS_1 << (f + rk*8))) break;
    }
    return result;    
}