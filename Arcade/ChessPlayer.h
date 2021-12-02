#pragma once
#include "Player.h"
#include "ChessBoard.h"

class ChessPlayer : public Player
{
public:
	//Constructors
	ChessPlayer() = delete;
	ChessPlayer(PLAYER_SYMBOL symbol, bool turn);
	ChessPlayer(const ChessPlayer& other);
	ChessPlayer(ChessPlayer&& other);
	ChessPlayer(ifstream& f, PLAYER_SYMBOL symbol);

	//Destructor
	virtual ~ChessPlayer();

	//Setters
	virtual void SetStonesArr();

	//Getters

	//Methods
	virtual void LoadStoneFromFile(ifstream& f);

private:

};

