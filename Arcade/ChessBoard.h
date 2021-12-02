#pragma once
#include "Board.h"
#include "ChessCell.h"

class ChessBoard : public Board
{
public:
	//Constructors
	ChessBoard() = delete;
	ChessBoard(int rows, int cols);
	ChessBoard(const ChessBoard& other);
	ChessBoard(ChessBoard&& other);

	//Desturctors
	virtual ~ChessBoard();

	//Setters
	void SetKingPos(PLAYER_SYMBOL playerPlaying, const Position& kingNewPos);

	//Getters
	const Position& GetKingPos(PLAYER_SYMBOL playerPlaying);

	//Methods
	bool ValidationCheckForThreatsRequest(const Position& pos, string& errorMessage);

private:
	Position m_KingPosPlayerO;
	Position m_KingPosPlayerX;
};

