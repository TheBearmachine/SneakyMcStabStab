#pragma once
#include "EntityState.h"

class Entity;

class EntityStateIdle : public EntityState
{
public:
	EntityStateIdle(Entity* owner);
	virtual ~EntityStateIdle();

	//Event Observer
	virtual void registerEvents() override;
	virtual void unregisterEvents() override;
	virtual void observe(const sf::Event& _event) override;

	//Entity State
	virtual void entry() override;
	virtual void exit() override;
	virtual void update(const sf::Time &deltaTime) override;

	void setIdleTimer(float idleTimer);

	// Transition functions
	virtual void die() override;
	virtual void startMoving(const sf::Vector2f &position) override;

private:
	sf::Vector2f mInitForward;
	float mIdleTimer;
	float mIdleTimerMax;
};