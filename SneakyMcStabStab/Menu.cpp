#include "Menu.h"
#include <SFML/Graphics/RenderTarget.hpp>

Menu::Menu()
{
	mBackground.setFillColor(sf::Color(255, 55, 55, 100));
	mBackground.setOutlineColor(sf::Color(255, 55, 55, 200));
	mBackground.setOutlineThickness(3.0f);
	mBackground.setPosition(-10.0f, -10.0f);
}

Menu::~Menu()
{
	clearButtons();
}

void Menu::setup(EventManager * eventManager, sf::RenderTarget * window)
{
	mEventManager = eventManager;
	mWindow = window;
}

void Menu::addButton(IButtonListener * listener, const std::string &buttonText, const std::string & textureName, unsigned int action)
{
	if (!mEventManager || !mWindow) return;

	Button* button = new Button(listener, textureName, action);
	button->setPosition(0.0f, mSize.y);
	button->setup(mEventManager, mWindow);
	button->setTextString(buttonText);
	mButtons.push_back(button);

	mSize.y += button->getSpriteBounds().height + 5.0f;
	mSize.x = fmaxf(button->getSpriteBounds().width, mSize.x);
	mBackground.setSize(mSize + sf::Vector2f(20.0f, 20.0f));
}

void Menu::clearButtons()
{
	while (!mButtons.empty())
	{
		mButtons.back()->unregisterEvents();
		delete mButtons.back();
		mButtons.pop_back();
	}
}

void Menu::setPosition(float x, float y)
{
	Menu::setPosition(sf::Vector2f(x, y));
}

void Menu::setPosition(const sf::Vector2f & pos)
{
	Transformable::setPosition(pos);
	setGlobalPosition(pos);
}

sf::Vector2f Menu::getSize() const
{
	return mSize;
}

void Menu::registerButtons()
{
	for (auto b : mButtons)
		b->registerEvents();
}

void Menu::unregisterButtons()
{
	for (auto b : mButtons)
		b->unregisterEvents();
}

void Menu::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	target.draw(mBackground, states);
	for (auto b : mButtons)
		target.draw(*b, states);
}

void Menu::setGlobalPosition(const sf::Vector2f & pos)
{
	mGlobalPosition = pos;
	for (auto b : mButtons)
	{
		b->setGlobalPosition(mGlobalPosition);
	}
}
