// Hendrik Junkawitsch

#include "pieces.h"

Precalc *pieces_precalculation() {
    // TODO: make struct and data within struct completely constant
    
    Precalc *precalc = (Precalc *) malloc(sizeof(Precalc));
    assert(precalc != NULL);

    precalc->pawn = (Bitboard64 **) malloc(4 * sizeof(Bitboard64 *));
    assert(precalc->pawn != NULL);

    // precalculate pawn move maps
    precalc->pawn[0] = pawn_get_quiet_movemaps(0);
    precalc->pawn[1] = pawn_get_attack_maps(0);
    precalc->pawn[2] = pawn_get_quiet_movemaps(1);
    precalc->pawn[3] = pawn_get_attack_maps(1);

    // precalculate knight and king move maps
    precalc->knight = knight_get_movemaps();
    precalc->king = king_get_movemaps();

    // precalculate bishop and rook magics
    precalc->rook = magic_compute(0);
    precalc->bishop = magic_compute(1);

    return precalc;
}

Node *pieces_all_moves(const Board *board, const Precalc *precalc) {
    Node *movelist;
    movelist = king_all_moves(board, precalc->king, NULL);
    movelist = queen_all_moves(board, precalc->rook, precalc->bishop, movelist);
    movelist = rook_all_moves(board, precalc->rook, movelist);
    movelist = bishop_all_moves(board, precalc->bishop, movelist);
    movelist = knight_all_moves(board, precalc->knight, movelist);
    movelist = pawn_all_moves(board, (const Bitboard64 *const *) precalc->pawn, movelist);

    return movelist;
}

char* pieces_name(U8 id) {
    assert(id < 6 && id > -1);
    switch(id) {
        case 0: return "KING";
        case 1: return "QUEEN";
        case 2: return "ROOK";
        case 3: return "BISHOP";
        case 4: return "KNIGHT";
        case 5: return "PAWN";
    }
}