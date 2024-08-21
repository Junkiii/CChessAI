// Hendrik Junkawitsch

#include "king.h"

Bitboard64 *king_get_movemaps() {
    Bitboard64 *movemaps = (Bitboard64 *) malloc(64 * sizeof(Bitboard64));
    assert(movemaps != NULL);
    for (U8 board_idx = 0; board_idx < 64; ++board_idx) {
        Bitboard64 king_pos = POS_1 << board_idx;
        movemaps[board_idx] = EMPTY_BOARD;
        movemaps[board_idx] |= (king_pos >> 1) & NOT_FILE_H;
        movemaps[board_idx] |= (king_pos >> 7) & NOT_FILE_A;
        movemaps[board_idx] |= (king_pos >> 8);
        movemaps[board_idx] |= (king_pos >> 9) & NOT_FILE_H;
        movemaps[board_idx] |= (king_pos << 1) & NOT_FILE_A;
        movemaps[board_idx] |= (king_pos << 7) & NOT_FILE_H;
        movemaps[board_idx] |= (king_pos << 8);
        movemaps[board_idx] |= (king_pos << 9) & NOT_FILE_A;
    }
    return movemaps;
}

Node *king_all_moves(const Board *board, const Bitboard64 *king_movemaps, Node *node) {
    U8 turn = (board->flags & TURN_MASK) >> 7;
    Bitboard64 king = board->piece_bb[KING_BB] & board->piece_bb[turn];
    
    Square king_orgn = bitboard_pop_LSB(&king);
    assert(king_orgn != -1); // there has to be a king on the board
    Bitboard64 king_moves = king_movemaps[king_orgn] & ~board->piece_bb[turn];
    U8 amount = bitboard_popcount(&king_moves);

    for (U8 m = 0; m < amount; ++m) {
        Square king_dest = bitboard_pop_LSB(&king_moves);
        Move* move = move_init();
        move->orgn = king_orgn;
        move->dest = king_dest;
        node = movelist_add(node, move);
    }
    return node;
}