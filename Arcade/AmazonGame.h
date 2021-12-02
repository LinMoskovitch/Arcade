#pragma once
#include "Game.h"
#include "AmazonPlayer.h"

class AmazonGame : public Game
{
public:
	//Constructors
	AmazonGame();
	AmazonGame(const AmazonGame& other);
	AmazonGame(AmazonGame&& other);
	AmazonGame(ifstream& f);

	//Destructor
	virtual ~AmazonGame();

	//Setters

	//Getters

	//Methods
	void SetStonePossibleMoves(Stone* stone);
	void SetStonePossibleMovesRec(Stone* stone, int rowDiff, int colDiff);
	void UpdateDiffs(int& rowDiff, int& colDiff);
	void SetDiffs(const Position& source, const Position& destination, int& rowDiff, int& colDiff);
	void MoveValidation(Position* posArr);
	bool CheckStraightPath(const Position& currPos, const Position& nextPos);
	bool CheckPath(AmazonBoard*& board, Position& source, const Position& destination, int& rowDiff, int& colDiff);
	void MakeAMove(const Position* posArr);
	void SetThreats();
	void DemandsForValidMove(string& demandsMessage);
	virtual bool CheckIfGameOver();
	virtual void EndOfTurn();
	virtual void SaveGameToFile(ofstream& f);
	virtual void SaveStoneToFile(ofstream& f, Stone* stone);

private:

};