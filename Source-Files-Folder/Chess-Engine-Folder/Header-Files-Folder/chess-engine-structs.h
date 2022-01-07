
#ifndef CHESS_ENGINE_STRUCTS_H
#define CHESS_ENGINE_STRUCTS_H

// rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1

// Bits 0-3 store white and black kingside/queenside castling legality		4
// Bits 4-7 store file of ep square (starting at 1, so 0 = no ep square)	4
// Bits 8-13 captured piece													6
// Bits 14-... fifty mover counter											+

// 	current			castles 		passant		turns		counter	
//	white/black		true/false * 4	file		0 - 128?	0 - 64
//	00				0000			0000		00000000	0000000

//	0000000 00000000 0000 0000 00

typedef unsigned int Piece; 	// 00 	000
								// team type

typedef int Point; 				// 000  000
								// file rank

typedef unsigned int Info;		// ????			 0000	 0000	 00
								// turns counter passant castles team

// board: Piece[64] or Piece* board

typedef unsigned int Castle;	// 0000

typedef unsigned int Turns;		// 000000

typedef unsigned int Counter; 	// 000000

typedef unsigned int File;		// 0000

#endif