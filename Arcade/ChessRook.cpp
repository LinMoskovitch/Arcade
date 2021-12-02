#include "ChessRook.h"

//---------------------------------------Constructors---------------------------------------//
ChessRook::ChessRook(const Position& pos, const char symbol, int index, PLAYER_SYMBOL playerProperty)
	: ChessStone(pos, symbol, index, playerProperty) {}

ChessRook::ChessRook(const ChessRook& other)
	: ChessStone(other) {}

ChessRook::ChessRook(ChessRook&& other)
	: ChessStone(other) {}

//---------------------------------------Destructor---------------------------------------//
ChessRook::~ChessRook() {}

//---------------------------------------Setters---------------------------------------//
void ChessRook::SetPossibleMoves(ChessBoard* board)
{
	const int numOfDiffs = 4;
	Position diffsArr[numOfDiffs] = { {1, 0}, {-1, 0}, {0, 1},{0, -1} };

	for (int i = 0; i < numOfDiffs; ++i)
	{
		SetPossibleMovesRec(board, diffsArr[i]);
	}
}

//---------------------------------------Getters---------------------------------------//


//---------------------------------------Methods---------------------------------------//