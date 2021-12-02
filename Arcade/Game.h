#pragma once
#include "Player.h"

enum class GAME_CODE { CHECKERS = 1, AMAZONS, CHESS };

class Game
{//Abstract class
protected:
	//Constructors
	Game();
	Game(const Game& other);
	Game(Game&& other);
	Game(istream& f);
public:
	//Destructor
	virtual ~Game();

	//Setters
	virtual void StartNewGame();
	void SetWinner(PLAYER_SYMBOL winner);

	//Getters
	PLAYER_SYMBOL GetWinner() const;
	PLAYER_SYMBOL GetTurn() const;
	Player*& GetPlayer(PLAYER_SYMBOL playerSymbol);
	bool GetGameOverStatus() const;
    Board*& GetBoard();
	int GetPositionsForMove();
	const string& GetGameName() const;

	//Methods
	virtual void SetStonePossibleMoves(Stone* stone) = 0;
	virtual void CheckPossibleMovesForPosition(const Position& pos, int& numOfPossibleMoves);
	virtual void MoveValidation(Position* posArr) = 0;
	virtual void MakeAMove(const Position* posArr);
	virtual void DemandsForValidMove(string& demandsMessage) = 0;
	bool CheckDiagonal(const Position& currPos, const Position& nextPos);
	void ChangeTurn();
	virtual void EndOfTurn();
	virtual bool CheckIfGameOver() = 0;
	void GameOver();
	virtual void SaveGameToFile(ofstream& f);
	virtual void SaveStoneToFile(ofstream& f, Stone* stone);

protected:
	Player* m_PlayerO;
	Player* m_PlayerX;
	Board* m_Board;
	PLAYER_SYMBOL m_Winner;
	bool m_GameOver;
	PLAYER_SYMBOL m_PlayerPlaying;
	int m_PositionsForMove;
	string m_GameName;
};