// Hendrik Junkawitsch

#pragma once

typedef signed char I8;         // 8-bit signed value
typedef signed int I16;         // 16-bit signed value
typedef signed long I32;        // 32-bit signed value
typedef signed long long I64;   // 64-bit signed value

typedef unsigned long long U64; // 64-bit unsigned value
typedef unsigned long U32;      // 32-bit unsigned value
typedef unsigned int U16;       // 16-bit unsigned value
typedef unsigned char U8;       //  8-bit unsigned value

typedef struct node Node;       // linked list (move list)
typedef U8 Square;              // square on the 64-bit bitboard [0,64)
typedef U16 Square2d;           // square in the 2d representation
typedef Square2d** Board8x8;    // 8x8 board [file][rank] (increasing number)
typedef U64 Bitboard64;         // 64-bit bitboard
typedef struct board Board;     // dense bitboard board representation
typedef struct move Move;       // move representation
typedef struct magic Magic;     // magic struct
typedef struct precalc Precalc; // precalculated data for move generation