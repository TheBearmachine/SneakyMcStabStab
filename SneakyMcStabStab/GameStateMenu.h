#pragma once
#include "GameState.h"
#include "EntityManager.h"
#include "Menu.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Text.hpp>

class GameStateMenu : public GameState, public IButtonListener
{
public:
	GameStateMenu(Game* owner);
	virtual ~GameStateMenu();

	virtual void entry() override;
	virtual void exit() override;
	virtual void update(const sf::Time &deltaTime);
	virtual void draw(sf::RenderTarget &window) const;

	void buttonAction(unsigned int action) override;

	//Event Observer
	virtual void registerEvents();
	virtual void unregisterEvents();
	virtual void observe(const sf::Event& _event);

	// Transition functions
	virtual void enterLevel(size_t level);

private:
	enum MenuActions
	{
		StartGame,
		ExitGame
	};

	EntityManager mEntityManager;
	float mTimer;
	sf::Sprite mTitle;
	sf::Text mHelpText;
	sf::RenderTarget* mWindow;
	Menu mMenu;
};