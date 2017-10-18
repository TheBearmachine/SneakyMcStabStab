#include "EntityStateIdle.h"
#include "Entity.h"
#include "VectorFunctions.h"
#include "Constants.h"

EntityStateIdle::EntityStateIdle(Entity * owner) :
	EntityState(owner),
	mIdleTimer(Constants::NPCs::IdleTime), mIdleTimerMax(Constants::NPCs::IdleTime),
	mInitForward(0.0f, 1.0f)
{
}

EntityStateIdle::~EntityStateIdle()
{
}

void EntityStateIdle::registerEvents()
{
}

void EntityStateIdle::unregisterEvents()
{
}

void EntityStateIdle::observe(const sf::Event & _event)
{
}

void EntityStateIdle::entry()
{
	mInitForward = mOwner->getForward();
}

void EntityStateIdle::exit()
{
}

void EntityStateIdle::update(const sf::Time & deltaTime)
{
	mIdleTimer -= deltaTime.asSeconds();
	float fancyThing = sinf((mIdleTimer / mIdleTimerMax) * Constants::NPCs::IdleTime * PI) * 25;
	VectorRotation rot(VectorRotation::inDegrees(fancyThing));
	rot = (VectorRotation(mInitForward) * rot).toVector();

	if (mOwner->getEyes()->detectTarget(rot.toVector()))
	{
		// Start chasing
		startChasing();
	}

	else if (mIdleTimer <= 0.0f)
	{
		mOwner->cyclePatrolPoints();
		startMoving(mOwner->getNextPatrolPoint());
	}
}

void EntityStateIdle::setIdleTimer(float idleTimer)
{
	mIdleTimerMax = mIdleTimer = idleTimer;
}

void EntityStateIdle::die()
{
	transition(this, mOwner->getDeadState());
}

void EntityStateIdle::startMoving(const sf::Vector2f & position)
{
	mOwner->getMovingState()->setTargetPosition(position);
	transition(this, mOwner->getMovingState());
}

void EntityStateIdle::startChasing()
{
	transition(this, mOwner->geChaseState());
}
