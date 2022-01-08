
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


// Maybe Piece and Point can be of type 'char' (1 byte = 8 bits)

typedef unsigned short Piece; 	// 00 	000
								// team type

typedef signed short Point; 	// 000  000
								// file rank

typedef unsigned int Info;		// 0000000	000000	0000	0000	00
								// turns 	counter passant castles team

typedef unsigned short Move;	// 000 	000000 000000
								// flag	point  point

// board: Piece[64] or Piece* board

// ==========================================

// I don't know if these are going to be used?:

typedef unsigned short Turns;	// 0000000

typedef unsigned short Counter; // 000000

typedef unsigned short Passant;	// 0000

typedef unsigned short Team;	// 00

typedef unsigned short Type;	// 000

typedef unsigned short Rank;	// 000

typedef unsigned short File;	// 000

typedef unsigned short Index;	//

#endif