#include "ChessKnight.h"
#include "ChessBoard.h"

//---------------------------------------Constructors---------------------------------------//
ChessKnight::ChessKnight(const Position& pos, const char symbol, int index, PLAYER_SYMBOL playerProperty)
	: ChessStone(pos, symbol, index, playerProperty) {}

ChessKnight::ChessKnight(const ChessKnight& other)
	: ChessStone(other) {}

ChessKnight::ChessKnight(ChessKnight&& other)
	: ChessStone(other) {}

//---------------------------------------Destructor---------------------------------------//
ChessKnight::~ChessKnight() {}

//---------------------------------------Setters---------------------------------------//
void ChessKnight::SetPossibleMoves(ChessBoard* board)
{
	const int numOfMaxPossibleMoves = 8;
	Position nextPos, kingPos = board->GetKingPos(m_PlayerProperty);
	array<Position, numOfMaxPossibleMoves> posArrDiffs = { -2, -1, -2, 1, 2, -1, 2, 1, -1, -2, 1, -2, -1, 2, 1, 2 };
	bool nextPosHaveStone;

	for (int i = 0; i < numOfMaxPossibleMoves; ++i)
	{
		nextPos = { m_Position.row + posArrDiffs[i].row, m_Position.col + posArrDiffs[i].col };

		if (board->CheckPositionInBoard(nextPos))
		{//nextPos in board
			if (!board->GetCell(nextPos)->GetHaveStone()
				|| board->GetCell(nextPos)->GetStoneInCell()->GetPlayerProperty() != m_PlayerProperty)
			{//Free position, or a rival stone
				nextPosHaveStone = board->GetCell(nextPos)->GetHaveStone();

				board->GetCell(nextPos)->SetHaveStone(false);
				Swap(board->GetCell(m_Position), board->GetCell(nextPos));

				if (CheckThreatsOnKing(board, kingPos))
				{
					Swap(board->GetCell(m_Position), board->GetCell(nextPos));
					board->GetCell(nextPos)->SetHaveStone(nextPosHaveStone);

					CheckIfThreatingAKing(board, nextPos);
					AddPossibleMove(nextPos);
					static_cast<ChessCell*>(board->GetCell(nextPos))->AddNewThreat(m_Position);
				}
				else
				{
					Swap(board->GetCell(m_Position), board->GetCell(nextPos));
					board->GetCell(nextPos)->SetHaveStone(nextPosHaveStone);
				}
			}
		}
	}
}

//---------------------------------------Getters---------------------------------------//


//---------------------------------------Methods---------------------------------------//