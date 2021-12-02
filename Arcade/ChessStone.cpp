#include "ChessStone.h"
#include "ChessBoard.h"

//---------------------------------------Constructors---------------------------------------//
ChessStone::ChessStone(const Position& pos, const char symbol, int index, PLAYER_SYMBOL playerProperty)
	: Stone(pos, symbol, playerProperty, index) {}

ChessStone::ChessStone(const ChessStone& other)
	: Stone(other) {}

ChessStone::ChessStone(ChessStone&& other)
	: Stone(other) {}

//---------------------------------------Destructor---------------------------------------//
ChessStone::~ChessStone() {}

//---------------------------------------Setters---------------------------------------//
void ChessStone::SetPossibleMovesRec(ChessBoard* board, Position& posDiff)
{
		Position nextPos = { m_Position.row + posDiff.row, m_Position.col + posDiff.col };

		if (board->CheckPositionInBoard(nextPos))
		{//Valid position on board
			if (!board->GetCell(nextPos)->GetHaveStone())
			{//Free position
				UpdateDiffs(posDiff);
				SetPossibleMovesRec(board, posDiff);
			}
			else if (board->GetCell(nextPos)->GetStoneInCell()->GetPlayerProperty() == m_PlayerProperty)
			{//Taken position with another stone of the same player (not a possible move)
				return;
			}

			Position kingPos = board->GetKingPos(m_PlayerProperty);
			bool nextPosHaveStone = board->GetCell(nextPos)->GetHaveStone();

			board->GetCell(nextPos)->SetHaveStone(false);
			Swap(board->GetCell(m_Position), board->GetCell(nextPos));

			if (CheckThreatsOnKing(board, kingPos))
			{//This move is not dangering the king
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

void ChessStone::CheckIfThreatingAKing(ChessBoard* board, const Position& nextPos)
{
	ChessKing* possibleRivalKing = dynamic_cast<ChessKing*>(board->GetCell(nextPos)->GetStoneInCell());

	if (nullptr != possibleRivalKing)
	{//There's a rival king
		possibleRivalKing->SetChecked(true);
	}
}

//---------------------------------------Getters---------------------------------------//


//---------------------------------------Methods---------------------------------------//
void ChessStone::UpdateDiffs(Position& posDiff)
{
	if (posDiff.row > 0)
		++posDiff.row;
	else if (posDiff.row < 0)
		--posDiff.row;

	if (posDiff.col > 0)
		++posDiff.col;
	else if (posDiff.col < 0)
		--posDiff.col;
}

bool ChessStone::CheckThreatsOnKing(ChessBoard* board, const Position& kingPos)
{
	if (!CheckPossibleThreatsByKing(board, kingPos))
		return false;
	else if (!CheckPossibleThreatsByKnights(board, kingPos))
		return false;
	else if (!CheckPossibleThreatsByPawns(board, kingPos))
		return false;
	else if (!CheckPossibleThreatsInStraightPaths(board, kingPos))
		return false;

	return true;
}

bool ChessStone::CheckPossibleThreatsInStraightPaths(ChessBoard* board, const Position& kingPos)
{
	const int numOfDiffs = 8;
	array<Position, numOfDiffs> posDiffArr = { -1, -1, -1, 0, -1, 1, 0, -1, 0, 1, 1, -1, 1, 0, 1, 1 };

	for (int i = 0; i < numOfDiffs; ++i)
	{
		if (!CheckPossibleThreatsInStraightPathsRec(board, kingPos, posDiffArr[i]))
			return false;
	}

	return true;
}

bool ChessStone::CheckPossibleThreatsInStraightPathsRec(ChessBoard* board, const Position& kingPos, Position& posDiffs)
{
	Position currPos = { kingPos.row + posDiffs.row, kingPos.col + posDiffs.col };

	if (!board->CheckPositionInBoard(currPos))
		return true;
	else if (board->GetCell(currPos)->GetHaveStone())
	{
		Stone* stoneFound = board->GetCell(currPos)->GetStoneInCell();

		if (stoneFound->GetPlayerProperty() == m_PlayerProperty)
			return true;

		//The stone found is a rival stone
		if (CheckDiagonal(kingPos, currPos) && typeid(*stoneFound) == typeid(ChessBishop))
			return false;
		else if (typeid(*stoneFound) == typeid(ChessRook))
			return false;

		if (typeid(*stoneFound) == typeid(ChessQueen))
			return false;

		return true;
	}

	UpdateDiffs(posDiffs);
	return CheckPossibleThreatsInStraightPathsRec(board, kingPos, posDiffs);
}

bool ChessStone::CheckPossibleThreatsByKing(ChessBoard* board, const Position& kingPos)
{
	Position possibleKingThreatPos;

	for (int i = -1; i <= 1; ++i)
	{
		for (int j = -1; j <= 1; ++j)
		{
			possibleKingThreatPos = { kingPos.row + i, kingPos.col + j };

			if ((i == 0 && j == 0) || !board->CheckPositionInBoard(possibleKingThreatPos))
				continue;
			else if (!board->GetCell(possibleKingThreatPos)->GetHaveStone())
				continue;
			else
			{//There's another stone around the next position of the king
				ChessKing* possibleKing = dynamic_cast<ChessKing*>(board->GetCell(possibleKingThreatPos)->GetStoneInCell());
				if (nullptr != possibleKing && possibleKing->GetPlayerProperty() != m_PlayerProperty)
					return false;
			}
		}
	}
	return true;
}

bool ChessStone::CheckPossibleThreatsByPawns(ChessBoard* board, const Position& kingPos)
{
	int rowDiff = m_PlayerProperty == PLAYER_SYMBOL::O_PLAYER ? -1 : 1;
	Position possiblePawnThreatPos;

	for (int j = -1; j <= 1; j += 2)
	{
		possiblePawnThreatPos = { kingPos.row + rowDiff, kingPos.col + j };
		if (!board->CheckPositionInBoard(possiblePawnThreatPos) || !board->GetCell(possiblePawnThreatPos)->GetHaveStone())
			continue;
		else
		{//There's a chance of a rival pawn in king's new position corners
			ChessPawn* possiblePawn = dynamic_cast<ChessPawn*>(board->GetCell(possiblePawnThreatPos)->GetStoneInCell());
			if (nullptr != possiblePawn && possiblePawn->GetPlayerProperty() != m_PlayerProperty)
				return false;
		}
	}
	return true;
}

bool ChessStone::CheckPossibleThreatsByKnights(ChessBoard* board, const Position& kingPos)
{
	const int numOfMaxPossibleMoves = 8;
	Position possibleKnightThreatPos;
	Position posArrDiffs[numOfMaxPossibleMoves] = { {-2, -1}, {-2, 1}, {2, -1}, {2, 1}, {-1, -2}, {1, -2}, {-1, 2}, {1, 2} };

	for (int i = 0; i < numOfMaxPossibleMoves; ++i)
	{
		possibleKnightThreatPos = { kingPos.row + posArrDiffs[i].row, kingPos.col + posArrDiffs[i].col };
		if (!board->CheckPositionInBoard(possibleKnightThreatPos) || !board->GetCell(possibleKnightThreatPos)->GetHaveStone())
			continue;
		else
		{
			ChessKnight* possibleKnight = dynamic_cast<ChessKnight*>(board->GetCell(possibleKnightThreatPos)->GetStoneInCell());
			if (nullptr != possibleKnight && possibleKnight->GetPlayerProperty() != m_PlayerProperty)
				return false;
		}
	}
	return true;
}

bool ChessStone::CheckDiagonal(const Position& src, const Position& dest)
{
	if (abs(src.row - dest.row) == abs(src.col - dest.col))
		return true;
	return false;
}

//---------------------------------------Operators---------------------------------------//
bool operator==(const char symbol, const CHESS_SYMBOL chessSymbol)
{
	return symbol == static_cast<char>(chessSymbol);
}