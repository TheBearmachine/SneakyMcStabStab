#pragma once
#include "GameState.h"
#include "EntityManager.h"

class EventManager;

class GameStateLevel : public GameState
{
public:
	GameStateLevel(Game* owner);
	virtual ~GameStateLevel();

	virtual void entry() override;
	virtual void exit() override;
	virtual void update(const sf::Time &deltaTime);
	virtual void draw(sf::RenderTarget &window) const;

	//Event Observer
	virtual void registerEvents();
	virtual void unregisterEvents();
	virtual void observe(const sf::Event& _event);

	void setEventManager(EventManager* eventManager);

	// Transition functions
	virtual void enterLevel(size_t level);

private:
	void setupLevel(size_t level);
	void setupLevel1();

	EntityManager mEntityManager;
	EventManager* mEventManager;
	size_t mCurrentLevel;
};