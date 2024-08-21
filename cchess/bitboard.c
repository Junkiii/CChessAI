// Hendrik Junkawitsch

#include "bitboard.h"

/**
 * Static Function: bitboard_write_to_file
 * ---------------------------------------
 * Helper function to write a single bitboard to a already opened file.
 */
static void bitboard_write_to_file(Bitboard64 bitboard, FILE *file);

Bitboard64 bitboard_random() {
    Bitboard64 u1 = (Bitboard64)(rand()) & 0xFFFF;
    Bitboard64 u2 = (Bitboard64)(rand()) & 0xFFFF;
    Bitboard64 u3 = (Bitboard64)(rand()) & 0xFFFF;
    Bitboard64 u4 = (Bitboard64)(rand()) & 0xFFFF;
    return u1 | (u2 << 16) | (u3 << 32) | (u4 << 48);
}

Bitboard64 bitboard_random_sparse() {
    return bitboard_random() & bitboard_random() & bitboard_random();
}

U8 bitboard_pop_LSB(Bitboard64 *bitboard) {
    if (*bitboard == 0) return -1;
    U8 pos = (U8)__builtin_ctzll(*bitboard);
    *bitboard &= (*bitboard) - 1;
    return pos;
}

U8 bitboard_popcount(const Bitboard64 *bitboard) {
    return __builtin_popcountll(*bitboard);
}

void bitboard_rotate_left(Bitboard64 *bitboard) {
    bitboard_flip_vertical(bitboard);
    bitboard_flip_diag_a1h8(bitboard);
}

void bitboard_rotate_right(Bitboard64 *bitboard) {
    bitboard_flip_vertical(bitboard);
    bitboard_flip_diag_a8h1(bitboard);
}

void bitboard_rotate_180(Bitboard64 *bitboard) {
    bitboard_flip_horizontal(bitboard);
    bitboard_flip_vertical(bitboard);
}

void bitboard_flip_diag_a1h8(Bitboard64 *bitboard) {
    Bitboard64 t;
    Bitboard64 k1 = 0x5500550055005500ULL;
    Bitboard64 k2 = 0x3333000033330000ULL;
    Bitboard64 k4 = 0x0f0f0f0f00000000ULL;
    t = k4 & (*bitboard ^ (*bitboard << 28));
    *bitboard ^= t ^ (t >> 28);
    t = k2 & (*bitboard ^ (*bitboard << 14));
    *bitboard ^= t ^ (t >> 14);
    t = k1 & (*bitboard ^ (*bitboard <<  7));
    *bitboard ^= t ^ (t >> 7);
}

void bitboard_flip_diag_a8h1(Bitboard64 *bitboard) {
    Bitboard64 t;
    Bitboard64 k1 = 0xaa00aa00aa00aa00ULL;
    Bitboard64 k2 = 0xcccc0000cccc0000ULL;
    Bitboard64 k4 = 0xf0f0f0f00f0f0f0fULL;
    t = *bitboard ^ (*bitboard << 36);
    *bitboard ^= k4 & (t ^ (*bitboard >> 36));
    t = k2 & (*bitboard ^ (*bitboard << 18));
    *bitboard ^= t ^ (t >> 18);
    t = k1 & (*bitboard ^ (*bitboard << 9));
    *bitboard ^= t ^ (t >> 9);
}

void bitboard_flip_vertical(Bitboard64 *bitboard) {
    *bitboard = __builtin_bswap64(*bitboard);
}

void bitboard_flip_horizontal(Bitboard64 *bitboard) {
    Bitboard64 k1 = 0x5555555555555555ULL;
    Bitboard64 k2 = 0x3333333333333333ULL;
    Bitboard64 k4 = 0x0f0f0f0f0f0f0f0fULL;
    *bitboard = ((*bitboard >> 1) & k1) +  2*(*bitboard & k1);
    *bitboard = ((*bitboard >> 2) & k2) +  4*(*bitboard & k2);
    *bitboard = ((*bitboard >> 4) & k4) + 16*(*bitboard & k4);
}

void bitboard_reverse_array(Bitboard64 *bitboards, U8 length) {
    I16 start = 0;
    I16 end = length - 1;
    while (start < end) {
        Bitboard64 temp = bitboards[start];
        bitboards[start] = bitboards[end];
        bitboards[end] = temp;
        start++;
        end--;
    }
}

void bitboard_print(Bitboard64 bitboard) {
    printf("\n    a b c d e f g h\n");
    printf("  +----------------\n");
    for (I8 rank = 8; rank >= 1; --rank) {
        printf("%d |", rank);
        for (I8 file = 1; file <= 8; ++file) {
            U8 square = (rank - 1) * 8 + (file - 1);
            Bitboard64 mask = POS_1 << square;
            if (bitboard & mask) printf(" X");
            else printf(" \u00B7");
        }
        printf("\n");
    }
}

void bitboard_write_multiple_to_file(const Bitboard64 *bitboards, U16 amount, char *path) {
    FILE *file = fopen(path, "w");
    if (file != NULL) {
        for (U16 i = 0; i < amount; ++i) {
            bitboard_write_to_file(bitboards[i], file);
        }
        fclose(file);
        printf("Bitboards successfully written to file.\n");
    } else {
        printf("Error opening the file!\n");
    }
}

static void bitboard_write_to_file(Bitboard64 bitboard, FILE *f) {
    fprintf(f, "\n    a b c d e f g h\n");
    fprintf(f, "  +----------------\n");
    for (U8 rank = 8; rank >= 1; --rank) {
        fprintf(f, "%d |", rank);
        for (U8 file = 1; file <= 8; ++file) {
            U8 square = (rank - 1) * 8 + (file - 1);
            Bitboard64 mask = POS_1 << square;
            if (bitboard & mask) fprintf(f, " X");
            else fprintf(f, " \u00B7");
        }
        fprintf(f, "\n");
    }
}