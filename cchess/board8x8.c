// Hendrik Junkawitsch

#include "board8x8.h"

Board8x8 board8x8_init() {
    Board8x8 board8x8 = (Board8x8) malloc(8 * sizeof(Square2d *));
    assert(board8x8 != NULL);
    for (U8 file = 0; file < 8; ++file) {
        board8x8[file] = (Square2d *) malloc(8 * sizeof(Square2d));
        assert(board8x8[file] != NULL);
    }
    return board8x8;
}

void board8x8_destroy(Board8x8 board8x8) {
    for (U8 file = 0; file < 8; ++file) {
        assert(board8x8[file] != NULL);
        free(board8x8[file]);
    }
    assert(board8x8 != NULL);
    free(board8x8);
}

void board8x8_from_board(Board8x8 board8x8, const Board *board) {
    for (U8 file = 0; file < 8; ++file) {
        for (U8 rank = 0; rank < 8; ++rank) {
            Square2d piece = EMPTY;
            // Check each bitboard for presence of a piece
            for (U8 piece_idx = 2; piece_idx < 8; ++piece_idx) {
                if (((board->piece_bb[piece_idx] & board->piece_bb[WHITE_BB]) >> (rank * 8 + file)) & 1) {
                    piece = W_KING + piece_idx - 2;
                    break;
                } else if (((board->piece_bb[piece_idx] & board->piece_bb[BLACK_BB]) >> (rank * 8 + file)) & 1) {
                    piece = B_KING + piece_idx - 2;
                    break;
                }
            }
            board8x8[file][rank] = piece;
        }
    }
}

void board8x8_print(const Board8x8 board8x8) {
    printf("  +-----------------+\n");
    for (I8 rank = 7; rank > -1; --rank) {
        printf("%d | ", rank + 1);
        for (I8 file = 0; file < 8; ++file) {
            printf("%lc ", (wint_t)board8x8[file][rank]);
        }
        printf("|\n");
    }
    printf("  +-----------------+\n");
    printf("    A B C D E F G H\n");
}