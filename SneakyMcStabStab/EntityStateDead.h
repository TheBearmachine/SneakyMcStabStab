#pragma once
#include "EntityState.h"

class Entity;

class EntityStateDead : public EntityState
{
public:
	EntityStateDead(Entity* owner);
	virtual ~EntityStateDead();

	//Event Observer
	virtual void registerEvents() override;
	virtual void unregisterEvents() override;
	virtual void observe(const sf::Event& _event) override;

	//Entity State
	virtual void entry() override;
	virtual void exit() override;
	virtual void update(const sf::Time &deltaTime) override;

private:

};