#include "GameStateLevel.h"
#include <SFML/Window/Event.hpp>
#include "Game.h"

GameStateLevel::GameStateLevel(Game * owner) :
	GameState(owner), mCurrentLevel(0)
{
}

GameStateLevel::~GameStateLevel()
{
}

void GameStateLevel::entry()
{
	registerEvents();

}

void GameStateLevel::exit()
{
	unregisterEvents();
}

void GameStateLevel::update(const sf::Time & deltaTime)
{
	mEntityManager.update(deltaTime);
}

void GameStateLevel::draw(sf::RenderTarget & window) const
{
	mEntityManager.draw(window);
}

void GameStateLevel::registerEvents()
{
}

void GameStateLevel::unregisterEvents()
{
}

void GameStateLevel::observe(const sf::Event & _event)
{
	if (_event.type == sf::Event::EventType::Closed)
		mOwner->getRenderWindow()->close();
}

void GameStateLevel::enterLevel(size_t level)
{
	if (mCurrentLevel != level)
	{
		transition(this, this);
		setupLevel(level);
	}
}

void GameStateLevel::setupLevel(size_t level)
{
	switch (level)
	{
	case 1:
		setupLevel1();
		break;

	default:
		break;
	}
}

void GameStateLevel::setupLevel1()
{
	Entity* entity = new Entity();
	mEntityManager.addEntity(entity);
	entity->possess();
	entity->setPosition(50.0f, 50.0f);

	entity = new Entity();
	mEntityManager.addEntity(entity);
	entity->setPosition(100.0f, 100.0f);
}
