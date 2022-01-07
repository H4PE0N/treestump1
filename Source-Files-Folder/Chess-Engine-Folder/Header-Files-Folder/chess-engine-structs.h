
#ifndef CHESS_ENGINE_STRUCTS_H
#define CHESS_ENGINE_STRUCTS_H

// rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1

// Bits 0-3 store white and black kingside/queenside castling legality		4
// Bits 4-7 store file of ep square (starting at 1, so 0 = no ep square)	4
// Bits 8-13 captured piece													6
// Bits 14-... fifty mover counter											+
	
// 	current			castles 		passant		counter		turns	
//	white/black		true/false * 4	0 - 15		0 - 63		0 - 127
//	00				0000			0000		000000 		0000000

//	0000000 000000 0000 0000 00

typedef unsigned int Piece; 	// 00 	000
								// team type

typedef int Point; 				// 000  000
								// file rank

typedef unsigned int Info;		// 0000000	000000	0000	0000	00
								// turns 	counter passant castles team

// board: Piece[64] or Piece* board

// ==========================================

typedef unsigned int Turns;		// 0000000

typedef unsigned int Counter; 	// 000000

typedef unsigned int Passant;	// 0000

typedef unsigned int Team;		// 00

typedef unsigned int Type;		// 000

typedef unsigned int Rank;		// 000

typedef unsigned int File;		// 000

#endif