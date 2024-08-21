// Hendrik Junkawitsch

#include "board.h"

void board_starting_position(Board *board) {
    board->flags = 0b00000000;
    board->halfmove_clock = 0;
    board->fullmove_clock = 1;
    board->piece_bb[WHITE_BB] = 0xffffULL;
    board->piece_bb[BLACK_BB] = 0xffff000000000000ULL;
    board->piece_bb[PAWN_BB] = 0xff00000000ff00ULL;
    board->piece_bb[KNIGHT_BB] = 0x4200000000000042ULL;
    board->piece_bb[BISHOP_BB] = 0x2400000000000024ULL;
    board->piece_bb[ROOK_BB] = 0x8100000000000081ULL;
    board->piece_bb[QUEEN_BB] = 0x800000000000008ULL; 
    board->piece_bb[KING_BB] = 0x1000000000000010ULL;
}

void board_print(const Board* board) {
    Board8x8 board8x8 = board8x8_init();
    board8x8_from_board(board8x8, board);
    board8x8_print(board8x8);
    board8x8_destroy(board8x8);
}

