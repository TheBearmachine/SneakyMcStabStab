#pragma once
#include "EntityState.h"


class EntityStatePossess : public EntityState
{
public:
	EntityStatePossess(Entity* owner);
	virtual ~EntityStatePossess();

	//Event Observer
	virtual void registerEvents() override;
	virtual void unregisterEvents() override;
	virtual void observe(const sf::Event& _event) override;

	//Entity State
	virtual void entry() override;
	virtual void exit() override;
	virtual void update(const sf::Time &deltaTime) override;

	void setEventManager(EventManager* eventManager);

	// Transition functions
	virtual void die() override;

private:
	EventManager* mEventManager;
};