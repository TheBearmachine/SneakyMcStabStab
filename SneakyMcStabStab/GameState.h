#pragma once
#include <SFML/System/Time.hpp>
#include "EventObserver.h"

class Game;
namespace sf
{
	class RenderTarget;
}

class GameState : public EventObserver
{
public:
	GameState(Game* owner) :mOwner(owner) {}
	virtual ~GameState() {}

	//Event Observer
	virtual void registerEvents() = 0;
	virtual void unregisterEvents() = 0;
	virtual void observe(const sf::Event& _event) = 0;

	//Game State
	virtual void entry() = 0;
	virtual void exit() = 0;
	virtual void transition(GameState* from, GameState* to);
	virtual void update(const sf::Time &deltaTime) = 0;
	virtual void draw(sf::RenderTarget &window) const = 0;

	// Transition functions
	virtual void enterLevel(size_t level) = 0;

protected:
	Game* mOwner;
};