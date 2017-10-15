#include "Game.h"
#include "GameStateMenu.h"
#include <SFML/Window/Event.hpp>

static const char* APP_TITLE = "Sneaky McStabStab";

Game::Game() :
	mGameStateMenu(this),
	mGameStateLevel(this)
{

	//sf::VideoMode vm = sf::VideoMode::getDesktopMode();
	sf::VideoMode vm(640, 480);
	sf::ContextSettings cs;
	cs.antialiasingLevel = 8U;
	mWindow.create(vm, APP_TITLE, 7U, cs);
}

Game::~Game()
{
	mCurrentGameState->exit();
}

void Game::run()
{
	sf::Clock clock;

	mCurrentGameState = &mGameStateMenu;
	mCurrentGameState->entry();

	while (mWindow.isOpen())
	{
		if (mCurrentGameState)
		{
			sf::Time time = clock.restart();

			handleEvents();
			mCurrentGameState->update(time);

			mWindow.clear();
			mCurrentGameState->draw(mWindow);
			mWindow.display();
		}
	}
}

void Game::setCurrentState(GameState *state)
{
	mCurrentGameState = state;
}

GameStateMenu * Game::getGameStateMenu()
{
	return &mGameStateMenu;
}

GameStateLevel * Game::getGameStateLevel()
{
	return &mGameStateLevel;
}

sf::RenderWindow * Game::getRenderWindow()
{
	return &mWindow;
}

EventManager * Game::getEventManager()
{
	return &mEventManager;
}

void Game::handleEvents()
{
	sf::Event currEvent;
	while (mWindow.pollEvent(currEvent))
	{
		mEventManager.notify(currEvent);
	}
}
