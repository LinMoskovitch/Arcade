#pragma once
#include "Game.h"
#include "ChessPlayer.h"

class ChessGame : public Game
{
public:
	//Constructors
	ChessGame();
	ChessGame(const ChessGame& other);
	ChessGame(ChessGame&& other);
	ChessGame(ifstream& f);

	//Destructor
	virtual ~ChessGame();

	//Setters
	void SetStonePossibleMoves(Stone* stone);

	//Getters

	//Methods
	virtual void MoveValidation(Position* posArr);
	virtual void MakeAMove(const Position* posArr);
	void MakeAMoveWithPawn(ChessPawn* pawn, const Position pawnNextPos);
	virtual void DemandsForValidMove(string& demandsMessage);
	virtual bool CheckIfGameOver();
	virtual void EndOfTurn();
	virtual void SaveGameToFile(ofstream& f);
	virtual void SaveStoneToFile(ofstream& f, Stone* stone);

private:

};