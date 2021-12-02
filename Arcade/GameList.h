#pragma once
#include "Game.h"
#include "AmazonGame.h"
#include "CheckersGame.h"
#include "ChessGame.h"

class GameListNode;

class GameList
{
public:
	class GameListNode
	{
	public:
		//Constructors
		GameListNode(int gameSelection);

		//Destructor
		~GameListNode();

		//Setters
		void SetPrev(GameListNode* prev);
		void SetNext(GameListNode* next);

		//Getters
		GameListNode*& GetPrevGame();
		GameListNode*& GetNextGame();
		Game*& GetGame();
		int GetGameNameIndex();

		//Methods

	private:
		Game* m_game;
		int m_GameNameIndex;
		GameListNode* m_prev = nullptr;
		GameListNode* m_next = nullptr;
	};

	//Constructors
	GameList();

	//Destructor
	~GameList();

	//Getters
	GameListNode*& GetHead();
	GameListNode*& GetTail();
	GameListNode*& GetCurrGame();
	int GetNumOfGames();
	int GetCurrGameIndex();

	//Setters
	void CreateNewGame(int gameSelection);
	void SetHead(GameListNode* newHead);
	void SetTail(GameListNode* newTail);
	void UpdateCurrGameIndex(int index);

	//Methods
	bool isEmptyList();
	void InsertToEndList(GameList::GameListNode* newTail);
	void DeleteCurrGameFromList();
	bool MoveToNextGame();

private:
	GameListNode* m_currGame;
	GameListNode* m_head;
	GameListNode* m_tail;
	int m_numOfGames;
	int m_currGameIndex;
};