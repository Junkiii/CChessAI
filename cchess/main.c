// Hendrik Junkawitsch

#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "board.h"
#include "pieces.h"
#include "magic.h"

/* main.c */
int main(int argc, char *argv[]) {
    printf("CCHESS ENGINE by Hendrik Junkawitsch\n\n");
    // misc prior setup
    setlocale(LC_ALL, "");
    srand(time(NULL));

    // precalculation
    printf("Precalculation... ");
    fflush(stdout);
    clock_t diff;
    clock_t start = clock();
    Precalc *precalc = pieces_precalculation();
    diff = clock() - start;
    printf("Finished!\n");
    int msec = diff * 1000 / CLOCKS_PER_SEC;
    printf("Time taken: %d seconds %d milliseconds.\n\n", msec/1000, msec%1000);

    // create board with starting position
    Board board;
    board_starting_position(&board);
    board_print(&board);

    // testing
    Node *all_moves = pieces_all_moves(&board, precalc);
    movelist_print(all_moves);
    
    move_make(&board, all_moves->move);
    board_print(&board);

    printf("\n\nEND\n\n");

    return 0;
}