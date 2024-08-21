// Hendrik Junkawitsch

#include "queen.h"

Bitboard64 *queen_get_movemaps() {
    Bitboard64 *movemaps = (Bitboard64 *) malloc(64 * sizeof(Bitboard64));
    assert(movemaps != NULL);
    for (U8 board_idx = 0; board_idx < 64; ++board_idx) {
        Bitboard64 queen_pos = POS_1 << board_idx;
        movemaps[board_idx] = EMPTY_BOARD;

        // diagonal movement (bishop movement)
        Bitboard64 new_pos;
        for (U8 i = 1; i < 8; ++i) {
            new_pos = (queen_pos << 9 * i) | (queen_pos >> 7 * i);
            if ((new_pos & NOT_FILE_A) == 0) break;
            movemaps[board_idx] |= new_pos;
        }
        for (U8 i = 1; i < 8; ++i) {
            new_pos = (queen_pos << 7 * i) | (queen_pos >> 9 * i);
            if ((new_pos & NOT_FILE_H) == 0) break;
            movemaps[board_idx] |= new_pos;
        }

        // vertical and horizontal movement (rook movement)
        for (U8 i = 1; i < 8; ++i) {
            movemaps[board_idx] |= (queen_pos << 8 * i);
            movemaps[board_idx] |= (queen_pos >> 8 * i);
        }
        bitboard_rotate_left(&movemaps[board_idx]);
        bitboard_rotate_left(&queen_pos);
        for (U8 i = 1; i < 8; ++i) {
            movemaps[board_idx] |= (queen_pos << 8 * i);
            movemaps[board_idx] |= (queen_pos >> 8 * i);
        }
        bitboard_rotate_right(&movemaps[board_idx]);
    }
    return movemaps;
}

Node *queen_all_moves(const Board *board, const Magic *rook_magics, const Magic *bishop_magics, Node *node) {
    U8 turn = (board->flags & TURN_MASK) >> 7;
    Bitboard64 queens = board->piece_bb[QUEEN_BB] & board->piece_bb[turn];
    U8 amount_queens = bitboard_popcount(&queens);

    for (U8 q = 0; q < amount_queens; ++q) {
        Square queen_orgn = bitboard_pop_LSB(&queens);

        Bitboard64 all = board->piece_bb[WHITE_BB] | board->piece_bb[BLACK_BB];
        Bitboard64 blockers_rook = all & rook_magics[queen_orgn].mask; 
        Bitboard64 blockers_bishop = all & bishop_magics[queen_orgn].mask;

        U16 index_rook = magic_transform(queen_orgn, blockers_rook, rook_magics[queen_orgn].magic, 0);
        U16 index_bishop = magic_transform(queen_orgn, blockers_bishop, bishop_magics[queen_orgn].magic, 1);

        Bitboard64 rook_moves = rook_magics[queen_orgn].movemaps[index_rook] & ~board->piece_bb[turn];
        Bitboard64 bishop_moves = bishop_magics[queen_orgn].movemaps[index_bishop] & ~board->piece_bb[turn];

        U8 amount_r = bitboard_popcount(&rook_moves);
        U8 amount_b = bitboard_popcount(&bishop_moves);

        for (U8 m = 0; m < amount_r; ++m) {
            Square queen_dest = bitboard_pop_LSB(&rook_moves);
            Move *move = move_init();
            move->orgn = queen_orgn;
            move->dest = queen_dest;
            move->piece = QUEEN_BB - 2;
            move->special = 0;
            node = movelist_add(node, move);
        }
        for (U8 m = 0; m < amount_b; ++m) {
            Square queen_dest = bitboard_pop_LSB(&bishop_moves);
            Move *move = move_init();
            move->orgn = queen_orgn;
            move->dest = queen_dest;
            move->piece = QUEEN_BB - 2;
            move->special = 0;
            node = movelist_add(node, move);
        }
    }
    return node;
}