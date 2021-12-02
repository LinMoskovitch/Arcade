#include "ChessQueen.h"
#include "ChessBoard.h"

//---------------------------------------Constructors---------------------------------------//
ChessQueen::ChessQueen(const Position& pos, const char symbol, int index, PLAYER_SYMBOL playerProperty)
	: ChessStone(pos, symbol, index, playerProperty) {}

ChessQueen::ChessQueen(const ChessQueen& other)
	: ChessStone(other) {}

ChessQueen::ChessQueen(ChessQueen&& other)
	: ChessStone(other) {}

//---------------------------------------Destructor---------------------------------------//
ChessQueen::~ChessQueen() {}

//---------------------------------------Setters---------------------------------------//
void ChessQueen::SetPossibleMoves(ChessBoard* board)
{
	Position currPosDiff;

	for (int i = -1; i <= 1; ++i)
	{
		for (int j = -1; j <= 1; ++j)
		{
			if (i != 0 || j != 0)
			{
				currPosDiff = { i, j };
				SetPossibleMovesRec(board, currPosDiff);
			}
		}
	}
}

//---------------------------------------Getters---------------------------------------//


//---------------------------------------Methods---------------------------------------//