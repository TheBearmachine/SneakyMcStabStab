#include "EntityStatePossess.h"
#include "Entity.h"
#include "Constants.h"
#include "VectorFunctions.h"
#include "EventManager.h"
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>

EntityStatePossess::EntityStatePossess(Entity * owner) :
	EntityState(owner)
{
	mRegistered = false;
}

EntityStatePossess::~EntityStatePossess()
{
}

void EntityStatePossess::registerEvents()
{
	if (mEventManager && !mRegistered)
	{
		mRegistered = true;
		mEventManager->registerObserver(this, sf::Event::EventType::KeyPressed);
	}
}

void EntityStatePossess::unregisterEvents()
{
	if (mEventManager && mRegistered)
	{
		mRegistered = false;
		mEventManager->registerObserver(this, sf::Event::EventType::KeyPressed);
	}
}

void EntityStatePossess::observe(const sf::Event & _event)
{
}

void EntityStatePossess::entry()
{
}

void EntityStatePossess::exit()
{
}

void EntityStatePossess::update(const sf::Time & deltaTime)
{
	sf::Vector2f toMove;
	float speed = Constants::Player::MoveSpeed;
	if (sf::Keyboard::isKeyPressed(Constants::Player::Binds::Left))
	{
		toMove.x = -1.0f;
	}
	else if (sf::Keyboard::isKeyPressed(Constants::Player::Binds::Right))
	{
		toMove.x = 1.0f;
	}
	if (sf::Keyboard::isKeyPressed(Constants::Player::Binds::Up))
	{
		toMove.y = -1.0f;
	}
	else if (sf::Keyboard::isKeyPressed(Constants::Player::Binds::Down))
	{
		toMove.y = 1.0f;
	}
	if (sf::Keyboard::isKeyPressed(Constants::Player::Binds::Sneak))
	{
		speed = Constants::Player::SneakSpeed;
	}

	VectorFunctions::normalizeVector(toMove);
	toMove *= deltaTime.asSeconds() * speed;
	mOwner->move(toMove);
}

void EntityStatePossess::setEventManager(EventManager * eventManager)
{
	mEventManager = eventManager;
}
