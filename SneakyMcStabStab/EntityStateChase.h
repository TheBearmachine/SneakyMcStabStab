#pragma once
#include "EntityState.h"

class Entity;

class EntityStateChase : public EntityState
{
public:
	EntityStateChase(Entity* owner);
	virtual ~EntityStateChase();

	//Event Observer
	virtual void registerEvents() override;
	virtual void unregisterEvents() override;
	virtual void observe(const sf::Event& _event) override;

	//Entity State
	virtual void entry() override;
	virtual void exit() override;
	virtual void update(const sf::Time &deltaTime) override;

	// Transition functions
	virtual void die() override;
	virtual void startMoving(const sf::Vector2f &position) override;


private:
	float mTimer;
};