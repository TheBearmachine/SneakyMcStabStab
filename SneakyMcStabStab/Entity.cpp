#include "Entity.h"
#include "EntityState.h"
#include <SFML/Graphics/RenderTarget.hpp>

static const float RADIUS = 7.0f;
static const float THICKNESS = 1.5f;

Entity::Entity() :
	mEntityStatePossess(this)
{
	mSprite.setFillColor(sf::Color::Red);
	mSprite.setOutlineColor(sf::Color::Black);
	mSprite.setRadius(RADIUS);
	mSprite.setOutlineThickness(THICKNESS);
	float diameter = mSprite.getLocalBounds().width;
	mSprite.setOrigin(-diameter / 2.0f, -diameter / 2.0f);
}

Entity::~Entity()
{

}

void Entity::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(mHands, states);
	target.draw(mSprite, states);
}

void Entity::update(const sf::Time & deltaTime)
{
	if (mCurrentEntityState)
		mCurrentEntityState->update(deltaTime);
}

void Entity::setCurrentState(EntityState * state)
{
	mCurrentEntityState = state;
}

EntityState * Entity::getCurrentEntityState()
{
	return mCurrentEntityState;
}

void Entity::setEventManager(EventManager * eventManager)
{
	mEntityStatePossess.setEventManager(eventManager);
}

EntityHands * Entity::getHands()
{
	return &mHands;
}

float Entity::getRadius() const
{
	return mSprite.getRadius() + mSprite.getOutlineThickness();
}

void Entity::onCollision(const sf::Vector2f & penetration)
{
}

void Entity::setForward(const sf::Vector2f & v)
{
	mForward = v;
}

sf::Vector2f Entity::getForward() const
{
	return mForward;
}

void Entity::possess()
{
	setCurrentState(&mEntityStatePossess);
	mSprite.setFillColor(sf::Color::Green);
	mHands.setColor(sf::Color::Green);
}
