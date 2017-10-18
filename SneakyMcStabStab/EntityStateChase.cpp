#include "EntityStateChase.h"
#include "Entity.h"
#include "VectorFunctions.h"
#include "Constants.h"

static const float CHASE_TIMER_MAX = 2.0f;

EntityStateChase::EntityStateChase(Entity * owner) :
	EntityState(owner)
{
}

EntityStateChase::~EntityStateChase()
{
}

void EntityStateChase::registerEvents()
{
}

void EntityStateChase::unregisterEvents()
{
}

void EntityStateChase::observe(const sf::Event & _event)
{
}

void EntityStateChase::entry()
{
	mTimer = CHASE_TIMER_MAX;
}

void EntityStateChase::exit()
{
}

void EntityStateChase::update(const sf::Time & deltaTime)
{
	mTimer -= deltaTime.asSeconds();
	sf::Vector2f newPos = mOwner->getEyes()->getLastKnownPlayerPosition() - mOwner->getPosition();
	mOwner->setForward(newPos);
	if (mOwner->getEyes()->detectTarget(newPos))
		mTimer = CHASE_TIMER_MAX;

	// Check to see if the target is close enough to attack
	if (VectorFunctions::vectorMagnitude(newPos) < Constants::NPCs::AttackDistance)
	{
		mOwner->getHands()->stab();
	}

	bool goalReached;
	newPos = VectorFunctions::lerp(mOwner->getPosition(), mOwner->getEyes()->getLastKnownPlayerPosition(), deltaTime.asSeconds() * Constants::NPCs::ChaseSpeed, goalReached);
	mOwner->setPosition(newPos);

	if (mTimer <= 0.0f)
	{
		startMoving(mOwner->getNextPatrolPoint());
	}
}

void EntityStateChase::die()
{
	transition(this, mOwner->getDeadState());
}

void EntityStateChase::startMoving(const sf::Vector2f & position)
{
	mOwner->getMovingState()->setTargetPosition(position);
	transition(this, mOwner->getMovingState());
}
