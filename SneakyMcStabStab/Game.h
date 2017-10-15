#pragma once
#include "SFML/Graphics/RenderWindow.hpp"
#include "EventManager.h"
#include "GameStateMenu.h"
#include "GameStateLevel.h"

class Game
{
public:
	Game();
	~Game();

	void run();

	void setCurrentState(GameState* state);
	GameStateMenu* getGameStateMenu();
	GameStateLevel* getGameStateLevel();

	sf::RenderWindow* getRenderWindow();
	EventManager* getEventManager();

private:
	void handleEvents();

	GameStateMenu mGameStateMenu;
	GameStateLevel mGameStateLevel;

	GameState* mCurrentGameState;
	sf::RenderWindow mWindow;
	EventManager mEventManager;
};