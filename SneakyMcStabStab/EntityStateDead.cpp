#include "EntityStateDead.h"
#include "Entity.h"

EntityStateDead::EntityStateDead(Entity * owner) :
	EntityState(owner)
{

}

EntityStateDead::~EntityStateDead()
{
}

void EntityStateDead::registerEvents()
{
}

void EntityStateDead::unregisterEvents()
{
}

void EntityStateDead::observe(const sf::Event & _event)
{
}

void EntityStateDead::entry()
{
	mOwner->getEyes()->setDrawSight(false);
}

void EntityStateDead::exit()
{
	mOwner->getEyes()->setDrawSight(true);
}

void EntityStateDead::update(const sf::Time & deltaTime)
{

}
