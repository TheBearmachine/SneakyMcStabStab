#include "EntityStateMoving.h"
#include "Entity.h"
#include "VectorFunctions.h"
#include "Constants.h"

EntityStateMoving::EntityStateMoving(Entity * owner) :
	EntityState(owner)
{

}

EntityStateMoving::~EntityStateMoving()
{
}

void EntityStateMoving::registerEvents()
{
}

void EntityStateMoving::unregisterEvents()
{
}

void EntityStateMoving::observe(const sf::Event & _event)
{
}

void EntityStateMoving::entry()
{
	mOwner->setForward(mOwner->getPosition() - mTargetPosition);
}

void EntityStateMoving::exit()
{
}

void EntityStateMoving::update(const sf::Time & deltaTime)
{
	bool goalReached;
	sf::Vector2f newPos = VectorFunctions::lerp(mOwner->getPosition(), mTargetPosition, deltaTime.asSeconds() * Constants::NPCs::MoveSpeed, goalReached);
	mOwner->setPosition(newPos);
	if (mOwner->getEyes()->detectTarget(newPos))
	{
		startChasing();
	}
	else if (goalReached)
	{
		startIdle(Constants::NPCs::IdleTime);
	}
}

void EntityStateMoving::setTargetPosition(const sf::Vector2f & targetPos)
{
	mTargetPosition = targetPos;
}

void EntityStateMoving::die()
{
	transition(this, mOwner->getDeadState());
}

void EntityStateMoving::startChasing()
{
	transition(this, mOwner->geChaseState());
}

void EntityStateMoving::startIdle(float idleTime)
{
	mOwner->getIdleState()->setIdleTimer(idleTime);
	transition(this, mOwner->getIdleState());
}
