// Hendrik Junkawitsch

#include "knight.h"

Bitboard64 *knight_get_movemaps() {
    Bitboard64 *movemaps = (Bitboard64 *) malloc(64 * sizeof(Bitboard64));
    assert(movemaps != NULL);
    for (U8 board_idx = 0; board_idx < 64; ++board_idx) {
        Bitboard64 knight_pos = POS_1 << board_idx;
        movemaps[board_idx] = EMPTY_BOARD;
        movemaps[board_idx] |= (knight_pos << 17) & NOT_FILE_A;
        movemaps[board_idx] |= (knight_pos << 10) & NOT_FILE_AB;
        movemaps[board_idx] |= (knight_pos >>  6) & NOT_FILE_AB;
        movemaps[board_idx] |= (knight_pos >> 15) & NOT_FILE_A;
        movemaps[board_idx] |= (knight_pos << 15) & NOT_FILE_H;
        movemaps[board_idx] |= (knight_pos <<  6) & NOT_FILE_GH;
        movemaps[board_idx] |= (knight_pos >> 10) & NOT_FILE_GH;
        movemaps[board_idx] |= (knight_pos >> 17) & NOT_FILE_H;
    }
    return movemaps;
}

Node *knight_all_moves(const Board *board, const Bitboard64 *knight_movemaps, Node *node) {
    U8 turn = (board->flags & TURN_MASK) >> 7;
    Bitboard64 knights = board->piece_bb[KNIGHT_BB] & board->piece_bb[turn];
    U8 amount_knights = bitboard_popcount(&knights);

    for (U8 k = 0; k < amount_knights; ++k) {
        Square knight_orgn = bitboard_pop_LSB(&knights);
        Bitboard64 knight_moves = knight_movemaps[knight_orgn] & ~board->piece_bb[turn];
        U8 amount = bitboard_popcount(&knight_moves);
        for (U8 m = 0; m < amount; ++m) {
            Square knight_dest = bitboard_pop_LSB(&knight_moves);
            Move* move = move_init();
            move->orgn = knight_orgn;
            move->dest = knight_dest;
            move->piece = KNIGHT_BB - 2;
            move->special = 0; 
            node = movelist_add(node, move);
        }
    }
    return node;
}