#include "GameList.h"

//---------------------------------------Constructors---------------------------------------//
GameList::GameList()
	: m_currGame(nullptr), m_head(nullptr), m_tail(nullptr), m_numOfGames(0),
	m_currGameIndex(0) {}

GameList::GameListNode::GameListNode(int gameSelection)
	: m_game(nullptr), m_prev(nullptr), m_next(nullptr)
{
	try
	{
		switch (gameSelection)
		{
			case 1:
			{
				m_game = new CheckersGame();
				m_GameNameIndex = 0;
				break;
			}
			case 2:
			{
				m_game = new AmazonGame();
				m_GameNameIndex = 1;
				break;
			}
			case 3:
			{
				m_game = new ChessGame();
				m_GameNameIndex = 2;
				break;
			}
			default:
				throw invalid_argument("Invalid selection of a game.");
		}
	}
	catch (bad_alloc& ba)
	{
		throw bad_alloc();
	}
}

//---------------------------------------Destructor---------------------------------------//
GameList::~GameList()
{
	GameList::GameListNode* currNode = m_head;

	while (nullptr != currNode)
	{
		SetHead(m_head->GetNextGame());
		delete currNode;
		currNode = m_head;
	}

	m_head = m_tail = m_currGame = nullptr;
	m_currGameIndex = m_numOfGames = 0;
}

GameList::GameListNode::~GameListNode()
{
	delete m_game;
}

//---------------------------------------Setters---------------------------------------//
void GameList::SetHead(GameList::GameListNode* newHead)
{
	m_head = newHead;
}

void GameList::SetTail(GameListNode* newTail)
{
	m_tail = newTail;
}

void GameList::GameListNode::SetPrev(GameListNode* prev)
{
	m_prev = prev;
}

void GameList::GameListNode::SetNext(GameListNode* next)
{
	m_next = next;
}

//---------------------------------------Getters---------------------------------------//
GameList::GameListNode*& GameList::GetHead()
{
	return m_head;
}

GameList::GameListNode*& GameList::GetTail()
{
	return m_tail;
}

GameList::GameListNode*& GameList::GetCurrGame()
{
	return m_currGame;
}

int GameList::GetNumOfGames()
{
	return m_numOfGames;
}

int GameList::GetCurrGameIndex()
{
	return m_currGameIndex;
}

GameList::GameListNode*& GameList::GameListNode::GetPrevGame()
{
	return m_prev;
}

Game*& GameList::GameListNode::GetGame()
{
	return m_game;
}

int GameList::GameListNode::GetGameNameIndex()
{
	return m_GameNameIndex;
}

GameList::GameListNode*& GameList::GameListNode::GetNextGame()
{
	return m_next;
}

//---------------------------------------Methods---------------------------------------//
void GameList::InsertToEndList(GameList::GameListNode* newTail)
{
	if (nullptr == m_head)
	{//Adding the first game to the list
		m_head = m_tail = newTail;
	}
	else
	{
		newTail->SetPrev(m_tail);
		m_tail->SetNext(newTail);
		m_tail = newTail;
	}
	m_currGame = newTail;
}

void GameList::DeleteCurrGameFromList()
{
	GameList::GameListNode* toDelete = m_currGame;
	GameList::GameListNode* dummy = nullptr;

	if (m_head == m_tail)
	{//Deleting the only game on the list
		m_head = m_tail = nullptr;
		m_currGameIndex = 0;
	}
	else if (m_head == toDelete)
	{//Deleting the first game on the list
		SetHead(m_head->GetNextGame());
		m_head->SetPrev(dummy);
		m_currGame = m_head;
		m_currGameIndex = 1;
	}
	else if (m_tail == toDelete)
	{//Deleting the last game on the list
		SetTail(m_tail->GetPrevGame());
		m_tail->SetNext(dummy);
		m_currGame = m_head;
		m_currGameIndex = 1;
	}
	else
	{//Deleting the game from the middle of the list
		toDelete->GetPrevGame()->SetNext(toDelete->GetNextGame());
		toDelete->GetNextGame()->SetPrev(toDelete->GetPrevGame());
		m_currGame = m_currGame->GetNextGame();
	}

	--m_numOfGames;

	delete toDelete;
}

bool GameList::MoveToNextGame()
{
	if (m_head == m_tail)
		return false;
	else if (m_currGame == m_tail)
	{
		m_currGame = m_head;
		m_currGameIndex = 1;
	}
	else
	{
		m_currGame = m_currGame->GetNextGame();
		++m_currGameIndex;
	}
	return true;
}

void GameList::UpdateCurrGameIndex(int index)
{
	m_currGameIndex = index;
}

bool GameList::isEmptyList()
{
	return m_head == nullptr;
}

void GameList::CreateNewGame(int gameSelection)
{
	GameListNode* newGame = new GameListNode(gameSelection);

	if (nullptr == newGame)
		throw bad_alloc();

	++m_numOfGames;
	m_currGameIndex = m_numOfGames;

	InsertToEndList(newGame);
}