#include "ChessPawn.h"
#include "ChessBoard.h"

//---------------------------------------Constructors---------------------------------------//
ChessPawn::ChessPawn(const Position& pos, const char symbol, int index, PLAYER_SYMBOL playerProperty)
	: ChessStone(pos, symbol, index, playerProperty), m_FirstTurn(true) {}

ChessPawn::ChessPawn(const ChessPawn& other)
	: ChessStone(other), m_FirstTurn(other.m_FirstTurn) {}

ChessPawn::ChessPawn(ChessPawn&& other)
	: ChessStone(other), m_FirstTurn(other.m_FirstTurn) {}

//---------------------------------------Destructor---------------------------------------//
ChessPawn::~ChessPawn() {}

//---------------------------------------Setters---------------------------------------//
void ChessPawn::SetPossibleMoves(ChessBoard* board)
{
	Position nextPos, kingPos = board->GetKingPos(m_PlayerProperty);
	int rowDiff = 1; //default = CHESS_SYMBOL::X_PAWN

	if (m_Symbol == CHESS_SYMBOL::O_PAWN)
		rowDiff = -1;

	nextPos = { m_Position.row + rowDiff, m_Position.col };

	if (!board->GetCell(nextPos)->GetHaveStone())
	{//Free spot
		Swap(board->GetCell(m_Position), board->GetCell(nextPos));

		if (CheckThreatsOnKing(board, kingPos))
		{//This move not dangering the king
			Swap(board->GetCell(m_Position), board->GetCell(nextPos));

			CheckIfThreatingAKing(board, nextPos);
			AddPossibleMove(nextPos);
			static_cast<ChessCell*>(board->GetCell(nextPos))->AddNewThreat(m_Position);
		}
		else
			Swap(board->GetCell(m_Position), board->GetCell(nextPos));
	}

	if (m_FirstTurn && !board->GetCell(nextPos)->GetHaveStone())
	{//It's pawn's first move
		nextPos.row += rowDiff;

		if (board->CheckPositionInBoard(nextPos) && !board->GetCell(nextPos)->GetHaveStone())
		{//NextPos in board and free
			Swap(board->GetCell(m_Position), board->GetCell(nextPos));

			if (CheckThreatsOnKing(board, kingPos))
			{//This move not dangering the king
				Swap(board->GetCell(m_Position), board->GetCell(nextPos));

				CheckIfThreatingAKing(board, nextPos);
				AddPossibleMove(nextPos);
				static_cast<ChessCell*>(board->GetCell(nextPos))->AddNewThreat(m_Position);
			}
			else
				Swap(board->GetCell(m_Position), board->GetCell(nextPos));
		}
	}

	//Checking if there's a stone to be captured (a possible move)
	Position capturePotentialPos;

	for (int j = -1; j <= 1; j += 2)
	{
		capturePotentialPos = { m_Position.row + rowDiff, m_Position.col + j };

		if (board->CheckPositionInBoard(capturePotentialPos) &&
			board->GetCell(capturePotentialPos)->GetHaveStone())
		{//Position in board and having a stone on it
			if (board->GetCell(capturePotentialPos)->GetStoneInCell()->GetPlayerProperty() != m_PlayerProperty)
			{//A rival stone
				board->GetCell(capturePotentialPos)->SetHaveStone(false);
				Swap(board->GetCell(m_Position), board->GetCell(capturePotentialPos));

				if (CheckThreatsOnKing(board, kingPos))
				{//This move not dangering the king
					Swap(board->GetCell(m_Position), board->GetCell(capturePotentialPos));
					board->GetCell(capturePotentialPos)->SetHaveStone(true);

					CheckIfThreatingAKing(board, capturePotentialPos);
					AddPossibleMove(capturePotentialPos);
					static_cast<ChessCell*>(board->GetCell(capturePotentialPos))->AddNewThreat(m_Position);
				}
				else
				{
					Swap(board->GetCell(m_Position), board->GetCell(capturePotentialPos));
					board->GetCell(capturePotentialPos)->SetHaveStone(true);
				}
			}
		}
	}
}

void ChessPawn::MadeFirstMove()
{
	m_FirstTurn = false;
}

//---------------------------------------Getters---------------------------------------//
bool ChessPawn::GetFirstTurn() const
{
	return m_FirstTurn;
}

//---------------------------------------Methods---------------------------------------//