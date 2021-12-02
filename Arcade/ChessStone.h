#pragma once
#include "Stone.h"

enum class CHESS_SYMBOL {
	X_QUEEN = 'Q', X_KING = 'K', X_KNIGHT = 'N', X_BISHOP = 'B', X_PAWN = 'P', X_ROOK = 'R',
	O_QUEEN = 'q', O_KING = 'k', O_KNIGHT = 'n', O_BISHOP = 'b', O_PAWN = 'p', O_ROOK = 'r'
};

enum class CHESS_NUMBERS { NUM_OF_PAWNS = 8, TOTAL_CHESS_STONES = 16, ROWS = 8, COLS = 8, KING_INDEX = 0};

class ChessBoard;

class ChessStone : public Stone
{
public:
	//Constructors
	ChessStone() = delete;
	ChessStone(const Position& pos, const char symbol, int index, PLAYER_SYMBOL playerProperty);
	ChessStone(const ChessStone& other);
	ChessStone(ChessStone&& other);

	//Destructor
	virtual ~ChessStone();

	//Setters
	virtual void SetPossibleMoves(ChessBoard* board) = 0;
	virtual void SetPossibleMovesRec(ChessBoard* board, Position& posDiff);
	virtual void CheckIfThreatingAKing(ChessBoard* board, const Position& nextPos);

	//Getters

	//Methods
	void UpdateDiffs(Position& posDiff);
	bool CheckThreatsOnKing(ChessBoard* board, const Position& kingPos);
	bool CheckPossibleThreatsInStraightPaths(ChessBoard* board, const Position& kingPos);
	bool CheckPossibleThreatsInStraightPathsRec(ChessBoard* board, const Position& kingPos, Position& posDiffs);
	bool CheckPossibleThreatsByKing(ChessBoard* board, const Position& kingPos);
	bool CheckPossibleThreatsByPawns(ChessBoard* board, const Position& kingPos);
	bool CheckPossibleThreatsByKnights(ChessBoard* board, const Position& kingPos);
	bool CheckDiagonal(const Position& src, const Position& dest);

	//Operators
protected:

};

bool operator==(const char symbol, const CHESS_SYMBOL chessSymbol);