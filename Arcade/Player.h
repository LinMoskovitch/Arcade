#pragma once

#include "Board.h"
class Player
{//Abstract class
protected:
	//Constructors
	Player() = delete;
	Player(PLAYER_SYMBOL symbol, bool turn);
	Player(const Player& other);
	Player(Player&& other);
	Player(ifstream& f, PLAYER_SYMBOL symbol);
public:
	//Destructor
	virtual ~Player();

	//Setters
	virtual void SetStonesArr() = 0;
	void SetTurn(bool ind);

	//Getters
	bool GetTurn() const;
	bool GetWinner() const;
	vector<Stone*>& GetStonesArr();
	PLAYER_SYMBOL GetPlayerSymbol() const;
	int GetNumOfStones() const;
	int GetNumOfStartingStones() const;

	//Methods
	void ChangeTurn();
	void PlayerWon();
	void DeleteStoneFromArr(Stone* toDelete);
	virtual void LoadStoneFromFile(ifstream& f) = 0;

protected:
	vector<Stone*> m_StonesArr;
	bool m_Turn;
	bool m_Won;
	PLAYER_SYMBOL m_Symbol;
	int m_NumOfStartingStones;
};