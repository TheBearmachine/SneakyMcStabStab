#pragma once
#include <SFML/System/Time.hpp>
#include "EventObserver.h"
#include <SFML/System/Vector2.hpp>

class EventManager;
class Entity;
namespace sf
{
	class RenderTarget;
}

class EntityState :public EventObserver
{
public:
	EntityState(Entity* owner) : mOwner(owner) {}
	virtual ~EntityState() {}

	//Event Observer
	virtual void registerEvents() = 0;
	virtual void unregisterEvents() = 0;
	virtual void observe(const sf::Event& _event) = 0;

	//Entity State
	virtual void entry() = 0;
	virtual void exit() = 0;
	virtual void transition(EntityState* from, EntityState* to);
	virtual void update(const sf::Time &deltaTime) = 0;

	// Transition functions
	virtual void die() {}
	virtual void startIdle(float idleTime) {}
	virtual void startMoving(const sf::Vector2f &position) {}
	virtual void startChasing() {}

protected:
	Entity* mOwner;

};