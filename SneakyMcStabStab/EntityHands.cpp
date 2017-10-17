#include "EntityHands.h"
#include "VectorRotation.h"
#include <SFML/Graphics/RenderTarget.hpp>

static const float RADIUS = 4.0f;
static const float THICKNESS = 1.0f;
static const float HAND_DISTANCE = 4.0f;

EntityHands::EntityHands() :
	mHand()
{
	for (size_t i = 0; i < 2; i++)
	{
		mHand[i].setOutlineThickness(-THICKNESS);
		mHand[i].setRadius(RADIUS);
		mHand[i].setOutlineColor(sf::Color::Black);
		mHand[i].setFillColor(sf::Color::Red);
		float diameter = mHand[i].getLocalBounds().width;
		mHand[i].setOrigin(diameter / 2.0f, diameter / 2.0f);
		mHand[i].setPosition(i * RADIUS * HAND_DISTANCE - RADIUS * HAND_DISTANCE * 0.5f, RADIUS * HAND_DISTANCE * 0.5f);
	}
	mWeapon.setSize(sf::Vector2f(1.8f, 7.0f));
	mWeapon.setFillColor(sf::Color(125, 125, 125));
	float diameter = mHand[1].getLocalBounds().width;
	float width = mWeapon.getLocalBounds().width;
	mWeapon.setOrigin(-diameter / 2.0f + width,/* -diameter / 2*/.0f);
	mWeapon.setPosition(0.0f, RADIUS + THICKNESS);
	mDefaultHandPosition = mHand[1].getPosition();
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

void EntityHands::stab()
{
	if (!mBusy)
	{
		mBusy = true;
		mCurrentAction = Stab;
		mTimer = .5f;
	}
}

void EntityHands::swing()
{
	if (!mBusy)
	{
		mBusy = true;
		mCurrentAction = Swing;
	}
}

void EntityHands::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	sf::RenderStates states2 = states;
	states2.transform *= mHand[1].getTransform();
	target.draw(mWeapon, states2);
	target.draw(mHand[0], states);
	target.draw(mHand[1], states);
}

void EntityHands::update(const sf::Time & deltaTime)
{
	if (!mBusy) return;

	mTimer -= deltaTime.asSeconds();
	if (mTimer <= 0.0f)
	{
		mBusy = false;
		mHand[1].setPosition(mDefaultHandPosition);
		return;
	}
	switch (mCurrentAction)
	{
	case Stab:
		mHand[1].setPosition(mDefaultHandPosition + sf::Vector2f(0.0f, sinf(mTimer * 2.0f * PI) * 5.0f));
		break;

	case Swing:

		break;
	}
}

bool EntityHands::getAttacking() const
{
	return mBusy;
}

sf::FloatRect EntityHands::getWeaponRect(sf::Transform transform)
{
	transform *= getTransform();
	transform *= mHand[1].getTransform();
	transform *= mWeapon.getTransform();
	return transform.transformRect(mWeapon.getLocalBounds());
}
