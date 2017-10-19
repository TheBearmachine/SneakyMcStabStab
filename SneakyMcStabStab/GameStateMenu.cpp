#include "GameStateMenu.h"
#include "Game.h"
#include "Constants.h"
#include "ResourceManager.h"
#include "VectorRotation.h"

static const std::string BUTTON = "Button.png";
static const std::string TITLE_TEXTURE = Constants::Filepaths::ImagesFolder + "Title.png";
static const std::string FONT = Constants::Filepaths::FontsFolder + "sui_generis_rg.ttf";

GameStateMenu::GameStateMenu(Game * owner) :
	GameState(owner), mMenu(), mTimer(0.0f)
{
	mMenu.setup(mOwner->getEventManager(), mOwner->getRenderWindow());
	mMenu.addButton(this, "Start Game", Constants::Filepaths::ImagesFolder + BUTTON, StartGame);
	mMenu.addButton(this, "Exit Game", Constants::Filepaths::ImagesFolder + BUTTON, ExitGame);

	mTitle.setTexture(ResourceManager::getInstance().getTexture(TITLE_TEXTURE));
	mTitle.setOrigin(mTitle.getLocalBounds().width / 2.0f, mTitle.getLocalBounds().height / 2.0f);
	mHelpText.setFont(ResourceManager::getInstance().getFont(FONT));
	mHelpText.setCharacterSize(32U);
	mHelpText.setString("Move with WASD\nStab with Space\nSneak with Shift\nDon't get caught!");
	mHelpText.setFillColor(sf::Color::Green);
}

GameStateMenu::~GameStateMenu()
{
	unregisterEvents();
}

void GameStateMenu::entry()
{
	// Convenience
	mWindow = mOwner->getRenderWindow();
	float winWidth = (float)mWindow->getSize().x;
	mMenu.setPosition((winWidth / 2.5f) - mMenu.getSize().x, 200.0f);
	float textWidth = mHelpText.getGlobalBounds().width + 10.0f;
	mHelpText.setPosition(winWidth - textWidth, 200.0f);
	float titleHeight = mTitle.getGlobalBounds().height;
	mTitle.setPosition(winWidth / 2.0f, titleHeight / 2.0f);
	//

	registerEvents();
}

void GameStateMenu::exit()
{
	unregisterEvents();
}

void GameStateMenu::update(const sf::Time & deltaTime)
{
	mTimer += deltaTime.asSeconds();
	mTitle.setScale(1 + sinf(mTimer) * 0.1f, 1 + cosf(mTimer) * 0.1f);
	mEntityManager.update(deltaTime);
}

void GameStateMenu::draw(sf::RenderTarget & window) const
{
	mEntityManager.draw(window);
	window.draw(mMenu);
	window.draw(mTitle);
	window.draw(mHelpText);
}

void GameStateMenu::buttonAction(unsigned int action)
{
	switch (action)
	{
	case MenuActions::StartGame:
		enterLevel(1U);
		break;

	/*case MenuActions::Help:

		break;*/

	case MenuActions::ExitGame:
		mOwner->getRenderWindow()->close();
		break;

	default:
		break;
	}
}

void GameStateMenu::registerEvents()
{
	mEntityManager.registerEntities();
	mMenu.registerButtons();
}

void GameStateMenu::unregisterEvents()
{
	mEntityManager.unregisterEntities();
	mMenu.unregisterButtons();
}

void GameStateMenu::observe(const sf::Event & _event)
{
	if (_event.type == sf::Event::EventType::Closed)
		mOwner->getRenderWindow()->close();
}

void GameStateMenu::enterLevel(size_t level)
{
	transition(this, mOwner->getGameStateLevel());
	mOwner->getGameStateLevel()->enterLevel(level);
}
