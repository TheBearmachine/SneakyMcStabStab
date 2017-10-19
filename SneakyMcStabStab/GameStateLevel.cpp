#include "GameStateLevel.h"
#include <SFML/Window/Event.hpp>
#include "Game.h"
#include "EventManager.h"

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
	mEntityManager.detectCollisions();
}

void GameStateLevel::draw(sf::RenderTarget & window) const
{
	mEntityManager.draw(window);
}

void GameStateLevel::registerEvents()
{
	if (mEventManager)
	{
		mEventManager->registerObserver(this, sf::Event::EventType::Closed);
	}
}

void GameStateLevel::unregisterEvents()
{
	if (mEventManager)
	{
		mEventManager->unregisterObserver(this, sf::Event::EventType::Closed);
	}
}

void GameStateLevel::observe(const sf::Event & _event)
{
	if (_event.type == sf::Event::EventType::Closed)
		mOwner->getRenderWindow()->close();
}

void GameStateLevel::setEventManager(EventManager * eventManager)
{
	mEventManager = eventManager;
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
	entity->setEventManager(mOwner->getEventManager());
	entity->possess();
	entity->setPosition(50.0f, 50.0f);
	mEntityManager.addEntity(entity);

	entity = new Entity();
	entity->setPosition(100.0f, 100.0f);
	entity->populatePatrolQueue(sf::Vector2f(200.0f, 100.0f));
	entity->populatePatrolQueue(sf::Vector2f(100.0f, 100.0f));
	mEntityManager.addEntity(entity);

	entity = new Entity();
	entity->setPosition(50.0f, 350.0f);
	entity->populatePatrolQueue(sf::Vector2f(250.0f, 350.0f));
	entity->populatePatrolQueue(sf::Vector2f(250.0f, 250.0f));
	entity->populatePatrolQueue(sf::Vector2f(50.0f, 250.0f));
	entity->populatePatrolQueue(sf::Vector2f(50.0f, 350.0f));
	mEntityManager.addEntity(entity);

	Wall* wall = new Wall(sf::Vector2f(250, 20), sf::Vector2f(20, 100));
	mEntityManager.addWall(wall);

	wall = new Wall(sf::Vector2f(350, 20), sf::Vector2f(20, 100));
	mEntityManager.addWall(wall);

	wall = new Wall(sf::Vector2f(20, 180), sf::Vector2f(200, 20));
	mEntityManager.addWall(wall);

	wall = new Wall(sf::Vector2f(280, 180), sf::Vector2f(340, 20));
	mEntityManager.addWall(wall);

	wall = new  Wall(sf::Vector2f(0, 0), sf::Vector2f(640, 20));
	mEntityManager.addWall(wall);

	wall = new  Wall(sf::Vector2f(0, 0), sf::Vector2f(20, 480));
	mEntityManager.addWall(wall);

	wall = new  Wall(sf::Vector2f(0, 460), sf::Vector2f(640, 20));
	mEntityManager.addWall(wall);

	wall = new  Wall(sf::Vector2f(620, 0), sf::Vector2f(20, 480));
	mEntityManager.addWall(wall);

	mEntityManager.setSearchTargets();
}
