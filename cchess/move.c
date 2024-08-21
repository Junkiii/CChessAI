// Hendrik Junkawitsch

#include "move.h"

Move *move_init() {
    Move *move = (Move *) malloc(sizeof(Move));
    assert(move != NULL);
    return move;
}

void move_destroy(Move *move) {
    assert(move != NULL);
    free(move);
}

void move_make(Board *board, const Move *move) {
    if (move->special == 0) { // standard move
        U8 turn = (board->flags & TURN_MASK) >> 7;
        Bitboard64 orgn_board = POS_1 << move->orgn;
        Bitboard64 dest_board = POS_1 << move->dest;
        Bitboard64 not_orgn_board = ~orgn_board;
        Bitboard64 not_dest_board = ~dest_board;

        // remove moving piece from orgn square
        board->piece_bb[move->piece + 2] &= not_orgn_board;
        board->piece_bb[turn] &= not_orgn_board;

        // remove potential piece from dest square
        board->piece_bb[turn ^ 0b1] &= not_dest_board;
        board->piece_bb[KING_BB] &= not_dest_board;
        board->piece_bb[QUEEN_BB] &= not_dest_board;
        board->piece_bb[ROOK_BB] &= not_dest_board;
        board->piece_bb[BISHOP_BB] &= not_dest_board;
        board->piece_bb[KNIGHT_BB] &= not_dest_board;
        board->piece_bb[PAWN_BB] &= not_dest_board;

        // add moving piece to dest square
        board->piece_bb[move->piece + 2] |= dest_board;
        board->piece_bb[turn] |= dest_board;
    } else if (move->special == 1) { // promotion
        // TODO: implement promotion
    } else if (move->special == 2) { // en passant
        // TODO: implement en passant
    } else { // castle
        // TODO: implement castling
    }
}

Move get_move(char *from, char *to) {
    Move move;
    move.orgn = (from[0] - 65) + (from[1] - 49) * 8;
    move.dest = (to[0] - 65) + (to[1] - 49) * 8;
    return move;
}

U64 move_to_string(const Move *move) {
    U8 orgn_rank = move->orgn / 8;
    U8 orgn_file = move->orgn % 8;
    U8 dest_rank = move->dest / 8;
    U8 dest_file = move->dest % 8;

    orgn_rank += 49;
    orgn_file += 65;
    dest_rank += 49;
    dest_file += 65;

    char char_array[8] = {orgn_file, orgn_rank, dest_file, dest_rank, '\0', '\0', '\0', '\0'};
    
    U64 move_string = 0;
    for (I8 i = 7; i > -1; --i) {
        move_string = (move_string << 8) | char_array[i];
    }
    return move_string;
}

void move_print(const Move *move) {
    U64 move_string_value = move_to_string(move);
    char *move_string = (char *) &move_string_value;
    printf("%s", move_string);
}