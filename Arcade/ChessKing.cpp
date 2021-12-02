#include "ChessKing.h"

//---------------------------------------Constructors---------------------------------------//
ChessKing::ChessKing(const Position& pos, const char symbol, int index, PLAYER_SYMBOL playerProperty)
	: ChessStone(pos, symbol, index, playerProperty), m_Checked(false) {}

ChessKing::ChessKing(const ChessKing& other)
	: ChessStone(other), m_Checked(other.m_Checked) {}

ChessKing::ChessKing(ChessKing&& other)
	: ChessStone(other), m_Checked(other.m_Checked) {}

//---------------------------------------Destructor---------------------------------------//
ChessKing::~ChessKing() {}

//---------------------------------------Setters---------------------------------------//
void ChessKing::SetPossibleMoves(ChessBoard* board)
{
	Position nextPos;
	int possiblePawnsRow = m_Symbol == CHESS_SYMBOL::O_KING ? -1 : 1;

	for (int i = -1; i <= 1; ++i)
	{
		for (int j = -1; j <= 1; ++j)
		{
			nextPos = { m_Position.row + i, m_Position.col + j };
			if ((i == 0 && j == 0) || !board->CheckPositionInBoard(nextPos))
				continue;
			else if (board->GetCell(nextPos)->GetHaveStone()
				&& board->GetCell(nextPos)->GetStoneInCell()->GetPlayerProperty() == m_PlayerProperty)
				continue;
			else if (!CheckThreatsOnKing(board, nextPos))
				continue;
			
			if (board->GetCell(nextPos)->GetHaveStone())
				CheckIfThreatingAKing(board, nextPos);

			AddPossibleMove(nextPos);
			static_cast<ChessCell*>(board->GetCell(nextPos))->AddNewThreat(m_Position);
		}
	}
}

void ChessKing::SetChecked(bool newCheckedMode)
{
	m_Checked = newCheckedMode;
}

//---------------------------------------Getters---------------------------------------//
bool ChessKing::GetCheckedStatus() const
{
	return m_Checked;
}

//---------------------------------------Methods---------------------------------------//
