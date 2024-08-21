// Hendrik Junkawitsch

#include "pawn.h"

Bitboard64 *pawn_get_quiet_movemaps(U8 color) {
    Bitboard64 *movemaps = (Bitboard64 *) malloc(64 * sizeof(Bitboard64));
    assert(movemaps != NULL);
    for (U8 board_idx = 0; board_idx < 64; ++board_idx) {        
        movemaps[board_idx] = EMPTY_BOARD;
        // first rank (there should never be pawns)
        if (board_idx < 8) continue;
        Bitboard64 pawn_pos = POS_1 << board_idx;
        // single push
        movemaps[board_idx] |= pawn_pos << 8; 
        // double push
        if (board_idx < 16) movemaps[board_idx] |= pawn_pos << 16;
        // flip if color is black
        if (color != 0) bitboard_rotate_180(&movemaps[board_idx]);
    }
    // reverse bitboard array if color is black 
    if (color != 0) bitboard_reverse_array(movemaps, 64);
    return movemaps;
}

Bitboard64 *pawn_get_attack_maps(U8 color) {
    Bitboard64 *movemaps = (Bitboard64 *) malloc(64 * sizeof(Bitboard64));
    assert(movemaps != NULL);
    for (U8 board_idx = 0; board_idx < 64; ++board_idx) {
        movemaps[board_idx] = EMPTY_BOARD;
        // first rank (there should never be pawns)
        if (board_idx < 8) continue;
        Bitboard64 pawn_pos = POS_1 << board_idx;
        // attacks
        movemaps[board_idx] |= (pawn_pos << 7) & NOT_FILE_H;
        movemaps[board_idx] |= (pawn_pos << 9) & NOT_FILE_A;
        // flip if color is black
        if (color != 0) bitboard_rotate_180(&movemaps[board_idx]);
    }
    // reverse bitboard array if color is black 
    if (color != 0) bitboard_reverse_array(movemaps, 64);
    return movemaps;
}

Node *pawn_all_moves(const Board *board, const Bitboard64 *const *pawn_maps, Node *node) {
    U8 turn = (board->flags & TURN_MASK) >> 7;
    Bitboard64 pawns = board->piece_bb[PAWN_BB] & board->piece_bb[turn];
    U8 amount_pawns = bitboard_popcount(&pawns); 

    for (U8 p = 0; p < amount_pawns; ++p) {
        Square pawn_orgn = bitboard_pop_LSB(&pawns);
        Bitboard64 pawn_quiet_moves = pawn_maps[turn * 2][pawn_orgn] & ~board->piece_bb[turn] 
                                                                     & ~board->piece_bb[turn ^ 1];
        Bitboard64 pawn_attacks = pawn_maps[turn * 2 + 1][pawn_orgn] & ~board->piece_bb[turn] 
                                                                     & board->piece_bb[turn ^ 1];
        U8 amount_quiet_moves = bitboard_popcount(&pawn_quiet_moves);
        U8 amount_attacks = bitboard_popcount(&pawn_attacks);

        for (U8 qm = 0; qm < amount_quiet_moves; ++qm) {
            Square pawn_dest = bitboard_pop_LSB(&pawn_quiet_moves);
            Move* move = move_init();
            move->orgn = pawn_orgn;
            move->dest = pawn_dest;
            move->piece = PAWN_BB - 2;
            // for now
            move->special = 0;
            // TODO: en passant and promotion
            node = movelist_add(node, move);
        }
        for (U8 a = 0; a < amount_attacks; ++a) {
            Square pawn_dest = bitboard_pop_LSB(&pawn_attacks);
            Move* move = move_init();
            move->orgn = pawn_orgn;
            move->dest = pawn_dest;
            move->piece = PAWN_BB - 2;
            // for now
            move->special = 0;
            // TODO: promotion
            node = movelist_add(node, move);
        }
    }
    return node;
}