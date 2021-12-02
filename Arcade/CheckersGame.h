#pragma once
#include "Game.h"
#include "CheckersPlayer.h"

class CheckersGame : public Game
{
public:
	//Constructors
	CheckersGame();
	CheckersGame(const CheckersGame& other);
	CheckersGame(CheckersGame&& other);
	CheckersGame(ifstream& f);

	//Destructor
	virtual ~CheckersGame();

	//Setter

	//Methods
	virtual void SetStonePossibleMoves(Stone* stone);
	virtual void SetStonePossibleMovesRec(Stone* stone, int rowDiff, int colDiff);
	bool EatingPotential(const Position& pos);
	virtual void MoveValidation(Position* posArr);
	virtual void MakeAMove(const Position* posArr);
	virtual void DemandsForValidMove(string& demandsMessage);
	virtual bool CheckIfGameOver();
	virtual void SaveGameToFile(ofstream& f);
	virtual void SaveStoneToFile(ofstream& f, Stone* stone);

private:

};