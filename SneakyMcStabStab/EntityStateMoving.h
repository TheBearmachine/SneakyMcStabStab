#pragma once
#include "EntityState.h"

class Entity;

class EntityStateMoving: public EntityState
{
public:
	EntityStateMoving(Entity* owner);
	virtual ~EntityStateMoving();

	//Event Observer
	virtual void registerEvents() override;
	virtual void unregisterEvents() override;
	virtual void observe(const sf::Event& _event) override;

	//Entity State
	virtual void entry() override;
	virtual void exit() override;
	virtual void update(const sf::Time &deltaTime) override;

	void setTargetPosition(const sf::Vector2f &targetPos);

private:
	sf::Vector2f mTargetPosition;
};