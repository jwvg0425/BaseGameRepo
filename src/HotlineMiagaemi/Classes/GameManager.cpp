#include "GameManager.h"
#include "Ant.h"
#include "Egg.h"

GameManager* GameManager::m_Instance = nullptr;

GameManager* GameManager::getInstance()
{
	if (m_Instance == nullptr)
	{
		m_Instance = new GameManager;
	}

	return m_Instance;
}

void GameManager::releaseInstance()
{
	if (m_Instance != nullptr)
	{
		delete m_Instance;
		m_Instance = nullptr;
	}
}

GameManager::GameManager() : m_NowAnt(nullptr)
{
	initAnt();
}

GameManager::~GameManager()
{

}

Ant* GameManager::getAnt()
{
	return m_NowAnt;
}

void GameManager::initAnt()
{
	m_NowAnt = new Egg();
}

void GameManager::setAnt(Ant* ant)
{
	if (m_NowAnt != nullptr)
	{
		delete m_NowAnt;
	}

	m_NowAnt = ant;
}
