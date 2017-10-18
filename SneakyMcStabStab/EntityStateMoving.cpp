#include "EntityStateMoving.h"
#include "Entity.h"

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
}

void EntityStateMoving::exit()
{
}

void EntityStateMoving::update(const sf::Time & deltaTime)
{
	//mOwner->move();
}

void EntityStateMoving::setTargetPosition(const sf::Vector2f & targetPos)
{
	mTargetPosition = targetPos;
}
