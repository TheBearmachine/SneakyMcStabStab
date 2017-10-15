#include "EntityHands.h"
#include <SFML/Graphics/RenderTarget.hpp>

static const float RADIUS = 2.0f;
static const float THICKNESS = 1.0f;

EntityHands::EntityHands() :
	mHand()
{
	for (size_t i = 0; i < 2; i++)
	{
		mHand[i].setRadius(RADIUS);
		mHand[i].setOutlineThickness(THICKNESS);
		mHand[i].setOutlineColor(sf::Color::Black);
		mHand[i].setFillColor(sf::Color::Red);
		mHand[i].setPosition(i * RADIUS * 10.0f - RADIUS * 5.0f, RADIUS * 5.0f);
		float diameter = mHand[i].getLocalBounds().width;
		mHand[i].setOrigin(-diameter / 2.0f, -diameter / 2.0f);
	}
	/*mHand[0].setPosition(-10, 0);
	mHand[1].setPosition(10, 0);*/
}

EntityHands::~EntityHands()
{
}

void EntityHands::setColor(const sf::Color & color)
{
	for (size_t i = 0; i < 2; i++)
	{
		mHand[i].setFillColor(color);
	}
}

void EntityHands::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	sf::RenderStates states2 = states;
	states.transform *= mHand[1].getTransform();
	target.draw(mWeapon, states2);
	target.draw(mHand[0], states);
	target.draw(mHand[1], states);
}
