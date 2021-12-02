#include "ChessBishop.h"

//---------------------------------------Constructors---------------------------------------//
ChessBishop::ChessBishop(const Position& pos, const char symbol, int index, PLAYER_SYMBOL playerProperty)
	: ChessStone(pos, symbol, index, playerProperty) {}

ChessBishop::ChessBishop(const ChessBishop& other)
	: ChessStone(other) {}

ChessBishop::ChessBishop(ChessBishop&& other)
	: ChessStone(other) {}

//---------------------------------------Destructor---------------------------------------//
ChessBishop::~ChessBishop() {}

//---------------------------------------Setters---------------------------------------//
void ChessBishop::SetPossibleMoves(ChessBoard* board)
{
	const int numOfDiffs = 4;
	Position diffsArr[numOfDiffs] = { {1, 1}, {1, -1}, {-1, 1},{-1, -1} };

	for (int i = 0; i < numOfDiffs ; ++i)
	{
		SetPossibleMovesRec(board, diffsArr[i]);
	}
}

//---------------------------------------Getters---------------------------------------//


//---------------------------------------Methods---------------------------------------//